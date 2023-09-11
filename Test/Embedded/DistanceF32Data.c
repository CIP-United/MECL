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

const s16 DistanceF32_Dims1_s16[2]={0x000A,0x0023};

const s16 DistanceF32_Dims9_s16[12]={0x000A,0x0023,0x0004,0x0003,0x0004,0x0004,0x0004,0x0003,0x0003,0x0004,0x0002,0x0002};

const u32 DistanceF32_DTWRef10_f32[3]={0x3e996838,0x3ed38dd7,0x3f1dfa43};

const u32 DistanceF32_InputA1_f32[350]={0x3e903410,0xbf1049d1,0x3ebf6eae,0xbfaf711a,0xbf5ed4c6,0xbf4f78f1,0xbf2fef2b,0xbcbe52ae,0xbe146d81,0xbf5fdfd8,0x3eb8f5f8,0x3eb82e63,0x3f82891e,0x3dfe9701,0xbc862250,0xbecebaf5,0xbf0cb3ec,0xbe843530,0x3fab8d13,0xbfd356c9,0x3e292f32,0x3edf40f8,0xbfd30e17,0x3fa526fb,0x3efc610b,0x40087d0d,0x3f60f572,0xbf67e768,0x3e6c3472,0x3f0fc336,0x3f9549f0,0xbefd0268,0xbc552cc4,0xbf9faae9,0xbe597e7b,0xbe41d269,0xbc159ea7,0xbf8ec46e,0x3f8f62b2,0x3ea85769,0x3c5823fd,0xbf3b41e5,0x3ec05dd8,0x3ec9157f,0x3f996de6,0xbe5dab16,0x3ed3ab33,0xbf5a5cc4,0xbe57df19,0xbf0dd789,0xbf3ae7b1,0x3f230249,0x3e0e1579,0x3fa0202e,0x3efe8bd5,0x3eb752fe,0x3f1728c6,0x3c61bd50,0xbed342a4,0xbf628545,0x3fa20144,0xbf182e53,0x3f9586ec,0x3d07297c,0xbfd6a380,0xbf420242,0x3eb9278f,0x3fa0d0f2,0xbf0cfa3b,0x3fd6f3b3,0x3f06fe7b,0xbf4a5ac5,0x3c586db4,0xbf5b0a7f,0x3faa05c4,0xbf25f001,0x3f6f42a6,0x3dc3709c,0x3f6152ae,0xbf1a3f69,0x3fa54138,0x3de1dd76,0x3f8ba76d,0x3e430e07,0xbf5531d7,0x3fea6e31,0x3e6b3735,0x3f8bb4e8,0x3ec01a6f,0x3f57ea90,0x3db169b2,0x3e8e0b9b,0x3f706587,0xbf0fea16,0x3f0b8f9c,0xbdc68d8b,0xbed0346f,0xbfa64fcb,0xbe4ac326,0x3fd085ef,0xbfe57faf,0x3f20891d,0xbec56937,0xbfd5da60,0x3ef422c8,0xbf0e69d0,0xbfa5db9a,0xbf05a8c6,0xbf28d539,0xbfd9a359,0x3f2d8b7c,0xbfb58669,0xbf188581,0x3f649a40,0xbfcc7bcf,0xbf935aed,0xbeebefd5,0xbfdda28e,0x3ea8d823,0x3f03b80d,0x3f277def,0xbf178d65,0xbec187eb,0x3f387b6d,0xbf599f0d,0x3f26f757,0x3da41c60,0xbfd426a9,0xbfb3da02,0x3f9087b9,0xc0060c3f,0xbe919801,0xbf3aaf4b,0xbd817fb0,0xbfd7f437,0x3e826504,0x3f31878c,0x3cb6e56b,0xbfdea209,0x3f56dc35,0xbf3e1dfa,0xbf0ed8d4,0xbf3a3c24,0xbf53c3cd,0xbf181365,0x3f108cf5,0xbf0dc043,0x3f2488a8,0x3e27baca,0x3f73505a,0xbe9395b7,0x3f7bf14b,0xbd23cee2,0xbde7c425,0x3e1e5ab9,0xbf33bcb5,0x3f858927,0xbf6ddfc1,0x3ecfb4b4,0x3f163e48,0x3f5ac87d,0x3f5cdf4c,0xbf973754,0x3f1df2f5,0x3dbb69aa,0x3f1be1a5,0x3ee8484b,0xbfd2ff0d,0xbfdd4b7f,0xc01ee6e0,0x3f49b8ef,0xbea5d56e,0x3e8c66a7,0x3eeecf27,0x3f4c58ff,0xbfc3b9c0,0x3f5eccb3,0x3f146c84,0x3f2cb766,0xbd560c22,0x3f9a229c,0xbffcd98d,0x3fed9496,0x3fc5a67f,0xbdc0cbd4,0x3fb97a32,0xbf226ef7,0x3f366c07,0xbff78136,0xbf320e8e,0xbfe1dc6b,0xbf6dc2a6,0xbe33abb4,0x3f886a9d,0x3efddfdb,0x3f61e505,0xbf0243bc,0x3fa939c7,0xbf98e722,0x3f1a5b01,0xbf802926,0xc00352db,0xbf81e544,0x3d838192,0xbf9cf2dd,0x3e6a922f,0x3fdecac4,0xbe7feea6,0x3e08ba97,0xbf6e2d34,0xbfefec52,0x3f223c74,0xbeed6b6a,0xbeafea05,0x3fcea804,0x3eeee3ad,0x3fca12b3,0x3fd2c20f,0xbfc3c2cd,0x3f92741f,0xbdae53ef,0x3e8df61d,0x3fcc7c9d,0x3ed2b8f0,0x3f338231,0x3edd80f0,0x3c70dce5,0xbec3a1f4,0xbe270d39,0x3f66fdf1,0xbf60b65b,0x3f8ebb48,0x3fd6ab9a,0x3e34f62e,0x3d1a4bde,0xbf459ee3,0xbffe2c58,0xbe84f3be,0x3f1046d6,0x3fa505e5,0x3fbca659,0x3f9a479c,0x3f4a6e64,0xbfc8f533,0xbd727cfb,0xbfbc0c65,0xbd0852af,0x3e21f429,0x3ecbf0fd,0x3f7352e2,0x3ee1e3d0,0xbf400d31,0xbea361c4,0xbf90734a,0x3f151a7b,0x3ffde702,0x3e0036d5,0xbe5b9b32,0xbf27c2db,0xbfbc4242,0xbf8707f1,0x3f37f8d6,0x3fbeaccc,0x3f86cf23,0xbfe24ea7,0x3f38e80d,0xbf9485be,0xbfc128b5,0x3f89c3ba,0x3ec7cf3e,0x3e9122e4,0x3ea5a164,0xbf3d8196,0xbeb71544,0x3efc081a,0xbe9e74ac,0xbdb46853,0xbeb54448,0xbe54adf2,0x3fd42c02,0x3f2728ed,0x3e09f09d,0x3fe2ca77,0x3f83e3b5,0xbfa9ae0b,0x3f20a3b5,0x3f8ebabd,0x3fdce810,0xbf423ee0,0xbefe3388,0xbee08746,0x4014e2cc,0x3d3e6204,0x3f591024,0xbf10e7b3,0xbfb956c4,0xbce36d09,0x3f076b43,0xbdfbd7f2,0x3f9577a6,0xbd11d862,0xbfa53b14,0xbf0d053e,0x3ec87a6f,0xbf21263e,0xbed6de0d,0xbf8ee39b,0x3fb71b3d,0xbf6ded63,0xbf10581d,0x3f88e75b,0x3f4b600c,0x3c419981,0xbde3de62,0xbcfab604,0xbfd9e978,0x3df95b72,0xbf28fa7b,0xbe70f3d1,0x3ccd35d2,0x3efb75c6,0x3ff97982,0xbf970cfe,0xbecb2c14,0x3f96844f,0xbfb75fcb,0x3e137579,0xc002cbd2,0xc01b8891,0xbd759be4,0xbea008d5,0xbd3dcbc7,0xbf80cd2a,0x3f62ad7d,0xbf3550ff,0x3dfca422,0x3efda9c5,0x3fb3d173,0xbdbd4558,0x3f042ff0,0x3fd3bc61,0xbf741a97,0x3fd65586,0xbeb245d3,0x3f9ab8e6,0xbe44fabc,0x3dc480f8,0x3f01a9b5,0xbf556abb,0x3e5333f4};

const u32 DistanceF32_InputA8_f32[350]={0x3c40954a,0x3cc0b259,0x3c7fa847,0x3d6a4d51,0x3d14cb90,0x3d0a8a17,0x3ceaf5ad,0x3a7e2cff,0x3bc6398e,0x3d157de6,0x3c7703bf,0x3c75f934,0x3d2e5476,0x3baa0083,0x3a3322b7,0x3c8a0b3a,0x3cbbe880,0x3c309026,0x3d651b20,0x3d8d1f0e,0x3be1f1f9,0x3c9513cf,0x3d8cee84,0x3d5c8f74,0x3ca88698,0x3db647ac,0x3d163745,0x3d1ada80,0x3c1db9b7,0x3cbffe95,0x3d475ff1,0x3ca8f258,0x3a0e58e3,0x3d553c53,0x3c113b3a,0x3c09576f,0x39d40a42,0x3d4a542f,0x3d4b3479,0x3c6e9284,0x3a19280e,0x3d04b0a1,0x3c884f6f,0x3c8e7cc7,0x3d59705e,0x3c1d12ca,0x3c95fcdd,0x3d1abb17,0x3c18f73e,0x3cc90475,0x3d0470b6,0x3ce703e0,0x3bc95c3c,0x3d62edd6,0x3cb45ede,0x3c81e723,0x3cd638cc,0x3a1ff54f,0x3c95b2c6,0x3d2082ff,0x3d6597a0,0x3cd7ab78,0x3d53e8a0,0x3abf8cfc,0x3d98179c,0x3d097957,0x3c83332a,0x3d63e859,0x3cc7cad4,0x3d985070,0x3ca907d1,0x3cfd5ff6,0x3a077fa8,0x3d09225e,0x3d54e40c,0x3ccfc69f,0x3d15cafb,0x3b74b77c,0x3d0d1132,0x3cc1237e,0x3d4eebc3,0x3b8d6815,0x3d2edd8a,0x3bf43c0d,0x3d05795c,0x3d92c4e1,0x3c1342ba,0x3d2eee6b,0x3c7089f2,0x3d072d8e,0x3b5e24ff,0x3c31dc12,0x3d168117,0x3cb43332,0x3caebfb8,0x3b789d5a,0x3c82599e,0x3d503e8f,0x3bfde2a8,0x3d828ca5,0x3d8fae77,0x3cc9030e,0x3c772f51,0x3d85e2e0,0x3c98d866,0x3c94c78f,0x3d2d45a5,0x3c8ba257,0x3cb0614f,0x3d635df4,0x3cb54d7e,0x3d3da3be,0x3c9f56ed,0x3ceed253,0x3d559fe0,0x3d19f13a,0x3c767bd7,0x3d678ae5,0x3c30645a,0x3c899b6a,0x3caefaad,0x3c9e53ba,0x3c4a2ea5,0x3cc0ba99,0x3ce35976,0x3cae6e10,0x3b2b726c,0x3d5da278,0x3d3be430,0x3d16fdb2,0x3d8c0a42,0x3c181a25,0x3cc307ac,0x3b0749a4,0x3d619b8b,0x3c083939,0x3cb97728,0x3a3f1270,0x3d6895cc,0x3ce07705,0x3cf5c7e2,0x3cb8abaf,0x3cf0c311,0x3d08e224,0x3cc499fa,0x3cbadf81,0x3cb740f9,0x3cd4b502,0x3bd8d6ae,0x3d1d46c4,0x3c3ecbaf,0x3d22da9c,0x3ad3c4d9,0x3b95cfe5,0x3bccb7e9,0x3ce85c9b,0x3d2ca21a,0x3d19c29a,0x3c864279,0x3cc23b84,0x3d0d6b82,0x3d0ec534,0x3d437d7b,0x3ccc31c3,0x3b7248e0,0x3cc9857a,0x3c962550,0x3d8862f6,0x3d8f0b25,0x3dcd6d19,0x3d026459,0x3c566337,0x3c35822c,0x3c9a5d59,0x3d0416c4,0x3d3b9630,0x3cd588ed,0x3c8e407f,0x3ca588c7,0x3acd2588,0x3d13b9cb,0x3d7255e3,0x3d63b377,0x3d3d6e72,0x3b38c774,0x3d31c3bb,0x3c9badcf,0x3caed616,0x3d6d3672,0x3caaa715,0x3d58780e,0x3ce3df9d,0x3bac330d,0x3d02be6a,0x3c735148,0x3cd8804d,0x3c79b20d,0x3d223051,0x3d128b6f,0x3c93efd8,0x3cf5a9ad,0x3d7bb9c0,0x3cf8fcf9,0x3afc134b,0x3d166c18,0x3be0d11a,0x3d558713,0x3bf54a2b,0x3b830b12,0x3ce445bd,0x3d7eed8e,0x3cac61e5,0x3c7c4490,0x3c3aea74,0x3d5b94a4,0x3c7dd45c,0x3d56b5f1,0x3d5ff05a,0x3d5000fc,0x3d1b9ce2,0x3b393af8,0x3c16d6f4,0x3d594680,0x3c5fe6a9,0x3cbebc2b,0x3c6b5b45,0x39ffed2d,0x3c4fde15,0x3bb17fc3,0x3cf57030,0x3ceec40f,0x3d17a873,0x3d641888,0x3bc0476d,0x3aa3f231,0x3cd1fad9,0x3d8708dd,0x3c0d4458,0x3c994cbe,0x3d2f57f5,0x3d4872af,0x3d23edab,0x3cd7175e,0x3d558696,0x3b00d3a4,0x3d639ec0,0x3aa5028a,0x3bc408c6,0x3c76db83,0x3d13437d,0x3c88b65d,0x3ce87732,0x3c45c350,0x3d2ed8f9,0x3cb47ad5,0x3d99aa7e,0x3b9b31dc,0x3c04e8cd,0x3ccb1051,0x3d63dff2,0x3d237233,0x3cdeaf97,0x3d66cca7,0x3d232d70,0x3d88f706,0x3cdfd126,0x3d33c6cb,0x3d69ce60,0x3d26c13e,0x3c71db2e,0x3c2fad87,0x3c487c11,0x3ce56279,0x3c5d9c22,0x3c9888a6,0x3c3fccd7,0x3b5a5f0e,0x3c5b694c,0x3c00b79a,0x3d8068f6,0x3cc99510,0x3ba6585e,0x3d88bf15,0x3d1f0c81,0x3d4c9f07,0x3cc1b81d,0x3d2c1efb,0x3d8532c7,0x3cea3ee3,0x3c99461c,0x3c8761da,0x3db38b98,0x3ae59666,0x3d02e182,0x3caebea2,0x3d5f813f,0x3a89211b,0x3ca34e20,0x3b97da2b,0x3d343f18,0x3aafe0e2,0x3d474185,0x3caa0f65,0x3c71c304,0x3cc25587,0x3c818e97,0x3d2c5044,0x3d5cd007,0x3d0f7615,0x3cae117b,0x3d25187d,0x3cf54158,0x39e97776,0x3b896573,0x3a972b5a,0x3d7f4dde,0x3b921294,0x3cc5f956,0x3c0d262a,0x3a706c41,0x3c934dee,0x3d922431,0x3d30f852,0x3c6e08fc,0x3d30582f,0x3d56d705,0x3bacc305,0x3d993d68,0x3db638cf,0x3b0fe07a,0x3c3b7ecc,0x3ade5d19,0x3d16e720,0x3d04c978,0x3cd46dd4,0x3b93ff0d,0x3c949852,0x3d52ac77,0x3b5dbf99,0x3c9adea3,0x3d781178,0x3d0efec5,0x3d7b1cc0,0x3c50dcf4,0x3d354582,0x3be6c79c,0x3b6638f3,0x3c97e984,0x3cfa09ab,0x3bf771a3};

const u32 DistanceF32_InputB1_f32[350]={0x3e04bc9d,0x3fe7a5bf,0xbf3e90cb,0x3fda466a,0xbf3e9446,0x3f5a689e,0xbeb58241,0xbf5517c1,0xbe9b6d68,0xbf0b0da7,0xbfcf54d0,0xbe16c192,0x3d4f844c,0xbec32914,0x3f190d49,0xbf180397,0xbf86303a,0xbf23901e,0x3f6686e5,0xbeb236d6,0x3f1badce,0xc0330d72,0xbf5e795a,0x3f6d58f8,0xbac3dcb3,0xbff6a54b,0x3ef28120,0x3e11dc59,0xbfca7646,0x3ea3570c,0x3e6eff63,0x3e9897c3,0x3f21dfb9,0xbfd47cbd,0xbf07a694,0xbfd9b2d4,0xbec24dd7,0xbece6eae,0x3edba25e,0xbe7bae5a,0x3e831cb1,0xbe9c9386,0x3eeb1291,0xbf9530a7,0xbeb06be4,0x3fb7fa42,0xbee989c7,0xbf8869ba,0xbe239b08,0xbf06a16d,0x3fad857e,0xbf1b10dd,0x3e795829,0xbfc75087,0xbf43297b,0xbf2cc1c1,0x3fc0e396,0x3f835c34,0xbf26da99,0xbfa97ad8,0x3f1bcd63,0xbf50302a,0xbf9103f8,0xc01031e8,0xbe13a0e0,0xbe3c205b,0xbf0c9a5a,0xbf651689,0x3f9e6793,0xbff5a158,0xbded40f1,0x3f18bd57,0xbfbb62a5,0xbea1b271,0xbf19d28b,0x3f496ea3,0x3d89b67a,0xbeba707e,0x3f3426a0,0x3f81d6fa,0xbf0431cd,0x3b2b451c,0x3fad1255,0xbd96faa9,0xbf83235a,0xbc3683d2,0xc00dfff5,0xc01229de,0xbf07e221,0xbf968045,0x3fe0096b,0xbe75bdd1,0x3f89385d,0x3f0d29db,0x3f945e1d,0x3f269891,0xbf047992,0x3ebe5737,0x3dca2e63,0xbf96c8ab,0x3eb6e866,0xbcaa2042,0x401cae07,0xbd7398e4,0x3f92b557,0x3ff203a0,0x3fe6bd7d,0x3f61e42c,0xbf50cdbe,0x3f6c2047,0xbe8673b8,0x3ed275f7,0x3f631e94,0x3f6103e0,0x3f465cb2,0x3f6705a5,0x3ed2b465,0x3f27494a,0xc06298ae,0xbfa0c942,0x3fac2a55,0xbf9fa72e,0x3f2560c5,0xbf0ecfcf,0x3e979c01,0xbeb340b4,0xbfa5d596,0xbc17ecd8,0xbfd9ef60,0x3f072750,0x3f9340a8,0xbf5a6fc9,0xbf08f41e,0xbf055577,0x3fc4f985,0xbff9507e,0xbd25cc0c,0x3ec4443d,0x3f6dc685,0x3f932b6d,0xbf9ffe2f,0xbf92b7d6,0x3ed7287e,0x3fa6bb14,0x3eb393df,0xbf2f72f8,0x3ee4f8a3,0xbfc482fc,0x3e8925d3,0x3f4cad0a,0xbdc088bd,0x3e039a67,0xbfe268ae,0xbf4314e0,0xbe0f43ca,0x3f819d86,0x3ffdc3f4,0xc0036cf8,0x3e95181d,0x3fac1e02,0xbf7e027b,0x3ef83732,0xbf653de8,0x3ee5f749,0xbe5e315c,0xbf53da00,0xbf8ab35a,0x3d9594c3,0xbcaf6d8b,0x3f9503f6,0xbdd4b440,0x3fd76f9d,0x3f4c0263,0xbf7273cc,0x3efcd732,0x4006f377,0x3ef51441,0x400d8bf7,0xbdd474b9,0x3f1467d9,0xbfb10a79,0xbd7a9c8f,0xbe2b918d,0x3ca3c350,0x3e107c2d,0xbde3df50,0x3aec8ce6,0x3dad5303,0x3ebaa109,0xbec4d962,0x3f620f98,0xbdffb842,0xbe895919,0xbea693ea,0x3e742ef7,0x3f9a28f8,0x3f14435b,0x3f1ac1d1,0xbf8c670f,0x3fe9e68b,0xbea25750,0x3ddae045,0x3eb2bc99,0x3ffba0ad,0xbef219d2,0xbf8946a8,0xbff32ff1,0xbdd15f08,0xbe779d09,0x3f62ccce,0x3f57b48d,0x3ed14b03,0x3fb1785b,0xbe836849,0xc0316132,0xbf41723a,0x3db408a0,0x3f1a36a8,0xbf720ac3,0x3eda1584,0xbefa8f4e,0xbdf65016,0xbf52b075,0xbf8ae362,0xbf191474,0xbf538f6f,0xbfebc0bc,0x3f380e5d,0x3f09fd15,0x3f8cecab,0xbe1416e3,0xbf25557d,0xbf08f942,0xbf815c93,0xbfeaafda,0x3c3e546f,0xbe17e210,0xbefb1ffc,0x3f23a1f1,0x3f53d87e,0xbf5a3362,0xbe37a5d7,0xbe83143a,0x3e9f1faf,0x3f5fca75,0xbe33e2ad,0xbd36ea59,0xbf22207e,0x3ef2dc4f,0xbec29a6b,0xbfd45329,0xbfd9e085,0x3deb674d,0x3fb6d332,0xbf1a62cf,0xbe302dce,0xbf61b12f,0xbec45a13,0xbf91db74,0x4001e805,0xbf1ad7ed,0x3f85ee7d,0xbecd849f,0xbd916f28,0x3b234d9a,0xbf13b80d,0x3ec37b72,0xbe6692f5,0xbecae3b4,0xc023262c,0x3d3c4346,0xbf1a3394,0x3f6d52aa,0xbe01e1e2,0xbf9821ec,0x3f55e59c,0xbf028d2c,0xbedcfefe,0xbf5420de,0xbf22de89,0x3e2dd23b,0x3e414b5e,0xbf770966,0xbf1d4804,0xbea67106,0xbf357bc1,0xbeb46cde,0x3ede8096,0x3efa88a0,0x3f249806,0x3edda908,0x3ec7fae7,0x3f53cc23,0xbfad4f52,0x3e82d01e,0x401004a1,0xbf52f8b3,0x3f1ad370,0xbcb1bd83,0xbf4cd701,0xbf128b38,0x3f65322a,0x3f3f0e80,0xbec433eb,0x3eaf5a02,0x3ecb0a93,0x3f0a289f,0x3fbfc0c4,0xbf0ece80,0x3f1b1511,0xbf9f2101,0x3f854af7,0x3dc5832a,0xbf45eeca,0x3fd7afca,0xc06093fc,0xbeff388c,0xbf2921d2,0xbdc06414,0x3f48a498,0xbf919906,0xbf71d70f,0x3f3d0ca1,0xbfb35f0f,0x3edb7ddb,0x3f9e58c5,0xbe914c0a,0x3f3ae660,0xbe7fcd6d,0x3e4eaeec,0xbe4c1390,0xbf56fe83,0xbf5052d4,0xbe610faa,0x3f9bc3ce,0x3f6edf8a,0x3fe9380c,0x3eea3d19,0xbef1b176,0x3f870f77,0x3feb681c,0xbfba9455,0x3f9b35d2,0xbe9963c7,0x3e655050,0xbcf95e59,0x3f7e31b2,0x3f8db3d2,0x3f637a25,0xbe50774f};

const u32 DistanceF32_InputB8_f32[350]={0x3b9b5177,0x3d878724,0x3cdefc29,0x3d7f6890,0x3cdf003c,0x3cff9097,0x3c546330,0x3cf95836,0x3c35de77,0x3ca2b599,0x3d729a5a,0x3bb06730,0x3af2d1ea,0x3c645c8f,0x3cb316e3,0x3cb1dffe,0x3d1d044d,0x3cbf637d,0x3d06df50,0x3c508849,0x3cb629d0,0x3dd18368,0x3d022930,0x3d0adce0,0x38652ebd,0x3d904d83,0x3c8de13f,0x3baaacc4,0x3d6ce7bf,0x3c3f20b5,0x3c0bd404,0x3c328d5f,0x3cbd6988,0x3d78a2d2,0x3c9eba56,0x3d7210da,0x3c580d82,0x3c6589e0,0x3c7437db,0x3c0bed10,0x3c11c9a1,0x3c2e1a20,0x3c82b137,0x3d25e39c,0x3c442b24,0x3d4c9207,0x3c81d6d7,0x3d17ae90,0x3bb5eb0e,0x3c95b32f,0x3d40f1a6,0x3cac6c2f,0x3c0aa07d,0x3d5d9fc5,0x3cd901bc,0x3cc01800,0x3d567ab6,0x3d121040,0x3cb987b3,0x3d3c7330,0x3cad3dd0,0x3ce77dad,0x3d213f4e,0x3da055bb,0x3ba42714,0x3bd12f02,0x3c9c573f,0x3cfebaeb,0x3d302291,0x3d888fde,0x3b8d6e4a,0x3cb619e7,0x3d5f682d,0x3c40c7d0,0x3cb76465,0x3cf02770,0x3b242f8c,0x3c5e477a,0x3cd6c824,0x3d1acc99,0x3c9d9b4e,0x38cc3194,0x3d4e5776,0x3b340096,0x3d1c58de,0x39d999ac,0x3da94bff,0x3dae42cf,0x3ca2012b,0x3d336eab,0x3d858d50,0x3c127d93,0x3d239931,0x3ca84cbd,0x3d30e385,0x3cc69f06,0x3c9df0e0,0x3c62ee30,0x3b710c0d,0x3d33c4fc,0x3c5a1196,0x3a4ad46f,0x3dbacc7e,0x3b11365a,0x3d2ee919,0x3d686f22,0x3d5d9b3e,0x3cd8f311,0x3cc889cb,0x3ce2c774,0x3c01213a,0x3c4a213a,0x3cda2106,0x3cd81ba5,0x3cbe828f,0x3cdde08b,0x3c4a5d2e,0x3ca0aa11,0x3dd9a06d,0x3d1a6be7,0x3d2559aa,0x3d19554f,0x3c9ed4e2,0x3c89289a,0x3c119ba5,0x3c2c2837,0x3d1f4513,0x3991e949,0x3d514ee4,0x3c81cdb6,0x3d0d6c73,0x3cd1ca38,0x3c838846,0x3c800e4e,0x3d3d2d71,0x3d6f7205,0x3a9f3bea,0x3c3c7f56,0x3ce45cfb,0x3d0d580f,0x3d36beb2,0x3d279515,0x3c75c14b,0x3d3e70e2,0x3c4d1d5e,0x3cc8662a,0x3c82c426,0x3d6074f5,0x3c1ca6aa,0x3ce9c83c,0x3b5be9e9,0x3b965165,0x3d814d87,0x3cded2c9,0x3ba3a352,0x3d140c26,0x3d90ed1f,0x3d961d7f,0x3c2a4bdd,0x3d4497e8,0x3d1110d5,0x3c8dc1b8,0x3d02ebb5,0x3c835594,0x3bfdca40,0x3cf1fa6b,0x3d1e6cb9,0x3b2ada3d,0x3a485ff8,0x3d2a34d8,0x3b72f3b5,0x3d761286,0x3ce90550,0x3d0a771e,0x3c9065e8,0x3dbdaaff,0x3cac3962,0x3dc6f01d,0x3b954c86,0x3cd093ee,0x3d78d2d0,0x3b301caa,0x3bf121e1,0x3a662970,0x3bcb1150,0x3ba021e8,0x38a63b14,0x3b739994,0x3c83264c,0x3c8a54e2,0x3d1edc09,0x3bb3b39f,0x3c41096e,0x3c6a1e36,0x3c2b9842,0x3d58aa57,0x3cd060a5,0x3cd98129,0x3d455471,0x3da45e60,0x3c6429da,0x3b99cf7d,0x3c7b34f5,0x3db0d374,0x3caa2199,0x3d40ef83,0x3daae50b,0x3b932195,0x3c2e014d,0x3d1f6100,0x3d07f41d,0x3c83e97f,0x3d5fb5ba,0x3c25a53d,0x3ddf9888,0x3cf3d936,0x3b62f0fc,0x3cc264cb,0x3d188d8f,0x3c8973ee,0x3c9debe6,0x3b9b3ea7,0x3d04cac8,0x3d2f1351,0x3cc0f6fa,0x3d055752,0x3d9496cc,0x3ce80306,0x3cadf102,0x3d31a46b,0x3bbaac8a,0x3cd0695e,0x3caca97c,0x3d231113,0x3d93eacf,0x39efeb8d,0x3bbf74c2,0x3c9e4716,0x3cce4456,0x3d05855e,0x3d0986c1,0x3be77f44,0x3c253b47,0x3c489557,0x3d0d0cb9,0x3bedc420,0x3af1c561,0x3cd64b25,0x3ca08090,0x3c809c18,0x3d8c5259,0x3d8ffdb2,0x3b9b92ee,0x3d71a6c8,0x3ccc0fd3,0x3be8ddf1,0x3d1527e7,0x3c81c3f2,0x3d40c9f2,0x3dabb49c,0x3cccaaa0,0x3d3106a6,0x3c87d2bc,0x3b403acd,0x38d7d923,0x3cc33fe4,0x3c8130d0,0x3c1861da,0x3c861603,0x3dd7a506,0x3af8d6c7,0x3ccbd166,0x3d1cd7aa,0x3babac80,0x3d491551,0x3d0d5c51,0x3cac8ee7,0x3c920d65,0x3d0c311c,0x3cd74655,0x3be77a72,0x3c00b496,0x3d247d64,0x3cd173ba,0x3c5da695,0x3cf1ae9d,0x3c7045df,0x3c94274e,0x3ca6d17b,0x3cdb30b0,0x3c9397c7,0x3c852837,0x3d0d0692,0x3d66cc1c,0x3c2e343e,0x3dbfca15,0x3d0c79c9,0x3cce2ea6,0x3a6cb286,0x3d08649a,0x3cc32725,0x3d189c4b,0x3cfe6e48,0x3c82a459,0x3c69842d,0x3c873206,0x3cb7fc84,0x3d7f5bae,0x3cbe2d14,0x3cce860c,0x3d53e99b,0x3d3181ab,0x3b838392,0x3d03cb3b,0x3d8f9d87,0x3df63f5e,0x3c8bec6d,0x3cb9739d,0x3b52f466,0x3cdc00c0,0x3d1fa57c,0x3d04966b,0x3ccf4a67,0x3d44adc7,0x3c70ab99,0x3d2da026,0x3c1f5113,0x3cccef0f,0x3c0c3e0c,0x3be2a048,0x3bdfc487,0x3cebbd2a,0x3ce46cb4,0x3bf6c6fb,0x3d2acb69,0x3d02f604,0x3d7fb8df,0x3c806b8e,0x3c8481ce,0x3d1417a5,0x3d810f7d,0x3d4c951a,0x3d2a2fba,0x3c2830b7,0x3bfb70ad,0x3a88b70c,0x3d0b5c51,0x3d1b6011,0x3cf96d24,0x3be494b4};

const u32 DistanceF32_InputBenchA1_f32[256]={0x3f89b7e2,0xbcf0d0bd,0x3f1bea34,0x3e70ce98,0xbee83d6c,0x3f348c31,0xbf0a8bde,0x3fb6bc1f,0x3f34a0f5,0xbf4cec8c,0x3e828592,0xbf9deca7,0xbfea202a,0x3e1489bf,0x3f6e80c1,0x3e8229a9,0xbf741bf4,0xc01352e3,0xbf376fca,0x3e9bb9d3,0xc04661f7,0xbf323ef6,0x3f86d3cf,0x3ee39f07,0x3f8d9e3e,0x3f0c2911,0x3fbe0c06,0xbfc6d3d9,0x3f63f3b9,0xbfa635b0,0x3c39fbd8,0xbf3f694b,0xbf8f437c,0x3e25f3db,0xbe8ac558,0xc00e9f7d,0x3e95f034,0x3f6f91e6,0xbf27cf1c,0xbfc3323f,0x3f76df87,0xbe197c30,0xbe54dbe0,0xbfe0fe5b,0x3fcf76b9,0x3e3d536c,0xbf13c05a,0x3f2f6f88,0xbf0a606f,0x401e9985,0xbf1e83e5,0xbf9cfa67,0x3f275429,0x3d687e12,0x3ff571a7,0xbf965d06,0x3feb70a0,0xbf40c204,0x3eeaf034,0xbf205791,0x3f91bb55,0xbf0580ae,0xbf2fc819,0x3f2b8130,0x3ebd9e4c,0xbff22a5f,0xc01905c0,0x3ee2676b,0x3e69d811,0xbf7df58c,0xbf7bfaaa,0xbf2f5ced,0x3e761eef,0x3f252c8e,0xbfa51e6a,0x3f5bfff6,0x3e1f32c6,0xc0147ebc,0x3df135ad,0xbfb0e7a3,0xbfc93df5,0x3f330cd6,0xbd8d8c44,0xbf8c57f8,0x3e9ca5e0,0xbe8bf952,0xbe404952,0xbf247171,0xbe1d3725,0xbf93d9f5,0xbfafb948,0x3f05d993,0xbf33db54,0xbf46edd5,0xbf082246,0x3f764b90,0xbd00cb26,0x3db5c198,0x3d233e88,0x3f7e24f0,0x3f152bee,0x3f3a14d8,0x3fb082c3,0x3f773b0d,0x401a3f70,0xbde265d1,0xbe0f1a18,0x3f33ce36,0x3fd925f5,0xbf38e268,0x3ef75a54,0xbfe4e726,0x3f853c8f,0xbf61288d,0xbfd1990b,0x3f1cc8c7,0x3fb4cfb7,0xbf015039,0xbebe52a7,0x3f73b68f,0x3f09bdce,0xbf42dcf2,0xbf9354e7,0x3faf521f,0xbe9d45d1,0x3d2d8bc6,0xbc28aa28,0x3ec63ef3,0xbfbe68ee,0x3e8ae1c9,0xbef8c770,0x3f53c3e4,0xbf23d5bd,0x3e45c7b7,0x3e44731e,0xbf980c21,0x3c6ab131,0x3fc42c63,0x3eae98b6,0xbf470171,0xbec15801,0xbc0f6146,0x3e9a4614,0x3e4d5c49,0x3f728f00,0x3eb95e1b,0xbfc8008f,0xbf35346a,0xbe978342,0xbf910ae9,0xbd8d62e1,0x3ee575e7,0xbf29b41a,0x3f1c3da4,0xbfa91c8d,0x3f21965c,0x3f58825b,0x3f837b63,0x3f1a9da8,0x3fa07f3c,0x3f1535b2,0xbf997531,0xbf0e59bb,0xbe9b4ceb,0x3e77cd28,0xbfa1b9b8,0x3de2a95c,0x3ded408e,0xbed5f1e4,0xbf3bb009,0x3fceca01,0xbeec8036,0xbf21e3fb,0x3f4dbc13,0xbd962322,0x3e01af7b,0x3f0f4317,0x3fb23c10,0x3e76e3f1,0x3e29dac9,0x3f2e9827,0xbe533756,0xbfd75fe8,0x3f326bae,0xc00e1c19,0x4005d908,0x3f772bd4,0xbfc25e87,0xbff6ba01,0x3f130cad,0x3f05441e,0x3f7b6b39,0x3e75c572,0xbfa7255c,0x3dfa5a96,0x3de307a9,0xbf28ba48,0xbdf8ebff,0xbefd56f9,0xbfa520d2,0xbe8c5fae,0xbf70a319,0xbf811189,0x3f9c8d39,0xbfe83b37,0xbf31653b,0xbfa77fa7,0xbf209d3c,0xbeb9a714,0x3f7ad9d0,0x3fdfcef0,0xbe583eb4,0x3f3d52c0,0x3f6ebe55,0x3e9e2444,0x3e21516f,0xbf287518,0x3fee223e,0x3e24f8c3,0xbf43d3cf,0x3f3d4b45,0xbf5c6e6f,0x401d71cc,0x38a0a8d4,0xbf5847ad,0x3df61be9,0xbfbfaa98,0xbf33c51e,0xbd7783ef,0x3f545fa5,0x3fceddf2,0xbfc3b80d,0xbf7f8c8c,0xbf63c24f,0x3fd8b7e8,0x3f1637ad,0x3f06dcf3,0xbfdcee12,0x3f40be4f,0xbd0b9ed3,0x3fbe8122,0xbf50beae,0x3fa3f44e,0x3faa6ed3,0xbf696930,0xbfc2113e,0x3fa841ee,0xbfd84aaa,0x3fc64a31,0x3f90cd44,0x3dca10fe,0x3f927edd,0xbf5189b4,0xbf922e08,0x3de1389f,0x3f66fdce};

const u32 DistanceF32_InputBenchB1_f32[256]={0x3f9b4d7b,0x3ffdbfad,0xbe843485,0xbf6b79b9,0xbf886cdf,0xbffa0265,0x3fbb6d52,0xbf7c74b5,0xbea23a64,0xbf91e9b9,0xbfaf8503,0x3fb72915,0x3fec2d2c,0xbf9e1c1a,0x3f14e448,0xba916b0d,0x3edd2f43,0xbf2373a2,0xbf9876ae,0x3f170821,0xbfcdb265,0x3cac33f6,0x3f224308,0xbf5bd6dd,0x3c8ae203,0x3e2e9a97,0x3f40ab06,0xbf9f7066,0x3d4b781c,0xbf684ab0,0xbeccfe2b,0xbf09ed49,0xbe913ad1,0xbd81c414,0xbe999c05,0xbebe5579,0xbf5eb25f,0x3ef2356d,0x3e359324,0xbe2e6c24,0xbd9f46e4,0x3de4b045,0x3f4e06b8,0xbf1abaac,0x3eb46611,0xbfa03a97,0x3e5c56ec,0xbd620c75,0x3eac5572,0xbe6f3eef,0xbf2d4f5f,0x3f2d9795,0xbfb2e319,0x3f2b4c61,0x3f8991f7,0x3e9e9f13,0x3fd67b26,0xbfc17fc2,0x3d9d3e21,0xbea980ba,0x3f260a16,0x3f393ab9,0x3f0257a3,0xbe94cf61,0xbf56c4e8,0x3e73c2b3,0xbd9c7165,0x400422e0,0x3eab29c2,0x3f99a4ca,0x3da63c92,0xbf660026,0x3f365c0c,0x3f9b1f90,0x3ec26875,0x3f0f0d9b,0x3e7f77ad,0x3e5b42c4,0xbd88942f,0xbf64f973,0xbfdc2878,0x3e2be565,0x3f9e2c24,0xbe5f50f0,0x3e210ccb,0xbdb99d49,0xbf0d0174,0x3ec00e1c,0x3ef79c41,0x3f342196,0x3f6f30d5,0x3f9d9709,0xbe67f95b,0xbfbe2474,0x3fbe8e33,0xbcd8c59c,0x40174ccd,0xbf5a1eb0,0x3f20caef,0xbf699a3e,0x3fba0b27,0xbfca4b86,0xbe6e65ef,0x3ecfff06,0x3f0e429c,0x3f6bed23,0xbf7fcfc9,0x3ea7195e,0x3ecd6079,0x3f8e12f4,0x3ee16ecc,0xbed30289,0x3ec47dc1,0xbf2c32dd,0x3eb40422,0xbdb983fa,0x3f996d8f,0x3f738add,0x400fbcf3,0xbed86bf2,0xbf6f5925,0xc00d07e8,0x3f16b458,0xbfcc7d3c,0xbe265a1a,0x3fc44e90,0x3f33f361,0x3f4aefca,0xc00b2ce5,0x3e42fcde,0x3f8ef201,0x3ef8875e,0x3efa73fb,0x3ef8e489,0x3ef9d291,0x3f57544f,0xbedfe447,0x3b8214a7,0x3debbbe0,0x3ede543c,0x3e3867f4,0xbf9c422f,0xbd92908b,0xbfb6b346,0x3f431908,0x3f0b7aaf,0x3be1d01c,0xbd148605,0xc07071b8,0x3e3e625a,0x3f6ccb26,0x401946e4,0xbf3b5109,0xbf159aa9,0x3ea13010,0xbeceb0eb,0xbe265b7e,0x401a223b,0x3fa524c5,0xbeb447fc,0x3f9c37eb,0x3f6e1710,0x3fe4fb0a,0xbfd4825b,0xbf4fe2a3,0x3eda06aa,0xbf073867,0x3fafe860,0xbe302e3d,0x3f139ff2,0x3f62970b,0xbef86bfd,0xbf30242d,0x3ec86205,0x3eefe1a4,0x3fa07542,0x3fc3707d,0xbf5c094d,0xc0004060,0xbf6800f3,0x3ce70c2d,0xbecc1a33,0x3f837279,0xbf4438fb,0x3c964155,0x3f2ce3b4,0x3fb7ec9a,0x3fcd9c34,0x3f0a7ea6,0xbf8a0925,0xbebd6717,0x3f8cb99a,0xbf07c33b,0x3f17d88a,0x3fe25ec0,0x3f47b273,0xbffa082c,0xbf97b5d5,0x3ec30647,0xbe2b2011,0x3e5a4106,0xbeff3f9e,0x3f9f8eab,0x3da6efe2,0x3ea749c3,0xbf78b46b,0x3fa5fe05,0x3ed419a6,0x3fc2a117,0x3f549027,0x3f77c9c9,0x3efa150f,0xbe1b442c,0xbf34cab3,0xbfb61b85,0xbfc5c6ad,0x3e8f0470,0x3f3e4175,0xbf338cde,0x3f499b2d,0xbe98cfd8,0xbeb10434,0x3f3bdf96,0xbd6a8d3b,0x3f00e71a,0x3f9f0224,0x3e58bf3c,0x3ea900ab,0xbe919663,0x3f23ccb1,0x3f2008ae,0x3f674826,0x3f3d9dd8,0xbe85f0e4,0x3edf9e9e,0xbff1a2f0,0x3e66d8ed,0x3d158d98,0xbf1bcab2,0xbf39e7f5,0x3f060a33,0xbff19dc3,0xbf7ded38,0xbfa2bff4,0x3fb3da5f,0xbede78f4,0x3ce21cce,0xc01b247c,0xbf21e6b3,0x3f04ba6e,0x3fd6e41a,0x3f5d83ae,0x3edb13c9,0x3f488029,0x3f324c61,0x3f6c34e1};

const u32 DistanceF32_InputBenchProbaA1_f32[256]={0x3ba671e7,0x39118605,0x3b3c6fe6,0x3a9184b9,0x3b0c5767,0x3b5a3540,0x3b27721b,0x3bdcd9fa,0x3b5a4e5a,0x3b77ab49,0x3a9dbf4d,0x3bbedda9,0x3c0d7b1e,0x3a338588,0x3b902049,0x3a9d5038,0x3b938392,0x3c320dd4,0x3b5db320,0x3abc356e,0x3c6fc366,0x3b576d1d,0x3ba2f374,0x3b098ce3,0x3bab2882,0x3b29657e,0x3be5b057,0x3bf04d0a,0x3b89c011,0x3bc8e11e,0x3860c731,0x3b675677,0x3bad259e,0x3a48918e,0x3aa7b792,0x3c2c5f6a,0x3ab536c1,0x3b90c559,0x3b4acff2,0x3bebe987,0x3b952f27,0x3a398023,0x3a80a12a,0x3c07f665,0x3bfabd14,0x3a64d13c,0x3b329221,0x3b54079e,0x3b273d9c,0x3c3fae96,0x3b3f9473,0x3bbdb8e1,0x3b4a3b59,0x398c7e78,0x3c14520e,0x3bb5ba47,0x3c0e4671,0x3b68f718,0x3b0df8d6,0x3b41c9ac,0x3bb02143,0x3b215997,0x3b5472a9,0x3b4f475d,0x3ae52bba,0x3c1256e2,0x3c38f0ff,0x3b08d095,0x3a8d4f8d,0x3b99775b,0x3b98450d,0x3b53f122,0x3a94bac5,0x3b47a0af,0x3bc78f98,0x3b84f1dd,0x3a4067ce,0x3c337838,0x3a11c304,0x3bd5ce2d,0x3bf33814,0x3b5865ef,0x39ab12c9,0x3ba99e2d,0x3abd52b8,0x3aa92bc9,0x3a686539,0x3b46be8a,0x3a3e024a,0x3bb2b113,0x3bd460c1,0x3b21c507,0x3b595f80,0x3b706c71,0x3b2487b0,0x3b94d5bd,0x391ba898,0x39dbab32,0x39454b9c,0x3b9993ff,0x3b34498b,0x3b60e568,0x3bd55443,0x3b956676,0x3c3a6c1d,0x3a08cf9d,0x3a2cf398,0x3b594fa5,0x3c0338ba,0x3b5f730c,0x3b15795c,0x3c0a532b,0x3ba10742,0x3b880fe4,0x3bfd515b,0x3b3d7ce6,0x3bda86dc,0x3b1c496d,0x3ae605b4,0x3b93464c,0x3b26790f,0x3b6b8270,0x3bb21044,0x3bd3e414,0x3abe1405,0x3951bef5,0x384bd8ae,0x3aef9915,0x3be620a1,0x3aa7d9f2,0x3b1655ff,0x3b7feff0,0x3b46025c,0x3a6f08fa,0x3a6d6d56,0x3bb7c34f,0x388dd2c2,0x3bed17d9,0x3ad303fe,0x3b708424,0x3ae9ac5d,0x382d499f,0x3aba7424,0x3a783255,0x3b9293b2,0x3ae0088d,0x3bf1b879,0x3b5b0091,0x3ab71de3,0x3baf4c0b,0x39aae0c3,0x3b0aa96f,0x3b4d1a19,0x3b3cd4be,0x3bcc62f0,0x3b434af6,0x3b82d5de,0x3b9ee864,0x3b3addfd,0x3bc1f99e,0x3b345559,0x3bb977af,0x3b2c0b1b,0x3abbb1cf,0x3a95bec0,0x3bc375b2,0x3a08f86e,0x3a0f5ecb,0x3b01492b,0x3b62d65e,0x3bf9ec55,0x3b0eea8f,0x3b43a8c6,0x3b78a619,0x39b57450,0x3a1cbc8e,0x3b2d2524,0x3bd7699d,0x3a9531d2,0x3a4d48da,0x3b530351,0x3a7f4612,0x3c022659,0x3b57a329,0x3c2bc09e,0x3c21c45e,0x3b955d43,0x3beae9a6,0x3c15187a,0x3b31b8f9,0x3b211065,0x3b97ee5e,0x3a9484b1,0x3bca02c9,0x3a17499e,0x3a09316a,0x3b4bec2b,0x3a166c16,0x3b191788,0x3bc79280,0x3aa9a77f,0x3b916a70,0x3b9bfdaa,0x3bbd34ed,0x3c0c5611,0x3b5665f8,0x3bca6fe9,0x3b421ddf,0x3ae060be,0x3b97967f,0x3c073f0a,0x3a82acfb,0x3b64d06c,0x3b904580,0x3abf20df,0x3a42f7a8,0x3b4b988d,0x3c0fe72c,0x3a476216,0x3b6caccb,0x3b64c761,0x3b8534a0,0x3c3e492d,0x34c22be3,0x3b82b268,0x3a14b8f1,0x3be7a563,0x3b5944a7,0x39959281,0x3b805618,0x3bfa046f,0x3bec8b3f,0x3b9a6d4e,0x3b89a235,0x3c02f63a,0x3b358d24,0x3b22fe81,0x3c0581c1,0x3b68f29d,0x3928be6a,0x3be63de1,0x3b7c4972,0x3bc6274d,0x3bcdfbc5,0x3b8d0c8c,0x3bea8c3e,0x3bcb5ab6,0x3c02b436,0x3befa6ab,0x3baf0189,0x39f43722,0x3bb10d94,0x3b7d3ed1,0x3bb0abe3,0x3a08199a,0x3b8b9642};

const u32 DistanceF32_InputBenchProbaB1_f32[256]={0x3bc9f5a7,0x3c24fd9d,0x3aabec49,0x3b991bf4,0x3bb16933,0x3c228f2e,0x3bf3bc25,0x3ba4266b,0x3ad2f730,0x3bbdbfbe,0x3be4400b,0x3bee2fc4,0x3c1990a2,0x3bcd9c29,0x3b419f65,0x36bd1b04,0x3b0fd12c,0x3b548e89,0x3bc6447f,0x3b4467d4,0x3c05bf2a,0x38dfefea,0x3b53026d,0x3b8ef13e,0x38b49b59,0x3a630f32,0x3b7a8cee,0x3bcf56b2,0x39844c5b,0x3b970a01,0x3b0549fb,0x3b335d1a,0x3abcdc49,0x39a8c03e,0x3ac7c1f8,0x3af783dc,0x3b90cce0,0x3b1d7cba,0x3a6c1fdf,0x3a62d2cb,0x39cf20b7,0x3a14b23c,0x3b85f5fe,0x3b4936bd,0x3aea9858,0x3bd05da1,0x3a8f4482,0x3992fad0,0x3ae01b76,0x3a9b8f8b,0x3b616078,0x3b61be60,0x3be8a11f,0x3b5ec2c3,0x3bb2e658,0x3ace467c,0x3c0b7555,0x3bfba193,0x39cc7b81,0x3adc6d04,0x3b57ec02,0x3b70e086,0x3b298022,0x3ac18435,0x3b8ba54b,0x3a9e7f09,0x39cb7143,0x3c2bd556,0x3ade95bd,0x3bc7cd5f,0x39d82da9,0x3b958ca1,0x3b6d2522,0x3bc9b9f0,0x3afcd02f,0x3b3a07ad,0x3aa61bb6,0x3a8e90f2,0x39b19c53,0x3b94e1d2,0x3c0f264d,0x3a5f89c0,0x3bcdb105,0x3a9133fa,0x3a516efc,0x39f160b3,0x3b375e0e,0x3af9c0df,0x3b20ffdc,0x3b6a3f4b,0x3b9b8660,0x3bccef1f,0x3a96d51f,0x3bf7441d,0x3bf7cda0,0x390cf2a8,0x3c44c121,0x3b8dd308,0x3b511956,0x3b97e430,0x3bf1ef93,0x3c0388ea,0x3a9b0273,0x3b073de6,0x3b38ffb3,0x3b9966fe,0x3ba65500,0x3ad94cca,0x3b0589e6,0x3bb8c1b8,0x3b12944d,0x3b09338c,0x3aff85b2,0x3b5fee7e,0x3aea18fe,0x39f13fc9,0x3bc7858c,0x3b9e5abc,0x3c3aebb3,0x3b0cb85c,0x3b9ba096,0x3c376672,0x3b43fae0,0x3c04f625,0x3a58540f,0x3bff4853,0x3b6a0335,0x3b83f3b8,0x3c34fcbb,0x3a7d912d,0x3bb9e3c9,0x3b2198bb,0x3b22d909,0x3b21d54f,0x3b227015,0x3b8c0289,0x3b1193c8,0x37a92906,0x3a1946f7,0x3b108fab,0x3a6fce6f,0x3bcb33de,0x39be98ae,0x3bed9691,0x3b7db5cd,0x3b3561e4,0x3812d393,0x394124d0,0x3c9c5705,0x3a77949b,0x3b99f75a,0x3c475343,0x3b73975c,0x3b428c90,0x3ad19cd8,0x3b0664a9,0x3a5855df,0x3c48707f,0x3bd6c1cc,0x3aea713a,0x3bcb2684,0x3b9acf2a,0x3c14e2db,0x3c0a2d1d,0x3b872b71,0x3b0dc36a,0x3b2fd80f,0x3be4c142,0x3a651c1d,0x3b3ff99f,0x3b9354ed,0x3b2186ee,0x3b650f06,0x3b024aa2,0x3b1bf956,0x3bd0a9ec,0x3bfe2788,0x3b8f1209,0x3c26c810,0x3b96da0f,0x39163ae7,0x3b04b5c0,0x3baaeff0,0x3b7f2c43,0x38c3654e,0x3b60d475,0x3bef2e07,0x3c05b0bc,0x3b341a23,0x3bb38155,0x3af64ddc,0x3bb7009e,0x3b308c99,0x3b4576da,0x3c133053,0x3b81d879,0x3c2292ef,0x3bc549b7,0x3afd9d6a,0x3a5e8923,0x3a8de95c,0x3b25f743,0x3bcf7e0f,0x39d916d7,0x3ad98bb9,0x3ba1b606,0x3bd7dc50,0x3b09e908,0x3bfd19d4,0x3b8a3615,0x3ba11d76,0x3b229b51,0x3a49e98c,0x3b6b1b36,0x3becd139,0x3c0098b7,0x3ab9fbc1,0x3b7769d4,0x3b697de5,0x3b831640,0x3ac6b873,0x3ae6325b,0x3b7450bc,0x3998822e,0x3b27a0e2,0x3bcec750,0x3a8cee84,0x3adbc67c,0x3abd535e,0x3b55025a,0x3b501cb9,0x3b9661e6,0x3b769510,0x3aae2e28,0x3b11667d,0x3c1d1d7a,0x3a961995,0x39427b92,0x3b4a987b,0x3b71c1ce,0x3b2e4f11,0x3c1d1a1c,0x3ba51b3b,0x3bd3a4e0,0x3be9e2af,0x3b10a78b,0x39130572,0x3c49c056,0x3b528a5b,0x3b2c9a6c,0x3c0bb993,0x3b900810,0x3b0e7266,0x3b825e3b,0x3b67dd1f,0x3b9995a4};

const s16 DistanceF32_PathRef10_s16[22]={0x0000,0x0000,0x0001,0x0000,0x0002,0x0000,0x0003,0x0000,0x0004,0x0000,0x0005,0x0001,0x0006,0x0002,0x0007,0x0002,0x0008,0x0002,0x0009,0x0003,0x0009,0x0004};

const u32 DistanceF32_Query10_f32[10]={0x3dabc511,0x3f2e4a66,0x3f88a5f1,0x3f639f09,0x3ed9ab29,0xbea6dd0f,0xbf4f317c,0xbf68e848,0xbf23e865,0x3d8dcc1a};

const u32 DistanceF32_Ref1_f32[10]={0x3f63b5fe,0x3f97046e,0x3f9ae03d,0x3fb2e7d5,0x3f80e323,0x3f9097aa,0x3f9a1384,0x3fa5821d,0x3fc4c259,0x3f472400};

const u32 DistanceF32_Ref2_f32[10]={0x41b6b3ba,0x41c35cc3,0x41e32de8,0x41ddf82e,0x41c35c3b,0x41d4a263,0x41db0f15,0x41d61028,0x41e0b123,0x41b5f5cd};

const u32 DistanceF32_Ref3_f32[10]={0x4081e7d9,0x40664a86,0x40580451,0x4077b3b3,0x406968db,0x4068fd5a,0x408c5a9a,0x40600926,0x406cb003,0x40393285};

const u32 DistanceF32_Ref4_f32[10]={0x42060ce8,0x4216c069,0x42255efd,0x424c075b,0x421233c7,0x422e4d4d,0x4230be1c,0x4225cc97,0x42221761,0x4207c3e2};

const u32 DistanceF32_Ref5_f32[10]={0x3f859d74,0x3f93ab9c,0x3f99520d,0x3fa68679,0x3f7fd83f,0x3f9274ed,0x3f96aa4e,0x3fa3da2d,0x3fa8963d,0x3f396ace};

const u32 DistanceF32_Ref6_f32[10]={0x3f83fb69,0x3f97fbf0,0x3f9811c1,0x3fa74a37,0x3f7f4cad,0x3f93b41b,0x3f9d3fc0,0x3fa14530,0x3fa44e0c,0x3f3aa672};

const u32 DistanceF32_Ref7_f32[10]={0x40fe1085,0x41022835,0x410afb8c,0x41283333,0x40f62da6,0x41138fd8,0x4111ee65,0x4109d81f,0x4106942b,0x40ee64a9};

const u32 DistanceF32_Ref8_f32[10]={0x3eb676e9,0x3eaf894a,0x3ed4d17d,0x3eae2504,0x3eb079f8,0x3ed571f9,0x3ecc3cf1,0x3ec9ce0f,0x3ea248ae,0x3ea9e5c8};

const u32 DistanceF32_Ref9_f32[10]={0x409aa2ab,0x40a8b1be,0x40902d52,0x40ab7998,0x4085ef55,0x40bd95cd,0x40bc1b1c,0x408f8efb,0x4106942b,0x40ee64a9};

const u32 DistanceF32_Template10_f32[5]={0x3f800000,0x3a50c095,0xbf7fffeb,0xbb1c9067,0x3f7fffab};
