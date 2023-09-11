/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        TransformFunctions.c
 * Description:  Combination of all transform function source files.
 *
 * $Date:        18. March 2019
 * $Revision:    V1.0.0
 *
 * -------------------------------------------------------------------- */
/*
 * Copyright (C) 2019 ARM Limited or its affiliates. All rights reserved.
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

#include "mips_bitreversal.c"
#include "mips_bitreversal2.c"
#include "mips_cfft_f32.c"
#include "mips_cfft_f64.c"
#include "mips_cfft_q15.c"
#include "mips_cfft_q31.c"
#include "mips_cfft_init_f32.c"
#include "mips_cfft_init_f64.c"
#include "mips_cfft_init_q15.c"
#include "mips_cfft_init_q31.c"
#include "mips_cfft_radix2_f32.c"
#include "mips_cfft_radix2_q15.c"
#include "mips_cfft_radix2_q31.c"
#include "mips_cfft_radix4_f32.c"
#include "mips_cfft_radix4_q15.c"
#include "mips_cfft_radix4_q31.c"
#include "mips_cfft_radix8_f32.c"
#include "mips_rfft_fast_f32.c"
#include "mips_rfft_fast_f64.c"
#include "mips_rfft_fast_init_f32.c"
#include "mips_rfft_fast_init_f64.c"

#include "mips_mfcc_init_f32.c"
#include "mips_mfcc_f32.c"

#include "mips_mfcc_init_q31.c"
#include "mips_mfcc_q31.c"

#include "mips_mfcc_init_q15.c"
#include "mips_mfcc_q15.c"

/* Deprecated */

#include "mips_dct4_f32.c"
#include "mips_dct4_init_f32.c"
#include "mips_dct4_init_q15.c"
#include "mips_dct4_init_q31.c"
#include "mips_dct4_q15.c"
#include "mips_dct4_q31.c"

#include "mips_rfft_f32.c"
#include "mips_rfft_q15.c"
#include "mips_rfft_q31.c"

#include "mips_rfft_init_f32.c"
#include "mips_rfft_init_q15.c"
#include "mips_rfft_init_q31.c"

#include "mips_cfft_radix4_init_f32.c"
#include "mips_cfft_radix4_init_q15.c"
#include "mips_cfft_radix4_init_q31.c"

#include "mips_cfft_radix2_init_f32.c"
#include "mips_cfft_radix2_init_q15.c"
#include "mips_cfft_radix2_init_q31.c"
