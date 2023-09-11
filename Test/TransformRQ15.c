#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/transform_functions.h"
#include "mips_common_tables.h"
#include "mips_const_structs.h"

#define SNR_THRESHOLD 40

#define RIFFT_SNR_THRESHOLD 25

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

    q15 q15inputNoisy32[MAX_SIZE] = {0};
    q15 q15inputNoisy64[MAX_SIZE] = {0};
    q15 q15inputNoisy128[MAX_SIZE] = {0};
    q15 q15inputNoisy256[MAX_SIZE] = {0};
    q15 q15inputNoisy512[MAX_SIZE] = {0};
    q15 q15inputNoisy1024[MAX_SIZE] = {0};
    q15 q15inputNoisy2048[MAX_SIZE] = {0};
    q15 q15inputNoisy4096[MAX_SIZE] = {0};

    int paramCountRefNoisy32 = 0;
    int paramCountRefNoisy64 = 0;
    int paramCountRefNoisy128 = 0;
    int paramCountRefNoisy256 = 0;
    int paramCountRefNoisy512 = 0;
    int paramCountRefNoisy1024 = 0;
    int paramCountRefNoisy2048 = 0;
    int paramCountRefNoisy4096 = 0;

    q15 q15refNoisy32[MAX_SIZE] = {0};
    q15 q15refNoisy64[MAX_SIZE] = {0};
    q15 q15refNoisy128[MAX_SIZE] = {0};
    q15 q15refNoisy256[MAX_SIZE] = {0};
    q15 q15refNoisy512[MAX_SIZE] = {0};
    q15 q15refNoisy1024[MAX_SIZE] = {0};
    q15 q15refNoisy2048[MAX_SIZE] = {0};
    q15 q15refNoisy4096[MAX_SIZE] = {0};

    int IFTparamCountInputNoisy32 = 0;
    int IFTparamCountInputNoisy64 = 0;
    int IFTparamCountInputNoisy128 = 0;
    int IFTparamCountInputNoisy256 = 0;
    int IFTparamCountInputNoisy512 = 0;
    int IFTparamCountInputNoisy1024 = 0;
    int IFTparamCountInputNoisy2048 = 0;
    int IFTparamCountInputNoisy4096 = 0;

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

    int paramCountRefStep32 = 0;
    int paramCountRefStep64 = 0;
    int paramCountRefStep128 = 0;
    int paramCountRefStep256 = 0;
    int paramCountRefStep512 = 0;
    int paramCountRefStep1024 = 0;
    int paramCountRefStep2048 = 0;
    int paramCountRefStep4096 = 0;

    q15 q15refStep32[MAX_SIZE] = {0};
    q15 q15refStep64[MAX_SIZE] = {0};
    q15 q15refStep128[MAX_SIZE] = {0};
    q15 q15refStep256[MAX_SIZE] = {0};
    q15 q15refStep512[MAX_SIZE] = {0};
    q15 q15refStep1024[MAX_SIZE] = {0};
    q15 q15refStep2048[MAX_SIZE] = {0};
    q15 q15refStep4096[MAX_SIZE] = {0};

    // file name. file path max length is 255, so use 255.

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
	snprintf(q15inputFileNoisy32, sizeof(q15inputFileNoisy32), "%s%s%s", Patterns_PATH, TransformQ15, "RealInputSamples_Noisy_32_2_q15.txt");
#else
	q15inputFileNoisy32 = TransformQ15_RealInputSamples_Noisy_32_2_q15;
	q15inputFileNoisy32Len = sizeof(TransformQ15_RealInputSamples_Noisy_32_2_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15inputFileNoisy64, sizeof(q15inputFileNoisy64), "%s%s%s", Patterns_PATH, TransformQ15, "RealInputSamples_Noisy_64_3_q15.txt");
#else
	q15inputFileNoisy64 = TransformQ15_RealInputSamples_Noisy_64_3_q15;
	q15inputFileNoisy64Len = sizeof(TransformQ15_RealInputSamples_Noisy_64_3_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15inputFileNoisy128, sizeof(q15inputFileNoisy128), "%s%s%s", Patterns_PATH, TransformQ15, "RealInputSamples_Noisy_128_4_q15.txt");
#else
	q15inputFileNoisy128 = TransformQ15_RealInputSamples_Noisy_128_4_q15;
	q15inputFileNoisy128Len = sizeof(TransformQ15_RealInputSamples_Noisy_128_4_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15inputFileNoisy256, sizeof(q15inputFileNoisy256), "%s%s%s", Patterns_PATH, TransformQ15, "RealInputSamples_Noisy_256_5_q15.txt");
#else
	q15inputFileNoisy256 = TransformQ15_RealInputSamples_Noisy_256_5_q15;
	q15inputFileNoisy256Len = sizeof(TransformQ15_RealInputSamples_Noisy_256_5_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15inputFileNoisy512, sizeof(q15inputFileNoisy512), "%s%s%s", Patterns_PATH, TransformQ15, "RealInputSamples_Noisy_512_6_q15.txt");
#else
	q15inputFileNoisy512 = TransformQ15_RealInputSamples_Noisy_512_6_q15;
	q15inputFileNoisy512Len = sizeof(TransformQ15_RealInputSamples_Noisy_512_6_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15inputFileNoisy1024, sizeof(q15inputFileNoisy1024), "%s%s%s", Patterns_PATH, TransformQ15, "RealInputSamples_Noisy_1024_7_q15.txt");
#else
	q15inputFileNoisy1024 = TransformQ15_RealInputSamples_Noisy_1024_7_q15;
	q15inputFileNoisy1024Len = sizeof(TransformQ15_RealInputSamples_Noisy_1024_7_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15inputFileNoisy2048, sizeof(q15inputFileNoisy2048), "%s%s%s", Patterns_PATH, TransformQ15, "RealInputSamples_Noisy_2048_8_q15.txt");
#else
	q15inputFileNoisy2048 = TransformQ15_RealInputSamples_Noisy_2048_8_q15;
	q15inputFileNoisy2048Len = sizeof(TransformQ15_RealInputSamples_Noisy_2048_8_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15inputFileNoisy4096, sizeof(q15inputFileNoisy4096), "%s%s%s", Patterns_PATH, TransformQ15, "RealInputSamples_Noisy_4096_9_q15.txt");
#else
	q15inputFileNoisy4096 = TransformQ15_RealInputSamples_Noisy_4096_9_q15;
	q15inputFileNoisy4096Len = sizeof(TransformQ15_RealInputSamples_Noisy_4096_9_q15);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(q15IFTinputFileNoisy32, sizeof(q15IFTinputFileNoisy32), "%s%s%s", Patterns_PATH, TransformQ15, "RealInputIFFTSamples_Noisy_32_2_q15.txt");
#else
	q15IFTinputFileNoisy32 = TransformQ15_RealInputIFFTSamples_Noisy_32_2_q15;
	q15IFTinputFileNoisy32Len = sizeof(TransformQ15_RealInputIFFTSamples_Noisy_32_2_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15IFTinputFileNoisy64, sizeof(q15IFTinputFileNoisy64), "%s%s%s", Patterns_PATH, TransformQ15, "RealInputIFFTSamples_Noisy_64_3_q15.txt");
#else
	q15IFTinputFileNoisy64 = TransformQ15_RealInputIFFTSamples_Noisy_64_3_q15;
	q15IFTinputFileNoisy64Len = sizeof(TransformQ15_RealInputIFFTSamples_Noisy_64_3_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15IFTinputFileNoisy128, sizeof(q15IFTinputFileNoisy128), "%s%s%s", Patterns_PATH, TransformQ15, "RealInputIFFTSamples_Noisy_128_4_q15.txt");
#else
	q15IFTinputFileNoisy128 = TransformQ15_RealInputIFFTSamples_Noisy_128_4_q15;
	q15IFTinputFileNoisy128Len = sizeof(TransformQ15_RealInputIFFTSamples_Noisy_128_4_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15IFTinputFileNoisy256, sizeof(q15IFTinputFileNoisy256), "%s%s%s", Patterns_PATH, TransformQ15, "RealInputIFFTSamples_Noisy_256_5_q15.txt");
#else
	q15IFTinputFileNoisy256 = TransformQ15_RealInputIFFTSamples_Noisy_256_5_q15;
	q15IFTinputFileNoisy256Len = sizeof(TransformQ15_RealInputIFFTSamples_Noisy_256_5_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15IFTinputFileNoisy512, sizeof(q15IFTinputFileNoisy512), "%s%s%s", Patterns_PATH, TransformQ15, "RealInputIFFTSamples_Noisy_512_6_q15.txt");
#else
	q15IFTinputFileNoisy512 = TransformQ15_RealInputIFFTSamples_Noisy_512_6_q15;
	q15IFTinputFileNoisy512Len = sizeof(TransformQ15_RealInputIFFTSamples_Noisy_512_6_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15IFTinputFileNoisy1024, sizeof(q15IFTinputFileNoisy1024), "%s%s%s", Patterns_PATH, TransformQ15, "RealInputIFFTSamples_Noisy_1024_7_q15.txt");
#else
	q15IFTinputFileNoisy1024 = TransformQ15_RealInputIFFTSamples_Noisy_1024_7_q15;
	q15IFTinputFileNoisy1024Len = sizeof(TransformQ15_RealInputIFFTSamples_Noisy_1024_7_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15IFTinputFileNoisy2048, sizeof(q15IFTinputFileNoisy2048), "%s%s%s", Patterns_PATH, TransformQ15, "RealInputIFFTSamples_Noisy_2048_8_q15.txt");
#else
	q15IFTinputFileNoisy2048 = TransformQ15_RealInputIFFTSamples_Noisy_2048_8_q15;
	q15IFTinputFileNoisy2048Len = sizeof(TransformQ15_RealInputIFFTSamples_Noisy_2048_8_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15IFTinputFileNoisy4096, sizeof(q15IFTinputFileNoisy4096), "%s%s%s", Patterns_PATH, TransformQ15, "RealInputIFFTSamples_Noisy_4096_9_q15.txt");
#else
	q15IFTinputFileNoisy4096 = TransformQ15_RealInputIFFTSamples_Noisy_4096_9_q15;
	q15IFTinputFileNoisy4096Len = sizeof(TransformQ15_RealInputIFFTSamples_Noisy_4096_9_q15);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(q15referenceFileNoisy32, sizeof(q15referenceFileNoisy32), "%s%s%s", Patterns_PATH, TransformQ15, "RealFFTSamples_Noisy_32_2_q15.txt");
#else
	q15referenceFileNoisy32 = TransformQ15_RealFFTSamples_Noisy_32_2_q15;
	q15referenceFileNoisy32Len = sizeof(TransformQ15_RealFFTSamples_Noisy_32_2_q15)/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15referenceFileNoisy64, sizeof(q15referenceFileNoisy64), "%s%s%s", Patterns_PATH, TransformQ15, "RealFFTSamples_Noisy_64_3_q15.txt");
#else
	q15referenceFileNoisy64 = TransformQ15_RealFFTSamples_Noisy_64_3_q15;
	q15referenceFileNoisy64Len = sizeof(TransformQ15_RealFFTSamples_Noisy_64_3_q15)/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15referenceFileNoisy128, sizeof(q15referenceFileNoisy128), "%s%s%s", Patterns_PATH, TransformQ15, "RealFFTSamples_Noisy_128_4_q15.txt");
#else
	q15referenceFileNoisy128 = TransformQ15_RealFFTSamples_Noisy_128_4_q15;
	q15referenceFileNoisy128Len = sizeof(TransformQ15_RealFFTSamples_Noisy_128_4_q15)/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15referenceFileNoisy256, sizeof(q15referenceFileNoisy256), "%s%s%s", Patterns_PATH, TransformQ15, "RealFFTSamples_Noisy_256_5_q15.txt");
#else
	q15referenceFileNoisy256 = TransformQ15_RealFFTSamples_Noisy_256_5_q15;
	q15referenceFileNoisy256Len = sizeof(TransformQ15_RealFFTSamples_Noisy_256_5_q15)/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15referenceFileNoisy512, sizeof(q15referenceFileNoisy512), "%s%s%s", Patterns_PATH, TransformQ15, "RealFFTSamples_Noisy_512_6_q15.txt");
#else
	q15referenceFileNoisy512 = TransformQ15_RealFFTSamples_Noisy_512_6_q15;
	q15referenceFileNoisy512Len = sizeof(TransformQ15_RealFFTSamples_Noisy_512_6_q15)/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15referenceFileNoisy1024, sizeof(q15referenceFileNoisy1024), "%s%s%s", Patterns_PATH, TransformQ15, "RealFFTSamples_Noisy_1024_7_q15.txt");
#else
	q15referenceFileNoisy1024 = TransformQ15_RealFFTSamples_Noisy_1024_7_q15;
	q15referenceFileNoisy1024Len = sizeof(TransformQ15_RealFFTSamples_Noisy_1024_7_q15)/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15referenceFileNoisy2048, sizeof(q15referenceFileNoisy2048), "%s%s%s", Patterns_PATH, TransformQ15, "RealFFTSamples_Noisy_2048_8_q15.txt");
#else
	q15referenceFileNoisy2048 = TransformQ15_RealFFTSamples_Noisy_2048_8_q15;
	q15referenceFileNoisy2048Len = sizeof(TransformQ15_RealFFTSamples_Noisy_2048_8_q15)/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15referenceFileNoisy4096, sizeof(q15referenceFileNoisy4096), "%s%s%s", Patterns_PATH, TransformQ15, "RealFFTSamples_Noisy_4096_9_q15.txt");
#else
	q15referenceFileNoisy4096 = TransformQ15_RealFFTSamples_Noisy_4096_9_q15;
	q15referenceFileNoisy4096Len = sizeof(TransformQ15_RealFFTSamples_Noisy_4096_9_q15)/sizeof(q15);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(q15inputFileStep16, sizeof(q15inputFileStep16), "%s%s%s", Patterns_PATH, TransformQ15, "RealInputSamples_Step_16_10_q15.txt");
#else
	q15inputFileStep16 = TransformQ15_RealInputSamples_Step_16_10_q15;
	q15inputFileStep16Len = sizeof(TransformQ15_RealInputSamples_Step_16_10_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15inputFileStep32, sizeof(q15inputFileStep32), "%s%s%s", Patterns_PATH, TransformQ15, "RealInputSamples_Step_32_11_q15.txt");
#else
	q15inputFileStep32 = TransformQ15_RealInputSamples_Step_32_11_q15;
	q15inputFileStep32Len = sizeof(TransformQ15_RealInputSamples_Step_32_11_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15inputFileStep64, sizeof(q15inputFileStep64), "%s%s%s", Patterns_PATH, TransformQ15, "RealInputSamples_Step_64_12_q15.txt");
#else
	q15inputFileStep64 = TransformQ15_RealInputSamples_Step_64_12_q15;
	q15inputFileStep64Len = sizeof(TransformQ15_RealInputSamples_Step_64_12_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15inputFileStep128, sizeof(q15inputFileStep128), "%s%s%s", Patterns_PATH, TransformQ15, "RealInputSamples_Step_128_13_q15.txt");
#else
	q15inputFileStep128 = TransformQ15_RealInputSamples_Step_128_13_q15;
	q15inputFileStep128Len = sizeof(TransformQ15_RealInputSamples_Step_128_13_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15inputFileStep256, sizeof(q15inputFileStep256), "%s%s%s", Patterns_PATH, TransformQ15, "RealInputSamples_Step_256_14_q15.txt");
#else
	q15inputFileStep256 = TransformQ15_RealInputSamples_Step_256_14_q15;
	q15inputFileStep256Len = sizeof(TransformQ15_RealInputSamples_Step_256_14_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15inputFileStep512, sizeof(q15inputFileStep512), "%s%s%s", Patterns_PATH, TransformQ15, "RealInputSamples_Step_512_15_q15.txt");
#else
	q15inputFileStep512 = TransformQ15_RealInputSamples_Step_512_15_q15;
	q15inputFileStep512Len = sizeof(TransformQ15_RealInputSamples_Step_512_15_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15inputFileStep1024, sizeof(q15inputFileStep1024), "%s%s%s", Patterns_PATH, TransformQ15, "RealInputSamples_Step_1024_16_q15.txt");
#else
	q15inputFileStep1024 = TransformQ15_RealInputSamples_Step_1024_16_q15;
	q15inputFileStep1024Len = sizeof(TransformQ15_RealInputSamples_Step_1024_16_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15inputFileStep2048, sizeof(q15inputFileStep2048), "%s%s%s", Patterns_PATH, TransformQ15, "RealInputSamples_Step_2048_17_q15.txt");
#else
	q15inputFileStep2048 = TransformQ15_RealInputSamples_Step_2048_17_q15;
	q15inputFileStep2048Len = sizeof(TransformQ15_RealInputSamples_Step_2048_17_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15inputFileStep4096, sizeof(q15inputFileStep4096), "%s%s%s", Patterns_PATH, TransformQ15, "RealInputSamples_Step_4096_18_q15.txt");
#else
	q15inputFileStep4096 = TransformQ15_RealInputSamples_Step_4096_18_q15;
	q15inputFileStep4096Len = sizeof(TransformQ15_RealInputSamples_Step_4096_18_q15);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(q15IFTinputFileStep16, sizeof(q15IFTinputFileStep16), "%s%s%s", Patterns_PATH, TransformQ15, "RealInputIFFTSamples_Step_16_10_q15.txt");
#else
	q15IFTinputFileStep16 = TransformQ15_RealInputIFFTSamples_Step_16_10_q15;
	q15IFTinputFileStep16Len = sizeof(TransformQ15_RealInputIFFTSamples_Step_16_10_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15IFTinputFileStep32, sizeof(q15IFTinputFileStep32), "%s%s%s", Patterns_PATH, TransformQ15, "RealInputIFFTSamples_Step_32_11_q15.txt");
#else
	q15IFTinputFileStep32 = TransformQ15_RealInputIFFTSamples_Step_32_11_q15;
	q15IFTinputFileStep32Len = sizeof(TransformQ15_RealInputIFFTSamples_Step_32_11_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15IFTinputFileStep64, sizeof(q15IFTinputFileStep64), "%s%s%s", Patterns_PATH, TransformQ15, "RealInputIFFTSamples_Step_64_12_q15.txt");
#else
	q15IFTinputFileStep64 = TransformQ15_RealInputIFFTSamples_Step_64_12_q15;
	q15IFTinputFileStep64Len = sizeof(TransformQ15_RealInputIFFTSamples_Step_64_12_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15IFTinputFileStep128, sizeof(q15IFTinputFileStep128), "%s%s%s", Patterns_PATH, TransformQ15, "RealInputIFFTSamples_Step_128_13_q15.txt");
#else
	q15IFTinputFileStep128 = TransformQ15_RealInputIFFTSamples_Step_128_13_q15;
	q15IFTinputFileStep128Len = sizeof(TransformQ15_RealInputIFFTSamples_Step_128_13_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15IFTinputFileStep256, sizeof(q15IFTinputFileStep256), "%s%s%s", Patterns_PATH, TransformQ15, "RealInputIFFTSamples_Step_256_14_q15.txt");
#else
	q15IFTinputFileStep256 = TransformQ15_RealInputIFFTSamples_Step_256_14_q15;
	q15IFTinputFileStep256Len = sizeof(TransformQ15_RealInputIFFTSamples_Step_256_14_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15IFTinputFileStep512, sizeof(q15IFTinputFileStep512), "%s%s%s", Patterns_PATH, TransformQ15, "RealInputIFFTSamples_Step_512_15_q15.txt");
#else
	q15IFTinputFileStep512 = TransformQ15_RealInputIFFTSamples_Step_512_15_q15;
	q15IFTinputFileStep512Len = sizeof(TransformQ15_RealInputIFFTSamples_Step_512_15_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15IFTinputFileStep1024, sizeof(q15IFTinputFileStep1024), "%s%s%s", Patterns_PATH, TransformQ15, "RealInputIFFTSamples_Step_1024_16_q15.txt");
#else
	q15IFTinputFileStep1024 = TransformQ15_RealInputIFFTSamples_Step_1024_16_q15;
	q15IFTinputFileStep1024Len = sizeof(TransformQ15_RealInputIFFTSamples_Step_1024_16_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15IFTinputFileStep2048, sizeof(q15IFTinputFileStep2048), "%s%s%s", Patterns_PATH, TransformQ15, "RealInputIFFTSamples_Step_2048_17_q15.txt");
#else
	q15IFTinputFileStep2048 = TransformQ15_RealInputIFFTSamples_Step_2048_17_q15;
	q15IFTinputFileStep2048Len = sizeof(TransformQ15_RealInputIFFTSamples_Step_2048_17_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15IFTinputFileStep4096, sizeof(q15IFTinputFileStep4096), "%s%s%s", Patterns_PATH, TransformQ15, "RealInputIFFTSamples_Step_4096_18_q15.txt");
#else
	q15IFTinputFileStep4096 = TransformQ15_RealInputIFFTSamples_Step_4096_18_q15;
	q15IFTinputFileStep4096Len = sizeof(TransformQ15_RealInputIFFTSamples_Step_4096_18_q15)/sizeof(q15);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(q15referenceFileStep16, sizeof(q15referenceFileStep16), "%s%s%s", Patterns_PATH, TransformQ15, "RealFFTSamples_Step_16_10_q15.txt");
#else
	q15referenceFileStep16 = TransformQ15_RealFFTSamples_Step_16_10_q15;
	q15referenceFileStep16Len = sizeof(TransformQ15_RealFFTSamples_Step_16_10_q15)/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15referenceFileStep32, sizeof(q15referenceFileStep32), "%s%s%s", Patterns_PATH, TransformQ15, "RealFFTSamples_Step_32_11_q15.txt");
#else
	q15referenceFileStep32 = TransformQ15_RealFFTSamples_Step_32_11_q15;
	q15referenceFileStep32Len = sizeof(TransformQ15_RealFFTSamples_Step_32_11_q15)/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15referenceFileStep64, sizeof(q15referenceFileStep64), "%s%s%s", Patterns_PATH, TransformQ15, "RealFFTSamples_Step_64_12_q15.txt");
#else
	q15referenceFileStep64 = TransformQ15_RealFFTSamples_Step_64_12_q15;
	q15referenceFileStep64Len = sizeof(TransformQ15_RealFFTSamples_Step_64_12_q15)/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15referenceFileStep128, sizeof(q15referenceFileStep128), "%s%s%s", Patterns_PATH, TransformQ15, "RealFFTSamples_Step_128_13_q15.txt");
#else
	q15referenceFileStep128 = TransformQ15_RealFFTSamples_Step_128_13_q15;
	q15referenceFileStep128Len = sizeof(TransformQ15_RealFFTSamples_Step_128_13_q15)/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15referenceFileStep256, sizeof(q15referenceFileStep256), "%s%s%s", Patterns_PATH, TransformQ15, "RealFFTSamples_Step_256_14_q15.txt");
#else
	q15referenceFileStep256 = TransformQ15_RealFFTSamples_Step_256_14_q15;
	q15referenceFileStep256Len = sizeof(TransformQ15_RealFFTSamples_Step_256_14_q15)/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15referenceFileStep512, sizeof(q15referenceFileStep512), "%s%s%s", Patterns_PATH, TransformQ15, "RealFFTSamples_Step_512_15_q15.txt");
#else
	q15referenceFileStep512 = TransformQ15_RealFFTSamples_Step_512_15_q15;
	q15referenceFileStep512Len = sizeof(TransformQ15_RealFFTSamples_Step_512_15_q15)/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15referenceFileStep1024, sizeof(q15referenceFileStep1024), "%s%s%s", Patterns_PATH, TransformQ15, "RealFFTSamples_Step_1024_16_q15.txt");
#else
	q15referenceFileStep1024 = TransformQ15_RealFFTSamples_Step_1024_16_q15;
	q15referenceFileStep1024Len = sizeof(TransformQ15_RealFFTSamples_Step_1024_16_q15)/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15referenceFileStep2048, sizeof(q15referenceFileStep2048), "%s%s%s", Patterns_PATH, TransformQ15, "RealFFTSamples_Step_2048_17_q15.txt");
#else
	q15referenceFileStep2048 = TransformQ15_RealFFTSamples_Step_2048_17_q15;
	q15referenceFileStep2048Len = sizeof(TransformQ15_RealFFTSamples_Step_2048_17_q15)/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15referenceFileStep4096, sizeof(q15referenceFileStep4096), "%s%s%s", Patterns_PATH, TransformQ15, "RealFFTSamples_Step_4096_18_q15.txt");
#else
	q15referenceFileStep4096 = TransformQ15_RealFFTSamples_Step_4096_18_q15;
	q15referenceFileStep4096Len = sizeof(TransformQ15_RealFFTSamples_Step_4096_18_q15)/sizeof(q15);
#endif


    // load input data
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
	load_data_q15(q15referenceFileNoisy32, &paramCountRefNoisy32, q15refNoisy32);
#else
	paramCountRefNoisy32 = q15referenceFileNoisy32Len;
	load_data_q15(q15referenceFileNoisy32, paramCountRefNoisy32, q15refNoisy32);
	paramCountRefNoisy32 = paramCountRefNoisy32/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15referenceFileNoisy64, &paramCountRefNoisy64, q15refNoisy64);
#else
	paramCountRefNoisy64 = q15referenceFileNoisy64Len;
	load_data_q15(q15referenceFileNoisy64, paramCountRefNoisy64, q15refNoisy64);
	paramCountRefNoisy64 = paramCountRefNoisy64/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15referenceFileNoisy128, &paramCountRefNoisy128, q15refNoisy128);
#else
	paramCountRefNoisy128 = q15referenceFileNoisy128Len;
	load_data_q15(q15referenceFileNoisy128, paramCountRefNoisy128, q15refNoisy128);
	paramCountRefNoisy128 = paramCountRefNoisy128/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15referenceFileNoisy256, &paramCountRefNoisy256, q15refNoisy256);
#else
	paramCountRefNoisy256 = q15referenceFileNoisy256Len;
	load_data_q15(q15referenceFileNoisy256, paramCountRefNoisy256, q15refNoisy256);
	paramCountRefNoisy256 = paramCountRefNoisy256/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15referenceFileNoisy512, &paramCountRefNoisy512, q15refNoisy512);
#else
	paramCountRefNoisy512 = q15referenceFileNoisy512Len;
	load_data_q15(q15referenceFileNoisy512, paramCountRefNoisy512, q15refNoisy512);
	paramCountRefNoisy512 = paramCountRefNoisy512/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15referenceFileNoisy1024, &paramCountRefNoisy1024, q15refNoisy1024);
#else
	paramCountRefNoisy1024 = q15referenceFileNoisy1024Len;
	load_data_q15(q15referenceFileNoisy1024, paramCountRefNoisy1024, q15refNoisy1024);
	paramCountRefNoisy1024 = paramCountRefNoisy1024/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15referenceFileNoisy2048, &paramCountRefNoisy2048, q15refNoisy2048);
#else
	paramCountRefNoisy2048 = q15referenceFileNoisy2048Len;
	load_data_q15(q15referenceFileNoisy2048, paramCountRefNoisy2048, q15refNoisy2048);
	paramCountRefNoisy2048 = paramCountRefNoisy2048/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15referenceFileNoisy4096, &paramCountRefNoisy4096, q15refNoisy4096);
#else
	paramCountRefNoisy4096 = q15referenceFileNoisy4096Len;
	load_data_q15(q15referenceFileNoisy4096, paramCountRefNoisy4096, q15refNoisy4096);
	paramCountRefNoisy4096 = paramCountRefNoisy4096/sizeof(q15);
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


#if defined(NOT_EMBEDDED)
	load_data_q15(q15referenceFileStep32, &paramCountRefStep32, q15refStep32);
#else
	paramCountRefStep32 = q15referenceFileStep32Len;
	load_data_q15(q15referenceFileStep32, paramCountRefStep32, q15refStep32);
	paramCountRefStep32 = paramCountRefStep32/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15referenceFileStep64, &paramCountRefStep64, q15refStep64);
#else
	paramCountRefStep64 = q15referenceFileStep64Len;
	load_data_q15(q15referenceFileStep64, paramCountRefStep64, q15refStep64);
	paramCountRefStep64 = paramCountRefStep64/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15referenceFileStep128, &paramCountRefStep128, q15refStep128);
#else
	paramCountRefStep128 = q15referenceFileStep128Len;
	load_data_q15(q15referenceFileStep128, paramCountRefStep128, q15refStep128);
	paramCountRefStep128 = paramCountRefStep128/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15referenceFileStep256, &paramCountRefStep256, q15refStep256);
#else
	paramCountRefStep256 = q15referenceFileStep256Len;
	load_data_q15(q15referenceFileStep256, paramCountRefStep256, q15refStep256);
	paramCountRefStep256 = paramCountRefStep256/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15referenceFileStep512, &paramCountRefStep512, q15refStep512);
#else
	paramCountRefStep512 = q15referenceFileStep512Len;
	load_data_q15(q15referenceFileStep512, paramCountRefStep512, q15refStep512);
	paramCountRefStep512 = paramCountRefStep512/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15referenceFileStep1024, &paramCountRefStep1024, q15refStep1024);
#else
	paramCountRefStep1024 = q15referenceFileStep1024Len;
	load_data_q15(q15referenceFileStep1024, paramCountRefStep1024, q15refStep1024);
	paramCountRefStep1024 = paramCountRefStep1024/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15referenceFileStep2048, &paramCountRefStep2048, q15refStep2048);
#else
	paramCountRefStep2048 = q15referenceFileStep2048Len;
	load_data_q15(q15referenceFileStep2048, paramCountRefStep2048, q15refStep2048);
	paramCountRefStep2048 = paramCountRefStep2048/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15referenceFileStep4096, &paramCountRefStep4096, q15refStep4096);
#else
	paramCountRefStep4096 = q15referenceFileStep4096Len;
	load_data_q15(q15referenceFileStep4096, paramCountRefStep4096, q15refStep4096);
	paramCountRefStep4096 = paramCountRefStep4096/sizeof(q15);
#endif


    q15 q15output[MAX_SIZE] = {0};
    q15 q15changed[MAX_SIZE] = {0};
    q15 q15overhead[MAX_SIZE] = {0};

    int ifft;
    int scaling;
    mips_status status;
    mips_rfft_instance_q15 instRfftQ15;
    // =====================
    printf("== mips_rfft_q15 Noisy_32 test ==  \n");

    memcpy(q15changed, q15inputNoisy32, sizeof(q15) * paramCountInputNoisy32);

    mips_rfft_init_q15(&instRfftQ15, 32, 0, 1);
    ifft = 0;

    mips_rfft_q15(&(instRfftQ15), q15changed, q15overhead);

    printf("mips_rfft_q15 Noisy_32 finish \n");

    printf("mips_rfft_q15 Noisy_32 checking \n\n");
    if (ifft)
    {
        for (unsigned long i = 0; i < 2 * paramCountRefNoisy32; i++)
        {
            q15overhead[i] = q15overhead[i] << scaling;
        }
    }

    memcpy(q15output, q15overhead, sizeof(q15) * paramCountRefNoisy32);

    if (ifft)
    {
#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileNoisy32, q15output, 0, (q15)RIFFT_SNR_THRESHOLD);
#else
	snr_check_special_q15(q15refNoisy32, q15output, paramCountRefNoisy32, (q15)RIFFT_SNR_THRESHOLD);
#endif

    }
    else
    {
#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileNoisy32, q15output, 0, (q15)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15refNoisy32, q15output, paramCountRefNoisy32, (q15)SNR_THRESHOLD);
#endif

    }

    printf("\n== mips_rfft_q15 Noisy_32 check done  == \n\n");

    // =====================
    printf("== mips_rfft_q15 IFTNoisy_32 test ==  \n");

    memcpy(q15changed, q15IFTinputNoisy32, sizeof(q15) * IFTparamCountInputNoisy32);

    mips_rfft_init_q15(&instRfftQ15, 32, 1, 1);
    ifft = 1;
    scaling = 5;

    mips_rfft_q15(&(instRfftQ15), q15changed, q15overhead);

    printf("mips_rfft_q15 IFTNoisy_32 finish \n");

    printf("mips_rfft_q15 IFTNoisy_32 checking \n\n");
    if (ifft)
    {
        for (unsigned long i = 0; i < 2 * paramCountInputNoisy32; i++)
        {
            q15overhead[i] = q15overhead[i] << scaling;
        }
    }

    memcpy(q15output, q15overhead, sizeof(q15) * paramCountInputNoisy32);

    if (ifft)
    {
#if defined(NOT_EMBEDDED)
	snr_check_q15(q15inputFileNoisy32, q15output, 0, (q15)RIFFT_SNR_THRESHOLD);
#else
	snr_check_special_q15(q15inputNoisy32, q15output, paramCountInputNoisy32, (q15)RIFFT_SNR_THRESHOLD);
#endif

    }
    else
    {
#if defined(NOT_EMBEDDED)
	snr_check_q15(q15inputFileNoisy32, q15output, 0, (q15)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15inputNoisy32, q15output, paramCountInputNoisy32, (q15)SNR_THRESHOLD);
#endif

    }

    printf("\n== mips_rfft_q15 IFTNoisy_32 check done  == \n\n");

    // =====================
    printf("== mips_rfft_q15 Noisy_64 test ==  \n");

    memcpy(q15changed, q15inputNoisy64, sizeof(q15) * paramCountInputNoisy64);

    mips_rfft_init_q15(&instRfftQ15, 64, 0, 1);
    ifft = 0;

    mips_rfft_q15(&(instRfftQ15), q15changed, q15overhead);

    printf("mips_rfft_q15 Noisy_64 finish \n");

    printf("mips_rfft_q15 Noisy_64 checking \n\n");
    if (ifft)
    {
        for (unsigned long i = 0; i < 2 * paramCountRefNoisy64; i++)
        {
            q15overhead[i] = q15overhead[i] << scaling;
        }
    }

    memcpy(q15output, q15overhead, sizeof(q15) * paramCountRefNoisy64);

    if (ifft)
    {
#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileNoisy64, q15output, 0, (q15)RIFFT_SNR_THRESHOLD);
#else
	snr_check_special_q15(q15refNoisy64, q15output, paramCountRefNoisy64, (q15)RIFFT_SNR_THRESHOLD);
#endif

    }
    else
    {
#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileNoisy64, q15output, 0, (q15)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15refNoisy64, q15output, paramCountRefNoisy64, (q15)SNR_THRESHOLD);
#endif

    }

    printf("\n== mips_rfft_q15 Noisy_64 check done  == \n\n");

    // =====================
    printf("== mips_rfft_q15 IFTNoisy_64 test ==  \n");

    memcpy(q15changed, q15IFTinputNoisy64, sizeof(q15) * IFTparamCountInputNoisy64);

    mips_rfft_init_q15(&instRfftQ15, 64, 1, 1);
    ifft = 1;
    scaling = 6;

    mips_rfft_q15(&(instRfftQ15), q15changed, q15overhead);

    printf("mips_rfft_q15 IFTNoisy_64 finish \n");

    printf("mips_rfft_q15 IFTNoisy_64 checking \n\n");
    if (ifft)
    {
        for (unsigned long i = 0; i < 2 * paramCountInputNoisy64; i++)
        {
            q15overhead[i] = q15overhead[i] << scaling;
        }
    }

    memcpy(q15output, q15overhead, sizeof(q15) * paramCountInputNoisy64);

    if (ifft)
    {
#if defined(NOT_EMBEDDED)
	snr_check_q15(q15inputFileNoisy64, q15output, 0, (q15)RIFFT_SNR_THRESHOLD);
#else
	snr_check_special_q15(q15inputNoisy64, q15output, paramCountInputNoisy64, (q15)RIFFT_SNR_THRESHOLD);
#endif

    }
    else
    {
#if defined(NOT_EMBEDDED)
	snr_check_q15(q15inputFileNoisy64, q15output, 0, (q15)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15inputNoisy64, q15output, paramCountInputNoisy64, (q15)SNR_THRESHOLD);
#endif

    }

    printf("\n== mips_rfft_q15 IFTNoisy_64 check done  == \n\n");

    // =====================
    printf("== mips_rfft_q15 Noisy_128 test ==  \n");

    memcpy(q15changed, q15inputNoisy128, sizeof(q15) * paramCountInputNoisy128);

    mips_rfft_init_q15(&instRfftQ15, 128, 0, 1);
    ifft = 0;

    mips_rfft_q15(&(instRfftQ15), q15changed, q15overhead);

    printf("mips_rfft_q15 Noisy_128 finish \n");

    printf("mips_rfft_q15 Noisy_128 checking \n\n");
    if (ifft)
    {
        for (unsigned long i = 0; i < 2 * paramCountRefNoisy128; i++)
        {
            q15overhead[i] = q15overhead[i] << scaling;
        }
    }

    memcpy(q15output, q15overhead, sizeof(q15) * paramCountRefNoisy128);

    if (ifft)
    {
#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileNoisy128, q15output, 0, (q15)RIFFT_SNR_THRESHOLD);
#else
	snr_check_special_q15(q15refNoisy128, q15output, paramCountRefNoisy128, (q15)RIFFT_SNR_THRESHOLD);
#endif

    }
    else
    {
#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileNoisy128, q15output, 0, (q15)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15refNoisy128, q15output, paramCountRefNoisy128, (q15)SNR_THRESHOLD);
#endif

    }

    printf("\n== mips_rfft_q15 Noisy_128 check done  == \n\n");

    // =====================
    printf("== mips_rfft_q15 IFTNoisy_128 test ==  \n");

    memcpy(q15changed, q15IFTinputNoisy128, sizeof(q15) * IFTparamCountInputNoisy128);

    mips_rfft_init_q15(&instRfftQ15, 128, 1, 1);
    ifft = 1;
    scaling = 7;

    mips_rfft_q15(&(instRfftQ15), q15changed, q15overhead);

    printf("mips_rfft_q15 IFTNoisy_128 finish \n");

    printf("mips_rfft_q15 IFTNoisy_128 checking \n\n");
    if (ifft)
    {
        for (unsigned long i = 0; i < 2 * paramCountInputNoisy128; i++)
        {
            q15overhead[i] = q15overhead[i] << scaling;
        }
    }

    memcpy(q15output, q15overhead, sizeof(q15) * paramCountInputNoisy128);

    if (ifft)
    {
#if defined(NOT_EMBEDDED)
	snr_check_q15(q15inputFileNoisy128, q15output, 0, (q15)RIFFT_SNR_THRESHOLD);
#else
	snr_check_special_q15(q15inputNoisy128, q15output, paramCountInputNoisy128, (q15)RIFFT_SNR_THRESHOLD);
#endif

    }
    else
    {
#if defined(NOT_EMBEDDED)
	snr_check_q15(q15inputFileNoisy128, q15output, 0, (q15)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15inputNoisy128, q15output, paramCountInputNoisy128, (q15)SNR_THRESHOLD);
#endif

    }

    printf("\n== mips_rfft_q15 IFTNoisy_128 check done  == \n\n");

    // =====================
    printf("== mips_rfft_q15 Noisy_256 test ==  \n");

    memcpy(q15changed, q15inputNoisy256, sizeof(q15) * paramCountInputNoisy256);

    mips_rfft_init_q15(&instRfftQ15, 256, 0, 1);
    ifft = 0;

    mips_rfft_q15(&(instRfftQ15), q15changed, q15overhead);

    printf("mips_rfft_q15 Noisy_256 finish \n");

    printf("mips_rfft_q15 Noisy_256 checking \n\n");
    if (ifft)
    {
        for (unsigned long i = 0; i < 2 * paramCountRefNoisy256; i++)
        {
            q15overhead[i] = q15overhead[i] << scaling;
        }
    }

    memcpy(q15output, q15overhead, sizeof(q15) * paramCountRefNoisy256);

    if (ifft)
    {
#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileNoisy256, q15output, 0, (q15)RIFFT_SNR_THRESHOLD);
#else
	snr_check_special_q15(q15refNoisy256, q15output, paramCountRefNoisy256, (q15)RIFFT_SNR_THRESHOLD);
#endif

    }
    else
    {
#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileNoisy256, q15output, 0, (q15)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15refNoisy256, q15output, paramCountRefNoisy256, (q15)SNR_THRESHOLD);
#endif

    }

    printf("\n== mips_rfft_q15 Noisy_256 check done  == \n\n");

#if 0
// =====================
    printf("== mips_rfft_q15 IFTNoisy_256 test ==  \n");

        memcpy(q15changed,q15IFTinputNoisy256,sizeof(q15)*IFTparamCountInputNoisy256);

        mips_rfft_init_q15(&instRfftQ15 ,256,1,1);
        ifft = 1;
        scaling = 8;
   
        mips_rfft_q15(&(instRfftQ15), q15changed, q15overhead);

    printf("mips_rfft_q15 IFTNoisy_256 finish \n");

    printf("mips_rfft_q15 IFTNoisy_256 checking \n\n");
    if (ifft)
       {
          for(unsigned long i = 0;i < 2*paramCountInputNoisy256; i++)
          {
              q15overhead[i] = q15overhead[i] << scaling;
          }
       }

       memcpy(q15output,q15overhead,sizeof(q15)*paramCountInputNoisy256);

       if (ifft)
       {
  #if defined(NOT_EMBEDDED)
	snr_check_q15(q15inputFileNoisy256, q15output, 0, (q15)RIFFT_SNR_THRESHOLD);
#else
	snr_check_special_q15(q15inputNoisy256, q15output, paramCountInputNoisy256, (q15)RIFFT_SNR_THRESHOLD);
#endif

       }
       else
       {
 #if defined(NOT_EMBEDDED)
	snr_check_q15(q15inputFileNoisy256, q15output, 0, (q15)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15inputNoisy256, q15output, paramCountInputNoisy256, (q15)SNR_THRESHOLD);
#endif

       }

    printf("\n== mips_rfft_q15 IFTNoisy_256 check done  == \n\n");
#endif
    // =====================
    printf("== mips_rfft_q15 Noisy_512 test ==  \n");

    memcpy(q15changed, q15inputNoisy512, sizeof(q15) * paramCountInputNoisy512);

    mips_rfft_init_q15(&instRfftQ15, 512, 0, 1);
    ifft = 0;

    mips_rfft_q15(&(instRfftQ15), q15changed, q15overhead);

    printf("mips_rfft_q15 Noisy_512 finish \n");

    printf("mips_rfft_q15 Noisy_512 checking \n\n");
    if (ifft)
    {
        for (unsigned long i = 0; i < 2 * paramCountRefNoisy512; i++)
        {
            q15overhead[i] = q15overhead[i] << scaling;
        }
    }

    memcpy(q15output, q15overhead, sizeof(q15) * paramCountRefNoisy512);

    if (ifft)
    {
#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileNoisy512, q15output, 0, (q15)RIFFT_SNR_THRESHOLD);
#else
	snr_check_special_q15(q15refNoisy512, q15output, paramCountRefNoisy512, (q15)RIFFT_SNR_THRESHOLD);
#endif

    }
    else
    {
#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileNoisy512, q15output, 0, (q15)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15refNoisy512, q15output, paramCountRefNoisy512, (q15)SNR_THRESHOLD);
#endif

    }

    printf("\n== mips_rfft_q15 Noisy_512 check done  == \n\n");

#if 0
// =====================
    printf("== mips_rfft_q15 IFTNoisy_512 test ==  \n");

        memcpy(q15changed,q15IFTinputNoisy512,sizeof(q15)*IFTparamCountInputNoisy512);

        mips_rfft_init_q15(&instRfftQ15 ,512,1,1);
        ifft = 1;
        scaling = 9;
   
        mips_rfft_q15(&(instRfftQ15), q15changed, q15overhead);

    printf("mips_rfft_q15 IFTNoisy_512 finish \n");

    printf("mips_rfft_q15 IFTNoisy_512 checking \n\n");
    if (ifft)
       {
          for(unsigned long i = 0;i < 2*paramCountInputNoisy512; i++)
          {
              q15overhead[i] = q15overhead[i] << scaling;
          }
       }

       memcpy(q15output,q15overhead,sizeof(q15)*paramCountInputNoisy512);

       if (ifft)
       {
  #if defined(NOT_EMBEDDED)
	snr_check_q15(q15inputFileNoisy512, q15output, 0, (q15)RIFFT_SNR_THRESHOLD);
#else
	snr_check_special_q15(q15inputNoisy512, q15output, paramCountInputNoisy512, (q15)RIFFT_SNR_THRESHOLD);
#endif

       }
       else
       {
 #if defined(NOT_EMBEDDED)
	snr_check_q15(q15inputFileNoisy512, q15output, 0, (q15)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15inputNoisy512, q15output, paramCountInputNoisy512, (q15)SNR_THRESHOLD);
#endif

       }

    printf("\n== mips_rfft_q15 IFTNoisy_512 check done  == \n\n");
#endif
    // =====================
    printf("== mips_rfft_q15 Noisy_1024 test ==  \n");

    memcpy(q15changed, q15inputNoisy1024, sizeof(q15) * paramCountInputNoisy1024);

    mips_rfft_init_q15(&instRfftQ15, 1024, 0, 1);
    ifft = 0;

    mips_rfft_q15(&(instRfftQ15), q15changed, q15overhead);

    printf("mips_rfft_q15 Noisy_1024 finish \n");

    printf("mips_rfft_q15 Noisy_1024 checking \n\n");
    if (ifft)
    {
        for (unsigned long i = 0; i < 2 * paramCountRefNoisy1024; i++)
        {
            q15overhead[i] = q15overhead[i] << scaling;
        }
    }

    memcpy(q15output, q15overhead, sizeof(q15) * paramCountRefNoisy1024);

    if (ifft)
    {
#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileNoisy1024, q15output, 0, (q15)RIFFT_SNR_THRESHOLD);
#else
	snr_check_special_q15(q15refNoisy1024, q15output, paramCountRefNoisy1024, (q15)RIFFT_SNR_THRESHOLD);
#endif

    }
    else
    {
#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileNoisy1024, q15output, 0, (q15)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15refNoisy1024, q15output, paramCountRefNoisy1024, (q15)SNR_THRESHOLD);
#endif

    }

    printf("\n== mips_rfft_q15 Noisy_1024 check done  == \n\n");

#if 0
// =====================
    printf("== mips_rfft_q15 IFTNoisy_1024 test ==  \n");

        memcpy(q15changed,q15IFTinputNoisy1024,sizeof(q15)*IFTparamCountInputNoisy1024);

        mips_rfft_init_q15(&instRfftQ15 ,1024,1,1);
        ifft = 1;
        scaling = 10;
   
        mips_rfft_q15(&(instRfftQ15), q15changed, q15overhead);

    printf("mips_rfft_q15 IFTNoisy_1024 finish \n");

    printf("mips_rfft_q15 IFTNoisy_1024 checking \n\n");
    if (ifft)
       {
          for(unsigned long i = 0;i < 2*paramCountInputNoisy1024; i++)
          {
              q15overhead[i] = q15overhead[i] << scaling;
          }
       }

       memcpy(q15output,q15overhead,sizeof(q15)*paramCountInputNoisy1024);

       if (ifft)
       {
  #if defined(NOT_EMBEDDED)
	snr_check_q15(q15inputFileNoisy1024, q15output, 0, (q15)RIFFT_SNR_THRESHOLD);
#else
	snr_check_special_q15(q15inputNoisy1024, q15output, paramCountInputNoisy1024, (q15)RIFFT_SNR_THRESHOLD);
#endif

       }
       else
       {
 #if defined(NOT_EMBEDDED)
	snr_check_q15(q15inputFileNoisy1024, q15output, 0, (q15)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15inputNoisy1024, q15output, paramCountInputNoisy1024, (q15)SNR_THRESHOLD);
#endif

       }

    printf("\n== mips_rfft_q15 IFTNoisy_1024 check done  == \n\n");
#endif
    // =====================
    printf("== mips_rfft_q15 Noisy_2048 test ==  \n");

    memcpy(q15changed, q15inputNoisy2048, sizeof(q15) * paramCountInputNoisy2048);

    mips_rfft_init_q15(&instRfftQ15, 2048, 0, 1);
    ifft = 0;

    mips_rfft_q15(&(instRfftQ15), q15changed, q15overhead);

    printf("mips_rfft_q15 Noisy_2048 finish \n");

    printf("mips_rfft_q15 Noisy_2048 checking \n\n");
    if (ifft)
    {
        for (unsigned long i = 0; i < 2 * paramCountRefNoisy2048; i++)
        {
            q15overhead[i] = q15overhead[i] << scaling;
        }
    }

    memcpy(q15output, q15overhead, sizeof(q15) * paramCountRefNoisy2048);

    if (ifft)
    {
#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileNoisy2048, q15output, 0, (q15)RIFFT_SNR_THRESHOLD);
#else
	snr_check_special_q15(q15refNoisy2048, q15output, paramCountRefNoisy2048, (q15)RIFFT_SNR_THRESHOLD);
#endif

    }
    else
    {
#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileNoisy2048, q15output, 0, (q15)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15refNoisy2048, q15output, paramCountRefNoisy2048, (q15)SNR_THRESHOLD);
#endif

    }

    printf("\n== mips_rfft_q15 Noisy_2048 check done  == \n\n");

#if 0
// =====================
    printf("== mips_rfft_q15 IFTNoisy_2048 test ==  \n");

        memcpy(q15changed,q15IFTinputNoisy2048,sizeof(q15)*IFTparamCountInputNoisy2048);

        mips_rfft_init_q15(&instRfftQ15 ,2048,1,1);
        ifft = 1;
        scaling = 11;
   
        mips_rfft_q15(&(instRfftQ15), q15changed, q15overhead);

    printf("mips_rfft_q15 IFTNoisy_2048 finish \n");

    printf("mips_rfft_q15 IFTNoisy_2048 checking \n\n");
    if (ifft)
       {
          for(unsigned long i = 0;i < 2*paramCountInputNoisy2048; i++)
          {
              q15overhead[i] = q15overhead[i] << scaling;
          }
       }

       memcpy(q15output,q15overhead,sizeof(q15)*paramCountInputNoisy2048);

       if (ifft)
       {
  #if defined(NOT_EMBEDDED)
	snr_check_q15(q15inputFileNoisy2048, q15output, 0, (q15)RIFFT_SNR_THRESHOLD);
#else
	snr_check_special_q15(q15inputNoisy2048, q15output, paramCountInputNoisy2048, (q15)RIFFT_SNR_THRESHOLD);
#endif

       }
       else
       {
 #if defined(NOT_EMBEDDED)
	snr_check_q15(q15inputFileNoisy2048, q15output, 0, (q15)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15inputNoisy2048, q15output, paramCountInputNoisy2048, (q15)SNR_THRESHOLD);
#endif

       }

    printf("\n== mips_rfft_q15 IFTNoisy_2048 check done  == \n\n");
#endif
    // =====================
    printf("== mips_rfft_q15 Noisy_4096 test ==  \n");

    memcpy(q15changed, q15inputNoisy4096, sizeof(q15) * paramCountInputNoisy4096);

    mips_rfft_init_q15(&instRfftQ15, 4096, 0, 1);
    ifft = 0;

    mips_rfft_q15(&(instRfftQ15), q15changed, q15overhead);

    printf("mips_rfft_q15 Noisy_4096 finish \n");

    printf("mips_rfft_q15 Noisy_4096 checking \n\n");
    if (ifft)
    {
        for (unsigned long i = 0; i < 2 * paramCountRefNoisy4096; i++)
        {
            q15overhead[i] = q15overhead[i] << scaling;
        }
    }

    memcpy(q15output, q15overhead, sizeof(q15) * paramCountRefNoisy4096);

    if (ifft)
    {
#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileNoisy4096, q15output, 0, (q15)RIFFT_SNR_THRESHOLD);
#else
	snr_check_special_q15(q15refNoisy4096, q15output, paramCountRefNoisy4096, (q15)RIFFT_SNR_THRESHOLD);
#endif

    }
    else
    {
#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileNoisy4096, q15output, 0, (q15)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15refNoisy4096, q15output, paramCountRefNoisy4096, (q15)SNR_THRESHOLD);
#endif

    }

    printf("\n== mips_rfft_q15 Noisy_4096 check done  == \n\n");

#if 0
// =====================
    printf("== mips_rfft_q15 IFTNoisy_4096 test ==  \n");

        memcpy(q15changed,q15IFTinputNoisy4096,sizeof(q15)*IFTparamCountInputNoisy4096);

        mips_rfft_init_q15(&instRfftQ15 ,4096,1,1);
        ifft = 1;
        scaling = 12;
   
        mips_rfft_q15(&(instRfftQ15), q15changed, q15overhead);

    printf("mips_rfft_q15 IFTNoisy_4096 finish \n");

    printf("mips_rfft_q15 IFTNoisy_4096 checking \n\n");
    if (ifft)
       {
          for(unsigned long i = 0;i < 2*paramCountInputNoisy4096; i++)
          {
              q15overhead[i] = q15overhead[i] << scaling;
          }
       }

       memcpy(q15output,q15overhead,sizeof(q15)*paramCountInputNoisy4096);

       if (ifft)
       {
  #if defined(NOT_EMBEDDED)
	snr_check_q15(q15inputFileNoisy4096, q15output, 0, (q15)RIFFT_SNR_THRESHOLD);
#else
	snr_check_special_q15(q15inputNoisy4096, q15output, paramCountInputNoisy4096, (q15)RIFFT_SNR_THRESHOLD);
#endif

       }
       else
       {
 #if defined(NOT_EMBEDDED)
	snr_check_q15(q15inputFileNoisy4096, q15output, 0, (q15)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15inputNoisy4096, q15output, paramCountInputNoisy4096, (q15)SNR_THRESHOLD);
#endif

       }

    printf("\n== mips_rfft_q15 IFTNoisy_4096 check done  == \n\n");
#endif

    // =====================
    printf("== mips_rfft_q15 Step_32 test ==  \n");

    memcpy(q15changed, q15inputStep32, sizeof(q15) * paramCountInputStep32);

    mips_rfft_init_q15(&instRfftQ15, 32, 0, 1);
    ifft = 0;

    mips_rfft_q15(&(instRfftQ15), q15changed, q15overhead);

    printf("mips_rfft_q15 Step_32 finish \n");

    printf("mips_rfft_q15 Step_32 checking \n\n");
    if (ifft)
    {
        for (unsigned long i = 0; i < 2 * paramCountRefStep32; i++)
        {
            q15overhead[i] = q15overhead[i] << scaling;
        }
    }

    memcpy(q15output, q15overhead, sizeof(q15) * paramCountRefStep32);

    if (ifft)
    {
#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileStep32, q15output, 0, (q15)RIFFT_SNR_THRESHOLD);
#else
	snr_check_special_q15(q15refStep32, q15output, paramCountRefStep32, (q15)RIFFT_SNR_THRESHOLD);
#endif

    }
    else
    {
#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileStep32, q15output, 0, (q15)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15refStep32, q15output, paramCountRefStep32, (q15)SNR_THRESHOLD);
#endif

    }

    printf("\n== mips_rfft_q15 Step_32 check done  == \n\n");

    // =====================
    printf("== mips_rfft_q15 IFTStep_32 test ==  \n");

    memcpy(q15changed, q15IFTinputStep32, sizeof(q15) * IFTparamCountInputStep32);

    mips_rfft_init_q15(&instRfftQ15, 32, 1, 1);
    ifft = 1;
    scaling = 5;

    mips_rfft_q15(&(instRfftQ15), q15changed, q15overhead);

    printf("mips_rfft_q15 IFTStep_32 finish \n");

    printf("mips_rfft_q15 IFTStep_32 checking \n\n");
    if (ifft)
    {
        for (unsigned long i = 0; i < 2 * paramCountInputStep32; i++)
        {
            q15overhead[i] = q15overhead[i] << scaling;
        }
    }

    memcpy(q15output, q15overhead, sizeof(q15) * paramCountInputStep32);

    if (ifft)
    {
#if defined(NOT_EMBEDDED)
	snr_check_q15(q15inputFileStep32, q15output, 0, (q15)RIFFT_SNR_THRESHOLD);
#else
	snr_check_special_q15(q15inputStep32, q15output, paramCountInputStep32, (q15)RIFFT_SNR_THRESHOLD);
#endif

    }
    else
    {
#if defined(NOT_EMBEDDED)
	snr_check_q15(q15inputFileStep32, q15output, 0, (q15)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15inputStep32, q15output, paramCountInputStep32, (q15)SNR_THRESHOLD);
#endif

    }

    printf("\n== mips_rfft_q15 IFTStep_32 check done  == \n\n");

    // =====================
    printf("== mips_rfft_q15 Step_64 test ==  \n");

    memcpy(q15changed, q15inputStep64, sizeof(q15) * paramCountInputStep64);

    mips_rfft_init_q15(&instRfftQ15, 64, 0, 1);
    ifft = 0;

    mips_rfft_q15(&(instRfftQ15), q15changed, q15overhead);

    printf("mips_rfft_q15 Step_64 finish \n");

    printf("mips_rfft_q15 Step_64 checking \n\n");
    if (ifft)
    {
        for (unsigned long i = 0; i < 2 * paramCountRefStep64; i++)
        {
            q15overhead[i] = q15overhead[i] << scaling;
        }
    }

    memcpy(q15output, q15overhead, sizeof(q15) * paramCountRefStep64);

    if (ifft)
    {
#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileStep64, q15output, 0, (q15)RIFFT_SNR_THRESHOLD);
#else
	snr_check_special_q15(q15refStep64, q15output, paramCountRefStep64, (q15)RIFFT_SNR_THRESHOLD);
#endif

    }
    else
    {
#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileStep64, q15output, 0, (q15)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15refStep64, q15output, paramCountRefStep64, (q15)SNR_THRESHOLD);
#endif

    }

    printf("\n== mips_rfft_q15 Step_64 check done  == \n\n");

    // =====================
    printf("== mips_rfft_q15 IFTStep_64 test ==  \n");

    memcpy(q15changed, q15IFTinputStep64, sizeof(q15) * IFTparamCountInputStep64);

    mips_rfft_init_q15(&instRfftQ15, 64, 1, 1);
    ifft = 1;
    scaling = 6;

    mips_rfft_q15(&(instRfftQ15), q15changed, q15overhead);

    printf("mips_rfft_q15 IFTStep_64 finish \n");

    printf("mips_rfft_q15 IFTStep_64 checking \n\n");
    if (ifft)
    {
        for (unsigned long i = 0; i < 2 * paramCountInputStep64; i++)
        {
            q15overhead[i] = q15overhead[i] << scaling;
        }
    }

    memcpy(q15output, q15overhead, sizeof(q15) * paramCountInputStep64);

    if (ifft)
    {
#if defined(NOT_EMBEDDED)
	snr_check_q15(q15inputFileStep64, q15output, 0, (q15)RIFFT_SNR_THRESHOLD);
#else
	snr_check_special_q15(q15inputStep64, q15output, paramCountInputStep64, (q15)RIFFT_SNR_THRESHOLD);
#endif

    }
    else
    {
#if defined(NOT_EMBEDDED)
	snr_check_q15(q15inputFileStep64, q15output, 0, (q15)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15inputStep64, q15output, paramCountInputStep64, (q15)SNR_THRESHOLD);
#endif

    }

    printf("\n== mips_rfft_q15 IFTStep_64 check done  == \n\n");

    // =====================
    printf("== mips_rfft_q15 Step_128 test ==  \n");

    memcpy(q15changed, q15inputStep128, sizeof(q15) * paramCountInputStep128);

    mips_rfft_init_q15(&instRfftQ15, 128, 0, 1);
    ifft = 0;

    mips_rfft_q15(&(instRfftQ15), q15changed, q15overhead);

    printf("mips_rfft_q15 Step_128 finish \n");

    printf("mips_rfft_q15 Step_128 checking \n\n");
    if (ifft)
    {
        for (unsigned long i = 0; i < 2 * paramCountRefStep128; i++)
        {
            q15overhead[i] = q15overhead[i] << scaling;
        }
    }

    memcpy(q15output, q15overhead, sizeof(q15) * paramCountRefStep128);

    if (ifft)
    {
#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileStep128, q15output, 0, (q15)RIFFT_SNR_THRESHOLD);
#else
	snr_check_special_q15(q15refStep128, q15output, paramCountRefStep128, (q15)RIFFT_SNR_THRESHOLD);
#endif

    }
    else
    {
#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileStep128, q15output, 0, (q15)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15refStep128, q15output, paramCountRefStep128, (q15)SNR_THRESHOLD);
#endif

    }

    printf("\n== mips_rfft_q15 Step_128 check done  == \n\n");

    // =====================
    printf("== mips_rfft_q15 IFTStep_128 test ==  \n");

    memcpy(q15changed, q15IFTinputStep128, sizeof(q15) * IFTparamCountInputStep128);

    mips_rfft_init_q15(&instRfftQ15, 128, 1, 1);
    ifft = 1;
    scaling = 7;

    mips_rfft_q15(&(instRfftQ15), q15changed, q15overhead);

    printf("mips_rfft_q15 IFTStep_128 finish \n");

    printf("mips_rfft_q15 IFTStep_128 checking \n\n");
    if (ifft)
    {
        for (unsigned long i = 0; i < 2 * paramCountInputStep128; i++)
        {
            q15overhead[i] = q15overhead[i] << scaling;
        }
    }

    memcpy(q15output, q15overhead, sizeof(q15) * paramCountInputStep128);

    if (ifft)
    {
#if defined(NOT_EMBEDDED)
	snr_check_q15(q15inputFileStep128, q15output, 0, (q15)RIFFT_SNR_THRESHOLD);
#else
	snr_check_special_q15(q15inputStep128, q15output, paramCountInputStep128, (q15)RIFFT_SNR_THRESHOLD);
#endif

    }
    else
    {
#if defined(NOT_EMBEDDED)
	snr_check_q15(q15inputFileStep128, q15output, 0, (q15)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15inputStep128, q15output, paramCountInputStep128, (q15)SNR_THRESHOLD);
#endif

    }

    printf("\n== mips_rfft_q15 IFTStep_128 check done  == \n\n");

    // =====================
    printf("== mips_rfft_q15 Step_256 test ==  \n");

    memcpy(q15changed, q15inputStep256, sizeof(q15) * paramCountInputStep256);

    mips_rfft_init_q15(&instRfftQ15, 256, 0, 1);
    ifft = 0;

    mips_rfft_q15(&(instRfftQ15), q15changed, q15overhead);

    printf("mips_rfft_q15 Step_256 finish \n");

    printf("mips_rfft_q15 Step_256 checking \n\n");
    if (ifft)
    {
        for (unsigned long i = 0; i < 2 * paramCountRefStep256; i++)
        {
            q15overhead[i] = q15overhead[i] << scaling;
        }
    }

    memcpy(q15output, q15overhead, sizeof(q15) * paramCountRefStep256);

    if (ifft)
    {
#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileStep256, q15output, 0, (q15)RIFFT_SNR_THRESHOLD);
#else
	snr_check_special_q15(q15refStep256, q15output, paramCountRefStep256, (q15)RIFFT_SNR_THRESHOLD);
#endif

    }
    else
    {
#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileStep256, q15output, 0, (q15)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15refStep256, q15output, paramCountRefStep256, (q15)SNR_THRESHOLD);
#endif

    }

    printf("\n== mips_rfft_q15 Step_256 check done  == \n\n");

#if 0
// =====================
    printf("== mips_rfft_q15 IFTStep_256 test ==  \n");

        memcpy(q15changed,q15IFTinputStep256,sizeof(q15)*IFTparamCountInputStep256);

        mips_rfft_init_q15(&instRfftQ15 ,256,1,1);
        ifft = 1;
        scaling = 8;
   
        mips_rfft_q15(&(instRfftQ15), q15changed, q15overhead);

    printf("mips_rfft_q15 IFTStep_256 finish \n");

    printf("mips_rfft_q15 IFTStep_256 checking \n\n");
    if (ifft)
       {
          for(unsigned long i = 0;i < 2*paramCountInputStep256; i++)
          {
              q15overhead[i] = q15overhead[i] << scaling;
          }
       }

       memcpy(q15output,q15overhead,sizeof(q15)*paramCountInputStep256);

       if (ifft)
       {
  #if defined(NOT_EMBEDDED)
	snr_check_q15(q15inputFileStep256, q15output, 0, (q15)RIFFT_SNR_THRESHOLD);
#else
	snr_check_special_q15(q15inputStep256, q15output, paramCountInputStep256, (q15)RIFFT_SNR_THRESHOLD);
#endif

       }
       else
       {
 #if defined(NOT_EMBEDDED)
	snr_check_q15(q15inputFileStep256, q15output, 0, (q15)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15inputStep256, q15output, paramCountInputStep256, (q15)SNR_THRESHOLD);
#endif

       }

    printf("\n== mips_rfft_q15 IFTStep_256 check done  == \n\n");
#endif
    // =====================
    printf("== mips_rfft_q15 Step_512 test ==  \n");

    memcpy(q15changed, q15inputStep512, sizeof(q15) * paramCountInputStep512);

    mips_rfft_init_q15(&instRfftQ15, 512, 0, 1);
    ifft = 0;

    mips_rfft_q15(&(instRfftQ15), q15changed, q15overhead);

    printf("mips_rfft_q15 Step_512 finish \n");

    printf("mips_rfft_q15 Step_512 checking \n\n");
    if (ifft)
    {
        for (unsigned long i = 0; i < 2 * paramCountRefStep512; i++)
        {
            q15overhead[i] = q15overhead[i] << scaling;
        }
    }

    memcpy(q15output, q15overhead, sizeof(q15) * paramCountRefStep512);

    if (ifft)
    {
#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileStep512, q15output, 0, (q15)RIFFT_SNR_THRESHOLD);
#else
	snr_check_special_q15(q15refStep512, q15output, paramCountRefStep512, (q15)RIFFT_SNR_THRESHOLD);
#endif

    }
    else
    {
#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileStep512, q15output, 0, (q15)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15refStep512, q15output, paramCountRefStep512, (q15)SNR_THRESHOLD);
#endif

    }

    printf("\n== mips_rfft_q15 Step_512 check done  == \n\n");

#if 0
// =====================
    printf("== mips_rfft_q15 IFTStep_512 test ==  \n");

        memcpy(q15changed,q15IFTinputStep512,sizeof(q15)*IFTparamCountInputStep512);

        mips_rfft_init_q15(&instRfftQ15 ,512,1,1);
        ifft = 1;
        scaling = 9;
   
        mips_rfft_q15(&(instRfftQ15), q15changed, q15overhead);

    printf("mips_rfft_q15 IFTStep_512 finish \n");

    printf("mips_rfft_q15 IFTStep_512 checking \n\n");
    if (ifft)
       {
          for(unsigned long i = 0;i < 2*paramCountInputStep512; i++)
          {
              q15overhead[i] = q15overhead[i] << scaling;
          }
       }

       memcpy(q15output,q15overhead,sizeof(q15)*paramCountInputStep512);

       if (ifft)
       {
  #if defined(NOT_EMBEDDED)
	snr_check_q15(q15inputFileStep512, q15output, 0, (q15)RIFFT_SNR_THRESHOLD);
#else
	snr_check_special_q15(q15inputStep512, q15output, paramCountInputStep512, (q15)RIFFT_SNR_THRESHOLD);
#endif

       }
       else
       {
 #if defined(NOT_EMBEDDED)
	snr_check_q15(q15inputFileStep512, q15output, 0, (q15)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15inputStep512, q15output, paramCountInputStep512, (q15)SNR_THRESHOLD);
#endif

       }

    printf("\n== mips_rfft_q15 IFTStep_512 check done  == \n\n");
#endif
    // =====================
    printf("== mips_rfft_q15 Step_1024 test ==  \n");

    memcpy(q15changed, q15inputStep1024, sizeof(q15) * paramCountInputStep1024);

    mips_rfft_init_q15(&instRfftQ15, 1024, 0, 1);
    ifft = 0;

    mips_rfft_q15(&(instRfftQ15), q15changed, q15overhead);

    printf("mips_rfft_q15 Step_1024 finish \n");

    printf("mips_rfft_q15 Step_1024 checking \n\n");
    if (ifft)
    {
        for (unsigned long i = 0; i < 2 * paramCountRefStep1024; i++)
        {
            q15overhead[i] = q15overhead[i] << scaling;
        }
    }

    memcpy(q15output, q15overhead, sizeof(q15) * paramCountRefStep1024);

    if (ifft)
    {
#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileStep1024, q15output, 0, (q15)RIFFT_SNR_THRESHOLD);
#else
	snr_check_special_q15(q15refStep1024, q15output, paramCountRefStep1024, (q15)RIFFT_SNR_THRESHOLD);
#endif

    }
    else
    {
#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileStep1024, q15output, 0, (q15)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15refStep1024, q15output, paramCountRefStep1024, (q15)SNR_THRESHOLD);
#endif

    }

    printf("\n== mips_rfft_q15 Step_1024 check done  == \n\n");

#if 0
// =====================
    printf("== mips_rfft_q15 IFTStep_1024 test ==  \n");

        memcpy(q15changed,q15IFTinputStep1024,sizeof(q15)*IFTparamCountInputStep1024);

        mips_rfft_init_q15(&instRfftQ15 ,1024,1,1);
        ifft = 1;
        scaling = 10;
   
        mips_rfft_q15(&(instRfftQ15), q15changed, q15overhead);

    printf("mips_rfft_q15 IFTStep_1024 finish \n");

    printf("mips_rfft_q15 IFTStep_1024 checking \n\n");
    if (ifft)
       {
          for(unsigned long i = 0;i < 2*paramCountInputStep1024; i++)
          {
              q15overhead[i] = q15overhead[i] << scaling;
          }
       }

       memcpy(q15output,q15overhead,sizeof(q15)*paramCountInputStep1024);

       if (ifft)
       {
  #if defined(NOT_EMBEDDED)
	snr_check_q15(q15inputFileStep1024, q15output, 0, (q15)RIFFT_SNR_THRESHOLD);
#else
	snr_check_special_q15(q15inputStep1024, q15output, paramCountInputStep1024, (q15)RIFFT_SNR_THRESHOLD);
#endif

       }
       else
       {
 #if defined(NOT_EMBEDDED)
	snr_check_q15(q15inputFileStep1024, q15output, 0, (q15)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15inputStep1024, q15output, paramCountInputStep1024, (q15)SNR_THRESHOLD);
#endif

       }

    printf("\n== mips_rfft_q15 IFTStep_1024 check done  == \n\n");
#endif
    // =====================
    printf("== mips_rfft_q15 Step_2048 test ==  \n");

    memcpy(q15changed, q15inputStep2048, sizeof(q15) * paramCountInputStep2048);

    mips_rfft_init_q15(&instRfftQ15, 2048, 0, 1);
    ifft = 0;

    mips_rfft_q15(&(instRfftQ15), q15changed, q15overhead);

    printf("mips_rfft_q15 Step_2048 finish \n");

    printf("mips_rfft_q15 Step_2048 checking \n\n");
    if (ifft)
    {
        for (unsigned long i = 0; i < 2 * paramCountRefStep2048; i++)
        {
            q15overhead[i] = q15overhead[i] << scaling;
        }
    }

    memcpy(q15output, q15overhead, sizeof(q15) * paramCountRefStep2048);

    if (ifft)
    {
#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileStep2048, q15output, 0, (q15)RIFFT_SNR_THRESHOLD);
#else
	snr_check_special_q15(q15refStep2048, q15output, paramCountRefStep2048, (q15)RIFFT_SNR_THRESHOLD);
#endif

    }
    else
    {
#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileStep2048, q15output, 0, (q15)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15refStep2048, q15output, paramCountRefStep2048, (q15)SNR_THRESHOLD);
#endif

    }

    printf("\n== mips_rfft_q15 Step_2048 check done  == \n\n");

#if 0
// =====================
    printf("== mips_rfft_q15 IFTStep_2048 test ==  \n");

        memcpy(q15changed,q15IFTinputStep2048,sizeof(q15)*IFTparamCountInputStep2048);

        mips_rfft_init_q15(&instRfftQ15 ,2048,1,1);
        ifft = 1;
        scaling = 11;
   
        mips_rfft_q15(&(instRfftQ15), q15changed, q15overhead);

    printf("mips_rfft_q15 IFTStep_2048 finish \n");

    printf("mips_rfft_q15 IFTStep_2048 checking \n\n");
    if (ifft)
       {
          for(unsigned long i = 0;i < 2*paramCountInputStep2048; i++)
          {
              q15overhead[i] = q15overhead[i] << scaling;
          }
       }

       memcpy(q15output,q15overhead,sizeof(q15)*paramCountInputStep2048);

       if (ifft)
       {
  #if defined(NOT_EMBEDDED)
	snr_check_q15(q15inputFileStep2048, q15output, 0, (q15)RIFFT_SNR_THRESHOLD);
#else
	snr_check_special_q15(q15inputStep2048, q15output, paramCountInputStep2048, (q15)RIFFT_SNR_THRESHOLD);
#endif

       }
       else
       {
 #if defined(NOT_EMBEDDED)
	snr_check_q15(q15inputFileStep2048, q15output, 0, (q15)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15inputStep2048, q15output, paramCountInputStep2048, (q15)SNR_THRESHOLD);
#endif

       }

    printf("\n== mips_rfft_q15 IFTStep_2048 check done  == \n\n");
#endif
    // =====================
    printf("== mips_rfft_q15 Step_4096 test ==  \n");

    memcpy(q15changed, q15inputStep4096, sizeof(q15) * paramCountInputStep4096);

    mips_rfft_init_q15(&instRfftQ15, 4096, 0, 1);
    ifft = 0;

    mips_rfft_q15(&(instRfftQ15), q15changed, q15overhead);

    printf("mips_rfft_q15 Step_4096 finish \n");

    printf("mips_rfft_q15 Step_4096 checking \n\n");
    if (ifft)
    {
        for (unsigned long i = 0; i < 2 * paramCountRefStep4096; i++)
        {
            q15overhead[i] = q15overhead[i] << scaling;
        }
    }

    memcpy(q15output, q15overhead, sizeof(q15) * paramCountRefStep4096);

    if (ifft)
    {
#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileStep4096, q15output, 0, (q15)RIFFT_SNR_THRESHOLD);
#else
	snr_check_special_q15(q15refStep4096, q15output, paramCountRefStep4096, (q15)RIFFT_SNR_THRESHOLD);
#endif

    }
    else
    {
#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileStep4096, q15output, 0, (q15)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15refStep4096, q15output, paramCountRefStep4096, (q15)SNR_THRESHOLD);
#endif

    }

    printf("\n== mips_rfft_q15 Step_4096 check done  == \n\n");

#if 0
// =====================
    printf("== mips_rfft_q15 IFTStep_4096 test ==  \n");

        memcpy(q15changed,q15IFTinputStep4096,sizeof(q15)*IFTparamCountInputStep4096);

        mips_rfft_init_q15(&instRfftQ15 ,4096,1,1);
        ifft = 1;
        scaling = 12;
   
        mips_rfft_q15(&(instRfftQ15), q15changed, q15overhead);

    printf("mips_rfft_q15 IFTStep_4096 finish \n");

    printf("mips_rfft_q15 IFTStep_4096 checking \n\n");
    if (ifft)
       {
          for(unsigned long i = 0;i < 2*paramCountInputStep4096; i++)
          {
              q15overhead[i] = q15overhead[i] << scaling;
          }
       }

       memcpy(q15output,q15overhead,sizeof(q15)*paramCountInputStep4096);

       if (ifft)
       {
  #if defined(NOT_EMBEDDED)
	snr_check_q15(q15inputFileStep4096, q15output, 0, (q15)RIFFT_SNR_THRESHOLD);
#else
	snr_check_special_q15(q15inputStep4096, q15output, paramCountInputStep4096, (q15)RIFFT_SNR_THRESHOLD);
#endif

       }
       else
       {
 #if defined(NOT_EMBEDDED)
	snr_check_q15(q15inputFileStep4096, q15output, 0, (q15)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15inputStep4096, q15output, paramCountInputStep4096, (q15)SNR_THRESHOLD);
#endif

       }

    printf("\n== mips_rfft_q15 IFTStep_4096 check done  == \n\n");
#endif
    return 0;
}