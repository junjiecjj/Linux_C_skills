#include<stdio.h>
#include<stdlib.h>


/* typedef struct stuff{ */
/*     int A ; */
/*     int B ; */
/* }jack; */


int returnA(void)
{
    int a = 123;
    printf("a = %d\n", a);
    return a;
}


char *returnStrStatic()
{
    static char p[]="hello world!";
    return p;
}

char *returnStr()
{
    char p[]="hello world!";
    return p;
}

int main(void)
{
    int aa = 222;
    printf("1 aa = %d\n", aa);
    aa = returnA();
    printf("2 aa = %d\n", aa);


    // char *str;
    // str=returnStr();
    // printf("%s\n", str);


    char *str;
    str=returnStrStatic();
    printf("%s\n", str);

    return 0;
}
