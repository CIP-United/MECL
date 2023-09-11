/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_sort_init_f32.c
 * Description:  Floating point sort initialization function
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

#include "mips_sorting.h"

/**
  @ingroup groupSupport
 */

/**
  @addtogroup Sorting
  @{
 */


  /**
   * @param[in,out]  S            points to an instance of the sorting structure.
   * @param[in]      alg          Selected algorithm.
   * @param[in]      dir          Sorting order.
   */
void mips_sort_init_f32(mips_sort_instance_f32 * S, mips_sort_alg alg, mips_sort_dir dir)
{
    S->alg         = alg;
    S->dir         = dir;
}

/**
  @} end of Sorting group
 */
