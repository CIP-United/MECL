/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        StatisticsFunctions.c
 * Description:  Combination of all statistics function source files.
 *
 * $Date:        31 Augest 2023
 * $Revision:    V1.0.0
 *
 * -------------------------------------------------------------------- */
/*
 * Copyright (C) 2019-2020 ARM Limited or its affiliates. All rights reserved.
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

#include "mips_entropy_f32.c"
#include "mips_entropy_f64.c"
#include "mips_kullback_leibler_f32.c"
#include "mips_kullback_leibler_f64.c"
#include "mips_logsumexp_dot_prod_f32.c"
#include "mips_logsumexp_f32.c"
#include "mips_max_f32.c"
#include "mips_max_f64.c"
#include "mips_max_q15.c"
#include "mips_max_q31.c"
#include "mips_max_q7.c"
#include "mips_max_no_idx_f32.c"
#include "mips_max_no_idx_f64.c"
#include "mips_max_no_idx_q31.c"
#include "mips_max_no_idx_q15.c"
#include "mips_max_no_idx_q7.c"
#include "mips_mean_f32.c"
#include "mips_mean_f64.c"
#include "mips_mean_q15.c"
#include "mips_mean_q31.c"
#include "mips_mean_q7.c"
#include "mips_min_f32.c"
#include "mips_min_f64.c"
#include "mips_min_q15.c"
#include "mips_min_q31.c"
#include "mips_min_q7.c"
#include "mips_min_no_idx_f32.c"
#include "mips_min_no_idx_f64.c"
#include "mips_min_no_idx_q31.c"
#include "mips_min_no_idx_q15.c"
#include "mips_min_no_idx_q7.c"
#include "mips_power_f32.c"
#include "mips_power_f64.c"
#include "mips_power_q15.c"
#include "mips_power_q31.c"
#include "mips_power_q7.c"
#include "mips_rms_f32.c"
#include "mips_rms_q15.c"
#include "mips_rms_q31.c"
#include "mips_std_f32.c"
#include "mips_std_f64.c"
#include "mips_std_q15.c"
#include "mips_std_q31.c"
#include "mips_var_f32.c"
#include "mips_var_f64.c"
#include "mips_var_q15.c"
#include "mips_var_q31.c"
#include "mips_absmax_f32.c"
#include "mips_absmax_f64.c"
#include "mips_absmax_q15.c"
#include "mips_absmax_q31.c"
#include "mips_absmax_q7.c"
#include "mips_absmin_f32.c"
#include "mips_absmin_f64.c"
#include "mips_absmin_q15.c"
#include "mips_absmin_q31.c"
#include "mips_absmin_q7.c"
#include "mips_absmax_no_idx_f32.c"
#include "mips_absmax_no_idx_f64.c"
#include "mips_absmax_no_idx_q15.c"
#include "mips_absmax_no_idx_q31.c"
#include "mips_absmax_no_idx_q7.c"
#include "mips_absmin_no_idx_f32.c"
#include "mips_absmin_no_idx_f64.c"
#include "mips_absmin_no_idx_q15.c"
#include "mips_absmin_no_idx_q31.c"
#include "mips_absmin_no_idx_q7.c"
#include "mips_mse_q7.c"
#include "mips_mse_q15.c"
#include "mips_mse_q31.c"
#include "mips_mse_f32.c"
#include "mips_mse_f64.c"
#include "mips_accumulate_f32.c"
#include "mips_accumulate_f64.c"


