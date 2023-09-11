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

const s16 BayesF32_Dims1_s16[3]={0x000A,0x0005,0x000E};

const s16 BayesF32_DimsBench2_s16[18]={0x0000,0x0000,0x000C,0x004C,0x0018,0x00CA,0x0024,0x012F,0x0032,0x0187,0x0040,0x0219,0x004E,0x028E,0x0062,0x030A,0x0076,0x03D8};

const u32 BayesF32_Inputs1_f32[140]={0xbd100bcc,0x3d014d09,0xbcdcee9e,0x3f8389d9,0xbb27c3ab,0xbdc39d5c,0xbc19509e,0x3d68ce98,0x3c34f509,0x3b6f875b,0x3ced89ac,0xbd89adc5,0x3bd1e0bf,0x3d3df0fe,0x3cd5f150,0x3bfd5fab,0x3f7e7f3f,0xbd548baf,0x3d9e7ac3,0xbc21dff2,0x3c197bbf,0x3ca0d0c7,0x3cda0989,0xbc92c4d8,0xbd04f1f4,0xbd9339b2,0xbd03ab72,0xba8995e6,0x3f80dbfe,0x3b57a93e,0x3c105dac,0xbd2bef4e,0xbc9fe3d8,0xbcf7781a,0x3d9137e7,0xbcef4510,0xbd5eb2c7,0xbd3a8641,0x3cd5ff8f,0x3be1acec,0x3d848637,0xbbb237d4,0x3c3334dd,0x3c9d4df0,0xbce648b3,0x3f845988,0xbccdb3be,0xbdc912e7,0xbd4082b1,0x3c6d61ec,0x3d0577e2,0xbc1410ea,0x3dd7e908,0x3cd03dc5,0x3c5153c4,0xbcd78bf9,0xbc0e0c2e,0xbd16e0a4,0x3f7adb28,0xbdd41bf4,0x3b3af454,0x3d568b17,0x3c9cd6b1,0x3daad266,0x3d1e3d95,0xbc8a2f2e,0xbd113b93,0xbd5d9e25,0xbd982278,0xbd1e0b45,0x3f7bede2,0x3c0afac8,0xbccdbb5a,0x3d870701,0x3d9912ab,0xba17be6c,0xbbba1a04,0x3cee4ae6,0x3ccd2ffd,0x3d58b8a9,0x3cd92b5a,0x3caa1c47,0x3caa3100,0xbd13caee,0xbc401b7b,0x3ae356ad,0x3f84bcbf,0x3cfac04e,0x3c9ad789,0xbb349b83,0x3d919356,0x3cbd996c,0xbd55d2ff,0xbc2c8091,0x3c443392,0xbd1a8a87,0xbbd8100b,0xbd180cd3,0x3d0e4ec5,0x3b9f6e7a,0xbd84ab00,0x3f8241d8,0xbae167d7,0x3d8816ab,0x3c256a41,0x3d84309d,0x3d1c2a86,0xbc5f6840,0x3d2deb7c,0xbc3db6e1,0x3d0dc63f,0x3d4249a0,0x3cb7a406,0xbcfc433b,0x3d69c5c0,0xbd575525,0x3f85950e,0xbcfc566f,0xbd4c9e68,0x3d6a1f2e,0x39379de9,0xbd67d93e,0x3bfb2031,0x3d0f9c8c,0x3b9cb944,0x3cbc8019,0xbdb4bfe1,0x3f78d04c,0x3d01d043,0x3d0ccccd,0x3cb24cab,0x3d3668c2,0x3d8a76bd,0xbc87fa7c,0xbc978387,0xbd0f572b,0xbd6b0f73,0x3d1a9eba,0x3ba90b82,0xbbf43ab4};

const u32 BayesF32_Inputs2_f32[138]={0x3f7e6d8d,0x3b560992,0x3d11fcc8,0xbdb92d74,0x3d33dd75,0xbd2e44f2,0x3d911948,0xbd859867,0x3c02cab8,0xbadb2eff,0xbce92cc8,0x3c32c31a,0xbdbe48c5,0x3d121905,0xb9f2ce6a,0x3f72430a,0x3bff8e6c,0xbd1bdf91,0xbac9679b,0xbcb2faf7,0xbda6eeae,0x3c6405b4,0xbc937ce5,0xbc975fdc,0x3a8d3045,0xbd8e2edc,0x3f7a7285,0xbc76ccc2,0xbdcdec89,0x3d6aa507,0xbce8dc1e,0x3c73499a,0xbd4e41db,0x3d433441,0x3c082839,0x3d25e83f,0xbc106253,0x3d39427e,0x3f83dc5a,0x3c805992,0x3c8e9f6a,0x3c083303,0xbbcb5f18,0x3d2051f2,0xbceca4dd,0x3d6c47e2,0x3d49bff8,0xbd006299,0x3dc4fa04,0x3ce1e1c8,0x3f697b77,0xbbcc361a,0x3d1aa1f4,0x3da50835,0xbcf43f5f,0x3d21d378,0x3d90bb29,0xbcbe5201,0xbc553b5e,0x3d3a8793,0x3c7af242,0xbd1d0bd8,0xbaf5f566,0x3d07e73d,0xbc1e5304,0xbda94df0,0x3bb77c75,0x3f6522c8,0x3d00093a,0xbc6168d0,0x3d8a4b85,0x3d70ba6a,0xbb4e893a,0xbcefe650,0x3cb7a583,0x3c823d8a,0xbd092c45,0xbd95efea,0x3f821c44,0x3d5ad1c4,0x3c43dce2,0x3ca84447,0x3c91cb17,0x3b18d194,0x3cb6c679,0x3cf5b3fc,0xbcca85ac,0xbd277dbc,0xbc0339b6,0x3d085d91,0x3cb42852,0xbc8f0267,0x3d383751,0x3d1d3291,0xbc839aba,0x3d050c11,0x3d58e783,0x3d2450a0,0x3c84b8be,0xbcd2621d,0x3f8172d6,0x3bf9678a,0x3d160ed5,0x3d28acc2,0x3dc7d6e9,0xbceccb92,0xbe013a2a,0xbdebebf8,0x3d87afca,0xb95ea1a9,0xbde0739e,0xbcf4e6bc,0xbd310982,0x3d89ef58,0x3c7bb139,0xbd04941e,0xbd3d46b7,0x3d9fcc50,0xbc9d3608,0x3f7e374a,0xbcecc174,0xbd0f2637,0x3b0b3e33,0x3d02122b,0xbd9b4b43,0xbd5d10ca,0xbc6f6bc9,0xbd589502,0x3cbdf07b,0x39e3664d,0xbce73343,0xbcacb466,0xbaf0bf56,0xbbb51ea2,0xbd37b529,0xbd8e322d,0x3d3c5144,0x3b84f778};

const u32 BayesF32_Params1_f32[146]={0x3f7ceb0a,0xbd6ad769,0xbcf5697e,0x3d6944c1,0xbc82c2be,0xbc899008,0x3d1c6747,0x3a980196,0x3db0508c,0x3d65fce9,0xbb0bea28,0x3e2353a0,0x3b652795,0xbd34b796,0xbcaa7fa4,0x3f7d01cd,0x3cad27ec,0x3c8e7244,0x3d465d10,0x3c6278b0,0xbd9902a5,0xbc8bf597,0xbc8287e2,0xbc7e80f9,0x3d8d10d4,0x3b17c9e3,0x3c966839,0x3cde1990,0xbd599788,0x3cf91505,0x3f714fe0,0xbb2ef079,0x3cd46af1,0x3c8481f1,0xbcc8a762,0xbad7d6c7,0xbcf585a5,0xbca5b605,0xbace4f95,0xbd03f633,0x3ca71a85,0xbd229d4d,0x3d083db9,0xbcff1b63,0x3cae30a6,0x3f830bd5,0x3c882a96,0x3d205c20,0x3cab4d7c,0xbd1d0cf9,0x3d0a1898,0x3d1b6fd8,0x3c73bb69,0x3d0fd265,0x3d793cff,0x3d2ff24b,0x3c779a0e,0x3c1eab6e,0x3c10ed30,0x3d90252d,0x3f7c002e,0xbc7a67e3,0x3ab58003,0xbdb756b2,0x3c85ecfe,0x3cd69be4,0x3cecd6e8,0xbd2c1c3f,0x3c33671b,0xbaa94116,0x3c4455a7,0x3b25b3cd,0x3a181c3f,0x3ab77872,0x3955fb53,0x3846e054,0x3a3c3b68,0x3bbdd4a1,0x3ba1fada,0x3ba4d9d3,0x3bfdba05,0x38ac164b,0x3aca21ac,0x3858947c,0x3bdc439d,0x3a572b16,0x3b19de22,0x3c023ab2,0x3bd2e6ae,0x3bb77cc5,0x3ba2f821,0x3ba325f1,0x3c35c87f,0x3bb10234,0x3c045a50,0x3c159c8c,0x3c346cc4,0x3b94862f,0x3b9829b8,0x3c06e497,0x3c2a6c86,0x3b7f844f,0x3c60e02d,0x3bdc5c5f,0x3b1bf980,0x3bbb896f,0x39f48aa4,0x3b1a824f,0x3bf51d6b,0x3bcf7af7,0x3c8071a0,0x3b765108,0x3aacb26b,0x3c4eaa6f,0x3b2f34cf,0x3c9283ed,0x3b2c7c97,0x3b387f92,0x3be5c025,0x3abbe754,0x3a5686a2,0x3bb08fac,0x3b7fde24,0x3b613af5,0x3b59247a,0x3be873df,0x3c10c125,0x3abfc5b0,0x3b76cc61,0x3b98e25f,0x3c0bc70e,0x3baaa3f4,0x3b943e13,0x3bbbd8e8,0x3bceec8c,0x3c131cd0,0x3af3356d,0x3b9d46fb,0x3bf84491,0x3b6a20b5,0x3d888889,0x3e888889,0x3e6eeeef,0x3e2aaaab,0x3e888889,0x2f579802};

const u32 BayesF32_Params2_f32[1149]={0x3f6c3932,0x3c26fd29,0x3cda9d12,0xbc646e1b,0x3d1aa23e,0x3d86fffa,0xbb421946,0xbd4dc146,0x3d476460,0x3ce22b26,0x3ad4c064,0xbd215099,0x3d115f24,0x3f7b71aa,0x3c160d0f,0xbc984708,0xbce3eb3a,0x3c3ab44c,0x3b85211f,0x3cbc79ed,0x3c66f106,0xbbe2f544,0xbce5f1d0,0xbba0dc76,0xbc89c785,0x3d77d66d,0x3f793915,0xbcc58faa,0x3cde104a,0x3d233868,0xbb5530c9,0x39ab42a1,0xbd1a2f77,0x3d226bcd,0x3c885f90,0x3cbf5956,0x3c052ef9,0x3c6b0cbc,0x3b4791ae,0x3b19f1e3,0x3c25897e,0x3adbf2b1,0x3b06a352,0x3c18001a,0x3b9063d8,0x3b398223,0x3bbac910,0x3c0cd19d,0x3bdf3ee5,0x3ba0a6ac,0x3c1fb7d8,0x3bd5b552,0x3bc5a8f1,0x3be7fc47,0x3c0974f5,0x3c22c3f7,0x3ac229a7,0x3bba9eba,0x3b7cc92a,0x3be5af98,0x3b6ea50d,0x3b83099d,0x3a9c2767,0x3b4a957b,0x3ac2b493,0x3ba0b0b7,0x3b178cf7,0x3b68b360,0x3b7e24a2,0x3bea7d26,0x3be02aa9,0x3bbc2d7b,0x3e4ccccd,0x3f088889,0x3e888889,0x2f7b00bb,0x3f6e76f5,0xbd44acb2,0x3ac92dd3,0xbcf55ddd,0xbd3958fc,0xbbe7bfe2,0xbcda3469,0xbcab2696,0xbc57476e,0x3cd996b9,0x3d0e77c0,0xbd56bdc5,0xbbab10e5,0x3f7a9ac9,0x3c103476,0x3bb54be9,0xbc5e0a0f,0xbcb150e3,0xbbcb5d95,0x3be3b39d,0xbc045d54,0x3d8d9eb9,0x3d0f9638,0x3b79a9a4,0x3b9a46f4,0xbd057bcc,0x3f846652,0xbca1c57c,0xbd11589f,0x3ab83e09,0xbc8f0121,0xbc86fe11,0x3cf63938,0xbb8dd750,0x39809b99,0xbc5e7c39,0x3d05c1e7,0xbc6f9500,0xb9b4d965,0x3f8627bd,0xbd0bb586,0x3d847286,0x3bc5ffb5,0xbd434cab,0xbc9d4838,0x3cd2aaad,0xbb6c759c,0xbd8f5af1,0xbcbd3db1,0x3cd4bc1e,0x3d83edb4,0x3c1a74e6,0x3f87ab2a,0x3d1cc640,0xbccaa82f,0xbcfae6f3,0x3d42a1ac,0xbd99ba59,0x3a8d866f,0xbc479918,0x3ad5d216,0x389bb1d1,0x3bcc47b7,0x3b2f1118,0x3b9b6e1f,0x3b8b7dab,0x3b859a17,0x3b99d041,0x3ac299e6,0x3bc72f92,0x3ba18445,0x3aef6701,0x3aff256b,0x3baedbdf,0x3c0119f1,0x3c2cbec3,0x3b4c723e,0x3ba86377,0x3c045328,0x39701111,0x3bc6e5cb,0x3b926d06,0x3a577889,0x3bc45809,0x3c43c0a0,0x3bc29395,0x3b6dc5dc,0x3c0cf467,0x3c1f85c7,0x3ba66c98,0x3ac085b3,0x3b2805b1,0x3c96c889,0x3b84703d,0x3b61dd8a,0x3b4463c9,0x3bb6906b,0x3b5367ce,0x3b7bdaa0,0x3b03949c,0x3b7fce6f,0x3a566405,0x3bc11c83,0x3c43fc63,0x3c0a9991,0x3b54b999,0x3c2d6c19,0x3b9622de,0x3c1a1675,0x3ad27bb1,0x3b0d7659,0x3b70c8a6,0x3b0323d7,0x3be025ea,0x3b3c1b9f,0x3c1ca308,0x3b7f43d9,0x3bc9a499,0x3b991ca8,0x3c16e17e,0x3e088889,0x3e6eeeef,0x3e6eeeef,0x3e4ccccd,0x3e4ccccd,0x2f568727,0x3f723088,0x3be1d637,0xbcda1522,0xbce3000f,0x3b6437c1,0xbd04d235,0xbaec7568,0x3ceeeafd,0xbcec1789,0xba7b8618,0x3ad8c2de,0xbc82e109,0xbd8d9262,0x3f70643f,0x3d406e62,0xbd2a8dd5,0xbd2538ca,0xbe01a11d,0xbccc0071,0xbd1b5fcf,0xbcc83201,0xbd25d12e,0xbb51e3b2,0x3c01441b,0x3d2920aa,0x3b78482d,0x3f7bc457,0xbb492c5f,0xbd69d468,0x3d252a8b,0x3c3e0587,0x3cfd4d96,0x3c3fb04f,0x3d565238,0xbd3c3ac1,0x3c5ec08c,0xbd5e003e,0x3c7fccb4,0x3bed066f,0x3f8625ca,0x3a9fec30,0x3cabebc6,0xbcfaca20,0xbc89ac17,0x3c9b8282,0xbbe276ca,0xbd30b0b7,0xbc04afdb,0x3c38be16,0x3bc410cb,0x3c0e87ec,0x3bd8b2aa,0x3b788cfb,0x3c618d18,0x3b8f806b,0x3c0b7bd7,0x3bacc3ac,0x3b821fe6,0x3b177281,0x3bb46dfa,0x3c4a2279,0x3b86cee7,0x39043202,0x3bfd6fcb,0x3a7ac2dc,0x3c194e56,0x3c84f059,0x3aa031db,0x3ae00121,0x3bac173b,0x3b865710,0x3a33c5f7,0x3c1077a9,0x3bdf2186,0x3b681dda,0x3b85b43b,0x3c324541,0x3bae11d4,0x3b834a9f,0x3b9de228,0x3a93fd76,0x3c120524,0x3bb10a96,0x3bc44d3c,0x3bf873d8,0x3b994f09,0x3be7723a,0x3b0c54fd,0x3b12fccf,0x3b6eae32,0x3b5af3e3,0x3bb01a98,0x3b4f3f6e,0x3b2e6e92,0x3b7d8561,0x3bd398d2,0x3e99999a,0x3e088889,0x3eaaaaab,0x3e6eeeef,0x2f72ea8e,0x3f833b60,0x3c458a65,0xbcfdf994,0xbc8231bd,0xbc6b3549,0xbcda6309,0x3d3e70a5,0xbd0d8e6a,0xbcf9acb9,0xbc298f1c,0xbc6213be,0x3b3be94d,0xbb45260e,0x3d17dd3f,0xba9ff1a3,0x3f7e1af0,0x3cda51b9,0xbc64e35c,0xbce14e15,0xbc9560bc,0xbc98727c,0xbc61aec1,0xbd19762f,0xbb5a8039,0xbc933267,0x3c69dc18,0xbd38ba22,0xbcd54e79,0xbd6b1b3a,0xbb5eb0d2,0x3f80ff4b,0x3d266009,0x3bf2b232,0x3c2e1524,0xbc7b54f0,0xba6c654d,0xbbd42686,0xbcce4a2d,0x3b5483a1,0x3d54c476,0x39fd1049,0x3c9400c2,0x3bba96f5,0x3b5145b8,0x3b1b2021,0x3a689218,0x3b84177f,0x3bd8d9e5,0x3bb834b7,0x3c0fb73d,0x3b1291da,0x3bf37536,0x3b40891b,0x3baa3d4c,0x3b8dc5c6,0x3a7d6eb7,0x3bd6d77e,0x3b869578,0x3bfaeed8,0x3bcdb8d9,0x3b9a9e47,0x3bf8f5a5,0x3bb457f2,0x3b770201,0x3b4ecb3b,0x3be18ccb,0x3b85f05e,0x3bc6471e,0x3c4ca027,0x3b4d73aa,0x3bca900f,0x3b6eb9df,0x3b6a8ce3,0x3ba14430,0x3c176d2e,0x3b21f371,0x3be25222,0x3c26586d,0x3baa11b6,0x3c1d5971,0x3c29b137,0x3bafdfc8,0x3bf6eb66,0x3b8d454b,0x3e6eeeef,0x3eaaaaab,0x3eddddde,0x2f8b2073,0x3f6c314c,0xbd083bf7,0x3d2403ae,0x3acda0da,0x3db9c848,0x3cbdb64a,0x3d37c24e,0x3daa5264,0x3c59ae7c,0x3c5db63a,0x3be703ca,0xbcb43f85,0x3d2fef1e,0x3dbdd3c3,0x3d9934cf,0x3f82a34d,0x3c6d4bdc,0x3aa4905f,0x3d835d27,0x3d7d2d35,0x3cc3ed05,0xbb94fc4e,0x3d1350c8,0xbd1dce33,0x3bc334ab,0xbc03e9b0,0xbb088c68,0xbc6a25a1,0xbd180cf7,0x3b8f8a67,0x3f824702,0x3c386027,0x3c86308a,0x3b1c2abf,0x3c76885e,0xba4ddcf5,0xbc1afd2d,0xbd1aa10d,0xbcd15dbf,0x3d89ee89,0x3bc3d431,0x3c782135,0x3b955edf,0xbb85ad6b,0x3cb9e6b5,0x3f7f082c,0xbcedd8d8,0xbd3cb4c0,0x3cfb3300,0x3c0fc9ea,0xbd1eca3e,0x3c30bdd6,0x3b845f9a,0xbc8b14d3,0x3c859301,0xbd1483dc,0xb9a8017d,0x3816c7f6,0x3d472776,0x3b5c2894,0x3f79df27,0x3aaaafe3,0x3d1fc7fa,0x3d6017e8,0x3b562683,0xba47b2a0,0xbcc2d59f,0xbbbb15b7,0xbd8532c7,0xbd6102ac,0x3bf6f315,0x3a2f5acb,0x3b33cea3,0x3bac02fa,0x396d9e06,0x3965460e,0x3af088d7,0x3b942f82,0x3c93ae9c,0x3bc3c4f1,0x3b8ca3c8,0x3af6e0b4,0x3baef5c1,0x3a328be2,0x3b999420,0x3b33be7b,0x3b95056f,0x3a597896,0x3bf3c03c,0x3c0ef43e,0x3b266e09,0x3b5d3409,0x3b8bab4f,0x3bc14a4a,0x3a757269,0x3c08ffb4,0x3baae24a,0x3aca2d4f,0x3b9ba81f,0x3a04d0d6,0x3c74f067,0x3b299d1c,0x3bda3a4e,0x3a6e4126,0x3b5613fb,0x3bc65537,0x3be4fd4b,0x3b7fab64,0x3b8eaa96,0x3ac85201,0x3b3885ff,0x3c3dd304,0x3b839e9e,0x3b66df7a,0x3c02e756,0x3bd1c04b,0x3b171d16,0x3c49f0f8,0x3be3b34f,0x3adfb705,0x3c00ade1,0x3c32aed8,0x3ba2882f,0x3b87cdf0,0x3c0105a2,0x3b70beaf,0x3bc617f1,0x3c11e932,0x3b7aa856,0x3bd81d00,0x3b9b7151,0x3b470462,0x3c047b84,0x3bcb85db,0x3b7a16fd,0x3bb04abb,0x3b50ad56,0x3bb69b20,0x3c438f06,0x3b804dce,0x3e088889,0x3e088889,0x3e4ccccd,0x3e6eeeef,0x3e99999a,0x2f577040,0x3f7ddc82,0xbb90e1a5,0xbc87f454,0xbb433c14,0xbc52f444,0xbce419b9,0xbcf5f7c1,0xbcb48e92,0xbd22f82f,0x3c885cb1,0xbcc235f0,0xbbd711f3,0xbc01bb35,0xbc0686fa,0xbc403275,0x3f80a62d,0xbc89bca2,0xbda19acc,0xbc2d431d,0x3ca51079,0xbb8fd581,0x3bbb4dcc,0x3d3a52a8,0x3d6e6b82,0x3c2f3f04,0x3b867afd,0x3cb4b0c1,0xbcf41321,0x3c177530,0xbbfabf57,0x3f7b1b14,0xbb953564,0x3bac0357,0xbcd66919,0x3c150018,0xbbddd7f0,0xbd284a52,0x3d0c99a1,0x3a8d9c37,0x3cd1d29b,0xbcb23f74,0xbd26b264,0xbd2e7ced,0x3d57360e,0xbce76c67,0x3f76fa38,0x3c8b6d3a,0xbdc6c823,0xbcb7a7f7,0x3c7d372f,0xbd8880f2,0xbcefe691,0x3cd6f068,0x3cc333dc,0xbd003961,0x3c530fd3,0x3c1dcbf3,0x3bcf5525,0x3bbf69be,0x3bc5feb5,0x3b7b8fd4,0x3b806418,0x3be92804,0x3b5c316c,0x3c0263bc,0x3c5ff1da,0x3b83c91a,0x3b2cd249,0x3b84f205,0x3b40b75f,0x3a9e43ef,0x3be0e1d7,0x3c1c629a,0x3b99d9f0,0x3b56ada2,0x3b48457e,0x3c0279d3,0x3c506b9e,0x39e8d839,0x3ca39c31,0x3b37ac59,0x3bdfc515,0x3af6e740,0x3b268dcd,0x3bdb41c1,0x3bdf6697,0x3c06b96f,0x3b4e03c8,0x3b21c24e,0x3b82d4c7,0x3b4b6cde,0x3b487eb2,0x3c13b24a,0x3b5ba9ed,0x3b6864b1,0x3b63bc38,0x3b837e2a,0x3bb54870,0x3bfa9c78,0x3c168b0a,0x3c4c69bb,0x3c1054f9,0x3b94671a,0x3b9bb9cc,0x3a7c4f62,0x3a7e0d93,0x3bc3eadc,0x3c8432b0,0x3b92a45a,0x3bca41d1,0x3c18a3dc,0x3bb4b141,0x3eaaaaab,0x3e2aaaab,0x3e99999a,0x3e4ccccd,0x2f7de56c,0x3f838976,0x3c87735d,0x3c5a0f4b,0x3c0e7393,0x3d993091,0xbd0730bd,0xbca9a6a6,0xbc94f48f,0xbca3ed3f,0x3c99c8d7,0xbc32e481,0x3cceccd3,0xba50072a,0x3c18ddcd,0x3c259330,0xbc1112e1,0xbaba5eb6,0xbd0b19fe,0x3cbf6628,0x3c37a22b,0x3b9610e3,0x3f7fe539,0xbd0ab161,0xbc09651a,0xbc480600,0xbc824d0f,0x3b83b426,0xbcc16c0f,0xbccf0ffa,0x3b97f3ab,0x3bf28f4a,0x3d4036b5,0x3be21d9c,0xba88f7e8,0x3c61fbe6,0xbca133a2,0xbd097ad2,0x3b9f5047,0xbca96e07,0x3b5b305a,0x3c830d23,0x3c0324a7,0x3f812e4b,0x3cb2b851,0x3cc41c98,0xbd09f031,0xbd855b23,0x3d1cae10,0x3be6aa2e,0x3c682a72,0xbcb29816,0xbc23b720,0x3d2f517d,0xbc805289,0x3b6e4ea4,0xbd17a424,0x3beb6003,0x3c689a21,0xbca25b50,0xbd024a1d,0x3bbdd721,0x3c244785,0x3c0757e4,0x3c2ff6f5,0x3bf231d1,0x3b919b73,0x3c096df0,0x3af30988,0x3bd643ed,0x3c3518cb,0x3c28f7ef,0x3b9fcbd8,0x3c223bd5,0x3b69539e,0x3b9338df,0x3b06a3ad,0x3b6fa337,0x3b2d1dda,0x3b9ea78b,0x3b154bc8,0x3c04fe84,0x3c09b023,0x3c7349af,0x3bea7bb1,0x3ba63462,0x3be2b24d,0x3c6448d8,0x3bcb06cf,0x3beeef7d,0x3bfd30f0,0x3bf1c7c4,0x3bcaa13c,0x3c1a5a4d,0x3b98fdb1,0x3ba49040,0x3c155ef5,0x3b1c7a85,0x3b589631,0x3b7a99bc,0x3be744d6,0x3b6592f5,0x3be1cd96,0x3ac4f3c9,0x3bf2da25,0x3c0b23c1,0x3b49f03a,0x3befb2a0,0x3b98f843,0x3b8f7e63,0x3bc9658a,0x3bd98837,0x3bdc42bb,0x3b85e45d,0x3bb23b39,0x3ba93739,0x3ba3c8c8,0x3b842165,0x3c4835e4,0x3bd67e2a,0x3b8285db,0x3eaaaaab,0x3e99999a,0x3ebbbbbc,0x2f88d443,0x3f83355e,0xbbaa8992,0xbd2498e7,0x3d228d3d,0xbc1b7769,0x3d4116a0,0x3abef305,0xbd34b664,0xbb0f3569,0x3d676a92,0x3c8ce2de,0xbd2a7e26,0x3cfb0dcf,0xbc6dcefc,0xbc170f48,0xbc5de367,0xbcb0d3ad,0x3c55b46c,0xbad78f7d,0x3cca1fc6,0x3c575dfc,0x3f7f5a5e,0x3c2c6277,0x3d1f59e4,0xbcd1b0e6,0xbc1ee143,0xbca7709f,0xbc36ba80,0x3bb73e99,0xbd375c28,0x3ca3051e,0xbce54b72,0x3d984278,0xbcdd3c32,0xbc579665,0xbd2ef079,0xbce684a6,0xbc339f8e,0x3cae4422,0x3c0736b0,0x3bd6566b,0xbc091c33,0x3f84aedc,0xbd661a63,0xbc410e1d,0x3cc6bc35,0xbda0aa0b,0xbad9dffd,0x3ae3f9f6,0xbdc67106,0x3cfd1abd,0x3bcac036,0x3c2cc426,0x3ce4f448,0xbd25e1fa,0xbd2b2414,0x3d24d3b7,0x39866ebe,0x3e12d078,0xbd35ab80,0x3c817be2,0x3875b399,0xbbe7e04b,0x3f7d772d,0x3cd3b677,0xbd10342a,0x3ce04642,0xbd54b1cb,0x3d0faf8f,0x3d53b79b,0x3bb4a23d,0xbcc9541a,0x3d400e4c,0xbc81d2a8,0x3d38255e,0x3d269bc8,0xbd255a0e,0x3d67c524,0xbc2707d6,0xbd2bd023,0xbca6975e,0x3c354ede,0x3c84fc8a,0xbdcb9e4b,0x3f83dee7,0x3b9ed575,0x3d64f594,0x3c91c890,0xbbc22c76,0xbb9eb3d2,0xbb99671d,0xbc48875c,0xbc94bf55,0x3c8bc7c6,0xbbbfaef7,0xbc8e8f15,0x3cf42255,0xbac5a254,0x3cd4da20,0xbc9caad6,0x3b1b5e3f,0x3be1619b,0x3c185f0f,0x3c03a69c,0x3ba5e28f,0x3a559ac7,0x3c486a89,0x3c12574e,0x3b8c7e29,0x3c8fdad2,0x3c8deb15,0x3bb452cc,0x3bad542b,0x3bba6115,0x3b148644,0x3bf3f7d9,0x3b8179f1,0x3b33d759,0x3be7a4a3,0x3babbfde,0x3c253a99,0x3bf1624c,0x3be331e9,0x3aafb6d9,0x3b8b6429,0x3b3282ee,0x3b6a8c41,0x3b8e585e,0x3b006170,0x3b14a2f0,0x3acebf96,0x3c1e505b,0x3b41371d,0x3c88387a,0x3b788442,0x3b179402,0x3b03ee63,0x3b0e7ed1,0x3bc409bc,0x3bc4be86,0x3c6d2870,0x3a189fc8,0x3a58722e,0x3b903d5b,0x3aea1d9c,0x3afdeea1,0x3b3085bc,0x3b8db7d3,0x3b39f412,0x3c27468f,0x3aa49050,0x3c159eea,0x3a81fce0,0x3a67f11d,0x3bfef8fe,0x3a70963b,0x3ba4a1d3,0x3c4e4a3e,0x3bbab4c6,0x39c55ead,0x3ad1920c,0x3a66edad,0x3b9ff232,0x3c06eade,0x3aae299a,0x3a4c7a0f,0x3b9d488d,0x3b8794b5,0x3bf79de1,0x3c4cff9e,0x3bc7127d,0x3b6e7772,0x3bb9ebdb,0x3b9b2263,0x3b4082f4,0x3c184a8f,0x3be05a66,0x3c29b19b,0x3c167fbf,0x3b84a6a4,0x3b931132,0x3b022b32,0x3ba2fdc1,0x3bff4b2e,0x3bbc6eb8,0x3b323d6c,0x3b5b5b5a,0x3b849fdd,0x3bc42c9d,0x3c26b0c8,0x3b999022,0x3c601401,0x3b79547a,0x3c05e0f4,0x3b2c5940,0x3a90757c,0x3ba9f4cb,0x3ba41d71,0x3b1d70af,0x3c1d4ba0,0x3e888889,0x3e4ccccd,0x3e088889,0x3e4ccccd,0x3e4ccccd,0x2f66ed13,0x3f82343e,0xbc7ab92f,0xbc9ea94f,0x3cafab34,0x3d81f057,0x3ba25087,0xbd0b04ac,0xbc9a297e,0x3c3851ca,0x3d2288c0,0x3cee4357,0xba65d079,0xbc7c7e25,0x3a73f3f7,0x3c6155a6,0x3d01e9d5,0xbdb9b3f6,0xbbf3abca,0x3c8fdf1b,0x3d43409a,0x3cd992d9,0x3f7c44b0,0x3d0117ad,0xbc0aced0,0x3c196eb1,0xbcd6018f,0x3ca7dd37,0xbd042f84,0x3d2aae73,0xbb910894,0x3cd43b90,0x3cfde1f9,0x3af50c8d,0x3c7ab6bf,0x3d2b6fa8,0x3b37e6fb,0xbcb7be7f,0xbdc22961,0xbb25c94f,0xbd52da3c,0xbbf48e8b,0x3cc67932,0x3f80ad52,0x3b9b75f4,0xbd4ee845,0x3ab906be,0xbd37c857,0xbc192e27,0xbcd00a60,0x3c7c6c3c,0x3ccb2fd4,0xbd09aa90,0x3bb8dbf1,0xbd139e36,0x3b272294,0xbce70c15,0x3d894b27,0xbd2df314,0x3af2d9c3,0xbbe34624,0xbc0594d3,0xbcb37c90,0x3cd39dac,0x3f7868d1,0xbcf815de,0xbd07b7f1,0x3d861274,0x3c759eff,0x3d24db5e,0x3b4e9768,0xbbd69ff5,0xbd18cbbb,0x3c2a41a5,0xbd840b72,0xbc90d51c,0xbc49fde3,0x3c418641,0xbba30360,0xba8ea650,0xbb9c3fd6,0x3b0ebb20,0x3b808d20,0x3b0aff70,0x3b1932e3,0x3b9dab31,0x3b191c25,0x3bad8f2f,0x3b3c9def,0x3b3a7fbb,0x3add3539,0x3c26f7cf,0x3c28a959,0x3bbcb443,0x3b2f15cc,0x3b2fa294,0x3b837e38,0x3bcb1365,0x3c2250df,0x3b83ca2e,0x3a93aebe,0x3b61c139,0x3b93302f,0x3ba0c602,0x3aeebf90,0x3a69e82b,0x3b823c0b,0x3ba9cbc9,0x3c0cdb4f,0x3bbc6e91,0x3b6341d8,0x3c388f59,0x3afc35d2,0x3b92ac56,0x3b8904b5,0x3ba8dadf,0x3bac2b1f,0x3b86458b,0x3b4e7a1a,0x3b52208d,0x3babe0e0,0x3c0ac885,0x3b953512,0x3ba10f31,0x3c1d02e1,0x3c2fe16d,0x3c4e5e33,0x3c2a2204,0x3ba801b8,0x3b8f0615,0x3b72dfa6,0x3bd9dccc,0x3c119758,0x3bf3d559,0x3b9ed658,0x3c2d8087,0x3b87f046,0x3c44ca3e,0x3b39e28e,0x3b872e62,0x3baded4c,0x3bc2e5b9,0x3bc92d35,0x3c0a8612,0x3ba4d59e,0x3c182c44,0x3b8279f1,0x3bb5b4a0,0x3b8c1741,0x3c2905dd,0x3b896fa4,0x3c6cab82,0x3be05808,0x3be21dab,0x3b4fd4f3,0x3bb030d7,0x3c75bbc6,0x3c0f0424,0x3c023cab,0x3b279387,0x3c231b6d,0x3e2aaaab,0x3e888889,0x3e888889,0x3e99999a,0x2f5d4ae5};

const s16 BayesF32_Predicts1_s16[10]={0x0003,0x0002,0x0004,0x0003,0x0002,0x0004,0x0002,0x0003,0x0004,0x0001};

const s16 BayesF32_Predicts2_s16[9]={0x0000,0x0003,0x0002,0x0002,0x0000,0x0003,0x0000,0x0002,0x0001};

const u32 BayesF32_Probas1_f32[50]={0xc44a8d01,0xc416aec5,0xc322f608,0x41547a33,0xc30782eb,0xc4a05753,0xc43fec14,0x418a5f04,0xc33ee18a,0xc31df1a7,0xc3084eed,0xc422ac19,0xc30fb46a,0xc3baec5a,0xc2bdd154,0xc406a173,0xc41a6a30,0xc3274102,0x41872cec,0xc30c5def,0xc499c319,0xc44ca755,0x416521af,0xc341ba82,0xc32789a9,0xc2de018a,0xc4200604,0xc30fa179,0xc3adfcb3,0xc2a1025d,0xc49a9672,0xc4466860,0x419b10e6,0xc34d3724,0xc32e6f9d,0xc427f5af,0xc41e6ae4,0xc327636f,0x4193c4b9,0xc30616f9,0xc5363b5f,0xc42c51be,0xc2623c21,0xc356e3f6,0x41886a0b,0xc3bced46,0x4192ce91,0xc29415fe,0xc2506338,0xc3b052ab};

const u32 BayesF32_Probas2_f32[36]={0xc32a4eab,0xc385e2b2,0x41825388,0xc36a9c64,0xc30cab9e,0xc38f9e8e,0x410b7a52,0xc379a144,0xc329dbc1,0x418313c5,0xc5463256,0xc269091d,0xc307cb21,0x4194059f,0xc317335b,0xc35b3a60,0xc301c09b,0x4194cdb0,0xc50cf275,0xc30a54c4,0xc34b8463,0xc305aa7d,0x419c57d1,0xc35623dd,0xc3e7d10b,0xc30d0be2,0x41dcf4a2,0xc3a8373e,0xc3a4675a,0x419c6975,0xc30fd14b,0xc4112cde,0x41a841f9,0xc2f7b44a,0xc39650c6,0xc33c35fa};
