#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;

int maxNum(int n[4]);
int minNum(int n[4]);
int Run(int x);

int main()
{
    int x = 0;
    cout << "Please enter the value of integer x(999<x<10000)." << endl;
    cin >> x;
    for (int i = 1;; i++)
    {
        int r = Run(x);
        if (r != x)
        {
            x = r;
            cout << "Operation " << i << endl
                 << endl;
        }
        else
        {
            cout << endl
                 << "Operation end." << endl
                 << endl;
            break;
        }
    }
    cout << "The final result is " << x << endl;
    system("pause");
    return 0;
}
int maxNum(int n[4])
{
    int temp[4] = {n[0], n[1], n[2], n[3]};
    int maxNum = 0;
    int Max[4] = {0};
    for (int i = 3; i >= 0; i--)
    {
        for (int j = 0; j < 4; j++)
        {
            if (temp[j] > Max[i])
            {
                Max[i] = temp[j];
            }
        }
        for (int j = 0; j < 4; j++)
        {
            if (temp[j] == Max[i])
            {
                temp[j] = 0;
                break;
            }
        }
        maxNum = maxNum + Max[i] * pow(10, i);
    }
    cout << "The max recofigurated integer is " << maxNum << endl;
    return maxNum;
}
int minNum(int n[4])
{
    int temp[4] = {n[0], n[1], n[2], n[3]};
    int minNum = 0;
    int Min[4] = {9, 9, 9, 9};
    for (int i = 3; i >= 0; i--)
    {
        for (int j = 0; j < 4; j++)
        {
            if (temp[j] < Min[i])
            {
                if ((i == 3) && (temp[j] == 0))
                {
                    continue;
                }
                else
                {
                    Min[i] = temp[j];
                }
            }
        }
        for (int j = 0; j < 4; j++)
        {
            if (temp[j] == Min[i])
            {
                temp[j] = 9;
                break;
            }
        }
        minNum = minNum + Min[i] * pow(10, i);
    }
    cout << "The min recofigurated integer is " << minNum << endl;
    return minNum;
}
int Run(int x)
{
    int r = 0;
    int n[4] = {0};
    for (int i = 3; i >= 0; i--)
    {
        n[i] = x;
        for (int j = i + 1; j < 4; j++)
        {
            n[i] = n[i] - n[j] * pow(10, j);
        }
        n[i] = n[i] / int(pow(10, i));
    }
    r = maxNum(n) - minNum(n);
    return r;
}
