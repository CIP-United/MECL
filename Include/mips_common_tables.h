/* ----------------------------------------------------------------------
 * Project:      MIPS Embedded Compute Library
 * Title:        mips_common_tables.h
 * Description:  Extern declaration for common tables
 *
 * @version  V1.0.0
 * @date     31 Augest 2023
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

#ifndef _MIPS_COMMON_TABLES_H
#define _MIPS_COMMON_TABLES_H

#include "mips_math_types.h"
#include "dsp/fast_math_functions.h"

#ifdef   __cplusplus
extern "C"
{
#endif

  /* Double Precision Float CFFT twiddles */
    extern const uint16_t mipsBitRevTable[1024];

    extern const uint64_t twiddleCoefF64_16[32];

    extern const uint64_t twiddleCoefF64_32[64];

    extern const uint64_t twiddleCoefF64_64[128];

    extern const uint64_t twiddleCoefF64_128[256];

    extern const uint64_t twiddleCoefF64_256[512];

    extern const uint64_t twiddleCoefF64_512[1024];

    extern const uint64_t twiddleCoefF64_1024[2048];

    extern const uint64_t twiddleCoefF64_2048[4096];

    extern const uint64_t twiddleCoefF64_4096[8192];

    extern const f32 twiddleCoef_16[32];

    extern const f32 twiddleCoef_32[64];

    extern const f32 twiddleCoef_64[128];

    extern const f32 twiddleCoef_128[256];

    extern const f32 twiddleCoef_256[512];

    extern const f32 twiddleCoef_512[1024];

    extern const f32 twiddleCoef_1024[2048];

    extern const f32 twiddleCoef_2048[4096];

    extern const f32 twiddleCoef_4096[8192];
    #define twiddleCoef twiddleCoef_4096

  /* Q31 */

    extern const q31 twiddleCoef_16_q31[24];

    extern const q31 twiddleCoef_32_q31[48];

    extern const q31 twiddleCoef_64_q31[96];

    extern const q31 twiddleCoef_128_q31[192];

    extern const q31 twiddleCoef_256_q31[384];

    extern const q31 twiddleCoef_512_q31[768];

    extern const q31 twiddleCoef_1024_q31[1536];

    extern const q31 twiddleCoef_2048_q31[3072];

    extern const q31 twiddleCoef_4096_q31[6144];

    extern const q15 twiddleCoef_16_q15[24];

    extern const q15 twiddleCoef_32_q15[48];

    extern const q15 twiddleCoef_64_q15[96];

    extern const q15 twiddleCoef_128_q15[192];

    extern const q15 twiddleCoef_256_q15[384];

    extern const q15 twiddleCoef_512_q15[768];

    extern const q15 twiddleCoef_1024_q15[1536];

    extern const q15 twiddleCoef_2048_q15[3072];

    extern const q15 twiddleCoef_4096_q15[6144];

  /* Double Precision Float RFFT twiddles */
    extern const uint64_t twiddleCoefF64_rfft_32[32];

    extern const uint64_t twiddleCoefF64_rfft_64[64];

    extern const uint64_t twiddleCoefF64_rfft_128[128];

    extern const uint64_t twiddleCoefF64_rfft_256[256];

    extern const uint64_t twiddleCoefF64_rfft_512[512];

    extern const uint64_t twiddleCoefF64_rfft_1024[1024];

    extern const uint64_t twiddleCoefF64_rfft_2048[2048];

    extern const uint64_t twiddleCoefF64_rfft_4096[4096];

    extern const f32 twiddleCoef_rfft_32[32];

    extern const f32 twiddleCoef_rfft_64[64];

    extern const f32 twiddleCoef_rfft_128[128];

    extern const f32 twiddleCoef_rfft_256[256];

    extern const f32 twiddleCoef_rfft_512[512];

    extern const f32 twiddleCoef_rfft_1024[1024];

    extern const f32 twiddleCoef_rfft_2048[2048];

    extern const f32 twiddleCoef_rfft_4096[4096];

  /* Double precision floating-point bit reversal tables */

    #define MIPSBITREVINDEXTABLEF64_16_TABLE_LENGTH ((uint16_t)12)
    extern const uint16_t mipsBitRevIndexTableF64_16[MIPSBITREVINDEXTABLEF64_16_TABLE_LENGTH];

    #define MIPSBITREVINDEXTABLEF64_32_TABLE_LENGTH ((uint16_t)24)
    extern const uint16_t mipsBitRevIndexTableF64_32[MIPSBITREVINDEXTABLEF64_32_TABLE_LENGTH];

    #define MIPSBITREVINDEXTABLEF64_64_TABLE_LENGTH ((uint16_t)56)
    extern const uint16_t mipsBitRevIndexTableF64_64[MIPSBITREVINDEXTABLEF64_64_TABLE_LENGTH];

    #define MIPSBITREVINDEXTABLEF64_128_TABLE_LENGTH ((uint16_t)112)
    extern const uint16_t mipsBitRevIndexTableF64_128[MIPSBITREVINDEXTABLEF64_128_TABLE_LENGTH];

    #define MIPSBITREVINDEXTABLEF64_256_TABLE_LENGTH ((uint16_t)240)
    extern const uint16_t mipsBitRevIndexTableF64_256[MIPSBITREVINDEXTABLEF64_256_TABLE_LENGTH];

    #define MIPSBITREVINDEXTABLEF64_512_TABLE_LENGTH ((uint16_t)480)
    extern const uint16_t mipsBitRevIndexTableF64_512[MIPSBITREVINDEXTABLEF64_512_TABLE_LENGTH];

    #define MIPSBITREVINDEXTABLEF64_1024_TABLE_LENGTH ((uint16_t)992)
    extern const uint16_t mipsBitRevIndexTableF64_1024[MIPSBITREVINDEXTABLEF64_1024_TABLE_LENGTH];

    #define MIPSBITREVINDEXTABLEF64_2048_TABLE_LENGTH ((uint16_t)1984)
    extern const uint16_t mipsBitRevIndexTableF64_2048[MIPSBITREVINDEXTABLEF64_2048_TABLE_LENGTH];

    #define MIPSBITREVINDEXTABLEF64_4096_TABLE_LENGTH ((uint16_t)4032)
    extern const uint16_t mipsBitRevIndexTableF64_4096[MIPSBITREVINDEXTABLEF64_4096_TABLE_LENGTH];
  /* floating-point bit reversal tables */

    #define MIPSBITREVINDEXTABLE_16_TABLE_LENGTH ((uint16_t)20)
    extern const uint16_t mipsBitRevIndexTable16[MIPSBITREVINDEXTABLE_16_TABLE_LENGTH];

    #define MIPSBITREVINDEXTABLE_32_TABLE_LENGTH ((uint16_t)48)
    extern const uint16_t mipsBitRevIndexTable32[MIPSBITREVINDEXTABLE_32_TABLE_LENGTH];

    #define MIPSBITREVINDEXTABLE_64_TABLE_LENGTH ((uint16_t)56)
    extern const uint16_t mipsBitRevIndexTable64[MIPSBITREVINDEXTABLE_64_TABLE_LENGTH];

    #define MIPSBITREVINDEXTABLE_128_TABLE_LENGTH ((uint16_t)208)
    extern const uint16_t mipsBitRevIndexTable128[MIPSBITREVINDEXTABLE_128_TABLE_LENGTH];

    #define MIPSBITREVINDEXTABLE_256_TABLE_LENGTH ((uint16_t)440)
    extern const uint16_t mipsBitRevIndexTable256[MIPSBITREVINDEXTABLE_256_TABLE_LENGTH];

    #define MIPSBITREVINDEXTABLE_512_TABLE_LENGTH ((uint16_t)448)
    extern const uint16_t mipsBitRevIndexTable512[MIPSBITREVINDEXTABLE_512_TABLE_LENGTH];

    #define MIPSBITREVINDEXTABLE_1024_TABLE_LENGTH ((uint16_t)1800)
    extern const uint16_t mipsBitRevIndexTable1024[MIPSBITREVINDEXTABLE_1024_TABLE_LENGTH];

    #define MIPSBITREVINDEXTABLE_2048_TABLE_LENGTH ((uint16_t)3808)
    extern const uint16_t mipsBitRevIndexTable2048[MIPSBITREVINDEXTABLE_2048_TABLE_LENGTH];

    #define MIPSBITREVINDEXTABLE_4096_TABLE_LENGTH ((uint16_t)4032)
    extern const uint16_t mipsBitRevIndexTable4096[MIPSBITREVINDEXTABLE_4096_TABLE_LENGTH];


  /* fixed-point bit reversal tables */

    #define MIPSBITREVINDEXTABLE_FIXED_16_TABLE_LENGTH ((uint16_t)12)
    extern const uint16_t mipsBitRevIndexTable_fixed_16[MIPSBITREVINDEXTABLE_FIXED_16_TABLE_LENGTH];

    #define MIPSBITREVINDEXTABLE_FIXED_32_TABLE_LENGTH ((uint16_t)24)
    extern const uint16_t mipsBitRevIndexTable_fixed_32[MIPSBITREVINDEXTABLE_FIXED_32_TABLE_LENGTH];

    #define MIPSBITREVINDEXTABLE_FIXED_64_TABLE_LENGTH ((uint16_t)56)
    extern const uint16_t mipsBitRevIndexTable_fixed_64[MIPSBITREVINDEXTABLE_FIXED_64_TABLE_LENGTH];

    #define MIPSBITREVINDEXTABLE_FIXED_128_TABLE_LENGTH ((uint16_t)112)
    extern const uint16_t mipsBitRevIndexTable_fixed_128[MIPSBITREVINDEXTABLE_FIXED_128_TABLE_LENGTH];

    #define MIPSBITREVINDEXTABLE_FIXED_256_TABLE_LENGTH ((uint16_t)240)
    extern const uint16_t mipsBitRevIndexTable_fixed_256[MIPSBITREVINDEXTABLE_FIXED_256_TABLE_LENGTH];

    #define MIPSBITREVINDEXTABLE_FIXED_512_TABLE_LENGTH ((uint16_t)480)
    extern const uint16_t mipsBitRevIndexTable_fixed_512[MIPSBITREVINDEXTABLE_FIXED_512_TABLE_LENGTH];

    #define MIPSBITREVINDEXTABLE_FIXED_1024_TABLE_LENGTH ((uint16_t)992)
    extern const uint16_t mipsBitRevIndexTable_fixed_1024[MIPSBITREVINDEXTABLE_FIXED_1024_TABLE_LENGTH];

    #define MIPSBITREVINDEXTABLE_FIXED_2048_TABLE_LENGTH ((uint16_t)1984)
    extern const uint16_t mipsBitRevIndexTable_fixed_2048[MIPSBITREVINDEXTABLE_FIXED_2048_TABLE_LENGTH];

    #define MIPSBITREVINDEXTABLE_FIXED_4096_TABLE_LENGTH ((uint16_t)4032)
    extern const uint16_t mipsBitRevIndexTable_fixed_4096[MIPSBITREVINDEXTABLE_FIXED_4096_TABLE_LENGTH];

    extern const f32 realCoefA[8192];
    extern const f32 realCoefB[8192];

    extern const q31 realCoefAQ31[8192];
    extern const q31 realCoefBQ31[8192];

    extern const q15 realCoefAQ15[8192];
    extern const q15 realCoefBQ15[8192];

    extern const f32 Weights_128[256];
    extern const f32 cos_factors_128[128];

    extern const f32 Weights_512[1024];
    extern const f32 cos_factors_512[512];

    extern const f32 Weights_2048[4096];
    extern const f32 cos_factors_2048[2048];

    extern const f32 Weights_8192[16384];
    extern const f32 cos_factors_8192[8192];

    extern const q15 WeightsQ15_128[256];
    extern const q15 cos_factorsQ15_128[128];

    extern const q15 WeightsQ15_512[1024];
    extern const q15 cos_factorsQ15_512[512];

    extern const q15 WeightsQ15_2048[4096];
    extern const q15 cos_factorsQ15_2048[2048];

    extern const q15 WeightsQ15_8192[16384];
    extern const q15 cos_factorsQ15_8192[8192];

    extern const q31 WeightsQ31_128[256];
    extern const q31 cos_factorsQ31_128[128];

    extern const q31 WeightsQ31_512[1024];
    extern const q31 cos_factorsQ31_512[512];

    extern const q31 WeightsQ31_2048[4096];
    extern const q31 cos_factorsQ31_2048[2048];

    extern const q31 WeightsQ31_8192[16384];
    extern const q31 cos_factorsQ31_8192[8192];


    extern const q15 mipsRecipTableQ15[64];

    extern const q31 mipsRecipTableQ31[64];

  /* Tables for Fast Math Sine and Cosine */
    extern const f32 sinTable_f32[FAST_MATH_TABLE_SIZE + 1];

    extern const q31 sinTable_q31[FAST_MATH_TABLE_SIZE + 1];

    extern const q15 sinTable_q15[FAST_MATH_TABLE_SIZE + 1];


  /* Accurate scalar sqrt */
       extern const q31 sqrt_initial_lut_q31[32];

       extern const q15 sqrt_initial_lut_q15[16];

#if defined(MIPS_MATH_MSA)
       extern const q15 sqrtTable_Q15[256];
       extern const q31 sqrtTable_Q31[256];
       extern const unsigned char hwLUT[256];
#endif 

#if defined(MIPS_MATH_MSA)
       extern const f32 exp_tab[8];
       extern const f32 __logf_lut_f32[8];
#endif 


#ifdef   __cplusplus
}
#endif

#endif /*  MIPS_COMMON_TABLES_H */

