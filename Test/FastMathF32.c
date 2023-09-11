#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/fast_math_functions.h"

#include "mips_common_tables.h"
#include "dsp/utils.h"

#define SNR_THRESHOLD 119
#define SNR_ATAN2_THRESHOLD 120

/*

Reference patterns are generated with
a double precision computation.

*/
#define REL_ERROR (1.0e-6)
#define ABS_ERROR (1.0e-5)

#define REL_ERROR_ATAN (5.0e-7)
#define ABS_ERROR_ATAN (5.0e-7)

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
	f32 f32input1[MAX_SIZE] = {0};
	f32 f32inputT[MAX_SIZE] = {0};

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
	snprintf(inputFile1, sizeof(inputFile1), "%s%s%s", Patterns_PATH, FastMathF32, "Angles1_f32.txt");
#else
	inputFile1 = FastMathF32_Angles1_f32;
	inputFile1Len = sizeof(FastMathF32_Angles1_f32);
#endif


	// load input data
#if defined(NOT_EMBEDDED)
	load_data_f32(inputFile1, &paramCountInput1, f32input1);
#else
	paramCountInput1 = inputFile1Len;
	load_data_f32(inputFile1, paramCountInput1, f32input1);
	paramCountInput1 = paramCountInput1/sizeof(f32);
#endif


	f32 f32output1[MAX_SIZE] = {0};

	// =====================

	f32 *inp = f32input1;
	f32 *outp = f32output1;

#if defined(NOT_EMBEDDED)
	snprintf(inputFileT, sizeof(inputFileT), "%s%s%s", Patterns_PATH, FastMathF32, "Cos1_f32.txt");
#else
	inputFileT = FastMathF32_Cos1_f32;
	inputFileTLen = sizeof(FastMathF32_Cos1_f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFileT, &paramCountInputT, f32inputT);
#else
	paramCountInputT = inputFileTLen;
	load_data_f32(inputFileT, paramCountInputT, f32inputT);
	paramCountInputT = paramCountInputT/sizeof(f32);
#endif


	printf("== mips_cos_f32 test ==  \n");

	unsigned long i;

	for (i = 0; i < paramCountInputT; i++)
	{
		outp[i] = mips_cos_f32(inp[i]);
	}

	printf("mips_cos_f32 finish \n");

	printf("mips_cos_f32 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FastMathF32, "Cos1_f32.txt");
#else
	referenceFile = FastMathF32_Cos1_f32;
	referenceFileLen = sizeof(FastMathF32_Cos1_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output1, 0, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output1, referenceFileLen, ABS_ERROR, REL_ERROR);
#endif

	printf("\n== mips_cos_f32 check done  == \n\n");

	// =====================

	inp = f32input1;
	outp = f32output1;

#if defined(NOT_EMBEDDED)
	snprintf(inputFileT, sizeof(inputFileT), "%s%s%s", Patterns_PATH, FastMathF32, "Sin1_f32.txt");
#else
	inputFileT = FastMathF32_Sin1_f32;
	inputFileTLen = sizeof(FastMathF32_Sin1_f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFileT, &paramCountInputT, f32inputT);
#else
	paramCountInputT = inputFileTLen;
	load_data_f32(inputFileT, paramCountInputT, f32inputT);
	paramCountInputT = paramCountInputT/sizeof(f32);
#endif


	printf("== mips_sin_f32 test ==  \n");

	for (i = 0; i < paramCountInputT; i++)
	{
		outp[i] = mips_sin_f32(inp[i]);
	}

	printf("mips_sin_f32 finish \n");

	printf("mips_sin_f32 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FastMathF32, "Sin1_f32.txt");
#else
	referenceFile = FastMathF32_Sin1_f32;
	referenceFileLen = sizeof(FastMathF32_Sin1_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output1, 0, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output1, referenceFileLen, ABS_ERROR, REL_ERROR);
#endif

	printf("\n== mips_sin_f32 check done  == \n\n");

	// =====================

	inp = f32input1;
	outp = f32output1;

#if defined(NOT_EMBEDDED)
	snprintf(inputFile1, sizeof(inputFile1), "%s%s%s", Patterns_PATH, FastMathF32, "SqrtInput1_f32.txt");
#else
	inputFile1 = FastMathF32_SqrtInput1_f32;
	inputFile1Len = sizeof(FastMathF32_SqrtInput1_f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFile1, &paramCountInput1, f32input1);
#else
	paramCountInput1 = inputFile1Len;
	load_data_f32(inputFile1, paramCountInput1, f32input1);
	paramCountInput1 = paramCountInput1/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(inputFileT, sizeof(inputFileT), "%s%s%s", Patterns_PATH, FastMathF32, "Sqrt1_f32.txt");
#else
	inputFileT = FastMathF32_Sqrt1_f32;
	inputFileTLen = sizeof(FastMathF32_Sqrt1_f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFileT, &paramCountInputT, f32inputT);
#else
	paramCountInputT = inputFileTLen;
	load_data_f32(inputFileT, paramCountInputT, f32inputT);
	paramCountInputT = paramCountInputT/sizeof(f32);
#endif


	printf("== mips_sqrt_f32 test ==  \n");
	mips_status status;

	for (i = 0; i < paramCountInputT; i++)
	{
		status = mips_sqrt_f32(inp[i], &outp[i]);
		ASSERT_TRUE((status == MIPS_MATH_SUCCESS) || ((inp[i] < 0.0f) && (status == MIPS_MATH_ARGUMENT_ERROR)));
	}

	printf("mips_sqrt_f32 finish \n");

	printf("mips_sqrt_f32 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FastMathF32, "Sqrt1_f32.txt");
#else
	referenceFile = FastMathF32_Sqrt1_f32;
	referenceFileLen = sizeof(FastMathF32_Sqrt1_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output1, 0, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output1, referenceFileLen, ABS_ERROR, REL_ERROR);
#endif

	printf("\n== mips_sqrt_f32 check done  == \n\n");

	// =====================

	inp = f32input1;
	outp = f32output1;

#if defined(NOT_EMBEDDED)
	snprintf(inputFileT, sizeof(inputFileT), "%s%s%s", Patterns_PATH, FastMathF32, "Log1_f32.txt");
#else
	inputFileT = FastMathF32_Log1_f32;
	inputFileTLen = sizeof(FastMathF32_Log1_f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFileT, &paramCountInputT, f32inputT);
#else
	paramCountInputT = inputFileTLen;
	load_data_f32(inputFileT, paramCountInputT, f32inputT);
	paramCountInputT = paramCountInputT/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(inputFile1, sizeof(inputFile1), "%s%s%s", Patterns_PATH, FastMathF32, "LogInput1_f32.txt");
#else
	inputFile1 = FastMathF32_LogInput1_f32;
	inputFile1Len = sizeof(FastMathF32_LogInput1_f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFile1, &paramCountInput1, f32input1);
#else
	paramCountInput1 = inputFile1Len;
	load_data_f32(inputFile1, paramCountInput1, f32input1);
	paramCountInput1 = paramCountInput1/sizeof(f32);
#endif


	printf("== mips_vlog_f32 long test ==  \n");

	mips_vlog_f32(inp, outp, paramCountInputT);

	printf("mips_vlog_f32 finish \n");

	printf("mips_vlog_f32 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FastMathF32, "Log1_f32.txt");
#else
	referenceFile = FastMathF32_Log1_f32;
	referenceFileLen = sizeof(FastMathF32_Log1_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output1, 0, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output1, referenceFileLen, ABS_ERROR, REL_ERROR);
#endif

	printf("\n== mips_vlog_f32 long check done  == \n\n");

	// =====================

	memset(f32output1, 0, sizeof(f32output1));
	inp = f32input1;
	outp = f32output1;

	printf("== mips_vlog_f32 2 test ==  \n");

	mips_vlog_f32(inp, outp, 3);

	printf("mips_vlog_f32 finish \n");

	printf("mips_vlog_f32 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FastMathF32, "Log1_f32.txt");
#else
	referenceFile = FastMathF32_Log1_f32;
	referenceFileLen = sizeof(FastMathF32_Log1_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, 3, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, 3, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output1, 3, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output1, 3, ABS_ERROR, REL_ERROR);
#endif

	printf("\n== mips_vlog_f32 2 check done  == \n\n");

	// =====================

	memset(f32output1, 0, sizeof(f32output1));
	inp = f32input1;
	outp = f32output1;

	printf("== mips_vlog_f32 2n test ==  \n");

	mips_vlog_f32(inp, outp, 8);

	printf("mips_vlog_f32 finish \n");

	printf("mips_vlog_f32 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FastMathF32, "Log1_f32.txt");
#else
	referenceFile = FastMathF32_Log1_f32;
	referenceFileLen = sizeof(FastMathF32_Log1_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, 8, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, 8, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output1, 8, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output1, 8, ABS_ERROR, REL_ERROR);
#endif

	printf("\n== mips_vlog_f32 2n check done  == \n\n");

	// =====================

	memset(f32output1, 0, sizeof(f32output1));
	inp = f32input1;
	outp = f32output1;

	printf("== mips_vlog_f32 2n+1 test ==  \n");

	mips_vlog_f32(inp, outp, 11);

	printf("mips_vlog_f32 finish \n");

	printf("mips_vlog_f32 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FastMathF32, "Log1_f32.txt");
#else
	referenceFile = FastMathF32_Log1_f32;
	referenceFileLen = sizeof(FastMathF32_Log1_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, 11, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, 11, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output1, 11, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output1, 11, ABS_ERROR, REL_ERROR);
#endif

	printf("\n== mips_vlog_f32 2n+1 check done  == \n\n");

	// =====================

	inp = f32input1;
	outp = f32output1;

#if defined(NOT_EMBEDDED)
	snprintf(inputFileT, sizeof(inputFileT), "%s%s%s", Patterns_PATH, FastMathF32, "Exp1_f32.txt");
#else
	inputFileT = FastMathF32_Exp1_f32;
	inputFileTLen = sizeof(FastMathF32_Exp1_f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFileT, &paramCountInputT, f32inputT);
#else
	paramCountInputT = inputFileTLen;
	load_data_f32(inputFileT, paramCountInputT, f32inputT);
	paramCountInputT = paramCountInputT/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(inputFile1, sizeof(inputFile1), "%s%s%s", Patterns_PATH, FastMathF32, "ExpInput1_f32.txt");
#else
	inputFile1 = FastMathF32_ExpInput1_f32;
	inputFile1Len = sizeof(FastMathF32_ExpInput1_f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFile1, &paramCountInput1, f32input1);
#else
	paramCountInput1 = inputFile1Len;
	load_data_f32(inputFile1, paramCountInput1, f32input1);
	paramCountInput1 = paramCountInput1/sizeof(f32);
#endif


	printf("== mips_vexp_f32 test ==  \n");

	mips_vexp_f32(inp, outp, paramCountInputT);

	printf("mips_vexp_f32 finish \n");

	printf("mips_vexp_f32 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FastMathF32, "Exp1_f32.txt");
#else
	referenceFile = FastMathF32_Exp1_f32;
	referenceFileLen = sizeof(FastMathF32_Exp1_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
	referenceFileLen = referenceFileLen/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output1, 0, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output1, referenceFileLen, ABS_ERROR, REL_ERROR);
#endif

	printf("\n== mips_vexp_f32 check done  == \n\n");

	// =====================

	memset(f32output1, 0, sizeof(f32output1));
	inp = f32input1;
	outp = f32output1;

	printf("== mips_vexp_f32 2 test ==  \n");

	mips_vexp_f32(inp, outp, 3);

	printf("mips_vexp_f32 finish \n");

	printf("mips_vexp_f32 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FastMathF32, "Exp1_f32.txt");
#else
	referenceFile = FastMathF32_Exp1_f32;
	referenceFileLen = sizeof(FastMathF32_Exp1_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, 3, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, 3, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output1, 3, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output1, 3, ABS_ERROR, REL_ERROR);
#endif

	printf("\n== mips_vexp_f32 2 check done  == \n\n");

	// =====================

	memset(f32output1, 0, sizeof(f32output1));
	inp = f32input1;
	outp = f32output1;

	printf("== mips_vexp_f32 2n test ==  \n");

	mips_vexp_f32(inp, outp, 8);

	printf("mips_vexp_f32 finish \n");

	printf("mips_vexp_f32 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FastMathF32, "Exp1_f32.txt");
#else
	referenceFile = FastMathF32_Exp1_f32;
	referenceFileLen = sizeof(FastMathF32_Exp1_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, 8, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, 8, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output1, 8, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output1, 8, ABS_ERROR, REL_ERROR);
#endif

	printf("\n== mips_vexp_f32 2n check done  == \n\n");

	// =====================

	memset(f32output1, 0, sizeof(f32output1));
	inp = f32input1;
	outp = f32output1;

	printf("== mips_vexp_f32 2n+1 test ==  \n");

	mips_vexp_f32(inp, outp, 11);

	printf("mips_vexp_f32 finish \n");

	printf("mips_vexp_f32 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FastMathF32, "Exp1_f32.txt");
#else
	referenceFile = FastMathF32_Exp1_f32;
	referenceFileLen = sizeof(FastMathF32_Exp1_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, 11, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, 11, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output1, 11, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output1, 11, ABS_ERROR, REL_ERROR);
#endif

	printf("\n== mips_vexp_f32 2n+1 check done  == \n\n");

	// =====================

	inp = f32input1;
	outp = f32output1;

#if defined(NOT_EMBEDDED)
	snprintf(inputFileT, sizeof(inputFileT), "%s%s%s", Patterns_PATH, FastMathF32, "Atan2Ref1_f32.txt");
#else
	inputFileT = FastMathF32_Atan2Ref1_f32;
	inputFileTLen = sizeof(FastMathF32_Atan2Ref1_f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFileT, &paramCountInputT, f32inputT);
#else
	paramCountInputT = inputFileTLen;
	load_data_f32(inputFileT, paramCountInputT, f32inputT);
	paramCountInputT = paramCountInputT/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(inputFile1, sizeof(inputFile1), "%s%s%s", Patterns_PATH, FastMathF32, "Atan2Input1_f32.txt");
#else
	inputFile1 = FastMathF32_Atan2Input1_f32;
	inputFile1Len = sizeof(FastMathF32_Atan2Input1_f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFile1, &paramCountInput1, f32input1);
#else
	paramCountInput1 = inputFile1Len;
	load_data_f32(inputFile1, paramCountInput1, f32input1);
	paramCountInput1 = paramCountInput1/sizeof(f32);
#endif


	printf("== mips_atan2_f32 test ==  \n");

	f32 res;
	status = MIPS_MATH_SUCCESS;
	for (i = 0; i < paramCountInputT; i++)
	{
		status = mips_atan2_f32(inp[2 * i], inp[2 * i + 1], &res);
		outp[i] = res;
		ASSERT_TRUE((status == MIPS_MATH_SUCCESS));
	}

	printf("mips_atan2_f32 finish \n");

	printf("mips_atan2_f32 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FastMathF32, "Atan2Ref1_f32.txt");
#else
	referenceFile = FastMathF32_Atan2Ref1_f32;
	referenceFileLen = sizeof(FastMathF32_Atan2Ref1_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, 0, SNR_ATAN2_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, referenceFileLen, SNR_ATAN2_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output1, 0, ABS_ERROR_ATAN, REL_ERROR_ATAN);
#else
	close_check_special_f32(referenceData_f32, f32output1, referenceFileLen, ABS_ERROR_ATAN, REL_ERROR_ATAN);
#endif

	printf("\n== mips_atan2_f32 check done  == \n\n");

	// =====================

	return 0;
}