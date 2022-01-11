#include <iostream>
using namespace std;

const char text[] = "program";

void row(char **matrix, bool **IsText, int n, int x)
{
    for (int i = 1; i <= n; i++)
    {
        if (matrix[x][i] == text[0] && i + 6 <= n)
        {
            int p = 1, q = i + 1;
            for (; p <= 6; p++, q++)
                if (matrix[x][q] != text[p])
                    break;
            if (p == 7)
            {
                for (int k = 0; k <= 6; k++, i++)
                    IsText[x][i] = true;
            }
        }
    }
    for (int i = n; i >= 1; i--)
    {
        if (matrix[x][i] == text[0] && i - 6 >= 1)
        {
            int p = 1, q = i - 1;
            for (; p <= 6; p++, q--)
                if (matrix[x][q] != text[p])
                    break;
            if (p == 7)
            {
                for (int k = 0; k <= 6; k++, i--)
                    IsText[x][i] = true;
            }
        }
    }
}

void col(char **matrix, bool **IsText, int n, int x)
{
    for (int i = 1; i <= n; i++)
    {
        if (matrix[i][x] == text[0] && i + 6 <= n)
        {
            int p = 1, q = i + 1;
            for (; p <= 6; p++, q++)
                if (matrix[q][x] != text[p])
                    break;
            if (p == 7)
            {
                for (int k = 0; k <= 6; k++, i++)
                    IsText[i][x] = true;
            }
        }
    }
    for (int i = n; i >= 1; i--)
    {
        if (matrix[i][x] == text[0] && i - 6 >= 1)
        {
            int p = 1, q = i - 1;
            for (; p <= 6; p++, q--)
                if (matrix[q][x] != text[p])
                    break;
            if (p == 7)
            {
                for (int k = 0; k <= 6; k++, i--)
                    IsText[i][x] = true;
            }
        }
    }
}

void slope_pos(char **matrix, bool **IsText, int n)
{
    int b = 0;
    for (b = 1 - n; b <= n - 1; b++)
    {
        for (int y = (b <= 0 ? 1 - b : 1); y + b <= n && y <= n; y++)
        {
            if (matrix[y + b][y] == text[0] && y + b + 6 <= n && y + 6 <= n)
            {
                int p = 1, q = y + 1;
                for (; p <= 6; p++, q++)
                    if (matrix[q + b][q] != text[p])
                        break;
                if (p == 7)
                {
                    for (int k = 0; k <= 6; k++, y++)
                    {
                        IsText[y + b][y] = true;
                    }
                }
            }
        }
    }
    for (b = 1 - n; b <= n - 1; b++)
    {
        for (int y = (b > 0 ? n - b : n); y + b >= 1 && y >= 1; y--)
        {
            if (matrix[y + b][y] == text[0] && y + b - 6 >= 1 && y - 6 >= 1)
            {
                int p = 1, q = y - 1;
                for (; p <= 6; p++, q--)
                    if (matrix[q + b][q] != text[p])
                        break;
                if (p == 7)
                {
                    for (int k = 0; k <= 6; k++, y--)
                    {
                        IsText[y + b][y] = true;
                    }
                }
            }
        }
    }
}

void slope_neg(char **matrix, bool **IsText, int n)
{
    int b = 0;
    for (b = 2; b <= 2 * n; b++)
    {
        for (int y = (b < n + 1 ? 1 : b - n); - y + b <= n && y <= n && y >= 1 && -y + b >= 1; y++)
        {
            if (matrix[-y + b][y] == text[0] && -y + b - 6 <= n && y + 6 <= n && -y + b - 6 >= 1 && y + 6 >= 1)
            {
                int p = 1, q = y + 1;
                for (; p <= 6; p++, q++)
                    if (matrix[-q + b][q] != text[p])
                        break;
                if (p == 7)
                {
                    for (int k = 0; k <= 6; k++, y++)
                    {
                        IsText[-y + b][y] = true;
                    }
                }
            }
        }
    }
    for (b = 2; b <= 2 * n; b++)
    {
        for (int y = (b < n + 1 ? b - 1 : n); - y + b <= n && y <= n && y >= 1 && -y + b >= 1; y--)
        {
            if (matrix[-y + b][y] == text[0] && -y + b + 6 <= n && y - 6 <= n && -y + b + 6 >= 1 && y - 6 >= 1)
            {
                int p = 1, q = y - 1;
                for (; p <= 6; p++, q--)
                    if (matrix[-q + b][q] != text[p])
                        break;
                if (p == 7)
                {
                    for (int k = 0; k <= 6; k++, y--)
                    {
                        IsText[-y + b][y] = true;
                    }
                }
            }
        }
    }
}

void change(char **matrix, bool **IsText, int n)
{
    for (int i = 1; i <= n; i++)
    {
        row(matrix, IsText, n, i);
        col(matrix, IsText, n, i);
    }
    slope_pos(matrix, IsText, n);
    slope_neg(matrix, IsText, n);
}

int main()
{
    int n = 0;
    cin >> n;
    char **matrix = new char *[n + 1]();
    bool **IsText = new bool *[n + 1]();
    for (int i = 1; i <= n; i++)
    {
        matrix[i] = new char[n + 1]();
        IsText[i] = new bool[n + 1]();
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> matrix[i][j];
    change(matrix, IsText, n);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            cout << (IsText[i][j] ? matrix[i][j] : '*');
        cout << endl;
    }
    return 0;
}