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

const u32 BIQUADF32_AllBiquadCoefs2_f32[330]={0x3ca3d70a,0x3c4537e4,0x3ca3d70a,0x3e4be208,0xbc499fe1,0x3f800000,0x3ff1cdec,0x3f800000,0xbf731e19,0xbe725f8a,0x3f800000,0x3f84c2d6,0x3f800000,0xbefd9b34,0xbea085a6,0x3ca3d70a,0xbcc888ab,0x3ca3d70a,0xbef1a105,0xbda88ab3,0x3f800000,0xbf5ff8c6,0x3f800000,0xbf5d20a3,0xbe55d122,0x3f800000,0xbf53bc2c,0x3f800000,0xbfb133d9,0xbef66cd1,0x3ca3d70a,0x3d1bc833,0x3ca3d70a,0xbd0355e1,0xb98bf1f3,0x3f800000,0x3fbccc2c,0x3f800000,0x3be8a4a2,0xbac68db9,0x3f800000,0xbff19732,0x3f800000,0x3f662d36,0xbec4b721,0x3ca3d70a,0xbc622b92,0x3ca3d70a,0xbdf0a4fa,0xbc45833d,0x3f800000,0x3f8a01cb,0x3f800000,0xbe04cb2b,0xbd079165,0x3f800000,0x3f7f1d51,0x3f800000,0xbe46fc7e,0xbd1c8ce6,0x3f800000,0xbf2feada,0x3f800000,0x3d82109a,0xbd2f34ea,0x3f800000,0x3fda1cdb,0x3f800000,0xbf0c54e7,0xbdaca1a4,0x3f800000,0xbf20eeb1,0x3f800000,0x3e4c4735,0xbe206b56,0x3f800000,0xbffba4b8,0x3f800000,0x3f2dc202,0xbe2d66a5,0x3f800000,0x3d590906,0x3f800000,0xbeb1fce7,0xbef8b263,0x3ca3d70a,0x3d236345,0x3ca3d70a,0xbd72a875,0xba66091c,0x3f800000,0x3ffd6291,0x3f800000,0xbd3a9e51,0xbc20c6a3,0x3f800000,0xbe6ebc3f,0x3f800000,0x3e6b5871,0xbc84f62a,0x3f800000,0xbee06e37,0x3f800000,0x3e516193,0xbcaf42f2,0x3f800000,0x3fd1ee78,0x3f800000,0xbeaea6cd,0xbdb3237b,0x3f800000,0xbf46d727,0x3f800000,0x3e8fe7d1,0xbe2063e0,0x3f800000,0xbfccd506,0x3f800000,0x3f583767,0xbe448ba6,0x3f800000,0x3d23e128,0x3f800000,0xbe57c043,0xbec0e285,0x3ca3d70a,0x3d1ee0b2,0x3ca3d70a,0x3dba8964,0xbb22da4f,0x3f800000,0x3ff302fc,0x3f800000,0x3dbf4b31,0xbbc33824,0x3f800000,0x3fea7ef0,0x3f800000,0xbd62fbcc,0xbbcb1d49,0x3f800000,0x3fe76d9e,0x3f800000,0xbce05a56,0xbcb1908b,0x3f800000,0x3f83ef38,0x3f800000,0x3ea2e05d,0xbce9f862,0x3f800000,0x3fed8262,0x3f800000,0xbf1ce115,0xbde09de6,0x3f800000,0xbfc616d5,0x3f800000,0x3f1f602c,0xbe017d15,0x3f800000,0xbd394a0c,0x3f800000,0x3e797d54,0xbea4f84a,0x3ca3d70a,0x3d1ef3ca,0x3ca3d70a,0x3dab83b1,0xbb80940d,0x3f800000,0x3fe3ff5d,0x3f800000,0xbe40cb7e,0xbc4713ed,0x3f800000,0x3fb58cab,0x3f800000,0x3e3fda77,0xbd4c7967,0x3f800000,0x3ff663b4,0x3f800000,0xbee73997,0xbd702bc4,0x3f800000,0x3f46d974,0x3f800000,0x3f0d62f9,0xbd9f9f9a,0x3f800000,0x3f97994d,0x3f800000,0xbecb7be9,0xbdcfccc5,0x3f800000,0x3fff7741,0x3f800000,0xbf2553d1,0xbdd58c04,0x3f800000,0xbfee8488,0x3f800000,0x3f256d44,0xbde819e8,0x3f800000,0xbfe05432,0x3f800000,0x3f21b227,0xbe0938f1,0x3f800000,0xbfcfc90b,0x3f800000,0x3f1a43cf,0xbe26c338,0x3f800000,0xbffd2247,0x3f800000,0x3f7bcc55,0xbe80ab96,0x3ca3d70a,0xbc92a917,0x3ca3d70a,0xbd0efc03,0xbb4e25cb,0x3f800000,0x3eb91cd3,0x3f800000,0xbdb8c052,0xbb9614fd,0x3f800000,0x3f4497fc,0x3f800000,0xbda3be0c,0xbc4a203f,0x3f800000,0x3f6fafa5,0x3f800000,0xbe36cc00,0xbd0be585,0x3f800000,0x3e6d7857,0x3f800000,0xbcd49373,0xbd74a00a,0x3f800000,0xbf856b67,0x3f800000,0x3f3a92ed,0xbe08fde1,0x3f800000,0x3f7527c5,0x3f800000,0xbf2e9558,0xbe365144,0x3f800000,0xbfafe47a,0x3f800000,0x3f7bfc50,0xbe9731c6,0x3f800000,0xbfc0461f,0x3f800000,0x3f8a3254,0xbea3ebb3,0x3f800000,0xbe347d51,0x3f800000,0x3d9b9805,0xbeac1463,0x3f800000,0xbfffa3b5,0x3f800000,0x3fa154f6,0xbed00ffb,0x3ca3d70a,0x3b077d7d,0x3ca3d70a,0xbd5fd22f,0xba9bb410,0x3f800000,0x3d82227c,0x3f800000,0x3d1d349f,0xbb18b85a,0x3f800000,0xbfa78858,0x3f800000,0x3e4e3fb8,0xbc265e7a,0x3f800000,0x3ea61d65,0x3f800000,0xbe4f335c,0xbd1022a9,0x3f800000,0x3e3b9525,0x3f800000,0xbd18ebdd,0xbd104721,0x3f800000,0x3ebe215e,0x3f800000,0xbed4f50b,0xbd385402,0x3f800000,0x3f1ee0a2,0x3f800000,0xbee0b2f1,0xbd49f354,0x3f800000,0x3fed7316,0x3f800000,0xbf055cd5,0xbdad3318,0x3f800000,0xbda8ed71,0x3f800000,0x3d227c25,0xbdd6b75f,0x3f800000,0x3f35da0f,0x3f800000,0xbeb5293e,0xbe7b0caf,0x3f800000,0x3ffb0d63,0x3f800000,0xbfa9d672,0xbeefb2fb};

const s16 BIQUADF32_AllBiquadConfigs2_s16[18]={0x0003,0x0003,0x0003,0x0008,0x0003,0x000B,0x0008,0x0003,0x0008,0x0008,0x0008,0x000B,0x000B,0x0003,0x000B,0x0008,0x000B,0x000B};

const u32 BIQUADF32_AllBiquadInputs2_f32[66]={0x3f800000,0x3f034193,0xbf286d19,0xbee540a5,0x3e26e33b,0xbf2064a6,0x3f70f85c,0xbe8b287e,0xbf800000,0x3e7579ed,0xbebc4f72,0xbf2b4a68,0xbf104907,0x3ca0f100,0xbf3dd896,0xbf2fde5c,0x3f21e0b3,0x3f1f8754,0x3f800000,0xbe09bfba,0xbd4457e9,0x3f6238c4,0xbf4004c9,0xbf800000,0x3f74d2d6,0x3f800000,0x3e92c4b5,0x3e8da5fa,0xbd2a1c65,0xbdb14ac5,0xbe8b6825,0xbd99fec1,0xbe0b24db,0x3e03246e,0xbeca6126,0xbefcb439,0x3e779dad,0xbb74140c,0xbedf52bc,0x3f800000,0xbea21297,0xbeb65edc,0xbf0988f0,0x3ecd5598,0x3e0b2e78,0xbeafcb0f,0xbf800000,0xbd643694,0xbe1980a7,0x3ee174e4,0x3e82ae0e,0x3e78118b,0xbeb45ecd,0x3f6c0927,0xbf800000,0xbe59d39d,0xbeedce8c,0xbf382234,0x3ee9bde9,0xbf800000,0x3df0c786,0x3f063be1,0xbebccb5b,0xbea9671c,0xbe0c57d3,0x3dac7612};

const u32 BIQUADF32_AllBiquadRefs2_f32[66]={0x3ca3d70a,0x3d64f6e7,0x3d9543cc,0xbc12b8bc,0x3d5c7346,0xbe45faed,0x3f0378e3,0xbf8df559,0x40009718,0xc0464621,0x40829547,0xbc5b4085,0xbd2fb6ba,0xbd29b07c,0x3b2c3898,0x3c7bc19a,0xba7fed63,0x3d160196,0x3dbed0f0,0x3d383dcf,0xbda8f659,0xbdf54d25,0xbc75c8af,0xbc43f9a7,0xbbf2b03c,0x3ca3d70a,0x3d9b78d8,0x3e25fff0,0x3e9a34d1,0x3ef32f44,0x3f1f1b8a,0x3f3f04e3,0x3f550dde,0x3b27dcb6,0x3c8569dd,0x3cbcd362,0xbdf73a80,0xbf349c5a,0xbff3c2f2,0xc05b3d2e,0xc092f716,0xc09bce97,0xc08a0adb,0xc06806b5,0x3b322700,0x3c12386f,0xbcd23f35,0xba920e74,0xbb11c874,0x3b9ab905,0xbc52df41,0x3d38eee2,0xbd5ba88b,0x3e2f01be,0xbe3955ce,0xbb8b68b7,0xbc886a6a,0xbd80d8c2,0xbe074ee7,0xbea20e09,0xbeee9221,0xbf58c7f2,0xbf7e3707,0xbfb6e6a5,0xbfbd1fa2,0xbfd7c425};

const u32 BIQUADF32_AllBiquadStereoInputs2_f32[132]={0x3f800000,0x3f0fca96,0x3f034193,0x3e8b72e4,0xbf286d19,0xbf800000,0xbee540a5,0xbca5c85b,0x3e26e33b,0xbf09ebf0,0xbf2064a6,0xbe5a3c55,0x3f70f85c,0xbef1939c,0xbe8b287e,0xbec023d9,0xbf800000,0xbd8c5657,0x3e7579ed,0xbf800000,0xbebc4f72,0xbe8f8384,0xbf2b4a68,0xbece16c6,0xbf104907,0xbea0cf77,0x3ca0f100,0x3f35f9fe,0xbf3dd896,0x3f800000,0xbf2fde5c,0xbe98e9f8,0x3f21e0b3,0xbf403348,0x3f1f8754,0xbda8470e,0x3f800000,0xbefdafc7,0xbe09bfba,0xbecd3997,0xbd4457e9,0x3edb9052,0x3f6238c4,0x3e826ac4,0xbf4004c9,0xbf800000,0xbf800000,0x3e1d94a4,0x3f74d2d6,0x3e08a537,0x3f800000,0xbf800000,0x3e92c4b5,0x3f3d9883,0x3e8da5fa,0xbe0a81cb,0xbd2a1c65,0x3f668a53,0xbdb14ac5,0x3f0e28e4,0xbe8b6825,0x3f46d398,0xbd99fec1,0x3f7ba66b,0xbe0b24db,0x3f6ec2a8,0x3e03246e,0xbdbdb8aa,0xbeca6126,0xbef74e68,0xbefcb439,0xbf3cb8bb,0x3e779dad,0xbebfb60b,0xbb74140c,0x3d9ab9ce,0xbedf52bc,0x3bdc4632,0x3f800000,0xbf270982,0xbea21297,0xbef701ef,0xbeb65edc,0xbf800000,0xbf0988f0,0xbe1db24a,0x3ecd5598,0xbd837835,0x3e0b2e78,0xbe536194,0xbeafcb0f,0xbf800000,0xbf800000,0x3f4f8d9f,0xbd643694,0x3f800000,0xbe1980a7,0xbf319706,0x3ee174e4,0xbe07352a,0x3e82ae0e,0x3f70b3d7,0x3e78118b,0x3f15a0f3,0xbeb45ecd,0x3f0addc1,0x3f6c0927,0xbe956eb6,0xbf800000,0x3ed77e8b,0xbe59d39d,0xbe0154f6,0xbeedce8c,0xbf41fcf3,0xbf382234,0x3e9d1fa7,0x3ee9bde9,0x3d987640,0xbf800000,0x3f4fcc49,0x3df0c786,0xbbf43bd0,0x3f063be1,0x3ec2ae50,0xbebccb5b,0xbe86fecd,0xbea9671c,0xbeb5ea0e,0xbe0c57d3,0xbe8e0803,0x3dac7612,0x3f800000};

const u32 BIQUADF32_AllBiquadStereoRefs2_f32[132]={0x3ca3d70a,0x3c380d8d,0x3d64f6e7,0x3cfea6d3,0x3d9543cc,0x3ce238d1,0xbc12b8bc,0xb9d433a7,0x3d5c7346,0xbc0b195a,0xbe45faed,0x3d49a9e3,0x3f0378e3,0xbe283bef,0xbf8df559,0x3ec1e4fc,0x40009718,0xbf2e90e4,0xc0464621,0x3f7b7ebf,0x40829547,0xbf92c72f,0xbc5b4085,0xbc03e59d,0xbd2fb6ba,0xbccf519f,0xbd29b07c,0xbc1fed41,0x3b2c3898,0x3d834c90,0x3c7bc19a,0x3dc1da96,0xba7fed63,0xbc8bd574,0x3d160196,0xbe11a765,0x3dbed0f0,0xbdd7e7aa,0x3d383dcf,0x3ca34d54,0xbda8f659,0x3da93489,0xbdf54d25,0x3dabd24b,0xbc75c8af,0xbca3d70a,0xbc43f9a7,0x3c6203de,0xbbf2b03c,0xbd473d5d,0x3ca3d70a,0xbca3d70a,0x3d9b78d8,0xbd62ca5f,0x3e25fff0,0xbdb28ef9,0x3e9a34d1,0xbe091d90,0x3ef32f44,0xbe0b278f,0x3f1f1b8a,0xbd36f73d,0x3f3f04e3,0x3de23de8,0x3f550dde,0x3ec4415f,0x3b27dcb6,0xbaf2d7e4,0x3c8569dd,0xbcde7c77,0x3cbcd362,0xbe3c3722,0xbdf73a80,0xbf44f1b4,0xbf349c5a,0xc00fa974,0xbff3c2f2,0xc09c138c,0xc05b3d2e,0xc10426c0,0xc092f716,0xc136328f,0xc09bce97,0xc1594e8b,0xc08a0adb,0xc175a67f,0xc06806b5,0xc18ffbfd,0x3b322700,0xbb8748b1,0x3c12386f,0xbd3427cc,0xbcd23f35,0xbe1b9858,0xba920e74,0x3ca3d70a,0xbb11c874,0xbce36786,0x3b9ab905,0x3df0fd01,0xbc52df41,0xbe106c81,0x3d38eee2,0x3eb7d7e5,0xbd5ba88b,0xbeae2fd1,0x3e2f01be,0x3f2e3967,0xbe3955ce,0xbef46dc6,0xbb8b68b7,0xbb258b78,0xbc886a6a,0xbc9ff714,0xbd80d8c2,0xbd21368c,0xbe074ee7,0xbe05a51d,0xbea20e09,0xbe21933c,0xbeee9221,0xbeac37ca,0xbf58c7f2,0xbe837de3,0xbf7e3707,0xbec73d0a,0xbfb6e6a5,0xbdda8855,0xbfbd1fa2,0xbd9cbe2c,0xbfd7c425,0x3e8eedc2};

const u32 BIQUADF32_BiquadCoefs1_f32[15]={0x3ca3d70a,0xbcb10bd8,0x3ca3d70a,0x3fdf3cc8,0xbf4f5c29,0x3f800000,0xbfcbcc26,0x3f800000,0x3fdf995a,0xbf70ded3,0x3f800000,0xbffff2e5,0x3f800000,0x3ffa9104,0xbf75dcc6};

const u32 BIQUADF32_BiquadInput1_f32[100]={0xbcf53bc7,0x3e91ab21,0x3f2b2c74,0x3e9d1f6b,0x3e5b1bd3,0x3f09c922,0x3f4428f3,0x3f103015,0x3de599a3,0xbca6e341,0xbd2e1214,0xbc87968f,0xbe2cd052,0xbf1c68c2,0xbf55dea8,0xbf235faa,0xbea2e717,0xbe899a6f,0xbecd218b,0xbec298f8,0xbcad67b9,0x3f090e58,0x3f0c6656,0x3ed75328,0x3ec7bfac,0x3f0fd65f,0x3f2f9107,0x3f093857,0x3e232195,0x3b76b844,0x3e1fd2af,0x3e3a5613,0xbebca9b8,0xbf1afad6,0xbf47003b,0xbf0e7990,0xbee72a14,0xbea58e41,0xbeed2177,0xbeb4be03,0x3e331239,0x3ecc8678,0x3ecf0e59,0x3e825328,0x3ee94d66,0x3f5c5a80,0x3f15de38,0x3f11777b,0xbdd445fa,0xbd36f3c5,0x3e8dc1e1,0xbe39fdc0,0xbec37d10,0xbf1e1615,0xbf025288,0xbee8c1b9,0xbe852759,0xbf11d5a3,0xbe896cfa,0xbe889cbe,0x3e0cc29d,0x3eedb816,0x3e41a0d4,0x3f015b2f,0x3eecfa87,0x3f4f110d,0x3f33430d,0x3f15c127,0xbda65fed,0xbb8b684e,0xbc6d801f,0xbe990fb9,0xbf1e907d,0xbf800000,0xbf0778bf,0xbed8543d,0xbe605a08,0xbef34813,0xbeae7557,0xbe56a0a4,0x3e98a4c2,0x3eee73cf,0x3eb95539,0x3e0baadd,0x3ebf8ced,0x3f09388c,0x3f1fa2cb,0x3ede4653,0x3df02037,0x3e4c6717,0xbda54f14,0xbe0e8987,0xbf1739b0,0xbf2d733a,0xbef4a308,0xbe930645,0xbef3abd9,0xbe380acc,0xbeaf6a8e,0x3dc64ce8};

const u32 BIQUADF32_BiquadOutput1_f32[100]={0xba1cf30f,0x3bab3ad5,0x3c896159,0x3cca4ba9,0x3d34eb78,0x3d98474d,0x3ddffb9d,0x3e156293,0x3e3a8e79,0x3e5f64c3,0x3e78947c,0x3e80a895,0x3e72c5d4,0x3e46d3d5,0x3e00f3a8,0x3d10671d,0xbd981b15,0xbe482bae,0xbea111c9,0xbed53e19,0xbef9a5b1,0xbf0455b7,0xbf015e56,0xbee35bf0,0xbeac923f,0xbe4645ec,0xbcf45f15,0x3e0ba33a,0x3e93132a,0x3ed22a4d,0x3efc9a2d,0x3f06219a,0x3efd2b97,0x3ed6e1a9,0x3e997914,0x3e1cc471,0xbc2fb69f,0xbe2e418b,0xbea13de4,0xbed9ebfe,0xbefb45e4,0xbf0361b8,0xbef9d0de,0xbed6d520,0xbe9ed526,0xbe2fd0ef,0xbcdfb793,0x3e005ddd,0x3e82009b,0x3ebb3497,0x3ee2b0ff,0x3eef06e1,0x3ee7aa3f,0x3ec8c4f8,0x3e98116d,0x3e2f24f4,0x3d045273,0xbdece40e,0xbe77e9f8,0xbeb39607,0xbed5f3cd,0xbee2a9b4,0xbedbd167,0xbeb9586a,0xbe8755f2,0xbe06b345,0x3c3d616e,0x3e23af4b,0x3e92e4fb,0x3ecb49ba,0x3eee1fbb,0x3ef7f6fe,0x3ee8e8ca,0x3ebfb232,0x3e867787,0x3de8c715,0xbd393c7a,0xbe540d98,0xbeb00880,0xbee62ce6,0xbf012e85,0xbf02c62a,0xbeedc2b5,0xbebe2501,0xbe71f4af,0xbda79e2f,0x3da2110d,0x3e6975ac,0x3eb39d35,0x3ee29319,0x3ef7a07e,0x3ef72790,0x3edc7ab2,0x3eb051b3,0x3e6c7fec,0x3dcda67d,0xbd1d8fcf,0xbe23b57d,0xbe8a1b97,0xbeaeb3a0};

const u32 BIQUADF32_Coefs1_f32[20]={0x3e8986fa,0xbc9455aa,0x3dd2a5b7,0x3e8ddaf5,0xbbab3f0c,0xbf40bcdb,0xbeaee585,0xbec6f05b,0xbeb80a9d,0x3f7895d8,0x3df79d69,0x3ef76aee,0xbe907a73,0xbf31e86a,0xbd1abc68,0xbf4278bf,0xbe96aff6,0xbed419c9,0x3f800000,0xbf2ed3df};

const u32 BIQUADF32_Samples1_f32[512]={0xbec0f69b,0xbe0ed2e3,0x3f4d8b8f,0xbe943429,0x3e83a83e,0x3ce34a18,0x3f0cf37c,0x3efbf423,0x3f10abfe,0xbdad00ad,0x3eca8ed7,0xbec40849,0x3e8c8464,0xbccc97c9,0x3e21c88f,0x3d5cbea9,0x3ec86c5a,0x3ec1aa8c,0x3d1e8782,0xbe0bfd64,0xbde8c5da,0x3d47f737,0xbf4b86a9,0xbd8ff9e2,0x3ed7a839,0xbd9da8b6,0x3dfd91b3,0x3eb183c2,0x3ef3eee1,0xbe4b4e32,0x3e3ba198,0xbd8f6c0a,0x3ea831c6,0xbe9e6310,0x3ea12166,0x3e9faaaf,0xbd4622bb,0xbe4b1de2,0xbe23d64b,0x3db8d29d,0x3e885e6e,0xbdb211d5,0x3c71d4c8,0x3dc08a02,0x3dffd96d,0x3cc99adb,0xbe45bbdf,0xbd1aafa6,0x3ddecbe1,0xbeb29f0f,0xbc5d9c9d,0xbddd28f9,0xbe118275,0xbf15221a,0x3f131e89,0x3e29a74f,0xbe1142e3,0xbd9f5fd8,0x3ed30a17,0xbe83cbd3,0x3f1a1bee,0xbe8e70e5,0xbddb9e38,0x3e15340c,0x3f03c4c4,0xbeb0a340,0x3ecb8f89,0xbf00e45e,0xbe9b95ea,0xbf192c9f,0x3e71c4c0,0x3ed16169,0xbee980d1,0xbd4a0a20,0xbeb63a01,0x3ef23ccf,0x3e34427c,0xbeba6558,0x3e3cbb42,0xbece76e8,0x3c1bf26c,0xbe45a6d0,0xbe632c2e,0x3e692509,0x3e085de7,0x3e2c5fa6,0xbdd5964c,0x3d172bc2,0x3dac93f1,0xbe9865e0,0xbeba393c,0xbea1e35b,0x3e113296,0x3e289b8d,0x3e9fdaeb,0xbd7d0c6b,0x3ed5846b,0x3f2109e0,0xbeb98546,0x3d91976b,0xbeb55b2c,0x3ea4cee8,0x3e8cd5b3,0x3d858cc4,0xbe57c666,0x3f0ddc96,0xbe37e6c7,0x3d5b3df3,0x3e99ea96,0xbeb4eb9e,0x3f0504e9,0xbdf94493,0xbe76e700,0xbdd5d042,0xbe219c6e,0x3ed76d83,0x3e9b63ab,0x3d211044,0xbe770268,0xbe0ac6a1,0x3ebc8877,0x3e83b274,0xbe8c6871,0x3e7331a2,0x3d6deaf8,0xbd954de7,0xbe5f5590,0xbec761e1,0xbe89a61a,0xbe9d25fa,0x3f3e7247,0x3efff1be,0x3ea37abf,0xbe5a593f,0x3cff14ea,0xbe9b5d6a,0xbe607c64,0xbc9923aa,0xbebf4c56,0xbdc024ec,0x3e6d6e1a,0x3de6e588,0x3d984579,0x3d1f70e3,0x3eb3ff27,0xbde394f6,0xbdb2227e,0xbdfaf410,0x3f180d9a,0x3e90ee09,0x3d140a6f,0x3e7d543c,0x3e85bb19,0xbdda5fda,0x3e441483,0x3dfc1f6a,0x3e0b613b,0xbf439f52,0x3e4d5c72,0xbd8ac7f3,0xbf036cc8,0xbe32bdbf,0xbdbad69b,0xbe276fff,0x3d775765,0x3e09b0fb,0x3f1d6fd0,0xbdc02a2c,0xbe83d028,0xbe5696a8,0x3e8e6526,0xbe1d3d48,0xbebabc3c,0xbe81499d,0xbe850a36,0x3ef0f8dd,0xbea8f4e5,0x3efdf678,0x3f800000,0xbe88b3ef,0xbf356689,0x3f30534a,0xbe089270,0x3da838dd,0xbe795827,0xbe456078,0x3e7f6a83,0xbe07e2d6,0x3e36df11,0x3ea549e5,0x3e8f2e10,0x3e2333b3,0xbe6417e4,0x3ef2e5ee,0xbe1f25e7,0xbef91fb1,0x3e79885b,0x3c6a056e,0x3ddd834a,0x3f0bde31,0xbeba5e53,0x3e970dea,0xbe67c643,0x3ef86a3c,0x3ec66e25,0x3e5f953a,0x3eb3cd72,0xbca42ea5,0xbecb217f,0x3c52df7f,0x3d7f0abf,0xbde17bfb,0x3dc8476f,0x3d041ab9,0x3e0f11b9,0xbe479253,0xbe83801d,0xbd8b8da0,0x3e447f73,0x3d2c72ff,0xbe6f2888,0x3d18539e,0x3d96255b,0xbe9b8529,0xbe739232,0x3eefa670,0x3e3c6281,0x3ded9355,0xbd018768,0x3e44a3e2,0x3f0f5ba0,0x3e05ae6b,0x3eb2ac28,0x3c7b7d7d,0xbd9a42e1,0xbf3c1401,0x3e264775,0xbe5713f9,0x3f077b8b,0x3e6422a5,0x3caec15c,0xbe9725b5,0x3e2bb4f4,0x3d2b67ea,0x3de9d2fd,0x3d8959fd,0x3e053f4f,0x3d9889f6,0xbeaf32e0,0x3e7cd925,0x3e331ef3,0x3cab8585,0x3e7508af,0x3eeee139,0xbe6fba78,0x3e266210,0x3f30dba5,0x3e08fa37,0x3e99b88f,0x3e892a61,0xbdd86134,0xbdb7d1d6,0xbe628ebe,0xbd7c77ca,0x3d5b5594,0x3e358b75,0x3e8649d9,0xbc3d84d4,0xbdfbf79f,0x3e063be3,0xbdf9a23a,0xbea2dcf9,0xbe49679f,0x3efa0f82,0xbf0f4b6b,0xbdec1bd7,0xbe5739b8,0xbd1a6eba,0x3eed8c71,0x3e839e55,0xbeb2a610,0x3eaa786c,0x3e006148,0xbda0ab63,0xbe879dbd,0x3f201c39,0x3ada1374,0x3ed4bbf5,0xbee6897f,0xbe9bcd2c,0x3e680b1c,0x3ebde87a,0x3e989fe7,0x3f068b9d,0x3d358104,0x3d322cf3,0xbd4dab9c,0x3dba08af,0x3ee5daf2,0x3f4b413c,0x3eadf408,0x3eb062a3,0xbe278259,0x3f0d65e7,0xbec3ed60,0xbf05074a,0x3b25ca70,0x3eadbda6,0xbd01707a,0xbe2a000d,0xbdd96317,0x3eaa4a0b,0xbcab5b91,0xbeb8daaa,0xbe112354,0x3e798c46,0xbeb24298,0x3ee576a1,0x3ebaac55,0x3eaa4e16,0xbdfbaa50,0x3d54e5e7,0x3ec5c686,0xbef78d0d,0x3df6b606,0xbf0c9c7d,0xbe14294f,0xbe98cc6b,0xbe87c173,0x3e89ff34,0xbe98058d,0xbe250000,0x3e2102ad,0xbede77cd,0xbd6ab567,0xbc838397,0x3e8928a3,0x3f14fe1f,0xbe251cdf,0xbe97c404,0xbebe912e,0x3e1426ef,0x3eb4fc99,0xbe9749b4,0x3ea96eb5,0xbe214bfd,0xbe32f225,0xbe497809,0x3e1939b3,0x3f10d70f,0xbdd48612,0xbf123ace,0x3f084378,0x3e10f337,0xbddd2573,0xbebbaef1,0xbc92f7e8,0xbdeb5891,0xbde7cad8,0xbcd04ead,0xbecd0646,0x3ecba5a4,0xbf5234d6,0xbe9b613a,0x3edc8628,0x3db78b26,0xbe03da46,0xbe242aea,0xbd852ee2,0xbe007eef,0xbe26555d,0x3e8a2024,0x3dfc8b2f,0xbe3ff00b,0xbe834039,0xbe80d286,0x3e602d1c,0xbe3f7a33,0x3de55c9b,0xbf134c27,0xbde07796,0x3eae54eb,0xbe634a9e,0x3f0c4e31,0xbd3db12f,0x3db8250f,0x3e4d102f,0xbe0349b4,0x3ee9ec2e,0x3dbe6496,0xbea5c849,0xbb72becc,0x3eb55a75,0xbf51f08f,0x3c9bbbdb,0x3cfc000f,0xbe880bad,0x3dcc81a8,0x3ea085b8,0xbeae6fd0,0xbedc4d02,0xbe47f853,0xbdbfaf70,0xbea5a3f8,0x3ce2910a,0x3da7063d,0x3f07d193,0x3dc9ed50,0xbe0f1f73,0xbe89789f,0xbeeb611b,0x3ed17ab4,0x3ef5cca9,0x3ca8d5d0,0xbeb4aa2d,0xbe232555,0xbf404660,0x3ed1fcdb,0x3defdecf,0xbd6ad3b2,0x3e4304b5,0xbe9a3cc9,0x3f216f10,0x3ee0e8db,0xbd4db3fe,0xbd26e4b4,0x3ebb60ad,0xbf0d6c9f,0xbe45f73e,0xbd9e2c66,0xbe0bbf33,0xbde56177,0x3d9f73b3,0xbe6b94cd,0xbf16c13e,0xbe8865a4,0xbe112eed,0x3e0b5736,0xbf037132,0xbe539f49,0x3e103773,0xbeb135fc,0xbdf9e62e,0xbe66168b,0x3cf89a3e,0xbf13892c,0xbdbf87e0,0xbe53606f,0xbc4afb75,0xbd8b0dfe,0x3db2796e,0xbe085cec,0x3e9189e4,0xbe30e903,0xbe46e8fe,0xbe6597dc,0x3e1a0cf8,0xbe59a214,0x3eb217f6,0x3d5adf3f,0x3dc47bf3,0x3edd937e,0xbea524da,0xbcbee382,0x3e4ea9b3,0xbd9a6c5a,0x3d918d32,0xbef9ce9e,0x3cfc0f95,0xbe934b91,0xbe504cc7,0x3dc57760,0x3f4e5a59,0x3eb4fe92,0x3d656a0c,0xbe0f9374,0xbd5d24ef,0xbe1a05eb,0xbd8f1fc9,0xbe8f10e2,0x3e3cd52e,0x3ef01569,0x3e6e4a87,0xbebed91d,0x3eb75320,0x3edf7bd4,0x3eed5218,0xbe1d5f66,0x3e889f96,0x3d0c483b,0xbead189d,0x3d5be7f0,0xbe6a6b02,0x3cc5d31e,0xbbd71564,0xbd81ade9,0xbebbe7c4,0x3d283b21,0xbd641569,0xbd0accae,0x3db1e021,0xbf50260d,0xbdfed5d3,0x3ec5b379,0xbe08e1df,0xbe866a67,0x3d8cc991,0x3e9cac57,0xbdd84e6c,0xbeb99147,0x3db8e47a,0x3f16a858};
