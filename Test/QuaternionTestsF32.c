#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/quaternion_math_functions.h"

#define SNR_THRESHOLD 120
#define REL_ERROR (1.0e-6)
#define ABS_ERROR (1.0e-7)

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
	int paramCountInput7 = 0;
	int paramCountOutput1 = 128;
	int paramCountOutput7 = 512;
	float f32input1[MAX_SIZE] = {0};
	float f32input2[MAX_SIZE] = {0};
	float f32input7[MAX_SIZE] = {0};

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
	char inputFile7[255] = {0};
#else
	void *inputFile7;
	int inputFile7Len = 0;
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
	snprintf(inputFile1, sizeof(inputFile1), "%s%s%s", Patterns_PATH, QuaternionMathsF32, "Input1_f32.txt");
#else
	inputFile1 = QuaternionMathsF32_Input1_f32;
	inputFile1Len = sizeof(QuaternionMathsF32_Input1_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile2, sizeof(inputFile2), "%s%s%s", Patterns_PATH, QuaternionMathsF32, "Input2_f32.txt");
#else
	inputFile2 = QuaternionMathsF32_Input2_f32;
	inputFile2Len = sizeof(QuaternionMathsF32_Input2_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile7, sizeof(inputFile7), "%s%s%s", Patterns_PATH, QuaternionMathsF32, "Input7_f32.txt");
#else
	inputFile7 = QuaternionMathsF32_Input7_f32;
	inputFile7Len = sizeof(QuaternionMathsF32_Input7_f32);
#endif


	// load input data
#if defined(NOT_EMBEDDED)
	load_data_f32(inputFile1, &paramCountInput1, f32input1);
#else
	paramCountInput1 = inputFile1Len;
	load_data_f32(inputFile1, paramCountInput1, f32input1);
	paramCountInput1 = paramCountInput1/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFile2, &paramCountInput2, f32input2);
#else
	paramCountInput2 = inputFile2Len;
	load_data_f32(inputFile2, paramCountInput2, f32input2);
	paramCountInput2 = paramCountInput2/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFile7, &paramCountInput7, f32input7);
#else
	paramCountInput7 = inputFile7Len;
	load_data_f32(inputFile7, paramCountInput7, f32input7);
	paramCountInput7 = paramCountInput7/sizeof(f32);
#endif


	float f32output1[MAX_SIZE] = {0};

	printf("== mips_quaternion_norm_f32 test ==  \n");
	mips_quaternion_norm_f32(f32input1, f32output1, paramCountOutput1);
	printf("mips_quaternion_norm_f32 finish \n");

	printf("mips_quaternion_norm_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, QuaternionMathsF32, "Reference1_f32.txt");
#else
	referenceFile = QuaternionMathsF32_Reference1_f32;
	referenceFileLen = sizeof(QuaternionMathsF32_Reference1_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output1, 0, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output1, referenceFileLen, ABS_ERROR, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, referenceFileLen, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_quaternion_norm_f32 check done  == \n\n");

	// for (size_t i = 0; i < paramCountInput1; i++)
	// {
	// 	printf("mips_quaternion_norm_f32 output = %f \n", f32output1[i]); 
	// }
	
// =====================

	printf("== mips_quaternion_inverse_f32 test ==  \n");
	mips_quaternion_inverse_f32(f32input1, f32output1, paramCountInput1 >> 2);
	printf("mips_quaternion_inverse_f32 finish \n");

	printf("mips_quaternion_inverse_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, QuaternionMathsF32, "Reference2_f32.txt");
#else
	referenceFile = QuaternionMathsF32_Reference2_f32;
	referenceFileLen = sizeof(QuaternionMathsF32_Reference2_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output1, 0, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output1, referenceFileLen, ABS_ERROR, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, referenceFileLen, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_quaternion_inverse_f32 check done  == \n\n");

// =====================

	printf("== mips_quaternion_conjugate_f32 test ==  \n");
	mips_quaternion_conjugate_f32(f32input1, f32output1, paramCountInput1 >> 2);
	printf("mips_quaternion_conjugate_f32 finish \n");

	printf("mips_quaternion_conjugate_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, QuaternionMathsF32, "Reference3_f32.txt");
#else
	referenceFile = QuaternionMathsF32_Reference3_f32;
	referenceFileLen = sizeof(QuaternionMathsF32_Reference3_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output1, 0, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output1, referenceFileLen, ABS_ERROR, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, referenceFileLen, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_quaternion_conjugate_f32 check done  == \n\n");

// =====================

	printf("== mips_quaternion_normalize_f32 test ==  \n");
	mips_quaternion_normalize_f32(f32input1, f32output1, paramCountInput1 >> 2);
	printf("mips_quaternion_normalize_f32 finish \n");

	printf("mips_quaternion_normalize_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, QuaternionMathsF32, "Reference4_f32.txt");
#else
	referenceFile = QuaternionMathsF32_Reference4_f32;
	referenceFileLen = sizeof(QuaternionMathsF32_Reference4_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output1, 0, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output1, referenceFileLen, ABS_ERROR, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, referenceFileLen, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_quaternion_normalize_f32 check done  == \n\n");

// =====================

	printf("== mips_quaternion_product_single_f32 test ==  \n");
	f32 *inp1 = f32input1;;
	f32 *inp2 = f32input2;;
	f32 *outp = f32output1; 
	
	for(uint32_t i = 0; i < paramCountInput1 >> 2; i++)
        {
           mips_quaternion_product_single_f32(inp1,inp2,outp);
           outp += 4;
           inp1 += 4;
           inp2 += 4;
        }

	printf("mips_quaternion_product_single_f32 finish \n");

	printf("mips_quaternion_product_single_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, QuaternionMathsF32, "Reference5_f32.txt");
#else
	referenceFile = QuaternionMathsF32_Reference5_f32;
	referenceFileLen = sizeof(QuaternionMathsF32_Reference5_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, referenceFileLen, (f32)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output1, 0, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output1, referenceFileLen, ABS_ERROR, REL_ERROR);
#endif


	printf("\n== mips_quaternion_product_single_f32 check done  == \n\n");

// =====================

	printf("== mips_quaternion_product_f32 test ==  \n");
	mips_quaternion_product_f32(f32input1, f32input2, f32output1, paramCountInput1 >> 2);
	printf("mips_quaternion_product_f32 finish \n");

	printf("mips_quaternion_product_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, QuaternionMathsF32, "Reference5_f32.txt");
#else
	referenceFile = QuaternionMathsF32_Reference5_f32;
	referenceFileLen = sizeof(QuaternionMathsF32_Reference5_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, referenceFileLen, (f32)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output1, 0, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output1, referenceFileLen, ABS_ERROR, REL_ERROR);
#endif


	printf("\n== mips_quaternion_product_f32 check done  == \n\n"); 

// =====================

	printf("== mips_quaternion2rotation_f32 test ==  \n");
	mips_quaternion2rotation_f32(f32input1, f32output1, paramCountInput1 >> 2);
	printf("mips_quaternion2rotation_f32 finish \n");

	printf("mips_quaternion2rotation_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, QuaternionMathsF32, "Reference6_f32.txt");
#else
	referenceFile = QuaternionMathsF32_Reference6_f32;
	referenceFileLen = sizeof(QuaternionMathsF32_Reference6_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output1, 0, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output1, referenceFileLen, ABS_ERROR, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, referenceFileLen, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_quaternion2rotation_f32 check done  == \n\n");

// =====================

	printf("== mips_rotation2quaternion_f32 test ==  \n");
	
	inp1 = &f32input7 ;
    outp = &f32output1;
	mips_rotation2quaternion_f32(inp1, outp, paramCountOutput7 >> 2);
	for(uint32_t i=0; i < paramCountOutput7 >> 2 ; i++)
        {
            if (outp[0] < 0.0f)
            {
                outp[0] = -outp[0];
                outp[1] = -outp[1];
                outp[2] = -outp[2];
                outp[3] = -outp[3];
            }

            outp += 4;
        }
	printf("mips_rotation2quaternion_f32 finish \n");

	printf("mips_rotation2quaternion_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, QuaternionMathsF32, "Reference7_f32.txt");
#else
	referenceFile = QuaternionMathsF32_Reference7_f32;
	referenceFileLen = sizeof(QuaternionMathsF32_Reference7_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output1, 0, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output1, referenceFileLen, ABS_ERROR, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output1, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, referenceFileLen, (f32)SNR_THRESHOLD);
#endif


	printf("\n== mips_rotation2quaternion_f32 check done  == \n\n"); 


// =====================  
	
	return 0;

}