#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/transform_functions.h"
#include "mips_common_tables.h"
#include "mips_const_structs.h"

#define SNR_THRESHOLD 30

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

    q15 q15inputNoisy16[MAX_SIZE] = {0};
    q15 q15inputNoisy32[MAX_SIZE] = {0};
    q15 q15inputNoisy64[MAX_SIZE] = {0};
    q15 q15inputNoisy128[MAX_SIZE] = {0};
    q15 q15inputNoisy256[MAX_SIZE] = {0};
    q15 q15inputNoisy512[MAX_SIZE] = {0};
    q15 q15inputNoisy1024[MAX_SIZE] = {0};
    q15 q15inputNoisy2048[MAX_SIZE] = {0};
    q15 q15inputNoisy4096[MAX_SIZE] = {0};

    int IFTparamCountInputNoisy16 = 0;
    int IFTparamCountInputNoisy32 = 0;
    int IFTparamCountInputNoisy64 = 0;
    int IFTparamCountInputNoisy128 = 0;
    int IFTparamCountInputNoisy256 = 0;
    int IFTparamCountInputNoisy512 = 0;
    int IFTparamCountInputNoisy1024 = 0;
    int IFTparamCountInputNoisy2048 = 0;
    int IFTparamCountInputNoisy4096 = 0;

    q15 q15IFTinputNoisy16[MAX_SIZE] = {0};
    q15 q15IFTinputNoisy32[MAX_SIZE] = {0};
    q15 q15IFTinputNoisy64[MAX_SIZE] = {0};
    q15 q15IFTinputNoisy128[MAX_SIZE] = {0};
    q15 q15IFTinputNoisy256[MAX_SIZE] = {0};
    q15 q15IFTinputNoisy512[MAX_SIZE] = {0};
    q15 q15IFTinputNoisy1024[MAX_SIZE] = {0};
    q15 q15IFTinputNoisy2048[MAX_SIZE] = {0};
    q15 q15IFTinputNoisy4096[MAX_SIZE] = {0};

    int paramCountInputStep16 = 0;
    int paramCountInputStep32 = 0;
    int paramCountInputStep64 = 0;
    int paramCountInputStep128 = 0;
    int paramCountInputStep256 = 0;
    int paramCountInputStep512 = 0;
    int paramCountInputStep1024 = 0;
    int paramCountInputStep2048 = 0;
    int paramCountInputStep4096 = 0;

    q15 q15inputStep16[MAX_SIZE] = {0};
    q15 q15inputStep32[MAX_SIZE] = {0};
    q15 q15inputStep64[MAX_SIZE] = {0};
    q15 q15inputStep128[MAX_SIZE] = {0};
    q15 q15inputStep256[MAX_SIZE] = {0};
    q15 q15inputStep512[MAX_SIZE] = {0};
    q15 q15inputStep1024[MAX_SIZE] = {0};
    q15 q15inputStep2048[MAX_SIZE] = {0};
    q15 q15inputStep4096[MAX_SIZE] = {0};

    int IFTparamCountInputStep16 = 0;
    int IFTparamCountInputStep32 = 0;
    int IFTparamCountInputStep64 = 0;
    int IFTparamCountInputStep128 = 0;
    int IFTparamCountInputStep256 = 0;
    int IFTparamCountInputStep512 = 0;
    int IFTparamCountInputStep1024 = 0;
    int IFTparamCountInputStep2048 = 0;
    int IFTparamCountInputStep4096 = 0;

    q15 q15IFTinputStep16[MAX_SIZE] = {0};
    q15 q15IFTinputStep32[MAX_SIZE] = {0};
    q15 q15IFTinputStep64[MAX_SIZE] = {0};
    q15 q15IFTinputStep128[MAX_SIZE] = {0};
    q15 q15IFTinputStep256[MAX_SIZE] = {0};
    q15 q15IFTinputStep512[MAX_SIZE] = {0};
    q15 q15IFTinputStep1024[MAX_SIZE] = {0};
    q15 q15IFTinputStep2048[MAX_SIZE] = {0};
    q15 q15IFTinputStep4096[MAX_SIZE] = {0};

    // file name. file path max length is 255, so use 255.

#if defined(NOT_EMBEDDED)
	char q15inputFileNoisy16[255] = {0};
#else
	void *q15inputFileNoisy16;
	int q15inputFileNoisy16Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15inputFileNoisy32[255] = {0};
#else
	void *q15inputFileNoisy32;
	int q15inputFileNoisy32Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15inputFileNoisy64[255] = {0};
#else
	void *q15inputFileNoisy64;
	int q15inputFileNoisy64Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15inputFileNoisy128[255] = {0};
#else
	void *q15inputFileNoisy128;
	int q15inputFileNoisy128Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15inputFileNoisy256[255] = {0};
#else
	void *q15inputFileNoisy256;
	int q15inputFileNoisy256Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15inputFileNoisy512[255] = {0};
#else
	void *q15inputFileNoisy512;
	int q15inputFileNoisy512Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15inputFileNoisy1024[255] = {0};
#else
	void *q15inputFileNoisy1024;
	int q15inputFileNoisy1024Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15inputFileNoisy2048[255] = {0};
#else
	void *q15inputFileNoisy2048;
	int q15inputFileNoisy2048Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15inputFileNoisy4096[255] = {0};
#else
	void *q15inputFileNoisy4096;
	int q15inputFileNoisy4096Len = 0;
#endif


#if defined(NOT_EMBEDDED)
	char q15inputFileStep16[255] = {0};
#else
	void *q15inputFileStep16;
	int q15inputFileStep16Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15inputFileStep32[255] = {0};
#else
	void *q15inputFileStep32;
	int q15inputFileStep32Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15inputFileStep64[255] = {0};
#else
	void *q15inputFileStep64;
	int q15inputFileStep64Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15inputFileStep128[255] = {0};
#else
	void *q15inputFileStep128;
	int q15inputFileStep128Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15inputFileStep256[255] = {0};
#else
	void *q15inputFileStep256;
	int q15inputFileStep256Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15inputFileStep512[255] = {0};
#else
	void *q15inputFileStep512;
	int q15inputFileStep512Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15inputFileStep1024[255] = {0};
#else
	void *q15inputFileStep1024;
	int q15inputFileStep1024Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15inputFileStep2048[255] = {0};
#else
	void *q15inputFileStep2048;
	int q15inputFileStep2048Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15inputFileStep4096[255] = {0};
#else
	void *q15inputFileStep4096;
	int q15inputFileStep4096Len = 0;
#endif


#if defined(NOT_EMBEDDED)
	char q15IFTinputFileNoisy16[255] = {0};
#else
	void *q15IFTinputFileNoisy16;
	int q15IFTinputFileNoisy16Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15IFTinputFileNoisy32[255] = {0};
#else
	void *q15IFTinputFileNoisy32;
	int q15IFTinputFileNoisy32Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15IFTinputFileNoisy64[255] = {0};
#else
	void *q15IFTinputFileNoisy64;
	int q15IFTinputFileNoisy64Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15IFTinputFileNoisy128[255] = {0};
#else
	void *q15IFTinputFileNoisy128;
	int q15IFTinputFileNoisy128Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15IFTinputFileNoisy256[255] = {0};
#else
	void *q15IFTinputFileNoisy256;
	int q15IFTinputFileNoisy256Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15IFTinputFileNoisy512[255] = {0};
#else
	void *q15IFTinputFileNoisy512;
	int q15IFTinputFileNoisy512Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15IFTinputFileNoisy1024[255] = {0};
#else
	void *q15IFTinputFileNoisy1024;
	int q15IFTinputFileNoisy1024Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15IFTinputFileNoisy2048[255] = {0};
#else
	void *q15IFTinputFileNoisy2048;
	int q15IFTinputFileNoisy2048Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15IFTinputFileNoisy4096[255] = {0};
#else
	void *q15IFTinputFileNoisy4096;
	int q15IFTinputFileNoisy4096Len = 0;
#endif


#if defined(NOT_EMBEDDED)
	char q15IFTinputFileStep16[255] = {0};
#else
	void *q15IFTinputFileStep16;
	int q15IFTinputFileStep16Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15IFTinputFileStep32[255] = {0};
#else
	void *q15IFTinputFileStep32;
	int q15IFTinputFileStep32Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15IFTinputFileStep64[255] = {0};
#else
	void *q15IFTinputFileStep64;
	int q15IFTinputFileStep64Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15IFTinputFileStep128[255] = {0};
#else
	void *q15IFTinputFileStep128;
	int q15IFTinputFileStep128Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15IFTinputFileStep256[255] = {0};
#else
	void *q15IFTinputFileStep256;
	int q15IFTinputFileStep256Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15IFTinputFileStep512[255] = {0};
#else
	void *q15IFTinputFileStep512;
	int q15IFTinputFileStep512Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15IFTinputFileStep1024[255] = {0};
#else
	void *q15IFTinputFileStep1024;
	int q15IFTinputFileStep1024Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15IFTinputFileStep2048[255] = {0};
#else
	void *q15IFTinputFileStep2048;
	int q15IFTinputFileStep2048Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15IFTinputFileStep4096[255] = {0};
#else
	void *q15IFTinputFileStep4096;
	int q15IFTinputFileStep4096Len = 0;
#endif


#if defined(NOT_EMBEDDED)
	char q15referenceFileNoisy16[255] = {0};
#else
	void *q15referenceFileNoisy16;
	int q15referenceFileNoisy16Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15referenceFileNoisy32[255] = {0};
#else
	void *q15referenceFileNoisy32;
	int q15referenceFileNoisy32Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15referenceFileNoisy64[255] = {0};
#else
	void *q15referenceFileNoisy64;
	int q15referenceFileNoisy64Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15referenceFileNoisy128[255] = {0};
#else
	void *q15referenceFileNoisy128;
	int q15referenceFileNoisy128Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15referenceFileNoisy256[255] = {0};
#else
	void *q15referenceFileNoisy256;
	int q15referenceFileNoisy256Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15referenceFileNoisy512[255] = {0};
#else
	void *q15referenceFileNoisy512;
	int q15referenceFileNoisy512Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15referenceFileNoisy1024[255] = {0};
#else
	void *q15referenceFileNoisy1024;
	int q15referenceFileNoisy1024Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15referenceFileNoisy2048[255] = {0};
#else
	void *q15referenceFileNoisy2048;
	int q15referenceFileNoisy2048Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15referenceFileNoisy4096[255] = {0};
#else
	void *q15referenceFileNoisy4096;
	int q15referenceFileNoisy4096Len = 0;
#endif


#if defined(NOT_EMBEDDED)
	char q15referenceFileStep16[255] = {0};
#else
	void *q15referenceFileStep16;
	int q15referenceFileStep16Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15referenceFileStep32[255] = {0};
#else
	void *q15referenceFileStep32;
	int q15referenceFileStep32Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15referenceFileStep64[255] = {0};
#else
	void *q15referenceFileStep64;
	int q15referenceFileStep64Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15referenceFileStep128[255] = {0};
#else
	void *q15referenceFileStep128;
	int q15referenceFileStep128Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15referenceFileStep256[255] = {0};
#else
	void *q15referenceFileStep256;
	int q15referenceFileStep256Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15referenceFileStep512[255] = {0};
#else
	void *q15referenceFileStep512;
	int q15referenceFileStep512Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15referenceFileStep1024[255] = {0};
#else
	void *q15referenceFileStep1024;
	int q15referenceFileStep1024Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15referenceFileStep2048[255] = {0};
#else
	void *q15referenceFileStep2048;
	int q15referenceFileStep2048Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15referenceFileStep4096[255] = {0};
#else
	void *q15referenceFileStep4096;
	int q15referenceFileStep4096Len = 0;
#endif


    // set file name by snprintf
    // relative path, function path, filename
#if defined(NOT_EMBEDDED)
	snprintf(q15inputFileNoisy16, sizeof(q15inputFileNoisy16), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexInputSamples_Noisy_16_1_q15.txt");
#else
	q15inputFileNoisy16 = TransformQ15_ComplexInputSamples_Noisy_16_1_q15;
	q15inputFileNoisy16Len = sizeof(TransformQ15_ComplexInputSamples_Noisy_16_1_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15inputFileNoisy32, sizeof(q15inputFileNoisy32), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexInputSamples_Noisy_32_2_q15.txt");
#else
	q15inputFileNoisy32 = TransformQ15_ComplexInputSamples_Noisy_32_2_q15;
	q15inputFileNoisy32Len = sizeof(TransformQ15_ComplexInputSamples_Noisy_32_2_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15inputFileNoisy64, sizeof(q15inputFileNoisy64), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexInputSamples_Noisy_64_3_q15.txt");
#else
	q15inputFileNoisy64 = TransformQ15_ComplexInputSamples_Noisy_64_3_q15;
	q15inputFileNoisy64Len = sizeof(TransformQ15_ComplexInputSamples_Noisy_64_3_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15inputFileNoisy128, sizeof(q15inputFileNoisy128), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexInputSamples_Noisy_128_4_q15.txt");
#else
	q15inputFileNoisy128 = TransformQ15_ComplexInputSamples_Noisy_128_4_q15;
	q15inputFileNoisy128Len = sizeof(TransformQ15_ComplexInputSamples_Noisy_128_4_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15inputFileNoisy256, sizeof(q15inputFileNoisy256), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexInputSamples_Noisy_256_5_q15.txt");
#else
	q15inputFileNoisy256 = TransformQ15_ComplexInputSamples_Noisy_256_5_q15;
	q15inputFileNoisy256Len = sizeof(TransformQ15_ComplexInputSamples_Noisy_256_5_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15inputFileNoisy512, sizeof(q15inputFileNoisy512), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexInputSamples_Noisy_512_6_q15.txt");
#else
	q15inputFileNoisy512 = TransformQ15_ComplexInputSamples_Noisy_512_6_q15;
	q15inputFileNoisy512Len = sizeof(TransformQ15_ComplexInputSamples_Noisy_512_6_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15inputFileNoisy1024, sizeof(q15inputFileNoisy1024), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexInputSamples_Noisy_1024_7_q15.txt");
#else
	q15inputFileNoisy1024 = TransformQ15_ComplexInputSamples_Noisy_1024_7_q15;
	q15inputFileNoisy1024Len = sizeof(TransformQ15_ComplexInputSamples_Noisy_1024_7_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15inputFileNoisy2048, sizeof(q15inputFileNoisy2048), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexInputSamples_Noisy_2048_8_q15.txt");
#else
	q15inputFileNoisy2048 = TransformQ15_ComplexInputSamples_Noisy_2048_8_q15;
	q15inputFileNoisy2048Len = sizeof(TransformQ15_ComplexInputSamples_Noisy_2048_8_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15inputFileNoisy4096, sizeof(q15inputFileNoisy4096), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexInputSamples_Noisy_4096_9_q15.txt");
#else
	q15inputFileNoisy4096 = TransformQ15_ComplexInputSamples_Noisy_4096_9_q15;
	q15inputFileNoisy4096Len = sizeof(TransformQ15_ComplexInputSamples_Noisy_4096_9_q15);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(q15IFTinputFileNoisy16, sizeof(q15IFTinputFileNoisy16), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexInputIFFTSamples_Noisy_16_1_q15.txt");
#else
	q15IFTinputFileNoisy16 = TransformQ15_ComplexInputIFFTSamples_Noisy_16_1_q15;
	q15IFTinputFileNoisy16Len = sizeof(TransformQ15_ComplexInputIFFTSamples_Noisy_16_1_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15IFTinputFileNoisy32, sizeof(q15IFTinputFileNoisy32), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexInputIFFTSamples_Noisy_32_2_q15.txt");
#else
	q15IFTinputFileNoisy32 = TransformQ15_ComplexInputIFFTSamples_Noisy_32_2_q15;
	q15IFTinputFileNoisy32Len = sizeof(TransformQ15_ComplexInputIFFTSamples_Noisy_32_2_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15IFTinputFileNoisy64, sizeof(q15IFTinputFileNoisy64), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexInputIFFTSamples_Noisy_64_3_q15.txt");
#else
	q15IFTinputFileNoisy64 = TransformQ15_ComplexInputIFFTSamples_Noisy_64_3_q15;
	q15IFTinputFileNoisy64Len = sizeof(TransformQ15_ComplexInputIFFTSamples_Noisy_64_3_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15IFTinputFileNoisy128, sizeof(q15IFTinputFileNoisy128), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexInputIFFTSamples_Noisy_128_4_q15.txt");
#else
	q15IFTinputFileNoisy128 = TransformQ15_ComplexInputIFFTSamples_Noisy_128_4_q15;
	q15IFTinputFileNoisy128Len = sizeof(TransformQ15_ComplexInputIFFTSamples_Noisy_128_4_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15IFTinputFileNoisy256, sizeof(q15IFTinputFileNoisy256), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexInputIFFTSamples_Noisy_256_5_q15.txt");
#else
	q15IFTinputFileNoisy256 = TransformQ15_ComplexInputIFFTSamples_Noisy_256_5_q15;
	q15IFTinputFileNoisy256Len = sizeof(TransformQ15_ComplexInputIFFTSamples_Noisy_256_5_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15IFTinputFileNoisy512, sizeof(q15IFTinputFileNoisy512), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexInputIFFTSamples_Noisy_512_6_q15.txt");
#else
	q15IFTinputFileNoisy512 = TransformQ15_ComplexInputIFFTSamples_Noisy_512_6_q15;
	q15IFTinputFileNoisy512Len = sizeof(TransformQ15_ComplexInputIFFTSamples_Noisy_512_6_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15IFTinputFileNoisy1024, sizeof(q15IFTinputFileNoisy1024), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexInputIFFTSamples_Noisy_1024_7_q15.txt");
#else
	q15IFTinputFileNoisy1024 = TransformQ15_ComplexInputIFFTSamples_Noisy_1024_7_q15;
	q15IFTinputFileNoisy1024Len = sizeof(TransformQ15_ComplexInputIFFTSamples_Noisy_1024_7_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15IFTinputFileNoisy2048, sizeof(q15IFTinputFileNoisy2048), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexInputIFFTSamples_Noisy_2048_8_q15.txt");
#else
	q15IFTinputFileNoisy2048 = TransformQ15_ComplexInputIFFTSamples_Noisy_2048_8_q15;
	q15IFTinputFileNoisy2048Len = sizeof(TransformQ15_ComplexInputIFFTSamples_Noisy_2048_8_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15IFTinputFileNoisy4096, sizeof(q15IFTinputFileNoisy4096), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexInputIFFTSamples_Noisy_4096_9_q15.txt");
#else
	q15IFTinputFileNoisy4096 = TransformQ15_ComplexInputIFFTSamples_Noisy_4096_9_q15;
	q15IFTinputFileNoisy4096Len = sizeof(TransformQ15_ComplexInputIFFTSamples_Noisy_4096_9_q15);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(q15referenceFileNoisy16, sizeof(q15referenceFileNoisy16), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexFFTSamples_Noisy_16_1_q15.txt");
#else
	q15referenceFileNoisy16 = TransformQ15_ComplexFFTSamples_Noisy_16_1_q15;
	q15referenceFileNoisy16Len = sizeof(TransformQ15_ComplexFFTSamples_Noisy_16_1_q15)/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15referenceFileNoisy32, sizeof(q15referenceFileNoisy32), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexFFTSamples_Noisy_32_2_q15.txt");
#else
	q15referenceFileNoisy32 = TransformQ15_ComplexFFTSamples_Noisy_32_2_q15;
	q15referenceFileNoisy32Len = sizeof(TransformQ15_ComplexFFTSamples_Noisy_32_2_q15)/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15referenceFileNoisy64, sizeof(q15referenceFileNoisy64), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexFFTSamples_Noisy_64_3_q15.txt");
#else
	q15referenceFileNoisy64 = TransformQ15_ComplexFFTSamples_Noisy_64_3_q15;
	q15referenceFileNoisy64Len = sizeof(TransformQ15_ComplexFFTSamples_Noisy_64_3_q15)/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15referenceFileNoisy128, sizeof(q15referenceFileNoisy128), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexFFTSamples_Noisy_128_4_q15.txt");
#else
	q15referenceFileNoisy128 = TransformQ15_ComplexFFTSamples_Noisy_128_4_q15;
	q15referenceFileNoisy128Len = sizeof(TransformQ15_ComplexFFTSamples_Noisy_128_4_q15)/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15referenceFileNoisy256, sizeof(q15referenceFileNoisy256), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexFFTSamples_Noisy_256_5_q15.txt");
#else
	q15referenceFileNoisy256 = TransformQ15_ComplexFFTSamples_Noisy_256_5_q15;
	q15referenceFileNoisy256Len = sizeof(TransformQ15_ComplexFFTSamples_Noisy_256_5_q15)/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15referenceFileNoisy512, sizeof(q15referenceFileNoisy512), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexFFTSamples_Noisy_512_6_q15.txt");
#else
	q15referenceFileNoisy512 = TransformQ15_ComplexFFTSamples_Noisy_512_6_q15;
	q15referenceFileNoisy512Len = sizeof(TransformQ15_ComplexFFTSamples_Noisy_512_6_q15)/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15referenceFileNoisy1024, sizeof(q15referenceFileNoisy1024), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexFFTSamples_Noisy_1024_7_q15.txt");
#else
	q15referenceFileNoisy1024 = TransformQ15_ComplexFFTSamples_Noisy_1024_7_q15;
	q15referenceFileNoisy1024Len = sizeof(TransformQ15_ComplexFFTSamples_Noisy_1024_7_q15)/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15referenceFileNoisy2048, sizeof(q15referenceFileNoisy2048), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexFFTSamples_Noisy_2048_8_q15.txt");
#else
	q15referenceFileNoisy2048 = TransformQ15_ComplexFFTSamples_Noisy_2048_8_q15;
	q15referenceFileNoisy2048Len = sizeof(TransformQ15_ComplexFFTSamples_Noisy_2048_8_q15)/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15referenceFileNoisy4096, sizeof(q15referenceFileNoisy4096), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexFFTSamples_Noisy_4096_9_q15.txt");
#else
	q15referenceFileNoisy4096 = TransformQ15_ComplexFFTSamples_Noisy_4096_9_q15;
	q15referenceFileNoisy4096Len = sizeof(TransformQ15_ComplexFFTSamples_Noisy_4096_9_q15)/sizeof(q15);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(q15inputFileStep16, sizeof(q15inputFileStep16), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexInputSamples_Step_16_10_q15.txt");
#else
	q15inputFileStep16 = TransformQ15_ComplexInputSamples_Step_16_10_q15;
	q15inputFileStep16Len = sizeof(TransformQ15_ComplexInputSamples_Step_16_10_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15inputFileStep32, sizeof(q15inputFileStep32), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexInputSamples_Step_32_11_q15.txt");
#else
	q15inputFileStep32 = TransformQ15_ComplexInputSamples_Step_32_11_q15;
	q15inputFileStep32Len = sizeof(TransformQ15_ComplexInputSamples_Step_32_11_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15inputFileStep64, sizeof(q15inputFileStep64), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexInputSamples_Step_64_12_q15.txt");
#else
	q15inputFileStep64 = TransformQ15_ComplexInputSamples_Step_64_12_q15;
	q15inputFileStep64Len = sizeof(TransformQ15_ComplexInputSamples_Step_64_12_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15inputFileStep128, sizeof(q15inputFileStep128), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexInputSamples_Step_128_13_q15.txt");
#else
	q15inputFileStep128 = TransformQ15_ComplexInputSamples_Step_128_13_q15;
	q15inputFileStep128Len = sizeof(TransformQ15_ComplexInputSamples_Step_128_13_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15inputFileStep256, sizeof(q15inputFileStep256), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexInputSamples_Step_256_14_q15.txt");
#else
	q15inputFileStep256 = TransformQ15_ComplexInputSamples_Step_256_14_q15;
	q15inputFileStep256Len = sizeof(TransformQ15_ComplexInputSamples_Step_256_14_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15inputFileStep512, sizeof(q15inputFileStep512), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexInputSamples_Step_512_15_q15.txt");
#else
	q15inputFileStep512 = TransformQ15_ComplexInputSamples_Step_512_15_q15;
	q15inputFileStep512Len = sizeof(TransformQ15_ComplexInputSamples_Step_512_15_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15inputFileStep1024, sizeof(q15inputFileStep1024), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexInputSamples_Step_1024_16_q15.txt");
#else
	q15inputFileStep1024 = TransformQ15_ComplexInputSamples_Step_1024_16_q15;
	q15inputFileStep1024Len = sizeof(TransformQ15_ComplexInputSamples_Step_1024_16_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15inputFileStep2048, sizeof(q15inputFileStep2048), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexInputSamples_Step_2048_17_q15.txt");
#else
	q15inputFileStep2048 = TransformQ15_ComplexInputSamples_Step_2048_17_q15;
	q15inputFileStep2048Len = sizeof(TransformQ15_ComplexInputSamples_Step_2048_17_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15inputFileStep4096, sizeof(q15inputFileStep4096), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexInputSamples_Step_4096_18_q15.txt");
#else
	q15inputFileStep4096 = TransformQ15_ComplexInputSamples_Step_4096_18_q15;
	q15inputFileStep4096Len = sizeof(TransformQ15_ComplexInputSamples_Step_4096_18_q15);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(q15IFTinputFileStep16, sizeof(q15IFTinputFileStep16), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexInputIFFTSamples_Step_16_10_q15.txt");
#else
	q15IFTinputFileStep16 = TransformQ15_ComplexInputIFFTSamples_Step_16_10_q15;
	q15IFTinputFileStep16Len = sizeof(TransformQ15_ComplexInputIFFTSamples_Step_16_10_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15IFTinputFileStep32, sizeof(q15IFTinputFileStep32), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexInputIFFTSamples_Step_32_11_q15.txt");
#else
	q15IFTinputFileStep32 = TransformQ15_ComplexInputIFFTSamples_Step_32_11_q15;
	q15IFTinputFileStep32Len = sizeof(TransformQ15_ComplexInputIFFTSamples_Step_32_11_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15IFTinputFileStep64, sizeof(q15IFTinputFileStep64), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexInputIFFTSamples_Step_64_12_q15.txt");
#else
	q15IFTinputFileStep64 = TransformQ15_ComplexInputIFFTSamples_Step_64_12_q15;
	q15IFTinputFileStep64Len = sizeof(TransformQ15_ComplexInputIFFTSamples_Step_64_12_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15IFTinputFileStep128, sizeof(q15IFTinputFileStep128), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexInputIFFTSamples_Step_128_13_q15.txt");
#else
	q15IFTinputFileStep128 = TransformQ15_ComplexInputIFFTSamples_Step_128_13_q15;
	q15IFTinputFileStep128Len = sizeof(TransformQ15_ComplexInputIFFTSamples_Step_128_13_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15IFTinputFileStep256, sizeof(q15IFTinputFileStep256), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexInputIFFTSamples_Step_256_14_q15.txt");
#else
	q15IFTinputFileStep256 = TransformQ15_ComplexInputIFFTSamples_Step_256_14_q15;
	q15IFTinputFileStep256Len = sizeof(TransformQ15_ComplexInputIFFTSamples_Step_256_14_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15IFTinputFileStep512, sizeof(q15IFTinputFileStep512), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexInputIFFTSamples_Step_512_15_q15.txt");
#else
	q15IFTinputFileStep512 = TransformQ15_ComplexInputIFFTSamples_Step_512_15_q15;
	q15IFTinputFileStep512Len = sizeof(TransformQ15_ComplexInputIFFTSamples_Step_512_15_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15IFTinputFileStep1024, sizeof(q15IFTinputFileStep1024), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexInputIFFTSamples_Step_1024_16_q15.txt");
#else
	q15IFTinputFileStep1024 = TransformQ15_ComplexInputIFFTSamples_Step_1024_16_q15;
	q15IFTinputFileStep1024Len = sizeof(TransformQ15_ComplexInputIFFTSamples_Step_1024_16_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15IFTinputFileStep2048, sizeof(q15IFTinputFileStep2048), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexInputIFFTSamples_Step_2048_17_q15.txt");
#else
	q15IFTinputFileStep2048 = TransformQ15_ComplexInputIFFTSamples_Step_2048_17_q15;
	q15IFTinputFileStep2048Len = sizeof(TransformQ15_ComplexInputIFFTSamples_Step_2048_17_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15IFTinputFileStep4096, sizeof(q15IFTinputFileStep4096), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexInputIFFTSamples_Step_4096_18_q15.txt");
#else
	q15IFTinputFileStep4096 = TransformQ15_ComplexInputIFFTSamples_Step_4096_18_q15;
	q15IFTinputFileStep4096Len = sizeof(TransformQ15_ComplexInputIFFTSamples_Step_4096_18_q15);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(q15referenceFileStep16, sizeof(q15referenceFileStep16), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexFFTSamples_Step_16_10_q15.txt");
#else
	q15referenceFileStep16 = TransformQ15_ComplexFFTSamples_Step_16_10_q15;
	q15referenceFileStep16Len = sizeof(TransformQ15_ComplexFFTSamples_Step_16_10_q15)/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15referenceFileStep32, sizeof(q15referenceFileStep32), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexFFTSamples_Step_32_11_q15.txt");
#else
	q15referenceFileStep32 = TransformQ15_ComplexFFTSamples_Step_32_11_q15;
	q15referenceFileStep32Len = sizeof(TransformQ15_ComplexFFTSamples_Step_32_11_q15)/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15referenceFileStep64, sizeof(q15referenceFileStep64), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexFFTSamples_Step_64_12_q15.txt");
#else
	q15referenceFileStep64 = TransformQ15_ComplexFFTSamples_Step_64_12_q15;
	q15referenceFileStep64Len = sizeof(TransformQ15_ComplexFFTSamples_Step_64_12_q15)/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15referenceFileStep128, sizeof(q15referenceFileStep128), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexFFTSamples_Step_128_13_q15.txt");
#else
	q15referenceFileStep128 = TransformQ15_ComplexFFTSamples_Step_128_13_q15;
	q15referenceFileStep128Len = sizeof(TransformQ15_ComplexFFTSamples_Step_128_13_q15)/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15referenceFileStep256, sizeof(q15referenceFileStep256), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexFFTSamples_Step_256_14_q15.txt");
#else
	q15referenceFileStep256 = TransformQ15_ComplexFFTSamples_Step_256_14_q15;
	q15referenceFileStep256Len = sizeof(TransformQ15_ComplexFFTSamples_Step_256_14_q15)/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15referenceFileStep512, sizeof(q15referenceFileStep512), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexFFTSamples_Step_512_15_q15.txt");
#else
	q15referenceFileStep512 = TransformQ15_ComplexFFTSamples_Step_512_15_q15;
	q15referenceFileStep512Len = sizeof(TransformQ15_ComplexFFTSamples_Step_512_15_q15)/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15referenceFileStep1024, sizeof(q15referenceFileStep1024), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexFFTSamples_Step_1024_16_q15.txt");
#else
	q15referenceFileStep1024 = TransformQ15_ComplexFFTSamples_Step_1024_16_q15;
	q15referenceFileStep1024Len = sizeof(TransformQ15_ComplexFFTSamples_Step_1024_16_q15)/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15referenceFileStep2048, sizeof(q15referenceFileStep2048), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexFFTSamples_Step_2048_17_q15.txt");
#else
	q15referenceFileStep2048 = TransformQ15_ComplexFFTSamples_Step_2048_17_q15;
	q15referenceFileStep2048Len = sizeof(TransformQ15_ComplexFFTSamples_Step_2048_17_q15)/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15referenceFileStep4096, sizeof(q15referenceFileStep4096), "%s%s%s", Patterns_PATH, TransformQ15, "ComplexFFTSamples_Step_4096_18_q15.txt");
#else
	q15referenceFileStep4096 = TransformQ15_ComplexFFTSamples_Step_4096_18_q15;
	q15referenceFileStep4096Len = sizeof(TransformQ15_ComplexFFTSamples_Step_4096_18_q15)/sizeof(q15);
#endif


    // load input data
#if defined(NOT_EMBEDDED)
	load_data_q15(q15inputFileNoisy16, &paramCountInputNoisy16, q15inputNoisy16);
#else
	paramCountInputNoisy16 = q15inputFileNoisy16Len;
	load_data_q15(q15inputFileNoisy16, paramCountInputNoisy16, q15inputNoisy16);
	paramCountInputNoisy16 = paramCountInputNoisy16/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15inputFileNoisy32, &paramCountInputNoisy32, q15inputNoisy32);
#else
	paramCountInputNoisy32 = q15inputFileNoisy32Len;
	load_data_q15(q15inputFileNoisy32, paramCountInputNoisy32, q15inputNoisy32);
	paramCountInputNoisy32 = paramCountInputNoisy32/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15inputFileNoisy64, &paramCountInputNoisy64, q15inputNoisy64);
#else
	paramCountInputNoisy64 = q15inputFileNoisy64Len;
	load_data_q15(q15inputFileNoisy64, paramCountInputNoisy64, q15inputNoisy64);
	paramCountInputNoisy64 = paramCountInputNoisy64/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15inputFileNoisy128, &paramCountInputNoisy128, q15inputNoisy128);
#else
	paramCountInputNoisy128 = q15inputFileNoisy128Len;
	load_data_q15(q15inputFileNoisy128, paramCountInputNoisy128, q15inputNoisy128);
	paramCountInputNoisy128 = paramCountInputNoisy128/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15inputFileNoisy256, &paramCountInputNoisy256, q15inputNoisy256);
#else
	paramCountInputNoisy256 = q15inputFileNoisy256Len;
	load_data_q15(q15inputFileNoisy256, paramCountInputNoisy256, q15inputNoisy256);
	paramCountInputNoisy256 = paramCountInputNoisy256/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15inputFileNoisy512, &paramCountInputNoisy512, q15inputNoisy512);
#else
	paramCountInputNoisy512 = q15inputFileNoisy512Len;
	load_data_q15(q15inputFileNoisy512, paramCountInputNoisy512, q15inputNoisy512);
	paramCountInputNoisy512 = paramCountInputNoisy512/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15inputFileNoisy1024, &paramCountInputNoisy1024, q15inputNoisy1024);
#else
	paramCountInputNoisy1024 = q15inputFileNoisy1024Len;
	load_data_q15(q15inputFileNoisy1024, paramCountInputNoisy1024, q15inputNoisy1024);
	paramCountInputNoisy1024 = paramCountInputNoisy1024/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15inputFileNoisy2048, &paramCountInputNoisy2048, q15inputNoisy2048);
#else
	paramCountInputNoisy2048 = q15inputFileNoisy2048Len;
	load_data_q15(q15inputFileNoisy2048, paramCountInputNoisy2048, q15inputNoisy2048);
	paramCountInputNoisy2048 = paramCountInputNoisy2048/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15inputFileNoisy4096, &paramCountInputNoisy4096, q15inputNoisy4096);
#else
	paramCountInputNoisy4096 = q15inputFileNoisy4096Len;
	load_data_q15(q15inputFileNoisy4096, paramCountInputNoisy4096, q15inputNoisy4096);
	paramCountInputNoisy4096 = paramCountInputNoisy4096/sizeof(q15);
#endif


#if defined(NOT_EMBEDDED)
	load_data_q15(q15IFTinputFileNoisy16, &IFTparamCountInputNoisy16, q15IFTinputNoisy16);
#else
	IFTparamCountInputNoisy16 = q15IFTinputFileNoisy16Len;
	load_data_q15(q15IFTinputFileNoisy16, IFTparamCountInputNoisy16, q15IFTinputNoisy16);
	IFTparamCountInputNoisy16 = IFTparamCountInputNoisy16/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15IFTinputFileNoisy32, &IFTparamCountInputNoisy32, q15IFTinputNoisy32);
#else
	IFTparamCountInputNoisy32 = q15IFTinputFileNoisy32Len;
	load_data_q15(q15IFTinputFileNoisy32, IFTparamCountInputNoisy32, q15IFTinputNoisy32);
	IFTparamCountInputNoisy32 = IFTparamCountInputNoisy32/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15IFTinputFileNoisy64, &IFTparamCountInputNoisy64, q15IFTinputNoisy64);
#else
	IFTparamCountInputNoisy64 = q15IFTinputFileNoisy64Len;
	load_data_q15(q15IFTinputFileNoisy64, IFTparamCountInputNoisy64, q15IFTinputNoisy64);
	IFTparamCountInputNoisy64 = IFTparamCountInputNoisy64/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15IFTinputFileNoisy128, &IFTparamCountInputNoisy128, q15IFTinputNoisy128);
#else
	IFTparamCountInputNoisy128 = q15IFTinputFileNoisy128Len;
	load_data_q15(q15IFTinputFileNoisy128, IFTparamCountInputNoisy128, q15IFTinputNoisy128);
	IFTparamCountInputNoisy128 = IFTparamCountInputNoisy128/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15IFTinputFileNoisy256, &IFTparamCountInputNoisy256, q15IFTinputNoisy256);
#else
	IFTparamCountInputNoisy256 = q15IFTinputFileNoisy256Len;
	load_data_q15(q15IFTinputFileNoisy256, IFTparamCountInputNoisy256, q15IFTinputNoisy256);
	IFTparamCountInputNoisy256 = IFTparamCountInputNoisy256/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15IFTinputFileNoisy512, &IFTparamCountInputNoisy512, q15IFTinputNoisy512);
#else
	IFTparamCountInputNoisy512 = q15IFTinputFileNoisy512Len;
	load_data_q15(q15IFTinputFileNoisy512, IFTparamCountInputNoisy512, q15IFTinputNoisy512);
	IFTparamCountInputNoisy512 = IFTparamCountInputNoisy512/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15IFTinputFileNoisy1024, &IFTparamCountInputNoisy1024, q15IFTinputNoisy1024);
#else
	IFTparamCountInputNoisy1024 = q15IFTinputFileNoisy1024Len;
	load_data_q15(q15IFTinputFileNoisy1024, IFTparamCountInputNoisy1024, q15IFTinputNoisy1024);
	IFTparamCountInputNoisy1024 = IFTparamCountInputNoisy1024/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15IFTinputFileNoisy2048, &IFTparamCountInputNoisy2048, q15IFTinputNoisy2048);
#else
	IFTparamCountInputNoisy2048 = q15IFTinputFileNoisy2048Len;
	load_data_q15(q15IFTinputFileNoisy2048, IFTparamCountInputNoisy2048, q15IFTinputNoisy2048);
	IFTparamCountInputNoisy2048 = IFTparamCountInputNoisy2048/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15IFTinputFileNoisy4096, &IFTparamCountInputNoisy4096, q15IFTinputNoisy4096);
#else
	IFTparamCountInputNoisy4096 = q15IFTinputFileNoisy4096Len;
	load_data_q15(q15IFTinputFileNoisy4096, IFTparamCountInputNoisy4096, q15IFTinputNoisy4096);
	IFTparamCountInputNoisy4096 = IFTparamCountInputNoisy4096/sizeof(q15);
#endif


#if defined(NOT_EMBEDDED)
	load_data_q15(q15inputFileStep16, &paramCountInputStep16, q15inputStep16);
#else
	paramCountInputStep16 = q15inputFileStep16Len;
	load_data_q15(q15inputFileStep16, paramCountInputStep16, q15inputStep16);
	paramCountInputStep16 = paramCountInputStep16/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15inputFileStep32, &paramCountInputStep32, q15inputStep32);
#else
	paramCountInputStep32 = q15inputFileStep32Len;
	load_data_q15(q15inputFileStep32, paramCountInputStep32, q15inputStep32);
	paramCountInputStep32 = paramCountInputStep32/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15inputFileStep64, &paramCountInputStep64, q15inputStep64);
#else
	paramCountInputStep64 = q15inputFileStep64Len;
	load_data_q15(q15inputFileStep64, paramCountInputStep64, q15inputStep64);
	paramCountInputStep64 = paramCountInputStep64/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15inputFileStep128, &paramCountInputStep128, q15inputStep128);
#else
	paramCountInputStep128 = q15inputFileStep128Len;
	load_data_q15(q15inputFileStep128, paramCountInputStep128, q15inputStep128);
	paramCountInputStep128 = paramCountInputStep128/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15inputFileStep256, &paramCountInputStep256, q15inputStep256);
#else
	paramCountInputStep256 = q15inputFileStep256Len;
	load_data_q15(q15inputFileStep256, paramCountInputStep256, q15inputStep256);
	paramCountInputStep256 = paramCountInputStep256/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15inputFileStep512, &paramCountInputStep512, q15inputStep512);
#else
	paramCountInputStep512 = q15inputFileStep512Len;
	load_data_q15(q15inputFileStep512, paramCountInputStep512, q15inputStep512);
	paramCountInputStep512 = paramCountInputStep512/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15inputFileStep1024, &paramCountInputStep1024, q15inputStep1024);
#else
	paramCountInputStep1024 = q15inputFileStep1024Len;
	load_data_q15(q15inputFileStep1024, paramCountInputStep1024, q15inputStep1024);
	paramCountInputStep1024 = paramCountInputStep1024/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15inputFileStep2048, &paramCountInputStep2048, q15inputStep2048);
#else
	paramCountInputStep2048 = q15inputFileStep2048Len;
	load_data_q15(q15inputFileStep2048, paramCountInputStep2048, q15inputStep2048);
	paramCountInputStep2048 = paramCountInputStep2048/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15inputFileStep4096, &paramCountInputStep4096, q15inputStep4096);
#else
	paramCountInputStep4096 = q15inputFileStep4096Len;
	load_data_q15(q15inputFileStep4096, paramCountInputStep4096, q15inputStep4096);
	paramCountInputStep4096 = paramCountInputStep4096/sizeof(q15);
#endif


#if defined(NOT_EMBEDDED)
	load_data_q15(q15IFTinputFileStep16, &IFTparamCountInputStep16, q15IFTinputStep16);
#else
	IFTparamCountInputStep16 = q15IFTinputFileStep16Len;
	load_data_q15(q15IFTinputFileStep16, IFTparamCountInputStep16, q15IFTinputStep16);
	IFTparamCountInputStep16 = IFTparamCountInputStep16/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15IFTinputFileStep32, &IFTparamCountInputStep32, q15IFTinputStep32);
#else
	IFTparamCountInputStep32 = q15IFTinputFileStep32Len;
	load_data_q15(q15IFTinputFileStep32, IFTparamCountInputStep32, q15IFTinputStep32);
	IFTparamCountInputStep32 = IFTparamCountInputStep32/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15IFTinputFileStep64, &IFTparamCountInputStep64, q15IFTinputStep64);
#else
	IFTparamCountInputStep64 = q15IFTinputFileStep64Len;
	load_data_q15(q15IFTinputFileStep64, IFTparamCountInputStep64, q15IFTinputStep64);
	IFTparamCountInputStep64 = IFTparamCountInputStep64/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15IFTinputFileStep128, &IFTparamCountInputStep128, q15IFTinputStep128);
#else
	IFTparamCountInputStep128 = q15IFTinputFileStep128Len;
	load_data_q15(q15IFTinputFileStep128, IFTparamCountInputStep128, q15IFTinputStep128);
	IFTparamCountInputStep128 = IFTparamCountInputStep128/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15IFTinputFileStep256, &IFTparamCountInputStep256, q15IFTinputStep256);
#else
	IFTparamCountInputStep256 = q15IFTinputFileStep256Len;
	load_data_q15(q15IFTinputFileStep256, IFTparamCountInputStep256, q15IFTinputStep256);
	IFTparamCountInputStep256 = IFTparamCountInputStep256/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15IFTinputFileStep512, &IFTparamCountInputStep512, q15IFTinputStep512);
#else
	IFTparamCountInputStep512 = q15IFTinputFileStep512Len;
	load_data_q15(q15IFTinputFileStep512, IFTparamCountInputStep512, q15IFTinputStep512);
	IFTparamCountInputStep512 = IFTparamCountInputStep512/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15IFTinputFileStep1024, &IFTparamCountInputStep1024, q15IFTinputStep1024);
#else
	IFTparamCountInputStep1024 = q15IFTinputFileStep1024Len;
	load_data_q15(q15IFTinputFileStep1024, IFTparamCountInputStep1024, q15IFTinputStep1024);
	IFTparamCountInputStep1024 = IFTparamCountInputStep1024/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15IFTinputFileStep2048, &IFTparamCountInputStep2048, q15IFTinputStep2048);
#else
	IFTparamCountInputStep2048 = q15IFTinputFileStep2048Len;
	load_data_q15(q15IFTinputFileStep2048, IFTparamCountInputStep2048, q15IFTinputStep2048);
	IFTparamCountInputStep2048 = IFTparamCountInputStep2048/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15IFTinputFileStep4096, &IFTparamCountInputStep4096, q15IFTinputStep4096);
#else
	IFTparamCountInputStep4096 = q15IFTinputFileStep4096Len;
	load_data_q15(q15IFTinputFileStep4096, IFTparamCountInputStep4096, q15IFTinputStep4096);
	IFTparamCountInputStep4096 = IFTparamCountInputStep4096/sizeof(q15);
#endif


    q15 q15output[MAX_SIZE] = {0};
    int ifft;
    int scaling;
    q15 *refp;
    mips_status status;
    mips_cfft_instance_q15 instCfftQ15;
    // =====================
    printf("== mips_cfft_q15 Noisy_16 test ==  \n");

    memcpy(q15output, q15inputNoisy16, sizeof(q15) * paramCountInputNoisy16);

    status = mips_cfft_init_q15(&instCfftQ15, 16);
    ifft = 0;

    mips_cfft_q15(&(instCfftQ15), q15output, ifft, 1);

    printf("mips_cfft_q15 Noisy_16 finish \n");

    printf("mips_cfft_q15 Noisy_16 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileNoisy16, q15output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15referenceFileNoisy16, q15output, q15referenceFileNoisy16Len, (f32)SNR_THRESHOLD);
#endif


    printf("\n== mips_cfft_q15 Noisy_16 check done  == \n\n");

    // =====================
    printf("== mips_cfft_q15 IFTNoisy_16 test ==  \n");

    memcpy(q15output, q15IFTinputNoisy16, sizeof(q15) * IFTparamCountInputNoisy16);

    status = mips_cfft_init_q15(&instCfftQ15, 16);
    ifft = 1;
    scaling = 4;
    refp = q15inputNoisy16;

    mips_cfft_q15(&(instCfftQ15), q15output, ifft, 1);
    for (unsigned long i = 0; i < paramCountInputNoisy16; i++)
    {
        refp[i] >>= scaling;
    }
    printf("mips_cfft_q15 IFTNoisy_16 finish \n");

    printf("mips_cfft_q15 IFTNoisy_16 checking \n\n");

    snr_check_special_q15(refp, q15output, paramCountInputNoisy16, (f32)SNR_THRESHOLD);

    printf("\n== mips_cfft_q15 IFTNoisy_16 check done  == \n\n");

    // =====================
    printf("== mips_cfft_q15 Noisy_32 test ==  \n");

    memcpy(q15output, q15inputNoisy32, sizeof(q15) * paramCountInputNoisy32);

    status = mips_cfft_init_q15(&instCfftQ15, 32);
    ifft = 0;

    mips_cfft_q15(&(instCfftQ15), q15output, ifft, 1);

    printf("mips_cfft_q15 Noisy_32 finish \n");

    printf("mips_cfft_q15 Noisy_32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileNoisy32, q15output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15referenceFileNoisy32, q15output, q15referenceFileNoisy32Len, (f32)SNR_THRESHOLD);
#endif


    printf("\n== mips_cfft_q15 Noisy_32 check done  == \n\n");

    // =====================
    printf("== mips_cfft_q15 IFTNoisy_32 test ==  \n");

    memcpy(q15output, q15IFTinputNoisy32, sizeof(q15) * IFTparamCountInputNoisy32);

    status = mips_cfft_init_q15(&instCfftQ15, 32);
    ifft = 1;
    scaling = 5;
    refp = q15inputNoisy32;

    mips_cfft_q15(&(instCfftQ15), q15output, ifft, 1);
    for (unsigned long i = 0; i < paramCountInputNoisy32; i++)
    {
        refp[i] >>= scaling;
    }
    printf("mips_cfft_q15 IFTNoisy_32 finish \n");

    printf("mips_cfft_q15 IFTNoisy_32 checking \n\n");

    snr_check_special_q15(refp, q15output, paramCountInputNoisy32, (f32)SNR_THRESHOLD);

    printf("\n== mips_cfft_q15 IFTNoisy_32 check done  == \n\n");

    // =====================
    printf("== mips_cfft_q15 Noisy_64 test ==  \n");

    memcpy(q15output, q15inputNoisy64, sizeof(q15) * paramCountInputNoisy64);

    status = mips_cfft_init_q15(&instCfftQ15, 64);
    ifft = 0;

    mips_cfft_q15(&(instCfftQ15), q15output, ifft, 1);

    printf("mips_cfft_q15 Noisy_64 finish \n");

    printf("mips_cfft_q15 Noisy_64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileNoisy64, q15output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15referenceFileNoisy64, q15output, q15referenceFileNoisy64Len, (f32)SNR_THRESHOLD);
#endif


    printf("\n== mips_cfft_q15 Noisy_64 check done  == \n\n");

    // =====================
    printf("== mips_cfft_q15 IFTNoisy_64 test ==  \n");

    memcpy(q15output, q15IFTinputNoisy64, sizeof(q15) * IFTparamCountInputNoisy64);

    status = mips_cfft_init_q15(&instCfftQ15, 64);
    ifft = 1;
    scaling = 6;
    refp = q15inputNoisy64;

    mips_cfft_q15(&(instCfftQ15), q15output, ifft, 1);
    for (unsigned long i = 0; i < paramCountInputNoisy64; i++)
    {
        refp[i] >>= scaling;
    }
    printf("mips_cfft_q15 IFTNoisy_64 finish \n");

    printf("mips_cfft_q15 IFTNoisy_64 checking \n\n");

    snr_check_special_q15(refp, q15output, paramCountInputNoisy64, (f32)SNR_THRESHOLD);

    printf("\n== mips_cfft_q15 IFTNoisy_64 check done  == \n\n");

    // =====================
    printf("== mips_cfft_q15 Noisy_128 test ==  \n");

    memcpy(q15output, q15inputNoisy128, sizeof(q15) * paramCountInputNoisy128);

    status = mips_cfft_init_q15(&instCfftQ15, 128);
    ifft = 0;

    mips_cfft_q15(&(instCfftQ15), q15output, ifft, 1);

    printf("mips_cfft_q15 Noisy_128 finish \n");

    printf("mips_cfft_q15 Noisy_128 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileNoisy128, q15output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15referenceFileNoisy128, q15output, q15referenceFileNoisy128Len, (f32)SNR_THRESHOLD);
#endif


    printf("\n== mips_cfft_q15 Noisy_128 check done  == \n\n");

    // =====================
    printf("== mips_cfft_q15 IFTNoisy_128 test ==  \n");

    memcpy(q15output, q15IFTinputNoisy128, sizeof(q15) * IFTparamCountInputNoisy128);

    status = mips_cfft_init_q15(&instCfftQ15, 128);
    ifft = 1;
    scaling = 7;
    refp = q15inputNoisy128;

    mips_cfft_q15(&(instCfftQ15), q15output, ifft, 1);
    for (unsigned long i = 0; i < paramCountInputNoisy128; i++)
    {
        refp[i] >>= scaling;
    }
    printf("mips_cfft_q15 IFTNoisy_128 finish \n");

    printf("mips_cfft_q15 IFTNoisy_128 checking \n\n");

    snr_check_special_q15(refp, q15output, paramCountInputNoisy128, (f32)SNR_THRESHOLD);

    printf("\n== mips_cfft_q15 IFTNoisy_128 check done  == \n\n");

    // =====================
    printf("== mips_cfft_q15 Noisy_256 test ==  \n");

    memcpy(q15output, q15inputNoisy256, sizeof(q15) * paramCountInputNoisy256);

    status = mips_cfft_init_q15(&instCfftQ15, 256);
    ifft = 0;

    mips_cfft_q15(&(instCfftQ15), q15output, ifft, 1);

    printf("mips_cfft_q15 Noisy_256 finish \n");

    printf("mips_cfft_q15 Noisy_256 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileNoisy256, q15output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15referenceFileNoisy256, q15output, q15referenceFileNoisy256Len, (f32)SNR_THRESHOLD);
#endif


    printf("\n== mips_cfft_q15 Noisy_256 check done  == \n\n");

    // =====================
    printf("== mips_cfft_q15 IFTNoisy_256 test ==  \n");

    memcpy(q15output, q15IFTinputNoisy256, sizeof(q15) * IFTparamCountInputNoisy256);

    status = mips_cfft_init_q15(&instCfftQ15, 256);
    ifft = 1;
    scaling = 8;
    refp = q15inputNoisy256;

    mips_cfft_q15(&(instCfftQ15), q15output, ifft, 1);
    for (unsigned long i = 0; i < paramCountInputNoisy256; i++)
    {
        refp[i] >>= scaling;
    }
    printf("mips_cfft_q15 IFTNoisy_256 finish \n");

    printf("mips_cfft_q15 IFTNoisy_256 checking \n\n");

    snr_check_special_q15(refp, q15output, paramCountInputNoisy256, (f32)SNR_THRESHOLD);

    printf("\n== mips_cfft_q15 IFTNoisy_256 check done  == \n\n");

    // =====================
    printf("== mips_cfft_q15 Noisy_512 test ==  \n");

    memcpy(q15output, q15inputNoisy512, sizeof(q15) * paramCountInputNoisy512);

    status = mips_cfft_init_q15(&instCfftQ15, 512);
    ifft = 0;

    mips_cfft_q15(&(instCfftQ15), q15output, ifft, 1);

    printf("mips_cfft_q15 Noisy_512 finish \n");

    printf("mips_cfft_q15 Noisy_512 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileNoisy512, q15output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15referenceFileNoisy512, q15output, q15referenceFileNoisy512Len, (f32)SNR_THRESHOLD);
#endif


    printf("\n== mips_cfft_q15 Noisy_512 check done  == \n\n");

#if 0
// =====================
	printf("== mips_cfft_q15 IFTNoisy_512 test ==  \n");

        memcpy(q15output,q15IFTinputNoisy512,sizeof(q15)*IFTparamCountInputNoisy512);

        status=mips_cfft_init_q15(&instCfftQ15,512);
        ifft = 1;
        scaling = 9;
        refp = q15inputNoisy512;
   
        mips_cfft_q15(&(instCfftQ15), q15output, ifft, 1);
        for(unsigned long i=0; i < paramCountInputNoisy512;i++)
        {
          refp[i] >>= scaling;
        }
	printf("mips_cfft_q15 IFTNoisy_512 finish \n");

	printf("mips_cfft_q15 IFTNoisy_512 checking \n\n");

    snr_check_special_q15(refp, q15output, paramCountInputNoisy512, (f32)SNR_THRESHOLD);

	printf("\n== mips_cfft_q15 IFTNoisy_512 check done  == \n\n");
#endif
    // =====================
    printf("== mips_cfft_q15 Noisy_1024 test ==  \n");

    memcpy(q15output, q15inputNoisy1024, sizeof(q15) * paramCountInputNoisy1024);

    status = mips_cfft_init_q15(&instCfftQ15, 1024);
    ifft = 0;

    mips_cfft_q15(&(instCfftQ15), q15output, ifft, 1);

    printf("mips_cfft_q15 Noisy_1024 finish \n");

    printf("mips_cfft_q15 Noisy_1024 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileNoisy1024, q15output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15referenceFileNoisy1024, q15output, q15referenceFileNoisy1024Len, (f32)SNR_THRESHOLD);
#endif


    printf("\n== mips_cfft_q15 Noisy_1024 check done  == \n\n");

#if 0
// =====================
	printf("== mips_cfft_q15 IFTNoisy_1024 test ==  \n");

        memcpy(q15output,q15IFTinputNoisy1024,sizeof(q15)*IFTparamCountInputNoisy1024);

        status=mips_cfft_init_q15(&instCfftQ15,1024);
        ifft = 1;
        scaling = 10;
        refp = q15inputNoisy1024;
   
        mips_cfft_q15(&(instCfftQ15), q15output, ifft, 1);
        for(unsigned long i=0; i < paramCountInputNoisy1024;i++)
        {
          refp[i] >>= scaling;
        }
	printf("mips_cfft_q15 IFTNoisy_1024 finish \n");

	printf("mips_cfft_q15 IFTNoisy_1024 checking \n\n");

    snr_check_special_q15(refp, q15output, paramCountInputNoisy1024, (f32)SNR_THRESHOLD);

	printf("\n== mips_cfft_q15 IFTNoisy_1024 check done  == \n\n");
#endif
    // =====================
    printf("== mips_cfft_q15 Noisy_2048 test ==  \n");

    memcpy(q15output, q15inputNoisy2048, sizeof(q15) * paramCountInputNoisy2048);

    status = mips_cfft_init_q15(&instCfftQ15, 2048);
    ifft = 0;

    mips_cfft_q15(&(instCfftQ15), q15output, ifft, 1);

    printf("mips_cfft_q15 Noisy_2048 finish \n");

    printf("mips_cfft_q15 Noisy_2048 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileNoisy2048, q15output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15referenceFileNoisy2048, q15output, q15referenceFileNoisy2048Len, (f32)SNR_THRESHOLD);
#endif


    printf("\n== mips_cfft_q15 Noisy_2048 check done  == \n\n");

#if 0
// =====================
	printf("== mips_cfft_q15 IFTNoisy_2048 test ==  \n");

        memcpy(q15output,q15IFTinputNoisy2048,sizeof(q15)*IFTparamCountInputNoisy2048);

        status=mips_cfft_init_q15(&instCfftQ15,2048);
        ifft = 1;
        scaling = 11;
        refp = q15inputNoisy2048;
   
        mips_cfft_q15(&(instCfftQ15), q15output, ifft, 1);
        for(unsigned long i=0; i < paramCountInputNoisy2048;i++)
        {
          refp[i] >>= scaling;
        }
	printf("mips_cfft_q15 IFTNoisy_2048 finish \n");

	printf("mips_cfft_q15 IFTNoisy_2048 checking \n\n");

    snr_check_special_q15(refp, q15output, paramCountInputNoisy2048, (f32)SNR_THRESHOLD);

	printf("\n== mips_cfft_q15 IFTNoisy_2048 check done  == \n\n");
#endif
    // =====================
    printf("== mips_cfft_q15 Noisy_4096 test ==  \n");

    memcpy(q15output, q15inputNoisy4096, sizeof(q15) * paramCountInputNoisy4096);

    status = mips_cfft_init_q15(&instCfftQ15, 4096);
    ifft = 0;

    mips_cfft_q15(&(instCfftQ15), q15output, ifft, 1);

    printf("mips_cfft_q15 Noisy_4096 finish \n");

    printf("mips_cfft_q15 Noisy_4096 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileNoisy4096, q15output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15referenceFileNoisy4096, q15output, q15referenceFileNoisy4096Len, (f32)SNR_THRESHOLD);
#endif


    printf("\n== mips_cfft_q15 Noisy_4096 check done  == \n\n");

#if 0
// =====================
	printf("== mips_cfft_q15 IFTNoisy_4096 test ==  \n");

        memcpy(q15output,q15IFTinputNoisy4096,sizeof(q15)*IFTparamCountInputNoisy4096);

        status=mips_cfft_init_q15(&instCfftQ15,4096);
        ifft = 1;
        scaling = 12;
        refp = q15inputNoisy4096;
   
        mips_cfft_q15(&(instCfftQ15), q15output, ifft, 1);
        for(unsigned long i=0; i < paramCountInputNoisy4096;i++)
        {
          refp[i] >>= scaling;
        }
	printf("mips_cfft_q15 IFTNoisy_4096 finish \n");

	printf("mips_cfft_q15 IFTNoisy_4096 checking \n\n");

    snr_check_special_q15(refp, q15output, paramCountInputNoisy4096, (f32)SNR_THRESHOLD);

	printf("\n== mips_cfft_q15 IFTNoisy_4096 check done  == \n\n");
#endif

    // =====================
    printf("== mips_cfft_q15 Step_16 test ==  \n");

    memcpy(q15output, q15inputStep16, sizeof(q15) * paramCountInputStep16);

    status = mips_cfft_init_q15(&instCfftQ15, 16);
    ifft = 0;

    mips_cfft_q15(&(instCfftQ15), q15output, ifft, 1);

    printf("mips_cfft_q15 Step_16 finish \n");

    printf("mips_cfft_q15 Step_16 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileStep16, q15output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15referenceFileStep16, q15output, q15referenceFileStep16Len, (f32)SNR_THRESHOLD);
#endif


    printf("\n== mips_cfft_q15 Step_16 check done  == \n\n");

    // =====================
    printf("== mips_cfft_q15 IFTStep_16 test ==  \n");

    memcpy(q15output, q15IFTinputStep16, sizeof(q15) * IFTparamCountInputStep16);

    status = mips_cfft_init_q15(&instCfftQ15, 16);
    ifft = 1;
    scaling = 4;
    refp = q15inputStep16;

    mips_cfft_q15(&(instCfftQ15), q15output, ifft, 1);
    for (unsigned long i = 0; i < paramCountInputStep16; i++)
    {
        refp[i] >>= scaling;
    }
    printf("mips_cfft_q15 IFTStep_16 finish \n");

    printf("mips_cfft_q15 IFTStep_16 checking \n\n");

    snr_check_special_q15(refp, q15output, paramCountInputStep16, (f32)SNR_THRESHOLD);

    printf("\n== mips_cfft_q15 IFTStep_16 check done  == \n\n");

    // =====================
    printf("== mips_cfft_q15 Step_32 test ==  \n");

    memcpy(q15output, q15inputStep32, sizeof(q15) * paramCountInputStep32);

    status = mips_cfft_init_q15(&instCfftQ15, 32);
    ifft = 0;

    mips_cfft_q15(&(instCfftQ15), q15output, ifft, 1);

    printf("mips_cfft_q15 Step_32 finish \n");

    printf("mips_cfft_q15 Step_32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileStep32, q15output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15referenceFileStep32, q15output, q15referenceFileStep32Len, (f32)SNR_THRESHOLD);
#endif


    printf("\n== mips_cfft_q15 Step_32 check done  == \n\n");

    // =====================
    printf("== mips_cfft_q15 IFTStep_32 test ==  \n");

    memcpy(q15output, q15IFTinputStep32, sizeof(q15) * IFTparamCountInputStep32);

    status = mips_cfft_init_q15(&instCfftQ15, 32);
    ifft = 1;
    scaling = 5;
    refp = q15inputStep32;

    mips_cfft_q15(&(instCfftQ15), q15output, ifft, 1);
    for (unsigned long i = 0; i < paramCountInputStep32; i++)
    {
        refp[i] >>= scaling;
    }
    printf("mips_cfft_q15 IFTStep_32 finish \n");

    printf("mips_cfft_q15 IFTStep_32 checking \n\n");

    snr_check_special_q15(refp, q15output, paramCountInputStep32, (f32)SNR_THRESHOLD);

    printf("\n== mips_cfft_q15 IFTStep_32 check done  == \n\n");

    // =====================
    printf("== mips_cfft_q15 Step_64 test ==  \n");

    memcpy(q15output, q15inputStep64, sizeof(q15) * paramCountInputStep64);

    status = mips_cfft_init_q15(&instCfftQ15, 64);
    ifft = 0;

    mips_cfft_q15(&(instCfftQ15), q15output, ifft, 1);

    printf("mips_cfft_q15 Step_64 finish \n");

    printf("mips_cfft_q15 Step_64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileStep64, q15output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15referenceFileStep64, q15output, q15referenceFileStep64Len, (f32)SNR_THRESHOLD);
#endif


    printf("\n== mips_cfft_q15 Step_64 check done  == \n\n");

    // =====================
    printf("== mips_cfft_q15 IFTStep_64 test ==  \n");

    memcpy(q15output, q15IFTinputStep64, sizeof(q15) * IFTparamCountInputStep64);

    status = mips_cfft_init_q15(&instCfftQ15, 64);
    ifft = 1;
    scaling = 6;
    refp = q15inputStep64;

    mips_cfft_q15(&(instCfftQ15), q15output, ifft, 1);
    for (unsigned long i = 0; i < paramCountInputStep64; i++)
    {
        refp[i] >>= scaling;
    }
    printf("mips_cfft_q15 IFTStep_64 finish \n");

    printf("mips_cfft_q15 IFTStep_64 checking \n\n");

    snr_check_special_q15(refp, q15output, paramCountInputStep64, (f32)SNR_THRESHOLD);

    printf("\n== mips_cfft_q15 IFTStep_64 check done  == \n\n");

    // =====================
    printf("== mips_cfft_q15 Step_128 test ==  \n");

    memcpy(q15output, q15inputStep128, sizeof(q15) * paramCountInputStep128);

    status = mips_cfft_init_q15(&instCfftQ15, 128);
    ifft = 0;

    mips_cfft_q15(&(instCfftQ15), q15output, ifft, 1);

    printf("mips_cfft_q15 Step_128 finish \n");

    printf("mips_cfft_q15 Step_128 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileStep128, q15output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15referenceFileStep128, q15output, q15referenceFileStep128Len, (f32)SNR_THRESHOLD);
#endif


    printf("\n== mips_cfft_q15 Step_128 check done  == \n\n");

    // =====================
    printf("== mips_cfft_q15 IFTStep_128 test ==  \n");

    memcpy(q15output, q15IFTinputStep128, sizeof(q15) * IFTparamCountInputStep128);

    status = mips_cfft_init_q15(&instCfftQ15, 128);
    ifft = 1;
    scaling = 7;
    refp = q15inputStep128;

    mips_cfft_q15(&(instCfftQ15), q15output, ifft, 1);
    for (unsigned long i = 0; i < paramCountInputStep128; i++)
    {
        refp[i] >>= scaling;
    }
    printf("mips_cfft_q15 IFTStep_128 finish \n");

    printf("mips_cfft_q15 IFTStep_128 checking \n\n");

    snr_check_special_q15(refp, q15output, paramCountInputStep128, (f32)SNR_THRESHOLD);

    printf("\n== mips_cfft_q15 IFTStep_128 check done  == \n\n");

    // =====================
    printf("== mips_cfft_q15 Step_256 test ==  \n");

    memcpy(q15output, q15inputStep256, sizeof(q15) * paramCountInputStep256);

    status = mips_cfft_init_q15(&instCfftQ15, 256);
    ifft = 0;

    mips_cfft_q15(&(instCfftQ15), q15output, ifft, 1);

    printf("mips_cfft_q15 Step_256 finish \n");

    printf("mips_cfft_q15 Step_256 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileStep256, q15output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15referenceFileStep256, q15output, q15referenceFileStep256Len, (f32)SNR_THRESHOLD);
#endif


    printf("\n== mips_cfft_q15 Step_256 check done  == \n\n");

    // =====================
    printf("== mips_cfft_q15 IFTStep_256 test ==  \n");

    memcpy(q15output, q15IFTinputStep256, sizeof(q15) * IFTparamCountInputStep256);

    status = mips_cfft_init_q15(&instCfftQ15, 256);
    ifft = 1;
    scaling = 8;
    refp = q15inputStep256;

    mips_cfft_q15(&(instCfftQ15), q15output, ifft, 1);
    for (unsigned long i = 0; i < paramCountInputStep256; i++)
    {
        refp[i] >>= scaling;
    }
    printf("mips_cfft_q15 IFTStep_256 finish \n");

    printf("mips_cfft_q15 IFTStep_256 checking \n\n");

    snr_check_special_q15(refp, q15output, paramCountInputStep256, (f32)SNR_THRESHOLD);

    printf("\n== mips_cfft_q15 IFTStep_256 check done  == \n\n");

    // =====================
    printf("== mips_cfft_q15 Step_512 test ==  \n");

    memcpy(q15output, q15inputStep512, sizeof(q15) * paramCountInputStep512);

    status = mips_cfft_init_q15(&instCfftQ15, 512);
    ifft = 0;

    mips_cfft_q15(&(instCfftQ15), q15output, ifft, 1);

    printf("mips_cfft_q15 Step_512 finish \n");

    printf("mips_cfft_q15 Step_512 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileStep512, q15output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15referenceFileStep512, q15output, q15referenceFileStep512Len, (f32)SNR_THRESHOLD);
#endif


    printf("\n== mips_cfft_q15 Step_512 check done  == \n\n");

#if 0
// =====================
	printf("== mips_cfft_q15 IFTStep_512 test ==  \n");

        memcpy(q15output,q15IFTinputStep512,sizeof(q15)*IFTparamCountInputStep512);

        status=mips_cfft_init_q15(&instCfftQ15,512);
        ifft = 1;
        scaling = 9;
        refp = q15inputStep512;
   
        mips_cfft_q15(&(instCfftQ15), q15output, ifft, 1);
        for(unsigned long i=0; i < paramCountInputStep512;i++)
        {
          refp[i] >>= scaling;
        }
	printf("mips_cfft_q15 IFTStep_512 finish \n");

	printf("mips_cfft_q15 IFTStep_512 checking \n\n");

    snr_check_special_q15(refp, q15output, paramCountInputStep512, (f32)SNR_THRESHOLD);

	printf("\n== mips_cfft_q15 IFTStep_512 check done  == \n\n");
#endif
    // =====================
    printf("== mips_cfft_q15 Step_1024 test ==  \n");

    memcpy(q15output, q15inputStep1024, sizeof(q15) * paramCountInputStep1024);

    status = mips_cfft_init_q15(&instCfftQ15, 1024);
    ifft = 0;

    mips_cfft_q15(&(instCfftQ15), q15output, ifft, 1);

    printf("mips_cfft_q15 Step_1024 finish \n");

    printf("mips_cfft_q15 Step_1024 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileStep1024, q15output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15referenceFileStep1024, q15output, q15referenceFileStep1024Len, (f32)SNR_THRESHOLD);
#endif


    printf("\n== mips_cfft_q15 Step_1024 check done  == \n\n");

#if 0
// =====================
	printf("== mips_cfft_q15 IFTStep_1024 test ==  \n");

        memcpy(q15output,q15IFTinputStep1024,sizeof(q15)*IFTparamCountInputStep1024);

        status=mips_cfft_init_q15(&instCfftQ15,1024);
        ifft = 1;
        scaling = 10;
        refp = q15inputStep1024;
   
        mips_cfft_q15(&(instCfftQ15), q15output, ifft, 1);
        for(unsigned long i=0; i < paramCountInputStep1024;i++)
        {
          refp[i] >>= scaling;
        }
	printf("mips_cfft_q15 IFTStep_1024 finish \n");

	printf("mips_cfft_q15 IFTStep_1024 checking \n\n");

    snr_check_special_q15(refp, q15output, paramCountInputStep1024, (f32)SNR_THRESHOLD);

	printf("\n== mips_cfft_q15 IFTStep_1024 check done  == \n\n");
#endif
    // =====================
    printf("== mips_cfft_q15 Step_2048 test ==  \n");

    memcpy(q15output, q15inputStep2048, sizeof(q15) * paramCountInputStep2048);

    status = mips_cfft_init_q15(&instCfftQ15, 2048);
    ifft = 0;

    mips_cfft_q15(&(instCfftQ15), q15output, ifft, 1);

    printf("mips_cfft_q15 Step_2048 finish \n");

    printf("mips_cfft_q15 Step_2048 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileStep2048, q15output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15referenceFileStep2048, q15output, q15referenceFileStep2048Len, (f32)SNR_THRESHOLD);
#endif


    printf("\n== mips_cfft_q15 Step_2048 check done  == \n\n");

#if 0
// =====================
	printf("== mips_cfft_q15 IFTStep_2048 test ==  \n");

        memcpy(q15output,q15IFTinputStep2048,sizeof(q15)*IFTparamCountInputStep2048);

        status=mips_cfft_init_q15(&instCfftQ15,2048);
        ifft = 1;
        scaling = 11;
        refp = q15inputStep2048;
   
        mips_cfft_q15(&(instCfftQ15), q15output, ifft, 1);
        for(unsigned long i=0; i < paramCountInputStep2048;i++)
        {
          refp[i] >>= scaling;
        }
	printf("mips_cfft_q15 IFTStep_2048 finish \n");

	printf("mips_cfft_q15 IFTStep_2048 checking \n\n");

    snr_check_special_q15(refp, q15output, paramCountInputStep2048, (f32)SNR_THRESHOLD);

	printf("\n== mips_cfft_q15 IFTStep_2048 check done  == \n\n");
#endif
    // =====================
    printf("== mips_cfft_q15 Step_4096 test ==  \n");

    memcpy(q15output, q15inputStep4096, sizeof(q15) * paramCountInputStep4096);

    status = mips_cfft_init_q15(&instCfftQ15, 4096);
    ifft = 0;

    mips_cfft_q15(&(instCfftQ15), q15output, ifft, 1);

    printf("mips_cfft_q15 Step_4096 finish \n");

    printf("mips_cfft_q15 Step_4096 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileStep4096, q15output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15referenceFileStep4096, q15output, q15referenceFileStep4096Len, (f32)SNR_THRESHOLD);
#endif


    printf("\n== mips_cfft_q15 Step_4096 check done  == \n\n");
#if 0
// =====================
	printf("== mips_cfft_q15 IFTStep_4096 test ==  \n");

        memcpy(q15output,q15IFTinputStep4096,sizeof(q15)*IFTparamCountInputStep4096);

        status=mips_cfft_init_q15(&instCfftQ15,4096);
        ifft = 1;
        scaling = 12;
        refp = q15inputStep4096;
   
        mips_cfft_q15(&(instCfftQ15), q15output, ifft, 1);
        for(unsigned long i=0; i < paramCountInputStep4096;i++)
        {
          refp[i] >>= scaling;
        }
	printf("mips_cfft_q15 IFTStep_4096 finish \n");

	printf("mips_cfft_q15 IFTStep_4096 checking \n\n");

    snr_check_special_q15(refp, q15output, paramCountInputStep4096, (f32)SNR_THRESHOLD);

	printf("\n== mips_cfft_q15 IFTStep_4096 check done  == \n\n");
#endif
    return 0;
}