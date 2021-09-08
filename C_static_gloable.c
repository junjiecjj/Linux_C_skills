/*************************************************************************
>> File Name: C_static_gloable.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com
>> Created Time: 2021年01月09日 星期六 22时54分58秒
>> 此程序的功能是：展示static、global、register、const、变量作用域和生存周期等。

（一）作用域:作用域描述程序中可访问标识符的区域。一个C变量的作用域可以是块作用域、函数作用域、函数原型作用域或文件作用域。
(1)块作用域:
到目前为止，本书程序示例中使用的变量几乎都具有块作用域。块是用一对花括号括起来的代码区域。例如，整个函数体是一个块，函数中的任意复合语句也是一个块。定义在块中的变量具有块作用域（block scope），块作用域变量的可见范围是从定义处到包含该定义的块的末尾。另外，虽然函数的形式参数声明在函数的左花括号之前，但是它们也具有块作用域，属于函数体这个块。所以到目前为止，我们使用的局部变量（包括函数的形式参数）都具有块作用域。因此，下面代码中的变量cleo和patrick都具有块作用域：
double blocky(double cleo)
{
    double patrick = 0.0;
    ...
    return patrick;
}

声明在内层块中的变量，其作用域仅局限于该声明所在的块：
double blocky(double cleo)
{
    double patrick = 0.0;
    int i;
    for(i = 0; i<10; ++i)
    {
        double q = cleo * i;   //q的作用域开始
        ...
        patrick  *=q;   //q的作用域结束
    }
    ...
    return patrick;
}

在该例中，q的作用域仅限于内层块，只有内层块中的代码才能访问q。以前，具有块作用域的变量都必须声明在块的开头。C99标准放宽了这一限制，允许在块中的任意位置声明变量。因此，对于for的循环头，现在可以这样写：
for(int i = 0; i<10; ++i)
    {
        printf("A C99 feature :i = %d", i);
    }

    为适应这个新特性，C99把块的概念扩展到包括for循环、while循环、do while循环和if语句所控制的代码，即使这些代码没有用花括号括起来，也算是块的一部分。所以，上面for循环中的变量i被视为for循环块的一部分，它的作用域仅限于for循环。一旦程序离开for循环，就不能再访问i。

    (2)函数作用域（function scope）:仅用于goto语句的标签。这意味着即使一个标签首次出现在函数的内层块中，它的作用域也延伸至整个函数。如果在两个块中使用相同的标签会很混乱，标签的函数作用域防止了这样的事情发生。

    (3)函数原型作用域（function prototype scope）用于函数原型中的形参名（变量名），如下所示：
    int mighty(int mouse, double large);
    函数原型作用域的范围是从形参定义处到原型声明结束。这意味着，编译器在处理函数原型中的形参时只关心它的类型，而形参名（如果有的话）通常无关紧要。而且，即使有形参名，也不必与函数定义中的形参名相匹配。只有在变长数组中，形参名才有用：
    void use_a_VLA(int n, int m, ar[n][m]);

    (4)文件作用域:变量的定义在函数的外面，具有文件作用域（file scope）。具有文件作用域的变量，从它的定义处到该定义所在文件的末尾均可见。考虑下面的例子：
    #include <stdio.h>
int units = 0;
void critic(void)
int main(int argc, char *argv[])
{
}
void critic(void)
{
}

这里，变量units具有文件作用域，main()和critic()函数都可以使用它（更准确地说，units具有外部链接文件作用域，稍后讲解）。由于这样的变量可用于多个函数，所以文件作用域变量也称为全局变量（global variable）。

注意 :翻译单元和文件你认为的多个文件在编译器中可能以一个文件出现。例如，通常在源代码（.c扩展名）中包含一个或多个头文件（.h扩展名）。头文件会依次包含其他头文件，所以会包含多个单独的物理文件。但是，C预处理实际上是用包含的头文件内容替换#include指令。所以，编译器把源代码文件和所有的头文件都看成是一个包含信息的单独文件。这个文件被称为翻译单元（translation unit）。描述一个具有文件作用域的变量时，它的实际可见范围是整个翻译单元。如果程序由多个源代码文件组成，那么该程序也将由多个翻译单元组成。每个翻译单元均对应一个源代码文件和它所包含的文件。

（二）链接
C变量有3种链接属性：外部链接、内部链接或无链接。具有块作用域、函数作用域或函数原型作用域的变量都是无链接变量。这意味着这些变量属于定义它们的块、函数或原型私有。具有文件作用域的变量可以是外部链接或内部链接。外部链接变量可以在多文件程序中使用，内部链接变量只能在一个翻译单元中使用。

注意 ：正式和非正式术语C标准用“内部链接的文件作用域”描述仅限于一个翻译单元（即一个源代码文件和它所包含的头文件）的作用域，用“外部链接的文件作用域”描述可延伸至其他翻译单元的作用域。但是，对程序员而言这些术语太长了。一些程序员把“内部链接的文件作用域”简称为“文件作用域”，把“外部链接的文件作用域”简称为“全局作用域”或“程序作用域”。

如何知道文件作用域变量是内部链接还是外部链接？可以查看外部定义中是否使用了存储类别说明符static：
int giants = 5;        //文件作用域，外部链接
static int dodgers = 3;     //文件作用域，内部链接
int main
{
    ...
}
该文件和同一程序的其他文件都可以使用变量giants。而变量dodgers属文件私有，该文件中的任意函数都可使用它。


（三）存储期
作用域和链接描述了标识符的可见性。存储期描述了通过这些标识符访问的对象的生存期。C对象有4种存储期：静态存储期、线程存储期、自动存储期、动态分配存储期。

如果对象具有静态存储期，那么它在程序的执行期间一直存在。文件作用域变量具有静态存储期。注意，对于文件作用域变量，关键字static表明了其链接属性，而非存储期。以static声明的文件作用域变量具有内部链接。但是无论是内部链接还是外部链接，所有的文件作用域变量都具有静态存储期。

线程存储期用于并发程序设计，程序执行可被分为多个线程。具有线程存储期的对象，从被声明时到线程结束一直存在。以关键字_Thread_local声明一个对象时，每个线程都获得该变量的私有备份。

块作用域的变量通常都具有自动存储期。当程序进入定义这些变量的块时，为这些变量分配内存；当退出这个块时，释放刚才为变量分配的内存。这种做法相当于把自动变量占用的内存视为一个可重复使用的工作区或暂存区。例如，一个函数调用结束后，其变量占用的内存可用于存储下一个被调用函数的变量。

变长数组稍有不同，它们的存储期从声明处到块的末尾，而不是从块的开始处到块的末尾。
我们到目前为止使用的局部变量都是自动类别。例如，在下面的代码中，变量number和index在每次调用bore()函数时被创建，在离开函数时被销毁：

int  bore(int number)
{
    int index;
    for(index = 0; index < number; ++index)
    {
        ...
    }
    return 0;
}
然而，块作用域变量也能具有静态存储期。为了创建这样的变量，要把变量声明在块中，且在声明前面加上关键字static：
int  bore(int number)
{
    int index;
    static int ct = 0;
    return 0;
}
这里，变量ct存储在静态内存中，它从程序被载入到程序结束期间都存在。但是，它的作用域定义在more()函数块中。只有在执行该函数时，程序才能使用ct访问它所指定的对象（但是，该函数可以给其他函数提供该存储区的地址以便间接访问该对象，例如通过指针形参或返回值）。

C使用作用域、链接和存储期为变量定义了多种存储方案。本书不涉及并发程序设计，所以不再赘述这方面的内容。动态分配存储期在本章后面介绍。因此，剩下5种存储类别：自动、寄存器、静态块作用域、静态外部链接、静态内部链接，如表12所列。现在，我们已经介绍了作用域、链接和存储期，接下来将详细讨论这些存储类别。

##########################################################################
存储类别                        存储期                          作用域                           链接                           声明方式
-------------------------------------------------------------------------------------------------------------------
自动                        自动                         块                                         无                        块内
寄存器                    自动                         块                                        无                       块内，使用关键字static
静态外部链接            静态                  文件                       外部                      所有函数外
静态内部链接             静态                 文件                      内部                     所有函数外，使用关键字static
静态无连接                 静态                 块                          无                         块内，使用关键字static

(一)自动变量/局部变量
属于自动存储类别的变量具有自动存储期、块作用域且无链接。默认情况下，声明在块或函数头中的任何变量都属于自动存储类别。

定义在函数内部，只有在函数内部才有效；特点：进来创建，出去销毁；

块作用域和无链接意味着只有在变量定义所在的块中才能通过变量名访问该变量（当然，参数用于传递变量的值和地址给另一个函数，但是这是间接的方法）。另一个函数可以使用同名变量，但是该变量是存储在不同内存位置上的另一个变量。变量具有自动存储期意味着，程序在进入该变量声明所在的块时变量存在，程序在退出该块时变量消失。原来该变量占用的内存位置现在可做他用。

如果内层块中声明的变量与外层块中的变量同名会怎样？内层块会隐藏外层块的定义。但是离开内层块后，外层块变量的作用域又回到了原来的作用域。

自动变量不会初始化，除非显式初始化它。


(二)寄存器变量

寄存器变量通常存储在计算机内存中。如果幸运的话，寄存器变量存储在CPU的寄存器中，或者概括地说，存储在最快的可用内存中。与普通变量相比，访问和处理这些变量的速度更快。由于寄存器变量存储在寄存器而非内存中，所以无法获取寄存器变量的地址。绝大多数方面，寄存器变量和自动变量都一样。也就是说，它们都是块作用域、无链接和自动存储期。使用存储类别说明符register便可声明寄存器变量：
int main()
{
    register int quick;
}

(三)静态无连接/块作用域的静态变量/静态局部变量
块作用域的静态变量（static variable）听起来自相矛盾，像是一个不可变的变量。实际上，静态的意思是该变量在内存中原地不动，并不是说它的值不变。具有文件作用域的变量自动具有（也必须是）静态存储期。前面提到过，可以创建具有静态存储期、块作用域的局部变量。这些变量和自动变量一样，具有相同的作用域，但是程序离开它们所在的函数后，这些变量不会消失。也就是说，这种变量具有块作用域、无链接，但是具有静态存储期。计算机在多次函数调用之间会记录它们的值。在块中（提供块作用域和无链接）以存储类别说明符static（提供静态存储期）声明这种变量。

定义在函数内部，只有在函数内部才有效；但是只会在开始分配一次内存，不会消失；特点：进来创建，一直保留；

#include <stdio.h>
void trystat(void);

int main(void)
{
    int count;

    for (count = 1; count <= 3; count++)
    {
        printf("Here comes iteration %d:\n", count);
        trystat();
    }

    return 0;
}

void trystat(void)
{
    int fade = 1;
    static int stay = 1;

    printf("fade = %d and stay = %d\n", fade++, stay++);
}

注意，trystat()函数先打印再递增变量的值。该程序的输出如下：
Here comes iteration 1:
fade = 1 and stay = 1
Here comes iteration 2:
fade = 1 and stay = 2
Here comes iteration 3:
fade = 1 and stay = 3

静态变量stay保存了它被递增1后的值，但是fade变量每次都是1。这表明了初始化的不同：每次调用trystat()都会初始化fade，但是stay只在编译trystat()时被初始化一次。如果未显式初始化静态变量，它们会被初始化为0。下面两个声明很相似：
    int fade = 1;
    static int stay = 1;

第1条声明确实是trystat()函数的一部分，每次调用该函数时都会执行这条声明。这是运行时行为。第2条声明实际上并不是trystat()函数的一部分。如果逐步调试该程序会发现，程序似乎跳过了这条声明。这是因为静态变量和外部变量在程序被载入内存时已执行完毕。把这条声明放在trystat()函数中是为了告诉编译器只有trystat()函数才能看到该变量。这条声明并未在运行时执行。不能在函数的形参中使用static：
int wontwork(static int flu);  //不允许

“局部静态变量”是描述具有块作用域的静态变量的另一个术语。阅读一些老的C文献时会发现，这种存储类别被称为内部静态存储类别（internal static storage class）。这里的内部指的是函数内部，而非内部链接。

(四)外部链接的静态变量/全局变量

 全局变量，定义在所有函数之外的变量，对整个工程文件有效。当前文件可直接使用，如果不是当前文件，则需在调用文件开头加上关键字 extern 。

外部链接的静态变量具有文件作用域、外部链接和静态存储期。该类别有时称为外部存储类别（external storage class），属于该类别的变量称为外部变量（external variable）。把变量的定义性声明（defining declaration）放在所有函数的外面便创建了外部变量。当然，为了指出该函数使用了外部变量，可以在函数中用关键字extern再次声明。如果一个源代码文件使用的外部变量定义在另一个源代码文件中，则必须用extern在该文件中声明该变量。如下所示：

int  Errupt;   //外部定义的变量
double Up[100];             //外部定义的数组
extern  char  Coal;         //如果Coal被定义在另一个文件
void next(void);
int main()
{
    extern int Errupt ;           //可选的声明
    extern  double   Up[];             //可选的声明
}

void  next(woid)
{
    ...
}
注意，在main()中声明Up数组时（这是可选的声明）不用指明数组大小，因为第1次声明已经提供了数组大小信息。main()中的两条extern声明完全可以省略，因为外部变量具有文件作用域，所以Errupt和Up从声明处到文件结尾都可见。它们出现在那里，仅为了说明main()函数要使用这两个变量。

1．初始化外部变量外部变量和自动变量类似，也可以被显式初始化。与自动变量不同的是，如果未初始化外部变量，它们会被自动初始化为0。这一原则也适用于外部定义的数组元素。与自动变量的情况不同，只能使用常量表达式初始化文件作用域变量：

int x = 10;     //没问题，10是常量
int y = 3+20 ;      没问题，用于初始化的是常量表达式
size_t  z = sizeof(int)     //没问题，用于初始化的是常量表达式
int x2 = 2*x；//不行，x是变量

2.定义和声明
下面进一步介绍定义变量和声明变量的区别。考虑下面的例子：
int tern  = 1;   //tern被定义
int main()
{
    extern int tern;   //使用了在别处定义的tern
}
这里，tern被声明了两次。第1次声明为变量预留了存储空间，该声明构成了变量的定义。第2次声明只告诉编译器使用之前已创建的tern变量，所以这不是定义。第1次声明被称为定义式声明（defining declaration），第2次声明被称为引用式声明（referencing declaration）。关键字extern表明该声明不是定义，因为它指示编译器去别处查询其定义。

假设这样写：
extern int tern;
int main()
{

}
编译器会假设tern实际的定义在该程序的别处，也许在别的文件中。该声明并不会引起分配存储空间。因此，不要用关键字extern创建外部定义，只用它来引用现有的外部定义。

外部变量只能初始化一次，且必须在定义该变量时进行。假设有下面的代码：
//file_one.c
char permits = 'N';

//file_two.c
extern char permits = 'Y';  //错误

file_two中的声明是错误的，因为file_one.c中的定义式声明已经创建并初始化了permis。

(五)内部链接的静态变量/静态全局变量
静态全局变量，也是一个全局变量，不过加上 静态 之后，就限定了此变量的作用范围。

该存储类别的变量具有静态存储期、文件作用域和内部链接。在所有函数外部（这点与外部变量相同），用存储类别说明符static定义的变量具有这种存储类别：
static  int svil = 1;   //静态变量，内部链接
int main(void)
{

}
这种变量过去称为外部静态变量（external static variable），但是这个术语有点自相矛盾（这些变量具有内部链接）。但是，没有合适的新简称，所以只能用内部链接的静态变量（static variable with internal linkage）。普通的外部变量可用于同一程序中任意文件中的函数，但是内部链接的静态变量只能用于同一个文件中的函数。可以使用存储类别说明符extern，在函数中重复声明任何具有文件作用域的变量。这样的声明并不会改变其链接属性。考虑下面的代码：

int traveler = 1;   //外部链接
static int stayhome = 1;   //内部链接

int main()
{
    extern int traveler;   //使用定义在别处的traveler
    extern int stayhome;   //使用定义在别处的stayhome
    ...
}
对于该程序所在的翻译单元，trveler和stayhome都具有文件作用域，但是只有traveler可用于其他翻译单元（因为它具有外部链接）。这两个声明都使用了extern关键字，指明了main()中使用的这两个变量的定义都在别处，但是这并未改变stayhome的内部链接属性。


-----------------------------------------------------------------------存储类别说明符----------------------------------------------------------------
关键字static和extern的含义取决于上下文。C语言有6个关键字作为存储类别说明符：auto、register、static、extern、_Thread_local和typedef。typedef关键字与任何内存存储无关，把它归于此类有一些语法上的原因。尤其是，在绝大多数情况下，不能在声明中使用多个存储类别说明符，所以这意味着不能使用多个存储类别说明符作为typedef的一部分。唯一例外的是_Thread_local，它可以和static或extern一起使用。

auto说明符表明变量是自动存储期，只能用于块作用域的变量声明中。由于在块中声明的变量本身就具有自动存储期，所以使用auto主要是为了明确表达要使用与外部变量同名的局部变量的意图。

register说明符也只用于块作用域的变量，它把变量归为寄存器存储类别，请求最快速度访问该变量。同时，还保护了该变量的地址不被获取。

用static说明符创建的对象具有静态存储期，载入程序时创建对象，当程序结束时对象消失。如果static用于文件作用域声明，作用域受限于该文件。如果static用于块作用域声明，作用域则受限于该块。因此，只要程序在运行对象就存在并保留其值，但是只有在执行块内的代码时，才能通过标识符访问。块作用域的静态变量无链接。文件作用域的静态变量具有内部链接。

extern说明符表明声明的变量定义在别处。如果包含extern的声明具有文件作用域，则引用的变量必须具有外部链接。如果包含extern的声明具有块作用域，则引用的变量可能具有外部链接或内部链接，这接取决于该变量的定义式声明。


-----------------------------------------------------------------------小结：存储类别----------------------------------------------------------------
自动变量具有块作用域、无链接、自动存储期。它们是局部变量，属于其定义所在块（通常指函数）私有。寄存器变量的属性和自动变量相同，但是编译器会使用更快的内存或寄存器存储它们。不能获取寄存器变量的地址。

具有静态存储期的变量可以具有外部链接、内部链接或无链接。在同一个文件所有函数的外部声明的变量是外部变量，具有文件作用域、外部链接和静态存储期。如果在这种声明前面加上关键字static，那么其声明的变量具有文件作用域、内部链接和静态存储期。如果在函数中用static声明一个变量，则该变量具有块作用域、无链接、静态存储期。

具有自动存储期的变量，程序在进入该变量的声明所在块时才为其分配内存，在退出该块时释放之前分配的内存。如果未初始化，自动变量中是垃圾值。程序在编译时为具有静态存储期的变量分配内存，并在程序的运行过程中一直保留这块内存。如果未初始化，这样的变量会被设置为0。

具有块作用域的变量是局部的，属于包含该声明的块私有。具有文件作用域的变量对文件（或翻译单元）中位于其声明后面的所有函数可见。具有外部链接的文件作用域变量，可用于该程序的其他翻译单元。具有内部链接的文件作用域变量，只能用于其声明所在的文件内。

-----------------------------------------------------------------------多文件extern、----------------------------------------------------------------
只有当程序由多个翻译单元组成时，才体现区别内部链接和外部链接的重要性。接下来简要介绍一下。复杂的C程序通常由多个单独的源代码文件组成。有时，这些文件可能要共享一个外部变量。C通过在一个文件中进行定义式声明，然后在其他文件中进行引用式声明来实现共享。也就是说，除了一个定义式声明外，其他声明都要使用extern关键字，一个变量只能有一个定义式声明，但是带extern的声明是引用式声明，可以有多个引用式声明。。而且，只有定义式声明才能初始化变量。注意，如果外部变量定义在一个文件中，那么其他文件在使用该变量之前必须先声明它（用extern关键字）。也就是说，在某文件中对外部变量进行定义式声明只是单方面允许其他文件使用该变量，其他文件在用extern声明之前不能直接使用它。
过去，不同的编译器遵循不同的规则。例如，许多UNIX系统允许在多个文件中不使用extern关键字声明变量，前提是只有一个带初始化的声明。编译器会把文件中一个带初始化的声明视为该变量的定义。

-----------------------------------------------------------------------constconst类型限定符----------------------------------------------------------------
在ANSI兼容的编译器中，以下代码：
const int nochange;            //限定nochange的值不能被修改
nochange = 12;                     //不允许
编译器会报错。但是，可以初始化const变量。因此，下面的代码没问题：
const int nochange = 12;     //可以
该声明让nochange成为只读变量。初始化后，就不能再改变它的值。
可以用const关键字创建不允许修改的数组：
const int  days[12] = {31,28,31,30,31,30,31,30,21,21,2,1};

1．在指针和形参声明中使用const
声明普通变量和数组时使用const关键字很简单。指针则复杂一些，因为要区分是限定指针本身为const还是限定指针指向的值为const。下面的声明：
const float * pf;    //pf指向一个float类型的const值

创建的pf指向不能被改变的值，而pf本身的值可以改变。例如，可以设置该指针指向其他const值。相比之下，下面的声明：
float * const pt;    //pt是一个const指针

创建的指针pt本身的值不能更改。pt必须指向同一个地址，但是它所指向的值可以改变。下面的声明：

const float * const ptr;

表明ptr既不能指向别处，它所指向的值也不能改变。

const关键字的常见用法是声明为函数形参的指针。例如，假设有一个函数要调用display()显示一个数组的内容。要把数组名作为实际参数传递给该函数，但是数组名是一个地址。该函数可能会更改主调函数中的数据，但是下面的原型保证了数据不会被更改：
void display(const int array[], int limit);
在函数原型和函数头，形参声明const int array[]与const int *array相同，所以该声明表明不能更改array指向的数据。

2．对全局数据使用const前面讲过，使用全局变量是一种冒险的方法，因为这样做暴露了数据，程序的任何部分都能更改数据。如果把数据设置为const，就可避免这样的危险，因此用const限定符声明全局数据很合理。可以创建const变量、const数组和const结构（结构是一种复合数据类型，将在下一章介绍）。
然而，在文件间共享const数据要小心。可以采用两个策略。第一，遵循外部变量的常用规则，即在一个文件中使用定义式声明，在其他文件中使用引用式声明（用extern关键字）：
//file1.c  --定义了一些外部const变量

const double PI = 3.14159;
const char *MOUNTHS[12] = {"January","Feb",March,...};


//file2.c--使用 定义在别处的外部const变量
extern const double PI;
extern const * MONTHS [];

另一种方案是，把const变量放在一个头文件中，然后在其他文件中包含该头文件：
// constant.h    --定义了一些外部const变量
static const double  PI = 3.14159;
static const  char * MONTHS[12] = {"janu","feb",...};

//file1.c  --使用了定义在别处的外部const变量
#include"constant.h"

//file2.c  --使用了定义在别处的外部const变量
#include"constant.h"

把文件名放在双引号中而不是尖括号中，指示编译器在本地查找文件，而不是到编译器存放标准头文件的位置去查找文件。

这种方案必须在头文件中用关键字static声明全局const变量。如果去掉static，那么在file1.c和file2.c中包含constant.h将导致每个文件中都有一个相同标识符的定义式声明，C标准不允许这样做（然而，有些编译器允许）。实际上，这种方案相当于给每个文件提供了一个单独的数据副本[插图]。由于每个副本只对该文件可见，所以无法用这些数据和其他文件通信。不过没关系，它们都是完全相同（每个文件都包含相同的头文件）的const数据（声明时使用了const关键字），这不是问题。头文件方案的好处是，方便你偷懒，不用惦记着在一个文件中使用定义式声明，在其他文件中使用引用式声明。所有的文件都只需包含同一个头文件即可。但它的缺点是，数据是重复的。对于前面的例子而言，这不算什么问题，但是如果const数据包含庞大的数组，就不能视而不见了。

-----------------------------------------------------------------------动态分配内存：malloc()和free()符----------------------------------------------------------------


主要的工具是malloc()函数，该函数接受一个参数：所需的内存字节数。malloc()函数会找到合适的空闲内存块，这样的内存是匿名的。也就是说，malloc()分配内存，但是不会为其赋名。然而，它确实返回动态分配内存块的首字节地址。因此，可以把该地址赋给一个指针变量，并使用指针访问这块内存。因为char表示1字节，malloc()的返回类型通常被定义为指向char的指针。然而，从ANSI C标准开始，C使用一个新的类型：指向void的指针。该类型相当于一个“通用指针”。malloc()函数可用于返回指向数组的指针、指向结构的指针等，所以通常该函数的返回值会被强制转换为匹配的类型。在ANSI C中，应该坚持使用强制类型转换，提高代码的可读性。然而，把指向void的指针赋给任意类型的指针完全不用考虑类型匹配的问题。如果malloc()分配内存失败，将返回空指针。

现在，我们有3种创建数组的方法。·声明数组时，用常量表达式表示数组的维度，用数组名访问数组的元素。可以用静态内存或自动内存创建这种数组。·声明变长数组（C99新增的特性）时，用变量表达式表示数组的维度，用数组名访问数组的元素。具有这种特性的数组只能在自动内存中创建。·声明一个指针，调用malloc()，将其返回值赋给指针，使用指针访问数组的元素。该指针可以是静态的或自动的。

通常，malloc()要与free()配套使用。free()函数的参数是之前malloc()返回的地址，该函数释放之前malloc()分配的内存。因此，动态分配内存的存储期从调用malloc()分配内存到调用free()释放内存为止。设想malloc()和free()管理着一个内存池。每次调用malloc()分配内存给程序使用，每次调用free()把内存归还内存池中，这样便可重复使用这些内存。free()的参数应该是一个指针，指向由malloc()分配的一块内存。不能用free()释放通过其他方式（如，声明一个数组）分配的内存。malloc()和free()的原型都在stdlib.h头文件中。

另外，free()所用的指针变量可以与malloc()的指针变量不同，但是两个指针必须存储相同的地址。但是，不能释放同一块内存两次。

使用malloc()，程序可以在运行时才确定数组大小。如程序清单12.14所示，它把内存块的地址赋给指针ptd，然后便可以使用数组名的方式使用ptd。另外，如果内存分配失败，可以调用exit()函数结束程序，其原型在stdlib.h中。EXIT_FAILURE的值也被定义在stdlib.h中。标准提供了两个返回值以保证在所有操作系统中都能正常工作：EXIT_SUCCESS（或者，相当于0）表示普通的程序结束，EXIT_FAILURE表示程序异常中止。一些操作系统（包括UNIX、Linux和Windows）还接受一些表示其他运行错误的整数值。

int main(int argc, char *argv[])
{
    double * ptd;
    int max;
    int number;
    int i = 0;

    puts("What is the maximum number of type double entries?");
    if (scanf("%d", &max) != 1)
    {
        puts("Number not correctly entered -- bye.");
        exit(EXIT_FAILURE);
    }
    ptd = (double *) malloc(max * sizeof (double));
    if (ptd == NULL)
    {
        puts("Memory allocation failed. Goodbye.");
        exit(EXIT_FAILURE);
    }

puts("Enter the values (q to quit):");
while (i < max && scanf("%lf", &ptd[i]) == 1)
    ++i;
printf("Here are your %d entries:\n", number = i);
for (i = 0; i < number; i++)
{
    printf("%7.2f ", ptd[i]);
    if (i % 7 == 6)
        putchar('\n');
}
if (i % 7 != 0)
    putchar('\n');
puts("Done.");
free(ptd);

return 0;
}

下面是该程序的运行示例。程序通过交互的方式让用户先确定数组的大小，我们设置数组大小为5。虽然我们后来输入了6个数，但程序也只处理前5个数。
What is the maximum number of type double entries?
5
Enter the values (q to quit):
20 30 40 50 60 90
Here are your %d entries:
20.00   30.00   40.00   50.00   60.00


一个非常重要的概念：我们在free() 释放一个指针指向的内存之后，编译器只会释放该指针所指向的内存空间，而不会删除这个指针本身。在free()释放一个指针之后，一定将该指针设置成空指针（即在 delete *p 之后一定要加上： p = NULL），只有这样，才会杜绝上面程序中出现的野指针的错误。 对于 NULL 的应用，我们不应该仅限于上面的方法，还可以应用 NULL 来判断指针是否初始化成功了，如下例 if 中的判断方法：

    int main()
{
    int *p = （int * ）malloc(sizeof(int));
    if (p == NULL)
    {
        // 判断指针 p 是不是空指针，如果是空指针，那么程序在这里就应该报错
        // 报错的方法有很多，比如说返回一个 ERROR 值：
        //return ERROR;
    }

    // 判断了操作成功之后我们才能进行一系列的操作
    //...

    分配内存还可以使用calloc() ，典型的用法如下： long *newmem = (long *)calloc(100, sizeof(long));

    和malloc() 类似，在ANSI之前，calloc() 也返回指向char的指针；在ANSI之后，返回指向void的指针。如果要存储不同的类型，应使用强制类型转换运算符。calloc() 函数接受两个无符号整数作为参数（ANSI规定是size_t类型）。第1个参数是所需的存储单元数量，第2个参数是存储单元的大小（以字节为单位）。在该例中，long为4字节，所以，前面的代码创建了100个4字节的存储单元，总共400字节。用sizeof(long) 而不是4，提高了代码的可移植性。这样，在其他long不是4字节的系统中也能正常工作。calloc() 函数还有一个特性：它把块中的所有位都设置为0（注意，在某些硬件系统中，不是把所有位都设置为0来表示浮点值0）。free() 函数也可用于释放calloc() 分配的内存。

        -----------------------------------------------------------------------存储类别和动态内存分配-- --------------------------------------------------------------
        存储类别和动态内存分配有何联系？我们来看一个理想化模型。可以认为程序把它可用的内存分为3部分：一部分供具有外部链接、内部链接和无链接的静态变量使用；一部分供自动变量使用；一部分供动态内存分配。静态存储类别所用的内存数量在编译时确定，只要程序还在运行，就可访问存储在该部分的数据。该类别的变量在程序开始执行时被创建，在程序结束时被销毁。然而，自动存储类别的变量在程序进入变量定义所在块时存在，在程序离开块时消失。因此，随着程序调用函数和函数结束，自动变量所用的内存数量也相应地增加和减少。这部分的内存通常作为栈来处理，这意味着新创建的变量按顺序加入内存，然后以相反的顺序销毁。动态分配的内存在调用malloc() 或相关函数时存在，在调用free() 后释放。这部分的内存由程序员管理，而不是一套规则。所以内存块可以在一个函数中创建，在另一个函数中销毁。正是因为这样，这部分的内存用于动态内存分配会支离破碎。也就是说，未使用的内存块分散在已使用的内存块之间。另外，使用动态内存通常比使用栈内存慢。总而言之，程序把静态对象、自动对象和动态分配的对象存储在不同的区域。
* /
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "diceroll.h"

int main(int argc, char *argv[])
{
    int dice, roll;
    int sides;
    int status;

    srand((unsigned int)time(0)); //randomize seed
    printf("Enter the number of sides per die, 0 to stop.\n");
    while (scanf("%d", &sides) == 1 && sides > 0)
    {
        printf("How many dice?\n");
        if ((status = scanf("%d", &dice)) != 1)
        {
            if (status == EOF)
                break; //exit loop
            else
            {
                printf("You should have entered an integer.");
                printf(" Let's begin again.\n");
                while (getchar() != '\n')
                    continue; // 处理错误输入
                printf("How many sides? Enter 0 to stop.\n");
                continue; // 进入下一次循环
            }
        }
        roll = roll_n_dice(dice, sides);
        printf("You have rolled a %d using %d %d-sided dice.\n",
               roll, dice, sides);
        printf("How many sides? Enter 0 to stop.\n");
    }
    printf("The rollem() function was called %d times.\n",
           roll_count); // 使用外部变量

    printf("GOOD FORTUNE TO YOU!\n");

    return 0;
}