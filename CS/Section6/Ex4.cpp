#include <iostream>
#include <stdlib.h>
using namespace std;

int main()
{
    int Length[5] = {0};
    int Depth = 0;
    int Dep[5];
    for (int i=0;i<4;i++)
    {
        Dep[i]=(i+2)*Length[i]+Length[i+1];
    }
    Dep[4]=6*Length[4]+Length[0];
    system("pause");
    return 0;
}