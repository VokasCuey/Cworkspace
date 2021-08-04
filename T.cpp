#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;

bool Get(int x);
int maxNum(int n[4]);
int minNum(int n[4]);
int Run(int x);

int main()
{
    int x = 0;
    if (!Get(x))
    {Get(x);}
    Run(x);
    system("pause");
    return 0;
}
bool Get(int x)
{
    cout << "Please enter the value of integer x(999<x<10000)." << endl;
    cin >> x;
    if ((x>999)&&(x<10000))
    {return true;}
    else
    {return false;}
}
int maxNum(int n[4])
{
    int maxNum = 0;
    int Max[4] = {0};
    for (int i = 3; i >= 0; i--)
    {
        for (int j = 0; j <= i; j++)
        {
            if (n[j] > Max[i])
            {
                Max[i] = n[j];
            }
        }
        maxNum = maxNum + Max[i] * pow(10, i);
    }
    cout << "The max recofigurated integer is " << maxNum << endl;
    return maxNum;
}
int Run(int x)
{
    int n[4] = {0};
    for (int i = 3; i >= 0; i--)
    {
        n[i] = x;
        for (int j = i + 1; j < 4; j++)
        {
            n[i] = n[i] - n[j] * pow(10, j);
        }
        n[i] = n[i] / int(pow(10, i));
        cout << n[i] << " ";
    }
    cout << endl;
    return 0;
}
