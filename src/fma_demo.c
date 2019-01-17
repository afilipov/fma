/**
 * Copyright (c) 2017 Atanas Filipov <it.feel.filipov@gmail.com>.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include "fast_moving_average.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    avr_t avr_val;
    input_t new_val;

    /* initialize random seed: */
    srand(time(NULL));

    fma_init(0);

    for (unsigned int i=0; i < 1024; i++) {
        new_val = rand() % MAX_INPUT_VALUE;

#if !defined(INPUT_RANGE_U32) && !defined(INPUT_RANGE_U16) && \
    !defined(INPUT_RANGE_U8)
        if (new_val & 0x1) {
            new_val *= -1;
        }
#endif

        avr_val = fma_calc(new_val);
#ifdef GNUPLOT_FORMAT
        /* Example"
         * plot "data.txt" using 1:2 title 'Input' with lines, "data.txt"\
         *  using 1:3 title 'Average' with lines
         */
        printf("%d %d %d\n", i, (int)new_val, (int)avr_val);
#else
        printf("New value:% 12d ==> Average:% 12d\n", (int)new_val,
               (int)avr_val);
#endif
    }

    return EXIT_SUCCESS;
}

