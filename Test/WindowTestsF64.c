#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/window_functions.h"

#define SNR_THRESHOLD 250
#define REL_ERROR (3.0e-15)
#define ABS_ERROR (3.0e-15)

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
	double f64output1[MAX_SIZE] = {0};

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
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, WindowF64, "RefWelch_1_f64.txt");
#else
	referenceFile = WindowF64_RefWelch_1_f64;
	referenceFileLen = sizeof(WindowF64_RefWelch_1_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif



	printf("== mips_welch_f64 test ==  \n");
	mips_welch_f64(f64output1, paramCountOutput1);
	printf("mips_welch_f64 finish \n");

	printf("mips_welch_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	close_check_f64(referenceFile, f64output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f64(referenceData_f64, f64output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, paramCountOutput1, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, paramCountOutput1, SNR_THRESHOLD);
#endif


	printf("\n== mips_welch_f64 check done  == \n\n");

	// for (size_t i = 0; i < paramCountInput1; i++)
	// {
	// 	printf("mips_add_f64 output = %f \n", f64output1[i]);
	// }
	
// =====================

	printf("== mips_bartlett_f64 test ==  \n");
	mips_bartlett_f64(f64output1, paramCountOutput1);
	printf("mips_bartlett_f64 finish \n");

	printf("mips_bartlett_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, WindowF64, "RefBartlett_2_f64.txt");
#else
	referenceFile = WindowF64_RefBartlett_2_f64;
	referenceFileLen = sizeof(WindowF64_RefBartlett_2_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f64(referenceFile, f64output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f64(referenceData_f64, f64output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, paramCountOutput1, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, paramCountOutput1, SNR_THRESHOLD);
#endif


	printf("\n== mips_bartlett_f64 check done  == \n\n");

// =====================

	printf("== mips_hamming_f64 test ==  \n");
	mips_hamming_f64(f64output1, paramCountOutput1);
	printf("mips_hamming_f64 finish \n");

	printf("mips_hamming_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, WindowF64, "RefHamming_3_f64.txt");
#else
	referenceFile = WindowF64_RefHamming_3_f64;
	referenceFileLen = sizeof(WindowF64_RefHamming_3_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f64(referenceFile, f64output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f64(referenceData_f64, f64output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, paramCountOutput1, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, paramCountOutput1, SNR_THRESHOLD);
#endif


	printf("\n== mips_hamming_f64 check done  == \n\n");

// =====================

	printf("== mips_hanning_f64 test ==  \n");
	mips_hanning_f64(f64output1, paramCountOutput1);
	printf("mips_hanning_f64 finish \n");

	printf("mips_hanning_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, WindowF64, "RefHanning_4_f64.txt");
#else
	referenceFile = WindowF64_RefHanning_4_f64;
	referenceFileLen = sizeof(WindowF64_RefHanning_4_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f64(referenceFile, f64output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f64(referenceData_f64, f64output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, paramCountOutput1, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, paramCountOutput1, SNR_THRESHOLD);
#endif


	printf("\n== mips_hanning_f64 check done  == \n\n");

// =====================

	printf("== mips_nuttall3_f64 test ==  \n");
	mips_nuttall3_f64(f64output1, paramCountOutput1);
	printf("mips_nuttall3_f64 finish \n");

	printf("mips_nuttall3_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, WindowF64, "RefNuttall3_5_f64.txt");
#else
	referenceFile = WindowF64_RefNuttall3_5_f64;
	referenceFileLen = sizeof(WindowF64_RefNuttall3_5_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f64(referenceFile, f64output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f64(referenceData_f64, f64output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, paramCountOutput1, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, paramCountOutput1, SNR_THRESHOLD);
#endif


	printf("\n== mips_nuttall3_f64 check done  == \n\n");

// =====================

	printf("== mips_nuttall4_f64 test ==  \n");
	mips_nuttall4_f64(f64output1, paramCountOutput1);
	printf("mips_nuttall4_f64 finish \n");

	printf("mips_nuttall4_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, WindowF64, "RefNuttall4_6_f64.txt");
#else
	referenceFile = WindowF64_RefNuttall4_6_f64;
	referenceFileLen = sizeof(WindowF64_RefNuttall4_6_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f64(referenceFile, f64output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f64(referenceData_f64, f64output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, paramCountOutput1, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, paramCountOutput1, SNR_THRESHOLD);
#endif


	printf("\n== mips_nuttall4_f64 check done  == \n\n");

// =====================

	printf("== mips_nuttall3a_f64 test ==  \n");
	mips_nuttall3a_f64(f64output1, paramCountOutput1);
	printf("mips_nuttall3a_f64 finish \n");

	printf("mips_nuttall3a_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, WindowF64, "RefNuttall3a_7_f64.txt");
#else
	referenceFile = WindowF64_RefNuttall3a_7_f64;
	referenceFileLen = sizeof(WindowF64_RefNuttall3a_7_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f64(referenceFile, f64output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f64(referenceData_f64, f64output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, paramCountOutput1, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, paramCountOutput1, SNR_THRESHOLD);
#endif


	printf("\n== mips_nuttall3a_f64 check done  == \n\n");

// =====================

	printf("== mips_nuttall3b_f64 test ==  \n");
	mips_nuttall3b_f64(f64output1, paramCountOutput1);
	printf("mips_nuttall3b_f64 finish \n");

	printf("mips_nuttall3b_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, WindowF64, "RefNuttall3b_8_f64.txt");
#else
	referenceFile = WindowF64_RefNuttall3b_8_f64;
	referenceFileLen = sizeof(WindowF64_RefNuttall3b_8_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f64(referenceFile, f64output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f64(referenceData_f64, f64output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, paramCountOutput1, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, paramCountOutput1, SNR_THRESHOLD);
#endif


	printf("\n== mips_nuttall3b_f64 check done  == \n\n");

// =====================

	printf("== mips_nuttall4a_f64 test ==  \n");
	mips_nuttall4a_f64(f64output1, paramCountOutput1);
	printf("mips_nuttall4a_f64 finish \n");

	printf("mips_nuttall4a_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, WindowF64, "RefNuttall4a_9_f64.txt");
#else
	referenceFile = WindowF64_RefNuttall4a_9_f64;
	referenceFileLen = sizeof(WindowF64_RefNuttall4a_9_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f64(referenceFile, f64output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f64(referenceData_f64, f64output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, paramCountOutput1, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, paramCountOutput1, SNR_THRESHOLD);
#endif


	printf("\n== mips_nuttall4a_f64 check done  == \n\n");

// =====================

	printf("== mips_blackman_harris_92db_f64 test ==  \n");
	mips_blackman_harris_92db_f64(f64output1, paramCountOutput1);
	printf("mips_blackman_harris_92db_f64 finish \n");

	printf("mips_blackman_harris_92db_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, WindowF64, "RefBlackman_harris_92db_10_f64.txt");
#else
	referenceFile = WindowF64_RefBlackman_harris_92db_10_f64;
	referenceFileLen = sizeof(WindowF64_RefBlackman_harris_92db_10_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f64(referenceFile, f64output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f64(referenceData_f64, f64output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, paramCountOutput1, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, paramCountOutput1, SNR_THRESHOLD);
#endif


	printf("\n== mips_blackman_harris_92db_f64 check done  == \n\n");

// =====================

	printf("== mips_nuttall4b_f64 test ==  \n");
	mips_nuttall4b_f64(f64output1, paramCountOutput1);
	printf("mips_nuttall4b_f64 finish \n");

	printf("mips_nuttall4b_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, WindowF64, "RefNuttall4b_11_f64.txt");
#else
	referenceFile = WindowF64_RefNuttall4b_11_f64;
	referenceFileLen = sizeof(WindowF64_RefNuttall4b_11_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f64(referenceFile, f64output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f64(referenceData_f64, f64output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, paramCountOutput1, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, paramCountOutput1, SNR_THRESHOLD);
#endif


	printf("\n== mips_nuttall4b_f64 check done  == \n\n");

// =====================

	printf("== mips_nuttall4c_f64 test ==  \n");
	mips_nuttall4c_f64(f64output1, paramCountOutput1);
	printf("mips_nuttall4c_f64 finish \n");

	printf("mips_nuttall4c_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, WindowF64, "RefNuttall4c_12_f64.txt");
#else
	referenceFile = WindowF64_RefNuttall4c_12_f64;
	referenceFileLen = sizeof(WindowF64_RefNuttall4c_12_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f64(referenceFile, f64output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f64(referenceData_f64, f64output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, paramCountOutput1, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, paramCountOutput1, SNR_THRESHOLD);
#endif


	printf("\n== mips_nuttall4c_f64 check done  == \n\n");

// =====================

	printf("== mips_hft90d_f64 test ==  \n");
	mips_hft90d_f64(f64output1, paramCountOutput1);
	printf("mips_hft90d_f64 finish \n");

	printf("mips_hft90d_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, WindowF64, "RefHft90d_13_f64.txt");
#else
	referenceFile = WindowF64_RefHft90d_13_f64;
	referenceFileLen = sizeof(WindowF64_RefHft90d_13_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f64(referenceFile, f64output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f64(referenceData_f64, f64output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, paramCountOutput1, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, paramCountOutput1, SNR_THRESHOLD);
#endif


	printf("\n== mips_hft90d_f64 check done  == \n\n");

// =====================

	printf("== mips_hft95_f64 test ==  \n");
	mips_hft95_f64(f64output1, paramCountOutput1);
	printf("mips_hft95_f64 finish \n");

	printf("mips_hft95_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, WindowF64, "RefHft95_14_f64.txt");
#else
	referenceFile = WindowF64_RefHft95_14_f64;
	referenceFileLen = sizeof(WindowF64_RefHft95_14_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f64(referenceFile, f64output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f64(referenceData_f64, f64output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, paramCountOutput1, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, paramCountOutput1, SNR_THRESHOLD);
#endif


	printf("\n== mips_hft95_f64 check done  == \n\n");

// =====================

	printf("== mips_hft116d_f64 test ==  \n");
	mips_hft116d_f64(f64output1, paramCountOutput1);
	printf("mips_hft116d_f64 finish \n");

	printf("mips_hft116d_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, WindowF64, "RefHft116d_15_f64.txt");
#else
	referenceFile = WindowF64_RefHft116d_15_f64;
	referenceFileLen = sizeof(WindowF64_RefHft116d_15_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f64(referenceFile, f64output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f64(referenceData_f64, f64output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, paramCountOutput1, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, paramCountOutput1, SNR_THRESHOLD);
#endif


	printf("\n== mips_hft116d_f64 check done  == \n\n");

// =====================

	printf("== mips_hft144d_f64 test ==  \n");
	mips_hft144d_f64(f64output1, paramCountOutput1);
	printf("mips_hft144d_f64 finish \n");

	printf("mips_hft144d_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, WindowF64, "RefHft144d_16_f64.txt");
#else
	referenceFile = WindowF64_RefHft144d_16_f64;
	referenceFileLen = sizeof(WindowF64_RefHft144d_16_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f64(referenceFile, f64output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f64(referenceData_f64, f64output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, paramCountOutput1, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, paramCountOutput1, SNR_THRESHOLD);
#endif


	printf("\n== mips_hft144d_f64 check done  == \n\n");

// =====================

	printf("== mips_hft169d_f64 test ==  \n");
	mips_hft169d_f64(f64output1, paramCountOutput1);
	printf("mips_hft169d_f64 finish \n");

	printf("mips_hft169d_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, WindowF64, "RefHft169d_17_f64.txt");
#else
	referenceFile = WindowF64_RefHft169d_17_f64;
	referenceFileLen = sizeof(WindowF64_RefHft169d_17_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f64(referenceFile, f64output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f64(referenceData_f64, f64output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, paramCountOutput1, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, paramCountOutput1, SNR_THRESHOLD);
#endif


	printf("\n== mips_hft169d_f64 check done  == \n\n");

// =====================

	printf("== mips_hft196d_f64 test ==  \n");
	mips_hft196d_f64(f64output1, paramCountOutput1);
	printf("mips_hft196d_f64 finish \n");

	printf("mips_hft196d_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, WindowF64, "RefHft196d_18_f64.txt");
#else
	referenceFile = WindowF64_RefHft196d_18_f64;
	referenceFileLen = sizeof(WindowF64_RefHft196d_18_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f64(referenceFile, f64output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f64(referenceData_f64, f64output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, paramCountOutput1, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, paramCountOutput1, SNR_THRESHOLD);
#endif


	printf("\n== mips_hft196d_f64 check done  == \n\n");

// =====================

	printf("== mips_hft223d_f64 test ==  \n");
	mips_hft223d_f64(f64output1, paramCountOutput1);
	printf("mips_hft223d_f64 finish \n");

	printf("mips_hft223d_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, WindowF64, "RefHft223d_19_f64.txt");
#else
	referenceFile = WindowF64_RefHft223d_19_f64;
	referenceFileLen = sizeof(WindowF64_RefHft223d_19_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f64(referenceFile, f64output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f64(referenceData_f64, f64output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, paramCountOutput1, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, paramCountOutput1, SNR_THRESHOLD);
#endif


	printf("\n== mips_hft223d_f64 check done  == \n\n");

// =====================

	printf("== mips_hft248d_f64 test ==  \n");
	mips_hft248d_f64(f64output1, paramCountOutput1);
	printf("mips_hft248d_f64 finish \n");

	printf("mips_hft248d_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, WindowF64, "RefHft248d_20_f64.txt");
#else
	referenceFile = WindowF64_RefHft248d_20_f64;
	referenceFileLen = sizeof(WindowF64_RefHft248d_20_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f64(referenceFile, f64output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f64(referenceData_f64, f64output1, paramCountOutput1, ABS_ERROR, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, paramCountOutput1, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, paramCountOutput1, SNR_THRESHOLD);
#endif


	printf("\n== mips_hft248d_f64 check done  == \n\n");

// =====================

	
	return 0;

}