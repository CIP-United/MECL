/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_mat_qr_f32.c
 * Description:  Floating-point matrix QR decomposition.
 *
 * $Date:        31 Augest 2023
 * $Revision:    V1.0.0
 *
 * -------------------------------------------------------------------- */
/*
 * Copyright (C) 2010-2022 ARM Limited or its affiliates. All rights reserved.
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
  @defgroup MatrixQR QR decomposition of a Matrix

    Computes the QR decomposition of a matrix M using Householder algorithm.

    \f[
        M = Q R
    \f]

    where Q is an orthogonal matrix and R is upper triangular.
    No pivoting strategy is used.

    The returned value for R is using a format a bit similar
    to LAPACK : it is not just containing the matrix R but
    also the Householder reflectors. 

    The function is also returning a vector \f$\tau\f$
    that is containing the scaling factor for the reflectors.

    Returned value R has the structure:

    \f[
    \begin{pmatrix}
    r_{11} & r_{12}     & \dots  & r_{1n} \\
    v_{12} & r_{22}     & \dots  & r_{2n} \\
    v_{13} & v_{22}     & \dots  & r_{3n} \\
    \vdots & \vdots     & \ddots & \vdots   \\
    v_{1m} & v_{2(m-1)} & \dots  & r_{mn} \\
    \end{pmatrix}
    \f]

    where 

    \f[
    v_1 = 
    \begin{pmatrix}
    1       \\
    v_{12}  \\
    \vdots  \\
    v_{1m}  \\
    \end{pmatrix}
    \f]

    is the first householder reflector.
    
    The Householder Matrix is given by \f$H_1\f$

    \f[
    H_1 = I - \tau_1 v_1 v_1^T
    \f]

    The Matrix Q is the product of the Householder matrices:
    
    \f[
    Q = H_1 H_2 \dots H_n
    \f]

    The computation of the matrix Q by this function is
    optional.

    And the matrix R, would be the returned value R without the
    householder reflectors:

    \f[
    \begin{pmatrix}
    r_{11} & r_{12} & \dots  & r_{1n} \\
    0      & r_{22} & \dots  & r_{2n} \\
    0      & 0      & \dots  & r_{3n} \\
    \vdots & \vdots & \ddots & \vdots   \\
    0      & 0      & \dots  & r_{mn} \\
    \end{pmatrix}
    \f]


 */

/**
  @addtogroup MatrixQR
  @{
 */

/**
  @brief     
  @brief         QR decomposition of a m x n floating point matrix with m >= n.
  @param[in]     pSrc      points to input matrix structure. The source matrix is modified by the function.
  @param[in]     threshold norm2 threshold.    
  @param[out]    pOutR     points to output R matrix structure of dimension m x n
  @param[out]    pOutQ     points to output Q matrix structure of dimension m x m (can be NULL)
  @param[out]    pOutTau   points to Householder scaling factors of dimension n
  @param[inout]  pTmpA     points to a temporary vector of dimension m.
  @param[inout]  pTmpB     points to a temporary vector of dimension m.
  @return        execution status
                   - \ref MIPS_MATH_SUCCESS       : Operation successful
                   - \ref MIPS_MATH_SIZE_MISMATCH : Matrix size check failed
  
  @par           pOutQ is optional:
                 pOutQ can be a NULL pointer.
                 In this case, the argument will be ignored
                 and the output Q matrix won't be computed.


  @par           Norm2 threshold 
                 For the meaning of this argument please 
                 refer to the \ref MatrixHouseholder documentation

 */




mips_status mips_mat_qr_f32(
    const mips_matrix_instance_f32 * pSrc,
    const f32 threshold,
    mips_matrix_instance_f32 * pOutR,
    mips_matrix_instance_f32 * pOutQ,
    f32 * pOutTau,
    f32 *pTmpA,
    f32 *pTmpB
    )

{
  int32_t col=0;
  int32_t nb,pos;
  f32 *pa,*pc;
  f32 beta;
  f32 *pv;
  f32 *pdst;
  f32 *p;

  if (pSrc->numRows < pSrc->numCols)
  {
    return(MIPS_MATH_SIZE_MISMATCH);
  }

  memcpy(pOutR->pData,pSrc->pData,pSrc->numCols * pSrc->numRows*sizeof(f32));
  pOutR->numCols = pSrc->numCols;
  pOutR->numRows = pSrc->numRows;
  
  p = pOutR->pData;
  
  pc = pOutTau;
  for(col=0 ; col < pSrc->numCols; col++)
  {
      int32_t i,j,k,blkCnt;
      f32 *pa0,*pa1,*pa2,*pa3;
      COPY_COL_F32(pOutR,col,col,pTmpA);

      beta = mips_householder_f32(pTmpA,threshold,pSrc->numRows - col,pTmpA);
      *pc++ = beta;
    
      pdst = pTmpB;

      /* v.T A(col:,col:) -> tmpb */
      pv = pTmpA;
      pa = p;
      for(j=0;j<pSrc->numCols-col; j++)
      {
              *pdst++ = *pv * *pa++; 
      }
      pa += col;
      pv++;
      pdst = pTmpB;

      pa0 = pa;
      pa1 = pa0 + pSrc->numCols;
      pa2 = pa1 + pSrc->numCols;
      pa3 = pa2 + pSrc->numCols;

      /* Unrolled loop */
      blkCnt = (pSrc->numRows-col - 1) >> 2;
      k=1;
      while(blkCnt > 0)
      {
          f32 sum;

          for(j=0;j<pSrc->numCols-col; j++)
          {
              sum = *pdst;

              sum += pv[0] * *pa0++;
              sum += pv[1] * *pa1++;
              sum += pv[2] * *pa2++;
              sum += pv[3] * *pa3++;
              
              *pdst++ = sum; 
          }
          pa0 += col + 3*pSrc->numCols;
          pa1 += col + 3*pSrc->numCols;
          pa2 += col + 3*pSrc->numCols;
          pa3 += col + 3*pSrc->numCols;
          pv  += 4;
          pdst = pTmpB;
          k += 4;
          blkCnt--;
      }

      pa = pa0;
      for(;k<pSrc->numRows-col; k++)
      {
          for(j=0;j<pSrc->numCols-col; j++)
          {
              *pdst++ += *pv * *pa++; 
          }
          pa += col;
          pv++;
          pdst = pTmpB;
      }

      /* A(col:,col:) - beta v tmpb */
      pa = p;
      for(j=0;j<pSrc->numRows-col; j++)
      {
        f32 f = beta * pTmpA[j];

        for(i=0;i<pSrc->numCols-col; i++)
        {
          *pa = *pa - f * pTmpB[i] ;
          pa++;
        }
        pa += col;
      } 

      /* Copy Householder reflectors into R matrix */
      pa = p + pOutR->numCols;
      for(k=0;k<pSrc->numRows-col-1; k++)
      {
         *pa = pTmpA[k+1];
         pa += pOutR->numCols;
      }

      p += 1 + pOutR->numCols;
  }

  /* Generate Q if requested by user matrix */

  if (pOutQ != NULL)
  {
     /* Initialize Q matrix to identity */
     memset(pOutQ->pData,0,sizeof(f32)*pOutQ->numRows*pOutQ->numRows);
     
     pa = pOutQ->pData;
     for(col=0 ; col < pOutQ->numCols; col++)
     {
        *pa = 1.0f;
        pa += pOutQ->numCols+1;
     }
   
     nb = pOutQ->numRows - pOutQ->numCols + 1;
   
     pc = pOutTau + pOutQ->numCols - 1;
     for(col=0 ; col < pOutQ->numCols; col++)
     {
       int32_t i,j,k, blkCnt;
       f32 *pa0,*pa1,*pa2,*pa3;
       pos = pSrc->numRows - nb;
       p = pOutQ->pData + pos + pOutQ->numCols*pos ;
   
       
       COPY_COL_F32(pOutR,pos,pos,pTmpA);
       pTmpA[0] = 1.0f;
       pdst = pTmpB;
      
       /* v.T A(col:,col:) -> tmpb */
       
       pv = pTmpA;
       pa = p;
       for(j=0;j<pOutQ->numRows-pos; j++)
       {
               *pdst++ = *pv * *pa++; 
       }
       pa += pos;
       pv++;
       pdst = pTmpB;
       pa0 = pa;
       pa1 = pa0 + pOutQ->numRows;
       pa2 = pa1 + pOutQ->numRows;
       pa3 = pa2 + pOutQ->numRows;

       /* Unrolled loop */
       blkCnt = (pOutQ->numRows-pos - 1) >> 2;
       k=1;
       while(blkCnt > 0)
       {
           f32 sum;

           for(j=0;j<pOutQ->numRows-pos; j++)
           {
              sum = *pdst;

              sum += pv[0] * *pa0++;
              sum += pv[1] * *pa1++;
              sum += pv[2] * *pa2++;
              sum += pv[3] * *pa3++;
              
              *pdst++ = sum; 
           }
           pa0 += pos + 3*pOutQ->numRows;
           pa1 += pos + 3*pOutQ->numRows;
           pa2 += pos + 3*pOutQ->numRows;
           pa3 += pos + 3*pOutQ->numRows;
           pv  += 4;
           pdst = pTmpB;
           k += 4;
           blkCnt--;
       }

       pa = pa0;
       for(;k<pOutQ->numRows-pos; k++)
       {
           for(j=0;j<pOutQ->numRows-pos; j++)
           {
               *pdst++ += *pv * *pa++; 
           }
           pa += pos;
           pv++;
           pdst = pTmpB;
       }
   
       pa = p;
       beta = *pc--;
       for(j=0;j<pOutQ->numRows-pos; j++)
       {
           f32 f = beta * pTmpA[j];

           for(i=0;i<pOutQ->numCols-pos; i++)
           {
             *pa = *pa - f * pTmpB[i] ;
             pa++;
           }
           pa += pos;
       } 
   
   
       nb++;
     }
  }

  mips_status status = MIPS_MATH_SUCCESS;
  /* Return to application */
  return (status);
}


/**
  @} end of MatrixQR group
 */
