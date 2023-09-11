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

const q15 FIRQ15_Coefs1_q15[64]={0xE7E1,0xE350,0xF347,0xEC86,0xB036,0xF01A,0xB079,0xAD1A,0xF73E,0xE391,0x0BB0,0x047F,0xE457,0xF2B9,0x8000,0xBB8A,0x4729,0xEB9B,0x9969,0xEFC3,0x0A00,0xDBF0,0xC119,0xDE09,0xDFA1,0xB72D,0xBC93,0x09CE,0x202C,0xDE47,0x54F0,0x196B,0xF513,0x4CAC,0x3CCB,0xCEAB,0xFF5D,0x060A,0xD1E3,0x1F3F,0x2ED5,0x19FD,0xFD56,0x4A67,0xE93B,0xF151,0xEEBF,0x1507,0xB452,0xDC7D,0xFE6C,0xE047,0xBE8E,0x5110,0x2C43,0xFC48,0xDF7B,0x4BAD,0xBAE1,0x2048,0xCC3E,0xB806,0x0B22,0x5677};

const q15 FIRQ15_FirCoefs1_q15[532]={0x4000,0x2000,0x0000,0x4CCD,0x3333,0x199A,0x5555,0x4000,0x2AAB,0x1555,0x0000,0x5B6E,0x4925,0x36DB,0x2492,0x1249,0x6000,0x5000,0x4000,0x3000,0x2000,0x1000,0x0000,0x638E,0x5555,0x471C,0x38E4,0x2AAB,0x1C72,0x0E39,0x6666,0x599A,0x4CCD,0x4000,0x3333,0x2666,0x199A,0x0CCD,0x0000,0x6C4F,0x6276,0x589E,0x4EC5,0x44EC,0x3B14,0x313B,0x2762,0x1D8A,0x13B1,0x09D9,0x0000,0x7685,0x71C7,0x6D09,0x684C,0x638E,0x5ED1,0x5A13,0x5555,0x5098,0x4BDA,0x471C,0x425F,0x3DA1,0x38E4,0x3426,0x2F68,0x2AAB,0x25ED,0x212F,0x1C72,0x17B4,0x12F7,0x0E39,0x097B,0x04BE,0x4000,0x2000,0x0000,0x4CCD,0x3333,0x199A,0x5555,0x4000,0x2AAB,0x1555,0x0000,0x5B6E,0x4925,0x36DB,0x2492,0x1249,0x6000,0x5000,0x4000,0x3000,0x2000,0x1000,0x0000,0x638E,0x5555,0x471C,0x38E4,0x2AAB,0x1C72,0x0E39,0x6666,0x599A,0x4CCD,0x4000,0x3333,0x2666,0x199A,0x0CCD,0x0000,0x6C4F,0x6276,0x589E,0x4EC5,0x44EC,0x3B14,0x313B,0x2762,0x1D8A,0x13B1,0x09D9,0x0000,0x7685,0x71C7,0x6D09,0x684C,0x638E,0x5ED1,0x5A13,0x5555,0x5098,0x4BDA,0x471C,0x425F,0x3DA1,0x38E4,0x3426,0x2F68,0x2AAB,0x25ED,0x212F,0x1C72,0x17B4,0x12F7,0x0E39,0x097B,0x04BE,0x4000,0x2000,0x0000,0x4CCD,0x3333,0x199A,0x5555,0x4000,0x2AAB,0x1555,0x0000,0x5B6E,0x4925,0x36DB,0x2492,0x1249,0x6000,0x5000,0x4000,0x3000,0x2000,0x1000,0x0000,0x638E,0x5555,0x471C,0x38E4,0x2AAB,0x1C72,0x0E39,0x6666,0x599A,0x4CCD,0x4000,0x3333,0x2666,0x199A,0x0CCD,0x0000,0x6C4F,0x6276,0x589E,0x4EC5,0x44EC,0x3B14,0x313B,0x2762,0x1D8A,0x13B1,0x09D9,0x0000,0x7685,0x71C7,0x6D09,0x684C,0x638E,0x5ED1,0x5A13,0x5555,0x5098,0x4BDA,0x471C,0x425F,0x3DA1,0x38E4,0x3426,0x2F68,0x2AAB,0x25ED,0x212F,0x1C72,0x17B4,0x12F7,0x0E39,0x097B,0x04BE,0x4000,0x2000,0x0000,0x4CCD,0x3333,0x199A,0x5555,0x4000,0x2AAB,0x1555,0x0000,0x5B6E,0x4925,0x36DB,0x2492,0x1249,0x6000,0x5000,0x4000,0x3000,0x2000,0x1000,0x0000,0x638E,0x5555,0x471C,0x38E4,0x2AAB,0x1C72,0x0E39,0x6666,0x599A,0x4CCD,0x4000,0x3333,0x2666,0x199A,0x0CCD,0x0000,0x6C4F,0x6276,0x589E,0x4EC5,0x44EC,0x3B14,0x313B,0x2762,0x1D8A,0x13B1,0x09D9,0x0000,0x7685,0x71C7,0x6D09,0x684C,0x638E,0x5ED1,0x5A13,0x5555,0x5098,0x4BDA,0x471C,0x425F,0x3DA1,0x38E4,0x3426,0x2F68,0x2AAB,0x25ED,0x212F,0x1C72,0x17B4,0x12F7,0x0E39,0x097B,0x04BE,0x4000,0x2000,0x0000,0x4CCD,0x3333,0x199A,0x5555,0x4000,0x2AAB,0x1555,0x0000,0x5B6E,0x4925,0x36DB,0x2492,0x1249,0x6000,0x5000,0x4000,0x3000,0x2000,0x1000,0x0000,0x638E,0x5555,0x471C,0x38E4,0x2AAB,0x1C72,0x0E39,0x6666,0x599A,0x4CCD,0x4000,0x3333,0x2666,0x199A,0x0CCD,0x0000,0x6C4F,0x6276,0x589E,0x4EC5,0x44EC,0x3B14,0x313B,0x2762,0x1D8A,0x13B1,0x09D9,0x0000,0x7685,0x71C7,0x6D09,0x684C,0x638E,0x5ED1,0x5A13,0x5555,0x5098,0x4BDA,0x471C,0x425F,0x3DA1,0x38E4,0x3426,0x2F68,0x2AAB,0x25ED,0x212F,0x1C72,0x17B4,0x12F7,0x0E39,0x097B,0x04BE,0x4000,0x2000,0x0000,0x4CCD,0x3333,0x199A,0x5555,0x4000,0x2AAB,0x1555,0x0000,0x5B6E,0x4925,0x36DB,0x2492,0x1249,0x6000,0x5000,0x4000,0x3000,0x2000,0x1000,0x0000,0x638E,0x5555,0x471C,0x38E4,0x2AAB,0x1C72,0x0E39,0x6666,0x599A,0x4CCD,0x4000,0x3333,0x2666,0x199A,0x0CCD,0x0000,0x6C4F,0x6276,0x589E,0x4EC5,0x44EC,0x3B14,0x313B,0x2762,0x1D8A,0x13B1,0x09D9,0x0000,0x7685,0x71C7,0x6D09,0x684C,0x638E,0x5ED1,0x5A13,0x5555,0x5098,0x4BDA,0x471C,0x425F,0x3DA1,0x38E4,0x3426,0x2F68,0x2AAB,0x25ED,0x212F,0x1C72,0x17B4,0x12F7,0x0E39,0x097B,0x04BE,0x4000,0x2000,0x0000,0x4CCD,0x3333,0x199A,0x5555,0x4000,0x2AAB,0x1555,0x0000,0x5B6E,0x4925,0x36DB,0x2492,0x1249,0x6000,0x5000,0x4000,0x3000,0x2000,0x1000,0x0000,0x638E,0x5555,0x471C,0x38E4,0x2AAB,0x1C72,0x0E39,0x6666,0x599A,0x4CCD,0x4000,0x3333,0x2666,0x199A,0x0CCD,0x0000,0x6C4F,0x6276,0x589E,0x4EC5,0x44EC,0x3B14,0x313B,0x2762,0x1D8A,0x13B1,0x09D9,0x0000,0x7685,0x71C7,0x6D09,0x684C,0x638E,0x5ED1,0x5A13,0x5555,0x5098,0x4BDA,0x471C,0x425F,0x3DA1,0x38E4,0x3426,0x2F68,0x2AAB,0x25ED,0x212F,0x1C72,0x17B4,0x12F7,0x0E39,0x097B,0x04BE};

const s16 FIRQ15_FirConfigs1_s16[126]={0x0001,0x0002,0x0001,0x0004,0x0001,0x0004,0x0001,0x0006,0x0001,0x0006,0x0001,0x0008,0x0001,0x0008,0x0001,0x000C,0x0001,0x001A,0x0002,0x0002,0x0002,0x0004,0x0002,0x0004,0x0002,0x0006,0x0002,0x0006,0x0002,0x0008,0x0002,0x0008,0x0002,0x000C,0x0002,0x001A,0x0003,0x0002,0x0003,0x0004,0x0003,0x0004,0x0003,0x0006,0x0003,0x0006,0x0003,0x0008,0x0003,0x0008,0x0003,0x000C,0x0003,0x001A,0x000C,0x0002,0x000C,0x0004,0x000C,0x0004,0x000C,0x0006,0x000C,0x0006,0x000C,0x0008,0x000C,0x0008,0x000C,0x000C,0x000C,0x001A,0x000D,0x0002,0x000D,0x0004,0x000D,0x0004,0x000D,0x0006,0x000D,0x0006,0x000D,0x0008,0x000D,0x0008,0x000D,0x000C,0x000D,0x001A,0x000E,0x0002,0x000E,0x0004,0x000E,0x0004,0x000E,0x0006,0x000E,0x0006,0x000E,0x0008,0x000E,0x0008,0x000E,0x000C,0x000E,0x001A,0x000F,0x0002,0x000F,0x0004,0x000F,0x0004,0x000F,0x0006,0x000F,0x0006,0x000F,0x0008,0x000F,0x0008,0x000F,0x000C,0x000F,0x001A};

const q15 FIRQ15_FirInput1_q15[46]={0xFFC6,0x0251,0x0376,0x02B3,0x0158,0xFE63,0xFCC4,0xFC4D,0xFD55,0xFFED,0x02A3,0x036D,0x033E,0x0147,0xFE71,0xFC4E,0xFC67,0xFD5E,0xFF34,0x02D8,0x0340,0x0362,0x0147,0xFED7,0xFCBD,0xFBF9,0xFDE3,0x0039,0x026F,0x035C,0x035E,0x019A,0xFEE8,0xFCA6,0xFC4C,0xFDB7,0xFFBC,0x0214,0x0371,0x02F5,0x0187,0xFE46,0xFC4E,0xFBBC,0xFE67,0xFFC6};

const q15 FIRQ15_FirRefs1_q15[1080]={0xFFF1,0x0077,0xFFF4,0x005F,0xFFF6,0x004F,0xFFF8,0x0044,0xFFF9,0x003C,0xFFFA,0x0035,0xFFFA,0x0030,0xFFFC,0x0025,0xFFFE,0x0012,0xFFF1,0x0077,0x0206,0x0268,0xFFF4,0x005F,0x017C,0x0351,0xFFF6,0x004F,0x013C,0x029C,0xFFF8,0x0044,0x010F,0x023D,0xFFF9,0x003C,0x00ED,0x01F5,0xFFFA,0x0035,0x00D3,0x01BE,0xFFFA,0x0030,0x00BE,0x0191,0xFFFC,0x0025,0x0092,0x0134,0xFFFE,0x0012,0x0046,0x0095,0xFFF1,0x0077,0x0206,0x0268,0x01B0,0x0045,0xFFF4,0x005F,0x017C,0x0351,0x036D,0x01D6,0xFFF6,0x004F,0x013C,0x029C,0x0466,0x03D6,0xFFF8,0x0044,0x010F,0x023D,0x039C,0x04F2,0xFFF9,0x003C,0x00ED,0x01F5,0x0328,0x0428,0xFFFA,0x0035,0x00D3,0x01BE,0x02CE,0x03B1,0xFFFA,0x0030,0x00BE,0x0191,0x0287,0x0353,0xFFFC,0x0025,0x0092,0x0134,0x01F1,0x028F,0xFFFE,0x0012,0x0046,0x0095,0x00EF,0x013B,0xFFF1,0x0077,0x0206,0x0268,0x01B0,0x0045,0xFE62,0xFD75,0xFD7C,0xFEA6,0x009F,0x022D,0x0286,0x01F1,0x0040,0xFE4C,0xFD41,0xFD8B,0xFE7C,0x0050,0x023C,0x0278,0x0203,0x0059,0xFFF4,0x005F,0x017C,0x0351,0x036D,0x01D6,0xFF84,0xFCFF,0xFC0C,0xFCB3,0xFEE6,0x01B2,0x039A,0x039B,0x0225,0xFF67,0xFCDE,0xFBD1,0xFCA1,0xFEAB,0x014F,0x03AF,0x038F,0x024F,0xFFF6,0x004F,0x013C,0x029C,0x0466,0x03D6,0x0165,0xFE65,0xFBA1,0xFB18,0xFC9E,0xFFA3,0x02F3,0x04C3,0x0412,0x01AA,0xFE3E,0xFB7A,0xFABA,0xFC7E,0xFF56,0x0289,0x04DC,0x0417,0xFFF8,0x0044,0x010F,0x023D,0x039C,0x04F2,0x03AB,0x008D,0xFD37,0xFAA4,0xFACA,0xFD0C,0x00A0,0x0408,0x055F,0x03DF,0x00CF,0xFD09,0xFA5E,0xFA5A,0xFCDC,0x004B,0x0399,0x0589,0xFFF9,0x003C,0x00ED,0x01F5,0x0328,0x0428,0x04F2,0x0314,0xFF96,0xFC52,0xFA3B,0xFAFD,0xFDC6,0x0187,0x04A5,0x055E,0x0346,0xFFD6,0xFC07,0xF9E4,0xFA7B,0xFD8F,0x012C,0x043F,0xFFFA,0x0035,0x00D3,0x01BE,0x02CE,0x03B1,0x0438,0x048A,0x0253,0xFED4,0xFBEB,0xFA4A,0xFB81,0xFE7B,0x020E,0x04B6,0x04F6,0x0284,0xFEFE,0xFB90,0xF9E2,0xFAF4,0xFE3E,0x01BA,0xFFFA,0x0030,0x00BE,0x0191,0x0287,0x0353,0x03CC,0x03E7,0x03F2,0x01B7,0xFE7C,0xFBF0,0xFAAA,0xFC0B,0xFEE4,0x021C,0x0468,0x0460,0x01D5,0xFE9A,0xFB84,0xFA36,0xFB76,0xFEAD,0xFFFC,0x0025,0x0092,0x0134,0x01F1,0x028F,0x02EC,0x0301,0x02E1,0x02BF,0x02D2,0x035E,0x01D5,0xFF28,0xFCCD,0xFB35,0xFBF6,0xFE22,0x00EC,0x0343,0x03A9,0x01D3,0xFF28,0xFC4E,0xFFFE,0x0012,0x0046,0x0095,0x00EF,0x013B,0x0168,0x0172,0x0163,0x0153,0x015C,0x0185,0x01CD,0x0221,0x0267,0x0289,0x028A,0x0271,0x0251,0x024C,0x0265,0x029F,0x02E5,0x031F,0xFFF1,0x0077,0x0206,0x0268,0x01B0,0x0045,0xFE62,0xFD75,0xFD7C,0xFEA6,0x009F,0x022D,0x0286,0x01F1,0x0040,0xFE4C,0xFD41,0xFD8B,0xFE7C,0x0050,0x023C,0x0278,0x0203,0x0059,0xFE9B,0xFD5D,0xFFF4,0x005F,0x017C,0x0351,0x036D,0x01D6,0xFF84,0xFCFF,0xFC0C,0xFCB3,0xFEE6,0x01B2,0x039A,0x039B,0x0225,0xFF67,0xFCDE,0xFBD1,0xFCA1,0xFEAB,0x014F,0x03AF,0x038F,0x024F,0xFFA7,0xFD32,0xFFF6,0x004F,0x013C,0x029C,0x0466,0x03D6,0x0165,0xFE65,0xFBA1,0xFB18,0xFC9E,0xFFA3,0x02F3,0x04C3,0x0412,0x01AA,0xFE3E,0xFB7A,0xFABA,0xFC7E,0xFF56,0x0289,0x04DC,0x0417,0x01F7,0xFE84,0xFFF8,0x0044,0x010F,0x023D,0x039C,0x04F2,0x03AB,0x008D,0xFD37,0xFAA4,0xFACA,0xFD0C,0x00A0,0x0408,0x055F,0x03DF,0x00CF,0xFD09,0xFA5E,0xFA5A,0xFCDC,0x004B,0x0399,0x0589,0x0401,0x0124,0xFFF9,0x003C,0x00ED,0x01F5,0x0328,0x0428,0x04F2,0x0314,0xFF96,0xFC52,0xFA3B,0xFAFD,0xFDC6,0x0187,0x04A5,0x055E,0x0346,0xFFD6,0xFC07,0xF9E4,0xFA7B,0xFD8F,0x012C,0x043F,0x05A3,0x0370,0xFFFA,0x0035,0x00D3,0x01BE,0x02CE,0x03B1,0x0438,0x048A,0x0253,0xFED4,0xFBEB,0xFA4A,0xFB81,0xFE7B,0x020E,0x04B6,0x04F6,0x0284,0xFEFE,0xFB90,0xF9E2,0xFAF4,0xFE3E,0x01BA,0x0464,0x0544,0xFFFA,0x0030,0x00BE,0x0191,0x0287,0x0353,0x03CC,0x03E7,0x03F2,0x01B7,0xFE7C,0xFBF0,0xFAAA,0xFC0B,0xFEE4,0x021C,0x0468,0x0460,0x01D5,0xFE9A,0xFB84,0xFA36,0xFB76,0xFEAD,0x01D8,0x041A,0xFFFC,0x0025,0x0092,0x0134,0x01F1,0x028F,0x02EC,0x0301,0x02E1,0x02BF,0x02D2,0x035E,0x01D5,0xFF28,0xFCCD,0xFB35,0xFBF6,0xFE22,0x00EC,0x0343,0x03A9,0x01D3,0xFF28,0xFC4E,0xFAC4,0xFB70,0xFFFE,0x0012,0x0046,0x0095,0x00EF,0x013B,0x0168,0x0172,0x0163,0x0153,0x015C,0x0185,0x01CD,0x0221,0x0267,0x0289,0x028A,0x0271,0x0251,0x024C,0x0265,0x029F,0x02E5,0x031F,0x033B,0x0369,0xFFF1,0x0077,0x0206,0x0268,0x01B0,0x0045,0xFE62,0xFD75,0xFD7C,0xFEA6,0x009F,0x022D,0x0286,0x01F1,0x0040,0xFE4C,0xFD41,0xFD8B,0xFE7C,0x0050,0x023C,0x0278,0x0203,0x0059,0xFE9B,0xFD5D,0xFD76,0xFF00,0xFFF4,0x005F,0x017C,0x0351,0x036D,0x01D6,0xFF84,0xFCFF,0xFC0C,0xFCB3,0xFEE6,0x01B2,0x039A,0x039B,0x0225,0xFF67,0xFCDE,0xFBD1,0xFCA1,0xFEAB,0x014F,0x03AF,0x038F,0x024F,0xFFA7,0xFD32,0xFC03,0xFCC9,0xFFF6,0x004F,0x013C,0x029C,0x0466,0x03D6,0x0165,0xFE65,0xFBA1,0xFB18,0xFC9E,0xFFA3,0x02F3,0x04C3,0x0412,0x01AA,0xFE3E,0xFB7A,0xFABA,0xFC7E,0xFF56,0x0289,0x04DC,0x0417,0x01F7,0xFE84,0xFBE7,0xFB25,0xFFF8,0x0044,0x010F,0x023D,0x039C,0x04F2,0x03AB,0x008D,0xFD37,0xFAA4,0xFACA,0xFD0C,0x00A0,0x0408,0x055F,0x03DF,0x00CF,0xFD09,0xFA5E,0xFA5A,0xFCDC,0x004B,0x0399,0x0589,0x0401,0x0124,0xFD67,0xFB03,0xFFF9,0x003C,0x00ED,0x01F5,0x0328,0x0428,0x04F2,0x0314,0xFF96,0xFC52,0xFA3B,0xFAFD,0xFDC6,0x0187,0x04A5,0x055E,0x0346,0xFFD6,0xFC07,0xF9E4,0xFA7B,0xFD8F,0x012C,0x043F,0x05A3,0x0370,0x0043,0xFC98,0xFFFA,0x0035,0x00D3,0x01BE,0x02CE,0x03B1,0x0438,0x048A,0x0253,0xFED4,0xFBEB,0xFA4A,0xFB81,0xFE7B,0x020E,0x04B6,0x04F6,0x0284,0xFEFE,0xFB90,0xF9E2,0xFAF4,0xFE3E,0x01BA,0x0464,0x0544,0x02C3,0xFF9A,0xFFFA,0x0030,0x00BE,0x0191,0x0287,0x0353,0x03CC,0x03E7,0x03F2,0x01B7,0xFE7C,0xFBF0,0xFAAA,0xFC0B,0xFEE4,0x021C,0x0468,0x0460,0x01D5,0xFE9A,0xFB84,0xFA36,0xFB76,0xFEAD,0x01D8,0x041A,0x04C2,0x023E,0xFFFC,0x0025,0x0092,0x0134,0x01F1,0x028F,0x02EC,0x0301,0x02E1,0x02BF,0x02D2,0x035E,0x01D5,0xFF28,0xFCCD,0xFB35,0xFBF6,0xFE22,0x00EC,0x0343,0x03A9,0x01D3,0xFF28,0xFC4E,0xFAC4,0xFB70,0xFE0A,0x00DA,0xFFFE,0x0012,0x0046,0x0095,0x00EF,0x013B,0x0168,0x0172,0x0163,0x0153,0x015C,0x0185,0x01CD,0x0221,0x0267,0x0289,0x028A,0x0271,0x0251,0x024C,0x0265,0x029F,0x02E5,0x031F,0x033B,0x0369,0x0112,0xFD8C,0xFFF1,0x0077,0x0206,0x0268,0x01B0,0x0045,0xFE62,0xFD75,0xFD7C,0xFEA6,0x009F,0x022D,0x0286,0x01F1,0x0040,0xFE4C,0xFD41,0xFD8B,0xFE7C,0x0050,0x023C,0x0278,0x0203,0x0059,0xFE9B,0xFD5D,0xFD76,0xFF00,0x00B8,0x020E,0xFFF4,0x005F,0x017C,0x0351,0x036D,0x01D6,0xFF84,0xFCFF,0xFC0C,0xFCB3,0xFEE6,0x01B2,0x039A,0x039B,0x0225,0xFF67,0xFCDE,0xFBD1,0xFCA1,0xFEAB,0x014F,0x03AF,0x038F,0x024F,0xFFA7,0xFD32,0xFC03,0xFCC9,0xFF4F,0x01C7,0xFFF6,0x004F,0x013C,0x029C,0x0466,0x03D6,0x0165,0xFE65,0xFBA1,0xFB18,0xFC9E,0xFFA3,0x02F3,0x04C3,0x0412,0x01AA,0xFE3E,0xFB7A,0xFABA,0xFC7E,0xFF56,0x0289,0x04DC,0x0417,0x01F7,0xFE84,0xFBE7,0xFB25,0xFCBE,0x0013,0xFFF8,0x0044,0x010F,0x023D,0x039C,0x04F2,0x03AB,0x008D,0xFD37,0xFAA4,0xFACA,0xFD0C,0x00A0,0x0408,0x055F,0x03DF,0x00CF,0xFD09,0xFA5E,0xFA5A,0xFCDC,0x004B,0x0399,0x0589,0x0401,0x0124,0xFD67,0xFB03,0xFAE0,0xFD30,0xFFF9,0x003C,0x00ED,0x01F5,0x0328,0x0428,0x04F2,0x0314,0xFF96,0xFC52,0xFA3B,0xFAFD,0xFDC6,0x0187,0x04A5,0x055E,0x0346,0xFFD6,0xFC07,0xF9E4,0xFA7B,0xFD8F,0x012C,0x043F,0x05A3,0x0370,0x0043,0xFC98,0xFAA6,0xFB18,0xFFFA,0x0035,0x00D3,0x01BE,0x02CE,0x03B1,0x0438,0x048A,0x0253,0xFED4,0xFBEB,0xFA4A,0xFB81,0xFE7B,0x020E,0x04B6,0x04F6,0x0284,0xFEFE,0xFB90,0xF9E2,0xFAF4,0xFE3E,0x01BA,0x0464,0x0544,0x02C3,0xFF9A,0xFC3D,0xFABD,0xFFFA,0x0030,0x00BE,0x0191,0x0287,0x0353,0x03CC,0x03E7,0x03F2,0x01B7,0xFE7C,0xFBF0,0xFAAA,0xFC0B,0xFEE4,0x021C,0x0468,0x0460,0x01D5,0xFE9A,0xFB84,0xFA36,0xFB76,0xFEAD,0x01D8,0x041A,0x04C2,0x023E,0xFF51,0xFC49,0xFFFC,0x0025,0x0092,0x0134,0x01F1,0x028F,0x02EC,0x0301,0x02E1,0x02BF,0x02D2,0x035E,0x01D5,0xFF28,0xFCCD,0xFB35,0xFBF6,0xFE22,0x00EC,0x0343,0x03A9,0x01D3,0xFF28,0xFC4E,0xFAC4,0xFB70,0xFE0A,0x00DA,0x033D,0x0464,0xFFFE,0x0012,0x0046,0x0095,0x00EF,0x013B,0x0168,0x0172,0x0163,0x0153,0x015C,0x0185,0x01CD,0x0221,0x0267,0x0289,0x028A,0x0271,0x0251,0x024C,0x0265,0x029F,0x02E5,0x031F,0x033B,0x0369,0x0112,0xFD8C,0xFAB9,0xF93A};

const q15 FIRQ15_Refs1_q15[256]={0xE15F,0x0C92,0x0C84,0x12AE,0x0593,0x50F5,0xCDED,0x1880,0xCAD9,0xEE6E,0xE44C,0xD6F7,0x1A30,0x1BB4,0xC255,0x17ED,0x22D6,0xECB8,0xC07E,0x3832,0x195C,0xA1D7,0x0445,0x15B7,0x1CA3,0x2243,0xBBDC,0x04C0,0x3247,0xCAAC,0x05F5,0xAA86,0x0C8B,0x2B43,0xFC43,0x1BA4,0x04DB,0x06FE,0x06E2,0xB449,0x3AB2,0x8BC8,0xF8E2,0x3412,0xC1BF,0x2645,0x0907,0xE977,0xD799,0xB90C,0x409E,0x2A87,0x31EB,0xF2A7,0xA2B9,0x0422,0x3B19,0xD626,0x2C12,0xE7C6,0x2AB6,0x14C8,0x1E4D,0x1342,0xD7EA,0xCB9B,0x2C6E,0x9F12,0x2677,0xD5B6,0x0FD2,0xDF3D,0x3E4B,0x0BC6,0x0D70,0xC263,0x410C,0xF189,0x1636,0x546E,0xD7D7,0xFCBA,0xCD18,0xC8CB,0x22DE,0xCCD4,0x0088,0xA222,0xE602,0xC965,0x4DB0,0x28F2,0xCAFA,0x19F0,0xE2CB,0xDEEE,0x11DB,0x250D,0xFE47,0xBFCB,0x9B6B,0xCFAF,0xC121,0x2341,0xF917,0x06C5,0x20DC,0x17B1,0x029A,0xD2F7,0x3AC4,0xCCDA,0x22B2,0x14B9,0x1C22,0x02CA,0x2812,0xE49D,0x387B,0xEFEB,0x07FE,0xFB0C,0x0EFE,0xFA4C,0xCBAD,0x2AA8,0xE59E,0x8C76,0xEC35,0x261F,0x4742,0xC7D0,0x0C89,0xF7F0,0x0CD6,0x1FA0,0x2DF2,0xB55B,0xE84A,0x1134,0xD9E3,0x2A6D,0x02CF,0x5E4E,0x26CC,0xD0B4,0xE63A,0xF5A0,0x0778,0x1B3A,0x2E72,0x207E,0x2B39,0x1DF7,0xE8B5,0x8000,0xD25B,0x62F9,0x1E9D,0x1714,0xF706,0x0E51,0xE372,0xF773,0x1E43,0x078F,0x1C3F,0xDF16,0x118A,0xFC68,0xEA25,0xE09D,0xF655,0x2AE9,0xECD0,0xE6FA,0xD010,0xE5B7,0x00F0,0x04CF,0x30D1,0x13E7,0xD29B,0x031A,0xFFF3,0xFC62,0x52C5,0x094C,0xF8BB,0xF40B,0xD672,0xF734,0x4079,0x1271,0xF7D8,0xF046,0xFF3E,0x1813,0xFA97,0x01B7,0x265C,0xEF14,0x381E,0xF8DE,0x1D9A,0xD5C7,0xBD6A,0x5218,0xFBF7,0xE624,0x13D4,0xF9FE,0xEEF0,0x13F1,0x23A1,0xCA61,0xF1B5,0xCF79,0xD29E,0x262B,0x1ED1,0xFF05,0x17B3,0x2C9F,0xF680,0x34FB,0x12D9,0x136E,0xC2C4,0xF595,0xC463,0xF1A5,0x4647,0xC7AA,0xE76E,0x1711,0xE9CB,0xD11A,0x194E,0xFE3F,0xF126,0xFD59,0xA3D8,0xACF7,0xB71C,0x3168,0xC3F6,0xF6E6,0xE1CE,0xFE09,0x075A,0xE733,0xF094,0xD8A3,0xD41A,0xE007};

const q15 FIRQ15_Samples1_q15[256]={0x000C,0xE683,0x282B,0xFB9A,0xD9F7,0xDB92,0xA944,0xC84A,0x264E,0x2D80,0xE00B,0x0115,0xBCC6,0x52AE,0x0208,0x3A91,0x0291,0x0681,0xBE70,0x0C63,0x57C0,0xC1FA,0xD0D7,0xF039,0xE7EE,0xD773,0xDD9E,0xF301,0x6847,0x0965,0x213A,0xF6EF,0xDC4A,0xFB4D,0x2915,0xE189,0x36A4,0xF0D8,0x42E5,0x0659,0x35A9,0xF979,0x4947,0xC971,0x173B,0xF825,0xFE65,0x1D3E,0xD3ED,0xEC80,0xC6A4,0xCD51,0xEDBC,0xF918,0xFC62,0x16E7,0x7391,0xE563,0x1261,0x3D72,0xC4EC,0x4049,0x2CC3,0x8E72,0x1371,0xD4F5,0x1A15,0x2533,0xF2F3,0x20BD,0x2E5A,0x3FF7,0x3C60,0x1799,0xE450,0xE7C6,0x0CB5,0x22E5,0x0AD5,0xFFBB,0xCA0B,0xDDFF,0xFD9D,0xE913,0xFB6D,0xBD63,0x6B66,0xE577,0xD95A,0xABF7,0xAEB3,0xE7C4,0x25CA,0xF90E,0x2B67,0xABEE,0x5CA6,0x3C57,0xCDAC,0xEF86,0xB05B,0x1B20,0x4D4D,0x53A6,0xB9D2,0x167D,0x3394,0x0109,0xFF4E,0x1465,0xEC74,0x145B,0x5912,0x264A,0xD847,0xD496,0x0580,0x2A03,0xC847,0xB79A,0x33D7,0xC5B1,0x27F0,0xE34F,0xD4D0,0xC76E,0x397D,0x2758,0xD4A0,0xF0D3,0x1E36,0x2FDD,0xFA00,0xFDB7,0xE499,0x12C7,0x0C4A,0x1961,0x25C2,0x0B31,0x351C,0x1775,0x36A7,0x140A,0x1484,0x3360,0x2148,0x1C61,0x7AF7,0xC232,0xF018,0x9FDD,0x4254,0xFD5C,0xCD29,0x1DED,0xF535,0x740D,0xC069,0x279A,0xF2B9,0x200B,0xCD07,0x10AA,0x0DDD,0x0869,0xCB21,0x436C,0x2A68,0xE539,0xF56A,0x1119,0x1973,0xD103,0x15B0,0xDFE7,0x02CB,0xEBEE,0x483B,0x38FC,0xF1E8,0x1AB0,0x29D7,0x0E21,0xA91F,0xF3BA,0xFE5A,0x12E8,0xE45B,0xDB44,0xA768,0x2DF7,0xC306,0x372F,0xE5BC,0x336C,0xE573,0x1761,0xF81A,0xE569,0xF0CD,0xF462,0x8000,0xED69,0x9ED7,0x365F,0xF50E,0xD0A0,0x28C6,0xEF7C,0x2865,0xFD80,0xF9A4,0xD57D,0xFCF4,0x00B8,0x0927,0x4C47,0x129C,0xC1FF,0x0EF3,0xD0F2,0x0ADE,0x2686,0xC173,0x0AD3,0x0346,0x1798,0xF695,0xD1CA,0xDDA6,0x2841,0xE66F,0x16B9,0xDAF9,0x208D,0xCBF2,0xBDD0,0xA4F7,0x21CE,0xEEE4,0x0957,0x1B81,0x2C47,0xBB34,0x1ACF,0xE9E2,0xC0AC,0xFDF2,0x06E1,0xC5DF,0x4559,0xBB48,0xEB0C,0xEA29,0x1D8E};
