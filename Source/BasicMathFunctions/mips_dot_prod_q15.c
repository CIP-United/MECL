/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_dot_prod_q15.c
 * Description:  Q15 dot product
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

#include "dsp/basic_math_functions.h"

/**
  @ingroup groupMath
 */

/**
  @addtogroup BasicDotProd
  @{
 */

/**
  @brief         Dot product of Q15 vectors.
  @param[in]     pSrcA      points to the first input vector
  @param[in]     pSrcB      points to the second input vector
  @param[in]     blockSize  number of samples in each vector
  @param[out]    result     output result returned here
  @return        none

  @par           Scaling and Overflow Behavior
                   The intermediate multiplications are in 1.15 x 1.15 = 2.30 format and these
                   results are added to a 64-bit accumulator in 34.30 format.
                   Nonsaturating additions are used and given that there are 33 guard bits in the accumulator
                   there is no risk of overflow.
                   The return result is in 34.30 format.
 */
#if defined(MIPS_MATH_DSP)

#include "mips_msa_utils.h"

void mips_dot_prod_q15(
    const q15 * pSrcA,
    const q15 * pSrcB,
    uint32_t blockSize,
    q63 * result)
{
    uint32_t  blkCnt;           /* loop counters */
    v2q15 vecA;
    v2q15 vecB;
    q63   sum = 0LL;

    /* Compute 2 outputs at a time */
    blkCnt = blockSize >> 1;
    while (blkCnt > 0U)
    {
        /*
         * C = A[0]* B[0] + A[1]* B[1] + A[2]* B[2] + .....+ A[blockSize-1]* B[blockSize-1]
         * Calculate dot product and then store the result in a temporary buffer.
         */
        vecA = mips_dsp_load_v2q15(pSrcA);
        vecB = mips_dsp_load_v2q15(pSrcB);
        sum  = _mips_dpa_w_ph(sum, vecA, vecB);
        /*
         * Decrement the blockSize loop counter
         */
        blkCnt--;
        /*
         * advance vector source and destination pointers
         */
        pSrcA += 2;
        pSrcB += 2;
    }
    /*
     * tail
     */
    blkCnt = blockSize & 1;

    while (blkCnt > 0U)
  {
    /* C = A[0]* B[0] + A[1]* B[1] + A[2]* B[2] + .....+ A[blockSize-1]* B[blockSize-1] */

    /* Calculate dot product and store result in a temporary buffer. */
//#if defined (MIPS_MATH_DSP)
//    sum  = __SMLALD(*pSrcA++, *pSrcB++, sum);
//#else
    sum += (q63)((q31) *pSrcA++ * *pSrcB++);
//#endif

    /* Decrement loop counter */
    blkCnt--;
  }

    *result = sum;
}

#else
void mips_dot_prod_q15(
  const q15 * pSrcA,
  const q15 * pSrcB,
        uint32_t blockSize,
        q63 * result)
{
        uint32_t blkCnt;                               /* Loop counter */
        q63 sum = 0;                                 /* Temporary return variable */

#if defined (MIPS_MATH_LOOPUNROLL)

  /* Loop unrolling: Compute 4 outputs at a time */
  blkCnt = blockSize >> 2U;

  while (blkCnt > 0U)
  {
    /* C = A[0]* B[0] + A[1]* B[1] + A[2]* B[2] + .....+ A[blockSize-1]* B[blockSize-1] */


    sum += (q63)((q31) *pSrcA++ * *pSrcB++);
    sum += (q63)((q31) *pSrcA++ * *pSrcB++);
    sum += (q63)((q31) *pSrcA++ * *pSrcB++);
    sum += (q63)((q31) *pSrcA++ * *pSrcB++);

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
    /* C = A[0]* B[0] + A[1]* B[1] + A[2]* B[2] + .....+ A[blockSize-1]* B[blockSize-1] */

    /* Calculate dot product and store result in a temporary buffer. */
//#if defined (MIPS_MATH_DSP)
//    sum  = __SMLALD(*pSrcA++, *pSrcB++, sum);
//#else
    sum += (q63)((q31) *pSrcA++ * *pSrcB++);
//#endif

    /* Decrement loop counter */
    blkCnt--;
  }

  /* Store result in destination buffer in 34.30 format */
  *result = sum;
}
#endif /* defined(MIPS_MATH_DSP) */

/**
  @} end of BasicDotProd group
 */
