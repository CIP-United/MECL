/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_q31_to_q7.c
 * Description:  Converts the elements of the Q31 vector to Q7 vector
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
  @brief         Converts the elements of the Q31 vector to Q7 vector.
  @param[in]     pSrc       points to the Q31 input vector
  @param[out]    pDst       points to the Q7 output vector
  @param[in]     blockSize  number of samples in each vector
  @return        none

  @par           Details
                   The equation used for the conversion process is:
  <pre>
      pDst[n] = (q7) pSrc[n] >> 24;   0 <= n < blockSize.
  </pre>
 */
#if defined(MIPS_MATH_DSP)
void mips_q31_to_q7(
  const q31 * pSrc,
        q7 * pDst,
        uint32_t blockSize)
{
    uint32_t  blkCnt;           /* loop counters */
    v2q15 evVec, oddVec;
    v4q7  vecDst;
    q31 const *pSrcVec;

    pSrcVec = (q31 const *) pSrc;
    blkCnt = blockSize >> 2;
    while (blkCnt > 0U)
    {  
        /* C = (q7) A >> 24 */
        /* convert from q31 to q7 and then store the results in the destination buffer */
        /*
         * narrow and pack evens
         */
        evVec = _mips_precrq_ph_w(*(pSrcVec+1),*pSrcVec);
        pSrcVec += 2;
        oddVec = _mips_precrq_ph_w(*(pSrcVec+1),*pSrcVec);
        pSrcVec += 2;
        vecDst = _mips_precrq_qb_ph(oddVec,evVec);
        mips_dsp_store_v4q7(pDst,vecDst);
        
        pDst += 4;
        /*
         * Decrement the blockSize loop counter
         */
        blkCnt--;
    }
    /*
     * tail
     */
    blkCnt = blockSize & 0x3;
    while (blkCnt > 0U)
    {
      /* C = (q7) (A >> 24) */
  
      /* Convert from q31 to q7 and store result in destination buffer */
      *pDst++ = (q7) (*pSrcVec++ >> 24);
  
      /* Decrement loop counter */
      blkCnt--;
    }
}
#else
void mips_q31_to_q7(
  const q31 * pSrc,
        q7 * pDst,
        uint32_t blockSize)
{
        uint32_t blkCnt;                               /* Loop counter */
  const q31 *pIn = pSrc;                             /* Source pointer */

#if defined (MIPS_MATH_LOOPUNROLL)

  q7 out1, out2, out3, out4;

  /* Loop unrolling: Compute 4 outputs at a time */
  blkCnt = blockSize >> 2U;

  while (blkCnt > 0U)
  {
    /* C = (q7) (A >> 24) */

    /* Convert from q31 to q7 and store result in destination buffer */

    out1 = (q7) (*pIn++ >> 24);
    out2 = (q7) (*pIn++ >> 24);
    out3 = (q7) (*pIn++ >> 24);
    out4 = (q7) (*pIn++ >> 24);
    write_q7x4_ia (&pDst, __PACKq7(out1, out2, out3, out4));

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
    /* C = (q7) (A >> 24) */

    /* Convert from q31 to q7 and store result in destination buffer */
    *pDst++ = (q7) (*pIn++ >> 24);

    /* Decrement loop counter */
    blkCnt--;
  }

}
#endif /* defined(MIPS_MATH_DSP) */

/**
  @} end of q31_to_x group
 */
