#include <iostream>
#include <malloc.h>
using namespace std;

typedef struct square_matrix
{
    int n;
    int **data;
} mat;

void create(mat &s, int n)
{
    s.n = n;
    s.data = (int **)malloc(sizeof(int *) * s.n);
    for (int i = 0; i < n; i++)
        s.data[i] = (int *)malloc(sizeof(int) * s.n);
}
int val(mat &s, int start, int x, int y, bool dirTag)
{
    if (start > s.n * s.n)
        return 0;
    bool valTag = true;
    for (int i = 0;; i++)
    {
        if (!valTag)
            break;
        if (x == 0 || y == 0 || x == s.n - 1 || y == s.n - 1)
            if (start == 1 || start == s.n * s.n || i)
                valTag = false;
        s.data[x][y] = start++;
        if (dirTag)
        {
            x--;
            y++;
        }
        else
        {
            x++;
            y--;
        }
    }
    dirTag = !dirTag;
    if (x == s.n)
        val(s, start, s.n - 1, y + 2, dirTag);
    else if (y == s.n)
        val(s, start, x + 2, s.n - 1, dirTag);
    else if (x == -1)
        val(s, start, 0, y, dirTag);
    else if (y == -1)
        val(s, start, x, 0, dirTag);
    return 0;
}
void print(mat s)
{
    for (int i = 0; i < s.n; i++)
    {
        for (int j = 0; j < s.n; j++)
            cout  << s.data[i][j] << ' ';
        cout << endl;
    }
}

int main()
{
    int n;
    cin >> n;
    mat s;
    create(s, n);
    val(s, 1, 0, 0, false);
    print(s);
    return 0;
}