/******************************************************************************
 * @file     mips_msa_define.h
 * @brief    Utility functions for MIPS MSA development
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

#pragma once 

#if defined(__mips_msa)
#include <msa.h>


#ifdef __cplusplus
extern "C" {
#endif

/* typedef */
#include "mips_math_types.h"

/* define 64 bits vector types */
typedef signed char v8i8 __attribute__ ((vector_size(8), aligned(8)));
typedef unsigned char v8u8 __attribute__ ((vector_size(8), aligned(8)));
typedef short v4i16 __attribute__ ((vector_size(8), aligned(8)));
typedef unsigned short v4u16 __attribute__ ((vector_size(8), aligned(8)));
typedef int v2i32 __attribute__ ((vector_size(8), aligned(8)));
typedef unsigned int v2u32 __attribute__ ((vector_size(8), aligned(8)));
typedef long long v1i64 __attribute__ ((vector_size(8), aligned(8)));
typedef unsigned long long v1u64 __attribute__ ((vector_size(8), aligned(8)));
typedef float v2f32 __attribute__ ((vector_size(8), aligned(8)));
typedef double v1f64 __attribute__ ((vector_size(8), aligned(8)));

/* define fixed-point types alisa */
typedef v16i8 v16q7;
typedef v8i16 v8q15;
typedef v4i32 v4q31;
typedef v2i64 v2q63;

typedef __attribute__((aligned(8))) union {
	float f32[2];
	v2f32 f32x2;
} v2f32_union;

typedef __attribute__((aligned(16))) union {
	float f32[4];
	v4f32 f32x4;
} v4f32_union;

typedef __attribute__((aligned(16))) union {
	double f64[2];
	v2f64 f64x2;
} v2f64_union;

typedef __attribute__((aligned(16))) union {
	long long q63[2];
	v2q63 q63x2;
} v2q63_union;
typedef __attribute__((aligned(16))) union {
    q31 q31[4];
    v4q31 q31x4;
} v4q31_union;

typedef __attribute__((aligned(16))) union {
    q15 q15[8];
    v8q15 q15x8;
} v8q15_union;

/* typedef of vector * n */
typedef struct v8q15x2 {
  v8q15 val[2];
} v8q15x2;

typedef struct v4q31x2 {
  v4q31 val[2];
} v4q31x2;

typedef struct v4f32x2 {
  v4f32 val[2];
} v4f32x2;

typedef struct v2f64x2 {
  v2f64 val[2];
} v2f64x2;

typedef struct v2f32x2 {
  v2f32 val[2];
} v2f32x2;

typedef struct v2f64x4 {
  v2f64 val[4];
} v2f64x4;

#ifdef _MIPSEB
#define LANE_IMM0_1(x)	(0b1 - ((x) & 0b1))
#define LANE_IMM0_3(x)	(0b11 - ((x) & 0b11))
#define LANE_IMM0_7(x)	(0b111 - ((x) & 0b111))
#define LANE_IMM0_15(x)	(0b1111 - ((x) & 0b1111))
#else
#define LANE_IMM0_1(x)	((x) & 0b1)
#define LANE_IMM0_3(x)	((x) & 0b11)
#define LANE_IMM0_7(x)	((x) & 0b111)
#define LANE_IMM0_15(x)	((x) & 0b1111)
#endif

/* get_low, get_high */
#if (__mips == 64)
#define __GET_LOW(__TYPE, a)	((__TYPE)((v1u64)(__msa_copy_u_d((v2i64)(a), 0))))
#define __GET_HIGH(__TYPE, a)	((__TYPE)((v1u64)(__msa_copy_u_d((v2i64)(a), 1))))
#else
#define __GET_LOW(__TYPE, a)	((__TYPE)(((v2u64)(a))[0]))
#define __GET_HIGH(__TYPE, a)	((__TYPE)(((v2u64)(a))[1]))
#endif

/* v2f32 msa_get_low_f32(v4f32 __a) */
#define msa_get_low_f32(__a)	__GET_LOW(v2f32, __a)

/* v2u32 msa_get_low_u32(v4u32 __a) */
#define msa_get_low_u32(__a)  __GET_LOW(v2u32, __a)

/* v2f32 msa_get_high_f32(v4f32 __a) */
#define msa_get_high_f32(__a)	__GET_HIGH(v2f32, __a)

/* v2u32 msa_get_high_u32(v4u32 __a) */
#define msa_get_high_u32(__a)  __GET_HIGH(v2u32, __a)

/* v4f32 msa_combine_f32(v2f32 __a, v2f32 __b) */
#define msa_combine_f32(__a, __b)	__COMBINE_64_64(v4f32, __a, __b)

/* v16i8 msa_combine_s8 (v8i8 __a, v8i8 __b) */
#define msa_combine_s8(__a, __b)  __COMBINE_64_64(v16i8, __a, __b)

/* v8i16 msa_combine_s16(v4i16 __a, v4i16 __b) */
#define msa_combine_s16(__a, __b)  __COMBINE_64_64(v8i16, __a, __b)

/* v4i32 msa_combine_s32(v2i32 __a, v2i32 __b) */
#define msa_combine_s32(__a, __b)  __COMBINE_64_64(v4i32, __a, __b)

#define msa_combine_q7	msa_combine_s8
#define msa_combine_q15	msa_combine_s16
#define msa_combine_q31	msa_combine_s32

/* load & store */
#define msa_ld1q_s8(__a)	((v16i8)__msa_ld_b(__a, 0))
#define msa_ld1q_s16(__a)	((v8i16)__msa_ld_h(__a, 0))
#define msa_ld1q_s32(__a)	((v4i32)__msa_ld_w(__a, 0))
#define msa_ld1q_s64(__a)	((v2i64)__msa_ld_d(__a, 0))

#define msa_ld1q_u8(__a)	((v16u8)__msa_ld_b(__a, 0))
#define msa_ld1q_u16(__a)	((v8u16)__msa_ld_h(__a, 0))
#define msa_ld1q_u32(__a)	((v4u32)__msa_ld_w(__a, 0))
#define msa_ld1q_u64(__a)	((v2u64)__msa_ld_d(__a, 0))

#define msa_ld1q_q7	msa_ld1q_s8
#define msa_ld1q_q15	msa_ld1q_s16
#define msa_ld1q_q31	msa_ld1q_s32
#define msa_ld1q_q63	msa_ld1q_s64

#define msa_ld1q_f32(__a)	((v4f32)__msa_ld_w(__a, 0))
#define msa_ld1q_f64(__a)	((v2f64)__msa_ld_d(__a, 0))

#define msa_st1q_s8(__a, __b)	(__msa_st_b((v16i8)(__b), __a, 0))
#define msa_st1q_s16(__a, __b)	(__msa_st_h((v8i16)(__b), __a, 0))
#define msa_st1q_s32(__a, __b)	(__msa_st_w((v4i32)(__b), __a, 0))
#define msa_st1q_s64(__a, __b)	(__msa_st_d((v2i64)(__b), __a, 0))

#define msa_st1q_u8(__a, __b)	(__msa_st_b((v16i8)(__b), __a, 0))
#define msa_st1q_u16(__a, __b)	(__msa_st_h((v8i16)(__b), __a, 0))
#define msa_st1q_u32(__a, __b)	(__msa_st_w((v4i32)(__b), __a, 0))
#define msa_st1q_u64(__a, __b)	(__msa_st_d((v2i64)(__b), __a, 0))

#define msa_st1q_q7	msa_st1q_s8
#define msa_st1q_q15	msa_st1q_s16
#define msa_st1q_q31	msa_st1q_s32
#define msa_st1q_q63	msa_st1q_s64

#define msa_st1q_f32(__a, __b)	(__msa_st_w((v4i32)(__b),__a, 0))
#define msa_st1q_f64(__a, __b)	(__msa_st_d((v2i64)(__b),__a, 0))

#define msa_ld1_f32(__a)	(*((v2f32*)(__a)))
#define msa_st1_f32(__a, __b)	(*((v2f32*)(__a)) = __b)

/* multi load & store */
#define MSA_IMPL_LOAD2_STORE2(_Tp, _Tpv, _Tpvs, suffix, df, units)                         \
__extension__ extern __inline _Tp                                                         \
	__attribute__((__always_inline__, __gnu_inline__, __artificial__))                     \
	msa_ld2q_##suffix(suffix *a)                                                             \
{                                                                                          \
  _Tp _res;                                                                                \
  _Tpv v0 = msa_ld1q_##suffix(a);                                                          \
  _Tpv v1 = msa_ld1q_##suffix(a + units);                                                  \
  _res.val[0] = (_Tpv)__msa_pckev_##df((_Tpvs)v1, (_Tpvs)v0);                              \
  _res.val[1] = (_Tpv)__msa_pckod_##df((_Tpvs)v1, (_Tpvs)v0);                              \
   return _res;                                                                              \
}                                                                                          \
__extension__ extern __inline void                                                         \
	__attribute__((__always_inline__, __gnu_inline__, __artificial__))                     \
	msa_st2q_##suffix(suffix *ptr, _Tp a)                                                  \
{                                                                                          \
  msa_st1q_##suffix(ptr, (_Tpv)__msa_ilvr_##df((_Tpvs)a.val[1], (_Tpvs)a.val[0]));         \
  msa_st1q_##suffix(ptr + units, (_Tpv)__msa_ilvl_##df((_Tpvs)a.val[1], (_Tpvs)a.val[0])); \
}

MSA_IMPL_LOAD2_STORE2(v8q15x2, v8q15, v8i16, q15, h, 8)
MSA_IMPL_LOAD2_STORE2(v4q31x2, v4q31, v4i32, q31, w, 4)
MSA_IMPL_LOAD2_STORE2(v4f32x2, v4f32, v4i32, f32, w, 4)
MSA_IMPL_LOAD2_STORE2(v2f64x2, v2f64, v2i64, f64, d, 2)

/* bitwise and: __builtin_msa_and_v */
#define msa_andq_u8(__a, __b)  ((v16u8)__builtin_msa_and_v((v16u8)(__a), (v16u8)(__b)))
#define msa_andq_s8(__a, __b)  ((v16i8)__builtin_msa_and_v((v16u8)(__a), (v16u8)(__b)))
#define msa_andq_u16(__a, __b) ((v8u16)__builtin_msa_and_v((v16u8)(__a), (v16u8)(__b)))
#define msa_andq_s16(__a, __b) ((v8i16)__builtin_msa_and_v((v16u8)(__a), (v16u8)(__b)))
#define msa_andq_u32(__a, __b) ((v4u32)__builtin_msa_and_v((v16u8)(__a), (v16u8)(__b)))
#define msa_andq_s32(__a, __b) ((v4i32)__builtin_msa_and_v((v16u8)(__a), (v16u8)(__b)))
#define msa_andq_u64(__a, __b) ((v2u64)__builtin_msa_and_v((v16u8)(__a), (v16u8)(__b)))
#define msa_andq_s64(__a, __b) ((v2i64)__builtin_msa_and_v((v16u8)(__a), (v16u8)(__b)))

/* bitwise or: __builtin_msa_or_v */
#define msa_orrq_u8(__a, __b)  ((v16u8)__builtin_msa_or_v((v16u8)(__a), (v16u8)(__b)))
#define msa_orrq_s8(__a, __b)  ((v16i8)__builtin_msa_or_v((v16u8)(__a), (v16u8)(__b)))
#define msa_orrq_u16(__a, __b) ((v8u16)__builtin_msa_or_v((v16u8)(__a), (v16u8)(__b)))
#define msa_orrq_s16(__a, __b) ((v8i16)__builtin_msa_or_v((v16u8)(__a), (v16u8)(__b)))
#define msa_orrq_u32(__a, __b) ((v4u32)__builtin_msa_or_v((v16u8)(__a), (v16u8)(__b)))
#define msa_orrq_s32(__a, __b) ((v4i32)__builtin_msa_or_v((v16u8)(__a), (v16u8)(__b)))
#define msa_orrq_u64(__a, __b) ((v2u64)__builtin_msa_or_v((v16u8)(__a), (v16u8)(__b)))
#define msa_orrq_s64(__a, __b) ((v2i64)__builtin_msa_or_v((v16u8)(__a), (v16u8)(__b)))

/* bitwise not: v16u8 __builtin_msa_xori_b (v16u8, 0xff) */
#define msa_mvnq_u8(__a)  ((v16u8)__builtin_msa_xori_b((v16u8)(__a), 0xFF))
#define msa_mvnq_s8(__a)  ((v16i8)__builtin_msa_xori_b((v16u8)(__a), 0xFF))
#define msa_mvnq_u16(__a) ((v8u16)__builtin_msa_xori_b((v16u8)(__a), 0xFF))
#define msa_mvnq_s16(__a) ((v8i16)__builtin_msa_xori_b((v16u8)(__a), 0xFF))
#define msa_mvnq_u32(__a) ((v4u32)__builtin_msa_xori_b((v16u8)(__a), 0xFF))
#define msa_mvnq_s32(__a) ((v4i32)__builtin_msa_xori_b((v16u8)(__a), 0xFF))
#define msa_mvnq_u64(__a) ((v2u64)__builtin_msa_xori_b((v16u8)(__a), 0xFF))
#define msa_mvnq_s64(__a) ((v2i64)__builtin_msa_xori_b((v16u8)(__a), 0xFF))

/* fill */
#define msa_dup_n_f32(__a)	((v2f32){__a, __a})

#define msa_dupq_n_s8(__a)  (__builtin_msa_fill_b((int32_t)(__a)))
#define msa_dupq_n_s16(__a) (__builtin_msa_fill_h((int32_t)(__a)))
#define msa_dupq_n_s32(__a) (__builtin_msa_fill_w((int32_t)(__a)))
#define msa_dupq_n_s64(__a) (__builtin_msa_fill_d((int64_t)(__a)))
#define msa_dupq_n_u8(__a)  ((v16u8)__builtin_msa_fill_b((int32_t)(__a)))
#define msa_dupq_n_u16(__a) ((v8u16)__builtin_msa_fill_h((int32_t)(__a)))
#define msa_dupq_n_u32(__a) ((v4u32)__builtin_msa_fill_w((int32_t)(__a)))
#define msa_dupq_n_u64(__a) ((v2u64)__builtin_msa_fill_d((int64_t)(__a)))
#define msa_dupq_n_f32(__a)	((v4f32){__a, __a, __a, __a})
#define msa_dupq_n_f64(__a) ((v2f64){__a, __a})

#define msa_dupq_n_q7 msa_dupq_n_s8
#define msa_dupq_n_q15 msa_dupq_n_s16
#define msa_dupq_n_q31 msa_dupq_n_s32

/* get */
#define msa_get_lane_f32(__a, __b)	((float)(__a)[LANE_IMM0_1(__b)])
#define msa_get_lane_f64(__a, __b)  ((double)(__a)[LANE_IMM0_1(__b)])
#define msa_getq_lane_f32(__a, __b)	((float)(__a)[LANE_IMM0_3(__b)])
#define msa_getq_lane_f64(__a, __b) ((double)(__a)[LANE_IMM0_1(__b)])
#define msa_get_lane_u32(__a, __b)       ((uint32_t)(__a)[LANE_IMM0_1(__b)])
#define msa_getq_lane_s16(__a, __b)	((int16_t)(__a)[LANE_IMM0_7(__b)])
#define msa_getq_lane_s32(__a, __b)  ((int32_t)(__a)[LANE_IMM0_3(__b)])

/* Store the value of the element with the index __c in vector __a to the given memory address. */
#define msa_st1_lane_f32(__a, __b, __c)  (*((float*)(__a)) = __b[__c])
#define msa_st1_lane_f64(__a, __b, __c)  (*((double*)(__a)) = __b[__c])
#define msa_st1q_lane_s8(__a, __b, __c)  (*((int8_t*)(__a)) = (int8_t)__builtin_msa_copy_s_b(__b, __c))
#define msa_st1q_lane_s16(__a, __b, __c) (*((int16_t*)(__a)) = (int16_t)__builtin_msa_copy_s_h(__b, __c))
#define msa_st1q_lane_s32(__a, __b, __c) (*((int32_t*)(__a)) = __builtin_msa_copy_s_w(__b, __c))
#define msa_st1q_lane_s64(__a, __b, __c) (*((int64_t*)(__a)) = __builtin_msa_copy_s_d(__b, __c))
#define msa_st1q_lane_f32(__a, __b, __c) (*((float*)(__a)) = __b[__c])
#define msa_st1q_lane_f64(__a, __b, __c) (*((double*)(__a)) = __b[__c])

/* Maximum values between corresponding elements in the two vectors are written to the returned vector. */
#define msa_maxq_s8(__a, __b)  (__builtin_msa_max_s_b(__a, __b))
#define msa_maxq_s16(__a, __b) (__builtin_msa_max_s_h(__a, __b))
#define msa_maxq_s32(__a, __b) (__builtin_msa_max_s_w(__a, __b))
#define msa_maxq_s64(__a, __b) (__builtin_msa_max_s_d(__a, __b))
#define msa_maxq_u8(__a, __b)  ((v16u8)__builtin_msa_max_u_b(__a, __b))
#define msa_maxq_u16(__a, __b) ((v8u16)__builtin_msa_max_u_h(__a, __b))
#define msa_maxq_u32(__a, __b) ((v4u32)__builtin_msa_max_u_w(__a, __b))
#define msa_maxq_u64(__a, __b) ((v2u64)__builtin_msa_max_u_d(__a, __b))
#define msa_maxq_f32(__a, __b) (__builtin_msa_fmax_w(__a, __b))
#define msa_maxq_f64(__a, __b) (__builtin_msa_fmax_d(__a, __b))

/* Minimum values between corresponding elements in the two vectors are written to the returned vector. */
#define msa_minq_s8(__a, __b)  (__builtin_msa_min_s_b(__a, __b))
#define msa_minq_s16(__a, __b) (__builtin_msa_min_s_h(__a, __b))
#define msa_minq_s32(__a, __b) (__builtin_msa_min_s_w(__a, __b))
#define msa_minq_s64(__a, __b) (__builtin_msa_min_s_d(__a, __b))
#define msa_minq_u8(__a, __b)  ((v16u8)__builtin_msa_min_u_b(__a, __b))
#define msa_minq_u16(__a, __b) ((v8u16)__builtin_msa_min_u_h(__a, __b))
#define msa_minq_u32(__a, __b) ((v4u32)__builtin_msa_min_u_w(__a, __b))
#define msa_minq_u64(__a, __b) ((v2u64)__builtin_msa_min_u_d(__a, __b))
#define msa_minq_f32(__a, __b) (__builtin_msa_fmin_w(__a, __b))
#define msa_minq_f64(__a, __b) (__builtin_msa_fmin_d(__a, __b))

/* reinterpret */
/* type_from_type */
#define msa_reinterpret(_typ, vec)	((_typ)(vec))
#define msa_reinterpretq_f32_s32 msa_reinterpret(v4f32, vec)
#define msa_reinterpretq_s32_f32 msa_reinterpret(v4i32, vec)
#define msa_reinterpretq_s32_u32 msa_reinterpret(v4i32, vec)
#define msa_reinterpretq_u32_f32 msa_reinterpret(v4u32, vec)
#define msa_reinterpretq_u8_u32 msa_reinterpret(v16u8, vec)

/* get high/low half bit of vector elements*/
#define msa_get_high_half_q15(a) __msa_hadd_u_h(a, __msa_ldi_b(0));
#define msa_get_low_half_q15(a) __msa_hadd_u_h(__msa_ldi_b(0), a);
#define msa_get_high_half_q31(a) __msa_hadd_u_w(a, __msa_ldi_w(0));
#define msa_get_low_half_q31(a) __msa_hadd_u_w(__msa_ldi_w(0),a);

/* hadd_u */
#define msa_hadd_u16 ((v8u16) __builtin_msa_hadd_u_h (v16u8, v16u8))
#define msa_hadd_u32 ((v4u32) __builtin_msa_hadd_u_w (v8u16, v8u16))
#define msa_hadd_u64 ((v2u64) __builtin_msa_hadd_u_d (v4u32, v4u32))

/* base calculate */
// interger
#define msa_addq_s8 __msa_addv_b
#define msa_subq_s8 __msa_subv_b
#define msa_mulq_s8 __msa_mulv_b
#define msa_divq_s8 __msa_div_s_b

#define msa_addq_s16 __msa_addv_h
#define msa_subq_s16 __msa_subv_h
#define msa_mulq_s16 __msa_mulv_h
#define msa_divq_s16 __msa_div_s_h

#define msa_addq_s32 __msa_addv_w
#define msa_subq_s32 __msa_subv_w
#define msa_mulq_s32 __msa_mulv_w
#define msa_divq_s32 __msa_div_s_w

#define msa_addq_s64 __msa_addv_d
#define msa_subq_s64 __msa_subv_d
#define msa_mulq_s64 __msa_mulv_d
#define msa_divq_s64 __msa_div_s_d

#define msa_mulq_u16(a,b) ((v8u16)__msa_mulv_h((v8i16)a,(v8i16)b))
#define msa_mulq_u32(a,b) ((v4u32)__msa_mulv_w((v4i32)a,(v4i32)b))

#define msa_addq_s_s8 __msa_adds_s_b
#define msa_addq_s_s16 __msa_adds_s_h
#define msa_addq_s_s32 __msa_adds_s_w
#define msa_addq_s_s64 __msa_adds_s_d

#define msa_subq_s_s8 __msa_subs_s_b
#define msa_subq_s_s16 __msa_subs_s_h
#define msa_subq_s_s32 __msa_subs_s_w
#define msa_subq_s_s64 __msa_subs_s_d

#define msa_absq_s8(x) __msa_add_a_b(x, __msa_fill_b(0))
#define msa_absq_s16(x) __msa_add_a_h(x, __msa_fill_h(0))
#define msa_absq_s32(x) __msa_add_a_w(x, __msa_fill_w(0))
#define msa_absq_s64(x) __msa_add_a_d(x, __msa_fill_d(0))

#define msa_absq_s_s8(x) __msa_adds_a_b(x, __msa_fill_b(0))
#define msa_absq_s_s16(x) __msa_adds_a_h(x, __msa_fill_h(0))
#define msa_absq_s_s32(x) __msa_adds_a_w(x, __msa_fill_w(0))
#define msa_absq_s_s64(x) __msa_adds_a_d(x, __msa_fill_d(0))

#define msa_addq_u16(a, b)    ((v8u16)__msa_addv_h((v8i16)(a), (v8i16)(b)))
#define msa_addq_u32(a, b)    ((v4u32)__msa_addv_w((v4i32)(a), (v4i32)(b)))
#define msa_addq_u64(a, b)    ((v2u64)__msa_addv_d((v2i64)(a), (v2i64)(b)))

// fixed-point
#define msa_addq_q7 msa_addq_s8
#define msa_subq_q7 msa_subq_s8

#define msa_addq_q15 msa_addq_s16
#define msa_subq_q15 msa_subq_s16

#define msa_addq_q31 msa_addq_s32
#define msa_subq_q31 msa_subq_s32

#define msa_addq_q63 msa_addq_s64
#define msa_subq_q63 msa_subq_s64

#define msa_addq_s_q7 msa_addq_s_s8
#define msa_addq_s_q15 msa_addq_s_s16
#define msa_addq_s_q31 msa_addq_s_s32
#define msa_addq_s_q63 msa_addq_s_s64

#define msa_subq_s_q7 msa_subq_s_s8
#define msa_subq_s_q15 msa_subq_s_s16
#define msa_subq_s_q31 msa_subq_s_s32
#define msa_subq_s_q63 msa_subq_s_s64

#define msa_maddq_q15 __msa_madd_q_h
#define msa_maddq_q31 __msa_madd_q_w

#define msa_maddq_r_q15 __msa_maddr_q_h
#define msa_maddq_r_q31 __msa_maddr_q_w

#define msa_msubq_q15 __msa_msub_q_h
#define msa_msubq_q31 __msa_msub_q_w

#define msa_msubq_r_q15 __msa_msubr_q_h
#define msa_msubq_r_q31 __msa_msubr_q_w

#define msa_mulq_q15 __msa_mul_q_h
#define msa_mulq_q31 __msa_mul_q_w

#define msa_mulq_r_q15 __msa_mulr_q_h
#define msa_mulq_r_q31 __msa_mulr_q_w

#define msa_mulhq_q15(a, b) msa_get_high_half_q15(msa_mulq_q15(a, b))
#define msa_mullbq_q15(a, b) msa_get_low_half_q15(msa_mulq_q15(a, b))
#define msa_mulhq_q31(a, b) msa_get_high_half_q31(msa_mulq_q31(a, b))
#define msa_mullbq_q31(a, b) msa_get_low_half_q31(msa_mulq_q31(a, b))

#define msa_absq_q7  msa_absq_s8
#define msa_absq_q15 msa_absq_s16
#define msa_absq_q31 msa_absq_s32
#define msa_absq_q63 msa_absq_s64

#define msa_absq_s_q7  msa_absq_s_s8
#define msa_absq_s_q15 msa_absq_s_s16
#define msa_absq_s_q31 msa_absq_s_s32
#define msa_absq_s_q63 msa_absq_s_s64

// float
#define msa_addq_f32 __msa_fadd_w
#define msa_subq_f32 __msa_fsub_w
#define msa_mulq_f32 __msa_fmul_w
#define msa_divq_f32 __msa_fdiv_w

#define msa_addq_f64 __msa_fadd_d
#define msa_subq_f64 __msa_fsub_d
#define msa_mulq_f64 __msa_fmul_d
#define msa_divq_f64 __msa_fdiv_d

#define msa_maddq_f32 __msa_fmadd_w
#define msa_msubq_f32 __msa_fmsub_w

#define msa_maddq_f64 __msa_fmadd_d
#define msa_msubq_f64 __msa_fmsub_d

#define msa_mla_f32(acc, a, b)	(acc + a * b) 
#define msa_mls_f32(acc, a, b)	(acc - a * b) 


// with immediate
#define msa_addqi_f32(__a, __b) msa_addq_f32(__a, msa_dupq_n_f32(__b))
#define msa_subqi_f32(__a, __b) msa_subq_f32(__a, msa_dupq_n_f32(__b))
#define msa_mulqi_f32(__a, __b) msa_mulq_f32(__a, msa_dupq_n_f32(__b))
#define msa_divqi_f32(__a, __b) msa_divq_f32(__a, msa_dupq_n_f32(__b))

#define msa_maddqi_f32(__a, __b, __c) msa_maddq_f32(__a, __b, msa_dupq_n_f32(__c))
#define msa_msubqi_f32(__a, __b, __c) msa_msubq_f32(__a, __b, msa_dupq_n_f32(__c))

#define msa_addqi_f64(__a, __b) msa_addq_f64(__a, msa_dupq_n_f64(__b))
#define msa_subqi_f64(__a, __b) msa_subq_f64(__a, msa_dupq_n_f64(__b))
#define msa_mulqi_f64(__a, __b) msa_mulq_f64(__a, msa_dupq_n_f64(__b))
#define msa_divqi_f64(__a, __b) msa_divq_f64(__a, msa_dupq_n_f64(__b))

#define msa_maddqi_f64(__a, __b, __c) msa_maddq_f64(__a, __b, msa_dupq_n_f64(__c))
#define msa_msubqi_f64(__a, __b, __c) msa_msubq_f64(__a, __b, msa_dupq_n_f64(__c))

#define msa_absq_f32(X) ((v4f32)__msa_bclri_w((v4u32)(X), 31))
#define msa_absq_f64(X) ((v2f64)__msa_bclri_d((v2u64)(X), 63))

/* Absolute difference */
#define msa_adbq_f32(a, b) msa_absq_f32(msa_subq_f32(a, b))
#define msa_adbq_f64(a, b) msa_absq_f64(msa_subq_f64(a, b))

/* cntq */
#define msa_cntq_s8           __msa_pcnt_b
#define msa_cntq_s16          __msa_pcnt_h
#define msa_cntq_s32          __msa_pcnt_w
#define msa_cntq_s64          __msa_pcnt_d

/* paddlq */
/* v8u16 msa_paddlq_u8(v16u8 __a) */
#define msa_paddlq_u8(__a)  (__msa_hadd_u_h(__a, __a))

/* v8i16 msa_paddlq_s8(v16i8 __a) */
#define msa_paddlq_s8(__a)  (__msa_hadd_s_h(__a, __a))

/* v4u32 msa_paddlq_u16 (v8u16 __a)*/
#define msa_paddlq_u16(__a)  (__msa_hadd_u_w(__a, __a))

/* v4i32 msa_paddlq_s16 (v8i16 __a)*/
#define msa_paddlq_s16(__a)  (__msa_hadd_s_w(__a, __a))

/* v2u64 msa_paddlq_u32(v4u32 __a) */
#define msa_paddlq_u32(__a)  (__msa_hadd_u_d(__a, __a))

/* v2i64 msa_paddlq_s32(v4i32 __a) */
#define msa_paddlq_s32(__a)  (__msa_hadd_s_d(__a, __a))

/* 128-bits*/
#define msa_addvq_f64(a)            \
__extension__({ \
	f64 _res; \
	v2f64_union _ret = { \
		.f64x2 = a; \
	} \
	_res = _ret.f64[0] +_ret.f64[1]; \
	_res;                            \
})

/* 64-bits */
#define msa_mul_f32(a, b)	(v2f32)(a * b) 

#define msa_padd_f32(a, b)	\
__extension__({	\
	v2f32_union _res;	\
	v2f32_union padd_a = {	\
		.f32x2 = a;	\
	}	\
	v2f32_union padd_b = {	\
		.f32x2 = b;	\
	}	\
	_res.f32[0] = padd_a.f32[0] + padd_a.f32[1];	\
	_res.f32[1] = padd_b.f32[0] + padd_b.f32[1]; \
	_res.f32x2;                              \
})

#define msa_padds_f32(a) \
__extension__({ \
	f32 _res; \
	v2f32_union padds_a = { \
		.f32x2 = a; \
	} \
	_res.f32 = { \
		padds_a.f32[0] + padds_a.f32[1]; \
	} \
	_res.f32; \
})

#define msa_pmax_f32(a, b) \
__extension__({ \
	v2f32_union _res;  \
	v2f32_union pmax_a = { \
		.f32x2 = a; \
	} \
	v2f32_union pmax_b = { \
		.f32x2 = b; \
	} \
	_res.f32x2 = { \
		pmax_a.f32[0] > pmax_a.f32[1] ? pmax_a.f32[0] : pmax_a.f32[1]; \
		pmax_b.f32[0] > pmax_b.f32[1] ? pmax_b.f32[0] : pmax_b.f32[1]; \
	} \
	_res.f32x2; \
})

#define msa_pmin_f32(a, b) \
__extension__({ \
	v2f32_union _res; \
	v2f32_union pmin_a = { \
		.f32x2 = a; \
	} \
	v2f32_union pmin_b = { \
		.f32x2 = b; \
	}; \
	_res.f32x2 = { \
		pmin_a.f32[0] < pmin_a.f32[1] ? pmin_a.f32[0] : pmin_a.f32[1]; \
		pmin_b.f32[0] < pmin_b.f32[1] ? pmin_b.f32[0] : pmin_b.f32[1]; \
	} \
	_res.f32x2; \
}) \

#define msa_pmin_u32(a,b) \
__extension__({ \
	v2u32_union _res; \
	v2u32_union pmin_a = { \
		.u32x2 = a; \
	}; \
	v2u32_union pmin_b = { \
		.u32x2 = b; \
	}; \
	_res.u32x2 = { \
		pmin_a.u32[0] < pmin_a.u32[1] ? pmin_a.u32[0] : pmin_a.u32[1]; \
		pmin_b.u32[0] < pmin_b.u32[1] ? pmin_b.u32[0] : pmin_b.u32[1]; \
	} \
	_res.u32x2; \
}) \
/* mov */
#define msa_set_lane_f32(a, v, lane) \
__extension__({ \
	v2f32_union res_v = { \
		.f32x2 = v; \
	} \
	res_v.f32[lane] = a; \
	res_v.f32x2; \
}) \

#define msa_setq_lane_f32(a, v, lane) \
__extension__({ \
	v4f32_union res_v = { \
		.f32x4 = v; \
	} \
	res_v.f32[lane] = a; \
	res_v.f32x4; \
}) \

#define msa_setq_lane_f64(a, v, lane) \
__extension__({ \
	v2f64_union res_v = { \
		.f64x2 = v; \
	} \
	res_v.f64[lane] = a; \
	res_v.f64x2; \
}) \

#define msa_setq_lane_s32(a, v, lane) \
__extension__({ \
	v4q31_union res_v = { \
		.q31x4 = v; \
	} \
	res_v.q31[lane] = a; \
	res_v.q31x4; \
}) \

/* negate */

/* compare */
#define msa_cltq_f32(__a, __b) ((v4u32)__msa_fclt_w((v4f32)(__a), (v4f32)(__b)))

#define msa_cgtq_f32(__a, __b) ((v4u32)__msa_fclt_w((v4f32)(__b), (v4f32)(__a)))

#define msa_ceqq_f32(__a, __b) ((v4u32)__builtin_msa_fceq_w((v4f32)(__a), (v4f32)(__b)))

/* bitwise xor: __builtin_msa_xor_v */
#define msa_eorq_u8(__a, __b)  ((v16u8)__builtin_msa_xor_v((v16u8)(__a), (v16u8)(__b)))
#define msa_eorq_s8(__a, __b)  ((v16i8)__builtin_msa_xor_v((v16u8)(__a), (v16u8)(__b)))
#define msa_eorq_u16(__a, __b) ((v8u16)__builtin_msa_xor_v((v16u8)(__a), (v16u8)(__b)))
#define msa_eorq_s16(__a, __b) ((v8i16)__builtin_msa_xor_v((v16u8)(__a), (v16u8)(__b)))
#define msa_eorq_u32(__a, __b) ((v4u32)__builtin_msa_xor_v((v16u8)(__a), (v16u8)(__b)))
#define msa_eorq_s32(__a, __b) ((v4i32)__builtin_msa_xor_v((v16u8)(__a), (v16u8)(__b)))

/* Shift Left Logical: shl -> ri = ai << bi; */
#define msa_shlq_u8(__a, __b)  ((v16u8)__builtin_msa_sll_b((v16i8)(__a), (v16i8)(__b)))
#define msa_shlq_s8(__a, __b)  ((v16i8)__builtin_msa_sll_b((v16i8)(__a), (v16i8)(__b)))
#define msa_shlq_u16(__a, __b) ((v8u16)__builtin_msa_sll_h((v8i16)(__a), (v8i16)(__b)))
#define msa_shlq_s16(__a, __b) ((v8i16)__builtin_msa_sll_h((v8i16)(__a), (v8i16)(__b)))
#define msa_shlq_u32(__a, __b) ((v4u32)__builtin_msa_sll_w((v4i32)(__a), (v4i32)(__b)))
#define msa_shlq_s32(__a, __b) ((v4i32)__builtin_msa_sll_w((v4i32)(__a), (v4i32)(__b)))
#define msa_shlq_u64(__a, __b) ((v2u64)__builtin_msa_sll_d((v2i64)(__a), (v2i64)(__b)))
#define msa_shlq_s64(__a, __b) ((v2i64)__builtin_msa_sll_d((v2i64)(__a), (v2i64)(__b)))

#define msa_shlq_q7  msa_shlq_s8
#define msa_shlq_q15  msa_shlq_s16
#define msa_shlq_q31  msa_shlq_s32
#define msa_shlq_q63  msa_shlq_s64

/* cvttruncq, cvtfintq, cvtfq */
#define msa_cvttruncq_u32_f32 __builtin_msa_ftrunc_u_w
#define msa_cvttruncq_s32_f32 __builtin_msa_ftrunc_s_w
#define msa_cvttruncq_u64_f64 __builtin_msa_ftrunc_u_d
#define msa_cvttruncq_s64_f64 __builtin_msa_ftrunc_s_d
#define msa_cvtfintq_f32_u32  __builtin_msa_ffint_u_w
#define msa_cvtfintq_f32_s32  __builtin_msa_ffint_s_w
#define msa_cvtfintq_f64_u64  __builtin_msa_ffint_u_d
#define msa_cvtfintq_f64_s64  __builtin_msa_ffint_s_d
#define msa_cvtfq_f32_f64     __builtin_msa_fexdo_w
#define msa_cvtflq_f64_f32    __builtin_msa_fexupr_d
#define msa_cvtfhq_f64_f32    __builtin_msa_fexupl_d

#define msa_ftq_q15_f32(__a, __b)  ((v8i16)__builtin_msa_ftq_h((v4f32)(__a), (v4f32)(__b)))
#define msa_ftq_q31_f64(__a, __b)  ((v4i32)__builtin_msa_ftq_w((v2f64)(__a), (v2f64)(__b)))

#define msa_ffql_f32_q15(__a)  ((v4f32)__builtin_msa_ffql_w((v8i16)(__a)))
#define msa_ffql_f64_q31(__a)  ((v2f64)__builtin_msa_ffql_d((v4i32)(__a)))
#define msa_ffqr_f32_q15(__a)  ((v4f32)__builtin_msa_ffqr_w((v8i16)(__a)))
#define msa_ffqr_f64_q31(__a)  ((v2f64)__builtin_msa_ffqr_d((v4i32)(__a)))

/* sqrtq, rsqrtq */
#define msa_sqrtq_f32         __msa_fsqrt_w
#define msa_sqrtq_f64         __msa_fsqrt_d
#define msa_rsqrtq_f32        __msa_frsqrt_w
#define msa_rsqrtq_f64        __msa_frsqrt_d

#define msa_rsqrt_f32 msa_get_low_f32(           \
	msa_rsqrtq_f32(                              \
		msa_combine_f32(a, msa_dup_n_f32(1.0f)), \
		msa_combine_f32(b, msa_dup_n_f32(1.0f))))

/* reciprocals */
#define msa_recpeq_f32        __msa_frcp_w
#define msa_recpsq_f32(a, b)  (__msa_fsub_w(msa_dupq_n_f32(2.0f), __msa_fmul_w(a, b)))

#define msa_recpe_f32(a, b) msa_get_low_f32(     \
	msa_recpeq_f32(                              \
		msa_combine_f32(a, msa_dup_n_f32(1.0f)), \
		msa_combine_f32(b, msa_dup_n_f32(1.0f))))

#define msa_recps_f32(a, b) msa_get_low_f32(     \
	msa_recpsq_f32(                              \
		msa_combine_f32(a, msa_dup_n_f32(1.0f)), \
		msa_combine_f32(b, msa_dup_n_f32(1.0f))))

#define msa_recpeq_f64        __msa_frcp_d
#define msa_recpsq_f64(a, b)  (__msa_fsub_d(msa_dupq_n_f64(2.0f), __msa_fmul_d(a, b)))

/* RSQRTS */
#define msa_vrsqrtsq_f32(a, b)                                     \
msa_divq_f32(msa_subq_f32(msa_dupq_f32(3.0f), msa_mulq_f32(a, b)), \
			 msa_dupq_f32(2.0f))

#define msa_vrsqrtsq_f64(a, b)                                     \
msa_divq_f64(msa_subq_f64(msa_dupq_f64(3.0f), msa_mulq_f64(a, b)), \
			 msa_dupq_f64(2.0f))

#define msa_vrsqrts_f32(a, b) msa_get_low_f32(   \
	msa_vrsqrtsq_f32(                            \
		msa_combine_f32(a, msa_dup_n_f32(1.0f)), \
		msa_combine_f32(b, msa_dup_n_f32(1.0f))))

/* bit select */
#define msa_bselq_f32(__a, __b, __c)	\
	msa_reinterpret(v4f32, __msa_bsel_v(	\
	(msa_reinterpret(v16u8), __a),	\
	(msa_reinterpret(v16u8), __b),	\
	(msa_reinterpret(v16u8), __c),	\
))

#define msa_bselq_u32(__a, __b, __c) \
    msa_reinterpret(v4u32, __msa_bsel_v( \
        (msa_reinterpret(v16u8), __a), \
        (msa_reinterpret(v16u8), __b), \
        (msa_reinterpret(v16u8), __c), \
))

/* pair implement with ld2q/st2q */
#define MSA_IMPL_PADDQ(_Tpv, _Tpvs, suffix, df)                                \
__extension__ extern __inline _Tpv                                            \
	__attribute__((__always_inline__, __gnu_inline__, __artificial__))        \
	msa_paddq_##suffix(_Tpv a, _Tpv b)                                        \
{                                                                             \
  return (_Tpv)msa_addq_##suffix((_Tpv)__msa_pckev_##df((_Tpvs)b, (_Tpvs)a),  \
								 (_Tpv)__msa_pckod_##df((_Tpvs)b, (_Tpvs)a)); \
}
MSA_IMPL_PADDQ(v4f32, v4i32, f32, w)
MSA_IMPL_PADDQ(v2f64, v2i64, f64, d)

/* Immediate Shift Right: shr -> ri = ai >> imm; */
#define msa_shrq_n_u8(__a, __imm)  ((v16u8)__builtin_msa_srli_b((v16i8)(__a), __imm))
#define msa_shrq_n_s8(__a, __imm)  ((v16i8)__builtin_msa_srai_b((v16i8)(__a), __imm))
#define msa_shrq_n_u16(__a, __imm) ((v8u16)__builtin_msa_srli_h((v8i16)(__a), __imm))
#define msa_shrq_n_s16(__a, __imm) ((v8i16)__builtin_msa_srai_h((v8i16)(__a), __imm))
#define msa_shrq_n_u32(__a, __imm) ((v4u32)__builtin_msa_srli_w((v4i32)(__a), __imm))
#define msa_shrq_n_s32(__a, __imm) ((v4i32)__builtin_msa_srai_w((v4i32)(__a), __imm))
#define msa_shrq_n_u64(__a, __imm) ((v2u64)__builtin_msa_srli_d((v2i64)(__a), __imm))
#define msa_shrq_n_s64(__a, __imm) ((v2i64)__builtin_msa_srai_d((v2i64)(__a), __imm))

#define msa_shrq_n_q7	msa_shrq_n_s8
#define msa_shrq_n_q15	msa_shrq_n_s16
#define msa_shrq_n_q31	msa_shrq_n_s32

/* Immediate Shift Right Rounded: shr -> ri = ai >> (rounded)imm; */
#define msa_rshrq_n_u8(__a, __imm)  ((v16u8)__builtin_msa_srlri_b((v16i8)(__a), __imm))
#define msa_rshrq_n_s8(__a, __imm)  ((v16i8)__builtin_msa_srari_b((v16i8)(__a), __imm))
#define msa_rshrq_n_u16(__a, __imm) ((v8u16)__builtin_msa_srlri_h((v8i16)(__a), __imm))
#define msa_rshrq_n_s16(__a, __imm) ((v8i16)__builtin_msa_srari_h((v8i16)(__a), __imm))
#define msa_rshrq_n_u32(__a, __imm) ((v4u32)__builtin_msa_srlri_w((v4i32)(__a), __imm))
#define msa_rshrq_n_s32(__a, __imm) ((v4i32)__builtin_msa_srari_w((v4i32)(__a), __imm))
#define msa_rshrq_n_u64(__a, __imm) ((v2u64)__builtin_msa_srlri_d((v2i64)(__a), __imm))
#define msa_rshrq_n_s64(__a, __imm) ((v2i64)__builtin_msa_srari_d((v2i64)(__a), __imm))

/* Immediate Shift Left Logical: shl -> ri = ai << imm; */
#define msa_shlq_n_u8(__a, __imm)  ((v16u8)__builtin_msa_slli_b((v16i8)(__a), __imm))
#define msa_shlq_n_s8(__a, __imm)  ((v16i8)__builtin_msa_slli_b((v16i8)(__a), __imm))
#define msa_shlq_n_u16(__a, __imm) ((v8u16)__builtin_msa_slli_h((v8i16)(__a), __imm))
#define msa_shlq_n_s16(__a, __imm) ((v8i16)__builtin_msa_slli_h((v8i16)(__a), __imm))
#define msa_shlq_n_u32(__a, __imm) ((v4u32)__builtin_msa_slli_w((v4i32)(__a), __imm))
#define msa_shlq_n_s32(__a, __imm) ((v4i32)__builtin_msa_slli_w((v4i32)(__a), __imm))
#define msa_shlq_n_u64(__a, __imm) ((v2u64)__builtin_msa_slli_d((v2i64)(__a), __imm))
#define msa_shlq_n_s64(__a, __imm) ((v2i64)__builtin_msa_slli_d((v2i64)(__a), __imm))

#define msa_shlq_n_q7	msa_shlq_n_s8
#define msa_shlq_n_q15	msa_shlq_n_s16
#define msa_shlq_n_q31	msa_shlq_n_s32

/* Vector saturating rounding shift left, qrshl -> ri = ai << bi; */
#define msa_qrshrq_s32(a, b)  ((v4i32)__msa_srar_w((v4i32)(a), (v4i32)(b)))

#define msa_qrshrq_n_s32(a, b)  msa_qrshrq_s32(a, msa_reinterpret(v4i32 ,msa_dupq_n_u32(b)))

/* Vector Data Preserving Shuffle */
#define msa_vshf_f32(a,b,c)	((v4f32)((v4i32) __builtin_msa_vshf_w ((v4i32)(a), (v4i32)(b), (v4i32)(c))))
#define msa_vshf_f64(a,b,c)	((v2f64)((v2i64) __builtin_msa_vshf_d ((v2i64)(a), (v2i64)(b), (v2i64)(c))))
#define msa_vshf_q15(a,b,c) ((v8q15)((v8i16) __builtin_msa_vshf_h ((v8i16)(a), (v8i16)(b), (v8i16)(c))))
#define msa_vshf_q31(a,b,c) ((v4q31)((v4i32) __builtin_msa_vshf_w ((v4i32)(a), (v4i32)(b), (v4i32)(c))))
#define msa_vshf_u32(a,b,c)	((v4u32)((v4i32) __builtin_msa_vshf_w ((v4i32)(a), (v4i32)(b), (v4i32)(c))))
#define msa_vshf_u64(a,b,c)	((v2u64)((v2i64) __builtin_msa_vshf_d ((v2i64)(a), (v2i64)(b), (v2i64)(c))))

/* Immediate Bit Negate */
#define msa_bnegiq_u8(__a, imm0_7)	((v16u8) __builtin_msa_bnegi_b ((v16u8)(__a), imm0_7))
#define msa_bnegiq_u16(__a, imm0_15)	((v8u16) __builtin_msa_bnegi_h ((v8u16)(__a), imm0_15))
#define msa_bnegiq_u32(__a, imm0_31)	((v4u32) __builtin_msa_bnegi_w ((v4u32)(__a), imm0_31))
#define msa_bnegiq_u64(__a, imm0_63)	((v2u64) __builtin_msa_bnegi_d ((v2u64)(__a), imm0_63))

#define msa_bnegiq_q7	((v16q7)msa_bnegiq_u8)
#define msa_bnegiq_q15	((v8q15)msa_bnegiq_u8)
#define msa_bnegiq_q31	((v4q31)msa_bnegiq_u8)
#define msa_bnegiq_f32	((v4f32)msa_bnegiq_u8)
#define msa_bnegiq_f64	((v2f64)msa_bnegiq_u8)

/* extract */
#define msa_ext_f32(a, b, c) __extension__ ({	\
	v2f32_union a_f32 = {	\
		.f32x2 = a;	\
	}	\
	v2f32_union b_f32 = {	\
		.f32x2 = b;	\
	}	\
	v4f32_union ext_f32	\
	ext_f32[0] = a_f32[0]	\
	ext_f32[1] = a_f32[1]	\
	ext_f32[2] = b_f32[0]	\
	ext_f32[3] = b_f32[1]	\
	a_f32[0] = ext_f32[0+c]	\
	a_f32[1] = ext_f32[0+c]	\
	a_f32.f32x2	\
})

//c range 0-3
#define msa_extq_f32(a, b, c) __extension__ ({	\
	v4f32_union a_f32 = {	\
		.f32x4 = a;	\
	}	\
	v4f32_union b_f32 = {	\
		.f32x4 = b;	\
	}	\
	for(int i = 0;i < 4;i++){	\
		if((i+c) < 4){	\
			a_f32[i] = a_f32[i+c];	\
		}	\
		else{	\
			a_f32[i] = b_f32[i+c-4];	\
		}	\
	}	\
	a_f32.f32x4	\
})

//c range 0-1
#define msa_extq_f64(a, b, c) __extension__ ({	\
	v2f64_union a_f64 = {	\
		.f64x2 = a;	\
	}	\
	v2f64_union b_f64 = {	\
		.f64x2 = b;	\
	}	\
	if(c = 1){	\
		a_f64[0] = a_f64[1];	\
		a_f64[1] = b_f64[0];	\
	}	\
	a_f64.f64x2	\
})

/* Reverse elements in 64-bit doublewords (vector) */
#define msa_rev_f32(a)	__extension__ ({	\
	v2f32_union b;	\
	v2f32_union rev_f32 = {	\
		.f32x2 = a	\
	};	\
	b.f32[0] = rev_f32.f32[1];	\
	b.f32[1] = rev_f32.f32[0];    \
	b.f32x2;	\
})

#define msa_revq_f32(a)	__extension__ ({	\
	v4f32_union b;	\
	v4f32_union rev_f32 = {	\
		.f32x4 = a	\
	};	\
	b.f32[0] = rev_f32.f32[1];	\
	b.f32[1] = rev_f32.f32[0];    \
	b.f32[2] = rev_f32.f32[3];	\
	b.f32[3] = rev_f32.f32[2];    \
	b.f32x4;	\
})

#define msa_revq_q31(a) __extension__ ({    \
    v4q31_union b;  \
    v4q31_union rev_q31 = { \
        .q31x4 = a \
    };   \
    b.q31[0] = rev_q31.q31[1];  \
    b.q31[1] = rev_q31.q31[0];    \
    b.q31[2] = rev_q31.q31[3];  \
    b.q31[3] = rev_q31.q31[2];    \
    b.q31x4;    \
})

#define msa_revq_q15(a) __extension__ ({    \
    v8q15_union b;  \
    v8q15_union rev_q15 = { \
        .q15x8 = a \
    };   \
    for(int i = 0;i < 4;i++)    \
    {   \
        b.q15[2*i] = rev_q15.q15[2*i+1];    \
        b.q15[2*i+1] = rev_q15.q15[2*i];    \
    }   \
    b.q15x8;    \
})

#define msa_revq_f32(a) __extension__ ({    \
    v4f32_union b;  \
    v4f32_union rev_q31 = { \
        .f32x4 = a \
    };   \
    b.f32[0] = rev_f32.f32[1];  \
    b.f32[1] = rev_f32.f32[0];    \
    b.f32[2] = rev_f32.f32[3];  \
    b.f32[3] = rev_f32.f32[2];    \
    b.f32x4;    \
})

#define vzipq_f32(a, b) __extension__ ({       \
    v4f32x2 rtn;  \
    rtn.val[0] = (v4f32)__builtin_msa_ilvr_w((v4i32)(b), (v4i32)(a));  \
    rtn.val[1] = (v4f32)__builtin_msa_ilvl_w((v4i32)(b), (v4i32)(a));  \
    rtn;  \
})

/*mlaldavq*/
#define msa_mlaldavq(a, b) __extension__({	\
	v4q31 c = __msa_dotp_s_w(a, b);	\
	int64_t acc = 0;	\
	v4q31_union add_q31 = {	\
		.q31x4 = c	\
	};	\
	for(int i = 0;i < 4;i++)	\
	{	\
		acc = acc + add_q31[i];	\
	}	\
	acc;	\
})

/*rmlaldavhq*/
#define msa_rmlaldavhq(a, b) __extension__({	\
	v2q63 c = __msa_dotp_s_d(a, b);	\
	int64_t acc = 0;	\
	v2q63_union add_q63 = {	\
		.q63x2 = c	\
	};	\
	acc = acc + add_q63[0] + add_q63[1];	\
	acc;	\
})

/*rmlaldavhaq*/
#define msa_rmlaldavhaq(acc, a, b) __extension__({	\
	v2q63 c = __msa_dotp_s_d(a, b);	\
	v2q63_union add_q63 = {	\
		.q63x2 = c	\
	};	\
	acc = acc + add_q63[0] + add_q63[1];	\
	acc;	\
})

/*lsll*/
#define msa_lsll(a, shift) __extension__({	\
	if (shift >= 0)	\
	{	\
		a = a << shift;	\
	}	\
	else	\
	{	\
		a = a >> (-shift);	\
	}	\
})

/*sqrshrl_sat48*/
__STATIC_FORCEINLINE int64_t msa_sqrshrl_sat48(int64_t val, int32_t shift)
{	
  if (shift >= 0){
	val = (val + (1 << (shift-1))) >> shift;
  }
  else
  {
	shift = -shift;
	val = val << shift;
	const int64_t max = 0x00007fffffffffff;
    const int64_t min = -1 - max ;
    if (val > max)
    {
      return max;
    }
    else if (val < min)
    {
      return min;
    }
  }
  return val;
}

/* haddq and hsubq */
#define msa_haddq_q15(A,B) ((v8q15)msa_addq_s16(msa_shrq_n_s16(A,1),msa_shrq_n_s16(B,1)))
#define msa_hsubq_q15(A,B) ((v8q15)msa_subq_s16(msa_shrq_n_s16(A,1),msa_shrq_n_s16(B,1)))

#define msa_haddq_q31(A,B) ((v4q31)msa_addq_s16(msa_shrq_n_s32(A,1),msa_shrq_n_s32(B,1)))
#define msa_hsubq_q31(A,B) ((v4q31)msa_subq_s16(msa_shrq_n_s32(A,1),msa_shrq_n_s32(B,1)))


#ifdef __cplusplus
} // extern "C"
#endif

#endif
