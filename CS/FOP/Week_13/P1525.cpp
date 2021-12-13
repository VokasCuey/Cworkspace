#include <iostream>
using namespace std;

int n = 0, m = 0;
int height[1005] = {0}, maxDes[1005] = {0}, must[105] = {0};
bool getMax[1005] = {0};

int max_destroy(int left, int right, int cur)
{
    if (left == right)
        return 0;
    if (!getMax[left])
    {
        int max = 0;
        for (int i = left + 1; i <= right; i++)
        {
            int num = 0;
            bool skip = false;
            for (int j = 0; j < m; j++)
                if ((must[j] > left && must[j] < i) || (must[j] > i && height[i] > height[must[j]]))
                {
                    skip = true;
                    break;
                }
            if (skip || height[i] < cur)
                continue;
            num = max_destroy(i, right, height[i]) + 1;
            if (num > max)
                max = num;
        }
        maxDes[left] = max;
        getMax[left] = true;
    }
    return maxDes[left];
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> height[i];
    cin >> m;
    for (int i = 0; i < m; i++)
        cin >> must[i];
    cout << max_destroy(-1, n - 1, 0) << endl;
    return 0;
}