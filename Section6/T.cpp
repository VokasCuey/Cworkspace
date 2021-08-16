#include <iostream>
#include <stdlib.h>
using namespace std;

typedef void (*fun)();
void f1();
void f2();
void f3();
void f4();
fun p[]={f1,f2,f3,f4};


int main()
{
    system ("pause");
    return 0;
}