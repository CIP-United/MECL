/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_cmplx_conj_q15.c
 * Description:  Q15 complex conjugate
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

#include "dsp/complex_math_functions.h"

/**
  @ingroup groupCmplxMath
 */

/**
  @addtogroup cmplx_conj
  @{
 */

/**
  @brief         Q15 complex conjugate.
  @param[in]     pSrc        points to the input vector
  @param[out]    pDst        points to the output vector
  @param[in]     numSamples  number of samples in each vector
  @return        none

  @par           Scaling and Overflow Behavior
                   The function uses saturating arithmetic.
                   The Q15 value -1 (0x8000) is saturated to the maximum allowable positive value 0x7FFF.
 */


#if defined(MIPS_MATH_DSP)
void mips_cmplx_conj_q15(
  const q15 * pSrc,
        q15 * pDst,
        uint32_t numSamples)
{
    uint32_t blockSize = numSamples * CMPLX_DIM;   /* loop counters */
    uint32_t blkCnt;
    q31 in1; 

    v2q15 vecSrc;
    v2q15 zero;

    zero = _mips_repl_ph(0);

	/* Compute 2 real samples at a time */
    blkCnt = blockSize >> 2U;
    while (blkCnt > 0U)
    {
        vecSrc = mips_dsp_set_v2q15(*(pSrc + 1), *(pSrc + 3));
        vecSrc = _mips_subq_s_ph(zero, vecSrc);
		*pDst = *pSrc;
		*(pDst+1) = mips_dsp_nth_q15_v2q15(vecSrc, 0);
		*(pDst+2) = *(pSrc + 2);
		*(pDst+3) = mips_dsp_nth_q15_v2q15(vecSrc, 1);
        /*
         * Decrement the blkCnt loop counter
         * Advance vector source and destination pointers
         */
        pSrc += 4;
        pDst += 4;
        blkCnt --;
    }

     /* Tail */
    blkCnt = (blockSize & 0x3) >> 1;

    while (blkCnt > 0U)
    {
      /* C[0] + jC[1] = A[0]+ j(-1)A[1] */
  
      /* Calculate Complex Conjugate and store result in destination buffer. */
      *pDst++ =  *pSrc++;
      in1 = *pSrc++;
      *pDst++ = __SSAT(-in1, 16);
  
      /* Decrement loop counter */
      blkCnt--;
    }
}
#else
void mips_cmplx_conj_q15(
  const q15 * pSrc,
        q15 * pDst,
        uint32_t numSamples)
{
        uint32_t blkCnt;                               /* Loop counter */
        q31 in1;                                       /* Temporary input variable */

#if defined (MIPS_MATH_LOOPUNROLL)

  /* Loop unrolling: Compute 4 outputs at a time */
  blkCnt = numSamples >> 2U;

  while (blkCnt > 0U)
  {
    /* C[0] + jC[1] = A[0]+ j(-1)A[1] */

    /* Calculate Complex Conjugate and store result in destination buffer. */

    *pDst++ =  *pSrc++;
    in1 = *pSrc++;
    *pDst++ = (in1 == (q15) 0x8000) ? (q15) 0x7fff : -in1;

    *pDst++ =  *pSrc++;
    in1 = *pSrc++;
    *pDst++ = (in1 == (q15) 0x8000) ? (q15) 0x7fff : -in1;

    *pDst++ =  *pSrc++;
    in1 = *pSrc++;
    *pDst++ = (in1 == (q15) 0x8000) ? (q15) 0x7fff : -in1;

    *pDst++ =  *pSrc++;
    in1 = *pSrc++;
    *pDst++ = (in1 == (q15) 0x8000) ? (q15) 0x7fff : -in1;

    /* Decrement loop counter */
    blkCnt--;
  }

  /* Loop unrolling: Compute remaining outputs */
  blkCnt = numSamples % 0x4U;

#else

  /* Initialize blkCnt with number of samples */
  blkCnt = numSamples;

#endif /* #if defined (MIPS_MATH_LOOPUNROLL) */

  while (blkCnt > 0U)
  {
    /* C[0] + jC[1] = A[0]+ j(-1)A[1] */

    /* Calculate Complex Conjugate and store result in destination buffer. */
    *pDst++ =  *pSrc++;
    in1 = *pSrc++;

    *pDst++ = (in1 == (q15) 0x8000) ? (q15) 0x7fff : -in1;

    /* Decrement loop counter */
    blkCnt--;
  }

}
#endif /* defined(MIPS_MATH_DSP) */

/**
  @} end of cmplx_conj group
 */
