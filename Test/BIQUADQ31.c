#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/filtering_functions.h"


#define SNR_THRESHOLD 115

#define ABS_ERROR_Q31 ((q31)1000)

#define SNR_32x64_THRESHOLD 140

#define ABS_32x64_ERROR_Q31 ((q31)25)

static void checkInnerTail(q31 *b)
{
    ASSERT_TRUE(b[0] == 0);
    ASSERT_TRUE(b[1] == 0);
    ASSERT_TRUE(b[2] == 0);
    ASSERT_TRUE(b[3] == 0);
}

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

    q31 state[32] = {0};
    q63 state64[32] = {0};
    q31 q31output1[MAX_SIZE] = {0};
    q31 q31output2[MAX_SIZE] = {0};


	// declare input value
	int paramCountInput1 = 0;
	int paramCountCoefs1 = 0;
	q31 q31inputs1[MAX_SIZE] = {0};
	q31 q31coefs1[MAX_SIZE] = {0};

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
	snprintf(inputFile1, sizeof(inputFile1), "%s%s%s", Patterns_PATH, BIQUADQ31, "BiquadInput1_q31.txt");
#else
	inputFile1 = BIQUADQ31_BiquadInput1_q31;
	inputFile1Len = sizeof(BIQUADQ31_BiquadInput1_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(coefsFile1, sizeof(coefsFile1), "%s%s%s", Patterns_PATH, BIQUADQ31, "BiquadCoefs1_q31.txt");
#else
	coefsFile1 = BIQUADQ31_BiquadCoefs1_q31;
	coefsFile1Len = sizeof(BIQUADQ31_BiquadCoefs1_q31);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile1, sizeof(referenceFile1), "%s%s%s", Patterns_PATH, BIQUADQ31, "BiquadOutput1_q31.txt");
#else
	referenceFile1 = BIQUADQ31_BiquadOutput1_q31;
	referenceFile1Len = sizeof(BIQUADQ31_BiquadOutput1_q31);
    load_data_q31(referenceFile1, referenceFile1Len, referenceData_q31);
#endif


	// load input data
#if defined(NOT_EMBEDDED)
	load_data_q31(inputFile1, &paramCountInput1, q31inputs1);
#else
	paramCountInput1 = inputFile1Len;
	load_data_q31(inputFile1, paramCountInput1, q31inputs1);
	paramCountInput1 = paramCountInput1/sizeof(q31);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q31(coefsFile1, &paramCountCoefs1, q31coefs1);
#else
	paramCountCoefs1 = coefsFile1Len;
	load_data_q31(coefsFile1, paramCountCoefs1, q31coefs1);
	paramCountCoefs1 = paramCountCoefs1/sizeof(q31);
#endif



// =======test_biquad_cascade_df1==============
    
    printf("== biquad_cascade_df1 test ==  \n");
    
    //pointers
    q31 *coefsp;
    coefsp = q31coefs1;
    q31 *statep;
    statep = state;
    q31 *inputp;
    inputp = q31inputs1;
    q31 *outp;
    outp = q31output1;
    

	int blockSize;

    blockSize = paramCountInput1 >> 1;

    mips_biquad_casd_df1_inst_q31 S;
    mips_biquad_cascade_df1_init_q31(&S,3,coefsp,statep,2);

    mips_biquad_cascade_df1_q31(&S,inputp,outp,blockSize);
    outp += blockSize;
           
    inputp += blockSize;
    mips_biquad_cascade_df1_q31(&S,inputp,outp,blockSize);
    outp += blockSize;

	printf("biquad_cascade_df1 finish \n");

	printf("biquad_cascade_df1 checking \n\n");

#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile1, q31output1, paramCountInput1, ABS_ERROR_Q31);
#else
	near_check_special_q31(referenceData_q31, q31output1, paramCountInput1, ABS_ERROR_Q31);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile1, q31output1, paramCountInput1, SNR_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, q31output1, paramCountInput1, SNR_THRESHOLD);
#endif


	printf("\n== biquad_cascade_df1 check done  == \n\n");


// =======test_biquad_cascade_df1_32x64==============
    
    printf("== biquad_cascade_df1_32x64 test ==  \n");
    
    //pointers
    coefsp = q31coefs1;
    q63 *state64p;
    state64p = state64;
    inputp = q31inputs1;
    outp = q31output2;
    

    blockSize = paramCountInput1 >> 1;

           /*

           The filter is initialized with the coefs, blockSize and numTaps.

           */
           mips_biquad_cas_df1_32x64_ins_q31 S32x64;
           mips_biquad_cas_df1_32x64_init_q31(&S32x64,3,coefsp,state64p,2);


           /*
           
           Python script is filtering a 2*blockSize number of samples.
           We do the same filtering in two pass to check (indirectly that
           the state management of the fir is working.)

           */
#if 0
           mips_biquad_cas_df1_32x64_q31(&S32x64,inputp,outp,blockSize);
           outp += blockSize;
           
           inputp += blockSize;
           mips_biquad_cas_df1_32x64_q31(&S32x64,inputp,outp,blockSize);
           outp += blockSize;

#else
           int delta=1;
           int k;
           for(k=0;k + delta <2*blockSize ; k+=delta)
           {
             mips_biquad_cas_df1_32x64_q31(&S32x64,inputp,outp,delta);
             outp += delta;
             checkInnerTail(outp);
           
             inputp += delta;
           }
           if (k < 2*blockSize)
           {
             delta = 2*blockSize - k;
             mips_biquad_cas_df1_32x64_q31(&S32x64,inputp,outp,delta);
             outp += delta;
             checkInnerTail(outp);
           
             inputp += delta;
           }
#endif

	printf("biquad_cascade_df1_32x64 finish \n");

	printf("biquad_cascade_df1_32x64 checking \n\n");

#if defined(NOT_EMBEDDED)
	near_check_q31(referenceFile1, q31output2, paramCountInput1, ABS_32x64_ERROR_Q31);
#else
	near_check_special_q31(referenceData_q31, q31output2, paramCountInput1, ABS_32x64_ERROR_Q31);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q31(referenceFile1, q31output2, paramCountInput1, SNR_32x64_THRESHOLD);
#else
	snr_check_special_q31(referenceData_q31, q31output2, paramCountInput1, SNR_32x64_THRESHOLD);
#endif


	printf("\n== biquad_cascade_df1_32x64 check done  == \n\n");
// =====================

	return 0;

}