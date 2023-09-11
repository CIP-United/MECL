/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_mat_scale_f32.c
 * Description:  Multiplies a floating-point matrix by a scalar
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
  @defgroup MatrixScale Matrix Scale

  Multiplies a matrix by a scalar.  This is accomplished by multiplying each element in the
  matrix by the scalar.  For example:

  @par Matrix Scaling of a 3 x 3 matrix 

  \f[
  \begin{pmatrix}
  a_{1,1} & a_{1,2} & a_{1,3} \\
  a_{2,1} & a_{2,2} & a_{2,3} \\
  a_{3,1} & a_{3,2} & a_{3,3} \\
  \end{pmatrix}
  * K = 
  \begin{pmatrix}
   K a_{1,1} & K a_{1,2} & K a_{1,3} \\
   K a_{2,1} & K a_{2,2} & K a_{2,3} \\
   K a_{3,1} & K a_{3,2} & K a_{3,3} \\
  \end{pmatrix}
  \f]

  The function checks to make sure that the input and output matrices are of the same size.

  In the fixed-point Q15 and Q31 functions, <code>scale</code> is represented by
  a fractional multiplication <code>scaleFract</code> and an arithmetic shift <code>shift</code>.
  The shift allows the gain of the scaling operation to exceed 1.0.
  The overall scale factor applied to the fixed-point data is
  <pre>
      scale = scaleFract * 2^shift.
  </pre>
 */

/**
  @addtogroup MatrixScale
  @{
 */

/**
  @brief         Floating-point matrix scaling.
  @param[in]     pSrc       points to input matrix
  @param[in]     scale      scale factor to be applied
  @param[out]    pDst       points to output matrix structure
  @return        execution status
                   - \ref MIPS_MATH_SUCCESS       : Operation successful
                   - \ref MIPS_MATH_SIZE_MISMATCH : Matrix size check failed
 */

mips_status mips_mat_scale_f32(
  const mips_matrix_instance_f32 * pSrc,
        f32                 scale,
        mips_matrix_instance_f32 * pDst)
{
  f32 *pIn = pSrc->pData;                  /* Input data matrix pointer */
  f32 *pOut = pDst->pData;                 /* Output data matrix pointer */
  uint32_t numSamples;                           /* Total number of elements in the matrix */
  uint32_t blkCnt;                               /* Loop counters */
  mips_status status;                             /* Status of matrix scaling */

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
      /* C(m,n) = A(m,n) * scale */

      /* Scale and store result in destination buffer. */
      *pOut++ = (*pIn++) * scale;
      *pOut++ = (*pIn++) * scale;
      *pOut++ = (*pIn++) * scale;
      *pOut++ = (*pIn++) * scale;

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
      /* C(m,n) = A(m,n) * scale */

      /* Scale and store result in destination buffer. */
      *pOut++ = (*pIn++) * scale;

      /* Decrement loop counter */
      blkCnt--;
    }

    /* Set status as MIPS_MATH_SUCCESS */
    status = MIPS_MATH_SUCCESS;
  }

  /* Return to application */
  return (status);
}

/**
  @} end of MatrixScale group
 */
