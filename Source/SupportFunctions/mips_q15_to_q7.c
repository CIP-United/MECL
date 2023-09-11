/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_q15_to_q7.c
 * Description:  Converts the elements of the Q15 vector to Q7 vector
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
  @addtogroup q15_to_x
  @{
 */

/**
  @brief         Converts the elements of the Q15 vector to Q7 vector.
  @param[in]     pSrc       points to the Q15 input vector
  @param[out]    pDst       points to the Q7 output vector
  @param[in]     blockSize  number of samples in each vector
  @return        none

  @par           Details
                   The equation used for the conversion process is:
  <pre>
      pDst[n] = (q7) pSrc[n] >> 8;   0 <= n < blockSize.
  </pre>
 */
#if defined(MIPS_MATH_DSP)
void mips_q15_to_q7(
  const q15 * pSrc,
        q7 * pDst,
        uint32_t blockSize)
{

    uint32_t  blkCnt;           /* loop counters */
    v2q15 tmp1,tmp2;
    q15 const *pSrcVec;
    v4i8 vecDsti = { 0 };
    v4q7 vecDst;


    pSrcVec = (q15 const *) pSrc;
    blkCnt = blockSize >> 2;
    while (blkCnt > 0U)
    {
        /* C = (q7) A >> 8 */
        /* convert from q15 to q7 and then store the results in the destination buffer */
        tmp1 = mips_dsp_load_v2q15(pSrcVec);   
        pSrcVec += 2;
        tmp2 = mips_dsp_load_v2q15(pSrcVec);
        pSrcVec += 2;
        vecDsti = _mips_precrq_qb_ph(tmp2, tmp1);
        vecDst = mips_dsp_vreinterpret_v4q7(vecDsti);
        mips_dsp_store_v4q7(pDst, vecDst);

        pDst += 4;
        /*
         * Decrement the blockSize loop counter
         */
        blkCnt--;
    }

  blkCnt = blockSize & 0x3;
  while (blkCnt > 0U)
  {
    /* C = (q7) A >> 8 */

    /* Convert from q15 to q7 and store result in destination buffer */
    *pDst++ = (q7) (*pSrcVec++ >> 8);

    /* Decrement loop counter */
    blkCnt--;
  }
}
#else
void mips_q15_to_q7(
  const q15 * pSrc,
        q7 * pDst,
        uint32_t blockSize)
{
        uint32_t blkCnt;                               /* Loop counter */
  const q15 *pIn = pSrc;                             /* Source pointer */

#if defined (MIPS_MATH_LOOPUNROLL)

  /* Loop unrolling: Compute 4 outputs at a time */
  blkCnt = blockSize >> 2U;

  while (blkCnt > 0U)
  {
    /* C = (q7) A >> 8 */

    /* Convert from q15 to q7 and store result in destination buffer */


    *pDst++ = (q7) (*pIn++ >> 8);
    *pDst++ = (q7) (*pIn++ >> 8);
    *pDst++ = (q7) (*pIn++ >> 8);
    *pDst++ = (q7) (*pIn++ >> 8);


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
    /* C = (q7) A >> 8 */

    /* Convert from q15 to q7 and store result in destination buffer */
    *pDst++ = (q7) (*pIn++ >> 8);

    /* Decrement loop counter */
    blkCnt--;
  }

}
#endif /* defined(MIPS_MATH_DSP) */

/**
  @} end of q15_to_x group
 */
