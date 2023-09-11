/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_mat_mult_f32.c
 * Description:  Floating-point matrix multiplication
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
 * @ingroup groupMatrix
 */

/**
 * @defgroup MatrixMult Matrix Multiplication
 *
 * Multiplies two matrices.
 *
 * @par Multiplication of two 3x3 matrices:
 * 
 * \f[
 * \begin{pmatrix}
 *  a_{1,1} & a_{1,2} & a_{1,3} \\
 *  a_{2,1} & a_{2,2} & a_{2,3} \\
 *  a_{3,1} & a_{3,2} & a_{3,3} \\
 * \end{pmatrix}
 * 
 * \begin{pmatrix}
 *  b_{1,1} & b_{1,2} & b_{1,3} \\
 *  b_{2,1} & b_{2,2} & b_{2,3} \\
 *  b_{3,1} & b_{3,2} & b_{3,3} \\
 * \end{pmatrix}
 * =
 * \begin{pmatrix}
 *  a_{1,1} b_{1,1}+a_{1,2} b_{2,1}+a_{1,3} b_{3,1} & a_{1,1} b_{1,2}+a_{1,2} b_{2,2}+a_{1,3} b_{3,2} & a_{1,1} b_{1,3}+a_{1,2} b_{2,3}+a_{1,3} b_{3,3} \\
 *  a_{2,1} b_{1,1}+a_{2,2} b_{2,1}+a_{2,3} b_{3,1} & a_{2,1} b_{1,2}+a_{2,2} b_{2,2}+a_{2,3} b_{3,2} & a_{2,1} b_{1,3}+a_{2,2} b_{2,3}+a_{2,3} b_{3,3} \\
 *  a_{3,1} b_{1,1}+a_{3,2} b_{2,1}+a_{3,3} b_{3,1} & a_{3,1} b_{1,2}+a_{3,2} b_{2,2}+a_{3,3} b_{3,2} & a_{3,1} b_{1,3}+a_{3,2} b_{2,3}+a_{3,3} b_{3,3} \\
 * \end{pmatrix}
 * \f]

 * Matrix multiplication is only defined if the number of columns of the
 * first matrix equals the number of rows of the second matrix.
 * Multiplying an <code>M x N</code> matrix with an <code>N x P</code> matrix results
 * in an <code>M x P</code> matrix.
 * When matrix size checking is enabled, the functions check: (1) that the inner dimensions of
 * <code>pSrcA</code> and <code>pSrcB</code> are equal; and (2) that the size of the output
 * matrix equals the outer dimensions of <code>pSrcA</code> and <code>pSrcB</code>.
 */


/**
 * @addtogroup MatrixMult
 * @{
 */



/**
 * @brief Floating-point matrix multiplication.
 * @param[in]       *pSrcA points to the first input matrix structure
 * @param[in]       *pSrcB points to the second input matrix structure
 * @param[out]      *pDst points to output matrix structure
 * @return          The function returns either
 * <code>MIPS_MATH_SIZE_MISMATCH</code> or <code>MIPS_MATH_SUCCESS</code> based on the outcome of size checking.
 */
mips_status mips_mat_mult_f32(
  const mips_matrix_instance_f32 * pSrcA,
  const mips_matrix_instance_f32 * pSrcB,
        mips_matrix_instance_f32 * pDst)
{
  f32 *pIn1 = pSrcA->pData;                /* Input data matrix pointer A */
  f32 *pIn2 = pSrcB->pData;                /* Input data matrix pointer B */
  f32 *pInA = pSrcA->pData;                /* Input data matrix pointer A */
  f32 *pInB = pSrcB->pData;                /* Input data matrix pointer B */
  f32 *pOut = pDst->pData;                 /* Output data matrix pointer */
  f32 *px;                                 /* Temporary output data matrix pointer */
  f32 sum;                                 /* Accumulator */
  uint16_t numRowsA = pSrcA->numRows;            /* Number of rows of input matrix A */
  uint16_t numColsB = pSrcB->numCols;            /* Number of columns of input matrix B */
  uint16_t numColsA = pSrcA->numCols;            /* Number of columns of input matrix A */
  uint32_t col, i = 0U, row = numRowsA, colCnt;  /* Loop counters */
  mips_status status;                             /* Status of matrix multiplication */

#ifdef MIPS_MATH_MATRIX_CHECK

  /* Check for matrix mismatch condition */
  if ((pSrcA->numCols != pSrcB->numRows) ||
      (pSrcA->numRows != pDst->numRows)  ||
      (pSrcB->numCols != pDst->numCols)    )
  {
    /* Set status as MIPS_MATH_SIZE_MISMATCH */
    status = MIPS_MATH_SIZE_MISMATCH;
  }
  else

#endif /* #ifdef MIPS_MATH_MATRIX_CHECK */

  {
    /* The following loop performs the dot-product of each row in pSrcA with each column in pSrcB */
    /* row loop */
    do
    {
      /* Output pointer is set to starting address of row being processed */
      px = pOut + i;

      /* For every row wise process, column loop counter is to be initiated */
      col = numColsB;

      /* For every row wise process, pIn2 pointer is set to starting address of pSrcB data */
      pIn2 = pSrcB->pData;

      /* column loop */
      do
      {
        /* Set the variable sum, that acts as accumulator, to zero */
        sum = 0.0f;

        /* Initialize pointer pIn1 to point to starting address of column being processed */
        pIn1 = pInA;

#if defined (MIPS_MATH_LOOPUNROLL)

        /* Loop unrolling: Compute 4 MACs at a time. */
        colCnt = numColsA >> 2U;

        /* matrix multiplication */
        while (colCnt > 0U)
        {
          /* c(m,p) = a(m,1) * b(1,p) + a(m,2) * b(2,p) + .... + a(m,n) * b(n,p) */

          /* Perform the multiply-accumulates */
          sum += *pIn1++ * *pIn2;
          pIn2 += numColsB;

          sum += *pIn1++ * *pIn2;
          pIn2 += numColsB;

          sum += *pIn1++ * *pIn2;
          pIn2 += numColsB;

          sum += *pIn1++ * *pIn2;
          pIn2 += numColsB;

          /* Decrement loop counter */
          colCnt--;
        }

        /* Loop unrolling: Compute remaining MACs */
        colCnt = numColsA % 0x4U;

#else

        /* Initialize cntCnt with number of columns */
        colCnt = numColsA;

#endif /* #if defined (MIPS_MATH_LOOPUNROLL) */

        while (colCnt > 0U)
        {
          /* c(m,p) = a(m,1) * b(1,p) + a(m,2) * b(2,p) + .... + a(m,n) * b(n,p) */

          /* Perform the multiply-accumulates */
          sum += *pIn1++ * *pIn2;
          pIn2 += numColsB;

          /* Decrement loop counter */
          colCnt--;
        }

        /* Store result in destination buffer */
        *px++ = sum;

        /* Decrement column loop counter */
        col--;

        /* Update pointer pIn2 to point to starting address of next column */
        pIn2 = pInB + (numColsB - col);

      } while (col > 0U);

      /* Update pointer pInA to point to starting address of next row */
      i = i + numColsB;
      pInA = pInA + numColsA;

      /* Decrement row loop counter */
      row--;

    } while (row > 0U);

    /* Set status as MIPS_MATH_SUCCESS */
    status = MIPS_MATH_SUCCESS;
  }

  /* Return to application */
  return (status);
}

/**
 * @} end of MatrixMult group
 */