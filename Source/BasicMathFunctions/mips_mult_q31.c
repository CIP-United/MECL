/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_mult_q31.c
 * Description:  Q31 vector multiplication
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
  @addtogroup BasicMult
  @{
 */

/**
  @brief         Q31 vector multiplication.
  @param[in]     pSrcA      points to the first input vector.
  @param[in]     pSrcB      points to the second input vector.
  @param[out]    pDst       points to the output vector.
  @param[in]     blockSize  number of samples in each vector.
  @return        none

  @par           Scaling and Overflow Behavior
                   The function uses saturating arithmetic.
                   Results outside of the allowable Q31 range[0x80000000 0x7FFFFFFF] are saturated.
 */
#if defined(MIPS_MATH_DSP)


void mips_mult_q31(
    const q31 * pSrcA,
    const q31 * pSrcB,
    q31 * pDst,
    uint32_t blockSize)
{
    uint32_t  blkCnt;           /* loop counters */

    /* Compute 4 outputs at a time */
    blkCnt = blockSize;
    while (blkCnt > 0U)
    {
        /*
         * C = A * B
         * Multiply the inputs and then store the results in the destination buffer.
         */
        *pDst = _mips_mulq_s_w(*pSrcA, *pSrcB);
        /*
         * Decrement the blockSize loop counter
         */
        blkCnt--;
        /*
         * advance vector source and destination pointers
         */
        pSrcA++;
        pSrcB++;
        pDst++;
    }
}

#else
void mips_mult_q31(
  const q31 * pSrcA,
  const q31 * pSrcB,
        q31 * pDst,
        uint32_t blockSize)
{
        uint32_t blkCnt;                               /* Loop counter */
        q31 out;                                     /* Temporary output variable */

#if defined (MIPS_MATH_LOOPUNROLL)

  /* Loop unrolling: Compute 4 outputs at a time */
  blkCnt = blockSize >> 2U;

  while (blkCnt > 0U)
  {
    /* C = A * B */

    /* Multiply inputs and store result in destination buffer. */
    out = ((q63) *pSrcA++ * *pSrcB++) >> 32;
    out = __SSAT(out, 31);
    *pDst++ = out << 1U;

    out = ((q63) *pSrcA++ * *pSrcB++) >> 32;
    out = __SSAT(out, 31);
    *pDst++ = out << 1U;

    out = ((q63) *pSrcA++ * *pSrcB++) >> 32;
    out = __SSAT(out, 31);
    *pDst++ = out << 1U;

    out = ((q63) *pSrcA++ * *pSrcB++) >> 32;
    out = __SSAT(out, 31);
    *pDst++ = out << 1U;

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
    /* C = A * B */

    /* Multiply inputs and store result in destination buffer. */
    out = ((q63) *pSrcA++ * *pSrcB++) >> 32;
    out = __SSAT(out, 31);
    *pDst++ = out << 1U;

    /* Decrement loop counter */
    blkCnt--;
  }

}
#endif /* defined(MIPS_MATH_DPS) */

/**
  @} end of BasicMult group
 */
