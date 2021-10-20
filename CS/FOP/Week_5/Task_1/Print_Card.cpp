#include <iostream>
#include "Get_Bit.cpp"
#include "Output_Num.cpp"
using namespace std;

void Print_Card(int cardNum, int maxNum)
{
    cout << "Card:" << cardNum << endl;
    for (int i = 0, j = 0; i < maxNum; i++)
        if (Get_Bit(i + 1, cardNum))
        {
            j++;
            Output_Num(i+1);
            if (!(j % 6))
                cout << endl;
        }
    cout << endl
         << endl;
}