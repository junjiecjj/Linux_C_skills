

#include "ArrayPoint.h"

//演示数组元素的地址和指针+1的含义
int pnt_add(void)
{
    short dates [SIZE];
    short * pti;
    short index;
    double bills[SIZE];
    double * ptf;

    pti = dates;    // assign address of array to pointer
    ptf = bills;
    printf("%23s %15s\n", "short", "double");
    for (index = 0; index < SIZE; index ++)
        printf("pointers + %d: %10p %10p\n",  index, pti + index, ptf + index);

    return 0;
}

// 测试一维数组的首地址和元素地址。
void PntAddress(void)
{
    int arr[10] = {0,1,2,3,4,5,6,7,8,9};
    int *pt;
    pt = arr;
    for(int idx = 0; idx<10; ++idx)
    {
        printf("address of arr[%d] is %p\n", idx, &arr[idx]);
    }
    printf("\narr数组的首地址为:%p = %p\n", arr, &arr[0]);
    for(int idx = 0; idx<10; ++idx)
    {
        printf("address of arr[%d] is %p\n", idx, pt+idx );
    }
}

/*
用栈声明的时候很明显，都是连续的。
在堆上的时候，由于是分批次分配内存（首先new出或malloc多少行，然后每一行再分别new），因此其存放是平行的几条连续存储，每一行是连续的，行与行之间并不连续。为此，我们尝试创建一个2X4的二维矩阵如下:
*/
// 测试C语言的栈内存分配
void C_stack(){
    printf("====== C stack ======\n");
    char str[2][4] = { {65,66,67,68}, {69,70,71,72} };
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 4; j++){
            printf("[%c]%p\t", str[i][j], &str[i][j]);
        }
        printf("\n");
    }
    printf("=====================\n\n");
}
// 测试C语言的堆内存分配
void C_malloc(){
    printf("====== C malloc ======\n");

    char **str = (char **)malloc(2*sizeof(char *));

    for (int i = 0; i < 2; i++)
        str[i] = (char*)malloc(4*sizeof(char));
    char s = 'A';
    for (int i = 0; i < 2; i++){
        for(int j = 0; j < 4; j++){
            str[i][j] = s++;
            printf("[%c]%p\t", str[i][j], &str[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < 2; i++)
        free(str[i]);
    free(str);
    printf("====================\n\n");
}


// void CXX_stack(){
//     cout<<"====== Cpp stack ======"<<endl;
//     char str[2][4] = { {65,66,67,68}, {69,70,71,72} };
//     for(int i = 0; i < 2; i++){
//         for(int j = 0; j < 4; j++){
//             cout<<"["<<str[i][j]<<"]"<<(void *)&str[i][j]<<"\t";
//         }
//         cout<<endl;
//     }
//     cout<<"======================"<<endl<<endl;
// }
// void CXX_new(){
//     cout<<"====== Cpp new ======"<<endl;

//     char **str = new char *[2];
//     for (int i = 0; i < 2; i++)
//         str[i] = new char [4];
//     char s = 'A';
//     for (int i = 0; i < 2; i++){
//         for(int j = 0; j < 4; j++){
//             str[i][j] = s++;
//             cout<<"["<<str[i][j]<<"]"<<(void *)&str[i][j]<<"\t";
//         }
//         cout<<endl;
//     }

//     for (int i = 0; i < 2; i++)
//         delete []str[i];
//     delete str;
//     cout<<"===================="<<endl;
// }

// 打印一维数组
void Show1DArrayKindsOfWays(void)
{
    printf("**********************************************************************************\n");
    printf("***************************** 申明、分配、打印一维数组 ******************\n");
    printf("**********************************************************************************\n\n");

    int len  = 5;
    int Arr[len];
    for(int i=0; i<len; ++i)
    {
        Arr[i] = i+1;
    }
    Display1DIntArray(Arr, 5);
    Display1DIntArray2(Arr, 5);
    Display1DIntArray3(Arr, 5);
    Display1DIntArray4(Arr, 5);

    int sum1 = Sum1DIntArray1(Arr,len);
    int sum2 = Sum1DIntArray2(Arr,Arr+len);
    printf("一维数组求和, sum1 = %d, sum2 = %d\n",sum1,  sum2);
}


void Show2DArrayKindsOfWaysC(void)
{
    printf("**********************************************************************************\n");
    printf("***************************** 申明、分配、打印二维数组 ******************\n");
    printf("**********************************************************************************\n");
    int m = 5, n = 10;
    printf("================== A[m][n]的方式申请数组=============================\n");

    int A[m][n]; // 这样的内存一定是是连续的；用栈声明的时候很明显，都是连续的
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            A[i][j] = i * n + j;
        }
    }
    // printf("打印A[m][n]方式申请的数组的元素地址\n");
    // for (int i = 0; i < m; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         printf("%15p",&A[i][j]);
    //     }
    //     printf("\n");
    // }

    printf("打印数组A第一次......\n");
    Display2DIntArray(m, n, A);  //ok

    printf("打印数组A第二次......\n");
    Display2DIntArray1(m, n, A);  //ok


    printf("打印数组A第三次......\n");
    Display2DIntArrayNorm(m, n, A);  //ok


    printf("打印数组A第四次......\n");
    //  Display2DIntArray2DPoint(m, n, &A[0][0]); //不能这么用
    //  Display2DIntArray2DPoint(m, n, A); //不能这么用

    printf("打印数组A第五次......\n");
    Display2DIntArrayUse1D(m, n, &A[0][0]); //ok，因为这样的分配是连续的，所以当成一维数组没问题

    printf("================== int **D 的方式申请数组,不连续分配=============================\n");

    int **D;
    //这样分配内存不连续,行内连续，行间不一定连续，
    D = (int **)malloc(m * sizeof(int *));  //每一行的首地址分配内存，不一定连续
    for (int i = 0; i < m; i++)
    {
        D[i] = (int *)malloc(n * sizeof(int)); //每一行一定连续
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            D[i][j] = i * n + j;
        }
    }

    // printf("打印**D方式申请的数组的元素地址\n");
    // for (int i = 0; i < m; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         printf("%15p",&D[i][j]);
    //     }
    //     printf("\n");
    // }
    // printf("打印**D方式申请的数组的元素地址\n");
    // for (int i = 0; i < m; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         printf("%15p",&D[i*n+j]);
    //     }
    //     printf("\n");
    // }

    printf("打印数组D第一次......\n");
    printf("D = %p\n",D);
    printf("D[0] = %p\n",D[0]);
    printf("D[0][0] = %p\n",&D[0][0]);
    //Display2DIntArray(m, n,&D[0]); //这样编译不会出错，但是结果不对
    printf("\n");
    //Display2DIntArray(m, n, D); //这样编译不会出错，但是结果不对
    printf("\n");
    //Display2DIntArray(m, n, D[0]); //这样编译不会出错，但是结果不对

    printf("打印数组D第二次......\n");
    //Display2DIntArray1(m, n, D); //这样编译不会出错，但是结果不对

    printf("打印数组D第三次......\n");
    //Display2DIntArrayNorm(m, n, D); //这样编译不会出错，但是结果不对

    printf("打印数组D第四次......\n");
    //Display2DIntArrayUse1D(m, n, &D[0][0]); //这样编译不会出错，但是结果不对
    //Display2DIntArrayUse1D(m, n, D);        //这样编译不会出错，但是结果不对

    printf("打印数组D第五次......\n");
    Display2DIntArray2DPoint(m, n, D); //正确的方式，推荐

    Free2DNotContinueMem(D, m, n);
    // for(int i=0; i<m; i++)
    // {
    //     free(D[i]);
    // }
    // free(D);


    printf("================== int **E 的方式申请数组,连续分配=============================\n");

    int **E;
    E = (int **)malloc(sizeof(int *) * m);    //分配指针数组
    E[0] = (int *)malloc(sizeof(int) * m * n);//一次性分配所有空间
    for(int i=1; i<m; i++)
    {
        E[i] = E[i-1] + n;
    }//采用如上内存分配方法，意味着将E的值初始化为m*n的二维数组首地址,且这块内存连续

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            E[i][j] =  i * n + j;
        }
    }
    // printf("打印**E方式申请的数组的元素地址\n");
    // for (int i = 0; i < m; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         printf("%15p",&E[i][j]);
    //     }
    //     printf("\n");
    // }

    printf("E[1][2] = %d\n", E[1][2]);


    printf("打印数组E第一次......\n");
    //Display2DIntArray(m, n, E[0]); //这样编译不会出错，但是结果不对

    printf("打印数组E第二次......\n");
    //Display2DIntArray1(m, n, E); //这样编译不会出错，但是结果不对

    printf("打印数组E第三次......\n");
    //Display2DIntArrayNorm(m, n, E); //这样编译不会出错，但是结果不对

    printf("打印数组E第四次......\n");
    Display2DIntArrayUse1D(m, n, &E[0][0]); //这样可以，把内存连续分配的二维数组当做一维打印
    printf("\n");
    Display2DIntArrayUse1D(m, n, E[0]); //这样可以，把内存连续分配的二维数组当做一维打印
    printf("\n");
    //Display2DIntArrayUse1D(m, n, &E[0]); //这样编译不会出错，但是结果不对
    printf("\n");
    // Display2DIntArrayUse1D(m, n, E[0][0]); //  段错误
    printf("\n");
    //Display2DIntArrayUse1D(m, n, E); //这样编译不会出错，但是结果不对

    printf("打印数组E第五次......\n");
    Display2DIntArray2DPoint(m, n, E); //正确的方式


    printf("%ld\n", sizeof(E));    //8，指针
    printf("%ld\n", sizeof(E[0])); //8，指针

    free(E[0]);  //
    // for(int i=0; i<m; i++)
    // {  段错误
    //     free(E[i]); // 重复释放
    // }
    free(E); E = NULL;
}




/*********************************************************************
%p是打印地址（指针地址）的，是十六进制的形式，但是会全部打完，即有多少位打印多少位。
下面分别描述了指针变量的基本操作。
·赋值：可以把地址赋给指针。例如，用数组名、带地址运算符（&）的变量名、另一个指针进行赋值。在该例中，把urn数组的首地址赋给了ptr1，该地址的编号恰好是0x7fff5fbff8d0。变量ptr2获得数组urn的第3个元素（urn[2]）的地址。注意，地址应该和指针类型兼容。也就是说，不能把double类型的地址赋给指向int的指针，至少要避免不明智的类型转换。C99/C11已经强制不允许这样做。
·解引用：*运算符给出指针指向地址上存储的值。因此，*ptr1的初值是100，该值存储在编号为0x7fff5fbff8d0的地址上。

·取址：和所有变量一样，指针变量也有自己的地址和值。对指针而言，&运算符给出指针本身的地址。本例中，ptr1存储在内存编号为0x7fff5fbff8c8的地址上，该存储单元存储的内容是0x7fff5fbff8d0，即urn的地址。因此&ptr1是指向ptr1的指针，而ptr1是指向utn[0]的指针。

·指针与整数相加：可以使用+运算符把指针与整数相加，或整数与指针相加。无论哪种情况，整数都会和指针所指向类型的大小（以字节为单位）相乘，然后把结果与初始地址相加。因此ptr1+4与&urn[4]等价。如果相加的结果超出了初始指针指向的数组范围，计算结果则是未定义的。除非正好超过数组末尾第一个位置，C保证该指针有效。

·递增指针：递增指向数组元素的指针可以让该指针移动至数组的下一个元素。因此，ptr1++相当于把ptr1的值加上4（我们的系统中int为4字节），ptr1指向urn[1]（见图10.4，该图中使用了简化的地址）。现在ptr1的值是0x7fff5fbff8d4（数组的下一个元素的地址），*ptr的值为200（即urn[1]的值）。注意，ptr1本身的地址仍是0x7fff5fbff8c8。毕竟，变量不会因为值发生变化就移动位置。

·指针减去一个整数：可以使用-运算符从一个指针中减去一个整数。指针必须是第1个运算对象，整数是第2个运算对象。该整数将乘以指针指向类型的大小（以字节为单位），然后用初始地址减去乘积。所以ptr3 - 2与&urn[2]等价，因为ptr3指向的是&urn[4]。如果相减的结果超出了初始指针所指向数组的范围，计算结果则是未定义的。除非正好超过数组末尾第一个位置，C保证该指针有效。

·递减指针：当然，除了递增指针还可以递减指针。在本例中，递减ptr2使其指向数组的第2个元素而不是第3个元素。前缀或后缀的递增和递减运算符都可以使用。注意，在重置ptr1和ptr2前，它们都指向相同的元素urn[1]。

·指针求差：可以计算两个指针的差值。通常，求差的两个指针分别指向同一个数组的不同元素，通过计算求出两元素之间的距离。差值的单位与数组类型的单位相同。例如，程序清单10.13的输出中，ptr2 - ptr1得2，意思是这两个指针所指向的两个元素相隔两个int，而不是2字节。只要两个指针都指向相同的数组（或者其中一个指针指向数组后面的第1个地址），C都能保证相减运算有效。如果指向两个不同数组的指针进行求差运算可能会得出一个值，或者导致运行时错误。

·比较：使用关系运算符可以比较两个指针的值，前提是两个指针都指向相同类型的对象。

在递增或递减指针时还要注意一些问题。编译器不会检查指针是否仍指向数组元素。C只能保证指向数组任意元素的指针和指向数组后面第1个位置的指针有效。但是，如果递增或递减一个指针后超出了这个范围，则是未定义的。另外，可以解引用指向数组任意元素的指针。但是，即使指针指向数组后面一个位置是有效的，也不能保证可以解引用这样的越界指针。

解引用未初始化的指针说到注意事项，一定要牢记一点：千万不要解引用未初始化的指针。例如，考虑下面的例子：
*/
    // int *pt; //未初始化的指针
    // *pt = 5; //严重错误

    /*
为何不行？第2行的意思是把5存储在pt指向的位置。但是pt未被初始化，其值是一个随机值，所以不知道5将存储在何处。这可能不会出什么错，也可能会擦写数据或代码，或者导致程序崩溃。切记：创建一个指针时，系统只分配了存储指针本身的内存，并未分配存储数据的内存。因此，在使用指针之前，必须先用已分配的地址初始化它。例如，可以用一个现有变量的地址初始化该指针（使用带指针形参的函数时，就属于这种情况）。或者还可以使用第12章将介绍的malloc()函数先分配内存。无论如何，使用指针时一定要注意，不要解引用未初始化的指针！
     double *pt1;  //未初始化的指针
    *pt1 = 2.4;  //严重错误
*********************************************************************/

int ptr_ops(void)
{
    printf("********************** 指针操作 ***********************\n");
    int urn[5] = {100,200,300,400,500};
    int * ptr1, * ptr2, *ptr3;

    ptr1 = urn;         // assign an address to a pointer
    ptr2 = &urn[2];     // ditto
    // dereference a pointer and take
    // the address of a pointer
    printf("\n pointer value, dereferenced pointer, pointer address:\n");
    printf("ptr1 = %p, *ptr1 =%d, &ptr1 = %p\n",  ptr1, *ptr1, &ptr1);

    // pointer addition
    ptr3 = ptr1 + 4;
    printf("\nadding an int to a pointer:\n");
    printf("ptr1 + 4 = %p, *(ptr1 + 4) = %d\n",  ptr1 + 4, *(ptr1 + 4));
    ptr1++;            // increment a pointer
    printf("\nvalues after ptr1++:\n");
    printf("ptr1 = %p, *ptr1 =%d, &ptr1 = %p\n",  ptr1, *ptr1, &ptr1);
    ptr2--;            // decrement a pointer
    printf("\nvalues after --ptr2:\n");
    printf("ptr2 = %p, *ptr2 = %d, &ptr2 = %p\n",   ptr2, *ptr2, &ptr2);
    --ptr1;            // restore to original value
    ++ptr2;            // restore to original value
    printf("\nPointers reset to original values:\n");
    printf("ptr1 = %p, ptr2 = %p\n", ptr1, ptr2);
    // subtract one pointer from another
    printf("\nsubtracting one pointer from another:\n");
    printf("ptr2 = %p, ptr1 = %p, ptr2 - ptr1 = %td\n",    ptr2, ptr1, ptr2 - ptr1);
    // subtract an integer from a pointer
    printf("\nsubtracting an int from a pointer:\n");
    printf("ptr3 = %p, ptr3 - 2 = %p\n",   ptr3,  ptr3 - 2);

    return 0;
}


// 指针与多维数组
void zippo1(void)
{
    printf("************************* 指针和多维数组 *************************\n");
    int zippo[4][2] = { {2,4}, {6,8}, {1,3}, {5, 7} };
    Display2DIntArrayNorm(4,2,zippo);
    printf("   zippo          = %p,    zippo + 1 = %p\n", zippo,  zippo + 1);
    printf("&zippo[0]         = %p\n", &zippo[0]);
    printf("zippo[0]          = %p, zippo[0] + 1 = %p\n", zippo[0], zippo[0] + 1);
    printf("&zippo[0][0]      = %p\n", &zippo[0][0]);
    printf("&zippo            = %p\n", &zippo);
    printf("  *zippo          = %p,   *zippo + 1 = %p\n", *zippo,   *zippo + 1);
    printf("zippo[0][0]       = %d\n", zippo[0][0]);
    printf("  *zippo[0]       = %d\n", *zippo[0]); // 所以*(zippo[0])表示储存在zippo[0][0]上的值（即一个int类型的值）
    printf("    **zippo       = %d\n", **zippo);
    printf(" zippo[2][1]      = %d\n", zippo[2][1]);
    printf("*(*(zippo+2) + 1) = %d\n", *(*(zippo+2) + 1));

}

void zippo2(void)
{
    printf("************************* 指向多维数组的指针 *************************\n");
    int zippo[4][2] = { {2,4}, {6,8}, {1,3}, {5, 7} };
    int (*pz)[2];
    pz = zippo;

    printf("   pz = %p,    pz + 1 = %p\n",  pz,         pz + 1);
    printf("pz[0] = %p, pz[0] + 1 = %p\n", pz[0],      pz[0] + 1);
    printf("  *pz = %p,   *pz + 1 = %p\n", *pz,        *pz + 1);
    printf("pz[0][0] = %d\n", pz[0][0]);
    printf("  *pz[0] = %d\n", *pz[0]);
    printf("    **pz = %d\n", **pz);
    printf("      pz[2][1] = %d\n", pz[2][1]);
    printf("*(*(pz+2) + 1) = %d\n", *(*(pz+2) + 1));

}


// 函数和多维数组
void sum_rows(int ar[][COLS], int rows)
{
    int r;
    int c;
    int tot;

    for (r = 0; r < rows; r++)
    {
        tot = 0;
        for (c = 0; c < COLS; c++)
            tot += ar[r][c];
        printf("row %d: sum = %d\n", r, tot);
    }
}

void sum_cols(int ar[][COLS], int rows)
{
    int r;
    int c;
    int tot;

    for (c = 0; c < COLS; c++)
    {
        tot = 0;
        for (r = 0; r < rows; r++)
            tot += ar[r][c];
        printf("col %d: sum = %d\n", c, tot);
    }
}

int sum2d(int ar[][COLS], int rows)
{
    int r;
    int c;
    int tot = 0;

    for (r = 0; r < rows; r++)
        for (c = 0; c < COLS; c++)
            tot += ar[r][c];

    return tot;
}
// 带变长数组形参的函数
int sum2dvar(int rows, int cols, int ar[rows][cols])
{
    int r;
    int c;
    int tot = 0;

    for (r = 0; r < rows; r++)
        for (c = 0; c < cols; c++)
            tot += ar[r][c];

    return tot;
}


int array2d(void)
{
    int junk[ROWS][COLS] = {
        {2,4,6,8},
        {3,5,7,9},
        {12,10,8,6}
    };

    sum_rows(junk, ROWS);
    sum_cols(junk, ROWS);
    printf("Sum of all elements = %d\n", sum2d(junk, ROWS));

    return 0;
}


int vararr2d(void)
{
    int i, j;
    int rs = 3;
    int cs = 10;
    int junk[ROWS][COLS] = {
        {2,4,6,8},
        {3,5,7,9},
        {12,10,8,6}
    };

    int morejunk[ROWS-1][COLS+2] = {
        {20,30,40,50,60,70},
        {5,6,7,8,9,10}
    };

    int varr[rs][cs];  // VLA

    for (i = 0; i < rs; i++)
        for (j = 0; j < cs; j++)
            varr[i][j] = i * j + j;

    printf("3x5 array\n");
    printf("Sum of all elements = %d\n", sum2dvar(ROWS, COLS, junk));

    printf("2x6 array\n");
    printf("Sum of all elements = %d\n", sum2dvar(ROWS-1, COLS+2, morejunk));

    printf("3x10 VLA\n");
    printf("Sum of all elements = %d\n", sum2dvar(rs, cs, varr));

    return 0;
}


/***********************************************************************
https://blog.csdn.net/haiwil/article/details/6691854
C语言，C语言返回局部变量的几种用法--（经典例子）
　　一般来说，函数是可以返回局部变量的。 局部变量的作用域只在函数内部，在函数返回后，局部变量的内存已经释放了。因此，如果函数返回的是局部变量的值，不涉及地址，程序不会出错。但是如果返回的是局部变量的地址(指针)的话，程序运行后会出错。
因为函数只是把指针复制后返回了，但是指针指向的内容已经被释放了，这样指针指向的内容就是不可预料的内容，调用就会出错。准确来说，函数不能通过返回指向栈内存的指针(注意这里指的是栈，返回指向堆内存的指针是可以的)。
　　总结如下：
　　（1）返回指向字符串常量的指
　　（2）不能返回以局部变量方式创建的字符串数组首地址
　　（3）在函数中，允许返回局部变量的值，不允许返回局部变量的地址
　　（4）在函数中，如果函数的返回值非要是一个局部变量的地址，那么该局部变量一定要申明为static类型。
　　（5）数组是不能作为函数的返回值
　　（6）返回指向堆内存的指针是可以的
当函数使用指针作为返回值时，它可以指向静态区域的地址，可以指向堆内存的地址，也可以指向函数调用者的栈空间，但是它不可以指向一个函数内部栈内存的地址。

因此，能不能返回局部指针变量，不在于这个指针变量的类型和性质（不在于该指针是不是局部指针变量），而在于该指针指向的对象的类型和性质。如果该指针指向函数内部的栈空间，则程序非法，如果指向静态区域的地址，则合法。
 因此，判断指针函数返回值是否合法，应该首先看看该返回指针变量指向的对象的存储区域，即该指针指向的区域。透过现象看本质，不同区域的对象本质区别在于 其的生存周期的有效性不同，判断返回的指针值是否有效合法，最本质应该看看该指针指向的对象的生存周期在函数结束后是否有效。如果该对象的生存周期长于指 针函数的生存周期，则该指针返回值合法，否则，该指针的值为非法地址。即使该指针指向堆区域的地址但在指针函数结束时，堆已释放，则该函数的返回地址仍为非法。
下面以函数返回局部变量的指针举几个典型的例子来说明：
************************************************************************/

char *returnStr(void)
{
    char *p="hello world!";
    return p;
}

//    这个没有任何问题，因为"hello world!"是一个字符串常量，存放在只读数据段，把该字符串常量存放的只读数据段的首地址赋值给了指针，所以returnStr函数退出时，该该字符串常量所在内存不会被回收，故能够通过指针顺利无误的访问。
int ReturnStr(void)
{
    printf("********************* 1. 返回指向字符串常量的指针 *********************\n");
    char *str;
    str=returnStr();
    printf("%s\n", str);
    return 0;
}


char *returnStr1(void)
{
    char p[]="hello world!";
    return p;
}
// "hello world!"是局部变量存放在栈中。当returnStr函数退出时，栈要清空，局部变量的内存也被清空了，所以这时的函数返回的是一个已被释放的内存地址，所以有可能打印出来的是乱码。
int ReturnStr1(void)
{
    printf("********************* 2. 不能返回以局部变量方式创建的字符串数组首地址 *********************\n");
    char *str;
    str=returnStr();
    printf("%s\n", str);
    return 0;
}


/*

3：在函数中，允许返回局部变量的值，不允许返回局部变量的地址

复制代码
int func()
{
　　int a;
　　....
　　return a; //允许
}
int * func()
{
　　int a;
　　....
　　return &a; //无意义，不应该这样做
}
int func(){ int a; .... return a; //允许} int * func(){ int a; .... return &a; //无意义，不应该这样做}
复制代码


局部变量也分局部自动变量和局部静态变量，由于a返回的是值，因此返回一个局部变量是可以的，无论自动还是静态，因为这时候返回的是这个局部变量的值，但不应该返回指向局部自动变量的指针，因为函数调用结束后该局部自动变量被抛弃，这个指针指向一个不再存在的对象，是无意义的。但可以返回指向局部静态变量的指针，因为静态变量的生存期从定义起到程序结束。
*/

char *returnStr2(void)
{
    static char p[]="hello world!";
    return p;
}
// "hello world!"是局部变量存放在栈中。当returnStr函数退出时，栈要清空，局部变量的内存也被清空了，所以这时的函数返回的是一个已被释放的内存地址，所以有可能打印出来的是乱码。
int ReturnStr2(void)
{
    printf("*********** 4：如果函数的返回值非要是一个局部变量的地址，那么该局部变量一定要申明为static类型。如下：  ************\n");
    char *str;
    str=returnStr();
    printf("%s\n", str);
    return 0;
}

/*
5： 数组是不能作为函数的返回值的，原因是编译器把数组名认为是局部变量（数组）的地址。返回一个数组一般用返回指向这个数组的指针代替，而且这个指针不能指向一个自动数组，因为函数结束后自动数组被抛弃，但可以返回一个指向静态局部数组的指针，因为静态存储期是从对象定义到程序结束的。如下：

复制代码
int* func( void )
{
　　static int a[10];
　　........
　　return a;
}
int* func( void ){ static int a[10]; ........ return a;}
*/


char *GetMemory3(int num)
{
    char *p = (char *)malloc(sizeof(char) * num);
    return p;
}
// 程序在运行的时候用 malloc 申请任意多少的内存,程序员自己负责在何时用 free释放内存。动态内存的生存期由程序员自己决定,使用非常灵活。
void ReturnHeap(void)
{
    printf("*********************** 返回指向堆内存的指针是可以的 *************************\n");
    char *str = NULL;
    str = GetMemory3(100);
    strcpy(str, "hello，jack");
    printf("%s\n", str);
    free(str);
}


void saferFree(void **pp)
{
    if(pp != NULL && *pp != NULL)
    {
        free(*pp);
        *pp = NULL;
    }
}

int testSafeFree(void)
{
    printf("*********************** 自己实现的安全的free函数 ***********************\n");
    int *pi;
    pi = (int *)malloc(sizeof(int));
    *pi = 5;
    printf("Before: %p\n", pi);
    safeFree(pi);
    printf("After: %p\n", pi);
    safeFree(pi);
    return (EXIT_SUCCESS);

}


/*
三维数组的分配和释放：
*/
int MallocFree3D(void)
{
    printf("*********************** 三维数组指针的分配和释放 ***********************\n");
    int i,j,k;   // p[2][3][4]

    int ***p;
    p = malloc( sizeof(int **)*high);
    for(i=0; i<high; i++)
    {
        p[i]= malloc( sizeof(int *)*row);//new int *[3];
        for(j=0; j<row; j++)
            p[i][j]= malloc( sizeof(int )*col);//new int[4];
    }

    //输出 p[i][j][k] 三维数据
    for(i=0; i<high; i++)
    {
        for(j=0; j<row; j++)
        {
            for(k=0;k<col;k++)
            {
                p[i][j][k]=i+j+k;
                printf("%d ",p[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }

    // 释放内存
    for(i=0; i<high; i++)
    {
        for(j=0; j<row; j++)
        {
            free(p[i][j]);
        }
    }
    for(i=0; i<high; i++)
    {
        free(p[i]);
    }
    free(p);
    return 0;
}


void zip1darray(void)
{
    printf("******************* 一维数组与指针 ********************\n");
    int vector[5] = {1,2,3,4,5};
    int *pv = vector;
    printf("vector     = %p\n", vector);
    printf("vector+1   = %p\n", vector+1);
    printf("&vector[0]   = %p\n", &vector[0]);
    printf("&vector[0]+1 = %p\n", &vector[0]+1);

    printf("&vector     = %p\n", &vector);
    printf("&vector+1   = %p\n", &vector+1);

    printf("sizeof(vector) = %lu\n", sizeof(vector));
    // vector     = 0x7fff405e9680
    // vector+1   = 0x7fff405e9684
    // &vector[0]   = 0x7fff405e9680
    // &vector[0]+1 = 0x7fff405e9684
    // &vector     = 0x7fff405e9680
    // &vector+1   = 0x7fff405e9694

}

void Pnt2DArray(void)
{
    printf("******************* 指针和多维数组 ********************\n");
    int matrix[2][5] = {{1,2,3,4,5},{6,7,8,9,10}};
    for(int i=0; i<2; ++i)
    {
        for(int j = 0; j<5; ++j)
        {
            printf("matrix[%d][%d] Adress: %p Value: %d\n",i, j, &matrix[i][j], matrix[i][j]);
        }
    }
    int (*pmat)[5] = matrix;
    printf("matrix   = %p\n", matrix);
    printf("matrix+1 = %p", matrix+1);
}

void Array2D(void)
{
    int m=2, n=3;
    int A[m][n];
    for(int i = 0; i<m; ++i)
    {
        for(int j = 0; j<n; ++j)
        {
            A[i][j] = i*n+j;
        }
    }

    printf("*************** 打印二维数组每行的地址 ******************\n");
    for(int i=0; i<m; ++i)
    {
        printf("&A[%d]: %p sizeof(A[%d]): %lu \n", i, &A[i], i, sizeof(A[i]));
    }
}

void AllocateArray(int **arr, int size, int value)
{
    *arr = (int *)malloc(size*sizeof(int));
    if(*arr != NULL)
    {
        for(int i=0; i<size; ++i)
        {
            *(*arr+i) = value;
        }
    }
}

void TestAllocateArray(void)
{
    printf("*************** 传递指针的指针 ***************\n");
    int *vector = NULL;
    AllocateArray(&vector,5,45);
}

void  TestArrayPoint(void)
{
    // printf(" ************************* 演示数组元素的地址和指针+1的含义 ************************\n");
    // pnt_add();
    // printf("************************* 一维数组与指针 *************************\n");
    // PntAddress();
    // printf(" ************************* 演示A[m][n]内存连续和int **A; malloc分配的内存不连续 ************************\n");
    // C_stack();
    // C_malloc();
    // // CXX_stack();
    // // CXX_new();
    // // 打印分配一维二维数组
    // Show1DArrayKindsOfWays();
    // Show2DArrayKindsOfWaysC();
    zip1darray();
    // ptr_ops();

    // array2d();
    // vararr2d();
    // zippo1();
    // zippo2();

    // ReturnStr();
    // ReturnStr1();
    // ReturnStr2();
    // ReturnHeap();
    // testSafeFree();
    // MallocFree3D();
    // Array2D();
    // Pnt2DArray();
    // TestAllocateArray();


}



