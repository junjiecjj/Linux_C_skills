/*************************************************************************
>> File Name: C_string.c
>> Author: chenjunjie
>> Mail: 2716705056qq.com
>> Created Time: 2019.03.25

const char * pt1 = "Something is pointing at me.";
该声明和下面的声明几乎相同：
const char ar1[] = "Something is pointing at me.";
以上两个声明表明，pt1和ar1都是该字符串的地址。在这两种情况下，带双引号的字符串本身决定了预留给字符串的存储空间。尽管如此，这两种形式并不完全相同。
数组和指针
数组形式和指针形式有何不同？以上面的声明为例，数组形式（ar1[]）在计算机的内存中分配为一个内含29个元素的数组（每个元素对应一个字符，还加上一个末尾的空字符'\0'），每个元素被初始化为字符串字面量对应的字符。通常，字符串都作为可执行文件的一部分存储在数据段中。当把程序载入内存时，也载入了程序中的字符串。字符串存储在静态存储区（static
memory）中。但是，程序在开始运行时才会为该数组分配内存。此时，才将字符串拷贝到数组中（第12章将详细讲解）。注意，此时字符串有两个副本。一个是在静态内存中的字符串字面量，另一个是存储在ar1数组中的字符串。
此后，编译器便把数组名ar1识别为该数组首元素地址（&ar1[0]）的别名。这里关键要理解，在数组形式中，ar1是地址常量。不能更改ar1，如果改变了ar1，则意味着改变了数组的存储位置（即地址）。可以进行类似ar1+1这样的操作，标识数组的下一个元素。但是不允许进行++ar1这样的操作。递增运算符只能用于变量名前（或概括地说，只能用于可修改的左值），不能用于常量。
指针形式（*pt1）也使得编译器为字符串在静态存储区预留29个元素的空间。另外，一旦开始执行程序，它会为指针变量pt1留出一个存储位置，并把字符串的地址存储在指针变量中。该变量最初指向该字符串的首字符，但是它的值可以改变。因此，可以使用递增运算符。例如，++pt1将指向第2个字符（o）。
字符串字面量被视为const数据。由于pt1指向这个const数据，所以应该把pt1声明为指向const数据的指针。这意味着不能用pt1改变它所指向的数据，但是仍然可以改变pt1的值（即，pt1指向的位置）。如果把一个字符串字面量拷贝给一个数组，就可以随意改变数据，除非把数组声明为const。
总之，初始化数组把静态存储区的字符串拷贝到数组中，而初始化指针只把字符串的地址拷贝给指针。
总之，如果打算修改字符串，就不要用指针指向字符串字面量。

初始化字符串的方式：
char S[91];
char S[]="hello,jack!!!";
char *p = (char *)malloc(sizeof(char)*Len);





还可以使用指针表示法创建字符串。例如，程序清单11.1中使用了下面的声明：

const char &pt1 = "Something is pointing at me."
该声明和下面的声明几乎相同：
const char ar1[] = "Something is pointing at me."
以上两个声明表明，pt1和ar1都是该字符串的地址。在这两种情况下，带双引号的字符串本身决定了预留给字符串的存储空间。尽管如此，这两种形式并不完全相同。


ANSI C库有20多个用于处理字符串的函数，下面总结了一些常用的函数。

char *strcpy(char * restrict s1, const char * restrict s2);
该函数把s2指向的字符串（包括空字符）拷贝至s1指向的位置，返回值是s1。

char *strncpy(char * restrict s1, const char * restrict s2, size_t n);
该函数把s2指向的字符串拷贝至s1指向的位置，拷贝的字符数不超过n，其返回值是s1。该函数不会拷贝空字符后面的字符，如果源字符串的字符少于n个，目标字符串就以拷贝的空字符结尾；如果源字符串有n个或超过n个字符，就不拷贝空字符。

char *strcat(char * restrict s1, const char * restrict s2);
该函数把s2指向的字符串拷贝至s1指向的字符串末尾。s2字符串的第1个字符将覆盖s1字符串末尾的空字符。该函数返回s1。


char *strncat(char * restrict s1, const char * restrict s2, size_t n);
该函数把s2字符串中的n个字符拷贝至s1字符串末尾。s2字符串的第1个字符将覆盖s1字符串末尾的空字符。不会拷贝s2字符串中空字符和其后的字符，并在拷贝字符的末尾添加一个空字符。该函数返回s1。

int strcmp(const char * s1, const char * s2);
如果s1字符串在机器排序序列中位于s2字符串的后面，该函数返回一个正数；如果两个字符串相等，则返回0；如果s1字符串在机器排序序列中位于s2字符串的前面，则返回一个负数。

int strncmp(const char * s1, const char * s2, size_t n);
该函数的作用和strcmp()类似，不同的是，该函数在比较n个字符后或遇到第1个空字符时停止比较。

char *strchr(const char * s, int c);
如果s字符串中包含c字符，该函数返回指向s字符串首次出现的c字符的指针（末尾的空字符也是字符串的一部分，所以在查找范围内）；如果在字符串s中未找到c字符，该函数则返回空指针。

char *strpbrk(const char * s1, const char * s2);
如果s1字符中包含s2字符串中的任意字符，该函数返回指向s1字符串首位置的指针；如果在s1字符串中未找到任何s2字符串中的字符，则返回空字符。

char *strrchr(const char * s, char c);
该函数返回s字符串中c字符的最后一次出现的位置（末尾的空字符也是字符串的一部分，所以在查找范围内）。如果未找到c字符，则返回空指针。

char *strstr(const char * s1, const char * s2);
该函数返回指向s1字符串中s2字符串出现的首位置。如果在s1中没有找到s2，则返回空指针。

size_t strlen(const char * s);
该函数返回s字符串中的字符数，不包括末尾的空字符。

请注意，那些使用const关键字的函数原型表明，函数不会更改字符串。例如，下面的函数原型：
char *strcpy(char * restrict s1, const char * restrict s2);
表明不能更改s2指向的字符串，至少不能在strcpy()函数中更改。但是可以更改s1指向的字符串。这样做很合理，因为s1是目标字符串，要改变，而s2是源字符串，不能更改。

************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define MAX 20
#define WORDS "beast"
#define TARGSIZE 7
#define SIZE 40
#define SLEN 40
#define LIM 5

char *s_gets(char *st, int n) {
  char *ret_val;
  int i = 0;

  ret_val = fgets(st, n, stdin);
  if (ret_val) {
    while (st[i] != '\n' && st[i] != '\0')
      i++;
    if (st[i] == '\n')
      st[i] = '\0';
    else // must have words[i] == '\0'
      while (getchar() != '\n')
        continue;
  }
  return ret_val;
}

void test1() {
  char heart[] = "I love Tillie!";
  char *head = "I love Tillie!";

  //首先，两者都可以使用数组表示法：

  for (int i = 0; i < 6; i++) {
    putchar(heart[i]);
  }
  putchar('\n');

  for (int i = 0; i < 6; i++) {
    putchar(head[i]);
  }
  putchar('\n');

  // 其次，两者都能进行指针加法操作：

  for (int i = 0; i < 6; i++) {
    putchar(*(heart + i));
  }
  putchar('\n');

  for (int i = 0; i < 6; i++) {
    putchar(*(head + i));
  }
  putchar('\n');

  //但是，只有指针表示法可以进行递增操作：
  while (*(head) != '\0') {
    putchar(*(head++));
  }

  //总之，如果打算修改字符串，就不要用指针指向字符串字面量。
}

/*
从某些方面来看，mytalents和yourtalents非常相似。两者都代表5个字符串。使用一个下标时都分别表示一个字符串，
如mytalents[0]和yourtalents[0]；使用两个下标时都分别表示一个字符，例如mytalents[1][2]表示mytalents数组中第2个指针所指向的字符串的第3个字符'l'，
yourtalents[1][2]表示youttalentes数组的第2个字符串的第3个字符'e'。而且，两者的初始化方式也相同。但是，它们也有区别。mytalents数组是一个内含5个指针的数组
，在我们的系统中共占用40字节。而yourtalents是一个内含5个数组的数组，每个数组内含40个char类型的值，共占用200字节。
所以，虽然mytalents[0]和yourtalents[0]都分别表示一个字符串，但mytalents和yourtalents的类型并不相同。mytalents中的指针指向初始化时所用的字符串字面量的位置，
这些字符串字面量被存储在静态内存中；而yourtalents中的数组则存储着字符串字面量的副本，所以每个字符串都被存储了两次。
此外，为字从某些方面来看，mytalents和yourtalents非常相似。两者都代表5个字符串。使用一个下标时都分别表示一个字符串，如mytalents[0]和yourtalents[0]；
使用两个下标时都分别表示一个字符，例如mytalents[1][2]表示mytalents数组中第2个指针所指向的字符串的第3个字符'l'，yourtalents[1][2]表示youttalentes数组的第2个字符串的第3个字符'e'。
而且，两者的初始化方式也相同。但是，它们也有区别。mytalents数组是一个内含5个指针的数组，在我们的系统中共占用40字节。而yourtalents是一个内含5个数组的数组，
每个数组内含40个char类型的值，共占用200字节。所以，虽然mytalents[0]和yourtalents[0]都分别表示一个字符串，但mytalents和yourtalents的类型并不相同。
mytalents中的指针指向初始化时所用的字符串字面量的位置，这些字符串字面量被存储在静态内存中；而yourtalents中的数组则存储着字符串字面量的副本，
所以每个字符串都被存储了两次。此外，为字符串数组分配内存的使用率较低。yourtalents中的每个元素的大小必须相同，而且必须是能存储最长字符串的大小。
我们可以把yourtalents想象成矩形二维数组，每行的长度都是40字节；把mytalents想象成不规则的数组，每行的长度不同。
图11.2演示了这两种数组的情况（实际上，mytalents数组的指针元素所指向的字符串不必存储在连续的内存中，图中所示只是为了强调两种数组的不同）。
*/
void test2() {
  const char *mytalents[LIM] = {
      "Adding numbers swiftly", "Multiplying accurately", "Stashing data",
      "Following instructions to the letter", "Understanding the C language"};
  char yourtalents[LIM][SLEN] = {"Walking in a straight line", "Sleeping",
                                 "Watching television", "Mailing letters",
                                 "Reading email"};
  int i;

  puts("Let's compare talents.");
  printf("%-36s  %-25s\n", "My Talents", "Your Talents");
  for (i = 0; i < LIM; i++)
    printf("%-36s  %-25s\n", mytalents[i], yourtalents[i]);
  printf("\nsizeof mytalents: %zd, sizeof yourtalents: %zd\n",
         sizeof(mytalents), sizeof(yourtalents));
}

/*
 我们来仔细分析最后两个printf()的输出。首先第1项，mesg和copy都以字符串形式输出（%s转换说明）。这里没问题，两个字符串都是"Don't
 be a fool!"。
 接着第2项，打印两个指针的地址。如上输出所示，指针mesg和copy分别存储在地址为0x0012ff48和0x0012ff44的内存中。注意最后一项，显示两个指针的值。
 所谓指针的值就是它存储的地址。mesg和copy的值都是0x0040a000，说明它们都指向的同一个位置。因此，程序并未拷贝字符串。语句copy
 = mesg;把mesg的值赋给copy，
 即让copy也指向mesg指向的字符串。为什么要这样做？为何不拷贝整个字符串？假设数组有50个元素，考虑一下哪种方法更效率：拷贝一个地址还是拷贝整个数组？
 通常，程序要完成某项操作只需要知道地址就可以了。如果确实需要拷贝整个数组，可以使用strcpy()或strncpy()函数，本章稍后介绍这两个函数。
 */

void test3() {
  const char *mesg = "Don't be a fool!";
  const char *copy;

  copy = mesg;
  printf("%s\n", copy);
  printf("mesg = %s; &mesg = %p; value = %p\n", mesg, &mesg, mesg);
  printf("copy = %s; &copy = %p; value = %p\n", copy, &copy, copy);
}

/*
前面提到过，如果pts1和pts2都是指向字符串的指针，那么下面语句拷贝的是字符串的地址而不是字符串本身：
pst2 = pst1;

如果希望拷贝整个字符串，要使用strcpy()函数。程序清单11.25要求用户输入以q开头的单词。该程序把输入拷贝至一个临时数组中，如果第1个字母是q，程序调用strcpy()把整个字符串从临时数组拷贝至目标数组中。strcpy()函数相当于字符串赋值运算符。

请注意，strcpy()第2个参数（temp）指向的字符串被拷贝至第1个参数（qword[i]）指向的数组中。拷贝出来的字符串被称为目标字符串，
最初的字符串被称为源字符串。参考赋值表达式语句，很容易记住strcpy()参数的顺序，即第1个是目标字符串，第2个是源字符串。

程序员有责任确保目标数组有足够的空间容纳源字符串的副本。下面的代码有点问题：
char *str;
strcpy(str, "the c of Tranquility");
strcpy()把"The C of
Tranquility"拷贝至str指向的地址上，但是str未被初始化，所以该字符串可能被拷贝到任意的地方！
总之，strcpy()接受两个字符串指针作为参数，可以把指向源字符串的第2个指针声明为指针、数组名或字符串常量；
而指向源字符串副本的第1个指针应指向一个数据对象（如，数组），且该对象有足够的空间存储源字符串的副本。
记住，声明数组将分配存储数据的空间，而声明指针只分配存储一个地址的空间。

*/

void test4() {
  char qwords[LIM][SIZE];
  char temp[SIZE];
  int i = 0;

  printf("Enter %d words beginning with q:\n", LIM);
  while (i < LIM && s_gets(temp, SIZE)) {
    if (temp[0] != 'q')
      printf("%s doesn't begin with q!\n", temp);
    else {
      strcpy(qwords[i], temp);
      i++;
    }
  }
  puts("Here are the words accepted:");
  for (i = 0; i < LIM; i++)
    puts(qwords[i]);
}

/*
strcpy()函数还有两个有用的属性。第一，strcpy()的返回类型是char
*，该函数返回的是第1个参数的值，即一个字符的地址。第二，第1个参数不必指向数组的开始。这个属性可用于拷贝数组的一部分。下面函数的这两个属性。
注意，strcpy()把源字符串中的空字符也拷贝在内。在该例中，空字符覆盖了copy数组中that的第1个t（见图11.5）。注意，由于第1个参数是copy
+ 7，所以ps指向copy中的第8个元素（下标为7）。因此puts(ps)从该处开始打印字符串。
 */
void test5() {
  const char *orig = WORDS;
  char copy[SIZE] = "Be the best that you can be.";
  char *ps;

  puts(orig);
  puts(copy);
  ps = strcpy(copy + 7, orig);
  puts(copy);
  puts(ps);
}

/*
更谨慎的选择：
strncpy()strcpy()和strcat()都有同样的问题，它们都不能检查目标空间是否能容纳源字符串的副本。
拷贝字符串用strncpy()更安全，该函数的第3个参数指明可拷贝的最大字符数。程序清单11.27用strncpy()代替程序清单11.25中的strcpy()。
为了演示目标空间装不下源字符串的副本会发生什么情况，该程序使用了一个相当小的目标字符串（共7个元素，包含6个字符）。

strncpy(target, source,
n)把source中的n个字符或空字符之前的字符（先满足哪个条件就拷贝到何处）拷贝至target中。
因此，如果source中的字符数小于n，则拷贝整个字符串，包括空字符。但是，strncpy()拷贝字符串的长度不会超过n，
如果拷贝到第n个字符时还未拷贝完整个源字符串，就不会拷贝空字符。所以，拷贝的副本中不一定有空字符。
鉴于此，该程序把n设置为比目标数组大小少1（TARGSIZE-1），然后把数组最后一个元素设置为空字符：
*/
void test6() {
  char qwords[LIM][TARGSIZE];
  char temp[SIZE];
  int i = 0;

  printf("Enter %d words beginning with q:\n", LIM);
  while (i < LIM && s_gets(temp, SIZE)) {
    if (temp[0] != 'q')
      printf("%s doesn't begin with q!\n", temp);
    else {
      strncpy(qwords[i], temp, TARGSIZE - 1);
      qwords[i][TARGSIZE - 1] = '\0';
      i++;
    }
  }
  puts("Here are the words accepted:");
  for (i = 0; i < LIM; i++)
    puts(qwords[i]);
}

/*

sprintf()函数声明在stdio.h中，而不是在string.h中。该函数和printf()类似，但是它是把数据写入字符串，而不是打印在显示器上。
因此，该函数可以把多个元素组合成一个字符串。sprintf()的第1个参数是目标字符串的地址。其余参数和printf()相同，即格式字符串和待写入项的列表。
程序清单11.28中的程序用sprintf()把3个项（两个字符串和一个数字）组合成一个字符串。注意，sprintf()的用法和printf()相同，
只不过sprintf()把组合后的字符串存储在数组formal中而不是显示在屏幕上。
*/
void test7() {
  char first[MAX];
  char last[MAX];
  char formal[2 * MAX + 10];
  double prize;

  puts("Enter your first name:");
  s_gets(first, MAX);
  puts("Enter your last name:");
  s_gets(last, MAX);
  puts("Enter your prize money:");
  scanf("%lf", &prize);
  sprintf(formal, "%s, %-19s: $%6.2f\n", last, first, prize);
  puts(formal);
}

void test8() {

  char S1[20] = "hello world";
  char S2[20] = {'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  char S3[20] = {'h', 'e', 'l', 'l', 'o', '\0', 'w', 'o', 'r', 'l', 'd', '\0'};
  char S4[20] = {'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
  char S5[] = "hello\0world";
  char S6[] = {'h', 'e', 'l', 'l', 'o', '\0', ' ',
               'w', 'o', 'r', 'l', 'd', '\0'};
  char S7[] = {'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  char S8[] = {
      'h', 'e', 'l', 'l', 'o', ' ',
      'w', 'o', 'r', 'l', 'd'}; // strlen(S8)产生未定义的结果，因为S8不是以'\0'结尾，strlen可能一直向前查找直到遇到空字符

  char *S9 = "hello world";
  printf("strlen(S1) = %zd ,\n strlen(S2) = %zd ,\n strlen(S3) = %zd ,\n "
         "strlen(S4) = %zd ,\n strlen(S5) = %zd ,\n strlen(S6) = %zd ,\n "
         "strlen(S7) = %zd ,\n strlen(S8) = %zd ,\n strlen(S9) = %zd\n",
         strlen(S1), strlen(S2), strlen(S3), strlen(S4), strlen(S5), strlen(S6),
         strlen(S7), strlen(S8), strlen(S9));

  printf("sizeof(S1) = %zd , sizeof(S2) = %zd , sizeof(S3) = %zd , sizeof(S4) "
         "= %zd , sizeof(S5) = %zd ,sizeof(S6) = %zd , sizeof(S7) = %zd , "
         "sizeof(S8) = %zd ,sizeof(S9) = %zd\n",
         sizeof(S1), sizeof(S2), sizeof(S3), sizeof(S4), sizeof(S5), sizeof(S6),
         sizeof(S7), sizeof(S8), sizeof(S9));

  printf("kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk"
         "kkkk\n");
  char a[] = "hello";
  printf("strlen(a) = %zd\n", strlen(a));
  printf("sizeof(a) = %zd\n\n", sizeof(a));
  printf("a = %s\n", a);

  char b[] = "hello\0";
  printf("strlen(b) = %zd\n", strlen(b));
  printf("sizeof(b) = %zd\n\n", sizeof(b));
  printf("b = %s\n", b);

  char c[] = "hello\n";
  printf("strlen(c) = %zd\n", strlen(c));
  printf("sizeof(c) = %zd\n\n", sizeof(c));
  printf("c = %s\n", c);

  char d[] = "hello\0\n";
  printf("strlen(d) = %zd\n", strlen(d));
  printf("sizeof(d) = %zd\n\n", sizeof(d));
  printf("d = %s\n", d);

  char e[] = "hello\n\0";
  printf("strlen(e) = %zd\n", strlen(e));
  printf("sizeof(e) = %zd\n\n", sizeof(e));
  printf("e = %s\n", e);

  char f[] = "hello\0\0\n";
  printf("strlen(f) = %zd\n", strlen(f));
  printf("sizeof(f) = %zd\n\n", sizeof(f));
  printf("f = %s\n", f);

  char g[] = "hello\n\0\0";
  printf("strlen(g) = %zd\n", strlen(g));
  printf("sizeof(g) = %zd\n\n", sizeof(g));
  printf("g = %s\n", g);

  char h[] = "hello\0\n\n";
  printf("strlen(h) = %zd\n", strlen(h));
  printf("sizeof(h) = %zd\n\n", sizeof(h));
  printf("h = %s\n", h);

  char i[] = "hello\n\n\0";
  printf("strlen(i) = %zd\n", strlen(i));
  printf("sizeof(i) = %zd\n\n", sizeof(i));
  printf("i = %s\n", i);

  char j[] = "hello\r\n";
  printf("strlen(j) = %zd\n", strlen(j));
  printf("sizeof(j) = %zd\n\n", sizeof(j));
  printf("j = %s\n", j);

  char k[] = "hello\n\r";
  printf("strlen(k) = %zd\n", strlen(k));
  printf("sizeof(k) = %zd\n\n", sizeof(k));
  printf("k = %s\n", k);
  return 0;

  //  strlen()只能以char
  //  *作为参数,不能以类型作为参数,该函数实际完成的功能是从代表该字符串的第一个地址开始遍历，直到遇到结束符'\0'。返回的长度大小不包括'\0'。
  //  c/c++ strlen(str)和str.length()和str.size()都可以求字符串长度。
  //  其中str.length()和str.size()是用于求string类对象长度的成员函数
  //  strlen(str)是用于求字符数组的长度，其参数是char*
}

int main(int argc, char *argv[]) {



  printf("**************************** test1 ******************************\n");
  test1();

  printf("**************************** test2 ******************************\n");
  test2();

  printf("**************************** test3 ******************************\n");
  test3();

  printf("**************************** test4 ******************************\n");
  test4();

  printf("**************************** test5 ******************************\n");
  test5();

  printf("**************************** test6 ******************************\n");
  test6();

  printf("**************************** test7 ******************************\n");
  test7();

  printf("**************************** test8 ******************************\n");
  test8();

}
/*
输出为：

strlen(S1) = 11 , strlen(S2) = 11 , strlen(S3) = 5 , strlen(S4) = 11 ,
strlen(S5) = 5 , strlen(S6) = 5 , strlen(S7) = 11 , strlen(S8) = 22 , strlen(S9)
= 11

sizeof(S1) = 20 , sizeof(S2) = 20 , sizeof(S3) = 20 , sizeof(S4) = 20 ,
sizeof(S5) = 12 ,sizeof(S6) = 13 , sizeof(S7) = 12 , sizeof(S8) = 11 ,sizeof(S9)
= 8 sizeof(S9)是求字符指针的字节数，为8个字节


 */
