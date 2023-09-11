/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_mat_mult_fast_q31.c
 * Description:  Q31 matrix multiplication (fast variant)
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
  @brief         Q31 matrix multiplication (fast variant).
  @param[in]     pSrcA      points to the first input matrix structure
  @param[in]     pSrcB      points to the second input matrix structure
  @param[out]    pDst       points to output matrix structure
  @return        execution status
                   - \ref MIPS_MATH_SUCCESS       : Operation successful
                   - \ref MIPS_MATH_SIZE_MISMATCH : Matrix size check failed

  @par           Scaling and Overflow Behavior
                   The difference between the function \ref mips_mat_mult_q31() and this fast variant is that
                   the fast variant use a 32-bit rather than a 64-bit accumulator.
                   The result of each 1.31 x 1.31 multiplication is truncated to
                   2.30 format. These intermediate results are accumulated in a 32-bit register in 2.30
                   format. Finally, the accumulator is saturated and converted to a 1.31 result.
  @par
                   The fast version has the same overflow behavior as the standard version but provides
                   less precision since it discards the low 32 bits of each multiplication result.
                   In order to avoid overflows completely the input signals must be scaled down.
                   Scale down one of the input matrices by log2(numColsA) bits to avoid overflows,
                   as a total of numColsA additions are computed internally for each output element.
  @remark
                   Refer to \ref mips_mat_mult_q31() for a slower implementation of this function
                   which uses 64-bit accumulation to provide higher precision.
 */

mips_status mips_mat_mult_fast_q31(
  const mips_matrix_instance_q31 * pSrcA,
  const mips_matrix_instance_q31 * pSrcB,
        mips_matrix_instance_q31 * pDst)
{
  q31 *pInA = pSrcA->pData;                    /* Input data matrix pointer A */
  q31 *pInB = pSrcB->pData;                    /* Input data matrix pointer B */
  q31 *pInA2;
  q31 *px;                                     /* Temporary output data matrix pointer */
  q31 *px2;
  q31 sum1, sum2, sum3, sum4;                  /* Accumulator */
  q31 inA1, inA2, inB1, inB2;
  uint16_t numRowsA = pSrcA->numRows;            /* Number of rows of input matrix A */
  uint16_t numColsB = pSrcB->numCols;            /* Number of columns of input matrix B */
  uint16_t numColsA = pSrcA->numCols;            /* Number of columns of input matrix A */
  uint32_t col, i = 0U, j, row = numRowsA, colCnt;  /* Loop counters */
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
    px = pDst->pData;

    row = row >> 1U;
    px2 = px + numColsB;

    /* The following loop performs the dot-product of each row in pSrcA with each column in pSrcB */
    /* row loop */
    while (row > 0U)
    {
      /* For every row wise process, column loop counter is to be initiated */
      col = numColsB;

      /* For every row wise process, pIn2 pointer is set to starting address of pSrcB data */
      pInB = pSrcB->pData;

      j = 0U;

      col = col >> 1U;

      /* column loop */
      while (col > 0U)
      {
        /* Set the variable sum, that acts as accumulator, to zero */
        sum1 = 0;
        sum2 = 0;
        sum3 = 0;
        sum4 = 0;
        
        /* Initiate data pointers */
        pInA = pSrcA->pData + i;
        pInB = pSrcB->pData + j;
        pInA2 = pInA + numColsA;
        
        colCnt = numColsA;

        /* matrix multiplication */
        while (colCnt > 0U)
        {
          /* c(m,n) = a(1,1) * b(1,1) + a(1,2) * b(2,1) + .... + a(m,p) * b(p,n) */

          inA1 = *pInA++;
          inB1 = pInB[0];
          inA2 = *pInA2++;
          inB2 = pInB[1];
          pInB += numColsB;


          sum1 = (q31) ((((q63) sum1 << 32) + ((q63) inA1 * inB1)) >> 32);
          sum2 = (q31) ((((q63) sum2 << 32) + ((q63) inA1 * inB2)) >> 32);
          sum3 = (q31) ((((q63) sum3 << 32) + ((q63) inA2 * inB1)) >> 32);
          sum4 = (q31) ((((q63) sum4 << 32) + ((q63) inA2 * inB2)) >> 32);

          /* Decrement loop counter */
          colCnt--;
        }

        /* Convert the result from 2.30 to 1.31 format and store in destination buffer */
        *px++  = sum1 << 1;
        *px++  = sum2 << 1;
        *px2++ = sum3 << 1;
        *px2++ = sum4 << 1;

        j += 2;

        /* Decrement column loop counter */
        col--;
      }

      i = i + (numColsA << 1U);
      px  = px2 + (numColsB & 1U);
      px2 = px  +  numColsB;

      /* Decrement row loop counter */
      row--;
    }

    /* Compute any remaining odd row/column below */

    /* Compute remaining output column */
    if (numColsB & 1U) {

      /* Avoid redundant computation of last element */
      row = numRowsA & (~1U);

      /* Point to remaining unfilled column in output matrix */
      px = pDst->pData + numColsB-1;
      pInA = pSrcA->pData;

      /* row loop */
      while (row > 0)
      {

        /* point to last column in matrix B */
        pInB  = pSrcB->pData + numColsB-1;

        /* Set variable sum1, that acts as accumulator, to zero */
        sum1  = 0;

#if defined (MIPS_MATH_LOOPUNROLL)

        /* Loop unrolling: Compute 4 columns at a time. */
        colCnt = numColsA >> 2U;

        /* matrix multiplication */
        while (colCnt > 0U)
        {

          sum1 = (q31) ((((q63) sum1 << 32) + ((q63) *pInA++ * *pInB)) >> 32);

          pInB += numColsB;


          sum1 = (q31) ((((q63) sum1 << 32) + ((q63) *pInA++ * *pInB)) >> 32);

          pInB += numColsB;


          sum1 = (q31) ((((q63) sum1 << 32) + ((q63) *pInA++ * *pInB)) >> 32);

          pInB += numColsB;


          sum1 = (q31) ((((q63) sum1 << 32) + ((q63) *pInA++ * *pInB)) >> 32);

          pInB += numColsB;

          /* Decrement loop counter */
          colCnt--;
        }

        /* Loop unrolling: Compute remaining column */
        colCnt = numColsA % 4U;

#else

        /* Initialize colCnt with number of columns */
        colCnt = numColsA;

#endif /* #if defined (MIPS_MATH_LOOPUNROLL) */

        while (colCnt > 0U) {

          sum1 = (q31) ((((q63) sum1 << 32) + ((q63) *pInA++ * *pInB)) >> 32);

          pInB += numColsB;
          
          colCnt--;
        }

        /* Convert the result from 2.30 to 1.31 format and store in destination buffer */
        *px = sum1 << 1;
        px += numColsB;

        /* Decrement row loop counter */
        row--;
      }
    }

    /* Compute remaining output row */
    if (numRowsA & 1U) {

      /* point to last row in output matrix */
      px = pDst->pData + (numColsB) * (numRowsA-1);

      col = numColsB;
      i = 0U;

      /* col loop */
      while (col > 0)
      {

        /* point to last row in matrix A */
        pInA = pSrcA->pData + (numRowsA-1) * numColsA;
        pInB  = pSrcB->pData + i;

        /* Set variable sum1, that acts as accumulator, to zero */
        sum1  = 0;

#if defined (MIPS_MATH_LOOPUNROLL)

        /* Loop unrolling: Compute 4 columns at a time. */
        colCnt = numColsA >> 2U;

        /* matrix multiplication */
        while (colCnt > 0U)
        {
          inA1 = *pInA++;
          inA2 = *pInA++;
          inB1 = *pInB;
          pInB += numColsB;
          inB2 = *pInB;
          pInB += numColsB;

          sum1 = (q31) ((((q63) sum1 << 32) + ((q63) inA1 * inB1)) >> 32);
          sum1 = (q31) ((((q63) sum1 << 32) + ((q63) inA2 * inB2)) >> 32);


          inA1 = *pInA++;
          inA2 = *pInA++;
          inB1 = *pInB;
          pInB += numColsB;
          inB2 = *pInB;
          pInB += numColsB;

          sum1 = (q31) ((((q63) sum1 << 32) + ((q63) inA1 * inB1)) >> 32);
          sum1 = (q31) ((((q63) sum1 << 32) + ((q63) inA2 * inB2)) >> 32);


          /* Decrement loop counter */
          colCnt--;
        }

        /* Loop unrolling: Compute remaining column */
        colCnt = numColsA % 4U;

#else

        /* Initialize colCnt with number of columns */
        colCnt = numColsA;

#endif /* #if defined (MIPS_MATH_LOOPUNROLL) */

        while (colCnt > 0U) {

          sum1 = (q31) ((((q63) sum1 << 32) + ((q63) *pInA++ * *pInB)) >> 32);
          
          pInB += numColsB;

          colCnt--;
        }

        /* Saturate and store the result in the destination buffer */
        *px++ = sum1 << 1;
        i++;

        /* Decrement col loop counter */
        col--;
      }
    }

    /* Set status as MIPS_MATH_SUCCESS */
    status = MIPS_MATH_SUCCESS;
  }

  /* Return to application */
  return (status);
}

/**
  @} end of MatrixMult group
 */