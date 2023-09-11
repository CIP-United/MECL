#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/transform_functions.h"
#include "mips_common_tables.h"
#include "mips_const_structs.h"

#define SNR_THRESHOLD 120

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
	int paramCountInputNoisy16 = 0;
    int paramCountInputNoisy32 = 0;
    int paramCountInputNoisy64 = 0;
    int paramCountInputNoisy128 = 0;
    int paramCountInputNoisy256 = 0;
    int paramCountInputNoisy512 = 0;
    int paramCountInputNoisy1024 = 0;
    int paramCountInputNoisy2048 = 0;
    int paramCountInputNoisy4096 = 0;

    f32 f32inputNoisy16[MAX_SIZE] = {0};
    f32 f32inputNoisy32[MAX_SIZE] = {0};
    f32 f32inputNoisy64[MAX_SIZE] = {0};
    f32 f32inputNoisy128[MAX_SIZE] = {0};
    f32 f32inputNoisy256[MAX_SIZE] = {0};
    f32 f32inputNoisy512[MAX_SIZE] = {0};
    f32 f32inputNoisy1024[MAX_SIZE] = {0};
    f32 f32inputNoisy2048[MAX_SIZE] = {0};
    f32 f32inputNoisy4096[MAX_SIZE] = {0};

	int IFTparamCountInputNoisy16 = 0;
    int IFTparamCountInputNoisy32 = 0;
    int IFTparamCountInputNoisy64 = 0;
    int IFTparamCountInputNoisy128 = 0;
    int IFTparamCountInputNoisy256 = 0;
    int IFTparamCountInputNoisy512 = 0;
    int IFTparamCountInputNoisy1024 = 0;
    int IFTparamCountInputNoisy2048 = 0;
    int IFTparamCountInputNoisy4096 = 0;

    f32 f32IFTinputNoisy16[MAX_SIZE] = {0};
    f32 f32IFTinputNoisy32[MAX_SIZE] = {0};
    f32 f32IFTinputNoisy64[MAX_SIZE] = {0};
    f32 f32IFTinputNoisy128[MAX_SIZE] = {0};
    f32 f32IFTinputNoisy256[MAX_SIZE] = {0};
    f32 f32IFTinputNoisy512[MAX_SIZE] = {0};
    f32 f32IFTinputNoisy1024[MAX_SIZE] = {0};
    f32 f32IFTinputNoisy2048[MAX_SIZE] = {0};
    f32 f32IFTinputNoisy4096[MAX_SIZE] = {0};

	int paramCountInputStep16 = 0;
    int paramCountInputStep32 = 0;
    int paramCountInputStep64 = 0;
    int paramCountInputStep128 = 0;
    int paramCountInputStep256 = 0;
    int paramCountInputStep512 = 0;
    int paramCountInputStep1024 = 0;
    int paramCountInputStep2048 = 0;
    int paramCountInputStep4096 = 0;

    f32 f32inputStep16[MAX_SIZE] = {0};
    f32 f32inputStep32[MAX_SIZE] = {0};
    f32 f32inputStep64[MAX_SIZE] = {0};
    f32 f32inputStep128[MAX_SIZE] = {0};
    f32 f32inputStep256[MAX_SIZE] = {0};
    f32 f32inputStep512[MAX_SIZE] = {0};
    f32 f32inputStep1024[MAX_SIZE] = {0};
    f32 f32inputStep2048[MAX_SIZE] = {0};
    f32 f32inputStep4096[MAX_SIZE] = {0};

	int IFTparamCountInputStep16 = 0;
    int IFTparamCountInputStep32 = 0;
    int IFTparamCountInputStep64 = 0;
    int IFTparamCountInputStep128 = 0;
    int IFTparamCountInputStep256 = 0;
    int IFTparamCountInputStep512 = 0;
    int IFTparamCountInputStep1024 = 0;
    int IFTparamCountInputStep2048 = 0;
    int IFTparamCountInputStep4096 = 0;

    f32 f32IFTinputStep16[MAX_SIZE] = {0};
    f32 f32IFTinputStep32[MAX_SIZE] = {0};
    f32 f32IFTinputStep64[MAX_SIZE] = {0};
    f32 f32IFTinputStep128[MAX_SIZE] = {0};
    f32 f32IFTinputStep256[MAX_SIZE] = {0};
    f32 f32IFTinputStep512[MAX_SIZE] = {0};
    f32 f32IFTinputStep1024[MAX_SIZE] = {0};
    f32 f32IFTinputStep2048[MAX_SIZE] = {0};
    f32 f32IFTinputStep4096[MAX_SIZE] = {0};

	// file name. file path max length is 255, so use 255.

#if defined(NOT_EMBEDDED)
	char f32inputFileNoisy16[255] = {0};
#else
	void *f32inputFileNoisy16;
	int f32inputFileNoisy16Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32inputFileNoisy32[255] = {0};
#else
	void *f32inputFileNoisy32;
	int f32inputFileNoisy32Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32inputFileNoisy64[255] = {0};
#else
	void *f32inputFileNoisy64;
	int f32inputFileNoisy64Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32inputFileNoisy128[255] = {0};
#else
	void *f32inputFileNoisy128;
	int f32inputFileNoisy128Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32inputFileNoisy256[255] = {0};
#else
	void *f32inputFileNoisy256;
	int f32inputFileNoisy256Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32inputFileNoisy512[255] = {0};
#else
	void *f32inputFileNoisy512;
	int f32inputFileNoisy512Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32inputFileNoisy1024[255] = {0};
#else
	void *f32inputFileNoisy1024;
	int f32inputFileNoisy1024Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32inputFileNoisy2048[255] = {0};
#else
	void *f32inputFileNoisy2048;
	int f32inputFileNoisy2048Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32inputFileNoisy4096[255] = {0};
#else
	void *f32inputFileNoisy4096;
	int f32inputFileNoisy4096Len = 0;
#endif


#if defined(NOT_EMBEDDED)
	char f32inputFileStep16[255] = {0};
#else
	void *f32inputFileStep16;
	int f32inputFileStep16Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32inputFileStep32[255] = {0};
#else
	void *f32inputFileStep32;
	int f32inputFileStep32Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32inputFileStep64[255] = {0};
#else
	void *f32inputFileStep64;
	int f32inputFileStep64Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32inputFileStep128[255] = {0};
#else
	void *f32inputFileStep128;
	int f32inputFileStep128Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32inputFileStep256[255] = {0};
#else
	void *f32inputFileStep256;
	int f32inputFileStep256Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32inputFileStep512[255] = {0};
#else
	void *f32inputFileStep512;
	int f32inputFileStep512Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32inputFileStep1024[255] = {0};
#else
	void *f32inputFileStep1024;
	int f32inputFileStep1024Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32inputFileStep2048[255] = {0};
#else
	void *f32inputFileStep2048;
	int f32inputFileStep2048Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32inputFileStep4096[255] = {0};
#else
	void *f32inputFileStep4096;
	int f32inputFileStep4096Len = 0;
#endif


#if defined(NOT_EMBEDDED)
	char f32IFTinputFileNoisy16[255] = {0};
#else
	void *f32IFTinputFileNoisy16;
	int f32IFTinputFileNoisy16Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32IFTinputFileNoisy32[255] = {0};
#else
	void *f32IFTinputFileNoisy32;
	int f32IFTinputFileNoisy32Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32IFTinputFileNoisy64[255] = {0};
#else
	void *f32IFTinputFileNoisy64;
	int f32IFTinputFileNoisy64Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32IFTinputFileNoisy128[255] = {0};
#else
	void *f32IFTinputFileNoisy128;
	int f32IFTinputFileNoisy128Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32IFTinputFileNoisy256[255] = {0};
#else
	void *f32IFTinputFileNoisy256;
	int f32IFTinputFileNoisy256Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32IFTinputFileNoisy512[255] = {0};
#else
	void *f32IFTinputFileNoisy512;
	int f32IFTinputFileNoisy512Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32IFTinputFileNoisy1024[255] = {0};
#else
	void *f32IFTinputFileNoisy1024;
	int f32IFTinputFileNoisy1024Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32IFTinputFileNoisy2048[255] = {0};
#else
	void *f32IFTinputFileNoisy2048;
	int f32IFTinputFileNoisy2048Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32IFTinputFileNoisy4096[255] = {0};
#else
	void *f32IFTinputFileNoisy4096;
	int f32IFTinputFileNoisy4096Len = 0;
#endif


#if defined(NOT_EMBEDDED)
	char f32IFTinputFileStep16[255] = {0};
#else
	void *f32IFTinputFileStep16;
	int f32IFTinputFileStep16Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32IFTinputFileStep32[255] = {0};
#else
	void *f32IFTinputFileStep32;
	int f32IFTinputFileStep32Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32IFTinputFileStep64[255] = {0};
#else
	void *f32IFTinputFileStep64;
	int f32IFTinputFileStep64Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32IFTinputFileStep128[255] = {0};
#else
	void *f32IFTinputFileStep128;
	int f32IFTinputFileStep128Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32IFTinputFileStep256[255] = {0};
#else
	void *f32IFTinputFileStep256;
	int f32IFTinputFileStep256Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32IFTinputFileStep512[255] = {0};
#else
	void *f32IFTinputFileStep512;
	int f32IFTinputFileStep512Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32IFTinputFileStep1024[255] = {0};
#else
	void *f32IFTinputFileStep1024;
	int f32IFTinputFileStep1024Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32IFTinputFileStep2048[255] = {0};
#else
	void *f32IFTinputFileStep2048;
	int f32IFTinputFileStep2048Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32IFTinputFileStep4096[255] = {0};
#else
	void *f32IFTinputFileStep4096;
	int f32IFTinputFileStep4096Len = 0;
#endif



#if defined(NOT_EMBEDDED)
	char f32referenceFileNoisy16[255] = {0};
#else
	void *f32referenceFileNoisy16;
	int f32referenceFileNoisy16Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32referenceFileNoisy32[255] = {0};
#else
	void *f32referenceFileNoisy32;
	int f32referenceFileNoisy32Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32referenceFileNoisy64[255] = {0};
#else
	void *f32referenceFileNoisy64;
	int f32referenceFileNoisy64Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32referenceFileNoisy128[255] = {0};
#else
	void *f32referenceFileNoisy128;
	int f32referenceFileNoisy128Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32referenceFileNoisy256[255] = {0};
#else
	void *f32referenceFileNoisy256;
	int f32referenceFileNoisy256Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32referenceFileNoisy512[255] = {0};
#else
	void *f32referenceFileNoisy512;
	int f32referenceFileNoisy512Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32referenceFileNoisy1024[255] = {0};
#else
	void *f32referenceFileNoisy1024;
	int f32referenceFileNoisy1024Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32referenceFileNoisy2048[255] = {0};
#else
	void *f32referenceFileNoisy2048;
	int f32referenceFileNoisy2048Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32referenceFileNoisy4096[255] = {0};
#else
	void *f32referenceFileNoisy4096;
	int f32referenceFileNoisy4096Len = 0;
#endif


#if defined(NOT_EMBEDDED)
	char f32referenceFileStep16[255] = {0};
#else
	void *f32referenceFileStep16;
	int f32referenceFileStep16Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32referenceFileStep32[255] = {0};
#else
	void *f32referenceFileStep32;
	int f32referenceFileStep32Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32referenceFileStep64[255] = {0};
#else
	void *f32referenceFileStep64;
	int f32referenceFileStep64Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32referenceFileStep128[255] = {0};
#else
	void *f32referenceFileStep128;
	int f32referenceFileStep128Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32referenceFileStep256[255] = {0};
#else
	void *f32referenceFileStep256;
	int f32referenceFileStep256Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32referenceFileStep512[255] = {0};
#else
	void *f32referenceFileStep512;
	int f32referenceFileStep512Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32referenceFileStep1024[255] = {0};
#else
	void *f32referenceFileStep1024;
	int f32referenceFileStep1024Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32referenceFileStep2048[255] = {0};
#else
	void *f32referenceFileStep2048;
	int f32referenceFileStep2048Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32referenceFileStep4096[255] = {0};
#else
	void *f32referenceFileStep4096;
	int f32referenceFileStep4096Len = 0;
#endif


	// set file name by snprintf
	// relative path, function path, filename
#if defined(NOT_EMBEDDED)
	snprintf(f32inputFileNoisy16, sizeof(f32inputFileNoisy16), "%s%s%s", Patterns_PATH, TransformF32, "ComplexInputSamples_Noisy_16_1_f32.txt");
#else
	f32inputFileNoisy16 = TransformF32_ComplexInputSamples_Noisy_16_1_f32;
	f32inputFileNoisy16Len = sizeof(TransformF32_ComplexInputSamples_Noisy_16_1_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32inputFileNoisy32, sizeof(f32inputFileNoisy32), "%s%s%s", Patterns_PATH, TransformF32, "ComplexInputSamples_Noisy_32_2_f32.txt");
#else
	f32inputFileNoisy32 = TransformF32_ComplexInputSamples_Noisy_32_2_f32;
	f32inputFileNoisy32Len = sizeof(TransformF32_ComplexInputSamples_Noisy_32_2_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32inputFileNoisy64, sizeof(f32inputFileNoisy64), "%s%s%s", Patterns_PATH, TransformF32, "ComplexInputSamples_Noisy_64_3_f32.txt");
#else
	f32inputFileNoisy64 = TransformF32_ComplexInputSamples_Noisy_64_3_f32;
	f32inputFileNoisy64Len = sizeof(TransformF32_ComplexInputSamples_Noisy_64_3_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32inputFileNoisy128, sizeof(f32inputFileNoisy128), "%s%s%s", Patterns_PATH, TransformF32, "ComplexInputSamples_Noisy_128_4_f32.txt");
#else
	f32inputFileNoisy128 = TransformF32_ComplexInputSamples_Noisy_128_4_f32;
	f32inputFileNoisy128Len = sizeof(TransformF32_ComplexInputSamples_Noisy_128_4_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32inputFileNoisy256, sizeof(f32inputFileNoisy256), "%s%s%s", Patterns_PATH, TransformF32, "ComplexInputSamples_Noisy_256_5_f32.txt");
#else
	f32inputFileNoisy256 = TransformF32_ComplexInputSamples_Noisy_256_5_f32;
	f32inputFileNoisy256Len = sizeof(TransformF32_ComplexInputSamples_Noisy_256_5_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32inputFileNoisy512, sizeof(f32inputFileNoisy512), "%s%s%s", Patterns_PATH, TransformF32, "ComplexInputSamples_Noisy_512_6_f32.txt");
#else
	f32inputFileNoisy512 = TransformF32_ComplexInputSamples_Noisy_512_6_f32;
	f32inputFileNoisy512Len = sizeof(TransformF32_ComplexInputSamples_Noisy_512_6_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32inputFileNoisy1024, sizeof(f32inputFileNoisy1024), "%s%s%s", Patterns_PATH, TransformF32, "ComplexInputSamples_Noisy_1024_7_f32.txt");
#else
	f32inputFileNoisy1024 = TransformF32_ComplexInputSamples_Noisy_1024_7_f32;
	f32inputFileNoisy1024Len = sizeof(TransformF32_ComplexInputSamples_Noisy_1024_7_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32inputFileNoisy2048, sizeof(f32inputFileNoisy2048), "%s%s%s", Patterns_PATH, TransformF32, "ComplexInputSamples_Noisy_2048_8_f32.txt");
#else
	f32inputFileNoisy2048 = TransformF32_ComplexInputSamples_Noisy_2048_8_f32;
	f32inputFileNoisy2048Len = sizeof(TransformF32_ComplexInputSamples_Noisy_2048_8_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32inputFileNoisy4096, sizeof(f32inputFileNoisy4096), "%s%s%s", Patterns_PATH, TransformF32, "ComplexInputSamples_Noisy_4096_9_f32.txt");
#else
	f32inputFileNoisy4096 = TransformF32_ComplexInputSamples_Noisy_4096_9_f32;
	f32inputFileNoisy4096Len = sizeof(TransformF32_ComplexInputSamples_Noisy_4096_9_f32);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(f32IFTinputFileNoisy16, sizeof(f32IFTinputFileNoisy16), "%s%s%s", Patterns_PATH, TransformF32, "ComplexInputIFFTSamples_Noisy_16_1_f32.txt");
#else
	f32IFTinputFileNoisy16 = TransformF32_ComplexInputIFFTSamples_Noisy_16_1_f32;
	f32IFTinputFileNoisy16Len = sizeof(TransformF32_ComplexInputIFFTSamples_Noisy_16_1_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32IFTinputFileNoisy32, sizeof(f32IFTinputFileNoisy32), "%s%s%s", Patterns_PATH, TransformF32, "ComplexInputIFFTSamples_Noisy_32_2_f32.txt");
#else
	f32IFTinputFileNoisy32 = TransformF32_ComplexInputIFFTSamples_Noisy_32_2_f32;
	f32IFTinputFileNoisy32Len = sizeof(TransformF32_ComplexInputIFFTSamples_Noisy_32_2_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32IFTinputFileNoisy64, sizeof(f32IFTinputFileNoisy64), "%s%s%s", Patterns_PATH, TransformF32, "ComplexInputIFFTSamples_Noisy_64_3_f32.txt");
#else
	f32IFTinputFileNoisy64 = TransformF32_ComplexInputIFFTSamples_Noisy_64_3_f32;
	f32IFTinputFileNoisy64Len = sizeof(TransformF32_ComplexInputIFFTSamples_Noisy_64_3_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32IFTinputFileNoisy128, sizeof(f32IFTinputFileNoisy128), "%s%s%s", Patterns_PATH, TransformF32, "ComplexInputIFFTSamples_Noisy_128_4_f32.txt");
#else
	f32IFTinputFileNoisy128 = TransformF32_ComplexInputIFFTSamples_Noisy_128_4_f32;
	f32IFTinputFileNoisy128Len = sizeof(TransformF32_ComplexInputIFFTSamples_Noisy_128_4_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32IFTinputFileNoisy256, sizeof(f32IFTinputFileNoisy256), "%s%s%s", Patterns_PATH, TransformF32, "ComplexInputIFFTSamples_Noisy_256_5_f32.txt");
#else
	f32IFTinputFileNoisy256 = TransformF32_ComplexInputIFFTSamples_Noisy_256_5_f32;
	f32IFTinputFileNoisy256Len = sizeof(TransformF32_ComplexInputIFFTSamples_Noisy_256_5_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32IFTinputFileNoisy512, sizeof(f32IFTinputFileNoisy512), "%s%s%s", Patterns_PATH, TransformF32, "ComplexInputIFFTSamples_Noisy_512_6_f32.txt");
#else
	f32IFTinputFileNoisy512 = TransformF32_ComplexInputIFFTSamples_Noisy_512_6_f32;
	f32IFTinputFileNoisy512Len = sizeof(TransformF32_ComplexInputIFFTSamples_Noisy_512_6_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32IFTinputFileNoisy1024, sizeof(f32IFTinputFileNoisy1024), "%s%s%s", Patterns_PATH, TransformF32, "ComplexInputIFFTSamples_Noisy_1024_7_f32.txt");
#else
	f32IFTinputFileNoisy1024 = TransformF32_ComplexInputIFFTSamples_Noisy_1024_7_f32;
	f32IFTinputFileNoisy1024Len = sizeof(TransformF32_ComplexInputIFFTSamples_Noisy_1024_7_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32IFTinputFileNoisy2048, sizeof(f32IFTinputFileNoisy2048), "%s%s%s", Patterns_PATH, TransformF32, "ComplexInputIFFTSamples_Noisy_2048_8_f32.txt");
#else
	f32IFTinputFileNoisy2048 = TransformF32_ComplexInputIFFTSamples_Noisy_2048_8_f32;
	f32IFTinputFileNoisy2048Len = sizeof(TransformF32_ComplexInputIFFTSamples_Noisy_2048_8_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32IFTinputFileNoisy4096, sizeof(f32IFTinputFileNoisy4096), "%s%s%s", Patterns_PATH, TransformF32, "ComplexInputIFFTSamples_Noisy_4096_9_f32.txt");
#else
	f32IFTinputFileNoisy4096 = TransformF32_ComplexInputIFFTSamples_Noisy_4096_9_f32;
	f32IFTinputFileNoisy4096Len = sizeof(TransformF32_ComplexInputIFFTSamples_Noisy_4096_9_f32);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(f32referenceFileNoisy16, sizeof(f32referenceFileNoisy16), "%s%s%s", Patterns_PATH, TransformF32, "ComplexFFTSamples_Noisy_16_1_f32.txt");
#else
	f32referenceFileNoisy16 = TransformF32_ComplexFFTSamples_Noisy_16_1_f32;
	f32referenceFileNoisy16Len = sizeof(TransformF32_ComplexFFTSamples_Noisy_16_1_f32)/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32referenceFileNoisy32, sizeof(f32referenceFileNoisy32), "%s%s%s", Patterns_PATH, TransformF32, "ComplexFFTSamples_Noisy_32_2_f32.txt");
#else
	f32referenceFileNoisy32 = TransformF32_ComplexFFTSamples_Noisy_32_2_f32;
	f32referenceFileNoisy32Len = sizeof(TransformF32_ComplexFFTSamples_Noisy_32_2_f32)/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32referenceFileNoisy64, sizeof(f32referenceFileNoisy64), "%s%s%s", Patterns_PATH, TransformF32, "ComplexFFTSamples_Noisy_64_3_f32.txt");
#else
	f32referenceFileNoisy64 = TransformF32_ComplexFFTSamples_Noisy_64_3_f32;
	f32referenceFileNoisy64Len = sizeof(TransformF32_ComplexFFTSamples_Noisy_64_3_f32)/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32referenceFileNoisy128, sizeof(f32referenceFileNoisy128), "%s%s%s", Patterns_PATH, TransformF32, "ComplexFFTSamples_Noisy_128_4_f32.txt");
#else
	f32referenceFileNoisy128 = TransformF32_ComplexFFTSamples_Noisy_128_4_f32;
	f32referenceFileNoisy128Len = sizeof(TransformF32_ComplexFFTSamples_Noisy_128_4_f32)/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32referenceFileNoisy256, sizeof(f32referenceFileNoisy256), "%s%s%s", Patterns_PATH, TransformF32, "ComplexFFTSamples_Noisy_256_5_f32.txt");
#else
	f32referenceFileNoisy256 = TransformF32_ComplexFFTSamples_Noisy_256_5_f32;
	f32referenceFileNoisy256Len = sizeof(TransformF32_ComplexFFTSamples_Noisy_256_5_f32)/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32referenceFileNoisy512, sizeof(f32referenceFileNoisy512), "%s%s%s", Patterns_PATH, TransformF32, "ComplexFFTSamples_Noisy_512_6_f32.txt");
#else
	f32referenceFileNoisy512 = TransformF32_ComplexFFTSamples_Noisy_512_6_f32;
	f32referenceFileNoisy512Len = sizeof(TransformF32_ComplexFFTSamples_Noisy_512_6_f32)/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32referenceFileNoisy1024, sizeof(f32referenceFileNoisy1024), "%s%s%s", Patterns_PATH, TransformF32, "ComplexFFTSamples_Noisy_1024_7_f32.txt");
#else
	f32referenceFileNoisy1024 = TransformF32_ComplexFFTSamples_Noisy_1024_7_f32;
	f32referenceFileNoisy1024Len = sizeof(TransformF32_ComplexFFTSamples_Noisy_1024_7_f32)/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32referenceFileNoisy2048, sizeof(f32referenceFileNoisy2048), "%s%s%s", Patterns_PATH, TransformF32, "ComplexFFTSamples_Noisy_2048_8_f32.txt");
#else
	f32referenceFileNoisy2048 = TransformF32_ComplexFFTSamples_Noisy_2048_8_f32;
	f32referenceFileNoisy2048Len = sizeof(TransformF32_ComplexFFTSamples_Noisy_2048_8_f32)/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32referenceFileNoisy4096, sizeof(f32referenceFileNoisy4096), "%s%s%s", Patterns_PATH, TransformF32, "ComplexFFTSamples_Noisy_4096_9_f32.txt");
#else
	f32referenceFileNoisy4096 = TransformF32_ComplexFFTSamples_Noisy_4096_9_f32;
	f32referenceFileNoisy4096Len = sizeof(TransformF32_ComplexFFTSamples_Noisy_4096_9_f32)/sizeof(f32);
#endif



#if defined(NOT_EMBEDDED)
	snprintf(f32inputFileStep16, sizeof(f32inputFileStep16), "%s%s%s", Patterns_PATH, TransformF32, "ComplexInputSamples_Step_16_10_f32.txt");
#else
	f32inputFileStep16 = TransformF32_ComplexInputSamples_Step_16_10_f32;
	f32inputFileStep16Len = sizeof(TransformF32_ComplexInputSamples_Step_16_10_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32inputFileStep32, sizeof(f32inputFileStep32), "%s%s%s", Patterns_PATH, TransformF32, "ComplexInputSamples_Step_32_11_f32.txt");
#else
	f32inputFileStep32 = TransformF32_ComplexInputSamples_Step_32_11_f32;
	f32inputFileStep32Len = sizeof(TransformF32_ComplexInputSamples_Step_32_11_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32inputFileStep64, sizeof(f32inputFileStep64), "%s%s%s", Patterns_PATH, TransformF32, "ComplexInputSamples_Step_64_12_f32.txt");
#else
	f32inputFileStep64 = TransformF32_ComplexInputSamples_Step_64_12_f32;
	f32inputFileStep64Len = sizeof(TransformF32_ComplexInputSamples_Step_64_12_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32inputFileStep128, sizeof(f32inputFileStep128), "%s%s%s", Patterns_PATH, TransformF32, "ComplexInputSamples_Step_128_13_f32.txt");
#else
	f32inputFileStep128 = TransformF32_ComplexInputSamples_Step_128_13_f32;
	f32inputFileStep128Len = sizeof(TransformF32_ComplexInputSamples_Step_128_13_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32inputFileStep256, sizeof(f32inputFileStep256), "%s%s%s", Patterns_PATH, TransformF32, "ComplexInputSamples_Step_256_14_f32.txt");
#else
	f32inputFileStep256 = TransformF32_ComplexInputSamples_Step_256_14_f32;
	f32inputFileStep256Len = sizeof(TransformF32_ComplexInputSamples_Step_256_14_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32inputFileStep512, sizeof(f32inputFileStep512), "%s%s%s", Patterns_PATH, TransformF32, "ComplexInputSamples_Step_512_15_f32.txt");
#else
	f32inputFileStep512 = TransformF32_ComplexInputSamples_Step_512_15_f32;
	f32inputFileStep512Len = sizeof(TransformF32_ComplexInputSamples_Step_512_15_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32inputFileStep1024, sizeof(f32inputFileStep1024), "%s%s%s", Patterns_PATH, TransformF32, "ComplexInputSamples_Step_1024_16_f32.txt");
#else
	f32inputFileStep1024 = TransformF32_ComplexInputSamples_Step_1024_16_f32;
	f32inputFileStep1024Len = sizeof(TransformF32_ComplexInputSamples_Step_1024_16_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32inputFileStep2048, sizeof(f32inputFileStep2048), "%s%s%s", Patterns_PATH, TransformF32, "ComplexInputSamples_Step_2048_17_f32.txt");
#else
	f32inputFileStep2048 = TransformF32_ComplexInputSamples_Step_2048_17_f32;
	f32inputFileStep2048Len = sizeof(TransformF32_ComplexInputSamples_Step_2048_17_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32inputFileStep4096, sizeof(f32inputFileStep4096), "%s%s%s", Patterns_PATH, TransformF32, "ComplexInputSamples_Step_4096_18_f32.txt");
#else
	f32inputFileStep4096 = TransformF32_ComplexInputSamples_Step_4096_18_f32;
	f32inputFileStep4096Len = sizeof(TransformF32_ComplexInputSamples_Step_4096_18_f32);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(f32IFTinputFileStep16, sizeof(f32IFTinputFileStep16), "%s%s%s", Patterns_PATH, TransformF32, "ComplexInputIFFTSamples_Step_16_10_f32.txt");
#else
	f32IFTinputFileStep16 = TransformF32_ComplexInputIFFTSamples_Step_16_10_f32;
	f32IFTinputFileStep16Len = sizeof(TransformF32_ComplexInputIFFTSamples_Step_16_10_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32IFTinputFileStep32, sizeof(f32IFTinputFileStep32), "%s%s%s", Patterns_PATH, TransformF32, "ComplexInputIFFTSamples_Step_32_11_f32.txt");
#else
	f32IFTinputFileStep32 = TransformF32_ComplexInputIFFTSamples_Step_32_11_f32;
	f32IFTinputFileStep32Len = sizeof(TransformF32_ComplexInputIFFTSamples_Step_32_11_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32IFTinputFileStep64, sizeof(f32IFTinputFileStep64), "%s%s%s", Patterns_PATH, TransformF32, "ComplexInputIFFTSamples_Step_64_12_f32.txt");
#else
	f32IFTinputFileStep64 = TransformF32_ComplexInputIFFTSamples_Step_64_12_f32;
	f32IFTinputFileStep64Len = sizeof(TransformF32_ComplexInputIFFTSamples_Step_64_12_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32IFTinputFileStep128, sizeof(f32IFTinputFileStep128), "%s%s%s", Patterns_PATH, TransformF32, "ComplexInputIFFTSamples_Step_128_13_f32.txt");
#else
	f32IFTinputFileStep128 = TransformF32_ComplexInputIFFTSamples_Step_128_13_f32;
	f32IFTinputFileStep128Len = sizeof(TransformF32_ComplexInputIFFTSamples_Step_128_13_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32IFTinputFileStep256, sizeof(f32IFTinputFileStep256), "%s%s%s", Patterns_PATH, TransformF32, "ComplexInputIFFTSamples_Step_256_14_f32.txt");
#else
	f32IFTinputFileStep256 = TransformF32_ComplexInputIFFTSamples_Step_256_14_f32;
	f32IFTinputFileStep256Len = sizeof(TransformF32_ComplexInputIFFTSamples_Step_256_14_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32IFTinputFileStep512, sizeof(f32IFTinputFileStep512), "%s%s%s", Patterns_PATH, TransformF32, "ComplexInputIFFTSamples_Step_512_15_f32.txt");
#else
	f32IFTinputFileStep512 = TransformF32_ComplexInputIFFTSamples_Step_512_15_f32;
	f32IFTinputFileStep512Len = sizeof(TransformF32_ComplexInputIFFTSamples_Step_512_15_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32IFTinputFileStep1024, sizeof(f32IFTinputFileStep1024), "%s%s%s", Patterns_PATH, TransformF32, "ComplexInputIFFTSamples_Step_1024_16_f32.txt");
#else
	f32IFTinputFileStep1024 = TransformF32_ComplexInputIFFTSamples_Step_1024_16_f32;
	f32IFTinputFileStep1024Len = sizeof(TransformF32_ComplexInputIFFTSamples_Step_1024_16_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32IFTinputFileStep2048, sizeof(f32IFTinputFileStep2048), "%s%s%s", Patterns_PATH, TransformF32, "ComplexInputIFFTSamples_Step_2048_17_f32.txt");
#else
	f32IFTinputFileStep2048 = TransformF32_ComplexInputIFFTSamples_Step_2048_17_f32;
	f32IFTinputFileStep2048Len = sizeof(TransformF32_ComplexInputIFFTSamples_Step_2048_17_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32IFTinputFileStep4096, sizeof(f32IFTinputFileStep4096), "%s%s%s", Patterns_PATH, TransformF32, "ComplexInputIFFTSamples_Step_4096_18_f32.txt");
#else
	f32IFTinputFileStep4096 = TransformF32_ComplexInputIFFTSamples_Step_4096_18_f32;
	f32IFTinputFileStep4096Len = sizeof(TransformF32_ComplexInputIFFTSamples_Step_4096_18_f32);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(f32referenceFileStep16, sizeof(f32referenceFileStep16), "%s%s%s", Patterns_PATH, TransformF32, "ComplexFFTSamples_Step_16_10_f32.txt");
#else
	f32referenceFileStep16 = TransformF32_ComplexFFTSamples_Step_16_10_f32;
	f32referenceFileStep16Len = sizeof(TransformF32_ComplexFFTSamples_Step_16_10_f32)/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32referenceFileStep32, sizeof(f32referenceFileStep32), "%s%s%s", Patterns_PATH, TransformF32, "ComplexFFTSamples_Step_32_11_f32.txt");
#else
	f32referenceFileStep32 = TransformF32_ComplexFFTSamples_Step_32_11_f32;
	f32referenceFileStep32Len = sizeof(TransformF32_ComplexFFTSamples_Step_32_11_f32)/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32referenceFileStep64, sizeof(f32referenceFileStep64), "%s%s%s", Patterns_PATH, TransformF32, "ComplexFFTSamples_Step_64_12_f32.txt");
#else
	f32referenceFileStep64 = TransformF32_ComplexFFTSamples_Step_64_12_f32;
	f32referenceFileStep64Len = sizeof(TransformF32_ComplexFFTSamples_Step_64_12_f32)/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32referenceFileStep128, sizeof(f32referenceFileStep128), "%s%s%s", Patterns_PATH, TransformF32, "ComplexFFTSamples_Step_128_13_f32.txt");
#else
	f32referenceFileStep128 = TransformF32_ComplexFFTSamples_Step_128_13_f32;
	f32referenceFileStep128Len = sizeof(TransformF32_ComplexFFTSamples_Step_128_13_f32)/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32referenceFileStep256, sizeof(f32referenceFileStep256), "%s%s%s", Patterns_PATH, TransformF32, "ComplexFFTSamples_Step_256_14_f32.txt");
#else
	f32referenceFileStep256 = TransformF32_ComplexFFTSamples_Step_256_14_f32;
	f32referenceFileStep256Len = sizeof(TransformF32_ComplexFFTSamples_Step_256_14_f32)/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32referenceFileStep512, sizeof(f32referenceFileStep512), "%s%s%s", Patterns_PATH, TransformF32, "ComplexFFTSamples_Step_512_15_f32.txt");
#else
	f32referenceFileStep512 = TransformF32_ComplexFFTSamples_Step_512_15_f32;
	f32referenceFileStep512Len = sizeof(TransformF32_ComplexFFTSamples_Step_512_15_f32)/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32referenceFileStep1024, sizeof(f32referenceFileStep1024), "%s%s%s", Patterns_PATH, TransformF32, "ComplexFFTSamples_Step_1024_16_f32.txt");
#else
	f32referenceFileStep1024 = TransformF32_ComplexFFTSamples_Step_1024_16_f32;
	f32referenceFileStep1024Len = sizeof(TransformF32_ComplexFFTSamples_Step_1024_16_f32)/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32referenceFileStep2048, sizeof(f32referenceFileStep2048), "%s%s%s", Patterns_PATH, TransformF32, "ComplexFFTSamples_Step_2048_17_f32.txt");
#else
	f32referenceFileStep2048 = TransformF32_ComplexFFTSamples_Step_2048_17_f32;
	f32referenceFileStep2048Len = sizeof(TransformF32_ComplexFFTSamples_Step_2048_17_f32)/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32referenceFileStep4096, sizeof(f32referenceFileStep4096), "%s%s%s", Patterns_PATH, TransformF32, "ComplexFFTSamples_Step_4096_18_f32.txt");
#else
	f32referenceFileStep4096 = TransformF32_ComplexFFTSamples_Step_4096_18_f32;
	f32referenceFileStep4096Len = sizeof(TransformF32_ComplexFFTSamples_Step_4096_18_f32)/sizeof(f32);
#endif



	// load input data
#if defined(NOT_EMBEDDED)
	load_data_f32(f32inputFileNoisy16, &paramCountInputNoisy16, f32inputNoisy16);
#else
	paramCountInputNoisy16 = f32inputFileNoisy16Len;
	load_data_f32(f32inputFileNoisy16, paramCountInputNoisy16, f32inputNoisy16);
	paramCountInputNoisy16 = paramCountInputNoisy16/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(f32inputFileNoisy32, &paramCountInputNoisy32, f32inputNoisy32);
#else
	paramCountInputNoisy32 = f32inputFileNoisy32Len;
	load_data_f32(f32inputFileNoisy32, paramCountInputNoisy32, f32inputNoisy32);
	paramCountInputNoisy32 = paramCountInputNoisy32/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(f32inputFileNoisy64, &paramCountInputNoisy64, f32inputNoisy64);
#else
	paramCountInputNoisy64 = f32inputFileNoisy64Len;
	load_data_f32(f32inputFileNoisy64, paramCountInputNoisy64, f32inputNoisy64);
	paramCountInputNoisy64 = paramCountInputNoisy64/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(f32inputFileNoisy128, &paramCountInputNoisy128, f32inputNoisy128);
#else
	paramCountInputNoisy128 = f32inputFileNoisy128Len;
	load_data_f32(f32inputFileNoisy128, paramCountInputNoisy128, f32inputNoisy128);
	paramCountInputNoisy128 = paramCountInputNoisy128/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(f32inputFileNoisy256, &paramCountInputNoisy256, f32inputNoisy256);
#else
	paramCountInputNoisy256 = f32inputFileNoisy256Len;
	load_data_f32(f32inputFileNoisy256, paramCountInputNoisy256, f32inputNoisy256);
	paramCountInputNoisy256 = paramCountInputNoisy256/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(f32inputFileNoisy512, &paramCountInputNoisy512, f32inputNoisy512);
#else
	paramCountInputNoisy512 = f32inputFileNoisy512Len;
	load_data_f32(f32inputFileNoisy512, paramCountInputNoisy512, f32inputNoisy512);
	paramCountInputNoisy512 = paramCountInputNoisy512/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(f32inputFileNoisy1024, &paramCountInputNoisy1024, f32inputNoisy1024);
#else
	paramCountInputNoisy1024 = f32inputFileNoisy1024Len;
	load_data_f32(f32inputFileNoisy1024, paramCountInputNoisy1024, f32inputNoisy1024);
	paramCountInputNoisy1024 = paramCountInputNoisy1024/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(f32inputFileNoisy2048, &paramCountInputNoisy2048, f32inputNoisy2048);
#else
	paramCountInputNoisy2048 = f32inputFileNoisy2048Len;
	load_data_f32(f32inputFileNoisy2048, paramCountInputNoisy2048, f32inputNoisy2048);
	paramCountInputNoisy2048 = paramCountInputNoisy2048/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(f32inputFileNoisy4096, &paramCountInputNoisy4096, f32inputNoisy4096);
#else
	paramCountInputNoisy4096 = f32inputFileNoisy4096Len;
	load_data_f32(f32inputFileNoisy4096, paramCountInputNoisy4096, f32inputNoisy4096);
	paramCountInputNoisy4096 = paramCountInputNoisy4096/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	load_data_f32(f32IFTinputFileNoisy16, &IFTparamCountInputNoisy16, f32IFTinputNoisy16);
#else
	IFTparamCountInputNoisy16 = f32IFTinputFileNoisy16Len;
	load_data_f32(f32IFTinputFileNoisy16, IFTparamCountInputNoisy16, f32IFTinputNoisy16);
	IFTparamCountInputNoisy16 = IFTparamCountInputNoisy16/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(f32IFTinputFileNoisy32, &IFTparamCountInputNoisy32, f32IFTinputNoisy32);
#else
	IFTparamCountInputNoisy32 = f32IFTinputFileNoisy32Len;
	load_data_f32(f32IFTinputFileNoisy32, IFTparamCountInputNoisy32, f32IFTinputNoisy32);
	IFTparamCountInputNoisy32 = IFTparamCountInputNoisy32/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(f32IFTinputFileNoisy64, &IFTparamCountInputNoisy64, f32IFTinputNoisy64);
#else
	IFTparamCountInputNoisy64 = f32IFTinputFileNoisy64Len;
	load_data_f32(f32IFTinputFileNoisy64, IFTparamCountInputNoisy64, f32IFTinputNoisy64);
	IFTparamCountInputNoisy64 = IFTparamCountInputNoisy64/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(f32IFTinputFileNoisy128, &IFTparamCountInputNoisy128, f32IFTinputNoisy128);
#else
	IFTparamCountInputNoisy128 = f32IFTinputFileNoisy128Len;
	load_data_f32(f32IFTinputFileNoisy128, IFTparamCountInputNoisy128, f32IFTinputNoisy128);
	IFTparamCountInputNoisy128 = IFTparamCountInputNoisy128/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(f32IFTinputFileNoisy256, &IFTparamCountInputNoisy256, f32IFTinputNoisy256);
#else
	IFTparamCountInputNoisy256 = f32IFTinputFileNoisy256Len;
	load_data_f32(f32IFTinputFileNoisy256, IFTparamCountInputNoisy256, f32IFTinputNoisy256);
	IFTparamCountInputNoisy256 = IFTparamCountInputNoisy256/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(f32IFTinputFileNoisy512, &IFTparamCountInputNoisy512, f32IFTinputNoisy512);
#else
	IFTparamCountInputNoisy512 = f32IFTinputFileNoisy512Len;
	load_data_f32(f32IFTinputFileNoisy512, IFTparamCountInputNoisy512, f32IFTinputNoisy512);
	IFTparamCountInputNoisy512 = IFTparamCountInputNoisy512/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(f32IFTinputFileNoisy1024, &IFTparamCountInputNoisy1024, f32IFTinputNoisy1024);
#else
	IFTparamCountInputNoisy1024 = f32IFTinputFileNoisy1024Len;
	load_data_f32(f32IFTinputFileNoisy1024, IFTparamCountInputNoisy1024, f32IFTinputNoisy1024);
	IFTparamCountInputNoisy1024 = IFTparamCountInputNoisy1024/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(f32IFTinputFileNoisy2048, &IFTparamCountInputNoisy2048, f32IFTinputNoisy2048);
#else
	IFTparamCountInputNoisy2048 = f32IFTinputFileNoisy2048Len;
	load_data_f32(f32IFTinputFileNoisy2048, IFTparamCountInputNoisy2048, f32IFTinputNoisy2048);
	IFTparamCountInputNoisy2048 = IFTparamCountInputNoisy2048/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(f32IFTinputFileNoisy4096, &IFTparamCountInputNoisy4096, f32IFTinputNoisy4096);
#else
	IFTparamCountInputNoisy4096 = f32IFTinputFileNoisy4096Len;
	load_data_f32(f32IFTinputFileNoisy4096, IFTparamCountInputNoisy4096, f32IFTinputNoisy4096);
	IFTparamCountInputNoisy4096 = IFTparamCountInputNoisy4096/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	load_data_f32(f32inputFileStep16, &paramCountInputStep16, f32inputStep16);
#else
	paramCountInputStep16 = f32inputFileStep16Len;
	load_data_f32(f32inputFileStep16, paramCountInputStep16, f32inputStep16);
	paramCountInputStep16 = paramCountInputStep16/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(f32inputFileStep32, &paramCountInputStep32, f32inputStep32);
#else
	paramCountInputStep32 = f32inputFileStep32Len;
	load_data_f32(f32inputFileStep32, paramCountInputStep32, f32inputStep32);
	paramCountInputStep32 = paramCountInputStep32/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(f32inputFileStep64, &paramCountInputStep64, f32inputStep64);
#else
	paramCountInputStep64 = f32inputFileStep64Len;
	load_data_f32(f32inputFileStep64, paramCountInputStep64, f32inputStep64);
	paramCountInputStep64 = paramCountInputStep64/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(f32inputFileStep128, &paramCountInputStep128, f32inputStep128);
#else
	paramCountInputStep128 = f32inputFileStep128Len;
	load_data_f32(f32inputFileStep128, paramCountInputStep128, f32inputStep128);
	paramCountInputStep128 = paramCountInputStep128/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(f32inputFileStep256, &paramCountInputStep256, f32inputStep256);
#else
	paramCountInputStep256 = f32inputFileStep256Len;
	load_data_f32(f32inputFileStep256, paramCountInputStep256, f32inputStep256);
	paramCountInputStep256 = paramCountInputStep256/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(f32inputFileStep512, &paramCountInputStep512, f32inputStep512);
#else
	paramCountInputStep512 = f32inputFileStep512Len;
	load_data_f32(f32inputFileStep512, paramCountInputStep512, f32inputStep512);
	paramCountInputStep512 = paramCountInputStep512/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(f32inputFileStep1024, &paramCountInputStep1024, f32inputStep1024);
#else
	paramCountInputStep1024 = f32inputFileStep1024Len;
	load_data_f32(f32inputFileStep1024, paramCountInputStep1024, f32inputStep1024);
	paramCountInputStep1024 = paramCountInputStep1024/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(f32inputFileStep2048, &paramCountInputStep2048, f32inputStep2048);
#else
	paramCountInputStep2048 = f32inputFileStep2048Len;
	load_data_f32(f32inputFileStep2048, paramCountInputStep2048, f32inputStep2048);
	paramCountInputStep2048 = paramCountInputStep2048/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(f32inputFileStep4096, &paramCountInputStep4096, f32inputStep4096);
#else
	paramCountInputStep4096 = f32inputFileStep4096Len;
	load_data_f32(f32inputFileStep4096, paramCountInputStep4096, f32inputStep4096);
	paramCountInputStep4096 = paramCountInputStep4096/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	load_data_f32(f32IFTinputFileStep16, &IFTparamCountInputStep16, f32IFTinputStep16);
#else
	IFTparamCountInputStep16 = f32IFTinputFileStep16Len;
	load_data_f32(f32IFTinputFileStep16, IFTparamCountInputStep16, f32IFTinputStep16);
	IFTparamCountInputStep16 = IFTparamCountInputStep16/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(f32IFTinputFileStep32, &IFTparamCountInputStep32, f32IFTinputStep32);
#else
	IFTparamCountInputStep32 = f32IFTinputFileStep32Len;
	load_data_f32(f32IFTinputFileStep32, IFTparamCountInputStep32, f32IFTinputStep32);
	IFTparamCountInputStep32 = IFTparamCountInputStep32/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(f32IFTinputFileStep64, &IFTparamCountInputStep64, f32IFTinputStep64);
#else
	IFTparamCountInputStep64 = f32IFTinputFileStep64Len;
	load_data_f32(f32IFTinputFileStep64, IFTparamCountInputStep64, f32IFTinputStep64);
	IFTparamCountInputStep64 = IFTparamCountInputStep64/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(f32IFTinputFileStep128, &IFTparamCountInputStep128, f32IFTinputStep128);
#else
	IFTparamCountInputStep128 = f32IFTinputFileStep128Len;
	load_data_f32(f32IFTinputFileStep128, IFTparamCountInputStep128, f32IFTinputStep128);
	IFTparamCountInputStep128 = IFTparamCountInputStep128/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(f32IFTinputFileStep256, &IFTparamCountInputStep256, f32IFTinputStep256);
#else
	IFTparamCountInputStep256 = f32IFTinputFileStep256Len;
	load_data_f32(f32IFTinputFileStep256, IFTparamCountInputStep256, f32IFTinputStep256);
	IFTparamCountInputStep256 = IFTparamCountInputStep256/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(f32IFTinputFileStep512, &IFTparamCountInputStep512, f32IFTinputStep512);
#else
	IFTparamCountInputStep512 = f32IFTinputFileStep512Len;
	load_data_f32(f32IFTinputFileStep512, IFTparamCountInputStep512, f32IFTinputStep512);
	IFTparamCountInputStep512 = IFTparamCountInputStep512/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(f32IFTinputFileStep1024, &IFTparamCountInputStep1024, f32IFTinputStep1024);
#else
	IFTparamCountInputStep1024 = f32IFTinputFileStep1024Len;
	load_data_f32(f32IFTinputFileStep1024, IFTparamCountInputStep1024, f32IFTinputStep1024);
	IFTparamCountInputStep1024 = IFTparamCountInputStep1024/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(f32IFTinputFileStep2048, &IFTparamCountInputStep2048, f32IFTinputStep2048);
#else
	IFTparamCountInputStep2048 = f32IFTinputFileStep2048Len;
	load_data_f32(f32IFTinputFileStep2048, IFTparamCountInputStep2048, f32IFTinputStep2048);
	IFTparamCountInputStep2048 = IFTparamCountInputStep2048/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(f32IFTinputFileStep4096, &IFTparamCountInputStep4096, f32IFTinputStep4096);
#else
	IFTparamCountInputStep4096 = f32IFTinputFileStep4096Len;
	load_data_f32(f32IFTinputFileStep4096, IFTparamCountInputStep4096, f32IFTinputStep4096);
	IFTparamCountInputStep4096 = IFTparamCountInputStep4096/sizeof(f32);
#endif


    f32 f32output[MAX_SIZE] = {0};
    int ifft;
    mips_status status;
    mips_cfft_instance_f32 varInstCfftF32;
// =====================
	printf("== mips_cfft_f32 Noisy_16 test ==  \n");

        memcpy(f32output,f32inputNoisy16,sizeof(f32)*paramCountInputNoisy16);

        status=mips_cfft_init_f32(&varInstCfftF32,16);
        ifft = 0;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
   
        mips_cfft_f32(&(varInstCfftF32), f32output, ifft, 1);

	printf("mips_cfft_f32 Noisy_16 finish \n");

	printf("mips_cfft_f32 Noisy_16 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(f32referenceFileNoisy16, f32output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(f32referenceFileNoisy16, f32output, f32referenceFileNoisy16Len, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_f32 Noisy_16 check done  == \n\n");

// =====================
	printf("== mips_cfft_f32 IFTNoisy_16 test ==  \n");

        memcpy(f32output,f32IFTinputNoisy16,sizeof(f32)*IFTparamCountInputNoisy16);

        status=mips_cfft_init_f32(&varInstCfftF32,16);
        ifft = 1;

        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
   
        mips_cfft_f32(&(varInstCfftF32), f32output, ifft, 1);

	printf("mips_cfft_f32 IFTNoisy_16 finish \n");

	printf("mips_cfft_f32 IFTNoisy_16 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(f32inputFileNoisy16, f32output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(f32inputNoisy16, f32output, paramCountInputNoisy16, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_f32 IFTNoisy_16 check done  == \n\n");

// =====================
	printf("== mips_cfft_f32 Noisy_32 test ==  \n");

        memcpy(f32output,f32inputNoisy32,sizeof(f32)*paramCountInputNoisy32);

        status=mips_cfft_init_f32(&varInstCfftF32,32);
        ifft = 0;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
   
        mips_cfft_f32(&(varInstCfftF32), f32output, ifft, 1);

	printf("mips_cfft_f32 Noisy_32 finish \n");

	printf("mips_cfft_f32 Noisy_32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(f32referenceFileNoisy32, f32output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(f32referenceFileNoisy32, f32output, f32referenceFileNoisy32Len, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_f32 Noisy_32 check done  == \n\n");

// =====================
	printf("== mips_cfft_f32 IFTNoisy_32 test ==  \n");

        memcpy(f32output,f32IFTinputNoisy32,sizeof(f32)*IFTparamCountInputNoisy32);

        status=mips_cfft_init_f32(&varInstCfftF32,32);
        ifft = 1;

        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
   
        mips_cfft_f32(&(varInstCfftF32), f32output, ifft, 1);

	printf("mips_cfft_f32 IFTNoisy_32 finish \n");

	printf("mips_cfft_f32 IFTNoisy_32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(f32inputFileNoisy32, f32output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(f32inputNoisy32, f32output, paramCountInputNoisy32, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_f32 IFTNoisy_32 check done  == \n\n");

// =====================
	printf("== mips_cfft_f32 Noisy_64 test ==  \n");

        memcpy(f32output,f32inputNoisy64,sizeof(f32)*paramCountInputNoisy64);

        status=mips_cfft_init_f32(&varInstCfftF32,64);
        ifft = 0;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
   
        mips_cfft_f32(&(varInstCfftF32), f32output, ifft, 1);

	printf("mips_cfft_f32 Noisy_64 finish \n");

	printf("mips_cfft_f32 Noisy_64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(f32referenceFileNoisy64, f32output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(f32referenceFileNoisy64, f32output, f32referenceFileNoisy64Len, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_f32 Noisy_64 check done  == \n\n");

// =====================
	printf("== mips_cfft_f32 IFTNoisy_64 test ==  \n");

        memcpy(f32output,f32IFTinputNoisy64,sizeof(f32)*IFTparamCountInputNoisy64);

        status=mips_cfft_init_f32(&varInstCfftF32,64);
        ifft = 1;

        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
   
        mips_cfft_f32(&(varInstCfftF32), f32output, ifft, 1);

	printf("mips_cfft_f32 IFTNoisy_64 finish \n");

	printf("mips_cfft_f32 IFTNoisy_64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(f32inputFileNoisy64, f32output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(f32inputNoisy64, f32output, paramCountInputNoisy64, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_f32 IFTNoisy_64 check done  == \n\n");

// =====================
	printf("== mips_cfft_f32 Noisy_128 test ==  \n");

        memcpy(f32output,f32inputNoisy128,sizeof(f32)*paramCountInputNoisy128);

        status=mips_cfft_init_f32(&varInstCfftF32,128);
        ifft = 0;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
   
        mips_cfft_f32(&(varInstCfftF32), f32output, ifft, 1);

	printf("mips_cfft_f32 Noisy_128 finish \n");

	printf("mips_cfft_f32 Noisy_128 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(f32referenceFileNoisy128, f32output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(f32referenceFileNoisy128, f32output, f32referenceFileNoisy128Len, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_f32 Noisy_128 check done  == \n\n");

// =====================
	printf("== mips_cfft_f32 IFTNoisy_128 test ==  \n");

        memcpy(f32output,f32IFTinputNoisy128,sizeof(f32)*IFTparamCountInputNoisy128);

        status=mips_cfft_init_f32(&varInstCfftF32,128);
        ifft = 1;

        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
   
        mips_cfft_f32(&(varInstCfftF32), f32output, ifft, 1);

	printf("mips_cfft_f32 IFTNoisy_128 finish \n");

	printf("mips_cfft_f32 IFTNoisy_128 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(f32inputFileNoisy128, f32output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(f32inputNoisy128, f32output, paramCountInputNoisy128, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_f32 IFTNoisy_128 check done  == \n\n");

// =====================
	printf("== mips_cfft_f32 Noisy_256 test ==  \n");

        memcpy(f32output,f32inputNoisy256,sizeof(f32)*paramCountInputNoisy256);

        status=mips_cfft_init_f32(&varInstCfftF32,256);
        ifft = 0;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
   
        mips_cfft_f32(&(varInstCfftF32), f32output, ifft, 1);

	printf("mips_cfft_f32 Noisy_256 finish \n");

	printf("mips_cfft_f32 Noisy_256 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(f32referenceFileNoisy256, f32output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(f32referenceFileNoisy256, f32output, f32referenceFileNoisy256Len, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_f32 Noisy_256 check done  == \n\n");

// =====================
	printf("== mips_cfft_f32 IFTNoisy_256 test ==  \n");

        memcpy(f32output,f32IFTinputNoisy256,sizeof(f32)*IFTparamCountInputNoisy256);

        status=mips_cfft_init_f32(&varInstCfftF32,256);
        ifft = 1;

        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
   
        mips_cfft_f32(&(varInstCfftF32), f32output, ifft, 1);

	printf("mips_cfft_f32 IFTNoisy_256 finish \n");

	printf("mips_cfft_f32 IFTNoisy_256 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(f32inputFileNoisy256, f32output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(f32inputNoisy256, f32output, paramCountInputNoisy256, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_f32 IFTNoisy_256 check done  == \n\n");

// =====================
	printf("== mips_cfft_f32 Noisy_512 test ==  \n");

        memcpy(f32output,f32inputNoisy512,sizeof(f32)*paramCountInputNoisy512);

        status=mips_cfft_init_f32(&varInstCfftF32,512);
        ifft = 0;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
   
        mips_cfft_f32(&(varInstCfftF32), f32output, ifft, 1);

	printf("mips_cfft_f32 Noisy_512 finish \n");

	printf("mips_cfft_f32 Noisy_512 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(f32referenceFileNoisy512, f32output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(f32referenceFileNoisy512, f32output, f32referenceFileNoisy512Len, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_f32 Noisy_512 check done  == \n\n");

// =====================
	printf("== mips_cfft_f32 IFTNoisy_512 test ==  \n");

        memcpy(f32output,f32IFTinputNoisy512,sizeof(f32)*IFTparamCountInputNoisy512);

        status=mips_cfft_init_f32(&varInstCfftF32,512);
        ifft = 1;

        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
   
        mips_cfft_f32(&(varInstCfftF32), f32output, ifft, 1);

	printf("mips_cfft_f32 IFTNoisy_512 finish \n");

	printf("mips_cfft_f32 IFTNoisy_512 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(f32inputFileNoisy512, f32output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(f32inputNoisy512, f32output, paramCountInputNoisy512, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_f32 IFTNoisy_512 check done  == \n\n");

// =====================
	printf("== mips_cfft_f32 Noisy_1024 test ==  \n");

        memcpy(f32output,f32inputNoisy1024,sizeof(f32)*paramCountInputNoisy1024);

        status=mips_cfft_init_f32(&varInstCfftF32,1024);
        ifft = 0;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
   
        mips_cfft_f32(&(varInstCfftF32), f32output, ifft, 1);

	printf("mips_cfft_f32 Noisy_1024 finish \n");

	printf("mips_cfft_f32 Noisy_1024 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(f32referenceFileNoisy1024, f32output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(f32referenceFileNoisy1024, f32output, f32referenceFileNoisy1024Len, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_f32 Noisy_1024 check done  == \n\n");

// =====================
	printf("== mips_cfft_f32 IFTNoisy_1024 test ==  \n");

        memcpy(f32output,f32IFTinputNoisy1024,sizeof(f32)*IFTparamCountInputNoisy1024);

        status=mips_cfft_init_f32(&varInstCfftF32,1024);
        ifft = 1;

        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
   
        mips_cfft_f32(&(varInstCfftF32), f32output, ifft, 1);

	printf("mips_cfft_f32 IFTNoisy_1024 finish \n");

	printf("mips_cfft_f32 IFTNoisy_1024 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(f32inputFileNoisy1024, f32output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(f32inputNoisy1024, f32output, paramCountInputNoisy1024, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_f32 IFTNoisy_1024 check done  == \n\n");

// =====================
	printf("== mips_cfft_f32 Noisy_2048 test ==  \n");

        memcpy(f32output,f32inputNoisy2048,sizeof(f32)*paramCountInputNoisy2048);

        status=mips_cfft_init_f32(&varInstCfftF32,2048);
        ifft = 0;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
   
        mips_cfft_f32(&(varInstCfftF32), f32output, ifft, 1);

	printf("mips_cfft_f32 Noisy_2048 finish \n");

	printf("mips_cfft_f32 Noisy_2048 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(f32referenceFileNoisy2048, f32output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(f32referenceFileNoisy2048, f32output, f32referenceFileNoisy2048Len, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_f32 Noisy_2048 check done  == \n\n");

// =====================
	printf("== mips_cfft_f32 IFTNoisy_2048 test ==  \n");

        memcpy(f32output,f32IFTinputNoisy2048,sizeof(f32)*IFTparamCountInputNoisy2048);

        status=mips_cfft_init_f32(&varInstCfftF32,2048);
        ifft = 1;

        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
   
        mips_cfft_f32(&(varInstCfftF32), f32output, ifft, 1);

	printf("mips_cfft_f32 IFTNoisy_2048 finish \n");

	printf("mips_cfft_f32 IFTNoisy_2048 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(f32inputFileNoisy2048, f32output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(f32inputNoisy2048, f32output, paramCountInputNoisy2048, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_f32 IFTNoisy_2048 check done  == \n\n");

// =====================
	printf("== mips_cfft_f32 Noisy_4096 test ==  \n");

        memcpy(f32output,f32inputNoisy4096,sizeof(f32)*paramCountInputNoisy4096);

        status=mips_cfft_init_f32(&varInstCfftF32,4096);
        ifft = 0;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
   
        mips_cfft_f32(&(varInstCfftF32), f32output, ifft, 1);

	printf("mips_cfft_f32 Noisy_4096 finish \n");

	printf("mips_cfft_f32 Noisy_4096 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(f32referenceFileNoisy4096, f32output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(f32referenceFileNoisy4096, f32output, f32referenceFileNoisy4096Len, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_f32 Noisy_4096 check done  == \n\n");

// =====================
	printf("== mips_cfft_f32 IFTNoisy_4096 test ==  \n");

        memcpy(f32output,f32IFTinputNoisy4096,sizeof(f32)*IFTparamCountInputNoisy4096);

        status=mips_cfft_init_f32(&varInstCfftF32,4096);
        ifft = 1;

        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
   
        mips_cfft_f32(&(varInstCfftF32), f32output, ifft, 1);

	printf("mips_cfft_f32 IFTNoisy_4096 finish \n");

	printf("mips_cfft_f32 IFTNoisy_4096 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(f32inputFileNoisy4096, f32output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(f32inputNoisy4096, f32output, paramCountInputNoisy4096, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_f32 IFTNoisy_4096 check done  == \n\n");


// =====================
	printf("== mips_cfft_f32 Step_16 test ==  \n");

        memcpy(f32output,f32inputStep16,sizeof(f32)*paramCountInputStep16);

        status=mips_cfft_init_f32(&varInstCfftF32,16);
        ifft = 0;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
   
        mips_cfft_f32(&(varInstCfftF32), f32output, ifft, 1);

	printf("mips_cfft_f32 Step_16 finish \n");

	printf("mips_cfft_f32 Step_16 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(f32referenceFileStep16, f32output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(f32referenceFileStep16, f32output, f32referenceFileStep16Len, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_f32 Step_16 check done  == \n\n");

// =====================
	printf("== mips_cfft_f32 IFTStep_16 test ==  \n");

        memcpy(f32output,f32IFTinputStep16,sizeof(f32)*IFTparamCountInputStep16);

        status=mips_cfft_init_f32(&varInstCfftF32,16);
        ifft = 1;

        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
   
        mips_cfft_f32(&(varInstCfftF32), f32output, ifft, 1);

	printf("mips_cfft_f32 IFTStep_16 finish \n");

	printf("mips_cfft_f32 IFTStep_16 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(f32inputFileStep16, f32output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(f32inputStep16, f32output, paramCountInputStep16, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_f32 IFTStep_16 check done  == \n\n");

// =====================
	printf("== mips_cfft_f32 Step_32 test ==  \n");

        memcpy(f32output,f32inputStep32,sizeof(f32)*paramCountInputStep32);

        status=mips_cfft_init_f32(&varInstCfftF32,32);
        ifft = 0;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
   
        mips_cfft_f32(&(varInstCfftF32), f32output, ifft, 1);

	printf("mips_cfft_f32 Step_32 finish \n");

	printf("mips_cfft_f32 Step_32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(f32referenceFileStep32, f32output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(f32referenceFileStep32, f32output, f32referenceFileStep32Len, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_f32 Step_32 check done  == \n\n");

// =====================
	printf("== mips_cfft_f32 IFTStep_32 test ==  \n");

        memcpy(f32output,f32IFTinputStep32,sizeof(f32)*IFTparamCountInputStep32);

        status=mips_cfft_init_f32(&varInstCfftF32,32);
        ifft = 1;

        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
   
        mips_cfft_f32(&(varInstCfftF32), f32output, ifft, 1);

	printf("mips_cfft_f32 IFTStep_32 finish \n");

	printf("mips_cfft_f32 IFTStep_32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(f32inputFileStep32, f32output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(f32inputStep32, f32output, paramCountInputStep32, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_f32 IFTStep_32 check done  == \n\n");

// =====================
	printf("== mips_cfft_f32 Step_64 test ==  \n");

        memcpy(f32output,f32inputStep64,sizeof(f32)*paramCountInputStep64);

        status=mips_cfft_init_f32(&varInstCfftF32,64);
        ifft = 0;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
   
        mips_cfft_f32(&(varInstCfftF32), f32output, ifft, 1);

	printf("mips_cfft_f32 Step_64 finish \n");

	printf("mips_cfft_f32 Step_64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(f32referenceFileStep64, f32output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(f32referenceFileStep64, f32output, f32referenceFileStep64Len, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_f32 Step_64 check done  == \n\n");

// =====================
	printf("== mips_cfft_f32 IFTStep_64 test ==  \n");

        memcpy(f32output,f32IFTinputStep64,sizeof(f32)*IFTparamCountInputStep64);

        status=mips_cfft_init_f32(&varInstCfftF32,64);
        ifft = 1;

        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
   
        mips_cfft_f32(&(varInstCfftF32), f32output, ifft, 1);

	printf("mips_cfft_f32 IFTStep_64 finish \n");

	printf("mips_cfft_f32 IFTStep_64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(f32inputFileStep64, f32output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(f32inputStep64, f32output, paramCountInputStep64, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_f32 IFTStep_64 check done  == \n\n");

// =====================
	printf("== mips_cfft_f32 Step_128 test ==  \n");

        memcpy(f32output,f32inputStep128,sizeof(f32)*paramCountInputStep128);

        status=mips_cfft_init_f32(&varInstCfftF32,128);
        ifft = 0;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
   
        mips_cfft_f32(&(varInstCfftF32), f32output, ifft, 1);

	printf("mips_cfft_f32 Step_128 finish \n");

	printf("mips_cfft_f32 Step_128 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(f32referenceFileStep128, f32output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(f32referenceFileStep128, f32output, f32referenceFileStep128Len, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_f32 Step_128 check done  == \n\n");

// =====================
	printf("== mips_cfft_f32 IFTStep_128 test ==  \n");

        memcpy(f32output,f32IFTinputStep128,sizeof(f32)*IFTparamCountInputStep128);

        status=mips_cfft_init_f32(&varInstCfftF32,128);
        ifft = 1;

        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
   
        mips_cfft_f32(&(varInstCfftF32), f32output, ifft, 1);

	printf("mips_cfft_f32 IFTStep_128 finish \n");

	printf("mips_cfft_f32 IFTStep_128 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(f32inputFileStep128, f32output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(f32inputStep128, f32output, paramCountInputStep128, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_f32 IFTStep_128 check done  == \n\n");

// =====================
	printf("== mips_cfft_f32 Step_256 test ==  \n");

        memcpy(f32output,f32inputStep256,sizeof(f32)*paramCountInputStep256);

        status=mips_cfft_init_f32(&varInstCfftF32,256);
        ifft = 0;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
   
        mips_cfft_f32(&(varInstCfftF32), f32output, ifft, 1);

	printf("mips_cfft_f32 Step_256 finish \n");

	printf("mips_cfft_f32 Step_256 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(f32referenceFileStep256, f32output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(f32referenceFileStep256, f32output, f32referenceFileStep256Len, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_f32 Step_256 check done  == \n\n");

// =====================
	printf("== mips_cfft_f32 IFTStep_256 test ==  \n");

        memcpy(f32output,f32IFTinputStep256,sizeof(f32)*IFTparamCountInputStep256);

        status=mips_cfft_init_f32(&varInstCfftF32,256);
        ifft = 1;

        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
   
        mips_cfft_f32(&(varInstCfftF32), f32output, ifft, 1);

	printf("mips_cfft_f32 IFTStep_256 finish \n");

	printf("mips_cfft_f32 IFTStep_256 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(f32inputFileStep256, f32output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(f32inputStep256, f32output, paramCountInputStep256, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_f32 IFTStep_256 check done  == \n\n");

// =====================
	printf("== mips_cfft_f32 Step_512 test ==  \n");

        memcpy(f32output,f32inputStep512,sizeof(f32)*paramCountInputStep512);

        status=mips_cfft_init_f32(&varInstCfftF32,512);
        ifft = 0;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
   
        mips_cfft_f32(&(varInstCfftF32), f32output, ifft, 1);

	printf("mips_cfft_f32 Step_512 finish \n");

	printf("mips_cfft_f32 Step_512 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(f32referenceFileStep512, f32output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(f32referenceFileStep512, f32output, f32referenceFileStep512Len, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_f32 Step_512 check done  == \n\n");

// =====================
	printf("== mips_cfft_f32 IFTStep_512 test ==  \n");

        memcpy(f32output,f32IFTinputStep512,sizeof(f32)*IFTparamCountInputStep512);

        status=mips_cfft_init_f32(&varInstCfftF32,512);
        ifft = 1;

        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
   
        mips_cfft_f32(&(varInstCfftF32), f32output, ifft, 1);

	printf("mips_cfft_f32 IFTStep_512 finish \n");

	printf("mips_cfft_f32 IFTStep_512 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(f32inputFileStep512, f32output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(f32inputStep512, f32output, paramCountInputStep512, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_f32 IFTStep_512 check done  == \n\n");

// =====================
	printf("== mips_cfft_f32 Step_1024 test ==  \n");

        memcpy(f32output,f32inputStep1024,sizeof(f32)*paramCountInputStep1024);

        status=mips_cfft_init_f32(&varInstCfftF32,1024);
        ifft = 0;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
   
        mips_cfft_f32(&(varInstCfftF32), f32output, ifft, 1);

	printf("mips_cfft_f32 Step_1024 finish \n");

	printf("mips_cfft_f32 Step_1024 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(f32referenceFileStep1024, f32output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(f32referenceFileStep1024, f32output, f32referenceFileStep1024Len, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_f32 Step_1024 check done  == \n\n");

// =====================
	printf("== mips_cfft_f32 IFTStep_1024 test ==  \n");

        memcpy(f32output,f32IFTinputStep1024,sizeof(f32)*IFTparamCountInputStep1024);

        status=mips_cfft_init_f32(&varInstCfftF32,1024);
        ifft = 1;

        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
   
        mips_cfft_f32(&(varInstCfftF32), f32output, ifft, 1);

	printf("mips_cfft_f32 IFTStep_1024 finish \n");

	printf("mips_cfft_f32 IFTStep_1024 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(f32inputFileStep1024, f32output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(f32inputStep1024, f32output, paramCountInputStep1024, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_f32 IFTStep_1024 check done  == \n\n");

// =====================
	printf("== mips_cfft_f32 Step_2048 test ==  \n");

        memcpy(f32output,f32inputStep2048,sizeof(f32)*paramCountInputStep2048);

        status=mips_cfft_init_f32(&varInstCfftF32,2048);
        ifft = 0;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
   
        mips_cfft_f32(&(varInstCfftF32), f32output, ifft, 1);

	printf("mips_cfft_f32 Step_2048 finish \n");

	printf("mips_cfft_f32 Step_2048 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(f32referenceFileStep2048, f32output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(f32referenceFileStep2048, f32output, f32referenceFileStep2048Len, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_f32 Step_2048 check done  == \n\n");

// =====================
	printf("== mips_cfft_f32 IFTStep_2048 test ==  \n");

        memcpy(f32output,f32IFTinputStep2048,sizeof(f32)*IFTparamCountInputStep2048);

        status=mips_cfft_init_f32(&varInstCfftF32,2048);
        ifft = 1;

        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
   
        mips_cfft_f32(&(varInstCfftF32), f32output, ifft, 1);

	printf("mips_cfft_f32 IFTStep_2048 finish \n");

	printf("mips_cfft_f32 IFTStep_2048 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(f32inputFileStep2048, f32output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(f32inputStep2048, f32output, paramCountInputStep2048, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_f32 IFTStep_2048 check done  == \n\n");

// =====================
	printf("== mips_cfft_f32 Step_4096 test ==  \n");

        memcpy(f32output,f32inputStep4096,sizeof(f32)*paramCountInputStep4096);

        status=mips_cfft_init_f32(&varInstCfftF32,4096);
        ifft = 0;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
   
        mips_cfft_f32(&(varInstCfftF32), f32output, ifft, 1);

	printf("mips_cfft_f32 Step_4096 finish \n");

	printf("mips_cfft_f32 Step_4096 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(f32referenceFileStep4096, f32output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(f32referenceFileStep4096, f32output, f32referenceFileStep4096Len, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_f32 Step_4096 check done  == \n\n");

// =====================
	printf("== mips_cfft_f32 IFTStep_4096 test ==  \n");

        memcpy(f32output,f32IFTinputStep4096,sizeof(f32)*IFTparamCountInputStep4096);

        status=mips_cfft_init_f32(&varInstCfftF32,4096);
        ifft = 1;

        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
   
        mips_cfft_f32(&(varInstCfftF32), f32output, ifft, 1);

	printf("mips_cfft_f32 IFTStep_4096 finish \n");

	printf("mips_cfft_f32 IFTStep_4096 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(f32inputFileStep4096, f32output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(f32inputStep4096, f32output, paramCountInputStep4096, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_f32 IFTStep_4096 check done  == \n\n");

    return 0;
}