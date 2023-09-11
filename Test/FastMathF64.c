#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/fast_math_functions.h"

#include "mips_common_tables.h"
#include "dsp/utils.h"

#define SNR_THRESHOLD 310
/* 

Reference patterns are generated with
a double precision computation.

*/
#define REL_ERROR (2.0e-16)
#define ABS_ERROR (2.0e-16)

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
	int paramCountInputT = 0;
	f64 f64input1[MAX_SIZE] = {0};
	f64 f64inputT[MAX_SIZE] = {0};

	// file name. file path max length is 255, so use 255.
#if defined(NOT_EMBEDDED)
	char inputFile1[255] = {0};
#else
	void *inputFile1;
	int inputFile1Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFileT[255] = {0};
#else
	void *inputFileT;
	int inputFileTLen = 0;
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
	snprintf(inputFile1, sizeof(inputFile1), "%s%s%s", Patterns_PATH, FastMathF64, "Angles1_f64.txt");
#else
	inputFile1 = FastMathF64_Angles1_f64;
	inputFile1Len = sizeof(FastMathF64_Angles1_f64);
#endif


	// load input data
#if defined(NOT_EMBEDDED)
	load_data_f64(inputFile1, &paramCountInput1, f64input1);
#else
	paramCountInput1 = inputFile1Len;
	load_data_f64(inputFile1, paramCountInput1, f64input1);
	paramCountInput1 = paramCountInput1/sizeof(f64);
#endif


	f64 f64output1[MAX_SIZE] = {0};

	// =====================

	f64 *inp = f64input1;
	f64 *outp = f64output1;

#if defined(NOT_EMBEDDED)
	snprintf(inputFileT, sizeof(inputFileT), "%s%s%s", Patterns_PATH, FastMathF64, "Log1_f64.txt");
#else
	inputFileT = FastMathF64_Log1_f64;
	inputFileTLen = sizeof(FastMathF64_Log1_f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(inputFileT, &paramCountInputT, f64inputT);
#else
	paramCountInputT = inputFileTLen;
	load_data_f64(inputFileT, paramCountInputT, f64inputT);
	paramCountInputT = paramCountInputT/sizeof(f64);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(inputFile1, sizeof(inputFile1), "%s%s%s", Patterns_PATH, FastMathF64, "LogInput1_f64.txt");
#else
	inputFile1 = FastMathF64_LogInput1_f64;
	inputFile1Len = sizeof(FastMathF64_LogInput1_f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(inputFile1, &paramCountInput1, f64input1);
#else
	paramCountInput1 = inputFile1Len;
	load_data_f64(inputFile1, paramCountInput1, f64input1);
	paramCountInput1 = paramCountInput1/sizeof(f64);
#endif


	printf("== mips_vlog_f64 long test ==  \n");

	mips_vlog_f64(inp, outp, paramCountInputT);

	printf("mips_vlog_f64 finish \n");

	printf("mips_vlog_f64 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FastMathF64, "Log1_f64.txt");
#else
	referenceFile = FastMathF64_Log1_f64;
	referenceFileLen = sizeof(FastMathF64_Log1_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f64(referenceFile, f64output1, 0, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f64(referenceData_f64, f64output1, referenceFileLen, ABS_ERROR, REL_ERROR);
#endif

	printf("\n== mips_vlog_f64 long check done  == \n\n");

	// =====================

	memset(f64output1, 0, sizeof(f64output1));
	inp = f64input1;
	outp = f64output1;

	printf("== mips_vlog_f64 2 test ==  \n");

	mips_vlog_f64(inp, outp, 2);

	printf("mips_vlog_f64 finish \n");

	printf("mips_vlog_f64 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FastMathF64, "Log1_f64.txt");
#else
	referenceFile = FastMathF64_Log1_f64;
	referenceFileLen = sizeof(FastMathF64_Log1_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, 2, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, 2, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f64(referenceFile, f64output1, 2, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f64(referenceData_f64, f64output1, 2, ABS_ERROR, REL_ERROR);
#endif

	printf("\n== mips_vlog_f64 2 check done  == \n\n");

	// =====================

	memset(f64output1, 0, sizeof(f64output1));
	inp = f64input1;
	outp = f64output1;

	printf("== mips_vlog_f64 2n test ==  \n");

	mips_vlog_f64(inp, outp, 4);

	printf("mips_vlog_f64 finish \n");

	printf("mips_vlog_f64 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FastMathF64, "Log1_f64.txt");
#else
	referenceFile = FastMathF64_Log1_f64;
	referenceFileLen = sizeof(FastMathF64_Log1_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, 4, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, 4, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f64(referenceFile, f64output1, 4, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f64(referenceData_f64, f64output1, 4, ABS_ERROR, REL_ERROR);
#endif

	printf("\n== mips_vlog_f64 2n check done  == \n\n");

	// =====================

	memset(f64output1, 0, sizeof(f64output1));
	inp = f64input1;
	outp = f64output1;

	printf("== mips_vlog_f64 2n+1 test ==  \n");

	mips_vlog_f64(inp, outp, 5);

	printf("mips_vlog_f64 finish \n");

	printf("mips_vlog_f64 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FastMathF64, "Log1_f64.txt");
#else
	referenceFile = FastMathF64_Log1_f64;
	referenceFileLen = sizeof(FastMathF64_Log1_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, 5, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, 5, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f64(referenceFile, f64output1, 5, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f64(referenceData_f64, f64output1, 5, ABS_ERROR, REL_ERROR);
#endif

	printf("\n== mips_vlog_f64 2n+1 check done  == \n\n");

	// =====================

	inp = f64input1;
	outp = f64output1;

#if defined(NOT_EMBEDDED)
	snprintf(inputFileT, sizeof(inputFileT), "%s%s%s", Patterns_PATH, FastMathF64, "Exp1_f64.txt");
#else
	inputFileT = FastMathF64_Exp1_f64;
	inputFileTLen = sizeof(FastMathF64_Exp1_f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(inputFileT, &paramCountInputT, f64inputT);
#else
	paramCountInputT = inputFileTLen;
	load_data_f64(inputFileT, paramCountInputT, f64inputT);
	paramCountInputT = paramCountInputT/sizeof(f64);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(inputFile1, sizeof(inputFile1), "%s%s%s", Patterns_PATH, FastMathF64, "ExpInput1_f64.txt");
#else
	inputFile1 = FastMathF64_ExpInput1_f64;
	inputFile1Len = sizeof(FastMathF64_ExpInput1_f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(inputFile1, &paramCountInput1, f64input1);
#else
	paramCountInput1 = inputFile1Len;
	load_data_f64(inputFile1, paramCountInput1, f64input1);
	paramCountInput1 = paramCountInput1/sizeof(f64);
#endif


	printf("== mips_vexp_f64 long test ==  \n");

	mips_vexp_f64(inp, outp, paramCountInputT);

	printf("mips_vexp_f64 finish \n");

	printf("mips_vexp_f64 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FastMathF64, "Exp1_f64.txt");
#else
	referenceFile = FastMathF64_Exp1_f64;
	referenceFileLen = sizeof(FastMathF64_Exp1_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
	referenceFileLen = referenceFileLen/sizeof(f64);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f64(referenceFile, f64output1, 0, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f64(referenceData_f64, f64output1, referenceFileLen, ABS_ERROR, REL_ERROR);
#endif

	printf("\n== mips_vexp_f64 long check done  == \n\n");

	// =====================

	memset(f64output1, 0, sizeof(f64output1));
	inp = f64input1;
	outp = f64output1;

	printf("== mips_vexp_f64 2 test ==  \n");

	mips_vexp_f64(inp, outp, 2);

	printf("mips_vexp_f64 finish \n");

	printf("mips_vexp_f64 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FastMathF64, "Exp1_f64.txt");
#else
	referenceFile = FastMathF64_Exp1_f64;
	referenceFileLen = sizeof(FastMathF64_Exp1_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, 2, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, 2, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f64(referenceFile, f64output1, 2, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f64(referenceData_f64, f64output1, 2, ABS_ERROR, REL_ERROR);
#endif

	printf("\n== mips_vexp_f64 2 check done  == \n\n");

	// =====================

	memset(f64output1, 0, sizeof(f64output1));
	inp = f64input1;
	outp = f64output1;

	printf("== mips_vexp_f64 2n test ==  \n");

	mips_vexp_f64(inp, outp, 4);

	printf("mips_vexp_f64 finish \n");

	printf("mips_vexp_f64 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FastMathF64, "Exp1_f64.txt");
#else
	referenceFile = FastMathF64_Exp1_f64;
	referenceFileLen = sizeof(FastMathF64_Exp1_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, 4, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, 4, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f64(referenceFile, f64output1, 4, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f64(referenceData_f64, f64output1, 4, ABS_ERROR, REL_ERROR);
#endif

	printf("\n== mips_vexp_f64 2n check done  == \n\n");

	// =====================

	memset(f64output1, 0, sizeof(f64output1));
	inp = f64input1;
	outp = f64output1;

	printf("== mips_vexp_f64 2n+1 test ==  \n");

	mips_vexp_f64(inp, outp, 5);

	printf("mips_vexp_f64 finish \n");

	printf("mips_vexp_f64 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FastMathF64, "Exp1_f64.txt");
#else
	referenceFile = FastMathF64_Exp1_f64;
	referenceFileLen = sizeof(FastMathF64_Exp1_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output1, 5, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, 5, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f64(referenceFile, f64output1, 5, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f64(referenceData_f64, f64output1, 5, ABS_ERROR, REL_ERROR);
#endif

	printf("\n== mips_vexp_f64 2n+1 check done  == \n\n");

	// =====================

	return 0;
}