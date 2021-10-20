#include <iostream>
using namespace std;

int main()
{
    int mul = 1;
    for (int i = 0; i < 100; i++)
    {
        mul *= (i + 1);
        printf("%3d", i + 1);
        cout << "!=";
        for (int j = 32; j > 0; j--)
            cout << ((mul & (1 << (j - 1))) >> (j - 1));
        cout << "=" << mul;
        cout << endl;
    }
    cout << "1*2*...*100=" << mul << endl;
    return 0;
}