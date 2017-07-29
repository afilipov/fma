# Define programs and commands.
SH     = sh
# Archive-maintaining program;
AR     = ar
# Program for doing assembly;
AS     = as
# Program for compiling C programs;
CC     = ${CROSS_COMPILE}gcc
# Command to remove a file;
RM     = rm -f
# Command make a file;
MAKE   = make
# Install program
INSTALL= install

# Target executable file name
TARGET = fma_demo

# Target library file name
OUTLIB  = fma

# Project
PRJDIR  = .
PRJINC  = $(PRJDIR)/include
PRJSRC  = $(PRJDIR)/src
PRJOBJ  = $(PRJDIR)/obj
PRJLIB  = $(PRJDIR)/lib
PRJBIN  = $(PRJDIR)/bin

EXTINC = $(PRJINC)

# Additional libraries "-lcommon"
EXTLIB =

# Place -I options here
INCLUDES = -I. $(addprefix -I,$(EXTINC))

# List C and CPP source files here. (C dependencies are automatically generated.)
SOURCES = \
	fast_moving_average.c	

# Add source directory prefix
ALLSOURCES = $(addprefix $(PRJSRC)/, $(SOURCES))

# Prepare "C" files list
CFILES   = $(filter %.c,   $(ALLSOURCES))

# Define "C" object files.
COBJS	= $(patsubst $(PRJSRC)/%,$(PRJOBJ)/%,$(CFILES:%.c=%.o))
# Define all object files.
OBJS	= $(COBJS)
# Define all dependencies
DEPS    = $(OBJS:%.o=%.d)

# Define output executable target
OUTBIN = $(PRJBIN)/$(TARGET)

# Define dynamic library file name
OUTDLIB = $(PRJLIB)/lib$(OUTLIB).so

# Define static library file name
OUTSLIB = $(PRJLIB)/lib$(OUTLIB).a

# Place -D or -U options here
DEF = -DNDEBUG -DIN_RANGE_S16 -DGNUPLOT_FORMAT

# Define CPU flags "-march=cpu-type"
CPU =

# Define specific MPU flags "-mno-fp-ret-in-387"
MPU =

# Define "C" standart
STD = -std=c99

# Global flags
OPT  = $(MPU) $(MPU) $(STD) -fPIC

# Generate dependencies
DEP  = -MMD

WRN  = -Wall -Wclobbered -Wempty-body -Wignored-qualifiers -Wmissing-field-initializers -Wsign-compare -Wtype-limits -Wuninitialized -Wno-deprecated-declarations

# Define only valid "C" optimization flags
COPT = $(OPT) -fomit-frame-pointer -fno-stack-check
# Define only valid "C" warnings flags
CWRN = $(WRN) \
	-Wmissing-parameter-type -Wold-style-declaration -Wimplicit-int -Wimplicit-function-declaration -Wimplicit -Wignored-qualifiers \
	-Wformat-nonliteral -Wcast-align -Wpointer-arith -Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes -Wmissing-declarations \
	-Wnested-externs -Wshadow -Wwrite-strings -Wfloat-equal -Woverride-init

# Extra flags to give to the C compiler.
CFLAGS = $(MCU) $(DEF) $(DEP) $(COPT) $(CWRN)

# Extra flags to give to the C compiler.
override CFLAGS += $(INCLUDES)

# Define global linker flags
EXFLAGS = $(EXTLIB)

# Linker flags to give to the linker.
override LDFLAGS = $(EXFLAGS) -Wl,--no-as-needed

# Special linker flags to build shared library
override SHFLAGS = $(EXFLAGS) -shared -s

# Executable not defined
ifeq ($(TARGET),)
 # Output library defined
 ifneq ($(OUTLIB),)
  all: $(OUTDLIB) $(OUTSLIB)
 else
  all:
	@echo "WARNING: Neither output, neither library defined!"
 endif
# Executable defined
else
 # Executable defined, but output library not defined
 ifeq ($(OUTLIB),)
  all: $(OUTBIN)
 # Executable and output library defined
 else
  all: $(OUTDLIB) $(OUTSLIB) $(OUTBIN)
 endif
endif

# Executable defined
ifneq ($(TARGET),)
 # Output library not defined
 ifeq ($(OUTLIB),)
  $(OUTBIN): $(OBJS)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) src/$(TARGET).c -o $(OUTBIN) $(LDFLAGS) $(OBJS)
 # Executable and output library defined
 else
  $(OUTBIN): $(OUTSLIB) $(OUTDLIB)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) src/$(TARGET).c -o $(OUTBIN) $(LDFLAGS) $(OUTDLIB)
 endif
endif

ifneq ($(OUTLIB),)
 $(OUTDLIB): $(OBJS)
	mkdir -p $(@D)
	$(CXX) -o $@ $^ $(SHFLAGS)

 $(OUTSLIB): $(OBJS)
	mkdir -p $(@D)
	$(AR) rcs -o $@ $^
endif

$(COBJS): $(PRJOBJ)/%.o: $(PRJSRC)/%.c
	mkdir -p $(@D)
	$(CC) -c -o $@ $< $(DEP) $(CFLAGS)

$(PRJBIN):
	mkdir -p $@

$(PRJOBJ):
	mkdir -p $@

$(PRJLIB):
	mkdir -p $@

install: ${OUTDLIB} ${OUTSLIB} ${OUTBIN}
ifneq ($(BINDIR),)
	$(INSTALL) -m 755 ${OUTBIN} $(BINDIR)
endif

ifneq ($(LIBDIR),)
	$(INSTALL) -m 755 ${OUTDLIB} $(LIBDIR)
	$(INSTALL) -m 755 ${OUTSLIB} $(LIBDIR)
endif

# Target: clean project.
clean:
	@echo Cleaning objects
	$(RM) -rf $(PRJOBJ)
	$(RM) $(PRJBIN)/$(TARGET).d

# Target: clean all.
distclean:
	@echo Cleaning all objects and executable
	$(RM) $(OBJS)
	$(RM) $(DEPS)

	$(RM) -rf $(PRJLIB)
	$(RM) -rf $(PRJBIN)
	$(RM) -rf $(PRJOBJ)

# Listing of phony targets.
.PHONY : all clean $(OUTDLIB) $(OUTSLIB) $(OUTBIN)

-include $(DEPS)
