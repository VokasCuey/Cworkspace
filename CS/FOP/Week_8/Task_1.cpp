#include <iostream>
using namespace std;

int main()
{
    int m = 1, n = 2;
    int data[10];
    int k = 3;
    for (int i = 0; i < 20; i++)
    {
        data[i] = i * 3;
        cout << i << " --> " << m << ' ' << n << ' ' << k << endl;
    }
    return 0;
}