#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/filtering_functions.h"

#define SNR_THRESHOLD 120
/* 

Reference patterns are generated with
a double precision computation.

*/
#define REL_ERROR (1.0e-6)
#define ABS_ERROR (1.0e-5)

/*

For tests of the error value of the Levinson Durbin algorithm

*/
#define REL_LD_ERROR (1.0e-6)
#define ABS_LD_ERROR (1.0e-6)


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

    float *inpA;
    float *inpB;
    float *outp;
    int nba,nbb,errOffset,first;

	// declare input value
	int paramCountInputA1 = 0;
	int paramCountInputB1 = 0;
    int paramCountInputA = 0;
	int paramCountInputB = 0;
	int paramCountInputC = 0;
	int paramCountInputErrors = 0;
    int paramCountInputA2 = 0;
	int paramCountInputB2 = 0;
    int paramCountReference1 = 0;
	float f32inputA1[MAX_SIZE] = {0};
	float f32inputB1[MAX_SIZE] = {0};
    float f32inputA[MAX_SIZE] = {0};
	float f32inputB[MAX_SIZE] = {0};
    float f32inputC[MAX_SIZE] = {0};
    float f32inputErrors[MAX_SIZE] = {0};
	float f32inputA2[MAX_SIZE] = {0};
    float f32inputB2[MAX_SIZE] = {0};
    float reference1[MAX_SIZE] = {0};

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
	char inputFileA[255] = {0};
#else
	void *inputFileA;
	int inputFileALen = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFileB[255] = {0};
#else
	void *inputFileB;
	int inputFileBLen = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFileC[255] = {0};
#else
	void *inputFileC;
	int inputFileCLen = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFileErrors[255] = {0};
#else
	void *inputFileErrors;
	int inputFileErrorsLen = 0;
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
	snprintf(inputFileA1, sizeof(inputFileA1), "%s%s%s", Patterns_PATH, MISCF32, "InputsA1_f32.txt");
#else
	inputFileA1 = MISCF32_InputsA1_f32;
	inputFileA1Len = sizeof(MISCF32_InputsA1_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileB1, sizeof(inputFileB1), "%s%s%s", Patterns_PATH, MISCF32, "InputsB1_f32.txt");
#else
	inputFileB1 = MISCF32_InputsB1_f32;
	inputFileB1Len = sizeof(MISCF32_InputsB1_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileA, sizeof(inputFileA), "%s%s%s", Patterns_PATH, MISCF32, "InputPhi81_f32.txt");
#else
	inputFileA = MISCF32_InputPhi81_f32;
	inputFileALen = sizeof(MISCF32_InputPhi81_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileB, sizeof(inputFileB), "%s%s%s", Patterns_PATH, MISCF32, "InputPhi82_f32.txt");
#else
	inputFileB = MISCF32_InputPhi82_f32;
	inputFileBLen = sizeof(MISCF32_InputPhi82_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileC, sizeof(inputFileC), "%s%s%s", Patterns_PATH, MISCF32, "InputPhi83_f32.txt");
#else
	inputFileC = MISCF32_InputPhi83_f32;
	inputFileCLen = sizeof(MISCF32_InputPhi83_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileErrors, sizeof(inputFileErrors), "%s%s%s", Patterns_PATH, MISCF32, "LDErrors81_f32.txt");
#else
	inputFileErrors = MISCF32_LDErrors81_f32;
	inputFileErrorsLen = sizeof(MISCF32_LDErrors81_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileA2, sizeof(inputFileA2), "%s%s%s", Patterns_PATH, MISCF32, "InputsA2_f32.txt");
#else
	inputFileA2 = MISCF32_InputsA2_f32;
	inputFileA2Len = sizeof(MISCF32_InputsA2_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileB2, sizeof(inputFileB2), "%s%s%s", Patterns_PATH, MISCF32, "InputsB2_f32.txt");
#else
	inputFileB2 = MISCF32_InputsB2_f32;
	inputFileB2Len = sizeof(MISCF32_InputsB2_f32);
#endif




	// load input data
#if defined(NOT_EMBEDDED)
	load_data_f32(inputFileA1, &paramCountInputA1, f32inputA1);
#else
	paramCountInputA1 = inputFileA1Len;
	load_data_f32(inputFileA1, paramCountInputA1, f32inputA1);
	paramCountInputA1 = paramCountInputA1/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFileB1, &paramCountInputB1, f32inputB1);
#else
	paramCountInputB1 = inputFileB1Len;
	load_data_f32(inputFileB1, paramCountInputB1, f32inputB1);
	paramCountInputB1 = paramCountInputB1/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFileA, &paramCountInputA, f32inputA);
#else
	paramCountInputA = inputFileALen;
	load_data_f32(inputFileA, paramCountInputA, f32inputA);
	paramCountInputA = paramCountInputA/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFileB, &paramCountInputB, f32inputB);
#else
	paramCountInputB = inputFileBLen;
	load_data_f32(inputFileB, paramCountInputB, f32inputB);
	paramCountInputB = paramCountInputB/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFileC, &paramCountInputC, f32inputC);
#else
	paramCountInputC = inputFileCLen;
	load_data_f32(inputFileC, paramCountInputC, f32inputC);
	paramCountInputC = paramCountInputC/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFileErrors, &paramCountInputErrors, f32inputErrors);
#else
	paramCountInputErrors = inputFileErrorsLen;
	load_data_f32(inputFileErrors, paramCountInputErrors, f32inputErrors);
	paramCountInputErrors = paramCountInputErrors/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFileA2, &paramCountInputA2, f32inputA2);
#else
	paramCountInputA2 = inputFileA2Len;
	load_data_f32(inputFileA2, paramCountInputA2, f32inputA2);
	paramCountInputA2 = paramCountInputA2/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFileB2, &paramCountInputB2, f32inputB2);
#else
	paramCountInputB2 = inputFileB2Len;
	load_data_f32(inputFileB2, paramCountInputB2, f32inputB2);
	paramCountInputB2 = paramCountInputB2/sizeof(f32);
#endif

    int num = 0;
    float f32output1[MAX_SIZE] = {0};
#if defined(NOT_EMBEDDED)
    char *id[] = {"Reference1_f32.txt", "Reference2_f32.txt", "Reference3_f32.txt", "Reference4_f32.txt", "Reference5_f32.txt", "Reference6_f32.txt", "Reference7_f32.txt", "Reference8_f32.txt", "Reference9_f32.txt", "Reference10_f32.txt", "Reference11_f32.txt", "Reference12_f32.txt", "Reference13_f32.txt", "Reference14_f32.txt", "Reference15_f32.txt", "Reference16_f32.txt", "Reference17_f32.txt", "Reference18_f32.txt", "Reference19_f32.txt", "Reference20_f32.txt", "Reference21_f32.txt", "Reference22_f32.txt", "Reference23_f32.txt", "Reference24_f32.txt", "Reference25_f32.txt", "Reference26_f32.txt", "Reference27_f32.txt", "Reference28_f32.txt", "Reference29_f32.txt", "Reference30_f32.txt", "Reference31_f32.txt", "Reference32_f32.txt", "Reference33_f32.txt", "Reference34_f32.txt", "Reference35_f32.txt", "Reference36_f32.txt", "Reference37_f32.txt", "Reference38_f32.txt", "Reference39_f32.txt", "Reference40_f32.txt", "Reference41_f32.txt", "Reference42_f32.txt", "Reference43_f32.txt", "Reference44_f32.txt", "Reference45_f32.txt", "Reference46_f32.txt", "Reference47_f32.txt", "Reference48_f32.txt", "Reference49_f32.txt", "Reference50_f32.txt", "Reference51_f32.txt", "Reference52_f32.txt", "Reference53_f32.txt", "Reference54_f32.txt", "Reference55_f32.txt", "Reference56_f32.txt", "Reference57_f32.txt", "Reference58_f32.txt", "Reference59_f32.txt", "Reference60_f32.txt", "Reference61_f32.txt", "Reference62_f32.txt", "Reference63_f32.txt", "Reference64_f32.txt", "Reference65_f32.txt", "Reference66_f32.txt", "Reference67_f32.txt", "Reference68_f32.txt", "Reference69_f32.txt", "Reference70_f32.txt", "Reference71_f32.txt", "Reference72_f32.txt", "Reference73_f32.txt", "Reference74_f32.txt", "Reference75_f32.txt", "Reference76_f32.txt", "Reference77_f32.txt", "Reference78_f32.txt", "Reference79_f32.txt", "Reference80_f32.txt", "Reference81_f32.txt", "Reference82_f32.txt", "Reference83_f32.txt", "Reference84_f32.txt", "Reference85_f32.txt", "Reference86_f32.txt"};
#else 
    u64 id[100] = {MISCF32_Reference1_f32, MISCF32_Reference2_f32, MISCF32_Reference3_f32, MISCF32_Reference4_f32, MISCF32_Reference5_f32, MISCF32_Reference6_f32, MISCF32_Reference7_f32, MISCF32_Reference8_f32, MISCF32_Reference9_f32, MISCF32_Reference10_f32, MISCF32_Reference11_f32, MISCF32_Reference12_f32, MISCF32_Reference13_f32, MISCF32_Reference14_f32, MISCF32_Reference15_f32, MISCF32_Reference16_f32, MISCF32_Reference17_f32, MISCF32_Reference18_f32, MISCF32_Reference19_f32, MISCF32_Reference20_f32, MISCF32_Reference21_f32, MISCF32_Reference22_f32, MISCF32_Reference23_f32, MISCF32_Reference24_f32, MISCF32_Reference25_f32, MISCF32_Reference26_f32, MISCF32_Reference27_f32, MISCF32_Reference28_f32, MISCF32_Reference29_f32, MISCF32_Reference30_f32, MISCF32_Reference31_f32, MISCF32_Reference32_f32, MISCF32_Reference33_f32, MISCF32_Reference34_f32, MISCF32_Reference35_f32, MISCF32_Reference36_f32, MISCF32_Reference37_f32, MISCF32_Reference38_f32, MISCF32_Reference39_f32, MISCF32_Reference40_f32, MISCF32_Reference41_f32, MISCF32_Reference42_f32, MISCF32_Reference43_f32, MISCF32_Reference44_f32, MISCF32_Reference45_f32, MISCF32_Reference46_f32, MISCF32_Reference47_f32, MISCF32_Reference48_f32, MISCF32_Reference49_f32, MISCF32_Reference50_f32, MISCF32_Reference51_f32, MISCF32_Reference52_f32, MISCF32_Reference53_f32, MISCF32_Reference54_f32, MISCF32_Reference55_f32, MISCF32_Reference56_f32, MISCF32_Reference57_f32, MISCF32_Reference58_f32, MISCF32_Reference59_f32, MISCF32_Reference60_f32, MISCF32_Reference61_f32, MISCF32_Reference62_f32, MISCF32_Reference63_f32, MISCF32_Reference64_f32, MISCF32_Reference65_f32, MISCF32_Reference66_f32, MISCF32_Reference67_f32, MISCF32_Reference68_f32, MISCF32_Reference69_f32, MISCF32_Reference70_f32, MISCF32_Reference71_f32, MISCF32_Reference72_f32, MISCF32_Reference73_f32, MISCF32_Reference74_f32, MISCF32_Reference75_f32, MISCF32_Reference76_f32, MISCF32_Reference77_f32, MISCF32_Reference78_f32, MISCF32_Reference79_f32, MISCF32_Reference80_f32, MISCF32_Reference81_f32, MISCF32_Reference82_f32, MISCF32_Reference83_f32, MISCF32_Reference84_f32, MISCF32_Reference85_f32, MISCF32_Reference86_f32};
    u32 size[100] = {sizeof(MISCF32_Reference1_f32), sizeof(MISCF32_Reference2_f32), sizeof(MISCF32_Reference3_f32), sizeof(MISCF32_Reference4_f32), sizeof(MISCF32_Reference5_f32), sizeof(MISCF32_Reference6_f32), sizeof(MISCF32_Reference7_f32), sizeof(MISCF32_Reference8_f32), sizeof(MISCF32_Reference9_f32), sizeof(MISCF32_Reference10_f32), sizeof(MISCF32_Reference11_f32), sizeof(MISCF32_Reference12_f32), sizeof(MISCF32_Reference13_f32), sizeof(MISCF32_Reference14_f32), sizeof(MISCF32_Reference15_f32), sizeof(MISCF32_Reference16_f32), sizeof(MISCF32_Reference17_f32), sizeof(MISCF32_Reference18_f32), sizeof(MISCF32_Reference19_f32), sizeof(MISCF32_Reference20_f32), sizeof(MISCF32_Reference21_f32), sizeof(MISCF32_Reference22_f32), sizeof(MISCF32_Reference23_f32), sizeof(MISCF32_Reference24_f32), sizeof(MISCF32_Reference25_f32), sizeof(MISCF32_Reference26_f32), sizeof(MISCF32_Reference27_f32), sizeof(MISCF32_Reference28_f32), sizeof(MISCF32_Reference29_f32), sizeof(MISCF32_Reference30_f32), sizeof(MISCF32_Reference31_f32), sizeof(MISCF32_Reference32_f32), sizeof(MISCF32_Reference33_f32), sizeof(MISCF32_Reference34_f32), sizeof(MISCF32_Reference35_f32), sizeof(MISCF32_Reference36_f32), sizeof(MISCF32_Reference37_f32), sizeof(MISCF32_Reference38_f32), sizeof(MISCF32_Reference39_f32), sizeof(MISCF32_Reference40_f32), sizeof(MISCF32_Reference41_f32), sizeof(MISCF32_Reference42_f32), sizeof(MISCF32_Reference43_f32), sizeof(MISCF32_Reference44_f32), sizeof(MISCF32_Reference45_f32), sizeof(MISCF32_Reference46_f32), sizeof(MISCF32_Reference47_f32), sizeof(MISCF32_Reference48_f32), sizeof(MISCF32_Reference49_f32), sizeof(MISCF32_Reference50_f32), sizeof(MISCF32_Reference51_f32), sizeof(MISCF32_Reference52_f32), sizeof(MISCF32_Reference53_f32), sizeof(MISCF32_Reference54_f32), sizeof(MISCF32_Reference55_f32), sizeof(MISCF32_Reference56_f32), sizeof(MISCF32_Reference57_f32), sizeof(MISCF32_Reference58_f32), sizeof(MISCF32_Reference59_f32), sizeof(MISCF32_Reference60_f32), sizeof(MISCF32_Reference61_f32), sizeof(MISCF32_Reference62_f32), sizeof(MISCF32_Reference63_f32), sizeof(MISCF32_Reference64_f32), sizeof(MISCF32_Reference65_f32), sizeof(MISCF32_Reference66_f32), sizeof(MISCF32_Reference67_f32), sizeof(MISCF32_Reference68_f32), sizeof(MISCF32_Reference69_f32), sizeof(MISCF32_Reference70_f32), sizeof(MISCF32_Reference71_f32), sizeof(MISCF32_Reference72_f32), sizeof(MISCF32_Reference73_f32), sizeof(MISCF32_Reference74_f32), sizeof(MISCF32_Reference75_f32), sizeof(MISCF32_Reference76_f32), sizeof(MISCF32_Reference77_f32), sizeof(MISCF32_Reference78_f32), sizeof(MISCF32_Reference79_f32), sizeof(MISCF32_Reference80_f32), sizeof(MISCF32_Reference81_f32), sizeof(MISCF32_Reference82_f32), sizeof(MISCF32_Reference83_f32), sizeof(MISCF32_Reference84_f32), sizeof(MISCF32_Reference85_f32), sizeof(MISCF32_Reference86_f32)};
#endif
// =======test_correlate_f32==============

    for(num = 1; num <= 40; num++){

    inpA = f32inputA1;
    inpB = f32inputB1;
    outp = f32output1;
    printf("test:%d \n",num);
    switch (num)
    {
    case 1:
        nba = 4;
        nbb = 1;
        break;
    case 2:
        nba = 4;
        nbb = 2;
        break;
    case 3:
        nba = 4;
        nbb = 3;
        break;
    case 4:
        nba = 4;
        nbb = 8;
        break;
    case 5:
        nba = 4;
        nbb = 11;
        break;
    case 6:
        nba = 5;
        nbb = 1;
        break;
    case 7:
        nba = 5;
        nbb = 2;
        break;
    case 8:
        nba = 5;
        nbb = 3;
        break;
    case 9:
        nba = 5;
        nbb = 8;
        break;
    case 10:
        nba = 5;
        nbb = 11;
        break;
     case 11:
        nba = 6;
        nbb = 1;
        break;
    case 12:
        nba = 6;
        nbb = 2;
        break;
    case 13:
        nba = 6;
        nbb = 3;
        break;
    case 14:
        nba = 6;
        nbb = 8;
        break;
    case 15:
        nba = 6;
        nbb = 11;
        break;
    case 16:
        nba = 9;
        nbb = 1;
        break;
    case 17:
        nba = 9;
        nbb = 2;
        break;
    case 18:
        nba = 9;
        nbb = 3;
        break;
    case 19:
        nba = 9;
        nbb = 8;
        break;
    case 20:
        nba = 9;
        nbb = 11;
        break;
    case 21:
        nba = 10;
        nbb = 1;
        break;
    case 22:
        nba = 10;
        nbb = 2;
        break;
    case 23:
        nba = 10;
        nbb = 3;
        break;
    case 24:
        nba = 10;
        nbb = 8;
        break;
    case 25:
        nba = 10;
        nbb = 11;
        break;
    case 26:
        nba = 11;
        nbb = 1;
        break;
    case 27:
        nba = 11;
        nbb = 2;
        break;
    case 28:
        nba = 11;
        nbb = 3;
        break;
    case 29:
        nba = 11;
        nbb = 8;
        break;
    case 30:
        nba = 11;
        nbb = 11;
        break;
     case 31:
        nba = 12;
        nbb = 1;
        break;
    case 32:
        nba = 12;
        nbb = 2;
        break;
    case 33:
        nba = 12;
        nbb = 3;
        break;
    case 34:
        nba = 12;
        nbb = 8;
        break;
    case 35:
        nba = 12;
        nbb = 11;
        break;
    case 36:
        nba = 13;
        nbb = 1;
        break;
    case 37:
        nba = 13;
        nbb = 2;
        break;
    case 38:
        nba = 13;
        nbb = 3;
        break;
    case 39:
        nba = 13;
        nbb = 8;
        break;
    case 40:
        nba = 13;
        nbb = 11;
        break;
    default:
        break;
    }
    printf("== correlate_f32  test ==  \n");

    mips_correlate_f32(inpA, nba,
      inpB, nbb,
      outp);
    
	printf("correlate_f32 finish \n");

	printf("correlate_f32 checking \n\n");

#if defined(NOT_EMBEDDED) 
    snprintf(referenceFile1, sizeof(referenceFile1), "%s%s%s", Patterns_PATH, MISCF32, id[num-1]);
#else
	referenceFile1 = id[num-1];
	referenceFile1Len = size[num-1];
    load_data_f32(referenceFile1, referenceFile1Len, referenceData_f32);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile1, f32output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, referenceFile1Len, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile1, f32output1, 0, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output1, referenceFile1Len, ABS_ERROR, REL_ERROR);
#endif

    memset(f32output1, 0, sizeof(float)*MAX_SIZE);
#if !defined(NOT_EMBEDDED)
    memset(referenceData_f32, 0, sizeof(float)*MAX_SIZE);
#endif
	printf("\n== correlate_f32 check done  == \n\n");
    };

// =======test_conv_f32 ==============

    for(num = 1; num <= 40; num++){

    inpA = f32inputA1;
    inpB = f32inputB1;
    outp = f32output1;
    printf("test:%d \n",(num+40));
    switch (num)
    {
    case 1:
        nba = 4;
        nbb = 1;
        break;
    case 2:
        nba = 4;
        nbb = 2;
        break;
    case 3:
        nba = 4;
        nbb = 3;
        break;
    case 4:
        nba = 4;
        nbb = 8;
        break;
    case 5:
        nba = 4;
        nbb = 11;
        break;
    case 6:
        nba = 5;
        nbb = 1;
        break;
    case 7:
        nba = 5;
        nbb = 2;
        break;
    case 8:
        nba = 5;
        nbb = 3;
        break;
    case 9:
        nba = 5;
        nbb = 8;
        break;
    case 10:
        nba = 5;
        nbb = 11;
        break;
     case 11:
        nba = 6;
        nbb = 1;
        break;
    case 12:
        nba = 6;
        nbb = 2;
        break;
    case 13:
        nba = 6;
        nbb = 3;
        break;
    case 14:
        nba = 6;
        nbb = 8;
        break;
    case 15:
        nba = 6;
        nbb = 11;
        break;
    case 16:
        nba = 9;
        nbb = 1;
        break;
    case 17:
        nba = 9;
        nbb = 2;
        break;
    case 18:
        nba = 9;
        nbb = 3;
        break;
    case 19:
        nba = 9;
        nbb = 8;
        break;
    case 20:
        nba = 9;
        nbb = 11;
        break;
    case 21:
        nba = 10;
        nbb = 1;
        break;
    case 22:
        nba = 10;
        nbb = 2;
        break;
    case 23:
        nba = 10;
        nbb = 3;
        break;
    case 24:
        nba = 10;
        nbb = 8;
        break;
    case 25:
        nba = 10;
        nbb = 11;
        break;
    case 26:
        nba = 11;
        nbb = 1;
        break;
    case 27:
        nba = 11;
        nbb = 2;
        break;
    case 28:
        nba = 11;
        nbb = 3;
        break;
    case 29:
        nba = 11;
        nbb = 8;
        break;
    case 30:
        nba = 11;
        nbb = 11;
        break;
     case 31:
        nba = 12;
        nbb = 1;
        break;
    case 32:
        nba = 12;
        nbb = 2;
        break;
    case 33:
        nba = 12;
        nbb = 3;
        break;
    case 34:
        nba = 12;
        nbb = 8;
        break;
    case 35:
        nba = 12;
        nbb = 11;
        break;
    case 36:
        nba = 13;
        nbb = 1;
        break;
    case 37:
        nba = 13;
        nbb = 2;
        break;
    case 38:
        nba = 13;
        nbb = 3;
        break;
    case 39:
        nba = 13;
        nbb = 8;
        break;
    case 40:
        nba = 13;
        nbb = 11;
        break;
    default:
        break;
    }
    printf("== conv_f32  test ==  \n");

    mips_conv_f32(inpA, nba,
      inpB, nbb,
      outp);
    
	printf("conv_f32 finish \n");

	printf("conv_f32 checking \n\n");

#if defined(NOT_EMBEDDED) 
    snprintf(referenceFile1, sizeof(referenceFile1), "%s%s%s", Patterns_PATH, MISCF32, id[num+40-1]);
#else
	referenceFile1 = id[num+40-1];
	referenceFile1Len = size[num+40-1];
    load_data_f32(referenceFile1, referenceFile1Len, referenceData_f32);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile1, f32output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, referenceFile1Len, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile1, f32output1, 0, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output1, referenceFile1Len, ABS_ERROR, REL_ERROR);
#endif

    memset(f32output1, 0, sizeof(float)*MAX_SIZE);
#if !defined(NOT_EMBEDDED)
    memset(referenceData_f32, 0, sizeof(float)*MAX_SIZE);
#endif
	printf("\n== conv_f32 check done  == \n\n");
    };
    
// =======test_levinson_durbin_f32==============

 for(num = 1; num <= 3; num++){
    float *errs;
    errs = f32inputErrors;
    float err;
    float refError = errs[errOffset];
    outp = f32output1;
    printf("test:%d \n",(num+80));
    switch (num)
    {
    case 1:
        inpA = f32inputA;
        nba = 3;
        errOffset = 0;
        break;
    case 2:
        inpA = f32inputB;
        nba = 8;
        errOffset = 1;
        break;
    case 3:
        inpA = f32inputC;
        nba = 11;
        errOffset = 2;
        break;

    default:
        break;
    }
    printf("== levinson_durbin_f32  test ==  \n");

    mips_levinson_durbin_f32(inpA,outp,&err,nba);
    
	printf("levinson_durbin_f32 finish \n");

	printf("levinson_durbin_f32 checking \n\n");

#if defined(NOT_EMBEDDED) 
    snprintf(referenceFile1, sizeof(referenceFile1), "%s%s%s", Patterns_PATH, MISCF32, id[num+80-1]);
#else
	referenceFile1 = id[num+80-1];
	referenceFile1Len = size[num+80-1];
    load_data_f32(referenceFile1, referenceFile1Len, referenceData_f32);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile1, f32output1, 0, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output1, referenceFile1Len, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile1, f32output1, 0, ABS_LD_ERROR, REL_LD_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output1, referenceFile1Len, ABS_LD_ERROR, REL_LD_ERROR);
#endif


    if (abs(err - refError) > (ABS_LD_ERROR + REL_LD_ERROR * abs(refError)))
		{
			char details[200];
			sprintf(details, "close error %g > %g: (val = %g, ref = %g)", abs(err - refError), ABS_LD_ERROR + REL_LD_ERROR * abs(refError), err, refError);
			printf("invalid value, details : %s \n", details);
		}
        else{
            printf("closeError count = 0, CLOSE Test PASSED!  \n");
        };

    memset(f32output1, 0, sizeof(float)*MAX_SIZE);
#if !defined(NOT_EMBEDDED)
    memset(referenceData_f32, 0, sizeof(float)*MAX_SIZE);
#endif

	printf("\n== levinson_durbin_f32 check done  == \n\n");
    };

// =======test_conv_partial_f32==============
    // This value must be coherent with the Python script
    // generating the test patterns
#define NBPOINTS 4

    float tmp[MAX_SIZE] = {0};
 for(num = 1; num <= 3; num++){
    inpA = f32inputA2;
    inpB = f32inputB2;
    outp = f32output1;
    float *tmpp;
    tmpp = tmp;
    printf("test:%d \n",(num+83));
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
    printf("== conv_partial_f32  test ==  \n");

    mips_status status=mips_conv_partial_f32(inpA, nba,
          inpB, nbb,
          outp,
          first,
          NBPOINTS);

    memcpy((void*)tmpp,(void*)&outp[first],NBPOINTS*sizeof(float));

	printf("conv_partial_f32 finish \n");

	printf("conv_partial_f32 checking \n\n");

#if defined(NOT_EMBEDDED) 
    snprintf(referenceFile1, sizeof(referenceFile1), "%s%s%s", Patterns_PATH, MISCF32, id[num+83-1]);
#else
	referenceFile1 = id[num+83-1];
	referenceFile1Len = size[num+83-1];
    load_data_f32(referenceFile1, referenceFile1Len, referenceData_f32);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile1, tmp, 0, SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, tmp, referenceFile1Len, SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile1, tmp, 0, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, tmp, referenceFile1Len, ABS_ERROR, REL_ERROR);
#endif

    ASSERT_TRUE(status==MIPS_MATH_SUCCESS);

    memset(f32output1, 0, sizeof(float)*MAX_SIZE);
#if !defined(NOT_EMBEDDED)
    memset(referenceData_f32, 0, sizeof(float)*MAX_SIZE);
#endif
    memset(tmp, 0, sizeof(float)*MAX_SIZE);
	printf("\n== conv_partial_f32 check done  == \n\n");
    };

    return 0;
}

	

