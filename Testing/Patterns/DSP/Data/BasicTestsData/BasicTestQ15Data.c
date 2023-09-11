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

const q15 Input1_q15[256] = {0x0EB1,0xD7DA,0xDFC2,0x2DDA,0xAEB8,0x1A8C,0x34D0,0xC949,0x19FF,0x1AFC,0xD67E,0x2639,0x1546,0xF32D,0x2A82,0xB79E,0x1317,0xEAF2,0xCBD9,0xC454,0x42FD,0xBB89,0x9B4F,0xCE5C,0x09A1,0xDFC2,0xD780,0x2B2C,0x0FDB,0xC69C,0x5D9B,0xBC82,0x2794,0xC287,0x152B,0xDA69,0x2BE1,0xE9BB,0xD5EE,0xC7C4,0xBCDA,0xC828,0x19B1,0x5F41,0x5146,0x00F0,0xDEF6,0x2A44,0xCD0A,0xE918,0xF4D0,0xD863,0x241F,0xE030,0x26F3,0x1ACB,0x245C,0x047C,0x9433,0x2BF5,0x2F0F,0x40E5,0xC00D,0x849C,0x215D,0xDE1B,0x264A,0x311D,0x0C88,0x1028,0x2D8F,0xCE0E,0x1B43,0x5529,0x2914,0xE215,0x0C95,0xF727,0xDF21,0xD12E,0xBF74,0xBFB5,0xC4B0,0xCDBB,0xE3D0,0xFAF9,0x2579,0xE9F5,0xE00D,0xE3B7,0x2FE5,0xE7A2,0xE72C,0x4C12,0x156E,0x03A9,0xE767,0x14B9,0x8F36,0x54D3,0xF8CF,0xC5F2,0xE3E2,0x3EEB,0x054A,0x6482,0x013C,0xFF6D,0x078F,0xA20A,0xEF63,0xCBAB,0xC222,0xA967,0x3F6B,0xFAFE,0x1498,0xF9D3,0xC2C3,0xCD2C,0x1B37,0xA9E8,0xF8A4,0xD3A6,0xD238,0x55EC,0xF7FA,0x007C,0xC1BF,0x161F,0x8000,0x273D,0xEEC7,0xFDDA,0xD41C,0x51C4,0x1697,0x3C98,0x2E62,0xC85D,0x01FF,0xC356,0xBCC5,0xF6C0,0xC2FB,0x1CC0,0xC736,0xED5C,0x1B3C,0xCEDC,0xDC71,0xD699,0x895A,0xF44E,0xFEAB,0xB470,0xE176,0xC915,0x23AD,0xDBDE,0x2579,0xB028,0xF293,0xF1D3,0x2BE9,0x3FE0,0x5143,0x8BB5,0xD9A9,0xC304,0x5BE4,0xBD39,0xF24A,0xC721,0xE044,0xE5EB,0x3015,0x22EB,0x0FC5,0xF766,0xCAEC,0x356E,0xF105,0xE3F6,0xC69B,0xC858,0x1EF3,0xD29A,0xF220,0x156B,0x0625,0xD1BA,0x0DF9,0x6A80,0xECF5,0xBBC4,0xE8B3,0x1DBD,0x27ED,0x43D5,0x38E0,0x0942,0x0DB3,0x93F4,0xF640,0xBC17,0xFB75,0xB565,0x39FD,0x037E,0x533F,0x3981,0x2FC2,0xA54D,0x2DAC,0x403B,0xD1AC,0x2397,0x06C3,0xDD46,0x9F4C,0xF716,0xD4F2,0xFEEA,0xCE26,0xF1C9,0x376E,0x2D6C,0x1DA1,0x1ADF,0x2DB9,0x1E02,0xFA30,0x0633,0x4356,0x06F1,0x0751,0x2881,0x1D47,0x2D8C,0xA430,0xB60E,0x9CBD,0xF925,0xF90C,0x235A,0xDAAC,0x3B2B,0x112A,0x8F09,0x00B9,0xB234,0xA386,0xD619,0x20AA,0x5063};
const q15 Input2_q15[256] = {0xF977,0xF484,0xB38D,0xC049,0x127F,0xEE0D,0x5183,0x1CFF,0x2EC8,0x7FFF,0x44B4,0xD9AD,0x4410,0x27AA,0x0313,0xC597,0xA23C,0xFCF7,0xF6CA,0x0540,0x3DD7,0x4BA0,0xCB04,0x4650,0x5117,0x0F7A,0x16B7,0x0052,0x04F6,0xCBB2,0xD270,0xFCD5,0xDFF0,0x389E,0x2413,0xD405,0x08F1,0xF872,0xABD2,0x13D4,0x86AB,0xDECA,0xEFE1,0x04D6,0x2F20,0xE4F2,0x74C9,0xFAFF,0x1E5B,0x4BBC,0xE50F,0x26A3,0xF12F,0x9774,0x0465,0x0FE1,0xB3DD,0xFF6A,0x2B48,0xD882,0xD6B7,0x077A,0xE7AC,0x94B7,0x03BB,0x2E0B,0xEE40,0xED35,0xEC88,0x3365,0x60B5,0x249E,0x03B7,0xCCB7,0xB6E0,0xB83B,0xEB34,0xEC7F,0xEC20,0x037F,0x29F7,0x9EE0,0x0079,0xF08C,0xE025,0xE064,0xF44A,0x28BF,0xDB1A,0x11F0,0xFF16,0x5896,0x01D3,0x2546,0x0D96,0xE7A4,0xFBAF,0xC158,0x1BD0,0x1349,0x0F56,0x3C3A,0x0971,0x0144,0x0103,0xD605,0x5F13,0xD660,0x56D8,0x281A,0xCB9C,0xF087,0x0DF1,0xE910,0x00A3,0xDB1F,0xEF24,0xCB3C,0xFDC3,0x33BF,0xC071,0x2387,0x1D00,0xFCAB,0xDEAF,0xD8BE,0x50D2,0xA530,0x3BED,0x33D0,0xC7B0,0x8906,0x1389,0x5832,0x12A8,0xCD6B,0x3FB1,0x2AF3,0x1438,0x230A,0x1D37,0xDBE5,0xC794,0xCF49,0xBD1F,0x0352,0xDDEF,0xF71B,0xF034,0x69E3,0xE115,0xD0FB,0x14C9,0xF522,0xDF36,0xE814,0xE306,0x2CE3,0xDB81,0x6658,0x02D7,0x1E97,0xBA82,0xEE1A,0x5C73,0x2956,0xBC37,0xF3FA,0xD52D,0xFE74,0xA370,0xE439,0x007A,0x0138,0xF675,0xDAB6,0xFB95,0xE5D5,0xF490,0xF4FD,0x0BD8,0x58FF,0xE5FA,0x1DC2,0x0DB3,0xD10F,0x006F,0xC3FA,0xE69E,0xFF03,0x01C4,0x2F8A,0xE336,0x05F5,0xD870,0xDF1E,0x532B,0x2F9B,0xED67,0xB192,0xF663,0xC955,0xD832,0xCB4F,0x060B,0x136A,0x3EC8,0xCBF4,0xF509,0x480F,0x22B4,0xE9D0,0x3610,0x35F0,0xD66A,0xC10A,0x3476,0x0C80,0x002B,0xEF29,0x02A2,0x8E39,0xED70,0x0D5D,0x8AF0,0x1793,0x1CD9,0xE7A7,0x45C4,0x422D,0xCF10,0x3A84,0xF767,0xC650,0xF766,0xCAA0,0x2688,0x1341,0x3C45,0x492B,0x01EE,0x156F,0x0862,0x28AF,0x42C1,0xE27E,0x0164,0x8BC3,0x678D,0xEECA,0xCAF7,0xE0AD,0x15EB,0x9059,0xCAB6,0xFE6E};
const q15 Input12_q15[17] = {0x271B,0xDA32,0x1348,0xF2FB,0x2AAB,0x011B,0x04BE,0xEDA1,0xF82B,0xF5EC,0x201A,0xE56E,0xE8B7,0x09B3,0x1889,0x15E1,0x00F3};
const q15 Input28_q15[279] = {0x8CCD,0x8DA1,0x8E75,0x8F49,0x901D,0x90F2,0x91C6,0x929A,0x936E,0x9442,0x9516,0x95EB,0x96BF,0x9793,0x9867,0x993B,0x9A0F,0x9AE4,0x9BB8,0x9C8C,0x9D60,0x9E34,0x9F08,0x9FDD,0xA0B1,0xA185,0xA259,0xA32D,0xA401,0xA4D6,0xA5AA,0xA67E,0xA752,0xA826,0xA8FA,0xA9CF,0xAAA3,0xAB77,0xAC4B,0xAD1F,0xADF3,0xAEC8,0xAF9C,0xB070,0xB144,0xB218,0xB2EC,0xB3C1,0xB495,0xB569,0xB63D,0xB711,0xB7E5,0xB8BA,0xB98E,0xBA62,0xBB36,0xBC0A,0xBCDE,0xBDB3,0xBE87,0xBF5B,0xC02F,0xC103,0xC1D7,0xC2AC,0xC380,0xC454,0xC528,0xC5FC,0xC6D0,0xC7A5,0xC879,0xC94D,0xCA21,0xCAF5,0xCBC9,0xCC9E,0xCD72,0xCE46,0xCF1A,0xCFEE,0xD0C2,0xD197,0xD26B,0xD33F,0xD413,0xD4E7,0xD5BB,0xD690,0xD764,0xD838,0xD90C,0xD9E0,0xDAB4,0xDB89,0xDC5D,0xDD31,0xDE05,0xDED9,0xDFAD,0xE082,0xE156,0xE22A,0xE2FE,0xE3D2,0xE4A6,0xE57B,0xE64F,0xE723,0xE7F7,0xE8CB,0xE99F,0xEA74,0xEB48,0xEC1C,0xECF0,0xEDC4,0xEE98,0xEF6D,0xF041,0xF115,0xF1E9,0xF2BD,0xF391,0xF466,0xF53A,0xF60E,0xF6E2,0xF7B6,0xF88A,0xF95F,0xFA33,0xFB07,0xFBDB,0xFCAF,0xFD83,0xFE58,0xFF2C,0x0000,0x00D4,0x01A8,0x027D,0x0351,0x0425,0x04F9,0x05CD,0x06A1,0x0776,0x084A,0x091E,0x09F2,0x0AC6,0x0B9A,0x0C6F,0x0D43,0x0E17,0x0EEB,0x0FBF,0x1093,0x1168,0x123C,0x1310,0x13E4,0x14B8,0x158C,0x1661,0x1735,0x1809,0x18DD,0x19B1,0x1A85,0x1B5A,0x1C2E,0x1D02,0x1DD6,0x1EAA,0x1F7E,0x2053,0x2127,0x21FB,0x22CF,0x23A3,0x2477,0x254C,0x2620,0x26F4,0x27C8,0x289C,0x2970,0x2A45,0x2B19,0x2BED,0x2CC1,0x2D95,0x2E69,0x2F3E,0x3012,0x30E6,0x31BA,0x328E,0x3362,0x3437,0x350B,0x35DF,0x36B3,0x3787,0x385B,0x3930,0x3A04,0x3AD8,0x3BAC,0x3C80,0x3D54,0x3E29,0x3EFD,0x3FD1,0x40A5,0x4179,0x424D,0x4322,0x43F6,0x44CA,0x459E,0x4672,0x4746,0x481B,0x48EF,0x49C3,0x4A97,0x4B6B,0x4C3F,0x4D14,0x4DE8,0x4EBC,0x4F90,0x5064,0x5138,0x520D,0x52E1,0x53B5,0x5489,0x555D,0x5631,0x5706,0x57DA,0x58AE,0x5982,0x5A56,0x5B2A,0x5BFF,0x5CD3,0x5DA7,0x5E7B,0x5F4F,0x6023,0x60F8,0x61CC,0x62A0,0x6374,0x6448,0x651C,0x65F1,0x66C5,0x6799,0x686D,0x6941,0x6A15,0x6AEA,0x6BBE,0x6C92,0x6D66,0x6E3A,0x6F0E,0x6FE3,0x70B7,0x718B,0x725F,0x7333};


const q15 MaxPosInput12_s16[17] = {0x7FFE,0x0001,0x7FFE,0x0001,0x7FFE,0x0001,0x7FFE,0x0001,0x7FFE,0x0001,0x7FFE,0x0001,0x7FFE,0x0001,0x7FFE,0x0001,0x7FFE};
const q15 MaxNegInput12_s16[17] = {0x8001,0xFFFF,0x8001,0xFFFF,0x8001,0xFFFF,0x8001,0xFFFF,0x8001,0xFFFF,0x8001,0xFFFF,0x8001,0xFFFF,0x8001,0xFFFF,0x8001};
const q15 MaxNeg2Input12_s16[17] = {0x8000,0xFFFE,0x8000,0xFFFE,0x8000,0xFFFE,0x8000,0xFFFE,0x8000,0xFFFE,0x8000,0xFFFE,0x8000,0xFFFE,0x8000,0xFFFE,0x8000};
const q15 BitwiseInput24_s16[23] = {0xF97D,0x7E98,0xE83E,0x9006,0x8ECF,0x82B2,0x873C,0xE6D0,0x42C6,0xA110,0x7D1E,0x0CDC,0xB6CC,0xB5A5,0xB245,0xC19A,0x7B95,0xB857,0x3E23,0xECC1,0x8AC4,0xA9A0,0x7CFF};
const q15 BitwiseInput25_s16[23] = {0xABDB,0x927F,0x5D5D,0xF0CC,0x90C8,0xE1A9,0xCACF,0x2B30,0xEDC4,0x5AB6,0x7E72,0x7867,0x0B8A,0x0E28,0x6421,0x5673,0x8AE7,0xF8DC,0x45A3,0xF95D,0x4B42,0xB9A3,0x7FE6};

const q15 NegSat13_q15[17] = {0x8000,0xFFFE,0x8000,0xFFFE,0x8000,0xFFFE,0x8000,0xFFFE,0x8000,0xFFFE,0x8000,0xFFFE,0x8000,0xFFFE,0x8000,0xFFFE,0x8000};
const q15 NegSat15_q15[17] = {0x8000,0xFFFE,0x8000,0xFFFE,0x8000,0xFFFE,0x8000,0xFFFE,0x8000,0xFFFE,0x8000,0xFFFE,0x8000,0xFFFE,0x8000,0xFFFE,0x8000};
const q15 NegSat19_q15[17] = {0x8000,0x8CCC,0x8000,0x8CCC,0x8000,0x8CCC,0x8000,0x8CCC,0x8000,0x8CCC,0x8000,0x8CCC,0x8000,0x8CCC,0x8000,0x8CCC,0x8000};


const q15 PosSat12_q15[17] = {0x7FFF,0x0002,0x7FFF,0x0002,0x7FFF,0x0002,0x7FFF,0x0002,0x7FFF,0x0002,0x7FFF,0x0002,0x7FFF,0x0002,0x7FFF,0x0002,0x7FFF};
const q15 PosSat14_q15[17] = {0x7FFF,0x0002,0x7FFF,0x0002,0x7FFF,0x0002,0x7FFF,0x0002,0x7FFF,0x0002,0x7FFF,0x0002,0x7FFF,0x0002,0x7FFF,0x0002,0x7FFF};
const q15 PosSat16_q15[17] = {0x7FFF,0x0000,0x7FFF,0x0000,0x7FFF,0x0000,0x7FFF,0x0000,0x7FFF,0x0000,0x7FFF,0x0000,0x7FFF,0x0000,0x7FFF,0x0000,0x7FFF};
const q15 PosSat17_q15[17] = {0x7FFF,0x0002,0x7FFF,0x0002,0x7FFF,0x0002,0x7FFF,0x0002,0x7FFF,0x0002,0x7FFF,0x0002,0x7FFF,0x0002,0x7FFF,0x0002,0x7FFF};
const q15 PosSat18_q15[17] = {0x7FFF,0x7334,0x7FFF,0x7334,0x7FFF,0x7334,0x7FFF,0x7334,0x7FFF,0x7334,0x7FFF,0x7334,0x7FFF,0x7334,0x7FFF,0x7334,0x7FFF};
const q15 PosSat20_q15[17] = {0x7FFF,0x0002,0x7FFF,0x0002,0x7FFF,0x0002,0x7FFF,0x0002,0x7FFF,0x0002,0x7FFF,0x0002,0x7FFF,0x0002,0x7FFF,0x0002,0x7FFF};


const q15 Shift21_q15[17] = {0x4E37,0xB463,0x268F,0xE5F5,0x5555,0x0235,0x097C,0xDB43,0xF056,0xEBD9,0x4034,0xCADC,0xD16D,0x1367,0x3113,0x2BC3,0x01E6};
const q15 Shift22_q15[17] = {0x7FFF,0x0002,0x7FFF,0x0002,0x7FFF,0x0002,0x7FFF,0x0002,0x7FFF,0x0002,0x7FFF,0x0002,0x7FFF,0x0002,0x7FFF,0x0002,0x7FFF};
const q15 Shift23_q15[17] = {0x8000,0xFFFE,0x8000,0xFFFE,0x8000,0xFFFE,0x8000,0xFFFE,0x8000,0xFFFE,0x8000,0xFFFE,0x8000,0xFFFE,0x8000,0xFFFE,0x8000};
const q15 And24_s16[23] = {0xA959,0x1218,0x481C,0x9004,0x80C8,0x80A0,0x820C,0x2210,0x40C4,0x0010,0x7C12,0x0844,0x0288,0x0420,0x2001,0x4012,0x0A85,0xB854,0x0423,0xE841,0x0A40,0xA9A0,0x7CE6};
const q15 Or25_s16[23] = {0xFBFF,0xFEFF,0xFD7F,0xF0CE,0x9ECF,0xE3BB,0xCFFF,0xEFF0,0xEFC6,0xFBB6,0x7F7E,0x7CFF,0xBFCE,0xBFAD,0xF665,0xD7FB,0xFBF7,0xF8DF,0x7FA3,0xFDDD,0xCBC6,0xB9A3,0x7FFF};
const q15 Not26_s16[23] = {0x0682,0x8167,0x17C1,0x6FF9,0x7130,0x7D4D,0x78C3,0x192F,0xBD39,0x5EEF,0x82E1,0xF323,0x4933,0x4A5A,0x4DBA,0x3E65,0x846A,0x47A8,0xC1DC,0x133E,0x753B,0x565F,0x8300};
const q15 Xor27_s16[23] = {0x52A6,0xECE7,0xB563,0x60CA,0x1E07,0x631B,0x4DF3,0xCDE0,0xAF02,0xFBA6,0x036C,0x74BB,0xBD46,0xBB8D,0xD664,0x97E9,0xF172,0x408B,0x7B80,0x159C,0xC186,0x1003,0x0319};



const q15 Reference1_q15[256] = {0x0827,0xCC5E,0x934F,0xEE23,0xC137,0x0899,0x7FFF,0xE647,0x48C7,0x7FFF,0x1B32,0xFFE7,0x5956,0x1AD7,0x2D96,0x8000,0xB553,0xE7E9,0xC2A3,0xC994,0x7FFF,0x072A,0x8000,0x14AC,0x5AB8,0xEF3B,0xEE37,0x2B7E,0x14D1,0x924E,0x300B,0xB957,0x0784,0xFB26,0x393E,0xAE6E,0x34D3,0xE22D,0x81C0,0xDB98,0x8000,0xA6F2,0x0992,0x6417,0x7FFF,0xE5E2,0x53BF,0x2543,0xEB65,0x34D3,0xD9DF,0xFF06,0x154E,0x8000,0x2B58,0x2AAC,0xD839,0x03E6,0xBF7B,0x0477,0x05C7,0x485F,0xA7B9,0x8000,0x2518,0x0C26,0x148A,0x1E53,0xF910,0x438D,0x7FFF,0xF2AD,0x1EFA,0x21E0,0xDFF5,0x9A50,0xF7C9,0xE3A5,0xCB41,0xD4AD,0xE96C,0x8000,0xC529,0xBE46,0xC3F5,0xDB5D,0x19C2,0x12B5,0xBB27,0xF5A7,0x2EFA,0x4038,0xE8FF,0x7159,0x2304,0xEB4D,0xE317,0xD611,0xAB06,0x681C,0x0825,0x022B,0xED53,0x402F,0x064D,0x3A86,0x6050,0xD5CD,0x5E68,0xCA23,0xBAFF,0xBC32,0xD013,0x9277,0x400E,0xD61D,0x03BC,0xC50F,0xC086,0x00EB,0xDBA8,0xCD6F,0x15A4,0xD051,0xB0E7,0x2EAA,0x48CC,0xA5AC,0xFDAC,0x49EF,0x8000,0xB044,0x0250,0x560C,0xE6C4,0x1F2F,0x5648,0x678B,0x429A,0xEB67,0x1F37,0x9F3B,0x8458,0xC609,0x801A,0x2012,0xA525,0xE477,0x0B71,0x38BF,0xBD86,0xA794,0x9E23,0xE970,0xDDE1,0x9C84,0xC47B,0xF5F8,0xFF2E,0x4237,0x2851,0xCEBF,0xAD15,0xDFED,0x7FFF,0x6936,0x0D7A,0x8000,0xAED7,0xC178,0xFF54,0xA172,0xF2C4,0xC859,0xD6B9,0xC0A1,0x2BAA,0x08C0,0x0455,0xEC63,0xD6C4,0x7FFF,0xD6FF,0x01B8,0xD44E,0x9968,0x1F62,0x9693,0xD8BE,0x146E,0x07E9,0x0143,0xF12F,0x7075,0xC565,0x9AE2,0x3BDE,0x4D58,0x1554,0xF567,0x2F43,0xD297,0xE5E5,0x8000,0xFC4B,0xCF81,0x3A3C,0x8158,0x2F06,0x4B8E,0x75F2,0x2351,0x65D3,0xDB3E,0x0417,0x0145,0x0623,0x3017,0x06EE,0xCC6F,0xA1ED,0x854F,0xC262,0x0C47,0x8000,0x095C,0x5447,0x1513,0x6365,0x5D0C,0xFCC9,0x5886,0xF197,0xCC83,0x3ABC,0xD191,0x2DD9,0x3BC2,0x598C,0x76B7,0xA61E,0xCB7E,0xA51F,0x21D4,0x3BCD,0x05D8,0xDC10,0xC6EE,0x78B7,0x8000,0xCBB0,0x92E1,0xB971,0x8000,0xEB5F,0x4ED1};
const q15 Reference2_q15[256] = {0x153A,0xE356,0x2C35,0x6D91,0x9C39,0x2C7F,0xE34D,0xAC4A,0xEB37,0x9AFC,0x91CA,0x4C8C,0xD136,0xCB83,0x276F,0xF207,0x70DB,0xEDFB,0xD50F,0xBF14,0x0526,0x8000,0xD04B,0x880D,0xB88A,0xD048,0xC0C9,0x2ADA,0x0AE5,0xFAEA,0x7FFF,0xBFAC,0x47A4,0x89E9,0xF118,0x0664,0x22F0,0xF148,0x2A1B,0xB3F0,0x3630,0xE95E,0x29D1,0x5A6A,0x2226,0x1BFE,0x8000,0x2F45,0xAEAF,0x9D5C,0x0FC1,0xB1C0,0x32F0,0x48BC,0x228D,0x0AEA,0x707F,0x0512,0x8000,0x5372,0x5858,0x396B,0xD861,0xEFE5,0x1DA3,0xB00F,0x380B,0x43E8,0x2000,0xDCC4,0xCCDB,0xA970,0x178C,0x7FFF,0x7234,0x29DA,0x2162,0x0AA8,0xF301,0xCDAE,0x957D,0x20D5,0xC437,0xDD2F,0x03AC,0x1A96,0x312F,0xC136,0x04F3,0xD1C8,0x30CF,0x8F0C,0xE559,0x26CC,0x07D8,0x1C05,0xEBB8,0x5361,0x8000,0x418A,0xE978,0x89B8,0xDA71,0x3DA7,0x0447,0x7FFF,0xA229,0x290C,0xB0B7,0x8000,0x23C7,0xDB24,0xB432,0xC057,0x3EC8,0x1FDF,0x2574,0x2E97,0xC500,0x996C,0x5AC6,0x8662,0xDBA5,0xD6FC,0xF389,0x7D2F,0xA729,0x5B4D,0x85D2,0xE250,0xB850,0x7FFF,0xDB3D,0xA5A7,0xC174,0x7FFF,0xD6E5,0x11A6,0x1A2A,0xA553,0xE4C8,0xE772,0xF531,0x2777,0x05DC,0x196E,0xE947,0xF641,0x2B08,0x8000,0xFB5B,0x059E,0x8000,0xFF2C,0x1F75,0xCC5C,0xFE70,0x9C33,0x482C,0x8000,0x22A2,0x9190,0x3810,0x03B9,0xCF75,0x168A,0x7FFF,0x97BB,0x047C,0xC490,0x7FFF,0xD900,0xF1D0,0xC5E9,0xE9CF,0x0B35,0x3480,0x3D16,0x1B35,0x0269,0xBF14,0xDC6F,0x0B0C,0xC635,0xB8E8,0xF749,0x1E85,0x0EA0,0x0B82,0x1668,0x0461,0xA230,0x2AC4,0x648A,0x1485,0xDCA6,0x9587,0xEE22,0x3A86,0x7FFF,0x427D,0x3FEC,0x3582,0xC8A5,0xF035,0xA8AE,0xBCAD,0xE971,0x44F5,0xBB6F,0x308B,0x4FB1,0xF9B2,0x8000,0x5742,0x7F30,0x9D36,0x1718,0x0698,0xEE1E,0x9CAA,0x68DD,0xE782,0xF18D,0x4335,0xDA36,0x1A95,0x45C5,0xD7DD,0xD8B2,0x5EA9,0xE37D,0x02C8,0x3FE3,0x4BF0,0x3C51,0xE0C8,0x1540,0xE102,0xE461,0xA242,0xA09F,0x945B,0xD076,0xB64A,0x40DC,0xD948,0x7FFF,0xA99D,0xA03F,0x35C2,0xD188,0x8D9B,0x45C0,0x55F4,0x51F5};
const q15 Reference3_q15[256] = {0xFF40,0x039A,0x1342,0xE92D,0xF441,0xFC47,0x21A2,0xF39B,0x0980,0x1AFC,0xE9B9,0xF48E,0x0B50,0xFC07,0x0105,0x2108,0xF204,0x0080,0x03C1,0xFD8E,0x205D,0xD78D,0x29AE,0xE4BC,0x061A,0xFC1A,0xF8D0,0x001C,0x009D,0x1774,0xDEAE,0x01AC,0xF616,0xE4CF,0x05F7,0x0CEB,0x0311,0x0150,0x1BAB,0xF74A,0x3FA6,0x0E7D,0xFCC4,0x039A,0x1DEC,0xFFCD,0xE1DC,0xFE59,0xF3EA,0xF272,0x025B,0xF40B,0xFBD2,0x19FB,0x0156,0x0353,0xEA60,0xFFFB,0xDB8D,0xF270,0xF0D2,0x03CA,0x0C28,0x676B,0x00F9,0xF3CF,0xFAB1,0xF8CA,0xFE18,0x067D,0x226C,0xF1B6,0x00CB,0xDDE1,0xE888,0x10C6,0xFDF5,0x0159,0x051B,0xFEB8,0xEAD7,0x30C9,0xFFC8,0x0612,0x0704,0x013E,0xFC92,0xF8FC,0x0936,0xFC09,0xFFA8,0xEF23,0xFFA5,0x1627,0x0246,0xFF4E,0x00D4,0xF5DB,0xE77E,0x0CC8,0xFF23,0xE4AF,0xFDED,0x009F,0x000B,0xDF09,0x00EB,0x0030,0x0521,0xE290,0x06CD,0x0653,0xF943,0x0F84,0x0051,0x0171,0xFD4A,0x028C,0x0112,0xEB73,0xF27C,0xE81B,0xFE55,0x0128,0x0BEB,0xE5A5,0xFAEF,0xFFA8,0xE2DB,0x08F4,0x3850,0xDB87,0xFD5F,0xFE85,0xF99A,0xDFB0,0x0B3D,0x1455,0x0754,0xF0C5,0x0075,0x111D,0x1DA3,0x0385,0x1FE2,0x00BF,0x0F1D,0x014C,0xFCA4,0xD759,0x0897,0x0F36,0xECBC,0x00FE,0x0057,0x0E1F,0x06EA,0xECBE,0xF5D4,0xE31C,0x00D5,0xECEB,0x074A,0x01FC,0x1FB7,0x14A1,0xD4F7,0x0AED,0x0CD4,0x00BD,0xBD8D,0x0E7E,0xFFF3,0xFF75,0x025E,0x0799,0xFE57,0xF8DD,0xFE97,0x00BD,0xFB17,0x2526,0x030C,0xF97B,0xF9DB,0x1469,0x001B,0x154A,0x02C0,0xFFD6,0x0016,0xEED0,0xFCDB,0x04F5,0x05E3,0x1187,0xF0DC,0x0B0F,0xFA33,0xD66F,0xFBBB,0xFC0C,0xFBBD,0x2C7A,0xFF8A,0xF5B3,0xFDC5,0x1E56,0xFB08,0x01F7,0x1692,0xF608,0x142C,0xD9C8,0xF129,0xE068,0xED03,0x037A,0x0002,0x0492,0xFE03,0x07EC,0x063E,0xFFE3,0x2D98,0xFD62,0x0C7E,0xF75C,0x1026,0x0DE4,0xEE85,0x0DB8,0x0064,0xFD35,0xFB7A,0xFD1B,0x0234,0x0618,0x0DC9,0x1A09,0xFE9E,0xF39E,0xF980,0xFDD2,0xFC5F,0xF7DA,0xFF98,0xCA45,0x0DE3,0x0F30,0xFFB3,0x130A,0xF02A,0x248D,0xF267,0xFF03};
const q15 Reference4_q15[256] = {0xF14F,0x2826,0x203E,0xD226,0x5148,0xE574,0xCB30,0x36B7,0xE601,0xE504,0x2982,0xD9C7,0xEABA,0x0CD3,0xD57E,0x4862,0xECE9,0x150E,0x3427,0x3BAC,0xBD03,0x4477,0x64B1,0x31A4,0xF65F,0x203E,0x2880,0xD4D4,0xF025,0x3964,0xA265,0x437E,0xD86C,0x3D79,0xEAD5,0x2597,0xD41F,0x1645,0x2A12,0x383C,0x4326,0x37D8,0xE64F,0xA0BF,0xAEBA,0xFF10,0x210A,0xD5BC,0x32F6,0x16E8,0x0B30,0x279D,0xDBE1,0x1FD0,0xD90D,0xE535,0xDBA4,0xFB84,0x6BCD,0xD40B,0xD0F1,0xBF1B,0x3FF3,0x7B64,0xDEA3,0x21E5,0xD9B6,0xCEE3,0xF378,0xEFD8,0xD271,0x31F2,0xE4BD,0xAAD7,0xD6EC,0x1DEB,0xF36B,0x08D9,0x20DF,0x2ED2,0x408C,0x404B,0x3B50,0x3245,0x1C30,0x0507,0xDA87,0x160B,0x1FF3,0x1C49,0xD01B,0x185E,0x18D4,0xB3EE,0xEA92,0xFC57,0x1899,0xEB47,0x70CA,0xAB2D,0x0731,0x3A0E,0x1C1E,0xC115,0xFAB6,0x9B7E,0xFEC4,0x0093,0xF871,0x5DF6,0x109D,0x3455,0x3DDE,0x5699,0xC095,0x0502,0xEB68,0x062D,0x3D3D,0x32D4,0xE4C9,0x5618,0x075C,0x2C5A,0x2DC8,0xAA14,0x0806,0xFF84,0x3E41,0xE9E1,0x7FFF,0xD8C3,0x1139,0x0226,0x2BE4,0xAE3C,0xE969,0xC368,0xD19E,0x37A3,0xFE01,0x3CAA,0x433B,0x0940,0x3D05,0xE340,0x38CA,0x12A4,0xE4C4,0x3124,0x238F,0x2967,0x76A6,0x0BB2,0x0155,0x4B90,0x1E8A,0x36EB,0xDC53,0x2422,0xDA87,0x4FD8,0x0D6D,0x0E2D,0xD417,0xC020,0xAEBD,0x744B,0x2657,0x3CFC,0xA41C,0x42C7,0x0DB6,0x38DF,0x1FBC,0x1A15,0xCFEB,0xDD15,0xF03B,0x089A,0x3514,0xCA92,0x0EFB,0x1C0A,0x3965,0x37A8,0xE10D,0x2D66,0x0DE0,0xEA95,0xF9DB,0x2E46,0xF207,0x9580,0x130B,0x443C,0x174D,0xE243,0xD813,0xBC2B,0xC720,0xF6BE,0xF24D,0x6C0C,0x09C0,0x43E9,0x048B,0x4A9B,0xC603,0xFC82,0xACC1,0xC67F,0xD03E,0x5AB3,0xD254,0xBFC5,0x2E54,0xDC69,0xF93D,0x22BA,0x60B4,0x08EA,0x2B0E,0x0116,0x31DA,0x0E37,0xC892,0xD294,0xE25F,0xE521,0xD247,0xE1FE,0x05D0,0xF9CD,0xBCAA,0xF90F,0xF8AF,0xD77F,0xE2B9,0xD274,0x5BD0,0x49F2,0x6343,0x06DB,0x06F4,0xDCA6,0x2554,0xC4D5,0xEED6,0x70F7,0xFF47,0x4DCC,0x5C7A,0x29E7,0xDF56,0xAF9D};
const q15 Reference5_q15[256] = {0x4EB1,0x17DA,0x1FC2,0x6DDA,0xEEB8,0x5A8C,0x74D0,0x0949,0x59FF,0x5AFC,0x167E,0x6639,0x5546,0x332D,0x6A82,0xF79E,0x5317,0x2AF2,0x0BD9,0x0454,0x7FFF,0xFB89,0xDB4F,0x0E5C,0x49A1,0x1FC2,0x1780,0x6B2C,0x4FDB,0x069C,0x7FFF,0xFC82,0x6794,0x0287,0x552B,0x1A69,0x6BE1,0x29BB,0x15EE,0x07C4,0xFCDA,0x0828,0x59B1,0x7FFF,0x7FFF,0x40F0,0x1EF6,0x6A44,0x0D0A,0x2918,0x34D0,0x1863,0x641F,0x2030,0x66F3,0x5ACB,0x645C,0x447C,0xD433,0x6BF5,0x6F0F,0x7FFF,0x000D,0xC49C,0x615D,0x1E1B,0x664A,0x711D,0x4C88,0x5028,0x6D8F,0x0E0E,0x5B43,0x7FFF,0x6914,0x2215,0x4C95,0x3727,0x1F21,0x112E,0xFF74,0xFFB5,0x04B0,0x0DBB,0x23D0,0x3AF9,0x6579,0x29F5,0x200D,0x23B7,0x6FE5,0x27A2,0x272C,0x7FFF,0x556E,0x43A9,0x2767,0x54B9,0xCF36,0x7FFF,0x38CF,0x05F2,0x23E2,0x7EEB,0x454A,0x7FFF,0x413C,0x3F6D,0x478F,0xE20A,0x2F63,0x0BAB,0x0222,0xE967,0x7F6B,0x3AFE,0x5498,0x39D3,0x02C3,0x0D2C,0x5B37,0xE9E8,0x38A4,0x13A6,0x1238,0x7FFF,0x37FA,0x407C,0x01BF,0x561F,0xC000,0x673D,0x2EC7,0x3DDA,0x141C,0x7FFF,0x5697,0x7C98,0x6E62,0x085D,0x41FF,0x0356,0xFCC5,0x36C0,0x02FB,0x5CC0,0x0736,0x2D5C,0x5B3C,0x0EDC,0x1C71,0x1699,0xC95A,0x344E,0x3EAB,0xF470,0x2176,0x0915,0x63AD,0x1BDE,0x6579,0xF028,0x3293,0x31D3,0x6BE9,0x7FE0,0x7FFF,0xCBB5,0x19A9,0x0304,0x7FFF,0xFD39,0x324A,0x0721,0x2044,0x25EB,0x7015,0x62EB,0x4FC5,0x3766,0x0AEC,0x756E,0x3105,0x23F6,0x069B,0x0858,0x5EF3,0x129A,0x3220,0x556B,0x4625,0x11BA,0x4DF9,0x7FFF,0x2CF5,0xFBC4,0x28B3,0x5DBD,0x67ED,0x7FFF,0x78E0,0x4942,0x4DB3,0xD3F4,0x3640,0xFC17,0x3B75,0xF565,0x79FD,0x437E,0x7FFF,0x7981,0x6FC2,0xE54D,0x6DAC,0x7FFF,0x11AC,0x6397,0x46C3,0x1D46,0xDF4C,0x3716,0x14F2,0x3EEA,0x0E26,0x31C9,0x776E,0x6D6C,0x5DA1,0x5ADF,0x6DB9,0x5E02,0x3A30,0x4633,0x7FFF,0x46F1,0x4751,0x6881,0x5D47,0x6D8C,0xE430,0xF60E,0xDCBD,0x3925,0x390C,0x635A,0x1AAC,0x7B2B,0x512A,0xCF09,0x40B9,0xF234,0xE386,0x1619,0x60AA,0x7FFF};
const q15 Reference6_q15[256] = {0x0758,0xEBED,0xEFE1,0x16ED,0xD75C,0x0D46,0x1A68,0xE4A4,0x0D00,0x0D7E,0xEB3F,0x131D,0x0AA3,0xF996,0x1541,0xDBCF,0x098B,0xF579,0xE5ED,0xE22A,0x217E,0xDDC5,0xCDA7,0xE72E,0x04D0,0xEFE1,0xEBC0,0x1596,0x07ED,0xE34E,0x2ECE,0xDE41,0x13CA,0xE144,0x0A95,0xED34,0x15F1,0xF4DD,0xEAF7,0xE3E2,0xDE6D,0xE414,0x0CD9,0x2FA0,0x28A3,0x0078,0xEF7B,0x1522,0xE685,0xF48C,0xFA68,0xEC32,0x120F,0xF018,0x1379,0x0D65,0x122E,0x023E,0xCA1A,0x15FA,0x1788,0x2073,0xE007,0xC24E,0x10AF,0xEF0D,0x1325,0x188F,0x0644,0x0814,0x16C8,0xE707,0x0DA1,0x2A94,0x148A,0xF10A,0x064B,0xFB93,0xEF90,0xE897,0xDFBA,0xDFDA,0xE258,0xE6DD,0xF1E8,0xFD7D,0x12BC,0xF4FB,0xF007,0xF1DC,0x17F2,0xF3D1,0xF396,0x2609,0x0AB7,0x01D4,0xF3B4,0x0A5C,0xC79B,0x2A6A,0xFC67,0xE2F9,0xF1F1,0x1F75,0x02A5,0x3241,0x009E,0xFFB6,0x03C8,0xD105,0xF7B1,0xE5D5,0xE111,0xD4B3,0x1FB5,0xFD7F,0x0A4C,0xFCEA,0xE161,0xE696,0x0D9C,0xD4F4,0xFC52,0xE9D3,0xE91C,0x2AF6,0xFBFD,0x003E,0xE0DF,0x0B10,0xC000,0x139F,0xF763,0xFEED,0xEA0E,0x28E2,0x0B4B,0x1E4C,0x1731,0xE42E,0x0100,0xE1AB,0xDE62,0xFB60,0xE17E,0x0E60,0xE39B,0xF6AE,0x0D9E,0xE76E,0xEE38,0xEB4C,0xC4AD,0xFA27,0xFF56,0xDA38,0xF0BB,0xE48B,0x11D7,0xEDEF,0x12BD,0xD814,0xF949,0xF8E9,0x15F4,0x1FF0,0x28A2,0xC5DA,0xECD5,0xE182,0x2DF2,0xDE9D,0xF925,0xE390,0xF022,0xF2F6,0x180B,0x1175,0x07E2,0xFBB3,0xE576,0x1AB7,0xF883,0xF1FB,0xE34E,0xE42C,0x0F7A,0xE94D,0xF910,0x0AB6,0x0313,0xE8DD,0x06FD,0x3540,0xF67B,0xDDE2,0xF459,0x0EDE,0x13F7,0x21EB,0x1C70,0x04A1,0x06DA,0xC9FA,0xFB20,0xDE0C,0xFDBA,0xDAB2,0x1CFF,0x01BF,0x299F,0x1CC0,0x17E1,0xD2A7,0x16D6,0x201D,0xE8D6,0x11CC,0x0361,0xEEA3,0xCFA6,0xFB8B,0xEA79,0xFF75,0xE713,0xF8E4,0x1BB7,0x16B6,0x0ED1,0x0D6F,0x16DC,0x0F01,0xFD18,0x0319,0x21AB,0x0378,0x03A8,0x1441,0x0EA4,0x16C6,0xD218,0xDB07,0xCE5E,0xFC93,0xFC86,0x11AD,0xED56,0x1D96,0x0895,0xC784,0x005C,0xD91A,0xD1C3,0xEB0D,0x1055,0x2832};
const q63 Reference7_q63[1] = {0x0000000008B96063};
const q63 Reference8_q63[1] = {0x00000000189A5933};
const q63 Reference9_q63[1] = {0x00000000234F66AE};
const q15 Reference10_q15[256] = {0x0EB1,0x2826,0x203E,0x2DDA,0x5148,0x1A8C,0x34D0,0x36B7,0x19FF,0x1AFC,0x2982,0x2639,0x1546,0x0CD3,0x2A82,0x4862,0x1317,0x150E,0x3427,0x3BAC,0x42FD,0x4477,0x64B1,0x31A4,0x09A1,0x203E,0x2880,0x2B2C,0x0FDB,0x3964,0x5D9B,0x437E,0x2794,0x3D79,0x152B,0x2597,0x2BE1,0x1645,0x2A12,0x383C,0x4326,0x37D8,0x19B1,0x5F41,0x5146,0x00F0,0x210A,0x2A44,0x32F6,0x16E8,0x0B30,0x279D,0x241F,0x1FD0,0x26F3,0x1ACB,0x245C,0x047C,0x6BCD,0x2BF5,0x2F0F,0x40E5,0x3FF3,0x7B64,0x215D,0x21E5,0x264A,0x311D,0x0C88,0x1028,0x2D8F,0x31F2,0x1B43,0x5529,0x2914,0x1DEB,0x0C95,0x08D9,0x20DF,0x2ED2,0x408C,0x404B,0x3B50,0x3245,0x1C30,0x0507,0x2579,0x160B,0x1FF3,0x1C49,0x2FE5,0x185E,0x18D4,0x4C12,0x156E,0x03A9,0x1899,0x14B9,0x70CA,0x54D3,0x0731,0x3A0E,0x1C1E,0x3EEB,0x054A,0x6482,0x013C,0x0093,0x078F,0x5DF6,0x109D,0x3455,0x3DDE,0x5699,0x3F6B,0x0502,0x1498,0x062D,0x3D3D,0x32D4,0x1B37,0x5618,0x075C,0x2C5A,0x2DC8,0x55EC,0x0806,0x007C,0x3E41,0x161F,0x7FFF,0x273D,0x1139,0x0226,0x2BE4,0x51C4,0x1697,0x3C98,0x2E62,0x37A3,0x01FF,0x3CAA,0x433B,0x0940,0x3D05,0x1CC0,0x38CA,0x12A4,0x1B3C,0x3124,0x238F,0x2967,0x76A6,0x0BB2,0x0155,0x4B90,0x1E8A,0x36EB,0x23AD,0x2422,0x2579,0x4FD8,0x0D6D,0x0E2D,0x2BE9,0x3FE0,0x5143,0x744B,0x2657,0x3CFC,0x5BE4,0x42C7,0x0DB6,0x38DF,0x1FBC,0x1A15,0x3015,0x22EB,0x0FC5,0x089A,0x3514,0x356E,0x0EFB,0x1C0A,0x3965,0x37A8,0x1EF3,0x2D66,0x0DE0,0x156B,0x0625,0x2E46,0x0DF9,0x6A80,0x130B,0x443C,0x174D,0x1DBD,0x27ED,0x43D5,0x38E0,0x0942,0x0DB3,0x6C0C,0x09C0,0x43E9,0x048B,0x4A9B,0x39FD,0x037E,0x533F,0x3981,0x2FC2,0x5AB3,0x2DAC,0x403B,0x2E54,0x2397,0x06C3,0x22BA,0x60B4,0x08EA,0x2B0E,0x0116,0x31DA,0x0E37,0x376E,0x2D6C,0x1DA1,0x1ADF,0x2DB9,0x1E02,0x05D0,0x0633,0x4356,0x06F1,0x0751,0x2881,0x1D47,0x2D8C,0x5BD0,0x49F2,0x6343,0x06DB,0x06F4,0x235A,0x2554,0x3B2B,0x112A,0x70F7,0x00B9,0x4DCC,0x5C7A,0x29E7,0x20AA,0x5063};
const q63 Reference11_q63[1] = {0x000000001C245239};
const q15 Reference28_q15[263] = {0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC02F,0xC103,0xC1D7,0xC2AC,0xC380,0xC454,0xC528,0xC5FC,0xC6D0,0xC7A5,0xC879,0xC94D,0xCA21,0xCAF5,0xCBC9,0xCC9E,0xCD72,0xCE46,0xCF1A,0xCFEE,0xD0C2,0xD197,0xD26B,0xD33F,0xD413,0xD4E7,0xD5BB,0xD690,0xD764,0xD838,0xD90C,0xD9E0,0xDAB4,0xDB89,0xDC5D,0xDD31,0xDE05,0xDED9,0xDFAD,0xE082,0xE156,0xE22A,0xE2FE,0xE3D2,0xE4A6,0xE57B,0xE64F,0xE723,0xE7F7,0xE8CB,0xE99F,0xEA74,0xEB48,0xEC1C,0xECF0,0xEDC4,0xEE98,0xEF6D,0xF041,0xF115,0xF1E9,0xF2BD,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333,0xF333};
const q15 Reference29_q15[272] = {0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC000,0xC02F,0xC103,0xC1D7,0xC2AC,0xC380,0xC454,0xC528,0xC5FC,0xC6D0,0xC7A5,0xC879,0xC94D,0xCA21,0xCAF5,0xCBC9,0xCC9E,0xCD72,0xCE46,0xCF1A,0xCFEE,0xD0C2,0xD197,0xD26B,0xD33F,0xD413,0xD4E7,0xD5BB,0xD690,0xD764,0xD838,0xD90C,0xD9E0,0xDAB4,0xDB89,0xDC5D,0xDD31,0xDE05,0xDED9,0xDFAD,0xE082,0xE156,0xE22A,0xE2FE,0xE3D2,0xE4A6,0xE57B,0xE64F,0xE723,0xE7F7,0xE8CB,0xE99F,0xEA74,0xEB48,0xEC1C,0xECF0,0xEDC4,0xEE98,0xEF6D,0xF041,0xF115,0xF1E9,0xF2BD,0xF391,0xF466,0xF53A,0xF60E,0xF6E2,0xF7B6,0xF88A,0xF95F,0xFA33,0xFB07,0xFBDB,0xFCAF,0xFD83,0xFE58,0xFF2C,0x0000,0x00D4,0x01A8,0x027D,0x0351,0x0425,0x04F9,0x05CD,0x06A1,0x0776,0x084A,0x091E,0x09F2,0x0AC6,0x0B9A,0x0C6F,0x0D43,0x0E17,0x0EEB,0x0FBF,0x1093,0x1168,0x123C,0x1310,0x13E4,0x14B8,0x158C,0x1661,0x1735,0x1809,0x18DD,0x19B1,0x1A85,0x1B5A,0x1C2E,0x1D02,0x1DD6,0x1EAA,0x1F7E,0x2053,0x2127,0x21FB,0x22CF,0x23A3,0x2477,0x254C,0x2620,0x26F4,0x27C8,0x289C,0x2970,0x2A45,0x2B19,0x2BED,0x2CC1,0x2D95,0x2E69,0x2F3E,0x3012,0x30E6,0x31BA,0x328E,0x3362,0x3437,0x350B,0x35DF,0x36B3,0x3787,0x385B,0x3930,0x3A04,0x3AD8,0x3BAC,0x3C80,0x3D54,0x3E29,0x3EFD,0x3FD1,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000};
const q15 Reference30_q15[279] = {0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0CCD,0x0D43,0x0E17,0x0EEB,0x0FBF,0x1093,0x1168,0x123C,0x1310,0x13E4,0x14B8,0x158C,0x1661,0x1735,0x1809,0x18DD,0x19B1,0x1A85,0x1B5A,0x1C2E,0x1D02,0x1DD6,0x1EAA,0x1F7E,0x2053,0x2127,0x21FB,0x22CF,0x23A3,0x2477,0x254C,0x2620,0x26F4,0x27C8,0x289C,0x2970,0x2A45,0x2B19,0x2BED,0x2CC1,0x2D95,0x2E69,0x2F3E,0x3012,0x30E6,0x31BA,0x328E,0x3362,0x3437,0x350B,0x35DF,0x36B3,0x3787,0x385B,0x3930,0x3A04,0x3AD8,0x3BAC,0x3C80,0x3D54,0x3E29,0x3EFD,0x3FD1,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000};