#include <iostream>
#include <limits.h>
using namespace std;

int main()
{
    int n = 0, k = 0;
    cin >> n >> k;
    int *time = new int[n + 1]();
    int min = INT_MAX;
    int min1 = 0, min2 = 0;
    for (int i = 1; i <= n; i++)
        cin >> time[i];
    for (int i = 1; i <= n; i++)
    {
        int sum1 = 0;
        if ((i - 1 < k && n - i - k + 1 < k) || (i + k - 1 > n))
            continue;
        for (int j = i; j <= i + k - 1; j++)
            sum1 += time[j];
        for (int j = 1; j <= n; j++)
        {
            int sum2 = sum1;
            if ((j >= i && j <= i + k - 1) || (j + k - 1 >= i && j + k - 1 <= i + k - 1) || (j + k - 1 > n))
                continue;
            for (int t = j; t <= j + k - 1; t++)
                sum2 += time[t];
            if (sum2 < min)
            {
                min1 = i;
                min2 = j;
                min = sum2;
            }
        }
    }
    cout << min1 << ' ' << min2 << endl;
    return 0;
}