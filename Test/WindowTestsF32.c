#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/window_functions.h"

#define SNR_THRESHOLD 120
#define REL_ERROR (1.0e-6)
#define ABS_ERROR (2.0e-6)

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

	// declare output and paramCountOutput value
	int paramCountOutput1 = 128;
	float f32output1[MAX_SIZE] = {0};

	// file name. file path max length is 255, so use 255.
#if defined(NOT_EMBEDDED)
	char referenceFile[255] = {0};
#else
	void *referenceFile;
	int referenceFileLen = 0;
#endif


	// set file name by snprintf
	// relative path, function path, filename
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, WindowF32, "RefWelch_1_f32.txt");
#else
	referenceFile = WindowF32_RefWelch_1_f32;
	referenceFileLen = sizeof(WindowF32_RefWelch_1_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif



	printf("== mips_welch_f32 test ==  \n");
	mips_welch_f32(f32output1, paramCountOutput1);
	printf("mips_welch_f32 finish \n");

	printf("mips_welch_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, paramCountOutput1, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, paramCountOutput1, SNR_THRESHOLD);
#endif


	printf("\n== mips_welch_f32 check done  == \n\n");

	// for (size_t i = 0; i < paramCountInput1; i++)
	// {
	// 	printf("mips_add_f32 output = %f \n", f32output1[i]);
	// }
	
// =====================

	printf("== mips_bartlett_f32 test ==  \n");
	mips_bartlett_f32(f32output1, paramCountOutput1);
	printf("mips_bartlett_f32 finish \n");

	printf("mips_bartlett_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, WindowF32, "RefBartlett_2_f32.txt");
#else
	referenceFile = WindowF32_RefBartlett_2_f32;
	referenceFileLen = sizeof(WindowF32_RefBartlett_2_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, paramCountOutput1, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, paramCountOutput1, SNR_THRESHOLD);
#endif


	printf("\n== mips_bartlett_f32 check done  == \n\n");

// =====================

	printf("== mips_hamming_f32 test ==  \n");
	mips_hamming_f32(f32output1, paramCountOutput1);
	printf("mips_hamming_f32 finish \n");

	printf("mips_hamming_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, WindowF32, "RefHamming_3_f32.txt");
#else
	referenceFile = WindowF32_RefHamming_3_f32;
	referenceFileLen = sizeof(WindowF32_RefHamming_3_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, paramCountOutput1, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, paramCountOutput1, SNR_THRESHOLD);
#endif


	printf("\n== mips_hamming_f32 check done  == \n\n");

// =====================

	printf("== mips_hanning_f32 test ==  \n");
	mips_hanning_f32(f32output1, paramCountOutput1);
	printf("mips_hanning_f32 finish \n");

	printf("mips_hanning_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, WindowF32, "RefHanning_4_f32.txt");
#else
	referenceFile = WindowF32_RefHanning_4_f32;
	referenceFileLen = sizeof(WindowF32_RefHanning_4_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, paramCountOutput1, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, paramCountOutput1, SNR_THRESHOLD);
#endif


	printf("\n== mips_hanning_f32 check done  == \n\n");

// =====================

	printf("== mips_nuttall3_f32 test ==  \n");
	mips_nuttall3_f32(f32output1, paramCountOutput1);
	printf("mips_nuttall3_f32 finish \n");

	printf("mips_nuttall3_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, WindowF32, "RefNuttall3_5_f32.txt");
#else
	referenceFile = WindowF32_RefNuttall3_5_f32;
	referenceFileLen = sizeof(WindowF32_RefNuttall3_5_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, paramCountOutput1, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, paramCountOutput1, SNR_THRESHOLD);
#endif


	printf("\n== mips_nuttall3_f32 check done  == \n\n");

// =====================

	printf("== mips_nuttall4_f32 test ==  \n");
	mips_nuttall4_f32(f32output1, paramCountOutput1);
	printf("mips_nuttall4_f32 finish \n");

	printf("mips_nuttall4_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, WindowF32, "RefNuttall4_6_f32.txt");
#else
	referenceFile = WindowF32_RefNuttall4_6_f32;
	referenceFileLen = sizeof(WindowF32_RefNuttall4_6_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, paramCountOutput1, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, paramCountOutput1, SNR_THRESHOLD);
#endif


	printf("\n== mips_nuttall4_f32 check done  == \n\n");

// =====================

	printf("== mips_nuttall3a_f32 test ==  \n");
	mips_nuttall3a_f32(f32output1, paramCountOutput1);
	printf("mips_nuttall3a_f32 finish \n");

	printf("mips_nuttall3a_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, WindowF32, "RefNuttall3a_7_f32.txt");
#else
	referenceFile = WindowF32_RefNuttall3a_7_f32;
	referenceFileLen = sizeof(WindowF32_RefNuttall3a_7_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, paramCountOutput1, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, paramCountOutput1, SNR_THRESHOLD);
#endif


	printf("\n== mips_nuttall3a_f32 check done  == \n\n");

// =====================

	printf("== mips_nuttall3b_f32 test ==  \n");
	mips_nuttall3b_f32(f32output1, paramCountOutput1);
	printf("mips_nuttall3b_f32 finish \n");

	printf("mips_nuttall3b_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, WindowF32, "RefNuttall3b_8_f32.txt");
#else
	referenceFile = WindowF32_RefNuttall3b_8_f32;
	referenceFileLen = sizeof(WindowF32_RefNuttall3b_8_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, paramCountOutput1, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, paramCountOutput1, SNR_THRESHOLD);
#endif


	printf("\n== mips_nuttall3b_f32 check done  == \n\n");

// =====================

	printf("== mips_nuttall4a_f32 test ==  \n");
	mips_nuttall4a_f32(f32output1, paramCountOutput1);
	printf("mips_nuttall4a_f32 finish \n");

	printf("mips_nuttall4a_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, WindowF32, "RefNuttall4a_9_f32.txt");
#else
	referenceFile = WindowF32_RefNuttall4a_9_f32;
	referenceFileLen = sizeof(WindowF32_RefNuttall4a_9_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, paramCountOutput1, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, paramCountOutput1, SNR_THRESHOLD);
#endif


	printf("\n== mips_nuttall4a_f32 check done  == \n\n");

// =====================

	printf("== mips_blackman_harris_92db_f32 test ==  \n");
	mips_blackman_harris_92db_f32(f32output1, paramCountOutput1);
	printf("mips_blackman_harris_92db_f32 finish \n");

	printf("mips_blackman_harris_92db_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, WindowF32, "RefBlackman_harris_92db_10_f32.txt");
#else
	referenceFile = WindowF32_RefBlackman_harris_92db_10_f32;
	referenceFileLen = sizeof(WindowF32_RefBlackman_harris_92db_10_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, paramCountOutput1, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, paramCountOutput1, SNR_THRESHOLD);
#endif


	printf("\n== mips_blackman_harris_92db_f32 check done  == \n\n");

// =====================

	printf("== mips_nuttall4b_f32 test ==  \n");
	mips_nuttall4b_f32(f32output1, paramCountOutput1);
	printf("mips_nuttall4b_f32 finish \n");

	printf("mips_nuttall4b_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, WindowF32, "RefNuttall4b_11_f32.txt");
#else
	referenceFile = WindowF32_RefNuttall4b_11_f32;
	referenceFileLen = sizeof(WindowF32_RefNuttall4b_11_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, paramCountOutput1, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, paramCountOutput1, SNR_THRESHOLD);
#endif


	printf("\n== mips_nuttall4b_f32 check done  == \n\n");

// =====================

	printf("== mips_nuttall4c_f32 test ==  \n");
	mips_nuttall4c_f32(f32output1, paramCountOutput1);
	printf("mips_nuttall4c_f32 finish \n");

	printf("mips_nuttall4c_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, WindowF32, "RefNuttall4c_12_f32.txt");
#else
	referenceFile = WindowF32_RefNuttall4c_12_f32;
	referenceFileLen = sizeof(WindowF32_RefNuttall4c_12_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, paramCountOutput1, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, paramCountOutput1, SNR_THRESHOLD);
#endif


	printf("\n== mips_nuttall4c_f32 check done  == \n\n");

// =====================

	printf("== mips_hft90d_f32 test ==  \n");
	mips_hft90d_f32(f32output1, paramCountOutput1);
	printf("mips_hft90d_f32 finish \n");

	printf("mips_hft90d_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, WindowF32, "RefHft90d_13_f32.txt");
#else
	referenceFile = WindowF32_RefHft90d_13_f32;
	referenceFileLen = sizeof(WindowF32_RefHft90d_13_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, paramCountOutput1, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, paramCountOutput1, SNR_THRESHOLD);
#endif


	printf("\n== mips_hft90d_f32 check done  == \n\n");

// =====================

	printf("== mips_hft95_f32 test ==  \n");
	mips_hft95_f32(f32output1, paramCountOutput1);
	printf("mips_hft95_f32 finish \n");

	printf("mips_hft95_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, WindowF32, "RefHft95_14_f32.txt");
#else
	referenceFile = WindowF32_RefHft95_14_f32;
	referenceFileLen = sizeof(WindowF32_RefHft95_14_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, paramCountOutput1, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, paramCountOutput1, SNR_THRESHOLD);
#endif


	printf("\n== mips_hft95_f32 check done  == \n\n");

// =====================

	printf("== mips_hft116d_f32 test ==  \n");
	mips_hft116d_f32(f32output1, paramCountOutput1);
	printf("mips_hft116d_f32 finish \n");

	printf("mips_hft116d_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, WindowF32, "RefHft116d_15_f32.txt");
#else
	referenceFile = WindowF32_RefHft116d_15_f32;
	referenceFileLen = sizeof(WindowF32_RefHft116d_15_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, paramCountOutput1, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, paramCountOutput1, SNR_THRESHOLD);
#endif


	printf("\n== mips_hft116d_f32 check done  == \n\n");

// =====================

	printf("== mips_hft144d_f32 test ==  \n");
	mips_hft144d_f32(f32output1, paramCountOutput1);
	printf("mips_hft144d_f32 finish \n");

	printf("mips_hft144d_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, WindowF32, "RefHft144d_16_f32.txt");
#else
	referenceFile = WindowF32_RefHft144d_16_f32;
	referenceFileLen = sizeof(WindowF32_RefHft144d_16_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, paramCountOutput1, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, paramCountOutput1, SNR_THRESHOLD);
#endif


	printf("\n== mips_hft144d_f32 check done  == \n\n");

// =====================

	printf("== mips_hft169d_f32 test ==  \n");
	mips_hft169d_f32(f32output1, paramCountOutput1);
	printf("mips_hft169d_f32 finish \n");

	printf("mips_hft169d_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, WindowF32, "RefHft169d_17_f32.txt");
#else
	referenceFile = WindowF32_RefHft169d_17_f32;
	referenceFileLen = sizeof(WindowF32_RefHft169d_17_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, paramCountOutput1, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, paramCountOutput1, SNR_THRESHOLD);
#endif


	printf("\n== mips_hft169d_f32 check done  == \n\n");

// =====================

	printf("== mips_hft196d_f32 test ==  \n");
	mips_hft196d_f32(f32output1, paramCountOutput1);
	printf("mips_hft196d_f32 finish \n");

	printf("mips_hft196d_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, WindowF32, "RefHft196d_18_f32.txt");
#else
	referenceFile = WindowF32_RefHft196d_18_f32;
	referenceFileLen = sizeof(WindowF32_RefHft196d_18_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, paramCountOutput1, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, paramCountOutput1, SNR_THRESHOLD);
#endif


	printf("\n== mips_hft196d_f32 check done  == \n\n");

// =====================

	printf("== mips_hft223d_f32 test ==  \n");
	mips_hft223d_f32(f32output1, paramCountOutput1);
	printf("mips_hft223d_f32 finish \n");

	printf("mips_hft223d_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, WindowF32, "RefHft223d_19_f32.txt");
#else
	referenceFile = WindowF32_RefHft223d_19_f32;
	referenceFileLen = sizeof(WindowF32_RefHft223d_19_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, paramCountOutput1, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, paramCountOutput1, SNR_THRESHOLD);
#endif


	printf("\n== mips_hft223d_f32 check done  == \n\n");

// =====================

	printf("== mips_hft248d_f32 test ==  \n");
	mips_hft248d_f32(f32output1, paramCountOutput1);
	printf("mips_hft248d_f32 finish \n");

	printf("mips_hft248d_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, WindowF32, "RefHft248d_20_f32.txt");
#else
	referenceFile = WindowF32_RefHft248d_20_f32;
	referenceFileLen = sizeof(WindowF32_RefHft248d_20_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, paramCountOutput1, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, paramCountOutput1, SNR_THRESHOLD);
#endif


	printf("\n== mips_hft248d_f32 check done  == \n\n");

// =====================

	
	return 0;

}