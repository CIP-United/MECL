/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_cmplx_mult_cmplx_q31.c
 * Description:  Q31 complex-by-complex multiplication
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
  @brief         Q31 complex-by-complex multiplication.
  @param[in]     pSrcA       points to first input vector
  @param[in]     pSrcB       points to second input vector
  @param[out]    pDst        points to output vector
  @param[in]     numSamples  number of samples in each vector
  @return        none

  @par           Scaling and Overflow Behavior
                   The function implements 1.31 by 1.31 multiplications and finally output is converted into 3.29 format.
                   Input down scaling is not required.
 */

void mips_cmplx_mult_cmplx_q31(
  const q31 * pSrcA,
  const q31 * pSrcB,
        q31 * pDst,
        uint32_t numSamples)
{
        uint32_t blkCnt;                               /* Loop counter */
        q31 a, b, c, d;                              /* Temporary variables */

#if defined (MIPS_MATH_LOOPUNROLL)

  /* Loop unrolling: Compute 4 outputs at a time */
  blkCnt = numSamples >> 2U;

  while (blkCnt > 0U)
  {
    /* C[2 * i    ] = A[2 * i] * B[2 * i    ] - A[2 * i + 1] * B[2 * i + 1]. */
    /* C[2 * i + 1] = A[2 * i] * B[2 * i + 1] + A[2 * i + 1] * B[2 * i    ]. */

#if defined (MIPS_MATH_DSP)

    a = *pSrcA++;
    b = *pSrcA++;
    c = *pSrcB++;
    d = *pSrcB++;
	*pDst++ = (q31) (_mips_shra_r_w(_mips_mulq_s_w(a, c), 2) - _mips_shra_r_w(_mips_mulq_s_w(b, d), 2));
	*pDst++ = (q31) (_mips_shra_r_w(_mips_mulq_s_w(a, d), 2) + _mips_shra_r_w(_mips_mulq_s_w(b, c), 2));

	a = *pSrcA++;
    b = *pSrcA++;
    c = *pSrcB++;
    d = *pSrcB++;
	*pDst++ = (q31) (_mips_shra_r_w(_mips_mulq_s_w(a, c), 2) - _mips_shra_r_w(_mips_mulq_s_w(b, d), 2));
	*pDst++ = (q31) (_mips_shra_r_w(_mips_mulq_s_w(a, d), 2) + _mips_shra_r_w(_mips_mulq_s_w(b, c), 2));

    a = *pSrcA++;
    b = *pSrcA++;
    c = *pSrcB++;
    d = *pSrcB++;
	*pDst++ = (q31) (_mips_shra_r_w(_mips_mulq_s_w(a, c), 2) - _mips_shra_r_w(_mips_mulq_s_w(b, d), 2));
	*pDst++ = (q31) (_mips_shra_r_w(_mips_mulq_s_w(a, d), 2) + _mips_shra_r_w(_mips_mulq_s_w(b, c), 2));

    a = *pSrcA++;
    b = *pSrcA++;
    c = *pSrcB++;
    d = *pSrcB++;
	*pDst++ = (q31) (_mips_shra_r_w(_mips_mulq_s_w(a, c), 2) - _mips_shra_r_w(_mips_mulq_s_w(b, d), 2));
	*pDst++ = (q31) (_mips_shra_r_w(_mips_mulq_s_w(a, d), 2) + _mips_shra_r_w(_mips_mulq_s_w(b, c), 2));
#else

    a = *pSrcA++;
    b = *pSrcA++;
    c = *pSrcB++;
    d = *pSrcB++;
    /* store result in 3.29 format in destination buffer. */
    *pDst++ = (q31) ( (((q63) a * c) >> 33) - (((q63) b * d) >> 33) );
    *pDst++ = (q31) ( (((q63) a * d) >> 33) + (((q63) b * c) >> 33) );

    a = *pSrcA++;
    b = *pSrcA++;
    c = *pSrcB++;
    d = *pSrcB++;
    *pDst++ = (q31) ( (((q63) a * c) >> 33) - (((q63) b * d) >> 33) );
    *pDst++ = (q31) ( (((q63) a * d) >> 33) + (((q63) b * c) >> 33) );

    a = *pSrcA++;
    b = *pSrcA++;
    c = *pSrcB++;
    d = *pSrcB++;
    *pDst++ = (q31) ( (((q63) a * c) >> 33) - (((q63) b * d) >> 33) );
    *pDst++ = (q31) ( (((q63) a * d) >> 33) + (((q63) b * c) >> 33) );

    a = *pSrcA++;
    b = *pSrcA++;
    c = *pSrcB++;
    d = *pSrcB++;
    *pDst++ = (q31) ( (((q63) a * c) >> 33) - (((q63) b * d) >> 33) );
    *pDst++ = (q31) ( (((q63) a * d) >> 33) + (((q63) b * c) >> 33) );

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

    a = *pSrcA++;
    b = *pSrcA++;
    c = *pSrcB++;
    d = *pSrcB++;

#if defined (MIPS_MATH_DSP)
	*pDst++ = (q31) (_mips_shra_r_w(_mips_mulq_s_w(a, c), 2) - _mips_shra_r_w(_mips_mulq_s_w(b, d), 2));
	*pDst++ = (q31) (_mips_shra_r_w(_mips_mulq_s_w(a, d), 2) + _mips_shra_r_w(_mips_mulq_s_w(b, c), 2));
	
#else

    /* store result in 3.29 format in destination buffer. */
    *pDst++ = (q31) ( (((q63) a * c) >> 33) - (((q63) b * d) >> 33) );
    *pDst++ = (q31) ( (((q63) a * d) >> 33) + (((q63) b * c) >> 33) );

#endif /* #if defined (MIPS_MATH_DSP) */
    /* Decrement loop counter */
    blkCnt--;
  }

}

/**
  @} end of CmplxByCmplxMult group
 */
