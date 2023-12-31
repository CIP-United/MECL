/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_mat_scale_q31.c
 * Description:  Multiplies a Q31 matrix by a scalar
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

#include "dsp/matrix_functions.h"

/**
  @ingroup groupMatrix
 */

/**
  @addtogroup MatrixScale
  @{
 */

/**
  @brief         Q31 matrix scaling.
  @param[in]     pSrc        points to input matrix
  @param[in]     scaleFract  fractional portion of the scale factor
  @param[in]     shift       number of bits to shift the result by
  @param[out]    pDst        points to output matrix structure
  @return        execution status
                   - \ref MIPS_MATH_SUCCESS       : Operation successful
                   - \ref MIPS_MATH_SIZE_MISMATCH : Matrix size check failed

  @par           Scaling and Overflow Behavior
                   The input data <code>*pSrc</code> and <code>scaleFract</code> are in 1.31 format.
                   These are multiplied to yield a 2.62 intermediate result which is shifted with saturation to 1.31 format.
 */
#if defined(MIPS_MATH_DSP)
mips_status mips_mat_scale_q31(
  const mips_matrix_instance_q31 * pSrc,
        q31                     scaleFract,
        int32_t                   shift,
        mips_matrix_instance_q31 * pDst)
{
    q31 *pIn = pSrc->pData;       /* input data matrix pointer */
    q31 *pOut = pDst->pData;      /* output data matrix pointer */
    uint32_t  numSamples;           /* total number of elements in the matrix */
    uint32_t  blkCnt;               /* loop counters */
    q31    const *pInVec;
    mips_status status;                             /* Status of matrix scaling */

    pInVec = (q31 const *) pIn;
  #ifdef MIPS_MATH_MATRIX_CHECK

  /* Check for matrix mismatch condition */
  if ((pSrc->numRows != pDst->numRows) ||
      (pSrc->numCols != pDst->numCols)   )
  {
    /* Set status as MIPS_MATH_SIZE_MISMATCH */
    status = MIPS_MATH_SIZE_MISMATCH;
  }
  else

#endif /* #ifdef MIPS_MATH_MATRIX_CHECK */
  {

     /*
     * Total number of samples in the input matrix
     */
    numSamples = (uint32_t) pSrc->numRows * pSrc->numCols;
    blkCnt = numSamples;
    while (blkCnt > 0U)
    {
        /*
         * C(m,n) = A(m,n) * scale
         * Scaling and results are stored in the destination buffer.
         */
        
        /* multiply input with scaler value */
        *pOut = _mips_mulq_s_w(*pInVec, scaleFract);
        /* apply shifting */
        *pOut = _mips_shll_s_w(*pOut, shift);

        pInVec ++ ;
        pOut ++ ;
        /*
         * Decrement the blockSize loop counter
         */
        blkCnt--;
    }
     /* Set status as MIPS_MATH_SUCCESS */
     status = MIPS_MATH_SUCCESS;
  }

  /* Return to application */
  return (status);
}

#else
mips_status mips_mat_scale_q31(
  const mips_matrix_instance_q31 * pSrc,
        q31                     scaleFract,
        int32_t                   shift,
        mips_matrix_instance_q31 * pDst)
{
  q31 *pIn = pSrc->pData;                      /* Input data matrix pointer */
  q31 *pOut = pDst->pData;                     /* Output data matrix pointer */
  uint32_t numSamples;                           /* Total number of elements in the matrix */
  uint32_t blkCnt;                               /* Loop counter */
  mips_status status;                             /* Status of matrix scaling */
  int32_t kShift = shift + 1;                    /* Shift to apply after scaling */
  q31 in, out;                                 /* Temporary variabels */

#ifdef MIPS_MATH_MATRIX_CHECK

  /* Check for matrix mismatch condition */
  if ((pSrc->numRows != pDst->numRows) ||
      (pSrc->numCols != pDst->numCols)   )
  {
    /* Set status as MIPS_MATH_SIZE_MISMATCH */
    status = MIPS_MATH_SIZE_MISMATCH;
  }
  else

#endif /* #ifdef MIPS_MATH_MATRIX_CHECK */

  {
    /* Total number of samples in input matrix */
    numSamples = (uint32_t) pSrc->numRows * pSrc->numCols;

#if defined (MIPS_MATH_LOOPUNROLL)

    /* Loop unrolling: Compute 4 outputs at a time */
    blkCnt = numSamples >> 2U;

    while (blkCnt > 0U)
    {
      /* C(m,n) = A(m,n) * k */

      /* Scale, saturate and store result in destination buffer. */
      in = *pIn++;                                 /* read four inputs from source */
      in = ((q63) in * scaleFract) >> 32;        /* multiply input with scaler value */
      out = in << kShift;                          /* apply shifting */
      if (in != (out >> kShift))                   /* saturate the results. */
        out = 0x7FFFFFFF ^ (in >> 31);
      *pOut++ = out;                               /* Store result destination */

      in = *pIn++;
      in = ((q63) in * scaleFract) >> 32;
      out = in << kShift;
      if (in != (out >> kShift))
        out = 0x7FFFFFFF ^ (in >> 31);
      *pOut++ = out;

      in = *pIn++;
      in = ((q63) in * scaleFract) >> 32;
      out = in << kShift;
      if (in != (out >> kShift))
        out = 0x7FFFFFFF ^ (in >> 31);
      *pOut++ = out;

      in = *pIn++;
      in = ((q63) in * scaleFract) >> 32;
      out = in << kShift;
      if (in != (out >> kShift))
        out = 0x7FFFFFFF ^ (in >> 31);
      *pOut++ = out;

      /* Decrement loop counter */
      blkCnt--;
    }

    /* Loop unrolling: Compute remaining outputs */
    blkCnt = numSamples % 0x4U;

#else

    /* Initialize blkCnt with number of samples */
    blkCnt = numSamples;

#endif /* #if defined (MIPS_MATH_LOOPUNROLL) */

    while (blkCnt > 0U)
    {
      /* C(m,n) = A(m,n) * k */

      /* Scale, saturate and store result in destination buffer. */
      in = *pIn++;
      in = ((q63) in * scaleFract) >> 32;
      out = in << kShift;
      if (in != (out >> kShift))
        out = 0x7FFFFFFF ^ (in >> 31);
      *pOut++ = out;

      /* Decrement loop counter */
      blkCnt--;
    }

    /* Set status as MIPS_MATH_SUCCESS */
    status = MIPS_MATH_SUCCESS;
  }

  /* Return to application */
  return (status);
}
#endif /* defined(MIPS_MATH_DSP) */

/**
  @} end of MatrixScale group
 */
