/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_fir_decimate_init_f32.c
 * Description:  Floating-point FIR Decimator initialization function
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

#include "dsp/filtering_functions.h"

/**
  @ingroup groupFilters
 */

/**
  @addtogroup FIR_decimate
  @{
 */

/**
  @brief         Initialization function for the floating-point FIR decimator.
  @param[in,out] S          points to an instance of the floating-point FIR decimator structure
  @param[in]     numTaps    number of coefficients in the filter
  @param[in]     M          decimation factor
  @param[in]     pCoeffs    points to the filter coefficients
  @param[in]     pState     points to the state buffer
  @param[in]     blockSize  number of input samples to process per call
  @return        execution status
                   - \ref MIPS_MATH_SUCCESS      : Operation successful
                   - \ref MIPS_MATH_LENGTH_ERROR : <code>blockSize</code> is not a multiple of <code>M</code>

  @par           Details
                   <code>pCoeffs</code> points to the array of filter coefficients stored in time reversed order:
  <pre>
      {b[numTaps-1], b[numTaps-2], b[N-2], ..., b[1], b[0]}
  </pre>
  @par
                   <code>pState</code> points to the array of state variables.
                   <code>pState</code> is of length <code>numTaps+blockSize-1</code> words where <code>blockSize</code> is the number of input samples passed to <code>mips_fir_decimate_f32()</code>.
                   <code>M</code> is the decimation factor.
 */

mips_status mips_fir_decimate_init_f32(
        mips_fir_decimate_instance_f32 * S,
        uint16_t numTaps,
        uint8_t M,
  const f32 * pCoeffs,
        f32 * pState,
        uint32_t blockSize)
{
  mips_status status;

  /* The size of the input block must be a multiple of the decimation factor */
  if ((blockSize % M) != 0U)
  {
    /* Set status as MIPS_MATH_LENGTH_ERROR */
    status = MIPS_MATH_LENGTH_ERROR;
  }
  else
  {
    /* Assign filter taps */
    S->numTaps = numTaps;

    /* Assign coefficient pointer */
    S->pCoeffs = pCoeffs;

    /* Clear the state buffer. The size is always (blockSize + numTaps - 1) */
    memset(pState, 0, (numTaps + (blockSize - 1U)) * sizeof(f32));

    /* Assign state pointer */
    S->pState = pState;

    /* Assign Decimation Factor */
    S->M = M;

    status = MIPS_MATH_SUCCESS;
  }

  return (status);

}

/**
  @} end of FIR_decimate group
 */
