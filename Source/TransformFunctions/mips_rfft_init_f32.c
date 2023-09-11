/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_rfft_init_f32.c
 * Description:  RFFT & RIFFT Floating point initialisation function
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
#include "mips_common_tables.h"


/**
  @addtogroup RealFFT
  @{
 */

/**
  @brief         Initialization function for the floating-point RFFT/RIFFT.
  @deprecated    Do not use this function. It has been superceded by \ref mips_rfft_fast_init_f32 and will be removed in the future.
  @param[in,out] S             points to an instance of the floating-point RFFT/RIFFT structure
  @param[in,out] S_CFFT        points to an instance of the floating-point CFFT/CIFFT structure
  @param[in]     fftLenReal     length of the FFT.
  @param[in]     ifftFlagR      flag that selects transform direction
                   - value = 0: forward transform
                   - value = 1: inverse transform
  @param[in]     bitReverseFlag flag that enables / disables bit reversal of output
                   - value = 0: disables bit reversal of output
                   - value = 1: enables bit reversal of output
  @return        execution status
                   - \ref MIPS_MATH_SUCCESS        : Operation successful
                   - \ref MIPS_MATH_ARGUMENT_ERROR : <code>fftLenReal</code> is not a supported length

  @par Description
                   The parameter <code>fftLenReal</code>specifies length of RFFT/RIFFT Process.
                   Supported FFT Lengths are 128, 512, 2048.
  @par
                   The parameter <code>ifftFlagR</code> controls whether a forward or inverse transform is computed.
                   Set(=1) ifftFlagR to calculate RIFFT, otherwise RFFT is calculated.
  @par
                   The parameter <code>bitReverseFlag</code> controls whether output is in normal order or bit reversed order.
                   Set(=1) bitReverseFlag for output to be in normal order otherwise output is in bit reversed order.
  @par
                   This function also initializes Twiddle factor table.
 */

mips_status mips_rfft_init_f32(
  mips_rfft_instance_f32 * S,
  mips_cfft_radix4_instance_f32 * S_CFFT,
  uint32_t fftLenReal,
  uint32_t ifftFlagR,
  uint32_t bitReverseFlag)
{
   /*  Initialise the default mips status */
  mips_status status = MIPS_MATH_ARGUMENT_ERROR;

#if !defined(MIPS_DSP_CONFIG_TABLES) || defined(MIPS_FFT_ALLOW_TABLES)

#if !defined(MIPS_DSP_CONFIG_TABLES) || defined(MIPS_ALL_FFT_TABLES) || defined(MIPS_TABLE_REALCOEF_F32)

  /*  Initialise the default mips status */
  status = MIPS_MATH_SUCCESS;

  /*  Initialize the Real FFT length */
  S->fftLenReal = (uint16_t) fftLenReal;

  /*  Initialize the Complex FFT length */
  S->fftLenBy2 = (uint16_t) fftLenReal / 2U;

  /*  Initialize the Twiddle coefficientA pointer */
  S->pTwiddleAReal = (f32 *) realCoefA;

  /*  Initialize the Twiddle coefficientB pointer */
  S->pTwiddleBReal = (f32 *) realCoefB;

  /*  Initialize the Flag for selection of RFFT or RIFFT */
  S->ifftFlagR = (uint8_t) ifftFlagR;

  /*  Initialize the Flag for calculation Bit reversal or not */
  S->bitReverseFlagR = (uint8_t) bitReverseFlag;

  /*  Initializations of structure parameters depending on the FFT length */
  switch (S->fftLenReal)
  {
    /* Init table modifier value */
  case 8192U:
    S->twidCoefRModifier = 1U;
    break;
  case 2048U:
    S->twidCoefRModifier = 4U;
    break;
  case 512U:
    S->twidCoefRModifier = 16U;
    break;
  case 128U:
    S->twidCoefRModifier = 64U;
    break;
  default:
    /*  Reporting argument error if rfftSize is not valid value */
    status = MIPS_MATH_ARGUMENT_ERROR;
    break;
  }

  /* Init Complex FFT Instance */
  S->pCfft = S_CFFT;

  if (S->ifftFlagR)
  {
    /* Initializes the CIFFT Module for fftLenreal/2 length */
    mips_cfft_radix4_init_f32(S->pCfft, S->fftLenBy2, 1U, 0U);
  }
  else
  {
    /* Initializes the CFFT Module for fftLenreal/2 length */
    mips_cfft_radix4_init_f32(S->pCfft, S->fftLenBy2, 0U, 0U);
  }

#endif
#endif
  /* return the status of RFFT Init function */
  return (status);

}

/**
  @} end of RealFFT group
 */
