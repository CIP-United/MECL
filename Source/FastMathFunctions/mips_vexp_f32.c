/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_vlog_f32.c
 * Description:  Fast vectorized log
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

#if defined(MIPS_MATH_MSA)
#include "mips_vec_math.h"
#endif

/**
  @ingroup groupFastMath
 */

/**
   @defgroup vexp Vector Exponential

   Compute the exp values of a vector of samples.
*/

/**
  @addtogroup vexp
  @{
 */

/**
  @brief         Floating-point vector of exp values.
  @param[in]     pSrc       points to the input vector
  @param[out]    pDst       points to the output vector
  @param[in]     blockSize  number of samples in each vector
  @return        none
 */
void mips_vexp_f32(
  const f32 * pSrc,
        f32 * pDst,
        uint32_t blockSize)
{
   uint32_t blkCnt; 

   blkCnt = blockSize;

   while (blkCnt > 0U)
   {
      /* C = log(A) */
  
      /* Calculate log and store result in destination buffer. */
      *pDst++ = expf(*pSrc++);
  
      /* Decrement loop counter */
      blkCnt--;
   }
}

/**
  @} end of vexp group
 */