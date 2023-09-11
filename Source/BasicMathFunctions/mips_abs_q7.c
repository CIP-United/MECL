/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_abs_q7.c
 * Description:  Q7 vector absolute value
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
  @brief         Q7 vector absolute value.
  @param[in]     pSrc       points to the input vector
  @param[out]    pDst       points to the output vector
  @param[in]     blockSize  number of samples in each vector
  @return        none

  @par           Conditions for optimum performance
                   Input and output buffers should be aligned by 32-bit
  @par           Scaling and Overflow Behavior
                   The function uses saturating arithmetic.
                   The Q7 value -1 (0x80) will be saturated to the maximum allowable positive value 0x7F.
 */

#if defined(MIPS_MATH_DSP)

void mips_abs_q7(
    const q7 * pSrc,
    q7 * pDst,
    uint32_t blockSize)
{
    uint32_t  blkCnt;           /* loop counters */
    v4q7 vecSrc;

    /* Compute 4 outputs at a time */
    blkCnt = blockSize >> 2;
    while (blkCnt > 0U)
    {
        /*
         * C = |A|
         * Calculate absolute and then store the results in the destination buffer.
         */
        vecSrc = mips_dsp_load_v4q7(pSrc);
        mips_dsp_store_v4q7 (pDst, _mips_absq_s_qb(vecSrc));
        /*
         * Decrement the blockSize loop counter
         */
        blkCnt--;
        /*
         * advance vector source and destination pointers
         */
        pSrc += 4;
        pDst += 4;
    }
    /*
     * tail
     */
    blkCnt = blockSize & 0x3;

    while (blkCnt > 0U)
    {
        q7 in;                                       /* Temporary input variable */

        in = *pSrc++;

        *pDst++ = (in > 0) ? in : ((in == (q7) 0x80) ? (q7) 0x7f : -in);

        blkCnt--;
    }
}

#else
void mips_abs_q7(
  const q7 * pSrc,
        q7 * pDst,
        uint32_t blockSize)
{
        uint32_t blkCnt;                               /* Loop counter */
        q7 in;                                         /* Temporary input variable */

#if defined (MIPS_MATH_LOOPUNROLL)

  /* Loop unrolling: Compute 4 outputs at a time */
  blkCnt = blockSize >> 2U;

  while (blkCnt > 0U)
  {
    /* C = |A| */

    /* Calculate absolute of input (if -1 then saturated to 0x7f) and store result in destination buffer. */
    in = *pSrc++;

    *pDst++ = (in > 0) ? in : ((in == (q7) 0x80) ? (q7) 0x7f : -in);

    in = *pSrc++;

    *pDst++ = (in > 0) ? in : ((in == (q7) 0x80) ? (q7) 0x7f : -in);

    in = *pSrc++;

    *pDst++ = (in > 0) ? in : ((in == (q7) 0x80) ? (q7) 0x7f : -in);

    in = *pSrc++;

    *pDst++ = (in > 0) ? in : ((in == (q7) 0x80) ? (q7) 0x7f : -in);

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

    /* Calculate absolute of input (if -1 then saturated to 0x7f) and store result in destination buffer. */
    in = *pSrc++;

    *pDst++ = (in > 0) ? in : ((in == (q7) 0x80) ? (q7) 0x7f : -in);

    /* Decrement loop counter */
    blkCnt--;
  }

}
#endif /* defined(MIPS_MATH_DSP) */

/**
  @} end of BasicAbs group
 */
