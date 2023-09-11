/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_mat_cmplx_trans_q31.c
 * Description:  Q15 complex matrix transpose
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
  @addtogroup MatrixComplexTrans
  @{
 */

/**
  @brief         Q15 complex matrix transpose.
  @param[in]     pSrc      points to input matrix
  @param[out]    pDst      points to output matrix
  @return        execution status
                   - \ref MIPS_MATH_SUCCESS       : Operation successful
                   - \ref MIPS_MATH_SIZE_MISMATCH : Matrix size check failed
 */
mips_status mips_mat_cmplx_trans_q15(
  const mips_matrix_instance_q15 * pSrc,
  mips_matrix_instance_q15 * pDst)
{
  q15 *pSrcA = pSrc->pData;                    /* input data matrix pointer */
  q15 *pOut = pDst->pData;                     /* output data matrix pointer */
  uint16_t nRows = pSrc->numRows;                /* number of nRows */
  uint16_t nColumns = pSrc->numCols;             /* number of nColumns */
  uint16_t col, row = nRows, i = 0U;             /* row and column loop counters */
  mips_status status;                             /* status of matrix transpose */


#ifdef MIPS_MATH_MATRIX_CHECK

  /* Check for matrix mismatch condition */
  if ((pSrc->numRows != pDst->numCols) || (pSrc->numCols != pDst->numRows))
  {
    /* Set status as MIPS_MATH_SIZE_MISMATCH */
    status = MIPS_MATH_SIZE_MISMATCH;
  }
  else
#endif /*    #ifdef MIPS_MATH_MATRIX_CHECK    */

  {
    /* Matrix transpose by exchanging the rows with columns */
    /* row loop     */
    do
    {
      /* The pointer pOut is set to starting address of the column being processed */
      pOut = pDst->pData + CMPLX_DIM * i;

      /* Initialize column loop counter */
      col = nColumns;

      while (col > 0U)
      {
        /* Read and store the input element in the destination */
        pOut[0] = *pSrcA++; //real
        pOut[1] = *pSrcA++; //imag

        /* Update the pointer pOut to point to the next row of the transposed matrix */
        pOut += CMPLX_DIM *nRows;

        /* Decrement the column loop counter */
        col--;
      }

      i++;

      /* Decrement the row loop counter */
      row--;

    } while (row > 0U);

    /* set status as MIPS_MATH_SUCCESS */
    status = MIPS_MATH_SUCCESS;
  }
  /* Return to application */
  return (status);
}

/**
 * @} end of MatrixTrans group
 */
