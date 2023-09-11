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

const q15 ComplexMathsQ15_Input1_q15[512]={0x3AE0,0x07CC,0xFBCC,0x1E50,0x9245,0xDE55,0xC639,0x9BD7,0x0F04,0xF9D3,0x1791,0x09CF,0xE123,0xEABD,0x9027,0xB7F0,0xD705,0xBEEE,0x15DD,0x13D9,0xFB04,0x096A,0x364E,0xDEE3,0xF4ED,0x1DEA,0xE666,0xF072,0xCAC8,0x2674,0x1092,0xEC36,0x0CB8,0xF380,0xA277,0x106B,0x3533,0x1316,0xCD5F,0x981C,0xEF8C,0x2C6D,0xDC77,0x0C5A,0x19BE,0xF295,0x58A7,0x1A81,0xCDFF,0x5E5D,0xDC2D,0xE1A0,0x1BDC,0x0BF1,0x54D9,0x2F62,0xDC7E,0xB395,0xF662,0x129F,0xCB93,0x2354,0x3029,0xF4B0,0xF8B8,0x1E70,0xE490,0xFB15,0x4EA3,0x45D3,0x292B,0x12C5,0xFF29,0xFDE5,0xF9DD,0x0F8B,0x1CE5,0xD229,0x2A9E,0xCA6A,0xDE36,0xF466,0xEDD6,0xF285,0x0399,0xF560,0xF36A,0x315B,0xD8D6,0x20C8,0xE6AE,0x46D5,0xFE1E,0xED5D,0xBC5D,0xDF83,0xB765,0xD9DC,0x185A,0xF23E,0xC918,0xDE19,0xAF0E,0x0F87,0x11AE,0xEE54,0xF53E,0x4094,0xD396,0xC093,0x56BD,0xFDA1,0xF0DD,0x1FF1,0xB897,0x170C,0x4587,0x11B6,0xF2E3,0xFC86,0xF2BF,0xCAD9,0xD692,0xD715,0xD8EF,0x1803,0x1F9B,0x5052,0x356C,0xFC89,0xB8E4,0x0B69,0x039D,0xC76C,0x1638,0x2B06,0x04B3,0xBB79,0xFABF,0x235B,0xB7D4,0xCCED,0xF385,0x2B54,0xECA0,0x04F4,0x4611,0xE983,0xD96D,0xC01B,0xE630,0xE1E9,0x3537,0xF4DE,0x2232,0xF89C,0x1A99,0x3344,0x1C06,0x21AB,0x3C10,0xF52D,0x13A3,0x13B4,0xFC6E,0xDE51,0x019E,0xFFB5,0xF7C9,0x2369,0xFF0B,0xE753,0xD5E9,0x13F9,0x1ED8,0xDE6E,0x1C72,0x0F75,0xEFEF,0xDBF0,0x64B3,0xE11C,0xD0F2,0xBE1C,0x11F6,0x0404,0x1878,0x006E,0x1DD3,0xFFEB,0xD696,0xDA5A,0xC28B,0xAF0D,0xD83D,0x4C16,0xED16,0x41DA,0xF6B5,0x0A81,0xDD9A,0x49FD,0x16D2,0x185C,0xF231,0xD9E9,0xDCEB,0x11CF,0xE27F,0xDF18,0x46EC,0xCCF1,0xC09F,0x02D6,0x4533,0x0BB6,0xE625,0x0AF9,0xD086,0x138C,0x026D,0xFCB4,0x33A1,0x0151,0xC969,0x1839,0xC66D,0xFEAB,0x0689,0xF67C,0x45BF,0x1AA9,0xBCF8,0xEC79,0x0FF2,0xE401,0xE3E9,0xF006,0xDC62,0x0624,0xE480,0x4A05,0xE54A,0xC8D5,0xE990,0x3BC1,0x1CA3,0x9A77,0xF679,0xEF34,0xDC7D,0xF7E2,0x16E7,0x28A7,0xC2F1,0xD3EA,0x2D66,0xC001,0x264E,0xE3C6,0x118F,0xB7AF,0x35BD,0xFA10,0xFC42,0xD890,0xF53E,0x00F1,0x1FE4,0xF135,0xEBAB,0xC64D,0x2955,0x26A4,0xF86D,0x0A7C,0x0AD2,0xD062,0x11E8,0xF909,0xF96F,0xD801,0xF115,0x1825,0xBF2E,0xEA40,0x2907,0xBCD6,0x1F69,0xCBFC,0xFAB0,0xE716,0xE981,0x072D,0x1360,0x0400,0xFDEE,0xF8BB,0xD823,0x5C07,0xDB67,0x3E52,0x0249,0xD300,0x1902,0x21C0,0x59C6,0xB4BA,0xAEB5,0x061C,0x2EDE,0x04D3,0xD4A4,0x0F9D,0x377E,0xAD85,0x1277,0xC080,0x46A2,0xF6C0,0x4095,0xE2BB,0x28A3,0xDFB4,0x35C4,0xFD6A,0xCB6B,0xF389,0x1D80,0x2545,0x5502,0xCD41,0x235B,0xF748,0x0AF3,0x125E,0xA413,0xE2CB,0xE5DC,0x276D,0xF656,0x5238,0xA3E3,0x1EC4,0x108E,0x2879,0xFCD3,0xD7E1,0x18B1,0x03F6,0xE792,0x2876,0x086F,0x7235,0xF700,0x0E04,0x27AE,0xD4E2,0x13EF,0xE041,0x0AE8,0xCD84,0x0C2C,0x8000,0x2F21,0x1478,0xDCBA,0x1DD8,0x0FC1,0x6E53,0xD496,0xF563,0x2761,0x9AF9,0xCFAD,0xEDB6,0x0451,0x0DAC,0xCC7C,0xCF22,0xCCE1,0xD269,0x0AC7,0x03FC,0xCED5,0x081E,0x0B2A,0x2E20,0xE7B3,0xF9CC,0x0B6B,0xD386,0xE4A7,0x1093,0x4C60,0x1930,0x12BB,0xE33C,0x1A3F,0x081C,0xF490,0xC923,0x2036,0x1445,0xC87B,0x0995,0x2CF2,0xE88E,0x0E29,0x30F7,0xCF82,0x0872,0x1167,0x101C,0xED63,0xC9F5,0xD30C,0x0B5A,0x19A5,0xCDCC,0x53A0,0x8F0D,0x417B,0xAB53,0xDAEE,0x49EB,0x09A3,0x038D,0xE882,0x3282,0x183E,0x3256,0x05F4,0x0B9C,0xFE7A,0x42A4,0xD758,0xA67F,0x15DC,0xF9EF,0x155C,0xF168,0xDB3C,0xC32A,0xD322,0xD36E,0x326A,0x06BB,0xF1C9,0xE217,0x2D43,0xDB4B,0x0A5B,0xE72B,0xCDA2,0xF3EF,0x3932,0xE21B,0xE95B,0xEB51,0x15FD,0xF1D2,0x1B54,0xFD4E,0xF4F0,0xD1C0,0x498A,0x0291,0x4AD8,0xEAEE,0x0390,0xD61B,0xF6DA,0x24FB,0xCED6,0x01B5,0x0696,0xB734,0xEFE3,0xB57F,0xD13D,0xA3CE,0xEF94,0xD554,0x2D58,0x1FDB,0xD52B,0xDD6B,0x0BE4,0xB266,0x28B7,0xD386,0xFBDE,0x0FA5,0x0509,0xF501,0xCC81,0x2D94,0xF901,0x466F,0xE58D,0xFB6A,0x153A,0x1D15,0x3E41,0xD358,0x18E3,0xD541,0xDF69,0xF8CF,0x4B62,0x3539};

const q15 ComplexMathsQ15_Input2_q15[512]={0x2726,0xED0F,0x15CA,0x1E72,0x156B,0x1318,0x34E9,0xCC4C,0x0C32,0xF12A,0xB338,0xBAEF,0xEA78,0xF3A5,0x1017,0x2314,0xFE9D,0xD945,0xFE4F,0xED5D,0x2B71,0xCEB4,0x559A,0xD27B,0xF166,0x127E,0x02D5,0xE47C,0x499F,0xD53A,0x2A13,0xF848,0xCD14,0xBF90,0x0825,0xDF5D,0xE78D,0x2338,0xDECE,0x0649,0xD83E,0x23EE,0x09D5,0x186B,0xDD0A,0xF2A6,0xE2F4,0x1729,0xEF46,0x09C2,0x08F1,0x2F48,0x0DD4,0x2760,0xF207,0xF0D3,0xEAD6,0x097E,0x19BC,0xE4DD,0xD1ED,0xFD18,0x042F,0xCBA7,0xFF37,0xFC63,0x1E31,0xFCE9,0x1CEB,0xD930,0x1266,0xBE64,0x07E8,0x0C04,0xF930,0x0E53,0x168E,0xDA4F,0xF480,0x25B6,0xDD12,0x24A2,0x8BDA,0xEE4F,0xF0D8,0x0A82,0xFAE9,0x014B,0xDDAB,0xB9DD,0x1352,0xD837,0x0BDD,0xF05D,0x2F6B,0x499D,0xE848,0x3BBA,0x0686,0xE3EC,0xE8C0,0x1D78,0x0409,0x28BC,0xF6C0,0x1456,0x02F1,0x0CFC,0x1EE5,0x2020,0xF5E7,0x72D3,0xFE01,0xF767,0xDD28,0x2554,0xC912,0x32AF,0xEA31,0x12C4,0xECB6,0x1E5B,0xD445,0x1A1B,0x0113,0xD09D,0xE02A,0xD3C8,0x2056,0xA2DC,0x537C,0xD6E2,0x348E,0x9FC3,0x4379,0x2270,0x2038,0x2E45,0x48C9,0xFBBA,0x174B,0x0FE2,0xF7E0,0x2C6F,0xD1D7,0xD83A,0x2380,0xB80F,0x4058,0xE327,0x19A1,0xD7F3,0xEAA1,0xD2C3,0xBD5F,0x0036,0x15AC,0x5238,0x0E02,0xDD01,0xF6A3,0xFF3B,0x113F,0x015A,0xECCA,0x00C1,0x0657,0xE6FA,0x31E2,0xEE8F,0x42EA,0xF692,0x1386,0xE151,0x353C,0xF624,0x004D,0xD40A,0x0A7B,0xCF3B,0xF793,0xF1C0,0xD4E8,0xAF87,0xF55C,0x1C43,0xF831,0xE8D5,0xEFAD,0x080B,0x112B,0x4F43,0xFE25,0xE26D,0x2A81,0xEAB7,0x05D2,0xAF2F,0x1AAF,0xB42E,0xFDF7,0x0BF3,0x0778,0xE445,0x2661,0x1E92,0x3A07,0x1EF8,0xD584,0xDA3C,0xF57A,0x2D54,0x1312,0x2DA7,0x1391,0xFF2D,0xE2FF,0xE1C2,0xD7DA,0x00E8,0x2A66,0xF27B,0xBFDB,0xDCB3,0x0E9E,0xFA3A,0xEC7B,0xE0DB,0x5452,0x07FC,0x26F0,0xEE19,0x246C,0x0CDC,0x1ABE,0x156E,0xEBD3,0xF940,0x0457,0xC644,0xE832,0xCD27,0x0610,0x0AE5,0xA0D9,0xB9FA,0x2B4A,0xCE5F,0x428C,0x01CD,0xE44E,0xFAA4,0x036D,0xED11,0xE0DD,0x215F,0x116A,0x111D,0x21D1,0x3F18,0x0C6B,0xFF88,0xDE91,0x07C0,0xD957,0x65D4,0xE797,0x3504,0xD100,0x28B5,0x0241,0xF6F0,0x7375,0x2E74,0x3BCC,0x00DE,0x16D5,0xB429,0xFDA9,0xD3C6,0x3078,0xE32C,0xF379,0xEE44,0xF025,0xBBE0,0x377A,0xE01B,0x1E90,0xD796,0x1923,0x01A0,0xEF95,0xF5DA,0xDBE5,0xDD02,0x1922,0xDC09,0x3C9F,0x0E2C,0x3B2A,0x41FE,0x2B7C,0x0358,0x38ED,0x0E04,0xF445,0xC6EA,0x0B82,0xF598,0xFAEA,0xF18B,0xD6C8,0x4613,0x5466,0xF95C,0x13DC,0x07DC,0x10F0,0xF5B4,0x310D,0x19AA,0xF938,0x035E,0x5474,0x0BC2,0x5869,0x021D,0xF958,0xAC03,0x10D7,0xF7B0,0x148D,0xECF1,0x1B0E,0x1FC7,0x0425,0x4A26,0xF7D3,0x3484,0xD9BD,0x1E70,0xD660,0xCDB3,0xF37D,0xF248,0x0294,0x2592,0xDE65,0x214D,0xFE72,0xE4B7,0x5C39,0x026D,0xFC08,0xF3BC,0x1C43,0xF166,0x1E0D,0x07FF,0x0FB9,0xD575,0xF485,0xF7BF,0x28E2,0x1D71,0xEC57,0xEF97,0xFA54,0xA7F8,0x6342,0x2DEA,0x27D8,0xBAD6,0x1A93,0x20AB,0x0625,0xB825,0x000A,0x27A9,0xD7E4,0xF8D8,0xDA6C,0xEEE2,0x0028,0x519E,0xF3F0,0x49DA,0x0099,0x036E,0x36AA,0xE1DF,0xE5AB,0x0DA2,0x22DC,0x46AC,0xFDC5,0xDB8F,0x5C2D,0xF4C5,0x0E23,0x169C,0x38FC,0xE0B2,0x0E83,0x2D42,0x25FC,0x001C,0x0CEA,0x20D5,0x19D1,0x18EE,0x30C6,0xF4FA,0x0F9A,0x3473,0x3309,0x16A5,0xCEBE,0x12AB,0xE592,0x2C89,0xD7EC,0xE02A,0x11E4,0xB7B0,0x2A81,0x2954,0x41AF,0x30D3,0xDE81,0xDBCA,0xD013,0xE45B,0xFA99,0x0924,0x5DAB,0x4ACC,0xFA5B,0x2746,0x0568,0xE190,0xE54B,0xF5BE,0xDF24,0xC63E,0xFBB5,0x12B4,0xC2CB,0xFA06,0x261C,0x0ED3,0xF4B9,0xFB1A,0xF6DD,0x264F,0xCBD6,0xC3CA,0x12B2,0xB78F,0x0866,0xFE93,0xEB56,0xE0F0,0x6623,0x0846,0x153A,0x121A,0x1B0B,0x0E12,0x516F,0xC22A,0xE56C,0x17C0,0x08D5,0xE392,0x1073,0x7FFF,0xBCFF,0xD449,0xF1A6,0xE4D9,0xDDC4,0xE1C2,0xF637,0xDFD7,0x03A3,0xDC5B,0xCBD5,0xC1C8,0xF37E,0x0101,0x105B,0xDB71,0x41B1,0xEA79,0xDC7F,0xB308,0xD47E,0x3A2E,0x1AC8,0xDDD1,0xAF67,0x2D81,0xC618,0x1DC1,0xFF5A,0xCC6E,0x2969,0xDC33,0x2C29,0xF6BF};

const q15 ComplexMathsQ15_Input3_q15[256]={0x13E3,0xEFF3,0x0498,0x01BB,0x07EB,0xE61D,0x0A9A,0xEA1A,0xC613,0x0F79,0xF3A2,0x9B75,0x173E,0x2EFB,0xF4A4,0xFC0D,0xEBAA,0xE8D6,0x1770,0x0750,0xF09C,0x1A67,0xEEAD,0x3925,0x1A90,0x2925,0xC852,0xC2C5,0xD114,0xC17F,0x5B19,0xCF7F,0xFF20,0xEE10,0x0DB6,0xF564,0x2D7C,0xF11C,0x1DBD,0xEABA,0xD44C,0x0D35,0xD87D,0x76DA,0xDCC0,0x0D3D,0xFE7B,0xD4D7,0x2DDB,0x2E55,0xF88E,0x1CA3,0xF01B,0xF198,0x157A,0x2953,0xD8BD,0xFF14,0xF1ED,0xFB1C,0x8000,0x2B0C,0xACD4,0xE237,0xE68E,0xFAD2,0xE1BB,0x3324,0xFF8C,0xF545,0x0976,0xD4AB,0xE4DA,0x0509,0x052B,0x01D7,0x0EF2,0x391F,0xAA8D,0xD10B,0x1A4B,0xE521,0x2D78,0x28A6,0xC865,0xF777,0xF044,0x0D7A,0xBBC3,0xF712,0x5E5D,0x3576,0xF4DF,0x4F37,0xD4AD,0x166B,0xC2B3,0xDB0D,0x0CFB,0x4096,0xDDD2,0xB7DD,0x2AF5,0x2590,0x1E99,0x19E2,0x22A8,0xFA2E,0xCA76,0xE855,0x4635,0x2522,0xE94C,0xFC15,0xE04E,0x3E84,0x6058,0xD1AE,0x9C90,0x3351,0xB733,0x0B20,0x09C0,0xC330,0x2FC7,0xF67B,0x151A,0x208D,0xF1BD,0xE6EC,0x03F6,0x47C6,0x2D9A,0xD71D,0xC0E7,0xC998,0xEA60,0x2A4F,0x0369,0x3A59,0xA671,0xF63B,0xD8F8,0xB5E7,0x05E2,0x1D84,0x1BB9,0xDE9E,0x425F,0xEFEB,0x23AE,0x3EFE,0x042B,0xFE53,0xE6F6,0x7682,0x2194,0xA26E,0x3725,0x0379,0x30B9,0xFC29,0x0AC6,0xDF33,0xFA41,0x4827,0xE243,0x25DB,0x00A3,0xFF10,0x1608,0x1B31,0x07BA,0x2686,0xFE5A,0xC658,0x0AAA,0x092D,0xF5D1,0xAD66,0xCAD9,0xABA9,0x70DD,0xDDD7,0x29B8,0xFC34,0x569B,0x27FA,0x04FE,0xDCB8,0xF6C4,0xEE4B,0xCAA5,0x2F73,0x1F07,0xFB9F,0x26BB,0x3667,0xCEFE,0x12AA,0x04AA,0x0264,0x8E10,0xF379,0xEFF1,0xCE3F,0xC560,0xEC38,0xABFE,0x16FD,0x6023,0x0C2A,0xC9A7,0x056D,0xED32,0xE69C,0xD93C,0x1F64,0x3425,0x083F,0xD0D6,0xE822,0xE50D,0xCBEA,0xF181,0x9407,0x3EE5,0xE35C,0xBACC,0xC112,0x10F9,0x6A52,0xCB2A,0x1271,0x18DE,0xFFC9,0xF9F8,0xCDA5,0x205C,0xC409,0x0F0E,0xCC7C,0xDF5E,0x1753,0x30A9,0xF78F,0x176B,0xEB12,0x0960,0x0ACC,0xEA8C,0xFBE9,0xFC87,0xD053,0xF4FD,0xCF46};

const q15 ComplexMathsQ15_Reference1_q15[512]={0x3AE0,0xF834,0xFBCC,0xE1B0,0x9245,0x21AB,0xC639,0x6429,0x0F04,0x062D,0x1791,0xF631,0xE123,0x1543,0x9027,0x4810,0xD705,0x4112,0x15DD,0xEC27,0xFB04,0xF696,0x364E,0x211D,0xF4ED,0xE216,0xE666,0x0F8E,0xCAC8,0xD98C,0x1092,0x13CA,0x0CB8,0x0C80,0xA277,0xEF95,0x3533,0xECEA,0xCD5F,0x67E4,0xEF8C,0xD393,0xDC77,0xF3A6,0x19BE,0x0D6B,0x58A7,0xE57F,0xCDFF,0xA1A3,0xDC2D,0x1E60,0x1BDC,0xF40F,0x54D9,0xD09E,0xDC7E,0x4C6B,0xF662,0xED61,0xCB93,0xDCAC,0x3029,0x0B50,0xF8B8,0xE190,0xE490,0x04EB,0x4EA3,0xBA2D,0x292B,0xED3B,0xFF29,0x021B,0xF9DD,0xF075,0x1CE5,0x2DD7,0x2A9E,0x3596,0xDE36,0x0B9A,0xEDD6,0x0D7B,0x0399,0x0AA0,0xF36A,0xCEA5,0xD8D6,0xDF38,0xE6AE,0xB92B,0xFE1E,0x12A3,0xBC5D,0x207D,0xB765,0x2624,0x185A,0x0DC2,0xC918,0x21E7,0xAF0E,0xF079,0x11AE,0x11AC,0xF53E,0xBF6C,0xD396,0x3F6D,0x56BD,0x025F,0xF0DD,0xE00F,0xB897,0xE8F4,0x4587,0xEE4A,0xF2E3,0x037A,0xF2BF,0x3527,0xD692,0x28EB,0xD8EF,0xE7FD,0x1F9B,0xAFAE,0x356C,0x0377,0xB8E4,0xF497,0x039D,0x3894,0x1638,0xD4FA,0x04B3,0x4487,0xFABF,0xDCA5,0xB7D4,0x3313,0xF385,0xD4AC,0xECA0,0xFB0C,0x4611,0x167D,0xD96D,0x3FE5,0xE630,0x1E17,0x3537,0x0B22,0x2232,0x0764,0x1A99,0xCCBC,0x1C06,0xDE55,0x3C10,0x0AD3,0x13A3,0xEC4C,0xFC6E,0x21AF,0x019E,0x004B,0xF7C9,0xDC97,0xFF0B,0x18AD,0xD5E9,0xEC07,0x1ED8,0x2192,0x1C72,0xF08B,0xEFEF,0x2410,0x64B3,0x1EE4,0xD0F2,0x41E4,0x11F6,0xFBFC,0x1878,0xFF92,0x1DD3,0x0015,0xD696,0x25A6,0xC28B,0x50F3,0xD83D,0xB3EA,0xED16,0xBE26,0xF6B5,0xF57F,0xDD9A,0xB603,0x16D2,0xE7A4,0xF231,0x2617,0xDCEB,0xEE31,0xE27F,0x20E8,0x46EC,0x330F,0xC09F,0xFD2A,0x4533,0xF44A,0xE625,0xF507,0xD086,0xEC74,0x026D,0x034C,0x33A1,0xFEAF,0xC969,0xE7C7,0xC66D,0x0155,0x0689,0x0984,0x45BF,0xE557,0xBCF8,0x1387,0x0FF2,0x1BFF,0xE3E9,0x0FFA,0xDC62,0xF9DC,0xE480,0xB5FB,0xE54A,0x372B,0xE990,0xC43F,0x1CA3,0x6589,0xF679,0x10CC,0xDC7D,0x081E,0x16E7,0xD759,0xC2F1,0x2C16,0x2D66,0x3FFF,0x264E,0x1C3A,0x118F,0x4851,0x35BD,0x05F0,0xFC42,0x2770,0xF53E,0xFF0F,0x1FE4,0x0ECB,0xEBAB,0x39B3,0x2955,0xD95C,0xF86D,0xF584,0x0AD2,0x2F9E,0x11E8,0x06F7,0xF96F,0x27FF,0xF115,0xE7DB,0xBF2E,0x15C0,0x2907,0x432A,0x1F69,0x3404,0xFAB0,0x18EA,0xE981,0xF8D3,0x1360,0xFC00,0xFDEE,0x0745,0xD823,0xA3F9,0xDB67,0xC1AE,0x0249,0x2D00,0x1902,0xDE40,0x59C6,0x4B46,0xAEB5,0xF9E4,0x2EDE,0xFB2D,0xD4A4,0xF063,0x377E,0x527B,0x1277,0x3F80,0x46A2,0x0940,0x4095,0x1D45,0x28A3,0x204C,0x35C4,0x0296,0xCB6B,0x0C77,0x1D80,0xDABB,0x5502,0x32BF,0x235B,0x08B8,0x0AF3,0xEDA2,0xA413,0x1D35,0xE5DC,0xD893,0xF656,0xADC8,0xA3E3,0xE13C,0x108E,0xD787,0xFCD3,0x281F,0x18B1,0xFC0A,0xE792,0xD78A,0x086F,0x8DCB,0xF700,0xF1FC,0x27AE,0x2B1E,0x13EF,0x1FBF,0x0AE8,0x327C,0x0C2C,0x7FFF,0x2F21,0xEB88,0xDCBA,0xE228,0x0FC1,0x91AD,0xD496,0x0A9D,0x2761,0x6507,0xCFAD,0x124A,0x0451,0xF254,0xCC7C,0x30DE,0xCCE1,0x2D97,0x0AC7,0xFC04,0xCED5,0xF7E2,0x0B2A,0xD1E0,0xE7B3,0x0634,0x0B6B,0x2C7A,0xE4A7,0xEF6D,0x4C60,0xE6D0,0x12BB,0x1CC4,0x1A3F,0xF7E4,0xF490,0x36DD,0x2036,0xEBBB,0xC87B,0xF66B,0x2CF2,0x1772,0x0E29,0xCF09,0xCF82,0xF78E,0x1167,0xEFE4,0xED63,0x360B,0xD30C,0xF4A6,0x19A5,0x3234,0x53A0,0x70F3,0x417B,0x54AD,0xDAEE,0xB615,0x09A3,0xFC73,0xE882,0xCD7E,0x183E,0xCDAA,0x05F4,0xF464,0xFE7A,0xBD5C,0xD758,0x5981,0x15DC,0x0611,0x155C,0x0E98,0xDB3C,0x3CD6,0xD322,0x2C92,0x326A,0xF945,0xF1C9,0x1DE9,0x2D43,0x24B5,0x0A5B,0x18D5,0xCDA2,0x0C11,0x3932,0x1DE5,0xE95B,0x14AF,0x15FD,0x0E2E,0x1B54,0x02B2,0xF4F0,0x2E40,0x498A,0xFD6F,0x4AD8,0x1512,0x0390,0x29E5,0xF6DA,0xDB05,0xCED6,0xFE4B,0x0696,0x48CC,0xEFE3,0x4A81,0xD13D,0x5C32,0xEF94,0x2AAC,0x2D58,0xE025,0xD52B,0x2295,0x0BE4,0x4D9A,0x28B7,0x2C7A,0xFBDE,0xF05B,0x0509,0x0AFF,0xCC81,0xD26C,0xF901,0xB991,0xE58D,0x0496,0x153A,0xE2EB,0x3E41,0x2CA8,0x18E3,0x2ABF,0xDF69,0x0731,0x4B62,0xCAC7};

const q31 ComplexMathsQ15_Reference2_q31[2]={0xFF7120DE,0xFF8EC992};

const q31 ComplexMathsQ15_Reference3_q31[2]={0xFF6737B0,0xFF4B14C3};

const q31 ComplexMathsQ15_Reference4_q31[2]={0xFF28DDCF,0xFF925F46};

const q15 ComplexMathsQ15_Reference5_q15[256]={0x1DB2,0x0F4D,0x3964,0x39D1,0x081E,0x0CC3,0x12BD,0x4287,0x2673,0x0EC4,0x0553,0x1FCD,0x0FF3,0x0EFA,0x20D4,0x0CE7,0x08EB,0x2F7B,0x1C43,0x39C9,0x17B0,0x12CF,0x0E84,0x2E44,0x3565,0x177C,0x0F28,0x3097,0x2A22,0x0A7B,0x1F9C,0x18BC,0x0FA6,0x0DF0,0x3495,0x16A0,0x0122,0x085B,0x1B18,0x223C,0x11DD,0x0B4F,0x059C,0x1978,0x1989,0x259C,0x095E,0x2585,0x2902,0x0DFC,0x2044,0x2936,0x0C80,0x20BC,0x26B7,0x2B62,0x11AD,0x2585,0x23E0,0x06C8,0x1B64,0x1D1E,0x16EE,0x2B28,0x1AC4,0x2402,0x1C59,0x1836,0x2258,0x11DF,0x2C35,0x168C,0x0A00,0x24CB,0x2551,0x13D3,0x1B2F,0x117E,0x1CE1,0x15E7,0x1E84,0x0DE9,0x10F0,0x00D3,0x122D,0x0C59,0x174B,0x16CB,0x1030,0x13BD,0x34AA,0x287C,0x0934,0x0C3D,0x0EE9,0x1BFC,0x32D1,0x2AED,0x2242,0x0703,0x28CC,0x10B1,0x1442,0x13AC,0x1619,0x2BB2,0x1FB8,0x2317,0x0E0B,0x19AC,0x020C,0x19D3,0x1DDC,0x1CCB,0x05C6,0x2556,0x22E9,0x101C,0x1028,0x1212,0x277B,0x1EA6,0x1FEA,0x34BF,0x09A8,0x1237,0x1754,0x25A8,0x273B,0x17CA,0x2536,0x1B08,0x13CF,0x0566,0x1194,0x1E97,0x1C4A,0x0678,0x186A,0x099B,0x1444,0x0E31,0x2230,0x275A,0x1E62,0x0CBC,0x0BCE,0x09E4,0x03C8,0x3225,0x2423,0x1687,0x1500,0x3A94,0x28C3,0x178E,0x170B,0x31B5,0x2111,0x239E,0x2374,0x19F4,0x1AEA,0x1B05,0x17C4,0x3180,0x1235,0x0AB1,0x303A,0x17A7,0x2964,0x308F,0x15DD,0x1420,0x0C81,0x17A2,0x3942,0x0854,0x1D4C,0x12BE,0x19D3,0x404A,0x19B1,0x171A,0x37B9,0x1659,0x3637,0x19D6,0x072B,0x2381,0x2240,0x05BF,0x18EB,0x17BA,0x0C8A,0x16F5,0x0FFD,0x2836,0x112A,0x0DBC,0x1C05,0x1308,0x1C2C,0x1959,0x197C,0x189C,0x0BDB,0x1C94,0x172F,0x1C30,0x4645,0x3585,0x2959,0x0523,0x1BDA,0x1BEF,0x0686,0x2154,0x3127,0x0B58,0x0CEF,0x238A,0x1F9F,0x196E,0x108F,0x1D23,0x0D74,0x19E5,0x2045,0x0F56,0x0D15,0x0DBB,0x17C7,0x24CB,0x26E0,0x1506,0x130C,0x1899,0x248C,0x261D,0x33B0,0x16DD,0x1BB5,0x1B87,0x2741,0x1E26,0x0817,0x060C,0x2262,0x2364,0x0D6C,0x1200,0x264F,0x18BB,0x10B0,0x2E23};

const q15 ComplexMathsQ15_Reference6_q15[256]={0x06E3,0x01D4,0x19BB,0x1A1D,0x0084,0x0146,0x02BE,0x2293,0x0B8D,0x01B4,0x0039,0x07E7,0x01FD,0x01C1,0x086B,0x014D,0x009F,0x119D,0x063D,0x1A16,0x0462,0x02C4,0x01A5,0x10B9,0x1646,0x044F,0x01CB,0x1272,0x0DDE,0x00DC,0x07CE,0x04C8,0x01EA,0x0185,0x159A,0x0400,0x0003,0x008C,0x05BC,0x0928,0x027E,0x0100,0x003F,0x0511,0x0518,0x0B0D,0x00AF,0x0AFF,0x0D23,0x0187,0x0822,0x0D45,0x0138,0x085F,0x0BB6,0x0EB4,0x0271,0x0AFF,0x0A0E,0x005C,0x05DC,0x069F,0x041B,0x0E8D,0x0599,0x0A21,0x0647,0x0494,0x0937,0x027F,0x0F45,0x03F9,0x00C8,0x0A94,0x0AE1,0x0312,0x05C6,0x0264,0x0684,0x03C0,0x0746,0x0183,0x023E,0x0001,0x0295,0x0131,0x043D,0x040F,0x020C,0x030B,0x15AB,0x0CCE,0x00A9,0x012B,0x01BD,0x061E,0x142D,0x0E65,0x092B,0x0062,0x0D01,0x022D,0x0335,0x0306,0x03D1,0x0EEB,0x07DC,0x099F,0x018A,0x0526,0x0008,0x0536,0x06F7,0x067A,0x0043,0x0AE4,0x0985,0x0207,0x020A,0x028D,0x0C2D,0x0757,0x07F5,0x15BD,0x00BA,0x0297,0x0441,0x0B14,0x0C06,0x046C,0x0AD1,0x05B6,0x0311,0x003A,0x026A,0x074F,0x0641,0x0054,0x04A8,0x00B9,0x0335,0x0193,0x0921,0x0C19,0x0736,0x0144,0x0117,0x00C4,0x001D,0x13A5,0x0A34,0x03F7,0x0372,0x1ACF,0x0CFB,0x0456,0x0426,0x134D,0x088B,0x09E9,0x09D2,0x0543,0x05A9,0x05B4,0x046A,0x1325,0x0297,0x00E5,0x122C,0x045F,0x0D63,0x126C,0x03BC,0x032A,0x0139,0x045D,0x199D,0x008B,0x06B5,0x02BF,0x0536,0x204A,0x0528,0x042B,0x1842,0x03E7,0x16F7,0x0537,0x0067,0x09D9,0x092A,0x0042,0x04DA,0x0466,0x013B,0x041E,0x01FF,0x0CA2,0x024D,0x0179,0x0622,0x02D4,0x0633,0x0505,0x0513,0x04BB,0x0119,0x0661,0x0433,0x0635,0x2693,0x1661,0x0D5B,0x0035,0x0610,0x0619,0x0055,0x08AE,0x12E0,0x0101,0x014F,0x09DE,0x07D0,0x050E,0x0224,0x06A2,0x016A,0x053D,0x0823,0x01D6,0x0156,0x0179,0x046B,0x0A93,0x0BCF,0x0374,0x02D6,0x04BA,0x0A6F,0x0B59,0x14DF,0x0415,0x05FF,0x05EB,0x0C0A,0x071A,0x0083,0x0049,0x093D,0x09C9,0x0168,0x0288,0x0B77,0x04C7,0x022D,0x10A1};

const q15 ComplexMathsQ15_Reference7_q15[512]={0x04CA,0xFE6B,0xFE05,0x010A,0xFCAA,0xFA80,0xEFEA,0xFB7C,0x002E,0xFF6B,0xFDCA,0xFB5A,0x00C9,0x01A4,0x016C,0xF612,0xFB30,0x0347,0x00A6,0xFF23,0x007C,0x0147,0x0623,0xF5A3,0xFF3C,0xFEBF,0xFF06,0x014A,0xFB8F,0x09FA,0x0110,0xFE20,0xFD29,0xFFA5,0xFF8F,0x0639,0xFC26,0x02C0,0x048F,0x061D,0xFE29,0xFB65,0xFEBB,0xFE8B,0xFDE4,0x003F,0xF9C5,0x0282,0xFFD6,0xFBF7,0x022E,0xFC29,0xFFD5,0x0277,0xFF17,0xFC31,0x02E2,0x0280,0x0081,0x0172,0x04EB,0xFD1E,0xFF3D,0xFAFC,0x003A,0x0001,0xFE5A,0xFFE0,0x09BC,0xFDFC,0x03E2,0xFB66,0x0009,0xFFF3,0xFFA6,0xFF9F,0xFDE6,0xFBDB,0x02FD,0x0458,0x0323,0xFE60,0x03A8,0x03AF,0x001D,0x0063,0x0000,0xFF7A,0x071E,0x032B,0x048C,0x04A4,0xFF63,0xFFA0,0xFE68,0xF344,0x07D0,0xF94C,0xFF8E,0xFE7D,0x0472,0xFE61,0xFE20,0xF9AF,0x0062,0x0106,0xFE4D,0x0019,0x014D,0xF963,0xFED2,0x1380,0x0098,0x0021,0x032E,0xF93A,0xF6CA,0x04FC,0x00B0,0xFFAB,0x03A7,0x0138,0x05A0,0x0162,0x0224,0x03AB,0x04F9,0xF847,0x02BE,0xF610,0xF552,0x0792,0xF5BC,0xF983,0x0009,0x072A,0x067D,0xFC1D,0xFF8C,0x0512,0xFE4D,0xFB70,0xFC70,0xFE3B,0x0222,0x010F,0x01B3,0xF498,0xF78D,0xFA25,0xFC5B,0x0083,0xFCCC,0xFBC3,0xFB8E,0x00FA,0xF8E5,0x0671,0x0311,0xFF01,0xFEE3,0x001C,0x009C,0x00B7,0x002F,0x0142,0x0001,0xFFEB,0x0068,0x03BB,0xFF6C,0xFCCB,0xFF98,0x0349,0x028F,0xFBEA,0x0158,0xFD91,0xFC3C,0x00CB,0xFD7C,0xFDB5,0xF99B,0x0CF1,0xFF68,0x00E8,0xFFA5,0xFEE3,0xFF0D,0x0079,0x0471,0xF854,0xFB8C,0x03D8,0xFFDD,0x07F8,0x0A2E,0x03BC,0x0112,0x01EC,0xFE69,0xFEE7,0x01A7,0xFF1F,0x013D,0xFC52,0xFAF2,0xFFE5,0x0005,0x04E8,0x0310,0x0754,0xFD63,0xFA74,0x02AA,0x0056,0x021D,0x00E8,0x03B0,0xFE62,0x001D,0xFFAA,0xF99F,0xFC47,0xFEB7,0x014F,0x021D,0x038E,0x013A,0xFE89,0x063C,0xFF97,0xFBB9,0xFCED,0x0201,0xFF35,0x00E5,0x0100,0x0064,0x0411,0x08A1,0xFF4A,0x00DC,0xFEC7,0x0C58,0xF7F7,0xF894,0xF4A4,0xFED2,0xFDC9,0x01D6,0x00D0,0x01A8,0xFF6D,0x0696,0xFEB4,0x03AF,0xFF57,0x0602,0x02DB,0x005C,0xFE3B,0xFC95,0x0133,0x0820,0x023C,0x006A,0xFED7,0xFE40,0x03E5,0xFEE4,0x001B,0x05D1,0x0C77,0xFF19,0x0136,0xF96E,0xFC46,0xFF51,0xFE7C,0xFD20,0xFC95,0x0134,0xFFED,0xFF1D,0x094C,0x0043,0xF62B,0xFDC5,0xFA6A,0xFFD1,0xFEC3,0x00DD,0x0037,0xFEE8,0xFE65,0xFF63,0xFFCA,0xF8BC,0x09CB,0xF3BD,0x027C,0x007D,0xFC31,0x01DB,0x0470,0xF58D,0xF7B7,0xFE4C,0x01CA,0xFFAC,0xFEA1,0x015B,0xF8CF,0x0814,0xF1AF,0x01B1,0xFDD2,0x0227,0xFE46,0x07A8,0x006F,0xFFAD,0x00B2,0x08EE,0x00CF,0xF6F9,0xFDA1,0x05BB,0xFAAD,0x01F9,0xFCF3,0x0118,0xFE55,0xFF70,0x01A6,0x037C,0xF273,0xFC60,0xFCB0,0xFBD6,0xF948,0x0A83,0x068C,0x00AE,0xFE91,0x02EE,0xFF91,0xFE1F,0x0159,0x023B,0x012E,0x00FA,0x149D,0x0068,0x001B,0x00F6,0xFC7D,0x01AA,0xFE73,0xFC24,0xFD8B,0xFDAA,0x02AC,0x0296,0x0458,0x0250,0xFFFC,0x12CB,0xFC12,0xF889,0xFA0D,0xF56B,0xF2D2,0xFEA9,0xFBF8,0x01F9,0xFF8F,0x03C8,0xFC02,0x035E,0x0449,0xFF58,0xFF59,0xFEB1,0xF82A,0xF915,0x0086,0x0003,0xFFD4,0xFE9A,0xFA94,0x00F7,0xFE6B,0x01B9,0x0C42,0xFDDF,0xFECB,0x04E7,0x00E2,0x021B,0xFDFB,0x04D3,0x0049,0xFD94,0xFB5D,0x0357,0xFE45,0xFD38,0x0225,0xFD25,0xFE11,0x0201,0x0129,0x04F8,0xFC72,0xFB04,0xFF25,0xFF5D,0x05C4,0x0582,0x0D1B,0xF59C,0x028F,0x0925,0x07D1,0x0083,0x0113,0xF82B,0x043D,0x01F9,0xFAFE,0x0012,0xFE98,0xFED4,0xFF45,0x05A3,0xE9B0,0x0039,0x01BE,0xFF5C,0xFE93,0x00B3,0x03E9,0xFDDA,0x07EC,0xFF55,0x01C9,0x015A,0x03BE,0x046E,0xFE94,0xFF89,0x0073,0x01CD,0xFC72,0xF6A8,0xFC52,0xFC3F,0x0273,0x0052,0xFFB5,0xFEBC,0xFE73,0xFE8A,0xF698,0x02F5,0x02B5,0x0488,0x00F2,0xFB82,0xF8E8,0xFEC2,0xFDA8,0xFF3F,0x02C2,0x1269,0xFF4F,0xFBBF,0x0B20,0xFC6C,0x0510,0xFE94,0x03D3,0x0122,0xFC8B,0xFD4A,0x02BD,0xF55C,0x0676,0xFF18,0x012B,0x00FC,0x00CB,0x002F,0xFE61,0x0A6C,0x0495,0xF897,0xF938,0xFE4F,0x0187,0xFA13,0xFD4F,0xFB8E,0x08AB,0xFBAA,0xFD8C,0xFCDC,0x01B2,0x0777,0x033A};

const q15 ComplexMathsQ15_Reference8_q15[512]={0x0926,0x0136,0x0087,0xFC33,0xFC10,0xFECB,0xFF38,0xFEA6,0x00EE,0xFF9E,0xFB3C,0xFE04,0xFD72,0xFE3D,0x1323,0x0C54,0x128C,0x1D73,0x02A5,0x0266,0x007B,0xFF17,0xD558,0x1A03,0xFDFD,0x056F,0xF69B,0xFA4B,0x04B9,0xFC96,0xFF7D,0x009C,0xFDFB,0x01FC,0x10ED,0xFD07,0x09BE,0x037F,0xFD1C,0xFA11,0x01FA,0xFAA9,0xF8AC,0x028C,0xFC84,0x01D1,0x2794,0x0BD5,0xF59F,0x1395,0xF47C,0xF63D,0xF3E1,0xFACE,0xD769,0xE955,0x0D04,0x1C03,0x04B2,0xF6E8,0xDAB1,0x1924,0xEDC0,0x0449,0x000D,0xFFCB,0x03D8,0x00B0,0x086D,0x077B,0xFC96,0xFE72,0xFFB4,0xFF40,0x00B7,0xFE31,0x06B7,0xF55A,0xF8EB,0x08E8,0x0B89,0x03F6,0xFE20,0xFE9C,0xFEE4,0x0348,0xF451,0x2DD4,0x0AC9,0xF6F9,0xFD62,0x0754,0x0006,0x0039,0x16CE,0x0AF4,0xE5FD,0xF256,0x08D1,0xFB05,0x0332,0x01F9,0xEDE4,0x0379,0xFDCE,0x0232,0x0136,0xF8BB,0xF88C,0xF55C,0x1C00,0xFF3C,0x04A5,0xF634,0x0083,0xFFD6,0xF85B,0xFE0D,0x0080,0x0022,0x0D41,0x3527,0xF211,0xF23D,0x1963,0xF066,0xF8A5,0xED50,0xF561,0x00B0,0x02E1,0xFF8A,0xFF25,0x0D61,0x08E0,0x1131,0xFFFC,0x003E,0x0071,0xFD09,0xFAAA,0xFC3A,0x043A,0xF155,0x041C,0xFEF3,0x02C1,0xFF1E,0xFE71,0xFD6C,0xFFA1,0xFF91,0x0636,0xFEB3,0x0F42,0xFCB4,0xEE3E,0xDDC6,0xF5B8,0xF3A6,0x0C56,0xFDC7,0xFBE1,0xFBDD,0xFEBB,0xF409,0x0084,0xFFE8,0x0392,0xF09E,0x0010,0x01A5,0x052D,0xFD8B,0x033F,0xFC77,0xF0D6,0xF7C2,0x011F,0x0284,0x4A3D,0xE93A,0xEC59,0xE47B,0xFE70,0xFFA7,0x0F25,0x0044,0xF5E8,0x0007,0xF8BF,0xF968,0x1D6F,0x26C5,0x0B7A,0xEA0A,0xFE15,0x06AD,0xFB4F,0x054D,0x092F,0xEC3E,0xF324,0xF245,0xFB5E,0xF338,0xF5B4,0x053A,0xF8F3,0xF822,0x0E57,0xF5AD,0xEED7,0x00C5,0xFCDA,0xFF78,0x0AD1,0xFB69,0x08C7,0xFC63,0x0154,0xFE31,0x0EFA,0x0062,0x09AF,0xFBB4,0x01C3,0x000A,0xFE62,0x025B,0x2211,0x0D05,0xCD8C,0xF14D,0xFA3B,0x0A22,0x15D2,0x0C69,0xF1B9,0x0276,0x0FA4,0xD5E7,0xFDAE,0xFB35,0xFE4A,0x048D,0xF265,0x303D,0xFC71,0xF9BB,0x02A4,0x009B,0x03C7,0x06B4,0xF079,0xF4CA,0xFAF1,0x0721,0xF87F,0x0588,0x008B,0xFDC3,0x1E22,0xFCAC,0xFEAB,0xF1F3,0x0370,0xFFB3,0xF048,0x074B,0x08A4,0x1886,0xF904,0xF979,0xFD7F,0x0377,0x004A,0xFEBB,0x082A,0xFCD3,0x0498,0x1BFC,0x0123,0xFE28,0x13C4,0x06A2,0xE840,0x26E1,0x0172,0xFD9C,0xFEC6,0xFA41,0xFB21,0x018E,0xFAF3,0xFEF5,0xFEED,0xFC3B,0x0502,0xF470,0xF5CC,0x115F,0x0120,0xE9DB,0x00D0,0x0119,0xFED3,0x00FC,0x0FE7,0xFECE,0x2B64,0x0478,0xF4A0,0x0419,0xD76F,0x3C4B,0x07F5,0xE4A5,0x01EB,0xFFC0,0x1895,0xF4DC,0xFEC8,0x00F8,0x0486,0xFFC8,0x0D7A,0x0332,0xFEAD,0xFE54,0x2FEB,0xE365,0xF7C9,0x0207,0x033D,0x056F,0xFF8B,0xFFDB,0x0031,0xFFB6,0xFE56,0x0E27,0xEC6F,0x0689,0x0100,0x0271,0xFF0B,0xF3ED,0xFFAF,0xFFF3,0x0B01,0xEDC6,0x00B4,0x0984,0xFF5B,0x0101,0xFCD8,0x036E,0xF323,0x147D,0xFB79,0x14F7,0xF7FA,0x5457,0x298E,0x120C,0x096A,0xF809,0x0523,0x23F5,0x014A,0x0051,0x1AA5,0xBBA5,0xF0E8,0xFA4A,0x002B,0x0089,0x0E33,0x0D78,0x03B0,0x034A,0xFE82,0xFF73,0x147F,0xFC9E,0x0424,0x1119,0xFA1C,0xFE7F,0xFF9C,0x0186,0xF7BA,0x0504,0x2076,0x0AB4,0xF8D4,0x0B04,0x03D4,0x012F,0xFF95,0xFE00,0x009A,0x0061,0x316B,0xF779,0xFB9A,0x024B,0xFE39,0xF9DB,0x12D9,0xFCB8,0xF808,0xF89F,0x02E0,0x085A,0x1D81,0xF88D,0x049B,0xF6FC,0x3ECF,0xAB2B,0x0639,0xF7F4,0x0FBD,0xE09E,0x0069,0x0027,0x0374,0xF895,0xFB31,0xF604,0xFE32,0xFC7C,0xFFA0,0x1058,0xEF70,0xDB8A,0x0169,0xFF9C,0xF821,0x0561,0x06DB,0x0B58,0x0972,0x0962,0xEB7C,0xFD43,0x019C,0x0363,0xD9D2,0x1EF7,0x0517,0xF3CC,0x0B45,0x02B3,0xE114,0x102A,0x0B22,0x0A2B,0x02EA,0xFE1F,0x16B3,0xFDC3,0x0491,0x1317,0x0A98,0x005F,0x0E8B,0xFBE8,0xFFFE,0x0012,0x006E,0xFE42,0x1357,0xFF54,0x01AA,0xED99,0x078D,0x22E7,0xFA80,0xF528,0x069C,0x112D,0xF471,0xF7E1,0xF832,0xF9B3,0x0485,0xE280,0xFD51,0x02EF,0xFF3F,0x02DD,0xFF2D,0x01CC,0xFC3A,0x0357,0xFF69,0x05F1,0x046F,0x00C5,0xFF52,0xFF12,0xFE4F,0x0136,0xF6BB,0x0FEC,0x02CE,0x009E,0xE34E,0xEBBD};

const q31 ComplexMathsQ15_Reference9_q31[2]={0x00AF430F,0xFD1EC257};

