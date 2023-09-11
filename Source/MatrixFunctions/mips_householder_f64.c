/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_householder_f64.c
 * Description:  Double floating-point Householder transform
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
#include "dsp/basic_math_functions.h"
#include "dsp/fast_math_functions.h"

#include "dsp/matrix_utils.h"

#include <math.h>



/**
  @ingroup groupMatrix
 */


/**
  @addtogroup MatrixHouseholder
  @{
 */

/**
  @brief         Householder transform of a double floating point vector.
  @param[in]     pSrc        points to the input vector.
  @param[in]     threshold   norm2 threshold.  
  @param[in]     blockSize   dimension of the vector space.
  @param[out]    pOut        points to the output vector.
  @return        beta        return the scaling factor beta
 */




f64 mips_householder_f64(
    const f64 * pSrc,
    const f64 threshold,
    uint32_t    blockSize,
    f64 * pOut
    )

{
  uint32_t i;
  f64 epsilon;
  f64 x1norm2,alpha;
  f64 beta,tau,r;

  epsilon = threshold;

  alpha = pSrc[0];

  for(i=1; i < blockSize; i++)
  {
    pOut[i] = pSrc[i];
  }
  pOut[0] = 1.0;

  mips_dot_prod_f64(pSrc+1,pSrc+1,blockSize-1,&x1norm2);

  if (x1norm2<=epsilon)
  {
     tau = 0.0;
     memset(pOut,0,blockSize * sizeof(f64));
  }
  else
  {
    beta =  alpha * alpha + x1norm2;
    beta=sqrt(beta);

    if (alpha > 0.0)
    {
      beta = -beta;
    }

    r = 1.0 / (alpha -beta);
    mips_scale_f64(pOut,r,pOut,blockSize);
    pOut[0] = 1.0;

    
    tau = (beta - alpha) / beta;

  }

  return(tau);

}


/**
  @} end of MatrixHouseholder group
 */
