#include <stdio.h>
#include <stdlib.h>

#define BIT5 0x20
#define BIT2 0x04

char dataA = 0xb6;
char dataB = 0xd9;
char dataC = 0x5a;

int main()
{
    if((dataA&BIT2)==1)
    {printf("good\n");
    system("pause");
    return 0;}
    dataA &= ~BIT5; //第一条语句，等价为 dataA =dataA&(~BIT5);
    dataB |= BIT5;  //第二条语句，等价为 dataB=dataB|BIT5;
    dataC ^= BIT5;  //第三条语句，等价为 dataC =dataC^BIT5;
    printf("A=%d",int(dataA));
    system("pause");
    return 0;
}