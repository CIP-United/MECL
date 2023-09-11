/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_scale_q15.c
 * Description:  Multiplies a Q15 vector by a scalar
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
  @addtogroup BasicScale
  @{
 */

/**
  @brief         Multiplies a Q15 vector by a scalar.
  @param[in]     pSrc       points to the input vector
  @param[in]     scaleFract fractional portion of the scale value
  @param[in]     shift      number of bits to shift the result by
  @param[out]    pDst       points to the output vector
  @param[in]     blockSize  number of samples in each vector
  @return        none

  @par           Scaling and Overflow Behavior
                   The input data <code>*pSrc</code> and <code>scaleFract</code> are in 1.15 format.
                   These are multiplied to yield a 2.30 intermediate result and this is shifted with saturation to 1.15 format.
 */

#if defined(MIPS_MATH_DSP) 


void mips_scale_q15(
    const q15 * pSrc,
    q15   scaleFract,
    int8_t  shift,
    q15 * pDst,
    uint32_t blockSize)
{
    uint32_t  blkCnt;           /* loop counters */
    v2q15 vecSrc;
    v2q15 vecDst;

    /* Compute 2 outputs at a time */
    blkCnt = blockSize >> 1;

    while (blkCnt > 0U)
    {
        /*
         * C = A * scale
         * Scale the input and then store the result in the destination buffer.
         */
        vecSrc = mips_dsp_load_v2q15(pSrc);
        vecDst = __builtin_mips_mulq_s_ph(vecSrc, _mips_replv_ph(scaleFract));
        vecDst = _mips_shll_s_ph(vecDst,shift);
        mips_dsp_store_v2q15(pDst, vecDst);
        /*
         * Decrement the blockSize loop counter
         */
        blkCnt--;
        /*
         * advance vector source and destination pointers
         */
        pSrc += 2;
        pDst += 2;
    }
    /*
     * tail
     */
    blkCnt = blockSize & 1;
    if (blkCnt > 0U)
    {
        /* C = A * scale */

        /* Scale input and store result in destination buffer. */
        *pDst++ = (q15) (__SSAT(((q31) *pSrc++ * scaleFract) >> (15 - shift), 16));

        /* Decrement loop counter */
        blkCnt--;
    }

}


#else
void mips_scale_q15(
  const q15 *pSrc,
        q15 scaleFract,
        int8_t shift,
        q15 *pDst,
        uint32_t blockSize)
{
        uint32_t blkCnt;                               /* Loop counter */
        int8_t kShift = 15 - shift;                    /* Shift to apply after scaling */


#if defined (MIPS_MATH_LOOPUNROLL)

  /* Loop unrolling: Compute 4 outputs at a time */
  blkCnt = blockSize >> 2U;

  while (blkCnt > 0U)
  {
    /* C = A * scale */


    *pDst++ = (q15) (__SSAT(((q31) *pSrc++ * scaleFract) >> kShift, 16));
    *pDst++ = (q15) (__SSAT(((q31) *pSrc++ * scaleFract) >> kShift, 16));
    *pDst++ = (q15) (__SSAT(((q31) *pSrc++ * scaleFract) >> kShift, 16));
    *pDst++ = (q15) (__SSAT(((q31) *pSrc++ * scaleFract) >> kShift, 16));


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
    /* C = A * scale */

    /* Scale input and store result in destination buffer. */
    *pDst++ = (q15) (__SSAT(((q31) *pSrc++ * scaleFract) >> kShift, 16));

    /* Decrement loop counter */
    blkCnt--;
  }

}
#endif /* defined(MIPS_MATH_DSP) */

/**
  @} end of BasicScale group
 */
