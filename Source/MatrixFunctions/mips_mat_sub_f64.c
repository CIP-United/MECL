/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_mat_sub_f64.c
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

mips_status mips_mat_sub_f64(
  const mips_matrix_instance_f64 * pSrcA,
  const mips_matrix_instance_f64 * pSrcB,
        mips_matrix_instance_f64 * pDst)
{
  f64 *pInA = pSrcA->pData;                /* input data matrix pointer A */
  f64 *pInB = pSrcB->pData;                /* input data matrix pointer B */
  f64 *pOut = pDst->pData;                 /* output data matrix pointer */

  uint64_t numSamples;                           /* total number of elements in the matrix */
  uint64_t blkCnt;                               /* loop counters */
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
    numSamples = (uint64_t) pSrcA->numRows * pSrcA->numCols;

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