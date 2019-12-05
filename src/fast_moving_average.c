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

#ifdef INPUT_RANGE_S32
 static int32_t  array_avr[MAX_ARRAY_SIZE];
#elif INPUT_RANGE_U32
 static uint32_t array_avr[MAX_ARRAY_SIZE];
#elif INPUT_RANGE_S16
 static int16_t  array_avr[MAX_ARRAY_SIZE];
#elif INPUT_RANGE_U16
 static uint16_t array_avr[MAX_ARRAY_SIZE];
#elif INPUT_RANGE_U8
 static int8_t   array_avr[MAX_ARRAY_SIZE];
#else
 static uint8_t  array_avr[MAX_ARRAY_SIZE];
#endif

static mov_avr_t avr_data;

avr_t fma_init(input_t initial_val)
{
    avr_data.sum = 0;
    avr_data.pos = 0;

    for (unsigned int i=0; i < MAX_ARRAY_SIZE; i++) {
        array_avr[i] = initial_val;
        avr_data.sum += array_avr[i];
    }

    /* return initial average */
    return avr_data.sum / sizeof(array_avr);
}

avr_t fma_calc(input_t current_val)
{
  /* Subtract the oldest value from the sum */
  avr_data.sum -= array_avr[avr_data.pos];

  /* Assign the value to the position in the array */
  array_avr[avr_data.pos] = current_val;

  /* Add the new value to the sum */
  avr_data.sum += array_avr[avr_data.pos];

  /* increment the position */
  avr_data.pos++;

  /* calcluate the average */
  return avr_data.sum / sizeof(array_avr);
}
