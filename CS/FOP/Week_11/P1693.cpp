#include <iostream>
using namespace std;

int *merge_sort(int *array, int left, int right)
{
    if (left != right)
    {
        int *a = merge_sort(array, left, (left + right - 1) / 2);
        int *b = merge_sort(array, (left + right + 1) / 2, right);
        int *r = new int[right - left + 1];
        int k = 0;
        for (int i = 0, j = 0;; k++)
        {
            if (i == (right - left + 1) / 2)
            {
                for (; j < (right - left + 1) / 2; k++, j++)
                    r[k] = b[j];
                break;
            }
            else if (j == (right - left + 1) / 2)
            {
                for (; i < (right - left + 1) / 2; k++, i++)
                    r[k] = a[i];
                break;
            }
            else
            {
                if (a[i] < b[j])
                    r[k] = a[i++];
                else
                    r[k] = b[j++];
            }
        }
        for (int i = 0; i < right - left + 1; i++)
            cout << r[i] << ' ';
        cout << endl;
        return r;
    }
    else
    {
        int *one = new int[1];
        one[0] = array[left];
        return one;
    }
}

int main()
{
    int n = 0;
    cin >> n;
    int *array = new int[n];
    for (int i = 0; i < n; i++)
        cin >> array[i];
    merge_sort(array, 0, n - 1);
    return 0;
}