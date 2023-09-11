#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/complex_math_functions.h"

#define SNR_THRESHOLD 310

#define REL_ERROR (3.0e-15)

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
	int paramCountInput1 = 0;
	int paramCountInput2 = 0;
	int paramCountInput3 = 0;
	f64 f64input1[MAX_SIZE] = {0};
	f64 f64input2[MAX_SIZE] = {0};
	f64 f64input3[MAX_SIZE] = {0};

	// file name. file path max length is 255, so use 255.
#if defined(NOT_EMBEDDED)
	char inputFile1[255] = {0};
#else
	void *inputFile1;
	int inputFile1Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFile2[255] = {0};
#else
	void *inputFile2;
	int inputFile2Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFile3[255] = {0};
#else
	void *inputFile3;
	int inputFile3Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char referenceFile[255] = {0};
#else
	void *referenceFile;
	int referenceFileLen = 0;
#endif


	// set file name by snprintf
	// relative path, function path, filename
#if defined(NOT_EMBEDDED)
	snprintf(inputFile1, sizeof(inputFile1), "%s%s%s", Patterns_PATH, ComplexMathsF64, "Input1_f64.txt");
#else
	inputFile1 = ComplexMathsF64_Input1_f64;
	inputFile1Len = sizeof(ComplexMathsF64_Input1_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile2, sizeof(inputFile2), "%s%s%s", Patterns_PATH, ComplexMathsF64, "Input2_f64.txt");
#else
	inputFile2 = ComplexMathsF64_Input2_f64;
	inputFile2Len = sizeof(ComplexMathsF64_Input2_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile3, sizeof(inputFile3), "%s%s%s", Patterns_PATH, ComplexMathsF64, "Input3_f64.txt");
#else
	inputFile3 = ComplexMathsF64_Input3_f64;
	inputFile3Len = sizeof(ComplexMathsF64_Input3_f64);
#endif


	// load input data
#if defined(NOT_EMBEDDED)
	load_data_f64(inputFile1, &paramCountInput1, f64input1);
#else
	paramCountInput1 = inputFile1Len;
	load_data_f64(inputFile1, paramCountInput1, f64input1);
	paramCountInput1 = paramCountInput1/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(inputFile2, &paramCountInput2, f64input2);
#else
	paramCountInput2 = inputFile2Len;
	load_data_f64(inputFile2, paramCountInput2, f64input2);
	paramCountInput2 = paramCountInput2/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(inputFile3, &paramCountInput3, f64input3);
#else
	paramCountInput3 = inputFile3Len;
	load_data_f64(inputFile3, paramCountInput3, f64input3);
	paramCountInput3 = paramCountInput3/sizeof(f64);
#endif


	f64 f64output1[MAX_SIZE] = {0};
	uint16_t u16output1[MAX_SIZE] = {0};

	printf("== mips_cmplx_mag_f64 2 test ==  \n");
	mips_cmplx_mag_f64(f64input1, f64output1, 4);
	printf("mips_cmplx_mag_f64 finish \n");

	printf("mips_cmplx_mag_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsF64, "Reference5_f64.txt");
#else
	referenceFile = ComplexMathsF64_Reference5_f64;
	referenceFileLen = sizeof(ComplexMathsF64_Reference5_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, 4, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, 4, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f64(referenceFile, f64output1, 4, REL_ERROR);
#else
	rel_check_special_f64(referenceData_f64, f64output1, 4, REL_ERROR);
#endif


	printf("\n== mips_cmplx_mag_f64 3 check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mag_f64 2N test ==  \n");
	mips_cmplx_mag_f64(f64input1, f64output1, 8);
	printf("mips_cmplx_mag_f64 finish \n");

	printf("mips_cmplx_mag_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsF64, "Reference5_f64.txt");
#else
	referenceFile = ComplexMathsF64_Reference5_f64;
	referenceFileLen = sizeof(ComplexMathsF64_Reference5_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, 8, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, 8, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f64(referenceFile, f64output1, 8, REL_ERROR);
#else
	rel_check_special_f64(referenceData_f64, f64output1, 8, REL_ERROR);
#endif


	printf("\n== mips_cmplx_mag_f64 2N check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mag_f64 2N+1 test ==  \n");
	mips_cmplx_mag_f64(f64input1, f64output1, 10);
	printf("mips_cmplx_mag_f64 finish \n");

	printf("mips_cmplx_mag_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsF64, "Reference5_f64.txt");
#else
	referenceFile = ComplexMathsF64_Reference5_f64;
	referenceFileLen = sizeof(ComplexMathsF64_Reference5_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, 10, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, 10, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f64(referenceFile, f64output1, 10, REL_ERROR);
#else
	rel_check_special_f64(referenceData_f64, f64output1, 10, REL_ERROR);
#endif


	printf("\n== mips_cmplx_mag_f64 2N+1 check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mag_f64 long test ==  \n");
	mips_cmplx_mag_f64(f64input1, f64output1, paramCountInput1);
	printf("mips_cmplx_mag_f64 finish \n");

	printf("mips_cmplx_mag_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsF64, "Reference5_f64.txt");
#else
	referenceFile = ComplexMathsF64_Reference5_f64;
	referenceFileLen = sizeof(ComplexMathsF64_Reference5_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
	referenceFileLen = referenceFileLen/sizeof(f64);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f64(referenceFile, f64output1, 0, REL_ERROR);
#else
	rel_check_special_f64(referenceData_f64, f64output1, referenceFileLen, REL_ERROR);
#endif


	printf("\n== mips_cmplx_mag_f64 long check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mag_squared_f64 2 test ==  \n");
	mips_cmplx_mag_squared_f64(f64input1, f64output1, 4);
	printf("mips_cmplx_mag_squared_f64 finish \n");

	printf("mips_cmplx_mag_squared_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsF64, "Reference6_f64.txt");
#else
	referenceFile = ComplexMathsF64_Reference6_f64;
	referenceFileLen = sizeof(ComplexMathsF64_Reference6_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, 2, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, 2, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f64(referenceFile, f64output1, 2, REL_ERROR);
#else
	rel_check_special_f64(referenceData_f64, f64output1, 2, REL_ERROR);
#endif


	printf("\n== mips_cmplx_mag_squared_f64 3 check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mag_squared_f64 2N test ==  \n");
	mips_cmplx_mag_squared_f64(f64input1, f64output1, 8);
	printf("mips_cmplx_mag_squared_f64 finish \n");

	printf("mips_cmplx_mag_squared_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsF64, "Reference6_f64.txt");
#else
	referenceFile = ComplexMathsF64_Reference6_f64;
	referenceFileLen = sizeof(ComplexMathsF64_Reference6_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, 4, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, 4, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f64(referenceFile, f64output1, 4, REL_ERROR);
#else
	rel_check_special_f64(referenceData_f64, f64output1, 4, REL_ERROR);
#endif


	printf("\n== mips_cmplx_mag_squared_f64 2N check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mag_squared_f64 2N+1 test ==  \n");
	mips_cmplx_mag_squared_f64(f64input1, f64output1, 10);
	printf("mips_cmplx_mag_squared_f64 finish \n");

	printf("mips_cmplx_mag_squared_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsF64, "Reference6_f64.txt");
#else
	referenceFile = ComplexMathsF64_Reference6_f64;
	referenceFileLen = sizeof(ComplexMathsF64_Reference6_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, 5, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, 5, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f64(referenceFile, f64output1, 5, REL_ERROR);
#else
	rel_check_special_f64(referenceData_f64, f64output1, 5, REL_ERROR);
#endif


	printf("\n== mips_cmplx_mag_squared_f64 2N check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mag_squared_f64 long test ==  \n");
	mips_cmplx_mag_squared_f64(f64input1, f64output1, paramCountInput1);
	printf("mips_cmplx_mag_squared_f64 finish \n");

	printf("mips_cmplx_mag_squared_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsF64, "Reference6_f64.txt");
#else
	referenceFile = ComplexMathsF64_Reference6_f64;
	referenceFileLen = sizeof(ComplexMathsF64_Reference6_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
	referenceFileLen = referenceFileLen/sizeof(f64);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f64(referenceFile, f64output1, 0, REL_ERROR);
#else
	rel_check_special_f64(referenceData_f64, f64output1, referenceFileLen, REL_ERROR);
#endif


	printf("\n== mips_cmplx_mag_squared_f64 long check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mult_cmplx_f64 2 test ==  \n");
	mips_cmplx_mult_cmplx_f64(f64input1, f64input2, f64output1, 4);
	printf("mips_cmplx_mult_cmplx_f64 finish \n");

	printf("mips_cmplx_mult_cmplx_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsF64, "Reference7_f64.txt");
#else
	referenceFile = ComplexMathsF64_Reference7_f64;
	referenceFileLen = sizeof(ComplexMathsF64_Reference7_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, 4, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, 4, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f64(referenceFile, f64output1, 4, REL_ERROR);
#else
	rel_check_special_f64(referenceData_f64, f64output1, 4, REL_ERROR);
#endif


	printf("\n== mips_cmplx_mult_cmplx_f64 3 check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mult_cmplx_f64 2N test ==  \n");
	mips_cmplx_mult_cmplx_f64(f64input1, f64input2, f64output1, 8);
	printf("mips_cmplx_mult_cmplx_f64 finish \n");

	printf("mips_cmplx_mult_cmplx_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsF64, "Reference7_f64.txt");
#else
	referenceFile = ComplexMathsF64_Reference7_f64;
	referenceFileLen = sizeof(ComplexMathsF64_Reference7_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, 8, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, 8, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f64(referenceFile, f64output1, 8, REL_ERROR);
#else
	rel_check_special_f64(referenceData_f64, f64output1, 8, REL_ERROR);
#endif


	printf("\n== mips_cmplx_mult_cmplx_f64 2N check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mult_cmplx_f64 2N+1 test ==  \n");
	mips_cmplx_mult_cmplx_f64(f64input1, f64input2, f64output1, 10);
	printf("mips_cmplx_mult_cmplx_f64 finish \n");

	printf("mips_cmplx_mult_cmplx_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsF64, "Reference7_f64.txt");
#else
	referenceFile = ComplexMathsF64_Reference7_f64;
	referenceFileLen = sizeof(ComplexMathsF64_Reference7_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, 10, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, 10, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f64(referenceFile, f64output1, 10, REL_ERROR);
#else
	rel_check_special_f64(referenceData_f64, f64output1, 10, REL_ERROR);
#endif


	printf("\n== mips_cmplx_mult_cmplx_f64 2N+1 check done  == \n\n");

	// =====================

	printf("== mips_cmplx_mult_cmplx_f64 long test ==  \n");
	mips_cmplx_mult_cmplx_f64(f64input1, f64input2, f64output1, paramCountInput1);
	printf("mips_cmplx_mult_cmplx_f64 finish \n");

	printf("mips_cmplx_mult_cmplx_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, ComplexMathsF64, "Reference7_f64.txt");
#else
	referenceFile = ComplexMathsF64_Reference7_f64;
	referenceFileLen = sizeof(ComplexMathsF64_Reference7_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
	referenceFileLen = referenceFileLen/sizeof(f64);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f64(referenceFile, f64output1, 0, REL_ERROR);
#else
	rel_check_special_f64(referenceData_f64, f64output1, referenceFileLen, REL_ERROR);
#endif


	printf("\n== mips_cmplx_mult_cmplx_f64 long check done  == \n\n");

	// =====================

	return 0;
}