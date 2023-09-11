/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_cmplx_mag_q15.c
 * Description:  Q15 complex magnitude
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
  @addtogroup cmplx_mag
  @{
 */

/**
  @brief         Q15 complex magnitude.
  @param[in]     pSrc        points to input vector
  @param[out]    pDst        points to output vector
  @param[in]     numSamples  number of samples in each vector
  @return        none

  @par           Scaling and Overflow Behavior
                   The function implements 1.15 by 1.15 multiplications and finally output is converted into 2.14 format.
 */

/* Sqrt q31 is used otherwise accuracy is not good enough
           for small values and for some applications it is
           an issue.
        */

void mips_cmplx_mag_q15(
  const q15 * pSrc,
        q15 * pDst,
        uint32_t numSamples)
{
        q31 res; /* temporary result */
        uint32_t blkCnt;                               /* Loop counter */

#if defined (MIPS_MATH_DSP)
      	v2q15 real, imag;                           /* Temporary input variables */
#else
       q15 real, imag;                              /* Temporary input variables */
#endif
       q31 acc0, acc1;                              /* Accumulators */

#if defined (MIPS_MATH_LOOPUNROLL)

  /* Loop unrolling: Compute 4 outputs at a time */
  blkCnt = numSamples >> 2U;

  while (blkCnt > 0U)
  {
    /* C[0] = sqrt(A[0] * A[0] + A[1] * A[1]) */

#if defined (MIPS_MATH_DSP)

	real = mips_dsp_load_v2q15(pSrc);
	acc0 = _mips_dpa_w_ph(0, real, real);
	mips_sqrt_q31(acc0 >> 1 , &res);
	pSrc+=2;

    *pDst++ = res >> 16;

	real = mips_dsp_load_v2q15(pSrc);
	acc0 = _mips_dpa_w_ph(0, real, real);
	mips_sqrt_q31(acc0 >> 1 , &res);
	pSrc+=2;
    *pDst++ = res >> 16;

	real = mips_dsp_load_v2q15(pSrc);
	acc0 = _mips_dpa_w_ph(0, real, real);
	mips_sqrt_q31(acc0 >> 1 , &res);
	pSrc+=2;
    *pDst++ = res >> 16;

	real = mips_dsp_load_v2q15(pSrc);
	acc0 = _mips_dpa_w_ph(0, real, real);
	mips_sqrt_q31(acc0 >> 1 , &res);
	pSrc+=2;
    *pDst++ = res >> 16;
#else
    real = *pSrc++;
    imag = *pSrc++;
    acc0 = ((q31) real * real);
    acc1 = ((q31) imag * imag);

    /* store result in 2.14 format in destination buffer. */
    mips_sqrt_q31((acc0 + acc1) >> 1 , &res);
    *pDst++ = res >> 16;

    real = *pSrc++;
    imag = *pSrc++;
    acc0 = ((q31) real * real);
    acc1 = ((q31) imag * imag);
    mips_sqrt_q31((acc0 + acc1) >> 1 , &res);
    *pDst++ = res >> 16;

    real = *pSrc++;
    imag = *pSrc++;
    acc0 = ((q31) real * real);
    acc1 = ((q31) imag * imag);
    mips_sqrt_q31((acc0 + acc1) >> 1 , &res);
    *pDst++ = res >> 16;

    real = *pSrc++;
    imag = *pSrc++;
    acc0 = ((q31) real * real);
    acc1 = ((q31) imag * imag);
    mips_sqrt_q31((acc0 + acc1) >> 1 , &res);
    *pDst++ = res >> 16;
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
    /* C[0] = sqrt(A[0] * A[0] + A[1] * A[1]) */

#if defined (MIPS_MATH_DSP)

	real = mips_dsp_load_v2q15(pSrc);
	acc0 = _mips_dpa_w_ph(0, real, real);
	mips_sqrt_q31(acc0 >> 1 , &res);

	pSrc+=2;

#else
    real = *pSrc++;
    imag = *pSrc++;
    acc0 = ((q31) real * real);
    acc1 = ((q31) imag * imag);

    /* store result in 2.14 format in destination buffer. */
    mips_sqrt_q31((acc0 + acc1) >> 1 , &res);

#endif /* #if defined (MIPS_MATH_DSP) */

    *pDst++ = res >> 16;

    /* Decrement loop counter */
    blkCnt--;
  }

}

/**
  @} end of cmplx_mag group
 */
