/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_f64_to_q7.c
 * Description:  Converts the elements of the 64 bit floating-point vector to Q7 vector
 *
 * $Date:        31 Augest 2023
 * $Revision:    V1.0.0
 *
 * -------------------------------------------------------------------- */
/*
 * Copyright (C) 2010-2022 ARM Limited or its affiliates. All rights reserved.
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
  @addtogroup f64_to_x
  @{
 */

/**
 * @brief Converts the elements of the 64 bit floating-point vector to Q7 vector.
 * @param[in]       *pSrc points to the 64 bit floating-point input vector
 * @param[out]      *pDst points to the Q7 output vector
 * @param[in]       blockSize length of the input vector
 * @return none.
 *
 *\par Description:
 * \par
 * The equation used for the conversion process is:
 * <pre>
 *   pDst[n] = (q7)(pSrc[n] * 128);   0 <= n < blockSize.
 * </pre>
 * \par Scaling and Overflow Behavior:
 * \par
 * The function uses saturating arithmetic.
 * Results outside of the allowable Q7 range [0x80 0x7F] will be saturated.
 * \note
 * In order to apply rounding, the library should be rebuilt with the ROUNDING macro
 * defined in the preprocessor section of project options.
 */

void mips_f64_to_q7(
  const f64 * pSrc,
        q7 * pDst,
        uint32_t blockSize)
{
        uint32_t blkCnt;                               /* Loop counter */
  const f64 *pIn = pSrc;                         /* Source pointer */

#ifdef MIPS_MATH_ROUNDING
        f64 in;
#endif /* #ifdef MIPS_MATH_ROUNDING */

#if defined (MIPS_MATH_LOOPUNROLL)

  /* Loop unrolling: Compute 4 outputs at a time */
  blkCnt = blockSize >> 2U;

  while (blkCnt > 0U)
  {
    /* C = A * 128 */

    /* Convert from float to q7 and store result in destination buffer */
#ifdef MIPS_MATH_ROUNDING

    in = (*pIn++ * 128);
    in += in > 0.0 ? 0.5 : -0.5;
    *pDst++ = (q7) (__SSAT((q15) (in), 8));

    in = (*pIn++ * 128);
    in += in > 0.0 ? 0.5 : -0.5;
    *pDst++ = (q7) (__SSAT((q15) (in), 8));

    in = (*pIn++ * 128);
    in += in > 0.0 ? 0.5 : -0.5;
    *pDst++ = (q7) (__SSAT((q15) (in), 8));

    in = (*pIn++ * 128);
    in += in > 0.0 ? 0.5 : -0.5;
    *pDst++ = (q7) (__SSAT((q15) (in), 8));

#else

    *pDst++ = __SSAT((q31) (*pIn++ * 128.0), 8);
    *pDst++ = __SSAT((q31) (*pIn++ * 128.0), 8);
    *pDst++ = __SSAT((q31) (*pIn++ * 128.0), 8);
    *pDst++ = __SSAT((q31) (*pIn++ * 128.0), 8);

#endif /* #ifdef MIPS_MATH_ROUNDING */

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
    /* C = A * 128 */

    /* Convert from float to q7 and store result in destination buffer */
#ifdef MIPS_MATH_ROUNDING

    in = (*pIn++ * 128);
    in += in > 0.0 ? 0.5 : -0.5;
    *pDst++ = (q7) (__SSAT((q15) (in), 8));

#else

    *pDst++ = (q7) __SSAT((q31) (*pIn++ * 128.0), 8);

#endif /* #ifdef MIPS_MATH_ROUNDING */

    /* Decrement loop counter */
    blkCnt--;
  }

}


/**
  @} end of f64_to_x group
 */
