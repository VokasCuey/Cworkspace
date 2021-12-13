#include <iostream>
using namespace std;

#define SIZE 4000
int n = 0, l = 0;
long long a[SIZE] = {0}, cost[SIZE] = {0};

long long _cost(int i, int j)
{
    long long sum = 0;
    for (int k = i; k <= j; k++)
        sum += a[k];
    return (sum - l) * (sum - l);
}
long long min_cost()
{
    for (int i = 1; i <= n; i++)
    {
        long long min = _cost(1, i);
        for (int j = 1; j <= i; j++)
        {
            long long tmp = cost[i - j] + _cost(i - j + 1, i);
            if (tmp < min)
                min = tmp;
        }
        cost[i] = min;
    }
    return cost[n];
}
int main()
{
    cin >> n >> l;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    cout << min_cost() << endl;
    return 0;
}