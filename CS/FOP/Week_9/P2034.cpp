#include <iostream>
#include <malloc.h>
using namespace std;

void swap(int &x, int &y)
{
    int t = x;
    x = y;
    y = t;
}
void sort(int *array, int n)
{
    for (int i = 0; i < n; i++)
    {
        int min = array[i], pos = i;
        for (int j = i + 1; j < n; j++)
            if (array[j] < min)
            {
                min = array[j];
                pos = j;
            }
        swap(array[i], array[pos]);
        cout << "swap(a[" << i << "], a[" << pos << "]):";
        for (int k = 0; k < n; k++)
            cout << array[k] << ' ';
        cout << endl;
    }
}

int main()
{
    int n = 0;
    cin >> n;
    int *array = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        cin >> array[i];
    sort(array, n);
    return 0;
}