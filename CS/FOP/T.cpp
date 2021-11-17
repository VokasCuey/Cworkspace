#include <iostream>
#include <cstring>
#include <cmath>
#include <stdlib.h>
#include <fstream>
#include <ctime>
using namespace std;

struct S
{
    int val;
    char str[10];
};

int main()
{
    S s1 = {110, "THU"};
    S s2;
    s2 = s1;
    cout << sizeof(s2.str);
    //system("pause");
    return 0;
}