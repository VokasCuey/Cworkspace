#include <iostream>
using namespace std;

int dis_2(int x1, int y1, int x2, int y2)
{
    return ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int main()
{
    int n = 0, m = 0;
    cin >> n;
    int **dot = new int *[n + 1]();
    for (int i = 1; i <= n; i++)
        dot[i] = new int[2]();
    for (int i = 1; i <= n; i++)
        cin >> dot[i][0] >> dot[i][1];
    cin >> m;
    int **circle = new int *[m + 1]();
    for (int i = 1; i <= m; i++)
        circle[i] = new int[4]();
    for (int i = 1; i <= m; i++)
        cin >> circle[i][0] >> circle[i][1] >> circle[i][2];
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            if (dis_2(circle[i][0], circle[i][1], dot[j][0], dot[j][1]) <= circle[i][2] * circle[i][2])
                circle[i][3]++;
    for (int i = 1; i <= m; i++)
        cout << circle[i][3] << ' ';
    return 0;
}