#include <iostream>
#include <stdlib.h>
using namespace std;

int rDn(int n);

int main()
{
    int n=0;
    cout << "Please enter positive integer n." << endl;
    cin >> n;
    cout << "D" << n << " = " << rDn(n) << endl;
    system("pause");
    return 0;
}
int rDn(int n)
{
    if (n<=0)
    {
        return -1;
    }
    else if (n==1)
    {
        return 0;
    }
    else if (n==2)
    {
        return 1;
    }
    else
    {
        return (n-1)*(rDn(n-1)+rDn(n-2));
    }
    return 0;
}