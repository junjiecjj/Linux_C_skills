
#ifndef _MatrixAnalysis_CJJ
#define _MatrixAnalysis_CJJ




#include "StdAfx.h"
#include "Utility.h"
#include "SortAlgorithms.h"


#define PI            3.14159265358979
#define SMALLPROB     1.0e-12
#define DBL_MAX       1.0e+300
#define MONTHS        12
#define SIZE          4


#ifdef __cplusplus
extern "C" {
#endif


// 此 MatrixAnalysis.h 和.cpp 主要是实现了矩阵的相关计算，如:求行列式，逆，伴随矩阵，LU分解，SVD分解，QR分解，范数，矩阵微分，求广义逆矩阵，解线性方程组，特殊矩阵，FFT等。


#define MAX 200  //最大计算阶数，可以更改

#define EPS  1e-20



/****************************************************************************************************************************************************************************
矩阵相关，求行列式
****************************************************************************************************************************************************************************/


double Determinant(double  **arr, int order);                    // 求矩阵的行列式, 递归求解
double Cofactor(double  **arr, int order, int raw, int col);     // 求矩阵的余子式, 递归求解




double DeterminantGaussNormal(double **arr, int order);         // 普通 gaussian 求行列式
double DeterminantGaussColPrime(double **arr, int order);       // 列主元 gaussian 求行列式
double DeterminantGaussGlobPrime(double **arr, int order);      // 全主元 gaussian 求行列式


void swap(double* a,double*b);
void SwapArrCol(double **arr, int col_a, int col_b, int order);  // 交换矩阵的两列
void SwapArrRaw(double **arr, int raw_a, int raw_b, int order);  // 交换矩阵的两行


/****************************************************************************************************************************************************************************
矩阵相关，求矩阵的逆
****************************************************************************************************************************************************************************/

void InverseGauss(double **matrix, double **inverse, int order);

/****************************************************************************************************************************************************************************
矩阵相关，解线性方程组
****************************************************************************************************************************************************************************/

void LinalgSolve(double **A, double *b, int order);

//================================================================


/****************************************************************************************************************************************************************************
矩阵相关，求矩阵的LV 分解
****************************************************************************************************************************************************************************/

void DecompositionLU_Crout(double **arr, double **Larr, double **Uarr, int order); //  矩阵的 LU Crout 分解
void DecompositionLU_Doolittle(double **arr, double **Larr, double **Uarr, int order);  // 矩阵的 LU Doolittle 分解;



/****************************************************************************************************************************************************************************
矩阵相关，求矩阵的 QR分解
****************************************************************************************************************************************************************************/
void DecompositionQR_Householder(double **arr, double **Qarr, double **Rarr, int order);                             //  矩阵的 QR 分解
void DecompositionQR_Givens(double **arr, double **Qarr, double **Rarr, int order);                                  //  矩阵的 QR 分解


/****************************************************************************************************************************************************************************
矩阵相关，求矩阵的 SVD分解
****************************************************************************************************************************************************************************/
int DecompositionSVD(double **arr, double **Uarr, double **Sigma, double **Varr,  int arr_raw_num, int arr_col_num); //  矩阵的 SVD 分解



/****************************************************************************************************************************************************************************
矩阵相关，求实对称矩阵的 特征值和特征向量
****************************************************************************************************************************************************************************/
void EigenValueVectors_Jacobi(double **arr, double *EigenValue, double **EigenVec, int order, double eps, int maxiternum);







#ifdef __cplusplus
};
#endif



#endif  //  _Utility_CJJ