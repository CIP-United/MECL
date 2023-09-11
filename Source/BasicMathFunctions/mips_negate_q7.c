/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_negate_q7.c
 * Description:  Negates Q7 vectors
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
  @brief         Negates the elements of a Q7 vector.
  @param[in]     pSrc       points to the input vector.
  @param[out]    pDst       points to the output vector.
  @param[in]     blockSize   number of samples in each vector.
  @return        none

  @par           Scaling and Overflow Behavior
                   The function uses saturating arithmetic.
                   The Q7 value -1 (0x80) is saturated to the maximum allowable positive value 0x7F.
 */
void mips_negate_q7(
  const q7 * pSrc,
        q7 * pDst,
        uint32_t blockSize)
{
        uint32_t blkCnt;                               /* Loop counter */
        q7 in;                                       /* Temporary input variable */

#if defined (MIPS_MATH_LOOPUNROLL)



  /* Loop unrolling: Compute 4 outputs at a time */
  blkCnt = blockSize >> 2U;

  while (blkCnt > 0U)
  {
    /* C = -A */


    in = *pSrc++;
    *pDst++ = (in == (q7) 0x80) ? (q7) 0x7f : -in;

    in = *pSrc++;
    *pDst++ = (in == (q7) 0x80) ? (q7) 0x7f : -in;

    in = *pSrc++;
    *pDst++ = (in == (q7) 0x80) ? (q7) 0x7f : -in;

    in = *pSrc++;
    *pDst++ = (in == (q7) 0x80) ? (q7) 0x7f : -in;



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


    *pDst++ = (in == (q7) 0x80) ? (q7) 0x7f : -in;

    /* Decrement loop counter */
    blkCnt--;
  }

}

/**
  @} end of BasicNegate group
 */
