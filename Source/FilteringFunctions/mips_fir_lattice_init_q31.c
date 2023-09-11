/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_fir_lattice_init_q31.c
 * Description:  Q31 FIR lattice filter initialization function
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
  @addtogroup FIR_Lattice
  @{
 */

/**
  @brief         Initialization function for the Q31 FIR lattice filter.
  @param[in]     S          points to an instance of the Q31 FIR lattice structure
  @param[in]     numStages  number of filter stages
  @param[in]     pCoeffs    points to the coefficient buffer.  The array is of length numStages
  @param[in]     pState     points to the state buffer.  The array is of length numStages
  @return        none
 */

void mips_fir_lattice_init_q31(
        mips_fir_lattice_instance_q31 * S,
        uint16_t numStages,
  const q31 * pCoeffs,
        q31 * pState)
{
  /* Assign filter taps */
  S->numStages = numStages;

  /* Assign coefficient pointer */
  S->pCoeffs = pCoeffs;

  /* Clear state buffer and size is always numStages */
  memset(pState, 0, (numStages) * sizeof(q31));

  /* Assign state pointer */
  S->pState = pState;
}

/**
  @} end of FIR_Lattice group
 */
