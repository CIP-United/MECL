#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/interpolation_functions.h"

#define SNR_THRESHOLD 119

/* 

Reference patterns are generated with
a double precision computation.

*/
#define REL_ERROR (8.0e-5)


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
    int paramCountConfig2 = 0;
	int paramCountYVals1 = 0;
	int paramCountYVals2 = 0;
	int paramCountinputX3 = 0;
    int paramCountinputY3 = 0;
	int paramCountinputX4 = 0;
    int paramCountinputY4 = 0;	
    int paramCountinputX5 = 0;
    int paramCountinputY5 = 0;
    int paramCountoutputX3 = 0;
    int paramCountoutputX4 = 0;
    int paramCountoutputX5 = 0;
	float f32input1[MAX_SIZE] = {0};
	float f32input2[MAX_SIZE] = {0};
    int16_t s16config2[MAX_SIZE] = {0};
    float f32YVals1[MAX_SIZE] = {0};
	float f32YVals2[MAX_SIZE] = {0};
    float f32inputX3[MAX_SIZE] = {0};
    float f32inputY3[MAX_SIZE] = {0};
	float f32inputX4[MAX_SIZE] = {0};
    float f32inputY4[MAX_SIZE] = {0};
    float f32inputX5[MAX_SIZE] = {0};
    float f32inputY5[MAX_SIZE] = {0};
    float f32outputX3[MAX_SIZE] = {0};
    float f32outputX4[MAX_SIZE] = {0};
    float f32outputX5[MAX_SIZE] = {0};

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
	char configFile2[255] = {0};
#else
	void *configFile2;
	int configFile2Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char yvalsFile1[255] = {0};
#else
	void *yvalsFile1;
	int yvalsFile1Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char yvalsFile2[255] = {0};
#else
	void *yvalsFile2;
	int yvalsFile2Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputXFile3[255] = {0};
#else
	void *inputXFile3;
	int inputXFile3Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputXFile4[255] = {0};
#else
	void *inputXFile4;
	int inputXFile4Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputXFile5[255] = {0};
#else
	void *inputXFile5;
	int inputXFile5Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputYFile3[255] = {0};
#else
	void *inputYFile3;
	int inputYFile3Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputYFile4[255] = {0};
#else
	void *inputYFile4;
	int inputYFile4Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputYFile5[255] = {0};
#else
	void *inputYFile5;
	int inputYFile5Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char outputXFile3[255] = {0};
#else
	void *outputXFile3;
	int outputXFile3Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char outputXFile4[255] = {0};
#else
	void *outputXFile4;
	int outputXFile4Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char outputXFile5[255] = {0};
#else
	void *outputXFile5;
	int outputXFile5Len = 0;
#endif


#if defined(NOT_EMBEDDED)
	char referenceFile1[255] = {0};
#else
	void *referenceFile1;
	int referenceFile1Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char referenceFile2[255] = {0};
#else
	void *referenceFile2;
	int referenceFile2Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char referenceFile3[255] = {0};
#else
	void *referenceFile3;
	int referenceFile3Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char referenceFile4[255] = {0};
#else
	void *referenceFile4;
	int referenceFile4Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char referenceFile5[255] = {0};
#else
	void *referenceFile5;
	int referenceFile5Len = 0;
#endif


	// set file name by snprintf
	// relative path, function path, filename
#if defined(NOT_EMBEDDED)
	snprintf(inputFile1, sizeof(inputFile1), "%s%s%s", Patterns_PATH, InterpolationF32, "Input1_f32.txt");
#else
	inputFile1 = InterpolationF32_Input1_f32;
	inputFile1Len = sizeof(InterpolationF32_Input1_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile2, sizeof(inputFile2), "%s%s%s", Patterns_PATH, InterpolationF32, "Input2_f32.txt");
#else
	inputFile2 = InterpolationF32_Input2_f32;
	inputFile2Len = sizeof(InterpolationF32_Input2_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(configFile2, sizeof(configFile2), "%s%s%s", Patterns_PATH, InterpolationF32, "Config2_s16.txt");
#else
	configFile2 = InterpolationF32_Config2_s16;
	configFile2Len = sizeof(InterpolationF32_Config2_s16);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(yvalsFile1, sizeof(yvalsFile1), "%s%s%s", Patterns_PATH, InterpolationF32, "YVals1_f32.txt");
#else
	yvalsFile1 = InterpolationF32_YVals1_f32;
	yvalsFile1Len = sizeof(InterpolationF32_YVals1_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(yvalsFile2, sizeof(yvalsFile2), "%s%s%s", Patterns_PATH, InterpolationF32, "YVals2_f32.txt");
#else
	yvalsFile2 = InterpolationF32_YVals2_f32;
	yvalsFile2Len = sizeof(InterpolationF32_YVals2_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputXFile3, sizeof(inputXFile3), "%s%s%s", Patterns_PATH, InterpolationF32, "InputX3_f32.txt");
#else
	inputXFile3 = InterpolationF32_InputX3_f32;
	inputXFile3Len = sizeof(InterpolationF32_InputX3_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputXFile4, sizeof(inputXFile4), "%s%s%s", Patterns_PATH, InterpolationF32, "InputX4_f32.txt");
#else
	inputXFile4 = InterpolationF32_InputX4_f32;
	inputXFile4Len = sizeof(InterpolationF32_InputX4_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputXFile5, sizeof(inputXFile5), "%s%s%s", Patterns_PATH, InterpolationF32, "InputX5_f32.txt");
#else
	inputXFile5 = InterpolationF32_InputX5_f32;
	inputXFile5Len = sizeof(InterpolationF32_InputX5_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputYFile3, sizeof(inputYFile3), "%s%s%s", Patterns_PATH, InterpolationF32, "InputY3_f32.txt");
#else
	inputYFile3 = InterpolationF32_InputY3_f32;
	inputYFile3Len = sizeof(InterpolationF32_InputY3_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputYFile4, sizeof(inputYFile4), "%s%s%s", Patterns_PATH, InterpolationF32, "InputY4_f32.txt");
#else
	inputYFile4 = InterpolationF32_InputY4_f32;
	inputYFile4Len = sizeof(InterpolationF32_InputY4_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputYFile5, sizeof(inputYFile5), "%s%s%s", Patterns_PATH, InterpolationF32, "InputY5_f32.txt");
#else
	inputYFile5 = InterpolationF32_InputY5_f32;
	inputYFile5Len = sizeof(InterpolationF32_InputY5_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(outputXFile3, sizeof(outputXFile3), "%s%s%s", Patterns_PATH, InterpolationF32, "OutputX3_f32.txt");
#else
	outputXFile3 = InterpolationF32_OutputX3_f32;
	outputXFile3Len = sizeof(InterpolationF32_OutputX3_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(outputXFile4, sizeof(outputXFile4), "%s%s%s", Patterns_PATH, InterpolationF32, "OutputX4_f32.txt");
#else
	outputXFile4 = InterpolationF32_OutputX4_f32;
	outputXFile4Len = sizeof(InterpolationF32_OutputX4_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(outputXFile5, sizeof(outputXFile5), "%s%s%s", Patterns_PATH, InterpolationF32, "OutputX5_f32.txt");
#else
	outputXFile5 = InterpolationF32_OutputX5_f32;
	outputXFile5Len = sizeof(InterpolationF32_OutputX5_f32);
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
	load_data_q15(configFile2, &paramCountConfig2, s16config2);
#else
	paramCountConfig2 = configFile2Len;
	load_data_q15(configFile2, paramCountConfig2, s16config2);
	paramCountConfig2 = paramCountConfig2/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(yvalsFile1, &paramCountYVals1, f32YVals1);
#else
	paramCountYVals1 = yvalsFile1Len;
	load_data_f32(yvalsFile1, paramCountYVals1, f32YVals1);
	paramCountYVals1 = paramCountYVals1/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(yvalsFile2, &paramCountYVals2, f32YVals2);
#else
	paramCountYVals2 = yvalsFile2Len;
	load_data_f32(yvalsFile2, paramCountYVals2, f32YVals2);
	paramCountYVals2 = paramCountYVals2/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputXFile3, &paramCountinputX3, f32inputX3);
#else
	paramCountinputX3 = inputXFile3Len;
	load_data_f32(inputXFile3, paramCountinputX3, f32inputX3);
	paramCountinputX3 = paramCountinputX3/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputXFile4, &paramCountinputX4, f32inputX4);
#else
	paramCountinputX4 = inputXFile4Len;
	load_data_f32(inputXFile4, paramCountinputX4, f32inputX4);
	paramCountinputX4 = paramCountinputX4/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputXFile5, &paramCountinputX5, f32inputX5);
#else
	paramCountinputX5 = inputXFile5Len;
	load_data_f32(inputXFile5, paramCountinputX5, f32inputX5);
	paramCountinputX5 = paramCountinputX5/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputYFile3, &paramCountinputY3, f32inputY3);
#else
	paramCountinputY3 = inputYFile3Len;
	load_data_f32(inputYFile3, paramCountinputY3, f32inputY3);
	paramCountinputY3 = paramCountinputY3/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputYFile4, &paramCountinputY4, f32inputY4);
#else
	paramCountinputY4 = inputYFile4Len;
	load_data_f32(inputYFile4, paramCountinputY4, f32inputY4);
	paramCountinputY4 = paramCountinputY4/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputYFile5, &paramCountinputY5, f32inputY5);
#else
	paramCountinputY5 = inputYFile5Len;
	load_data_f32(inputYFile5, paramCountinputY5, f32inputY5);
	paramCountinputY5 = paramCountinputY5/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(outputXFile3, &paramCountoutputX3, f32outputX3);
#else
	paramCountoutputX3 = outputXFile3Len;
	load_data_f32(outputXFile3, paramCountoutputX3, f32outputX3);
	paramCountoutputX3 = paramCountoutputX3/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(outputXFile4, &paramCountoutputX4, f32outputX4);
#else
	paramCountoutputX4 = outputXFile4Len;
	load_data_f32(outputXFile4, paramCountoutputX4, f32outputX4);
	paramCountoutputX4 = paramCountoutputX4/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(outputXFile5, &paramCountoutputX5, f32outputX5);
#else
	paramCountoutputX5 = outputXFile5Len;
	load_data_f32(outputXFile5, paramCountoutputX5, f32outputX5);
	paramCountoutputX5 = paramCountoutputX5/sizeof(f32);
#endif



    float f32output[MAX_SIZE] = {0};
    // pointers
    float *inp;
    float *inpX;
    float *inpY;
    float *outX;
    float *outp;
    float *y1;
    float *y2;
    int16_t *pConfig;
    
// =======test_linear_interp_f32==============

    printf("== linear_interp_f32  test ==  \n");
    inp = f32input1;
    outp = f32output;
    y1 = f32YVals1;

    mips_linear_interp_instance_f32 S;
    S.nValues=paramCountYVals1;           /**< nValues */
          /* Those values must be coherent with the ones in the 
          Python script generating the patterns */
    S.x1=0.0;               /**< x1 */
    S.xSpacing=1.0;         /**< xSpacing */
    S.pYData=y1;          /**< pointer to the table of Y values */
    unsigned long nb;
    for(nb = 0; nb < paramCountInput1; nb++)
    {
        outp[nb] = mips_linear_interp_f32(&S,inp[nb]);
    }
    
	printf("linear_interp_f32 finish \n");

	printf("linear_interp_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile1, sizeof(referenceFile1), "%s%s%s", Patterns_PATH, InterpolationF32, "Reference1_f32.txt");
#else
	referenceFile1 = InterpolationF32_Reference1_f32;
	referenceFile1Len = sizeof(InterpolationF32_Reference1_f32);
	load_data_f32(referenceFile1, referenceFile1Len, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile1, f32output, 0, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output, referenceFile1Len, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f32(referenceFile1, f32output, 0, REL_ERROR);
#else
	rel_check_special_f32(referenceData_f32, f32output, referenceFile1Len, REL_ERROR);
#endif

    memset(f32output, 0, sizeof(float)*MAX_SIZE);
	printf("\n== linear_interp_f32 check done  == \n\n");
    

// =======test_bilinear_interp_f32 ==============
printf("== bilinear_interp_f32  test ==  \n");
    inp = f32input2;
    outp = f32output;
    y2 = f32YVals2;
    pConfig = s16config2;

    mips_bilinear_interp_instance_f32 SBI;
    SBI.numRows = pConfig[1];
    SBI.numCols = pConfig[0];      
    SBI.pData = y2;

    float x,y;
    for(nb = 0; nb < paramCountInput2; nb += 2)
    {
        x = inp[nb];
        y = inp[nb+1];
        *outp++=mips_bilinear_interp_f32(&SBI,x,y);
    }

    
	printf("bilinear_interp_f32 finish \n");

	printf("bilinear_interp_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile2, sizeof(referenceFile2), "%s%s%s", Patterns_PATH, InterpolationF32, "Reference2_f32.txt");
#else
	referenceFile2 = InterpolationF32_Reference2_f32;
	referenceFile2Len = sizeof(InterpolationF32_Reference2_f32);
	load_data_f32(referenceFile2, referenceFile2Len, referenceData_f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile2, f32output, 0, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output, referenceFile2Len, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f32(referenceFile2, f32output, 0, REL_ERROR);
#else
	rel_check_special_f32(referenceData_f32, f32output, referenceFile2Len, REL_ERROR);
#endif

    memset(f32output, 0, sizeof(float)*MAX_SIZE);
	printf("\n== bilinear_interp_f32 check done  == \n\n");

    // =======test_spline_square_f32==============

    printf("== spline_square_f32  test ==  \n");
    inpX = f32inputX3;
    inpY = f32inputY3;
    outX = f32outputX3;
    float splineCoefs1[3*(4-1)] = {0};
    float buffer1[2*4-1] = {0};
    float f32output1[20] = {0};
    outp = f32output1;
    float *coef;
    coef = splineCoefs1;
    float *buf;
    buf = buffer1;

    mips_spline_instance_f32 SP;
    mips_spline_init_f32(&SP, MIPS_SPLINE_PARABOLIC_RUNOUT, inpX, inpY, 4, coef, buf);
    mips_spline_f32(&SP, outX, outp, 20);
    
	printf("spline_square_f32 finish \n");

	printf("spline_square_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile3, sizeof(referenceFile3), "%s%s%s", Patterns_PATH, InterpolationF32, "Reference3_f32.txt");
#else
	referenceFile3 = InterpolationF32_Reference3_f32;
	referenceFile3Len = sizeof(InterpolationF32_Reference3_f32);
	load_data_f32(referenceFile3, referenceFile3Len, referenceData_f32);
	referenceFile3Len = referenceFile3Len/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile3, f32output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, referenceFile3Len, SNR_THRESHOLD);
#endif

	printf("\n== spline_square_f32 check done  == \n\n");

// =======test_spline_sine_f32==============

    printf("== spline_sine_f32  test ==  \n");
    inpX = f32inputX4;
    inpY = f32inputY4;
    outX = f32outputX4;
    float splineCoefs2[3*(9-1)] = {0};
    float buffer2[2*9-1] = {0};
    float f32output2[33] = {0};
    outp = f32output2;
    coef = splineCoefs2;
    buf = buffer2;

    mips_spline_init_f32(&SP, MIPS_SPLINE_NATURAL, inpX, inpY, 9, coef, buf);
    mips_spline_f32(&SP, outX, outp, 33);
    
	printf("spline_sine_f32 finish \n");

	printf("spline_sine_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile4, sizeof(referenceFile4), "%s%s%s", Patterns_PATH, InterpolationF32, "Reference4_f32.txt");
#else
	referenceFile4 = InterpolationF32_Reference4_f32;
	referenceFile4Len = sizeof(InterpolationF32_Reference4_f32);
	load_data_f32(referenceFile4, referenceFile4Len, referenceData_f32);
	referenceFile4Len = referenceFile4Len/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile4, f32output2, 0, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output2, referenceFile4Len, SNR_THRESHOLD);
#endif

	printf("\n== spline_sine_f32 check done  == \n\n");

// =======test_spline_ramp_f32==============

    printf("== spline_ramp_f32  test ==  \n");
    inpX = f32inputX5;
    inpY = f32inputY5;
    outX = f32outputX5;
    float splineCoefs3[3*(3-1)] = {0};
    float buffer3[2*3-1] = {0};
    float f32output3[30] = {0};
    outp = f32output3;
    coef = splineCoefs3;
    buf = buffer3;

    mips_spline_init_f32(&SP, MIPS_SPLINE_PARABOLIC_RUNOUT, inpX, inpY, 3, coef, buf);
    mips_spline_f32(&SP, outX, outp, 30);
    
	printf("spline_ramp_f32 finish \n");

	printf("spline_ramp_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile5, sizeof(referenceFile5), "%s%s%s", Patterns_PATH, InterpolationF32, "Reference5_f32.txt");
#else
	referenceFile5 = InterpolationF32_Reference5_f32;
	referenceFile5Len = sizeof(InterpolationF32_Reference5_f32);
	load_data_f32(referenceFile5, referenceFile5Len, referenceData_f32);
	referenceFile5Len = referenceFile5Len/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile5, f32output3, 0, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output3, referenceFile5Len, SNR_THRESHOLD);
#endif

	printf("\n== spline_ramp_f32 check done  == \n\n");

    return 0;
}

	

