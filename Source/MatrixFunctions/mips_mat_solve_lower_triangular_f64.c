/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_mat_solve_lower_triangular_f64.c
 * Description:  Solve linear system LT X = A with LT lower triangular matrix
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
  @addtogroup MatrixInv
  @{
 */


   /**
   * @brief Solve LT . X = A where LT is a lower triangular matrix
   * @param[in]  lt  The lower triangular matrix
   * @param[in]  a  The matrix a
   * @param[out] dst The solution X of LT . X = A
   * @return The function returns MIPS_MATH_SINGULAR, if the system can't be solved.
   */

mips_status mips_mat_solve_lower_triangular_f64(
    const mips_matrix_instance_f64 * lt,
    const mips_matrix_instance_f64 * a,
    mips_matrix_instance_f64 * dst)
{
    mips_status status;                             /* status of matrix inverse */
    
    
#ifdef MIPS_MATH_MATRIX_CHECK
    
    /* Check for matrix mismatch condition */
    if ((lt->numRows != lt->numCols) ||
        (lt->numRows != a->numRows)   )
    {
        /* Set status as MIPS_MATH_SIZE_MISMATCH */
        status = MIPS_MATH_SIZE_MISMATCH;
    }
    else
        
#endif /* #ifdef MIPS_MATH_MATRIX_CHECK */
        
    {
        /* a1 b1 c1   x1 = a1
         b2 c2   x2   a2
         c3   x3   a3
         
         x3 = a3 / c3
         x2 = (a2 - c2 x3) / b2
         
         */
        int i,j,k,n,cols;
        
        f64 *pX = dst->pData;
        f64 *pLT = lt->pData;
        f64 *pA = a->pData;
        
        f64 *lt_row;
        f64 *a_col;
        
        n = dst->numRows;
        cols = dst->numCols;
        
        for(j=0; j < cols; j ++)
        {
            a_col = &pA[j];
            
            for(i=0; i < n ; i++)
            {
                f64 tmp=a_col[i * cols];
                
                lt_row = &pLT[n*i];
                
                for(k=0; k < i; k++)
                {
                    tmp -= lt_row[k] * pX[cols*k+j];
                }
                
                if (lt_row[i]==0.0)
                {
                    return(MIPS_MATH_SINGULAR);
                }
                tmp = tmp / lt_row[i];
                pX[i*cols+j] = tmp;
            }
            
        }
        status = MIPS_MATH_SUCCESS;
        
    }
    
    /* Return to application */
    return (status);
}
/**
  @} end of MatrixInv group
 */
