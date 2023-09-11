#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

#include "Embedded/BasicMathsF32Data.c"
// #include "BasicFramework.h"

// #if !defined(NOT_EMBEDDED)
// #include "Embedded/data.c"
// #endif


typedef int8_t q7;
#define MAX_SIZE 512

#if 0
// q7
int load_data_q7(char fileName[], int *paramCount, q7 *loadedData)
{
	printf("data is %s, \n", fileName);

	char *tmp = NULL;
	tmp = strtok(fileName, (char [])"/");
	// loadedData[100];
	// printf("data is %d, %x \n", i, q7input1[i]);
	printf("data is %s, \n", tmp);
	while (tmp = strtok(NULL, "/"))
	{ // 使用第一个参数为NULL来提取子串
		printf("data %s\n", tmp);
	}
	*paramCount = 10;

	return 0;
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

	// declare input value
	int paramCountInput1 = 0;
	q7 q7input1[MAX_SIZE] = {0};

#if defined(NOT_EMBEDDED)
#if defined(NOT_EMBEDDED)
	load_data_q7("../Testing/Patterns/DSP/BasicMaths/BasicMathsQ7/Input1_q7.txt", &paramCountInput1, q7input1);
#else
	paramCountInput1 = "../Testing/Patterns/DSP/BasicMaths/BasicMathsQ7/Input1_q7.txt"Len;
	load_data_q7("../Testing/Patterns/DSP/BasicMaths/BasicMathsQ7/Input1_q7.txt", paramCountInput1, q7input1);
	paramCountInput1Len = paramCountInput1/sizeof(q7);
#endif

#else
	paramCountInput1 = "../Testing/Patterns/DSP/BasicMaths/BasicMathsQ7/Input1_q7.txt"Len;
	load_data_q7("../Testing/Patterns/DSP/BasicMaths/BasicMathsQ7/Input1_q7.txt", paramCountInput1, q7input1);
	paramCountInput1 = paramCountInput1/sizeof(q7);
#endif

	q7 q7output1[MAX_SIZE] = {0};

	// printf("data is %d, %x \n", i, q7input1[i]);

	for (size_t i = 0; i < paramCountInput1; i++)
	{
		// printf("data is %d, %x \n",i, q7input1[i]);
	}

	return 0;
}
#endif

typedef int8_t q7;
typedef int16_t q15;
typedef int32_t q31;
typedef int64_t q63;

typedef float f32;
typedef double f64;


#if 1

void split(char str[],char delims[])
{
    char *result = NULL; 
    result = strtok( str, delims );  
    while( result != NULL ) {  
    printf( "result is \"%s\"\n", result );  
    result = strtok( NULL, delims );  
    }  
}
void load_data_f32(void *valuePointer, float *aaa)
{
    // printf( "length result is %d \n", sizeof(*(float **)valuePointer) );  
    printf( "length result is %d \n", strlen(valuePointer) );  
    printf( "length22222 result is %d \n", sizeof(BasicMathsF32_Input12_f32) );  
	memcpy(aaa, valuePointer, sizeof(BasicMathsF32_Input12_f32));

    printf( "done \n" );  
}
void load_data_f64(void *valuePointer, double *aaa)
{
    // printf( "length result is %d \n", sizeof(*(double **)valuePointer) );  
    printf( "length result is %d \n", strlen(valuePointer) );  

    printf( "length22222 result is %d \n", sizeof(BasicMathsF32_Input12_f32) );  
	memcpy(aaa, valuePointer, sizeof(BasicMathsF32_Input12_f32));
    printf( "length result is %d \n", strlen(aaa) );  

    printf( "done \n" );  
}
int main()  
{  
    // char str[] = "../Testing/Patterns/DSP/BasicMaths/BasicMathsQ7/Input1_q7.txt";  
    // char delims[] = "/";  
	// split(str,delims);
    // printf( "length is %d \n", sizeof(*(void *)BasicMathsF32_Input12_f32) );  
    printf( "length is %d \n", sizeof(BasicMathsF32_Input12_f32) );  
    // printf( "length is %d \n",  );
	float xx[MAX_SIZE] = {0};
	void *abcde;
	abcde = BasicMathsF32_Input12_f32;
	// abcde = BasicMathsF64_Input1_f64;
    printf( "9999999999999 result is %d \n", sizeof(*(float **)abcde) );  

	load_data_f32(abcde,xx);
    printf( "sizeof is %d \n", sizeof(BasicMathsF32_Input12_f32) );  

	f32 test[267]={0};
	memcpy((void *)test, (void *)BasicMathsF32_Input12_f32, sizeof(BasicMathsF32_Input12_f32));
    printf( "length is %x \n", &test );  
    printf( "length is %d \n", sizeof(BasicMathsF32_Reference11_f32) );  
	printf(" float is %d \n", sizeof(xx));
	for (size_t i = 0; i < 200; i++)
	{
		printf(" float is %f", xx[i]);
	}
	

	return 0;
}  
#endif
