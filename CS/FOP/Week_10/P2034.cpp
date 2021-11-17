#include <iostream>
using namespace std;

void swap(int &x, int &y)
{
    int t = x;
    x = y;
    y = t;
}
void print(int i, int j, int *array, int n)
{
    cout << "swap(a[" << i << "], a[" << j << "]):";
    for (int i = 0; i < n; i++)
        cout << array[i] << ' ';
    cout << endl;
}
int sort(int *array, int n, int start)
{
    int min = array[start], pos = start;
    for (int i = start; i < n; i++)
        if (array[i] < min)
        {
            min = array[i];
            pos = i;
        }
    swap(array[start], array[pos]);
    print(start, pos, array, n);
    if (start == n - 1)
        return 0;
    sort(array, n, start + 1);
    return 0;
}

int main()
{
    int n = 0;
    cin >> n;
    int *array = new int[n];
    for (int i = 0; i < n; i++)
        cin >> array[i];
    sort(array, n, 0);
    return 0;
}