/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_offset_q15.c
 * Description:  Q15 vector offset
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
  @addtogroup BasicOffset
  @{
 */

/**
  @brief         Adds a constant offset to a Q15 vector.
  @param[in]     pSrc       points to the input vector
  @param[in]     offset     is the offset to be added
  @param[out]    pDst       points to the output vector
  @param[in]     blockSize  number of samples in each vector
  @return        none

  @par           Scaling and Overflow Behavior
                   The function uses saturating arithmetic.
                   Results outside of the allowable Q15 range [0x8000 0x7FFF] are saturated.
 */
#if defined(MIPS_MATH_DSP)

void mips_offset_q15(
    const q15 * pSrc,
    q15   offset,
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
         * C = A + offset
         * Add offset and then store the result in the destination buffer.
         */
        vecSrc =  mips_dsp_load_v2q15(pSrc);
        v2q15 vecOff = _mips_replv_ph(offset);
        mips_dsp_store_v2q15(pDst, _mips_addq_s_ph(vecSrc, vecOff));
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
    while(blkCnt > 0U)
    {
       *pDst++ = (q15) __SSAT(((q31) *pSrc++ + offset), 16);
       blkCnt--;
    }
}

#else
void mips_offset_q15(
  const q15 * pSrc,
        q15 offset,
        q15 * pDst,
        uint32_t blockSize)
{
        uint32_t blkCnt;                               /* Loop counter */

#if defined (MIPS_MATH_LOOPUNROLL)

  /* Loop unrolling: Compute 4 outputs at a time */
  blkCnt = blockSize >> 2U;

  while (blkCnt > 0U)
  {
    /* C = A + offset */

    *pDst++ = (q15) __SSAT(((q31) *pSrc++ + offset), 16);
    *pDst++ = (q15) __SSAT(((q31) *pSrc++ + offset), 16);
    *pDst++ = (q15) __SSAT(((q31) *pSrc++ + offset), 16);
    *pDst++ = (q15) __SSAT(((q31) *pSrc++ + offset), 16);


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
    /* C = A + offset */

    /* Add offset and store result in destination buffer. */
    *pDst++ = (q15) __SSAT(((q31) *pSrc++ + offset), 16);


    /* Decrement loop counter */
    blkCnt--;
  }

}
#endif /* defined(MIPS_MATH_DSP) */

/**
  @} end of BasicOffset group
 */
