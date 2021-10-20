#include <iostream>
#include "Print_Card.cpp"
#include "Max_Pos.cpp"
using namespace std;

int main()
{
    int maxNum=0;
    cin >> maxNum;
    for (int cardNum = 0; cardNum < Max_Pos(maxNum); cardNum++)
        Print_Card(cardNum,maxNum);
    return 0;
}