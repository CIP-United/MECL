#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/filtering_functions.h"

#define SNR_THRESHOLD 65
/* 

Reference patterns are generated with
a double precision computation.

*/
#define ABS_ERROR_Q15 ((q15)10)

#define ABS_ERROR_FAST_Q15 ((q15)20)


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

    q15 *inpA;
    q15 *inpB;
    q15 *outp;
    int nba,nbb,first;

	// declare input value
	int paramCountInputA1 = 0;
	int paramCountInputB1 = 0;
    int paramCountInputA2 = 0;
	int paramCountInputB2 = 0;
    int paramCountReference1 = 0;
	q15 q15inputA1[MAX_SIZE] = {0};
	q15 q15inputB1[MAX_SIZE] = {0};
	q15 q15inputA2[MAX_SIZE] = {0};
    q15 q15inputB2[MAX_SIZE] = {0};
    q15 reference1[MAX_SIZE] = {0};

	// file name. file path max length is 255, so use 255.
#if defined(NOT_EMBEDDED)
	char inputFileA1[255] = {0};
#else
	void *inputFileA1;
	int inputFileA1Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFileB1[255] = {0};
#else
	void *inputFileB1;
	int inputFileB1Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFileA2[255] = {0};
#else
	void *inputFileA2;
	int inputFileA2Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFileB2[255] = {0};
#else
	void *inputFileB2;
	int inputFileB2Len = 0;
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
	snprintf(inputFileA1, sizeof(inputFileA1), "%s%s%s", Patterns_PATH, MISCQ15, "InputsA1_q15.txt");
#else
	inputFileA1 = MISCQ15_InputsA1_q15;
	inputFileA1Len = sizeof(MISCQ15_InputsA1_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileB1, sizeof(inputFileB1), "%s%s%s", Patterns_PATH, MISCQ15, "InputsB1_q15.txt");
#else
	inputFileB1 = MISCQ15_InputsB1_q15;
	inputFileB1Len = sizeof(MISCQ15_InputsB1_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileA2, sizeof(inputFileA2), "%s%s%s", Patterns_PATH, MISCQ15, "InputsA2_q15.txt");
#else
	inputFileA2 = MISCQ15_InputsA2_q15;
	inputFileA2Len = sizeof(MISCQ15_InputsA2_q15);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileB2, sizeof(inputFileB2), "%s%s%s", Patterns_PATH, MISCQ15, "InputsB2_q15.txt");
#else
	inputFileB2 = MISCQ15_InputsB2_q15;
	inputFileB2Len = sizeof(MISCQ15_InputsB2_q15);
#endif




	// load input data
#if defined(NOT_EMBEDDED)
	load_data_q15(inputFileA1, &paramCountInputA1, q15inputA1);
#else
	paramCountInputA1 = inputFileA1Len;
	load_data_q15(inputFileA1, paramCountInputA1, q15inputA1);
	paramCountInputA1 = paramCountInputA1/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(inputFileB1, &paramCountInputB1, q15inputB1);
#else
	paramCountInputB1 = inputFileB1Len;
	load_data_q15(inputFileB1, paramCountInputB1, q15inputB1);
	paramCountInputB1 = paramCountInputB1/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(inputFileA2, &paramCountInputA2, q15inputA2);
#else
	paramCountInputA2 = inputFileA2Len;
	load_data_q15(inputFileA2, paramCountInputA2, q15inputA2);
	paramCountInputA2 = paramCountInputA2/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(inputFileB2, &paramCountInputB2, q15inputB2);
#else
	paramCountInputB2 = inputFileB2Len;
	load_data_q15(inputFileB2, paramCountInputB2, q15inputB2);
	paramCountInputB2 = paramCountInputB2/sizeof(q15);
#endif

    int num = 0;
    q15 q15output1[MAX_SIZE] = {0};
#if defined(NOT_EMBEDDED)
    char *id[] = {"Reference1_q15.txt", "Reference2_q15.txt", "Reference3_q15.txt", "Reference4_q15.txt", "Reference5_q15.txt", "Reference6_q15.txt", "Reference7_q15.txt", "Reference8_q15.txt", "Reference9_q15.txt", "Reference10_q15.txt", "Reference11_q15.txt", "Reference12_q15.txt", "Reference13_q15.txt", "Reference14_q15.txt", "Reference15_q15.txt", "Reference16_q15.txt", "Reference17_q15.txt", "Reference18_q15.txt", "Reference19_q15.txt", "Reference20_q15.txt", "Reference21_q15.txt", "Reference22_q15.txt", "Reference23_q15.txt", "Reference24_q15.txt", "Reference25_q15.txt", "Reference26_q15.txt", "Reference27_q15.txt", "Reference28_q15.txt", "Reference29_q15.txt", "Reference30_q15.txt", "Reference31_q15.txt", "Reference32_q15.txt", "Reference33_q15.txt", "Reference34_q15.txt", "Reference35_q15.txt", "Reference36_q15.txt", "Reference37_q15.txt", "Reference38_q15.txt", "Reference39_q15.txt", "Reference40_q15.txt", "Reference41_q15.txt", "Reference42_q15.txt", "Reference43_q15.txt", "Reference44_q15.txt", "Reference45_q15.txt", "Reference46_q15.txt", "Reference47_q15.txt", "Reference48_q15.txt", "Reference49_q15.txt", "Reference50_q15.txt", "Reference54_q15.txt", "Reference55_q15.txt", "Reference56_q15.txt", "Reference54_q15.txt", "Reference55_q15.txt", "Reference56_q15.txt"};
#else
    u64 id[100] = {MISCQ15_Reference1_q15, MISCQ15_Reference2_q15, MISCQ15_Reference3_q15, MISCQ15_Reference4_q15, MISCQ15_Reference5_q15, MISCQ15_Reference6_q15, MISCQ15_Reference7_q15, MISCQ15_Reference8_q15, MISCQ15_Reference9_q15, MISCQ15_Reference10_q15, MISCQ15_Reference11_q15, MISCQ15_Reference12_q15, MISCQ15_Reference13_q15, MISCQ15_Reference14_q15, MISCQ15_Reference15_q15, MISCQ15_Reference16_q15, MISCQ15_Reference17_q15, MISCQ15_Reference18_q15, MISCQ15_Reference19_q15, MISCQ15_Reference20_q15, MISCQ15_Reference21_q15, MISCQ15_Reference22_q15, MISCQ15_Reference23_q15, MISCQ15_Reference24_q15, MISCQ15_Reference25_q15, MISCQ15_Reference26_q15, MISCQ15_Reference27_q15, MISCQ15_Reference28_q15, MISCQ15_Reference29_q15, MISCQ15_Reference30_q15, MISCQ15_Reference31_q15, MISCQ15_Reference32_q15, MISCQ15_Reference33_q15, MISCQ15_Reference34_q15, MISCQ15_Reference35_q15, MISCQ15_Reference36_q15, MISCQ15_Reference37_q15, MISCQ15_Reference38_q15, MISCQ15_Reference39_q15, MISCQ15_Reference40_q15, MISCQ15_Reference41_q15, MISCQ15_Reference42_q15, MISCQ15_Reference43_q15, MISCQ15_Reference44_q15, MISCQ15_Reference45_q15, MISCQ15_Reference46_q15, MISCQ15_Reference47_q15, MISCQ15_Reference48_q15, MISCQ15_Reference49_q15, MISCQ15_Reference50_q15, MISCQ15_Reference54_q15, MISCQ15_Reference55_q15, MISCQ15_Reference56_q15, MISCQ15_Reference54_q15, MISCQ15_Reference55_q15, MISCQ15_Reference56_q15};
    u32 size[100] = {sizeof(MISCQ15_Reference1_q15), sizeof(MISCQ15_Reference2_q15), sizeof(MISCQ15_Reference3_q15), sizeof(MISCQ15_Reference4_q15), sizeof(MISCQ15_Reference5_q15), sizeof(MISCQ15_Reference6_q15), sizeof(MISCQ15_Reference7_q15), sizeof(MISCQ15_Reference8_q15), sizeof(MISCQ15_Reference9_q15), sizeof(MISCQ15_Reference10_q15), sizeof(MISCQ15_Reference11_q15), sizeof(MISCQ15_Reference12_q15), sizeof(MISCQ15_Reference13_q15), sizeof(MISCQ15_Reference14_q15), sizeof(MISCQ15_Reference15_q15), sizeof(MISCQ15_Reference16_q15), sizeof(MISCQ15_Reference17_q15), sizeof(MISCQ15_Reference18_q15), sizeof(MISCQ15_Reference19_q15), sizeof(MISCQ15_Reference20_q15), sizeof(MISCQ15_Reference21_q15), sizeof(MISCQ15_Reference22_q15), sizeof(MISCQ15_Reference23_q15), sizeof(MISCQ15_Reference24_q15), sizeof(MISCQ15_Reference25_q15), sizeof(MISCQ15_Reference26_q15), sizeof(MISCQ15_Reference27_q15), sizeof(MISCQ15_Reference28_q15), sizeof(MISCQ15_Reference29_q15), sizeof(MISCQ15_Reference30_q15), sizeof(MISCQ15_Reference31_q15), sizeof(MISCQ15_Reference32_q15), sizeof(MISCQ15_Reference33_q15), sizeof(MISCQ15_Reference34_q15), sizeof(MISCQ15_Reference35_q15), sizeof(MISCQ15_Reference36_q15), sizeof(MISCQ15_Reference37_q15), sizeof(MISCQ15_Reference38_q15), sizeof(MISCQ15_Reference39_q15), sizeof(MISCQ15_Reference40_q15), sizeof(MISCQ15_Reference41_q15), sizeof(MISCQ15_Reference42_q15), sizeof(MISCQ15_Reference43_q15), sizeof(MISCQ15_Reference44_q15), sizeof(MISCQ15_Reference45_q15), sizeof(MISCQ15_Reference46_q15), sizeof(MISCQ15_Reference47_q15), sizeof(MISCQ15_Reference48_q15), sizeof(MISCQ15_Reference49_q15), sizeof(MISCQ15_Reference50_q15), sizeof(MISCQ15_Reference54_q15), sizeof(MISCQ15_Reference55_q15), sizeof(MISCQ15_Reference56_q15), sizeof(MISCQ15_Reference54_q15), sizeof(MISCQ15_Reference55_q15), sizeof(MISCQ15_Reference56_q15)};
#endif
// =======test_correlate_q15==============

    for(num = 1; num <= 25; num++){

    inpA = q15inputA1;
    inpB = q15inputB1;
    outp = q15output1;
    printf("test:%d \n",num);
    switch (num)
    {
    case 1:
        nba = 14;
        nbb = 15;
        break;
    case 2:
        nba = 14;
        nbb = 16;
        break;
    case 3:
        nba = 14;
        nbb = 17;
        break;
    case 4:
        nba = 14;
        nbb = 18;
        break;
    case 5:
        nba = 14;
        nbb = 33;
        break;
    case 6:
        nba = 15;
        nbb = 15;
        break;
    case 7:
        nba = 15;
        nbb = 16;
        break;
    case 8:
        nba = 15;
        nbb = 17;
        break;
    case 9:
        nba = 15;
        nbb = 18;
        break;
    case 10:
        nba = 15;
        nbb = 33;
        break;
     case 11:
        nba = 16;
        nbb = 15;
        break;
    case 12:
        nba = 16;
        nbb = 16;
        break;
    case 13:
        nba = 16;
        nbb = 17;
        break;
    case 14:
        nba = 16;
        nbb = 18;
        break;
    case 15:
        nba = 16;
        nbb = 33;
        break;
    case 16:
        nba = 17;
        nbb = 15;
        break;
    case 17:
        nba = 17;
        nbb = 16;
        break;
    case 18:
        nba = 17;
        nbb = 17;
        break;
    case 19:
        nba = 17;
        nbb = 18;
        break;
    case 20:
        nba = 17;
        nbb = 33;
        break;
    case 21:
        nba = 32;
        nbb = 15;
        break;
    case 22:
        nba = 32;
        nbb = 16;
        break;
    case 23:
        nba = 32;
        nbb = 17;
        break;
    case 24:
        nba = 32;
        nbb = 18;
        break;
    case 25:
        nba = 32;
        nbb = 33;
        break;
    
    default:
        break;
    }
    printf("== correlate_q15  test ==  \n");

    mips_correlate_q15(inpA, nba,
      inpB, nbb,
      outp);
    
	printf("correlate_q15 finish \n");

	printf("correlate_q15 checking \n\n");

#if defined(NOT_EMBEDDED) 
    snprintf(referenceFile1, sizeof(referenceFile1), "%s%s%s", Patterns_PATH, MISCQ15, id[num-1]);
#else
	referenceFile1 = id[num-1];
	referenceFile1Len = size[num-1];
    load_data_q15(referenceFile1, referenceFile1Len, referenceData_q15);
    referenceFile1Len = referenceFile1Len/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile1, q15output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output1, referenceFile1Len, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile1, q15output1, 0, ABS_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, q15output1, referenceFile1Len, ABS_ERROR_Q15);
#endif

    memset(q15output1, 0, sizeof(q15)*MAX_SIZE);
#if !defined(NOT_EMBEDDED)
    memset(referenceData_q15, 0, sizeof(q15)*MAX_SIZE);
#endif
	printf("\n== correlate_q15 check done  == \n\n");
    };

// =======test_conv_q15 ==============

    for(num = 1; num <= 25; num++){

    inpA = q15inputA1;
    inpB = q15inputB1;
    outp = q15output1;
    printf("test:%d \n",(num+25));
    switch (num)
    {
    case 1:
        nba = 14;
        nbb = 15;
        break;
    case 2:
        nba = 14;
        nbb = 16;
        break;
    case 3:
        nba = 14;
        nbb = 17;
        break;
    case 4:
        nba = 14;
        nbb = 18;
        break;
    case 5:
        nba = 14;
        nbb = 33;
        break;
    case 6:
        nba = 15;
        nbb = 15;
        break;
    case 7:
        nba = 15;
        nbb = 16;
        break;
    case 8:
        nba = 15;
        nbb = 17;
        break;
    case 9:
        nba = 15;
        nbb = 18;
        break;
    case 10:
        nba = 15;
        nbb = 33;
        break;
     case 11:
        nba = 16;
        nbb = 15;
        break;
    case 12:
        nba = 16;
        nbb = 16;
        break;
    case 13:
        nba = 16;
        nbb = 17;
        break;
    case 14:
        nba = 16;
        nbb = 18;
        break;
    case 15:
        nba = 16;
        nbb = 33;
        break;
    case 16:
        nba = 17;
        nbb = 15;
        break;
    case 17:
        nba = 17;
        nbb = 16;
        break;
    case 18:
        nba = 17;
        nbb = 17;
        break;
    case 19:
        nba = 17;
        nbb = 18;
        break;
    case 20:
        nba = 17;
        nbb = 33;
        break;
    case 21:
        nba = 32;
        nbb = 15;
        break;
    case 22:
        nba = 32;
        nbb = 16;
        break;
    case 23:
        nba = 32;
        nbb = 17;
        break;
    case 24:
        nba = 32;
        nbb = 18;
        break;
    case 25:
        nba = 32;
        nbb = 33;
        break;

    default:
        break;
    }
    printf("== conv_q15  test ==  \n");

    mips_conv_q15(inpA, nba,
      inpB, nbb,
      outp);
    
	printf("conv_q15 finish \n");

	printf("conv_q15 checking \n\n");

#if defined(NOT_EMBEDDED) 
    snprintf(referenceFile1, sizeof(referenceFile1), "%s%s%s", Patterns_PATH, MISCQ15, id[num+25-1]);
#else
	referenceFile1 = id[num+25-1];
	referenceFile1Len = size[num+25-1];
    load_data_q15(referenceFile1, referenceFile1Len, referenceData_q15);
    referenceFile1Len = referenceFile1Len/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile1, q15output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, q15output1, referenceFile1Len, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile1, q15output1, 0, ABS_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, q15output1, referenceFile1Len, ABS_ERROR_Q15);
#endif

    memset(q15output1, 0, sizeof(q15)*MAX_SIZE);
#if !defined(NOT_EMBEDDED)
    memset(referenceData_q15, 0, sizeof(q15)*MAX_SIZE);
#endif
	printf("\n== conv_q15 check done  == \n\n");
    };

// =======test_conv_partial_q15==============
    // This value must be coherent with the Python script
    // generating the test patterns
#define NBPOINTS 4

    q15 tmp[MAX_SIZE] = {0};
    q15 *tmpp;

 for(num = 1; num <= 3; num++){
    inpA = q15inputA2;
    inpB = q15inputB2;
    outp = q15output1;
    tmpp = tmp;
    printf("test:%d \n",(num+50));
    switch (num)
    {
    case 1:
        first=3;
        nba = 6;
        nbb = 8;
        break;
    case 2:
        first=9;
        nba = 6;
        nbb = 8;
        break;
    case 3:
        first=7;
        nba = 6;
        nbb = 8;
        break;

    default:
        break;
    }
    printf("== conv_partial_q15  test ==  \n");

    mips_status status=mips_conv_partial_q15(inpA, nba,
          inpB, nbb,
          outp,
          first,
          NBPOINTS);


    memcpy((void*)tmpp,(void*)&outp[first],NBPOINTS*sizeof(q15));

	printf("conv_partial_q15 finish \n");

	printf("conv_partial_q15 checking \n\n");

#if defined(NOT_EMBEDDED) 
    snprintf(referenceFile1, sizeof(referenceFile1), "%s%s%s", Patterns_PATH, MISCQ15, id[num+50-1]);
#else
	referenceFile1 = id[num+50-1];
	referenceFile1Len = size[num+50-1];
    load_data_q15(referenceFile1, referenceFile1Len, referenceData_q15);
    referenceFile1Len = referenceFile1Len/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile1, tmp, 0, SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, tmp, referenceFile1Len, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile1, tmp, 0, ABS_ERROR_Q15);
#else
	near_check_special_q15(referenceData_q15, tmp, referenceFile1Len, ABS_ERROR_Q15);
#endif

    ASSERT_TRUE(status==MIPS_MATH_SUCCESS);

    memset(q15output1, 0, sizeof(q15)*MAX_SIZE);
    memset(tmp, 0, sizeof(q15)*MAX_SIZE);
#if !defined(NOT_EMBEDDED)
    memset(referenceData_q15, 0, sizeof(q15)*MAX_SIZE);
#endif
	printf("\n== conv_partial_q15 check done  == \n\n");
    };

// =======test_conv_partial_opt_q15==============

    q15 scratchA[24] = {0};
    q15 scratchB[24] = {0};
    q15 *scratchAp;
    q15 *scratchBp;

 for(num = 1; num <= 3; num++){
    inpA = q15inputA2;
    inpB = q15inputB2;
    outp = q15output1;
    tmpp = tmp;
    scratchAp = scratchA;
    scratchBp = scratchB;
    printf("test:%d \n",(num+53));
    switch (num)
    {
    case 1:
        first=3;
        nba = 6;
        nbb = 8;
        break;
    case 2:
        first=9;
        nba = 6;
        nbb = 8;
        break;
    case 3:
        first=7;
        nba = 6;
        nbb = 8;
        break;

    default:
        break;
    }
    printf("== conv_partial_opt_q15  test ==  \n");

    mips_status status=mips_conv_partial_opt_q15(inpA, nba,
          inpB, nbb,
          outp,
          first,
          NBPOINTS,
          scratchAp,
          scratchBp
          );

    memcpy((void*)tmpp,(void*)&outp[first],NBPOINTS*sizeof(q15));

	printf("conv_partial_opt_q15 finish \n");

	printf("conv_partial_opt_q15 checking \n\n");

#if defined(NOT_EMBEDDED) 
    snprintf(referenceFile1, sizeof(referenceFile1), "%s%s%s", Patterns_PATH, MISCQ15, id[num+53-1]);
#else
	referenceFile1 = id[num+53-1];
	referenceFile1Len = size[num+53-1];
    load_data_q15(referenceFile1, referenceFile1Len, referenceData_q15);
    referenceFile1Len = referenceFile1Len/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q15(referenceFile1, tmp, 0, SNR_THRESHOLD);
#else
	snr_check_special_q15(referenceData_q15, tmp, referenceFile1Len, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q15(referenceFile1, tmp, 0, ABS_ERROR_FAST_Q15);
#else
	near_check_special_q15(referenceData_q15, tmp, referenceFile1Len, ABS_ERROR_FAST_Q15);
#endif

    ASSERT_TRUE(status==MIPS_MATH_SUCCESS);

    memset(q15output1, 0, sizeof(q15)*MAX_SIZE);
    memset(tmp, 0, sizeof(q15)*MAX_SIZE);
#if !defined(NOT_EMBEDDED)
    memset(referenceData_q15, 0, sizeof(q15)*MAX_SIZE);
#endif
	printf("\n== conv_partial_opt_q15 check done  == \n\n");
    };
    return 0;
}

	

