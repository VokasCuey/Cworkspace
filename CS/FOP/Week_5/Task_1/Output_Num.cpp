#include <iostream>
using namespace std;

void Output_Num(int i)
{
    cout << i;
    int num=0;
    for (int j=1;j<10000;j*=10,num++)
        if (!(i/j))
            break;
    for (int j=4-num;j>0;j--)
        cout << " ";
}