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

const u32 SupportQ7_Samples1_f32[260]={0x3f51cb9c,0x3e917351,0x3eaff2fe,0x3e830cea,0x3f5f76ac,0x3f14ef92,0x3ef0391b,0x3f6114c7,0x3f2e861b,0x3e883c2b,0x3eb388e3,0x3eea1f64,0x3f62a99d,0x3f52b6d7,0x3f67e065,0x3e41910d,0x3f40b1c5,0x3dbcea86,0x3f7702c9,0x3f6fdd1d,0x3f52dbbb,0x3d4dd457,0x3d127ba6,0x3f01db69,0x3ce7a192,0x3bd9e64c,0x3e8cad3e,0x3e83573b,0x3ec74719,0x3eae0b15,0x3f5a5821,0x3f1800ff,0x3d621bc4,0x3f15c98d,0x3eae4fc1,0x3e40c4fb,0x3e12a8b3,0x3da75da8,0x3f2dea98,0x3d46ac35,0x3ee1bd72,0x3f7fe628,0x3e64f42c,0x3f369022,0x3f552149,0x3de4d2ca,0x3eaf57fc,0x3dcf6768,0x3f2aa7c3,0x3e79e666,0x3f047ad4,0x3f7f15bc,0x3de4e2a9,0x3f5ebb17,0x3eb10214,0x3b933766,0x3e9ae6cb,0x3ee9a9b8,0x3efd45e7,0x3e0c38cb,0x3f54cdc3,0x3f678646,0x3f67d230,0x3daccaf0,0x3f14bf9a,0x3f1ca1ec,0x3ed8fa75,0x3f2cdccd,0x3f241eb8,0x3f07ed6d,0x3eb6701f,0x3f71a6c0,0x3ea8742a,0x3f1a4fc3,0x3f0d0f1e,0x3ed544a8,0x3ed33f2e,0x3e1c90dc,0x3f72fa33,0x3ee00102,0x3f485b4b,0x3f56b6d7,0x3f08c203,0x3f57301a,0x3f6c01af,0x3e6e32d0,0x3ea4217a,0x3db5930d,0x3dbec57f,0x3e9ca970,0x3f4bf1d2,0x3eea3206,0x3db50bee,0x3ed0df69,0x3d32df51,0x3f66f5e6,0x3e15e3b9,0x3f76e95e,0x3ea718a1,0x3f800000,0x3f138640,0x3edbb9f9,0x3f7575fb,0x3f0befae,0x3f543875,0x3e6df3e3,0x3f085f90,0x3e9934c0,0x3de77168,0x3f18a176,0x3e46f709,0x3e849cd6,0x3eaa7311,0x3edbbba8,0x3f7f3526,0x3f0eb67c,0x3d77ad5e,0x3deadead,0x3f3d8a05,0x3e05411b,0x3f703ad2,0x3e603a5b,0x3f7d0dea,0x3f4c73b5,0x3f5f1350,0x3f0fbf99,0x3ef8b4e7,0x3ef846b0,0x3eec7855,0x3f19f03c,0x3f4bdfee,0x3edaef1b,0x3f2ab439,0x3f7d8e2c,0x3f6bc2d5,0x3f593741,0x3f368a8f,0x3f043a30,0x3f5c6097,0x3edb2f95,0x3cc4b254,0x3f231b44,0x3e98315b,0x3f38fec8,0x3f22f61f,0x3f564336,0x3ef889c6,0x3db3e996,0x3eb87873,0x3ebe16ed,0x3f4cc99c,0x3f7341bd,0x3f13ed35,0x3f580947,0x3eaa6f17,0x3f22d4e7,0x3f09b289,0x3f5de64e,0x3f1523a3,0x3ed4122b,0x3f3fa527,0x3e7b8487,0x3efafa40,0x3f6b6472,0x3bac14ca,0x3f5f9dae,0x3f15e0bc,0x3ef67924,0x3ed124d0,0x3ed8a1b4,0x3d9eee92,0x3db45c1f,0x3f201c30,0x3f5715af,0x3e0002fa,0x3e15590c,0x3c2d3d9b,0x3eea5256,0x3f37fca4,0x3e798e96,0x3dda7094,0x3f13c9f5,0x3d89cd8d,0x3e28d59a,0x3eada765,0x3eafd521,0x3f2e47af,0x3e34b409,0x3ebe3e6e,0x3f40490d,0x3eaf2bfa,0x3d8623ec,0x3d7ba2c7,0x3e89698c,0x3f5c28ac,0x3f5c3c47,0x3f5844a2,0x3e70e1a1,0x3f51380d,0x3f60b218,0x3d89330f,0x3f11dc0d,0x3d407295,0x3f696c77,0x3efba540,0x3e8cc6e5,0x3ef467a9,0x3ee19635,0x3f70312a,0x3f577235,0x3ed2ba77,0x3f63302f,0x3ea8bc77,0x3e5451c3,0x3dc84d34,0x3f6795df,0x3f01b79f,0x3f238948,0x3f6e866f,0x3f08dc06,0x3ee921f1,0x3e86b657,0x3f085a05,0x3f0951e3,0x3f4d1534,0x3f34eb04,0x3e968341,0x3e8fda71,0x3ef37a31,0x3e135e28,0x3ef15e93,0x3f0ebbcd,0x3f78ac9b,0x3c119c29,0x3f286800,0x3f1b25da,0x3e718f6d,0x3eb16368,0x3b870426,0x3f0f8f85,0x3f7c6cfc,0x3ee2fa19,0x3f32e885,0x3f4f39b0,0x3f06fc72,0x3f642057,0x3f53daf5,0x3f7b2982,0x3e3da9df,0x3eb15bf8,0x3d85b7bc,0x3e430088,0x3f4ccf28,0x3e11cde2,0x3e962d9c,0x3d5ac820,0xbf800000,0x3f800000,0xc0066666,0x40066666};

const q15 SupportQ7_Samples3_q15[260]={0x68E6,0x245D,0x2BFD,0x20C3,0x6FBB,0x4A78,0x3C0E,0x708A,0x5743,0x220F,0x2CE2,0x3A88,0x7155,0x695B,0x73F0,0x1832,0x6059,0x0BCF,0x7B81,0x77EF,0x696E,0x066F,0x0494,0x40EE,0x039F,0x00DA,0x232B,0x20D6,0x31D2,0x2B83,0x6D2C,0x4C00,0x0711,0x4AE5,0x2B94,0x1819,0x1255,0x0A76,0x56F5,0x0635,0x386F,0x7FF3,0x1C9F,0x5B48,0x6A91,0x0E4D,0x2BD6,0x0CF6,0x5554,0x1F3D,0x423D,0x7F8B,0x0E4E,0x6F5E,0x2C41,0x0093,0x26BA,0x3A6A,0x3F51,0x1187,0x6A67,0x73C3,0x73E9,0x0ACD,0x4A60,0x4E51,0x363F,0x566E,0x520F,0x43F7,0x2D9C,0x78D3,0x2A1D,0x4D28,0x4688,0x3551,0x34D0,0x1392,0x797D,0x3800,0x642E,0x6B5B,0x4461,0x6B98,0x7601,0x1DC6,0x2908,0x0B59,0x0BEC,0x272A,0x65F9,0x3A8D,0x0B51,0x3438,0x0597,0x737B,0x12BC,0x7B75,0x29C6,0x7FFF,0x49C3,0x36EE,0x7ABB,0x45F8,0x6A1C,0x1DBE,0x4430,0x264D,0x0E77,0x4C51,0x18DF,0x2127,0x2A9D,0x36EF,0x7F9B,0x475B,0x07BD,0x0EAE,0x5EC5,0x10A8,0x781D,0x1C07,0x7E87,0x663A,0x6F8A,0x47E0,0x3E2D,0x3E12,0x3B1E,0x4CF8,0x65F0,0x36BC,0x555A,0x7EC7,0x75E1,0x6C9C,0x5B45,0x421D,0x6E30,0x36CC,0x0313,0x518E,0x260C,0x5C7F,0x517B,0x6B22,0x3E22,0x0B3F,0x2E1E,0x2F86,0x6665,0x79A1,0x49F7,0x6C05,0x2A9C,0x516A,0x44D9,0x6EF3,0x4A92,0x3505,0x5FD3,0x1F71,0x3EBF,0x75B2,0x00AC,0x6FCF,0x4AF0,0x3D9E,0x3449,0x3628,0x09EF,0x0B46,0x500E,0x6B8B,0x1000,0x12AB,0x015A,0x3A95,0x5BFE,0x1F32,0x0DA7,0x49E5,0x089D,0x151B,0x2B6A,0x2BF5,0x5724,0x1697,0x2F90,0x6025,0x2BCB,0x0862,0x07DD,0x225A,0x6E14,0x6E1E,0x6C22,0x1E1C,0x689C,0x7059,0x0893,0x48EE,0x0604,0x74B6,0x3EE9,0x2332,0x3D1A,0x3866,0x7819,0x6BB9,0x34AF,0x7198,0x2A2F,0x1A8A,0x0C85,0x73CB,0x40DC,0x51C5,0x7743,0x446E,0x3A48,0x21AE,0x442D,0x44A9,0x668B,0x5A76,0x25A1,0x23F7,0x3CDF,0x126C,0x3C58,0x475E,0x7C56,0x0123,0x5434,0x4D93,0x1E32,0x2C59,0x0087,0x47C8,0x7E36,0x38BF,0x5974,0x679D,0x437E,0x7210,0x69ED,0x7D95,0x17B5,0x2C57,0x085B,0x1860,0x6668,0x123A,0x258B,0x06D6,0x8000,0x7FFF,0x8000,0x7FFF};

const q31 SupportQ7_Samples4_q31[260]={0x68E5CE34,0x245CD454,0x2BFCBF67,0x20C33A70,0x6FBB561E,0x4A77C911,0x3C0E46A1,0x708A636D,0x57430D9E,0x220F0ADF,0x2CE238CD,0x3A87D8E5,0x7154CE5F,0x695B6B60,0x73F0325F,0x1832219A,0x6058E245,0x0BCEA863,0x7B816489,0x77EE8E86,0x696DDD75,0x066EA2B5,0x0493DD31,0x40EDB455,0x039E8648,0x00D9E64C,0x232B4F8A,0x20D5CEC9,0x31D1C654,0x2B82C546,0x6D2C107B,0x4C007F63,0x0710DE24,0x4AE4C6A4,0x2B93F040,0x18189F6C,0x12551656,0x0A75DA7B,0x56F54BD1,0x063561A5,0x386F5C86,0x7FF313D6,0x1C9E8574,0x5B4810CF,0x6A90A44E,0x0E4D2CA1,0x2BD5FEE8,0x0CF6767F,0x5553E177,0x1F3CCCC6,0x423D69FA,0x7F8ADE2C,0x0E4E2A97,0x6F5D8B92,0x2C4084FB,0x00933766,0x26B9B2D6,0x3A6A6DE2,0x3F5179A2,0x1187195E,0x6A66E16D,0x73C322D1,0x73E917D3,0x0ACCAEFE,0x4A5FCCCE,0x4E50F62A,0x363E9D42,0x566E6678,0x520F5BC5,0x43F6B65B,0x2D9C07DE,0x78D35FF1,0x2A1D0A76,0x4D27E1A0,0x46878F12,0x355129ED,0x34CFCB89,0x13921B80,0x797D196D,0x38004064,0x642DA588,0x6B5B6BA2,0x44610169,0x6B980CC6,0x7600D79F,0x1DC659F6,0x29085E6C,0x0B5930D3,0x0BEC57ED,0x272A5BF8,0x65F8E8F2,0x3A8C8196,0x0B50BEE2,0x3437DA33,0x0596FA8A,0x737AF30E,0x12BC7710,0x7B74AEFB,0x29C6285A,0x7FFFFFFF,0x49C31FCB,0x36EE7E30,0x7ABAFDBB,0x45F7D714,0x6A1C3ABA,0x1DBE7C68,0x442FC818,0x264D2FE6,0x0E77167B,0x4C50BB08,0x18DEE125,0x2127359B,0x2A9CC448,0x36EEE9E5,0x7F9A933A,0x475B3DEA,0x07BD6AED,0x0EADEAC9,0x5EC50256,0x10A82359,0x781D68D0,0x1C074B57,0x7E86F50D,0x6639DA68,0x6F89A824,0x47DFCC48,0x3E2D39A4,0x3E11AC17,0x3B1E1542,0x4CF81E28,0x65EFF706,0x36BBC6D5,0x555A1C44,0x7EC715D7,0x75E16AA9,0x6C9BA06D,0x5B454763,0x421D1807,0x6E304BBA,0x36CBE53E,0x0312C951,0x518DA1E6,0x260C56CD,0x5C7F6434,0x517B0FB2,0x6B219AEE,0x3E227180,0x0B3E995E,0x2E1E1CCF,0x2F85BB23,0x6664CDC8,0x79A0DE4F,0x49F69A91,0x6C04A34F,0x2A9BC5A1,0x516A73A3,0x44D94490,0x6EF326E8,0x4A91D15B,0x35048AAA,0x5FD29352,0x1F7090D6,0x3EBE9007,0x75B23930,0x00AC14CA,0x6FCED6FB,0x4AF05DFA,0x3D9E48F0,0x344933E6,0x36286CEE,0x09EEE923,0x0B45C1F0,0x500E1822,0x6B8AD7B1,0x10005F45,0x12AB2175,0x015A7B35,0x3A949568,0x5BFE51C3,0x1F31D2D0,0x0DA70943,0x49E4FA8F,0x089CD8D5,0x151AB332,0x2B69D923,0x2BF54828,0x5723D75D,0x1696811D,0x2F8F9B9D,0x60248661,0x2BCAFE77,0x08623EC7,0x07DD163B,0x225A631E,0x6E14563E,0x6E1E236B,0x6C2250F9,0x1E1C3426,0x689C0671,0x70590BDE,0x089330EA,0x48EE0645,0x060394A6,0x74B63B44,0x3EE95001,0x2331B954,0x3D19EA59,0x38658D52,0x7818951D,0x6BB91A70,0x34AE9DA3,0x719817BE,0x2A2F1DC6,0x1A8A385B,0x0C84D33C,0x73CAEFB6,0x40DBCF84,0x51C4A412,0x77433789,0x446E033F,0x3A487C3E,0x21AD95C1,0x442D0299,0x44A8F183,0x668A9A2D,0x5A758230,0x25A0D025,0x23F69C3F,0x3CDE8C4E,0x126BC509,0x3C57A4B1,0x475DE65E,0x7C564D68,0x01233851,0x54340006,0x4D92ECE5,0x1E31ED9D,0x2C58D9EF,0x00870426,0x47C7C262,0x7E367DEC,0x38BE8656,0x59744280,0x679CD813,0x437E392C,0x72102B5D,0x69ED7A65,0x7D94C0E4,0x17B53BD8,0x2C56FDED,0x085B7BC4,0x18601108,0x666793D8,0x1239BC48,0x258B66F2,0x06D640FD,0x80000000,0x7FFFFFFF,0x80000000,0x7FFFFFFF};

const q7 SupportQ7_Samples5_q7[260]={0x69,0x24,0x2C,0x21,0x70,0x4A,0x3C,0x71,0x57,0x22,0x2D,0x3B,0x71,0x69,0x74,0x18,0x60,0x0C,0x7C,0x78,0x69,0x06,0x05,0x41,0x04,0x01,0x23,0x21,0x32,0x2C,0x6D,0x4C,0x07,0x4B,0x2C,0x18,0x12,0x0A,0x57,0x06,0x38,0x7F,0x1D,0x5B,0x6B,0x0E,0x2C,0x0D,0x55,0x1F,0x42,0x7F,0x0E,0x6F,0x2C,0x01,0x27,0x3A,0x3F,0x12,0x6A,0x74,0x74,0x0B,0x4A,0x4E,0x36,0x56,0x52,0x44,0x2E,0x79,0x2A,0x4D,0x47,0x35,0x35,0x14,0x79,0x38,0x64,0x6B,0x44,0x6C,0x76,0x1E,0x29,0x0B,0x0C,0x27,0x66,0x3B,0x0B,0x34,0x06,0x73,0x13,0x7B,0x2A,0x7F,0x4A,0x37,0x7B,0x46,0x6A,0x1E,0x44,0x26,0x0E,0x4C,0x19,0x21,0x2B,0x37,0x7F,0x47,0x08,0x0F,0x5F,0x11,0x78,0x1C,0x7F,0x66,0x70,0x48,0x3E,0x3E,0x3B,0x4D,0x66,0x37,0x55,0x7F,0x76,0x6D,0x5B,0x42,0x6E,0x37,0x03,0x52,0x26,0x5C,0x51,0x6B,0x3E,0x0B,0x2E,0x30,0x66,0x7A,0x4A,0x6C,0x2B,0x51,0x45,0x6F,0x4B,0x35,0x60,0x1F,0x3F,0x76,0x01,0x70,0x4B,0x3E,0x34,0x36,0x0A,0x0B,0x50,0x6C,0x10,0x13,0x01,0x3B,0x5C,0x1F,0x0E,0x4A,0x09,0x15,0x2B,0x2C,0x57,0x17,0x30,0x60,0x2C,0x08,0x08,0x22,0x6E,0x6E,0x6C,0x1E,0x69,0x70,0x09,0x49,0x06,0x75,0x3F,0x23,0x3D,0x38,0x78,0x6C,0x35,0x72,0x2A,0x1B,0x0D,0x74,0x41,0x52,0x77,0x44,0x3A,0x22,0x44,0x45,0x67,0x5A,0x26,0x24,0x3D,0x12,0x3C,0x47,0x7C,0x01,0x54,0x4E,0x1E,0x2C,0x01,0x48,0x7E,0x39,0x59,0x68,0x43,0x72,0x6A,0x7E,0x18,0x2C,0x08,0x18,0x66,0x12,0x26,0x07,0x80,0x7F,0x80,0x7F};

const u64 SupportQ7_Samples6_f64[260]={0x3fea39738cfa5a91,0x3fd22e6a29c137d7,0x3fd5fe5fb3864022,0x3fd0619d37d5bac0,0x3febeed58777ff40,0x3fe29df2443df1dc,0x3fde0723504efc08,0x3fec2298db5ebe14,0x3fe5d0c367766dfc,0x3fd107856f48a7e1,0x3fd6711c66a2ad59,0x3fdd43ec7247f22c,0x3fec553397d6a146,0x3fea56dad810e279,0x3fecfc0c97bd0d5d,0x3fc832219a6c1ef1,0x3fe81638912d3467,0x3fb79d50c624a673,0x3feee05922566a68,0x3fedfba3a17c3928,0x3fea5b775d41b9bc,0x3fa9ba8ad30a7256,0x3fa24f74c409b6ac,0x3fe03b6d1523b668,0x3f9cf4323fac5e25,0x3f7b3cc9712025e3,0x3fd195a7c4e9130b,0x3fd06ae764b3ebb4,0x3fd8e8e329f6aac8,0x3fd5c162a2cc58e8,0x3feb4b041eab0bd4,0x3fe3001fd8c4b797,0x3fac43788f5e8afb,0x3fe2b931a9053f58,0x3fd5c9f81fe9cfea,0x3fc8189f6c53e937,0x3fc2551655b114e8,0x3fb4ebb4f6894f97,0x3fe5bd52f44dc96a,0x3fa8d58695fb5834,0x3fdc37ae430e075b,0x3feffcc4f56901c1,0x3fcc9e85744daf2c,0x3fe6d20433b664cf,0x3feaa429139b022d,0x3fbc9a5942fba73f,0x3fd5eaff73eabb46,0x3fb9ececfdc14b77,0x3fe554f85dbb992b,0x3fcf3cccc5f91561,0x3fe08f5a7e83c82a,0x3fefe2b78b0b8551,0x3fbc9c552ebfa092,0x3febd762e492ad3d,0x3fd620427d7d4bb9,0x3f7266ecc810fcd7,0x3fd35cd96aeb70ad,0x3fdd3536f12bba66,0x3fdfa8bcd0e4a612,0x3fc187195e49e325,0x3fea99b85b45df5d,0x3fecf0c8b425032a,0x3fecfa45f4cb27b3,0x3fb5995dfb0ced50,0x3fe297f333859c60,0x3fe3943d8a6d7d17,0x3fdb1f4ea10ce9b6,0x3fe59b999e1b3db8,0x3fe483d6f13bf8cf,0x3fe0fdad96bc812f,0x3fd6ce03eef46904,0x3fee34d7fc44cb4f,0x3fd50e853ae23127,0x3fe349f867f725cc,0x3fe1a1e3c4985182,0x3fdaa894f660008e,0x3fda67e5c48e87a2,0x3fc3921b7f819341,0x3fee5f465b46a1c8,0x3fdc002031fe2608,0x3fe90b69621486aa,0x3fead6dae8738ec9,0x3fe118405a34f731,0x3feae603317922ac,0x3fed8035e7b4407c,0x3fcdc659f599da72,0x3fd4842f35e81f8a,0x3fb6b261a59e4fd7,0x3fb7d8afd9264289,0x3fd3952dfbdcde4d,0x3fe97e3a3c84fe3a,0x3fdd4640cb2b0db9,0x3fb6a17dc4d5d442,0x3fda1bed197786cd,0x3fa65bea27e92c30,0x3fecdebcc3715ca6,0x3fc2bc77100b471b,0x3feedd2bbece1dbe,0x3fd4e3142ccc00aa,0x3ff0000000000000,0x3fe270c7f2de7c05,0x3fdb773f17ff3c81,0x3feeaebf6ea88860,0x3fe17df5c4fe2e31,0x3fea870eae634782,0x3fcdbe7c687f1806,0x3fe10bf2061151b6,0x3fd32697f321e448,0x3fbcee2cf5288222,0x3fe3142ec1ecf1fc,0x3fc8dee12512f0b8,0x3fd0939acdb42e93,0x3fd54e62243c9d37,0x3fdb7774f27bb041,0x3fefe6a4ce94dcda,0x3fe1d6cf7a75fd93,0x3faef5abb5180bf6,0x3fbd5bd59264f6cf,0x3fe7b140956ca173,0x3fc0a823594ca5c5,0x3fee075a341b5f4b,0x3fcc074b57277f0f,0x3fefa1bd43544569,0x3fe98e769a05bad8,0x3febe26a08ee5f03,0x3fe1f7f311fb1dc5,0x3fdf169cd1c88505,0x3fdf08d60bac70ef,0x3fdd8f0aa0d7d345,0x3fe33e0789e9b862,0x3fe97bfdc191dbc8,0x3fdb5de36a55a25c,0x3fe5568710fae144,0x3fefb1c575aaf962,0x3fed785aaa594be0,0x3feb26e81b564b0f,0x3fe6d151d8a43cc9,0x3fe0874601c3483c,0x3feb8c12ee79ba77,0x3fdb65f29f104cfa,0x3f98964a8bdba905,0x3fe4636879940307,0x3fd3062b66945b27,0x3fe71fd90ced6549,0x3fe45ec3ec754af9,0x3feac866bb7db8c1,0x3fdf1138bfc7490d,0x3fb67d32bc674365,0x3fd70f0e6759b6f4,0x3fd7c2dd9145a7bb,0x3fe99933720c6af0,0x3fee683793bbaf81,0x3fe27da6a45b5424,0x3feb0128d3a819fc,0x3fd54de2d0913259,0x3fe45a9ce8b185bf,0x3fe13651241a768a,0x3febbcc9b9f53cd8,0x3fe2a47456c6404c,0x3fda824555168a18,0x3fe7f4a4d4667e9c,0x3fcf7090d66f1d57,0x3fdf5f48038a098a,0x3fed6c8e4c14d3ec,0x3f758299330af367,0x3febf3b5bec95a80,0x3fe2bc177e9dcfb7,0x3fdecf2477ec50bc,0x3fda2499f2c64e4c,0x3fdb143676c64d75,0x3fb3ddd245d75948,0x3fb68b83df24b959,0x3fe403860873527b,0x3feae2b5ec4aebff,0x3fc0005f4484e974,0x3fc2ab21748f8439,0x3f85a7b357b34d2d,0x3fdd4a4ab43cf4db,0x3fe6ff9470b371f5,0x3fcf31d2cfd514c9,0x3fbb4e1285d6f82a,0x3fe2793ea3ce6107,0x3fb139b1a9a64223,0x3fc51ab3319c9940,0x3fd5b4ec91badd4d,0x3fd5faa413cdeaf9,0x3fe5c8f5d7460340,0x3fc696811d2632eb,0x3fd7c7cdce84ca7b,0x3fe809219827e281,0x3fd5e57f3b585b1a,0x3fb0c47d8d898152,0x3faf7458ec053237,0x3fd12d318f1f5deb,0x3feb85158f7dff3d,0x3feb8788dabcb1a8,0x3feb08943e22fc53,0x3fce1c34262bff69,0x3fea27019c5f55d2,0x3fec1642f7869c11,0x3fb12661d38f5289,0x3fe23b8191564988,0x3fa80e52968bd025,0x3fed2d8ed0f02b56,0x3fdf74a800591daa,0x3fd198dca9d72441,0x3fde8cf52cadbb92,0x3fdc32c6a9084f63,0x3fee0625473dde19,0x3feaee469c010d3f,0x3fda574ed178aea4,0x3fec6605ef840aea,0x3fd5178ee3011067,0x3fca8a385b04f689,0x3fb909a677138d4e,0x3fecf2bbed7f5e45,0x3fe036f3e11e4869,0x3fe4712904606bc1,0x3fedd0cde2509a8c,0x3fe11b80cfda0c6e,0x3fdd243e1ecb224b,0x3fd0d6cae0732f43,0x3fe10b40a6569805,0x3fe12a3c60b05881,0x3fe9a2a68b550b9f,0x3fe69d608c16ce32,0x3fd2d0681263d4dc,0x3fd1fb4e1f46139c,0x3fde6f462728f0ed,0x3fc26bc508bfe4c4,0x3fde2bd258b70142,0x3fe1d779976348ea,0x3fef15935a1af356,0x3f82338511fdaedc,0x3fe50d0001967b6f,0x3fe364bb392ac6c2,0x3fce31ed9c8117df,0x3fd62c6cf7bf3f91,0x3f70e084ce63400f,0x3fe1f1f0988e95fe,0x3fef8d9f7af4b4f6,0x3fdc5f432afeaeae,0x3fe65d10a0188ec2,0x3fe9e73604a790e4,0x3fe0df8e4af034c6,0x3fec840ad758ff68,0x3fea7b5e9956baff,0x3fef653038ecc991,0x3fc7b53bd86b6149,0x3fd62b7ef69e9a2c,0x3fb0b6f7887ae5da,0x3fc8601107a3bd67,0x3fe999e4f6119411,0x3fc239bc487e40e2,0x3fd2c5b378dcf5f2,0x3fab5903f48b1420,0xbff0000000000000,0x3ff0000000000000,0xc000cccccccccccd,0x4000cccccccccccd};

