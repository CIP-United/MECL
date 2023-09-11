#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/matrix_functions.h"

#define SNR_THRESHOLD 250

/* 

Reference patterns are generated with
a double precision computation.

*/
#define REL_ERROR (1.0e-12)
#define ABS_ERROR (1.0e-12)

/*

Comparisons for householder

*/
#define SNR_HOUSEHOLDER_THRESHOLD 270
#define REL_HOUSEHOLDER_ERROR (1.0e-13)
#define ABS_HOUSEHOLDER_ERROR (1.0e-13)

/*

Comparison for QR decomposition

*/
#define SNR_QR_THRESHOLD 270
#define REL_QR_ERROR (1.0e-13)
#define ABS_QR_ERROR (1.0e-13)

/*

Comparison for Cholesky

*/
#define SNR_THRESHOLD_CHOL 269
#define REL_ERROR_CHOL (1.0e-9)
#define ABS_ERROR_CHOL (1.0e-9)

/* LDLT comparison */

#define REL_ERROR_LDLT (1e-5)
#define ABS_ERROR_LDLT (1e-5)

/* Upper bound of maximum matrix dimension used by Python */
#define MAXMATRIXDIM 40



#define SWAP_ROWS(A,i,j)     \
  for(int w=0;w < n; w++)    \
  {                          \
     f64 tmp;          \
     tmp = A[i*n + w];       \
     A[i*n + w] = A[j*n + w];\
     A[j*n + w] = tmp;       \
  }



static void checkInnerTailOverflow(f64 *b)
{
    ASSERT_TRUE(b[0] == 0);
    ASSERT_TRUE(b[1] == 0);
}


static void refInnerTail(f64 *b)
{
    b[0] = 1.0;
    b[1] = -2.0;
}


static void checkInnerTail(f64 *b)
{
    ASSERT_TRUE(b[0] == 1.0);
    ASSERT_TRUE(b[1] == -2.0);
}



static void trans_f64(const f64 *src, f64 *dst, int n)
    {
        for(int r=0; r<n ; r++)
        {
          for(int c=0; c<n ; c++)
          {
              dst[c*n+r] = src[r*n+c];
          }
        }
    }

    
static void mult_f64_f64(const f64 *srcA, const f64 *srcB, f64 *dst,int n)
    {
        for(int r=0; r<n ; r++)
        {
          for(int c=0; c<n ; c++)
          {
             f64 sum=0.0;
             for(int k=0; k < n ; k++)
             {
                sum += srcA[r*n+k] * srcB[k*n+c];
             }
             dst[r*n+c] = sum;
          }
        }
    }




double f64outputa[MAX_SIZE] = {0};
double f64outputb[MAX_SIZE] = {0};
double f64outputll[MAX_SIZE] = {0};
double f64outputd[MAX_SIZE] = {0};
int16_t f64outputp[MAX_SIZE] = {0};

           
f64 *outa = f64outputa;
f64 *outb = f64outputb;   

mips_matrix_instance_f64 in1;
mips_matrix_instance_f64 outd;
mips_matrix_instance_f64 outll;

f64 *outllp = f64outputll;
f64 *outdp = f64outputd;

const int16_t *outpp = f64outputp;


static void compute_ldlt_error(const int n,const int16_t *outpp)
    {
           double f64tmpapat[MAXMATRIXDIM*MAXMATRIXDIM] = {0};
           double f64tmpbpat[MAXMATRIXDIM*MAXMATRIXDIM] = {0};
           double f64tmpcpat[MAXMATRIXDIM*MAXMATRIXDIM] = {0};

           f64 *tmpa  = f64tmpapat ;
           f64 *tmpb  = f64tmpbpat ;
           f64 *tmpc  = f64tmpcpat ;

           
           

          /* Compute P A P^t */

          // Create identiy matrix
          for(int r=0; r < n; r++)
          {
            for(int c=0; c < n; c++)
            {
               if (r == c)
               {
                 tmpa[r*n+c] = 1.0;
               }
               else
               {
                 tmpa[r*n+c] = 0.0;
               }
            }
          }

          // Create permutation matrix

          for(int r=0;r < n; r++)
          {
            SWAP_ROWS(tmpa,r,outpp[r]);
          }

          

          trans_f64((const f64*)tmpa,tmpb,n);
          mult_f64_f64((const f64*)in1.pData,(const f64*)tmpb,tmpc,n);
          mult_f64_f64((const f64*)tmpa,(const f64*)tmpc,outa,n);


          /* Compute L D L^t */
          trans_f64((const f64*)outll.pData,tmpc,n);
          mult_f64_f64((const f64*)outd.pData,(const f64*)tmpc,tmpa,n);
          mult_f64_f64((const f64*)outll.pData,(const f64*)tmpa,outb,n);

          
    }

#define LOADDATA2()                          \
      const double *inp1, *inp2;    \
      double  *outp, *ap, *bp;    \
                                             \
      inp1 = f64input1;                 \
      inp2 = f64input2;                 \
      outp = f64output;                 \
      ap = f64a1;                 \
      bp = f64b1;                 \
                                             \
      int16_t *dimsp;          \
      dimsp = f64dims;           \
      int nbMatrixes = paramCountdims / 3;\
      int rows,internal,columns;  

#define PREPAREDATA2()                                                   \
      mips_matrix_instance_f64 in1;\
      mips_matrix_instance_f64 in2;\
      mips_matrix_instance_f64 out;\
      in1.numRows=rows;                                                  \
      in1.numCols=columns;                                               \
      memcpy((void*)ap,(const void*)inp1,sizeof(f64)*rows*columns);\
      in1.pData = ap;                                                    \
                                                                         \
      in2.numRows=rows;                                                  \
      in2.numCols=columns;                                               \
      memcpy((void*)bp,(const void*)inp2,sizeof(f64)*rows*columns);\
      in2.pData = bp;                                                    \
                                                                         \
      out.numRows=rows;                                                  \
      out.numCols=columns;                                               \
      out.pData = outp;

#define PREPAREDATALT()                                                  \
      mips_matrix_instance_f64 in1;\
      mips_matrix_instance_f64 in2;\
      mips_matrix_instance_f64 out;\
      in1.numRows=rows;                                                  \
      in1.numCols=rows;                                                  \
      memcpy((void*)ap,(const void*)inp1,sizeof(f64)*rows*rows);   \
      in1.pData = ap;                                                    \
                                                                         \
      in2.numRows=rows;                                                  \
      in2.numCols=columns;                                               \
      memcpy((void*)bp,(const void*)inp2,sizeof(f64)*rows*columns);\
      in2.pData = bp;                                                    \
                                                                         \
      out.numRows=rows;                                                  \
      out.numCols=columns;                                               \
      out.pData = outp;
#define PREPAREDATA1(TRANSPOSED)                                         \
      mips_matrix_instance_f64 in1;\
      mips_matrix_instance_f64 out;\
      in1.numRows=rows;                                                  \
      in1.numCols=columns;                                               \
      memcpy((void*)ap,(const void*)inp1,sizeof(f64)*rows*columns);\
      in1.pData = ap;                                                    \
                                                                         \
      if (TRANSPOSED)                                                    \
      {                                                                  \
         out.numRows=columns;                                            \
         out.numCols=rows;                                               \
      }                                                                  \
      else                                                               \
      {                                                                  \
      out.numRows=rows;                                                  \
      out.numCols=columns;                                               \
      }                                                                  \
      out.pData = outp;

#define PREPAREDATA1C(TRANSPOSED)                                         \
      mips_matrix_instance_f64 in1;\
      mips_matrix_instance_f64 out;\
      in1.numRows=rows;                                                  \
      in1.numCols=columns;                                               \
      memcpy((void*)ap,(const void*)inp1,2*sizeof(f64)*rows*columns);\
      in1.pData = ap;                                                    \
                                                                         \
      if (TRANSPOSED)                                                    \
      {                                                                  \
         out.numRows=columns;                                            \
         out.numCols=rows;                                               \
      }                                                                  \
      else                                                               \
      {                                                                  \
      out.numRows=rows;                                                  \
      out.numCols=columns;                                               \
      }                                                                  \
      out.pData = outp;
                            
#define PREPAREDATALL1()                                                 \
      in1.numRows=rows;                                                  \
      in1.numCols=columns;                                               \
      memcpy((void*)ap,(const void*)inp1,sizeof(f64)*rows*columns);\
      in1.pData = ap;                                                    \
                                                                         \
      outll.numRows=rows;                                                \
      outll.numCols=columns;                                             \
                                                                         \
      outll.pData = outllp;



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
    int paramCountInput3 = 0;
    int paramCountInput4 = 0;
    int paramCountInput5 = 0;
    int paramCountInput6 = 0;
    int paramCountInput7 = 0;
    int paramCountInput8 = 0;
    int paramCountInput9 = 0;

    int paramCountInputa1 = 0;
    int paramCountInputa2 = 0;
    int paramCountInputa3 = 0;
    int paramCountInputb1 = 0;
    int paramCountInputb2 = 0;
    int paramCountInputb3 = 0;


    
    int paramCountdims1 = 0;
    int paramCountdims2 = 0;
    int paramCountdims3 = 0;
    int paramCountdims4 = 0;
    int paramCountdims5 = 0;
    int paramCountdims6 = 0;
    int paramCountdims7 = 0;


	double f64input1[MAX_SIZE] = {0};
    double f64input2[MAX_SIZE] = {0};
    double f64input3[MAX_SIZE] = {0};
    double f64input4[MAX_SIZE] = {0};
    double f64input5[MAX_SIZE] = {0};
    double f64input6[MAX_SIZE] = {0};
    double f64input7[MAX_SIZE] = {0};
    double f64input8[MAX_SIZE] = {0};
    double f64input9[MAX_SIZE] = {0};

    double f64inputa1[MAX_SIZE] = {0};
    double f64inputa2[MAX_SIZE] = {0};
    double f64inputa3[MAX_SIZE] = {0};
    double f64inputb1[MAX_SIZE] = {0};
    double f64inputb2[MAX_SIZE] = {0};
    double f64inputb3[MAX_SIZE] = {0};

    q15 f64dims1[MAX_SIZE] = {0};
    q15 f64dims2[MAX_SIZE] = {0};
    q15 f64dims3[MAX_SIZE] = {0};
    q15 f64dims4[MAX_SIZE] = {0};
    q15 f64dims5[MAX_SIZE] = {0};
    q15 f64dims6[MAX_SIZE] = {0};
    q15 f64dims7[MAX_SIZE] = {0};


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
	char inputFile3[255] = {0};
#else
	void *inputFile3;
	int inputFile3Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFile4[255] = {0};
#else
	void *inputFile4;
	int inputFile4Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFile5[255] = {0};
#else
	void *inputFile5;
	int inputFile5Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFile6[255] = {0};
#else
	void *inputFile6;
	int inputFile6Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFile7[255] = {0};
#else
	void *inputFile7;
	int inputFile7Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFile8[255] = {0};
#else
	void *inputFile8;
	int inputFile8Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFile9[255] = {0};
#else
	void *inputFile9;
	int inputFile9Len = 0;
#endif



#if defined(NOT_EMBEDDED)
	char inputFilea1[255] = {0};
#else
	void *inputFilea1;
	int inputFilea1Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFilea2[255] = {0};
#else
	void *inputFilea2;
	int inputFilea2Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFilea3[255] = {0};
#else
	void *inputFilea3;
	int inputFilea3Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFileb1[255] = {0};
#else
	void *inputFileb1;
	int inputFileb1Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFileb2[255] = {0};
#else
	void *inputFileb2;
	int inputFileb2Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char inputFileb3[255] = {0};
#else
	void *inputFileb3;
	int inputFileb3Len = 0;
#endif


#if defined(NOT_EMBEDDED)
	char dimsFile1[255] = {0};
#else
	void *dimsFile1;
	int dimsFile1Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char dimsFile2[255] = {0};
#else
	void *dimsFile2;
	int dimsFile2Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char dimsFile3[255] = {0};
#else
	void *dimsFile3;
	int dimsFile3Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char dimsFile4[255] = {0};
#else
	void *dimsFile4;
	int dimsFile4Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char dimsFile5[255] = {0};
#else
	void *dimsFile5;
	int dimsFile5Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char dimsFile6[255] = {0};
#else
	void *dimsFile6;
	int dimsFile6Len = 0;
#endif

#if defined(NOT_EMBEDDED)
	char dimsFile7[255] = {0};
#else
	void *dimsFile7;
	int dimsFile7Len = 0;
#endif



#if defined(NOT_EMBEDDED)
	char referenceFile[255] = {0};
#else
	void *referenceFile;
	int referenceFileLen = 0;
#endif

#if defined(NOT_EMBEDDED)
	char referenceFileBeta[255] = {0};
#else
	void *referenceFileBeta;
	int referenceFileBetaLen = 0;
#endif

#if defined(NOT_EMBEDDED)
	char referenceFileQ[255] = {0};
#else
	void *referenceFileQ;
	int referenceFileQLen = 0;
#endif

#if defined(NOT_EMBEDDED)
	char referenceFileR[255] = {0};
#else
	void *referenceFileR;
	int referenceFileRLen = 0;
#endif

#if defined(NOT_EMBEDDED)
	char referenceFileTau[255] = {0};
#else
	void *referenceFileTau;
	int referenceFileTauLen = 0;
#endif



	// set file name by snprintf
	// relative path, function path, filename

    //input
#if defined(NOT_EMBEDDED)
	snprintf(inputFile1, sizeof(inputFile1), "%s%s%s", Patterns_PATH, UnaryF64, "InputA1_f64.txt");
#else
	inputFile1 = UnaryF64_InputA1_f64;
	inputFile1Len = sizeof(UnaryF64_InputA1_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile2, sizeof(inputFile2), "%s%s%s", Patterns_PATH, UnaryF64, "InputB1_f64.txt");
#else
	inputFile2 = UnaryF64_InputB1_f64;
	inputFile2Len = sizeof(UnaryF64_InputB1_f64);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(inputFile3, sizeof(inputFile3), "%s%s%s", Patterns_PATH, UnaryF64, "InputAC1_f64.txt");
#else
	inputFile3 = UnaryF64_InputAC1_f64;
	inputFile3Len = sizeof(UnaryF64_InputAC1_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile4, sizeof(inputFile4), "%s%s%s", Patterns_PATH, UnaryF64, "InputVec1_f64.txt");
#else
	inputFile4 = UnaryF64_InputVec1_f64;
	inputFile4Len = sizeof(UnaryF64_InputVec1_f64);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(inputFile5, sizeof(inputFile5), "%s%s%s", Patterns_PATH, UnaryF64, "InputInvert1_f64.txt");
#else
	inputFile5 = UnaryF64_InputInvert1_f64;
	inputFile5Len = sizeof(UnaryF64_InputInvert1_f64);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(inputFile6, sizeof(inputFile6), "%s%s%s", Patterns_PATH, UnaryF64, "InputCholeskyDPO1_f64.txt");
#else
	inputFile6 = UnaryF64_InputCholeskyDPO1_f64;
	inputFile6Len = sizeof(UnaryF64_InputCholeskyDPO1_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile7, sizeof(inputFile7), "%s%s%s", Patterns_PATH, UnaryF64, "InputCholeskySDPO1_f64.txt");
#else
	inputFile7 = UnaryF64_InputCholeskySDPO1_f64;
	inputFile7Len = sizeof(UnaryF64_InputCholeskySDPO1_f64);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(inputFile8, sizeof(inputFile8), "%s%s%s", Patterns_PATH, UnaryF64, "InputMatrixQR1_f64.txt");
#else
	inputFile8 = UnaryF64_InputMatrixQR1_f64;
	inputFile8Len = sizeof(UnaryF64_InputMatrixQR1_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile9, sizeof(inputFile9), "%s%s%s", Patterns_PATH, UnaryF64, "InputVectorHouseHolder1_f64.txt");
#else
	inputFile9 = UnaryF64_InputVectorHouseHolder1_f64;
	inputFile9Len = sizeof(UnaryF64_InputVectorHouseHolder1_f64);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(inputFilea1, sizeof(inputFilea3), "%s%s%s", Patterns_PATH, UnaryF64, "InputUTDPO1_f64.txt");
#else
	inputFilea1 = UnaryF64_InputUTDPO1_f64;
	inputFilea1Len = sizeof(UnaryF64_InputUTDPO1_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFilea2, sizeof(inputFilea3), "%s%s%s", Patterns_PATH, UnaryF64, "InputLTDPO1_f64.txt");
#else
	inputFilea2 = UnaryF64_InputLTDPO1_f64;
	inputFilea2Len = sizeof(UnaryF64_InputLTDPO1_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFilea3, sizeof(inputFilea3), "%s%s%s", Patterns_PATH, UnaryF64, "InputRNDA1_f64.txt");
#else
	inputFilea3 = UnaryF64_InputRNDA1_f64;
	inputFilea3Len = sizeof(UnaryF64_InputRNDA1_f64);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(inputFileb1, sizeof(inputFileb1), "%s%s%s", Patterns_PATH, UnaryF64, "InputMatrixLTSolve1_f64.txt");
#else
	inputFileb1 = UnaryF64_InputMatrixLTSolve1_f64;
	inputFileb1Len = sizeof(UnaryF64_InputMatrixLTSolve1_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileb2, sizeof(inputFileb2), "%s%s%s", Patterns_PATH, UnaryF64, "InputMatrixUTSolve1_f64.txt");
#else
	inputFileb2 = UnaryF64_InputMatrixUTSolve1_f64;
	inputFileb2Len = sizeof(UnaryF64_InputMatrixUTSolve1_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileb3, sizeof(inputFileb3), "%s%s%s", Patterns_PATH, UnaryF64, "InputVectorLTSolve1_f64.txt");
#else
	inputFileb3 = UnaryF64_InputVectorLTSolve1_f64;
	inputFileb3Len = sizeof(UnaryF64_InputVectorLTSolve1_f64);
#endif

    
	//dim
#if defined(NOT_EMBEDDED)
	snprintf(dimsFile1, sizeof(dimsFile1), "%s%s%s", Patterns_PATH, UnaryF64, "DimsUnary1_s16.txt");
#else
	dimsFile1 = UnaryF64_DimsUnary1_s16;
	dimsFile1Len = sizeof(UnaryF64_DimsUnary1_s16);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(dimsFile2, sizeof(dimsFile2), "%s%s%s", Patterns_PATH, UnaryF64, "DimsInvert1_s16.txt");
#else
	dimsFile2 = UnaryF64_DimsInvert1_s16;
	dimsFile2Len = sizeof(UnaryF64_DimsInvert1_s16);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(dimsFile3, sizeof(dimsFile3), "%s%s%s", Patterns_PATH, UnaryF64, "DimsCholeskyDPO1_s16.txt");
#else
	dimsFile3 = UnaryF64_DimsCholeskyDPO1_s16;
	dimsFile3Len = sizeof(UnaryF64_DimsCholeskyDPO1_s16);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(dimsFile4, sizeof(dimsFile4), "%s%s%s", Patterns_PATH, UnaryF64, "DimsCholeskySDPO1_s16.txt");
#else
	dimsFile4 = UnaryF64_DimsCholeskySDPO1_s16;
	dimsFile4Len = sizeof(UnaryF64_DimsCholeskySDPO1_s16);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(dimsFile5, sizeof(dimsFile5), "%s%s%s", Patterns_PATH, UnaryF64, "DimsLTSolve1_s16.txt");
#else
	dimsFile5 = UnaryF64_DimsLTSolve1_s16;
	dimsFile5Len = sizeof(UnaryF64_DimsLTSolve1_s16);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(dimsFile6, sizeof(dimsFile6), "%s%s%s", Patterns_PATH, UnaryF64, "DimsQR1_s16.txt");
#else
	dimsFile6 = UnaryF64_DimsQR1_s16;
	dimsFile6Len = sizeof(UnaryF64_DimsQR1_s16);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(dimsFile7, sizeof(dimsFile7), "%s%s%s", Patterns_PATH, UnaryF64, "DimsHouseholder1_s16.txt");
#else
	dimsFile7 = UnaryF64_DimsHouseholder1_s16;
	dimsFile7Len = sizeof(UnaryF64_DimsHouseholder1_s16);
#endif


    //ref
#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, UnaryF64, "Ref_UTINV_DPO1_f64.txt");
#else
	referenceFile = UnaryF64_Ref_UTINV_DPO1_f64;
	referenceFileLen = sizeof(UnaryF64_Ref_UTINV_DPO1_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, UnaryF64, "Ref_LTINV_DPO1_f64.txt");
#else
	referenceFile = UnaryF64_Ref_LTINV_DPO1_f64;
	referenceFileLen = sizeof(UnaryF64_Ref_LTINV_DPO1_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, UnaryF64, "Ref_CHOLINV_DPO1_f64.txt");
#else
	referenceFile = UnaryF64_Ref_CHOLINV_DPO1_f64;
	referenceFileLen = sizeof(UnaryF64_Ref_CHOLINV_DPO1_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
#endif




	// load input data
#if defined(NOT_EMBEDDED)
	load_data_f64(inputFile1, &paramCountInput1, f64input1);
#else
	paramCountInput1 = inputFile1Len;
	load_data_f64(inputFile1, paramCountInput1, f64input1);
	paramCountInput1 = paramCountInput1/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(inputFile2, &paramCountInput2, f64input2);
#else
	paramCountInput2 = inputFile2Len;
	load_data_f64(inputFile2, paramCountInput2, f64input2);
	paramCountInput2 = paramCountInput2/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(inputFile3, &paramCountInput3, f64input3);
#else
	paramCountInput3 = inputFile3Len;
	load_data_f64(inputFile3, paramCountInput3, f64input3);
	paramCountInput3 = paramCountInput3/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(inputFile4, &paramCountInput4, f64input4);
#else
	paramCountInput4 = inputFile4Len;
	load_data_f64(inputFile4, paramCountInput4, f64input4);
	paramCountInput4 = paramCountInput4/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(inputFile5, &paramCountInput5, f64input5);
#else
	paramCountInput5 = inputFile5Len;
	load_data_f64(inputFile5, paramCountInput5, f64input5);
	paramCountInput5 = paramCountInput5/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(inputFile6, &paramCountInput6, f64input6);
#else
	paramCountInput6 = inputFile6Len;
	load_data_f64(inputFile6, paramCountInput6, f64input6);
	paramCountInput6 = paramCountInput6/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(inputFile7, &paramCountInput7, f64input7);
#else
	paramCountInput7 = inputFile7Len;
	load_data_f64(inputFile7, paramCountInput7, f64input7);
	paramCountInput7 = paramCountInput7/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(inputFile8, &paramCountInput8, f64input8);
#else
	paramCountInput8 = inputFile8Len;
	load_data_f64(inputFile8, paramCountInput8, f64input8);
	paramCountInput8 = paramCountInput8/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(inputFile9, &paramCountInput9, f64input9);
#else
	paramCountInput9 = inputFile9Len;
	load_data_f64(inputFile9, paramCountInput9, f64input9);
	paramCountInput9 = paramCountInput9/sizeof(f64);
#endif


#if defined(NOT_EMBEDDED)
	load_data_f64(inputFilea1, &paramCountInputa1, f64inputa1);
#else
	paramCountInputa1 = inputFilea1Len;
	load_data_f64(inputFilea1, paramCountInputa1, f64inputa1);
	paramCountInputa1 = paramCountInputa1/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(inputFilea2, &paramCountInputa2, f64inputa2);
#else
	paramCountInputa2 = inputFilea2Len;
	load_data_f64(inputFilea2, paramCountInputa2, f64inputa2);
	paramCountInputa2 = paramCountInputa2/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(inputFilea3, &paramCountInputa3, f64inputa3);
#else
	paramCountInputa3 = inputFilea3Len;
	load_data_f64(inputFilea3, paramCountInputa3, f64inputa3);
	paramCountInputa3 = paramCountInputa3/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(inputFileb1, &paramCountInputb1, f64inputb1);
#else
	paramCountInputb1 = inputFileb1Len;
	load_data_f64(inputFileb1, paramCountInputb1, f64inputb1);
	paramCountInputb1 = paramCountInputb1/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(inputFileb2, &paramCountInputb2, f64inputb2);
#else
	paramCountInputb2 = inputFileb2Len;
	load_data_f64(inputFileb2, paramCountInputb2, f64inputb2);
	paramCountInputb2 = paramCountInputb2/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f64(inputFileb3, &paramCountInputb3, f64inputb3);
#else
	paramCountInputb3 = inputFileb3Len;
	load_data_f64(inputFileb3, paramCountInputb3, f64inputb3);
	paramCountInputb3 = paramCountInputb3/sizeof(f64);
#endif


#if defined(NOT_EMBEDDED)
	load_data_q15(dimsFile1, &paramCountdims1, f64dims1);
#else
	paramCountdims1 = dimsFile1Len;
	load_data_q15(dimsFile1, paramCountdims1, f64dims1);
	paramCountdims1 = paramCountdims1/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(dimsFile2, &paramCountdims2, f64dims2);
#else
	paramCountdims2 = dimsFile2Len;
	load_data_q15(dimsFile2, paramCountdims2, f64dims2);
	paramCountdims2 = paramCountdims2/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(dimsFile3, &paramCountdims3, f64dims3);
#else
	paramCountdims3 = dimsFile3Len;
	load_data_q15(dimsFile3, paramCountdims3, f64dims3);
	paramCountdims3 = paramCountdims3/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(dimsFile4, &paramCountdims4, f64dims4);
#else
	paramCountdims4 = dimsFile4Len;
	load_data_q15(dimsFile4, paramCountdims4, f64dims4);
	paramCountdims4 = paramCountdims4/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(dimsFile5, &paramCountdims5, f64dims5);
#else
	paramCountdims5 = dimsFile5Len;
	load_data_q15(dimsFile5, paramCountdims5, f64dims5);
	paramCountdims5 = paramCountdims5/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(dimsFile6, &paramCountdims6, f64dims6);
#else
	paramCountdims6 = dimsFile6Len;
	load_data_q15(dimsFile6, paramCountdims6, f64dims6);
	paramCountdims6 = paramCountdims6/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(dimsFile7, &paramCountdims7, f64dims7);
#else
	paramCountdims7 = dimsFile7Len;
	load_data_q15(dimsFile7, paramCountdims7, f64dims7);
	paramCountdims7 = paramCountdims7/sizeof(q15);
#endif


	double f64output[MAX_SIZE] = {0};
    double f64outputBeta[MAX_SIZE] = {0};


    double f64outputTau[MAX_SIZE] = {0};
    double f64outputR[MAX_SIZE] = {0};
    double f64outputQ[MAX_SIZE] = {0};
   

    double f64a[MAXMATRIXDIM*MAXMATRIXDIM] = {0};
    double f64b[MAXMATRIXDIM*MAXMATRIXDIM] = {0};
    double f64a2[47] = {0};
    double f64b2[MAXMATRIXDIM] = {0};
    double f64b3[47] = {0};

    

    mips_status status;

    const double *inp1;
    const double *inp2;    
    double  *outBetap;
    double  *outp;    
    double  *ap;
    double  *bp;
                                                           
    int16_t *dimsp;           
                
    int nbMatrixes;
    int rows,internal,columns;
    int i;  

// =====================

	printf("== mips_mat_sub_f64 test ==  \n"); 
    
    inp1 = f64input1;
    inp2 = f64input2;
    outp = f64output;
    dimsp = f64dims1;
    ap = f64a;
    bp = f64b;
    nbMatrixes = paramCountdims1 >> 1;

      for(i=0;i < nbMatrixes ; i ++)
      {
          rows = *dimsp++;
          columns = *dimsp++;

          PREPAREDATA2();

          status=mips_mat_sub_f64(&in1,&in2,&out);
          ASSERT_TRUE(status==MIPS_MATH_SUCCESS);

          outp += (rows * columns);

      }


	printf("mips_mat_sub_f64 finish \n");

	printf("mips_mat_sub_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, UnaryF64, "RefSub1_f64.txt");
#else
	referenceFile = UnaryF64_RefSub1_f64;
	referenceFileLen = sizeof(UnaryF64_RefSub1_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
    referenceFileLen = referenceFileLen/sizeof(f64);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output, 0, (f64)SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output, referenceFileLen, (f64)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f64(referenceFile, f64output, 0, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f64(referenceData_f64, f64output, referenceFileLen, ABS_ERROR, REL_ERROR);
#endif


    memset(f64output, 0, sizeof(double)*MAX_SIZE);

	printf("\n== mips_mat_sub_f64 check done  == \n\n");   

// =====================

	printf("== mips_mat_trans_f64 test ==  \n"); 
    
    inp1 = f64input1;
    outp = f64output;
    dimsp = f64dims1;
    ap = f64a;
    nbMatrixes = paramCountdims1 >> 1;

      for(i=0;i < nbMatrixes ; i ++)
      {
          rows = *dimsp++;
          columns = *dimsp++;

          PREPAREDATA1(true);

          status=mips_mat_trans_f64(&in1,&out);
          ASSERT_TRUE(status==MIPS_MATH_SUCCESS);

          outp += (rows * columns);

      }


	printf("mips_mat_trans_f64 finish \n");

	printf("mips_mat_trans_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, UnaryF64, "RefTranspose1_f64.txt");
#else
	referenceFile = UnaryF64_RefTranspose1_f64;
	referenceFileLen = sizeof(UnaryF64_RefTranspose1_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
    referenceFileLen = referenceFileLen/sizeof(f64);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output, 0, (f64)SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output, referenceFileLen, (f64)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f64(referenceFile, f64output, 0, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f64(referenceData_f64, f64output, referenceFileLen, ABS_ERROR, REL_ERROR);
#endif


    memset(f64output, 0, sizeof(double)*MAX_SIZE);

	printf("\n== mips_mat_trans_f64 check done  == \n\n");  

// =====================

	printf("== mips_mat_inverse_f64 test ==  \n"); 

    inp1 = f64input5;
    outp = f64output;
    dimsp = f64dims2;
    ap = f64a;
    bp = f64b;
    nbMatrixes = paramCountdims2;

      for(i=0;i < nbMatrixes ; i ++)
      {
          rows = *dimsp++;
          columns = rows;

          PREPAREDATA1(false);

          refInnerTail(outp+(rows * columns));

          status=mips_mat_inverse_f64(&in1,&out);
          ASSERT_TRUE(status==MIPS_MATH_SUCCESS);

          outp += (rows * columns);
          inp1 += (rows * columns);

          checkInnerTail(outp);

      }


	printf("mips_mat_inverse_f64 finish \n");

	printf("mips_mat_inverse_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, UnaryF64, "RefInvert1_f64.txt");
#else
	referenceFile = UnaryF64_RefInvert1_f64;
	referenceFileLen = sizeof(UnaryF64_RefInvert1_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
    referenceFileLen = referenceFileLen/sizeof(f64);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output, 0, (f64)SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output, referenceFileLen, (f64)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f64(referenceFile, f64output, 0, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f64(referenceData_f64, f64output, referenceFileLen, ABS_ERROR, REL_ERROR);
#endif


    memset(f64output, 0, sizeof(double)*MAX_SIZE);

	printf("\n== mips_mat_inverse_f64 check done  == \n\n");   

// =====================

	printf("== mips_mat_cholesky_dpo_f64 test ==  \n"); 

    inp1 = f64input6;
    outp = f64output;
    dimsp = f64dims3;
    ap = f64a;
    nbMatrixes = paramCountdims3;

      for(i=0;i < nbMatrixes ; i ++)
      {
          rows = *dimsp++;
          columns = rows;

          PREPAREDATA1(false);

          status=mips_mat_cholesky_f64(&in1,&out);
          ASSERT_TRUE(status==MIPS_MATH_SUCCESS);

          outp += (rows * columns);
          inp1 += (rows * columns);

      }


	printf("mips_mat_cholesky_dpo_f64 finish \n");

	printf("mips_mat_cholesky_dpo_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, UnaryF64, "RefCholeskyDPO1_f64.txt");
#else
	referenceFile = UnaryF64_RefCholeskyDPO1_f64;
	referenceFileLen = sizeof(UnaryF64_RefCholeskyDPO1_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
    referenceFileLen = referenceFileLen/sizeof(f64);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output, 0, (f64)SNR_THRESHOLD_CHOL);
#else
	snr_check_special_f64(referenceData_f64, f64output, referenceFileLen, (f64)SNR_THRESHOLD_CHOL);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f64(referenceFile, f64output, 0, ABS_ERROR_CHOL, REL_ERROR_CHOL);
#else
	close_check_special_f64(referenceData_f64, f64output, referenceFileLen, ABS_ERROR_CHOL, REL_ERROR_CHOL);
#endif


    memset(f64output, 0, sizeof(double)*MAX_SIZE);

	printf("\n== mips_mat_cholesky_dpo_f64 check done  == \n\n");  

// =====================

	printf("== mips_mat_solve_upper_triangular_f64 test ==  \n"); 

    inp1 = f64inputb2;
    inp2 = f64inputb3;
    outp = f64output;
    dimsp = f64dims5;
    ap = f64a;
    bp = f64b;
    nbMatrixes = paramCountdims1 >> 1;

      for(i=0;i < nbMatrixes ; i ++)
      {
          rows = *dimsp++;
          columns = *dimsp++;

          PREPAREDATALT();

          status=mips_mat_solve_upper_triangular_f64(&in1,&in2,&out);
          ASSERT_TRUE(status==MIPS_MATH_SUCCESS);

          outp += (rows * columns);
          inp1 += (rows * rows);
          inp2 += (rows * columns);

      }


	printf("mips_mat_solve_upper_triangular_f64 finish \n");

	printf("mips_mat_solve_upper_triangular_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, UnaryF64, "RefUTSolve1_f64.txt");
#else
	referenceFile = UnaryF64_RefUTSolve1_f64;
	referenceFileLen = sizeof(UnaryF64_RefUTSolve1_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
    referenceFileLen = referenceFileLen/sizeof(f64);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output, 0, (f64)SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output, referenceFileLen, (f64)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f64(referenceFile, f64output, 0, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f64(referenceData_f64, f64output, referenceFileLen, ABS_ERROR, REL_ERROR);
#endif


    memset(f64output, 0, sizeof(double)*MAX_SIZE);

	printf("\n== mips_mat_solve_upper_triangular_f64 check done  == \n\n");  

// =====================

	printf("== mips_mat_solve_lower_triangular_f64 test ==  \n"); 

    inp1 = f64inputb1;
    inp2 = f64inputb3;
    outp = f64output;
    dimsp = f64dims5;
    ap = f64a;
    bp = f64b;
    nbMatrixes = paramCountdims1 >> 1;

      for(i=0;i < nbMatrixes ; i ++)
      {
          rows = *dimsp++;
          columns = *dimsp++;

          PREPAREDATALT();

          status=mips_mat_solve_lower_triangular_f64(&in1,&in2,&out);
          ASSERT_TRUE(status==MIPS_MATH_SUCCESS);

          outp += (rows * columns);
          inp1 += (rows * rows);
          inp2 += (rows * columns);

      }


	printf("mips_mat_solve_lower_triangular_f64 finish \n");

	printf("mips_mat_solve_lower_triangular_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, UnaryF64, "RefLTSolve1_f64.txt");
#else
	referenceFile = UnaryF64_RefLTSolve1_f64;
	referenceFileLen = sizeof(UnaryF64_RefLTSolve1_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
    referenceFileLen = referenceFileLen/sizeof(f64);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output, 0, (f64)SNR_THRESHOLD);
#else
	snr_check_special_f64(referenceData_f64, f64output, referenceFileLen, (f64)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f64(referenceFile, f64output, 0, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f64(referenceData_f64, f64output, referenceFileLen, ABS_ERROR, REL_ERROR);
#endif


    memset(f64output, 0, sizeof(double)*MAX_SIZE);

	printf("\n== mips_mat_solve_lower_triangular_f64 check done  == \n\n");  

// =====================

	printf("== mips_mat_ldlt_f64 11 test ==  \n"); 
 
   
    inp1 = f64input6;
    dimsp = f64dims3;
    ap = f64a;
    nbMatrixes = paramCountdims3;


      for(i=0;i < nbMatrixes ; i ++)
      {
          rows = *dimsp++;
          columns = rows;

          PREPAREDATALL1();

          outd.numRows=rows;
          outd.numCols=columns;
          outd.pData=outdp;

          


          memset(outpp,0,rows*sizeof(uint16_t));
          memset(outdp,0,columns*rows*sizeof(f64));

          status=mips_mat_ldlt_f64(&in1,&outll,&outd,(uint16_t*)outpp);
          ASSERT_TRUE(status==MIPS_MATH_SUCCESS);

          compute_ldlt_error(rows,outpp);

          outllp += (rows * columns);
          outdp += (rows * columns);
          outpp += rows;

          outa += (rows * columns);
          outb +=(rows * columns);

          inp1 += (rows * columns);

      }


	printf("mips_mat_ldlt_f64 11 finish \n");

	printf("mips_mat_ldlt_f64 11 checking \n\n");

	close_check_special_f64(f64outputa, f64outputb, paramCountInput6,REL_ERROR_LDLT,ABS_ERROR_LDLT);


    memset(f64outputa, 0, sizeof(double)*MAX_SIZE);
    memset(f64outputb, 0, sizeof(double)*MAX_SIZE);
    memset(f64outputll, 0, sizeof(double)*MAX_SIZE);
    memset(f64outputd, 0, sizeof(double)*MAX_SIZE);

	printf("\n== mips_mat_ldlt_f64 11 check done  == \n\n");

// =====================

	printf("== mips_mat_ldlt_f64 12 test ==  \n"); 

    outllp = f64outputll;   
    outdp = f64outputd;
    outa = f64outputa;   
    outb = f64outputb;    
    outpp = f64outputp; 

    inp1 = f64input7;
    dimsp = f64dims4;
    ap = f64a;
    nbMatrixes = paramCountdims4;

      for(i=0;i < nbMatrixes ; i ++)
      {
          rows = *dimsp++;
          columns = rows;

          PREPAREDATALL1();

          outd.numRows=rows;
          outd.numCols=columns;
          outd.pData=outdp;

          


          memset(outpp,0,rows*sizeof(uint16_t));
          memset(outdp,0,columns*rows*sizeof(f64));

          status=mips_mat_ldlt_f64(&in1,&outll,&outd,(uint16_t*)outpp);
          ASSERT_TRUE(status==MIPS_MATH_SUCCESS);

          compute_ldlt_error(rows,outpp);

          outllp += (rows * columns);
          outdp += (rows * columns);
          outpp += rows;

          outa += (rows * columns);
          outb +=(rows * columns);

          inp1 += (rows * columns);

      }


	printf("mips_mat_ldlt_f64 12 finish \n");

	printf("mips_mat_ldlt_f64 12 checking \n\n");

	close_check_special_f64(f64outputa, f64outputb, paramCountInput7,ABS_ERROR_LDLT,REL_ERROR_LDLT);

    
	printf("\n== mips_mat_ldlt_f64 12 check done  == \n\n");  

// =====================   

	printf("== mips_householder_f64 test ==  \n");

    inp1 = f64input9;
    outp = f64output;
    outBetap = f64outputBeta;
    dimsp = f64dims7;

    int64_t vecDim;
    int nbVectors = paramCountdims7;

      for(int i=0; i < nbVectors ; i++)
   {
      vecDim = *dimsp++;

      f64 beta = mips_householder_f64(inp1,DEFAULT_HOUSEHOLDER_THRESHOLD_F64,vecDim,outp);
      *outBetap = beta; 

      outp += vecDim;
      inp1 += vecDim;
      outBetap++;
      checkInnerTailOverflow(outp);
      checkInnerTailOverflow(outBetap);

   }


	printf("mips_householder_f64 finish \n");

	printf("mips_householder_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, UnaryF64, "RefVectorHouseholder1_f64.txt");
#else
	referenceFile = UnaryF64_RefVectorHouseholder1_f64;
	referenceFileLen = sizeof(UnaryF64_RefVectorHouseholder1_f64);
	load_data_f64(referenceFile, referenceFileLen, referenceData_f64);
    referenceFileLen = referenceFileLen/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFileBeta, sizeof(referenceFileBeta), "%s%s%s", Patterns_PATH, UnaryF64, "RefValueHouseholder1_f64.txt");
#else
	referenceFileBeta = UnaryF64_RefValueHouseholder1_f64;
	referenceFileBetaLen = sizeof(UnaryF64_RefValueHouseholder1_f64);
    load_data_f64(referenceFileBeta, referenceFileBetaLen, referenceData_f64);
    referenceFileBetaLen = referenceFileBetaLen/sizeof(f64);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFile, f64output, 0, (f64)SNR_HOUSEHOLDER_THRESHOLD);
#else
	snr_check_special_f64(referenceFile, f64output, referenceFileLen, (f64)SNR_HOUSEHOLDER_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFileBeta, f64outputBeta, 0, (f64)SNR_HOUSEHOLDER_THRESHOLD);
#else
	snr_check_special_f64(referenceFileBeta, f64outputBeta, referenceFileBetaLen, (f64)SNR_HOUSEHOLDER_THRESHOLD);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f64(referenceFile, f64output, 0, ABS_HOUSEHOLDER_ERROR, REL_HOUSEHOLDER_ERROR);
#else
	close_check_special_f64(referenceFile, f64output, referenceFileLen, ABS_HOUSEHOLDER_ERROR, REL_HOUSEHOLDER_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f64(referenceFileBeta, f64outputBeta, 0, ABS_HOUSEHOLDER_ERROR, REL_HOUSEHOLDER_ERROR);
#else
	close_check_special_f64(referenceFileBeta, f64outputBeta, referenceFileBetaLen, ABS_HOUSEHOLDER_ERROR, REL_HOUSEHOLDER_ERROR);
#endif


    memset(f64output, 0, sizeof(double)*MAX_SIZE);

	printf("\n== mips_householder_f64 check done  == \n\n");  

// =====================

	printf("== mips_mat_qr_f64 test ==  \n");

    int64_t row, column, rank;
    int nb;
    dimsp = f64dims6;          
    nbMatrixes = paramCountdims6 / 3;
    inp1 = f64input8; 

    f64 *outTaup=f64outputTau;   
    f64 *outRp=f64outputR; 
    f64 *outQp=f64outputQ;  
 
    f64 *pTmpA = f64a2;  
    f64 *pTmpB = f64b3;

    mips_matrix_instance_f64 in1;
    mips_matrix_instance_f64 outR;
    mips_matrix_instance_f64 outQ;  

   (void) outTaup;
   (void) outRp; 
   (void) outQp; 
   (void)nbMatrixes;
   (void)nb;
   (void)dimsp;
   (void)inp1;

   nb=0;
   for(int i=0; i < nbMatrixes ; i++)
   //for(int i=0; i < 1 ; i++)
   {
      row = *dimsp++;
      column = *dimsp++;
      rank = *dimsp++;
      (void)rank;

      //printf("--> %d %d : %lld %lld\n",nb,i,rows,columns);
      nb += rows * columns;

      in1.numRows=row;
      in1.numCols=column;
      in1.pData = (f64*)inp1;

      outR.numRows = row;
      outR.numCols = column;
      outR.pData = (f64*)outRp;

      outQ.numRows = row;
      outQ.numCols = row;
      outQ.pData = (f64*)outQp;

      
      mips_status status=mips_mat_qr_f64(&in1,DEFAULT_HOUSEHOLDER_THRESHOLD_F64,&outR,&outQ,outTaup,pTmpA,pTmpB);
      ASSERT_TRUE(status==MIPS_MATH_SUCCESS);
      
      // Set Householder reflectors into R matrix to 0
      //f64 *p = outRp ;
      //printf("%d %d %d\n",in1.numCols, outR.numRows,outR.numCols);
      #if 0
      for(int col=0 ; col < in1.numCols; col++)
      {
          f64 *pa = p + outR.numCols;
          for(int k=0;k<outR.numRows-col-1; k++)
          {
             *pa = 0;
             pa += outR.numCols;
          }
          p += 1 + outR.numCols;
      }
      #endif
      //PM_f64("Corrected R",&outR);

      inp1 += row * column;
      outRp += row * column;
      outQp += row * row;
      outTaup += column;

      checkInnerTailOverflow(outRp);
      checkInnerTailOverflow(outQp);
      checkInnerTailOverflow(outTaup);


   }



	printf("mips_mat_qr_f64 finish \n");

	printf("mips_mat_qr_f64 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFileQ, sizeof(referenceFileQ), "%s%s%s", Patterns_PATH, UnaryF64, "RefQ1_f64.txt");
#else
	referenceFileQ = UnaryF64_RefQ1_f64;
	referenceFileQLen = sizeof(UnaryF64_RefQ1_f64);
    load_data_f64(referenceFileQ, referenceFileQLen, referenceData_f64);
    referenceFileQLen = referenceFileQLen/sizeof(f64);
    
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFileR, sizeof(referenceFileR), "%s%s%s", Patterns_PATH, UnaryF64, "RefR1_f64.txt");
#else
	referenceFileR = UnaryF64_RefR1_f64;
	referenceFileRLen = sizeof(UnaryF64_RefR1_f64);
    load_data_f64(referenceFileR, referenceFileRLen, referenceData_f64);
    referenceFileRLen = referenceFileRLen/sizeof(f64);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFileTau, sizeof(referenceFileTau), "%s%s%s", Patterns_PATH, UnaryF64, "RefTau1_f64.txt");
#else
	referenceFileTau = UnaryF64_RefTau1_f64;
	referenceFileTauLen = sizeof(UnaryF64_RefTau1_f64);
    load_data_f64(referenceFileTau, referenceFileTauLen, referenceData_f64);
    referenceFileTauLen = referenceFileTauLen/sizeof(f64);
#endif



#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFileQ, f64outputQ, 0, (f64)SNR_QR_THRESHOLD);
#else
	snr_check_special_f64(referenceFileQ, f64outputQ, referenceFileQLen, (f64)SNR_QR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFileR, f64outputR, 0, (f64)SNR_QR_THRESHOLD);
#else
	snr_check_special_f64(referenceFileR, f64outputR, referenceFileRLen, (f64)SNR_QR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f64(referenceFileTau, f64outputTau, 0, (f64)SNR_QR_THRESHOLD);
#else
	snr_check_special_f64(referenceFileTau, f64outputTau, referenceFileTauLen, (f64)SNR_QR_THRESHOLD);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f64(referenceFileQ, f64outputQ, 0, ABS_QR_ERROR, REL_QR_ERROR);
#else
	close_check_special_f64(referenceFileQ, f64outputQ, referenceFileQLen, ABS_QR_ERROR, REL_QR_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f64(referenceFileR, f64outputR, 0, ABS_QR_ERROR, REL_QR_ERROR);
#else
	close_check_special_f64(referenceFileR, f64outputR, referenceFileRLen, ABS_QR_ERROR, REL_QR_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f64(referenceFileTau, f64outputTau, 0, ABS_QR_ERROR, REL_QR_ERROR);
#else
	close_check_special_f64(referenceFileTau, f64outputTau, referenceFileTauLen, ABS_QR_ERROR, REL_QR_ERROR);
#endif


	printf("\n== mips_mat_qr_f64 check done  == \n\n");  

// =====================


return 0;



}