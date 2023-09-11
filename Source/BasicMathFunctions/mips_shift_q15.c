/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_shift_q15.c
 * Description:  Shifts the elements of a Q15 vector by a specified number of bits
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
  @addtogroup BasicShift
  @{
 */

/**
  @brief         Shifts the elements of a Q15 vector a specified number of bits
  @param[in]     pSrc       points to the input vector
  @param[in]     shiftBits  number of bits to shift.  A positive value shifts left; a negative value shifts right.
  @param[out]    pDst       points to the output vector
  @param[in]     blockSize  number of samples in each vector
  @return        none

  @par           Scaling and Overflow Behavior
                   The function uses saturating arithmetic.
                   Results outside of the allowable Q15 range [0x8000 0x7FFF] are saturated.
 */

#if defined(MIPS_MATH_DSP)

#include "mips_msa_utils.h"

void mips_shift_q15(
    const q15 * pSrc,
    int8_t shiftBits,
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
         * C = A (>> or <<) shiftBits
         * Shift the input and then store the result in the destination buffer.
         */
        if(shiftBits >= 0)
         {
          *pDst++ = __SSAT(((q31) *pSrc++ << shiftBits), 16);
          *pDst++ = __SSAT(((q31) *pSrc++ << shiftBits), 16);
          *pDst++ = __SSAT(((q31) *pSrc++ << shiftBits), 16);
          *pDst++ = __SSAT(((q31) *pSrc++ << shiftBits), 16);
         }
        else
         {
           vecSrc = mips_dsp_load_v2q15(pSrc);
           vecDst = _mips_shra_ph(vecSrc, -shiftBits);
           mips_dsp_store_v2q15(pDst, vecDst);

           pSrc += 2;
           pDst += 2;
         }
        /*
         * Decrement the blockSize loop counter
         */
        blkCnt--;
        /*
         * advance vector source and destination pointers
         */
    }
    /*
     * tail
     */
    blkCnt = blockSize & 1;
    if (shiftBits >= 0)
  {
    while (blkCnt > 0U)
    {
      /* C = A << shiftBits */

      /* Shift input and store result in destination buffer. */
      *pDst++ = __SSAT(((q31) *pSrc++ << shiftBits), 16);

      /* Decrement loop counter */
      blkCnt--;
    }
  }
  else
  {
    while (blkCnt > 0U)
    {
      /* C = A >> shiftBits */

      /* Shift input and store result in destination buffer. */
      *pDst++ = (*pSrc++ >> -shiftBits);

      /* Decrement loop counter */
      blkCnt--;
    }
  }
}

#else
void mips_shift_q15(
  const q15 * pSrc,
        int8_t shiftBits,
        q15 * pDst,
        uint32_t blockSize)
{
        uint32_t blkCnt;                               /* Loop counter */
        uint8_t sign = (shiftBits & 0x80);             /* Sign of shiftBits */

#if defined (MIPS_MATH_LOOPUNROLL)



  /* Loop unrolling: Compute 4 outputs at a time */
  blkCnt = blockSize >> 2U;

  /* If the shift value is positive then do right shift else left shift */
  if (sign == 0U)
  {
    while (blkCnt > 0U)
    {
      /* C = A << shiftBits */


      *pDst++ = __SSAT(((q31) *pSrc++ << shiftBits), 16);
      *pDst++ = __SSAT(((q31) *pSrc++ << shiftBits), 16);
      *pDst++ = __SSAT(((q31) *pSrc++ << shiftBits), 16);
      *pDst++ = __SSAT(((q31) *pSrc++ << shiftBits), 16);


      /* Decrement loop counter */
      blkCnt--;
    }
  }
  else
  {
    while (blkCnt > 0U)
    {
      /* C = A >> shiftBits */


      *pDst++ = (*pSrc++ >> -shiftBits);
      *pDst++ = (*pSrc++ >> -shiftBits);
      *pDst++ = (*pSrc++ >> -shiftBits);
      *pDst++ = (*pSrc++ >> -shiftBits);


      /* Decrement loop counter */
      blkCnt--;
    }
  }

  /* Loop unrolling: Compute remaining outputs */
  blkCnt = blockSize % 0x4U;

#else

  /* Initialize blkCnt with number of samples */
  blkCnt = blockSize;

#endif /* #if defined (MIPS_MATH_LOOPUNROLL) */

  /* If the shift value is positive then do right shift else left shift */
  if (sign == 0U)
  {
    while (blkCnt > 0U)
    {
      /* C = A << shiftBits */

      /* Shift input and store result in destination buffer. */
      *pDst++ = __SSAT(((q31) *pSrc++ << shiftBits), 16);

      /* Decrement loop counter */
      blkCnt--;
    }
  }
  else
  {
    while (blkCnt > 0U)
    {
      /* C = A >> shiftBits */

      /* Shift input and store result in destination buffer. */
      *pDst++ = (*pSrc++ >> -shiftBits);

      /* Decrement loop counter */
      blkCnt--;
    }
  }

}
#endif /* defined(MIPS_MATH_DSP) */

/**
  @} end of BasicShift group
 */
