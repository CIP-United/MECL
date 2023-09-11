#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/transform_functions.h"
#include "mips_common_tables.h"
#include "mips_const_structs.h"

#define SNR_THRESHOLD 90

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

    q31 q31inputNoisy16[MAX_SIZE] = {0};
    q31 q31inputNoisy32[MAX_SIZE] = {0};
    q31 q31inputNoisy64[MAX_SIZE] = {0};
    q31 q31inputNoisy128[MAX_SIZE] = {0};
    q31 q31inputNoisy256[MAX_SIZE] = {0};
    q31 q31inputNoisy512[MAX_SIZE] = {0};
    q31 q31inputNoisy1024[MAX_SIZE] = {0};
    q31 q31inputNoisy2048[MAX_SIZE] = {0};
    q31 q31inputNoisy4096[MAX_SIZE] = {0};

	int IFTparamCountInputNoisy16 = 0;
    int IFTparamCountInputNoisy32 = 0;
    int IFTparamCountInputNoisy64 = 0;
    int IFTparamCountInputNoisy128 = 0;
    int IFTparamCountInputNoisy256 = 0;
    int IFTparamCountInputNoisy512 = 0;
    int IFTparamCountInputNoisy1024 = 0;
    int IFTparamCountInputNoisy2048 = 0;
    int IFTparamCountInputNoisy4096 = 0;

    q31 q31IFTinputNoisy16[MAX_SIZE] = {0};
    q31 q31IFTinputNoisy32[MAX_SIZE] = {0};
    q31 q31IFTinputNoisy64[MAX_SIZE] = {0};
    q31 q31IFTinputNoisy128[MAX_SIZE] = {0};
    q31 q31IFTinputNoisy256[MAX_SIZE] = {0};
    q31 q31IFTinputNoisy512[MAX_SIZE] = {0};
    q31 q31IFTinputNoisy1024[MAX_SIZE] = {0};
    q31 q31IFTinputNoisy2048[MAX_SIZE] = {0};
    q31 q31IFTinputNoisy4096[MAX_SIZE] = {0};

	int paramCountInputStep16 = 0;
    int paramCountInputStep32 = 0;
    int paramCountInputStep64 = 0;
    int paramCountInputStep128 = 0;
    int paramCountInputStep256 = 0;
    int paramCountInputStep512 = 0;
    int paramCountInputStep1024 = 0;
    int paramCountInputStep2048 = 0;
    int paramCountInputStep4096 = 0;

    q31 q31inputStep16[MAX_SIZE] = {0};
    q31 q31inputStep32[MAX_SIZE] = {0};
    q31 q31inputStep64[MAX_SIZE] = {0};
    q31 q31inputStep128[MAX_SIZE] = {0};
    q31 q31inputStep256[MAX_SIZE] = {0};
    q31 q31inputStep512[MAX_SIZE] = {0};
    q31 q31inputStep1024[MAX_SIZE] = {0};
    q31 q31inputStep2048[MAX_SIZE] = {0};
    q31 q31inputStep4096[MAX_SIZE] = {0};

	int IFTparamCountInputStep16 = 0;
    int IFTparamCountInputStep32 = 0;
    int IFTparamCountInputStep64 = 0;
    int IFTparamCountInputStep128 = 0;
    int IFTparamCountInputStep256 = 0;
    int IFTparamCountInputStep512 = 0;
    int IFTparamCountInputStep1024 = 0;
    int IFTparamCountInputStep2048 = 0;
    int IFTparamCountInputStep4096 = 0;

    q31 q31IFTinputStep16[MAX_SIZE] = {0};
    q31 q31IFTinputStep32[MAX_SIZE] = {0};
    q31 q31IFTinputStep64[MAX_SIZE] = {0};
    q31 q31IFTinputStep128[MAX_SIZE] = {0};
    q31 q31IFTinputStep256[MAX_SIZE] = {0};
    q31 q31IFTinputStep512[MAX_SIZE] = {0};
    q31 q31IFTinputStep1024[MAX_SIZE] = {0};
    q31 q31IFTinputStep2048[MAX_SIZE] = {0};
    q31 q31IFTinputStep4096[MAX_SIZE] = {0};

	// file name. file path max length is 255, so use 255.

#if defined(NOT_EMBEDDED)
	char q31inputFileNoisy16[255] = {0};
#else
	void *q31inputFileNoisy16;
	int q31inputFileNoisy16Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31inputFileNoisy32[255] = {0};
#else
	void *q31inputFileNoisy32;
	int q31inputFileNoisy32Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31inputFileNoisy64[255] = {0};
#else
	void *q31inputFileNoisy64;
	int q31inputFileNoisy64Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31inputFileNoisy128[255] = {0};
#else
	void *q31inputFileNoisy128;
	int q31inputFileNoisy128Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31inputFileNoisy256[255] = {0};
#else
	void *q31inputFileNoisy256;
	int q31inputFileNoisy256Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31inputFileNoisy512[255] = {0};
#else
	void *q31inputFileNoisy512;
	int q31inputFileNoisy512Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31inputFileNoisy1024[255] = {0};
#else
	void *q31inputFileNoisy1024;
	int q31inputFileNoisy1024Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31inputFileNoisy2048[255] = {0};
#else
	void *q31inputFileNoisy2048;
	int q31inputFileNoisy2048Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31inputFileNoisy4096[255] = {0};
#else
	void *q31inputFileNoisy4096;
	int q31inputFileNoisy4096Len = 0;
#endif


#if defined(NOT_EMBEDDED)
	char q31inputFileStep16[255] = {0};
#else
	void *q31inputFileStep16;
	int q31inputFileStep16Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31inputFileStep32[255] = {0};
#else
	void *q31inputFileStep32;
	int q31inputFileStep32Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31inputFileStep64[255] = {0};
#else
	void *q31inputFileStep64;
	int q31inputFileStep64Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31inputFileStep128[255] = {0};
#else
	void *q31inputFileStep128;
	int q31inputFileStep128Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31inputFileStep256[255] = {0};
#else
	void *q31inputFileStep256;
	int q31inputFileStep256Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31inputFileStep512[255] = {0};
#else
	void *q31inputFileStep512;
	int q31inputFileStep512Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31inputFileStep1024[255] = {0};
#else
	void *q31inputFileStep1024;
	int q31inputFileStep1024Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31inputFileStep2048[255] = {0};
#else
	void *q31inputFileStep2048;
	int q31inputFileStep2048Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31inputFileStep4096[255] = {0};
#else
	void *q31inputFileStep4096;
	int q31inputFileStep4096Len = 0;
#endif


#if defined(NOT_EMBEDDED)
	char q31IFTinputFileNoisy16[255] = {0};
#else
	void *q31IFTinputFileNoisy16;
	int q31IFTinputFileNoisy16Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31IFTinputFileNoisy32[255] = {0};
#else
	void *q31IFTinputFileNoisy32;
	int q31IFTinputFileNoisy32Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31IFTinputFileNoisy64[255] = {0};
#else
	void *q31IFTinputFileNoisy64;
	int q31IFTinputFileNoisy64Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31IFTinputFileNoisy128[255] = {0};
#else
	void *q31IFTinputFileNoisy128;
	int q31IFTinputFileNoisy128Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31IFTinputFileNoisy256[255] = {0};
#else
	void *q31IFTinputFileNoisy256;
	int q31IFTinputFileNoisy256Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31IFTinputFileNoisy512[255] = {0};
#else
	void *q31IFTinputFileNoisy512;
	int q31IFTinputFileNoisy512Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31IFTinputFileNoisy1024[255] = {0};
#else
	void *q31IFTinputFileNoisy1024;
	int q31IFTinputFileNoisy1024Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31IFTinputFileNoisy2048[255] = {0};
#else
	void *q31IFTinputFileNoisy2048;
	int q31IFTinputFileNoisy2048Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31IFTinputFileNoisy4096[255] = {0};
#else
	void *q31IFTinputFileNoisy4096;
	int q31IFTinputFileNoisy4096Len = 0;
#endif


#if defined(NOT_EMBEDDED)
	char q31IFTinputFileStep16[255] = {0};
#else
	void *q31IFTinputFileStep16;
	int q31IFTinputFileStep16Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31IFTinputFileStep32[255] = {0};
#else
	void *q31IFTinputFileStep32;
	int q31IFTinputFileStep32Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31IFTinputFileStep64[255] = {0};
#else
	void *q31IFTinputFileStep64;
	int q31IFTinputFileStep64Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31IFTinputFileStep128[255] = {0};
#else
	void *q31IFTinputFileStep128;
	int q31IFTinputFileStep128Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31IFTinputFileStep256[255] = {0};
#else
	void *q31IFTinputFileStep256;
	int q31IFTinputFileStep256Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31IFTinputFileStep512[255] = {0};
#else
	void *q31IFTinputFileStep512;
	int q31IFTinputFileStep512Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31IFTinputFileStep1024[255] = {0};
#else
	void *q31IFTinputFileStep1024;
	int q31IFTinputFileStep1024Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31IFTinputFileStep2048[255] = {0};
#else
	void *q31IFTinputFileStep2048;
	int q31IFTinputFileStep2048Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31IFTinputFileStep4096[255] = {0};
#else
	void *q31IFTinputFileStep4096;
	int q31IFTinputFileStep4096Len = 0;
#endif



#if defined(NOT_EMBEDDED)
	char q31referenceFileNoisy16[255] = {0};
#else
	void *q31referenceFileNoisy16;
	int q31referenceFileNoisy16Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31referenceFileNoisy32[255] = {0};
#else
	void *q31referenceFileNoisy32;
	int q31referenceFileNoisy32Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31referenceFileNoisy64[255] = {0};
#else
	void *q31referenceFileNoisy64;
	int q31referenceFileNoisy64Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31referenceFileNoisy128[255] = {0};
#else
	void *q31referenceFileNoisy128;
	int q31referenceFileNoisy128Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31referenceFileNoisy256[255] = {0};
#else
	void *q31referenceFileNoisy256;
	int q31referenceFileNoisy256Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31referenceFileNoisy512[255] = {0};
#else
	void *q31referenceFileNoisy512;
	int q31referenceFileNoisy512Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31referenceFileNoisy1024[255] = {0};
#else
	void *q31referenceFileNoisy1024;
	int q31referenceFileNoisy1024Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31referenceFileNoisy2048[255] = {0};
#else
	void *q31referenceFileNoisy2048;
	int q31referenceFileNoisy2048Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31referenceFileNoisy4096[255] = {0};
#else
	void *q31referenceFileNoisy4096;
	int q31referenceFileNoisy4096Len = 0;
#endif


#if defined(NOT_EMBEDDED)
	char q31referenceFileStep16[255] = {0};
#else
	void *q31referenceFileStep16;
	int q31referenceFileStep16Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31referenceFileStep32[255] = {0};
#else
	void *q31referenceFileStep32;
	int q31referenceFileStep32Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31referenceFileStep64[255] = {0};
#else
	void *q31referenceFileStep64;
	int q31referenceFileStep64Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31referenceFileStep128[255] = {0};
#else
	void *q31referenceFileStep128;
	int q31referenceFileStep128Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31referenceFileStep256[255] = {0};
#else
	void *q31referenceFileStep256;
	int q31referenceFileStep256Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31referenceFileStep512[255] = {0};
#else
	void *q31referenceFileStep512;
	int q31referenceFileStep512Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31referenceFileStep1024[255] = {0};
#else
	void *q31referenceFileStep1024;
	int q31referenceFileStep1024Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31referenceFileStep2048[255] = {0};
#else
	void *q31referenceFileStep2048;
	int q31referenceFileStep2048Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31referenceFileStep4096[255] = {0};
#else
	void *q31referenceFileStep4096;
	int q31referenceFileStep4096Len = 0;
#endif


	// set file name by snprintf
	// relative path, function path, filename
#if defined(NOT_EMBEDDED)
	snprintf(q31inputFileNoisy16, sizeof(q31inputFileNoisy16), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexInputSamples_Noisy_16_1_q31.txt");
#else
	q31inputFileNoisy16 = TransformQ31_ComplexInputSamples_Noisy_16_1_q31;
	q31inputFileNoisy16Len = sizeof(TransformQ31_ComplexInputSamples_Noisy_16_1_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31inputFileNoisy32, sizeof(q31inputFileNoisy32), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexInputSamples_Noisy_32_2_q31.txt");
#else
	q31inputFileNoisy32 = TransformQ31_ComplexInputSamples_Noisy_32_2_q31;
	q31inputFileNoisy32Len = sizeof(TransformQ31_ComplexInputSamples_Noisy_32_2_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31inputFileNoisy64, sizeof(q31inputFileNoisy64), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexInputSamples_Noisy_64_3_q31.txt");
#else
	q31inputFileNoisy64 = TransformQ31_ComplexInputSamples_Noisy_64_3_q31;
	q31inputFileNoisy64Len = sizeof(TransformQ31_ComplexInputSamples_Noisy_64_3_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31inputFileNoisy128, sizeof(q31inputFileNoisy128), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexInputSamples_Noisy_128_4_q31.txt");
#else
	q31inputFileNoisy128 = TransformQ31_ComplexInputSamples_Noisy_128_4_q31;
	q31inputFileNoisy128Len = sizeof(TransformQ31_ComplexInputSamples_Noisy_128_4_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31inputFileNoisy256, sizeof(q31inputFileNoisy256), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexInputSamples_Noisy_256_5_q31.txt");
#else
	q31inputFileNoisy256 = TransformQ31_ComplexInputSamples_Noisy_256_5_q31;
	q31inputFileNoisy256Len = sizeof(TransformQ31_ComplexInputSamples_Noisy_256_5_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31inputFileNoisy512, sizeof(q31inputFileNoisy512), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexInputSamples_Noisy_512_6_q31.txt");
#else
	q31inputFileNoisy512 = TransformQ31_ComplexInputSamples_Noisy_512_6_q31;
	q31inputFileNoisy512Len = sizeof(TransformQ31_ComplexInputSamples_Noisy_512_6_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31inputFileNoisy1024, sizeof(q31inputFileNoisy1024), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexInputSamples_Noisy_1024_7_q31.txt");
#else
	q31inputFileNoisy1024 = TransformQ31_ComplexInputSamples_Noisy_1024_7_q31;
	q31inputFileNoisy1024Len = sizeof(TransformQ31_ComplexInputSamples_Noisy_1024_7_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31inputFileNoisy2048, sizeof(q31inputFileNoisy2048), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexInputSamples_Noisy_2048_8_q31.txt");
#else
	q31inputFileNoisy2048 = TransformQ31_ComplexInputSamples_Noisy_2048_8_q31;
	q31inputFileNoisy2048Len = sizeof(TransformQ31_ComplexInputSamples_Noisy_2048_8_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31inputFileNoisy4096, sizeof(q31inputFileNoisy4096), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexInputSamples_Noisy_4096_9_q31.txt");
#else
	q31inputFileNoisy4096 = TransformQ31_ComplexInputSamples_Noisy_4096_9_q31;
	q31inputFileNoisy4096Len = sizeof(TransformQ31_ComplexInputSamples_Noisy_4096_9_q31);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(q31IFTinputFileNoisy16, sizeof(q31IFTinputFileNoisy16), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexInputIFFTSamples_Noisy_16_1_q31.txt");
#else
	q31IFTinputFileNoisy16 = TransformQ31_ComplexInputIFFTSamples_Noisy_16_1_q31;
	q31IFTinputFileNoisy16Len = sizeof(TransformQ31_ComplexInputIFFTSamples_Noisy_16_1_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31IFTinputFileNoisy32, sizeof(q31IFTinputFileNoisy32), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexInputIFFTSamples_Noisy_32_2_q31.txt");
#else
	q31IFTinputFileNoisy32 = TransformQ31_ComplexInputIFFTSamples_Noisy_32_2_q31;
	q31IFTinputFileNoisy32Len = sizeof(TransformQ31_ComplexInputIFFTSamples_Noisy_32_2_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31IFTinputFileNoisy64, sizeof(q31IFTinputFileNoisy64), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexInputIFFTSamples_Noisy_64_3_q31.txt");
#else
	q31IFTinputFileNoisy64 = TransformQ31_ComplexInputIFFTSamples_Noisy_64_3_q31;
	q31IFTinputFileNoisy64Len = sizeof(TransformQ31_ComplexInputIFFTSamples_Noisy_64_3_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31IFTinputFileNoisy128, sizeof(q31IFTinputFileNoisy128), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexInputIFFTSamples_Noisy_128_4_q31.txt");
#else
	q31IFTinputFileNoisy128 = TransformQ31_ComplexInputIFFTSamples_Noisy_128_4_q31;
	q31IFTinputFileNoisy128Len = sizeof(TransformQ31_ComplexInputIFFTSamples_Noisy_128_4_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31IFTinputFileNoisy256, sizeof(q31IFTinputFileNoisy256), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexInputIFFTSamples_Noisy_256_5_q31.txt");
#else
	q31IFTinputFileNoisy256 = TransformQ31_ComplexInputIFFTSamples_Noisy_256_5_q31;
	q31IFTinputFileNoisy256Len = sizeof(TransformQ31_ComplexInputIFFTSamples_Noisy_256_5_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31IFTinputFileNoisy512, sizeof(q31IFTinputFileNoisy512), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexInputIFFTSamples_Noisy_512_6_q31.txt");
#else
	q31IFTinputFileNoisy512 = TransformQ31_ComplexInputIFFTSamples_Noisy_512_6_q31;
	q31IFTinputFileNoisy512Len = sizeof(TransformQ31_ComplexInputIFFTSamples_Noisy_512_6_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31IFTinputFileNoisy1024, sizeof(q31IFTinputFileNoisy1024), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexInputIFFTSamples_Noisy_1024_7_q31.txt");
#else
	q31IFTinputFileNoisy1024 = TransformQ31_ComplexInputIFFTSamples_Noisy_1024_7_q31;
	q31IFTinputFileNoisy1024Len = sizeof(TransformQ31_ComplexInputIFFTSamples_Noisy_1024_7_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31IFTinputFileNoisy2048, sizeof(q31IFTinputFileNoisy2048), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexInputIFFTSamples_Noisy_2048_8_q31.txt");
#else
	q31IFTinputFileNoisy2048 = TransformQ31_ComplexInputIFFTSamples_Noisy_2048_8_q31;
	q31IFTinputFileNoisy2048Len = sizeof(TransformQ31_ComplexInputIFFTSamples_Noisy_2048_8_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31IFTinputFileNoisy4096, sizeof(q31IFTinputFileNoisy4096), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexInputIFFTSamples_Noisy_4096_9_q31.txt");
#else
	q31IFTinputFileNoisy4096 = TransformQ31_ComplexInputIFFTSamples_Noisy_4096_9_q31;
	q31IFTinputFileNoisy4096Len = sizeof(TransformQ31_ComplexInputIFFTSamples_Noisy_4096_9_q31);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(q31referenceFileNoisy16, sizeof(q31referenceFileNoisy16), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexFFTSamples_Noisy_16_1_q31.txt");
#else
	q31referenceFileNoisy16 = TransformQ31_ComplexFFTSamples_Noisy_16_1_q31;
	q31referenceFileNoisy16Len = sizeof(TransformQ31_ComplexFFTSamples_Noisy_16_1_q31)/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31referenceFileNoisy32, sizeof(q31referenceFileNoisy32), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexFFTSamples_Noisy_32_2_q31.txt");
#else
	q31referenceFileNoisy32 = TransformQ31_ComplexFFTSamples_Noisy_32_2_q31;
	q31referenceFileNoisy32Len = sizeof(TransformQ31_ComplexFFTSamples_Noisy_32_2_q31)/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31referenceFileNoisy64, sizeof(q31referenceFileNoisy64), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexFFTSamples_Noisy_64_3_q31.txt");
#else
	q31referenceFileNoisy64 = TransformQ31_ComplexFFTSamples_Noisy_64_3_q31;
	q31referenceFileNoisy64Len = sizeof(TransformQ31_ComplexFFTSamples_Noisy_64_3_q31)/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31referenceFileNoisy128, sizeof(q31referenceFileNoisy128), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexFFTSamples_Noisy_128_4_q31.txt");
#else
	q31referenceFileNoisy128 = TransformQ31_ComplexFFTSamples_Noisy_128_4_q31;
	q31referenceFileNoisy128Len = sizeof(TransformQ31_ComplexFFTSamples_Noisy_128_4_q31)/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31referenceFileNoisy256, sizeof(q31referenceFileNoisy256), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexFFTSamples_Noisy_256_5_q31.txt");
#else
	q31referenceFileNoisy256 = TransformQ31_ComplexFFTSamples_Noisy_256_5_q31;
	q31referenceFileNoisy256Len = sizeof(TransformQ31_ComplexFFTSamples_Noisy_256_5_q31)/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31referenceFileNoisy512, sizeof(q31referenceFileNoisy512), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexFFTSamples_Noisy_512_6_q31.txt");
#else
	q31referenceFileNoisy512 = TransformQ31_ComplexFFTSamples_Noisy_512_6_q31;
	q31referenceFileNoisy512Len = sizeof(TransformQ31_ComplexFFTSamples_Noisy_512_6_q31)/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31referenceFileNoisy1024, sizeof(q31referenceFileNoisy1024), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexFFTSamples_Noisy_1024_7_q31.txt");
#else
	q31referenceFileNoisy1024 = TransformQ31_ComplexFFTSamples_Noisy_1024_7_q31;
	q31referenceFileNoisy1024Len = sizeof(TransformQ31_ComplexFFTSamples_Noisy_1024_7_q31)/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31referenceFileNoisy2048, sizeof(q31referenceFileNoisy2048), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexFFTSamples_Noisy_2048_8_q31.txt");
#else
	q31referenceFileNoisy2048 = TransformQ31_ComplexFFTSamples_Noisy_2048_8_q31;
	q31referenceFileNoisy2048Len = sizeof(TransformQ31_ComplexFFTSamples_Noisy_2048_8_q31)/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31referenceFileNoisy4096, sizeof(q31referenceFileNoisy4096), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexFFTSamples_Noisy_4096_9_q31.txt");
#else
	q31referenceFileNoisy4096 = TransformQ31_ComplexFFTSamples_Noisy_4096_9_q31;
	q31referenceFileNoisy4096Len = sizeof(TransformQ31_ComplexFFTSamples_Noisy_4096_9_q31)/sizeof(q31);
#endif



#if defined(NOT_EMBEDDED)
	snprintf(q31inputFileStep16, sizeof(q31inputFileStep16), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexInputSamples_Step_16_10_q31.txt");
#else
	q31inputFileStep16 = TransformQ31_ComplexInputSamples_Step_16_10_q31;
	q31inputFileStep16Len = sizeof(TransformQ31_ComplexInputSamples_Step_16_10_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31inputFileStep32, sizeof(q31inputFileStep32), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexInputSamples_Step_32_11_q31.txt");
#else
	q31inputFileStep32 = TransformQ31_ComplexInputSamples_Step_32_11_q31;
	q31inputFileStep32Len = sizeof(TransformQ31_ComplexInputSamples_Step_32_11_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31inputFileStep64, sizeof(q31inputFileStep64), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexInputSamples_Step_64_12_q31.txt");
#else
	q31inputFileStep64 = TransformQ31_ComplexInputSamples_Step_64_12_q31;
	q31inputFileStep64Len = sizeof(TransformQ31_ComplexInputSamples_Step_64_12_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31inputFileStep128, sizeof(q31inputFileStep128), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexInputSamples_Step_128_13_q31.txt");
#else
	q31inputFileStep128 = TransformQ31_ComplexInputSamples_Step_128_13_q31;
	q31inputFileStep128Len = sizeof(TransformQ31_ComplexInputSamples_Step_128_13_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31inputFileStep256, sizeof(q31inputFileStep256), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexInputSamples_Step_256_14_q31.txt");
#else
	q31inputFileStep256 = TransformQ31_ComplexInputSamples_Step_256_14_q31;
	q31inputFileStep256Len = sizeof(TransformQ31_ComplexInputSamples_Step_256_14_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31inputFileStep512, sizeof(q31inputFileStep512), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexInputSamples_Step_512_15_q31.txt");
#else
	q31inputFileStep512 = TransformQ31_ComplexInputSamples_Step_512_15_q31;
	q31inputFileStep512Len = sizeof(TransformQ31_ComplexInputSamples_Step_512_15_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31inputFileStep1024, sizeof(q31inputFileStep1024), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexInputSamples_Step_1024_16_q31.txt");
#else
	q31inputFileStep1024 = TransformQ31_ComplexInputSamples_Step_1024_16_q31;
	q31inputFileStep1024Len = sizeof(TransformQ31_ComplexInputSamples_Step_1024_16_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31inputFileStep2048, sizeof(q31inputFileStep2048), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexInputSamples_Step_2048_17_q31.txt");
#else
	q31inputFileStep2048 = TransformQ31_ComplexInputSamples_Step_2048_17_q31;
	q31inputFileStep2048Len = sizeof(TransformQ31_ComplexInputSamples_Step_2048_17_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31inputFileStep4096, sizeof(q31inputFileStep4096), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexInputSamples_Step_4096_18_q31.txt");
#else
	q31inputFileStep4096 = TransformQ31_ComplexInputSamples_Step_4096_18_q31;
	q31inputFileStep4096Len = sizeof(TransformQ31_ComplexInputSamples_Step_4096_18_q31);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(q31IFTinputFileStep16, sizeof(q31IFTinputFileStep16), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexInputIFFTSamples_Step_16_10_q31.txt");
#else
	q31IFTinputFileStep16 = TransformQ31_ComplexInputIFFTSamples_Step_16_10_q31;
	q31IFTinputFileStep16Len = sizeof(TransformQ31_ComplexInputIFFTSamples_Step_16_10_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31IFTinputFileStep32, sizeof(q31IFTinputFileStep32), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexInputIFFTSamples_Step_32_11_q31.txt");
#else
	q31IFTinputFileStep32 = TransformQ31_ComplexInputIFFTSamples_Step_32_11_q31;
	q31IFTinputFileStep32Len = sizeof(TransformQ31_ComplexInputIFFTSamples_Step_32_11_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31IFTinputFileStep64, sizeof(q31IFTinputFileStep64), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexInputIFFTSamples_Step_64_12_q31.txt");
#else
	q31IFTinputFileStep64 = TransformQ31_ComplexInputIFFTSamples_Step_64_12_q31;
	q31IFTinputFileStep64Len = sizeof(TransformQ31_ComplexInputIFFTSamples_Step_64_12_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31IFTinputFileStep128, sizeof(q31IFTinputFileStep128), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexInputIFFTSamples_Step_128_13_q31.txt");
#else
	q31IFTinputFileStep128 = TransformQ31_ComplexInputIFFTSamples_Step_128_13_q31;
	q31IFTinputFileStep128Len = sizeof(TransformQ31_ComplexInputIFFTSamples_Step_128_13_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31IFTinputFileStep256, sizeof(q31IFTinputFileStep256), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexInputIFFTSamples_Step_256_14_q31.txt");
#else
	q31IFTinputFileStep256 = TransformQ31_ComplexInputIFFTSamples_Step_256_14_q31;
	q31IFTinputFileStep256Len = sizeof(TransformQ31_ComplexInputIFFTSamples_Step_256_14_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31IFTinputFileStep512, sizeof(q31IFTinputFileStep512), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexInputIFFTSamples_Step_512_15_q31.txt");
#else
	q31IFTinputFileStep512 = TransformQ31_ComplexInputIFFTSamples_Step_512_15_q31;
	q31IFTinputFileStep512Len = sizeof(TransformQ31_ComplexInputIFFTSamples_Step_512_15_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31IFTinputFileStep1024, sizeof(q31IFTinputFileStep1024), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexInputIFFTSamples_Step_1024_16_q31.txt");
#else
	q31IFTinputFileStep1024 = TransformQ31_ComplexInputIFFTSamples_Step_1024_16_q31;
	q31IFTinputFileStep1024Len = sizeof(TransformQ31_ComplexInputIFFTSamples_Step_1024_16_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31IFTinputFileStep2048, sizeof(q31IFTinputFileStep2048), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexInputIFFTSamples_Step_2048_17_q31.txt");
#else
	q31IFTinputFileStep2048 = TransformQ31_ComplexInputIFFTSamples_Step_2048_17_q31;
	q31IFTinputFileStep2048Len = sizeof(TransformQ31_ComplexInputIFFTSamples_Step_2048_17_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31IFTinputFileStep4096, sizeof(q31IFTinputFileStep4096), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexInputIFFTSamples_Step_4096_18_q31.txt");
#else
	q31IFTinputFileStep4096 = TransformQ31_ComplexInputIFFTSamples_Step_4096_18_q31;
	q31IFTinputFileStep4096Len = sizeof(TransformQ31_ComplexInputIFFTSamples_Step_4096_18_q31);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(q31referenceFileStep16, sizeof(q31referenceFileStep16), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexFFTSamples_Step_16_10_q31.txt");
#else
	q31referenceFileStep16 = TransformQ31_ComplexFFTSamples_Step_16_10_q31;
	q31referenceFileStep16Len = sizeof(TransformQ31_ComplexFFTSamples_Step_16_10_q31)/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31referenceFileStep32, sizeof(q31referenceFileStep32), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexFFTSamples_Step_32_11_q31.txt");
#else
	q31referenceFileStep32 = TransformQ31_ComplexFFTSamples_Step_32_11_q31;
	q31referenceFileStep32Len = sizeof(TransformQ31_ComplexFFTSamples_Step_32_11_q31)/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31referenceFileStep64, sizeof(q31referenceFileStep64), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexFFTSamples_Step_64_12_q31.txt");
#else
	q31referenceFileStep64 = TransformQ31_ComplexFFTSamples_Step_64_12_q31;
	q31referenceFileStep64Len = sizeof(TransformQ31_ComplexFFTSamples_Step_64_12_q31)/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31referenceFileStep128, sizeof(q31referenceFileStep128), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexFFTSamples_Step_128_13_q31.txt");
#else
	q31referenceFileStep128 = TransformQ31_ComplexFFTSamples_Step_128_13_q31;
	q31referenceFileStep128Len = sizeof(TransformQ31_ComplexFFTSamples_Step_128_13_q31)/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31referenceFileStep256, sizeof(q31referenceFileStep256), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexFFTSamples_Step_256_14_q31.txt");
#else
	q31referenceFileStep256 = TransformQ31_ComplexFFTSamples_Step_256_14_q31;
	q31referenceFileStep256Len = sizeof(TransformQ31_ComplexFFTSamples_Step_256_14_q31)/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31referenceFileStep512, sizeof(q31referenceFileStep512), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexFFTSamples_Step_512_15_q31.txt");
#else
	q31referenceFileStep512 = TransformQ31_ComplexFFTSamples_Step_512_15_q31;
	q31referenceFileStep512Len = sizeof(TransformQ31_ComplexFFTSamples_Step_512_15_q31)/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31referenceFileStep1024, sizeof(q31referenceFileStep1024), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexFFTSamples_Step_1024_16_q31.txt");
#else
	q31referenceFileStep1024 = TransformQ31_ComplexFFTSamples_Step_1024_16_q31;
	q31referenceFileStep1024Len = sizeof(TransformQ31_ComplexFFTSamples_Step_1024_16_q31)/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31referenceFileStep2048, sizeof(q31referenceFileStep2048), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexFFTSamples_Step_2048_17_q31.txt");
#else
	q31referenceFileStep2048 = TransformQ31_ComplexFFTSamples_Step_2048_17_q31;
	q31referenceFileStep2048Len = sizeof(TransformQ31_ComplexFFTSamples_Step_2048_17_q31)/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31referenceFileStep4096, sizeof(q31referenceFileStep4096), "%s%s%s", Patterns_PATH, TransformQ31, "ComplexFFTSamples_Step_4096_18_q31.txt");
#else
	q31referenceFileStep4096 = TransformQ31_ComplexFFTSamples_Step_4096_18_q31;
	q31referenceFileStep4096Len = sizeof(TransformQ31_ComplexFFTSamples_Step_4096_18_q31)/sizeof(q31);
#endif



	// load input data
#if defined(NOT_EMBEDDED)
	load_data_q31(q31inputFileNoisy16, &paramCountInputNoisy16, q31inputNoisy16);
#else
	paramCountInputNoisy16 = q31inputFileNoisy16Len;
	load_data_q31(q31inputFileNoisy16, paramCountInputNoisy16, q31inputNoisy16);
	paramCountInputNoisy16 = paramCountInputNoisy16/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(q31inputFileNoisy32, &paramCountInputNoisy32, q31inputNoisy32);
#else
	paramCountInputNoisy32 = q31inputFileNoisy32Len;
	load_data_q31(q31inputFileNoisy32, paramCountInputNoisy32, q31inputNoisy32);
	paramCountInputNoisy32 = paramCountInputNoisy32/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(q31inputFileNoisy64, &paramCountInputNoisy64, q31inputNoisy64);
#else
	paramCountInputNoisy64 = q31inputFileNoisy64Len;
	load_data_q31(q31inputFileNoisy64, paramCountInputNoisy64, q31inputNoisy64);
	paramCountInputNoisy64 = paramCountInputNoisy64/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(q31inputFileNoisy128, &paramCountInputNoisy128, q31inputNoisy128);
#else
	paramCountInputNoisy128 = q31inputFileNoisy128Len;
	load_data_q31(q31inputFileNoisy128, paramCountInputNoisy128, q31inputNoisy128);
	paramCountInputNoisy128 = paramCountInputNoisy128/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(q31inputFileNoisy256, &paramCountInputNoisy256, q31inputNoisy256);
#else
	paramCountInputNoisy256 = q31inputFileNoisy256Len;
	load_data_q31(q31inputFileNoisy256, paramCountInputNoisy256, q31inputNoisy256);
	paramCountInputNoisy256 = paramCountInputNoisy256/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(q31inputFileNoisy512, &paramCountInputNoisy512, q31inputNoisy512);
#else
	paramCountInputNoisy512 = q31inputFileNoisy512Len;
	load_data_q31(q31inputFileNoisy512, paramCountInputNoisy512, q31inputNoisy512);
	paramCountInputNoisy512 = paramCountInputNoisy512/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(q31inputFileNoisy1024, &paramCountInputNoisy1024, q31inputNoisy1024);
#else
	paramCountInputNoisy1024 = q31inputFileNoisy1024Len;
	load_data_q31(q31inputFileNoisy1024, paramCountInputNoisy1024, q31inputNoisy1024);
	paramCountInputNoisy1024 = paramCountInputNoisy1024/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(q31inputFileNoisy2048, &paramCountInputNoisy2048, q31inputNoisy2048);
#else
	paramCountInputNoisy2048 = q31inputFileNoisy2048Len;
	load_data_q31(q31inputFileNoisy2048, paramCountInputNoisy2048, q31inputNoisy2048);
	paramCountInputNoisy2048 = paramCountInputNoisy2048/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(q31inputFileNoisy4096, &paramCountInputNoisy4096, q31inputNoisy4096);
#else
	paramCountInputNoisy4096 = q31inputFileNoisy4096Len;
	load_data_q31(q31inputFileNoisy4096, paramCountInputNoisy4096, q31inputNoisy4096);
	paramCountInputNoisy4096 = paramCountInputNoisy4096/sizeof(q31);
#endif


#if defined(NOT_EMBEDDED)
	load_data_q31(q31IFTinputFileNoisy16, &IFTparamCountInputNoisy16, q31IFTinputNoisy16);
#else
	IFTparamCountInputNoisy16 = q31IFTinputFileNoisy16Len;
	load_data_q31(q31IFTinputFileNoisy16, IFTparamCountInputNoisy16, q31IFTinputNoisy16);
	IFTparamCountInputNoisy16 = IFTparamCountInputNoisy16/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(q31IFTinputFileNoisy32, &IFTparamCountInputNoisy32, q31IFTinputNoisy32);
#else
	IFTparamCountInputNoisy32 = q31IFTinputFileNoisy32Len;
	load_data_q31(q31IFTinputFileNoisy32, IFTparamCountInputNoisy32, q31IFTinputNoisy32);
	IFTparamCountInputNoisy32 = IFTparamCountInputNoisy32/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(q31IFTinputFileNoisy64, &IFTparamCountInputNoisy64, q31IFTinputNoisy64);
#else
	IFTparamCountInputNoisy64 = q31IFTinputFileNoisy64Len;
	load_data_q31(q31IFTinputFileNoisy64, IFTparamCountInputNoisy64, q31IFTinputNoisy64);
	IFTparamCountInputNoisy64 = IFTparamCountInputNoisy64/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(q31IFTinputFileNoisy128, &IFTparamCountInputNoisy128, q31IFTinputNoisy128);
#else
	IFTparamCountInputNoisy128 = q31IFTinputFileNoisy128Len;
	load_data_q31(q31IFTinputFileNoisy128, IFTparamCountInputNoisy128, q31IFTinputNoisy128);
	IFTparamCountInputNoisy128 = IFTparamCountInputNoisy128/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(q31IFTinputFileNoisy256, &IFTparamCountInputNoisy256, q31IFTinputNoisy256);
#else
	IFTparamCountInputNoisy256 = q31IFTinputFileNoisy256Len;
	load_data_q31(q31IFTinputFileNoisy256, IFTparamCountInputNoisy256, q31IFTinputNoisy256);
	IFTparamCountInputNoisy256 = IFTparamCountInputNoisy256/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(q31IFTinputFileNoisy512, &IFTparamCountInputNoisy512, q31IFTinputNoisy512);
#else
	IFTparamCountInputNoisy512 = q31IFTinputFileNoisy512Len;
	load_data_q31(q31IFTinputFileNoisy512, IFTparamCountInputNoisy512, q31IFTinputNoisy512);
	IFTparamCountInputNoisy512 = IFTparamCountInputNoisy512/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(q31IFTinputFileNoisy1024, &IFTparamCountInputNoisy1024, q31IFTinputNoisy1024);
#else
	IFTparamCountInputNoisy1024 = q31IFTinputFileNoisy1024Len;
	load_data_q31(q31IFTinputFileNoisy1024, IFTparamCountInputNoisy1024, q31IFTinputNoisy1024);
	IFTparamCountInputNoisy1024 = IFTparamCountInputNoisy1024/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(q31IFTinputFileNoisy2048, &IFTparamCountInputNoisy2048, q31IFTinputNoisy2048);
#else
	IFTparamCountInputNoisy2048 = q31IFTinputFileNoisy2048Len;
	load_data_q31(q31IFTinputFileNoisy2048, IFTparamCountInputNoisy2048, q31IFTinputNoisy2048);
	IFTparamCountInputNoisy2048 = IFTparamCountInputNoisy2048/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(q31IFTinputFileNoisy4096, &IFTparamCountInputNoisy4096, q31IFTinputNoisy4096);
#else
	IFTparamCountInputNoisy4096 = q31IFTinputFileNoisy4096Len;
	load_data_q31(q31IFTinputFileNoisy4096, IFTparamCountInputNoisy4096, q31IFTinputNoisy4096);
	IFTparamCountInputNoisy4096 = IFTparamCountInputNoisy4096/sizeof(q31);
#endif


#if defined(NOT_EMBEDDED)
	load_data_q31(q31inputFileStep16, &paramCountInputStep16, q31inputStep16);
#else
	paramCountInputStep16 = q31inputFileStep16Len;
	load_data_q31(q31inputFileStep16, paramCountInputStep16, q31inputStep16);
	paramCountInputStep16 = paramCountInputStep16/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(q31inputFileStep32, &paramCountInputStep32, q31inputStep32);
#else
	paramCountInputStep32 = q31inputFileStep32Len;
	load_data_q31(q31inputFileStep32, paramCountInputStep32, q31inputStep32);
	paramCountInputStep32 = paramCountInputStep32/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(q31inputFileStep64, &paramCountInputStep64, q31inputStep64);
#else
	paramCountInputStep64 = q31inputFileStep64Len;
	load_data_q31(q31inputFileStep64, paramCountInputStep64, q31inputStep64);
	paramCountInputStep64 = paramCountInputStep64/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(q31inputFileStep128, &paramCountInputStep128, q31inputStep128);
#else
	paramCountInputStep128 = q31inputFileStep128Len;
	load_data_q31(q31inputFileStep128, paramCountInputStep128, q31inputStep128);
	paramCountInputStep128 = paramCountInputStep128/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(q31inputFileStep256, &paramCountInputStep256, q31inputStep256);
#else
	paramCountInputStep256 = q31inputFileStep256Len;
	load_data_q31(q31inputFileStep256, paramCountInputStep256, q31inputStep256);
	paramCountInputStep256 = paramCountInputStep256/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(q31inputFileStep512, &paramCountInputStep512, q31inputStep512);
#else
	paramCountInputStep512 = q31inputFileStep512Len;
	load_data_q31(q31inputFileStep512, paramCountInputStep512, q31inputStep512);
	paramCountInputStep512 = paramCountInputStep512/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(q31inputFileStep1024, &paramCountInputStep1024, q31inputStep1024);
#else
	paramCountInputStep1024 = q31inputFileStep1024Len;
	load_data_q31(q31inputFileStep1024, paramCountInputStep1024, q31inputStep1024);
	paramCountInputStep1024 = paramCountInputStep1024/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(q31inputFileStep2048, &paramCountInputStep2048, q31inputStep2048);
#else
	paramCountInputStep2048 = q31inputFileStep2048Len;
	load_data_q31(q31inputFileStep2048, paramCountInputStep2048, q31inputStep2048);
	paramCountInputStep2048 = paramCountInputStep2048/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(q31inputFileStep4096, &paramCountInputStep4096, q31inputStep4096);
#else
	paramCountInputStep4096 = q31inputFileStep4096Len;
	load_data_q31(q31inputFileStep4096, paramCountInputStep4096, q31inputStep4096);
	paramCountInputStep4096 = paramCountInputStep4096/sizeof(q31);
#endif


#if defined(NOT_EMBEDDED)
	load_data_q31(q31IFTinputFileStep16, &IFTparamCountInputStep16, q31IFTinputStep16);
#else
	IFTparamCountInputStep16 = q31IFTinputFileStep16Len;
	load_data_q31(q31IFTinputFileStep16, IFTparamCountInputStep16, q31IFTinputStep16);
	IFTparamCountInputStep16 = IFTparamCountInputStep16/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(q31IFTinputFileStep32, &IFTparamCountInputStep32, q31IFTinputStep32);
#else
	IFTparamCountInputStep32 = q31IFTinputFileStep32Len;
	load_data_q31(q31IFTinputFileStep32, IFTparamCountInputStep32, q31IFTinputStep32);
	IFTparamCountInputStep32 = IFTparamCountInputStep32/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(q31IFTinputFileStep64, &IFTparamCountInputStep64, q31IFTinputStep64);
#else
	IFTparamCountInputStep64 = q31IFTinputFileStep64Len;
	load_data_q31(q31IFTinputFileStep64, IFTparamCountInputStep64, q31IFTinputStep64);
	IFTparamCountInputStep64 = IFTparamCountInputStep64/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(q31IFTinputFileStep128, &IFTparamCountInputStep128, q31IFTinputStep128);
#else
	IFTparamCountInputStep128 = q31IFTinputFileStep128Len;
	load_data_q31(q31IFTinputFileStep128, IFTparamCountInputStep128, q31IFTinputStep128);
	IFTparamCountInputStep128 = IFTparamCountInputStep128/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(q31IFTinputFileStep256, &IFTparamCountInputStep256, q31IFTinputStep256);
#else
	IFTparamCountInputStep256 = q31IFTinputFileStep256Len;
	load_data_q31(q31IFTinputFileStep256, IFTparamCountInputStep256, q31IFTinputStep256);
	IFTparamCountInputStep256 = IFTparamCountInputStep256/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(q31IFTinputFileStep512, &IFTparamCountInputStep512, q31IFTinputStep512);
#else
	IFTparamCountInputStep512 = q31IFTinputFileStep512Len;
	load_data_q31(q31IFTinputFileStep512, IFTparamCountInputStep512, q31IFTinputStep512);
	IFTparamCountInputStep512 = IFTparamCountInputStep512/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(q31IFTinputFileStep1024, &IFTparamCountInputStep1024, q31IFTinputStep1024);
#else
	IFTparamCountInputStep1024 = q31IFTinputFileStep1024Len;
	load_data_q31(q31IFTinputFileStep1024, IFTparamCountInputStep1024, q31IFTinputStep1024);
	IFTparamCountInputStep1024 = IFTparamCountInputStep1024/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(q31IFTinputFileStep2048, &IFTparamCountInputStep2048, q31IFTinputStep2048);
#else
	IFTparamCountInputStep2048 = q31IFTinputFileStep2048Len;
	load_data_q31(q31IFTinputFileStep2048, IFTparamCountInputStep2048, q31IFTinputStep2048);
	IFTparamCountInputStep2048 = IFTparamCountInputStep2048/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(q31IFTinputFileStep4096, &IFTparamCountInputStep4096, q31IFTinputStep4096);
#else
	IFTparamCountInputStep4096 = q31IFTinputFileStep4096Len;
	load_data_q31(q31IFTinputFileStep4096, IFTparamCountInputStep4096, q31IFTinputStep4096);
	IFTparamCountInputStep4096 = IFTparamCountInputStep4096/sizeof(q31);
#endif


    q31 q31output[MAX_SIZE] = {0};
    int ifft;
    int scaling;
    q31 *refp;
    mips_status status;
    mips_cfft_instance_q31 instCfftQ31;
// =====================
	printf("== mips_cfft_q31 Noisy_16 test ==  \n");

        memcpy(q31output,q31inputNoisy16,sizeof(q31)*paramCountInputNoisy16);

        status=mips_cfft_init_q31(&instCfftQ31,16);
        ifft = 0;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
   
        mips_cfft_q31(&(instCfftQ31), q31output, ifft, 1);

	printf("mips_cfft_q31 Noisy_16 finish \n");

	printf("mips_cfft_q31 Noisy_16 checking \n\n");
#if defined(NOT_EMBEDDED)
	near_check_q31(q31referenceFileNoisy16, q31output, 0, (q31)32);
#else
	near_check_special_q31(q31referenceFileNoisy16, q31output, q31referenceFileNoisy16Len, (q31)32);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q31(q31referenceFileNoisy16, q31output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_q31(q31referenceFileNoisy16, q31output, q31referenceFileNoisy16Len, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_q31 Noisy_16 check done  == \n\n");

// =====================
	printf("== mips_cfft_q31 IFTNoisy_16 test ==  \n");

        memcpy(q31output,q31IFTinputNoisy16,sizeof(q31)*IFTparamCountInputNoisy16);

        status=mips_cfft_init_q31(&instCfftQ31,16);
        ifft = 1;
        scaling = 4;
        refp = q31inputNoisy16;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
        mips_cfft_q31(&(instCfftQ31), q31output, ifft, 1);
        for(unsigned long i=0; i < paramCountInputNoisy16;i++)
        {
          refp[i] >>= scaling;
        }
	printf("mips_cfft_q31 IFTNoisy_16 finish \n");

	printf("mips_cfft_q31 IFTNoisy_16 checking \n\n");

    snr_check_special_q31(refp, q31output, paramCountInputNoisy16, (f32)SNR_THRESHOLD);

	printf("\n== mips_cfft_q31 IFTNoisy_16 check done  == \n\n");

// =====================
	printf("== mips_cfft_q31 Noisy_32 test ==  \n");

        memcpy(q31output,q31inputNoisy32,sizeof(q31)*paramCountInputNoisy32);

        status=mips_cfft_init_q31(&instCfftQ31,32);
        ifft = 0;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);  
        mips_cfft_q31(&(instCfftQ31), q31output, ifft, 1);

	printf("mips_cfft_q31 Noisy_32 finish \n");

	printf("mips_cfft_q31 Noisy_32 checking \n\n");
#if defined(NOT_EMBEDDED)
	near_check_q31(q31referenceFileNoisy32, q31output, 0, (q31)32);
#else
	near_check_special_q31(q31referenceFileNoisy32, q31output, q31referenceFileNoisy32Len, (q31)32);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q31(q31referenceFileNoisy32, q31output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_q31(q31referenceFileNoisy32, q31output, q31referenceFileNoisy32Len, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_q31 Noisy_32 check done  == \n\n");

// =====================
	printf("== mips_cfft_q31 IFTNoisy_32 test ==  \n");

        memcpy(q31output,q31IFTinputNoisy32,sizeof(q31)*IFTparamCountInputNoisy32);

        status=mips_cfft_init_q31(&instCfftQ31,32);
        ifft = 1;
        scaling = 5;
        refp = q31inputNoisy32;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);   
        mips_cfft_q31(&(instCfftQ31), q31output, ifft, 1);
        for(unsigned long i=0; i < paramCountInputNoisy32;i++)
        {
          refp[i] >>= scaling;
        }
	printf("mips_cfft_q31 IFTNoisy_32 finish \n");

	printf("mips_cfft_q31 IFTNoisy_32 checking \n\n");

    snr_check_special_q31(refp, q31output, paramCountInputNoisy32, (f32)SNR_THRESHOLD);

	printf("\n== mips_cfft_q31 IFTNoisy_32 check done  == \n\n");

// =====================
	printf("== mips_cfft_q31 Noisy_64 test ==  \n");

        memcpy(q31output,q31inputNoisy64,sizeof(q31)*paramCountInputNoisy64);

        status=mips_cfft_init_q31(&instCfftQ31,64);
        ifft = 0;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);   
        mips_cfft_q31(&(instCfftQ31), q31output, ifft, 1);

	printf("mips_cfft_q31 Noisy_64 finish \n");

	printf("mips_cfft_q31 Noisy_64 checking \n\n");
#if defined(NOT_EMBEDDED)
	near_check_q31(q31referenceFileNoisy64, q31output, 0, (q31)32);
#else
	near_check_special_q31(q31referenceFileNoisy64, q31output, q31referenceFileNoisy64Len, (q31)32);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q31(q31referenceFileNoisy64, q31output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_q31(q31referenceFileNoisy64, q31output, q31referenceFileNoisy64Len, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_q31 Noisy_64 check done  == \n\n");

// =====================
	printf("== mips_cfft_q31 IFTNoisy_64 test ==  \n");

        memcpy(q31output,q31IFTinputNoisy64,sizeof(q31)*IFTparamCountInputNoisy64);

        status=mips_cfft_init_q31(&instCfftQ31,64);
        ifft = 1;
        scaling = 6;
        refp = q31inputNoisy64;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);   
        mips_cfft_q31(&(instCfftQ31), q31output, ifft, 1);
        for(unsigned long i=0; i < paramCountInputNoisy64;i++)
        {
          refp[i] >>= scaling;
        }
	printf("mips_cfft_q31 IFTNoisy_64 finish \n");

	printf("mips_cfft_q31 IFTNoisy_64 checking \n\n");

    snr_check_special_q31(refp, q31output, paramCountInputNoisy64, (f32)SNR_THRESHOLD);

	printf("\n== mips_cfft_q31 IFTNoisy_64 check done  == \n\n");

// =====================
	printf("== mips_cfft_q31 Noisy_128 test ==  \n");

        memcpy(q31output,q31inputNoisy128,sizeof(q31)*paramCountInputNoisy128);

        status=mips_cfft_init_q31(&instCfftQ31,128);
        ifft = 0;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);   
        mips_cfft_q31(&(instCfftQ31), q31output, ifft, 1);

	printf("mips_cfft_q31 Noisy_128 finish \n");

	printf("mips_cfft_q31 Noisy_128 checking \n\n");
#if defined(NOT_EMBEDDED)
	near_check_q31(q31referenceFileNoisy128, q31output, 0, (q31)32);
#else
	near_check_special_q31(q31referenceFileNoisy128, q31output, q31referenceFileNoisy128Len, (q31)32);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q31(q31referenceFileNoisy128, q31output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_q31(q31referenceFileNoisy128, q31output, q31referenceFileNoisy128Len, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_q31 Noisy_128 check done  == \n\n");

// =====================
	printf("== mips_cfft_q31 IFTNoisy_128 test ==  \n");

        memcpy(q31output,q31IFTinputNoisy128,sizeof(q31)*IFTparamCountInputNoisy128);

        status=mips_cfft_init_q31(&instCfftQ31,128);
        ifft = 1;
        scaling = 7;
        refp = q31inputNoisy128;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);   
        mips_cfft_q31(&(instCfftQ31), q31output, ifft, 1);
        for(unsigned long i=0; i < paramCountInputNoisy128;i++)
        {
          refp[i] >>= scaling;
        }
	printf("mips_cfft_q31 IFTNoisy_128 finish \n");

	printf("mips_cfft_q31 IFTNoisy_128 checking \n\n");

    snr_check_special_q31(refp, q31output, paramCountInputNoisy128, (f32)SNR_THRESHOLD);

	printf("\n== mips_cfft_q31 IFTNoisy_128 check done  == \n\n");

// =====================
	printf("== mips_cfft_q31 Noisy_256 test ==  \n");

        memcpy(q31output,q31inputNoisy256,sizeof(q31)*paramCountInputNoisy256);

        status=mips_cfft_init_q31(&instCfftQ31,256);
        ifft = 0;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);  
        mips_cfft_q31(&(instCfftQ31), q31output, ifft, 1);

	printf("mips_cfft_q31 Noisy_256 finish \n");

	printf("mips_cfft_q31 Noisy_256 checking \n\n");
#if defined(NOT_EMBEDDED)
	near_check_q31(q31referenceFileNoisy256, q31output, 0, (q31)32);
#else
	near_check_special_q31(q31referenceFileNoisy256, q31output, q31referenceFileNoisy256Len, (q31)32);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q31(q31referenceFileNoisy256, q31output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_q31(q31referenceFileNoisy256, q31output, q31referenceFileNoisy256Len, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_q31 Noisy_256 check done  == \n\n");

// =====================
	printf("== mips_cfft_q31 IFTNoisy_256 test ==  \n");

        memcpy(q31output,q31IFTinputNoisy256,sizeof(q31)*IFTparamCountInputNoisy256);

        status=mips_cfft_init_q31(&instCfftQ31,256);
        ifft = 1;
        scaling = 8;
        refp = q31inputNoisy256;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
        mips_cfft_q31(&(instCfftQ31), q31output, ifft, 1);
        for(unsigned long i=0; i < paramCountInputNoisy256;i++)
        {
          refp[i] >>= scaling;
        }
	printf("mips_cfft_q31 IFTNoisy_256 finish \n");

	printf("mips_cfft_q31 IFTNoisy_256 checking \n\n");

    snr_check_special_q31(refp, q31output, paramCountInputNoisy256, (f32)SNR_THRESHOLD);

	printf("\n== mips_cfft_q31 IFTNoisy_256 check done  == \n\n");

// =====================
	printf("== mips_cfft_q31 Noisy_512 test ==  \n");

        memcpy(q31output,q31inputNoisy512,sizeof(q31)*paramCountInputNoisy512);

        status=mips_cfft_init_q31(&instCfftQ31,512);
        ifft = 0;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
        mips_cfft_q31(&(instCfftQ31), q31output, ifft, 1);

	printf("mips_cfft_q31 Noisy_512 finish \n");

	printf("mips_cfft_q31 Noisy_512 checking \n\n");
#if defined(NOT_EMBEDDED)
	near_check_q31(q31referenceFileNoisy512, q31output, 0, (q31)32);
#else
	near_check_special_q31(q31referenceFileNoisy512, q31output, q31referenceFileNoisy512Len, (q31)32);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q31(q31referenceFileNoisy512, q31output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_q31(q31referenceFileNoisy512, q31output, q31referenceFileNoisy512Len, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_q31 Noisy_512 check done  == \n\n");

// =====================
	printf("== mips_cfft_q31 IFTNoisy_512 test ==  \n");

        memcpy(q31output,q31IFTinputNoisy512,sizeof(q31)*IFTparamCountInputNoisy512);

        status=mips_cfft_init_q31(&instCfftQ31,512);
        ifft = 1;
        scaling = 9;
        refp = q31inputNoisy512;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
        mips_cfft_q31(&(instCfftQ31), q31output, ifft, 1);
        for(unsigned long i=0; i < paramCountInputNoisy512;i++)
        {
          refp[i] >>= scaling;
        }
	printf("mips_cfft_q31 IFTNoisy_512 finish \n");

	printf("mips_cfft_q31 IFTNoisy_512 checking \n\n");

    snr_check_special_q31(refp, q31output, paramCountInputNoisy512, (f32)SNR_THRESHOLD);

	printf("\n== mips_cfft_q31 IFTNoisy_512 check done  == \n\n");

// =====================
	printf("== mips_cfft_q31 Noisy_1024 test ==  \n");

        memcpy(q31output,q31inputNoisy1024,sizeof(q31)*paramCountInputNoisy1024);

        status=mips_cfft_init_q31(&instCfftQ31,1024);
        ifft = 0;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
        mips_cfft_q31(&(instCfftQ31), q31output, ifft, 1);

	printf("mips_cfft_q31 Noisy_1024 finish \n");

	printf("mips_cfft_q31 Noisy_1024 checking \n\n");
#if defined(NOT_EMBEDDED)
	near_check_q31(q31referenceFileNoisy1024, q31output, 0, (q31)32);
#else
	near_check_special_q31(q31referenceFileNoisy1024, q31output, q31referenceFileNoisy1024Len, (q31)32);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q31(q31referenceFileNoisy1024, q31output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_q31(q31referenceFileNoisy1024, q31output, q31referenceFileNoisy1024Len, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_q31 Noisy_1024 check done  == \n\n");

// =====================
	printf("== mips_cfft_q31 IFTNoisy_1024 test ==  \n");

        memcpy(q31output,q31IFTinputNoisy1024,sizeof(q31)*IFTparamCountInputNoisy1024);

        status=mips_cfft_init_q31(&instCfftQ31,1024);
        ifft = 1;
        scaling = 10;
        refp = q31inputNoisy1024;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
        mips_cfft_q31(&(instCfftQ31), q31output, ifft, 1);
        for(unsigned long i=0; i < paramCountInputNoisy1024;i++)
        {
          refp[i] >>= scaling;
        }
	printf("mips_cfft_q31 IFTNoisy_1024 finish \n");

	printf("mips_cfft_q31 IFTNoisy_1024 checking \n\n");

    snr_check_special_q31(refp, q31output, paramCountInputNoisy1024, (f32)SNR_THRESHOLD);

	printf("\n== mips_cfft_q31 IFTNoisy_1024 check done  == \n\n");

// =====================
	printf("== mips_cfft_q31 Noisy_2048 test ==  \n");

        memcpy(q31output,q31inputNoisy2048,sizeof(q31)*paramCountInputNoisy2048);

        status=mips_cfft_init_q31(&instCfftQ31,2048);
        ifft = 0;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
        mips_cfft_q31(&(instCfftQ31), q31output, ifft, 1);

	printf("mips_cfft_q31 Noisy_2048 finish \n");

	printf("mips_cfft_q31 Noisy_2048 checking \n\n");
#if defined(NOT_EMBEDDED)
	near_check_q31(q31referenceFileNoisy2048, q31output, 0, (q31)32);
#else
	near_check_special_q31(q31referenceFileNoisy2048, q31output, q31referenceFileNoisy2048Len, (q31)32);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q31(q31referenceFileNoisy2048, q31output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_q31(q31referenceFileNoisy2048, q31output, q31referenceFileNoisy2048Len, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_q31 Noisy_2048 check done  == \n\n");

// =====================
	printf("== mips_cfft_q31 IFTNoisy_2048 test ==  \n");

        memcpy(q31output,q31IFTinputNoisy2048,sizeof(q31)*IFTparamCountInputNoisy2048);

        status=mips_cfft_init_q31(&instCfftQ31,2048);
        ifft = 1;
        scaling = 11;
        refp = q31inputNoisy2048;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
        mips_cfft_q31(&(instCfftQ31), q31output, ifft, 1);
        for(unsigned long i=0; i < paramCountInputNoisy2048;i++)
        {
          refp[i] >>= scaling;
        }
	printf("mips_cfft_q31 IFTNoisy_2048 finish \n");

	printf("mips_cfft_q31 IFTNoisy_2048 checking \n\n");

    snr_check_special_q31(refp, q31output, paramCountInputNoisy2048, (f32)SNR_THRESHOLD);

	printf("\n== mips_cfft_q31 IFTNoisy_2048 check done  == \n\n");

// =====================
	printf("== mips_cfft_q31 Noisy_4096 test ==  \n");

        memcpy(q31output,q31inputNoisy4096,sizeof(q31)*paramCountInputNoisy4096);

        status=mips_cfft_init_q31(&instCfftQ31,4096);
        ifft = 0;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
        mips_cfft_q31(&(instCfftQ31), q31output, ifft, 1);

	printf("mips_cfft_q31 Noisy_4096 finish \n");

	printf("mips_cfft_q31 Noisy_4096 checking \n\n");
#if defined(NOT_EMBEDDED)
	near_check_q31(q31referenceFileNoisy4096, q31output, 0, (q31)32);
#else
	near_check_special_q31(q31referenceFileNoisy4096, q31output, q31referenceFileNoisy4096Len, (q31)32);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q31(q31referenceFileNoisy4096, q31output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_q31(q31referenceFileNoisy4096, q31output, q31referenceFileNoisy4096Len, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_q31 Noisy_4096 check done  == \n\n");

// =====================
	printf("== mips_cfft_q31 IFTNoisy_4096 test ==  \n");

        memcpy(q31output,q31IFTinputNoisy4096,sizeof(q31)*IFTparamCountInputNoisy4096);

        status=mips_cfft_init_q31(&instCfftQ31,4096);
        ifft = 1;
        scaling = 12;
        refp = q31inputNoisy4096;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
        mips_cfft_q31(&(instCfftQ31), q31output, ifft, 1);
        for(unsigned long i=0; i < paramCountInputNoisy4096;i++)
        {
          refp[i] >>= scaling;
        }
	printf("mips_cfft_q31 IFTNoisy_4096 finish \n");

	printf("mips_cfft_q31 IFTNoisy_4096 checking \n\n");

    snr_check_special_q31(refp, q31output, paramCountInputNoisy4096, (f32)SNR_THRESHOLD);

	printf("\n== mips_cfft_q31 IFTNoisy_4096 check done  == \n\n");


// =====================
	printf("== mips_cfft_q31 Step_16 test ==  \n");

        memcpy(q31output,q31inputStep16,sizeof(q31)*paramCountInputStep16);

        status=mips_cfft_init_q31(&instCfftQ31,16);
        ifft = 0;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
        mips_cfft_q31(&(instCfftQ31), q31output, ifft, 1);

	printf("mips_cfft_q31 Step_16 finish \n");

	printf("mips_cfft_q31 Step_16 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_q31(q31referenceFileStep16, q31output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_q31(q31referenceFileStep16, q31output, q31referenceFileStep16Len, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_q31 Step_16 check done  == \n\n");

// =====================
	printf("== mips_cfft_q31 IFTStep_16 test ==  \n");

        memcpy(q31output,q31IFTinputStep16,sizeof(q31)*IFTparamCountInputStep16);

        status=mips_cfft_init_q31(&instCfftQ31,16);
        ifft = 1;
        scaling = 4;
        refp = q31inputStep16;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
        mips_cfft_q31(&(instCfftQ31), q31output, ifft, 1);
        for(unsigned long i=0; i < paramCountInputStep16;i++)
        {
          refp[i] >>= scaling;
        }
	printf("mips_cfft_q31 IFTStep_16 finish \n");

	printf("mips_cfft_q31 IFTStep_16 checking \n\n");

    snr_check_special_q31(refp, q31output, paramCountInputStep16, (f32)SNR_THRESHOLD);

	printf("\n== mips_cfft_q31 IFTStep_16 check done  == \n\n");

// =====================
	printf("== mips_cfft_q31 Step_32 test ==  \n");

        memcpy(q31output,q31inputStep32,sizeof(q31)*paramCountInputStep32);

        status=mips_cfft_init_q31(&instCfftQ31,32);
        ifft = 0;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
        mips_cfft_q31(&(instCfftQ31), q31output, ifft, 1);

	printf("mips_cfft_q31 Step_32 finish \n");

	printf("mips_cfft_q31 Step_32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_q31(q31referenceFileStep32, q31output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_q31(q31referenceFileStep32, q31output, q31referenceFileStep32Len, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_q31 Step_32 check done  == \n\n");

// =====================
	printf("== mips_cfft_q31 IFTStep_32 test ==  \n");

        memcpy(q31output,q31IFTinputStep32,sizeof(q31)*IFTparamCountInputStep32);

        status=mips_cfft_init_q31(&instCfftQ31,32);
        ifft = 1;
        scaling = 5;
        refp = q31inputStep32;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
        mips_cfft_q31(&(instCfftQ31), q31output, ifft, 1);
        for(unsigned long i=0; i < paramCountInputStep32;i++)
        {
          refp[i] >>= scaling;
        }
	printf("mips_cfft_q31 IFTStep_32 finish \n");

	printf("mips_cfft_q31 IFTStep_32 checking \n\n");

    snr_check_special_q31(refp, q31output, paramCountInputStep32, (f32)SNR_THRESHOLD);

	printf("\n== mips_cfft_q31 IFTStep_32 check done  == \n\n");

// =====================
	printf("== mips_cfft_q31 Step_64 test ==  \n");

        memcpy(q31output,q31inputStep64,sizeof(q31)*paramCountInputStep64);

        status=mips_cfft_init_q31(&instCfftQ31,64);
        ifft = 0;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
        mips_cfft_q31(&(instCfftQ31), q31output, ifft, 1);

	printf("mips_cfft_q31 Step_64 finish \n");

	printf("mips_cfft_q31 Step_64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_q31(q31referenceFileStep64, q31output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_q31(q31referenceFileStep64, q31output, q31referenceFileStep64Len, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_q31 Step_64 check done  == \n\n");

// =====================
	printf("== mips_cfft_q31 IFTStep_64 test ==  \n");

        memcpy(q31output,q31IFTinputStep64,sizeof(q31)*IFTparamCountInputStep64);

        status=mips_cfft_init_q31(&instCfftQ31,64);
        ifft = 1;
        scaling = 6;
        refp = q31inputStep64;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
        mips_cfft_q31(&(instCfftQ31), q31output, ifft, 1);
        for(unsigned long i=0; i < paramCountInputStep64;i++)
        {
          refp[i] >>= scaling;
        }
	printf("mips_cfft_q31 IFTStep_64 finish \n");

	printf("mips_cfft_q31 IFTStep_64 checking \n\n");

    snr_check_special_q31(refp, q31output, paramCountInputStep64, (f32)SNR_THRESHOLD);

	printf("\n== mips_cfft_q31 IFTStep_64 check done  == \n\n");

// =====================
	printf("== mips_cfft_q31 Step_128 test ==  \n");

        memcpy(q31output,q31inputStep128,sizeof(q31)*paramCountInputStep128);

        status=mips_cfft_init_q31(&instCfftQ31,128);
        ifft = 0;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
        mips_cfft_q31(&(instCfftQ31), q31output, ifft, 1);

	printf("mips_cfft_q31 Step_128 finish \n");

	printf("mips_cfft_q31 Step_128 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_q31(q31referenceFileStep128, q31output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_q31(q31referenceFileStep128, q31output, q31referenceFileStep128Len, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_q31 Step_128 check done  == \n\n");

// =====================
	printf("== mips_cfft_q31 IFTStep_128 test ==  \n");

        memcpy(q31output,q31IFTinputStep128,sizeof(q31)*IFTparamCountInputStep128);

        status=mips_cfft_init_q31(&instCfftQ31,128);
        ifft = 1;
        scaling = 7;
        refp = q31inputStep128;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
        mips_cfft_q31(&(instCfftQ31), q31output, ifft, 1);
        for(unsigned long i=0; i < paramCountInputStep128;i++)
        {
          refp[i] >>= scaling;
        }
	printf("mips_cfft_q31 IFTStep_128 finish \n");

	printf("mips_cfft_q31 IFTStep_128 checking \n\n");

    snr_check_special_q31(refp, q31output, paramCountInputStep128, (f32)SNR_THRESHOLD);

	printf("\n== mips_cfft_q31 IFTStep_128 check done  == \n\n");

// =====================
	printf("== mips_cfft_q31 Step_256 test ==  \n");

        memcpy(q31output,q31inputStep256,sizeof(q31)*paramCountInputStep256);

        status=mips_cfft_init_q31(&instCfftQ31,256);
        ifft = 0;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
        mips_cfft_q31(&(instCfftQ31), q31output, ifft, 1);

	printf("mips_cfft_q31 Step_256 finish \n");

	printf("mips_cfft_q31 Step_256 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_q31(q31referenceFileStep256, q31output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_q31(q31referenceFileStep256, q31output, q31referenceFileStep256Len, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_q31 Step_256 check done  == \n\n");

// =====================
	printf("== mips_cfft_q31 IFTStep_256 test ==  \n");

        memcpy(q31output,q31IFTinputStep256,sizeof(q31)*IFTparamCountInputStep256);

        status=mips_cfft_init_q31(&instCfftQ31,256);
        ifft = 1;
        scaling = 8;
        refp = q31inputStep256;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
        mips_cfft_q31(&(instCfftQ31), q31output, ifft, 1);
        for(unsigned long i=0; i < paramCountInputStep256;i++)
        {
          refp[i] >>= scaling;
        }
	printf("mips_cfft_q31 IFTStep_256 finish \n");

	printf("mips_cfft_q31 IFTStep_256 checking \n\n");

    snr_check_special_q31(refp, q31output, paramCountInputStep256, (f32)SNR_THRESHOLD);

	printf("\n== mips_cfft_q31 IFTStep_256 check done  == \n\n");

// =====================
	printf("== mips_cfft_q31 Step_512 test ==  \n");

        memcpy(q31output,q31inputStep512,sizeof(q31)*paramCountInputStep512);

        status=mips_cfft_init_q31(&instCfftQ31,512);
        ifft = 0;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
        mips_cfft_q31(&(instCfftQ31), q31output, ifft, 1);

	printf("mips_cfft_q31 Step_512 finish \n");

	printf("mips_cfft_q31 Step_512 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_q31(q31referenceFileStep512, q31output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_q31(q31referenceFileStep512, q31output, q31referenceFileStep512Len, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_q31 Step_512 check done  == \n\n");

// =====================
	printf("== mips_cfft_q31 IFTStep_512 test ==  \n");

        memcpy(q31output,q31IFTinputStep512,sizeof(q31)*IFTparamCountInputStep512);

        status=mips_cfft_init_q31(&instCfftQ31,512);
        ifft = 1;
        scaling = 9;
        refp = q31inputStep512;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
        mips_cfft_q31(&(instCfftQ31), q31output, ifft, 1);
        for(unsigned long i=0; i < paramCountInputStep512;i++)
        {
          refp[i] >>= scaling;
        }
	printf("mips_cfft_q31 IFTStep_512 finish \n");

	printf("mips_cfft_q31 IFTStep_512 checking \n\n");

    snr_check_special_q31(refp, q31output, paramCountInputStep512, (f32)SNR_THRESHOLD);

	printf("\n== mips_cfft_q31 IFTStep_512 check done  == \n\n");

// =====================
	printf("== mips_cfft_q31 Step_1024 test ==  \n");

        memcpy(q31output,q31inputStep1024,sizeof(q31)*paramCountInputStep1024);

        status=mips_cfft_init_q31(&instCfftQ31,1024);
        ifft = 0;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
        mips_cfft_q31(&(instCfftQ31), q31output, ifft, 1);

	printf("mips_cfft_q31 Step_1024 finish \n");

	printf("mips_cfft_q31 Step_1024 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_q31(q31referenceFileStep1024, q31output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_q31(q31referenceFileStep1024, q31output, q31referenceFileStep1024Len, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_q31 Step_1024 check done  == \n\n");

// =====================
	printf("== mips_cfft_q31 IFTStep_1024 test ==  \n");

        memcpy(q31output,q31IFTinputStep1024,sizeof(q31)*IFTparamCountInputStep1024);

        status=mips_cfft_init_q31(&instCfftQ31,1024);
        ifft = 1;
        scaling = 10;
        refp = q31inputStep1024;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
        mips_cfft_q31(&(instCfftQ31), q31output, ifft, 1);
        for(unsigned long i=0; i < paramCountInputStep1024;i++)
        {
          refp[i] >>= scaling;
        }
	printf("mips_cfft_q31 IFTStep_1024 finish \n");

	printf("mips_cfft_q31 IFTStep_1024 checking \n\n");

    snr_check_special_q31(refp, q31output, paramCountInputStep1024, (f32)SNR_THRESHOLD);

	printf("\n== mips_cfft_q31 IFTStep_1024 check done  == \n\n");

// =====================
	printf("== mips_cfft_q31 Step_2048 test ==  \n");

        memcpy(q31output,q31inputStep2048,sizeof(q31)*paramCountInputStep2048);

        status=mips_cfft_init_q31(&instCfftQ31,2048);
        ifft = 0;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
        mips_cfft_q31(&(instCfftQ31), q31output, ifft, 1);

	printf("mips_cfft_q31 Step_2048 finish \n");

	printf("mips_cfft_q31 Step_2048 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_q31(q31referenceFileStep2048, q31output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_q31(q31referenceFileStep2048, q31output, q31referenceFileStep2048Len, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_q31 Step_2048 check done  == \n\n");

// =====================
	printf("== mips_cfft_q31 IFTStep_2048 test ==  \n");

        memcpy(q31output,q31IFTinputStep2048,sizeof(q31)*IFTparamCountInputStep2048);

        status=mips_cfft_init_q31(&instCfftQ31,2048);
        ifft = 1;
        scaling = 11;
        refp = q31inputStep2048;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
        mips_cfft_q31(&(instCfftQ31), q31output, ifft, 1);
        for(unsigned long i=0; i < paramCountInputStep2048;i++)
        {
          refp[i] >>= scaling;
        }
	printf("mips_cfft_q31 IFTStep_2048 finish \n");

	printf("mips_cfft_q31 IFTStep_2048 checking \n\n");

    snr_check_special_q31(refp, q31output, paramCountInputStep2048, (f32)SNR_THRESHOLD);

	printf("\n== mips_cfft_q31 IFTStep_2048 check done  == \n\n");

// =====================
	printf("== mips_cfft_q31 Step_4096 test ==  \n");

        memcpy(q31output,q31inputStep4096,sizeof(q31)*paramCountInputStep4096);

        status=mips_cfft_init_q31(&instCfftQ31,4096);
        ifft = 0;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
        mips_cfft_q31(&(instCfftQ31), q31output, ifft, 1);

	printf("mips_cfft_q31 Step_4096 finish \n");

	printf("mips_cfft_q31 Step_4096 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_q31(q31referenceFileStep4096, q31output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_q31(q31referenceFileStep4096, q31output, q31referenceFileStep4096Len, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_cfft_q31 Step_4096 check done  == \n\n");

// =====================
	printf("== mips_cfft_q31 IFTStep_4096 test ==  \n");

        memcpy(q31output,q31IFTinputStep4096,sizeof(q31)*IFTparamCountInputStep4096);

        status=mips_cfft_init_q31(&instCfftQ31,4096);
        ifft = 1;
        scaling = 12;
        refp = q31inputStep4096;
        ASSERT_TRUE(status == MIPS_MATH_SUCCESS);
        mips_cfft_q31(&(instCfftQ31), q31output, ifft, 1);
        for(unsigned long i=0; i < paramCountInputStep4096;i++)
        {
          refp[i] >>= scaling;
        }
	printf("mips_cfft_q31 IFTStep_4096 finish \n");

	printf("mips_cfft_q31 IFTStep_4096 checking \n\n");

    snr_check_special_q31(refp, q31output, paramCountInputStep4096, (f32)SNR_THRESHOLD);

	printf("\n== mips_cfft_q31 IFTStep_4096 check done  == \n\n");

        return 0;
}