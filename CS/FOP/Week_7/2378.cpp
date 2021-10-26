#include <iostream>
#include <stdlib.h>
using namespace std;

typedef struct matrix
{
    int n;
    int *array;
} mat;

void init_m(mat m)
{
    m.n = 0;
    m.array = NULL;
}

void spin(mat m, int a, int b)
{
    int i[4] = {a, m.n - b + 1, m.n - a + 1, b};
    int j[4] = {b, a, m.n - b + 1, m.n - a + 1};
    int t = m.array[m.n * (i[0] - 1) + j[0] - 1];
    for (int k = 0; k < 3; k++)
        m.array[m.n * (i[k] - 1) + j[k] - 1] = m.array[m.n * (i[k + 1] - 1) + j[k + 1] - 1];
    m.array[m.n * (i[3] - 1) + j[3] - 1] = t;
}

int main()
{
    mat m;
    init_m(m);
    cin >> m.n;
    m.array = (int *)malloc(sizeof(int) * m.n * m.n);
    for (int i = 1; i <= m.n; i++)
        for (int j = 1; j <= m.n; j++)
            cin >> m.array[m.n * (i - 1) + j - 1];
    for (int i = 1; i <= m.n / 2; i++)
        for (int j = i; j <= m.n - i; j++)
            spin(m, i, j);
    for (int i = 1; i <= m.n; i++)
    {
        for (int j = 1; j <= m.n; j++)
            cout << m.array[m.n * (i - 1) + j - 1] << " ";
        cout << endl;
    }
    return 0;
}