#include <iostream>
#include <ctime>
#include <cmath>
using namespace std;

#define SIZE 4000

long long a[SIZE] = {0}, minCost[SIZE] = {0}, cost[SIZE][SIZE] = {0};
bool getMin[SIZE] = {false};

long long min_cost(int cur, int n)
{
    if (cur > n)
        return 0;
    if (!getMin[cur])
    {
        long long min = cost[cur][n];
        for (int cut = cur; cut < n; cut++)
        {
            long long tmp = cost[cur][cut] + min_cost(cut + 1, n);
            if (tmp < min)
                min = tmp;
        }
        minCost[cur] = min;
        getMin[cur] = true;
    }
    return minCost[cur];
}

int main()
{
    int n = 0;
    long long l = 0;
    // cin >> n >> l;
    // for (int i = 1; i <= n; i++)
    //     cin >> a[i];
    srand((unsigned int)time(NULL));
    n = 3000;
    l = (int)(((float)rand() / RAND_MAX) *(pow(2,20)-1));
    for (int i = 1; i <= n; i++)
        a[i] = (int)(((float)rand() / RAND_MAX) * 100000);
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++)
        {
            long long sum = 0;
            for (int k = i; k <= j; k++)
                sum += a[k];
            cost[i][j] = (sum - l) * (sum - l);
        }
    cout << min_cost(1, n);
    return 0;
}