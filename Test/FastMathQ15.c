#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/fast_math_functions.h"

#include "mips_common_tables.h"
#include "dsp/utils.h"

#define SNR_THRESHOLD (f32)69
/*

Reference patterns are generated with
a double precision computation.

*/
#define ABS_SQRT_ERROR ((q15)6)

#define ABS_ERROR ((q15)10)

#define LOG_ABS_ERROR ((q15)3)
#define ABS_ATAN_ERROR ((q15)3)
#define DIV_ERROR ((q15)2)
#define RECIP_ERROR ((q15)2)

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
	int paramCountInputLog = 0;
	int paramCountInputSqrt = 0;
	int paramCountInputAngle = 0;
	int paramCountInputT = 0;
	q15 q15inputLog[MAX_SIZE] = {0};
	q15 q15inputSqrt[MAX_SIZE] = {0};
	q15 q15inputAngle[MAX_SIZE] = {0};
	q15 q15inputT[MAX_SIZE] = {0};


	// file name. file path max length is 255, so use 255.
#if defined(NOT_EMBEDDED)
	char inputFileLog[255] = {0};
#else
	void *inputFileLog;
	int inputFileLogLen = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFileSqrt[255] = {0};
#else
	void *inputFileSqrt;
	int inputFileSqrtLen = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFileAngle[255] = {0};
#else
	void *inputFileAngle;
	int inputFileAngleLen = 0;
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
	snprintf(inputFileLog, sizeof(inputFileLog), "%s%s%s", Patterns_PATH, FastMathQ15, "LogInput1_q15.txt");
#else
	inputFileLog = FastMathQ15_LogInput1_q15;
	inputFileLogLen = sizeof(FastMathQ15_LogInput1_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileSqrt, sizeof(inputFileSqrt), "%s%s%s", Patterns_PATH, FastMathQ15, "SqrtInput1_q15.txt");
#else
	inputFileSqrt = FastMathQ15_SqrtInput1_q15;
	inputFileSqrtLen = sizeof(FastMathQ15_SqrtInput1_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileAngle, sizeof(inputFileAngle), "%s%s%s", Patterns_PATH, FastMathQ15, "Angles1_q15.txt");
#else
	inputFileAngle = FastMathQ15_Angles1_q15;
	inputFileAngleLen = sizeof(FastMathQ15_Angles1_q15);
#endif


	// load input data
#if defined(NOT_EMBEDDED)
	load_data_q15(inputFileLog, &paramCountInputLog, q15inputLog);
#else
	paramCountInputLog = inputFileLogLen;
	load_data_q15(inputFileLog, paramCountInputLog, q15inputLog);
	paramCountInputLog = paramCountInputLog/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(inputFileSqrt, &paramCountInputSqrt, q15inputSqrt);
#else
	paramCountInputSqrt = inputFileSqrtLen;
	load_data_q15(inputFileSqrt, paramCountInputSqrt, q15inputSqrt);
	paramCountInputSqrt = paramCountInputSqrt/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(inputFileAngle, &paramCountInputAngle, q15inputAngle);
#else
	paramCountInputAngle = inputFileAngleLen;
	load_data_q15(inputFileAngle, paramCountInputAngle, q15inputAngle);
	paramCountInputAngle = paramCountInputAngle/sizeof(q15);
#endif


	q15 q15output1[MAX_SIZE] = {0};
	int16_t shift[MAX_SIZE] = {0};
	q15 numerator[MAX_SIZE] = {0};
	q15 denominator[MAX_SIZE] = {0};

	// =====================

	q15 *inp = q15inputAngle;
	q15 *outp = q15output1;

	printf("== mips_cos_q15 test ==  \n");

	unsigned long i;

	for (i = 0; i < paramCountInputAngle; i++)
	{
		outp[i] = mips_cos_q15(inp[i]);
	}

	printf("mips_cos_q15 finish \n");

	printf("mips_cos_q15 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FastMathQ15, "Cos1_q15.txt");
#else
	referenceFile = FastMathQ15_Cos1_q15;
	referenceFileLen = sizeof(FastMathQ15_Cos1_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output1, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output1, 0, ABS_ERROR);
#else
	near_check_special_q15(referenceData_q15, q15output1, referenceFileLen, ABS_ERROR);
#endif

	printf("\n== mips_cos_q15 check done  == \n\n");

	// =====================

	inp = q15inputAngle;
	outp = q15output1;

	printf("== mips_sin_q15 test ==  \n");

	for (i = 0; i < paramCountInputAngle; i++)
	{
		outp[i] = mips_sin_q15(inp[i]);
	}

	printf("mips_sin_q15 finish \n");

	printf("mips_sin_q15 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FastMathQ15, "Sin1_q15.txt");
#else
	referenceFile = FastMathQ15_Sin1_q15;
	referenceFileLen = sizeof(FastMathQ15_Sin1_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output1, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output1, 0, ABS_ERROR);
#else
	near_check_special_q15(referenceData_q15, q15output1, referenceFileLen, ABS_ERROR);
#endif

	printf("\n== mips_sin_q15 check done  == \n\n");

	// =====================

	inp = q15inputSqrt;
	outp = q15output1;
	mips_status status;

	printf("== mips_sqrt_q15 test ==  \n");

	for (i = 0; i < paramCountInputSqrt; i++)
	{
		status = mips_sqrt_q15(inp[i], &outp[i]);
		ASSERT_TRUE((status == MIPS_MATH_SUCCESS) || ((inp[i] <= 0) && (status == MIPS_MATH_ARGUMENT_ERROR)));
	}

	printf("mips_sqrt_q15 finish \n");

	printf("mips_sqrt_q15 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FastMathQ15, "Sqrt1_q15.txt");
#else
	referenceFile = FastMathQ15_Sqrt1_q15;
	referenceFileLen = sizeof(FastMathQ15_Sqrt1_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
	referenceFileLen = referenceFileLen/sizeof(q15);

#endif


#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output1, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output1, 0, ABS_SQRT_ERROR);
#else
	near_check_special_q15(referenceData_q15, q15output1, referenceFileLen, ABS_SQRT_ERROR);
#endif

	printf("\n== mips_sqrt_q15 check done  == \n\n");

	// =====================

	outp = q15output1;

#if defined(NOT_EMBEDDED)
	snprintf(inputFileT, sizeof(inputFileAngle), "%s%s%s", Patterns_PATH, FastMathQ15, "Numerator1_q15.txt");
#else
	inputFileT = FastMathQ15_Numerator1_q15;
	inputFileTLen = sizeof(FastMathQ15_Numerator1_q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(inputFileT, &paramCountInputT, numerator);
#else
	paramCountInputT = inputFileTLen;
	load_data_q15(inputFileT, paramCountInputT, numerator);
	paramCountInputT = paramCountInputT/sizeof(q15);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(inputFileT, sizeof(inputFileAngle), "%s%s%s", Patterns_PATH, FastMathQ15, "Denominator1_q15.txt");
#else
	inputFileT = FastMathQ15_Denominator1_q15;
	inputFileTLen = sizeof(FastMathQ15_Denominator1_q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(inputFileT, &paramCountInputT, denominator);
#else
	paramCountInputT = inputFileTLen;
	load_data_q15(inputFileT, paramCountInputT, denominator);
	paramCountInputT = paramCountInputT/sizeof(q15);
#endif


	const q15 *nump = numerator;
	const q15 *denp = denominator;
	int16_t *shiftp = shift;

	printf("== mips_divide_q15 test ==  \n");

	for (i = 0; i < paramCountInputT; i++)
	{
		status = mips_divide_q15(nump[i], denp[i], &outp[i], &shiftp[i]);
	}
	(void)status;

	printf("mips_divide_q15 finish \n");

	printf("mips_divide_q15 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FastMathQ15, "DivisionValue1_q15.txt");
#else
	referenceFile = FastMathQ15_DivisionValue1_q15;
	referenceFileLen = sizeof(FastMathQ15_DivisionValue1_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output1, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output1, 0, DIV_ERROR);
#else
	near_check_special_q15(referenceData_q15, q15output1, referenceFileLen, DIV_ERROR);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FastMathQ15, "DivisionShift1_s16.txt");
#else
	referenceFile = FastMathQ15_DivisionShift1_s16;
	referenceFileLen = sizeof(FastMathQ15_DivisionShift1_s16);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
	referenceFileLen = referenceFileLen/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	eq_check_q15(referenceFile, shift, 0);
#else
	eq_check_special_q15(referenceData_q15, shift, referenceFileLen);
#endif


	printf("\n== mips_divide_q15 check done  == \n\n");

	// =====================

	inp = q15inputLog;
	outp = q15output1;

	printf("== mips_vlog_q15 test all ==  \n");

	mips_vlog_q15(inp, outp, paramCountInputLog);

	printf("mips_vlog_q15 finish \n");

	printf("mips_vlog_q15 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FastMathQ15, "Log1_q15.txt");
#else
	referenceFile = FastMathQ15_Log1_q15;
	referenceFileLen = sizeof(FastMathQ15_Log1_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
	referenceFileLen = referenceFileLen/sizeof(q15);

#endif


#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output1, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output1, 0, LOG_ABS_ERROR);
#else
	near_check_special_q15(referenceData_q15, q15output1, referenceFileLen, LOG_ABS_ERROR);
#endif

	printf("\n== mips_vlog_q15 all check done  == \n\n");

	// =====================

	memset(q15output1, 0, sizeof(q15output1));
	inp = q15inputLog;
	outp = q15output1;

	printf("== mips_vlog_q15 test 7 ==  \n");

	mips_vlog_q15(inp, outp, 7);

	printf("mips_vlog_q15 finish \n");

	printf("mips_vlog_q15 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FastMathQ15, "Log1_q15.txt");
#else
	referenceFile = FastMathQ15_Log1_q15;
	referenceFileLen = sizeof(FastMathQ15_Log1_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output1, 7, SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output1, 7, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output1, 7, LOG_ABS_ERROR);
#else
	near_check_special_q15(referenceData_q15, q15output1, 7, LOG_ABS_ERROR);
#endif

	printf("\n== mips_vlog_q15 7 check done  == \n\n");

	// =====================

	memset(q15output1, 0, sizeof(q15output1));
	inp = q15inputLog;
	outp = q15output1;

	printf("== mips_vlog_q15 test 16 ==  \n");

	mips_vlog_q15(inp, outp, 16);

	printf("mips_vlog_q15 finish \n");

	printf("mips_vlog_q15 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FastMathQ15, "Log1_q15.txt");
#else
	referenceFile = FastMathQ15_Log1_q15;
	referenceFileLen = sizeof(FastMathQ15_Log1_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output1, 16, SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output1, 16, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output1, 16, LOG_ABS_ERROR);
#else
	near_check_special_q15(referenceData_q15, q15output1, 16, LOG_ABS_ERROR);
#endif

	printf("\n== mips_vlog_q15 16 check done  == \n\n");

	// =====================

	memset(q15output1, 0, sizeof(q15output1));
	inp = q15inputLog;
	outp = q15output1;

	printf("== mips_vlog_q15 test 23 ==  \n");

	mips_vlog_q15(inp, outp, 23);

	printf("mips_vlog_q15 finish \n");

	printf("mips_vlog_q15 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FastMathQ15, "Log1_q15.txt");
#else
	referenceFile = FastMathQ15_Log1_q15;
	referenceFileLen = sizeof(FastMathQ15_Log1_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output1, 23, SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output1, 23, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output1, 23, LOG_ABS_ERROR);
#else
	near_check_special_q15(referenceData_q15, q15output1, 23, LOG_ABS_ERROR);
#endif

	printf("\n== mips_vlog_q15 23 check done  == \n\n");

	// =====================

	outp = q15output1;
	q15 res;

	int paramCountInputRefTmp = 0;

#if defined(NOT_EMBEDDED)
	snprintf(inputFileT, sizeof(inputFileAngle), "%s%s%s", Patterns_PATH, FastMathQ15, "Atan2Ref1_q15.txt");
#else
	inputFileT = FastMathQ15_Atan2Ref1_q15;
	inputFileTLen = sizeof(FastMathQ15_Atan2Ref1_q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(inputFileT, &paramCountInputRefTmp, q15inputT);
#else
	paramCountInputRefTmp = inputFileTLen;
	load_data_q15(inputFileT, paramCountInputRefTmp, q15inputT);
	paramCountInputRefTmp = paramCountInputRefTmp/sizeof(q15);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(inputFileT, sizeof(inputFileAngle), "%s%s%s", Patterns_PATH, FastMathQ15, "Atan2Input1_q15.txt");
#else
	inputFileT = FastMathQ15_Atan2Input1_q15;
	inputFileTLen = sizeof(FastMathQ15_Atan2Input1_q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(inputFileT, &paramCountInputT, q15inputT);
#else
	paramCountInputT = inputFileTLen;
	load_data_q15(inputFileT, paramCountInputT, q15inputT);
	paramCountInputT = paramCountInputT/sizeof(q15);
#endif


	inp = q15inputT;
	status = MIPS_MATH_SUCCESS;

	printf("== mips_atan2_q15 test ==  \n");

	for (i = 0; i < paramCountInputRefTmp; i++)
	{
		status = mips_atan2_q15(inp[2 * i], inp[2 * i + 1], &res);
		outp[i] = res;

		ASSERT_TRUE((status == MIPS_MATH_SUCCESS));
	}

	printf("mips_atan2_q15 finish \n");

	printf("mips_atan2_q15 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FastMathQ15, "Atan2Ref1_q15.txt");
#else
	referenceFile = FastMathQ15_Atan2Ref1_q15;
	referenceFileLen = sizeof(FastMathQ15_Atan2Ref1_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
	referenceFileLen = referenceFileLen/sizeof(q15);

#endif


#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output1, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output1, 0, ABS_ATAN_ERROR);
#else
	near_check_special_q15(referenceData_q15, q15output1, referenceFileLen, ABS_ATAN_ERROR);
#endif


	printf("\n== mips_atan2_q15 check done  == \n\n");

	// =====================

	outp = q15output1;

#if defined(NOT_EMBEDDED)
	snprintf(inputFileT, sizeof(inputFileAngle), "%s%s%s", Patterns_PATH, FastMathQ15, "RecipRef1_q15.txt");
#else
	inputFileT = FastMathQ15_RecipRef1_q15;
	inputFileTLen = sizeof(FastMathQ15_RecipRef1_q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(inputFileT, &paramCountInputRefTmp, q15inputT);
#else
	paramCountInputRefTmp = inputFileTLen;
	load_data_q15(inputFileT, paramCountInputRefTmp, q15inputT);
	paramCountInputRefTmp = paramCountInputRefTmp/sizeof(q15);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(inputFileT, sizeof(inputFileAngle), "%s%s%s", Patterns_PATH, FastMathQ15, "RecipInput1_q15.txt");
#else
	inputFileT = FastMathQ15_RecipInput1_q15;
	inputFileTLen = sizeof(FastMathQ15_RecipInput1_q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(inputFileT, &paramCountInputT, q15inputT);
#else
	paramCountInputT = inputFileTLen;
	load_data_q15(inputFileT, paramCountInputT, q15inputT);
	paramCountInputT = paramCountInputT/sizeof(q15);
#endif

	inp = q15inputT;

	shiftp = shift;

	printf("== mips_recip_q15 test ==  \n");

	for (i = 0; i < paramCountInputRefTmp; i++)
	{
          shiftp[i] = mips_recip_q15(inp[i],&outp[i],mipsRecipTableQ15);
	}

	printf("mips_recip_q15 finish \n");

	printf("mips_recip_q15 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FastMathQ15, "RecipRef1_q15.txt");
#else
	referenceFile = FastMathQ15_RecipRef1_q15;
	referenceFileLen = sizeof(FastMathQ15_RecipRef1_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
	referenceFileLen = referenceFileLen/sizeof(q15);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output1, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output1, 0, RECIP_ERROR);
#else
	near_check_special_q15(referenceData_q15, q15output1, referenceFileLen, RECIP_ERROR);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FastMathQ15, "RecipShift1_s16.txt");
#else
	referenceFile = FastMathQ15_RecipShift1_s16;
	referenceFileLen = sizeof(FastMathQ15_RecipShift1_s16);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
	referenceFileLen = referenceFileLen/sizeof(q15);

#endif

#if defined(NOT_EMBEDDED)
	eq_check_q15(referenceFile, shift, 0);
#else
	eq_check_special_q15(referenceData_q15, shift, referenceFileLen);
#endif


	printf("\n== mips_recip_q15 check done  == \n\n");

	// =====================


	return 0;
}
