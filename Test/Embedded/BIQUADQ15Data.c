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

const q15 BIQUADQ15_AllBiquadCoefs2_q15[828]={0x00A4,0x0000,0x00F0,0x00A4,0xFF54,0xFFFB,0x2000,0x0000,0xE1A8,0x2000,0x00D8,0xFFD4,0x2000,0x0000,0xDD28,0x2000,0x039C,0xFFC5,0x2000,0x0000,0x3FA9,0x2000,0xF46C,0xFEF2,0x2000,0x0000,0xCFBA,0x2000,0x0C77,0xFDE4,0x2000,0x0000,0x3F3A,0x2000,0xECC5,0xFCBF,0x2000,0x0000,0xC5A5,0x2000,0x1F10,0xF77E,0x00A4,0x0000,0xFEBD,0x00A4,0x0604,0xFFB8,0x2000,0x0000,0xC136,0x2000,0xF56B,0xFEBE,0x2000,0x0000,0x37F1,0x2000,0xF25B,0xFD13,0x2000,0x0000,0xCCC6,0x2000,0x0D1F,0xFA86,0x2000,0x0000,0x00D5,0x2000,0x024D,0xF97F,0x2000,0x0000,0xFBCC,0x2000,0x0FBF,0xF67F,0x2000,0x0000,0x311F,0x2000,0xE2E4,0xF409,0x00A4,0x0000,0x013E,0x00A4,0x06C9,0xFF9B,0x2000,0x0000,0x212E,0x2000,0xF84B,0xFF1E,0x2000,0x0000,0x3770,0x2000,0xF6C3,0xFF16,0x2000,0x0000,0x2042,0x2000,0x019B,0xFCF9,0x2000,0x0000,0x0BE2,0x2000,0xFA49,0xFC09,0x2000,0x0000,0xED59,0x2000,0x22E2,0xF5F5,0x2000,0x0000,0xD61C,0x2000,0x1BD6,0xF3DB,0x00A4,0x0000,0xFF4B,0x00A4,0xFDC1,0xFFF6,0x2000,0x0000,0xC006,0x2000,0x02AC,0xFFF1,0x2000,0x0000,0xE216,0x2000,0xFC76,0xFFD2,0x2000,0x0000,0xE986,0x2000,0xFDCA,0xFF86,0x2000,0x0000,0x3743,0x2000,0xFD0B,0xFF67,0x2000,0x0000,0xC03F,0x2000,0x0883,0xFF5B,0x2000,0x0000,0xEF2C,0x2000,0x00D3,0xFF16,0x2000,0x0000,0x0026,0x2000,0xFB96,0xFE5E,0x2000,0x0000,0x0689,0x2000,0xF703,0xFD34,0x2000,0x0000,0xD9A7,0x2000,0x100A,0xFCE7,0x2000,0x0000,0x126F,0x2000,0xFA01,0xFC37,0x2000,0x0000,0x2397,0x2000,0xF37B,0xFC01,0x2000,0x0000,0x3C9E,0x2000,0xE4CA,0xF9E0,0x2000,0x0000,0x32CC,0x2000,0xE9CF,0xF869,0x2000,0x0000,0xCA40,0x2000,0x1B53,0xF611,0x2000,0x0000,0x08BB,0x2000,0xF96A,0xF395,0x00A4,0x0000,0xFEB8,0x00A4,0xFDE0,0xFFF7,0x2000,0x0000,0xC0E2,0x2000,0xFF28,0xFFF0,0x2000,0x0000,0xFAC1,0x2000,0x00A7,0xFFAA,0x2000,0x0000,0xFC0C,0x2000,0xFC0C,0xFFA6,0x2000,0x0000,0xC153,0x2000,0x0955,0xFF1F,0x2000,0x0000,0x0328,0x2000,0xFB23,0xFE90,0x2000,0x0000,0x1110,0x2000,0xFC4C,0xFE7C,0x2000,0x0000,0x2075,0x2000,0xF695,0xFE42,0x2000,0x0000,0x2E77,0x2000,0xED47,0xFC9E,0x2000,0x0000,0x0666,0x2000,0xFDDE,0xFC41,0x2000,0x0000,0xF544,0x2000,0x0768,0xF9B3,0x2000,0x0000,0xD7B5,0x2000,0x109B,0xF97F,0x2000,0x0000,0x2E92,0x2000,0xDF6B,0xF784,0x2000,0x0000,0xC341,0x2000,0x1F3E,0xF55B,0x2000,0x0000,0xF1E9,0x2000,0x0FD9,0xF245,0x2000,0x0000,0x3B9A,0x2000,0xD9FD,0xF21A,0x00A4,0x0000,0xFEC5,0x00A4,0xFFFD,0xFFC4,0x2000,0x0000,0x3EC6,0x2000,0xF8F4,0xFF90,0x2000,0x0000,0xCCA9,0x2000,0x0660,0xFF16,0x2000,0x0000,0x3685,0x2000,0xFD65,0xFEF9,0x2000,0x0000,0xD370,0x2000,0x05F6,0xFEB7,0x2000,0x0000,0x34AF,0x2000,0xFD94,0xFDF6,0x2000,0x0000,0xE4DE,0x2000,0xFD7F,0xFC99,0x2000,0x0000,0xE79A,0x2000,0x09D3,0xFB4C,0x2000,0x0000,0x25BA,0x2000,0xF862,0xFADC,0x2000,0x0000,0xC21C,0x2000,0x1AA3,0xFA25,0x2000,0x0000,0xEA8F,0x2000,0x0B1F,0xF634,0x2000,0x0000,0xECFD,0x2000,0x0280,0xF56E,0x2000,0x0000,0xF0D4,0x2000,0xFC6E,0xF50B,0x2000,0x0000,0xCFC5,0x2000,0x1E9A,0xF2D9,0x2000,0x0000,0x2288,0x2000,0xECA0,0xF207,0x2000,0x0000,0x224F,0x2000,0xE967,0xF068,0x00A4,0x0000,0xFED7,0x00A4,0xFFD1,0x0000,0x2000,0x0000,0xD0F2,0x2000,0xFD7E,0xFFEF,0x2000,0x0000,0x279D,0x2000,0xFF67,0xFFB3,0x2000,0x0000,0xC04D,0x2000,0x091A,0xFF57,0x2000,0x0000,0x296D,0x2000,0xF6C3,0xFF50,0x2000,0x0000,0xD6E6,0x2000,0x06D1,0xFEB9,0x2000,0x0000,0x1FC9,0x2000,0xF6B9,0xFD79,0x2000,0x0000,0xDB08,0x2000,0x0363,0xFCE0,0x2000,0x0000,0x1C03,0x2000,0xF9E3,0xFCDD,0x2000,0x0000,0x33A3,0x2000,0xEAED,0xFC2B,0x2000,0x0000,0x3716,0x2000,0xE7D8,0xFB71,0x2000,0x0000,0x3FDD,0x2000,0xE8AA,0xFB69,0x2000,0x0000,0xC76B,0x2000,0x158D,0xFAE0,0x2000,0x0000,0xE3C8,0x2000,0x03C4,0xFA01,0x2000,0x0000,0xE42D,0x2000,0x0426,0xF937,0x2000,0x0000,0xC000,0x2000,0x1E23,0xF8E4,0x2000,0x0000,0x11DF,0x2000,0xF8CC,0xF795,0x2000,0x0000,0xD0DE,0x2000,0x1B30,0xF6D6,0x2000,0x0000,0x31A1,0x2000,0xE503,0xF6AA,0x2000,0x0000,0xE06E,0x2000,0x1184,0xF662,0x2000,0x0000,0xF79F,0x2000,0x0A09,0xF656,0x2000,0x0000,0x2B92,0x2000,0xE74A,0xF652,0x2000,0x0000,0x3BCE,0x2000,0xDB85,0xF35A,0x00A4,0x0000,0x0140,0x00A4,0xFE0C,0xFFF8,0x2000,0x0000,0x3A8C,0x2000,0x02A2,0xFFC9,0x2000,0x0000,0x27ED,0x2000,0x01EC,0xFFC0,0x2000,0x0000,0x1808,0x2000,0x0423,0xFF36,0x2000,0x0000,0x39AE,0x2000,0xF774,0xFF33,0x2000,0x0000,0x164C,0x2000,0x1230,0xFD35,0x2000,0x0000,0xE299,0x2000,0x0CD9,0xFD18,0x2000,0x0000,0x2EEE,0x2000,0xF27A,0xFD05,0x2000,0x0000,0x0857,0x2000,0x0175,0xFCCD,0x2000,0x0000,0xCF3C,0x2000,0x186F,0xFB51,0x2000,0x0000,0x3E1C,0x2000,0xE6BE,0xFA87,0x2000,0x0000,0xEF56,0x2000,0x0423,0xFA4F,0x2000,0x0000,0x04B5,0x2000,0x0220,0xF7F2,0x2000,0x0000,0xCCF0,0x2000,0x2059,0xF738,0x2000,0x0000,0x3CD6,0x2000,0xE040,0xF725,0x2000,0x0000,0x3F0C,0x2000,0xDD44,0xF670,0x2000,0x0000,0xD57F,0x2000,0x163F,0xF613,0x2000,0x0000,0x20F9,0x2000,0xEEDA,0xF5F0,0x2000,0x0000,0x1B5B,0x2000,0xEF09,0xF56A,0x2000,0x0000,0x2117,0x2000,0xEAF9,0xF48D,0x2000,0x0000,0xE263,0x2000,0x12AC,0xF448,0x2000,0x0000,0xC73D,0x2000,0x23F1,0xF2BF,0x2000,0x0000,0x392B,0x2000,0xDAB5,0xF1F9,0x00A4,0x0000,0xFEFC,0x00A4,0xFFF8,0x0000,0x2000,0x0000,0xD11D,0x2000,0x00DE,0xFFFD,0x2000,0x0000,0xD190,0x2000,0x02FA,0xFFDD,0x2000,0x0000,0xD363,0x2000,0xFE53,0xFFD0,0x2000,0x0000,0xCCD7,0x2000,0x06E4,0xFF98,0x2000,0x0000,0xD602,0x2000,0xFA28,0xFF5F,0x2000,0x0000,0x3FEC,0x2000,0xF6D6,0xFF10,0x2000,0x0000,0x3E91,0x2000,0xFA21,0xFF10,0x2000,0x0000,0xD7C5,0x2000,0xFE66,0xFE4A,0x2000,0x0000,0xEBB7,0x2000,0xFCB5,0xFDAA,0x2000,0x0000,0xE9D1,0x2000,0x06C2,0xFD6D,0x2000,0x0000,0xECDA,0x2000,0xF90C,0xFC14,0x2000,0x0000,0x2423,0x2000,0xEA46,0xF8F9,0x2000,0x0000,0x249D,0x2000,0xE6F5,0xF8A0,0x2000,0x0000,0x3390,0x2000,0xE75C,0xF89C,0x2000,0x0000,0xCBB8,0x2000,0x1E3D,0xF893,0x2000,0x0000,0x3C7E,0x2000,0xE220,0xF7C8,0x2000,0x0000,0x2A87,0x2000,0xE553,0xF495,0x2000,0x0000,0xC8D4,0x2000,0x23B2,0xF387,0x2000,0x0000,0x2283,0x2000,0xF8AD,0xF0E3,0x2000,0x0000,0xD1C0,0x2000,0x1FA7,0xF0D9,0x2000,0x0000,0x1524,0x2000,0xF477,0xF08C,0x2000,0x0000,0xC042,0x2000,0x2BE3,0xF067};

const s16 BIQUADQ15_AllBiquadConfigs2_s16[18]={0x0007,0x0007,0x0007,0x0010,0x0007,0x0017,0x0010,0x0007,0x0010,0x0010,0x0010,0x0017,0x0017,0x0007,0x0017,0x0010,0x0017,0x0017};

const q15 BIQUADQ15_AllBiquadInputs2_q15[138]={0xC7D6,0x1008,0x7FFF,0x558D,0x725B,0x5ED4,0x1313,0xD8B7,0xA9A2,0xDB34,0x7FFF,0x39FD,0xE74D,0xC995,0xDAB3,0x36D7,0xF7E5,0xF829,0x5E1B,0xCD5C,0xF08E,0xD383,0x5260,0x0CE7,0xDB24,0xD1E7,0x5C7D,0x555E,0xA36A,0xC721,0xF4B0,0x435E,0x1CC8,0xEB4E,0x6760,0x8BF7,0x1170,0x3019,0x5529,0x6DAF,0x2FAF,0x9829,0xFA82,0xC3C8,0xEF7E,0x8000,0x7FFF,0x3D5B,0xFCE1,0x481F,0xF0EC,0xF3BB,0x6865,0xF87D,0x5453,0xDE2C,0xDBE9,0x7F45,0x5DA8,0xDE04,0xE9CA,0x62D3,0x0586,0xC765,0x7FFF,0xA3FB,0xC78E,0xBBB4,0xEC76,0xFD22,0x221C,0x1D4A,0xE236,0x12C1,0x2459,0x02A3,0x6D16,0x7FFF,0xF61A,0xE60F,0x1865,0xF2A5,0xFC24,0xC5E0,0x09D2,0x56F8,0x17A8,0x2AB3,0xFD87,0xF0F5,0x09A5,0xE62C,0x1769,0x1779,0xA83E,0x1AF3,0xD367,0x8000,0x1982,0x0027,0xA2C7,0xEF9E,0xE625,0xE50A,0x8000,0x1DA5,0xEFEA,0xBAEA,0xF856,0xB03E,0x5A90,0xFF81,0x000A,0x3EC6,0x069E,0x2D21,0x1465,0xBA22,0x0707,0x3627,0xDE20,0xF16F,0x17DC,0x0F06,0xC85F,0x2ADD,0x7FFF,0x44B5,0xA8FC,0xED24,0x3851,0x3DEA,0xFEE7,0x3218,0x2DC1,0xA651,0xF06D,0x64A0};

const q15 BIQUADQ15_AllBiquadRefs2_q15[138]={0xFEE0,0xFFAC,0x0446,0x0118,0xFCEC,0x0772,0x0917,0xFF37,0x0085,0x01FC,0x00EB,0xF96E,0x038E,0xFEE4,0x0235,0x031D,0xFEEA,0xF7DC,0x048E,0xFD4F,0x0840,0xFD64,0x00BD,0x0042,0x00BD,0xFF7C,0xF9B4,0xF0A9,0xEB6C,0xF0F2,0xFFF5,0x1045,0x1B3B,0x2046,0x246E,0x2DB6,0x3F7F,0x58A2,0x7632,0x7FFF,0x7FFF,0x7FFF,0x7FFF,0x7FFF,0x7FFF,0x7FFF,0x028F,0xF6AF,0x1776,0xD640,0x3A39,0xBDC2,0x3EE3,0xFFDA,0x0262,0xF576,0x1E3C,0xBBCD,0x7FFF,0x8000,0x7FFF,0x8000,0x7FFF,0x8000,0x7FFF,0x8000,0x7FFF,0x8000,0x7FFF,0xFFF1,0x00D0,0xFEEA,0xFF74,0x039C,0xFDDB,0xFBEC,0x0843,0x015C,0xF2F2,0x07E5,0x0F59,0xEBAF,0xF7E6,0x2045,0xFCAC,0xD540,0x1D5D,0x28E3,0xC7F1,0xECC7,0x4C23,0xF54B,0x0078,0xFF34,0xFE67,0x05B1,0xF994,0x0274,0xFB28,0x0001,0xFE2C,0xEAE9,0x84C1,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x00E7,0xFA5F,0x0F80,0xEC47,0xFE4A,0x2C66,0xC6F3,0x02B6,0x388E,0xE8AD,0xCDE2,0xF34E,0x7FFF,0x8000,0xC47F,0x7FFF,0xEF1D,0x8000,0x33ED,0x7FFF,0x8000,0x8000,0x7FFF};

const q15 BIQUADQ15_BiquadCoefs1_q15[18]={0x00A4,0x0000,0xFF4F,0x00A4,0x37CF,0xE614,0x2000,0x0000,0xCD0D,0x2000,0x37E6,0xE1E4,0x2000,0x0000,0xC003,0x2000,0x3EA4,0xE144};

const q15 BIQUADQ15_BiquadInput1_q15[100]={0xE62B,0x1CF7,0x3208,0x37FC,0x2781,0x3AD3,0x69CF,0x5E5B,0x2BC7,0xF39B,0xFACD,0xFC7A,0xD180,0xBC84,0xAEE2,0xDA97,0xD292,0xD9FC,0xAF9D,0xCA17,0xFAD5,0x4342,0x2821,0x2EB8,0x3F63,0x46A5,0x4E09,0x3C16,0x1876,0x1355,0x04C3,0x1530,0xD8FB,0x95D8,0x9DDB,0xD93C,0xDC86,0xD476,0xC63A,0xCDC3,0x267F,0x3926,0x25C3,0x31E3,0x4759,0x5D47,0x690D,0x3D75,0x12E4,0xF69C,0xF606,0x0373,0xCB95,0x8000,0xA910,0xB61A,0xDDFF,0xA016,0xC5D5,0xDF9E,0x1FA5,0x3811,0x29D2,0x061A,0x291F,0x570A,0x6886,0x383D,0x12A8,0x15C2,0xE5EE,0xEADA,0xB11B,0x9FC1,0x9EDD,0xBEE8,0xC9B5,0xB03B,0xB88E,0xE495,0x2595,0x5D53,0x2599,0x295B,0x4C34,0x6936,0x5B61,0x15D5,0x07B1,0x056F,0x08EE,0xF182,0xD6CE,0xABFD,0xB1BC,0xC994,0xEC29,0xC002,0xC69B,0x168A};

const q15 BIQUADQ15_BiquadOutput1_q15[100]={0xFF7C,0x002E,0x0092,0x0195,0x0324,0x0618,0x0A77,0x0F3E,0x1487,0x19BA,0x1EB8,0x219D,0x2141,0x1DE7,0x169B,0x0C5C,0xFE58,0xEF0A,0xDE9A,0xD05E,0xC538,0xBF56,0xBE37,0xC44B,0xD056,0xE104,0xF4F7,0x09C0,0x1D29,0x2DA1,0x38BC,0x3E46,0x3C2F,0x3397,0x2617,0x14EA,0x00F7,0xED60,0xDBD4,0xCE0E,0xC652,0xC375,0xC67F,0xCFAD,0xDD6C,0xEE73,0x0148,0x138E,0x242A,0x314B,0x39D4,0x3D0E,0x399C,0x302B,0x2306,0x1120,0xFDB2,0xE88B,0xD68F,0xC761,0xBDD7,0xBA29,0xBD05,0xC5FF,0xD530,0xE847,0xFD79,0x1256,0x25A3,0x358B,0x3F18,0x4334,0x3F99,0x363C,0x2764,0x150A,0x007C,0xEB9B,0xD930,0xCACC,0xC200,0xBFE2,0xC359,0xCE50,0xDEC4,0xF2F7,0x08D3,0x1DD8,0x3119,0x3FA3,0x483F,0x49DD,0x44C7,0x3912,0x28C3,0x151E,0x008B,0xEBE5,0xDAE7,0xCF40};

const q15 BIQUADQ15_Coefs1_q15[20]={0xD1F8,0xE8FE,0x7FFF,0xC947,0x3ED7,0xC514,0xF7D3,0x1D78,0x3DBD,0x346C,0x99B6,0xF040,0x04A1,0x001A,0x3766,0x2156,0xB488,0x5BFA,0x2997,0xBB98};

const q15 BIQUADQ15_Samples1_q15[512]={0x4F82,0x22B8,0x2A23,0xC20A,0x397B,0x0A07,0xC1A5,0x6DE4,0xFCA9,0xFB1B,0x2E11,0xCE41,0xC029,0x0180,0xF235,0xD48B,0x34F2,0x324A,0x1683,0x246C,0x191C,0xC9FC,0xDCDA,0xEDF9,0x36BA,0xEB17,0xD742,0xFCCA,0xA802,0xEF5C,0x2C01,0xB493,0x32E0,0xEF05,0x0193,0xD37D,0xEC7D,0xEEBD,0x0040,0x0F8D,0x3726,0x1CFD,0xEFB7,0x3D0F,0x1CDE,0x4910,0x131E,0xF3AC,0x2720,0xC3AB,0xE2B1,0x0DE3,0xF17D,0xC570,0x186E,0xFF0F,0x2949,0xAC25,0x4692,0x91D6,0x43DE,0x041E,0x08FF,0x12A2,0x0B25,0xB364,0xCE3D,0xEFF5,0x4247,0xBFC5,0x04A0,0xB853,0xDEC9,0xDD58,0xC50F,0x22FC,0x0CE5,0xE3C2,0x82B4,0x0C6D,0xE26F,0x9758,0x2BD3,0x0023,0x255C,0xE887,0x1000,0x1BFC,0xF3E8,0xE37B,0x0FB5,0x0C15,0x025A,0xDD87,0x707F,0x218D,0x096A,0x08FC,0xE1EA,0x2091,0xFB87,0xEFF3,0x4093,0x0617,0x2393,0x16C4,0xDE3E,0x8D2E,0xDCB5,0xCC96,0xC42D,0x3DEF,0x0B8C,0xE327,0x06EE,0x238C,0xDC51,0xA727,0x1D02,0x3E19,0xE27E,0xEF1A,0xF8E0,0xC5E9,0x13DA,0xFF9F,0x6195,0xBE44,0xBA75,0x6048,0xE22B,0x4F49,0x53FD,0x014D,0xD01B,0x7ED9,0x26E2,0x05C1,0xCAF3,0xD27E,0xAFAF,0xE73E,0xBB23,0xEC7B,0xCF4B,0x1D6B,0x2220,0xBE7E,0xC89E,0x6106,0xD4A7,0x2CF9,0xFB26,0x2AA8,0xDDB3,0xB7DB,0x1ACB,0x3692,0xECAA,0x01F6,0x07F7,0x24AC,0x1BE0,0xFCB8,0x0E33,0x39FA,0xE426,0xF256,0xEDEA,0xEC90,0xD26B,0x2765,0xFB55,0x1C95,0xDD5A,0xE8E7,0xEDB1,0xD60A,0xC6C1,0x2EF3,0x3D57,0x0776,0x624D,0x2930,0xECEA,0x0A5C,0x0479,0xA2EB,0xEFFF,0xD00E,0x3AFE,0x0BF5,0xEFC3,0x288D,0x4B47,0x1EAE,0x3E2F,0xEF95,0xFA35,0x3848,0xF48D,0xD18E,0xFE93,0x3B25,0x1019,0xFB2E,0x0496,0x05F7,0x3DC2,0xF260,0xED0E,0xFC38,0xF9F3,0x1293,0xE35A,0xFAA9,0xB918,0xD380,0x39FC,0xD11A,0x68E0,0xF7BF,0xECC2,0xDC51,0x17E4,0xF545,0xF781,0x449F,0xC4BC,0xAC28,0x36A1,0xE505,0xEC6A,0x061F,0xC873,0xFBD2,0xEE9A,0x6CA5,0x1326,0x2901,0x183F,0x3AAD,0x0749,0x3002,0x1500,0xC278,0x131F,0xDFF5,0xF108,0xF442,0x4D60,0x3DEA,0xE4FE,0xA860,0x0979,0xFFDE,0x2D0F,0x06FE,0xF81B,0x095B,0xE529,0xE4E4,0x2674,0xA8E1,0x1664,0xEB8A,0x821D,0x2D90,0xCDA6,0x11D2,0xEC3C,0x1928,0xFB91,0xFCCD,0x0B85,0x218E,0x58E7,0xF109,0xC871,0xCE5E,0x8000,0x6A20,0x24E9,0xD6BF,0xDF5D,0x2759,0xF123,0x0F96,0xE0E5,0x0432,0xE998,0x3A62,0x09B3,0xF4EF,0x1F79,0xD105,0xDE63,0xBFAD,0x29D2,0xF178,0x497B,0xD716,0x34D0,0xE9AF,0xF2DD,0x0104,0x27C0,0xC84C,0x46C7,0xFA97,0xD01F,0x07D4,0xF898,0x031B,0x25D0,0x1C42,0xF7E1,0x2BD0,0xE6B8,0xFFF7,0xFA7E,0x2DA7,0xCE4F,0x2E41,0x0003,0x0B2F,0x044B,0xF8B9,0xCFAB,0x1CA6,0xFEFF,0xA1EE,0x2482,0xDE84,0xED25,0xA94E,0x2E6A,0x21D1,0x20BF,0x0F41,0x49E1,0x194D,0x0F6E,0x1D5B,0x1466,0xCDD5,0x2F9A,0xBA22,0xE973,0x218C,0x804B,0xD7A7,0x075B,0xDAE9,0x9FAA,0xF3DB,0xB416,0xB557,0xCD48,0x1791,0xCF10,0xF5C3,0x2CCA,0xD3EA,0xCC0C,0xDF5A,0x1C58,0x145D,0x1026,0xCC8C,0x63B2,0xB594,0xA565,0xEA1C,0x0BD0,0x21C9,0x9EA2,0x09C2,0x298C,0x40AD,0xF305,0xAC3D,0x00E9,0x4E41,0xF026,0x088B,0x065E,0x26AC,0x1C08,0x1F24,0x493A,0x7512,0x071B,0x3FBF,0xCB9C,0xACC6,0x1AC6,0x1FB1,0x14A0,0xDF92,0xA665,0xD3CB,0xC6F8,0x2434,0xF33E,0xEEB3,0xD197,0xDC0C,0xAD8F,0xFC68,0x1C4A,0xEAF5,0x2AE4,0x3FCA,0x0CE0,0x34D1,0x5560,0xE95C,0x0DF6,0x2909,0xCB22,0xEE55,0xE6E1,0xF237,0x02C5,0x0EA1,0x3BDE,0xD254,0xEF10,0xF25D,0x278B,0x164E,0xDFC1,0xBC44,0xFC8E,0x2729,0x1334,0x1766,0xE6FF,0xD595,0xACEE,0x1A22,0xD784,0x1FA7,0x3BD1,0xA527,0xB376,0xF04B,0xD3DC,0x11F1,0x123A,0x4B98,0x06FD,0x1757,0x4204,0xAB70,0xE3D2,0x0EF2,0x33EC,0x066F,0xE070,0xE4BC,0x3582,0xE8B4,0x017F,0x1AAC,0xE5BD,0xF390,0x0074,0xE16B,0x06B2,0xDCE7,0x38FD,0xD293,0xFE9F,0xE0C2,0x1CAF,0xFC98,0xF88F,0x0433,0x0AE5,0x07AD,0xCB92,0x3813,0x1D3D,0x04D8,0x1887,0xF732,0x0B40,0xF55C,0xFFC3,0x9E43,0x0646,0x14BC,0xB221,0x3823,0xC99C,0xFE4A,0xEE3C,0x0571,0x1518,0x1585,0xD04B,0xCCBC,0x15F3,0x19DD,0xFEBA,0x0740,0x51B7,0xFC43,0xF54F,0x101A};

