#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/fast_math_functions.h"

#include "mips_common_tables.h"
#include "dsp/utils.h"

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
	int paramCountInputu64 = 0;
	int paramCountInputs64 = 0;
	int paramCountInputs32 = 0;
	int paramCountInputT = 0;
	uint64_t u64input[MAX_SIZE] = {0};
	q63 s64input[MAX_SIZE] = {0};
	q31 s32input[MAX_SIZE] = {0};
	q31 q31inputT[MAX_SIZE] = {0};

	// file name. file path max length is 255, so use 255.
#if defined(NOT_EMBEDDED)
	char inputFileu64[255] = {0};
#else
	void *inputFileu64;
	int inputFileu64Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFiles64[255] = {0};
#else
	void *inputFiles64;
	int inputFiles64Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFiles32[255] = {0};
#else
	void *inputFiles32;
	int inputFiles32Len = 0;
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
	snprintf(inputFileu64, 255, "%s%s%s", Patterns_PATH, FastMathQ63, "Norm64To32_Input1_u64.txt");
#else
	inputFileu64 = FastMathQ63_Norm64To32_Input1_u64;
	inputFileu64Len = sizeof(FastMathQ63_Norm64To32_Input1_u64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFiles64, 255, "%s%s%s", Patterns_PATH, FastMathQ63, "DivDenInput1_s64.txt");
#else
	inputFiles64 = FastMathQ63_DivDenInput1_s64;
	inputFiles64Len = sizeof(FastMathQ63_DivDenInput1_s64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFiles32, 255, "%s%s%s", Patterns_PATH, FastMathQ63, "DivNumInput1_s32.txt");
#else
	inputFiles32 = FastMathQ63_DivNumInput1_s32;
	inputFiles32Len = sizeof(FastMathQ63_DivNumInput1_s32);
#endif


	// load input data
#if defined(NOT_EMBEDDED)
	load_data_u64(inputFileu64, &paramCountInputu64, u64input);
#else
	paramCountInputu64 = inputFileu64Len;
	load_data_u64(inputFileu64, paramCountInputu64, u64input);
	paramCountInputu64 = paramCountInputu64/sizeof(uint64_t);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q63(inputFiles64, &paramCountInputs64, s64input);
#else
	paramCountInputs64 = inputFiles64Len;
	load_data_q63(inputFiles64, paramCountInputs64, s64input);
	paramCountInputs64 = paramCountInputs64/sizeof(q63);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(inputFiles32, &paramCountInputs32, s32input);
#else
	paramCountInputs32 = inputFiles32Len;
	load_data_q31(inputFiles32, paramCountInputs32, s32input);
	paramCountInputs32 = paramCountInputs32/sizeof(q31);
#endif


	int32_t outputVals[MAX_SIZE] = {0};
	int16_t outputNorms[MAX_SIZE] = {0};
	int32_t refVal[MAX_SIZE] = {0};
	int16_t refNorm[MAX_SIZE] = {0};

	// =====================

	uint64_t *inp = u64input;
	int32_t *outValp = outputVals;
	int16_t *outNormp = outputNorms;

#if defined(NOT_EMBEDDED)
	snprintf(inputFileT, 255, "%s%s%s", Patterns_PATH, FastMathQ63, "RefNorm64To32_Vals1_s32.txt");
#else
	inputFileT = FastMathQ63_RefNorm64To32_Vals1_s32;
	inputFileTLen = sizeof(FastMathQ63_RefNorm64To32_Vals1_s32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(inputFileT, &paramCountInputT, q31inputT);
#else
	paramCountInputT = inputFileTLen;
	load_data_q31(inputFileT, paramCountInputT, q31inputT);
	paramCountInputT = paramCountInputT/sizeof(q31);
#endif


	printf("== mips_norm_64_to_32u test ==  \n");

	unsigned long i;

	for (i = 0; i < paramCountInputT; i++)
	{
		int32_t val;
		int32_t norm;

		mips_norm_64_to_32u(inp[i], &val, &norm);
		outValp[i] = val;
		outNormp[i] = norm;
	}

	printf("mips_norm_64_to_32u finish \n");

	printf("mips_norm_64_to_32u checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FastMathQ63, "RefNorm64To32_Vals1_s32.txt");
#else
	referenceFile = FastMathQ63_RefNorm64To32_Vals1_s32;
	referenceFileLen = sizeof(FastMathQ63_RefNorm64To32_Vals1_s32);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
	referenceFileLen = referenceFileLen/sizeof(q31);
#endif


#if defined(NOT_EMBEDDED)
	eq_check_q31(referenceFile, outputVals, 0);
#else
	eq_check_special_q31(referenceData_q31, outputVals, referenceFileLen);
#endif

	
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FastMathQ63, "RefNorm64To32_Norms1_s16.txt");
#else
	referenceFile = FastMathQ63_RefNorm64To32_Norms1_s16;
	referenceFileLen = sizeof(FastMathQ63_RefNorm64To32_Norms1_s16);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
	referenceFileLen = referenceFileLen/sizeof(q15);
#endif


#if defined(NOT_EMBEDDED)
	eq_check_q15(referenceFile, outputNorms, 0);
#else
	eq_check_special_q15(referenceData_q15, outputNorms, referenceFileLen);
#endif


	
	printf("\n== mips_norm_64_to_32u check done  == \n\n");

	// =====================

	int64_t *denp = s64input;
	int32_t *nump = s32input;

	outValp = outputVals;

#if defined(NOT_EMBEDDED)
	snprintf(inputFileT, 255, "%s%s%s", Patterns_PATH, FastMathQ63, "DivRef1_u32.txt");
#else
	inputFileT = FastMathQ63_DivRef1_u32;
	inputFileTLen = sizeof(FastMathQ63_DivRef1_u32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(inputFileT, &paramCountInputT, q31inputT);
#else
	paramCountInputT = inputFileTLen;
	load_data_q31(inputFileT, paramCountInputT, q31inputT);
	paramCountInputT = paramCountInputT/sizeof(q31);
#endif


	printf("== mips_div_int64_to_int32 test ==  \n");

	for (i = 0; i < paramCountInputT; i++)
	{
		int32_t val;

		val = mips_div_int64_to_int32(denp[i], nump[i]);
		outValp[i] = val;
	}

	printf("mips_div_int64_to_int32 finish \n");

	printf("mips_div_int64_to_int32 checking \n\n");
	
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, FastMathQ63, "DivRef1_u32.txt");
#else
	referenceFile = FastMathQ63_DivRef1_u32;
	referenceFileLen = sizeof(FastMathQ63_DivRef1_u32);
	load_data_u32(referenceFile, referenceFileLen, referenceData_u32);
	referenceFileLen = referenceFileLen/sizeof(uint32_t);
#endif


#if defined(NOT_EMBEDDED)
	eq_check_u32(referenceFile, outputVals, 0);
#else
	eq_check_special_u32(referenceData_u32, outputVals, referenceFileLen);
#endif


	printf("\n== mips_div_int64_to_int32 check done  == \n\n");

	// =====================

	return 0;
}
