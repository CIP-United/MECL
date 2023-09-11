/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_negate_q15.c
 * Description:  Negates Q15 vectors
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
  @addtogroup BasicNegate
  @{
 */

/**
  @brief         Negates the elements of a Q15 vector.
  @param[in]     pSrc       points to the input vector.
  @param[out]    pDst       points to the output vector.
  @param[in]     blockSize  number of samples in each vector.
  @return        none

  @par           Conditions for optimum performance
                   Input and output buffers should be aligned by 32-bit
  @par           Scaling and Overflow Behavior
                   The function uses saturating arithmetic.
                   The Q15 value -1 (0x8000) is saturated to the maximum allowable positive value 0x7FFF.
 */
void mips_negate_q15(
  const q15 * pSrc,
        q15 * pDst,
        uint32_t blockSize)
{
        uint32_t blkCnt;                               /* Loop counter */
        q15 in;                                      /* Temporary input variable */

#if defined (MIPS_MATH_LOOPUNROLL)

#if defined (MIPS_MATH_DSP)
  v2q15 in1;                                    /* Temporary input variables */
#endif

  /* Loop unrolling: Compute 4 outputs at a time */
  blkCnt = blockSize >> 2U;

  while (blkCnt > 0U)
  {
    /* C = -A */

#if defined (MIPS_MATH_DSP)
    /* Negate and store result in destination buffer (2 samples at a time). */
    in1=mips_dsp_load_v2q15(pSrc);
    mips_dsp_store_v2q15(pDst, _mips_subq_s_ph(0,in1));

    pSrc += 2;
    pDst += 2;
    in1=mips_dsp_load_v2q15(pSrc);
    mips_dsp_store_v2q15(pDst, _mips_subq_s_ph(0,in1));
#else
    in = *pSrc++;
    *pDst++ = (in == (q15) 0x8000) ? (q15) 0x7fff : -in;

    in = *pSrc++;
    *pDst++ = (in == (q15) 0x8000) ? (q15) 0x7fff : -in;

    in = *pSrc++;
    *pDst++ = (in == (q15) 0x8000) ? (q15) 0x7fff : -in;

    in = *pSrc++;
    *pDst++ = (in == (q15) 0x8000) ? (q15) 0x7fff : -in;
#endif

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
    /* C = -A */

    /* Negate and store result in destination buffer. */
    in = *pSrc++;
    *pDst++ = (in == (q15) 0x8000) ? (q15) 0x7fff : -in;

    /* Decrement loop counter */
    blkCnt--;
  }

}

/**
  @} end of BasicNegate group
 */
