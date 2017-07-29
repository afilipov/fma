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

#ifndef __FAST_MOVING_AVERAGE_H__
#define __FAST_MOVING_AVERAGE_H__

#include <limits.h>
#include <stdint.h>

#define MAX_ARRAY_SIZE 16U

#ifdef IN_RANGE_S32
 #define MIN_INPUT_VALUE INT_MIN
 #define MAX_INPUT_VALUE INT_MAX
 struct moving_average {
     int64_t pos: 4;
     int64_t sum:60;     /* Max value is 60 bits, MAX_ARRAY_SIZE * INT_MAX */
 }__attribute__((packed));
 typedef int32_t input_t;
 typedef int64_t avr_t;
#elif IN_RANGE_U32
 #define MIN_INPUT_VALUE 0
 #define MAX_INPUT_VALUE UINT_MAX
 struct moving_average {
     uint64_t pos: 4;
     uint64_t sum:60;    /* Max value is 60 bits, MAX_ARRAY_SIZE * UINT_MAX */
 }__attribute__((packed));
 typedef uint32_t input_t;
 typedef uint64_t avr_t;
#elif IN_RANGE_S16
 #define MIN_INPUT_VALUE SHRT_MIN
 #define MAX_INPUT_VALUE SHRT_MAX
 struct moving_average {
     int32_t pos: 4;
     int32_t sum:28;     /* Max value is 28 bits, MAX_ARRAY_SIZE * SHRT_MAX */
 }__attribute__((packed));
 typedef int16_t input_t;
 typedef int32_t avr_t;
#elif IN_RANGE_U16
 #define MIN_INPUT_VALUE 0
 #define MAX_INPUT_VALUE USHRT_MAX
 struct moving_average {
     uint32_t pos: 4;
     uint32_t sum:28;    /* Max value is 28 bits, MAX_ARRAY_SIZE * USHRT_MAX */
 }__attribute__((packed));
 typedef uint16_t input_t;
 typedef uint32_t avr_t;
#elif IN_RANGE_U8
 #define MIN_INPUT_VALUE 0
 #define MAX_INPUT_VALUE UCHAR_MAX
 struct moving_average {
     uint16_t pos: 4;
     uint16_t sum:12;    /* Max value is 12 bits, MAX_ARRAY_SIZE * UCHAR_MAX */
 }__attribute__((packed));
 typedef uint8_t  input_t;
 typedef uint16_t avr_t;
#else
 #define MIN_INPUT_VALUE SCHAR_MIN
 #define MAX_INPUT_VALUE SCHAR_MAX
 struct moving_average {
     int16_t pos: 4;
     int16_t sum:12;    /* Max value is 12 bits, MAX_ARRAY_SIZE * SCHAR_MIN */
 }__attribute__((packed));
 typedef int8_t  input_t;
 typedef int16_t avr_t;
#endif

typedef struct moving_average mov_avr_t;

avr_t fma_init(input_t initial_val);

avr_t fma_calc(input_t current_val);

#endif
