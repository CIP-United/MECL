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

const u32 ControllerF32_Samples1_f32[256]={0xbda925c5,0x3ec83be3,0xbec8b4cf,0x3f6567bb,0xbeb1e8a8,0xbeff2a3a,0x3ecd5225,0x3ed86291,0xbe165fcb,0x3ef8d72c,0x3e87d0e7,0xbdd71448,0x3f2f8e7f,0x3ecd6baf,0x3ebbd6d9,0xbe9c5843,0x3ead6d46,0x3f07a100,0x3e4e69cc,0xbe35368c,0xbde75551,0x3ec4a5f0,0xbf3bb17e,0x3edaced0,0xbedbed2c,0xbd5adaec,0x3ef2c362,0xbf245f5b,0x3df135d0,0x3cdc49f2,0xbe5dc25d,0x3e94079b,0x3ed3f535,0xbda25f3b,0x3ec68c3f,0x3f13dd0f,0x3ec56807,0x3f2b4521,0x3d7e71c8,0xbeb6cdaf,0xbe79efcc,0xbed88c83,0x3e886a39,0x3bb846c6,0x3e135fd7,0x3f040e82,0x3d260888,0x3e3ed125,0xbe39d3e8,0x3d653df6,0x3ebce0bc,0xbe6a5eb9,0xbec5562a,0xbe173e01,0xbea0dbfe,0x3eb10a84,0xbe3f2451,0xbe38600a,0x3ee5766f,0x3e45bbc8,0xbeea0c81,0xbd527a11,0x3e1fa521,0x3a61896b,0x3df60bf5,0xbe19cc54,0xbe7e19db,0x3d8f6231,0xbf00556e,0xbecb0aa9,0x3ef7dea4,0xbdd3ec02,0x3e67fd1a,0xbf19de37,0xbe1da0d1,0x3e43a267,0x3d1cd253,0xbe13323a,0xbd9ba48d,0xbebfb194,0xbe77ad0c,0xbdcfd70d,0xbeb227be,0xbdb86527,0xbeb28c29,0xbeb209a7,0x3dc408ae,0x3d3accf5,0xbdb1e97a,0x3e8d3369,0x3d158fc1,0xbe00edbe,0x3e0c3560,0xbeac158b,0x3e727a13,0x3dae9b40,0xbf183785,0xbe8f9352,0x3edc9796,0xbec731e5,0xbe4728a0,0xbea2b988,0xbeb427ab,0xbdf7c4eb,0x3e1c4611,0xbd193120,0xbdd1f04b,0xbe6f0366,0x3d2de234,0x3e07e095,0xbd37a813,0xbd92cbf0,0x3cfb0155,0xbefd89ea,0x3dbbaee7,0xbe978f0f,0xbe4bf1e4,0xbcc9946b,0x3ef5e13a,0x3e971b4f,0x3e9744cb,0x3c58b4c5,0x3d9ba4fb,0x3dc3cb79,0xbe9ec103,0xbeba3d68,0x3e667903,0x3eaaf4c7,0xbeff2cd8,0xbc9b4407,0xbed92c49,0x3e2ca993,0xbeaa3423,0x3e4ec1eb,0x3e8071ad,0xbeb2e9f8,0xbe4f644b,0xbe182182,0x3d4f14f7,0xbdaaa920,0xbe925f92,0xbeeeb1bd,0x3f800000,0x3e75e739,0xbcf2b69c,0x3c8b234c,0x3e9c57f7,0xbebd103e,0xbee3f7a4,0xbe8ad0ba,0xbe7d2fbf,0xbea2d853,0x3eca1491,0x3ea85d4e,0xbe2da0a6,0xbef07ccb,0x3ed05982,0xbf1094c7,0xbf26998d,0xbeb76fad,0xbe275121,0x3e7320cb,0x3e589538,0x3dd7c7ba,0x3de83bdf,0x3e31a5b2,0xbd25f445,0x3d292258,0xbe44426a,0xbf25c13d,0xbe89b5af,0x3cc4e1f5,0xbd059b67,0x3ec635bf,0xbd5d463d,0xbf1355d8,0xbd65c7d5,0x3e8648af,0x3db4e937,0xbdcb97e0,0xbf158891,0xbe0857d7,0xbe58ab63,0xbf3a8ce6,0xbb3a71ed,0x3f009972,0xbf0246b5,0xbe420e21,0xbd221b29,0xbd1a8a30,0x3f023b80,0xbdbd885e,0x3e02a9d7,0x3eac0441,0x3eceaaae,0xbe856fb3,0x3e562373,0xbdc1481f,0xbe32c2be,0xbe6634a2,0x3e8b3ad8,0xbdc0ff4d,0x3ef0fe1b,0xbdbbcff8,0x3d990554,0x3ec2ea39,0x3e256fb4,0x3e6003a6,0x3eed0d58,0x3d83bc4b,0xbd745c19,0x3d85a811,0xbe8547b6,0x3dc7eb4b,0xbe59f5d2,0xbeaa1a0a,0x3dbc532f,0x3dbe51e4,0xbe0ea641,0xbe0ca645,0xbd28e4c1,0xbe55ffa6,0xbd12fec1,0x3ef61494,0xbd435637,0x3eb18af7,0xbc3e75a6,0xbe77a35c,0x3eefc03f,0xbd88dfea,0x3e311967,0xbe879e1e,0xbd9f4d07,0x3e70d1d4,0x3e79652e,0xbf02dfa5,0xbd18a050,0x3e559264,0x3ee5756b,0xbf016da4,0xbddd6d55,0x3e617aff,0xbe91c58d,0x3e0c48ff,0xbdce43d1,0x3e45243d,0x3e3d637e,0xbf2906f9,0x3d2626d3,0xbdcc6c3e,0xbde233e7,0x3cbc21e1,0x3f225cd6,0xbe2f7897,0x3da8a150,0x3e0bffd4};

