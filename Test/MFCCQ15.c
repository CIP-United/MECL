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


#define SNR_THRESHOLD 34
#define ABS_ERROR ((q15)30)
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

    q15 q15inputNoise256[MAX_SIZE] = {0};
    q15 q15inputNoise512[MAX_SIZE] = {0};
    q15 q15inputNoise1024[MAX_SIZE] = {0};

    int paramCountInputSine256 = 0;
    int paramCountInputSine512 = 0;
    int paramCountInputSine1024 = 0;

    q15 q15inputSine256[MAX_SIZE] = {0};
    q15 q15inputSine512[MAX_SIZE] = {0};
    q15 q15inputSine1024[MAX_SIZE] = {0};

    // file name. file path max length is 255, so use 255.
#if defined(NOT_EMBEDDED)
	char q15inputFileNoise256[255] = {0};
#else
	void *q15inputFileNoise256;
	int q15inputFileNoise256Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15inputFileNoise512[255] = {0};
#else
	void *q15inputFileNoise512;
	int q15inputFileNoise512Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15inputFileNoise1024[255] = {0};
#else
	void *q15inputFileNoise1024;
	int q15inputFileNoise1024Len = 0;
#endif


#if defined(NOT_EMBEDDED)
	char q15inputFileSine256[255] = {0};
#else
	void *q15inputFileSine256;
	int q15inputFileSine256Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15inputFileSine512[255] = {0};
#else
	void *q15inputFileSine512;
	int q15inputFileSine512Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15inputFileSine1024[255] = {0};
#else
	void *q15inputFileSine1024;
	int q15inputFileSine1024Len = 0;
#endif


#if defined(NOT_EMBEDDED)
	char q15referenceFileNoise256[255] = {0};
#else
	void *q15referenceFileNoise256;
	int q15referenceFileNoise256Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15referenceFileNoise512[255] = {0};
#else
	void *q15referenceFileNoise512;
	int q15referenceFileNoise512Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15referenceFileNoise1024[255] = {0};
#else
	void *q15referenceFileNoise1024;
	int q15referenceFileNoise1024Len = 0;
#endif


#if defined(NOT_EMBEDDED)
	char q15referenceFileSine256[255] = {0};
#else
	void *q15referenceFileSine256;
	int q15referenceFileSine256Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15referenceFileSine512[255] = {0};
#else
	void *q15referenceFileSine512;
	int q15referenceFileSine512Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char q15referenceFileSine1024[255] = {0};
#else
	void *q15referenceFileSine1024;
	int q15referenceFileSine1024Len = 0;
#endif


    // set file name by snprintf
    // relative path, function path, filename
#if defined(NOT_EMBEDDED)
	snprintf(q15inputFileNoise256, sizeof(q15inputFileNoise256), "%s%s%s", Patterns_PATH, MFCCQ15, "MFCCNoiseInput_256_1_q15.txt");
#else
	q15inputFileNoise256 = MFCCQ15_MFCCNoiseInput_256_1_q15;
	q15inputFileNoise256Len = sizeof(MFCCQ15_MFCCNoiseInput_256_1_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15inputFileNoise512, sizeof(q15inputFileNoise512), "%s%s%s", Patterns_PATH, MFCCQ15, "MFCCNoiseInput_512_1_q15.txt");
#else
	q15inputFileNoise512 = MFCCQ15_MFCCNoiseInput_512_1_q15;
	q15inputFileNoise512Len = sizeof(MFCCQ15_MFCCNoiseInput_512_1_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15inputFileNoise1024, sizeof(q15inputFileNoise1024), "%s%s%s", Patterns_PATH, MFCCQ15, "MFCCNoiseInput_1024_1_q15.txt");
#else
	q15inputFileNoise1024 = MFCCQ15_MFCCNoiseInput_1024_1_q15;
	q15inputFileNoise1024Len = sizeof(MFCCQ15_MFCCNoiseInput_1024_1_q15);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(q15referenceFileNoise256, sizeof(q15referenceFileNoise256), "%s%s%s", Patterns_PATH, MFCCQ15, "MFCCNoiseRef_256_1_q15.txt");
#else
	q15referenceFileNoise256 = MFCCQ15_MFCCNoiseRef_256_1_q15;
	q15referenceFileNoise256Len = sizeof(MFCCQ15_MFCCNoiseRef_256_1_q15)/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15referenceFileNoise512, sizeof(q15referenceFileNoise512), "%s%s%s", Patterns_PATH, MFCCQ15, "MFCCNoiseRef_512_1_q15.txt");
#else
	q15referenceFileNoise512 = MFCCQ15_MFCCNoiseRef_512_1_q15;
	q15referenceFileNoise512Len = sizeof(MFCCQ15_MFCCNoiseRef_512_1_q15)/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15referenceFileNoise1024, sizeof(q15referenceFileNoise1024), "%s%s%s", Patterns_PATH, MFCCQ15, "MFCCNoiseRef_1024_1_q15.txt");
#else
	q15referenceFileNoise1024 = MFCCQ15_MFCCNoiseRef_1024_1_q15;
	q15referenceFileNoise1024Len = sizeof(MFCCQ15_MFCCNoiseRef_1024_1_q15)/sizeof(q15);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(q15inputFileSine256, sizeof(q15inputFileSine256), "%s%s%s", Patterns_PATH, MFCCQ15, "MFCCSineInput_256_1_q15.txt");
#else
	q15inputFileSine256 = MFCCQ15_MFCCSineInput_256_1_q15;
	q15inputFileSine256Len = sizeof(MFCCQ15_MFCCSineInput_256_1_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15inputFileSine512, sizeof(q15inputFileSine512), "%s%s%s", Patterns_PATH, MFCCQ15, "MFCCSineInput_512_1_q15.txt");
#else
	q15inputFileSine512 = MFCCQ15_MFCCSineInput_512_1_q15;
	q15inputFileSine512Len = sizeof(MFCCQ15_MFCCSineInput_512_1_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15inputFileSine1024, sizeof(q15inputFileSine1024), "%s%s%s", Patterns_PATH, MFCCQ15, "MFCCSineInput_1024_1_q15.txt");
#else
	q15inputFileSine1024 = MFCCQ15_MFCCSineInput_1024_1_q15;
	q15inputFileSine1024Len = sizeof(MFCCQ15_MFCCSineInput_1024_1_q15);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(q15referenceFileSine256, sizeof(q15referenceFileSine256), "%s%s%s", Patterns_PATH, MFCCQ15, "MFCCSineRef_256_1_q15.txt");
#else
	q15referenceFileSine256 = MFCCQ15_MFCCSineRef_256_1_q15;
	q15referenceFileSine256Len = sizeof(MFCCQ15_MFCCSineRef_256_1_q15)/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15referenceFileSine512, sizeof(q15referenceFileSine512), "%s%s%s", Patterns_PATH, MFCCQ15, "MFCCSineRef_512_1_q15.txt");
#else
	q15referenceFileSine512 = MFCCQ15_MFCCSineRef_512_1_q15;
	q15referenceFileSine512Len = sizeof(MFCCQ15_MFCCSineRef_512_1_q15)/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(q15referenceFileSine1024, sizeof(q15referenceFileSine1024), "%s%s%s", Patterns_PATH, MFCCQ15, "MFCCSineRef_1024_1_q15.txt");
#else
	q15referenceFileSine1024 = MFCCQ15_MFCCSineRef_1024_1_q15;
	q15referenceFileSine1024Len = sizeof(MFCCQ15_MFCCSineRef_1024_1_q15)/sizeof(q15);
#endif


    // load input data
#if defined(NOT_EMBEDDED)
	load_data_q15(q15inputFileNoise256, &paramCountInputNoise256, q15inputNoise256);
#else
	paramCountInputNoise256 = q15inputFileNoise256Len;
	load_data_q15(q15inputFileNoise256, paramCountInputNoise256, q15inputNoise256);
	paramCountInputNoise256 = paramCountInputNoise256/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15inputFileNoise512, &paramCountInputNoise512, q15inputNoise512);
#else
	paramCountInputNoise512 = q15inputFileNoise512Len;
	load_data_q15(q15inputFileNoise512, paramCountInputNoise512, q15inputNoise512);
	paramCountInputNoise512 = paramCountInputNoise512/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15inputFileNoise1024, &paramCountInputNoise1024, q15inputNoise1024);
#else
	paramCountInputNoise1024 = q15inputFileNoise1024Len;
	load_data_q15(q15inputFileNoise1024, paramCountInputNoise1024, q15inputNoise1024);
	paramCountInputNoise1024 = paramCountInputNoise1024/sizeof(q15);
#endif


#if defined(NOT_EMBEDDED)
	load_data_q15(q15inputFileSine256, &paramCountInputSine256, q15inputSine256);
#else
	paramCountInputSine256 = q15inputFileSine256Len;
	load_data_q15(q15inputFileSine256, paramCountInputSine256, q15inputSine256);
	paramCountInputSine256 = paramCountInputSine256/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15inputFileSine512, &paramCountInputSine512, q15inputSine512);
#else
	paramCountInputSine512 = q15inputFileSine512Len;
	load_data_q15(q15inputFileSine512, paramCountInputSine512, q15inputSine512);
	paramCountInputSine512 = paramCountInputSine512/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(q15inputFileSine1024, &paramCountInputSine1024, q15inputSine1024);
#else
	paramCountInputSine1024 = q15inputFileSine1024Len;
	load_data_q15(q15inputFileSine1024, paramCountInputSine1024, q15inputSine1024);
	paramCountInputSine1024 = paramCountInputSine1024/sizeof(q15);
#endif


    q15 q15output[MAX_SIZE] = {0};
    q15 q15tmpinp[MAX_SIZE] = {0};
    q31 q31tmpp[MAX_SIZE] = {0};

    uint32_t fftLen;
    unsigned long nb = MAX_NB_SAMPLES;
    
    mips_mfcc_instance_q15 mfcc;

// =====================
    printf("== mips_mfcc_q15 Noise_256 test ==  \n");

    nb = 256;
    fftLen = nb;

    mips_mfcc_init_q15(&mfcc,
                    nb,20,13,mfcc_dct_coefs_config1_q15,
                    mfcc_filter_pos_config3_q15,mfcc_filter_len_config3_q15,
                    mfcc_filter_coefs_config3_q15,
                    mfcc_window_coefs_config3_q15);
    memcpy((void*)q15tmpinp,(void*)q15inputNoise256,sizeof(q15)*fftLen);
    mips_mfcc_q15(&mfcc,q15tmpinp,q15output,q31tmpp);

    printf("mips_mfcc_q15 Noise_256 finish \n");

    printf("mips_mfcc_q15 Noise_256 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileNoise256, q15output, 0, (q15)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15referenceFileNoise256, q15output, q15referenceFileNoise256Len, (q15)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(q15referenceFileNoise256, q15output, 0, ABS_ERROR);
#else
	near_check_special_q15(q15referenceFileNoise256, q15output, q15referenceFileNoise256Len, ABS_ERROR);
#endif

    printf("\n== mips_mfcc_q15 Noise_256 check done  == \n\n");

// =====================
    printf("== mips_mfcc_q15 Noise_512 test ==  \n");

    nb = 512;
    fftLen = nb;

    mips_mfcc_init_q15(&mfcc,
                      nb,20,13,mfcc_dct_coefs_config1_q15,
                      mfcc_filter_pos_config2_q15,mfcc_filter_len_config2_q15,
                      mfcc_filter_coefs_config2_q15,
                      mfcc_window_coefs_config2_q15);
    memcpy((void*)q15tmpinp,(void*)q15inputNoise512,sizeof(q15)*fftLen);
    mips_mfcc_q15(&mfcc,q15tmpinp,q15output,q31tmpp);

    printf("mips_mfcc_q15 Noise_512 finish \n");

    printf("mips_mfcc_q15 Noise_512 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileNoise512, q15output, 0, (q15)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15referenceFileNoise512, q15output, q15referenceFileNoise512Len, (q15)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(q15referenceFileNoise512, q15output, 0, ABS_ERROR);
#else
	near_check_special_q15(q15referenceFileNoise512, q15output, q15referenceFileNoise512Len, ABS_ERROR);
#endif

    printf("\n== mips_mfcc_q15 Noise_512 check done  == \n\n");

// =====================
    printf("== mips_mfcc_q15 Noise_1024 test ==  \n");

    nb = 1024;
    fftLen = nb;

    mips_mfcc_init_q15(&mfcc,
                      nb,20,13,mfcc_dct_coefs_config1_q15,
                      mfcc_filter_pos_config1_q15,mfcc_filter_len_config1_q15,
                      mfcc_filter_coefs_config1_q15,
                      mfcc_window_coefs_config1_q15);
    memcpy((void*)q15tmpinp,(void*)q15inputNoise1024,sizeof(q15)*fftLen);
    mips_mfcc_q15(&mfcc,q15tmpinp,q15output,q31tmpp);

    printf("mips_mfcc_q15 Noise_1024 finish \n");

    printf("mips_mfcc_q15 Noise_1024 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileNoise1024, q15output, 0, (q15)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15referenceFileNoise1024, q15output, q15referenceFileNoise1024Len, (q15)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(q15referenceFileNoise1024, q15output, 0, ABS_ERROR);
#else
	near_check_special_q15(q15referenceFileNoise1024, q15output, q15referenceFileNoise1024Len, ABS_ERROR);
#endif

    printf("\n== mips_mfcc_q15 Noise_1024 check done  == \n\n");

    q15 q15sineoutput[MAX_SIZE] = {0};
    q15 q15sinnetmpinp[MAX_SIZE] = {0};
    q31 q31sinetmpp[MAX_SIZE] = {0};
// =====================
    printf("== mips_mfcc_q15 Sine_256 test ==  \n");

    nb = 256;
    fftLen = nb;

    mips_mfcc_init_q15(&mfcc,
                    nb,20,13,mfcc_dct_coefs_config1_q15,
                    mfcc_filter_pos_config3_q15,mfcc_filter_len_config3_q15,
                    mfcc_filter_coefs_config3_q15,
                    mfcc_window_coefs_config3_q15);
    memcpy((void*)q15sinnetmpinp,(void*)q15inputSine256,sizeof(q15)*fftLen);
    mips_mfcc_q15(&mfcc,q15sinnetmpinp,q15sineoutput,q31sinetmpp);

    printf("mips_mfcc_q15 Sine_256 finish \n");

    printf("mips_mfcc_q15 Sine_256 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileSine256, q15sineoutput, 0, (q15)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15referenceFileSine256, q15sineoutput, q15referenceFileSine256Len, (q15)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(q15referenceFileSine256, q15sineoutput, 0, ABS_ERROR);
#else
	near_check_special_q15(q15referenceFileSine256, q15sineoutput, q15referenceFileSine256Len, ABS_ERROR);
#endif

    printf("\n== mips_mfcc_q15 Sine_256 check done  == \n\n");

// =====================
    printf("== mips_mfcc_q15 Sine_512 test ==  \n");

    nb = 512;
    fftLen = nb;

    mips_mfcc_init_q15(&mfcc,
                      nb,20,13,mfcc_dct_coefs_config1_q15,
                      mfcc_filter_pos_config2_q15,mfcc_filter_len_config2_q15,
                      mfcc_filter_coefs_config2_q15,
                      mfcc_window_coefs_config2_q15);
    memcpy((void*)q15sinnetmpinp,(void*)q15inputSine512,sizeof(q15)*fftLen);
    mips_mfcc_q15(&mfcc,q15sinnetmpinp,q15sineoutput,q31sinetmpp);

    printf("mips_mfcc_q15 Sine_512 finish \n");

    printf("mips_mfcc_q15 Sine_512 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileSine512, q15sineoutput, 0, (q15)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15referenceFileSine512, q15sineoutput, q15referenceFileSine512Len, (q15)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(q15referenceFileSine512, q15sineoutput, 0, ABS_ERROR);
#else
	near_check_special_q15(q15referenceFileSine512, q15sineoutput, q15referenceFileSine512Len, ABS_ERROR);
#endif

    printf("\n== mips_mfcc_q15 Sine_512 check done  == \n\n");

// =====================
    printf("== mips_mfcc_q15 Sine_1024 test ==  \n");

    nb = 1024;
    fftLen = nb;

    mips_mfcc_init_q15(&mfcc,
                      nb,20,13,mfcc_dct_coefs_config1_q15,
                      mfcc_filter_pos_config1_q15,mfcc_filter_len_config1_q15,
                      mfcc_filter_coefs_config1_q15,
                      mfcc_window_coefs_config1_q15);
    memcpy((void*)q15sinnetmpinp,(void*)q15inputSine1024,sizeof(q15)*fftLen);
    mips_mfcc_q15(&mfcc,q15sinnetmpinp,q15sineoutput,q31sinetmpp);

    printf("mips_mfcc_q15 Sine_1024 finish \n");

    printf("mips_mfcc_q15 Sine_1024 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_q15(q15referenceFileSine1024, q15sineoutput, 0, (q15)SNR_THRESHOLD);
#else
	snr_check_special_q15(q15referenceFileSine1024, q15sineoutput, q15referenceFileSine1024Len, (q15)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(q15referenceFileSine1024, q15sineoutput, 0, ABS_ERROR);
#else
	near_check_special_q15(q15referenceFileSine1024, q15sineoutput, q15referenceFileSine1024Len, ABS_ERROR);
#endif

    printf("\n== mips_mfcc_q15 Sine_1024 check done  == \n\n");

    return 0;
}
