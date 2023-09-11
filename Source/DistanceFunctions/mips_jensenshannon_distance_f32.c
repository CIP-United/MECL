
/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_jensenshannon_distance_f32.c
 * Description:  Jensen-Shannon distance between two vectors
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

#include "dsp/distance_functions.h"
#include <limits.h>
#include <math.h>


/**
  @addtogroup JensenShannon
  @{
 */

/// @private
__STATIC_INLINE f32 rel_entr(f32 x, f32 y)
{
    return (x * logf(x / y));
}


/**
 * @brief        Jensen-Shannon distance between two vectors
 *
 * This function is assuming that elements of second vector are > 0
 * and 0 only when the corresponding element of first vector is 0.
 * Otherwise the result of the computation does not make sense
 * and for speed reasons, the cases returning NaN or Infinity are not
 * managed.
 *
 * When the function is computing x log (x / y) with x == 0 and y == 0,
 * it will compute the right result (0) but a division by zero will occur
 * and should be ignored in client code.
 *
 * @param[in]    pA         First vector
 * @param[in]    pB         Second vector
 * @param[in]    blockSize  vector length
 * @return distance
 *
 */


f32 mips_jensenshannon_distance_f32(const f32 *pA,const f32 *pB, uint32_t blockSize)
{
    f32 left, right,sum, result, tmp;
    uint32_t i;

    left = 0.0f; 
    right = 0.0f;
    for(i=0; i < blockSize; i++)
    {
      tmp = (pA[i] + pB[i]) / 2.0f;
      left  += rel_entr(pA[i], tmp);
      right += rel_entr(pB[i], tmp);
    }


    sum = left + right;
    mips_sqrt_f32(sum/2.0f, &result);
    return(result);

}

/**
 * @} end of JensenShannon group
 */
