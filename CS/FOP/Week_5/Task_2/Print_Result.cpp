#include <iostream>
using namespace std;

void Print_Result(int i)
{
    for (int j = 0; j < 6; j++)
        if (i & (1 << j))
            cout << char('A' + j) << " ";
    cout << endl;
}