#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/interpolation_functions.h"

#define SNR_THRESHOLD 100

/* 

Reference patterns are generated with
a double precision computation.

*/
#define ABS_ERROR_Q31 ((q31)2000)
      



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

    q31 q31input1[MAX_SIZE] = {0};
    q31 q31input2[MAX_SIZE] = {0};
    int16_t s16config[MAX_SIZE] = {0};
    q31 q31y1[MAX_SIZE] = {0};
    q31 q31y2[MAX_SIZE] = {0};



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
	snprintf(inputFile1, sizeof(inputFile1), "%s%s%s", Patterns_PATH, InterpolationQ31, "Input1_q31.txt");
#else
	inputFile1 = InterpolationQ31_Input1_q31;
	inputFile1Len = sizeof(InterpolationQ31_Input1_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile2, sizeof(inputFile2), "%s%s%s", Patterns_PATH, InterpolationQ31, "Input2_q31.txt");
#else
	inputFile2 = InterpolationQ31_Input2_q31;
	inputFile2Len = sizeof(InterpolationQ31_Input2_q31);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(configFile, sizeof(configFile), "%s%s%s", Patterns_PATH, InterpolationQ31, "Config2_s16.txt");
#else
	configFile = InterpolationQ31_Config2_s16;
	configFileLen = sizeof(InterpolationQ31_Config2_s16);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(yFile1, sizeof(yFile1), "%s%s%s", Patterns_PATH, InterpolationQ31, "YVals1_q31.txt");
#else
	yFile1 = InterpolationQ31_YVals1_q31;
	yFile1Len = sizeof(InterpolationQ31_YVals1_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(yFile2, sizeof(yFile2), "%s%s%s", Patterns_PATH, InterpolationQ31, "YVals2_q31.txt");
#else
	yFile2 = InterpolationQ31_YVals2_q31;
	yFile2Len = sizeof(InterpolationQ31_YVals2_q31);
#endif


    // load input data
#if defined(NOT_EMBEDDED)
	load_data_q31(inputFile1, &paramCountInput1, q31input1);
#else
	paramCountInput1 = inputFile1Len;
	load_data_q31(inputFile1, paramCountInput1, q31input1);
	paramCountInput1 = paramCountInput1/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(inputFile2, &paramCountInput2, q31input2);
#else
	paramCountInput2 = inputFile2Len;
	load_data_q31(inputFile2, paramCountInput2, q31input2);
	paramCountInput2 = paramCountInput2/sizeof(q31);
#endif


#if defined(NOT_EMBEDDED)
	load_data_q15(configFile, &paramCountconfig, s16config);
#else
	paramCountconfig = configFileLen;
	load_data_q15(configFile, paramCountconfig, s16config);
	paramCountconfig = paramCountconfig/sizeof(q15);
#endif


#if defined(NOT_EMBEDDED)
	load_data_q31(yFile1, &paramCounty1, q31y1);
#else
	paramCounty1 = yFile1Len;
	load_data_q31(yFile1, paramCounty1, q31y1);
	paramCounty1 = paramCounty1/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(yFile2, &paramCounty2, q31y2);
#else
	paramCounty2 = yFile2Len;
	load_data_q31(yFile2, paramCounty2, q31y2);
	paramCounty2 = paramCounty2/sizeof(q31);
#endif


    
    q31 q31output[MAX_SIZE] = {0};
    

    const q31 *inp;
    int16_t *pConfig;   
    q31  *outp;
    q31  *y1;    
                                                           
    int16_t *dimsp;           
                
    unsigned long nb;

// =====================

	printf("== mips_linear_interp_q31 test ==  \n"); 
    
    inp = q31input1;
    outp = q31output;
    y1 = q31y1;

    for(nb = 0; nb < paramCountInput1; nb++)
       {
          outp[nb] = mips_linear_interp_q31(y1,inp[nb],paramCounty1);
       }
      

	printf("mips_linear_interp_q31 finish \n");

	printf("mips_linear_interp_q31 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, InterpolationQ31, "Reference1_q31.txt");
#else
	referenceFile = InterpolationQ31_Reference1_q31;
	referenceFileLen = sizeof(InterpolationQ31_Reference1_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);\
	referenceFileLen = referenceFileLen/sizeof(q31);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile, q31output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, q31output, referenceFileLen, (f32)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile, q31output, 0, ABS_ERROR_Q31);
#else
	near_check_special_q31(referenceData_q31, q31output, referenceFileLen, ABS_ERROR_Q31);
#endif


    memset(q31output, 0, sizeof(q31)*MAX_SIZE);

	printf("\n== mips_linear_interp_q31 check done  == \n\n");  

// =====================

	printf("== mips_bilinear_interp_q31 test ==  \n"); 
    
    inp = q31input2;
    outp = q31output;
    y1 = q31y2;
    q31 x,y;

    mips_bilinear_interp_instance_q31 SBI;
    pConfig = s16config;

    SBI.numRows = pConfig[1];
    SBI.numCols = pConfig[0];
    SBI.pData = y1;

    for(nb = 0; nb < paramCountInput2; nb += 2)
       {
          x = inp[nb];
          y = inp[nb+1];
          *outp++=mips_bilinear_interp_q31(&SBI,x,y);
       }
      

	printf("mips_linear_interp_q31 finish \n");

	printf("mips_linear_interp_q31 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, InterpolationQ31, "Reference2_q31.txt");
#else
	referenceFile = InterpolationQ31_Reference2_q31;
	referenceFileLen = sizeof(InterpolationQ31_Reference2_q31);
	load_data_q31(referenceFile, referenceFileLen, referenceData_q31);
	referenceFileLen = referenceFileLen/sizeof(q31);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile, q31output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, q31output, referenceFileLen, (f32)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile, q31output, 0, ABS_ERROR_Q31);
#else
	near_check_special_q31(referenceData_q31, q31output, referenceFileLen, ABS_ERROR_Q31);
#endif


	printf("\n== mips_linear_interp_q31 check done  == \n\n");  

// =====================

return 0;

}