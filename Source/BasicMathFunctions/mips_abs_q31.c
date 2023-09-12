/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_abs_q31.c
 * Description:  Q31 vector absolute value
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

#include "dsp/basic_math_functions.h"

/**
  @ingroup groupMath
 */

/**
  @addtogroup BasicAbs
  @{
 */

/**
  @brief         Q31 vector absolute value.
  @param[in]     pSrc       points to the input vector
  @param[out]    pDst       points to the output vector
  @param[in]     blockSize  number of samples in each vector
  @return        none

  @par           Scaling and Overflow Behavior
                   The function uses saturating arithmetic.
                   The Q31 value -1 (0x80000000) will be saturated to the maximum allowable positive value 0x7FFFFFFF.
 */

#if defined(MIPS_MATH_DSP)

void mips_abs_q31(
    const q31 * pSrc,
    q31 * pDst,
    uint32_t blockSize)
{
    uint32_t  blkCnt;           /* Loop counters */

    blkCnt = blockSize;

    while (blkCnt > 0U)
    {
        /*
         * C = |A|
         * Calculate absolute and then store the results in the destination buffer.
         */
        *pDst = _mips_absq_s_w(*pDst);
        /*
         * Decrement the blockSize loop counter
         */
        blkCnt--;
        /*
         * Advance vector source and destination pointers
         */
        pSrc++;
        pDst++;
    }
}

#else
void mips_abs_q31(
  const q31 * pSrc,
        q31 * pDst,
        uint32_t blockSize)
{
        uint32_t blkCnt;                               /* Loop counter */
        q31 in;                                        /* Temporary variable */

#if defined (MIPS_MATH_LOOPUNROLL)

  /* Loop unrolling: Compute 4 outputs at a time */
  blkCnt = blockSize >> 2U;

  while (blkCnt > 0U)
  {
    /* C = |A| */

    /* Calculate absolute of input (if -1 then saturated to 0x7fffffff) and store result in destination buffer. */
    in = *pSrc++;

    *pDst++ = (in > 0) ? in : ((in == INT32_MIN) ? INT32_MAX : -in);
    
    in = *pSrc++;

    *pDst++ = (in > 0) ? in : ((in == INT32_MIN) ? INT32_MAX : -in);

    in = *pSrc++;

    *pDst++ = (in > 0) ? in : ((in == INT32_MIN) ? INT32_MAX : -in);

    in = *pSrc++;

    *pDst++ = (in > 0) ? in : ((in == INT32_MIN) ? INT32_MAX : -in);

    /* Decrement loop counter */
    blkCnt--;
  }

  /* Loop unrolling: Compute remaining outputs */
  blkCnt = blockSize % 0x4U;

#else

  /* Initialize blkCnt with number of samples */
  blkCnt = blockSize;

#endif /* #if defined (MIPS_MATH_LOOPUNROLL) */

  while (blkCnt > 0U)
  {
    /* C = |A| */

    /* Calculate absolute of input (if -1 then saturated to 0x7fffffff) and store result in destination buffer. */
    in = *pSrc++;

    *pDst++ = (in > 0) ? in : ((in == INT32_MIN) ? INT32_MAX : -in);

    /* Decrement loop counter */
    blkCnt--;
  }

}
#endif /* #if defined (MIPS_MATH_DSP) */
/**
  @} end of BasicAbs group
 */
