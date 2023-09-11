/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_cmplx_dot_prod_q15.c
 * Description:  Processing function for the Q15 Complex Dot product
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
  @addtogroup cmplx_dot_prod
  @{
 */

/**
  @brief         Q15 complex dot product.
  @param[in]     pSrcA       points to the first input vector
  @param[in]     pSrcB       points to the second input vector
  @param[in]     numSamples  number of samples in each vector
  @param[out]    realResult  real part of the result returned here
  @param[out]    imagResult  imaginary part of the result returned her
  @return        none

  @par           Scaling and Overflow Behavior
                   The function is implemented using an internal 64-bit accumulator.
                   The intermediate 1.15 by 1.15 multiplications are performed with full precision and yield a 2.30 result.
                   These are accumulated in a 64-bit accumulator with 34.30 precision.
                   As a final step, the accumulators are converted to 8.24 format.
                   The return results <code>realResult</code> and <code>imagResult</code> are in 8.24 format.
 */

void mips_cmplx_dot_prod_q15(
  const q15 * pSrcA,
  const q15 * pSrcB,
        uint32_t numSamples,
        q31 * realResult,
        q31 * imagResult)
{
        uint32_t blkCnt;                               /* Loop counter */
        q63 real_sum = 0, imag_sum = 0;                /* Temporary result variables */
    	q15 a0,b0,c0,d0;

#if defined(MIPS_MATH_DSP)

	v2q15 va0,vb0,vc0,vd0;

  /* Initialize blkCnt with number of samples */
  /* Loop unrolling: Compute 2 outputs at a time */
  blkCnt = numSamples >> 1U;

  while (blkCnt > 0U)
  {

	  va0 = mips_dsp_set_v2q15(*pSrcA, *(pSrcA + 2));	   // A0,A2
	  vb0 = mips_dsp_set_v2q15(*pSrcB, *(pSrcB + 2));	   // B0,B2
	  vc0 = mips_dsp_set_v2q15(*(pSrcA + 1), *(pSrcA + 3)); // A1,A3
	  vd0 = mips_dsp_set_v2q15(*(pSrcB + 1), *(pSrcB + 3)); // B1,B3

	  real_sum = _mips_dpa_w_ph(real_sum, va0, vb0); // A0*B0+A2*B2
	  imag_sum = _mips_dpa_w_ph(imag_sum, va0, vd0); // A0*B1+A2*B2
	  real_sum = _mips_dps_w_ph(real_sum, vc0, vd0); // A1*B1-A3*B3
	  imag_sum = _mips_dpa_w_ph(imag_sum, vc0, vb0); // A1*B0+A3*B2

	  pSrcA += 4;
	  pSrcB += 4;

	  /* Decrement loop counter */
	  blkCnt--;
  }

  /* Loop unrolling: Compute remaining outputs */
  blkCnt = numSamples % 0x2U;

#else

#if defined (MIPS_MATH_LOOPUNROLL)
  /* Loop unrolling: Compute 4 outputs at a time */
  blkCnt = numSamples >> 2U;

  while (blkCnt > 0U)
  {
    a0 = *pSrcA++;
    b0 = *pSrcA++;
    c0 = *pSrcB++;
    d0 = *pSrcB++;

    real_sum += (q31)a0 * c0;
    imag_sum += (q31)a0 * d0;
    real_sum -= (q31)b0 * d0;
    imag_sum += (q31)b0 * c0;

    a0 = *pSrcA++;
    b0 = *pSrcA++;
    c0 = *pSrcB++;
    d0 = *pSrcB++;

    real_sum += (q31)a0 * c0;
    imag_sum += (q31)a0 * d0;
    real_sum -= (q31)b0 * d0;
    imag_sum += (q31)b0 * c0;

    a0 = *pSrcA++;
    b0 = *pSrcA++;
    c0 = *pSrcB++;
    d0 = *pSrcB++;

    real_sum += (q31)a0 * c0;
    imag_sum += (q31)a0 * d0;
    real_sum -= (q31)b0 * d0;
    imag_sum += (q31)b0 * c0;

    a0 = *pSrcA++;
    b0 = *pSrcA++;
    c0 = *pSrcB++;
    d0 = *pSrcB++;

    real_sum += (q31)a0 * c0;
    imag_sum += (q31)a0 * d0;
    real_sum -= (q31)b0 * d0;
    imag_sum += (q31)b0 * c0;

    /* Decrement loop counter */
    blkCnt--;
  }

  /* Loop unrolling: Compute remaining outputs */
  blkCnt = numSamples % 0x4U;

#else

  /* Initialize blkCnt with number of samples */
  blkCnt = numSamples;

#endif /* #if defined (MIPS_MATH_LOOPUNROLL) */
#endif /* defined(MIPS_MATH_DSP) */

  while (blkCnt > 0U)
  {
    a0 = *pSrcA++;
    b0 = *pSrcA++;
    c0 = *pSrcB++;
    d0 = *pSrcB++;

    real_sum += (q31)a0 * c0;
    imag_sum += (q31)a0 * d0;
    real_sum -= (q31)b0 * d0;
    imag_sum += (q31)b0 * c0;

    /* Decrement loop counter */
    blkCnt--;
  }

  /* Store real and imaginary result in 8.24 format  */
  /* Convert real data in 34.30 to 8.24 by 6 right shifts */
  *realResult = (q31) (real_sum >> 6);
  /* Convert imaginary data in 34.30 to 8.24 by 6 right shifts */
  *imagResult = (q31) (imag_sum >> 6);
}

/**
  @} end of cmplx_dot_prod group
 */
