/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_cmplx_mag_squared_q31.c
 * Description:  Q31 complex magnitude squared
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
  @addtogroup cmplx_mag_squared
  @{
 */

/**
  @brief         Q31 complex magnitude squared.
  @param[in]     pSrc        points to input vector
  @param[out]    pDst        points to output vector
  @param[in]     numSamples  number of samples in each vector
  @return        none

  @par           Scaling and Overflow Behavior
                   The function implements 1.31 by 1.31 multiplications and finally output is converted into 3.29 format.
                   Input down scaling is not required.
 */

void mips_cmplx_mag_squared_q31(
  const q31 * pSrc,
        q31 * pDst,
        uint32_t numSamples)
{
        uint32_t blkCnt;                               /* Loop counter */
#if !defined (MIPS_MATH_DSP)
        q31 real, imag;                              /* Temporary input variables */
#endif
        q31 acc0, acc1;                              /* Accumulators */

#if defined (MIPS_MATH_LOOPUNROLL)

  /* Loop unrolling: Compute 4 outputs at a time */
  blkCnt = numSamples >> 2U;

  while (blkCnt > 0U)
  {
    /* C[0] = (A[0] * A[0] + A[1] * A[1]) */

#if defined (MIPS_MATH_DSP)

	acc0 = _mips_mulq_s_w(*pSrc, *pSrc);
	acc0 = _mips_shra_r_w(acc0, 2);
	pSrc++;
	acc1 = _mips_mulq_s_w(*pSrc, *pSrc);
	acc1 = _mips_shra_r_w(acc1, 2);
	pSrc++;
	*pDst++ = _mips_addq_s_w(acc0, acc1);

	acc0 = _mips_mulq_s_w(*pSrc, *pSrc);
	acc0 = _mips_shra_r_w(acc0, 2);
	pSrc++;
	acc1 = _mips_mulq_s_w(*pSrc, *pSrc);
	acc1 = _mips_shra_r_w(acc1, 2);
	pSrc++;
	*pDst++ = _mips_addq_s_w(acc0, acc1);

	acc0 = _mips_mulq_s_w(*pSrc, *pSrc);
	acc0 = _mips_shra_r_w(acc0, 2);
	pSrc++;
	acc1 = _mips_mulq_s_w(*pSrc, *pSrc);
	acc1 = _mips_shra_r_w(acc1, 2);
	pSrc++;
	*pDst++ = _mips_addq_s_w(acc0, acc1);

	acc0 = _mips_mulq_s_w(*pSrc, *pSrc);
	acc0 = _mips_shra_r_w(acc0, 2);
	pSrc++;
	acc1 = _mips_mulq_s_w(*pSrc, *pSrc);
	acc1 = _mips_shra_r_w(acc1, 2);
	pSrc++;
	*pDst++ = _mips_addq_s_w(acc0, acc1);

#else

    real = *pSrc++;
    imag = *pSrc++;
    acc0 = (q31) (((q63) real * real) >> 33);
    acc1 = (q31) (((q63) imag * imag) >> 33);
    /* store the result in 3.29 format in the destination buffer. */
    *pDst++ = acc0 + acc1;

    real = *pSrc++;
    imag = *pSrc++;
    acc0 = (q31) (((q63) real * real) >> 33);
    acc1 = (q31) (((q63) imag * imag) >> 33);
    *pDst++ = acc0 + acc1;

    real = *pSrc++;
    imag = *pSrc++;
    acc0 = (q31) (((q63) real * real) >> 33);
    acc1 = (q31) (((q63) imag * imag) >> 33);
    *pDst++ = acc0 + acc1;

    real = *pSrc++;
    imag = *pSrc++;
    acc0 = (q31) (((q63) real * real) >> 33);
    acc1 = (q31) (((q63) imag * imag) >> 33);
    *pDst++ = acc0 + acc1;

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
    /* C[0] = (A[0] * A[0] + A[1] * A[1]) */
#if defined (MIPS_MATH_DSP)

	acc0 = _mips_mulq_s_w(*pSrc, *pSrc);
	acc0 = _mips_shra_r_w(acc0, 2);
	pSrc++;
	acc1 = _mips_mulq_s_w(*pSrc, *pSrc);
	acc1 = _mips_shra_r_w(acc1, 2);
	pSrc++;
	
	*pDst++ = _mips_addq_s_w(acc0, acc1);

#else
    real = *pSrc++;
    imag = *pSrc++;
    acc0 = (q31) (((q63) real * real) >> 33);
    acc1 = (q31) (((q63) imag * imag) >> 33);

    /* store result in 3.29 format in destination buffer. */
    *pDst++ = acc0 + acc1;
#endif /* #if defined (MIPS_MATH_DSP) */

    /* Decrement loop counter */
    blkCnt--;
  }

}

/**
  @} end of cmplx_mag_squared group
 */
