/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_mat_init_f32.c
 * Description:  Floating-point matrix initialization
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
  @defgroup MatrixInit Matrix Initialization
 
  Initializes the underlying matrix data structure.
  The functions set the <code>numRows</code>,
  <code>numCols</code>, and <code>pData</code> fields
  of the matrix data structure.
 */

/**
  @addtogroup MatrixInit
  @{
 */

/**
  @brief         Floating-point matrix initialization.
  @param[in,out] S         points to an instance of the floating-point matrix structure
  @param[in]     nRows     number of rows in the matrix
  @param[in]     nColumns  number of columns in the matrix
  @param[in]     pData     points to the matrix data array
  @return        none
 */

void mips_mat_init_f32(
  mips_matrix_instance_f32 * S,
  uint16_t nRows,
  uint16_t nColumns,
  f32 * pData)
{
  /* Assign Number of Rows */
  S->numRows = nRows;

  /* Assign Number of Columns */
  S->numCols = nColumns;

  /* Assign Data pointer */
  S->pData = pData;
}

/**
  @} end of MatrixInit group
 */
