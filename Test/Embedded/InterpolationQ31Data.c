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

const s16 InterpolationQ31_Config2_s16[2]={0x0007,0x0008};

const q31 InterpolationQ31_Input1_q31[42]={0xFFF1999A,0x0001999A,0x0011999A,0x0021999A,0x0031999A,0x0041999A,0x0051999A,0x0061999A,0x0071999A,0x0081999A,0x0091999A,0x00A1999A,0x00B1999A,0x00C1999A,0x00D1999A,0x00E1999A,0x00F1999A,0x0101999A,0x0111999A,0x0121999A,0x0131999A,0x0141999A,0x0151999A,0x0161999A,0x0171999A,0x0181999A,0x0191999A,0x01A1999A,0x01B1999A,0x01C1999A,0x01D1999A,0x01E1999A,0x01F1999A,0x0201999A,0x0211999A,0x0221999A,0x0231999A,0x0241999A,0x0251999A,0x0261999A,0x0271999A,0x0289999A};

const q31 InterpolationQ31_Input2_q31[300]={0x00080000,0x00080000,0x000F1C72,0x00080000,0x001638E4,0x00080000,0x001D5555,0x00080000,0x002471C7,0x00080000,0x002B8E39,0x00080000,0x0032AAAB,0x00080000,0x0039C71C,0x00080000,0x0040E38E,0x00080000,0x00480000,0x00080000,0x00080000,0x000DB6DB,0x000F1C72,0x000DB6DB,0x001638E4,0x000DB6DB,0x001D5555,0x000DB6DB,0x002471C7,0x000DB6DB,0x002B8E39,0x000DB6DB,0x0032AAAB,0x000DB6DB,0x0039C71C,0x000DB6DB,0x0040E38E,0x000DB6DB,0x00480000,0x000DB6DB,0x00080000,0x00136DB7,0x000F1C72,0x00136DB7,0x001638E4,0x00136DB7,0x001D5555,0x00136DB7,0x002471C7,0x00136DB7,0x002B8E39,0x00136DB7,0x0032AAAB,0x00136DB7,0x0039C71C,0x00136DB7,0x0040E38E,0x00136DB7,0x00480000,0x00136DB7,0x00080000,0x00192492,0x000F1C72,0x00192492,0x001638E4,0x00192492,0x001D5555,0x00192492,0x002471C7,0x00192492,0x002B8E39,0x00192492,0x0032AAAB,0x00192492,0x0039C71C,0x00192492,0x0040E38E,0x00192492,0x00480000,0x00192492,0x00080000,0x001EDB6E,0x000F1C72,0x001EDB6E,0x001638E4,0x001EDB6E,0x001D5555,0x001EDB6E,0x002471C7,0x001EDB6E,0x002B8E39,0x001EDB6E,0x0032AAAB,0x001EDB6E,0x0039C71C,0x001EDB6E,0x0040E38E,0x001EDB6E,0x00480000,0x001EDB6E,0x00080000,0x00249249,0x000F1C72,0x00249249,0x001638E4,0x00249249,0x001D5555,0x00249249,0x002471C7,0x00249249,0x002B8E39,0x00249249,0x0032AAAB,0x00249249,0x0039C71C,0x00249249,0x0040E38E,0x00249249,0x00480000,0x00249249,0x00080000,0x002A4925,0x000F1C72,0x002A4925,0x001638E4,0x002A4925,0x001D5555,0x002A4925,0x002471C7,0x002A4925,0x002B8E39,0x002A4925,0x0032AAAB,0x002A4925,0x0039C71C,0x002A4925,0x0040E38E,0x002A4925,0x00480000,0x002A4925,0x00080000,0x00300000,0x000F1C72,0x00300000,0x001638E4,0x00300000,0x001D5555,0x00300000,0x002471C7,0x00300000,0x002B8E39,0x00300000,0x0032AAAB,0x00300000,0x0039C71C,0x00300000,0x0040E38E,0x00300000,0x00480000,0x00300000,0x00080000,0x0035B6DB,0x000F1C72,0x0035B6DB,0x001638E4,0x0035B6DB,0x001D5555,0x0035B6DB,0x002471C7,0x0035B6DB,0x002B8E39,0x0035B6DB,0x0032AAAB,0x0035B6DB,0x0039C71C,0x0035B6DB,0x0040E38E,0x0035B6DB,0x00480000,0x0035B6DB,0x00080000,0x003B6DB7,0x000F1C72,0x003B6DB7,0x001638E4,0x003B6DB7,0x001D5555,0x003B6DB7,0x002471C7,0x003B6DB7,0x002B8E39,0x003B6DB7,0x0032AAAB,0x003B6DB7,0x0039C71C,0x003B6DB7,0x0040E38E,0x003B6DB7,0x00480000,0x003B6DB7,0x00080000,0x00412492,0x000F1C72,0x00412492,0x001638E4,0x00412492,0x001D5555,0x00412492,0x002471C7,0x00412492,0x002B8E39,0x00412492,0x0032AAAB,0x00412492,0x0039C71C,0x00412492,0x0040E38E,0x00412492,0x00480000,0x00412492,0x00080000,0x0046DB6E,0x000F1C72,0x0046DB6E,0x001638E4,0x0046DB6E,0x001D5555,0x0046DB6E,0x002471C7,0x0046DB6E,0x002B8E39,0x0046DB6E,0x0032AAAB,0x0046DB6E,0x0039C71C,0x0046DB6E,0x0040E38E,0x0046DB6E,0x00480000,0x0046DB6E,0x00080000,0x004C9249,0x000F1C72,0x004C9249,0x001638E4,0x004C9249,0x001D5555,0x004C9249,0x002471C7,0x004C9249,0x002B8E39,0x004C9249,0x0032AAAB,0x004C9249,0x0039C71C,0x004C9249,0x0040E38E,0x004C9249,0x00480000,0x004C9249,0x00080000,0x00524925,0x000F1C72,0x00524925,0x001638E4,0x00524925,0x001D5555,0x00524925,0x002471C7,0x00524925,0x002B8E39,0x00524925,0x0032AAAB,0x00524925,0x0039C71C,0x00524925,0x0040E38E,0x00524925,0x00480000,0x00524925,0x00080000,0x00580000,0x000F1C72,0x00580000,0x001638E4,0x00580000,0x001D5555,0x00580000,0x002471C7,0x00580000,0x002B8E39,0x00580000,0x0032AAAB,0x00580000,0x0039C71C,0x00580000,0x0040E38E,0x00580000,0x00480000,0x00580000};

const q31 InterpolationQ31_InputX3_q31[4]={0x00000000,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF};

const q31 InterpolationQ31_InputX4_q31[9]={0x00000000,0x6487ED51,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF};

const q31 InterpolationQ31_InputX5_q31[3]={0x00000000,0x7FFFFFFF,0x7FFFFFFF};

const q31 InterpolationQ31_InputY3_q31[4]={0x00000000,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF};

const q31 InterpolationQ31_InputY4_q31[9]={0x00000000,0x5A82799A,0x7FFFFFFF,0x5A82799A,0x00000000,0xA57D8666,0x80000000,0xA57D8666,0x00000000};

const q31 InterpolationQ31_InputY5_q31[3]={0x00000000,0x7FFFFFFF,0x7FFFFFFF};

const q31 InterpolationQ31_OutputX3_q31[20]={0x00000000,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF};

const q31 InterpolationQ31_OutputX4_q31[33]={0x00000000,0x1921FB54,0x3243F6A9,0x4B65F1FD,0x6487ED51,0x7DA9E8A5,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF};

const q31 InterpolationQ31_OutputX5_q31[30]={0x80000000,0x80000000,0x80000000,0x80000000,0x80000000,0x80000000,0x80000000,0x80000000,0x80000000,0x80000000,0x00000000,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF};

const q31 InterpolationQ31_Reference1_q31[42]={0x7FFFFFFF,0x7FFEEC41,0x7FE51603,0x7F0E27D5,0x7BE24BEE,0x73E64706,0x640DCF94,0x497760C6,0x22B9B470,0xF1B5FC22,0xBD6D7243,0x92B0EBC0,0x81FAEE5C,0x99187FD8,0xD950BCDB,0x2EA54B2D,0x709D80C5,0x742DF182,0x2BD88AB9,0xC0E36E27,0x85CE5589,0xB652E06F,0x3004F60D,0x78BD443E,0x36E66FB3,0xAFC76E4A,0x93432DD9,0x12ED0456,0x75C739B9,0x18587B95,0x912D9338,0xD592F709,0x6B1604B4,0x25CA987D,0x913D5412,0xF5732A11,0x701AF303,0xD9380158,0xA77F4E37,0x5D75DFEE,0x1222B240,0x822EC32F};

const q31 InterpolationQ31_Reference2_q31[150]={0x2FCB0F88,0x1A16C2AC,0x017C833A,0xE87845B3,0xD3D2EED8,0xC1CCEF31,0xB83733DD,0xBCB1EA6A,0xC83D2221,0x053BE205,0x035B21B5,0xD666F6E5,0xF048ED35,0x14497A8B,0x00913226,0xCB6A031F,0xB470E5F7,0xCFC49141,0xEC9742BC,0x13E31F8D,0xF8A7A363,0xD99685C2,0xF33D8270,0x14FECC06,0x09B21CC9,0xE35D0B74,0xD32BF4FB,0xE7E1809B,0xFC4BEB7E,0x0EA8713A,0x0471C4BD,0x0C05A661,0x03A23481,0xF8F6DB44,0xFB14CC50,0x04DEB6B9,0x08E7EC9D,0x035AA04C,0xFE3CEF04,0xFC2C7AFF,0x103BE617,0x3E74C701,0x1406E691,0xDCEEEA82,0xEC777BD6,0x266061FE,0x3EA3E43F,0x1ED3BFFC,0x002DF28A,0xE9B084C4,0xED55886A,0x12840F65,0x09E01CC3,0xFAB061E7,0x0ED3FA80,0x382991F9,0x4AA525F8,0x370AB42C,0x2004B661,0xF10DE49F,0xBEC30AFC,0xCEFB61BB,0xF91673FE,0x26E43354,0x3D6EECF2,0x4604A321,0x4C37BA38,0x4E711D7B,0x4754EA4D,0xFEE199FF,0x90308D8E,0x8B72B411,0xE84CCB39,0x531804C2,0x6C09DF64,0x53DFB449,0x4DCA4E78,0x65D786CB,0x6EA51E38,0x0CB54F60,0x97C08C60,0x892E49BD,0xE634A36F,0x5299EEE4,0x6596B887,0x42EE6778,0x380C12F6,0x54C90E09,0x638A46A1,0x10692DE3,0x9F508B32,0x86E9DF69,0xE41C7BA5,0x521BD906,0x5F2391A9,0x31FD1AA8,0x224DD775,0x43BA9547,0x586F6F0B,0x141D0C66,0xA3DDC486,0x865103F0,0xE3215A99,0x516CB494,0x5B312F6C,0x28A4BDFA,0x1676B480,0x3A3B5850,0x52067F52,0x15FF3CB7,0x9C5FE7E5,0x8C6663E4,0xE69A5488,0x4FF955D6,0x6141DFAE,0x3DB021D9,0x323BF3BD,0x4EF90A80,0x5E652F11,0x109AB43F,0x94E20B45,0x927BC3D8,0xEA134E76,0x4E85F717,0x67528FF0,0x52BB85B7,0x4E0132F9,0x63B6BCB1,0x6AC3DED1,0x0B362BC6,0xA8B7FD23,0xB44DF11B,0xF311567A,0x39245E56,0x530BA1EE,0x52723C90,0x558BFD12,0x5ED05209,0x5BD34840,0x030CA73D,0xE58BA4C2,0xFFBB5254,0x0456F39C,0x05DD6E91,0x17414685,0x3229EFDF,0x3EBF1776,0x3373BC1C,0x23EBC839,0xF6BBA89A};

const q31 InterpolationQ31_Reference3_q31[20]={0x00000000,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF};

const q31 InterpolationQ31_Reference4_q31[33]={0x00000000,0x18EC2D0B,0x30ED543B,0x47186FB4,0x5A82799A,0x6A575E21,0x761ED1B7,0x7D777AD8,0x7FFFFFFF,0x7D777AD8,0x761ED1B7,0x6A575E21,0x5A82799A,0x47186FB4,0x30ED543B,0x18EC2D0B,0x00000000,0xE713D2F5,0xCF12ABC5,0xB8E7904C,0xA57D8666,0x95A8A1DF,0x89E12E49,0x82888528,0x80000000,0x82888528,0x89E12E49,0x95A8A1DF,0xA57D8666,0xB8E7904C,0xCF12ABC5,0xE713D2F5,0x00000000};

const q31 InterpolationQ31_Reference5_q31[30]={0x80000000,0x80000000,0x80000000,0x80000000,0x80000000,0x80000000,0x80000000,0x80000000,0x80000000,0x80000000,0x00000000,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF};

const q31 InterpolationQ31_YVals1_q31[41]={0x7FFFFFFF,0x7FF53A8E,0x7F53CD1F,0x7C9B5835,0x7560DD71,0x6696FD43,0x4D3B346F,0x2794EFD3,0xF7049DF8,0xC1F24B95,0x94C1CE62,0x8018F412,0x92ECBAF9,0xD0A26BAC,0x27719787,0x6F769C05,0x7AFB8B87,0x36F38755,0xC7E5A942,0x81CF5A32,0xA9C52B9A,0x274E3BE8,0x7E71815B,0x45671E38,0xB4604D03,0x866799C7,0x06FB627E,0x7E6BB4F4,0x27FEE4A7,0x8B7EC9ED,0xC452A6DC,0x70D5C8A0,0x37582165,0x87D0C855,0xE60E3DB9,0x7FFF7927,0xE1123BC0,0x928BF3B1,0x640D7CEB,0x22215B09,0x822EC32F};

const q31 InterpolationQ31_YVals2_q31[56]={0x61CE022E,0x7A34B6CC,0x81B5AD59,0xC7D0B690,0x89EC9B27,0x5783AFCB,0xA3428493,0x2E9DC9D1,0xB48BBB55,0x3C77AFE8,0xA541A842,0xF74DF921,0x3C3143FF,0x716B3B02,0xD5E59CB2,0x4F497006,0xBF55C93A,0x574959F7,0x03E3C0CF,0xC8187FD4,0x8C6E6F06,0x9586223C,0x8ADAF8E1,0x7B243A55,0x44C55958,0x7AE31813,0x9E8786AD,0x5238F619,0xC9A99D57,0x811110C2,0x7B71C31F,0x02F8263F,0x569C6317,0xD78A4CED,0x792034A4,0x89EC9B27,0x96DA0C3B,0x72368FED,0x581B91CE,0x7F76A2DC,0x907D10ED,0x3DFDF962,0x063F67D2,0x6F2883D2,0x9AA9296C,0x2DDB21A1,0xD3ACF57E,0xF74DF921,0x803BB3D3,0xE62A1730,0x886751E7,0x7028D0B3,0xE51192FB,0x3E43C8D8,0xF4F3A57B,0x7F6F3C60};
