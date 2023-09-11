/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_q31_to_q15.c
 * Description:  Converts the elements of the Q31 vector to Q15 vector
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
  @addtogroup q31_to_x
  @{
 */

/**
  @brief         Converts the elements of the Q31 vector to Q15 vector.
  @param[in]     pSrc       points to the Q31 input vector
  @param[out]    pDst       points to the Q15 output vector
  @param[in]     blockSize  number of samples in each vector
  @return        none

  @par           Details
                   The equation used for the conversion process is:
  <pre>
      pDst[n] = (q15) pSrc[n] >> 16;   0 <= n < blockSize.
  </pre>
 */
#if defined(MIPS_MATH_DSP)
void mips_q31_to_q15(
  const q31 * pSrc,
        q15 * pDst,
        uint32_t blockSize)
{
    uint32_t  blkCnt;           /* loop counters */
    v2q15 vecDst;
    q31 const *pSrcVec;


    pSrcVec = (q31 const *) pSrc;
    blkCnt = blockSize >> 1;
    while (blkCnt > 0U)
    {
        /* C = (q15) A >> 16 */
        /* convert from q31 to q15 and then store the results in the destination buffer */
           
        
        vecDst =_mips_precrq_ph_w(*(pSrcVec+1),*pSrcVec);
        pSrcVec += 2;
        mips_dsp_store_v2q15(pDst,vecDst);   
        pDst += 2;
        /*
         * Decrement the blockSize loop counter
         */
        blkCnt--;
    }

    /*
     * tail
     */
    blkCnt = blockSize & 1;
    while (blkCnt > 0U)
    {
      /* C = (q15) (A >> 16) */
  
      /* Convert from q31 to q15 and store result in destination buffer */
      *pDst++ = (q15) (*pSrcVec++ >> 16);
  
      /* Decrement loop counter */
      blkCnt--;
    }
}

#else
void mips_q31_to_q15(
  const q31 * pSrc,
        q15 * pDst,
        uint32_t blockSize)
{
        uint32_t blkCnt;                               /* Loop counter */
  const q31 *pIn = pSrc;                             /* Source pointer */

#if defined (MIPS_MATH_LOOPUNROLL)

  /* Loop unrolling: Compute 4 outputs at a time */
  blkCnt = blockSize >> 2U;

  while (blkCnt > 0U)
  {
    /* C = (q15) (A >> 16) */

    /* Convert from q31 to q15 and store result in destination buffer */


    *pDst++ = (q15) (*pIn++ >> 16);
    *pDst++ = (q15) (*pIn++ >> 16);
    *pDst++ = (q15) (*pIn++ >> 16);
    *pDst++ = (q15) (*pIn++ >> 16);



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
    /* C = (q15) (A >> 16) */

    /* Convert from q31 to q15 and store result in destination buffer */
    *pDst++ = (q15) (*pIn++ >> 16);

    /* Decrement loop counter */
    blkCnt--;
  }

}
#endif /* defined(MIPS_MATH_DSP) */

/**
  @} end of q31_to_x group
 */
