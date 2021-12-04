#include <iostream>
#include <ctime>
using namespace std;
#define SIZE 100

void swap(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}
void quick_sort(int *array, int low, int high)
{
    if (low >= high)
        return;
    int M = (low + high + 1) / 2, left = low, right = high, L = 0, R = 0;
    int ref = array[M], leftNum = 0, rightNum = 0;
    int count = 0;
    bool Lpick = false, Rpick = false;
    while (count < high - low + 1)
    {
        while (1)
        {
            if (count == high - low + 1)
                break;
            L = left;
            if (left != M)
            {
                leftNum = array[left];
                if (L > M)
                    swap(L, M);
                if (leftNum > ref)
                {
                    Lpick = true;
                    break;
                }
                array[L] = leftNum;
            }
            left++;
            count++;
        }
        while (1)
        {
            if (count == high - low + 1)
                break;
            R = right;
            if (right != M)
            {
                rightNum = array[right];
                if (R < M)
                    swap(R, M);
                if (rightNum < ref)
                {
                    Rpick = true;
                    break;
                }
                array[R] = rightNum;
            }
            right--;
            count++;
        }
        if (Lpick && Rpick)
        {
            array[left] = rightNum;
            array[right] = leftNum;
        }
        else if (Lpick)
        {
            swap(L, M);
            array[L] = leftNum;
        }
        else if (Rpick)
        {
            swap(R, M);
            array[R] = rightNum;
        }
        Lpick = false;
        Rpick = false;
    }
    array[M] = ref;
    quick_sort(array, low, M - 1);
    quick_sort(array, M + 1, high);
}

int main()
{
    // int array[SIZE] = {3, 0, 4, 3, 9, 7, 6, 4, 4, 3};
    int *array = new int[SIZE];
    srand((unsigned int)time(NULL));
    for (int i = 0; i < SIZE; i++)
        array[i] = 100 * (float)rand() / RAND_MAX;
    quick_sort(array, 0, SIZE - 1);
    for (int i = 0; i < SIZE; i++)
        cout << array[i] << ' ';
    cout << endl;
    return 0;
}