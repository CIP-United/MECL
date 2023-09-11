#include <stdint.h>

typedef int8_t q7;
typedef int16_t q15;
typedef int32_t q31;
typedef int64_t q63;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef uint32_t u32;
typedef uint64_t u64;

typedef float f32;
typedef double f64;

const s64 FastMathQ63_DivDenInput1_s64[12]={0x7FFFFFFFFFFFFFFF,0x8000000000000000,0x4000000000000000,0xC000000000000000,0x2000000000000000,0xE000000000000000,0x1000000000000000,0xF000000000000000,0x0000000080000000,0xFFFFFFFF80000000,0x0000000040000000,0xFFFFFFFF80000000};

const s32 FastMathQ63_DivNumInput1_s32[12]={0x00000002,0x00000002,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x00000002,0x00000002,0x00000002,0x00000002};

const u32 FastMathQ63_DivRef1_u32[12]={0xFFFFFFFF,0x00000000,0x80000001,0x7FFFFFFF,0x40000000,0xC0000000,0x20000000,0xE0000000,0x40000000,0xC0000000,0x20000000,0xC0000000};

const u64 FastMathQ63_Norm64To32_Input1_u64[4]={0x1000000080000000,0x0000000080000000,0x0000000020000000,0x0000000000000000};

const s16 FastMathQ63_RefNorm64To32_Norms1_s16[4]={0xFFE2,0xFFFF,0x0001,0x0000};

const s32 FastMathQ63_RefNorm64To32_Vals1_s32[4]={0x40000002,0x40000000,0x40000000,0x00000000};

