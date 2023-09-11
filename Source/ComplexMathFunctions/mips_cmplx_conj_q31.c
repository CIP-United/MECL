/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_cmplx_conj_q31.c
 * Description:  Q31 complex conjugate
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
  @brief         Q31 complex conjugate.
  @param[in]     pSrc        points to the input vector
  @param[out]    pDst        points to the output vector
  @param[in]     numSamples  number of samples in each vector
  @return        none

  @par           Scaling and Overflow Behavior
                   The function uses saturating arithmetic.
                   The Q31 value -1 (0x80000000) is saturated to the maximum allowable positive value 0x7FFFFFFF.
 */

#if defined(MIPS_MATH_DSP)

void mips_cmplx_conj_q31(
  const q31 * pSrc,
        q31 * pDst,
        uint32_t numSamples)
{

    uint32_t blkCnt;
    q31 in;                                        /* Temporary input variable */

	blkCnt = numSamples;
    while (blkCnt > 0U)
    {
		*pDst++ = *pSrc++;
		*pDst++ = _mips_subq_s_w(0, *pSrc++);
        blkCnt --;
    }

}
#else

void mips_cmplx_conj_q31(
  const q31 * pSrc,
        q31 * pDst,
        uint32_t numSamples)
{
        uint32_t blkCnt;                               /* Loop counter */
        q31 in;                                        /* Temporary input variable */

#if defined (MIPS_MATH_LOOPUNROLL)

  /* Loop unrolling: Compute 4 outputs at a time */
  blkCnt = numSamples >> 2U;

  while (blkCnt > 0U)
  {
    /* C[0] + jC[1] = A[0]+ j(-1)A[1] */

    /* Calculate Complex Conjugate and store result in destination buffer. */
    *pDst++ =  *pSrc++;
    in = *pSrc++;

    *pDst++ = (in == INT32_MIN) ? INT32_MAX : -in;

    *pDst++ =  *pSrc++;
    in =  *pSrc++;

    *pDst++ = (in == INT32_MIN) ? INT32_MAX : -in;

    *pDst++ =  *pSrc++;
    in = *pSrc++;

    *pDst++ = (in == INT32_MIN) ? INT32_MAX : -in;

    *pDst++ =  *pSrc++;
    in = *pSrc++;

    *pDst++ = (in == INT32_MIN) ? INT32_MAX : -in;

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
    in = *pSrc++;

    *pDst++ = (in == INT32_MIN) ? INT32_MAX : -in;

    /* Decrement loop counter */
    blkCnt--;
  }

}
#endif /* defined(MIPS_MATH_DSP) */

/**
  @} end of cmplx_conj group
 */
