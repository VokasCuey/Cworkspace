#include <iostream>
using namespace std;

int maxPlace = 0;
bool _try(int col, int n, int num, bool **place, bool *rowUnsafe, bool *LUnsafe, bool *RUnsafe)
{
    if (col == n)
    {
        num > maxPlace ? maxPlace = num : maxPlace = maxPlace;
        return true;
    }
    for (int row = 0; row < n + 1; row++)
    {
        if (row < n)
        {
            if (!place[row][col] || rowUnsafe[row] || LUnsafe[row + col] || RUnsafe[row - col + n - 1])
                continue;
            num++;
            rowUnsafe[row] = true;
            LUnsafe[row + col] = true;
            RUnsafe[row - col + n - 1] = true;
            _try(col + 1, n, num, place, rowUnsafe, LUnsafe, RUnsafe);
            num--;
            rowUnsafe[row] = false;
            LUnsafe[row + col] = false;
            RUnsafe[row - col + n - 1] = false;
        }
        else
            _try(col + 1, n, num, place, rowUnsafe, LUnsafe, RUnsafe);
    }
    return true;
}

int main()
{
    int n = 0;
    cin >> n;
    bool **place = new bool *[n]();
    for (int i = 0; i < n; i++)
        place[i] = new bool[n]();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            int tmp = 0;
            cin >> tmp;
            if (tmp)
                place[i][j] = true;
        }
    bool *rowUnsafe = new bool[n]();
    bool *LUnsafe = new bool[2 * n - 1]();
    bool *RUnsafe = new bool[2 * n - 1]();
    _try(0, n, 0, place, rowUnsafe, LUnsafe, RUnsafe);
    cout << maxPlace << endl;
    return 0;
}