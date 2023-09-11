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


#define SNR_THRESHOLD 115
#define REL_ERROR (1.2e-3)
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

    f32 f32inputNoise256[MAX_SIZE] = {0};
    f32 f32inputNoise512[MAX_SIZE] = {0};
    f32 f32inputNoise1024[MAX_SIZE] = {0};

    int paramCountInputSine256 = 0;
    int paramCountInputSine512 = 0;
    int paramCountInputSine1024 = 0;

    f32 f32inputSine256[MAX_SIZE] = {0};
    f32 f32inputSine512[MAX_SIZE] = {0};
    f32 f32inputSine1024[MAX_SIZE] = {0};

    // file name. file path max length is 255, so use 255.
#if defined(NOT_EMBEDDED)
	char f32inputFileNoise256[255] = {0};
#else
	void *f32inputFileNoise256;
	int f32inputFileNoise256Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32inputFileNoise512[255] = {0};
#else
	void *f32inputFileNoise512;
	int f32inputFileNoise512Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32inputFileNoise1024[255] = {0};
#else
	void *f32inputFileNoise1024;
	int f32inputFileNoise1024Len = 0;
#endif


#if defined(NOT_EMBEDDED)
	char f32inputFileSine256[255] = {0};
#else
	void *f32inputFileSine256;
	int f32inputFileSine256Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32inputFileSine512[255] = {0};
#else
	void *f32inputFileSine512;
	int f32inputFileSine512Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32inputFileSine1024[255] = {0};
#else
	void *f32inputFileSine1024;
	int f32inputFileSine1024Len = 0;
#endif


#if defined(NOT_EMBEDDED)
	char f32referenceFileNoise256[255] = {0};
#else
	void *f32referenceFileNoise256;
	int f32referenceFileNoise256Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32referenceFileNoise512[255] = {0};
#else
	void *f32referenceFileNoise512;
	int f32referenceFileNoise512Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32referenceFileNoise1024[255] = {0};
#else
	void *f32referenceFileNoise1024;
	int f32referenceFileNoise1024Len = 0;
#endif


#if defined(NOT_EMBEDDED)
	char f32referenceFileSine256[255] = {0};
#else
	void *f32referenceFileSine256;
	int f32referenceFileSine256Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32referenceFileSine512[255] = {0};
#else
	void *f32referenceFileSine512;
	int f32referenceFileSine512Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char f32referenceFileSine1024[255] = {0};
#else
	void *f32referenceFileSine1024;
	int f32referenceFileSine1024Len = 0;
#endif


    // set file name by snprintf
    // relative path, function path, filename
#if defined(NOT_EMBEDDED)
	snprintf(f32inputFileNoise256, sizeof(f32inputFileNoise256), "%s%s%s", Patterns_PATH, MFCCF32, "MFCCNoiseInput_256_1_f32.txt");
#else
	f32inputFileNoise256 = MFCCF32_MFCCNoiseInput_256_1_f32;
	f32inputFileNoise256Len = sizeof(MFCCF32_MFCCNoiseInput_256_1_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32inputFileNoise512, sizeof(f32inputFileNoise512), "%s%s%s", Patterns_PATH, MFCCF32, "MFCCNoiseInput_512_1_f32.txt");
#else
	f32inputFileNoise512 = MFCCF32_MFCCNoiseInput_512_1_f32;
	f32inputFileNoise512Len = sizeof(MFCCF32_MFCCNoiseInput_512_1_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32inputFileNoise1024, sizeof(f32inputFileNoise1024), "%s%s%s", Patterns_PATH, MFCCF32, "MFCCNoiseInput_1024_1_f32.txt");
#else
	f32inputFileNoise1024 = MFCCF32_MFCCNoiseInput_1024_1_f32;
	f32inputFileNoise1024Len = sizeof(MFCCF32_MFCCNoiseInput_1024_1_f32);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(f32referenceFileNoise256, sizeof(f32referenceFileNoise256), "%s%s%s", Patterns_PATH, MFCCF32, "MFCCNoiseRef_256_1_f32.txt");
#else
	f32referenceFileNoise256 = MFCCF32_MFCCNoiseRef_256_1_f32;
	f32referenceFileNoise256Len = sizeof(MFCCF32_MFCCNoiseRef_256_1_f32)/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32referenceFileNoise512, sizeof(f32referenceFileNoise512), "%s%s%s", Patterns_PATH, MFCCF32, "MFCCNoiseRef_512_1_f32.txt");
#else
	f32referenceFileNoise512 = MFCCF32_MFCCNoiseRef_512_1_f32;
	f32referenceFileNoise512Len = sizeof(MFCCF32_MFCCNoiseRef_512_1_f32)/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32referenceFileNoise1024, sizeof(f32referenceFileNoise1024), "%s%s%s", Patterns_PATH, MFCCF32, "MFCCNoiseRef_1024_1_f32.txt");
#else
	f32referenceFileNoise1024 = MFCCF32_MFCCNoiseRef_1024_1_f32;
	f32referenceFileNoise1024Len = sizeof(MFCCF32_MFCCNoiseRef_1024_1_f32)/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(f32inputFileSine256, sizeof(f32inputFileSine256), "%s%s%s", Patterns_PATH, MFCCF32, "MFCCSineInput_256_1_f32.txt");
#else
	f32inputFileSine256 = MFCCF32_MFCCSineInput_256_1_f32;
	f32inputFileSine256Len = sizeof(MFCCF32_MFCCSineInput_256_1_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32inputFileSine512, sizeof(f32inputFileSine512), "%s%s%s", Patterns_PATH, MFCCF32, "MFCCSineInput_512_1_f32.txt");
#else
	f32inputFileSine512 = MFCCF32_MFCCSineInput_512_1_f32;
	f32inputFileSine512Len = sizeof(MFCCF32_MFCCSineInput_512_1_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32inputFileSine1024, sizeof(f32inputFileSine1024), "%s%s%s", Patterns_PATH, MFCCF32, "MFCCSineInput_1024_1_f32.txt");
#else
	f32inputFileSine1024 = MFCCF32_MFCCSineInput_1024_1_f32;
	f32inputFileSine1024Len = sizeof(MFCCF32_MFCCSineInput_1024_1_f32);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(f32referenceFileSine256, sizeof(f32referenceFileSine256), "%s%s%s", Patterns_PATH, MFCCF32, "MFCCSineRef_256_1_f32.txt");
#else
	f32referenceFileSine256 = MFCCF32_MFCCSineRef_256_1_f32;
	f32referenceFileSine256Len = sizeof(MFCCF32_MFCCSineRef_256_1_f32)/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32referenceFileSine512, sizeof(f32referenceFileSine512), "%s%s%s", Patterns_PATH, MFCCF32, "MFCCSineRef_512_1_f32.txt");
#else
	f32referenceFileSine512 = MFCCF32_MFCCSineRef_512_1_f32;
	f32referenceFileSine512Len = sizeof(MFCCF32_MFCCSineRef_512_1_f32)/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(f32referenceFileSine1024, sizeof(f32referenceFileSine1024), "%s%s%s", Patterns_PATH, MFCCF32, "MFCCSineRef_1024_1_f32.txt");
#else
	f32referenceFileSine1024 = MFCCF32_MFCCSineRef_1024_1_f32;
	f32referenceFileSine1024Len = sizeof(MFCCF32_MFCCSineRef_1024_1_f32)/sizeof(f32);
#endif


    // load input data
#if defined(NOT_EMBEDDED)
	load_data_f32(f32inputFileNoise256, &paramCountInputNoise256, f32inputNoise256);
#else
	paramCountInputNoise256 = f32inputFileNoise256Len;
	load_data_f32(f32inputFileNoise256, paramCountInputNoise256, f32inputNoise256);
	paramCountInputNoise256 = paramCountInputNoise256/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(f32inputFileNoise512, &paramCountInputNoise512, f32inputNoise512);
#else
	paramCountInputNoise512 = f32inputFileNoise512Len;
	load_data_f32(f32inputFileNoise512, paramCountInputNoise512, f32inputNoise512);
	paramCountInputNoise512 = paramCountInputNoise512/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(f32inputFileNoise1024, &paramCountInputNoise1024, f32inputNoise1024);
#else
	paramCountInputNoise1024 = f32inputFileNoise1024Len;
	load_data_f32(f32inputFileNoise1024, paramCountInputNoise1024, f32inputNoise1024);
	paramCountInputNoise1024 = paramCountInputNoise1024/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	load_data_f32(f32inputFileSine256, &paramCountInputSine256, f32inputSine256);
#else
	paramCountInputSine256 = f32inputFileSine256Len;
	load_data_f32(f32inputFileSine256, paramCountInputSine256, f32inputSine256);
	paramCountInputSine256 = paramCountInputSine256/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(f32inputFileSine512, &paramCountInputSine512, f32inputSine512);
#else
	paramCountInputSine512 = f32inputFileSine512Len;
	load_data_f32(f32inputFileSine512, paramCountInputSine512, f32inputSine512);
	paramCountInputSine512 = paramCountInputSine512/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(f32inputFileSine1024, &paramCountInputSine1024, f32inputSine1024);
#else
	paramCountInputSine1024 = f32inputFileSine1024Len;
	load_data_f32(f32inputFileSine1024, paramCountInputSine1024, f32inputSine1024);
	paramCountInputSine1024 = paramCountInputSine1024/sizeof(f32);
#endif


    f32 f32output[MAX_SIZE] = {0};
    f32 f32tmpinp[MAX_SIZE] = {0};
    f32 f32tmpp[MAX_SIZE] = {0};

    uint32_t fftLen;
    unsigned long nb = MAX_NB_SAMPLES;
    
    mips_mfcc_instance_f32 mfcc;

// =====================
    printf("== mips_mfcc_f32 Noise_256 test ==  \n");

    nb = 256;
    fftLen = nb;

    mips_mfcc_init_f32(&mfcc,
                    nb,20,13,mfcc_dct_coefs_config1_f32,
                    mfcc_filter_pos_config3_f32,mfcc_filter_len_config3_f32,
                    mfcc_filter_coefs_config3_f32,
                    mfcc_window_coefs_config3_f32);
    memcpy((void*)f32tmpinp,(void*)f32inputNoise256,sizeof(f32)*fftLen);
    mips_mfcc_f32(&mfcc,f32tmpinp,f32output,f32tmpp);

    printf("mips_mfcc_f32 Noise_256 finish \n");

    printf("mips_mfcc_f32 Noise_256 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(f32referenceFileNoise256, f32output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(f32referenceFileNoise256, f32output, f32referenceFileNoise256Len, (f32)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f32(f32referenceFileNoise256, f32output, 0, REL_ERROR);
#else
	rel_check_special_f32(f32referenceFileNoise256, f32output, f32referenceFileNoise256Len, REL_ERROR);
#endif

    printf("\n== mips_mfcc_f32 Noise_256 check done  == \n\n");

// =====================
    printf("== mips_mfcc_f32 Noise_512 test ==  \n");

    nb = 512;
    fftLen = nb;

    mips_mfcc_init_f32(&mfcc,
                      nb,20,13,mfcc_dct_coefs_config1_f32,
                      mfcc_filter_pos_config2_f32,mfcc_filter_len_config2_f32,
                      mfcc_filter_coefs_config2_f32,
                      mfcc_window_coefs_config2_f32);
    memcpy((void*)f32tmpinp,(void*)f32inputNoise512,sizeof(f32)*fftLen);
    mips_mfcc_f32(&mfcc,f32tmpinp,f32output,f32tmpp);

    printf("mips_mfcc_f32 Noise_512 finish \n");

    printf("mips_mfcc_f32 Noise_512 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(f32referenceFileNoise512, f32output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(f32referenceFileNoise512, f32output, f32referenceFileNoise512Len, (f32)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f32(f32referenceFileNoise512, f32output, 0, REL_ERROR);
#else
	rel_check_special_f32(f32referenceFileNoise512, f32output, f32referenceFileNoise512Len, REL_ERROR);
#endif

    printf("\n== mips_mfcc_f32 Noise_512 check done  == \n\n");

// =====================
    printf("== mips_mfcc_f32 Noise_1024 test ==  \n");

    nb = 1024;
    fftLen = nb;

    mips_mfcc_init_f32(&mfcc,
                      nb,20,13,mfcc_dct_coefs_config1_f32,
                      mfcc_filter_pos_config1_f32,mfcc_filter_len_config1_f32,
                      mfcc_filter_coefs_config1_f32,
                      mfcc_window_coefs_config1_f32);
    memcpy((void*)f32tmpinp,(void*)f32inputNoise1024,sizeof(f32)*fftLen);
    mips_mfcc_f32(&mfcc,f32tmpinp,f32output,f32tmpp);

    printf("mips_mfcc_f32 Noise_1024 finish \n");

    printf("mips_mfcc_f32 Noise_1024 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(f32referenceFileNoise1024, f32output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(f32referenceFileNoise1024, f32output, f32referenceFileNoise1024Len, (f32)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f32(f32referenceFileNoise1024, f32output, 0, REL_ERROR);
#else
	rel_check_special_f32(f32referenceFileNoise1024, f32output, f32referenceFileNoise1024Len, REL_ERROR);
#endif

    printf("\n== mips_mfcc_f32 Noise_1024 check done  == \n\n");

    f32 f32sineoutput[MAX_SIZE] = {0};
    f32 f32sinnetmpinp[MAX_SIZE] = {0};
    f32 f32sinetmpp[MAX_SIZE] = {0};
// =====================
    printf("== mips_mfcc_f32 Sine_256 test ==  \n");

    nb = 256;
    fftLen = nb;

    mips_mfcc_init_f32(&mfcc,
                    nb,20,13,mfcc_dct_coefs_config1_f32,
                    mfcc_filter_pos_config3_f32,mfcc_filter_len_config3_f32,
                    mfcc_filter_coefs_config3_f32,
                    mfcc_window_coefs_config3_f32);
    memcpy((void*)f32sinnetmpinp,(void*)f32inputSine256,sizeof(f32)*fftLen);
    mips_mfcc_f32(&mfcc,f32sinnetmpinp,f32sineoutput,f32sinetmpp);

    printf("mips_mfcc_f32 Sine_256 finish \n");

    printf("mips_mfcc_f32 Sine_256 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(f32referenceFileSine256, f32sineoutput, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(f32referenceFileSine256, f32sineoutput, f32referenceFileSine256Len, (f32)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f32(f32referenceFileSine256, f32sineoutput, 0, REL_ERROR);
#else
	rel_check_special_f32(f32referenceFileSine256, f32sineoutput, f32referenceFileSine256Len, REL_ERROR);
#endif

    printf("\n== mips_mfcc_f32 Sine_256 check done  == \n\n");

// =====================
    printf("== mips_mfcc_f32 Sine_512 test ==  \n");

    nb = 512;
    fftLen = nb;

    mips_mfcc_init_f32(&mfcc,
                      nb,20,13,mfcc_dct_coefs_config1_f32,
                      mfcc_filter_pos_config2_f32,mfcc_filter_len_config2_f32,
                      mfcc_filter_coefs_config2_f32,
                      mfcc_window_coefs_config2_f32);
    memcpy((void*)f32sinnetmpinp,(void*)f32inputSine512,sizeof(f32)*fftLen);
    mips_mfcc_f32(&mfcc,f32sinnetmpinp,f32sineoutput,f32sinetmpp);

    printf("mips_mfcc_f32 Sine_512 finish \n");

    printf("mips_mfcc_f32 Sine_512 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(f32referenceFileSine512, f32sineoutput, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(f32referenceFileSine512, f32sineoutput, f32referenceFileSine512Len, (f32)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f32(f32referenceFileSine512, f32sineoutput, 0, REL_ERROR);
#else
	rel_check_special_f32(f32referenceFileSine512, f32sineoutput, f32referenceFileSine512Len, REL_ERROR);
#endif

    printf("\n== mips_mfcc_f32 Sine_512 check done  == \n\n");

// =====================
    printf("== mips_mfcc_f32 Sine_1024 test ==  \n");

    nb = 1024;
    fftLen = nb;

    mips_mfcc_init_f32(&mfcc,
                      nb,20,13,mfcc_dct_coefs_config1_f32,
                      mfcc_filter_pos_config1_f32,mfcc_filter_len_config1_f32,
                      mfcc_filter_coefs_config1_f32,
                      mfcc_window_coefs_config1_f32);
    memcpy((void*)f32sinnetmpinp,(void*)f32inputSine1024,sizeof(f32)*fftLen);
    mips_mfcc_f32(&mfcc,f32sinnetmpinp,f32sineoutput,f32sinetmpp);

    printf("mips_mfcc_f32 Sine_1024 finish \n");

    printf("mips_mfcc_f32 Sine_1024 checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f32(f32referenceFileSine1024, f32sineoutput, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(f32referenceFileSine1024, f32sineoutput, f32referenceFileSine1024Len, (f32)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f32(f32referenceFileSine1024, f32sineoutput, 0, REL_ERROR);
#else
	rel_check_special_f32(f32referenceFileSine1024, f32sineoutput, f32referenceFileSine1024Len, REL_ERROR);
#endif

    printf("\n== mips_mfcc_f32 Sine_1024 check done  == \n\n");

    return 0;
}
