#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/transform_functions.h"
#include "mips_common_tables.h"
#include "mips_const_structs.h"

#define SNR_THRESHOLD 250

int main()
{

#if !defined(NOT_EMBEDDED)
	uint8_t referenceData_u8[MAX_SIZE] = {0};
	uint16_t referenceData_u16[MAX_SIZE] = {0};
	uint32_t referenceData_u32[MAX_SIZE] = {0};
	uint64_t referenceData_u64[MAX_SIZE] = {0};
	q7 referenceData_q7[MAX_SIZE] = {0};
	q15 referenceData_q15[MAX_SIZE] = {0};
	q31 referenceData_q31[MAX_SIZE] = {0};
	q63 referenceData_q63[MAX_SIZE] = {0};
	f32 referenceData_f32[MAX_SIZE] = {0};
	f64 referenceData_f64[MAX_SIZE] = {0};
#endif

    // declare input value

    int paramCountInputNoisy32 = 0;
    int paramCountInputNoisy64 = 0;
    int paramCountInputNoisy128 = 0;
    int paramCountInputNoisy256 = 0;
    int paramCountInputNoisy512 = 0;
    int paramCountInputNoisy1024 = 0;
    int paramCountInputNoisy2048 = 0;
    int paramCountInputNoisy4096 = 0;

    f64 f64inputNoisy32[MAX_SIZE] = {0};
    f64 f64inputNoisy64[MAX_SIZE] = {0};
    f64 f64inputNoisy128[MAX_SIZE] = {0};
    f64 f64inputNoisy256[MAX_SIZE] = {0};
    f64 f64inputNoisy512[MAX_SIZE] = {0};
    f64 f64inputNoisy1024[MAX_SIZE] = {0};
    f64 f64inputNoisy2048[MAX_SIZE] = {0};
    f64 f64inputNoisy4096[MAX_SIZE] = {0};

    int IFTparamCountInputNoisy32 = 0;
    int IFTparamCountInputNoisy64 = 0;
    int IFTparamCountInputNoisy128 = 0;
    int IFTparamCountInputNoisy256 = 0;
    int IFTparamCountInputNoisy512 = 0;
    int IFTparamCountInputNoisy1024 = 0;
    int IFTparamCountInputNoisy2048 = 0;
    int IFTparamCountInputNoisy4096 = 0;

    f64 f64IFTinputNoisy32[MAX_SIZE] = {0};
    f64 f64IFTinputNoisy64[MAX_SIZE] = {0};
    f64 f64IFTinputNoisy128[MAX_SIZE] = {0};
    f64 f64IFTinputNoisy256[MAX_SIZE] = {0};
    f64 f64IFTinputNoisy512[MAX_SIZE] = {0};
    f64 f64IFTinputNoisy1024[MAX_SIZE] = {0};
    f64 f64IFTinputNoisy2048[MAX_SIZE] = {0};
    f64 f64IFTinputNoisy4096[MAX_SIZE] = {0};

    int paramCountInputStep16 = 0;
    int paramCountInputStep32 = 0;
    int paramCountInputStep64 = 0;
    int paramCountInputStep128 = 0;
    int paramCountInputStep256 = 0;
    int paramCountInputStep512 = 0;
    int paramCountInputStep1024 = 0;
    int paramCountInputStep2048 = 0;
    int paramCountInputStep4096 = 0;

    f64 f64inputStep16[MAX_SIZE] = {0};
    f64 f64inputStep32[MAX_SIZE] = {0};
    f64 f64inputStep64[MAX_SIZE] = {0};
    f64 f64inputStep128[MAX_SIZE] = {0};
    f64 f64inputStep256[MAX_SIZE] = {0};
    f64 f64inputStep512[MAX_SIZE] = {0};
    f64 f64inputStep1024[MAX_SIZE] = {0};
    f64 f64inputStep2048[MAX_SIZE] = {0};
    f64 f64inputStep4096[MAX_SIZE] = {0};

    int IFTparamCountInputStep16 = 0;
    int IFTparamCountInputStep32 = 0;
    int IFTparamCountInputStep64 = 0;
    int IFTparamCountInputStep128 = 0;
    int IFTparamCountInputStep256 = 0;
    int IFTparamCountInputStep512 = 0;
    int IFTparamCountInputStep1024 = 0;
    int IFTparamCountInputStep2048 = 0;
    int IFTparamCountInputStep4096 = 0;

    f64 f64IFTinputStep16[MAX_SIZE] = {0};
    f64 f64IFTinputStep32[MAX_SIZE] = {0};
    f64 f64IFTinputStep64[MAX_SIZE] = {0};
    f64 f64IFTinputStep128[MAX_SIZE] = {0};
    f64 f64IFTinputStep256[MAX_SIZE] = {0};
    f64 f64IFTinputStep512[MAX_SIZE] = {0};
    f64 f64IFTinputStep1024[MAX_SIZE] = {0};
    f64 f64IFTinputStep2048[MAX_SIZE] = {0};
    f64 f64IFTinputStep4096[MAX_SIZE] = {0};

    // file name. file path max length is 255, so use 255.

#if defined(NOT_EMBEDDED)
	char f64inputFileNoisy32[255] = {0};
#else
	void *f64inputFileNoisy32;
	int f64inputFileNoisy32Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f64inputFileNoisy64[255] = {0};
#else
	void *f64inputFileNoisy64;
	int f64inputFileNoisy64Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f64inputFileNoisy128[255] = {0};
#else
	void *f64inputFileNoisy128;
	int f64inputFileNoisy128Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f64inputFileNoisy256[255] = {0};
#else
	void *f64inputFileNoisy256;
	int f64inputFileNoisy256Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f64inputFileNoisy512[255] = {0};
#else
	void *f64inputFileNoisy512;
	int f64inputFileNoisy512Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f64inputFileNoisy1024[255] = {0};
#else
	void *f64inputFileNoisy1024;
	int f64inputFileNoisy1024Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f64inputFileNoisy2048[255] = {0};
#else
	void *f64inputFileNoisy2048;
	int f64inputFileNoisy2048Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f64inputFileNoisy4096[255] = {0};
#else
	void *f64inputFileNoisy4096;
	int f64inputFileNoisy4096Len = 0;
#endif


#if defined(NOT_EMBEDDED)
	char f64inputFileStep16[255] = {0};
#else
	void *f64inputFileStep16;
	int f64inputFileStep16Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f64inputFileStep32[255] = {0};
#else
	void *f64inputFileStep32;
	int f64inputFileStep32Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f64inputFileStep64[255] = {0};
#else
	void *f64inputFileStep64;
	int f64inputFileStep64Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f64inputFileStep128[255] = {0};
#else
	void *f64inputFileStep128;
	int f64inputFileStep128Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f64inputFileStep256[255] = {0};
#else
	void *f64inputFileStep256;
	int f64inputFileStep256Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f64inputFileStep512[255] = {0};
#else
	void *f64inputFileStep512;
	int f64inputFileStep512Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f64inputFileStep1024[255] = {0};
#else
	void *f64inputFileStep1024;
	int f64inputFileStep1024Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f64inputFileStep2048[255] = {0};
#else
	void *f64inputFileStep2048;
	int f64inputFileStep2048Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f64inputFileStep4096[255] = {0};
#else
	void *f64inputFileStep4096;
	int f64inputFileStep4096Len = 0;
#endif


#if defined(NOT_EMBEDDED)
	char f64IFTinputFileNoisy32[255] = {0};
#else
	void *f64IFTinputFileNoisy32;
	int f64IFTinputFileNoisy32Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f64IFTinputFileNoisy64[255] = {0};
#else
	void *f64IFTinputFileNoisy64;
	int f64IFTinputFileNoisy64Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f64IFTinputFileNoisy128[255] = {0};
#else
	void *f64IFTinputFileNoisy128;
	int f64IFTinputFileNoisy128Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f64IFTinputFileNoisy256[255] = {0};
#else
	void *f64IFTinputFileNoisy256;
	int f64IFTinputFileNoisy256Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f64IFTinputFileNoisy512[255] = {0};
#else
	void *f64IFTinputFileNoisy512;
	int f64IFTinputFileNoisy512Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f64IFTinputFileNoisy1024[255] = {0};
#else
	void *f64IFTinputFileNoisy1024;
	int f64IFTinputFileNoisy1024Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f64IFTinputFileNoisy2048[255] = {0};
#else
	void *f64IFTinputFileNoisy2048;
	int f64IFTinputFileNoisy2048Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f64IFTinputFileNoisy4096[255] = {0};
#else
	void *f64IFTinputFileNoisy4096;
	int f64IFTinputFileNoisy4096Len = 0;
#endif


#if defined(NOT_EMBEDDED)
	char f64IFTinputFileStep16[255] = {0};
#else
	void *f64IFTinputFileStep16;
	int f64IFTinputFileStep16Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f64IFTinputFileStep32[255] = {0};
#else
	void *f64IFTinputFileStep32;
	int f64IFTinputFileStep32Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f64IFTinputFileStep64[255] = {0};
#else
	void *f64IFTinputFileStep64;
	int f64IFTinputFileStep64Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f64IFTinputFileStep128[255] = {0};
#else
	void *f64IFTinputFileStep128;
	int f64IFTinputFileStep128Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f64IFTinputFileStep256[255] = {0};
#else
	void *f64IFTinputFileStep256;
	int f64IFTinputFileStep256Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f64IFTinputFileStep512[255] = {0};
#else
	void *f64IFTinputFileStep512;
	int f64IFTinputFileStep512Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f64IFTinputFileStep1024[255] = {0};
#else
	void *f64IFTinputFileStep1024;
	int f64IFTinputFileStep1024Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f64IFTinputFileStep2048[255] = {0};
#else
	void *f64IFTinputFileStep2048;
	int f64IFTinputFileStep2048Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f64IFTinputFileStep4096[255] = {0};
#else
	void *f64IFTinputFileStep4096;
	int f64IFTinputFileStep4096Len = 0;
#endif


#if defined(NOT_EMBEDDED)
	char f64referenceFileNoisy32[255] = {0};
#else
	void *f64referenceFileNoisy32;
	int f64referenceFileNoisy32Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f64referenceFileNoisy64[255] = {0};
#else
	void *f64referenceFileNoisy64;
	int f64referenceFileNoisy64Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f64referenceFileNoisy128[255] = {0};
#else
	void *f64referenceFileNoisy128;
	int f64referenceFileNoisy128Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f64referenceFileNoisy256[255] = {0};
#else
	void *f64referenceFileNoisy256;
	int f64referenceFileNoisy256Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f64referenceFileNoisy512[255] = {0};
#else
	void *f64referenceFileNoisy512;
	int f64referenceFileNoisy512Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f64referenceFileNoisy1024[255] = {0};
#else
	void *f64referenceFileNoisy1024;
	int f64referenceFileNoisy1024Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f64referenceFileNoisy2048[255] = {0};
#else
	void *f64referenceFileNoisy2048;
	int f64referenceFileNoisy2048Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f64referenceFileNoisy4096[255] = {0};
#else
	void *f64referenceFileNoisy4096;
	int f64referenceFileNoisy4096Len = 0;
#endif


#if defined(NOT_EMBEDDED)
	char f64referenceFileStep16[255] = {0};
#else
	void *f64referenceFileStep16;
	int f64referenceFileStep16Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f64referenceFileStep32[255] = {0};
#else
	void *f64referenceFileStep32;
	int f64referenceFileStep32Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f64referenceFileStep64[255] = {0};
#else
	void *f64referenceFileStep64;
	int f64referenceFileStep64Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f64referenceFileStep128[255] = {0};
#else
	void *f64referenceFileStep128;
	int f64referenceFileStep128Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f64referenceFileStep256[255] = {0};
#else
	void *f64referenceFileStep256;
	int f64referenceFileStep256Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f64referenceFileStep512[255] = {0};
#else
	void *f64referenceFileStep512;
	int f64referenceFileStep512Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f64referenceFileStep1024[255] = {0};
#else
	void *f64referenceFileStep1024;
	int f64referenceFileStep1024Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f64referenceFileStep2048[255] = {0};
#else
	void *f64referenceFileStep2048;
	int f64referenceFileStep2048Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f64referenceFileStep4096[255] = {0};
#else
	void *f64referenceFileStep4096;
	int f64referenceFileStep4096Len = 0;
#endif


    // set file name by snprintf
    // relative path, function path, filename
#if defined(NOT_EMBEDDED)
	snprintf(f64inputFileNoisy32, sizeof(f64inputFileNoisy32), "%s%s%s", Patterns_PATH, TransformF64, "RealInputSamples_Noisy_32_2_f64.txt");
#else
	f64inputFileNoisy32 = TransformF64_RealInputSamples_Noisy_32_2_f64;
	f64inputFileNoisy32Len = sizeof(TransformF64_RealInputSamples_Noisy_32_2_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f64inputFileNoisy64, sizeof(f64inputFileNoisy64), "%s%s%s", Patterns_PATH, TransformF64, "RealInputSamples_Noisy_64_3_f64.txt");
#else
	f64inputFileNoisy64 = TransformF64_RealInputSamples_Noisy_64_3_f64;
	f64inputFileNoisy64Len = sizeof(TransformF64_RealInputSamples_Noisy_64_3_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f64inputFileNoisy128, sizeof(f64inputFileNoisy128), "%s%s%s", Patterns_PATH, TransformF64, "RealInputSamples_Noisy_128_4_f64.txt");
#else
	f64inputFileNoisy128 = TransformF64_RealInputSamples_Noisy_128_4_f64;
	f64inputFileNoisy128Len = sizeof(TransformF64_RealInputSamples_Noisy_128_4_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f64inputFileNoisy256, sizeof(f64inputFileNoisy256), "%s%s%s", Patterns_PATH, TransformF64, "RealInputSamples_Noisy_256_5_f64.txt");
#else
	f64inputFileNoisy256 = TransformF64_RealInputSamples_Noisy_256_5_f64;
	f64inputFileNoisy256Len = sizeof(TransformF64_RealInputSamples_Noisy_256_5_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f64inputFileNoisy512, sizeof(f64inputFileNoisy512), "%s%s%s", Patterns_PATH, TransformF64, "RealInputSamples_Noisy_512_6_f64.txt");
#else
	f64inputFileNoisy512 = TransformF64_RealInputSamples_Noisy_512_6_f64;
	f64inputFileNoisy512Len = sizeof(TransformF64_RealInputSamples_Noisy_512_6_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f64inputFileNoisy1024, sizeof(f64inputFileNoisy1024), "%s%s%s", Patterns_PATH, TransformF64, "RealInputSamples_Noisy_1024_7_f64.txt");
#else
	f64inputFileNoisy1024 = TransformF64_RealInputSamples_Noisy_1024_7_f64;
	f64inputFileNoisy1024Len = sizeof(TransformF64_RealInputSamples_Noisy_1024_7_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f64inputFileNoisy2048, sizeof(f64inputFileNoisy2048), "%s%s%s", Patterns_PATH, TransformF64, "RealInputSamples_Noisy_2048_8_f64.txt");
#else
	f64inputFileNoisy2048 = TransformF64_RealInputSamples_Noisy_2048_8_f64;
	f64inputFileNoisy2048Len = sizeof(TransformF64_RealInputSamples_Noisy_2048_8_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f64inputFileNoisy4096, sizeof(f64inputFileNoisy4096), "%s%s%s", Patterns_PATH, TransformF64, "RealInputSamples_Noisy_4096_9_f64.txt");
#else
	f64inputFileNoisy4096 = TransformF64_RealInputSamples_Noisy_4096_9_f64;
	f64inputFileNoisy4096Len = sizeof(TransformF64_RealInputSamples_Noisy_4096_9_f64);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(f64IFTinputFileNoisy32, sizeof(f64IFTinputFileNoisy32), "%s%s%s", Patterns_PATH, TransformF64, "RealInputIFFTSamples_Noisy_32_2_f64.txt");
#else
	f64IFTinputFileNoisy32 = TransformF64_RealInputIFFTSamples_Noisy_32_2_f64;
	f64IFTinputFileNoisy32Len = sizeof(TransformF64_RealInputIFFTSamples_Noisy_32_2_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f64IFTinputFileNoisy64, sizeof(f64IFTinputFileNoisy64), "%s%s%s", Patterns_PATH, TransformF64, "RealInputIFFTSamples_Noisy_64_3_f64.txt");
#else
	f64IFTinputFileNoisy64 = TransformF64_RealInputIFFTSamples_Noisy_64_3_f64;
	f64IFTinputFileNoisy64Len = sizeof(TransformF64_RealInputIFFTSamples_Noisy_64_3_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f64IFTinputFileNoisy128, sizeof(f64IFTinputFileNoisy128), "%s%s%s", Patterns_PATH, TransformF64, "RealInputIFFTSamples_Noisy_128_4_f64.txt");
#else
	f64IFTinputFileNoisy128 = TransformF64_RealInputIFFTSamples_Noisy_128_4_f64;
	f64IFTinputFileNoisy128Len = sizeof(TransformF64_RealInputIFFTSamples_Noisy_128_4_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f64IFTinputFileNoisy256, sizeof(f64IFTinputFileNoisy256), "%s%s%s", Patterns_PATH, TransformF64, "RealInputIFFTSamples_Noisy_256_5_f64.txt");
#else
	f64IFTinputFileNoisy256 = TransformF64_RealInputIFFTSamples_Noisy_256_5_f64;
	f64IFTinputFileNoisy256Len = sizeof(TransformF64_RealInputIFFTSamples_Noisy_256_5_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f64IFTinputFileNoisy512, sizeof(f64IFTinputFileNoisy512), "%s%s%s", Patterns_PATH, TransformF64, "RealInputIFFTSamples_Noisy_512_6_f64.txt");
#else
	f64IFTinputFileNoisy512 = TransformF64_RealInputIFFTSamples_Noisy_512_6_f64;
	f64IFTinputFileNoisy512Len = sizeof(TransformF64_RealInputIFFTSamples_Noisy_512_6_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f64IFTinputFileNoisy1024, sizeof(f64IFTinputFileNoisy1024), "%s%s%s", Patterns_PATH, TransformF64, "RealInputIFFTSamples_Noisy_1024_7_f64.txt");
#else
	f64IFTinputFileNoisy1024 = TransformF64_RealInputIFFTSamples_Noisy_1024_7_f64;
	f64IFTinputFileNoisy1024Len = sizeof(TransformF64_RealInputIFFTSamples_Noisy_1024_7_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f64IFTinputFileNoisy2048, sizeof(f64IFTinputFileNoisy2048), "%s%s%s", Patterns_PATH, TransformF64, "RealInputIFFTSamples_Noisy_2048_8_f64.txt");
#else
	f64IFTinputFileNoisy2048 = TransformF64_RealInputIFFTSamples_Noisy_2048_8_f64;
	f64IFTinputFileNoisy2048Len = sizeof(TransformF64_RealInputIFFTSamples_Noisy_2048_8_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f64IFTinputFileNoisy4096, sizeof(f64IFTinputFileNoisy4096), "%s%s%s", Patterns_PATH, TransformF64, "RealInputIFFTSamples_Noisy_4096_9_f64.txt");
#else
	f64IFTinputFileNoisy4096 = TransformF64_RealInputIFFTSamples_Noisy_4096_9_f64;
	f64IFTinputFileNoisy4096Len = sizeof(TransformF64_RealInputIFFTSamples_Noisy_4096_9_f64);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(f64referenceFileNoisy32, sizeof(f64referenceFileNoisy32), "%s%s%s", Patterns_PATH, TransformF64, "RealFFTSamples_Noisy_32_2_f64.txt");
#else
	f64referenceFileNoisy32 = TransformF64_RealFFTSamples_Noisy_32_2_f64;
	f64referenceFileNoisy32Len = sizeof(TransformF64_RealFFTSamples_Noisy_32_2_f64)/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f64referenceFileNoisy64, sizeof(f64referenceFileNoisy64), "%s%s%s", Patterns_PATH, TransformF64, "RealFFTSamples_Noisy_64_3_f64.txt");
#else
	f64referenceFileNoisy64 = TransformF64_RealFFTSamples_Noisy_64_3_f64;
	f64referenceFileNoisy64Len = sizeof(TransformF64_RealFFTSamples_Noisy_64_3_f64)/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f64referenceFileNoisy128, sizeof(f64referenceFileNoisy128), "%s%s%s", Patterns_PATH, TransformF64, "RealFFTSamples_Noisy_128_4_f64.txt");
#else
	f64referenceFileNoisy128 = TransformF64_RealFFTSamples_Noisy_128_4_f64;
	f64referenceFileNoisy128Len = sizeof(TransformF64_RealFFTSamples_Noisy_128_4_f64)/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f64referenceFileNoisy256, sizeof(f64referenceFileNoisy256), "%s%s%s", Patterns_PATH, TransformF64, "RealFFTSamples_Noisy_256_5_f64.txt");
#else
	f64referenceFileNoisy256 = TransformF64_RealFFTSamples_Noisy_256_5_f64;
	f64referenceFileNoisy256Len = sizeof(TransformF64_RealFFTSamples_Noisy_256_5_f64)/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f64referenceFileNoisy512, sizeof(f64referenceFileNoisy512), "%s%s%s", Patterns_PATH, TransformF64, "RealFFTSamples_Noisy_512_6_f64.txt");
#else
	f64referenceFileNoisy512 = TransformF64_RealFFTSamples_Noisy_512_6_f64;
	f64referenceFileNoisy512Len = sizeof(TransformF64_RealFFTSamples_Noisy_512_6_f64)/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f64referenceFileNoisy1024, sizeof(f64referenceFileNoisy1024), "%s%s%s", Patterns_PATH, TransformF64, "RealFFTSamples_Noisy_1024_7_f64.txt");
#else
	f64referenceFileNoisy1024 = TransformF64_RealFFTSamples_Noisy_1024_7_f64;
	f64referenceFileNoisy1024Len = sizeof(TransformF64_RealFFTSamples_Noisy_1024_7_f64)/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f64referenceFileNoisy2048, sizeof(f64referenceFileNoisy2048), "%s%s%s", Patterns_PATH, TransformF64, "RealFFTSamples_Noisy_2048_8_f64.txt");
#else
	f64referenceFileNoisy2048 = TransformF64_RealFFTSamples_Noisy_2048_8_f64;
	f64referenceFileNoisy2048Len = sizeof(TransformF64_RealFFTSamples_Noisy_2048_8_f64)/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f64referenceFileNoisy4096, sizeof(f64referenceFileNoisy4096), "%s%s%s", Patterns_PATH, TransformF64, "RealFFTSamples_Noisy_4096_9_f64.txt");
#else
	f64referenceFileNoisy4096 = TransformF64_RealFFTSamples_Noisy_4096_9_f64;
	f64referenceFileNoisy4096Len = sizeof(TransformF64_RealFFTSamples_Noisy_4096_9_f64)/sizeof(f64);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(f64inputFileStep16, sizeof(f64inputFileStep16), "%s%s%s", Patterns_PATH, TransformF64, "RealInputSamples_Step_16_10_f64.txt");
#else
	f64inputFileStep16 = TransformF64_RealInputSamples_Step_16_10_f64;
	f64inputFileStep16Len = sizeof(TransformF64_RealInputSamples_Step_16_10_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f64inputFileStep32, sizeof(f64inputFileStep32), "%s%s%s", Patterns_PATH, TransformF64, "RealInputSamples_Step_32_11_f64.txt");
#else
	f64inputFileStep32 = TransformF64_RealInputSamples_Step_32_11_f64;
	f64inputFileStep32Len = sizeof(TransformF64_RealInputSamples_Step_32_11_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f64inputFileStep64, sizeof(f64inputFileStep64), "%s%s%s", Patterns_PATH, TransformF64, "RealInputSamples_Step_64_12_f64.txt");
#else
	f64inputFileStep64 = TransformF64_RealInputSamples_Step_64_12_f64;
	f64inputFileStep64Len = sizeof(TransformF64_RealInputSamples_Step_64_12_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f64inputFileStep128, sizeof(f64inputFileStep128), "%s%s%s", Patterns_PATH, TransformF64, "RealInputSamples_Step_128_13_f64.txt");
#else
	f64inputFileStep128 = TransformF64_RealInputSamples_Step_128_13_f64;
	f64inputFileStep128Len = sizeof(TransformF64_RealInputSamples_Step_128_13_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f64inputFileStep256, sizeof(f64inputFileStep256), "%s%s%s", Patterns_PATH, TransformF64, "RealInputSamples_Step_256_14_f64.txt");
#else
	f64inputFileStep256 = TransformF64_RealInputSamples_Step_256_14_f64;
	f64inputFileStep256Len = sizeof(TransformF64_RealInputSamples_Step_256_14_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f64inputFileStep512, sizeof(f64inputFileStep512), "%s%s%s", Patterns_PATH, TransformF64, "RealInputSamples_Step_512_15_f64.txt");
#else
	f64inputFileStep512 = TransformF64_RealInputSamples_Step_512_15_f64;
	f64inputFileStep512Len = sizeof(TransformF64_RealInputSamples_Step_512_15_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f64inputFileStep1024, sizeof(f64inputFileStep1024), "%s%s%s", Patterns_PATH, TransformF64, "RealInputSamples_Step_1024_16_f64.txt");
#else
	f64inputFileStep1024 = TransformF64_RealInputSamples_Step_1024_16_f64;
	f64inputFileStep1024Len = sizeof(TransformF64_RealInputSamples_Step_1024_16_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f64inputFileStep2048, sizeof(f64inputFileStep2048), "%s%s%s", Patterns_PATH, TransformF64, "RealInputSamples_Step_2048_17_f64.txt");
#else
	f64inputFileStep2048 = TransformF64_RealInputSamples_Step_2048_17_f64;
	f64inputFileStep2048Len = sizeof(TransformF64_RealInputSamples_Step_2048_17_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f64inputFileStep4096, sizeof(f64inputFileStep4096), "%s%s%s", Patterns_PATH, TransformF64, "RealInputSamples_Step_4096_18_f64.txt");
#else
	f64inputFileStep4096 = TransformF64_RealInputSamples_Step_4096_18_f64;
	f64inputFileStep4096Len = sizeof(TransformF64_RealInputSamples_Step_4096_18_f64);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(f64IFTinputFileStep16, sizeof(f64IFTinputFileStep16), "%s%s%s", Patterns_PATH, TransformF64, "RealInputIFFTSamples_Step_16_10_f64.txt");
#else
	f64IFTinputFileStep16 = TransformF64_RealInputIFFTSamples_Step_16_10_f64;
	f64IFTinputFileStep16Len = sizeof(TransformF64_RealInputIFFTSamples_Step_16_10_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f64IFTinputFileStep32, sizeof(f64IFTinputFileStep32), "%s%s%s", Patterns_PATH, TransformF64, "RealInputIFFTSamples_Step_32_11_f64.txt");
#else
	f64IFTinputFileStep32 = TransformF64_RealInputIFFTSamples_Step_32_11_f64;
	f64IFTinputFileStep32Len = sizeof(TransformF64_RealInputIFFTSamples_Step_32_11_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f64IFTinputFileStep64, sizeof(f64IFTinputFileStep64), "%s%s%s", Patterns_PATH, TransformF64, "RealInputIFFTSamples_Step_64_12_f64.txt");
#else
	f64IFTinputFileStep64 = TransformF64_RealInputIFFTSamples_Step_64_12_f64;
	f64IFTinputFileStep64Len = sizeof(TransformF64_RealInputIFFTSamples_Step_64_12_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f64IFTinputFileStep128, sizeof(f64IFTinputFileStep128), "%s%s%s", Patterns_PATH, TransformF64, "RealInputIFFTSamples_Step_128_13_f64.txt");
#else
	f64IFTinputFileStep128 = TransformF64_RealInputIFFTSamples_Step_128_13_f64;
	f64IFTinputFileStep128Len = sizeof(TransformF64_RealInputIFFTSamples_Step_128_13_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f64IFTinputFileStep256, sizeof(f64IFTinputFileStep256), "%s%s%s", Patterns_PATH, TransformF64, "RealInputIFFTSamples_Step_256_14_f64.txt");
#else
	f64IFTinputFileStep256 = TransformF64_RealInputIFFTSamples_Step_256_14_f64;
	f64IFTinputFileStep256Len = sizeof(TransformF64_RealInputIFFTSamples_Step_256_14_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f64IFTinputFileStep512, sizeof(f64IFTinputFileStep512), "%s%s%s", Patterns_PATH, TransformF64, "RealInputIFFTSamples_Step_512_15_f64.txt");
#else
	f64IFTinputFileStep512 = TransformF64_RealInputIFFTSamples_Step_512_15_f64;
	f64IFTinputFileStep512Len = sizeof(TransformF64_RealInputIFFTSamples_Step_512_15_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f64IFTinputFileStep1024, sizeof(f64IFTinputFileStep1024), "%s%s%s", Patterns_PATH, TransformF64, "RealInputIFFTSamples_Step_1024_16_f64.txt");
#else
	f64IFTinputFileStep1024 = TransformF64_RealInputIFFTSamples_Step_1024_16_f64;
	f64IFTinputFileStep1024Len = sizeof(TransformF64_RealInputIFFTSamples_Step_1024_16_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f64IFTinputFileStep2048, sizeof(f64IFTinputFileStep2048), "%s%s%s", Patterns_PATH, TransformF64, "RealInputIFFTSamples_Step_2048_17_f64.txt");
#else
	f64IFTinputFileStep2048 = TransformF64_RealInputIFFTSamples_Step_2048_17_f64;
	f64IFTinputFileStep2048Len = sizeof(TransformF64_RealInputIFFTSamples_Step_2048_17_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f64IFTinputFileStep4096, sizeof(f64IFTinputFileStep4096), "%s%s%s", Patterns_PATH, TransformF64, "RealInputIFFTSamples_Step_4096_18_f64.txt");
#else
	f64IFTinputFileStep4096 = TransformF64_RealInputIFFTSamples_Step_4096_18_f64;
	f64IFTinputFileStep4096Len = sizeof(TransformF64_RealInputIFFTSamples_Step_4096_18_f64);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(f64referenceFileStep16, sizeof(f64referenceFileStep16), "%s%s%s", Patterns_PATH, TransformF64, "RealFFTSamples_Step_16_10_f64.txt");
#else
	f64referenceFileStep16 = TransformF64_RealFFTSamples_Step_16_10_f64;
	f64referenceFileStep16Len = sizeof(TransformF64_RealFFTSamples_Step_16_10_f64)/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f64referenceFileStep32, sizeof(f64referenceFileStep32), "%s%s%s", Patterns_PATH, TransformF64, "RealFFTSamples_Step_32_11_f64.txt");
#else
	f64referenceFileStep32 = TransformF64_RealFFTSamples_Step_32_11_f64;
	f64referenceFileStep32Len = sizeof(TransformF64_RealFFTSamples_Step_32_11_f64)/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f64referenceFileStep64, sizeof(f64referenceFileStep64), "%s%s%s", Patterns_PATH, TransformF64, "RealFFTSamples_Step_64_12_f64.txt");
#else
	f64referenceFileStep64 = TransformF64_RealFFTSamples_Step_64_12_f64;
	f64referenceFileStep64Len = sizeof(TransformF64_RealFFTSamples_Step_64_12_f64)/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f64referenceFileStep128, sizeof(f64referenceFileStep128), "%s%s%s", Patterns_PATH, TransformF64, "RealFFTSamples_Step_128_13_f64.txt");
#else
	f64referenceFileStep128 = TransformF64_RealFFTSamples_Step_128_13_f64;
	f64referenceFileStep128Len = sizeof(TransformF64_RealFFTSamples_Step_128_13_f64)/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f64referenceFileStep256, sizeof(f64referenceFileStep256), "%s%s%s", Patterns_PATH, TransformF64, "RealFFTSamples_Step_256_14_f64.txt");
#else
	f64referenceFileStep256 = TransformF64_RealFFTSamples_Step_256_14_f64;
	f64referenceFileStep256Len = sizeof(TransformF64_RealFFTSamples_Step_256_14_f64)/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f64referenceFileStep512, sizeof(f64referenceFileStep512), "%s%s%s", Patterns_PATH, TransformF64, "RealFFTSamples_Step_512_15_f64.txt");
#else
	f64referenceFileStep512 = TransformF64_RealFFTSamples_Step_512_15_f64;
	f64referenceFileStep512Len = sizeof(TransformF64_RealFFTSamples_Step_512_15_f64)/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f64referenceFileStep1024, sizeof(f64referenceFileStep1024), "%s%s%s", Patterns_PATH, TransformF64, "RealFFTSamples_Step_1024_16_f64.txt");
#else
	f64referenceFileStep1024 = TransformF64_RealFFTSamples_Step_1024_16_f64;
	f64referenceFileStep1024Len = sizeof(TransformF64_RealFFTSamples_Step_1024_16_f64)/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f64referenceFileStep2048, sizeof(f64referenceFileStep2048), "%s%s%s", Patterns_PATH, TransformF64, "RealFFTSamples_Step_2048_17_f64.txt");
#else
	f64referenceFileStep2048 = TransformF64_RealFFTSamples_Step_2048_17_f64;
	f64referenceFileStep2048Len = sizeof(TransformF64_RealFFTSamples_Step_2048_17_f64)/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f64referenceFileStep4096, sizeof(f64referenceFileStep4096), "%s%s%s", Patterns_PATH, TransformF64, "RealFFTSamples_Step_4096_18_f64.txt");
#else
	f64referenceFileStep4096 = TransformF64_RealFFTSamples_Step_4096_18_f64;
	f64referenceFileStep4096Len = sizeof(TransformF64_RealFFTSamples_Step_4096_18_f64)/sizeof(f64);
#endif


    // load input data
#if defined(NOT_EMBEDDED)
	load_data_f64(f64inputFileNoisy32, &paramCountInputNoisy32, f64inputNoisy32);
#else
	paramCountInputNoisy32 = f64inputFileNoisy32Len;
	load_data_f64(f64inputFileNoisy32, paramCountInputNoisy32, f64inputNoisy32);
	paramCountInputNoisy32 = paramCountInputNoisy32/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(f64inputFileNoisy64, &paramCountInputNoisy64, f64inputNoisy64);
#else
	paramCountInputNoisy64 = f64inputFileNoisy64Len;
	load_data_f64(f64inputFileNoisy64, paramCountInputNoisy64, f64inputNoisy64);
	paramCountInputNoisy64 = paramCountInputNoisy64/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(f64inputFileNoisy128, &paramCountInputNoisy128, f64inputNoisy128);
#else
	paramCountInputNoisy128 = f64inputFileNoisy128Len;
	load_data_f64(f64inputFileNoisy128, paramCountInputNoisy128, f64inputNoisy128);
	paramCountInputNoisy128 = paramCountInputNoisy128/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(f64inputFileNoisy256, &paramCountInputNoisy256, f64inputNoisy256);
#else
	paramCountInputNoisy256 = f64inputFileNoisy256Len;
	load_data_f64(f64inputFileNoisy256, paramCountInputNoisy256, f64inputNoisy256);
	paramCountInputNoisy256 = paramCountInputNoisy256/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(f64inputFileNoisy512, &paramCountInputNoisy512, f64inputNoisy512);
#else
	paramCountInputNoisy512 = f64inputFileNoisy512Len;
	load_data_f64(f64inputFileNoisy512, paramCountInputNoisy512, f64inputNoisy512);
	paramCountInputNoisy512 = paramCountInputNoisy512/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(f64inputFileNoisy1024, &paramCountInputNoisy1024, f64inputNoisy1024);
#else
	paramCountInputNoisy1024 = f64inputFileNoisy1024Len;
	load_data_f64(f64inputFileNoisy1024, paramCountInputNoisy1024, f64inputNoisy1024);
	paramCountInputNoisy1024 = paramCountInputNoisy1024/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(f64inputFileNoisy2048, &paramCountInputNoisy2048, f64inputNoisy2048);
#else
	paramCountInputNoisy2048 = f64inputFileNoisy2048Len;
	load_data_f64(f64inputFileNoisy2048, paramCountInputNoisy2048, f64inputNoisy2048);
	paramCountInputNoisy2048 = paramCountInputNoisy2048/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(f64inputFileNoisy4096, &paramCountInputNoisy4096, f64inputNoisy4096);
#else
	paramCountInputNoisy4096 = f64inputFileNoisy4096Len;
	load_data_f64(f64inputFileNoisy4096, paramCountInputNoisy4096, f64inputNoisy4096);
	paramCountInputNoisy4096 = paramCountInputNoisy4096/sizeof(f64);
#endif


#if defined(NOT_EMBEDDED)
	load_data_f64(f64IFTinputFileNoisy32, &IFTparamCountInputNoisy32, f64IFTinputNoisy32);
#else
	IFTparamCountInputNoisy32 = f64IFTinputFileNoisy32Len;
	load_data_f64(f64IFTinputFileNoisy32, IFTparamCountInputNoisy32, f64IFTinputNoisy32);
	IFTparamCountInputNoisy32 = IFTparamCountInputNoisy32/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(f64IFTinputFileNoisy64, &IFTparamCountInputNoisy64, f64IFTinputNoisy64);
#else
	IFTparamCountInputNoisy64 = f64IFTinputFileNoisy64Len;
	load_data_f64(f64IFTinputFileNoisy64, IFTparamCountInputNoisy64, f64IFTinputNoisy64);
	IFTparamCountInputNoisy64 = IFTparamCountInputNoisy64/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(f64IFTinputFileNoisy128, &IFTparamCountInputNoisy128, f64IFTinputNoisy128);
#else
	IFTparamCountInputNoisy128 = f64IFTinputFileNoisy128Len;
	load_data_f64(f64IFTinputFileNoisy128, IFTparamCountInputNoisy128, f64IFTinputNoisy128);
	IFTparamCountInputNoisy128 = IFTparamCountInputNoisy128/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(f64IFTinputFileNoisy256, &IFTparamCountInputNoisy256, f64IFTinputNoisy256);
#else
	IFTparamCountInputNoisy256 = f64IFTinputFileNoisy256Len;
	load_data_f64(f64IFTinputFileNoisy256, IFTparamCountInputNoisy256, f64IFTinputNoisy256);
	IFTparamCountInputNoisy256 = IFTparamCountInputNoisy256/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(f64IFTinputFileNoisy512, &IFTparamCountInputNoisy512, f64IFTinputNoisy512);
#else
	IFTparamCountInputNoisy512 = f64IFTinputFileNoisy512Len;
	load_data_f64(f64IFTinputFileNoisy512, IFTparamCountInputNoisy512, f64IFTinputNoisy512);
	IFTparamCountInputNoisy512 = IFTparamCountInputNoisy512/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(f64IFTinputFileNoisy1024, &IFTparamCountInputNoisy1024, f64IFTinputNoisy1024);
#else
	IFTparamCountInputNoisy1024 = f64IFTinputFileNoisy1024Len;
	load_data_f64(f64IFTinputFileNoisy1024, IFTparamCountInputNoisy1024, f64IFTinputNoisy1024);
	IFTparamCountInputNoisy1024 = IFTparamCountInputNoisy1024/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(f64IFTinputFileNoisy2048, &IFTparamCountInputNoisy2048, f64IFTinputNoisy2048);
#else
	IFTparamCountInputNoisy2048 = f64IFTinputFileNoisy2048Len;
	load_data_f64(f64IFTinputFileNoisy2048, IFTparamCountInputNoisy2048, f64IFTinputNoisy2048);
	IFTparamCountInputNoisy2048 = IFTparamCountInputNoisy2048/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(f64IFTinputFileNoisy4096, &IFTparamCountInputNoisy4096, f64IFTinputNoisy4096);
#else
	IFTparamCountInputNoisy4096 = f64IFTinputFileNoisy4096Len;
	load_data_f64(f64IFTinputFileNoisy4096, IFTparamCountInputNoisy4096, f64IFTinputNoisy4096);
	IFTparamCountInputNoisy4096 = IFTparamCountInputNoisy4096/sizeof(f64);
#endif


#if defined(NOT_EMBEDDED)
	load_data_f64(f64inputFileStep16, &paramCountInputStep16, f64inputStep16);
#else
	paramCountInputStep16 = f64inputFileStep16Len;
	load_data_f64(f64inputFileStep16, paramCountInputStep16, f64inputStep16);
	paramCountInputStep16 = paramCountInputStep16/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(f64inputFileStep32, &paramCountInputStep32, f64inputStep32);
#else
	paramCountInputStep32 = f64inputFileStep32Len;
	load_data_f64(f64inputFileStep32, paramCountInputStep32, f64inputStep32);
	paramCountInputStep32 = paramCountInputStep32/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(f64inputFileStep64, &paramCountInputStep64, f64inputStep64);
#else
	paramCountInputStep64 = f64inputFileStep64Len;
	load_data_f64(f64inputFileStep64, paramCountInputStep64, f64inputStep64);
	paramCountInputStep64 = paramCountInputStep64/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(f64inputFileStep128, &paramCountInputStep128, f64inputStep128);
#else
	paramCountInputStep128 = f64inputFileStep128Len;
	load_data_f64(f64inputFileStep128, paramCountInputStep128, f64inputStep128);
	paramCountInputStep128 = paramCountInputStep128/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(f64inputFileStep256, &paramCountInputStep256, f64inputStep256);
#else
	paramCountInputStep256 = f64inputFileStep256Len;
	load_data_f64(f64inputFileStep256, paramCountInputStep256, f64inputStep256);
	paramCountInputStep256 = paramCountInputStep256/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(f64inputFileStep512, &paramCountInputStep512, f64inputStep512);
#else
	paramCountInputStep512 = f64inputFileStep512Len;
	load_data_f64(f64inputFileStep512, paramCountInputStep512, f64inputStep512);
	paramCountInputStep512 = paramCountInputStep512/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(f64inputFileStep1024, &paramCountInputStep1024, f64inputStep1024);
#else
	paramCountInputStep1024 = f64inputFileStep1024Len;
	load_data_f64(f64inputFileStep1024, paramCountInputStep1024, f64inputStep1024);
	paramCountInputStep1024 = paramCountInputStep1024/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(f64inputFileStep2048, &paramCountInputStep2048, f64inputStep2048);
#else
	paramCountInputStep2048 = f64inputFileStep2048Len;
	load_data_f64(f64inputFileStep2048, paramCountInputStep2048, f64inputStep2048);
	paramCountInputStep2048 = paramCountInputStep2048/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(f64inputFileStep4096, &paramCountInputStep4096, f64inputStep4096);
#else
	paramCountInputStep4096 = f64inputFileStep4096Len;
	load_data_f64(f64inputFileStep4096, paramCountInputStep4096, f64inputStep4096);
	paramCountInputStep4096 = paramCountInputStep4096/sizeof(f64);
#endif


#if defined(NOT_EMBEDDED)
	load_data_f64(f64IFTinputFileStep16, &IFTparamCountInputStep16, f64IFTinputStep16);
#else
	IFTparamCountInputStep16 = f64IFTinputFileStep16Len;
	load_data_f64(f64IFTinputFileStep16, IFTparamCountInputStep16, f64IFTinputStep16);
	IFTparamCountInputStep16 = IFTparamCountInputStep16/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(f64IFTinputFileStep32, &IFTparamCountInputStep32, f64IFTinputStep32);
#else
	IFTparamCountInputStep32 = f64IFTinputFileStep32Len;
	load_data_f64(f64IFTinputFileStep32, IFTparamCountInputStep32, f64IFTinputStep32);
	IFTparamCountInputStep32 = IFTparamCountInputStep32/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(f64IFTinputFileStep64, &IFTparamCountInputStep64, f64IFTinputStep64);
#else
	IFTparamCountInputStep64 = f64IFTinputFileStep64Len;
	load_data_f64(f64IFTinputFileStep64, IFTparamCountInputStep64, f64IFTinputStep64);
	IFTparamCountInputStep64 = IFTparamCountInputStep64/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(f64IFTinputFileStep128, &IFTparamCountInputStep128, f64IFTinputStep128);
#else
	IFTparamCountInputStep128 = f64IFTinputFileStep128Len;
	load_data_f64(f64IFTinputFileStep128, IFTparamCountInputStep128, f64IFTinputStep128);
	IFTparamCountInputStep128 = IFTparamCountInputStep128/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(f64IFTinputFileStep256, &IFTparamCountInputStep256, f64IFTinputStep256);
#else
	IFTparamCountInputStep256 = f64IFTinputFileStep256Len;
	load_data_f64(f64IFTinputFileStep256, IFTparamCountInputStep256, f64IFTinputStep256);
	IFTparamCountInputStep256 = IFTparamCountInputStep256/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(f64IFTinputFileStep512, &IFTparamCountInputStep512, f64IFTinputStep512);
#else
	IFTparamCountInputStep512 = f64IFTinputFileStep512Len;
	load_data_f64(f64IFTinputFileStep512, IFTparamCountInputStep512, f64IFTinputStep512);
	IFTparamCountInputStep512 = IFTparamCountInputStep512/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(f64IFTinputFileStep1024, &IFTparamCountInputStep1024, f64IFTinputStep1024);
#else
	IFTparamCountInputStep1024 = f64IFTinputFileStep1024Len;
	load_data_f64(f64IFTinputFileStep1024, IFTparamCountInputStep1024, f64IFTinputStep1024);
	IFTparamCountInputStep1024 = IFTparamCountInputStep1024/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(f64IFTinputFileStep2048, &IFTparamCountInputStep2048, f64IFTinputStep2048);
#else
	IFTparamCountInputStep2048 = f64IFTinputFileStep2048Len;
	load_data_f64(f64IFTinputFileStep2048, IFTparamCountInputStep2048, f64IFTinputStep2048);
	IFTparamCountInputStep2048 = IFTparamCountInputStep2048/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(f64IFTinputFileStep4096, &IFTparamCountInputStep4096, f64IFTinputStep4096);
#else
	IFTparamCountInputStep4096 = f64IFTinputFileStep4096Len;
	load_data_f64(f64IFTinputFileStep4096, IFTparamCountInputStep4096, f64IFTinputStep4096);
	IFTparamCountInputStep4096 = IFTparamCountInputStep4096/sizeof(f64);
#endif


    f64 f64output[MAX_SIZE] = {0};
    f64 f64changed[MAX_SIZE] = {0};

    int ifft;
    mips_status status;
    mips_rfft_fast_instance_f64 instRfftF64;
// =====================
    printf("== mips_rfft_fast_f64 Noisy_32 test ==  \n");

        memcpy(f64changed,f64inputNoisy32,sizeof(f64)*paramCountInputNoisy32);

        status=mips_rfft_fast_init_f64(&instRfftF64,32);
        ifft = 0;
   
        mips_rfft_fast_f64(&(instRfftF64), f64changed, f64output, ifft);

    printf("mips_rfft_fast_f64 Noisy_32 finish \n");

    printf("mips_rfft_fast_f64 Noisy_32 checking \n\n");
#if defined(NOT_EMBEDDED)
	snr_check_f64(f64referenceFileNoisy32, f64output, 0, (f64)SNR_THRESHOLD);
#else
	snr_check_special_f64(f64referenceFileNoisy32, f64output, f64referenceFileNoisy32Len, (f64)SNR_THRESHOLD);
#endif


    printf("\n== mips_rfft_fast_f64 Noisy_32 check done  == \n\n");

// =====================
    printf("== mips_rfft_fast_f64 Noisy_32 test ==  \n");

        memcpy(f64changed,f64IFTinputNoisy32,sizeof(f64)*IFTparamCountInputNoisy32);

        status=mips_rfft_fast_init_f64(&instRfftF64,32);
        ifft = 1;
   
        mips_rfft_fast_f64(&(instRfftF64), f64changed, f64output, ifft);

    printf("mips_rfft_fast_f64 Noisy_32 finish \n");

    printf("mips_rfft_fast_f64 Noisy_32 checking \n\n");
#if defined(NOT_EMBEDDED)
	snr_check_f64(f64inputFileNoisy32, f64output, 0, (f64)SNR_THRESHOLD);
#else
	snr_check_special_f64(f64inputNoisy32, f64output, paramCountInputNoisy32, (f64)SNR_THRESHOLD);
#endif


    printf("\n== mips_rfft_fast_f64 Noisy_32 check done  == \n\n");

// =====================
    printf("== mips_rfft_fast_f64 Noisy_64 test ==  \n");

        memcpy(f64changed,f64inputNoisy64,sizeof(f64)*paramCountInputNoisy64);

        status=mips_rfft_fast_init_f64(&instRfftF64,64);
        ifft = 0;
   
        mips_rfft_fast_f64(&(instRfftF64), f64changed, f64output, ifft);

    printf("mips_rfft_fast_f64 Noisy_64 finish \n");

    printf("mips_rfft_fast_f64 Noisy_64 checking \n\n");
#if defined(NOT_EMBEDDED)
	snr_check_f64(f64referenceFileNoisy64, f64output, 0, (f64)SNR_THRESHOLD);
#else
	snr_check_special_f64(f64referenceFileNoisy64, f64output, f64referenceFileNoisy64Len, (f64)SNR_THRESHOLD);
#endif


    printf("\n== mips_rfft_fast_f64 Noisy_64 check done  == \n\n");

// =====================
    printf("== mips_rfft_fast_f64 Noisy_64 test ==  \n");

        memcpy(f64changed,f64IFTinputNoisy64,sizeof(f64)*IFTparamCountInputNoisy64);

        status=mips_rfft_fast_init_f64(&instRfftF64,64);
        ifft = 1;
   
        mips_rfft_fast_f64(&(instRfftF64), f64changed, f64output, ifft);

    printf("mips_rfft_fast_f64 Noisy_64 finish \n");

    printf("mips_rfft_fast_f64 Noisy_64 checking \n\n");
#if defined(NOT_EMBEDDED)
	snr_check_f64(f64inputFileNoisy64, f64output, 0, (f64)SNR_THRESHOLD);
#else
	snr_check_special_f64(f64inputNoisy64, f64output, paramCountInputNoisy64, (f64)SNR_THRESHOLD);
#endif


    printf("\n== mips_rfft_fast_f64 Noisy_32 check done  == \n\n");

// =====================
    printf("== mips_rfft_fast_f64 Noisy_128 test ==  \n");

        memcpy(f64changed,f64inputNoisy128,sizeof(f64)*paramCountInputNoisy128);

        status=mips_rfft_fast_init_f64(&instRfftF64,128);
        ifft = 0;
   
        mips_rfft_fast_f64(&(instRfftF64), f64changed, f64output, ifft);

    printf("mips_rfft_fast_f64 Noisy_128 finish \n");

    printf("mips_rfft_fast_f64 Noisy_128 checking \n\n");
#if defined(NOT_EMBEDDED)
	snr_check_f64(f64referenceFileNoisy128, f64output, 0, (f64)SNR_THRESHOLD);
#else
	snr_check_special_f64(f64referenceFileNoisy128, f64output, f64referenceFileNoisy128Len, (f64)SNR_THRESHOLD);
#endif


    printf("\n== mips_rfft_fast_f64 Noisy_128 check done  == \n\n");

// =====================
    printf("== mips_rfft_fast_f64 Noisy_128 test ==  \n");

        memcpy(f64changed,f64IFTinputNoisy128,sizeof(f64)*IFTparamCountInputNoisy128);

        status=mips_rfft_fast_init_f64(&instRfftF64,128);
        ifft = 1;
   
        mips_rfft_fast_f64(&(instRfftF64), f64changed, f64output, ifft);

    printf("mips_rfft_fast_f64 Noisy_128 finish \n");

    printf("mips_rfft_fast_f64 Noisy_128 checking \n\n");
#if defined(NOT_EMBEDDED)
	snr_check_f64(f64inputFileNoisy128, f64output, 0, (f64)SNR_THRESHOLD);
#else
	snr_check_special_f64(f64inputNoisy128, f64output, paramCountInputNoisy128, (f64)SNR_THRESHOLD);
#endif


    printf("\n== mips_rfft_fast_f128 Noisy_32 check done  == \n\n");

// =====================
    printf("== mips_rfft_fast_f64 Noisy_256 test ==  \n");

        memcpy(f64changed,f64inputNoisy256,sizeof(f64)*paramCountInputNoisy256);

        status=mips_rfft_fast_init_f64(&instRfftF64,256);
        ifft = 0;
   
        mips_rfft_fast_f64(&(instRfftF64), f64changed, f64output, ifft);

    printf("mips_rfft_fast_f64 Noisy_256 finish \n");

    printf("mips_rfft_fast_f64 Noisy_256 checking \n\n");
#if defined(NOT_EMBEDDED)
	snr_check_f64(f64referenceFileNoisy256, f64output, 0, (f64)SNR_THRESHOLD);
#else
	snr_check_special_f64(f64referenceFileNoisy256, f64output, f64referenceFileNoisy256Len, (f64)SNR_THRESHOLD);
#endif


    printf("\n== mips_rfft_fast_f64 Noisy_256 check done  == \n\n");

// =====================
    printf("== mips_rfft_fast_f64 Noisy_256 test ==  \n");

        memcpy(f64changed,f64IFTinputNoisy256,sizeof(f64)*IFTparamCountInputNoisy256);

        status=mips_rfft_fast_init_f64(&instRfftF64,256);
        ifft = 1;
   
        mips_rfft_fast_f64(&(instRfftF64), f64changed, f64output, ifft);

    printf("mips_rfft_fast_f64 Noisy_256 finish \n");

    printf("mips_rfft_fast_f64 Noisy_256 checking \n\n");
#if defined(NOT_EMBEDDED)
	snr_check_f64(f64inputFileNoisy256, f64output, 0, (f64)SNR_THRESHOLD);
#else
	snr_check_special_f64(f64inputNoisy256, f64output, paramCountInputNoisy256, (f64)SNR_THRESHOLD);
#endif


    printf("\n== mips_rfft_fast_f256 Noisy_32 check done  == \n\n");

// =====================
    printf("== mips_rfft_fast_f64 Noisy_512 test ==  \n");

        memcpy(f64changed,f64inputNoisy512,sizeof(f64)*paramCountInputNoisy512);

        status=mips_rfft_fast_init_f64(&instRfftF64,512);
        ifft = 0;
   
        mips_rfft_fast_f64(&(instRfftF64), f64changed, f64output, ifft);

    printf("mips_rfft_fast_f64 Noisy_512 finish \n");

    printf("mips_rfft_fast_f64 Noisy_512 checking \n\n");
#if defined(NOT_EMBEDDED)
	snr_check_f64(f64referenceFileNoisy512, f64output, 0, (f64)SNR_THRESHOLD);
#else
	snr_check_special_f64(f64referenceFileNoisy512, f64output, f64referenceFileNoisy512Len, (f64)SNR_THRESHOLD);
#endif


    printf("\n== mips_rfft_fast_f64 Noisy_512 check done  == \n\n");

// =====================
    printf("== mips_rfft_fast_f64 Noisy_512 test ==  \n");

        memcpy(f64changed,f64IFTinputNoisy512,sizeof(f64)*IFTparamCountInputNoisy512);

        status=mips_rfft_fast_init_f64(&instRfftF64,512);
        ifft = 1;
   
        mips_rfft_fast_f64(&(instRfftF64), f64changed, f64output, ifft);

    printf("mips_rfft_fast_f64 Noisy_512 finish \n");

    printf("mips_rfft_fast_f64 Noisy_512 checking \n\n");
#if defined(NOT_EMBEDDED)
	snr_check_f64(f64inputFileNoisy512, f64output, 0, (f64)SNR_THRESHOLD);
#else
	snr_check_special_f64(f64inputNoisy512, f64output, paramCountInputNoisy512, (f64)SNR_THRESHOLD);
#endif


    printf("\n== mips_rfft_fast_f512 Noisy_32 check done  == \n\n");

// =====================
    printf("== mips_rfft_fast_f64 Noisy_1024 test ==  \n");

        memcpy(f64changed,f64inputNoisy1024,sizeof(f64)*paramCountInputNoisy1024);

        status=mips_rfft_fast_init_f64(&instRfftF64,1024);
        ifft = 0;
   
        mips_rfft_fast_f64(&(instRfftF64), f64changed, f64output, ifft);

    printf("mips_rfft_fast_f64 Noisy_1024 finish \n");

    printf("mips_rfft_fast_f64 Noisy_1024 checking \n\n");
#if defined(NOT_EMBEDDED)
	snr_check_f64(f64referenceFileNoisy1024, f64output, 0, (f64)SNR_THRESHOLD);
#else
	snr_check_special_f64(f64referenceFileNoisy1024, f64output, f64referenceFileNoisy1024Len, (f64)SNR_THRESHOLD);
#endif


    printf("\n== mips_rfft_fast_f64 Noisy_1024 check done  == \n\n");

// =====================
    printf("== mips_rfft_fast_f64 Noisy_1024 test ==  \n");

        memcpy(f64changed,f64IFTinputNoisy1024,sizeof(f64)*IFTparamCountInputNoisy1024);

        status=mips_rfft_fast_init_f64(&instRfftF64,1024);
        ifft = 1;
   
        mips_rfft_fast_f64(&(instRfftF64), f64changed, f64output, ifft);

    printf("mips_rfft_fast_f64 Noisy_1024 finish \n");

    printf("mips_rfft_fast_f64 Noisy_1024 checking \n\n");
#if defined(NOT_EMBEDDED)
	snr_check_f64(f64inputFileNoisy1024, f64output, 0, (f64)SNR_THRESHOLD);
#else
	snr_check_special_f64(f64inputNoisy1024, f64output, paramCountInputNoisy1024, (f64)SNR_THRESHOLD);
#endif


    printf("\n== mips_rfft_fast_f1024 Noisy_32 check done  == \n\n");

// =====================
    printf("== mips_rfft_fast_f64 Noisy_2048 test ==  \n");

        memcpy(f64changed,f64inputNoisy2048,sizeof(f64)*paramCountInputNoisy2048);

        status=mips_rfft_fast_init_f64(&instRfftF64,2048);
        ifft = 0;
   
        mips_rfft_fast_f64(&(instRfftF64), f64changed, f64output, ifft);

    printf("mips_rfft_fast_f64 Noisy_2048 finish \n");

    printf("mips_rfft_fast_f64 Noisy_2048 checking \n\n");
#if defined(NOT_EMBEDDED)
	snr_check_f64(f64referenceFileNoisy2048, f64output, 0, (f64)SNR_THRESHOLD);
#else
	snr_check_special_f64(f64referenceFileNoisy2048, f64output, f64referenceFileNoisy2048Len, (f64)SNR_THRESHOLD);
#endif


    printf("\n== mips_rfft_fast_f64 Noisy_2048 check done  == \n\n");

// =====================
    printf("== mips_rfft_fast_f64 Noisy_2048 test ==  \n");

        memcpy(f64changed,f64IFTinputNoisy2048,sizeof(f64)*IFTparamCountInputNoisy2048);

        status=mips_rfft_fast_init_f64(&instRfftF64,2048);
        ifft = 1;
   
        mips_rfft_fast_f64(&(instRfftF64), f64changed, f64output, ifft);

    printf("mips_rfft_fast_f64 Noisy_2048 finish \n");

    printf("mips_rfft_fast_f64 Noisy_2048 checking \n\n");
#if defined(NOT_EMBEDDED)
	snr_check_f64(f64inputFileNoisy2048, f64output, 0, (f64)SNR_THRESHOLD);
#else
	snr_check_special_f64(f64inputNoisy2048, f64output, paramCountInputNoisy2048, (f64)SNR_THRESHOLD);
#endif


    printf("\n== mips_rfft_fast_f64 Noisy_2048 check done  == \n\n");

// =====================
    printf("== mips_rfft_fast_f64 Noisy_4096 test ==  \n");

        memcpy(f64changed,f64inputNoisy4096,sizeof(f64)*paramCountInputNoisy4096);

        status=mips_rfft_fast_init_f64(&instRfftF64,4096);
        ifft = 0;
   
        mips_rfft_fast_f64(&(instRfftF64), f64changed, f64output, ifft);

    printf("mips_rfft_fast_f64 Noisy_4096 finish \n");

    printf("mips_rfft_fast_f64 Noisy_4096 checking \n\n");
#if defined(NOT_EMBEDDED)
	snr_check_f64(f64referenceFileNoisy4096, f64output, 0, (f64)SNR_THRESHOLD);
#else
	snr_check_special_f64(f64referenceFileNoisy4096, f64output, f64referenceFileNoisy4096Len, (f64)SNR_THRESHOLD);
#endif


    printf("\n== mips_rfft_fast_f64 Noisy_4096 check done  == \n\n");

// =====================

    printf("== mips_rfft_fast_f64 Noisy_4096 test ==  \n");

        memcpy(f64changed,f64IFTinputNoisy4096,sizeof(f64)*IFTparamCountInputNoisy4096);

        status=mips_rfft_fast_init_f64(&instRfftF64,4096);
        ifft = 1;
   
        mips_rfft_fast_f64(&(instRfftF64), f64changed, f64output, ifft);

    printf("mips_rfft_fast_f64 Noisy_4096 finish \n");

    printf("mips_rfft_fast_f64 Noisy_4096 checking \n\n");
#if defined(NOT_EMBEDDED)
	snr_check_f64(f64inputFileNoisy4096, f64output, 0, (f64)SNR_THRESHOLD);
#else
	snr_check_special_f64(f64inputNoisy4096, f64output, paramCountInputNoisy4096, (f64)SNR_THRESHOLD);
#endif


    printf("\n== mips_rfft_fast_f64 Noisy_4096 check done  == \n\n");

    f64 f64changedstep[MAX_SIZE] = {0};
    f64 f64outputstep[MAX_SIZE] = {0};
 // =====================
    printf("== mips_rfft_fast_f64 Step_32 test ==  \n");

        memcpy(f64changedstep,f64inputStep32,sizeof(f64)*paramCountInputStep32);

        status=mips_rfft_fast_init_f64(&instRfftF64,32);
        ifft = 0;
   
        mips_rfft_fast_f64(&(instRfftF64), f64changedstep, f64outputstep, ifft);

    printf("mips_rfft_fast_f64 Step_32 finish \n");

    printf("mips_rfft_fast_f64 Step_32 checking \n\n");
#if defined(NOT_EMBEDDED)
	snr_check_f64(f64referenceFileStep32, f64outputstep, 0, (f64)SNR_THRESHOLD);
#else
	snr_check_special_f64(f64referenceFileStep32, f64outputstep, f64referenceFileStep32Len, (f64)SNR_THRESHOLD);
#endif


    printf("\n== mips_rfft_fast_f64 Step_32 check done  == \n\n");

// =====================
    printf("== mips_rfft_fast_f64 Step_32 test ==  \n");

        memcpy(f64changedstep,f64IFTinputStep32,sizeof(f64)*IFTparamCountInputStep32);

        status=mips_rfft_fast_init_f64(&instRfftF64,32);
        ifft = 1;
   
        mips_rfft_fast_f64(&(instRfftF64), f64changedstep, f64outputstep, ifft);

    printf("mips_rfft_fast_f64 Step_32 finish \n");

    printf("mips_rfft_fast_f64 Step_32 checking \n\n");
#if defined(NOT_EMBEDDED)
	snr_check_f64(f64inputFileStep32, f64outputstep, 0, (f64)SNR_THRESHOLD);
#else
	snr_check_special_f64(f64inputStep32, f64outputstep, paramCountInputStep32, (f64)SNR_THRESHOLD);
#endif


    printf("\n== mips_rfft_fast_f64 Step_32 check done  == \n\n");

// =====================
    printf("== mips_rfft_fast_f64 Step_64 test ==  \n");

        memcpy(f64changedstep,f64inputStep64,sizeof(f64)*paramCountInputStep64);

        status=mips_rfft_fast_init_f64(&instRfftF64,64);
        ifft = 0;
   
        mips_rfft_fast_f64(&(instRfftF64), f64changedstep, f64outputstep, ifft);

    printf("mips_rfft_fast_f64 Step_64 finish \n");

    printf("mips_rfft_fast_f64 Step_64 checking \n\n");
#if defined(NOT_EMBEDDED)
	snr_check_f64(f64referenceFileStep64, f64outputstep, 0, (f64)SNR_THRESHOLD);
#else
	snr_check_special_f64(f64referenceFileStep64, f64outputstep, f64referenceFileStep64Len, (f64)SNR_THRESHOLD);
#endif


    printf("\n== mips_rfft_fast_f64 Step_64 check done  == \n\n");

// =====================
    printf("== mips_rfft_fast_f64 Step_64 test ==  \n");

        memcpy(f64changedstep,f64IFTinputStep64,sizeof(f64)*IFTparamCountInputStep64);

        status=mips_rfft_fast_init_f64(&instRfftF64,64);
        ifft = 1;
   
        mips_rfft_fast_f64(&(instRfftF64), f64changedstep, f64outputstep, ifft);

    printf("mips_rfft_fast_f64 Step_64 finish \n");

    printf("mips_rfft_fast_f64 Step_64 checking \n\n");
#if defined(NOT_EMBEDDED)
	snr_check_f64(f64inputFileStep64, f64outputstep, 0, (f64)SNR_THRESHOLD);
#else
	snr_check_special_f64(f64inputStep64, f64outputstep, paramCountInputStep64, (f64)SNR_THRESHOLD);
#endif


    printf("\n== mips_rfft_fast_f64 Step_32 check done  == \n\n");

// =====================
    printf("== mips_rfft_fast_f64 Step_128 test ==  \n");

        memcpy(f64changedstep,f64inputStep128,sizeof(f64)*paramCountInputStep128);

        status=mips_rfft_fast_init_f64(&instRfftF64,128);
        ifft = 0;
   
        mips_rfft_fast_f64(&(instRfftF64), f64changedstep, f64outputstep, ifft);

    printf("mips_rfft_fast_f64 Step_128 finish \n");

    printf("mips_rfft_fast_f64 Step_128 checking \n\n");
#if defined(NOT_EMBEDDED)
	snr_check_f64(f64referenceFileStep128, f64outputstep, 0, (f64)SNR_THRESHOLD);
#else
	snr_check_special_f64(f64referenceFileStep128, f64outputstep, f64referenceFileStep128Len, (f64)SNR_THRESHOLD);
#endif


    printf("\n== mips_rfft_fast_f64 Step_128 check done  == \n\n");

// =====================
    printf("== mips_rfft_fast_f64 Step_128 test ==  \n");

        memcpy(f64changedstep,f64IFTinputStep128,sizeof(f64)*IFTparamCountInputStep128);

        status=mips_rfft_fast_init_f64(&instRfftF64,128);
        ifft = 1;
   
        mips_rfft_fast_f64(&(instRfftF64), f64changedstep, f64outputstep, ifft);

    printf("mips_rfft_fast_f64 Step_128 finish \n");

    printf("mips_rfft_fast_f64 Step_128 checking \n\n");
#if defined(NOT_EMBEDDED)
	snr_check_f64(f64inputFileStep128, f64outputstep, 0, (f64)SNR_THRESHOLD);
#else
	snr_check_special_f64(f64inputStep128, f64outputstep, paramCountInputStep128, (f64)SNR_THRESHOLD);
#endif


    printf("\n== mips_rfft_fast_f64 Step_128 check done  == \n\n");

// =====================
    printf("== mips_rfft_fast_f64 Step_256 test ==  \n");

        memcpy(f64changedstep,f64inputStep256,sizeof(f64)*paramCountInputStep256);

        status=mips_rfft_fast_init_f64(&instRfftF64,256);
        ifft = 0;
   
        mips_rfft_fast_f64(&(instRfftF64), f64changedstep, f64outputstep, ifft);

    printf("mips_rfft_fast_f64 Step_256 finish \n");

    printf("mips_rfft_fast_f64 Step_256 checking \n\n");
#if defined(NOT_EMBEDDED)
	snr_check_f64(f64referenceFileStep256, f64outputstep, 0, (f64)SNR_THRESHOLD);
#else
	snr_check_special_f64(f64referenceFileStep256, f64outputstep, f64referenceFileStep256Len, (f64)SNR_THRESHOLD);
#endif


    printf("\n== mips_rfft_fast_f64 Step_256 check done  == \n\n");

// =====================
    printf("== mips_rfft_fast_f64 Step_256 test ==  \n");

        memcpy(f64changedstep,f64IFTinputStep256,sizeof(f64)*IFTparamCountInputStep256);

        status=mips_rfft_fast_init_f64(&instRfftF64,256);
        ifft = 1;
   
        mips_rfft_fast_f64(&(instRfftF64), f64changedstep, f64outputstep, ifft);

    printf("mips_rfft_fast_f64 Step_256 finish \n");

    printf("mips_rfft_fast_f64 Step_256 checking \n\n");
#if defined(NOT_EMBEDDED)
	snr_check_f64(f64inputFileStep256, f64outputstep, 0, (f64)SNR_THRESHOLD);
#else
	snr_check_special_f64(f64inputStep256, f64outputstep, paramCountInputStep256, (f64)SNR_THRESHOLD);
#endif


    printf("\n== mips_rfft_fast_f64 Step_256 check done  == \n\n");

// =====================
    printf("== mips_rfft_fast_f64 Step_512 test ==  \n");

        memcpy(f64changedstep,f64inputStep512,sizeof(f64)*paramCountInputStep512);

        status=mips_rfft_fast_init_f64(&instRfftF64,512);
        ifft = 0;
   
        mips_rfft_fast_f64(&(instRfftF64), f64changedstep, f64outputstep, ifft);

    printf("mips_rfft_fast_f64 Step_512 finish \n");

    printf("mips_rfft_fast_f64 Step_512 checking \n\n");
#if defined(NOT_EMBEDDED)
	snr_check_f64(f64referenceFileStep512, f64outputstep, 0, (f64)SNR_THRESHOLD);
#else
	snr_check_special_f64(f64referenceFileStep512, f64outputstep, f64referenceFileStep512Len, (f64)SNR_THRESHOLD);
#endif


    printf("\n== mips_rfft_fast_f64 Step_512 check done  == \n\n");

// =====================
    printf("== mips_rfft_fast_f64 Step_512 test ==  \n");

        memcpy(f64changedstep,f64IFTinputStep512,sizeof(f64)*IFTparamCountInputStep512);

        status=mips_rfft_fast_init_f64(&instRfftF64,512);
        ifft = 1;
   
        mips_rfft_fast_f64(&(instRfftF64), f64changedstep, f64outputstep, ifft);

    printf("mips_rfft_fast_f64 Step_512 finish \n");

    printf("mips_rfft_fast_f64 Step_512 checking \n\n");
#if defined(NOT_EMBEDDED)
	snr_check_f64(f64inputFileStep512, f64outputstep, 0, (f64)SNR_THRESHOLD);
#else
	snr_check_special_f64(f64inputStep512, f64outputstep, paramCountInputStep512, (f64)SNR_THRESHOLD);
#endif


    printf("\n== mips_rfft_fast_f64 Step_1024 check done  == \n\n");

// =====================
    printf("== mips_rfft_fast_f64 Step_1024 test ==  \n");

        memcpy(f64changedstep,f64inputStep1024,sizeof(f64)*paramCountInputStep1024);

        status=mips_rfft_fast_init_f64(&instRfftF64,1024);
        ifft = 0;
   
        mips_rfft_fast_f64(&(instRfftF64), f64changedstep, f64outputstep, ifft);

    printf("mips_rfft_fast_f64 Step_1024 finish \n");

    printf("mips_rfft_fast_f64 Step_1024 checking \n\n");
#if defined(NOT_EMBEDDED)
	snr_check_f64(f64referenceFileStep1024, f64outputstep, 0, (f64)SNR_THRESHOLD);
#else
	snr_check_special_f64(f64referenceFileStep1024, f64outputstep, f64referenceFileStep1024Len, (f64)SNR_THRESHOLD);
#endif


    printf("\n== mips_rfft_fast_f64 Step_1024 check done  == \n\n");

// =====================
    printf("== mips_rfft_fast_f64 Step_1024 test ==  \n");

        memcpy(f64changedstep,f64IFTinputStep1024,sizeof(f64)*IFTparamCountInputStep1024);

        status=mips_rfft_fast_init_f64(&instRfftF64,1024);
        ifft = 1;
   
        mips_rfft_fast_f64(&(instRfftF64), f64changedstep, f64outputstep, ifft);

    printf("mips_rfft_fast_f64 Step_1024 finish \n");

    printf("mips_rfft_fast_f64 Step_1024 checking \n\n");
#if defined(NOT_EMBEDDED)
	snr_check_f64(f64inputFileStep1024, f64outputstep, 0, (f64)SNR_THRESHOLD);
#else
	snr_check_special_f64(f64inputStep1024, f64outputstep, paramCountInputStep1024, (f64)SNR_THRESHOLD);
#endif


    printf("\n== mips_rfft_fast_f64 Step_1024 check done  == \n\n");

// =====================
    printf("== mips_rfft_fast_f64 Step_2048 test ==  \n");

        memcpy(f64changedstep,f64inputStep2048,sizeof(f64)*paramCountInputStep2048);

        status=mips_rfft_fast_init_f64(&instRfftF64,2048);
        ifft = 0;
   
        mips_rfft_fast_f64(&(instRfftF64), f64changedstep, f64outputstep, ifft);

    printf("mips_rfft_fast_f64 Step_2048 finish \n");

    printf("mips_rfft_fast_f64 Step_2048 checking \n\n");
#if defined(NOT_EMBEDDED)
	snr_check_f64(f64referenceFileStep2048, f64outputstep, 0, (f64)SNR_THRESHOLD);
#else
	snr_check_special_f64(f64referenceFileStep2048, f64outputstep, f64referenceFileStep2048Len, (f64)SNR_THRESHOLD);
#endif


    printf("\n== mips_rfft_fast_f64 Step_2048 check done  == \n\n");

// =====================
    printf("== mips_rfft_fast_f64 Step_2048 test ==  \n");

        memcpy(f64changedstep,f64IFTinputStep2048,sizeof(f64)*IFTparamCountInputStep2048);

        status=mips_rfft_fast_init_f64(&instRfftF64,2048);
        ifft = 1;
   
        mips_rfft_fast_f64(&(instRfftF64), f64changedstep, f64outputstep, ifft);

    printf("mips_rfft_fast_f64 Step_2048 finish \n");

    printf("mips_rfft_fast_f64 Step_2048 checking \n\n");
#if defined(NOT_EMBEDDED)
	snr_check_f64(f64inputFileStep2048, f64outputstep, 0, (f64)SNR_THRESHOLD);
#else
	snr_check_special_f64(f64inputStep2048, f64outputstep, paramCountInputStep2048, (f64)SNR_THRESHOLD);
#endif


    printf("\n== mips_rfft_fast_f64 Step_2048 check done  == \n\n");

// =====================
    printf("== mips_rfft_fast_f64 Step_4096 test ==  \n");

        memcpy(f64changedstep,f64inputStep4096,sizeof(f64)*paramCountInputStep4096);

        status=mips_rfft_fast_init_f64(&instRfftF64,4096);
        ifft = 0;
   
        mips_rfft_fast_f64(&(instRfftF64), f64changedstep, f64outputstep, ifft);

    printf("mips_rfft_fast_f64 Step_4096 finish \n");

    printf("mips_rfft_fast_f64 Step_4096 checking \n\n");
#if defined(NOT_EMBEDDED)
	snr_check_f64(f64referenceFileStep4096, f64outputstep, 0, (f64)SNR_THRESHOLD);
#else
	snr_check_special_f64(f64referenceFileStep4096, f64outputstep, f64referenceFileStep4096Len, (f64)SNR_THRESHOLD);
#endif


    printf("\n== mips_rfft_fast_f64 Step_4096 check done  == \n\n");

// =====================
    printf("== mips_rfft_fast_f64 Step_4096 test ==  \n");

        memcpy(f64changedstep,f64IFTinputStep4096,sizeof(f64)*IFTparamCountInputStep4096);

        status=mips_rfft_fast_init_f64(&instRfftF64,4096);
        ifft = 1;
   
        mips_rfft_fast_f64(&(instRfftF64), f64changedstep, f64outputstep, ifft);

    printf("mips_rfft_fast_f64 Step_4096 finish \n");

    printf("mips_rfft_fast_f64 Step_4096 checking \n\n");
#if defined(NOT_EMBEDDED)
	snr_check_f64(f64inputFileStep4096, f64outputstep, 0, (f64)SNR_THRESHOLD);
#else
	snr_check_special_f64(f64inputStep4096, f64outputstep, paramCountInputStep4096, (f64)SNR_THRESHOLD);
#endif


    printf("\n== mips_rfft_fast_f64 Step_4096 check done  == \n\n");

    return 0;
}