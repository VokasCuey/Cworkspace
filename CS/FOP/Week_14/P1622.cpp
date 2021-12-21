#include <iostream>
using namespace std;

#define MAX(a, b) ((a > b) ? a : b)

int T = 0, M = 0;
int cost[105] = {0}, val[105] = {0};
int maxVal[105][1005] = {0};

int main()
{
    cin >> T >> M;
    for (int i = 1; i <= M; i++)
        cin >> cost[i] >> val[i];
    for (int i = 1; i <= M; i++)
        for (int j = 1; j <= T; j++)
        {
            if (cost[i] <= j)
                maxVal[i][j] = MAX(maxVal[i - 1][j], maxVal[i - 1][j - cost[i]] + val[i]);
            else
                maxVal[i][j] = maxVal[i - 1][j];
        }
    cout << maxVal[M][T];
    return 0;
}