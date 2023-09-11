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

#include <stdlib.h>

/**
  @ingroup groupFastMath
 */

/**
  @addtogroup divide
  @{
 */

/**
  @brief         Fixed point division
  @param[in]     numerator    Numerator
  @param[in]     denominator  Denominator
  @param[out]    quotient     Quotient value normalized between -1.0 and 1.0
  @param[out]    shift        Shift left value to get the unnormalized quotient
  @return        error status

  When dividing by 0, an error MIPS_MATH_NANINF is returned. And the quotient is forced
  to the saturated negative or positive value.
 */

mips_status mips_divide_q31(q31 numerator,
  q31 denominator,
  q31 *quotient,
  int16_t *shift)
{
  int16_t sign=0;
  q63 temp;
  int16_t shiftForNormalizing;

  *shift = 0;

  sign = (numerator>>31) ^ (denominator>>31);

  if (denominator == 0)
  {
     if (sign)
     {
        *quotient = 0x80000000;
     }
     else
     {
        *quotient = 0x7FFFFFFF;
     }
     return(MIPS_MATH_NANINF);
  }

  mips_abs_q31(&numerator,&numerator,1);
  mips_abs_q31(&denominator,&denominator,1);

  temp = ((q63)numerator << 31) / ((q63)denominator);

  shiftForNormalizing= 32 - __CLZ(temp >> 31);
  if (shiftForNormalizing > 0)
  {
     *shift = shiftForNormalizing;
     temp = temp >> shiftForNormalizing;
  }

  if (sign)
  {
    temp = -temp;
  }

  *quotient=(q31)temp;

  return(MIPS_MATH_SUCCESS);
}

/**
  @} end of divide group
 */