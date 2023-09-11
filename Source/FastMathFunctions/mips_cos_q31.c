/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_cos_q31.c
 * Description:  Fast cosine calculation for Q31 values
 *
 * $Date:        31 Augest 2023
 * $Revision:    V1.0.0
 *
 * -------------------------------------------------------------------- */
/*
 * Copyright (C) 2010-2021 ARM Limited or its affiliates. All rights reserved.
 * Copyright (C) 2023 CIP United Co. Ltd. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "dsp/fast_math_functions.h"
#include "mips_common_tables.h"

/**
  @ingroup groupFastMath
 */

/**
  @addtogroup cos
  @{
 */

/**
  @brief         Fast approximation to the trigonometric cosine function for Q31 data.
  @param[in]     x  Scaled input value in radians
  @return        cos(x)

  The Q31 input value is in the range [0 +0.9999] and is mapped to a radian value in the range [0 2*PI).
 */

q31 mips_cos_q31(
  q31 x)
{
  q31 cosVal;                                  /* Temporary input, output variables */
  int32_t index;                                 /* Index variable */
  q31 a, b;                                    /* Two nearest output values */
  q31 fract;                                   /* Temporary values for fractional values */

  /* add 0.25 (pi/2) to read sine table */
  x = (uint32_t)x + 0x20000000;
  if (x < 0)
  { /* convert negative numbers to corresponding positive ones */
    x = (uint32_t)x + 0x80000000;
  }

  /* Calculate the nearest index */
  index = (uint32_t)x >> FAST_MATH_Q31_SHIFT;

  /* Calculation of fractional value */
  fract = (x - (index << FAST_MATH_Q31_SHIFT)) << 9;

  /* Read two nearest values of input value from the sin table */
  a = sinTable_q31[index];
  b = sinTable_q31[index+1];

  /* Linear interpolation process */
  cosVal = (q63) (0x80000000 - fract) * a >> 32;
  cosVal = (q31) ((((q63) cosVal << 32) + ((q63) fract * b)) >> 32);

  /* Return output value */
  return (cosVal << 1);
}

/**
  @} end of cos group
 */
