/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_abs_q15.c
 * Description:  Q15 vector absolute value
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
  @brief         Q15 vector absolute value.
  @param[in]     pSrc       points to the input vector
  @param[out]    pDst       points to the output vector
  @param[in]     blockSize  number of samples in each vector
  @return        none

  @par           Scaling and Overflow Behavior
                   The function uses saturating arithmetic.
                   The Q15 value -1 (0x8000) will be saturated to the maximum allowable positive value 0x7FFF.
 */

#if defined(MIPS_MATH_DSP)

void mips_abs_q15(
    const q15 * pSrc,
    q15 * pDst,
    uint32_t blockSize)
{
    uint32_t  blkCnt;           /* loop counters */
    v2q15 vecSrc;

    /* Compute 2 outputs at a time */
    blkCnt = blockSize >> 1;
    while (blkCnt > 0U)
    {
        /*
         * C = |A|
         * Calculate absolute and then store the results in the destination buffer.
         */
        vecSrc = mips_dsp_load_v2q15(pSrc);
        mips_dsp_store_v2q15 (pDst, _mips_absq_s_ph(vecSrc));
        /*
         * Decrement the blockSize loop counter
         */
        blkCnt--;
        /*
         * advance vector source and destination pointers
         */
        pSrc += 2;
        pDst += 2;
    }
    /*
     * tail
     */
    blkCnt = blockSize & 1;
    while (blkCnt > 0U)
    {
        q15 in;                                        /* Temporary input variable */

        in = *pSrc++;

        *pDst++ = (in > 0) ? in : ((in == (q15) 0x8000) ? 0x7fff : -in);

        blkCnt--;
    }
}

#else
void mips_abs_q15(
  const q15 * pSrc,
        q15 * pDst,
        uint32_t blockSize)
{
        uint32_t blkCnt;                               /* Loop counter */
        q15 in;                                        /* Temporary input variable */

#if defined (MIPS_MATH_LOOPUNROLL)

  /* Loop unrolling: Compute 4 outputs at a time */
  blkCnt = blockSize >> 2U;

  while (blkCnt > 0U)
  {
    /* C = |A| */

    /* Calculate absolute of input (if -1 then saturated to 0x7fff) and store result in destination buffer. */
    in = *pSrc++;

    *pDst++ = (in > 0) ? in : ((in == (q15) 0x8000) ? 0x7fff : -in);

    in = *pSrc++;

    *pDst++ = (in > 0) ? in : ((in == (q15) 0x8000) ? 0x7fff : -in);

    in = *pSrc++;

    *pDst++ = (in > 0) ? in : ((in == (q15) 0x8000) ? 0x7fff : -in);

    in = *pSrc++;

    *pDst++ = (in > 0) ? in : ((in == (q15) 0x8000) ? 0x7fff : -in);

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

    /* Calculate absolute of input (if -1 then saturated to 0x7fff) and store result in destination buffer. */
    in = *pSrc++;

    *pDst++ = (in > 0) ? in : ((in == (q15) 0x8000) ? 0x7fff : -in);

    /* Decrement loop counter */
    blkCnt--;
  }

}
#endif /* defined(MIPS_MATH_DSP) */

/**
  @} end of BasicAbs group
 */
