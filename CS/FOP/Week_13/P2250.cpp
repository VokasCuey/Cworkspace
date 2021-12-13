#include <iostream>
using namespace std;

#define OFFSET 233

int a[1000] = {0}, b[1000] = {0}, val[1000] = {0};

void sort(int n)
{
    for (int i = 0; i < n; i++)
        if (b[i] > val[a[i]])
            val[a[i]] = b[i];
}
int link(int len1, int len2, int val1, int val2)
{
    if (len1 == len2)
        return val1 + val2 + OFFSET;
    else
        return val1 + val2;
}
int cut(int m)
{
    for (int i = 1; i <= m; i++)
    {
        int max = 0, tmp = 0;
        for (int j = 1; j <= i; j++)
        {
            tmp = link(i - j, j, val[i - j], val[j]);
            if (tmp > max)
                max = tmp;
        }
        val[i] = max;
    }
    return val[m];
}

int main()
{
    int n = 0, m = 0;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n; i++)
        cin >> b[i];
    sort(n);
    cout << cut(m) << endl;
    return 0;
}