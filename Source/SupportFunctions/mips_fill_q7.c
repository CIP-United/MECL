/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_fill_q7.c
 * Description:  Fills a constant value into a Q7 vector
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

#include "dsp/support_functions.h"

/**
  @ingroup groupSupport
 */

/**
  @addtogroup Fill
  @{
 */

/**
  @brief         Fills a constant value into a Q7 vector.
  @param[in]     value      input value to be filled
  @param[out]    pDst       points to output vector
  @param[in]     blockSize  number of samples in each vector
  @return        none
 */
#if defined(MIPS_MATH_DSP)
void mips_fill_q7(
  q7 value,
  q7 * pDst,
  uint32_t blockSize)
{
  uint32_t blkCnt; 

  blkCnt = blockSize >> 2;
  while (blkCnt > 0U)
  {

        mips_dsp_store_v4q7(pDst,_mips_replv_qb(value));
        /*
         * Decrement the blockSize loop counter
         * Advance vector source and destination pointers
         */
        pDst += 4;
        blkCnt --;
    }

  blkCnt = blockSize & 0x3;
  while (blkCnt > 0U)
  {
    /* C = value */

    /* Fill value in destination buffer */
    *pDst++ = value;

    /* Decrement loop counter */
    blkCnt--;
  }
}
#else
void mips_fill_q7(
  q7 value,
  q7 * pDst,
  uint32_t blockSize)
{
  uint32_t blkCnt;                               /* Loop counter */

#if defined (MIPS_MATH_LOOPUNROLL)
  q31 packedValue;                             /* value packed to 32 bits */

  /* Packing four 8 bit values to 32 bit value in order to use SIMD */
  packedValue = __PACKq7(value, value, value, value);

  /* Loop unrolling: Compute 4 outputs at a time */
  blkCnt = blockSize >> 2U;

  while (blkCnt > 0U)
  {
    /* C = value */

    /* fill 4 samples at a time */
    write_q7x4_ia (&pDst, packedValue);

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
    /* C = value */

    /* Fill value in destination buffer */
    *pDst++ = value;

    /* Decrement loop counter */
    blkCnt--;
  }
}
#endif /* defined(MIPS_MATH_DSP) */

/**
  @} end of Fill group
 */
