/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_mat_ldl_f32.c
 * Description:  Floating-point LDL decomposition
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
#include "dsp/matrix_utils.h"





/**
  @ingroup groupMatrix
 */

/**
  @addtogroup MatrixChol
  @{
 */

/**
   * @brief Floating-point LDL^t decomposition of positive semi-definite matrix.
   * @param[in]  pSrc   points to the instance of the input floating-point matrix structure.
   * @param[out] pl   points to the instance of the output floating-point triangular matrix structure.
   * @param[out] pd   points to the instance of the output floating-point diagonal matrix structure.
   * @param[out] pp   points to the instance of the output floating-point permutation vector.
   * @return The function returns MIPS_MATH_SIZE_MISMATCH, if the dimensions do not match.
   * @return        execution status
                   - \ref MIPS_MATH_SUCCESS       : Operation successful
                   - \ref MIPS_MATH_SIZE_MISMATCH : Matrix size check failed
                   - \ref MIPS_MATH_DECOMPOSITION_FAILURE      : Input matrix cannot be decomposed
   * @par
   *  Computes the LDL^t decomposition of a matrix A such that P A P^t = L D L^t.
   */
mips_status mips_mat_ldlt_f32(
  const mips_matrix_instance_f32 * pSrc,
  mips_matrix_instance_f32 * pl,
  mips_matrix_instance_f32 * pd,
  uint16_t * pp)
{

  mips_status status;                             /* status of matrix inverse */


#ifdef MIPS_MATH_MATRIX_CHECK

  /* Check for matrix mismatch condition */
  if ((pSrc->numRows != pSrc->numCols) ||
      (pl->numRows != pl->numCols) ||
      (pd->numRows != pd->numCols) ||
      (pl->numRows != pd->numRows)   )
  {
    /* Set status as MIPS_MATH_SIZE_MISMATCH */
    status = MIPS_MATH_SIZE_MISMATCH;
  }
  else

#endif /* #ifdef MIPS_MATH_MATRIX_CHECK */

  {

    const int n=pSrc->numRows;
    int fullRank = 1, diag,k;
    f32 *pA;
    int row,d;

    memset(pd->pData,0,sizeof(f32)*n*n);
    memcpy(pl->pData,pSrc->pData,n*n*sizeof(f32));
    pA = pl->pData;

    for(k=0;k < n; k++)
    {
      pp[k] = k;
    }


    for(k=0;k < n; k++)
    {
        /* Find pivot */
        f32 m=F32_MIN,a;
        int j=k;


        int r;
        int w;

        for(r=k;r<n;r++)
        {
           if (pA[r*n+r] > m)
           {
             m = pA[r*n+r];
             j = r;
           }
        }

        if(j != k)
        {
          SWAP_ROWS_F32(pl,0,k,j);
          SWAP_COLS_F32(pl,0,k,j);
        }


        pp[k] = j;

        a = pA[k*n+k];

        if (fabsf(a) < 1.0e-8f)
        {

            fullRank = 0;
            break;
        }

        for(w=k+1;w<n;w++)
        {
          int x;
          for(x=k+1;x<n;x++)
          {
             pA[w*n+x] = pA[w*n+x] - pA[w*n+k] * pA[x*n+k] / a;
          }
        }

        for(w=k+1;w<n;w++)
        {
               pA[w*n+k] = pA[w*n+k] / a;
        }



    }



    diag=k;
    if (!fullRank)
    {
      diag--;
      for(row=0; row < n;row++)
      {
        int col;
        for(col=k; col < n;col++)
        {
           pl->pData[row*n+col]=0.0;
        }
      }
    }

    for(row=0; row < n;row++)
    {
       int col;
       for(col=row+1; col < n;col++)
       {
         pl->pData[row*n+col] = 0.0;
       }
    }

    for(d=0; d < diag;d++)
    {
      pd->pData[d*n+d] = pl->pData[d*n+d];
      pl->pData[d*n+d] = 1.0;
    }

    status = MIPS_MATH_SUCCESS;

  }


  /* Return to application */
  return (status);
}

/**
  @} end of MatrixChol group
 */