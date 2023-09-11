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

const u64 BIQUADF64_AllBiquadCoefs2_f64[150]={0x3f947ae147ae147b,0x3f9995aebc73cbe3,0x3f947ae147ae147b,0x3ff2db6f78b33348,0xbfd6bb5a2b3b3977,0x3f947ae147ae147b,0x3f9007fdbcc2b9ec,0x3f947ae147ae147b,0x3fc5e58c6620ffb6,0xbfa0d826829ac3b4,0x3f947ae147ae147b,0xbf6b9a2f5e019e7f,0x3f947ae147ae147b,0x3fc15e2beced748c,0xbf72ecb758b3c945,0x3f947ae147ae147b,0xbfa07617a3a1d28a,0x3f947ae147ae147b,0xbfd2ccc6f59229c0,0xbf96c6523f98501c,0x3ff0000000000000,0xbff65117cd218cac,0x3ff0000000000000,0xbfd15213e91d8239,0xbfa0a85b3ffd1162,0x3ff0000000000000,0x3fd5d0d7168642e3,0x3ff0000000000000,0x3fbc8a6e3519e694,0xbfa3484d8571cb61,0x3ff0000000000000,0x3ffc6d7219d23ff8,0x3ff0000000000000,0xbfefe825b49f0706,0xbfd975b0a3960ecb,0x3f947ae147ae147b,0xbf83c00877a76c9b,0x3f947ae147ae147c,0x3fc1829b775d4fb8,0xbf7535f5b17edfe7,0x3ff0000000000000,0xbfda21416888ba0f,0x3ff0000000000000,0xbfdd6cecdd6261b2,0xbfb84d9bd150abd2,0x3ff0000000000000,0xbfffffd7a908ca5c,0x3fefffffffffffff,0x3fe57a660ce78538,0xbfc07278a7f21fbc,0x3ff0000000000000,0x3f69f30c1cacf401,0x3ff0000000000000,0xbfc459805153d58c,0xbfc0a8835596898c,0x3f947ae147ae147b,0xbfa3e26b942d71e8,0x3f947ae147ae147b,0x3fe2405a072c65cd,0xbfd2b49d2cc72ae0,0x3ff0000000000000,0xbff0ac85baa1b40c,0x3fefffffffffffff,0xbfec32988c816f9a,0xbfd419a3169ce49c,0x3ff0000000000000,0xbff80c302992f205,0x3ff0000000000000,0x3ff0a7a729309fda,0xbfd965531789dc20,0x3ff0000000000000,0xbfe1e73182790b46,0x3ff0000000000000,0x3fc32e1c080b699a,0xbfdf5c061bd1c764,0x3f947ae147ae147b,0xbfa1d367fd854a38,0x3f947ae147ae147b,0x3fd58b61b8c2ae90,0xbf9d09c221a3f26e,0x3ff0000000000000,0xbfe6fdc299f32beb,0x3ff0000000000000,0x3fce7296e18f02af,0xbfa8cdde379cd8c4,0x3ff0000000000000,0xbff51195142afc43,0x3ff0000000000000,0x3fd8f77cb44a0b50,0xbfb3a7c444bd505e,0x3ff0000000000000,0x3ffffec9390229f8,0x3ff0000000000000,0xbff128bbeeb25e7b,0xbfd3a676036f1bb6,0x3ff0000000000000,0x3fd0a3c55cffd5f9,0x3ff0000000000000,0xbfdd1d588f8debfe,0xbfdf507f401d58d9,0x3f947ae147ae147b,0xbfa1c51976110f1e,0x3f947ae147ae147b,0xbed1e759ff07bf6a,0xbee4c63149ae1ba0,0x3ff0000000000000,0xbffa802fc483d3bd,0x3ff0000000000000,0x3fd03a741b6ed570,0xbfabebb0ef001347,0x3ff0000000000000,0xbfe11fb5f4603257,0x3ff0000000000001,0xbfc04bf839da42d0,0xbfaf3166b0afe73a,0x3ff0000000000000,0x3ffbf5b69b3f30ca,0x3ff0000000000000,0xbfefaf6f0a24fdc2,0xbfd71c5c7ac287f4,0x3ff0000000000000,0x3fffab29f0124803,0x3fefffffffffffff,0xbff4fb05728d9303,0xbfdc2d2861a38b0d,0x3f947ae147ae147b,0x3f43c6f386bb80d0,0x3f947ae147ae147b,0xbf7b0820164f63d6,0xbef53ea77e5c4fa2,0x3ff0000000000000,0xbfe5abe3f80c4718,0x3fefffffffffffff,0x3fa43a013070a814,0xbf6bcbbbdcb73bcf,0x3ff0000000000000,0x3fe1260981a97598,0x3ff0000000000000,0xbfe47e30b26a7183,0xbfc2607689a14bd2,0x3ff0000000000000,0x3ff66b189b2e74a1,0x3ff0000000000000,0xbfe24f5f1123568a,0xbfc4b4c2956701f5,0x3ff0000000000000,0xbffe618cbe2d9672,0x3ff0000000000000,0x3fec0529d05f1810,0xbfc8b3cc14dbe7e2};

const s16 BIQUADF64_AllBiquadConfigs2_s16[18]={0x0001,0x0001,0x0001,0x0004,0x0001,0x0005,0x0004,0x0001,0x0004,0x0004,0x0004,0x0005,0x0005,0x0001,0x0005,0x0004,0x0005,0x0005};

const u64 BIQUADF64_AllBiquadInputs2_f64[30]={0x3ff0000000000000,0x3fc238f0b99af428,0x3fcf645f0ba9b0da,0xbff0000000000000,0xbfcb9afcf69baa6b,0x3fec2e0ae645e34e,0x3fdb24929f937c13,0xbff0000000000000,0x3fd59c3892e5e8ad,0xbfabe2c897cd2d76,0xbff0000000000000,0x3fe21bca7db13479,0x3fda491158ed8937,0xbff0000000000000,0xbfc3ccacb75ffdde,0x3fbb20b4326308cc,0xbfd6d57214ae01b1,0xbff0000000000000,0xbfda828ac7e95e64,0xbfdb299e0ec9a148,0x3ff0000000000000,0xbfd945a4b0a32fbf,0xbfe15c4a6e2c6b82,0x3ff0000000000000,0x3fd958e61a687112,0x3fcbae1f3862020c,0x3ff0000000000000,0xbfa915f638076ccb,0xbfa8dab28fd8af03,0x3fb29c7360086241};

const u64 BIQUADF64_AllBiquadRefs2_f64[30]={0x3f947ae147ae147b,0x3f67531fa5e50f8f,0x3f7f37081f85a02e,0xbf88c992e3b879f1,0xbf91cd6037703fe1,0x3f9208fcbc55b032,0x3f80305abf6f96d8,0xbf67254950f72300,0x3f929f0e34da08c0,0xbf94386e437ad778,0xbf947ae147ae147b,0x3f872dcffd0bc849,0xbf96db782ded7efb,0x3f93ce97ce08e1b4,0x3f788752b7c9a580,0x3f615c9c4935245a,0xbf90595358747562,0x3f9c934dfef9e560,0xbf824ba3126f789d,0xbfaa39fbb6b92c04,0x3f947ae147ae147b,0xbf802c925c91663d,0x3f8031f1feab8ccb,0x3fa03498999db991,0xbfb1cbf219e041e0,0x3f71b71e3890a527,0x3f906fdd9eef716d,0xbf812a2ddd7a9ad4,0x3fa38f266a433f28,0xbfa50a6f8ef9cf14};

const u64 BIQUADF64_BiquadCoefs1_f64[15]={0x3f947ae147ae147b,0xbf96217af56297be,0x3f947ae147ae147b,0x3ffbe798f5f156c4,0xbfe9eb851eb851ea,0x3ff0000000000000,0xbff97984baf498c2,0x3ff0000000000000,0x3ffbf32b35561e8f,0xbfee1bda5119ce06,0x3ff0000000000000,0xbffffe5c95658d96,0x3ff0000000000000,0x3fff52207be53342,0xbfeebb98c7e28242};

const u64 BIQUADF64_BiquadInput1_f64[100]={0xbfa50d708a3ad40f,0x3fd72a3a6bd8f631,0x3fe1abfece15c872,0x3fd152afa9ce856e,0x3fdb52267db5dae1,0x3fe0933f50d791d4,0x3fe8271b7fa25977,0x3fdac3ea2139aa9b,0x3fd635e7c72072a0,0x3fb9ffb3f59def29,0x3fa3fbb73f222df0,0x3f888b6dafb93976,0xbfdab10f16aaa629,0xbfe70b737613efe8,0xbfed342b433ec346,0xbfdac5e3d9cd3c62,0xbfc83118fbf2bf1a,0xbfcbf3220f539623,0xbfe2dd3605ad94ee,0xbfd8798991c0e769,0xbfa462703e574080,0x3fcc9993cb73fd36,0x3fd646a9eb3911d4,0x3fd91119aae1210a,0x3fd8a7b203011999,0x3fd89de09ace920c,0x3fe3d95696c2513c,0x3fdf71604e1ebecd,0x3fc26667009221d2,0xbfb5691f6ad2e422,0x3fc176df511741f5,0x3fcc69caf692c6c3,0xbfd8530086362859,0xbfe8d404d4ebfd15,0xbff0000000000000,0xbfe41ea0a279277c,0xbfca087eb38e8d97,0xbfd96fca371fb1c7,0xbfe397c603a735e5,0xbfc9cd3d531ad4fa,0x3fd616ba3d805cb7,0x3fd4f5dfe56c1535,0x3fdc2d9cca3e79ff,0x3fe0be14368a4fd6,0x3fc3ec6a3fde5832,0x3fe4d787545f43cb,0x3fef9ca2761780c4,0x3fd4dd375f550730,0x3fb3522c904118cb,0x3fade71d39c952d3,0x3fc6c79328d3d06b,0x3f9e61c378bce0c6,0xbfd7fdad369128f6,0xbfe4c63c310f9f95,0xbfe30d62137357c4,0xbfdd7e278558efec,0xbfd898ececb5f5be,0xbfe16c6665ed08bd,0xbfe21f7706f0dcc4,0xbfc2cc359c87979a,0x3fc95eb39708e94e,0x3fe17cf063d12b1e,0x3fd9ef1018871a58,0x3fcba4f8e2300cae,0x3fd5bba4f0a72a6f,0x3fe3c6f88524aa2b,0x3fe639ba12475dc1,0x3fd44a9a17953c84,0x3fb83f6ce1186608,0xbfc0cc8972f31732,0xbfa119bda59562e1,0xbfd18c6aacfbbcac,0xbfdd59608b38cf24,0xbfe90833454ae370,0xbfed2c589401350a,0xbfcfd4ec4d3636e6,0xbfd1f619f34bebc8,0xbfe0f77bb27f11e1,0xbfd67f561d289ee9,0x3fb8cea64b13008e,0x3fd4395d066056cc,0x3fdeeec04a6cc3ae,0x3fd579a08a08ea4d,0x3fd49cba2d89ea16,0x3fe324405c56e9dd,0x3febd63a26d0e14c,0x3fe758e60957cf54,0x3fd8adf074105858,0x3f9a24d3481a78cc,0x3fab2787b8b1150f,0x3fcb86e8f6bfca3b,0xbfcec9325d6a5d3d,0xbfe38603d2c03bfd,0xbfe6386449126232,0xbfdec25b57e4808e,0xbfd5306ef29e180e,0xbfc2a5479f5fa4b1,0xbfd17246f20085e3,0xbfc6dda28ef1e8a7,0x3fbc7e2c1a958ad6};

const u64 BIQUADF64_BiquadOutput1_f64[100]={0xbf4af27b9236d1ff,0x3f7b0976a000280a,0x3f8f4271d4e4f6d8,0x3f98d1881a7736ad,0x3fa819f9271d4aa2,0x3fb307a2b3ae7dbb,0x3fbc99a02c55379c,0x3fc2d504a2c58bbb,0x3fc857ada9567566,0x3fccf31469c9f67a,0x3fd050c48b8ebb6c,0x3fd12b220b132b32,0x3fd042c7671f1d34,0x3fcb773b58b42bfa,0x3fc267e47f4d5bc8,0x3fab3a0735731674,0xbfaff42e3b53ce20,0xbfc81d3557eb0145,0xbfd43a1b4184eefe,0xbfdafb2581e23cb4,0xbfe00418df34614d,0xbfe153df68ca40eb,0xbfe12653bab2da19,0xbfdec8cb2893f7db,0xbfd869b4ce4c1fa2,0xbfcf9cff75d623e6,0xbfb6520aa12370fb,0x3fb2d72f73a310b6,0x3fcc4c0d5fa6c87c,0x3fd5df928da03a84,0x3fdb5ae581dd1e78,0x3fddb83d047559ae,0x3fdc6d1015417d01,0x3fd85a608e449dd6,0x3fd18be0d68c1a58,0x3fc2476be716625f,0xbf6f2b9a8471fa30,0xbfc4040951522739,0xbfd2b52973e2911b,0xbfd9296cbdfe3633,0xbfdd27c654e70d92,0xbfdeb2858347dc55,0xbfdce0f3ac5e1970,0xbfd82a84343ae52c,0xbfd188ce976839e9,0xbfc0bf1c013f0110,0x3f995014f43efc2c,0x3fc5b08958e7f4c1,0x3fd3bb01351c06da,0x3fdad96abbbd15ba,0x3fdf8d6c4eb7d6d2,0x3fe09c2e18cc210a,0x3fdfc35c04b2eb2c,0x3fdb82f717332734,0x3fd4e922dbe82bd4,0x3fc8d9766f939b8e,0x3fa752321d99362a,0xbfbb736d5e0650c8,0xbfcf88ce914952a5,0xbfd6c7ec4c105bba,0xbfdba01985937bd4,0xbfdd7da461db7f2e,0xbfdc9fbd592d11c6,0xbfd8d32aaffa4345,0xbfd25f5bc493737d,0xbfc415cdfc1ab964,0xbf88959f8eaa5930,0x3fc0c07a21706605,0x3fd0ea22b3319440,0x3fd79608ba11bf3c,0x3fdc09f14fdd7912,0x3fdd3b2da4ab761d,0x3fdb7c3f2b581f62,0x3fd69b5d3392a8bd,0x3fce7eb3be851c70,0x3fbb1eb6052a35dc,0xbfa8eef58555ff85,0xbfc987b90c43998b,0xbfd4c9daf624b876,0xbfda8e35a6aeb5c8,0xbfddb4421eddbabe,0xbfdd84b91780f4ec,0xbfda51a06a982b11,0xbfd42303b23b9e5a,0xbfc71f070d004cae,0xbf9963907715f238,0x3fc132abd03d8fd0,0x3fd22b543353908a,0x3fda1ab73d70490b,0x3fdfdfaac4085fee,0x3fe16701e58d9d3d,0x3fe10d62660ec9cc,0x3fde7fb273f1eb36,0x3fd842616554d5e5,0x3fcffd7f43743694,0x3fb957c66ab7282a,0xbfabe1459488c9fa,0xbfc9b912688d9388,0xbfd478bc052cf6bf,0xbfd9b94be34ccc48};

const u64 BIQUADF64_Coefs1_f64[20]={0x3fc1cb0749fbdd37,0x3fccc629cc398f15,0x3fc279b66e5fdf00,0x3fa3bc74c20af5ed,0x3fb9c5e99c2ba1d5,0x3fb50376b96af6fa,0xbfd67d7e3641a446,0x3fd2a54021e70e4a,0x3fc8be9083d8b548,0xbfc7cd8e0c405a3a,0x3fc0a3f89328e000,0xbfd07348fdd533c6,0xbff0000000000000,0xbfe40852198f2d21,0xbfb48db51ea64dd3,0xbf958aa7a53a645e,0x3fbb564ccc588b8d,0xbfd03fc867921620,0x3fe040271e52b680,0xbfcca01bf1dc51f5};

const u64 BIQUADF64_Samples1_f64[512]={0x3fcb166432781d49,0xbfeb136b536d5a4f,0xbfd63f158e5947d1,0xbfddb66bfd8ae533,0x3fd2bac443be13eb,0xbfdd1fb883456524,0x3fe313731a390517,0xbfe36f675187ba48,0xbfc39cbabf2e6c6e,0xbfd6b96e4284ebec,0xbf919563c862a430,0x3fbfa570ff8973dd,0x3fd7a3d0290341e2,0x3fd167583d4abbf1,0x3f9f310dffd92e5a,0xbfd29ae62d65453a,0x3fc6a32c76213995,0x3f85cba166e55e8a,0x3fde42a03bacd9cb,0x3fc64d64e3807b42,0x3fdf0642c9d410fa,0xbfdc818cc26df7ef,0xbfdb57a171a6daf5,0xbfd76160820ce2af,0x3fbbe83e23849267,0x3fdb83003bbeee71,0x3fd9ce8652471a62,0xbfd52da9676ceb99,0xbfb014762c76f8d7,0xbfcdff0dae2a6999,0x3fe762cb2bdbdeae,0x3fe665871cbe6f4c,0xbfd33a1cf2899a23,0x3fc52161947b40dd,0x3fb9a0af17a302e7,0x3fcdd8e0e85b54f8,0xbfb78dcefff55060,0x3fe2580369917479,0x3fc41981a740978d,0xbfdd105a89508e47,0xbfc80f0ad08d2262,0x3fcf51a206242b69,0x3fc6b911fe933a3b,0xbfbe36d4b45b9e09,0xbfaa95fafba00697,0xbfb5b22fc2b8cfbb,0x3fe10d4c8e199c0c,0x3fd8347d12856fcc,0x3fd0d9c82afb1ff9,0xbfcb423e92e62989,0x3fc0dbdf73fe9077,0xbfd8ea0228477beb,0x3fa513d878c27428,0xbfab5b5729059503,0xbfc2ac62b7fd854b,0x3fcab8e382bc8ff9,0x3fd3981f9f397433,0xbfd46c4080304b50,0x3fdb6fd85b2b9426,0x3fb04b556469f4ce,0xbfdcb297028d6084,0x3fd01613abc6cd25,0xbfcef143ab465456,0xbfd85669a8c72b02,0x3fcf35f53532dbe9,0x3fe33cfa86218269,0xbfd47d193a9caf24,0xbfdcb0e09fbb7f95,0xbfd69007c7b9da0b,0x3fc535a64e5fbf33,0x3fe63e11143d96d3,0x3fd9218a54fd49d3,0xbfd7ae6795dbe787,0x3fdf6ce46af07e28,0xbfa82ee050e183bf,0xbfb75d5ac1270762,0xbfbc0897d02f4d68,0x3fd0672fe19876ff,0xbfc4e2358d6afee8,0x3f82833bd6ce9c01,0xbfbcc4773cf4a1d3,0x3fec05cc6e2ab99d,0xbfad261b5290b050,0xbfc180c7985f6307,0x3fc3093bafad52f0,0xbfea877b50c57942,0xbfe820e2fc605496,0xbfd2917c313f8305,0x3f9f655f38ffee4d,0x3fdaf032de96cd56,0xbfbdc624bd5e09e6,0xbfe75523e88735f0,0x3fc038d5cde8c408,0xbfe69934afe692b7,0x3fe4ff3b4f970d9d,0x3fe97b438ad7ddd6,0x3fe3d9c24e649e7c,0xbfc0981bc94fcb49,0x3feb7dee08ce09ec,0xbfd96a5c209ed347,0xbf9934b8b328c425,0x3fd70489f7040d7d,0x3fe64639b4b1fa2e,0x3fd4fd167027f827,0xbfd377a72853731b,0xbfc9a8f7e61b1318,0x3f72fbab70c135b6,0xbfde194ae24b66bd,0x3fd3f55b14eeaeb9,0x3fb147af6c793aa6,0xbf9a4d5619693565,0xbf80a9ec3ef04f4f,0xbfe0663585af2a71,0x3fc951b9188c717f,0x3fe9ddfa46ae39ee,0xbfd8d3d0c3750193,0x3fb1313a37d130f3,0x3fddee672287cc75,0xbfb3dea319b1873f,0xbfcc615ac7d0cc06,0xbfb171976271ce33,0x3fdd52a494ec8805,0xbfceee78edbde03d,0x3fd45fb50ed425cb,0xbfd093296e2eac95,0xbfa8e01c923f4d9c,0x3fdb9ba4d7bdd3cd,0xbfd1a20ca36c75d8,0xbf9f576ae7e5ed97,0x3fbeae635ed97ca3,0xbfcce1a5d6475ca7,0xbfb30f9d62d8d721,0xbf8ceaec46091bac,0xbfc63119106410f4,0x3fd07e7e19488585,0x3fd198863eec1fc5,0x3fc1b1129d0bafb6,0x3fd39b0d0a04b558,0x3fe5420b04f611c8,0x3fbcebbb6cd56b62,0x3fa83ed9fbeaeafe,0xbfd343d0c81ab5ea,0x3fc597843b7bb5d5,0xbfdc1a46a343e88e,0x3fb4ec10d90304e5,0xbfe3b01cade8e345,0xbfc8319c89e9a44a,0x3fe1b749b2ff962e,0x3fced2a0c59764cf,0xbfe4d82bb7c89e81,0xbfd9c90c5a7b906d,0xbfd6f0a53010cbfd,0x3faff6e1519660c3,0x3fe57491f9ec9497,0x3fd405a89e86b524,0xbfb58c02a55661a1,0x3fe58b56cce85fce,0xbfd16fc0486b5b35,0xbf92d912dda6f21b,0xbfd5085b366d44ce,0xbfc4b93080f88fdd,0x3f94d47eb4b7d1d1,0xbfe47556c920c618,0x3fd13f19149578f1,0x3f9a66e9e539a121,0x3fc08b636b94dd0a,0xbfc3c7fca583f79d,0x3fb77f94b88cfd90,0x3fcf56b342787df0,0x3fe68593a92005da,0xbfc0ccf44ab94fe4,0x3fcce829ca5ffd6e,0x3fe1763dee759d58,0x3fc20f5d8ce5b155,0xbfa45e9564bc2ee4,0xbfba351cd741ea75,0xbfedf61c74338100,0x3f85235074a0582e,0xbfc6c535dfbd4377,0xbfbcca3f5d212b1b,0x3fb8d9183b52a310,0x3fdf647b8111f028,0xbfc2ad2f87f04c2d,0xbfcd75275b6104a3,0xbfc70859b4099c32,0xbfdee92f0ba955bd,0x3fe0d32c7c6d1c5e,0x3f9fd82a91dfb543,0x3fb55878bf18ab3f,0xbfb04291c442a138,0xbfbebb5a77644b71,0xbf9a895680a5747a,0xbfb8a861cc07ddf5,0x3fe57dee09f62d6f,0x3fb385509c898c5d,0x3feb63fd3a7efd38,0x3fed8f2e74da85a3,0x3ff0000000000000,0xbfc4eb5bed7a66bf,0xbfeb3c685c3877d9,0xbfce72187a0dbbdb,0x3fd36074bd70615f,0xbfdfc4476013c30f,0xbfd0bc7656b3a3c9,0xbfc8a8796c2a9b6e,0xbfe0c81271e977f1,0x3fd867b4e8de56c3,0xbfe00609414dccf3,0x3fe01b93df8c1fb1,0xbfd6b0b94609a91b,0x3fcd09972e994a19,0x3fe14e3a40371e33,0xbfd1c0aef861d39d,0x3fea897074adbd23,0xbfa8d318059428c2,0x3fd2741151abe7a4,0x3f6ef9a2f9d412e1,0xbfc1505c364ba138,0xbfa42ed886e367ad,0x3fd57acdc1a674d9,0xbfe9deae7a81b0ad,0x3fc8d95b6ec24050,0x3fccd5e668552cb2,0xbfd6d1c46b576ed7,0xbfb568ff7d7d4721,0x3fb74d5a12087687,0xbfcc261f74e44ad2,0x3fc76fb86c48b3a6,0x3fe42df96447e896,0x3fd58c7499da563a,0x3fb7660dd85d1d2d,0x3f9f1e2027a37849,0xbfd3f37032752f98,0xbfe0b8c939643b91,0x3fc3a458b66d9472,0xbfd2066569442142,0x3fcc845b23b4350a,0x3fa2de088801bb6e,0xbfd1b51794c9bba7,0x3fb5cb7a5c0fa868,0xbfe3b372679b2c6d,0xbfc80bcd7665b746,0x3fd0f31f3e04fdd7,0xbfbc8191efbddf96,0xbfd54c1f33f77a1e,0x3fd886486a88dbbf,0x3fc50fb7447a5f73,0xbfe7ac5d75eade9a,0x3f9c7f58e75a9510,0xbf89c690bce2c7cd,0xbfb746177579d295,0xbfd0041f2df553c9,0xbfc8cf05405f7c59,0xbfd45a5907ce00ec,0x3fc20199b73046b4,0xbfc4871042ef1b32,0xbfb200ebb2757e6c,0x3fc273461fb56969,0xbfe6e840323e2d1a,0xbfd93a64a5d345db,0x3fe612dff4c4a236,0xbf9d7f500e266e97,0xbfc6d1a8d0ca2bec,0xbfc1a02a1aa1d315,0x3fb56d0f0ea34154,0x3fa5428800327464,0x3fcb11865c9c067c,0xbf88a6e6d3ada702,0xbfdae284b76b097c,0x3fccae501d7e3d2c,0x3f959587959700df,0xbfd39e854ccba1c2,0xbfd584c7db5d6d53,0x3f9061f5dd26904d,0xbfc334c3e9a0f3c4,0xbfdc419ea6314c9a,0x3fb6e56870b415a2,0xbfdd81147280d33e,0x3fd227cb2e3e9d88,0x3fdf9d637a68d5d6,0x3fb3454b3fda0da9,0x3fe3d1886f13e088,0xbfd5b733a2400b7a,0xbfb4f7e0e0550441,0x3fd5ffc826d3c485,0x3fdc6589a6040b1c,0x3fd55d40218d5cc9,0x3fe93ff51be7b355,0xbfa0e7a6e9b2df4b,0xbfdab8e1569431f0,0xbfcd3f5c74f11d24,0xbfdbc39bb2649de9,0x3fd12357b6fe6cf3,0x3fe399ca36d21b92,0xbfccd603ca977810,0x3fd9d16362fba28b,0x3fd72c894d1d8b07,0xbfc148e4ff12a954,0xbfed6a1003b09739,0xbfb71311f1790516,0x3fd5ac4525f06512,0x3faac891dda1ef12,0x3fd6822d23f765dd,0xbf9a643196988f54,0xbfc0a87762f92771,0x3fe514c3e65679ec,0xbfcfb95acadc5d12,0x3fbaa9f6ef7506c8,0x3fd362d55d72da8f,0xbf90bcae5c830d7b,0xbfc63f3975274e50,0xbfbbabc99168d2fd,0xbfb0cb26cd74b50f,0xbfd210a1d0dcbcf7,0x3fb76aab62cf975f,0x3fe9625b439c399d,0xbfe677c68bfbe17c,0xbfdafa89db809578,0x3fd0e369bd1fb256,0xbfe5bf91e53782cf,0xbfd5258ce1bec89e,0xbfda2a5ed2db9b56,0xbfd49cf48c969cef,0x3fd4921806e0e706,0x3fd422cd9b72780c,0xbfcb4322dfae0052,0x3fef53af7b4a8834,0x3fb26b336c7d6163,0x3fcf7b9059a0bc10,0x3fcbb37d77187cfd,0x3fe8e8e4251c5753,0xbfbe8e6c0382e5f1,0xbfc95c04ece2107f,0xbfbced75ea9506dd,0x3fe7e7e2cddf1359,0xbfd290cb01ec1210,0xbfbf3a304d43ce74,0x3fcb867b9509dc59,0x3fe429a81763203a,0x3fe887ab7537b0ab,0x3fc900f8cead94af,0xbfd580fe686fceae,0x3fafe8091df61e87,0x3f85b4e596d00c92,0xbfd251cc5cc44861,0xbfb52a2955dc1fe5,0xbfe210bac1b8e428,0x3f91a205c1140630,0x3fc90795b872392d,0x3fcd1cd7e6b6a901,0x3fd0899c17358c2c,0xbfdea8485a16a1bc,0x3fbcb2818e743378,0xbfd0bbc8d0e845d6,0xbfda7a6b82c8cfaa,0xbfdbea4adba3d94e,0x3fdb7108ca62c054,0xbfe52c6e91cadd37,0xbfee01ce5ab8ec71,0xbfd753427d7e1a92,0xbfc17e8e53eaf88d,0x3fd0f5ba442374d9,0x3f72091534a23395,0xbfd03b84e559d959,0x3fd0ca8d720f86ac,0x3fed5ba1e1edb1db,0x3fd6171b161e4c06,0x3fab758dd990ca06,0x3fa59e05a2541e60,0xbfd870af2bc6e5a2,0xbf5278835f84d77a,0x3f97cf05add297e9,0x3fa2485e0c407692,0x3fd2966cb44a96b0,0xbfcac77dffa45a53,0xbfa532f41f5777e1,0xbfcd1cf8ab728f99,0x3fd8df2a8d666ec5,0x3fd45595401e68e0,0x3fbac67668b5e89d,0x3fc59b856cbf2589,0xbf988fc161e7368b,0xbfbb6daf39b9bbe2,0x3fd4b1156afee53c,0x3fb0481194e3eb98,0x3fa333406d0df713,0x3f918a254064576c,0x3fa2fc36152372fe,0x3fde9f3deec1d8a7,0x3fe15f0da27850a0,0xbfe014b30997865f,0xbf8dd95a5d494c5e,0xbfd1479b758685d4,0xbfd5a423c3d85b7f,0xbfc544008e0ab630,0x3fb69c9e49f0093c,0x3fe537777462fbdd,0x3fa04e8d2772c879,0xbf8b923423db4987,0x3fd04caefa2dcb45,0x3fc9ad909d11868f,0x3fb3b639a3044366,0x3fc06e3e7ef8de6b,0xbfd33ff1e201f88e,0xbfbdb6ca96479162,0xbfd35d18d672b9fe,0x3fb34c279ac4388e,0xbfc32c49fe8e7c13,0xbfcfae8d6a2c0b65,0x3f627a56169e2974,0xbf9e5d7c7bf55252,0x3fe47a2c05468eb8,0x3f8e1b4b44d51bc9,0xbfd990e856a8a87e,0xbfca290733044084,0xbfb9ad8951360fb7,0x3fa033b5073af2d8,0x3fb2fe897492b087,0x3fe03d9a72eb33b1,0xbfaaf03b5ed907b2,0xbfdcb2d4b6893615,0x3fdb7a9cf4a2cdab,0x3fc59d3c3e412b09,0xbfd4995e4f03c321,0xbfd6b2f642b04a51,0x3fdf4b6bb28fd78a,0x3fe0bb02dfdb4209,0x3fe31cbba277681a,0xbfd5ecbbdc64f04f,0x3fc51d850f2437b8,0xbf9cf4fcd9c4c2cf,0xbfe14ba6ad8f0cac,0xbfd5a6294fa2bcef,0xbfd5ebed29444109,0xbfd25bac9e0438be,0x3fdec2bae24c68a2,0xbfa7fd18bece7887,0x3fd8ecdadcd8607a,0x3fd6fac2c18a31f7,0xbf9fd9a5d8fc6610,0xbfd492671c241a42,0xbfc00d548f40e808,0x3f7ac3c5417a3b63,0x3fcb203ea1666c8e,0x3fe3f91846b8b043,0xbfc1bdefbdab86f4,0x3fa70bb1c19bc556,0xbfe14425fcc8dff0,0xbfe5ea5d482242f6,0xbfdc2169183f8730,0x3fb7c56fece5018a,0x3fcc5d315730a0c9,0x3fd6eff914e5faa0,0xbfd56b478ca6b563,0x3fd65b0a9e18bebd,0x3fd1fbe95b6e991c,0x3fcb7939ee1b30ff,0x3fd5961785c01ab9,0x3fc68013d161d386,0xbfc34bac3507491d,0xbfed0749830e4046,0x3fd009f5f718dffb,0xbfd077d898ad1c66,0xbfdf1b9d5f35ebb4,0x3fce1fe2e199371f,0xbfb92b1918cfb784,0xbfcf75091cc5c559,0x3fa3e31f816435a3,0x3fcf489566b006cf,0x3fc7675e707ec8a6,0x3fb51410bdfc0d6b,0xbfd694c73f5553d3,0x3fde05d028f2d40e,0x3fb80889d2b7080d,0xbfded5da43d123ee,0xbfc9f03ac601b7c7,0x3fbc703f775004b5,0x3f9676073fde90d4,0x3fd3d8bbfe0ccac8,0x3f9074396e3860a3,0x3fdbdeb063da29a7,0x3fd0dddaaafc2187,0x3fd79570d7a92a06,0x3fcf4607160661d4,0xbfb62579b6340309,0x3fd375ead0f2386c,0x3fda52355900338e,0xbfd6a6b9281cb93e,0xbfae864e70f06fe3,0xbfce3f6c7261a757,0xbfde0daf3bfe24e8,0xbfea5df2bf7526d2,0x3fb15023f53c8d7e,0xbfedf8fc18dfd81e,0xbfba7414ed4f015d,0xbfd943bcb8f1380c,0x3fd3f1be63bbd62c,0x3fd092d094265adb,0x3fd7a01e8f18b77a,0x3fdae80d93a1377e,0xbfb752c25cd8fcf6,0x3fd1528bda7a1bde,0x3fd21bd0bc97f0a9,0xbfdbbe4edc69371e,0x3fa82675fe122b8a,0xbfec0487fb2f427e,0xbf819c5273a3d190,0xbfd731129021a1d3,0x3fdccdb6a35dc0de,0xbfe3fba3b7eafd4d,0xbf9acfa7d5e6bc0e,0xbfdffbccad2fd84e};
