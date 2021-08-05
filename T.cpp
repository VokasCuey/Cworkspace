#include <iostream>
#include <stdlib.h>
using namespace std;

int test(int n[4]);

int main()
{
    int n[4]={0};
    test(n);
    for (int i = 0; i < 4; i++)
    {
        cout << n[i] << endl;
    }
    system("pause");
    return 0;
}
int test(int n[4])
{
    for (int i=0;i<4;i++)
    {
        n[i]=i;
    }
    return 0;
}