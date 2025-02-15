


#include "MatrixAnalysis.h"




/****************************************************************************************************************************************************************************
矩阵相关，求行列式
****************************************************************************************************************************************************************************/


// 递归计算行列式,当 order 超过10时不适用, 计算时间指数级, 一般都用Gauss消元法.
double Determinant(double **arr, int order)
{
    double  sum = 0;//i是第一行的列指标，M是余子式的值，sum是行列式的计算值

	if (order == 1)//一阶行列式直接得出结果
		return arr[0][0];
	else if (order > 1)
	{
        // printf("here!!!\n");
		for (int i = 0; i < order; i++)//按第一行展开
		{
			sum += 1.0 * pow(-1, i+2) * arr[0][i] * Cofactor(arr, order, 0, i);
		}
	}
	return sum;
}


/**************************************************************
功能:递归计算 arr 的 row 行 col 列的余子式. 基本不用，一般都用Gauss消元法.
**************************************************************/
double Cofactor(double **arr, int order, int row, int col)
{

    double result = 0;
	double  **arr2;
    int origin_i, origin_j, r, c;

    //分配内存
    arr2 = (double **)malloc((order-1) * sizeof(double *));  //每一行的首地址分配内存，不一定连续
    for (int i = 0; i < order-1; i++)
    {
        arr2[i] = (double *)malloc((order-1) * sizeof(double)); //每一行一定连续
    }

	//以下为构造余子式的过程。由于C语言的特性，这个过程会比较复杂，需要观察余子式与原行列式的关系。
    for (int i = 0; i < order; i++)
    {
        for (int j = 0; j < order; j++)
        {
            origin_i = i;
            origin_j = j;
            if(i == row || j == col);
            else
            {
                if(i > row)
                    i --;
                if(j > col)
                    j --;
                arr2[i][j] = arr[origin_i][origin_j];
                i = origin_i;
                j = origin_j;
            }
        }
    }
    // printf("order : %d\n", order-1);
    // Display2DFloatArray2DPoint(order-1, order-1, arr2);


    if(order >= 2)
    {
        result = Determinant(arr2, order - 1);//构造完后，余子式是一个新的行列式，返回DET函数进行计算。
    }

    // 释放内存
    for(int i=0;  i < order-1; ++i){
        free(arr2[i]);
        arr2[i] = NULL;
    }
    free(arr2);
    arr2 = NULL;

	return result;
}


void swap(double* a, double*b)
{
	double tmp = *a;
	*a = *b;
	*b = tmp;
}

// 交换矩阵的两列
void SwapArrCol(double **arr, int col_a, int col_b, int order)
{

	for(int i = 0; i < order; i++)
		swap(&arr[i][col_a], &arr[i][col_b]);
}


// 交换矩阵的两行
void SwapArrRaw(double **arr, int raw_a, int raw_b, int order)
{
	for(int i = 0; i < order; i++)
		swap(&arr[raw_a][i], &arr[raw_b][i]);
}

/**********************************************************************************************
https://blog.csdn.net/Dream_wave/article/details/119192417
数学知识:
矩阵行列式的初等行变换：
1）换行变换：交换两行（行列式需变号）
2）倍法变换：将行列式的某一行（列）的所有元素同乘以数k（行列式需乘K倍）
3）消法变换：把行列式的某一行（列）的所有元素乘以一个数k并加到另一行（列）的对应元素上（行列式不变）

这里要用到几个性质：
1） 矩阵的某行或某列全部元素乘上一个常数，则行列式的值也乘上这个常数。
2） 矩阵的某行（列）全部加上另一行（列）的元素*常数，行列式的值不变。
3） 下（上）三角矩阵的行列式等于其对角线元素的乘积。
4） 矩阵的某行或某列全为零，行列式为零。
5） 转置不改变行列式。
6） 交换两行或两列，行列式取相反数。
7) 若行列式的两行或者两列成比例，则行列式为0.

其中 1)会使矩阵的行列式的值反号;  2)会使得行列式的值变为 k*|A|;  3) 不改变行列式的值.
因此我们主要使用 1)和3) 化简矩阵，需要记录操作 1) 的总次数，包括行交换次数a 和 列交换的次数 b, 使得其变为对角阵, 然后对角相乘，再乘以 (-1)^(a+b) 得到最后的结果;

注意: 高斯消元法也分为 普通的高斯消元法 和 列主元的高斯消元法  和 全主元的高斯消元法，这里是普通的消元法;

方法一: 普通的消元法
功能: 利用普通的高斯消元法计算行列式：
1) 首先输入矩阵A;
2) 对于 A[i][i]的对角元素，找到第 i 行第一个不为0的元素的列 j, 以A[i][j]为主元，交换A[:][i] 和 A[:][j], 即交换A的第 i 和 j 列;
3) 消去 >i 的所有行的第 i 个元素;

重复以上过程，得到三角矩阵，对角元素乘积 再乘以 列交换的次数 就是行列式的值;
*****************************************************************************************/

double DeterminantGaussNormal(double **matrix, int order)
{
    int k;
	int n;				    // 阶数
	int sign = 0;			// 行列式交换一次需要改变符号，此变量记录交换次数
	double tmp;			    // 暂存乘积因子
    double tmpvalue;        // 暂存矩阵的值
	double sum = 1.0;       // 结果

    // 检查指针是否为空
    if(matrix == NULL){
        printf("error:数组为空, [file:%s,fun:%s, Line:%d ] \n\n", __FILE__, __func__, __LINE__);
        exit(EXIT_FAILURE);
    }


    //========================================================================
    // 为了消元过程不影响原 matrix, 先分配内存并拷贝数值;
    //========================================================================
    double **arr;
    arr = (double **)malloc(order * sizeof(double *));
    for (int i = 0; i < order; i++)
    {
        arr[i] = (double *)malloc(order * sizeof(double));
    }
    // 拷贝矩阵数值
	for (int i = 0; i < order; i++) {
		for (int j = 0; j < order; j++) {
			arr[i][j] = matrix[i][j];
		}
	}

    // 开始消元
	for(int i = 0; i < order - 1; i++){// 遍历对角线, 消元是以对角线为主轴的.
		k = 1;
		while(arr[i][i] == 0.0 && i+k < order){	     //确保标准数不为0. 寻找第i行的第一个不为0 的元素的列，并交换i 和 j列.
			// SwapArrCol(arr, i, i+(k++), order);
            for(int raw = 0; raw < order; raw++){
                tmpvalue = arr[raw][i];
                arr[raw][i] = arr[raw][i+k];
                arr[raw][i+k] = tmpvalue;
            }
            k++;
			sign++;
		}
        // printf("sign = %d\n", sign);
		if(arr[i][i] == 0.0 && i+k == order){		// 若整个一行都为0, 则结果为0, 结束;
			// printf("0");
			return 0;
		}
		for(int j = i + 1; j < order; j++){     // 开始消去i行后的每一行;
			if(arr[j][i] == 0.0){			    // 如 j 行的第 i 列元素为0, 则那一行不用化简;
				continue;
            }
			else{
				tmp = -(double)arr[j][i]/arr[i][i];		    // 保存乘积因子;
				for(k = i; k < order; k++)                  // 消去第 j 行的每一列元素;
					arr[j][k] += (tmp*arr[i][k]);
			}
		}

	}
	for(int i = 0; i < order; i++)
		sum *= arr[i][i];
    sum = sum * pow(-1, sign); // 考虑列交换的次数

    //================ 释放内存 ======================
    for(int i = 0;  i < order; ++i){
        free(arr[i]);
        arr[i] = NULL;
    }
    free(arr);

	return sum;
}

/********************************************************************************************
注意: 高斯消元法也分为 普通的高斯消元法 和 列主元的高斯消元法  和 全主元的高斯消元法，这里是列主元 的消元法;

方法二: 列主元 的消元法
功能: 利用 列主元 的高斯消元法计算行列式：
整体流程与代码
1）判断传入指针是否为空
2）判断矩阵维数，判断是否为方阵
3）为临时矩阵开辟空间
4）将原矩阵数据拷贝到临时矩阵中（保护原矩阵）
5）选择主元：利用初等行变换，找出每列绝对值最大的数，与主元行互换（1.提高一定的精度 2.避免原函数主对角线有0）
6）利用初等行变换进行消0

高斯消去法在消元过程中可能出现零主元，即，这时消元过程将无法进行；也可能主元绝对值非常小，用它做除法将会导致舍入误差的扩散，使数值解不可靠。解决该问题的办法是避免使用绝对值过小的元素作主元。
选择主元的方法：
1）找到主对角线以下每列最大的数Max所在的行数k
2）利用初等行变换——换行变换，将k行与当前主元行互换（记录总共换行次数n）
3）以当前主元行为基，利用初等行变换——消法变换，将主对角线下方消0
4）行列式每次换行需变号，行列式最后的符号为
5）每次进行高斯消去前都必须选择主元，计算n维的行列式，则需要进行n-1次主元选择.
*****************************************************************************************/
double DeterminantGaussColPrime(double **matrix, int order)
{
    int k;
    int maxrow;             // 暂存主元的行号
    double maxval;             // 暂存对角线及以下元素的最大值

	int sign = 0;			 // 行列式交换一次需要改变符号，此变量记录交换次数
	double tmp = 0;			 // 暂存乘积因子
    double tmpv = 0;         // 暂存元素值
	double sum = 1.0;        // 结果

    // 检查指针是否为空
    if(matrix == NULL){
        printf("error:数组为空, [file:%s,fun:%s, Line:%d ] \n\n", __FILE__, __func__, __LINE__);
        exit(EXIT_FAILURE);
    }


    //=======================================================
    // 为了消元过程不影响matrix, 先分配内存并拷贝数值;
    //=======================================================
    double **arr;
    arr = (double **)malloc(order * sizeof(double *));     // 每一行的首地址分配内存，不一定连续
    for (int i = 0; i < order; i++)
    {
        arr[i] = (double *)malloc(order * sizeof(double)); // 每一行一定连续
    }

	for (int i = 0; i < order; i++) {
		for (int j = 0; j < order; j++) {
			arr[i][j] = matrix[i][j];
		}
	}
    // printf("拷贝的 %d × %d 矩阵:\n",order,order);
    // Display2DFloatArray2DPoint(order, order, arr);

    //================================================================
    for(int i = 0; i < order - 1; ++i){// 遍历对角线, 消元是以对角线为主轴的.

        maxval = fabs(arr[i][i]);
        maxrow = i;
        for(int j = i + 1; j < order; ++j ){ // 寻找 第 i 列的 >= i+1 中的最大元素的行.
            if( fabs(arr[j][i]) > maxval ){
                maxrow = j;
                maxval = fabs(arr[j][i]);
            }
        }
        // printf("i = %d, maxrow = %d\n", i, maxrow);

        if(maxval == 0.0)
        {
            printf("zero colum\n");
            return 0;
        }
        if(maxrow > i){
            for(int j = 0; j < order; ++j) // 交换行
            {
                tmpv = arr[i][j];
                arr[i][j] = arr[maxrow][j];
                arr[maxrow][j] = tmpv;
            }
            sign++;
        }

        for(int k = i + 1; k < order; ++k) // 消元
        {
            if(arr[k][i] == 0.0){
                continue;
            }
            else{
                tmp = -(double)arr[k][i]/arr[i][i];;
                for(int j = i; j < order; ++j){
                    arr[k][j] += tmp*arr[i][j];
                }
            }
        }
    }

	for(int i = 0; i < order; i++)
		sum *= arr[i][i];
    sum = sum * pow(-1, sign); // 考虑列交换的次数


    //======================================
    // 释放内存
    //======================================
    for(int i = 0;  i < order; ++i){
        free(arr[i]);
        arr[i] = NULL;
    }
    free(arr);

	return sum;

}


/******************************************************************************************
注意: 高斯消元法也分为 普通的高斯消元法 和 列主元的高斯消元法  和 全主元的高斯消元法，这里是列主元 的消元法;

方法二: 列主元 的消元法
功能: 利用 列主元 的高斯消元法计算行列式：
整体流程与代码
1）判断传入指针是否为空
2）判断矩阵维数，判断是否为方阵
3）为临时矩阵开辟空间
4）将原矩阵数据拷贝到临时矩阵中（保护原矩阵）
5）选择主元：利用初等行变换，找出当前对角线元素右下角(包括自己)绝对值最大的数，与主元行互换（1.提高一定的精度 2.避免原函数主对角线有0）
6）利用初等行变换进行消0

*****************************************************************************************/
double DeterminantGaussGlobPrime(double **matrix, int order)
{
    int k;
    int maxrow;             // 暂存主元的行号
    int maxcol;             // 暂存主元的列号
    double maxval;             // 暂存对角线及以下元素的最大值

	int sign = 0;			// 行列式交换一次需要改变符号，此变量记录交换次数
	double tmp = 0;			    // 暂存乘积因子
    double tmpv = 0;            // 暂存元素值
	double sum = 1.0;       // 结果

    // 检查指针是否为空
    if(matrix == NULL){
        printf("error:数组为空, [file:%s,fun:%s, Line:%d ] \n\n", __FILE__, __func__, __LINE__);
        exit(EXIT_FAILURE);
    }

    //=======================================================
    // 为了消元过程不影响matrix, 先分配内存并拷贝数值;
    //=======================================================
    double **arr;
    arr = (double **)malloc(order * sizeof(double *));     // 每一行的首地址分配内存，不一定连续
    for (int i = 0; i < order; i++)
    {
        arr[i] = (double *)malloc(order * sizeof(double)); // 每一行一定连续
    }

	for (int i = 0; i < order; i++) {
		for (int j = 0; j < order; j++) {
			arr[i][j] = matrix[i][j];
		}
	}
    // printf("拷贝的 %d × %d 矩阵:\n",order,order);
    // Display2DFloatArray2DPoint(order, order, arr);

    //================================================================
    for(int i = 0; i < order - 1; ++i){// 遍历对角线, 消元是以对角线为主轴的.

        maxval = fabs(arr[i][i]);
        maxrow = i;
        maxcol = i;
        // 找到当前对角线主元右下角(包括自己)所有元素中的最大的元素的行和列
        for(int j = i; j < order; ++j ){
            for(int k = i; k < order; ++k){
                if( fabs(arr[j][k]) > maxval ){
                    maxrow = j;
                    maxcol = k;
                    maxval = fabs(arr[j][i]);
                }
            }
        }
        // printf("i = %d, maxrow = %d, maxcol = %d\n", i, maxrow, maxcol);

        if(maxval == 0.0)
        {
            // printf("max value is zero, exit \n");
            return 0;
        }
        // 交换行
        if(maxrow > i){
            for(int j = 0; j < order; ++j)
            {
                tmpv = arr[maxrow][j];
                arr[maxrow][j] = arr[i][j];
                arr[i][j] = tmpv;
            }
            sign++;
        }
        // 交换列
        if(maxcol > i){
            for(int j = 0; j < order; ++j)
            {
                tmpv = arr[j][maxcol];
                arr[j][maxcol] = arr[j][i];
                arr[j][i] = tmpv;
            }
            sign++;
        }

        for(int k = i + 1; k < order; ++k){
            if(arr[k][i] == 0.0){
                continue;
            }
            else{
                tmp = -(double)arr[k][i]/arr[i][i];;
                for(int j = i; j < order; ++j){
                    arr[k][j] += tmp*arr[i][j];
                }
            }
        }
    }

	for(int i = 0; i < order; i++)
		sum *= arr[i][i];
    sum = sum * pow(-1, sign); // 考虑列交换的次数

    //======================================
    // 释放内存
    //======================================
    for(int i = 0;  i < order; ++i){
        free(arr[i]);
        arr[i] = NULL;
    }
    free(arr);

	return sum;
}



/****************************************************************************************************************************************************************************
矩阵相关，求矩阵的逆
****************************************************************************************************************************************************************************/


/****************************************************************************************************************
功能: 利用高斯消元法计算矩阵的逆矩阵;
注意: 高斯消元法也分为  列主元的高斯消元法  和 全主元的高斯消元法，全主元的高斯消元法需要记录列交换的结果以后续的恢复顺序，相对麻烦。这里是列主元的高斯消元法。

矩阵的初等变换又分为矩阵的初等行变换和矩阵的初等列变换。矩阵的初等行变换和初等列变换统称为初等变换。另外：分块矩阵也可以定义初等变换。
定义：如果B可以由A经过一系列初等变换得到，则称矩阵A与B称为等价。

数域V上的矩阵具有以下三种行变换：
1）以V中一个非零的数，乘以矩阵的某一行
2）把矩阵的某一行的a倍加到另一行(a∈V)
3）互换矩阵中两行的位置
矩阵A通过以上三种行变换变成矩阵B，称为A→B

主元就是在矩阵消去过程中，每列的要保留的非零元素，用它可以把该列其他消去。在阶梯型矩阵中，主元就是每个非零行第一个非零元素就是主元。
选择主元的方法：

1）找到主对角线以下每列最大的数Max所在的行数k
2）利用初等行变换——换行变换，将k行与当前主元行互换（记录总共换行次数n）
3）以当前主元行为基，利用初等行变换——消法变换，将主对角线上下方消0
4）行列式每次换行需变号，行列式最后的符号为
5）每次进行高斯消去前都必须选择主元，计算n维的行列式，则需要进行n-1次主元选择



数学知识: 对于阶数为 n 的矩阵A，求它的逆矩阵可以如下:
1) 构造矩阵 B = [A, I]_{nx2n} .
2） 只能利用初等行变换将 B 化简为 B = [I, A^-1]的形式 .
3) B 的右部分就是 A 的逆矩阵.

整体流程：
1）判断传入指针是否为空，判断矩阵是否为方针
2）为增广矩阵、输出的逆矩阵开辟空间，并初始化为0
3）将原矩阵中的数据拷贝到增广矩阵中，并将增广矩阵右侧化为单位阵
4）逐列开始，选择主元，将其他位置化为0，每列阶梯位置化为1
6）将增广矩阵右侧的逆矩阵拷贝到输入矩阵中，并释放增广矩阵内存


初等变换法是常用的矩阵求逆方法之一。
相对于伴随法，初等行变换法有着较低的时间复杂度，可以进行相对高维的矩阵运算，但同时也会损失一点点精度。


输入:
    matrix:原矩阵
    inverse: 逆矩阵
*********************************************************************************************************************/
void InverseGauss(double **matrix, double **inverse, int order)
{
    int k;
    int maxrow;             // 暂存主元的行号
    int maxcol;             // 暂存主元的列号
    double maxval;             // 暂存对角线及以下元素的最大值

	int sign = 0;			// 行列式交换一次需要改变符号，此变量记录交换次数
	double tmp = 0;			    // 暂存乘积因子
    double tmpv = 0;            // 暂存元素值
	double sum = 1.0;       // 结果

    // 检查指针是否为空
    if(matrix == NULL){
        printf("error:数组为空, [file:%s,fun:%s, Line:%d ] \n\n", __FILE__, __func__, __LINE__);
        exit(EXIT_FAILURE);
    }

    //================================================================================
    // 为了消元过程不影响matrix, 先分配内存并拷贝数值;
    //================================================================================
    double **augmentArr;
    augmentArr = (double **)malloc(order * sizeof(double *));            // 每一行的首地址分配内存，不一定连续
    for (int i = 0; i < order; i++){
        augmentArr[i] = (double *)malloc(2 * order * sizeof(double));   // 每一行一定连续
        memset(augmentArr[i], 0,  2 * order * sizeof(double));          // 初始化
    }

	for (int i = 0; i < order; i++) {
        // // 进行数据拷贝，方法一
		// for (int j = 0; j < order; j++) {
		// 	augmentArr[i][j] = matrix[i][j];
		// }
        // 进行数据拷贝,方法二
        memcpy(augmentArr[i], matrix[i], sizeof(augmentArr[0][0]) * order);


        //将增广矩阵右侧变为单位阵
        augmentArr[i][order + i] = 1;
	}

    // printf("拷贝的 %d × %d 矩阵:\n",order,order);
    // Display2DFloatArray2DPoint(order, 2 * order, augmentArr);

    //================================================================
    for(int i = 0; i < order; ++i){// 遍历对角线, 消元是以对角线为主轴的.

        //  整理增广矩阵，选主元
        maxrow = i;
        maxval = fabs(augmentArr[maxrow][i]);

        for(int j = i; j < order; ++j ){
            if(fabs(augmentArr[j][i]) > maxval){
                maxrow = j;
                maxval = fabs(augmentArr[j][i]);
            }
        }
        // printf("i = %d, maxrow = %d, maxcol = %d, maxval = %lf\n", i, maxrow, maxcol, maxval);


        if(maxval == 0.0)
        {
            printf("error: 某列最大值为0, 不可逆, [file:%s,fun:%s, Line:%d ] \n\n", __FILE__, __func__, __LINE__);
            exit(EXIT_FAILURE);
        }
        if(maxrow != i){
            for(int k = 0; k < 2 * order; ++k)
            {
                tmpv = augmentArr[maxrow][k];
                augmentArr[maxrow][k] = augmentArr[i][k];
                augmentArr[i][k] = tmpv;
            }
            sign++;
        }

        // 将每列其他元素化0
        for(int k = 0; k < order; ++k){
            if(k == i || augmentArr[k][i] == 0.0){
                continue;
            }
            else{
                tmp = -(double)augmentArr[k][i]/augmentArr[i][i];;
                for(int j = 0; j < 2 * order; ++j){
                    augmentArr[k][j] += tmp*augmentArr[i][j];
                }
            }
        }

        tmp = 1.0/augmentArr[i][i];
        for(int j = 0; j < 2 * order; ++j){
            augmentArr[i][j] *= tmp;
        }
    }

    // // 将逆矩阵部分拷贝到 inverse 中，方法一
    // for(int i = 0; i < order; ++i){
    //     for(int j = 0; j < order; ++j){
    //         inverse[i][j] = augmentArr[i][j+order];
    //     }
    // }
    // 将逆矩阵部分拷贝到 inverse 中, 方法二，内存拷贝
    for(int i = 0; i < order; ++i){
        memcpy(inverse[i], augmentArr[i] + order, sizeof(augmentArr[0][0]) * order);
    }

    //======================================
    // 释放内存
    //======================================
    for(int i = 0;  i < order; ++i){
        free(augmentArr[i]);
        augmentArr[i] = NULL;
    }
    free(augmentArr);
}


/****************************************************************************************************************************************************************************
矩阵相关，解线性方程组
****************************************************************************************************************************************************************************/

/*****************************************************************************************
功能: 利用高斯消元法求解线性方程组;
注意: 高斯消元法也分为 普通的高斯消元法 和 列主元的高斯消元法  和 全主元的高斯消元法，这里是

数学知识: 对于阶数为 n 的矩阵A，求它的逆矩阵可以如下:
1) 构造矩阵 B = [A, I]_{nx2n}
2） 只能利用初等行变换将 B 化简为 B = [I, A^-1]的形式
3) B 的右部分就是 A 的逆矩阵.

*****************************************************************************************/
void LinalgSolve(double **A, double *b, int order)
{


}


/****************************************************************************************************************************************************************************
功能: 矩阵的LU分解

A = LU
如果方针A可以分解为一个下三角矩阵L和一个上三角矩阵U的乘积，则称A可以作三角分解或LU分解；

如果L是单位下三角阵， U是上三角矩阵，此时的三角分解称为杜立特分解(Doolittle)；
如果L是下三角矩阵，U是单位上三角矩阵，此时的三角分解成为克劳特分解(Crout);

输入:
    arr：待分解矩阵
    order: 矩阵的阶
    Larr：分解后的 L 下三角矩阵
    Uarr: 分解后的 U 上三角矩阵

****************************************************************************************************************************************************************************/
void DecompositionLU_Crout(double **arr, double **Larr, double **Uarr, int order) //  矩阵的 LU 分解
{
    if(arr == NULL){
        printf("error:数组为空, [file:%s,fun:%s, Line:%d ] \n\n", __FILE__, __func__, __LINE__);
        exit(EXIT_FAILURE);
    }
    double tmpsum = 0;

    for(int i = 0; i<order; i++){
        for(int j = 0; j < order; ++j){
            Larr[i][j] = 0;
            Uarr[i][j] = 0;
        }
        Uarr[i][i] = 1;
    }
    for(int k = 0; k < order; ++k){
        // 计算Larr的第 k 列;
        for(int i = k; i < order; ++i){
            Larr[i][k] = arr[i][k];
            for(int j = 0; j <= k - 1; ++j)
            {
                Larr[i][k] -= (Larr[i][j]*Uarr[j][k]);
            }
        }
        // 计算Uarr的 第 k 行;
        for(int i = k + 1; i < order; ++i){
            Uarr[k][i] = arr[k][i];
            for(int j = 0; j <= k -1; ++j){
                Uarr[k][i] -= Larr[k][j] * Uarr[j][i];
            }
            Uarr[k][i] /= Larr[k][k];
        }
    }
}

// 矩阵的杜立特分解(Doolittle)；
void DecompositionLU_Doolittle(double **arr, double **Larr, double **Uarr, int order) //  矩阵的 LU 分解
{
    if(arr == NULL){
        printf("error:数组为空, [file:%s,fun:%s, Line:%d ] \n\n", __FILE__, __func__, __LINE__);
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i<order; i++){
        for(int j = 0; j < order; ++j){
            Larr[i][j] = 0;
            Uarr[i][j] = 0;
        }
        Larr[i][i] = 1;
    }

    for(int i = 0; i<order; i++){
        Larr[i][i] = 1 ;
    }

    for(int k = 0; k < order; ++k){
        // 计算Uarr的第 k 行;
        for(int i = k; i < order; ++i){
            Uarr[k][i] = arr[k][i];
            for(int j = 0; j <= k - 1; ++j)
            {
                Uarr[k][i] -= (Larr[k][j]*Uarr[j][i]);
            }
        }
        // 计算 Larr的 第 k 列;
        for(int i = k + 1; i < order; ++i){
            Larr[i][k] = arr[i][k];
            for(int j = 0; j <= k -1; ++j){
                Larr[i][k] -= Larr[i][j] * Uarr[j][k];
            }
            Larr[i][k] /= Uarr[k][k];
        }
    }
}

/****************************************************************************************************************************************************************************
矩阵相关，求矩阵的 QR分解
****************************************************************************************************************************************************************************/

//  矩阵的 QR 分解, Householder方法
void DecompositionQR_Householder(double **arr, double **Qarr, double **Rarr, int order)
{

}

//  矩阵的 QR 分解， Givens方法
void DecompositionQR_Givens(double **arr, double **Qarr, double **Rarr, int order)
{

}


/****************************************************************************************************************************************************************************
矩阵相关，求矩阵的 SVD分解

功能: 矩阵的SVD分解

输入:
    Arr: row_num x col_num的二维矩阵

输出:
    Uarr: row_num x row_num 的二维矩阵
    Sigma: row_num x col_num 的二维矩阵
    Varr: col_num x col_num 的二维矩阵
    eigvalue_num: Sigma非零的特征值个数

https://blog.csdn.net/chenaiyanmie/article/details/80011244?spm=1001.2101.3001.6650.6&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7ERate-6-80011244-blog-122266936.235%5Ev27%5Epc_relevant_multi_platform_whitelistv3&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7ERate-6-80011244-blog-122266936.235%5Ev27%5Epc_relevant_multi_platform_whitelistv3&utm_relevant_index=9


https://zhuanlan.zhihu.com/p/122259109

https://zhuanlan.zhihu.com/p/480389473

https://taotaoiit.blog.csdn.net/article/details/125237191?spm=1001.2101.3001.6650.5&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7ERate-5-125237191-blog-122266936.235%5Ev27%5Epc_relevant_multi_platform_whitelistv3&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7ERate-5-125237191-blog-122266936.235%5Ev27%5Epc_relevant_multi_platform_whitelistv3&utm_relevant_index=8

****************************************************************************************************************************************************************************/

int DecompositionSVD(double **Aarr, double **Uarr, double **Sigma, double **VarrT,  int row_num, int col_num) //  矩阵的 SVD 分解
{
    int eigvalue_num = 0;
    double eps = 1e-40;//误差
    int iter_max_num = 10000;//迭代总次数

	if (Aarr == NULL || Uarr == NULL || VarrT == NULL || Sigma == NULL )
	{
		printf("error: 数组为空, [file:%s,fun:%s, Line:%d ] \n\n", __FILE__, __func__, __LINE__);
		exit(EXIT_FAILURE);
	}


    for(int i = 0; i < row_num; ++i){
        for(int j = 0; j < col_num; ++j){
            Sigma[i][j] = 0;
        }
    }

    for(int i = 0; i < row_num; ++i){
        for(int j = 0; j < row_num; ++j){
            Uarr[i][j] = 0;
        }
    }

    for(int i = 0; i < col_num; ++i){
        for(int j = 0; j < col_num; ++j){
            VarrT[i][j] = 0;
        }
    }

    // printf("A 为:\n");
    // Display2DDoubleArray2DPoint(row_num, col_num, Aarr);

    // 为特征向量组 分配临时内存
    double **EigenVec;
    EigenVec = malloc2DDouble(col_num, col_num);
    printf("EigenVec  1 为:\n");
    Display2DDoubleArray2DPoint(col_num, col_num, EigenVec);

    // EigenVec = (double **)malloc(col_num * sizeof(double *));
	// if (EigenVec == NULL)
	// {
	// 	printf("error :申请数组内存空间失败 [file:%s,fun:%s, Line:%d ] \n\n", __FILE__, __func__, __LINE__);
	// 	exit(EXIT_FAILURE);
	// }
    // for (int i = 0; i < col_num; i++)
    // {
    //     EigenVec[i] = (double *)malloc(col_num * sizeof(double));
	// 	if (EigenVec[i] == NULL)
	// 	{
	// 		printf("error :申请数组子内存空间失败 [file:%s,fun:%s, Line:%d ] \n\n", __FILE__, __func__, __LINE__);
	// 		exit(EXIT_FAILURE);
	// 	}
    // }

    // 特征值, 临时
    double *EigenValue;
    EigenValue = (double *)malloc(col_num * sizeof(double));
    if (EigenVec == NULL)
    {
        printf("error :申请数组子内存空间失败 [file:%s,fun:%s, Line:%d ] \n\n", __FILE__, __func__, __LINE__);
        exit(EXIT_FAILURE);
    }

    // 为A^TA分配内存, 临时
    double **ATA;
    ATA = malloc2DDouble(col_num, col_num);
    // ATA = (double **)malloc(col_num * sizeof(double *));
	// if (ATA == NULL)
	// {
	// 	printf("error :申请数组内存空间失败 [file:%s,fun:%s, Line:%d ] \n\n", __FILE__, __func__, __LINE__);
	// 	exit(EXIT_FAILURE);
	// }
    // for (int i = 0; i < col_num; i++)
    // {
    //     ATA[i] = (double *)malloc(col_num * sizeof(double));
	// 	if (ATA[i] == NULL)
	// 	{
	// 		printf("error :申请数组子内存空间失败 [file:%s,fun:%s, Line:%d ] \n\n", __FILE__, __func__, __LINE__);
	// 		exit(EXIT_FAILURE);
	// 	}
    // }

    // 为A的转置分配内存, 临时
    double **transArr;
    transArr = malloc2DDouble(col_num, row_num);
    // transArr = (double **)malloc(col_num * sizeof(double *));
	// if (transArr == NULL)
	// {
	// 	printf("error :申请数组内存空间失败 [file:%s,fun:%s, Line:%d ] \n\n", __FILE__, __func__, __LINE__);
	// 	exit(EXIT_FAILURE);
	// }
    // for (int i = 0; i < col_num; i++)
    // {
    //     transArr[i] = (double *)malloc(row_num * sizeof(double));
	// 	if (transArr[i] == NULL)
	// 	{
	// 		printf("error :申请数组子内存空间失败 [file:%s,fun:%s, Line:%d ] \n\n", __FILE__, __func__, __LINE__);
	// 		exit(EXIT_FAILURE);
	// 	}
    // }

    // 为 Sigma 的转置的倒数分配内存, 临时.
    double **transSigma;
    transSigma = malloc2DDouble(col_num, row_num);
    // transSigma = (double **)malloc(col_num * sizeof(double *));
	// if (transSigma == NULL)
	// {
	// 	printf("error :申请数组内存空间失败 [file:%s,fun:%s, Line:%d ] \n\n", __FILE__, __func__, __LINE__);
	// 	exit(EXIT_FAILURE);
	// }
    // for (int i = 0; i < col_num; i++)
    // {
    //     transSigma[i] = (double *)malloc(row_num * sizeof(double));
	// 	if (transSigma[i] == NULL)
	// 	{
	// 		printf("error :申请数组子内存空间失败 [file:%s,fun:%s, Line:%d ] \n\n", __FILE__, __func__, __LINE__);
	// 		exit(EXIT_FAILURE);
	// 	}
    // }
    // // 初始化
    // for(int i = 0; i < col_num; ++i){
    //     for(int j = 0; j < row_num; ++j){
    //         transSigma[i][j] = 0;
    //     }
    // }

    // 为 A*V 分配内存, 临时.
    double **AV;
    AV = malloc2DDouble(row_num, col_num);
    // AV = (double **)malloc(row_num * sizeof(double *));
	// if (AV == NULL)
	// {
	// 	printf("error :申请数组内存空间失败 [file:%s,fun:%s, Line:%d ] \n\n", __FILE__, __func__, __LINE__);
	// 	exit(EXIT_FAILURE);
	// }
    // for (int i = 0; i < row_num; i++)
    // {
    //     AV[i] = (double *)malloc(col_num * sizeof(double));
	// 	if (AV[i] == NULL)
	// 	{
	// 		printf("error :申请数组子内存空间失败 [file:%s,fun:%s, Line:%d ] \n\n", __FILE__, __func__, __LINE__);
	// 		exit(EXIT_FAILURE);
	// 	}
    // }

    Transpose2DDoubleMatrix(Aarr, transArr, row_num, col_num);
    // printf("AT  为:\n");
    // Display2DDoubleArray2DPoint(col_num, row_num, transArr);

    MatrixMultiplyDouble(transArr, col_num, row_num, Aarr, row_num, col_num, ATA);

    // printf("ATA 为:\n");
    // Display2DDoubleArray2DPoint(col_num, col_num, ATA);

    EigenValueVectors_Jacobi(ATA, EigenValue, EigenVec, col_num, eps, iter_max_num);


    eigvalue_num = 0;
    for(int i = 0; i < col_num; ++i){
        if( fabs(EigenValue[i]) > 1e-10){
            eigvalue_num++;
        }
        else{
            break;
        }
    }

    for(int i = 0; i < col_num; ++i){
        for(int j = 0; j < col_num; ++j){
            VarrT[i][j] = EigenVec[j][i];
        }
    }

    printf("eigvalue_num = %d\n", eigvalue_num);

    for(int i = 0; i < eigvalue_num; ++i){
        Sigma[i][i] = sqrt(EigenValue[i]);
        transSigma[i][i] = 1.0/sqrt(EigenValue[i]);
    }

    // printf("Sigma.T 为:\n");
    // Display2DDoubleArray2DPoint(col_num, row_num, transSigma);

    MatrixMultiplyDouble(Aarr, row_num, col_num, EigenVec, col_num, col_num, AV);
    MatrixMultiplyDouble(AV, row_num, col_num, transSigma, col_num, row_num, Uarr);



    // printf("Uarr 为:\n");
    // Display2DDoubleArray2DPoint(row_num, row_num, Uarr);


    // printf("Sigma 为:\n");
    // Display2DDoubleArray2DPoint(row_num, col_num, Sigma);


    // printf("V 的转置为:\n");
    // Display2DDoubleArray2DPoint(col_num, col_num, VarrT);


    // 释放内存.
    Matrix_Free_2DDouble(transArr, col_num, row_num);
    Matrix_Free_2DDouble(transSigma, col_num, row_num);
    Matrix_Free_2DDouble(ATA, col_num, col_num);
    Matrix_Free_2DDouble(EigenVec, col_num, col_num);
    Matrix_Free_2DDouble(AV, row_num, col_num);


    return eigvalue_num;
}




/*****************************************************************************************
https://blog.csdn.net/zhouxuguang236/article/details/40212143


功能: 求实对称矩阵 的特征值和特征向量

雅可比方法用于求解实对称矩阵的特征值和特征向量,对于实对称矩阵A ,必有正交矩阵U ,使得U^T*A*U = D .D是一个对角阵,主对角线的元素是矩阵 A  的特征值,正交矩阵 U 的每一列对应于属于矩阵 D 的主对角线对应元素的特征向量.

输入:
    arr:  order x order 的矩阵
    eps：精度
    maxiternum: 最大迭代次数

输出:
    EigenValue: 特征值, 1 x order. 从大到小排序
    EigenVec: order x order二维矩阵, 每一列是对应 EigenValue 的特征向量。
*****************************************************************************************/
void EigenValueVectors_Jacobi(double **arr, double *EigenValue, double **EigenVec, int order, double eps, int maxiternum)
{
    int flag = 0;
    double max = 1e-20;
    int iternum = 0;
    int row = 0, col = 0;

    int p = 0, q = 0;

	if (arr == NULL)
	{
		printf("error: 数组为空, [file:%s,fun:%s, Line:%d ] \n\n", __FILE__, __func__, __LINE__);
		exit(EXIT_FAILURE);
	}
	//判断是否为对称矩阵
	for (int i = 0; i < order; i++)
	{
		for (int j = i; j < order; j++)
		{
			if (arr[i][j] != arr[j][i])
			{
				flag = 1;
				break;
			}
		}
	}
	if (flag == 1)
	{
		printf("error : 输入并非是对称矩阵, [file:%s,fun:%s, Line:%d ] \n\n", __FILE__, __func__, __LINE__);
		exit(EXIT_FAILURE);
	}

    //=======================================================
    // 为了消元过程不影响matrix, 先分配内存并拷贝数值;
    //=======================================================
    double **tmparr;
    tmparr = (double **)malloc(order * sizeof(double *));
	if (tmparr == NULL)
	{
		printf("error :申请数组内存空间失败 [file:%s,fun:%s, Line:%d ] \n\n", __FILE__, __func__, __LINE__);
		exit(EXIT_FAILURE);
	}
    for (int i = 0; i < order; i++)
    {
        tmparr[i] = (double *)malloc(order * sizeof(double));
		if (tmparr[i] == NULL)
		{
			printf("error :申请数组子内存空间失败 [file:%s,fun:%s, Line:%d ] \n\n", __FILE__, __func__, __LINE__);
			exit(EXIT_FAILURE);
		}
    }

    // 为特征向量组分配临时内存
    double **tmpEgVec;
    tmpEgVec = (double **)malloc(order * sizeof(double *));
	if (tmpEgVec == NULL)
	{
		printf("error :申请数组内存空间失败 [file:%s,fun:%s, Line:%d ] \n\n", __FILE__, __func__, __LINE__);
		exit(EXIT_FAILURE);
	}
    for (int i = 0; i < order; i++)
    {
        tmpEgVec[i] = (double *)malloc(order * sizeof(double));
		if (tmpEgVec[i] == NULL)
		{
			printf("error :申请数组子内存空间失败 [file:%s,fun:%s, Line:%d ] \n\n", __FILE__, __func__, __LINE__);
			exit(EXIT_FAILURE);
		}
    }

    //先copy一份array在temp_mat中，因为 在堆区申请的空间,在对其进行处理的过程中会修改原矩阵的值,因此要存储起来 .
    for(int i = 0; i < order; i++){
        for(int j = 0; j < order; ++j){
            tmparr[i][j] = arr[i][j];

            if(i == j){
                tmpEgVec[i][j] = 1;
            }
            else{
                tmpEgVec[i][j] = 0;
            }
        }
    }

    //printf("拷贝的temarr和EigenVec\n");
    //Display2DDoubleArray2DPoint(order, order, tmparr);
    //Display2DDoubleArray2DPoint(order, order, tmpEgVec);

    while(iternum < maxiternum && max >= eps){

        max = fabs(tmparr[0][1]);
        row = 0;
        col = 1;
        for(int i = 0; i < order; i++){
            for(int j = 0; j < order; ++j){
                if(i != j && fabs(tmparr[i][j]) > max ){
                    max = fabs(tmparr[i][j]);
                    row = i;
                    col = j;
                }
            }
        }

        double theta = 0.5 * atan2( -2 * tmparr[row][col], (tmparr[col][col] - tmparr[row][row]) );

        //update Arr
        double App = tmparr[row][row];
        double Aqq = tmparr[col][col];
        double Apq = tmparr[row][col];

        // 旋转矩阵的值
        double sin_theta = sin(theta);
        double cos_theta = cos(theta);
        double sin_2theta = sin(2 * theta);
        double cos_2theta = cos(2 * theta);

        tmparr[row][row] = App*cos_theta*cos_theta + Aqq*sin_theta*sin_theta + Apq*sin_2theta;  // App'
        tmparr[col][col] = App*sin_theta*sin_theta + Aqq*cos_theta*cos_theta - Apq*sin_2theta;  // Aqq'
        tmparr[row][col] = 0.5*(Aqq - App)*sin_2theta + Apq*cos_2theta;                         // Apq'
        tmparr[col][row] = tmparr[row][col];                                                    // Aqp'
        for (int k = 0; k < order; k++)
        {
            if (k != row && k != col)
            {
                double arowk = tmparr[row][k];
                double acolk = tmparr[col][k];
                tmparr[row][k] =  arowk * cos_theta + acolk * sin_theta;                         // Api', i = 0...order
                tmparr[k][row] = tmparr[row][k];                                                // Aip', i = 0...order
                tmparr[col][k] = - arowk * sin_theta + acolk * cos_theta ;                      // Aqi', i = 0...order
                tmparr[k][col] = tmparr[col][k];                                                // Aiq', i = 0...order
            }
        } //  A1 仍然是实对称阵，因为，UpqT = Upq-1，知 A1 与 A 的特征值相同。


        // 更新特征向量
        double Eki;
        double Ekj;
        for(int k = 0; k < order; k++){
            Eki = tmpEgVec[k][row];
            Ekj = tmpEgVec[k][col];
            tmpEgVec[k][row] =   Eki*cos_theta + Ekj*sin_theta;
            tmpEgVec[k][col] = - Eki*sin_theta + Ekj*cos_theta ;
        }

        iternum++;
    } // end while
    printf("Maximum off-diagonal element is: %lf, iterate: %d times\n\n", max, iternum);

    // 更新特征值
    for(int i = 0; i < order; i++){
        EigenValue[i] = tmparr[i][i];
    }

    // printf("排序前 特征值:\n");
    // Display1DDoubleArray1DPoint(order, EigenValue);

    // printf("排序前 特征向量为:\n");
    // Display2DDoubleArray2DPoint(order, order, tmpEgVec);


    // 排序特征值并返回索引，以从大到小排序特征值和特征向量.
    int *Index;
    Index = (int *)malloc(sizeof(int) * order);
	if (Index == NULL)
	{
		printf("error :申请数组内存空间失败 [file:%s,fun:%s, Line:%d ] \n\n", __FILE__, __func__, __LINE__);
		exit(EXIT_FAILURE);
	}

    for(int i = 0; i < order; i++){
        Index[i] = i;
    }
    BubbleSortDouble(EigenValue, order, Index);


    for(int i = 0; i < order; ++i){
        for(int j = 0; j < order; ++j){
            EigenVec[i][j] = tmpEgVec[i][Index[j]];
        }
    }

    // Display1DIntArray3(Index, order);

    // printf("排序后 特征值:\n");
    // Display1DDoubleArray1DPoint(order, EigenValue);

    // printf("排序后 特征向量为:\n");
    // Display2DDoubleArray2DPoint(order, order, EigenVec);

    // 释放内存
    Matrix_Free_2DDouble(tmparr, order, order);
    Matrix_Free_2DDouble(tmpEgVec, order, order);
    Matrix_Free_1DInt(Index, order);
}

