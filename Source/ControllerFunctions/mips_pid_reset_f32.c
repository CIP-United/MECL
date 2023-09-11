/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_pid_reset_f32.c
 * Description:  Floating-point PID Control reset function
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
  @brief         Reset function for the floating-point PID Control.
  @param[in,out] S  points to an instance of the floating-point PID structure
  @return        none

  @par           Details
                   The function resets the state buffer to zeros.
 */

void mips_pid_reset_f32(
  mips_pid_instance_f32 * S)
{
  /* Reset state to zero, The size will be always 3 samples */
  memset(S->state, 0, 3U * sizeof(f32));
}

/**
  @} end of PID group
 */
