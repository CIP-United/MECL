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

const s16 InterpolationF32_Config2_s16[2]={0x0007,0x0008};

const u32 InterpolationF32_Input1_f32[42]={0xbf666666,0x3dcccccd,0x3f8ccccd,0x40066666,0x40466666,0x40833333,0x40a33333,0x40c33333,0x40e33333,0x4101999a,0x4111999a,0x4121999a,0x4131999a,0x4141999a,0x4151999a,0x4161999a,0x4171999a,0x4180cccd,0x4188cccd,0x4190cccd,0x4198cccd,0x41a0cccd,0x41a8cccd,0x41b0cccd,0x41b8cccd,0x41c0cccd,0x41c8cccd,0x41d0cccd,0x41d8cccd,0x41e0cccd,0x41e8cccd,0x41f0cccd,0x41f8cccd,0x42006666,0x42046666,0x42086666,0x420c6666,0x42106666,0x42146666,0x42186666,0x421c6666,0x42226666};

const u32 InterpolationF32_Input2_f32[300]={0x3f000000,0x3f000000,0x3f71c71c,0x3f000000,0x3fb1c71c,0x3f000000,0x3feaaaab,0x3f000000,0x4011c71c,0x3f000000,0x402e38e4,0x3f000000,0x404aaaab,0x3f000000,0x40671c72,0x3f000000,0x4081c71c,0x3f000000,0x40900000,0x3f000000,0x3f000000,0x3f5b6db7,0x3f71c71c,0x3f5b6db7,0x3fb1c71c,0x3f5b6db7,0x3feaaaab,0x3f5b6db7,0x4011c71c,0x3f5b6db7,0x402e38e4,0x3f5b6db7,0x404aaaab,0x3f5b6db7,0x40671c72,0x3f5b6db7,0x4081c71c,0x3f5b6db7,0x40900000,0x3f5b6db7,0x3f000000,0x3f9b6db7,0x3f71c71c,0x3f9b6db7,0x3fb1c71c,0x3f9b6db7,0x3feaaaab,0x3f9b6db7,0x4011c71c,0x3f9b6db7,0x402e38e4,0x3f9b6db7,0x404aaaab,0x3f9b6db7,0x40671c72,0x3f9b6db7,0x4081c71c,0x3f9b6db7,0x40900000,0x3f9b6db7,0x3f000000,0x3fc92492,0x3f71c71c,0x3fc92492,0x3fb1c71c,0x3fc92492,0x3feaaaab,0x3fc92492,0x4011c71c,0x3fc92492,0x402e38e4,0x3fc92492,0x404aaaab,0x3fc92492,0x40671c72,0x3fc92492,0x4081c71c,0x3fc92492,0x40900000,0x3fc92492,0x3f000000,0x3ff6db6e,0x3f71c71c,0x3ff6db6e,0x3fb1c71c,0x3ff6db6e,0x3feaaaab,0x3ff6db6e,0x4011c71c,0x3ff6db6e,0x402e38e4,0x3ff6db6e,0x404aaaab,0x3ff6db6e,0x40671c72,0x3ff6db6e,0x4081c71c,0x3ff6db6e,0x40900000,0x3ff6db6e,0x3f000000,0x40124925,0x3f71c71c,0x40124925,0x3fb1c71c,0x40124925,0x3feaaaab,0x40124925,0x4011c71c,0x40124925,0x402e38e4,0x40124925,0x404aaaab,0x40124925,0x40671c72,0x40124925,0x4081c71c,0x40124925,0x40900000,0x40124925,0x3f000000,0x40292492,0x3f71c71c,0x40292492,0x3fb1c71c,0x40292492,0x3feaaaab,0x40292492,0x4011c71c,0x40292492,0x402e38e4,0x40292492,0x404aaaab,0x40292492,0x40671c72,0x40292492,0x4081c71c,0x40292492,0x40900000,0x40292492,0x3f000000,0x40400000,0x3f71c71c,0x40400000,0x3fb1c71c,0x40400000,0x3feaaaab,0x40400000,0x4011c71c,0x40400000,0x402e38e4,0x40400000,0x404aaaab,0x40400000,0x40671c72,0x40400000,0x4081c71c,0x40400000,0x40900000,0x40400000,0x3f000000,0x4056db6e,0x3f71c71c,0x4056db6e,0x3fb1c71c,0x4056db6e,0x3feaaaab,0x4056db6e,0x4011c71c,0x4056db6e,0x402e38e4,0x4056db6e,0x404aaaab,0x4056db6e,0x40671c72,0x4056db6e,0x4081c71c,0x4056db6e,0x40900000,0x4056db6e,0x3f000000,0x406db6db,0x3f71c71c,0x406db6db,0x3fb1c71c,0x406db6db,0x3feaaaab,0x406db6db,0x4011c71c,0x406db6db,0x402e38e4,0x406db6db,0x404aaaab,0x406db6db,0x40671c72,0x406db6db,0x4081c71c,0x406db6db,0x40900000,0x406db6db,0x3f000000,0x40824925,0x3f71c71c,0x40824925,0x3fb1c71c,0x40824925,0x3feaaaab,0x40824925,0x4011c71c,0x40824925,0x402e38e4,0x40824925,0x404aaaab,0x40824925,0x40671c72,0x40824925,0x4081c71c,0x40824925,0x40900000,0x40824925,0x3f000000,0x408db6db,0x3f71c71c,0x408db6db,0x3fb1c71c,0x408db6db,0x3feaaaab,0x408db6db,0x4011c71c,0x408db6db,0x402e38e4,0x408db6db,0x404aaaab,0x408db6db,0x40671c72,0x408db6db,0x4081c71c,0x408db6db,0x40900000,0x408db6db,0x3f000000,0x40992492,0x3f71c71c,0x40992492,0x3fb1c71c,0x40992492,0x3feaaaab,0x40992492,0x4011c71c,0x40992492,0x402e38e4,0x40992492,0x404aaaab,0x40992492,0x40671c72,0x40992492,0x4081c71c,0x40992492,0x40900000,0x40992492,0x3f000000,0x40a49249,0x3f71c71c,0x40a49249,0x3fb1c71c,0x40a49249,0x3feaaaab,0x40a49249,0x4011c71c,0x40a49249,0x402e38e4,0x40a49249,0x404aaaab,0x40a49249,0x40671c72,0x40a49249,0x4081c71c,0x40a49249,0x40900000,0x40a49249,0x3f000000,0x40b00000,0x3f71c71c,0x40b00000,0x3fb1c71c,0x40b00000,0x3feaaaab,0x40b00000,0x4011c71c,0x40b00000,0x402e38e4,0x40b00000,0x404aaaab,0x40b00000,0x40671c72,0x40b00000,0x4081c71c,0x40b00000,0x40900000,0x40b00000};

const u32 InterpolationF32_InputX3_f32[4]={0x0,0x40400000,0x41200000,0x41a00000};

const u32 InterpolationF32_InputX4_f32[9]={0x0,0x3f490fdb,0x3fc90fdb,0x4016cbe4,0x40490fdb,0x407b53d1,0x4096cbe4,0x40afeddf,0x40c90fdb};

const u32 InterpolationF32_InputX5_f32[3]={0x0,0x40400000,0x41200000};

const u32 InterpolationF32_InputY3_f32[4]={0x0,0x41100000,0x42c80000,0x43c80000};

const u32 InterpolationF32_InputY4_f32[9]={0x0,0x3f3504f3,0x3f800000,0x3f3504f3,0x250d3132,0xbf3504f3,0xbf800000,0xbf3504f3,0xa58d3132};

const u32 InterpolationF32_InputY5_f32[3]={0x0,0x40400000,0x41200000};

const u32 InterpolationF32_OutputX3_f32[20]={0x0,0x3f800000,0x40000000,0x40400000,0x40800000,0x40a00000,0x40c00000,0x40e00000,0x41000000,0x41100000,0x41200000,0x41300000,0x41400000,0x41500000,0x41600000,0x41700000,0x41800000,0x41880000,0x41900000,0x41980000};

const u32 InterpolationF32_OutputX4_f32[33]={0x0,0x3e490fdb,0x3ec90fdb,0x3f16cbe4,0x3f490fdb,0x3f7b53d1,0x3f96cbe4,0x3fafeddf,0x3fc90fdb,0x3fe231d6,0x3ffb53d1,0x400a3ae6,0x4016cbe4,0x40235ce2,0x402feddf,0x403c7edd,0x40490fdb,0x4055a0d8,0x406231d6,0x406ec2d4,0x407b53d1,0x4083f267,0x408a3ae6,0x40908365,0x4096cbe4,0x409d1463,0x40a35ce2,0x40a9a560,0x40afeddf,0x40b6365e,0x40bc7edd,0x40c2c75c,0x40c90fdb};

const u32 InterpolationF32_OutputX5_f32[30]={0xc1200000,0xc1100000,0xc1000000,0xc0e00000,0xc0c00000,0xc0a00000,0xc0800000,0xc0400000,0xc0000000,0xbf800000,0x0,0x3f800000,0x40000000,0x40400000,0x40800000,0x40a00000,0x40c00000,0x40e00000,0x41000000,0x41100000,0x41200000,0x41300000,0x41400000,0x41500000,0x41600000,0x41700000,0x41800000,0x41880000,0x41900000,0x41980000};

const u32 InterpolationF32_Reference1_f32[42]={0x3f800000,0x3f7ffdd9,0x3f7fca2c,0x3f7e1c50,0x3f77c498,0x3f67cc8e,0x3f481b9f,0x3f12eec2,0x3e8ae6d2,0xbde4a03e,0xbf05251b,0xbf5a9e28,0xbf7c0a23,0xbf4dcf00,0xbe9abd0d,0x3eba952d,0x3f613b02,0x3f685be3,0x3eaf622b,0xbefc7247,0xbf746355,0xbf135a3f,0x3ec013d8,0x3f717a88,0x3edb99bf,0xbf207123,0xbf5979a4,0x3e176823,0x3f6b8e73,0x3e42c3dd,0xbf5da4da,0xbea9b424,0x3f562c09,0x3e972a62,0xbf5d8558,0xbda8cd5f,0x3f6035e6,0xbe9b1ffb,0xbf310164,0x3f3aebc0,0x3e111592,0xbf7ba27a};

const u32 InterpolationF32_Reference2_f32[150]={0x3ebf2c3e,0x3e50b615,0x3c3e419d,0xbe3c3dd2,0xbeb0b445,0xbef8cc43,0xbf0f9198,0xbf069c2b,0xbedf0b77,0x3d277c41,0x3cd6c86d,0xbea66424,0xbdfb712d,0x3e224bd4,0x3b913226,0xbed257f4,0xbf171e34,0xbec0edbb,0xbe1b45ea,0x3e1f18fc,0xbd6b0b94,0xbe99a5e9,0xbdcc27d9,0x3e27f660,0x3d9b21cd,0xbe6517a4,0xbeb3502c,0xbe40f3fb,0xbced0521,0x3dea8714,0x3d0e3898,0x3dc05a66,0x3ce88d20,0xbd612497,0xbd1d6676,0x3d1bd6d7,0x3d8e7eca,0x3cd6a813,0xbc61887e,0xbcf4e140,0x3e01df31,0x3ef9d31c,0x3e203735,0xbe8c4456,0xbe1c4421,0x3e998188,0x3efa8f91,0x3e769e00,0x3ab7ca27,0xbe327bda,0xbe1553bd,0x3e14207b,0x3d9e01cc,0xbd29f3c3,0x3ded3fa8,0x3ee0a648,0x3f154a4c,0x3edc2ad1,0x3e8012da,0xbdef21b6,0xbf0279ea,0xbec41279,0xbd5d3180,0x3e9b90cd,0x3ef5bbb4,0x3f0c0946,0x3f186f74,0x3f1ce23b,0x3f0ea9d5,0xbc0f3300,0xbf5f9ee5,0xbf691a98,0xbe3d99a6,0x3f26300a,0x3f5813bf,0x3f27bf69,0x3f1b949d,0x3f4baf0e,0x3f5d4a3c,0x3dcb54f6,0xbf507ee7,0xbf6da36d,0xbe4e5ae5,0x3f2533de,0x3f4b2d71,0x3f05dccf,0x3ee0304c,0x3f29921c,0x3f47148d,0x3e03496f,0xbf415eea,0xbf722c41,0xbe5f1c23,0x3f2437b2,0x3f3e4723,0x3ec7f46b,0x3e89375e,0x3f07752b,0x3f30dede,0x3e20e863,0xbf384477,0xbf735df8,0xbe66f52b,0x3f22d969,0x3f36625f,0x3ea292f8,0x3e33b5a4,0x3ee8ed61,0x3f240cff,0x3e2ff9e6,0xbf474030,0xbf673338,0xbe4b2d5c,0x3f1ff2ac,0x3f4283bf,0x3ef6c087,0x3ec8efcf,0x3f1df215,0x3f3cca5e,0x3e04d5a2,0xbf563be9,0xbf5b0878,0xbe2f658c,0x3f1d0bee,0x3f4ea520,0x3f25770b,0x3f1c0266,0x3f476d79,0x3f5587be,0x3db362bc,0xbf2e9006,0xbf17641e,0xbdceea98,0x3ee49179,0x3f261744,0x3f24e479,0x3f2b17fa,0x3f3da0a4,0x3f37a691,0x3cc329cf,0xbe53a2da,0xbb095b58,0x3d0ade74,0x3d3badd2,0x3e3a0a34,0x3ec8a7bf,0x3efafc5e,0x3ecdcef0,0x3e8faf21,0xbd944576};

const u32 InterpolationF32_Reference3_f32[20]={0x0,0x3f800000,0x40800000,0x41100000,0x41800000,0x41c80000,0x42100000,0x42440000,0x42800000,0x42a20000,0x42c80000,0x42f20000,0x43100000,0x43290000,0x43440000,0x43610000,0x43800000,0x43908000,0x43a20000,0x43b48000};

const u32 InterpolationF32_Reference4_f32[33]={0x0,0x3e476168,0x3ec3b551,0x3f0e30df,0x3f3504f3,0x3f54aebc,0x3f6c3da3,0x3f7aeef6,0x3f800000,0x3f7aeef6,0x3f6c3da3,0x3f54aebc,0x3f3504f3,0x3f0e30df,0x3ec3b551,0x3e476168,0x250d3132,0xbe476168,0xbec3b551,0xbf0e30df,0xbf3504f3,0xbf54aebc,0xbf6c3da3,0xbf7aeef6,0xbf800000,0xbf7aeef6,0xbf6c3da3,0xbf54aebc,0xbf3504f3,0xbf0e30df,0xbec3b551,0xbe476168,0xa5a00000};

const u32 InterpolationF32_Reference5_f32[30]={0xc1200000,0xc1100000,0xc1000000,0xc0e00000,0xc0c00000,0xc0a00000,0xc0800000,0xc0400000,0xc0000000,0xbf800000,0x0,0x3f800000,0x40000000,0x40400000,0x40800000,0x40a00000,0x40c00000,0x40e00000,0x41000000,0x41100000,0x41200000,0x41300000,0x41400000,0x41500000,0x41600000,0x41700000,0x41800000,0x41880000,0x41900000,0x41980000};

const u32 InterpolationF32_YVals1_f32[41]={0x3f800000,0x3f7fea75,0x3f7ea79a,0x3f7936b0,0x3f6ac1bb,0x3f4d2dfb,0x3f1a7669,0x3e9e53bf,0xbd8fb620,0xbef836d2,0xbf567c63,0xbf7fce18,0xbf5a268a,0xbebd7651,0x3e9dc65e,0x3f5eed38,0x3f75f717,0x3edbce1d,0xbee0695b,0xbf7c614c,0xbf2c75a9,0x3e9d38f0,0x3f7ce303,0x3f0ace3c,0xbf173f66,0xbf7330cc,0x3d5f6c50,0x3f7cd76a,0x3e9ffb93,0xbf69026c,0xbeeeb565,0x3f61ab91,0x3edd6086,0xbf705e6f,0xbe4f8e12,0x3f7ffef2,0xbe776e22,0xbf5ae819,0x3f481afa,0x3e88856c,0xbf7ba27a};

const u32 InterpolationF32_YVals2_f32[56]={0x3f439c04,0x3f74696e,0xbf7c94a5,0xbee0bd26,0xbf6c26ca,0x3f2f0760,0xbf397af7,0x3eba7727,0xbf16e889,0x3ef1dec0,0xbf357caf,0xbd8b206e,0x3ef0c510,0x3f62d676,0xbea8698d,0x3f1e92e0,0xbf01546e,0x3f2e92b4,0x3cf8f034,0xbedf9e01,0xbf672322,0xbf54f3bc,0xbf6a4a0e,0x3f764875,0x3f098ab3,0x3f75c630,0xbf42f0f3,0x3f2471ec,0xbed9598b,0xbf7dddde,0x3f76e386,0x3cbe0990,0x3f2d38c6,0xbea1d6cc,0x3f724069,0xbf6c26ca,0xbf524be8,0x3f646d20,0x3f303724,0x3f7eed46,0xbf5f05de,0x3ef7f7e6,0x3d47ecfa,0x3f5e5108,0xbf4aadad,0x3eb76c87,0xbeb14c2a,0xbd8b206e,0xbf7f8898,0xbe4eaf46,0xbf6f315c,0x3f6051a1,0xbe577368,0x3ef90f23,0xbdb0c5a8,0x3f7ede79};

