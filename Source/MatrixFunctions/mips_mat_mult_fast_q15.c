/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_mat_mult_fast_q15.c
 * Description:  Q15 matrix multiplication (fast variant)
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
  @addtogroup MatrixMult
  @{
 */

/**
  @brief         Q15 matrix multiplication (fast variant).
  @param[in]     pSrcA      points to the first input matrix structure
  @param[in]     pSrcB      points to the second input matrix structure
  @param[out]    pDst       points to output matrix structure
  @param[in]     pState     points to the array for storing intermediate results
  @return        execution status
                   - \ref MIPS_MATH_SUCCESS       : Operation successful
                   - \ref MIPS_MATH_SIZE_MISMATCH : Matrix size check failed

  @par           Scaling and Overflow Behavior
                   The difference between the function \ref mips_mat_mult_q15() and this fast variant is that
                   the fast variant use a 32-bit rather than a 64-bit accumulator.
                   The result of each 1.15 x 1.15 multiplication is truncated to
                   2.30 format. These intermediate results are accumulated in a 32-bit register in 2.30
                   format. Finally, the accumulator is saturated and converted to a 1.15 result.
  @par
                   The fast version has the same overflow behavior as the standard version but provides
                   less precision since it discards the low 16 bits of each multiplication result.
                   In order to avoid overflows completely the input signals must be scaled down.
                   Scale down one of the input matrices by log2(numColsA) bits to avoid overflows,
                   as a total of numColsA additions are computed internally for each output element.
  @remark
                   Refer to \ref mips_mat_mult_q15() for a slower implementation of this function
                   which uses 64-bit accumulation to provide higher precision.
 */

mips_status mips_mat_mult_fast_q15(
  const mips_matrix_instance_q15 * pSrcA,
  const mips_matrix_instance_q15 * pSrcB,
        mips_matrix_instance_q15 * pDst,
        q15                   * pState)
{
        q31 sum;                                     /* Accumulator */
        q15 *pSrcBT = pState;                        /* Input data matrix pointer for transpose */
        q15 *pInA = pSrcA->pData;                    /* Input data matrix pointer A of Q15 type */
        q15 *pInB = pSrcB->pData;                    /* Input data matrix pointer B of Q15 type */
        q15 *px;                                     /* Temporary output data matrix pointer */
        uint16_t numRowsA = pSrcA->numRows;            /* Number of rows of input matrix A */
        uint16_t numColsB = pSrcB->numCols;            /* Number of columns of input matrix B */
        uint16_t numColsA = pSrcA->numCols;            /* Number of columns of input matrix A */
        uint16_t numRowsB = pSrcB->numRows;            /* Number of rows of input matrix B */
        uint32_t col, i = 0U, row = numRowsB, colCnt;  /* Loop counters */
        mips_status status;                             /* Status of matrix multiplication */


        q15 in;                                      /* Temporary variable to hold the input value */
        q15 inA1, inB1, inA2, inB2;

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
    /* Matrix transpose */
    do
    {
      /* The pointer px is set to starting address of column being processed */
      px = pSrcBT + i;

      /* Apply loop unrolling and exchange columns with row elements */
      col = numColsB >> 2U;

      /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.
       ** a second loop below computes the remaining 1 to 3 samples. */
      while (col > 0U)
      {



        /* Read one element from row */
        in = *pInB++;

        /* Store one element in destination */
        *px = in;

        /* Update pointer px to point to next row of transposed matrix */
        px += numRowsB;

        in = *pInB++;
        *px = in;
        px += numRowsB;

        in = *pInB++;
        *px = in;
        px += numRowsB;

        in = *pInB++;
        *px = in;
        px += numRowsB;


        /* Decrement column loop counter */
        col--;
      }

      /* If the columns of pSrcB is not a multiple of 4, compute any remaining output samples here.
       ** No loop unrolling is used. */
      col = numColsB % 0x4U;

      while (col > 0U)
      {
        /* Read and store input element in destination */
        *px = *pInB++;

        /* Update pointer px to point to next row of transposed matrix */
        px += numRowsB;

        /* Decrement column loop counter */
        col--;
      }

      i++;

      /* Decrement row loop counter */
      row--;

    } while (row > 0U);

    /* Reset variables for usage in following multiplication process */
    row = numRowsA;
    i = 0U;
    px = pDst->pData;


    /* The following loop performs the dot-product of each row in pSrcA with each column in pSrcB */
    /* row loop */
    while (row > 0U)
    {
      /* For every row wise process, column loop counter is to be initiated */
      col = numColsB;

      /* For every row wise process, pIn2 pointer is set to starting address of transposed pSrcB data */
      pInB = pSrcBT;

      /* column loop */
      while (col > 0U)
      {
        /* Set variable sum, that acts as accumulator, to zero */
        sum = 0;

        /* Initiate pointer pInA to point to starting address of column being processed */
        pInA = pSrcA->pData + i;


        colCnt = numColsA >> 2U;

        /* matrix multiplication */
        while (colCnt > 0U)
        {
          /* c(m,n) = a(1,1) * b(1,1) + a(1,2) * b(2,1) + .... + a(m,p) * b(p,n) */


          /* read real and imag values from pSrcA and pSrcB buffer */
          inA1 = *pInA++;
          inB1 = *pInB++;
          /* Multiply and Accumulates */
          sum += inA1 * inB1;

          inA2 = *pInA++;
          inB2 = *pInB++;
          sum += inA2 * inB2;

          inA1 = *pInA++;
          inB1 = *pInB++;
          sum += inA1 * inB1;

          inA2 = *pInA++;
          inB2 = *pInB++;
          sum += inA2 * inB2;

          /* Decrement loop counter */
          colCnt--;
        }

        /* process odd column samples */

        colCnt = numColsA % 0x4U;

        while (colCnt > 0U)
        {
          /* c(m,n) = a(1,1) * b(1,1) + a(1,2) * b(2,1) + .... + a(m,p) * b(p,n) */
          sum += (q31) *pInA++ * *pInB++;

          /* Decrement loop counter */
          colCnt--;
        }

        /* Saturate and store result in destination buffer */
        *px++  = (q15) (sum >> 15);



        /* Decrement column loop counter */
        col--;

      }

      i = i + numColsA;



      /* Decrement row loop counter */
      row--;

    }

    /* Compute any remaining odd row/column below */


    /* Set status as MIPS_MATH_SUCCESS */
    status = MIPS_MATH_SUCCESS;
  }

  /* Return to application */
  return (status);
}

/**
  @} end of MatrixMult group
 */
