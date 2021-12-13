#include <iostream>
using namespace std;

#define MAX(a, b) ((a > b) ? a : b)
#define SIZE 1000

int pyramid[SIZE][SIZE] = {0}, maxVal[SIZE][SIZE] = {0};

void way(int n, int x, int y, int pyramid[SIZE][SIZE], int maxVal[SIZE][SIZE])
{
    if (x > n)
        return;
    if (x == 1)
        maxVal[0][0] = pyramid[0][0];
    else if (y == 1)
        maxVal[x - 1][y - 1] = maxVal[x - 2][y - 1] + pyramid[x - 1][y - 1];
    else if (y == n)
        maxVal[x - 1][y - 1] = maxVal[x - 2][y - 2] + pyramid[x - 1][y - 1];
    else
        maxVal[x - 1][y - 1] = MAX(maxVal[x - 2][y - 1], maxVal[x - 2][y - 2]) + pyramid[x - 1][y - 1];
}

int main()
{
    int n = 0;
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= i; j++)
            cin >> pyramid[i][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= i; j++)
            way(n, i + 1, j + 1, pyramid, maxVal);
    int max = 0;
    for (int i = 0; i < n; i++)
        if (maxVal[n - 1][i] > max)
            max = maxVal[n - 1][i];
    cout << max << endl;
    return 0;
}