/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_q15_to_q31.c
 * Description:  Converts the elements of the Q15 vector to Q31 vector
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
  @addtogroup q15_to_x
  @{
 */

/**
  @brief         Converts the elements of the Q15 vector to Q31 vector.
  @param[in]     pSrc       points to the Q15 input vector
  @param[out]    pDst       points to the Q31 output vector
  @param[in]     blockSize  number of samples in each vector
  @return        none

  @par           Details
                   The equation used for the conversion process is:
  <pre>
      pDst[n] = (q31) pSrc[n] << 16;   0 <= n < blockSize.
  </pre>
 */
#if defined(MIPS_MATH_DSP)
void mips_q15_to_q31(
  const q15 * pSrc,
        q31 * pDst,
        uint32_t blockSize)
{

  uint32_t blkCnt;

  v2q15 vecPrc;

  blkCnt = blockSize>> 1;
  while (blkCnt > 0U)
  {

        /* C = (q31)A << 16 */
        /* convert from q15 to q31 and then store the results in the destination buffer */
        /* load q15 + 32-bit widening */
        vecPrc = mips_dsp_load_v2q15(pSrc);
        *pDst++ = _mips_preceq_w_phr(vecPrc);
        *pDst++ = _mips_preceq_w_phl(vecPrc);


        /*
         * Decrement the blockSize loop counter
         * Advance vector source and destination pointers
         */
        
        pSrc += 2;
        blkCnt --;
    }

  blkCnt = blockSize & 1;
  while (blkCnt > 0U)
  {
    /* C = (q31) A << 16 */

    /* Convert from q15 to q31 and store result in destination buffer */
    *pDst++ = (q31) *pSrc++ << 16;

    /* Decrement loop counter */
    blkCnt--;
  }
}
#else
void mips_q15_to_q31(
  const q15 * pSrc,
        q31 * pDst,
        uint32_t blockSize)
{
        uint32_t blkCnt;                               /* Loop counter */
  const q15 *pIn = pSrc;                             /* Source pointer */

#if defined (MIPS_MATH_LOOPUNROLL)
        q31 in1, in2;
        q31 out1, out2, out3, out4;
#endif
#if defined (MIPS_MATH_LOOPUNROLL)

  /* Loop unrolling: Compute 4 outputs at a time */
  blkCnt = blockSize >> 2U;

  while (blkCnt > 0U)
  {
    /* C = (q31)A << 16 */

    /* Convert from q15 to q31 and store result in destination buffer */
    in1 = read_q15x2_ia (&pIn);
    in2 = read_q15x2_ia (&pIn);

#ifndef MIPS_MATH_BIG_ENDIAN

    /* extract lower 16 bits to 32 bit result */
    out1 = in1 << 16U;
    /* extract upper 16 bits to 32 bit result */
    out2 = in1 & 0xFFFF0000;
    /* extract lower 16 bits to 32 bit result */
    out3 = in2 << 16U;
    /* extract upper 16 bits to 32 bit result */
    out4 = in2 & 0xFFFF0000;

#else

    /* extract upper 16 bits to 32 bit result */
    out1 = in1 & 0xFFFF0000;
    /* extract lower 16 bits to 32 bit result */
    out2 = in1 << 16U;
    /* extract upper 16 bits to 32 bit result */
    out3 = in2 & 0xFFFF0000;
    /* extract lower 16 bits to 32 bit result */
    out4 = in2 << 16U;

#endif /* #ifndef MIPS_MATH_BIG_ENDIAN */

    *pDst++ = out1;
    *pDst++ = out2;
    *pDst++ = out3;
    *pDst++ = out4;

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
    /* C = (q31) A << 16 */

    /* Convert from q15 to q31 and store result in destination buffer */
    *pDst++ = (q31) *pIn++ << 16;

    /* Decrement loop counter */
    blkCnt--;
  }

}
#endif /* defined(MIPS_MATH_DSP) */

/**
  @} end of q15_to_x group
 */
