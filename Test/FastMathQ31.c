#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/fast_math_functions.h"

#include "mips_common_tables.h"
#include "dsp/utils.h"

#define SNR_THRESHOLD 100
/* 

Reference patterns are generated with
a double precision computation.

*/
#define ABS_SQRT_ERROR ((q31)7)

#define ABS_ERROR ((q31)2200)
#define ABS_DIV_ERROR ((q31)2)
#define LOG_ABS_ERROR ((q31)2)

#define ABS_ATAN_ERROR ((q31)3)
#define RECIP_ERROR ((q31)10)

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
	q31 q31inputLog[MAX_SIZE] = {0};
	q31 q31inputSqrt[MAX_SIZE] = {0};
	q31 q31inputAngle[MAX_SIZE] = {0};
	q31 q31inputT[MAX_SIZE] = {0};


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
	snprintf(inputFileLog, sizeof(inputFileLog), "%s%s%s", Patterns_PATH, FastMathQ31, "LogInput1_q31.txt");
#else
	inputFileLog = FastMathQ31_LogInput1_q31;
	inputFileLogLen = sizeof(FastMathQ31_LogInput1_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileSqrt, sizeof(inputFileSqrt), "%s%s%s", Patterns_PATH, FastMathQ31, "SqrtInput1_q31.txt");
#else
	inputFileSqrt = FastMathQ31_SqrtInput1_q31;
	inputFileSqrtLen = sizeof(FastMathQ31_SqrtInput1_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileAngle, sizeof(inputFileAngle), "%s%s%s", Patterns_PATH, FastMathQ31, "Angles1_q31.txt");
#else
	inputFileAngle = FastMathQ31_Angles1_q31;
	inputFileAngleLen = sizeof(FastMathQ31_Angles1_q31);
#endif


	// load input data
#if defined(NOT_EMBEDDED)
	load_data_q31(inputFileLog, &paramCountInputLog, q31inputLog);
#else
	paramCountInputLog = inputFileLogLen;
	load_data_q31(inputFileLog, paramCountInputLog, q31inputLog);
	paramCountInputLog = paramCountInputLog/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(inputFileSqrt, &paramCountInputSqrt, q31inputSqrt);
#else
	paramCountInputSqrt = inputFileSqrtLen;
	load_data_q31(inputFileSqrt, paramCountInputSqrt, q31inputSqrt);
	paramCountInputSqrt = paramCountInputSqrt/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(inputFileAngle, &paramCountInputAngle, q31inputAngle);
#else
	paramCountInputAngle = inputFileAngleLen;
	load_data_q31(inputFileAngle, paramCountInputAngle, q31inputAngle);
	paramCountInputAngle = paramCountInputAngle/sizeof(q31);
#endif


	q31 q31output1[MAX_SIZE] = {0};
	int16_t shift[MAX_SIZE] = {0};
	q31 numerator[MAX_SIZE] = {0};
	q31 denominator[MAX_SIZE] = {0};

	// =====================

	q31 *inp = q31inputAngle;
	q31 *outp = q31output1;

	printf("== mips_cos_q31 test ==  \n");

	unsigned long i;

	for (i = 0; i < paramCountInputAngle; i++)
	{
		outp[i] = mips_cos_q31(inp[i]);
	}

	printf("mips_cos_q31 finish \n");

	printf("mips_cos_q31 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FastMathQ31, "Cos1_q31.txt");
#else
	referenceFile = FastMathQ31_Cos1_q31;
	referenceFileLen = sizeof(FastMathQ31_Cos1_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile, q31output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, q31output1, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile, q31output1, 0, ABS_ERROR);
#else
	near_check_special_q31(referenceData_q31, q31output1, referenceFileLen, ABS_ERROR);
#endif

	printf("\n== mips_cos_q31 check done  == \n\n");

	// =====================

	inp = q31inputAngle;
	outp = q31output1;

	printf("== mips_sin_q31 test ==  \n");

	for (i = 0; i < paramCountInputAngle; i++)
	{
		outp[i] = mips_sin_q31(inp[i]);
	}

	printf("mips_sin_q31 finish \n");

	printf("mips_sin_q31 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FastMathQ31, "Sin1_q31.txt");
#else
	referenceFile = FastMathQ31_Sin1_q31;
	referenceFileLen = sizeof(FastMathQ31_Sin1_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile, q31output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, q31output1, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile, q31output1, 0, ABS_ERROR);
#else
	near_check_special_q31(referenceData_q31, q31output1, referenceFileLen, ABS_ERROR);
#endif

	printf("\n== mips_sin_q31 check done  == \n\n");

	// =====================

	inp = q31inputSqrt;
	outp = q31output1;
	mips_status status;

	printf("== mips_sqrt_q31 test ==  \n");

	for (i = 0; i < paramCountInputSqrt; i++)
	{
		status = mips_sqrt_q31(inp[i], &outp[i]);
		ASSERT_TRUE((status == MIPS_MATH_SUCCESS) || ((inp[i] <= 0) && (status == MIPS_MATH_ARGUMENT_ERROR)));
	}

	printf("mips_sqrt_q31 finish \n");

	printf("mips_sqrt_q31 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FastMathQ31, "Sqrt1_q31.txt");
#else
	referenceFile = FastMathQ31_Sqrt1_q31;
	referenceFileLen = sizeof(FastMathQ31_Sqrt1_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
	referenceFileLen = referenceFileLen/sizeof(q31);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile, q31output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, q31output1, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile, q31output1, 0, ABS_SQRT_ERROR);
#else
	near_check_special_q31(referenceData_q31, q31output1, referenceFileLen, ABS_SQRT_ERROR);
#endif

	printf("\n== mips_sqrt_q31 check done  == \n\n");

	// =====================

	outp = q31output1;

#if defined(NOT_EMBEDDED)
	snprintf(inputFileT, sizeof(inputFileAngle), "%s%s%s", Patterns_PATH, FastMathQ31, "Numerator1_q31.txt");
#else
	inputFileT = FastMathQ31_Numerator1_q31;
	inputFileTLen = sizeof(FastMathQ31_Numerator1_q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(inputFileT, &paramCountInputT, numerator);
#else
	paramCountInputT = inputFileTLen;
	load_data_q31(inputFileT, paramCountInputT, numerator);
	paramCountInputT = paramCountInputT/sizeof(q31);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(inputFileT, sizeof(inputFileAngle), "%s%s%s", Patterns_PATH, FastMathQ31, "Denominator1_q31.txt");
#else
	inputFileT = FastMathQ31_Denominator1_q31;
	inputFileTLen = sizeof(FastMathQ31_Denominator1_q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(inputFileT, &paramCountInputT, denominator);
#else
	paramCountInputT = inputFileTLen;
	load_data_q31(inputFileT, paramCountInputT, denominator);
	paramCountInputT = paramCountInputT/sizeof(q31);
#endif


	const q31 *nump = numerator;
	const q31 *denp = denominator;
	int16_t *shiftp = shift;

	printf("== mips_divide_q31 test ==  \n");

	for (i = 0; i < paramCountInputT; i++)
	{
		status = mips_divide_q31(nump[i], denp[i], &outp[i], &shiftp[i]);
	}
	(void)status;

	printf("mips_divide_q31 finish \n");

	printf("mips_divide_q31 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FastMathQ31, "DivisionValue1_q31.txt");
#else
	referenceFile = FastMathQ31_DivisionValue1_q31;
	referenceFileLen = sizeof(FastMathQ31_DivisionValue1_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile, q31output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, q31output1, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile, q31output1, 0, ABS_DIV_ERROR);
#else
	near_check_special_q31(referenceData_q31, q31output1, referenceFileLen, ABS_DIV_ERROR);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FastMathQ31, "DivisionShift1_s16.txt");
#else
	referenceFile = FastMathQ31_DivisionShift1_s16;
	referenceFileLen = sizeof(FastMathQ31_DivisionShift1_s16);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
	referenceFileLen = referenceFileLen/sizeof(q15);

#endif

#if defined(NOT_EMBEDDED)
	eq_check_q15(referenceFile, shift, 0);
#else
	eq_check_special_q15(referenceData_q15, shift, referenceFileLen);
#endif


	printf("\n== mips_divide_q31 check done  == \n\n");

	// =====================

	inp = q31inputLog;
	outp = q31output1;

	printf("== mips_vlog_q31 test all ==  \n");

	mips_vlog_q31(inp, outp, paramCountInputLog);

	printf("mips_vlog_q31 finish \n");

	printf("mips_vlog_q31 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FastMathQ31, "Log1_q31.txt");
#else
	referenceFile = FastMathQ31_Log1_q31;
	referenceFileLen = sizeof(FastMathQ31_Log1_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
	referenceFileLen = referenceFileLen/sizeof(q31);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile, q31output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, q31output1, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile, q31output1, 0, LOG_ABS_ERROR);
#else
	near_check_special_q31(referenceData_q31, q31output1, referenceFileLen, LOG_ABS_ERROR);
#endif

	printf("\n== mips_vlog_q31 all check done  == \n\n");

	// =====================

	memset(q31output1, 0, sizeof(q31output1));
	inp = q31inputLog;
	outp = q31output1;

	printf("== mips_vlog_q31 test 7 ==  \n");

	mips_vlog_q31(inp, outp, 7);

	printf("mips_vlog_q31 finish \n");

	printf("mips_vlog_q31 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FastMathQ31, "Log1_q31.txt");
#else
	referenceFile = FastMathQ31_Log1_q31;
	referenceFileLen = sizeof(FastMathQ31_Log1_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile, q31output1, 7, SNR_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, q31output1, 7, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile, q31output1, 7, LOG_ABS_ERROR);
#else
	near_check_special_q31(referenceData_q31, q31output1, 7, LOG_ABS_ERROR);
#endif

	printf("\n== mips_vlog_q31 7 check done  == \n\n");

	// =====================

	memset(q31output1, 0, sizeof(q31output1));
	inp = q31inputLog;
	outp = q31output1;

	printf("== mips_vlog_q31 test 16 ==  \n");

	mips_vlog_q31(inp, outp, 16);

	printf("mips_vlog_q31 finish \n");

	printf("mips_vlog_q31 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FastMathQ31, "Log1_q31.txt");
#else
	referenceFile = FastMathQ31_Log1_q31;
	referenceFileLen = sizeof(FastMathQ31_Log1_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
	referenceFileLen = referenceFileLen/sizeof(q31);

#endif


#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile, q31output1, 16, SNR_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, q31output1, 16, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile, q31output1, 16, LOG_ABS_ERROR);
#else
	near_check_special_q31(referenceData_q31, q31output1, 16, LOG_ABS_ERROR);
#endif

	printf("\n== mips_vlog_q31 16 check done  == \n\n");

	// =====================

	memset(q31output1, 0, sizeof(q31output1));
	inp = q31inputLog;
	outp = q31output1;

	printf("== mips_vlog_q31 test 23 ==  \n");

	mips_vlog_q31(inp, outp, 23);

	printf("mips_vlog_q31 finish \n");

	printf("mips_vlog_q31 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FastMathQ31, "Log1_q31.txt");
#else
	referenceFile = FastMathQ31_Log1_q31;
	referenceFileLen = sizeof(FastMathQ31_Log1_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile, q31output1, 23, SNR_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, q31output1, 23, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile, q31output1, 23, LOG_ABS_ERROR);
#else
	near_check_special_q31(referenceData_q31, q31output1, 23, LOG_ABS_ERROR);
#endif

	printf("\n== mips_vlog_q31 23 check done  == \n\n");

	// =====================

	outp = q31output1;
	q31 res;

	int paramCountInputRefTmp = 0;

#if defined(NOT_EMBEDDED)
	snprintf(inputFileT, sizeof(inputFileAngle), "%s%s%s", Patterns_PATH, FastMathQ31, "Atan2Ref1_q31.txt");
#else
	inputFileT = FastMathQ31_Atan2Ref1_q31;
	inputFileTLen = sizeof(FastMathQ31_Atan2Ref1_q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(inputFileT, &paramCountInputRefTmp, q31inputT);
#else
	paramCountInputRefTmp = inputFileTLen;
	load_data_q31(inputFileT, paramCountInputRefTmp, q31inputT);
	paramCountInputRefTmp = paramCountInputRefTmp/sizeof(q31);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(inputFileT, sizeof(inputFileAngle), "%s%s%s", Patterns_PATH, FastMathQ31, "Atan2Input1_q31.txt");
#else
	inputFileT = FastMathQ31_Atan2Input1_q31;
	inputFileTLen = sizeof(FastMathQ31_Atan2Input1_q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(inputFileT, &paramCountInputT, q31inputT);
#else
	paramCountInputT = inputFileTLen;
	load_data_q31(inputFileT, paramCountInputT, q31inputT);
	paramCountInputT = paramCountInputT/sizeof(q31);
#endif


	inp = q31inputT;
	status = MIPS_MATH_SUCCESS;

	printf("== mips_atan2_q31 test ==  \n");

	for (i = 0; i < paramCountInputRefTmp; i++)
	{
		status = mips_atan2_q31(inp[2 * i], inp[2 * i + 1], &res);
		outp[i] = res;

		ASSERT_TRUE((status == MIPS_MATH_SUCCESS));
	}

	printf("mips_atan2_q31 finish \n");

	printf("mips_atan2_q31 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FastMathQ31, "Atan2Ref1_q31.txt");
#else
	referenceFile = FastMathQ31_Atan2Ref1_q31;
	referenceFileLen = sizeof(FastMathQ31_Atan2Ref1_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
	referenceFileLen = referenceFileLen/sizeof(q31);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile, q31output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, q31output1, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile, q31output1, 0, ABS_ATAN_ERROR);
#else
	near_check_special_q31(referenceData_q31, q31output1, referenceFileLen, ABS_ATAN_ERROR);
#endif


	printf("\n== mips_atan2_q31 check done  == \n\n");

	// =====================

	outp = q31output1;

#if defined(NOT_EMBEDDED)
	snprintf(inputFileT, sizeof(inputFileAngle), "%s%s%s", Patterns_PATH, FastMathQ31, "RecipRef1_q31.txt");
#else
	inputFileT = FastMathQ31_RecipRef1_q31;
	inputFileTLen = sizeof(FastMathQ31_RecipRef1_q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(inputFileT, &paramCountInputRefTmp, q31inputT);
#else
	paramCountInputRefTmp = inputFileTLen;
	load_data_q31(inputFileT, paramCountInputRefTmp, q31inputT);
	paramCountInputRefTmp = paramCountInputRefTmp/sizeof(q31);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(inputFileT, sizeof(inputFileAngle), "%s%s%s", Patterns_PATH, FastMathQ31, "RecipInput1_q31.txt");
#else
	inputFileT = FastMathQ31_RecipInput1_q31;
	inputFileTLen = sizeof(FastMathQ31_RecipInput1_q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(inputFileT, &paramCountInputT, q31inputT);
#else
	paramCountInputT = inputFileTLen;
	load_data_q31(inputFileT, paramCountInputT, q31inputT);
	paramCountInputT = paramCountInputT/sizeof(q31);
#endif

	inp = q31inputT;

	shiftp = shift;

	printf("== mips_recip_q31 test ==  \n");

	for (i = 0; i < paramCountInputRefTmp; i++)
	{
          shiftp[i] = mips_recip_q31(inp[i],&outp[i],mipsRecipTableQ31);
	}

	printf("mips_recip_q31 finish \n");

	printf("mips_recip_q31 checking \n\n");
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FastMathQ31, "RecipRef1_q31.txt");
#else
	referenceFile = FastMathQ31_RecipRef1_q31;
	referenceFileLen = sizeof(FastMathQ31_RecipRef1_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
	referenceFileLen = referenceFileLen/sizeof(q31);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile, q31output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, q31output1, referenceFileLen, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile, q31output1, 0, RECIP_ERROR);
#else
	near_check_special_q31(referenceData_q31, q31output1, referenceFileLen, RECIP_ERROR);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FastMathQ31, "RecipShift1_s16.txt");
#else
	referenceFile = FastMathQ31_RecipShift1_s16;
	referenceFileLen = sizeof(FastMathQ31_RecipShift1_s16);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
	referenceFileLen = referenceFileLen/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	eq_check_q15(referenceFile, shift, 0);
#else
	eq_check_special_q15(referenceData_q15, shift, referenceFileLen);
#endif


	printf("\n== mips_recip_q31 check done  == \n\n");

	// =====================


	return 0;
}
