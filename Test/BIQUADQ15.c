#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/filtering_functions.h"


#define SNR_THRESHOLD 30

#define ABS_ERROR_Q15 ((q15)500)


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

    q15 state[32] = {0};
    q15 q15output1[MAX_SIZE] = {0};


	// declare input value
	int paramCountInput1 = 0;
	int paramCountCoefs1 = 0;
	q15 q15inputs1[MAX_SIZE] = {0};
	q15 q15coefs1[MAX_SIZE] = {0};

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
	snprintf(inputFile1, sizeof(inputFile1), "%s%s%s", Patterns_PATH, BIQUADQ15, "BiquadInput1_q15.txt");
#else
	inputFile1 = BIQUADQ15_BiquadInput1_q15;
	inputFile1Len = sizeof(BIQUADQ15_BiquadInput1_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(coefsFile1, sizeof(coefsFile1), "%s%s%s", Patterns_PATH, BIQUADQ15, "BiquadCoefs1_q15.txt");
#else
	coefsFile1 = BIQUADQ15_BiquadCoefs1_q15;
	coefsFile1Len = sizeof(BIQUADQ15_BiquadCoefs1_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile1, sizeof(referenceFile1), "%s%s%s", Patterns_PATH, BIQUADQ15, "BiquadOutput1_q15.txt");
#else
	referenceFile1 = BIQUADQ15_BiquadOutput1_q15;
	referenceFile1Len = sizeof(BIQUADQ15_BiquadOutput1_q15);
	load_data_q15(referenceFile1, referenceFile1Len, referenceData_q15);
#endif


	// load input data
#if defined(NOT_EMBEDDED)
	load_data_q15(inputFile1, &paramCountInput1, q15inputs1);
#else
	paramCountInput1 = inputFile1Len;
	load_data_q15(inputFile1, paramCountInput1, q15inputs1);
	paramCountInput1 = paramCountInput1/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(coefsFile1, &paramCountCoefs1, q15coefs1);
#else
	paramCountCoefs1 = coefsFile1Len;
	load_data_q15(coefsFile1, paramCountCoefs1, q15coefs1);
	paramCountCoefs1 = paramCountCoefs1/sizeof(q15);
#endif



// =======test_biquad_cascade_df1==============
    
    printf("== biquad_cascade_df1 test ==  \n");
    
    //pointers
    q15 *coefsp;
    coefsp = q15coefs1;
    q15 *statep;
    statep = state;
    q15 *inputp;
    inputp = q15inputs1;
    q15 *outp;
    outp = q15output1;
    

	int blockSize;

    blockSize = paramCountInput1 >> 1;

    mips_biquad_casd_df1_inst_q15 S;
    mips_biquad_cascade_df1_init_q15(&S,3,coefsp,statep,2);

    mips_biquad_cascade_df1_q15(&S,inputp,outp,blockSize);
    outp += blockSize;
           
    inputp += blockSize;
    mips_biquad_cascade_df1_q15(&S,inputp,outp,blockSize);
    outp += blockSize;

	printf("biquad_cascade_df1 finish \n");

	printf("biquad_cascade_df1 checking \n\n");

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile1, q15output1, paramCountInput1, ABS_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, q15output1, paramCountInput1, ABS_ERROR_Q15);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile1, q15output1, paramCountInput1, SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output1, paramCountInput1, SNR_THRESHOLD);
#endif


	printf("\n== biquad_cascade_df1 check done  == \n\n");
	
// =====================

	return 0;

}