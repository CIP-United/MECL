/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_mfcc_q15.c
 * Description:  MFCC function for the q15 version
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



#include "dsp/transform_functions.h"
#include "dsp/statistics_functions.h"
#include "dsp/basic_math_functions.h"
#include "dsp/complex_math_functions.h"
#include "dsp/fast_math_functions.h"
#include "dsp/matrix_functions.h"

/* Constants for Q15 implementation */
#define LOG2TOLOG_Q15 0x02C5C860
#define MICRO_Q15 0x00000219
#define SHIFT_MELFILTER_SATURATION_Q15 10
/**
  @ingroup groupTransforms
 */



/**
  @addtogroup MFCC
  @{
 */

/**
  @brief         MFCC Q15
  @param[in]    S       points to the mfcc instance structure
  @param[in]     pSrc points to the input samples in Q15
  @param[out]     pDst  points to the output MFCC values in q8.7 format
  @param[inout]     pTmp  points to a temporary buffer of complex

  @return        none

  @par           Description
                   The number of input samples is the FFT length used
                   when initializing the instance data structure.

                   The temporary buffer has a 2*fft length.

                   The source buffer is modified by this function.

                   The function may saturate. If the FFT length is too
                   big and the number of MEL filters too small then the fixed
                   point computations may saturate.

 */

mips_status mips_mfcc_q15(
  const mips_mfcc_instance_q15 * S,
  q15 *pSrc,
  q15 *pDst,
  q31 *pTmp
  )
{
    q15 m;
    uint32_t index;
    uint32_t fftShift=0;
    q31 logExponent;
    q63 result;
    mips_matrix_instance_q15 pDctMat;
    uint32_t i;
    uint32_t coefsPos;
    uint32_t filterLimit;
    q15 *pTmp2=(q15*)pTmp;

    mips_status status = MIPS_MATH_SUCCESS;
    
    // q15
    mips_absmax_q15(pSrc,S->fftLen,&m,&index);

    if (m !=0)
    {
       q15 quotient;
       int16_t shift;

       status = mips_divide_q15(0x7FFF,m,&quotient,&shift);
       if (status != MIPS_MATH_SUCCESS)
       {
          return(status);
       }
 
       mips_scale_q15(pSrc,quotient,shift,pSrc,S->fftLen);
    }


    // q15
    mips_mult_q15(pSrc,S->windowCoefs, pSrc, S->fftLen);


    /* Compute spectrum magnitude 
    */
    fftShift = 31 - __CLZ(S->fftLen);
#if defined(MIPS_MFCC_CFFT_BASED)
    /* some HW accelerator for MECL used in some boards
       are only providing acceleration for CFFT.
       With MIPS_MFCC_CFFT_BASED enabled, CFFT is used and the MFCC
       will be accelerated on those boards.
 
       The default is to use RFFT
    */
    /* Convert from real to complex */
    for(i=0; i < S->fftLen ; i++)
    {
      pTmp2[2*i] = pSrc[i];
      pTmp2[2*i+1] = 0;
    }
    mips_cfft_q15(&(S->cfft),pTmp2,0,1);
#else
    /* Default RFFT based implementation */
    mips_rfft_q15(&(S->rfft),pSrc,pTmp2);
#endif
    filterLimit = 1 + (S->fftLen >> 1);


    // q15 - fftShift
    mips_cmplx_mag_q15(pTmp2,pSrc,filterLimit);
    // q14 - fftShift

    /* Apply MEL filters */
    coefsPos = 0;
    for(i=0; i<S->nbMelFilters; i++)
    {
      mips_dot_prod_q15(pSrc+S->filterPos[i],
        &(S->filterCoefs[coefsPos]),
        S->filterLengths[i],
        &result);

      coefsPos += S->filterLengths[i];

      // q34.29 - fftShift
      result += MICRO_Q15;
      result >>= SHIFT_MELFILTER_SATURATION_Q15;
      // q34.29 - fftShift - satShift
      pTmp[i] = __SSAT(result,31) ;

    }


    // q34.29 - fftShift - satShift
    /* Compute the log */
    mips_vlog_q31(pTmp,pTmp,S->nbMelFilters);


    // q5.26
   
    logExponent = fftShift + 2 + SHIFT_MELFILTER_SATURATION_Q15;
    logExponent = logExponent * LOG2TOLOG_Q15;


    // q8.26
    mips_offset_q31(pTmp,logExponent,pTmp,S->nbMelFilters);
    mips_shift_q31(pTmp,-19,pTmp,S->nbMelFilters);
    for(i=0; i<S->nbMelFilters; i++)
    { 
      pSrc[i] = __SSAT((q15)pTmp[i],16);
    }

    // q8.7

    pDctMat.numRows=S->nbDctOutputs;
    pDctMat.numCols=S->nbMelFilters;
    pDctMat.pData=(q15*)S->dctCoefs;

    mips_mat_vec_mult_q15(&pDctMat, pSrc, pDst);

    return(status);
}

/**
  @} end of MFCC group
 */
