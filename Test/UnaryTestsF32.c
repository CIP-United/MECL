#include "BasicFramework.h"

#if !defined(NOT_EMBEDDED)
#include "Embedded/data.c"
#endif

#include "dsp/matrix_functions.h"

#define SNR_THRESHOLD 120
#define DEFAULT_HOUSEHOLDER_THRESHOLD_F32 (1.0e-12f)
/* Reference patterns are generated with
a double precision computation.*/
#define REL_ERROR (1.0e-5)
#define ABS_ERROR (1.0e-5)

/*Comparisons for Householder*/
#define SNR_HOUSEHOLDER_THRESHOLD 140
#define REL_HOUSEHOLDER_ERROR (1.0e-7)
#define ABS_HOUSEHOLDER_ERROR (1.0e-7)

/*Comparisons for QR decomposition*/
#define SNR_QR_THRESHOLD 90
#define REL_QR_ERROR (1.0e-4)
#define ABS_QR_ERROR (2.0e-4)

/*omparisons for inverse*/

/* Not very accurate for big matrix.
But big matrix needed for checking the vectorized code */
#define SNR_THRESHOLD_INV 99
#define REL_ERROR_INV (3.0e-5)
#define ABS_ERROR_INV (2.0e-5)

/*Comparison for Cholesky*/
#define SNR_THRESHOLD_CHOL 92
#define REL_ERROR_CHOL (1.0e-5)
#define ABS_ERROR_CHOL (5.0e-4)

/* LDLT comparison */
#define REL_ERROR_LDLT (1e-5)
#define ABS_ERROR_LDLT (1e-5)
#define REL_ERROR_LDLT_SPDO (1e-5)
#define ABS_ERROR_LDLT_SDPO (2e-1)

#define MAXMATRIXDIM 40



#define SWAP_ROWS(A,i,j)     \
  for(int w=0;w < n; w++)    \
  {                          \
     f64 tmp;          \
     tmp = A[i*n + w];       \
     A[i*n + w] = A[j*n + w];\
     A[j*n + w] = tmp;       \
  }



static void checkInnerTailOverflow(f32 *b)
{
    ASSERT_TRUE(b[0] == 0.0f);
    ASSERT_TRUE(b[1] == 0.0f);
    ASSERT_TRUE(b[2] == 0.0f);
    ASSERT_TRUE(b[3] == 0.0f);
}


static void refInnerTail(f32 *b)
{
    b[0] = 1.0f;
    b[1] = -2.0f;
    b[2] = 3.0f;
    b[3] = -4.0f;
}


static void checkInnerTail(f32 *b)
{
    ASSERT_TRUE(b[0] == 1.0f);
    ASSERT_TRUE(b[1] == -2.0f);
    ASSERT_TRUE(b[2] == 3.0f);
    ASSERT_TRUE(b[3] == -4.0f);
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


static void trans_f32_f64(const f32 *src, f64 *dst, int n)
    {
        for(int r=0; r<n ; r++)
        {
          for(int c=0; c<n ; c++)
          {
             dst[c*n+r] = (f64)src[r*n+c];
          }
        }
    }


static void mult_f32_f64(const f32 *srcA, const f64 *srcB, f64 *dst,int n)
    {
        for(int r=0; r<n ; r++)
        {
          for(int c=0; c<n ; c++)
          {
             f64 sum=0.0;
             for(int k=0; k < n ; k++)
             {
                sum += (f64)srcA[r*n+k] * srcB[k*n+c];
             }
             dst[r*n+c] = sum;
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




double f32outputa[MAX_SIZE] = {0};
double f32outputb[MAX_SIZE] = {0};
float f32outputll[MAX_SIZE] = {0};
float f32outputd[MAX_SIZE] = {0};
int16_t f32outputp[MAX_SIZE] = {0};

           
f64 *outa = f32outputa;
f64 *outb = f32outputb;   

mips_matrix_instance_f32 in1;
mips_matrix_instance_f32 outd;
mips_matrix_instance_f32 outll;

f32 *outllp = f32outputll;
f64 *outdp = f32outputd;

const int16_t *outpp = f32outputp;


static void compute_ldlt_error(const int n,const int16_t *outpp)
    {
           double f32tmpapat[MAXMATRIXDIM*MAXMATRIXDIM] = {0};
           double f32tmpbpat[MAXMATRIXDIM*MAXMATRIXDIM] = {0};
           double f32tmpcpat[MAXMATRIXDIM*MAXMATRIXDIM] = {0};

           f64 *tmpa  = f32tmpapat ;
           f64 *tmpb  = f32tmpbpat ;
           f64 *tmpc  = f32tmpcpat ;

           
           

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
          mult_f32_f64((const f32*)in1.pData,(const f64*)tmpb,tmpc,n);
          mult_f64_f64((const f64*)tmpa,(const f64*)tmpc,outa,n);
         


          /* Compute L D L^t */
          trans_f32_f64((const f32*)outll.pData,tmpc,n);
          mult_f32_f64((const f32*)outd.pData,(const f64*)tmpc,tmpa,n);
          mult_f32_f64((const f32*)outll.pData,(const f64*)tmpa,outb,n);

         
          
    }

#define LOADDATA2()                          \
      const float *inp1, *inp2;    \
      float  *outp, *ap, *bp;    \
                                             \
      inp1 = f32input1;                 \
      inp2 = f32input2;                 \
      outp = f32output;                 \
      ap = f32a1;                 \
      bp = f32b1;                 \
                                             \
      int16_t *dimsp;          \
      dimsp = f32dims;           \
      int nbMatrixes = paramCountdims / 3;\
      int rows,internal,columns;  

#define PREPAREDATA2()                                                   \
      mips_matrix_instance_f32 in1;\
      mips_matrix_instance_f32 in2;\
      mips_matrix_instance_f32 out;\
      in1.numRows=rows;                                                  \
      in1.numCols=columns;                                               \
      memcpy((void*)ap,(const void*)inp1,sizeof(f32)*rows*columns);\
      in1.pData = ap;                                                    \
                                                                         \
      in2.numRows=rows;                                                  \
      in2.numCols=columns;                                               \
      memcpy((void*)bp,(const void*)inp2,sizeof(f32)*rows*columns);\
      in2.pData = bp;                                                    \
                                                                         \
      out.numRows=rows;                                                  \
      out.numCols=columns;                                               \
      out.pData = outp;

#define PREPAREDATALT()                                                  \
      mips_matrix_instance_f32 in1;\
      mips_matrix_instance_f32 in2;\
      mips_matrix_instance_f32 out;\
      in1.numRows=rows;                                                  \
      in1.numCols=rows;                                                  \
      memcpy((void*)ap,(const void*)inp1,sizeof(f32)*rows*rows);   \
      in1.pData = ap;                                                    \
                                                                         \
      in2.numRows=rows;                                                  \
      in2.numCols=columns;                                               \
      memcpy((void*)bp,(const void*)inp2,sizeof(f32)*rows*columns);\
      in2.pData = bp;                                                    \
                                                                         \
      out.numRows=rows;                                                  \
      out.numCols=columns;                                               \
      out.pData = outp;
#define PREPAREDATA1(TRANSPOSED)                                         \
      mips_matrix_instance_f32 in1;\
      mips_matrix_instance_f32 out;\
      in1.numRows=rows;                                                  \
      in1.numCols=columns;                                               \
      memcpy((void*)ap,(const void*)inp1,sizeof(f32)*rows*columns);\
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
      mips_matrix_instance_f32 in1;\
      mips_matrix_instance_f32 out;\
      in1.numRows=rows;                                                  \
      in1.numCols=columns;                                               \
      memcpy((void*)ap,(const void*)inp1,2*sizeof(f32)*rows*columns);\
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
#define PREPAREVECDATA2()                                                 \
      mips_matrix_instance_f32 in1;\
      in1.numRows=rows;                                                   \
      in1.numCols=internal;                                               \
      memcpy((void*)ap,(const void*)inp1,sizeof(f32)*rows*internal);\
      in1.pData = ap;                                                     \
                                                                          \
      memcpy((void*)bp,(const void*)inp2,sizeof(f32)*internal);
                            
#define PREPAREDATALL1()                                                 \
      in1.numRows=rows;                                                  \
      in1.numCols=columns;                                               \
      memcpy((void*)ap,(const void*)inp1,sizeof(f32)*rows*columns);\
      in1.pData = ap;                                                    \
                                                                         \
      outll.numRows=rows;                                                \
      outll.numCols=columns;                                             \
                                                                         \
      outll.pData = outllp;



int main()
{

#if !defined(NOT_EMBEDDED)	
	f32 referenceData_f32[MAX_SIZE] = {0};
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


	float f32input1[MAX_SIZE] = {0};
    float f32input2[MAX_SIZE] = {0};
    float f32input3[MAX_SIZE] = {0};
    float f32input4[MAX_SIZE] = {0};
    float f32input5[MAX_SIZE] = {0};
    float f32input6[MAX_SIZE] = {0};
    float f32input7[MAX_SIZE] = {0};
    float f32input8[MAX_SIZE] = {0};
    float f32input9[MAX_SIZE] = {0};

    float f32inputa1[MAX_SIZE] = {0};
    float f32inputa2[MAX_SIZE] = {0};
    float f32inputa3[MAX_SIZE] = {0};
    float f32inputb1[MAX_SIZE] = {0};
    float f32inputb2[MAX_SIZE] = {0};
    float f32inputb3[MAX_SIZE] = {0};

    q15 f32dims1[MAX_SIZE] = {0};
    q15 f32dims2[MAX_SIZE] = {0};
    q15 f32dims3[MAX_SIZE] = {0};
    q15 f32dims4[MAX_SIZE] = {0};
    q15 f32dims5[MAX_SIZE] = {0};
    q15 f32dims6[MAX_SIZE] = {0};
    q15 f32dims7[MAX_SIZE] = {0};


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
	snprintf(inputFile1, sizeof(inputFile1), "%s%s%s", Patterns_PATH, UnaryF32, "InputA1_f32.txt");
#else
	inputFile1 = UnaryF32_InputA1_f32;
	inputFile1Len = sizeof(UnaryF32_InputA1_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile2, sizeof(inputFile2), "%s%s%s", Patterns_PATH, UnaryF32, "InputB1_f32.txt");
#else
	inputFile2 = UnaryF32_InputB1_f32;
	inputFile2Len = sizeof(UnaryF32_InputB1_f32);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(inputFile3, sizeof(inputFile3), "%s%s%s", Patterns_PATH, UnaryF32, "InputAC1_f32.txt");
#else
	inputFile3 = UnaryF32_InputAC1_f32;
	inputFile3Len = sizeof(UnaryF32_InputAC1_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile4, sizeof(inputFile4), "%s%s%s", Patterns_PATH, UnaryF32, "InputVec1_f32.txt");
#else
	inputFile4 = UnaryF32_InputVec1_f32;
	inputFile4Len = sizeof(UnaryF32_InputVec1_f32);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(inputFile5, sizeof(inputFile5), "%s%s%s", Patterns_PATH, UnaryF32, "InputInvert1_f32.txt");
#else
	inputFile5 = UnaryF32_InputInvert1_f32;
	inputFile5Len = sizeof(UnaryF32_InputInvert1_f32);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(inputFile6, sizeof(inputFile6), "%s%s%s", Patterns_PATH, UnaryF32, "InputCholeskyDPO1_f32.txt");
#else
	inputFile6 = UnaryF32_InputCholeskyDPO1_f32;
	inputFile6Len = sizeof(UnaryF32_InputCholeskyDPO1_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile7, sizeof(inputFile7), "%s%s%s", Patterns_PATH, UnaryF32, "InputCholeskySDPO1_f32.txt");
#else
	inputFile7 = UnaryF32_InputCholeskySDPO1_f32;
	inputFile7Len = sizeof(UnaryF32_InputCholeskySDPO1_f32);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(inputFile8, sizeof(inputFile8), "%s%s%s", Patterns_PATH, UnaryF32, "InputMatrixQR1_f32.txt");
#else
	inputFile8 = UnaryF32_InputMatrixQR1_f32;
	inputFile8Len = sizeof(UnaryF32_InputMatrixQR1_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFile9, sizeof(inputFile9), "%s%s%s", Patterns_PATH, UnaryF32, "InputVectorHouseHolder1_f32.txt");
#else
	inputFile9 = UnaryF32_InputVectorHouseHolder1_f32;
	inputFile9Len = sizeof(UnaryF32_InputVectorHouseHolder1_f32);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(inputFilea1, sizeof(inputFilea3), "%s%s%s", Patterns_PATH, UnaryF32, "InputUTDPO1_f32.txt");
#else
	inputFilea1 = UnaryF32_InputUTDPO1_f32;
	inputFilea1Len = sizeof(UnaryF32_InputUTDPO1_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFilea2, sizeof(inputFilea3), "%s%s%s", Patterns_PATH, UnaryF32, "InputLTDPO1_f32.txt");
#else
	inputFilea2 = UnaryF32_InputLTDPO1_f32;
	inputFilea2Len = sizeof(UnaryF32_InputLTDPO1_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFilea3, sizeof(inputFilea3), "%s%s%s", Patterns_PATH, UnaryF32, "InputRNDA1_f32.txt");
#else
	inputFilea3 = UnaryF32_InputRNDA1_f32;
	inputFilea3Len = sizeof(UnaryF32_InputRNDA1_f32);
#endif


#if defined(NOT_EMBEDDED)
	snprintf(inputFileb1, sizeof(inputFileb1), "%s%s%s", Patterns_PATH, UnaryF32, "InputMatrixLTSolve1_f32.txt");
#else
	inputFileb1 = UnaryF32_InputMatrixLTSolve1_f32;
	inputFileb1Len = sizeof(UnaryF32_InputMatrixLTSolve1_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileb2, sizeof(inputFileb2), "%s%s%s", Patterns_PATH, UnaryF32, "InputMatrixUTSolve1_f32.txt");
#else
	inputFileb2 = UnaryF32_InputMatrixUTSolve1_f32;
	inputFileb2Len = sizeof(UnaryF32_InputMatrixUTSolve1_f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(inputFileb3, sizeof(inputFileb3), "%s%s%s", Patterns_PATH, UnaryF32, "InputVectorLTSolve1_f32.txt");
#else
	inputFileb3 = UnaryF32_InputVectorLTSolve1_f32;
	inputFileb3Len = sizeof(UnaryF32_InputVectorLTSolve1_f32);
#endif

    
	//dim
#if defined(NOT_EMBEDDED)
	snprintf(dimsFile1, sizeof(dimsFile1), "%s%s%s", Patterns_PATH, UnaryF32, "DimsUnary1_s16.txt");
#else
	dimsFile1 = UnaryF32_DimsUnary1_s16;
	dimsFile1Len = sizeof(UnaryF32_DimsUnary1_s16);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(dimsFile2, sizeof(dimsFile2), "%s%s%s", Patterns_PATH, UnaryF32, "DimsInvert1_s16.txt");
#else
	dimsFile2 = UnaryF32_DimsInvert1_s16;
	dimsFile2Len = sizeof(UnaryF32_DimsInvert1_s16);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(dimsFile3, sizeof(dimsFile3), "%s%s%s", Patterns_PATH, UnaryF32, "DimsCholeskyDPO1_s16.txt");
#else
	dimsFile3 = UnaryF32_DimsCholeskyDPO1_s16;
	dimsFile3Len = sizeof(UnaryF32_DimsCholeskyDPO1_s16);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(dimsFile4, sizeof(dimsFile4), "%s%s%s", Patterns_PATH, UnaryF32, "DimsCholeskySDPO1_s16.txt");
#else
	dimsFile4 = UnaryF32_DimsCholeskySDPO1_s16;
	dimsFile4Len = sizeof(UnaryF32_DimsCholeskySDPO1_s16);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(dimsFile5, sizeof(dimsFile5), "%s%s%s", Patterns_PATH, UnaryF32, "DimsLTSolve1_s16.txt");
#else
	dimsFile5 = UnaryF32_DimsLTSolve1_s16;
	dimsFile5Len = sizeof(UnaryF32_DimsLTSolve1_s16);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(dimsFile6, sizeof(dimsFile6), "%s%s%s", Patterns_PATH, UnaryF32, "DimsQR1_s16.txt");
#else
	dimsFile6 = UnaryF32_DimsQR1_s16;
	dimsFile6Len = sizeof(UnaryF32_DimsQR1_s16);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(dimsFile7, sizeof(dimsFile7), "%s%s%s", Patterns_PATH, UnaryF32, "DimsHouseholder1_s16.txt");
#else
	dimsFile7 = UnaryF32_DimsHouseholder1_s16;
	dimsFile7Len = sizeof(UnaryF32_DimsHouseholder1_s16);
#endif






	// load input data
#if defined(NOT_EMBEDDED)
	load_data_f32(inputFile1, &paramCountInput1, f32input1);
#else
	paramCountInput1 = inputFile1Len;
	load_data_f32(inputFile1, paramCountInput1, f32input1);
	paramCountInput1 = paramCountInput1/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFile2, &paramCountInput2, f32input2);
#else
	paramCountInput2 = inputFile2Len;
	load_data_f32(inputFile2, paramCountInput2, f32input2);
	paramCountInput2 = paramCountInput2/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFile3, &paramCountInput3, f32input3);
#else
	paramCountInput3 = inputFile3Len;
	load_data_f32(inputFile3, paramCountInput3, f32input3);
	paramCountInput3 = paramCountInput3/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFile4, &paramCountInput4, f32input4);
#else
	paramCountInput4 = inputFile4Len;
	load_data_f32(inputFile4, paramCountInput4, f32input4);
	paramCountInput4 = paramCountInput4/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFile5, &paramCountInput5, f32input5);
#else
	paramCountInput5 = inputFile5Len;
	load_data_f32(inputFile5, paramCountInput5, f32input5);
	paramCountInput5 = paramCountInput5/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFile6, &paramCountInput6, f32input6);
#else
	paramCountInput6 = inputFile6Len;
	load_data_f32(inputFile6, paramCountInput6, f32input6);
	paramCountInput6 = paramCountInput6/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFile7, &paramCountInput7, f32input7);
#else
	paramCountInput7 = inputFile7Len;
	load_data_f32(inputFile7, paramCountInput7, f32input7);
	paramCountInput7 = paramCountInput7/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFile8, &paramCountInput8, f32input8);
#else
	paramCountInput8 = inputFile8Len;
	load_data_f32(inputFile8, paramCountInput8, f32input8);
	paramCountInput8 = paramCountInput8/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFile9, &paramCountInput9, f32input9);
#else
	paramCountInput9 = inputFile9Len;
	load_data_f32(inputFile9, paramCountInput9, f32input9);
	paramCountInput9 = paramCountInput9/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	load_data_f32(inputFilea1, &paramCountInputa1, f32inputa1);
#else
	paramCountInputa1 = inputFilea1Len;
	load_data_f32(inputFilea1, paramCountInputa1, f32inputa1);
	paramCountInputa1 = paramCountInputa1/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFilea2, &paramCountInputa2, f32inputa2);
#else
	paramCountInputa2 = inputFilea2Len;
	load_data_f32(inputFilea2, paramCountInputa2, f32inputa2);
	paramCountInputa2 = paramCountInputa2/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFilea3, &paramCountInputa3, f32inputa3);
#else
	paramCountInputa3 = inputFilea3Len;
	load_data_f32(inputFilea3, paramCountInputa3, f32inputa3);
	paramCountInputa3 = paramCountInputa3/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFileb1, &paramCountInputb1, f32inputb1);
#else
	paramCountInputb1 = inputFileb1Len;
	load_data_f32(inputFileb1, paramCountInputb1, f32inputb1);
	paramCountInputb1 = paramCountInputb1/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFileb2, &paramCountInputb2, f32inputb2);
#else
	paramCountInputb2 = inputFileb2Len;
	load_data_f32(inputFileb2, paramCountInputb2, f32inputb2);
	paramCountInputb2 = paramCountInputb2/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	load_data_f32(inputFileb3, &paramCountInputb3, f32inputb3);
#else
	paramCountInputb3 = inputFileb3Len;
	load_data_f32(inputFileb3, paramCountInputb3, f32inputb3);
	paramCountInputb3 = paramCountInputb3/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	load_data_q15(dimsFile1, &paramCountdims1, f32dims1);
#else
	paramCountdims1 = dimsFile1Len;
	load_data_q15(dimsFile1, paramCountdims1, f32dims1);
	paramCountdims1 = paramCountdims1/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(dimsFile2, &paramCountdims2, f32dims2);
#else
	paramCountdims2 = dimsFile2Len;
	load_data_q15(dimsFile2, paramCountdims2, f32dims2);
	paramCountdims2 = paramCountdims2/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(dimsFile3, &paramCountdims3, f32dims3);
#else
	paramCountdims3 = dimsFile3Len;
	load_data_q15(dimsFile3, paramCountdims3, f32dims3);
	paramCountdims3 = paramCountdims3/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(dimsFile4, &paramCountdims4, f32dims4);
#else
	paramCountdims4 = dimsFile4Len;
	load_data_q15(dimsFile4, paramCountdims4, f32dims4);
	paramCountdims4 = paramCountdims4/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(dimsFile5, &paramCountdims5, f32dims5);
#else
	paramCountdims5 = dimsFile5Len;
	load_data_q15(dimsFile5, paramCountdims5, f32dims5);
	paramCountdims5 = paramCountdims5/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(dimsFile6, &paramCountdims6, f32dims6);
#else
	paramCountdims6 = dimsFile6Len;
	load_data_q15(dimsFile6, paramCountdims6, f32dims6);
	paramCountdims6 = paramCountdims6/sizeof(q15);
#endif

#if defined(NOT_EMBEDDED)
	load_data_q15(dimsFile7, &paramCountdims7, f32dims7);
#else
	paramCountdims7 = dimsFile7Len;
	load_data_q15(dimsFile7, paramCountdims7, f32dims7);
	paramCountdims7 = paramCountdims7/sizeof(q15);
#endif


	float f32output[MAX_SIZE] = {0};
    float f32outputBeta[MAX_SIZE] = {0};


    float f32outputTau[MAX_SIZE] = {0};
    float f32outputR[MAX_SIZE] = {0};
    float f32outputQ[MAX_SIZE] = {0};

    

    

    float f32a[MAXMATRIXDIM*MAXMATRIXDIM] = {0};
    float f32b[MAXMATRIXDIM*MAXMATRIXDIM] = {0};
    float f32a2[47] = {0};
    float f32b2[MAXMATRIXDIM] = {0};
    float f32b3[47] = {0};

    

    mips_status status;

    const float *inp1;
    const float *inp2;    
    float  *outBetap;
    float  *outp;    
    float  *ap;
    float  *bp;
                                                           
    int16_t *dimsp;           
                
    int nbMatrixes;
    int rows,internal,columns;
    int i;
// =====================

	printf("== mips_mat_add_f32 test ==  \n"); 
    
    inp1 = f32input1;
    inp2 = f32input2;
    outp = f32output;
    dimsp = f32dims1;
    ap = f32a;
    bp = f32b;
    nbMatrixes = paramCountdims1 >> 1;


      for(i=0;i < nbMatrixes ; i ++)
      {
          rows = *dimsp++;
          columns = *dimsp++;

          PREPAREDATA2();

          status=mips_mat_add_f32(&in1,&in2,&out);
          ASSERT_TRUE(status==MIPS_MATH_SUCCESS);

          outp += (rows * columns);
          checkInnerTailOverflow(outp);

      }


	printf("mips_mat_add_f32 finish \n");

	printf("mips_mat_add_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, UnaryF32, "RefAdd1_f32.txt");
#else
	referenceFile = UnaryF32_RefAdd1_f32;
	referenceFileLen = sizeof(UnaryF32_RefAdd1_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
    referenceFileLen = referenceFileLen/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output, referenceFileLen, (f32)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output, 0, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output, referenceFileLen, ABS_ERROR, REL_ERROR);
#endif


    memset(f32output, 0, sizeof(float)*MAX_SIZE);

	printf("\n== mips_mat_add_f32 check done  == \n\n");  

// =====================

	printf("== mips_mat_sub_f32 test ==  \n"); 
    
    inp1 = f32input1;
    inp2 = f32input2;
    outp = f32output;
    dimsp = f32dims1;
    ap = f32a;
    bp = f32b;
    nbMatrixes = paramCountdims1 >> 1;

      for(i=0;i < nbMatrixes ; i ++)
      {
          rows = *dimsp++;
          columns = *dimsp++;

          PREPAREDATA2();

          status=mips_mat_sub_f32(&in1,&in2,&out);
          ASSERT_TRUE(status==MIPS_MATH_SUCCESS);

          outp += (rows * columns);
          checkInnerTailOverflow(outp);

      }


	printf("mips_mat_sub_f32 finish \n");

	printf("mips_mat_sub_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, UnaryF32, "RefSub1_f32.txt");
#else
	referenceFile = UnaryF32_RefSub1_f32;
	referenceFileLen = sizeof(UnaryF32_RefSub1_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
    referenceFileLen = referenceFileLen/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output, referenceFileLen, (f32)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output, 0, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output, referenceFileLen, ABS_ERROR, REL_ERROR);
#endif


    memset(f32output, 0, sizeof(float)*MAX_SIZE);

	printf("\n== mips_mat_sub_f32 check done  == \n\n");  

// =====================

	printf("== mips_mat_scale_f32 test ==  \n"); 
    
    inp1 = f32input1;
    outp = f32output;
    dimsp = f32dims1;
    ap = f32a;
    nbMatrixes = paramCountdims1 >> 1;

      for(i=0;i < nbMatrixes ; i ++)
      {
          rows = *dimsp++;
          columns = *dimsp++;

          PREPAREDATA1(false);

          status=mips_mat_scale_f32(&in1,0.5f,&out);
          ASSERT_TRUE(status==MIPS_MATH_SUCCESS);

          outp += (rows * columns);
          checkInnerTailOverflow(outp);

      }


	printf("mips_mat_scale_f32 finish \n");

	printf("mips_mat_scale_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, UnaryF32, "RefScale1_f32.txt");
#else
	referenceFile = UnaryF32_RefScale1_f32;
	referenceFileLen = sizeof(UnaryF32_RefScale1_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
    referenceFileLen = referenceFileLen/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output, referenceFileLen, (f32)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output, 0, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output, referenceFileLen, ABS_ERROR, REL_ERROR);
#endif


    memset(f32output, 0, sizeof(float)*MAX_SIZE);

	printf("\n== mips_mat_scale_f32 check done  == \n\n");  

// =====================

	printf("== mips_mat_trans_f32 test ==  \n"); 
    
    inp1 = f32input1;
    outp = f32output;
    dimsp = f32dims1;
    ap = f32a;
    nbMatrixes = paramCountdims1 >> 1;

      for(i=0;i < nbMatrixes ; i ++)
      {
          rows = *dimsp++;
          columns = *dimsp++;

          PREPAREDATA1(true);

          status=mips_mat_trans_f32(&in1,&out);
          ASSERT_TRUE(status==MIPS_MATH_SUCCESS);

          outp += (rows * columns);
          checkInnerTailOverflow(outp);

      }


	printf("mips_mat_trans_f32 finish \n");

	printf("mips_mat_trans_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, UnaryF32, "RefTranspose1_f32.txt");
#else
	referenceFile = UnaryF32_RefTranspose1_f32;
	referenceFileLen = sizeof(UnaryF32_RefTranspose1_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
    referenceFileLen = referenceFileLen/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output, referenceFileLen, (f32)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output, 0, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output, referenceFileLen, ABS_ERROR, REL_ERROR);
#endif


    memset(f32output, 0, sizeof(float)*MAX_SIZE);

	printf("\n== mips_mat_trans_f32 check done  == \n\n");  

// =====================

	printf("== mips_mat_inverse_f32 test ==  \n"); 

    inp1 = f32input5;
    outp = f32output;
    dimsp = f32dims2;
    ap = f32a;
    bp = f32b;
    nbMatrixes = paramCountdims2;

      for(i=0;i < nbMatrixes ; i ++)
      {
          rows = *dimsp++;
          columns = rows;

          PREPAREDATA1(false);

          refInnerTail(outp+(rows * columns));

          status=mips_mat_inverse_f32(&in1,&out);
          ASSERT_TRUE(status==MIPS_MATH_SUCCESS);

          outp += (rows * columns);
          inp1 += (rows * columns);

          checkInnerTail(outp);

      }


	printf("mips_mat_inverse_f32 finish \n");

	printf("mips_mat_inverse_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, UnaryF32, "RefInvert1_f32.txt");
#else
	referenceFile = UnaryF32_RefInvert1_f32;
	referenceFileLen = sizeof(UnaryF32_RefInvert1_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
    referenceFileLen = referenceFileLen/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output, 0, (f32)SNR_THRESHOLD_INV);
#else
	snr_check_special_f32(referenceData_f32, f32output, referenceFileLen, (f32)SNR_THRESHOLD_INV);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output, 0, ABS_ERROR_INV, REL_ERROR_INV);
#else
	close_check_special_f32(referenceData_f32, f32output, referenceFileLen, ABS_ERROR_INV, REL_ERROR_INV);
#endif


    memset(f32output, 0, sizeof(float)*MAX_SIZE);

	printf("\n== mips_mat_inverse_f32 check done  == \n\n");   

// =====================

	printf("== mips_mat_vec_mult_f32 test ==  \n"); 
    
    inp1 = f32input1;
    inp2 = f32input4;
    outp = f32output;
    dimsp = f32dims1;
    ap = f32a;
    bp = f32b2;
    nbMatrixes = paramCountdims1 / 2;
    

      for(i=0;i < nbMatrixes ; i ++)
      {
          rows = *dimsp++;
          internal = *dimsp++;

          PREPAREVECDATA2();

          mips_mat_vec_mult_f32(&in1, bp, outp);

          outp += rows ;
          checkInnerTailOverflow(outp);

      }


	printf("mips_mat_vec_mult_f32 finish \n");

	printf("mips_mat_vec_mult_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, UnaryF32, "RefVecMul1_f32.txt");
#else
	referenceFile = UnaryF32_RefVecMul1_f32;
	referenceFileLen = sizeof(UnaryF32_RefVecMul1_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
    referenceFileLen = referenceFileLen/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output, referenceFileLen, (f32)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output, 0, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output, referenceFileLen, ABS_ERROR, REL_ERROR);
#endif


    memset(f32output, 0, sizeof(float)*MAX_SIZE);

	printf("\n== mips_mat_vec_mult_f32 check done  == \n\n");  

// =====================

	printf("== mips_mat_cmplx_trans_f32 test ==  \n"); 
    
    inp1 = f32input3;
    outp = f32output;
    dimsp = f32dims1;
    ap = f32a;
    nbMatrixes = paramCountdims1 >> 1;


      for(i=0;i < nbMatrixes ; i ++)
      {
          rows = *dimsp++;
          columns = *dimsp++;

          PREPAREDATA1C(true);

          status=mips_mat_cmplx_trans_f32(&in1,&out);
          ASSERT_TRUE(status==MIPS_MATH_SUCCESS);

          outp += 2*(rows * columns);
          checkInnerTailOverflow(outp);

      }


	printf("mips_mat_cmplx_trans_f32 finish \n");

	printf("mips_mat_cmplx_trans_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, UnaryF32, "RefTransposeC1_f32.txt");
#else
	referenceFile = UnaryF32_RefTransposeC1_f32;
	referenceFileLen = sizeof(UnaryF32_RefTransposeC1_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
    referenceFileLen = referenceFileLen/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output, referenceFileLen, (f32)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output, 0, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output, referenceFileLen, ABS_ERROR, REL_ERROR);
#endif


    memset(f32output, 0, sizeof(float)*MAX_SIZE);

	printf("\n== mips_mat_cmplx_trans_f32 check done  == \n\n"); 

// =====================

	printf("== mips_mat_cholesky_dpo_f32 test ==  \n"); 

    inp1 = f32input6;
    outp = f32output;
    dimsp = f32dims3;
    ap = f32a;
    nbMatrixes = paramCountdims3;

      for(i=0;i < nbMatrixes ; i ++)
      {
          rows = *dimsp++;
          columns = rows;

          PREPAREDATA1(false);

          status=mips_mat_cholesky_f32(&in1,&out);
          ASSERT_TRUE(status==MIPS_MATH_SUCCESS);

          outp += (rows * columns);
          inp1 += (rows * columns);
          checkInnerTailOverflow(outp);

      }


	printf("mips_mat_cholesky_dpo_f32 finish \n");

	printf("mips_mat_cholesky_dpo_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, UnaryF32, "RefCholeskyDPO1_f32.txt");
#else
	referenceFile = UnaryF32_RefCholeskyDPO1_f32;
	referenceFileLen = sizeof(UnaryF32_RefCholeskyDPO1_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
    referenceFileLen = referenceFileLen/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output, 0, (f32)SNR_THRESHOLD_CHOL);
#else
	snr_check_special_f32(referenceData_f32, f32output, referenceFileLen, (f32)SNR_THRESHOLD_CHOL);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output, 0, ABS_ERROR_CHOL, REL_ERROR_CHOL);
#else
	close_check_special_f32(referenceData_f32, f32output, referenceFileLen, ABS_ERROR_CHOL, REL_ERROR_CHOL);
#endif


    memset(f32output, 0, sizeof(float)*MAX_SIZE);

	printf("\n== mips_mat_cholesky_dpo_f32 check done  == \n\n");  

// =====================

	printf("== mips_mat_solve_upper_triangular_f32 test ==  \n"); 

    inp1 = f32inputb2;
    inp2 = f32inputb3;
    outp = f32output;
    dimsp = f32dims5;
    ap = f32a;
    bp = f32b;
    nbMatrixes = paramCountdims1 >> 1;

      for(i=0;i < nbMatrixes ; i ++)
      {
          rows = *dimsp++;
          columns = *dimsp++;

          PREPAREDATALT();

          status=mips_mat_solve_upper_triangular_f32(&in1,&in2,&out);
          ASSERT_TRUE(status==MIPS_MATH_SUCCESS);

          outp += (rows * columns);
          inp1 += (rows * rows);
          inp2 += (rows * columns);
          checkInnerTailOverflow(outp);

      }


	printf("mips_mat_solve_upper_triangular_f32 finish \n");

	printf("mips_mat_solve_upper_triangular_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, UnaryF32, "RefUTSolve1_f32.txt");
#else
	referenceFile = UnaryF32_RefUTSolve1_f32;
	referenceFileLen = sizeof(UnaryF32_RefUTSolve1_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
    referenceFileLen = referenceFileLen/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output, referenceFileLen, (f32)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output, 0, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output, referenceFileLen, ABS_ERROR, REL_ERROR);
#endif


    memset(f32output, 0, sizeof(float)*MAX_SIZE);

	printf("\n== mips_mat_solve_upper_triangular_f32 check done  == \n\n");  

// =====================

	printf("== mips_mat_solve_lower_triangular_f32 test ==  \n"); 

    inp1 = f32inputb1;
    inp2 = f32inputb3;
    outp = f32output;
    dimsp = f32dims5;
    ap = f32a;
    bp = f32b;
    nbMatrixes = paramCountdims1 >> 1;

      for(i=0;i < nbMatrixes ; i ++)
      {
          rows = *dimsp++;
          columns = *dimsp++;

          PREPAREDATALT();

          status=mips_mat_solve_lower_triangular_f32(&in1,&in2,&out);
          ASSERT_TRUE(status==MIPS_MATH_SUCCESS);

          outp += (rows * columns);
          inp1 += (rows * rows);
          inp2 += (rows * columns);
          checkInnerTailOverflow(outp);

      }


	printf("mips_mat_solve_lower_triangular_f32 finish \n");

	printf("mips_mat_solve_lower_triangular_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, UnaryF32, "RefLTSolve1_f32.txt");
#else
	referenceFile = UnaryF32_RefLTSolve1_f32;
	referenceFileLen = sizeof(UnaryF32_RefLTSolve1_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
    referenceFileLen = referenceFileLen/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output, 0, (f32)SNR_THRESHOLD);
#else
	snr_check_special_f32(referenceData_f32, f32output, referenceFileLen, (f32)SNR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output, 0, ABS_ERROR, REL_ERROR);
#else
	close_check_special_f32(referenceData_f32, f32output, referenceFileLen, ABS_ERROR, REL_ERROR);
#endif


    memset(f32output, 0, sizeof(float)*MAX_SIZE);

	printf("\n== mips_mat_solve_lower_triangular_f32 check done  == \n\n");  

// =====================

	printf("== mips_mat_ldlt_f32 11 test ==  \n"); 
 
   
    inp1 = f32input6;
    dimsp = f32dims3;
    ap = f32a;
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
          memset(outdp,0,columns*rows*sizeof(f32));

          status=mips_mat_ldlt_f32(&in1,&outll,&outd,(uint16_t*)outpp);
          ASSERT_TRUE(status==MIPS_MATH_SUCCESS);
 

          compute_ldlt_error(rows,outpp);

         
          outllp += (rows * columns);
          outdp += (rows * columns);
          outpp += rows;

          outa += (rows * columns);
          outb +=(rows * columns);

          inp1 += (rows * columns);

          checkInnerTailOverflow(outllp);
          checkInnerTailOverflow(outdp);


      }


	printf("mips_mat_ldlt_f32 11 finish \n");

	printf("mips_mat_ldlt_f32 11 checking \n\n");

	close_check_special_f64(f32outputa, f32outputb, paramCountInput6,REL_ERROR_LDLT,ABS_ERROR_LDLT);



    memset(f32outputa, 0, sizeof(double)*MAX_SIZE);
    memset(f32outputb, 0, sizeof(double)*MAX_SIZE);
    memset(f32outputll, 0, sizeof(float)*MAX_SIZE);
    memset(f32outputd, 0, sizeof(float)*MAX_SIZE);

	printf("\n== mips_mat_ldlt_f32 11 check done  == \n\n");

// =====================

	printf("== mips_mat_ldlt_f32 12 test ==  \n"); 

    outllp = f32outputll;   
    outdp = f32outputd;
    outa = f32outputa;   
    outb = f32outputb;    
    outpp = f32outputp; 

    inp1 = f32input7;
    dimsp = f32dims4;
    ap = f32a;
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
          memset(outdp,0,columns*rows*sizeof(f32));

          status=mips_mat_ldlt_f32(&in1,&outll,&outd,(uint16_t*)outpp);
          ASSERT_TRUE(status==MIPS_MATH_SUCCESS);
 

          compute_ldlt_error(rows,outpp);

         
          outllp += (rows * columns);
          outdp += (rows * columns);
          outpp += rows;

          outa += (rows * columns);
          outb +=(rows * columns);

          inp1 += (rows * columns);

          checkInnerTailOverflow(outllp);
          checkInnerTailOverflow(outdp);


      }


	printf("mips_mat_ldlt_f32 12 finish \n");

	printf("mips_mat_ldlt_f32 12 checking \n\n");



	close_check_special_f64(f32outputa, f32outputb, paramCountInput7,REL_ERROR_LDLT_SPDO,ABS_ERROR_LDLT_SDPO);

    
	printf("\n== mips_mat_ldlt_f32 12 check done  == \n\n");  

// =====================   

	printf("== mips_householder_f32 test ==  \n");

    inp1 = f32input9;
    outp = f32output;
    outBetap = f32outputBeta;
    dimsp = f32dims7;

    int32_t vecDim;
    int nbVectors = paramCountdims7;

      for(i = 0;i < nbVectors ; i ++)
      {
          vecDim = *dimsp++;
          

          f32 beta = mips_householder_f32(inp1,DEFAULT_HOUSEHOLDER_THRESHOLD_F32,vecDim,outp);
          *outBetap = beta;

          outp += vecDim;
          inp1 += vecDim;
          outBetap++;
          checkInnerTailOverflow(outp);
          checkInnerTailOverflow(outBetap);

      }


	printf("mips_householder_f32 finish \n");

	printf("mips_householder_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFile, sizeof(referenceFile), "%s%s%s", Patterns_PATH, UnaryF32, "RefVectorHouseholder1_f32.txt");
#else
	referenceFile = UnaryF32_RefVectorHouseholder1_f32;
	referenceFileLen = sizeof(UnaryF32_RefVectorHouseholder1_f32);
	load_data_f32(referenceFile, referenceFileLen, referenceData_f32);
    referenceFileLen = referenceFileLen/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFileBeta, sizeof(referenceFileBeta), "%s%s%s", Patterns_PATH, UnaryF32, "RefValueHouseholder1_f32.txt");
#else
	referenceFileBeta = UnaryF32_RefValueHouseholder1_f32;
	referenceFileBetaLen = sizeof(UnaryF32_RefValueHouseholder1_f32);
    load_data_f32(referenceFileBeta, referenceFileBetaLen, referenceData_f32);
    referenceFileBetaLen = referenceFileBetaLen/sizeof(f32);
#endif


#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFile, f32output, 0, (f32)SNR_HOUSEHOLDER_THRESHOLD);
#else
	snr_check_special_f32(referenceFile, f32output, referenceFileLen, (f32)SNR_HOUSEHOLDER_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFileBeta, f32outputBeta, 0, (f32)SNR_HOUSEHOLDER_THRESHOLD);
#else
	snr_check_special_f32(referenceFileBeta, f32outputBeta, referenceFileBetaLen, (f32)SNR_HOUSEHOLDER_THRESHOLD);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFile, f32output, 0, ABS_HOUSEHOLDER_ERROR, REL_HOUSEHOLDER_ERROR);
#else
	close_check_special_f32(referenceFile, f32output, referenceFileLen, ABS_HOUSEHOLDER_ERROR, REL_HOUSEHOLDER_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFileBeta, f32outputBeta, 0, ABS_HOUSEHOLDER_ERROR, REL_HOUSEHOLDER_ERROR);
#else
	close_check_special_f32(referenceFileBeta, f32outputBeta, referenceFileBetaLen, ABS_HOUSEHOLDER_ERROR, REL_HOUSEHOLDER_ERROR);
#endif


	printf("\n== mips_householder_f32 check done  == \n\n");  

// =====================

	printf("== mips_mat_qr_f32 test ==  \n");

    int32_t row, column, rank;
    int nb;
    dimsp = f32dims6;          
    nbMatrixes = paramCountdims6 / 3;
    inp1 = f32input8; 

    f32 *outTaup=f32outputTau;   
    f32 *outRp=f32outputR; 
    f32 *outQp=f32outputQ;  
 
    f32 *pTmpA = f32a2;  
    f32 *pTmpB = f32b3;

    mips_matrix_instance_f32 in1;
    mips_matrix_instance_f32 outR;
    mips_matrix_instance_f32 outQ;  

   (void) outTaup;
   (void) outRp; 
   (void) outQp; 
   (void)nbMatrixes;
   (void)nb;

   nb=0;
   for(int i=0; i < nbMatrixes ; i++)
   //for(int i=0; i < 1 ; i++)
   {
      row = *dimsp++;
      column = *dimsp++;
      rank = *dimsp++;
      (void)rank;

      //printf("--> %d %d\n",nb,i);
      nb += row * column;


      in1.numRows=row;
      in1.numCols=column;
      in1.pData = (f32*)inp1;

      outR.numRows = row;
      outR.numCols = column;
      outR.pData = (f32*)outRp;

      outQ.numRows = row;
      outQ.numCols = row;
      outQ.pData = (f32*)outQp;

    
      mips_status status1=mips_mat_qr_f32(&in1,DEFAULT_HOUSEHOLDER_THRESHOLD_F32,&outR,&outQ,outTaup,pTmpA,pTmpB);
      ASSERT_TRUE(status1==MIPS_MATH_SUCCESS);


      inp1 += row * column;
      outRp += row * column;
      outQp += row * row;
      outTaup += column;

      checkInnerTailOverflow(outRp);
      checkInnerTailOverflow(outQp);
      checkInnerTailOverflow(outTaup);

   }



	printf("mips_mat_qr_f32 finish \n");

	printf("mips_mat_qr_f32 checking \n\n");

#if defined(NOT_EMBEDDED)
	snprintf(referenceFileQ, sizeof(referenceFileQ), "%s%s%s", Patterns_PATH, UnaryF32, "RefQ1_f32.txt");
#else
	referenceFileQ = UnaryF32_RefQ1_f32;
	referenceFileQLen = sizeof(UnaryF32_RefQ1_f32);
    load_data_f32(referenceFileQ, referenceFileQLen, referenceData_f32);
    referenceFileQLen = referenceFileQLen/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFileR, sizeof(referenceFileR), "%s%s%s", Patterns_PATH, UnaryF32, "RefR1_f32.txt");
#else
	referenceFileR = UnaryF32_RefR1_f32;
	referenceFileRLen = sizeof(UnaryF32_RefR1_f32);
    load_data_f32(referenceFileR, referenceFileRLen, referenceData_f32);
    referenceFileRLen = referenceFileRLen/sizeof(f32);
#endif

#if defined(NOT_EMBEDDED)
	snprintf(referenceFileTau, sizeof(referenceFileTau), "%s%s%s", Patterns_PATH, UnaryF32, "RefTau1_f32.txt");
#else
	referenceFileTau = UnaryF32_RefTau1_f32;
	referenceFileTauLen = sizeof(UnaryF32_RefTau1_f32);
    load_data_f32(referenceFileTau, referenceFileTauLen, referenceData_f32);
    referenceFileTauLen = referenceFileTauLen/sizeof(f32);
#endif



#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFileQ, f32outputQ, 0, (f32)SNR_QR_THRESHOLD);
#else
	snr_check_special_f32(referenceFileQ, f32outputQ, referenceFileQLen, (f32)SNR_QR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFileR, f32outputR, 0, (f32)SNR_QR_THRESHOLD);
#else
	snr_check_special_f32(referenceFileR, f32outputR, referenceFileRLen, (f32)SNR_QR_THRESHOLD);
#endif

#if defined(NOT_EMBEDDED)
	snr_check_f32(referenceFileTau, f32outputTau, 0, (f32)SNR_QR_THRESHOLD);
#else
	snr_check_special_f32(referenceFileTau, f32outputTau, referenceFileTauLen, (f32)SNR_QR_THRESHOLD);
#endif


#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFileQ, f32outputQ, 0, ABS_QR_ERROR, REL_QR_ERROR);
#else
	close_check_special_f32(referenceFileQ, f32outputQ, referenceFileQLen, ABS_QR_ERROR, REL_QR_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFileR, f32outputR, 0, ABS_QR_ERROR, REL_QR_ERROR);
#else
	close_check_special_f32(referenceFileR, f32outputR, referenceFileRLen, ABS_QR_ERROR, REL_QR_ERROR);
#endif

#if defined(NOT_EMBEDDED)
	close_check_f32(referenceFileTau, f32outputTau, 0, ABS_QR_ERROR, REL_QR_ERROR);
#else
	close_check_special_f32(referenceFileTau, f32outputTau, referenceFileTauLen, ABS_QR_ERROR, REL_QR_ERROR);
#endif


	printf("\n== mips_mat_qr_f32 check done  == \n\n");  

// =====================


return 0;



}