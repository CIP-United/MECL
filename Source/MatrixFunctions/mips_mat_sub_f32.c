/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_mat_sub_f32.c
 * Description:  Floating-point matrix subtraction
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
  @defgroup MatrixSub Matrix Subtraction

  Subtract two matrices.
  @par Subraction of two 3 x 3 matrices
  
  \f[
  \begin{pmatrix}
   a_{1,1} & a_{1,2} & a_{1,3} \\
   a_{2,1} & a_{2,2} & a_{2,3} \\
   a_{3,1} & a_{3,2} & a_{3,3} \\
  \end{pmatrix}
  -
  \begin{pmatrix}
   b_{1,1} & b_{1,2} & b_{1,3} \\
   b_{2,1} & b_{2,2} & b_{2,3} \\
   b_{3,1} & b_{3,2} & b_{3,3} \\
  \end{pmatrix}
  =
  \begin{pmatrix}
   a_{1,1}-b_{1,1} & a_{1,2}-b_{1,2} & a_{1,3}-b_{1,3} \\
   a_{2,1}-b_{2,1} & a_{2,2}-b_{2,2} & a_{2,3}-b_{2,3} \\
   a_{3,1}-b_{3,1} & a_{3,2}-b_{3,2} & a_{3,3}-b_{3,3} \\
  \end{pmatrix}
  \f]
  The functions check to make sure that
  <code>pSrcA</code>, <code>pSrcB</code>, and <code>pDst</code> have the same
  number of rows and columns.
 */

/**
  @addtogroup MatrixSub
  @{
 */

/**
  @brief         Floating-point matrix subtraction.
  @param[in]     pSrcA      points to the first input matrix structure
  @param[in]     pSrcB      points to the second input matrix structure
  @param[out]    pDst       points to output matrix structure
  @return        execution status
                   - \ref MIPS_MATH_SUCCESS       : Operation successful
                   - \ref MIPS_MATH_SIZE_MISMATCH : Matrix size check failed
 */
mips_status mips_mat_sub_f32(
  const mips_matrix_instance_f32 * pSrcA,
  const mips_matrix_instance_f32 * pSrcB,
        mips_matrix_instance_f32 * pDst)
{
  f32 *pInA = pSrcA->pData;                /* input data matrix pointer A */
  f32 *pInB = pSrcB->pData;                /* input data matrix pointer B */
  f32 *pOut = pDst->pData;                 /* output data matrix pointer */

  uint32_t numSamples;                           /* total number of elements in the matrix */
  uint32_t blkCnt;                               /* loop counters */
  mips_status status;                             /* status of matrix subtraction */

#ifdef MIPS_MATH_MATRIX_CHECK

  /* Check for matrix mismatch condition */
  if ((pSrcA->numRows != pSrcB->numRows) ||
      (pSrcA->numCols != pSrcB->numCols) ||
      (pSrcA->numRows != pDst->numRows)  ||
      (pSrcA->numCols != pDst->numCols)    )
  {
    /* Set status as MIPS_MATH_SIZE_MISMATCH */
    status = MIPS_MATH_SIZE_MISMATCH;
  }
  else

#endif /* #ifdef MIPS_MATH_MATRIX_CHECK */

  {
    /* Total number of samples in input matrix */
    numSamples = (uint32_t) pSrcA->numRows * pSrcA->numCols;

#if defined (MIPS_MATH_LOOPUNROLL)

    /* Loop unrolling: Compute 4 outputs at a time */
    blkCnt = numSamples >> 2U;

    while (blkCnt > 0U)
    {
      /* C(m,n) = A(m,n) - B(m,n) */

      /* Subtract and store result in destination buffer. */
      *pOut++ = (*pInA++) - (*pInB++);
      *pOut++ = (*pInA++) - (*pInB++);
      *pOut++ = (*pInA++) - (*pInB++);
      *pOut++ = (*pInA++) - (*pInB++);

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
      /* C(m,n) = A(m,n) - B(m,n) */

      /* Subtract and store result in destination buffer. */
      *pOut++ = (*pInA++) - (*pInB++);

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
  @} end of MatrixSub group
 */
