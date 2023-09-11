/******************************************************************************
 * @file     matrix_utils.h
 * @brief    Public header file for MIPS Embedded Compute Library
 * @version  V1.0.0
 * @date     31 Augest 2023
 ******************************************************************************/
/*
 * Copyright (c) 2010-2022 ARM Limited or its affiliates. All rights reserved.
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

 
#ifndef _MATRIX_UTILS_H_
#define _MATRIX_UTILS_H_

#include "mips_math_types.h"
#include "mips_math_memory.h"

#include "dsp/none.h"
#include "dsp/utils.h"

#ifdef   __cplusplus
extern "C"
{
#endif

#define ELEM(A,ROW,COL) &((A)->pData[(A)->numCols* (ROW) + (COL)])

#define SCALE_COL_T(T,CAST,A,ROW,v,i)        \
{                                       \
  int32_t w;                            \
  T *data = (A)->pData;                 \
  const int32_t numCols = (A)->numCols; \
  const int32_t nb = (A)->numRows - ROW;\
                                        \
  data += i + numCols * (ROW);          \
                                        \
  for(w=0;w < nb; w++)                  \
  {                                     \
     *data *= CAST v;                   \
     data += numCols;                   \
  }                                     \
}

#define COPY_COL_T(T,A,ROW,COL,DST)               \
{                                                 \
    uint32_t row;                                 \
    T *pb=DST;                                    \
    T *pa = (A)->pData + ROW * (A)->numCols + COL;\
    for(row = ROW; row < (A)->numRows; row ++)    \
    {                                             \
         *pb++ = *pa;                             \
         pa += (A)->numCols;                      \
    }                                             \
}


#if defined(MIPS_MATH_MSA)

#define SWAP_ROWS_F32(A,COL,i,j)                  \
  {                                               \
    int cnt = ((A)->numCols)-(COL);               \
    f32 *data = (A)->pData;                 \
    const int32_t numCols = (A)->numCols;        \
    int32_t w;                                   \
                                                  \
    for(w=(COL);w < numCols; w+=4)                \
    {                                             \
       f32x4_t tmpa,tmpb;                         \
       mve_pred16_t p0 = vctp32q(cnt);            \
                                                  \
       tmpa=vldrwq_z_f32(&data[i*numCols + w],p0);\
       tmpb=vldrwq_z_f32(&data[j*numCols + w],p0);\
                                                  \
       vstrwq_p(&data[i*numCols + w], tmpb, p0);  \
       vstrwq_p(&data[j*numCols + w], tmpa, p0);  \
                                                  \
       cnt -= 4;                                  \
    }                                             \
  }

#define MAC_ROW_F32(COL,A,i,v,B,j)                   \
{                                                    \
  int cnt = ((A)->numCols)-(COL);                    \
  f32 *dataA = (A)->pData;                     \
  f32 *dataB = (B)->pData;                     \
  const int32_t numCols = (A)->numCols;             \
  int32_t w;                                        \
                                                     \
  for(w=(COL);w < numCols; w+=4)                     \
  {                                                  \
       f32x4_t tmpa,tmpb;                            \
       mve_pred16_t p0 = vctp32q(cnt);               \
       tmpa = vldrwq_z_f32(&dataA[i*numCols + w],p0);\
       tmpb = vldrwq_z_f32(&dataB[j*numCols + w],p0);\
       tmpa = vfmaq_n_f32(tmpa,tmpb,v);              \
       vstrwq_p(&dataA[i*numCols + w], tmpa, p0);    \
       cnt -= 4;                                     \
  }                                                  \
                                                     \
}

#define MAS_ROW_F32(COL,A,i,v,B,j)                   \
{                                                    \
  int cnt = ((A)->numCols)-(COL);                    \
  f32 *dataA = (A)->pData;                     \
  f32 *dataB = (B)->pData;                     \
  const int32_t numCols = (A)->numCols;             \
  int32_t w;                                        \
  f32x4_t vec=vdupq_n_f32(v);                        \
                                                     \
  for(w=(COL);w < numCols; w+=4)                     \
  {                                                  \
       f32x4_t tmpa,tmpb;                            \
       mve_pred16_t p0 = vctp32q(cnt);               \
       tmpa = vldrwq_z_f32(&dataA[i*numCols + w],p0);\
       tmpb = vldrwq_z_f32(&dataB[j*numCols + w],p0);\
       tmpa = vfmsq_f32(tmpa,tmpb,vec);              \
       vstrwq_p(&dataA[i*numCols + w], tmpa, p0);    \
       cnt -= 4;                                     \
  }                                                  \
                                                     \
}

#define SCALE_ROW_F32(A,COL,v,i)                    \
{                                                   \
  int cnt = ((A)->numCols)-(COL);                   \
  f32 *data = (A)->pData;                     \
  const int32_t numCols = (A)->numCols;            \
  int32_t w;                                       \
                                                    \
  for(w=(COL);w < numCols; w+=4)                    \
  {                                                 \
       f32x4_t tmpa;                                \
       mve_pred16_t p0 = vctp32q(cnt);              \
       tmpa = vldrwq_z_f32(&data[i*numCols + w],p0);\
       tmpa = vmulq_n_f32(tmpa,v);                  \
       vstrwq_p(&data[i*numCols + w], tmpa, p0);    \
       cnt -= 4;                                    \
  }                                                 \
                                                    \
}

#elif defined(MIPS_MATH_MSA)

#define SWAP_ROWS_F32(A,COL,i,j)       \
{                                      \
  int32_t w;                           \
  f32 *dataI = (A)->pData;       \
  f32 *dataJ = (A)->pData;       \
  const int32_t numCols = (A)->numCols;\
  const int32_t nb = numCols - COL;    \
                                       \
  dataI += i*numCols + (COL);          \
  dataJ += j*numCols + (COL);          \
                                       \
  f32 tmp;                       \
                                       \
  for(w=0;w < nb; w++)                 \
  {                                    \
     tmp = *dataI;                     \
     *dataI++ = *dataJ;                \
     *dataJ++ = tmp;                   \
  }                                    \
}

#define MAC_ROW_F32(COL,A,i,v,B,j)     \
{                                      \
  f32 *dataA = (A)->pData;       \
  f32 *dataB = (B)->pData;       \
  const int32_t numCols = (A)->numCols;\
  const int32_t nb = numCols - (COL);  \
  int32_t nbElems;                     \
  f32x4_t vec = vdupq_n_f32(v);        \
                                       \
  nbElems = nb >> 2;                   \
                                       \
  dataA += i*numCols + (COL);          \
  dataB += j*numCols + (COL);          \
                                       \
  while(nbElems>0)                     \
  {                                    \
       f32x4_t tmpa,tmpb;              \
       tmpa = vld1q_f32(dataA,p0);     \
       tmpb = vld1q_f32(dataB,p0);     \
       tmpa = vmlaq_f32(tmpa,tmpb,vec);\
       vst1q_f32(dataA, tmpa, p0);     \
       nbElems--;                      \
       dataA += 4;                     \
       dataB += 4;                     \
  }                                    \
                                       \
  nbElems = nb & 3;                    \
  while(nbElems > 0)                   \
  {                                    \
     *dataA++ += v* *dataB++;          \
     nbElems--;                        \
  }                                    \
}

#define MAS_ROW_F32(COL,A,i,v,B,j)     \
{                                      \
  f32 *dataA = (A)->pData;       \
  f32 *dataB = (B)->pData;       \
  const int32_t numCols = (A)->numCols;\
  const int32_t nb = numCols - (COL);  \
  int32_t nbElems;                     \
  f32x4_t vec = vdupq_n_f32(v);        \
                                       \
  nbElems = nb >> 2;                   \
                                       \
  dataA += i*numCols + (COL);          \
  dataB += j*numCols + (COL);          \
                                       \
  while(nbElems>0)                     \
  {                                    \
       f32x4_t tmpa,tmpb;              \
       tmpa = vld1q_f32(dataA);        \
       tmpb = vld1q_f32(dataB);        \
       tmpa = vmlsq_f32(tmpa,tmpb,vec);\
       vst1q_f32(dataA, tmpa);         \
       nbElems--;                      \
       dataA += 4;                     \
       dataB += 4;                     \
  }                                    \
                                       \
  nbElems = nb & 3;                    \
  while(nbElems > 0)                   \
  {                                    \
     *dataA++ -= v* *dataB++;          \
     nbElems--;                        \
  }                                    \
}

#define SCALE_ROW_F32(A,COL,v,i)        \
{                                       \
  f32 *data = (A)->pData;         \
  const int32_t numCols = (A)->numCols; \
  const int32_t nb = numCols - (COL);   \
  int32_t nbElems;                      \
  f32x4_t vec = vdupq_n_f32(v);         \
                                        \
  nbElems = nb >> 2;                    \
                                        \
  data += i*numCols + (COL);            \
  while(nbElems>0)                      \
  {                                     \
       f32x4_t tmpa;                    \
       tmpa = vld1q_f32(data);          \
       tmpa = vmulq_f32(tmpa,vec);      \
       vst1q_f32(data, tmpa);           \
       data += 4;                       \
       nbElems --;                      \
  }                                     \
                                        \
  nbElems = nb & 3;                     \
  while(nbElems > 0)                    \
  {                                     \
     *data++ *= v;                      \
     nbElems--;                         \
  }                                     \
                                        \
}

#else

#define SWAP_ROWS_F32(A,COL,i,j)       \
{                                      \
  int32_t w;                           \
  f32 tmp;                       \
  f32 *dataI = (A)->pData;       \
  f32 *dataJ = (A)->pData;       \
  const int32_t numCols = (A)->numCols;\
  const int32_t nb = numCols - COL;    \
                                       \
  dataI += i*numCols + (COL);          \
  dataJ += j*numCols + (COL);          \
                                       \
                                       \
  for(w=0;w < nb; w++)                 \
  {                                    \
     tmp = *dataI;                     \
     *dataI++ = *dataJ;                \
     *dataJ++ = tmp;                   \
  }                                    \
}

#define SCALE_ROW_F32(A,COL,v,i)       \
{                                      \
  int32_t w;                           \
  f32 *data = (A)->pData;        \
  const int32_t numCols = (A)->numCols;\
  const int32_t nb = numCols - COL;    \
                                       \
  data += i*numCols + (COL);           \
                                       \
  for(w=0;w < nb; w++)                 \
  {                                    \
     *data++ *= v;                     \
  }                                    \
}


#define MAC_ROW_F32(COL,A,i,v,B,j)     \
{                                      \
  int32_t w;                           \
  f32 *dataA = (A)->pData;       \
  f32 *dataB = (B)->pData;       \
  const int32_t numCols = (A)->numCols;\
  const int32_t nb = numCols-(COL);    \
                                       \
  dataA = dataA + i*numCols + (COL);   \
  dataB = dataB + j*numCols + (COL);   \
                                       \
  for(w=0;w < nb; w++)                 \
  {                                    \
     *dataA++ += v* *dataB++;          \
  }                                    \
}

#define MAS_ROW_F32(COL,A,i,v,B,j)     \
{                                      \
  int32_t w;                           \
  f32 *dataA = (A)->pData;       \
  f32 *dataB = (B)->pData;       \
  const int32_t numCols = (A)->numCols;\
  const int32_t nb = numCols-(COL);    \
                                       \
  dataA = dataA + i*numCols + (COL);   \
  dataB = dataB + j*numCols + (COL);   \
                                       \
  for(w=0;w < nb; w++)                 \
  {                                    \
     *dataA++ -= v* *dataB++;          \
  }                                    \
}

#endif /* defined(MIPS_MATH_MSA) */


/* Functions with only a scalar version */

#define COPY_COL_F32(A,ROW,COL,DST) \
  COPY_COL_T(f32,A,ROW,COL,DST)

#define COPY_COL_F64(A,ROW,COL,DST) \
  COPY_COL_T(f64,A,ROW,COL,DST)

#define SWAP_COLS_F32(A,COL,i,j)               \
{                                              \
  int32_t w;                                  \
  f32 *data = (A)->pData;                \
  const int32_t numCols = (A)->numCols;       \
  for(w=(COL);w < numCols; w++)                \
  {                                            \
     f32 tmp;                            \
     tmp = data[w*numCols + i];                \
     data[w*numCols + i] = data[w*numCols + j];\
     data[w*numCols + j] = tmp;                \
  }                                            \
}

#define SCALE_COL_F32(A,ROW,v,i)        \
  SCALE_COL_T(f32,,A,ROW,v,i)

#define SWAP_ROWS_F64(A,COL,i,j)       \
{                                      \
  int32_t w;                           \
  f64 *dataI = (A)->pData;       \
  f64 *dataJ = (A)->pData;       \
  const int32_t numCols = (A)->numCols;\
  const int32_t nb = numCols-(COL);    \
                                       \
  dataI += i*numCols + (COL);          \
  dataJ += j*numCols + (COL);          \
                                       \
  for(w=0;w < nb; w++)                 \
  {                                    \
     f64 tmp;                    \
     tmp = *dataI;                     \
     *dataI++ = *dataJ;                \
     *dataJ++ = tmp;                   \
  }                                    \
}

#define SWAP_COLS_F64(A,COL,i,j)               \
{                                              \
  int32_t w;                                  \
  f64 *data = (A)->pData;                \
  const int32_t numCols = (A)->numCols;       \
  for(w=(COL);w < numCols; w++)                \
  {                                            \
     f64 tmp;                            \
     tmp = data[w*numCols + i];                \
     data[w*numCols + i] = data[w*numCols + j];\
     data[w*numCols + j] = tmp;                \
  }                                            \
}

#define SCALE_ROW_F64(A,COL,v,i)       \
{                                      \
  int32_t w;                           \
  f64 *data = (A)->pData;        \
  const int32_t numCols = (A)->numCols;\
  const int32_t nb = numCols-(COL);    \
                                       \
  data += i*numCols + (COL);           \
                                       \
  for(w=0;w < nb; w++)                 \
  {                                    \
     *data++ *= v;                     \
  }                                    \
}

#define SCALE_COL_F64(A,ROW,v,i)        \
  SCALE_COL_T(f64,,A,ROW,v,i)

#define MAC_ROW_F64(COL,A,i,v,B,j)      \
{                                       \
  int32_t w;                           \
  f64 *dataA = (A)->pData;        \
  f64 *dataB = (B)->pData;        \
  const int32_t numCols = (A)->numCols;\
  const int32_t nb = numCols-(COL);     \
                                        \
  dataA += i*numCols + (COL);           \
  dataB += j*numCols + (COL);           \
                                        \
  for(w=0;w < nb; w++)                  \
  {                                     \
     *dataA++ += v* *dataB++;           \
  }                                     \
}

#define MAS_ROW_F64(COL,A,i,v,B,j)      \
{                                       \
  int32_t w;                           \
  f64 *dataA = (A)->pData;        \
  f64 *dataB = (B)->pData;        \
  const int32_t numCols = (A)->numCols;\
  const int32_t nb = numCols-(COL);     \
                                        \
  dataA += i*numCols + (COL);           \
  dataB += j*numCols + (COL);           \
                                        \
  for(w=0;w < nb; w++)                  \
  {                                     \
     *dataA++ -= v* *dataB++;           \
  }                                     \
}

#ifdef   __cplusplus
}
#endif

#endif /* ifndef _MATRIX_UTILS_H_ */
