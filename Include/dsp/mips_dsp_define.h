/******************************************************************************
 * @file     mips_dsp_define.h
 * @brief    Utility functions for MIPS DSP development
 * @version  V1.0.0
 * @date     31 Augest 2023
 ******************************************************************************/
/*
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

#ifndef _MIPS_DSP_DEFINE_H
#define _MIPS_DSP_DEFINE_H 

typedef signed char v4q7 __attribute__ ((vector_size(4)));
typedef signed char v4i8 __attribute__ ((vector_size(4)));
typedef short v2q15 __attribute__ ((vector_size(4)));
typedef short v2i16 __attribute__ ((vector_size(4)));

typedef signed char q7;
typedef signed char i8;
typedef short q15;
typedef short i16;
typedef int q31;
typedef int i32;
typedef unsigned int ui32;
typedef long long a64;

typedef __attribute__((aligned(4))) union {
    v4q7  _v4q7;
    v2q15 _v2q15;
    v4i8  _v4i8;
    v2i16 _v2i16;
    q7    _q7[4];
    q15   _q15[2];
    i8    _i8[4];
    i16   _i16[2];
    q31   _q31;
    i32   _i32;
    ui32  _ui32;
} DSPREG32;

#if defined(__mips_dsp)
#define _mips_addq_ph __builtin_mips_addq_ph
#define _mips_addq_s_ph __builtin_mips_addq_s_ph
#define _mips_addq_s_w __builtin_mips_addq_s_w
#define _mips_addu_qb __builtin_mips_addu_qb
#define _mips_addu_s_qb __builtin_mips_addu_s_qb
#define _mips_subq_ph __builtin_mips_subq_ph
#define _mips_subq_s_ph __builtin_mips_subq_s_ph
#define _mips_subq_s_w __builtin_mips_subq_s_w
#define _mips_subu_qb __builtin_mips_subu_qb
#define _mips_subu_s_qb __builtin_mips_subu_s_qb
#define _mips_addsc __builtin_mips_addsc
#define _mips_addwc __builtin_mips_addwc
#define _mips_modsub __builtin_mips_modsub
#define _mips_raddu_w_qb __builtin_mips_raddu_w_qb
#define _mips_absq_s_ph __builtin_mips_absq_s_ph
#define _mips_absq_s_w __builtin_mips_absq_s_w
#define _mips_precrq_qb_ph __builtin_mips_precrq_qb_ph
#define _mips_precrq_ph_w __builtin_mips_precrq_ph_w
#define _mips_precrq_rs_ph_w __builtin_mips_precrq_rs_ph_w
#define _mips_precrqu_s_qb_ph __builtin_mips_precrqu_s_qb_ph
#define _mips_preceq_w_phl __builtin_mips_preceq_w_phl
#define _mips_preceq_w_phr __builtin_mips_preceq_w_phr
#define _mips_precequ_ph_qbl __builtin_mips_precequ_ph_qbl
#define _mips_precequ_ph_qbr __builtin_mips_precequ_ph_qbr
#define _mips_precequ_ph_qbla __builtin_mips_precequ_ph_qbla
#define _mips_precequ_ph_qbra __builtin_mips_precequ_ph_qbra
#define _mips_preceu_ph_qbl __builtin_mips_preceu_ph_qbl
#define _mips_preceu_ph_qbr __builtin_mips_preceu_ph_qbr
#define _mips_preceu_ph_qbla __builtin_mips_preceu_ph_qbla
#define _mips_preceu_ph_qbra __builtin_mips_preceu_ph_qbra
#define _mips_shll_qb __builtin_mips_shll_qb
#define _mips_shll_qb __builtin_mips_shll_qb
#define _mips_shll_ph __builtin_mips_shll_ph
#define _mips_shll_ph __builtin_mips_shll_ph
#define _mips_shll_s_ph __builtin_mips_shll_s_ph
#define _mips_shll_s_ph __builtin_mips_shll_s_ph
#define _mips_shll_s_w __builtin_mips_shll_s_w
#define _mips_shll_s_w __builtin_mips_shll_s_w
#define _mips_shrl_qb __builtin_mips_shrl_qb
#define _mips_shrl_qb __builtin_mips_shrl_qb
#define _mips_shra_ph __builtin_mips_shra_ph
#define _mips_shra_ph __builtin_mips_shra_ph
#define _mips_shra_r_ph __builtin_mips_shra_r_ph
#define _mips_shra_r_ph __builtin_mips_shra_r_ph
#define _mips_shra_r_w __builtin_mips_shra_r_w
#define _mips_shra_r_w __builtin_mips_shra_r_w
#define _mips_muleu_s_ph_qbl __builtin_mips_muleu_s_ph_qbl
#define _mips_muleu_s_ph_qbr __builtin_mips_muleu_s_ph_qbr
#define _mips_mulq_rs_ph __builtin_mips_mulq_rs_ph
#define _mips_muleq_s_w_phl __builtin_mips_muleq_s_w_phl
#define _mips_muleq_s_w_phr __builtin_mips_muleq_s_w_phr
#define _mips_dpau_h_qbl __builtin_mips_dpau_h_qbl
#define _mips_dpau_h_qbr __builtin_mips_dpau_h_qbr
#define _mips_dpsu_h_qbl __builtin_mips_dpsu_h_qbl
#define _mips_dpsu_h_qbr __builtin_mips_dpsu_h_qbr
#define _mips_dpaq_s_w_ph __builtin_mips_dpaq_s_w_ph
#define _mips_dpaq_sa_l_w __builtin_mips_dpaq_sa_l_w
#define _mips_dpsq_s_w_ph __builtin_mips_dpsq_s_w_ph
#define _mips_dpsq_sa_l_w __builtin_mips_dpsq_sa_l_w
#define _mips_mulsaq_s_w_ph __builtin_mips_mulsaq_s_w_ph
#define _mips_maq_s_w_phl __builtin_mips_maq_s_w_phl
#define _mips_maq_s_w_phr __builtin_mips_maq_s_w_phr
#define _mips_maq_sa_w_phl __builtin_mips_maq_sa_w_phl
#define _mips_maq_sa_w_phr __builtin_mips_maq_sa_w_phr
#define _mips_bitrev __builtin_mips_bitrev
#define _mips_insv __builtin_mips_insv
#define _mips_repl_qb __builtin_mips_repl_qb
#define _mips_repl_qb __builtin_mips_repl_qb
#define _mips_repl_ph __builtin_mips_repl_ph
#define _mips_repl_ph __builtin_mips_repl_ph
#define _mips_cmpu_eq_qb __builtin_mips_cmpu_eq_qb
#define _mips_cmpu_lt_qb __builtin_mips_cmpu_lt_qb
#define _mips_cmpu_le_qb __builtin_mips_cmpu_le_qb
#define _mips_cmpgu_eq_qb __builtin_mips_cmpgu_eq_qb
#define _mips_cmpgu_lt_qb __builtin_mips_cmpgu_lt_qb
#define _mips_cmpgu_le_qb __builtin_mips_cmpgu_le_qb
#define _mips_cmp_eq_ph __builtin_mips_cmp_eq_ph
#define _mips_cmp_lt_ph __builtin_mips_cmp_lt_ph
#define _mips_cmp_le_ph __builtin_mips_cmp_le_ph
#define _mips_pick_qb __builtin_mips_pick_qb
#define _mips_pick_ph __builtin_mips_pick_ph
#define _mips_packrl_ph __builtin_mips_packrl_ph
#define _mips_extr_w __builtin_mips_extr_w
#define _mips_extr_w __builtin_mips_extr_w
#define _mips_extr_r_w __builtin_mips_extr_r_w
#define _mips_extr_s_h __builtin_mips_extr_s_h
#define _mips_extr_rs_w __builtin_mips_extr_rs_w
#define _mips_extr_rs_w __builtin_mips_extr_rs_w
#define _mips_extr_s_h __builtin_mips_extr_s_h
#define _mips_extr_r_w __builtin_mips_extr_r_w
#define _mips_extp __builtin_mips_extp
#define _mips_extp __builtin_mips_extp
#define _mips_extpdp __builtin_mips_extpdp
#define _mips_extpdp __builtin_mips_extpdp
#define _mips_shilo __builtin_mips_shilo
#define _mips_shilo __builtin_mips_shilo
#define _mips_mthlip __builtin_mips_mthlip
#define _mips_wrdsp __builtin_mips_wrdsp
#define _mips_rddsp __builtin_mips_rddsp
#define _mips_lbux __builtin_mips_lbux
#define _mips_lhx __builtin_mips_lhx
#define _mips_lwx __builtin_mips_lwx
#define _mips_ldx __builtin_mips_ldx
#define _mips_bposge32 __builtin_mips_bposge32
#define _mips_madd __builtin_mips_madd
#define _mips_maddu __builtin_mips_maddu
#define _mips_msub __builtin_mips_msub
#define _mips_msubu __builtin_mips_msubu
#define _mips_mult __builtin_mips_mult
#define _mips_multu __builtin_mips_multu
#endif /* defined(__mips_dsp) */

#if defined(__mips_dspr2)
#define _mips_absq_s_qb __builtin_mips_absq_s_qb
#define _mips_addu_ph __builtin_mips_addu_ph
#define _mips_addu_s_ph __builtin_mips_addu_s_ph
#define _mips_adduh_qb __builtin_mips_adduh_qb
#define _mips_adduh_r_qb __builtin_mips_adduh_r_qb
#define _mips_append __builtin_mips_append
#define _mips_balign __builtin_mips_balign
#define _mips_cmpgdu_eq_qb __builtin_mips_cmpgdu_eq_qb
#define _mips_cmpgdu_lt_qb __builtin_mips_cmpgdu_lt_qb
#define _mips_cmpgdu_le_qb __builtin_mips_cmpgdu_le_qb
#define _mips_dpa_w_ph __builtin_mips_dpa_w_ph
#define _mips_dps_w_ph __builtin_mips_dps_w_ph
#define _mips_mul_ph __builtin_mips_mul_ph
#define _mips_mul_s_ph __builtin_mips_mul_s_ph
#define _mips_mulq_rs_w __builtin_mips_mulq_rs_w
#define _mips_mulq_s_ph __builtin_mips_mulq_s_ph
#define _mips_mulq_s_w __builtin_mips_mulq_s_w
#define _mips_mulsa_w_ph __builtin_mips_mulsa_w_ph
#define _mips_precr_qb_ph __builtin_mips_precr_qb_ph
#define _mips_precr_sra_ph_w __builtin_mips_precr_sra_ph_w
#define _mips_precr_sra_r_ph_w __builtin_mips_precr_sra_r_ph_w
#define _mips_prepend __builtin_mips_prepend
#define _mips_shra_qb __builtin_mips_shra_qb
#define _mips_shra_r_qb __builtin_mips_shra_r_qb
#define _mips_shra_qb __builtin_mips_shra_qb
#define _mips_shra_r_qb __builtin_mips_shra_r_qb
#define _mips_shrl_ph __builtin_mips_shrl_ph
#define _mips_shrl_ph __builtin_mips_shrl_ph
#define _mips_subu_ph __builtin_mips_subu_ph
#define _mips_subu_s_ph __builtin_mips_subu_s_ph
#define _mips_subuh_qb __builtin_mips_subuh_qb
#define _mips_subuh_r_qb __builtin_mips_subuh_r_qb
#define _mips_addqh_ph __builtin_mips_addqh_ph
#define _mips_addqh_r_ph __builtin_mips_addqh_r_ph
#define _mips_addqh_w __builtin_mips_addqh_w
#define _mips_addqh_r_w __builtin_mips_addqh_r_w
#define _mips_subqh_ph __builtin_mips_subqh_ph
#define _mips_subqh_r_ph __builtin_mips_subqh_r_ph
#define _mips_subqh_w __builtin_mips_subqh_w
#define _mips_subqh_r_w __builtin_mips_subqh_r_w
#define _mips_dpax_w_ph __builtin_mips_dpax_w_ph
#define _mips_dpsx_w_ph __builtin_mips_dpsx_w_ph
#define _mips_dpaqx_s_w_ph __builtin_mips_dpaqx_s_w_ph
#define _mips_dpaqx_sa_w_ph __builtin_mips_dpaqx_sa_w_ph
#define _mips_dpsqx_s_w_ph __builtin_mips_dpsqx_s_w_ph
#define _mips_dpsqx_sa_w_ph __builtin_mips_dpsqx_sa_w_ph
#endif /* defined(__mips_dspr2) */

// undefined builtin opcode

// mips_extrv_r_w
// mips_extrv_rs_w
// mips_extrv_s_h
// mips_mfhi
// mips_mflo
// mips_mthi
// mips_mtlo
// mips_shilov
// mips_shllv_s_ph
// mips_shllv_qb
// mips_shllv_s_w
// mips_shrav_ph
// mips_shrav_r_ph
// mips_shrav_qb
// mips_shrav_r_qb
// mips_shrav_r_w
// mips_shrlv_ph
// mips_shrlv_qb

#define mips_dsp_reinterpret_i32(x) \
__extension__(({union {i32 i; typeof(x) v;} $ = { .v = x }; $.i;}))
#define mips_dsp_reinterpret_ui32(x) \
__extension__(({union {ui32 u; typeof(x) v;} $ = { .v = x }; $.u;}))

#define mips_dsp_vreinterpret_v4q7(x) ((v4q7)(x))
#define mips_dsp_vreinterpret_v2q15(x) ((v2q15)(x))
#define mips_dsp_vreinterpret_v4i8(x) ((v4i8)(x))
#define mips_dsp_vreinterpret_v2i16(x) ((v2i16)(x))

#define mips_dsp_nth_i8_v4i8(x, n) (((DSPREG32*)&x)->_i8[n])
#define mips_dsp_nth_i16_v2i16(x, n) (((DSPREG32*)&x)->_i16[n])
#define mips_dsp_nth_q7_v4q7(x, n) (((DSPREG32*)&x)->_q7[n])
#define mips_dsp_nth_q15_v2q15(x, n) (((DSPREG32*)&x)->_q15[n])

#ifdef __cplusplus
extern "C"
{
#endif

static inline v4q7 mips_dsp_load_v4q7(const q7* src)
{
    return *((v4q7*)src);
}

static inline v2q15 mips_dsp_load_v2q15(const q15* src)
{
    return *((v2q15*)src);
}

static inline v4i8 mips_dsp_load_v2i8(const i8* src)
{
    return *((v4i8*)src);
}

static inline v2i16 mips_dsp_load_v2i16(const i16* src)
{
    return *((v2i16*)src);
}

static inline void mips_dsp_store_v4q7(q7* dst, v4q7 a)
{
    *((v4q7*)dst) = a;
}

static inline void mips_dsp_store_v2q15(q15* dst, v2q15 a)
{
    *((v2q15*)dst) = a;
}

static inline void mips_dsp_store_v4i8(i8* dst, v4i8 a)
{
    *((v4i8*)dst) = a;
}

static inline void mips_dsp_store_v2i16(i16* dst, v2i16 a)
{
    *((v2i16*)dst) = a;
}

static inline v4q7 mips_dsp_set_v4q7(q7 a,q7 b,q7 c,q7 d)
{
    DSPREG32 reg = {
        ._q7 = { a, b, c, d }
    };
    return reg._v4q7;
}

static inline v2q15 mips_dsp_set_v2q15(q15 a,q15 b)
{
    DSPREG32 reg = {
        ._q15= { a, b }
    };
    return reg._v2q15;
}

static inline v4i8 mips_dsp_set_v4i8(i8 a,i8 b,i8 c,i8 d)
{
    DSPREG32 reg = {
        ._i8 = { a, b, c, d }
    };
    return reg._v4i8;
}

static inline v2i16 mips_dsp_set_v2i16(i16 a,i16 b)
{
    DSPREG32 reg = {
        ._i16= { a, b }
    };
    return reg._v2i16;
}

// mips_replv_ph
static inline v2q15 _mips_replv_ph(q15 a)
{
    v2q15 b;
    asm("replv.ph %0, %1" 
        :"=r"(b)
        :"r"(a) 
        :);
    return b;
}

// mips_replv_qb 
static inline v4q7 _mips_replv_qb(q7 a)
{
    v4q7 b;
    asm("replv.qb %0, %1" 
        :"=r"(b)
        :"r"(a) 
        :);
    return b;
}

#ifdef   __cplusplus
}
#endif

#endif /* defined(_MIPS_DSP_DEFINE_H) */
