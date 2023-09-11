/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_const_structs.c
 * Description:  Constant structs that are initialized for user convenience.
 *               For example, some can be given as arguments to the mips_cfft_f32() or mips_rfft_f32() functions.
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

#include "mips_math_types.h"
#include "mips_const_structs.h"

/*
ALLOW TABLE is true when config table is enabled and the Tramsform folder is included 
for compilation.
*/

/* Floating-point structs */
const mips_cfft_instance_f64 mips_cfft_sR_f64_len16 = {
  16, (const f64 *)twiddleCoefF64_16, mipsBitRevIndexTableF64_16, MIPSBITREVINDEXTABLEF64_16_TABLE_LENGTH
};

const mips_cfft_instance_f64 mips_cfft_sR_f64_len32 = {
  32, (const f64 *)twiddleCoefF64_32, mipsBitRevIndexTableF64_32, MIPSBITREVINDEXTABLEF64_32_TABLE_LENGTH
};

const mips_cfft_instance_f64 mips_cfft_sR_f64_len64 = {
  64, (const f64 *)twiddleCoefF64_64, mipsBitRevIndexTableF64_64, MIPSBITREVINDEXTABLEF64_64_TABLE_LENGTH
};

const mips_cfft_instance_f64 mips_cfft_sR_f64_len128 = {
  128, (const f64 *)twiddleCoefF64_128, mipsBitRevIndexTableF64_128, MIPSBITREVINDEXTABLEF64_128_TABLE_LENGTH
};

const mips_cfft_instance_f64 mips_cfft_sR_f64_len256 = {
  256, (const f64 *)twiddleCoefF64_256, mipsBitRevIndexTableF64_256, MIPSBITREVINDEXTABLEF64_256_TABLE_LENGTH
};

const mips_cfft_instance_f64 mips_cfft_sR_f64_len512 = {
  512, (const f64 *)twiddleCoefF64_512, mipsBitRevIndexTableF64_512, MIPSBITREVINDEXTABLEF64_512_TABLE_LENGTH
};

const mips_cfft_instance_f64 mips_cfft_sR_f64_len1024 = {
  1024, (const f64 *)twiddleCoefF64_1024, mipsBitRevIndexTableF64_1024, MIPSBITREVINDEXTABLEF64_1024_TABLE_LENGTH
};

const mips_cfft_instance_f64 mips_cfft_sR_f64_len2048 = {
  2048, (const f64 *)twiddleCoefF64_2048, mipsBitRevIndexTableF64_2048, MIPSBITREVINDEXTABLEF64_2048_TABLE_LENGTH
};

const mips_cfft_instance_f64 mips_cfft_sR_f64_len4096 = {
  4096, (const f64 *)twiddleCoefF64_4096, mipsBitRevIndexTableF64_4096, MIPSBITREVINDEXTABLEF64_4096_TABLE_LENGTH
};

/* Floating-point structs */
#if !defined(MIPS_MATH_MSA)


const mips_cfft_instance_f32 mips_cfft_sR_f32_len16 = {
  16, twiddleCoef_16, mipsBitRevIndexTable16, MIPSBITREVINDEXTABLE_16_TABLE_LENGTH
};


const mips_cfft_instance_f32 mips_cfft_sR_f32_len32 = {
  32, twiddleCoef_32, mipsBitRevIndexTable32, MIPSBITREVINDEXTABLE_32_TABLE_LENGTH
};

const mips_cfft_instance_f32 mips_cfft_sR_f32_len64 = {
  64, twiddleCoef_64, mipsBitRevIndexTable64, MIPSBITREVINDEXTABLE_64_TABLE_LENGTH
};

const mips_cfft_instance_f32 mips_cfft_sR_f32_len128 = {
  128, twiddleCoef_128, mipsBitRevIndexTable128, MIPSBITREVINDEXTABLE_128_TABLE_LENGTH
};

const mips_cfft_instance_f32 mips_cfft_sR_f32_len256 = {
  256, twiddleCoef_256, mipsBitRevIndexTable256, MIPSBITREVINDEXTABLE_256_TABLE_LENGTH
};

const mips_cfft_instance_f32 mips_cfft_sR_f32_len512 = {
  512, twiddleCoef_512, mipsBitRevIndexTable512, MIPSBITREVINDEXTABLE_512_TABLE_LENGTH
};

const mips_cfft_instance_f32 mips_cfft_sR_f32_len1024 = {
  1024, twiddleCoef_1024, mipsBitRevIndexTable1024, MIPSBITREVINDEXTABLE_1024_TABLE_LENGTH
};

const mips_cfft_instance_f32 mips_cfft_sR_f32_len2048 = {
  2048, twiddleCoef_2048, mipsBitRevIndexTable2048, MIPSBITREVINDEXTABLE_2048_TABLE_LENGTH
};

const mips_cfft_instance_f32 mips_cfft_sR_f32_len4096 = {
  4096, twiddleCoef_4096, mipsBitRevIndexTable4096, MIPSBITREVINDEXTABLE_4096_TABLE_LENGTH
};

#endif /* !defined(MIPS_MATH_MSA) */

/* Fixed-point structs */

#if !defined(MIPS_MATH_MSA)

/* 

Those structures cannot be used to initialize the MSA version of the FFT Q31 instances.
So they are not compiled when MSA is defined.

For the MSA version, the new mips_cfft_init_f32 must be used.


*/

const mips_cfft_instance_q31 mips_cfft_sR_q31_len16 = {
  16, twiddleCoef_16_q31, mipsBitRevIndexTable_fixed_16, MIPSBITREVINDEXTABLE_FIXED_16_TABLE_LENGTH
};

const mips_cfft_instance_q31 mips_cfft_sR_q31_len32 = {
  32, twiddleCoef_32_q31, mipsBitRevIndexTable_fixed_32, MIPSBITREVINDEXTABLE_FIXED_32_TABLE_LENGTH
};

const mips_cfft_instance_q31 mips_cfft_sR_q31_len64 = {
  64, twiddleCoef_64_q31, mipsBitRevIndexTable_fixed_64, MIPSBITREVINDEXTABLE_FIXED_64_TABLE_LENGTH
};

const mips_cfft_instance_q31 mips_cfft_sR_q31_len128 = {
  128, twiddleCoef_128_q31, mipsBitRevIndexTable_fixed_128, MIPSBITREVINDEXTABLE_FIXED_128_TABLE_LENGTH
};

const mips_cfft_instance_q31 mips_cfft_sR_q31_len256 = {
  256, twiddleCoef_256_q31, mipsBitRevIndexTable_fixed_256, MIPSBITREVINDEXTABLE_FIXED_256_TABLE_LENGTH
};

const mips_cfft_instance_q31 mips_cfft_sR_q31_len512 = {
  512, twiddleCoef_512_q31, mipsBitRevIndexTable_fixed_512, MIPSBITREVINDEXTABLE_FIXED_512_TABLE_LENGTH
};

const mips_cfft_instance_q31 mips_cfft_sR_q31_len1024 = {
  1024, twiddleCoef_1024_q31, mipsBitRevIndexTable_fixed_1024, MIPSBITREVINDEXTABLE_FIXED_1024_TABLE_LENGTH
};

const mips_cfft_instance_q31 mips_cfft_sR_q31_len2048 = {
  2048, twiddleCoef_2048_q31, mipsBitRevIndexTable_fixed_2048, MIPSBITREVINDEXTABLE_FIXED_2048_TABLE_LENGTH
};

const mips_cfft_instance_q31 mips_cfft_sR_q31_len4096 = {
  4096, twiddleCoef_4096_q31, mipsBitRevIndexTable_fixed_4096, MIPSBITREVINDEXTABLE_FIXED_4096_TABLE_LENGTH
};


const mips_cfft_instance_q15 mips_cfft_sR_q15_len16 = {
  16, twiddleCoef_16_q15, mipsBitRevIndexTable_fixed_16, MIPSBITREVINDEXTABLE_FIXED_16_TABLE_LENGTH
};

const mips_cfft_instance_q15 mips_cfft_sR_q15_len32 = {
  32, twiddleCoef_32_q15, mipsBitRevIndexTable_fixed_32, MIPSBITREVINDEXTABLE_FIXED_32_TABLE_LENGTH
};

const mips_cfft_instance_q15 mips_cfft_sR_q15_len64 = {
  64, twiddleCoef_64_q15, mipsBitRevIndexTable_fixed_64, MIPSBITREVINDEXTABLE_FIXED_64_TABLE_LENGTH
};

const mips_cfft_instance_q15 mips_cfft_sR_q15_len128 = {
  128, twiddleCoef_128_q15, mipsBitRevIndexTable_fixed_128, MIPSBITREVINDEXTABLE_FIXED_128_TABLE_LENGTH
};

const mips_cfft_instance_q15 mips_cfft_sR_q15_len256 = {
  256, twiddleCoef_256_q15, mipsBitRevIndexTable_fixed_256, MIPSBITREVINDEXTABLE_FIXED_256_TABLE_LENGTH
};

const mips_cfft_instance_q15 mips_cfft_sR_q15_len512 = {
  512, twiddleCoef_512_q15, mipsBitRevIndexTable_fixed_512, MIPSBITREVINDEXTABLE_FIXED_512_TABLE_LENGTH
};

const mips_cfft_instance_q15 mips_cfft_sR_q15_len1024 = {
  1024, twiddleCoef_1024_q15, mipsBitRevIndexTable_fixed_1024, MIPSBITREVINDEXTABLE_FIXED_1024_TABLE_LENGTH
};

const mips_cfft_instance_q15 mips_cfft_sR_q15_len2048 = {
  2048, twiddleCoef_2048_q15, mipsBitRevIndexTable_fixed_2048, MIPSBITREVINDEXTABLE_FIXED_2048_TABLE_LENGTH
};

const mips_cfft_instance_q15 mips_cfft_sR_q15_len4096 = {
  4096, twiddleCoef_4096_q15, mipsBitRevIndexTable_fixed_4096, MIPSBITREVINDEXTABLE_FIXED_4096_TABLE_LENGTH
};

#endif /* !defined(MIPS_MATH_MSA) */

/* Structure for real-value inputs */
/* Double precision strucs */

const mips_rfft_fast_instance_f64 mips_rfft_fast_sR_f64_len32 = {
  { 16, (const f64 *)twiddleCoefF64_16, mipsBitRevIndexTableF64_16, MIPSBITREVINDEXTABLEF64_16_TABLE_LENGTH },
  32U,
  (f64 *)twiddleCoefF64_rfft_32
};

const mips_rfft_fast_instance_f64 mips_rfft_fast_sR_f64_len64 = {
   { 32, (const f64 *)twiddleCoefF64_32, mipsBitRevIndexTableF64_32, MIPSBITREVINDEXTABLEF64_32_TABLE_LENGTH },
  64U,
  (f64 *)twiddleCoefF64_rfft_64
};

const mips_rfft_fast_instance_f64 mips_rfft_fast_sR_f64_len128 = {
  { 64, (const f64 *)twiddleCoefF64_64, mipsBitRevIndexTableF64_64, MIPSBITREVINDEXTABLEF64_64_TABLE_LENGTH },
  128U,
  (f64 *)twiddleCoefF64_rfft_128
};

const mips_rfft_fast_instance_f64 mips_rfft_fast_sR_f64_len256 = {
  { 128, (const f64 *)twiddleCoefF64_128, mipsBitRevIndexTableF64_128, MIPSBITREVINDEXTABLEF64_128_TABLE_LENGTH },
  256U,
  (f64 *)twiddleCoefF64_rfft_256
};

const mips_rfft_fast_instance_f64 mips_rfft_fast_sR_f64_len512 = {
  { 256, (const f64 *)twiddleCoefF64_256, mipsBitRevIndexTableF64_256, MIPSBITREVINDEXTABLEF64_256_TABLE_LENGTH },
  512U,
  (f64 *)twiddleCoefF64_rfft_512
};

const mips_rfft_fast_instance_f64 mips_rfft_fast_sR_f64_len1024 = {
  { 512, (const f64 *)twiddleCoefF64_512, mipsBitRevIndexTableF64_512, MIPSBITREVINDEXTABLEF64_512_TABLE_LENGTH },
  1024U,
  (f64 *)twiddleCoefF64_rfft_1024
};

const mips_rfft_fast_instance_f64 mips_rfft_fast_sR_f64_len2048 = {
  { 1024, (const f64 *)twiddleCoefF64_1024, mipsBitRevIndexTableF64_1024, MIPSBITREVINDEXTABLEF64_1024_TABLE_LENGTH },
  2048U,
  (f64 *)twiddleCoefF64_rfft_2048
};

const mips_rfft_fast_instance_f64 mips_rfft_fast_sR_f64_len4096 = {
  { 2048, (const f64 *)twiddleCoefF64_2048, mipsBitRevIndexTableF64_2048, MIPSBITREVINDEXTABLEF64_2048_TABLE_LENGTH },
  4096U,
  (f64 *)twiddleCoefF64_rfft_4096
};

/* Floating-point structs */

#if !defined(MIPS_MATH_MSA)

const mips_rfft_fast_instance_f32 mips_rfft_fast_sR_f32_len32 = {
  { 16, twiddleCoef_16, mipsBitRevIndexTable16, MIPSBITREVINDEXTABLE_16_TABLE_LENGTH },
  32U,
  (f32 *)twiddleCoef_rfft_32
};

const mips_rfft_fast_instance_f32 mips_rfft_fast_sR_f32_len64 = {
   { 32, twiddleCoef_32, mipsBitRevIndexTable32, MIPSBITREVINDEXTABLE_32_TABLE_LENGTH },
  64U,
  (f32 *)twiddleCoef_rfft_64
};

const mips_rfft_fast_instance_f32 mips_rfft_fast_sR_f32_len128 = {
  { 64, twiddleCoef_64, mipsBitRevIndexTable64, MIPSBITREVINDEXTABLE_64_TABLE_LENGTH },
  128U,
  (f32 *)twiddleCoef_rfft_128
};

const mips_rfft_fast_instance_f32 mips_rfft_fast_sR_f32_len256 = {
  { 128, twiddleCoef_128, mipsBitRevIndexTable128, MIPSBITREVINDEXTABLE_128_TABLE_LENGTH },
  256U,
  (f32 *)twiddleCoef_rfft_256
};

const mips_rfft_fast_instance_f32 mips_rfft_fast_sR_f32_len512 = {
  { 256, twiddleCoef_256, mipsBitRevIndexTable256, MIPSBITREVINDEXTABLE_256_TABLE_LENGTH },
  512U,
  (f32 *)twiddleCoef_rfft_512
};

const mips_rfft_fast_instance_f32 mips_rfft_fast_sR_f32_len1024 = {
  { 512, twiddleCoef_512, mipsBitRevIndexTable512, MIPSBITREVINDEXTABLE_512_TABLE_LENGTH },
  1024U,
  (f32 *)twiddleCoef_rfft_1024
};

const mips_rfft_fast_instance_f32 mips_rfft_fast_sR_f32_len2048 = {
  { 1024, twiddleCoef_1024, mipsBitRevIndexTable1024, MIPSBITREVINDEXTABLE_1024_TABLE_LENGTH },
  2048U,
  (f32 *)twiddleCoef_rfft_2048
};

const mips_rfft_fast_instance_f32 mips_rfft_fast_sR_f32_len4096 = {
  { 2048, twiddleCoef_2048, mipsBitRevIndexTable2048, MIPSBITREVINDEXTABLE_2048_TABLE_LENGTH },
  4096U,
  (f32 *)twiddleCoef_rfft_4096
};

#endif /* #if !defined(MIPS_MATH_MSA) */

/* Fixed-point structs */
/* q31 */

#if !defined(MIPS_MATH_MSA)

/* 

Those structures cannot be used to initialize the MSA version of the FFT Q31 instances.
So they are not compiled when MSA is defined.

For the MSA version, the new mips_cfft_init_f32 must be used.


*/

const mips_rfft_instance_q31 mips_rfft_sR_q31_len32 = {
  32U,
  0,
  1,
  256U,
  (q31*)realCoefAQ31,
  (q31*)realCoefBQ31,
  &mips_cfft_sR_q31_len16
};

const mips_rfft_instance_q31 mips_rfft_sR_q31_len64 = {
  64U,
  0,
  1,
  128U,
  (q31*)realCoefAQ31,
  (q31*)realCoefBQ31,
  &mips_cfft_sR_q31_len32
};

const mips_rfft_instance_q31 mips_rfft_sR_q31_len128 = {
  128U,
  0,
  1,
  64U,
  (q31*)realCoefAQ31,
  (q31*)realCoefBQ31,
  &mips_cfft_sR_q31_len64
};

const mips_rfft_instance_q31 mips_rfft_sR_q31_len256 = {
  256U,
  0,
  1,
  32U,
  (q31*)realCoefAQ31,
  (q31*)realCoefBQ31,
  &mips_cfft_sR_q31_len128
};

const mips_rfft_instance_q31 mips_rfft_sR_q31_len512 = {
  512U,
  0,
  1,
  16U,
  (q31*)realCoefAQ31,
  (q31*)realCoefBQ31,
  &mips_cfft_sR_q31_len256
};

const mips_rfft_instance_q31 mips_rfft_sR_q31_len1024 = {
  1024U,
  0,
  1,
  8U,
  (q31*)realCoefAQ31,
  (q31*)realCoefBQ31,
  &mips_cfft_sR_q31_len512
};

const mips_rfft_instance_q31 mips_rfft_sR_q31_len2048 = {
  2048U,
  0,
  1,
  4U,
  (q31*)realCoefAQ31,
  (q31*)realCoefBQ31,
  &mips_cfft_sR_q31_len1024
};

const mips_rfft_instance_q31 mips_rfft_sR_q31_len4096 = {
  4096U,
  0,
  1,
  2U,
  (q31*)realCoefAQ31,
  (q31*)realCoefBQ31,
  &mips_cfft_sR_q31_len2048
};

const mips_rfft_instance_q31 mips_rfft_sR_q31_len8192 = {
  8192U,
  0,
  1,
  1U,
  (q31*)realCoefAQ31,
  (q31*)realCoefBQ31,
  &mips_cfft_sR_q31_len4096
};

/* q15 */
const mips_rfft_instance_q15 mips_rfft_sR_q15_len32 = {
  32U,
  0,
  1,
  256U,
  (q15*)realCoefAQ15,
  (q15*)realCoefBQ15,
  &mips_cfft_sR_q15_len16
};

const mips_rfft_instance_q15 mips_rfft_sR_q15_len64 = {
  64U,
  0,
  1,
  128U,
  (q15*)realCoefAQ15,
  (q15*)realCoefBQ15,
  &mips_cfft_sR_q15_len32
};

const mips_rfft_instance_q15 mips_rfft_sR_q15_len128 = {
  128U,
  0,
  1,
  64U,
  (q15*)realCoefAQ15,
  (q15*)realCoefBQ15,
  &mips_cfft_sR_q15_len64
};

const mips_rfft_instance_q15 mips_rfft_sR_q15_len256 = {
  256U,
  0,
  1,
  32U,
  (q15*)realCoefAQ15,
  (q15*)realCoefBQ15,
  &mips_cfft_sR_q15_len128
};

const mips_rfft_instance_q15 mips_rfft_sR_q15_len512 = {
  512U,
  0,
  1,
  16U,
  (q15*)realCoefAQ15,
  (q15*)realCoefBQ15,
  &mips_cfft_sR_q15_len256
};

const mips_rfft_instance_q15 mips_rfft_sR_q15_len1024 = {
  1024U,
  0,
  1,
  8U,
  (q15*)realCoefAQ15,
  (q15*)realCoefBQ15,
  &mips_cfft_sR_q15_len512
};

const mips_rfft_instance_q15 mips_rfft_sR_q15_len2048 = {
  2048U,
  0,
  1,
  4U,
  (q15*)realCoefAQ15,
  (q15*)realCoefBQ15,
  &mips_cfft_sR_q15_len1024
};

const mips_rfft_instance_q15 mips_rfft_sR_q15_len4096 = {
  4096U,
  0,
  1,
  2U,
  (q15*)realCoefAQ15,
  (q15*)realCoefBQ15,
  &mips_cfft_sR_q15_len2048
};

const mips_rfft_instance_q15 mips_rfft_sR_q15_len8192 = {
  8192U,
  0,
  1,
  1U,
  (q15*)realCoefAQ15,
  (q15*)realCoefBQ15,
  &mips_cfft_sR_q15_len4096
};

#endif /* !defined(MIPS_MATH_MSA) */


