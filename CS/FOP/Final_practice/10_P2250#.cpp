#include <iostream>
using namespace std;

#define OFFSET 233

int n = 0, m = 0;
int len[1005] = {0}, val[1005] = {0}, val_len[1005] = {0};

void sort()
{
    for (int i = 1; i <= n; i++)
        if (val[i] > val_len[len[i]])
            val_len[len[i]] = val[i];
}

int connect(int len1, int val1, int len2, int val2)
{
    int res = val1 + val2;
    if (len1 == len2)
        res += OFFSET;
    return res;
}

int cut(int x)
{
    for (int i = 1; i <= x; i++)
        for (int j = 0; j < i; j++)
        {
            int tmp = connect(j, val_len[j], i - j, val_len[i - j]);
            if (tmp > val_len[i])
                val_len[i] = tmp;
        }
    return val_len[x];
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> len[i];
    for (int i = 1; i <= n; i++)
        cin >> val[i];
    sort();
    cout << cut(m) << endl;
    return 0;
}