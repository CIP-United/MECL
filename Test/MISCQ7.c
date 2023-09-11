#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/filtering_functions.h"

#define SNR_THRESHOLD 15
/* 

Reference patterns are generated with
a double precision computation.

*/
#define ABS_ERROR_Q7 ((q7)5)
#define ABS_ERROR_FAST_Q7 ((q7)5)


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

    q7 *inpA;
    q7 *inpB;
    q7 *outp;
    int nba,nbb,first;

	// declare input value
	int paramCountInputA1 = 0;
	int paramCountInputB1 = 0;
    int paramCountInputA2 = 0;
	int paramCountInputB2 = 0;
    int paramCountReference1 = 0;
	q7 q7inputA1[MAX_SIZE] = {0};
	q7 q7inputB1[MAX_SIZE] = {0};
	q7 q7inputA2[MAX_SIZE] = {0};
    q7 q7inputB2[MAX_SIZE] = {0};
    q7 reference1[MAX_SIZE] = {0};

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
	snprintf(inputFileA1, sizeof(inputFileA1), "%s%s%s", Patterns_PATH, MISCQ7, "InputsA1_q7.txt");
#else
	inputFileA1 = MISCQ7_InputsA1_q7;
	inputFileA1Len = sizeof(MISCQ7_InputsA1_q7);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileB1, sizeof(inputFileB1), "%s%s%s", Patterns_PATH, MISCQ7, "InputsB1_q7.txt");
#else
	inputFileB1 = MISCQ7_InputsB1_q7;
	inputFileB1Len = sizeof(MISCQ7_InputsB1_q7);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileA2, sizeof(inputFileA2), "%s%s%s", Patterns_PATH, MISCQ7, "InputsA2_q7.txt");
#else
	inputFileA2 = MISCQ7_InputsA2_q7;
	inputFileA2Len = sizeof(MISCQ7_InputsA2_q7);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileB2, sizeof(inputFileB2), "%s%s%s", Patterns_PATH, MISCQ7, "InputsB2_q7.txt");
#else
	inputFileB2 = MISCQ7_InputsB2_q7;
	inputFileB2Len = sizeof(MISCQ7_InputsB2_q7);
#endif




	// load input data
#if defined(NOT_EMBEDDED)
	load_data_q7(inputFileA1, &paramCountInputA1, q7inputA1);
#else
	paramCountInputA1 = inputFileA1Len;
	load_data_q7(inputFileA1, paramCountInputA1, q7inputA1);
	paramCountInputA1 = paramCountInputA1/sizeof(q7);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q7(inputFileB1, &paramCountInputB1, q7inputB1);
#else
	paramCountInputB1 = inputFileB1Len;
	load_data_q7(inputFileB1, paramCountInputB1, q7inputB1);
	paramCountInputB1 = paramCountInputB1/sizeof(q7);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q7(inputFileA2, &paramCountInputA2, q7inputA2);
#else
	paramCountInputA2 = inputFileA2Len;
	load_data_q7(inputFileA2, paramCountInputA2, q7inputA2);
	paramCountInputA2 = paramCountInputA2/sizeof(q7);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q7(inputFileB2, &paramCountInputB2, q7inputB2);
#else
	paramCountInputB2 = inputFileB2Len;
	load_data_q7(inputFileB2, paramCountInputB2, q7inputB2);
	paramCountInputB2 = paramCountInputB2/sizeof(q7);
#endif

    int num = 0;
    q7 q7output1[MAX_SIZE] = {0};
#if defined(NOT_EMBEDDED)
    char *id[] = {"Reference1_q7.txt", "Reference2_q7.txt", "Reference3_q7.txt", "Reference4_q7.txt", "Reference5_q7.txt", "Reference6_q7.txt", "Reference7_q7.txt", "Reference8_q7.txt", "Reference9_q7.txt", "Reference10_q7.txt", "Reference11_q7.txt", "Reference12_q7.txt", "Reference13_q7.txt", "Reference14_q7.txt", "Reference15_q7.txt", "Reference16_q7.txt", "Reference17_q7.txt", "Reference18_q7.txt", "Reference19_q7.txt", "Reference20_q7.txt", "Reference21_q7.txt", "Reference22_q7.txt", "Reference23_q7.txt", "Reference24_q7.txt", "Reference25_q7.txt", "Reference26_q7.txt", "Reference27_q7.txt", "Reference28_q7.txt", "Reference29_q7.txt", "Reference30_q7.txt", "Reference31_q7.txt", "Reference32_q7.txt", "Reference33_q7.txt", "Reference34_q7.txt", "Reference35_q7.txt", "Reference36_q7.txt", "Reference37_q7.txt", "Reference38_q7.txt", "Reference39_q7.txt", "Reference40_q7.txt", "Reference41_q7.txt", "Reference42_q7.txt", "Reference43_q7.txt", "Reference44_q7.txt", "Reference45_q7.txt", "Reference46_q7.txt", "Reference47_q7.txt", "Reference48_q7.txt", "Reference49_q7.txt", "Reference50_q7.txt", "Reference54_q7.txt", "Reference55_q7.txt", "Reference56_q7.txt", "Reference54_q7.txt", "Reference55_q7.txt", "Reference56_q7.txt"};
#else
    u64 id[100] = {MISCQ7_Reference1_q7, MISCQ7_Reference2_q7, MISCQ7_Reference3_q7, MISCQ7_Reference4_q7, MISCQ7_Reference5_q7, MISCQ7_Reference6_q7, MISCQ7_Reference7_q7, MISCQ7_Reference8_q7, MISCQ7_Reference9_q7, MISCQ7_Reference10_q7, MISCQ7_Reference11_q7, MISCQ7_Reference12_q7, MISCQ7_Reference13_q7, MISCQ7_Reference14_q7, MISCQ7_Reference15_q7, MISCQ7_Reference16_q7, MISCQ7_Reference17_q7, MISCQ7_Reference18_q7, MISCQ7_Reference19_q7, MISCQ7_Reference20_q7, MISCQ7_Reference21_q7, MISCQ7_Reference22_q7, MISCQ7_Reference23_q7, MISCQ7_Reference24_q7, MISCQ7_Reference25_q7, MISCQ7_Reference26_q7, MISCQ7_Reference27_q7, MISCQ7_Reference28_q7, MISCQ7_Reference29_q7, MISCQ7_Reference30_q7, MISCQ7_Reference31_q7, MISCQ7_Reference32_q7, MISCQ7_Reference33_q7, MISCQ7_Reference34_q7, MISCQ7_Reference35_q7, MISCQ7_Reference36_q7, MISCQ7_Reference37_q7, MISCQ7_Reference38_q7, MISCQ7_Reference39_q7, MISCQ7_Reference40_q7, MISCQ7_Reference41_q7, MISCQ7_Reference42_q7, MISCQ7_Reference43_q7, MISCQ7_Reference44_q7, MISCQ7_Reference45_q7, MISCQ7_Reference46_q7, MISCQ7_Reference47_q7, MISCQ7_Reference48_q7, MISCQ7_Reference49_q7, MISCQ7_Reference50_q7, MISCQ7_Reference54_q7, MISCQ7_Reference55_q7, MISCQ7_Reference56_q7, MISCQ7_Reference54_q7, MISCQ7_Reference55_q7, MISCQ7_Reference56_q7};
    u32 size[100] = {sizeof(MISCQ7_Reference1_q7), sizeof(MISCQ7_Reference2_q7), sizeof(MISCQ7_Reference3_q7), sizeof(MISCQ7_Reference4_q7), sizeof(MISCQ7_Reference5_q7), sizeof(MISCQ7_Reference6_q7), sizeof(MISCQ7_Reference7_q7), sizeof(MISCQ7_Reference8_q7), sizeof(MISCQ7_Reference9_q7), sizeof(MISCQ7_Reference10_q7), sizeof(MISCQ7_Reference11_q7), sizeof(MISCQ7_Reference12_q7), sizeof(MISCQ7_Reference13_q7), sizeof(MISCQ7_Reference14_q7), sizeof(MISCQ7_Reference15_q7), sizeof(MISCQ7_Reference16_q7), sizeof(MISCQ7_Reference17_q7), sizeof(MISCQ7_Reference18_q7), sizeof(MISCQ7_Reference19_q7), sizeof(MISCQ7_Reference20_q7), sizeof(MISCQ7_Reference21_q7), sizeof(MISCQ7_Reference22_q7), sizeof(MISCQ7_Reference23_q7), sizeof(MISCQ7_Reference24_q7), sizeof(MISCQ7_Reference25_q7), sizeof(MISCQ7_Reference26_q7), sizeof(MISCQ7_Reference27_q7), sizeof(MISCQ7_Reference28_q7), sizeof(MISCQ7_Reference29_q7), sizeof(MISCQ7_Reference30_q7), sizeof(MISCQ7_Reference31_q7), sizeof(MISCQ7_Reference32_q7), sizeof(MISCQ7_Reference33_q7), sizeof(MISCQ7_Reference34_q7), sizeof(MISCQ7_Reference35_q7), sizeof(MISCQ7_Reference36_q7), sizeof(MISCQ7_Reference37_q7), sizeof(MISCQ7_Reference38_q7), sizeof(MISCQ7_Reference39_q7), sizeof(MISCQ7_Reference40_q7), sizeof(MISCQ7_Reference41_q7), sizeof(MISCQ7_Reference42_q7), sizeof(MISCQ7_Reference43_q7), sizeof(MISCQ7_Reference44_q7), sizeof(MISCQ7_Reference45_q7), sizeof(MISCQ7_Reference46_q7), sizeof(MISCQ7_Reference47_q7), sizeof(MISCQ7_Reference48_q7), sizeof(MISCQ7_Reference49_q7), sizeof(MISCQ7_Reference50_q7), sizeof(MISCQ7_Reference54_q7), sizeof(MISCQ7_Reference55_q7), sizeof(MISCQ7_Reference56_q7), sizeof(MISCQ7_Reference54_q7), sizeof(MISCQ7_Reference55_q7), sizeof(MISCQ7_Reference56_q7)};
#endif
// =======test_correlate_q7==============

    for(num = 1; num <= 25; num++){

    inpA = q7inputA1;
    inpB = q7inputB1;
    outp = q7output1;
    printf("test:%d \n",num);
    switch (num)
    {
    case 1:
        nba = 30;
        nbb = 31;
        break;
    case 2:
        nba = 30;
        nbb = 32;
        break;
    case 3:
        nba = 30;
        nbb = 33;
        break;
    case 4:
        nba = 30;
        nbb = 34;
        break;
    case 5:
        nba = 30;
        nbb = 49;
        break;
    case 6:
        nba = 31;
        nbb = 31;
        break;
    case 7:
        nba = 31;
        nbb = 32;
        break;
    case 8:
        nba = 31;
        nbb = 33;
        break;
    case 9:
        nba = 31;
        nbb = 34;
        break;
    case 10:
        nba = 31;
        nbb = 49;
        break;
     case 11:
        nba = 32;
        nbb = 31;
        break;
    case 12:
        nba = 32;
        nbb = 32;
        break;
    case 13:
        nba = 32;
        nbb = 33;
        break;
    case 14:
        nba = 32;
        nbb = 34;
        break;
    case 15:
        nba = 32;
        nbb = 49;
        break;
    case 16:
        nba = 33;
        nbb = 31;
        break;
    case 17:
        nba = 33;
        nbb = 32;
        break;
    case 18:
        nba = 33;
        nbb = 33;
        break;
    case 19:
        nba = 33;
        nbb = 34;
        break;
    case 20:
        nba = 33;
        nbb = 49;
        break;
    case 21:
        nba = 48;
        nbb = 31;
        break;
    case 22:
        nba = 48;
        nbb = 32;
        break;
    case 23:
        nba = 48;
        nbb = 33;
        break;
    case 24:
        nba = 48;
        nbb = 34;
        break;
    case 25:
        nba = 48;
        nbb = 49;
        break;
    
    default:
        break;
    }
    printf("== correlate_q7  test ==  \n");

    mips_correlate_q7(inpA, nba,
      inpB, nbb,
      outp);
    
	printf("correlate_q7 finish \n");

	printf("correlate_q7 checking \n\n");

#if defined(NOT_EMBEDDED) 
    snprintf(referenceFile1, sizeof(referenceFile1), "%s%s%s", Patterns_PATH, MISCQ7, id[num-1]);
#else
	referenceFile1 = id[num-1];
	referenceFile1Len = size[num-1];
    load_data_q7(referenceFile1, referenceFile1Len, referenceData_q7);
    referenceFile1Len = referenceFile1Len/sizeof(q7);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q7(referenceFile1, q7output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q7(referenceData_q7, q7output1, referenceFile1Len, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q7(referenceFile1, q7output1, 0, ABS_ERROR_Q7);
#else
	near_check_special_q7(referenceData_q7, q7output1, referenceFile1Len, ABS_ERROR_Q7);
#endif

    memset(q7output1, 0, sizeof(q7)*MAX_SIZE);
#if !defined(NOT_EMBEDDED)
    memset(referenceData_q7, 0, sizeof(q7)*MAX_SIZE);
#endif
	printf("\n== correlate_q7 check done  == \n\n");
    };

// =======test_conv_q7 ==============

    for(num = 1; num <= 25; num++){

    inpA = q7inputA1;
    inpB = q7inputB1;
    outp = q7output1;
    printf("test:%d \n",(num+25));
    switch (num)
    {
    case 1:
        nba = 30;
        nbb = 31;
        break;
    case 2:
        nba = 30;
        nbb = 32;
        break;
    case 3:
        nba = 30;
        nbb = 33;
        break;
    case 4:
        nba = 30;
        nbb = 34;
        break;
    case 5:
        nba = 30;
        nbb = 49;
        break;
    case 6:
        nba = 31;
        nbb = 31;
        break;
    case 7:
        nba = 31;
        nbb = 32;
        break;
    case 8:
        nba = 31;
        nbb = 33;
        break;
    case 9:
        nba = 31;
        nbb = 34;
        break;
    case 10:
        nba = 31;
        nbb = 49;
        break;
     case 11:
        nba = 32;
        nbb = 31;
        break;
    case 12:
        nba = 32;
        nbb = 32;
        break;
    case 13:
        nba = 32;
        nbb = 33;
        break;
    case 14:
        nba = 32;
        nbb = 34;
        break;
    case 15:
        nba = 32;
        nbb = 49;
        break;
    case 16:
        nba = 33;
        nbb = 31;
        break;
    case 17:
        nba = 33;
        nbb = 32;
        break;
    case 18:
        nba = 33;
        nbb = 33;
        break;
    case 19:
        nba = 33;
        nbb = 34;
        break;
    case 20:
        nba = 33;
        nbb = 49;
        break;
    case 21:
        nba = 48;
        nbb = 31;
        break;
    case 22:
        nba = 48;
        nbb = 32;
        break;
    case 23:
        nba = 48;
        nbb = 33;
        break;
    case 24:
        nba = 48;
        nbb = 34;
        break;
    case 25:
        nba = 48;
        nbb = 49;
        break;

    default:
        break;
    }
    printf("== conv_q7  test ==  \n");

    mips_conv_q7(inpA, nba,
      inpB, nbb,
      outp);
    
	printf("conv_q7 finish \n");

	printf("conv_q7 checking \n\n");

#if defined(NOT_EMBEDDED) 
    snprintf(referenceFile1, sizeof(referenceFile1), "%s%s%s", Patterns_PATH, MISCQ7, id[num+25-1]);
#else
	referenceFile1 = id[num+25-1];
	referenceFile1Len = size[num+25-1];
    load_data_q7(referenceFile1, referenceFile1Len, referenceData_q7);
    referenceFile1Len = referenceFile1Len/sizeof(q7);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q7(referenceFile1, q7output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_q7(referenceData_q7, q7output1, referenceFile1Len, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q7(referenceFile1, q7output1, 0, ABS_ERROR_Q7);
#else
	near_check_special_q7(referenceData_q7, q7output1, referenceFile1Len, ABS_ERROR_Q7);
#endif

    memset(q7output1, 0, sizeof(q7)*MAX_SIZE);
#if !defined(NOT_EMBEDDED)
    memset(referenceData_q7, 0, sizeof(q7)*MAX_SIZE);
#endif
	printf("\n== conv_q7 check done  == \n\n");
    };

// =======test_conv_partial_q7==============
    // This value must be coherent with the Python script
    // generating the test patterns
#define NBPOINTS 4

    q7 tmp[MAX_SIZE] = {0};
    q7 *tmpp;

 for(num = 1; num <= 3; num++){
    inpA = q7inputA2;
    inpB = q7inputB2;
    outp = q7output1;
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
    printf("== conv_partial_q7  test ==  \n");

    mips_status status=mips_conv_partial_q7(inpA, nba,
          inpB, nbb,
          outp,
          first,
          NBPOINTS);


    memcpy((void*)tmpp,(void*)&outp[first],NBPOINTS*sizeof(q7));

	printf("conv_partial_q7 finish \n");

	printf("conv_partial_q7 checking \n\n");

#if defined(NOT_EMBEDDED) 
    snprintf(referenceFile1, sizeof(referenceFile1), "%s%s%s", Patterns_PATH, MISCQ7, id[num+50-1]);
#else
	referenceFile1 = id[num+50-1];
	referenceFile1Len = size[num+50-1];
    load_data_q7(referenceFile1, referenceFile1Len, referenceData_q7);
    referenceFile1Len = referenceFile1Len/sizeof(q7);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q7(referenceFile1, tmp, 0, SNR_THRESHOLD);
#else
	snr_check_special_q7(referenceData_q7, tmp, referenceFile1Len, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q7(referenceFile1, tmp, 0, ABS_ERROR_Q7);
#else
	near_check_special_q7(referenceData_q7, tmp, referenceFile1Len, ABS_ERROR_Q7);
#endif

    ASSERT_TRUE(status==MIPS_MATH_SUCCESS);

    memset(q7output1, 0, sizeof(q7)*MAX_SIZE);
#if !defined(NOT_EMBEDDED)
    memset(referenceData_q7, 0, sizeof(q7)*MAX_SIZE);
#endif
    memset(tmp, 0, sizeof(q7)*MAX_SIZE);
	printf("\n== conv_partial_q7 check done  == \n\n");
    };

// =======test_conv_partial_opt_q7==============

    q15 scratchA[24] = {0};
    q15 scratchB[24] = {0};
    q15 *scratchAp;
    q15 *scratchBp;

 for(num = 1; num <= 3; num++){
    inpA = q7inputA2;
    inpB = q7inputB2;
    outp = q7output1;
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
    printf("== conv_partial_opt_q7  test ==  \n");

    mips_status status=mips_conv_partial_opt_q7(inpA, nba,
          inpB, nbb,
          outp,
          first,
          NBPOINTS,
          scratchAp,
          scratchBp
          );

    memcpy((void*)tmpp,(void*)&outp[first],NBPOINTS*sizeof(q7));

	printf("conv_partial_opt_q7 finish \n");

	printf("conv_partial_opt_q7 checking \n\n");

#if defined(NOT_EMBEDDED) 
    snprintf(referenceFile1, sizeof(referenceFile1), "%s%s%s", Patterns_PATH, MISCQ7, id[num+53-1]);
#else
	referenceFile1 = id[num+53-1];
	referenceFile1Len = size[num+53-1];
    load_data_q7(referenceFile1, referenceFile1Len, referenceData_q7);
    referenceFile1Len = referenceFile1Len/sizeof(q7);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_q7(referenceFile1, tmp, 0, SNR_THRESHOLD);
#else
	snr_check_special_q7(referenceData_q7, tmp, referenceFile1Len, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	near_check_q7(referenceFile1, tmp, 0, ABS_ERROR_FAST_Q7);
#else
	near_check_special_q7(referenceData_q7, tmp, referenceFile1Len, ABS_ERROR_FAST_Q7);
#endif

    ASSERT_TRUE(status==MIPS_MATH_SUCCESS);

    memset(q7output1, 0, sizeof(q7)*MAX_SIZE);
#if !defined(NOT_EMBEDDED)
    memset(referenceData_q7, 0, sizeof(q7)*MAX_SIZE);
#endif
    memset(tmp, 0, sizeof(q7)*MAX_SIZE);
	printf("\n== conv_partial_opt_q7 check done  == \n\n");
    };
    return 0;
}

	

