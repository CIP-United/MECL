/******************************************************************************
 * @file     none.h
 * @brief    Intrinsincs when no DSP extension available
 * @version  V1.0.0
 * @date     20. July 2020
 ******************************************************************************/
/*
 * Copyright (c) 2010-2020 Arm Limited or its affiliates. All rights reserved.
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

/*

Definitions in this file are allowing to reuse some versions of the
MECL to build on a core (M0 for instance) or a host where
DSP extension are not available.

Ideally a pure C version should have been used instead.
But those are not always available or use a restricted set
of intrinsics.

*/
 
#ifndef _NONE_H_
#define _NONE_H_

#include "mips_math_types.h"

#if defined(MIPS_MATH_DSP)
#include "mips_dsp_define.h"
#endif

#if defined(MIPS_MATH_MSA)
#include <msa.h>
#endif

#ifdef   __cplusplus
extern "C"
{
#endif

 
    __STATIC_FORCEINLINE uint8_t __CLZ(uint32_t data)
    {
      if (data == 0U) { return 32U; }

      uint32_t count = 0U;
      uint32_t mask = 0x80000000U;

      while ((data & mask) == 0U)
      {
        count += 1U;
        mask = mask >> 1U;
      }
      return count;
    }

  __STATIC_FORCEINLINE int32_t __SSAT(int32_t val, uint32_t sat)
  {
    if ((sat >= 1U) && (sat <= 32U))
    {
      const int32_t max = (int32_t)((1U << (sat - 1U)) - 1U);
      const int32_t min = -1 - max ;
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

  __STATIC_FORCEINLINE uint32_t __USAT(int32_t val, uint32_t sat)
  {
    if (sat <= 31U)
    {
      const uint32_t max = ((1U << sat) - 1U);
      if (val > (int32_t)max)
      {
        return max;
      }
      else if (val < 0)
      {
        return 0U;
      }
    }
    return (uint32_t)val;
  }

 /**
  \brief   Rotate Right in unsigned value (32 bit)
  \details Rotate Right (immediate) provides the value of the contents of a register rotated by a variable number of bits.
  \param [in]    op1  Value to rotate
  \param [in]    op2  Number of Bits to rotate
  \return               Rotated value
 */
__STATIC_FORCEINLINE uint32_t __ROR(uint32_t op1, uint32_t op2)
{
  op2 %= 32U;
  if (op2 == 0U)
  {
    return op1;
  }
  return (op1 >> op2) | (op1 << (32U - op2));
}



/**
   * @brief Clips Q63 to Q31 values.
   */
  __STATIC_FORCEINLINE q31 clip_q63_to_q31(
  q63 x)
  {
    return ((q31) (x >> 32) != ((q31) x >> 31)) ?
      ((0x7FFFFFFF ^ ((q31) (x >> 63)))) : (q31) x;
  }

  /**
   * @brief Clips Q63 to Q15 values.
   */
  __STATIC_FORCEINLINE q15 clip_q63_to_q15(
  q63 x)
  {
    return ((q31) (x >> 32) != ((q31) x >> 31)) ?
      ((0x7FFF ^ ((q15) (x >> 63)))) : (q15) (x >> 15);
  }

  /**
   * @brief Clips Q31 to Q7 values.
   */
  __STATIC_FORCEINLINE q7 clip_q31o_q7(
  q31 x)
  {
    return ((q31) (x >> 24) != ((q31) x >> 23)) ?
      ((0x7F ^ ((q7) (x >> 31)))) : (q7) x;
  }

  /**
   * @brief Clips Q31 to Q15 values.
   */
  __STATIC_FORCEINLINE q15 clip_q31o_q15(
  q31 x)
  {
    return ((q31) (x >> 16) != ((q31) x >> 15)) ?
      ((0x7FFF ^ ((q15) (x >> 31)))) : (q15) x;
  }

  /**
   * @brief Multiplies 32 X 64 and returns 32 bit result in 2.30 format.
   */
  __STATIC_FORCEINLINE q63 mult32x64(
  q63 x,
  q31 y)
  {
    return ((((q63) (x & 0x00000000FFFFFFFF) * y) >> 32) +
            (((q63) (x >> 32)                * y)      )  );
  }

/* SMMLAR */
#define multAcc_32x32_keep32_R(a, x, y) \
    a = (q31) (((((q63) a) << 32) + ((q63) x * y) + 0x80000000LL ) >> 32)

/* SMMLSR */
#define multSub_32x32_keep32_R(a, x, y) \
    a = (q31) (((((q63) a) << 32) - ((q63) x * y) + 0x80000000LL ) >> 32)

/* SMMULR */
#define mult_32x32_keep32_R(a, x, y) \
    a = (q31) (((q63) x * y + 0x80000000LL ) >> 32)

/* SMMLA */
#define multAcc_32x32_keep32(a, x, y) \
    a += (q31) (((q63) x * y) >> 32)

/* SMMLS */
#define multSub_32x32_keep32(a, x, y) \
    a -= (q31) (((q63) x * y) >> 32)

/* SMMUL */
#define mult_32x32_keep32(a, x, y) \
    a = (q31) (((q63) x * y ) >> 32)

#ifndef ARM_MATH_DSP
  /**
   * @brief definition to pack two 16 bit values.
   */
  #define __PKHBT(ARG1, ARG2, ARG3) ( (((int32_t)(ARG1) <<    0) & (int32_t)0x0000FFFF) | \
                                      (((int32_t)(ARG2) << ARG3) & (int32_t)0xFFFF0000)  )
  #define __PKHTB(ARG1, ARG2, ARG3) ( (((int32_t)(ARG1) <<    0) & (int32_t)0xFFFF0000) | \
                                      (((int32_t)(ARG2) >> ARG3) & (int32_t)0x0000FFFF)  )
#endif

   /**
   * @brief definition to pack four 8 bit values.
   */
#ifndef ARM_MATH_BIG_ENDIAN
  #define __PACKq7(v0,v1,v2,v3) ( (((int32_t)(v0) <<  0) & (int32_t)0x000000FF) | \
                                  (((int32_t)(v1) <<  8) & (int32_t)0x0000FF00) | \
                                  (((int32_t)(v2) << 16) & (int32_t)0x00FF0000) | \
                                  (((int32_t)(v3) << 24) & (int32_t)0xFF000000)  )
#else
  #define __PACKq7(v0,v1,v2,v3) ( (((int32_t)(v3) <<  0) & (int32_t)0x000000FF) | \
                                  (((int32_t)(v2) <<  8) & (int32_t)0x0000FF00) | \
                                  (((int32_t)(v1) << 16) & (int32_t)0x00FF0000) | \
                                  (((int32_t)(v0) << 24) & (int32_t)0xFF000000)  )
#endif


 

/*
 * @brief C custom defined intrinsic functions
 */


  /*
   * @brief C custom defined QADD8
   */
  __STATIC_FORCEINLINE uint32_t __QADD8(
  uint32_t x,
  uint32_t y)
  {
    q31 r, s, t, u;

    r = __SSAT(((((q31)x << 24) >> 24) + (((q31)y << 24) >> 24)), 8) & (int32_t)0x000000FF;
    s = __SSAT(((((q31)x << 16) >> 24) + (((q31)y << 16) >> 24)), 8) & (int32_t)0x000000FF;
    t = __SSAT(((((q31)x <<  8) >> 24) + (((q31)y <<  8) >> 24)), 8) & (int32_t)0x000000FF;
    u = __SSAT(((((q31)x      ) >> 24) + (((q31)y      ) >> 24)), 8) & (int32_t)0x000000FF;

    return ((uint32_t)((u << 24) | (t << 16) | (s <<  8) | (r      )));
  }


  /*
   * @brief C custom defined QSUB8
   */
  __STATIC_FORCEINLINE uint32_t __QSUB8(
  uint32_t x,
  uint32_t y)
  {
    q31 r, s, t, u;

    r = __SSAT(((((q31)x << 24) >> 24) - (((q31)y << 24) >> 24)), 8) & (int32_t)0x000000FF;
    s = __SSAT(((((q31)x << 16) >> 24) - (((q31)y << 16) >> 24)), 8) & (int32_t)0x000000FF;
    t = __SSAT(((((q31)x <<  8) >> 24) - (((q31)y <<  8) >> 24)), 8) & (int32_t)0x000000FF;
    u = __SSAT(((((q31)x      ) >> 24) - (((q31)y      ) >> 24)), 8) & (int32_t)0x000000FF;

    return ((uint32_t)((u << 24) | (t << 16) | (s <<  8) | (r      )));
  }


  /*
   * @brief C custom defined QADD16
   */
  __STATIC_FORCEINLINE uint32_t __QADD16(
  uint32_t x,
  uint32_t y)
  {
/*  q31 r,     s;  without initialisation 'arm_offset_q15 test' fails  but 'intrinsic' tests pass! for armCC */
    q31 r = 0, s = 0;

    r = __SSAT(((((q31)x << 16) >> 16) + (((q31)y << 16) >> 16)), 16) & (int32_t)0x0000FFFF;
    s = __SSAT(((((q31)x      ) >> 16) + (((q31)y      ) >> 16)), 16) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r      )));
  }


  /*
   * @brief C custom defined SHADD16
   */
  __STATIC_FORCEINLINE uint32_t __SHADD16(
  uint32_t x,
  uint32_t y)
  {
    q31 r, s;

    r = (((((q31)x << 16) >> 16) + (((q31)y << 16) >> 16)) >> 1) & (int32_t)0x0000FFFF;
    s = (((((q31)x      ) >> 16) + (((q31)y      ) >> 16)) >> 1) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r      )));
  }


  /*
   * @brief C custom defined QSUB16
   */
  __STATIC_FORCEINLINE uint32_t __QSUB16(
  uint32_t x,
  uint32_t y)
  {
    q31 r, s;

    r = __SSAT(((((q31)x << 16) >> 16) - (((q31)y << 16) >> 16)), 16) & (int32_t)0x0000FFFF;
    s = __SSAT(((((q31)x      ) >> 16) - (((q31)y      ) >> 16)), 16) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r      )));
  }


  /*
   * @brief C custom defined SHSUB16
   */
  __STATIC_FORCEINLINE uint32_t __SHSUB16(
  uint32_t x,
  uint32_t y)
  {
    q31 r, s;

    r = (((((q31)x << 16) >> 16) - (((q31)y << 16) >> 16)) >> 1) & (int32_t)0x0000FFFF;
    s = (((((q31)x      ) >> 16) - (((q31)y      ) >> 16)) >> 1) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r      )));
  }


  /*
   * @brief C custom defined QASX
   */
  __STATIC_FORCEINLINE uint32_t __QASX(
  uint32_t x,
  uint32_t y)
  {
    q31 r, s;

    r = __SSAT(((((q31)x << 16) >> 16) - (((q31)y      ) >> 16)), 16) & (int32_t)0x0000FFFF;
    s = __SSAT(((((q31)x      ) >> 16) + (((q31)y << 16) >> 16)), 16) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r      )));
  }


  /*
   * @brief C custom defined SHASX
   */
  __STATIC_FORCEINLINE uint32_t __SHASX(
  uint32_t x,
  uint32_t y)
  {
    q31 r, s;

    r = (((((q31)x << 16) >> 16) - (((q31)y      ) >> 16)) >> 1) & (int32_t)0x0000FFFF;
    s = (((((q31)x      ) >> 16) + (((q31)y << 16) >> 16)) >> 1) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r      )));
  }


  /*
   * @brief C custom defined QSAX
   */
  __STATIC_FORCEINLINE uint32_t __QSAX(
  uint32_t x,
  uint32_t y)
  {
    q31 r, s;

    r = __SSAT(((((q31)x << 16) >> 16) + (((q31)y      ) >> 16)), 16) & (int32_t)0x0000FFFF;
    s = __SSAT(((((q31)x      ) >> 16) - (((q31)y << 16) >> 16)), 16) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r      )));
  }


  /*
   * @brief C custom defined SHSAX
   */
  __STATIC_FORCEINLINE uint32_t __SHSAX(
  uint32_t x,
  uint32_t y)
  {
    q31 r, s;

    r = (((((q31)x << 16) >> 16) + (((q31)y      ) >> 16)) >> 1) & (int32_t)0x0000FFFF;
    s = (((((q31)x      ) >> 16) - (((q31)y << 16) >> 16)) >> 1) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r      )));
  }


  /*
   * @brief C custom defined SMUSDX
   */
  __STATIC_FORCEINLINE uint32_t __SMUSDX(
  uint32_t x,
  uint32_t y)
  {
    return ((uint32_t)(((((q31)x << 16) >> 16) * (((q31)y      ) >> 16)) -
                       ((((q31)x      ) >> 16) * (((q31)y << 16) >> 16))   ));
  }

  /*
   * @brief C custom defined SMUADX
   */
  __STATIC_FORCEINLINE uint32_t __SMUADX(
  uint32_t x,
  uint32_t y)
  {
    return ((uint32_t)(((((q31)x << 16) >> 16) * (((q31)y      ) >> 16)) +
                       ((((q31)x      ) >> 16) * (((q31)y << 16) >> 16))   ));
  }


  /*
   * @brief C custom defined QADD
   */
#if defined(MIPS_MATH_DSP)
  __STATIC_FORCEINLINE q31 __QADD(
  q31 x,
  q31 y)
  {
    return (_mips_addq_s_w((q31)x, (q31)y));
  }
#else
  __STATIC_FORCEINLINE int32_t __QADD(
  int32_t x,
  int32_t y)
  {
    return ((int32_t)(clip_q63_to_q31((q63)x + (q31)y)));
  }
#endif


  /*
   * @brief C custom defined QSUB
   */
#if defined(MIPS_MATH_DSP)
  __STATIC_FORCEINLINE q31 __QSUB(
  q31 x,
  q31 y)
  {
    return (_mips_subq_s_w((q31)x, (q31)y));
  }
#else
  __STATIC_FORCEINLINE int32_t __QSUB(
  int32_t x,
  int32_t y)
  {
    return ((int32_t)(clip_q63_to_q31((q63)x - (q31)y)));
  }
#endif


  /*
   * @brief C custom defined SMLAD
   */
  __STATIC_FORCEINLINE uint32_t __SMLAD(
  uint32_t x,
  uint32_t y,
  uint32_t sum)
  {
    return ((uint32_t)(((((q31)x << 16) >> 16) * (((q31)y << 16) >> 16)) +
                       ((((q31)x      ) >> 16) * (((q31)y      ) >> 16)) +
                       ( ((q31)sum    )                                  )   ));
  }


  /*
   * @brief C custom defined SMLADX
   */
  __STATIC_FORCEINLINE uint32_t __SMLADX(
  uint32_t x,
  uint32_t y,
  uint32_t sum)
  {
    return ((uint32_t)(((((q31)x << 16) >> 16) * (((q31)y      ) >> 16)) +
                       ((((q31)x      ) >> 16) * (((q31)y << 16) >> 16)) +
                       ( ((q31)sum    )                                  )   ));
  }


  /*
   * @brief C custom defined SMLSDX
   */
  __STATIC_FORCEINLINE uint32_t __SMLSDX(
  uint32_t x,
  uint32_t y,
  uint32_t sum)
  {
    return ((uint32_t)(((((q31)x << 16) >> 16) * (((q31)y      ) >> 16)) -
                       ((((q31)x      ) >> 16) * (((q31)y << 16) >> 16)) +
                       ( ((q31)sum    )                                  )   ));
  }


  /*
   * @brief C custom defined SMLALD
   */
  __STATIC_FORCEINLINE uint64_t __SMLALD(
  uint32_t x,
  uint32_t y,
  uint64_t sum)
  {
/*  return (sum + ((q15) (x >> 16) * (q15) (y >> 16)) + ((q15) x * (q15) y)); */
    return ((uint64_t)(((((q31)x << 16) >> 16) * (((q31)y << 16) >> 16)) +
                       ((((q31)x      ) >> 16) * (((q31)y      ) >> 16)) +
                       ( ((q63)sum    )                                  )   ));
  }


  /*
   * @brief C custom defined SMLALDX
   */
  __STATIC_FORCEINLINE uint64_t __SMLALDX(
  uint32_t x,
  uint32_t y,
  uint64_t sum)
  {
/*  return (sum + ((q15) (x >> 16) * (q15) y)) + ((q15) x * (q15) (y >> 16)); */
    return ((uint64_t)(((((q31)x << 16) >> 16) * (((q31)y      ) >> 16)) +
                       ((((q31)x      ) >> 16) * (((q31)y << 16) >> 16)) +
                       ( ((q63)sum    )                                  )   ));
  }


  /*
   * @brief C custom defined SMUAD
   */
  __STATIC_FORCEINLINE uint32_t __SMUAD(
  uint32_t x,
  uint32_t y)
  {
    return ((uint32_t)(((((q31)x << 16) >> 16) * (((q31)y << 16) >> 16)) +
                       ((((q31)x      ) >> 16) * (((q31)y      ) >> 16))   ));
  }


  /*
   * @brief C custom defined SMUSD
   */
  __STATIC_FORCEINLINE uint32_t __SMUSD(
  uint32_t x,
  uint32_t y)
  {
    return ((uint32_t)(((((q31)x << 16) >> 16) * (((q31)y << 16) >> 16)) -
                       ((((q31)x      ) >> 16) * (((q31)y      ) >> 16))   ));
  }


  /*
   * @brief C custom defined SXTB16
   */
  __STATIC_FORCEINLINE uint32_t __SXTB16(
  uint32_t x)
  {
    return ((uint32_t)(((((q31)x << 24) >> 24) & (q31)0x0000FFFF) |
                       ((((q31)x <<  8) >>  8) & (q31)0xFFFF0000)  ));
  }

  /*
   * @brief C custom defined SMMLA
   */
  __STATIC_FORCEINLINE int32_t __SMMLA(
  int32_t x,
  int32_t y,
  int32_t sum)
  {
    return (sum + (int32_t) (((int64_t) x * y) >> 32));
  }



#ifdef   __cplusplus
}
#endif

#endif /* ifndef _TRANSFORM_FUNCTIONS_H_ */
