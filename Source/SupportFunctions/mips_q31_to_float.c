/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_q31_to_float.c
 * Description:  Converts the elements of the Q31 vector to floating-point vector
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
 * @defgroup q31_to_x  Convert 32-bit fixed point value
 */

/**
  @addtogroup q31_to_x
  @{
 */

/**
  @brief         Converts the elements of the Q31 vector to floating-point vector.
  @param[in]     pSrc       points to the Q31 input vector
  @param[out]    pDst       points to the floating-point output vector
  @param[in]     blockSize  number of samples in each vector
  @return        none

  @par           Details
                   The equation used for the conversion process is:
  <pre>
      pDst[n] = (f32) pSrc[n] / 2147483648;   0 <= n < blockSize.
  </pre>
 */

void mips_q31_to_float(
  const q31 * pSrc,
  f32 * pDst,
  uint32_t blockSize)
{
  const q31 *pIn = pSrc;                             /* Src pointer */
  uint32_t blkCnt;                               /* loop counter */

#if defined (MIPS_MATH_LOOPUNROLL)

  /* Loop unrolling */
  blkCnt = blockSize >> 2U;

  while (blkCnt > 0U)
  {
    /* C = (f32) A / 2147483648 */

    /* Convert from q31 to float and store result in destination buffer */
    *pDst++ = ((f32) *pIn++ / 2147483648.0f);
    *pDst++ = ((f32) *pIn++ / 2147483648.0f);
    *pDst++ = ((f32) *pIn++ / 2147483648.0f);
    *pDst++ = ((f32) *pIn++ / 2147483648.0f);

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
    /* C = (f32) A / 2147483648 */

    /* Convert from q31 to float and store result in destination buffer */
    *pDst++ = ((f32) *pIn++ / 2147483648.0f);

    /* Decrement loop counter */
    blkCnt--;
  }

}

/**
  @} end of q31_to_x group
 */
