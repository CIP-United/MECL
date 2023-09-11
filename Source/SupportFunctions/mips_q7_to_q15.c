/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_q7_to_q15.c
 * Description:  Converts the elements of the Q7 vector to Q15 vector
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

#include "dsp/support_functions.h"

/**
  @ingroup groupSupport
 */

/**
  @addtogroup q7_to_x
  @{
 */

/**
  @brief         Converts the elements of the Q7 vector to Q15 vector.
  @param[in]     pSrc       points to the Q7 input vector
  @param[out]    pDst       points to the Q15 output vector
  @param[in]     blockSize  number of samples in each vector
  @return        none

  @par           Details
                   The equation used for the conversion process is:
  <pre>
      pDst[n] = (q15) pSrc[n] << 8;   0 <= n < blockSize.
  </pre>
 */

#if defined(MIPS_MATH_DSP)
void mips_q7_to_q15(
  const q7 * pSrc,
        q15 * pDst,
        uint32_t blockSize)
{
    uint32_t  blkCnt;           /* loop counters */
    v4q7 vecPrc;
    v4i8 vecPrci;
    v2q15 vecDst;

    q7 const *pSrcVec;

    pSrcVec = (q7 const *) pSrc;
    blkCnt = blockSize >> 2;
    while (blkCnt > 0U)
    {
        /* C = (q15) A << 8 */
        /* convert from q7 to q15 and then store the results in the destination buffer */
        /* load q7 + 32-bit widening */
        vecPrc = mips_dsp_load_v4q7(pSrcVec);
        vecPrci = mips_dsp_vreinterpret_v4i8(vecPrc); 

        vecDst = _mips_preceu_ph_qbr(vecPrci);
        vecDst = _mips_shll_ph(vecDst,8);
        mips_dsp_store_v2q15(pDst, vecDst);
        pDst += 2;

        vecDst = _mips_preceu_ph_qbl(vecPrci);
        vecDst = _mips_shll_ph(vecDst,8);
        mips_dsp_store_v2q15(pDst, vecDst);
        pDst += 2;


        /* 一次计算两个
        vecDst = mips_dsp_load_v2q15((short)(*pSrcVec));
        vecDst = _mips_shll_ph(vecDst,8);
        mips_dsp_store_v2q15(pDst, vecDst);
        pDst += 2;
        pSrcVec += 2; */

        /*
         * Decrement the blockSize loop counter
         */
        pSrcVec += 4;
        blkCnt--;
    }

  blkCnt = blockSize & 3;
  while (blkCnt > 0U)
  {
    /* C = (q15) A << 8 */

    /* Convert from q7 to q15 and store result in destination buffer */
    *pDst++ = (q15) * pSrcVec++ << 8;

    /* Decrement loop counter */
    blkCnt--;
  }

}
#else
void mips_q7_to_q15(
  const q7 * pSrc,
        q15 * pDst,
        uint32_t blockSize)
{
        uint32_t blkCnt;                               /* Loop counter */
  const q7 *pIn = pSrc;                              /* Source pointer */

#if defined (MIPS_MATH_LOOPUNROLL)

  /* Loop unrolling: Compute 4 outputs at a time */
  blkCnt = blockSize >> 2U;

  while (blkCnt > 0U)
  {
    /* C = (q15) A << 8 */

    /* Convert from q7 to q15 and store result in destination buffer */


    *pDst++ = (q15) *pIn++ << 8;
    *pDst++ = (q15) *pIn++ << 8;
    *pDst++ = (q15) *pIn++ << 8;
    *pDst++ = (q15) *pIn++ << 8;

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
    /* C = (q15) A << 8 */

    /* Convert from q7 to q15 and store result in destination buffer */
    *pDst++ = (q15) * pIn++ << 8;

    /* Decrement loop counter */
    blkCnt--;
  }

}
#endif /* defined(MIPS_MATH_DSP) */

/**
  @} end of q7_to_x group
 */
