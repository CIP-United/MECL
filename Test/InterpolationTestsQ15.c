#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/interpolation_functions.h"

#define SNR_THRESHOLD 70

/* 

Reference patterns are generated with
a double precision computation.

*/
#define ABS_ERROR_Q15 ((q15)2)
      



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
    int paramCountconfig = 0;
    int paramCounty1 = 0;
    int paramCounty2 = 0;

    q31 q15input1[MAX_SIZE] = {0};
    q31 q15input2[MAX_SIZE] = {0};
    q15 q15config[MAX_SIZE] = {0};
    q15 q15y1[MAX_SIZE] = {0};
    q15 q15y2[MAX_SIZE] = {0};



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
	char referenceFile[255] = {0};
#else
	void *referenceFile;
	int referenceFileLen = 0;
#endif

#if defined(NOT_EMBEDDED)
	char configFile[255] = {0};
#else
	void *configFile;
	int configFileLen = 0;
#endif

#if defined(NOT_EMBEDDED)
	char yFile1[255] = {0};
#else
	void *yFile1;
	int yFile1Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char yFile2[255] = {0};
#else
	void *yFile2;
	int yFile2Len = 0;
#endif



    // set file name by snprintf
    // relative path, function path, filename
#if defined(NOT_EMBEDDED)
	snprintf(inputFile1, sizeof(inputFile1), "%s%s%s", Patterns_PATH, InterpolationQ15, "Input1_q31.txt");
#else
	inputFile1 = InterpolationQ15_Input1_q31;
	inputFile1Len = sizeof(InterpolationQ15_Input1_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile2, sizeof(inputFile2), "%s%s%s", Patterns_PATH, InterpolationQ15, "Input2_q31.txt");
#else
	inputFile2 = InterpolationQ15_Input2_q31;
	inputFile2Len = sizeof(InterpolationQ15_Input2_q31);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(configFile, sizeof(configFile), "%s%s%s", Patterns_PATH, InterpolationQ15, "Config2_s16.txt");
#else
	configFile = InterpolationQ15_Config2_s16;
	configFileLen = sizeof(InterpolationQ15_Config2_s16);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(yFile1, sizeof(yFile1), "%s%s%s", Patterns_PATH, InterpolationQ15, "YVals1_q15.txt");
#else
	yFile1 = InterpolationQ15_YVals1_q15;
	yFile1Len = sizeof(InterpolationQ15_YVals1_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(yFile2, sizeof(yFile2), "%s%s%s", Patterns_PATH, InterpolationQ15, "YVals2_q15.txt");
#else
	yFile2 = InterpolationQ15_YVals2_q15;
	yFile2Len = sizeof(InterpolationQ15_YVals2_q15);
#endif


    // load input data
#if defined(NOT_EMBEDDED)
	load_data_q31(inputFile1, &paramCountInput1, q15input1);
#else
	paramCountInput1 = inputFile1Len;
	load_data_q31(inputFile1, paramCountInput1, q15input1);
	paramCountInput1 = paramCountInput1/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(inputFile2, &paramCountInput2, q15input2);
#else
	paramCountInput2 = inputFile2Len;
	load_data_q31(inputFile2, paramCountInput2, q15input2);
	paramCountInput2 = paramCountInput2/sizeof(q31);
#endif


#if defined(NOT_EMBEDDED)
	load_data_q15(configFile, &paramCountconfig, q15config);
#else
	paramCountconfig = configFileLen;
	load_data_q15(configFile, paramCountconfig, q15config);
	paramCountconfig = paramCountconfig/sizeof(q15);
#endif


#if defined(NOT_EMBEDDED)
	load_data_q15(yFile1, &paramCounty1, q15y1);
#else
	paramCounty1 = yFile1Len;
	load_data_q15(yFile1, paramCounty1, q15y1);
	paramCounty1 = paramCounty1/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(yFile2, &paramCounty2, q15y2);
#else
	paramCounty2 = yFile2Len;
	load_data_q15(yFile2, paramCounty2, q15y2);
	paramCounty2 = paramCounty2/sizeof(q15);
#endif


    
    q15 q15output[MAX_SIZE] = {0};
    

    const q31 *inp;
    q15 *pConfig;   
    q15  *outp;
    q15  *y1;    
                                                                           
    unsigned long nb;

// =====================

	printf("== mips_linear_interp_q15 test ==  \n"); 
    
    inp = q15input1;
    outp = q15output;
    y1 = q15y1;

    for(nb = 0; nb < paramCountInput1; nb++)
       {
          outp[nb] = mips_linear_interp_q15(y1,inp[nb],paramCounty1);
       }
      

	printf("mips_linear_interp_q15 finish \n");

	printf("mips_linear_interp_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, InterpolationQ15, "Reference1_q15.txt");
#else
	referenceFile = InterpolationQ15_Reference1_q15;
	referenceFileLen = sizeof(InterpolationQ15_Reference1_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output, referenceFileLen, (f32)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output, 0, ABS_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, q15output, referenceFileLen, ABS_ERROR_Q15);
#endif


    memset(q15output, 0, sizeof(q15)*MAX_SIZE);

	printf("\n== mips_linear_interp_q15 check done  == \n\n");  

// =====================

	printf("== mips_bilinear_interp_q15 test ==  \n"); 
    
    inp = q15input2;
    outp = q15output;
    y1 = q15y2;
    q31 x,y;

    mips_bilinear_interp_instance_q15 SBI;
    pConfig = q15config;

    SBI.numRows = pConfig[1];
    SBI.numCols = pConfig[0];
    SBI.pData = y1;

    for(nb = 0; nb < paramCountInput2; nb += 2)
       {
          x = inp[nb];
          y = inp[nb+1];
          *outp++=mips_bilinear_interp_q15(&SBI,x,y);
       }
      

	printf("mips_linear_interp_q15 finish \n");

	printf("mips_linear_interp_q15 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, InterpolationQ15, "Reference2_q15.txt");
#else
	referenceFile = InterpolationQ15_Reference2_q15;
	referenceFileLen = sizeof(InterpolationQ15_Reference2_q15);
	load_data_q15(referenceFile, referenceFileLen, referenceData_q15);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile, q15output, 0, (q15)SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output, referenceFileLen, (q15)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile, q15output, 0, ABS_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, q15output, referenceFileLen, ABS_ERROR_Q15);
#endif


	printf("\n== mips_linear_interp_q15 check done  == \n\n");  

// =====================

return 0;

}