#include "dsp/transform_functions.h"
#include "dsp/statistics_functions.h"
#include "dsp/basic_math_functions.h"
#include "dsp/complex_math_functions.h"
#include "dsp/fast_math_functions.h"
#include "dsp/matrix_functions.h"
#include "mfccdata.h"
#include "mfccdata.c"
#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif


#define SNR_THRESHOLD 66
#define ABS_ERROR ((q31)49000)
#define MAX_NB_SAMPLES 0
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

    int paramCountInputNoise256 = 0;
    int paramCountInputNoise512 = 0;
    int paramCountInputNoise1024 = 0;

    q31 q31inputNoise256[MAX_SIZE] = {0};
    q31 q31inputNoise512[MAX_SIZE] = {0};
    q31 q31inputNoise1024[MAX_SIZE] = {0};

    int paramCountInputSine256 = 0;
    int paramCountInputSine512 = 0;
    int paramCountInputSine1024 = 0;

    q31 q31inputSine256[MAX_SIZE] = {0};
    q31 q31inputSine512[MAX_SIZE] = {0};
    q31 q31inputSine1024[MAX_SIZE] = {0};

    // file name. file path max length is 255, so use 255.
#if defined(NOT_EMBEDDED)
	char q31inputFileNoise256[255] = {0};
#else
	void *q31inputFileNoise256;
	int q31inputFileNoise256Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31inputFileNoise512[255] = {0};
#else
	void *q31inputFileNoise512;
	int q31inputFileNoise512Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31inputFileNoise1024[255] = {0};
#else
	void *q31inputFileNoise1024;
	int q31inputFileNoise1024Len = 0;
#endif


#if defined(NOT_EMBEDDED)
	char q31inputFileSine256[255] = {0};
#else
	void *q31inputFileSine256;
	int q31inputFileSine256Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31inputFileSine512[255] = {0};
#else
	void *q31inputFileSine512;
	int q31inputFileSine512Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31inputFileSine1024[255] = {0};
#else
	void *q31inputFileSine1024;
	int q31inputFileSine1024Len = 0;
#endif


#if defined(NOT_EMBEDDED)
	char q31referenceFileNoise256[255] = {0};
#else
	void *q31referenceFileNoise256;
	int q31referenceFileNoise256Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31referenceFileNoise512[255] = {0};
#else
	void *q31referenceFileNoise512;
	int q31referenceFileNoise512Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31referenceFileNoise1024[255] = {0};
#else
	void *q31referenceFileNoise1024;
	int q31referenceFileNoise1024Len = 0;
#endif


#if defined(NOT_EMBEDDED)
	char q31referenceFileSine256[255] = {0};
#else
	void *q31referenceFileSine256;
	int q31referenceFileSine256Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31referenceFileSine512[255] = {0};
#else
	void *q31referenceFileSine512;
	int q31referenceFileSine512Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q31referenceFileSine1024[255] = {0};
#else
	void *q31referenceFileSine1024;
	int q31referenceFileSine1024Len = 0;
#endif


    // set file name by snprintf
    // relative path, function path, filename
#if defined(NOT_EMBEDDED)
	snprintf(q31inputFileNoise256, sizeof(q31inputFileNoise256), "%s%s%s", Patterns_PATH, MFCCQ31, "MFCCNoiseInput_256_1_q31.txt");
#else
	q31inputFileNoise256 = MFCCQ31_MFCCNoiseInput_256_1_q31;
	q31inputFileNoise256Len = sizeof(MFCCQ31_MFCCNoiseInput_256_1_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31inputFileNoise512, sizeof(q31inputFileNoise512), "%s%s%s", Patterns_PATH, MFCCQ31, "MFCCNoiseInput_512_1_q31.txt");
#else
	q31inputFileNoise512 = MFCCQ31_MFCCNoiseInput_512_1_q31;
	q31inputFileNoise512Len = sizeof(MFCCQ31_MFCCNoiseInput_512_1_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31inputFileNoise1024, sizeof(q31inputFileNoise1024), "%s%s%s", Patterns_PATH, MFCCQ31, "MFCCNoiseInput_1024_1_q31.txt");
#else
	q31inputFileNoise1024 = MFCCQ31_MFCCNoiseInput_1024_1_q31;
	q31inputFileNoise1024Len = sizeof(MFCCQ31_MFCCNoiseInput_1024_1_q31);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(q31referenceFileNoise256, sizeof(q31referenceFileNoise256), "%s%s%s", Patterns_PATH, MFCCQ31, "MFCCNoiseRef_256_1_q31.txt");
#else
	q31referenceFileNoise256 = MFCCQ31_MFCCNoiseRef_256_1_q31;
	q31referenceFileNoise256Len = sizeof(MFCCQ31_MFCCNoiseRef_256_1_q31)/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31referenceFileNoise512, sizeof(q31referenceFileNoise512), "%s%s%s", Patterns_PATH, MFCCQ31, "MFCCNoiseRef_512_1_q31.txt");
#else
	q31referenceFileNoise512 = MFCCQ31_MFCCNoiseRef_512_1_q31;
	q31referenceFileNoise512Len = sizeof(MFCCQ31_MFCCNoiseRef_512_1_q31)/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31referenceFileNoise1024, sizeof(q31referenceFileNoise1024), "%s%s%s", Patterns_PATH, MFCCQ31, "MFCCNoiseRef_1024_1_q31.txt");
#else
	q31referenceFileNoise1024 = MFCCQ31_MFCCNoiseRef_1024_1_q31;
	q31referenceFileNoise1024Len = sizeof(MFCCQ31_MFCCNoiseRef_1024_1_q31)/sizeof(q31);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(q31inputFileSine256, sizeof(q31inputFileSine256), "%s%s%s", Patterns_PATH, MFCCQ31, "MFCCSineInput_256_1_q31.txt");
#else
	q31inputFileSine256 = MFCCQ31_MFCCSineInput_256_1_q31;
	q31inputFileSine256Len = sizeof(MFCCQ31_MFCCSineInput_256_1_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31inputFileSine512, sizeof(q31inputFileSine512), "%s%s%s", Patterns_PATH, MFCCQ31, "MFCCSineInput_512_1_q31.txt");
#else
	q31inputFileSine512 = MFCCQ31_MFCCSineInput_512_1_q31;
	q31inputFileSine512Len = sizeof(MFCCQ31_MFCCSineInput_512_1_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31inputFileSine1024, sizeof(q31inputFileSine1024), "%s%s%s", Patterns_PATH, MFCCQ31, "MFCCSineInput_1024_1_q31.txt");
#else
	q31inputFileSine1024 = MFCCQ31_MFCCSineInput_1024_1_q31;
	q31inputFileSine1024Len = sizeof(MFCCQ31_MFCCSineInput_1024_1_q31);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(q31referenceFileSine256, sizeof(q31referenceFileSine256), "%s%s%s", Patterns_PATH, MFCCQ31, "MFCCSineRef_256_1_q31.txt");
#else
	q31referenceFileSine256 = MFCCQ31_MFCCSineRef_256_1_q31;
	q31referenceFileSine256Len = sizeof(MFCCQ31_MFCCSineRef_256_1_q31)/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31referenceFileSine512, sizeof(q31referenceFileSine512), "%s%s%s", Patterns_PATH, MFCCQ31, "MFCCSineRef_512_1_q31.txt");
#else
	q31referenceFileSine512 = MFCCQ31_MFCCSineRef_512_1_q31;
	q31referenceFileSine512Len = sizeof(MFCCQ31_MFCCSineRef_512_1_q31)/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q31referenceFileSine1024, sizeof(q31referenceFileSine1024), "%s%s%s", Patterns_PATH, MFCCQ31, "MFCCSineRef_1024_1_q31.txt");
#else
	q31referenceFileSine1024 = MFCCQ31_MFCCSineRef_1024_1_q31;
	q31referenceFileSine1024Len = sizeof(MFCCQ31_MFCCSineRef_1024_1_q31)/sizeof(q31);
#endif


    // load input data
#if defined(NOT_EMBEDDED)
	load_data_q31(q31inputFileNoise256, &paramCountInputNoise256, q31inputNoise256);
#else
	paramCountInputNoise256 = q31inputFileNoise256Len;
	load_data_q31(q31inputFileNoise256, paramCountInputNoise256, q31inputNoise256);
	paramCountInputNoise256 = paramCountInputNoise256/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(q31inputFileNoise512, &paramCountInputNoise512, q31inputNoise512);
#else
	paramCountInputNoise512 = q31inputFileNoise512Len;
	load_data_q31(q31inputFileNoise512, paramCountInputNoise512, q31inputNoise512);
	paramCountInputNoise512 = paramCountInputNoise512/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(q31inputFileNoise1024, &paramCountInputNoise1024, q31inputNoise1024);
#else
	paramCountInputNoise1024 = q31inputFileNoise1024Len;
	load_data_q31(q31inputFileNoise1024, paramCountInputNoise1024, q31inputNoise1024);
	paramCountInputNoise1024 = paramCountInputNoise1024/sizeof(q31);
#endif


#if defined(NOT_EMBEDDED)
	load_data_q31(q31inputFileSine256, &paramCountInputSine256, q31inputSine256);
#else
	paramCountInputSine256 = q31inputFileSine256Len;
	load_data_q31(q31inputFileSine256, paramCountInputSine256, q31inputSine256);
	paramCountInputSine256 = paramCountInputSine256/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(q31inputFileSine512, &paramCountInputSine512, q31inputSine512);
#else
	paramCountInputSine512 = q31inputFileSine512Len;
	load_data_q31(q31inputFileSine512, paramCountInputSine512, q31inputSine512);
	paramCountInputSine512 = paramCountInputSine512/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(q31inputFileSine1024, &paramCountInputSine1024, q31inputSine1024);
#else
	paramCountInputSine1024 = q31inputFileSine1024Len;
	load_data_q31(q31inputFileSine1024, paramCountInputSine1024, q31inputSine1024);
	paramCountInputSine1024 = paramCountInputSine1024/sizeof(q31);
#endif


    q31 q31output[MAX_SIZE] = {0};
    q31 q31tmpinp[MAX_SIZE] = {0};
    q31 q31tmpp[MAX_SIZE] = {0};

    uint32_t fftLen;
    unsigned long nb = MAX_NB_SAMPLES;
    
    mips_mfcc_instance_q31 mfcc;

// =====================
    printf("== mips_mfcc_q31 Noise_256 test ==  \n");

    nb = 256;
    fftLen = nb;

    mips_mfcc_init_q31(&mfcc,
                    nb,20,13,mfcc_dct_coefs_config1_q31,
                    mfcc_filter_pos_config3_q31,mfcc_filter_len_config3_q31,
                    mfcc_filter_coefs_config3_q31,
                    mfcc_window_coefs_config3_q31);
    memcpy((void*)q31tmpinp,(void*)q31inputNoise256,sizeof(q31)*fftLen);
    mips_mfcc_q31(&mfcc,q31tmpinp,q31output,q31tmpp);

    printf("mips_mfcc_q31 Noise_256 finish \n");

    printf("mips_mfcc_q31 Noise_256 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_q31(q31referenceFileNoise256, q31output, 0, (q31)SNR_THRESHOLD);
#else
	snr_check_special_q31(q31referenceFileNoise256, q31output, q31referenceFileNoise256Len, (q31)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q31(q31referenceFileNoise256, q31output, 0, ABS_ERROR);
#else
	near_check_special_q31(q31referenceFileNoise256, q31output, q31referenceFileNoise256Len, ABS_ERROR);
#endif

    printf("\n== mips_mfcc_q31 Noise_256 check done  == \n\n");

// =====================
    printf("== mips_mfcc_q31 Noise_512 test ==  \n");

    nb = 512;
    fftLen = nb;

    mips_mfcc_init_q31(&mfcc,
                      nb,20,13,mfcc_dct_coefs_config1_q31,
                      mfcc_filter_pos_config2_q31,mfcc_filter_len_config2_q31,
                      mfcc_filter_coefs_config2_q31,
                      mfcc_window_coefs_config2_q31);
    memcpy((void*)q31tmpinp,(void*)q31inputNoise512,sizeof(q31)*fftLen);
    mips_mfcc_q31(&mfcc,q31tmpinp,q31output,q31tmpp);

    printf("mips_mfcc_q31 Noise_512 finish \n");

    printf("mips_mfcc_q31 Noise_512 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_q31(q31referenceFileNoise512, q31output, 0, (q31)SNR_THRESHOLD);
#else
	snr_check_special_q31(q31referenceFileNoise512, q31output, q31referenceFileNoise512Len, (q31)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q31(q31referenceFileNoise512, q31output, 0, ABS_ERROR);
#else
	near_check_special_q31(q31referenceFileNoise512, q31output, q31referenceFileNoise512Len, ABS_ERROR);
#endif

    printf("\n== mips_mfcc_q31 Noise_512 check done  == \n\n");

// =====================
    printf("== mips_mfcc_q31 Noise_1024 test ==  \n");

    nb = 1024;
    fftLen = nb;

    mips_mfcc_init_q31(&mfcc,
                      nb,20,13,mfcc_dct_coefs_config1_q31,
                      mfcc_filter_pos_config1_q31,mfcc_filter_len_config1_q31,
                      mfcc_filter_coefs_config1_q31,
                      mfcc_window_coefs_config1_q31);
    memcpy((void*)q31tmpinp,(void*)q31inputNoise1024,sizeof(q31)*fftLen);
    mips_mfcc_q31(&mfcc,q31tmpinp,q31output,q31tmpp);

    printf("mips_mfcc_q31 Noise_1024 finish \n");

    printf("mips_mfcc_q31 Noise_1024 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_q31(q31referenceFileNoise1024, q31output, 0, (q31)SNR_THRESHOLD);
#else
	snr_check_special_q31(q31referenceFileNoise1024, q31output, q31referenceFileNoise1024Len, (q31)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q31(q31referenceFileNoise1024, q31output, 0, ABS_ERROR);
#else
	near_check_special_q31(q31referenceFileNoise1024, q31output, q31referenceFileNoise1024Len, ABS_ERROR);
#endif

    printf("\n== mips_mfcc_q31 Noise_1024 check done  == \n\n");

    q31 q31sineoutput[MAX_SIZE] = {0};
    q31 q31sinnetmpinp[MAX_SIZE] = {0};
    q31 q31sinetmpp[MAX_SIZE] = {0};
// =====================
    printf("== mips_mfcc_q31 Sine_256 test ==  \n");

    nb = 256;
    fftLen = nb;

    mips_mfcc_init_q31(&mfcc,
                    nb,20,13,mfcc_dct_coefs_config1_q31,
                    mfcc_filter_pos_config3_q31,mfcc_filter_len_config3_q31,
                    mfcc_filter_coefs_config3_q31,
                    mfcc_window_coefs_config3_q31);
    memcpy((void*)q31sinnetmpinp,(void*)q31inputSine256,sizeof(q31)*fftLen);
    mips_mfcc_q31(&mfcc,q31sinnetmpinp,q31sineoutput,q31sinetmpp);

    printf("mips_mfcc_q31 Sine_256 finish \n");

    printf("mips_mfcc_q31 Sine_256 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_q31(q31referenceFileSine256, q31sineoutput, 0, (q31)SNR_THRESHOLD);
#else
	snr_check_special_q31(q31referenceFileSine256, q31sineoutput, q31referenceFileSine256Len, (q31)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q31(q31referenceFileSine256, q31sineoutput, 0, ABS_ERROR);
#else
	near_check_special_q31(q31referenceFileSine256, q31sineoutput, q31referenceFileSine256Len, ABS_ERROR);
#endif

    printf("\n== mips_mfcc_q31 Sine_256 check done  == \n\n");

// =====================
    printf("== mips_mfcc_q31 Sine_512 test ==  \n");

    nb = 512;
    fftLen = nb;

    mips_mfcc_init_q31(&mfcc,
                      nb,20,13,mfcc_dct_coefs_config1_q31,
                      mfcc_filter_pos_config2_q31,mfcc_filter_len_config2_q31,
                      mfcc_filter_coefs_config2_q31,
                      mfcc_window_coefs_config2_q31);
    memcpy((void*)q31sinnetmpinp,(void*)q31inputSine512,sizeof(q31)*fftLen);
    mips_mfcc_q31(&mfcc,q31sinnetmpinp,q31sineoutput,q31sinetmpp);

    printf("mips_mfcc_q31 Sine_512 finish \n");

    printf("mips_mfcc_q31 Sine_512 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_q31(q31referenceFileSine512, q31sineoutput, 0, (q31)SNR_THRESHOLD);
#else
	snr_check_special_q31(q31referenceFileSine512, q31sineoutput, q31referenceFileSine512Len, (q31)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q31(q31referenceFileSine512, q31sineoutput, 0, ABS_ERROR);
#else
	near_check_special_q31(q31referenceFileSine512, q31sineoutput, q31referenceFileSine512Len, ABS_ERROR);
#endif

    printf("\n== mips_mfcc_q31 Sine_512 check done  == \n\n");

// =====================
    printf("== mips_mfcc_q31 Sine_1024 test ==  \n");

    nb = 1024;
    fftLen = nb;

    mips_mfcc_init_q31(&mfcc,
                      nb,20,13,mfcc_dct_coefs_config1_q31,
                      mfcc_filter_pos_config1_q31,mfcc_filter_len_config1_q31,
                      mfcc_filter_coefs_config1_q31,
                      mfcc_window_coefs_config1_q31);
    memcpy((void*)q31sinnetmpinp,(void*)q31inputSine1024,sizeof(q31)*fftLen);
    mips_mfcc_q31(&mfcc,q31sinnetmpinp,q31sineoutput,q31sinetmpp);

    printf("mips_mfcc_q31 Sine_1024 finish \n");

    printf("mips_mfcc_q31 Sine_1024 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_q31(q31referenceFileSine1024, q31sineoutput, 0, (q31)SNR_THRESHOLD);
#else
	snr_check_special_q31(q31referenceFileSine1024, q31sineoutput, q31referenceFileSine1024Len, (q31)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q31(q31referenceFileSine1024, q31sineoutput, 0, ABS_ERROR);
#else
	near_check_special_q31(q31referenceFileSine1024, q31sineoutput, q31referenceFileSine1024Len, ABS_ERROR);
#endif

    printf("\n== mips_mfcc_q31 Sine_1024 check done  == \n\n");

    return 0;
}
