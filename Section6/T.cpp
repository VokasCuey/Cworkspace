#include <iostream>
#include <stdlib.h>
using namespace std;

int main()
{
    float avgLake = 0.0;
    int Lake[5][5];
    int(*p)[5] = Lake;
    int *t = &Lake[4][4];
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            Lake[i][j] = i * j + j;
        }
    }
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << p[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << *(*(Lake + i) + j) << " ";
        }
        cout << endl;
    }
    do
    {
        cout << *t << endl;
        t--;
    } while (t >= Lake[0]);
    system("pause");
    return 0;
}
