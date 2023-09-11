/******************************************************************************
 * @file     mips_math_types.h
 * @brief    Public header file for MIPS Embedded Compute Library
 * @version  V1.0.0
 * @date     31 Augest 2023
 ******************************************************************************/
/*
 * Copyright (c) 2010-2021 Arm Limited or its affiliates. All rights reserved.
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

#ifndef _MIPS_MATH_TYPES_H_

#define _MIPS_MATH_TYPES_H_

#ifdef   __cplusplus
extern "C"
{
#endif

/* Compiler specific diagnostic adjustment */
#if defined ( __GNUC__ )
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wsign-conversion"
  #pragma GCC diagnostic ignored "-Wconversion"
  #pragma GCC diagnostic ignored "-Wunused-parameter"

#else
  #error Unknown compiler
#endif

#include <stdint.h>

/* Included for instrinsics definitions */
#if defined (__GNUC_PYTHON__)
#define  __ALIGNED(x) __attribute__((aligned(x)))
#define __STATIC_FORCEINLINE static inline __attribute__((always_inline)) 
#define __STATIC_INLINE static inline

#elif defined ( __GNUC__ )
/* compiler specific defines */
#ifndef   __ASM
  #define __ASM                                  __asm
#endif
#ifndef   __INLINE
  #define __INLINE                               inline
#endif
#ifndef   __STATIC_INLINE
  #define __STATIC_INLINE                        static inline
#endif
#ifndef   __STATIC_FORCEINLINE
  #define __STATIC_FORCEINLINE                   __attribute__((always_inline)) static inline
#endif
#ifndef   __NO_RETURN
  #define __NO_RETURN                            __attribute__((__noreturn__))
#endif
#ifndef   __USED
  #define __USED                                 __attribute__((used))
#endif
#ifndef   __WEAK
  #define __WEAK                                 __attribute__((weak))
#endif
#ifndef   __PACKED
  #define __PACKED                               __attribute__((packed, aligned(1)))
#endif
#ifndef   __PACKED_STRUCT
  #define __PACKED_STRUCT                        struct __attribute__((packed, aligned(1)))
#endif
#ifndef   __PACKED_UNION
  #define __PACKED_UNION                         union __attribute__((packed, aligned(1)))
#endif
#ifndef   __UNALIGNED_UINT32        /* deprecated */
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wpacked"
  #pragma GCC diagnostic ignored "-Wattributes"
  struct __attribute__((packed)) T_UINT32 { uint32_t v; };
  #pragma GCC diagnostic pop
  #define __UNALIGNED_UINT32(x)                  (((struct T_UINT32 *)(x))->v)
#endif
#ifndef   __UNALIGNED_UINT16_WRITE
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wpacked"
  #pragma GCC diagnostic ignored "-Wattributes"
  __PACKED_STRUCT T_UINT16_WRITE { uint16_t v; };
  #pragma GCC diagnostic pop
  #define __UNALIGNED_UINT16_WRITE(addr, val)    (void)((((struct T_UINT16_WRITE *)(void *)(addr))->v) = (val))
#endif
#ifndef   __UNALIGNED_UINT16_READ
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wpacked"
  #pragma GCC diagnostic ignored "-Wattributes"
  __PACKED_STRUCT T_UINT16_READ { uint16_t v; };
  #pragma GCC diagnostic pop
  #define __UNALIGNED_UINT16_READ(addr)          (((const struct T_UINT16_READ *)(const void *)(addr))->v)
#endif
#ifndef   __UNALIGNED_UINT32_WRITE
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wpacked"
  #pragma GCC diagnostic ignored "-Wattributes"
  __PACKED_STRUCT T_UINT32_WRITE { uint32_t v; };
  #pragma GCC diagnostic pop
  #define __UNALIGNED_UINT32_WRITE(addr, val)    (void)((((struct T_UINT32_WRITE *)(void *)(addr))->v) = (val))
#endif
#ifndef   __UNALIGNED_UINT32_READ
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wpacked"
  #pragma GCC diagnostic ignored "-Wattributes"
  __PACKED_STRUCT T_UINT32_READ { uint32_t v; };
  #pragma GCC diagnostic pop
  #define __UNALIGNED_UINT32_READ(addr)          (((const struct T_UINT32_READ *)(const void *)(addr))->v)
#endif
#ifndef   __ALIGNED
  #define __ALIGNED(x)                           __attribute__((aligned(x)))
#endif
#ifndef   __RESTRICT
  #define __RESTRICT                             __restrict
#endif
#ifndef   __COMPILER_BARRIER
  #define __COMPILER_BARRIER()                   __ASM volatile("":::"memory")
#endif
#ifndef __NO_INIT
  #define __NO_INIT                              __attribute__ ((section (".bss.noinit")))
#endif
#ifndef __ALIAS
  #define __ALIAS(x)                             __attribute__ ((alias(x)))
#endif

#else
  #error Unknown compiler.
#endif



#include <string.h>
#include <math.h>
#include <float.h>
#include <limits.h>


#if defined ( __GNUC__ )
  #define LOW_OPTIMIZATION_ENTER \
       __attribute__(( optimize("-O1") ))
  #define LOW_OPTIMIZATION_EXIT
  #define IAR_ONLY_LOW_OPTIMIZATION_ENTER
  #define IAR_ONLY_LOW_OPTIMIZATION_EXIT

#elif defined(__GNUC_PYTHON__)
      #define LOW_OPTIMIZATION_ENTER
      #define LOW_OPTIMIZATION_EXIT
      #define IAR_ONLY_LOW_OPTIMIZATION_ENTER 
      #define IAR_ONLY_LOW_OPTIMIZATION_EXIT
#endif



/* Compiler specific diagnostic adjustment */
#if defined ( __GNUC__ )
#pragma GCC diagnostic pop

#else
  #error Unknown compiler
#endif

#ifdef   __cplusplus
}
#endif

#if defined(MIPS_MATH_MSA)
#include <msa.h>
#include "mips_msa_define.h"
#endif

#ifdef   __cplusplus
extern "C"
{
#endif

#if defined(MIPS_MATH_DSP)
#include "dsp/mips_dsp_define.h"
#else
/**
   * @brief 8-bit fractional data type in 1.7 format.
   */
  typedef int8_t q7;

  /**
   * @brief 16-bit fractional data type in 1.15 format.
   */
  typedef int16_t q15;

  /**
   * @brief 32-bit fractional data type in 1.31 format.
   */
  typedef int32_t q31;

#endif

  /**
   * @brief 64-bit fractional data type in 1.63 format.
   */
  typedef int64_t q63;

  /**
   * @brief 32-bit floating-point type definition.
   */
  typedef float f32;

  /**
   * @brief 64-bit floating-point type definition.
   */
  typedef double f64;



#if defined(MIPS_MATH_MSA)
  /**
   * @brief 32-bit ubiquitous 128-bit vector data type
   */
  typedef union _any32x4_t
  {
      v4f32	f;
      v4i32	i;
  } any32x4_t;

#endif






#define F64_MAX   ((f64)DBL_MAX)
#define F32_MAX   ((f32)FLT_MAX)



#define F64_MIN   (-DBL_MAX)
#define F32_MIN   (-FLT_MAX)



#define F64_ABSMAX   ((f64)DBL_MAX)
#define F32_ABSMAX   ((f32)FLT_MAX)



#define F64_ABSMIN   ((f64)0.0)
#define F32_ABSMIN   ((f32)0.0)


#define Q31_MAX   ((q31)(0x7FFFFFFFL))
#define Q15_MAX   ((q15)(0x7FFF))
#define Q7_MAX    ((q7)(0x7F))
#define Q31_MIN   ((q31)(0x80000000L))
#define Q15_MIN   ((q15)(0x8000))
#define Q7_MIN    ((q7)(0x80))

#define Q31_ABSMAX   ((q31)(0x7FFFFFFFL))
#define Q15_ABSMAX   ((q15)(0x7FFF))
#define Q7_ABSMAX    ((q7)(0x7F))
#define Q31_ABSMIN   ((q31)0)
#define Q15_ABSMIN   ((q15)0)
#define Q7_ABSMIN    ((q7)0)

  /* Dimension C vector space */
  #define CMPLX_DIM 2

  /**
   * @brief Error status returned by some functions in the library.
   */

  typedef enum
  {
    MIPS_MATH_SUCCESS                 =  0,        /**< No error */
    MIPS_MATH_ARGUMENT_ERROR          = -1,        /**< One or more arguments are incorrect */
    MIPS_MATH_LENGTH_ERROR            = -2,        /**< Length of data buffer is incorrect */
    MIPS_MATH_SIZE_MISMATCH           = -3,        /**< Size of matrices is not compatible with the operation */
    MIPS_MATH_NANINF                  = -4,        /**< Not-a-number (NaN) or infinity is generated */
    MIPS_MATH_SINGULAR                = -5,        /**< Input matrix is singular and cannot be inverted */
    MIPS_MATH_TEST_FAILURE            = -6,        /**< Test Failed */
    MIPS_MATH_DECOMPOSITION_FAILURE   = -7         /**< Decomposition Failed */
  } mips_status;


#ifdef   __cplusplus
}
#endif

#endif /*ifndef _MIPS_MATH_TYPES_H_ */
