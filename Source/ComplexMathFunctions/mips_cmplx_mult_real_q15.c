/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_cmplx_mult_real_q15.c
 * Description:  Q15 complex by real multiplication
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
  @addtogroup CmplxByRealMult
  @{
 */

/**
  @brief         Q15 complex-by-real multiplication.
  @param[in]     pSrcCmplx   points to complex input vector
  @param[in]     pSrcReal    points to real input vector
  @param[out]    pCmplxDst   points to complex output vector
  @param[in]     numSamples  number of samples in each vector
  @return        none

  @par           Scaling and Overflow Behavior
                   The function uses saturating arithmetic.
                   Results outside of the allowable Q15 range [0x8000 0x7FFF] are saturated.
 */

void mips_cmplx_mult_real_q15(
  const q15 * pSrcCmplx,
  const q15 * pSrcReal,
        q15 * pCmplxDst,
        uint32_t numSamples)
{
        uint32_t blkCnt;                               /* Loop counter */
#if defined(MIPS_MATH_DSP)
		v2q15 in1, in2;								   /* Temporary variable */
#else
        q15 in;                                        /* Temporary variable */
#endif /* #if defined(MIPS_MATH_DSP) */

#if defined (MIPS_MATH_LOOPUNROLL)


  /* Loop unrolling: Compute 4 outputs at a time */
  blkCnt = numSamples >> 2U;

  while (blkCnt > 0U)
  {
    /* C[2 * i    ] = A[2 * i    ] * B[i]. */
    /* C[2 * i + 1] = A[2 * i + 1] * B[i]. */

#if defined (MIPS_MATH_DSP)
	in1 = mips_dsp_set_v2q15(*pSrcReal, *pSrcReal);
	*pSrcReal++;
	in2 = mips_dsp_load_v2q15(pSrcCmplx);
	pSrcCmplx += 2;
	mips_dsp_store_v2q15(pCmplxDst, _mips_mulq_s_ph(in1, in2));
	pCmplxDst += 2;

	in1 = mips_dsp_set_v2q15(*pSrcReal, *pSrcReal);
	*pSrcReal++;
	in2 = mips_dsp_load_v2q15(pSrcCmplx);
	pSrcCmplx += 2;
	mips_dsp_store_v2q15(pCmplxDst, _mips_mulq_s_ph(in1, in2));
	pCmplxDst += 2;

	in1 = mips_dsp_set_v2q15(*pSrcReal, *pSrcReal);
	*pSrcReal++;
	in2 = mips_dsp_load_v2q15(pSrcCmplx);
	pSrcCmplx += 2;
	mips_dsp_store_v2q15(pCmplxDst, _mips_mulq_s_ph(in1, in2));
	pCmplxDst += 2;

	in1 = mips_dsp_set_v2q15(*pSrcReal, *pSrcReal);
	*pSrcReal++;
	in2 = mips_dsp_load_v2q15(pSrcCmplx);
	pSrcCmplx += 2;
	mips_dsp_store_v2q15(pCmplxDst, _mips_mulq_s_ph(in1, in2));
	pCmplxDst += 2;
#else
    in = *pSrcReal++;
    *pCmplxDst++ = (q15) __SSAT((((q31) *pSrcCmplx++ * in) >> 15), 16);
    *pCmplxDst++ = (q15) __SSAT((((q31) *pSrcCmplx++ * in) >> 15), 16);

    in = *pSrcReal++;
    *pCmplxDst++ = (q15) __SSAT((((q31) *pSrcCmplx++ * in) >> 15), 16);
    *pCmplxDst++ = (q15) __SSAT((((q31) *pSrcCmplx++ * in) >> 15), 16);

    in = *pSrcReal++;
    *pCmplxDst++ = (q15) __SSAT((((q31) *pSrcCmplx++ * in) >> 15), 16);
    *pCmplxDst++ = (q15) __SSAT((((q31) *pSrcCmplx++ * in) >> 15), 16);

    in = *pSrcReal++;
    *pCmplxDst++ = (q15) __SSAT((((q31) *pSrcCmplx++ * in) >> 15), 16);
    *pCmplxDst++ = (q15) __SSAT((((q31) *pSrcCmplx++ * in) >> 15), 16);
#endif /* #if defined(MIPS_MATH_DSP) */

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
    /* C[2 * i    ] = A[2 * i    ] * B[i]. */
    /* C[2 * i + 1] = A[2 * i + 1] * B[i]. */

#if defined(MIPS_MATH_DSP)

	in1 = mips_dsp_set_v2q15(*pSrcReal, *pSrcReal);
	pSrcReal++;
	in2 = mips_dsp_load_v2q15(pSrcCmplx);
	pSrcCmplx += 2;
	mips_dsp_store_v2q15(pCmplxDst, _mips_mulq_s_ph(in1, in2));
	pCmplxDst += 2;

#else
    in = *pSrcReal++;
    /* store the result in the destination buffer. */
    *pCmplxDst++ = (q15) __SSAT((((q31) *pSrcCmplx++ * in) >> 15), 16);
    *pCmplxDst++ = (q15) __SSAT((((q31) *pSrcCmplx++ * in) >> 15), 16);

#endif /* #if defined(MIPS_MATH_DSP) */
    /* Decrement loop counter */
    blkCnt--;
  }

}

/**
  @} end of CmplxByRealMult group
 */
