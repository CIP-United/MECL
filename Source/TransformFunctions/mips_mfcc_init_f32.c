/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_mfcc_init_f32.c
 * Description:  MFCC initialization function for the f32 version
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

/**
  @ingroup groupTransforms
 */


/**
  @addtogroup MFCC
  @{
 */


#include "dsp/transform_functions.h"



/**
  @brief         Initialization of the MFCC F32 instance structure
  @param[out]    S       points to the mfcc instance structure
  @param[in]     fftLen  fft length
  @param[in]     nbMelFilters  number of Mel filters
  @param[in]     nbDctOutputs  number of Dct outputs
  @param[in]     dctCoefs  points to an array of DCT coefficients
  @param[in]     filterPos  points of the array of filter positions
  @param[in]     filterLengths  points to the array of filter lengths
  @param[in]     filterCoefs  points to the array of filter coefficients
  @param[in]     windowCoefs  points to the array of window coefficients

  @return        error status

  @par           Description
                   The matrix of Mel filter coefficients is sparse.
                   Most of the coefficients are zero.
                   To avoid multiplying the spectrogram by those zeros, the
                   filter is applied only to a given position in the spectrogram
                   and on a given number of FFT bins (the filter length).
                   It is the reason for the arrays filterPos and filterLengths.

                   window coefficients can describe (for instance) a Hamming window.
                   The array has the same size as the FFT length.

                   The folder Scripts is containing a Python script which can be used
                   to generate the filter, dct and window arrays.
 */

mips_status mips_mfcc_init_f32(
  mips_mfcc_instance_f32 * S,
  uint32_t fftLen,
  uint32_t nbMelFilters,
  uint32_t nbDctOutputs,
  const f32 *dctCoefs,
  const uint32_t *filterPos,
  const uint32_t *filterLengths,
  const f32 *filterCoefs,
  const f32 *windowCoefs
  )
{
 mips_status status;

 S->fftLen=fftLen;
 S->nbMelFilters=nbMelFilters;
 S->nbDctOutputs=nbDctOutputs;
 S->dctCoefs=dctCoefs;
 S->filterPos=filterPos;
 S->filterLengths=filterLengths;
 S->filterCoefs=filterCoefs;
 S->windowCoefs=windowCoefs;

 #if defined(MIPS_MFCC_CFFT_BASED)
 status=mips_cfft_init_f32(&(S->cfft),fftLen);
 #else
 status=mips_rfft_fast_init_f32(&(S->rfft),fftLen);
 #endif
 
 return(status);
}

/**
  @} end of MFCC group
 */
