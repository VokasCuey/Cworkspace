#include <iostream>
using namespace std;

void step(int n, int m, int curX, int curY, int &total, bool **unStep)
{
    if (curX == n && curY == m)
    {
        total++;
        return;
    }
    int dir[4][2] = {{1, 2}, {2, 1}, {2, -1}, {1, -2}};
    for (int i = 0; i < 4; i++)
    {
        if (curX + dir[i][0] > n || curY + dir[i][1] > m || curY + dir[i][1] < 0)
            continue;
        if (unStep[curX + dir[i][0]][curY + dir[i][1]])
            continue;
        curX += dir[i][0];
        curY += dir[i][1];
        step(n, m, curX, curY, total, unStep);
        curX -= dir[i][0];
        curY -= dir[i][1];
    }
}

int main()
{
    int n = 0, m = 0, k = 0;
    cin >> n >> m >> k;
    bool **unStep = new bool *[n + 1]();
    for (int i = 0; i < n + 1; i++)
        unStep[i] = new bool[m + 1]();
    for (int i = 0; i < k; i++)
    {
        int tmp1 = 0, tmp2 = 0;
        cin >> tmp1 >> tmp2;
        unStep[tmp1][tmp2] = true;
    }
    int total = 0;
    step(n, m, 0, 0, total, unStep);
    cout << total << endl;
    return 0;
}