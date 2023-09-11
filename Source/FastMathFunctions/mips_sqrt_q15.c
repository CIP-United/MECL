/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_sqrt_q15.c
 * Description:  Q15 square root function
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

#define Q12QUARTER 0x2000

/**
  @ingroup groupFastMath
 */

/**
  @addtogroup SQRT
  @{
 */

/**
  @brief         Q15 square root function.
  @param[in]     in    input value.  The range of the input value is [0 +1) or 0x0000 to 0x7FFF
  @param[out]    pOut  points to square root of input value
  @return        execution status
                   - \ref MIPS_MATH_SUCCESS        : input value is positive
                   - \ref MIPS_MATH_ARGUMENT_ERROR : input value is negative; *pOut is set to 0
 */

mips_status mips_sqrt_q15(
  q15 in,
  q15 * pOut)
{
  q15 number, var1, signBits1,temp;

  number = in;

  /* If the input is a positive number then compute the signBits. */
  if (number > 0)
  {
    signBits1 = __CLZ(number) - 17;

    /* Shift by the number of signBits1 */
    if ((signBits1 % 2) == 0)
    {
      number = number << signBits1;
    }
    else
    {
      number = number << (signBits1 - 1);
    }
    /* Start value for 1/sqrt(x) for the Newton iteration */
    var1 = sqrt_initial_lut_q15[(number>> 11) - (Q12QUARTER >> 11)];

    /* 0.5 var1 * (3 - number * var1 * var1) */
    /* 1st iteration */

   temp = ((q31) var1 * var1) >> 12;
   temp = ((q31) number * temp) >> 15;
   temp = 0x3000 - temp; 
   var1 = ((q31) var1 * temp) >> 13;

   temp = ((q31) var1 * var1) >> 12;
   temp = ((q31) number * temp) >> 15;
   temp = 0x3000 - temp; 
   var1 = ((q31) var1 * temp) >> 13;

   temp = ((q31) var1 * var1) >> 12;
   temp = ((q31) number * temp) >> 15;
   temp = 0x3000 - temp; 
   var1 = ((q31) var1 * temp) >> 13;

    /* Multiply the inverse square root with the original value */

    var1 = ((q15) (((q31) number * var1) >> 12));

    /* Shift the output down accordingly */
    if ((signBits1 % 2) == 0)
    {
      var1 = var1 >> (signBits1 / 2);
    }
    else
    {
      var1 = var1 >> ((signBits1 - 1) / 2);
    }
    *pOut = var1;


    return (MIPS_MATH_SUCCESS);
  }
  /* If the number is a negative number then store zero as its square root value */
  else
  {
    *pOut = 0;

    return (MIPS_MATH_ARGUMENT_ERROR);
  }
}

/**
  @} end of SQRT group
 */
