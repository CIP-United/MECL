#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/filtering_functions.h"


#define SNR_THRESHOLD 98

/* 

Reference patterns are generated with
a double precision computation.

*/
#define REL_ERROR (1.2e-3)


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

    double state[128] = {0};
    double f64output1[MAX_SIZE] = {0};


	// declare input value
	int paramCountInput1 = 0;
	int paramCountCoefs1 = 0;
	double f64inputs1[MAX_SIZE] = {0};
	double f64coefs1[MAX_SIZE] = {0};

	// file name. file path max length is 255, so use 255.
#if defined(NOT_EMBEDDED)
	char inputFile1[255] = {0};
#else
	void *inputFile1;
	int inputFile1Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char coefsFile1[255] = {0};
#else
	void *coefsFile1;
	int coefsFile1Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char referenceFile1[255] = {0};
#else
	void *referenceFile1;
	int referenceFile1Len = 0;
#endif


	// set file name by snprintf
	// relative path, function path, filename
#if defined(NOT_EMBEDDED)
	snprintf(inputFile1, sizeof(inputFile1), "%s%s%s", Patterns_PATH, BIQUADF64, "BiquadInput1_f64.txt");
#else
	inputFile1 = BIQUADF64_BiquadInput1_f64;
	inputFile1Len = sizeof(BIQUADF64_BiquadInput1_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(coefsFile1, sizeof(coefsFile1), "%s%s%s", Patterns_PATH, BIQUADF64, "BiquadCoefs1_f64.txt");
#else
	coefsFile1 = BIQUADF64_BiquadCoefs1_f64;
	coefsFile1Len = sizeof(BIQUADF64_BiquadCoefs1_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile1, sizeof(referenceFile1), "%s%s%s", Patterns_PATH, BIQUADF64, "BiquadOutput1_f64.txt");
#else
	referenceFile1 = BIQUADF64_BiquadOutput1_f64;
	referenceFile1Len = sizeof(BIQUADF64_BiquadOutput1_f64);
	load_data_f64(referenceFile1, referenceFile1Len, referenceData_f64);
#endif


	// load input data
#if defined(NOT_EMBEDDED)
	load_data_f64(inputFile1, &paramCountInput1, f64inputs1);
#else
	paramCountInput1 = inputFile1Len;
	load_data_f64(inputFile1, paramCountInput1, f64inputs1);
	paramCountInput1 = paramCountInput1/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(coefsFile1, &paramCountCoefs1, f64coefs1);
#else
	paramCountCoefs1 = coefsFile1Len;
	load_data_f64(coefsFile1, paramCountCoefs1, f64coefs1);
	paramCountCoefs1 = paramCountCoefs1/sizeof(f64);
#endif



// =======test_biquad_cascade_df2T_ref==============
    
    printf("== biquad_cascade_df2T_ref test ==  \n");
    
    //pointers
    double *coefsp;
    coefsp = f64coefs1;
    double *statep;
    statep = state;
    double *inputp;
    inputp = f64inputs1;
    double *outp;
    outp = f64output1;
    

	int blockSize;

    blockSize = paramCountInput1 >> 1;

    mips_biquad_cascade_df2T_instance_f64 Sdf2T;
    mips_biquad_cascade_df2T_init_f64(&Sdf2T,3,coefsp,statep);
    mips_biquad_cascade_df2T_f64(&Sdf2T,inputp,outp,blockSize);
    outp += blockSize;

           
    inputp += blockSize;
    mips_biquad_cascade_df2T_f64(&Sdf2T,inputp,outp,blockSize);
    outp += blockSize;

	printf("biquad_cascade_df2T_ref finish \n");

	printf("biquad_cascade_df2T_ref checking \n\n");

#if defined(NOT_EMBEDDED)
	rel_check_f64(referenceFile1, f64output1, paramCountInput1, REL_ERROR);
#else
	rel_check_special_f64(referenceData_f64, f64output1, paramCountInput1, REL_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile1, f64output1, paramCountInput1, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, paramCountInput1, SNR_THRESHOLD);
#endif


	printf("\n== biquad_cascade_df2T_ref check done  == \n\n");
	
// =======test_biquad_cascade_df2T_rand==============

// declare input value
	int paramCountInput2 = 0;
	int paramCountCoefs2 = 0;
    int paramCountConfigs = 0;
	double f64inputs2[MAX_SIZE] = {0};
	double f64coefs2[MAX_SIZE] = {0};
    int16_t s16configs[MAX_SIZE] = {0};

	// file name. file path max length is 255, so use 255.
#if defined(NOT_EMBEDDED)
	char inputFile2[255] = {0};
#else
	void *inputFile2;
	int inputFile2Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char coefsFile2[255] = {0};
#else
	void *coefsFile2;
	int coefsFile2Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char referenceFile2[255] = {0};
#else
	void *referenceFile2;
	int referenceFile2Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char configsFile[255] = {0};
#else
	void *configsFile;
	int configsFileLen = 0;
#endif


	// set file name by snprintf
	// relative path, function path, filename
#if defined(NOT_EMBEDDED)
	snprintf(inputFile2, sizeof(inputFile2), "%s%s%s", Patterns_PATH, BIQUADF64, "AllBiquadInputs2_f64.txt");
#else
	inputFile2 = BIQUADF64_AllBiquadInputs2_f64;
	inputFile2Len = sizeof(BIQUADF64_AllBiquadInputs2_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(coefsFile2, sizeof(coefsFile2), "%s%s%s", Patterns_PATH, BIQUADF64, "AllBiquadCoefs2_f64.txt");
#else
	coefsFile2 = BIQUADF64_AllBiquadCoefs2_f64;
	coefsFile2Len = sizeof(BIQUADF64_AllBiquadCoefs2_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile2, sizeof(referenceFile2), "%s%s%s", Patterns_PATH, BIQUADF64, "AllBiquadRefs2_f64.txt");
#else
	referenceFile2 = BIQUADF64_AllBiquadRefs2_f64;
	referenceFile2Len = sizeof(BIQUADF64_AllBiquadRefs2_f64);
	load_data_f64(referenceFile2, referenceFile2Len, referenceData_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(configsFile, sizeof(configsFile), "%s%s%s", Patterns_PATH, BIQUADF64, "AllBiquadConfigs2_s16.txt");
#else
	configsFile = BIQUADF64_AllBiquadConfigs2_s16;
	configsFileLen = sizeof(BIQUADF64_AllBiquadConfigs2_s16);
#endif


	// load input data
#if defined(NOT_EMBEDDED)
	load_data_f64(inputFile2, &paramCountInput2, f64inputs2);
#else
	paramCountInput2 = inputFile2Len;
	load_data_f64(inputFile2, paramCountInput2, f64inputs2);
	paramCountInput2 = paramCountInput2/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(coefsFile2, &paramCountCoefs2, f64coefs2);
#else
	paramCountCoefs2 = coefsFile2Len;
	load_data_f64(coefsFile2, paramCountCoefs2, f64coefs2);
	paramCountCoefs2 = paramCountCoefs2/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(configsFile, &paramCountConfigs, s16configs);
#else
	paramCountConfigs = configsFileLen;
	load_data_q15(configsFile, paramCountConfigs, s16configs);
	paramCountConfigs = paramCountConfigs/sizeof(q15);
#endif


	printf("== biquad_cascade_df2T_rand test ==  \n");

        int numStages;

        unsigned long i;

        //pointers
        int16_t *configsp;
        configsp = s16configs;
        coefsp = f64coefs2;
        statep = state;
        inputp = f64inputs2;
        outp = f64output1;

        for(i=0;i < paramCountConfigs; i+=2)
        {

        /*

        Python script is generating different tests with
        different blockSize and numTaps.

        We loop on those configs.

        */
        
           numStages = configsp[0];
           blockSize = configsp[1];

           configsp += 2;

          

           /*

           The filter is initialized with the coefs, blockSize and numTaps.

           */
           mips_biquad_cascade_df2T_instance_f64 Sdf2T;
           mips_biquad_cascade_df2T_init_f64(&Sdf2T,numStages,coefsp,statep);

           coefsp += numStages * 5;

           /*
           
           Python script is filtering a 2*blockSize number of samples.
           We do the same filtering in two pass to check (indirectly that
           the state management of the fir is working.)

           */

           mips_biquad_cascade_df2T_f64(&Sdf2T,inputp,outp,blockSize);
           outp += blockSize;
           inputp += blockSize;
           
        }
    
	printf("biquad_cascade_df2T_rand finish \n");

	printf("biquad_cascade_df2T_rand checking \n\n");

#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile2, f64output1, paramCountInput2, SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output1, paramCountInput2, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	rel_check_f64(referenceFile2, f64output1, paramCountInput2, REL_ERROR);
#else
	rel_check_special_f64(referenceData_f64, f64output1, paramCountInput2, REL_ERROR);
#endif


	printf("\n== biquad_cascade_df2T_rand check done  == \n\n");



// =====================

	return 0;

}