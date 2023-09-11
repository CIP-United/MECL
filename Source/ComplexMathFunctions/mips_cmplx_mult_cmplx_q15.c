/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_cmplx_mult_cmplx_q15.c
 * Description:  Q15 complex-by-complex multiplication
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
  @addtogroup CmplxByCmplxMult
  @{
 */

/**
  @brief         Q15 complex-by-complex multiplication.
  @param[in]     pSrcA       points to first input vector
  @param[in]     pSrcB       points to second input vector
  @param[out]    pDst        points to output vector
  @param[in]     numSamples  number of samples in each vector
  @return        none

  @par           Scaling and Overflow Behavior
                   The function implements 1.15 by 1.15 multiplications and finally output is converted into 3.13 format.
 */

void mips_cmplx_mult_cmplx_q15(
  const q15 * pSrcA,
  const q15 * pSrcB,
        q15 * pDst,
        uint32_t numSamples)
{
        uint32_t blkCnt;                               /* Loop counter */
#if defined (MIPS_MATH_DSP)
        v2q15 a, b, c;                                 /* Temporary variables */
        v2q15 vecTmpA, vecTmpB;                        /* Temporary variables */
#else
        q15 a, b, c, d;                                /* Temporary variables */
#endif

#if defined (MIPS_MATH_LOOPUNROLL)

  /* Loop unrolling: Compute 4 outputs at a time */
  blkCnt = numSamples >> 2U;

  while (blkCnt > 0U)
  {
    /* C[2 * i    ] = A[2 * i] * B[2 * i    ] - A[2 * i + 1] * B[2 * i + 1]. */
    /* C[2 * i + 1] = A[2 * i] * B[2 * i + 1] + A[2 * i + 1] * B[2 * i    ]. */
#if defined (MIPS_MATH_DSP)
	a = mips_dsp_load_v2q15(pSrcA);
	b = mips_dsp_load_v2q15(pSrcB);
	c = mips_dsp_set_v2q15(*(pSrcA+1), *pSrcA);
	vecTmpA = _mips_mulq_s_ph(a, b);
	vecTmpB = _mips_mulq_s_ph(b, c);
	vecTmpA = _mips_shra_ph(vecTmpA, 2);
	vecTmpB = _mips_shra_ph(vecTmpB, 2);
	*pDst++ = (q15) (mips_dsp_nth_q15_v2q15(vecTmpA, 0) - mips_dsp_nth_q15_v2q15(vecTmpA, 1));
	*pDst++ = (q15) (mips_dsp_nth_q15_v2q15(vecTmpB, 1) + mips_dsp_nth_q15_v2q15(vecTmpB, 0));
	pSrcA += 2;
	pSrcB += 2;

	a = mips_dsp_load_v2q15(pSrcA);
	b = mips_dsp_load_v2q15(pSrcB);
	c = mips_dsp_set_v2q15(*(pSrcA+1), *pSrcA);
	vecTmpA = _mips_mulq_s_ph(a, b);
	vecTmpB = _mips_mulq_s_ph(b, c);
	vecTmpA = _mips_shra_ph(vecTmpA, 2);
	vecTmpB = _mips_shra_ph(vecTmpB, 2);
	*pDst++ = (q15) (mips_dsp_nth_q15_v2q15(vecTmpA, 0) - mips_dsp_nth_q15_v2q15(vecTmpA, 1));
	*pDst++ = (q15) (mips_dsp_nth_q15_v2q15(vecTmpB, 1) + mips_dsp_nth_q15_v2q15(vecTmpB, 0));
	pSrcA += 2;
	pSrcB += 2;

	a = mips_dsp_load_v2q15(pSrcA);
	b = mips_dsp_load_v2q15(pSrcB);
	c = mips_dsp_set_v2q15(*(pSrcA+1), *pSrcA);
	vecTmpA = _mips_mulq_s_ph(a, b);
	vecTmpB = _mips_mulq_s_ph(b, c);
	vecTmpA = _mips_shra_ph(vecTmpA, 2);
	vecTmpB = _mips_shra_ph(vecTmpB, 2);
	*pDst++ = (q15) (mips_dsp_nth_q15_v2q15(vecTmpA, 0) - mips_dsp_nth_q15_v2q15(vecTmpA, 1));
	*pDst++ = (q15) (mips_dsp_nth_q15_v2q15(vecTmpB, 1) + mips_dsp_nth_q15_v2q15(vecTmpB, 0));
	pSrcA += 2;
	pSrcB += 2;

	a = mips_dsp_load_v2q15(pSrcA);
	b = mips_dsp_load_v2q15(pSrcB);
	c = mips_dsp_set_v2q15(*(pSrcA+1), *pSrcA);
	vecTmpA = _mips_mulq_s_ph(a, b);
	vecTmpB = _mips_mulq_s_ph(b, c);
	vecTmpA = _mips_shra_ph(vecTmpA, 2);
	vecTmpB = _mips_shra_ph(vecTmpB, 2);
	*pDst++ = (q15) (mips_dsp_nth_q15_v2q15(vecTmpA, 0) - mips_dsp_nth_q15_v2q15(vecTmpA, 1));
	*pDst++ = (q15) (mips_dsp_nth_q15_v2q15(vecTmpB, 1) + mips_dsp_nth_q15_v2q15(vecTmpB, 0));
	pSrcA += 2;
	pSrcB += 2;

#else

    a = *pSrcA++;
    b = *pSrcA++;
    c = *pSrcB++;
    d = *pSrcB++;
    /* store result in 3.13 format in destination buffer. */
    *pDst++ = (q15) ( (((q31) a * c) >> 17) - (((q31) b * d) >> 17) );
    *pDst++ = (q15) ( (((q31) a * d) >> 17) + (((q31) b * c) >> 17) );

    a = *pSrcA++;
    b = *pSrcA++;
    c = *pSrcB++;
    d = *pSrcB++;
    *pDst++ = (q15) ( (((q31) a * c) >> 17) - (((q31) b * d) >> 17) );
    *pDst++ = (q15) ( (((q31) a * d) >> 17) + (((q31) b * c) >> 17) );

    a = *pSrcA++;
    b = *pSrcA++;
    c = *pSrcB++;
    d = *pSrcB++;
    *pDst++ = (q15) ( (((q31) a * c) >> 17) - (((q31) b * d) >> 17) );
    *pDst++ = (q15) ( (((q31) a * d) >> 17) + (((q31) b * c) >> 17) );

    a = *pSrcA++;
    b = *pSrcA++;
    c = *pSrcB++;
    d = *pSrcB++;
    *pDst++ = (q15) ( (((q31) a * c) >> 17) - (((q31) b * d) >> 17) );
    *pDst++ = (q15) ( (((q31) a * d) >> 17) + (((q31) b * c) >> 17) );
#endif /* #if defined (MIPS_MATH_DSP) */

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
    /* C[2 * i    ] = A[2 * i] * B[2 * i    ] - A[2 * i + 1] * B[2 * i + 1]. */
    /* C[2 * i + 1] = A[2 * i] * B[2 * i + 1] + A[2 * i + 1] * B[2 * i    ]. */

#if defined (MIPS_MATH_DSP)
	a = mips_dsp_load_v2q15(pSrcA);
	b = mips_dsp_load_v2q15(pSrcB);
	c = mips_dsp_set_v2q15(*(pSrcA+1), *pSrcA);

	vecTmpA = _mips_mulq_s_ph(a, b);
	vecTmpB = _mips_mulq_s_ph(b, c);
	vecTmpA = _mips_shra_ph(vecTmpA, 2);
	vecTmpB = _mips_shra_ph(vecTmpB, 2);

	*pDst++ = (q15) (mips_dsp_nth_q15_v2q15(vecTmpA, 0) - mips_dsp_nth_q15_v2q15(vecTmpA, 1));
	*pDst++ = (q15) (mips_dsp_nth_q15_v2q15(vecTmpB, 1) + mips_dsp_nth_q15_v2q15(vecTmpB, 0));

	pSrcA += 2;
	pSrcB += 2;

#else
    a = *pSrcA++;
    b = *pSrcA++;
    c = *pSrcB++;
    d = *pSrcB++;

    /* store result in 3.13 format in destination buffer. */
    *pDst++ = (q15) ( (((q31) a * c) >> 17) - (((q31) b * d) >> 17) );
    *pDst++ = (q15) ( (((q31) a * d) >> 17) + (((q31) b * c) >> 17) );

#endif /* #if defined (MIPS_MATH_DSP) */

    /* Decrement loop counter */
    blkCnt--;
  }

}

/**
  @} end of CmplxByCmplxMult group
 */
