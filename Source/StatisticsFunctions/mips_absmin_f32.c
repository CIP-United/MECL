/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_absmin_f32.c
 * Description:  Minimum value of absolute values of a floating-point vector
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

#include "dsp/statistics_functions.h"



/**
  @ingroup groupStats
 */

/**
  @defgroup AbsMin Absolute Minimum

  Computes the minimum value of absolute values of an array of data.
  The function returns both the minimum value and its position within the array.
  There are separate functions for floating-point, Q31, Q15, and Q7 data types.
 */

/**
  @addtogroup AbsMin
  @{
 */

/**
  @brief         Minimum value of absolute values of a floating-point vector.
  @param[in]     pSrc       points to the input vector
  @param[in]     blockSize  number of samples in input vector
  @param[out]    pResult    minimum value returned here
  @param[out]    pIndex     index of minimum value returned here
  @return        none
 */


#if defined(MIPS_MATH_LOOPUNROLL)
void mips_absmin_f32(
  const f32 * pSrc,
        uint32_t blockSize,
        f32 * pResult,
        uint32_t * pIndex)
{
        f32 cur_absmin, out;                     /* Temporary variables to store the output value. */\
        uint32_t blkCnt, outIndex;                     /* Loop counter */                                   \
        uint32_t index;                                /* index of maximum value */                         \
                                                                                                            \
  /* Initialize index value to zero. */                                                                     \
  outIndex = 0U;                                                                                            \
  /* Load first input value that act as reference value for comparision */                                  \
  out = *pSrc++;                                                                                            \
  out = (out > 0.0f) ? out : -out;                                                                             \
  /* Initialize index of extrema value. */                                                                  \
  index = 0U;                                                                                               \
                                                                                                            \
  /* Loop unrolling: Compute 4 outputs at a time */                                                         \
  blkCnt = (blockSize - 1U) >> 2U;                                                                          \
                                                                                                            \
  while (blkCnt > 0U)                                                                                       \
  {                                                                                                         \
    /* Initialize cur_absmin to next consecutive values one by one */                                         \
    cur_absmin = *pSrc++;                                                                                     \
    cur_absmin = (cur_absmin > 0.0f) ? cur_absmin : -cur_absmin;                                                                 \
    /* compare for the extrema value */                                                                     \
    if (cur_absmin < out)                                                                         \
    {                                                                                                       \
      /* Update the extrema value and it's index */                                                         \
      out = cur_absmin;                                                                                       \
      outIndex = index + 1U;                                                                                \
    }                                                                                                       \
                                                                                                            \
    cur_absmin = *pSrc++;                                                                                     \
    cur_absmin = (cur_absmin > 0.0f) ? cur_absmin : -cur_absmin;                                                                 \
    if (cur_absmin < out)                                                                         \
    {                                                                                                       \
      out = cur_absmin;                                                                                       \
      outIndex = index + 2U;                                                                                \
    }                                                                                                       \
                                                                                                            \
    cur_absmin = *pSrc++;                                                                                     \
    cur_absmin = (cur_absmin > 0.0f) ? cur_absmin : -cur_absmin;                                                                 \
    if (cur_absmin < out)                                                                          \
    {                                                                                                       \
      out = cur_absmin;                                                                                       \
      outIndex = index + 3U;                                                                                \
    }                                                                                                       \
                                                                                                            \
    cur_absmin = *pSrc++;                                                                                     \
    cur_absmin = (cur_absmin > 0.0f) ? cur_absmin : -cur_absmin;                                                                 \
    if (cur_absmin < out)                                                                          \
    {                                                                                                       \
      out = cur_absmin;                                                                                       \
      outIndex = index + 4U;                                                                                \
    }                                                                                                       \
                                                                                                            \
    index += 4U;                                                                                            \
                                                                                                            \
    /* Decrement loop counter */                                                                            \
    blkCnt--;                                                                                               \
  }                                                                                                         \
                                                                                                            \
  /* Loop unrolling: Compute remaining outputs */                                                           \
  blkCnt = (blockSize - 1U) % 4U;                                                                           \
                                                                                                            \
                                                                                                            \
  while (blkCnt > 0U)                                                                                       \
  {                                                                                                         \
    cur_absmin = *pSrc++;                                                                                     \
    cur_absmin = (cur_absmin > 0.0f) ? cur_absmin : -cur_absmin;                                                                 \
    if (cur_absmin < out)                                                                         \
    {                                                                                                       \
      out = cur_absmin;                                                                                       \
      outIndex = blockSize - blkCnt;                                                                        \
    }                                                                                                       \
                                                                                                            \
    /* Decrement loop counter */                                                                            \
    blkCnt--;                                                                                               \
  }                                                                                                         \
                                                                                                            \
  /* Store the extrema value and it's index into destination pointers */                                    \
  *pResult = out;                                                                                           \
  *pIndex = outIndex;  
}
#else
void mips_absmin_f32(
  const f32 * pSrc,
        uint32_t blockSize,
        f32 * pResult,
        uint32_t * pIndex)
{
       f32 minVal, out;                         /* Temporary variables to store the output value. */
       uint32_t blkCnt, outIndex;                     /* Loop counter */

  /* Initialise index value to zero. */
  outIndex = 0U;

  /* Load first input value that act as reference value for comparision */
  out = fabsf(*pSrc++);

  /* Initialize blkCnt with number of samples */
  blkCnt = (blockSize - 1U);

  while (blkCnt > 0U)
  {
    /* Initialize minVal to the next consecutive values one by one */
    minVal = fabsf(*pSrc++);

    /* compare for the minimum value */
    if (out > minVal)
    {
      /* Update the minimum value and it's index */
      out = minVal;
      outIndex = blockSize - blkCnt;
    }

    /* Decrement loop counter */
    blkCnt--;
  }

  /* Store the minimum value and it's index into destination pointers */
  *pResult = out;
  *pIndex = outIndex;
}

#endif /* defined(MIPS_MATH_LOOPUNROLL) */
/**
  @} end of AbsMin group
 */
