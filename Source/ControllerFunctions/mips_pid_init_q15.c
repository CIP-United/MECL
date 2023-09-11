/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_pid_init_q15.c
 * Description:  Q15 PID Control initialization function
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

#include "dsp/controller_functions.h"

/**
  @addtogroup PID
  @{
 */

/**
  @brief         Initialization function for the Q15 PID Control.
  @param[in,out] S               points to an instance of the Q15 PID structure
  @param[in]     resetStateFlag
                   - value = 0: no change in state
                   - value = 1: reset state
  @return        none

  @par           Details
                   The <code>resetStateFlag</code> specifies whether to set state to zero or not. \n
                   The function computes the structure fields: <code>A0</code>, <code>A1</code> <code>A2</code>
                   using the proportional gain( \c Kp), integral gain( \c Ki) and derivative gain( \c Kd)
                   also sets the state variables to all zeros.
 */

void mips_pid_init_q15(
  mips_pid_instance_q15 * S,
  int32_t resetStateFlag)
{

  q31 temp;                                    /* to store the sum */

  /* Derived coefficient A0 */
  temp = S->Kp + S->Ki + S->Kd;
  S->A0 = (q15) __SSAT(temp, 16);

  /* Derived coefficients and pack into A1 */
  temp = -(S->Kd + S->Kd + S->Kp);
  S->A1 = (q15) __SSAT(temp, 16);
  S->A2 = S->Kd;


  /* Check whether state needs reset or not */
  if (resetStateFlag)
  {
    /* Reset state to zero, The size will be always 3 samples */
    memset(S->state, 0, 3U * sizeof(q15));
  }

}

/**
  @} end of PID group
 */
