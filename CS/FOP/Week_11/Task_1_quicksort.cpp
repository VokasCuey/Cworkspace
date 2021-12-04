#include <iostream>
#include <ctime>
using namespace std;
#define SIZE 1000

// 交换两个int型变量的值
void swap(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}
void quick_sort(int *array, int low, int high)
{
    // 序列中仅含一个元素时无需排序
    if (low >= high)
        return;
    // 选择中间元素为pivot，left/right指向从左/右开始当前所找的数的下标
    // L，M，R按从小到大的顺序指向取走元素之后的空位下标
    int M = (low + high + 1) / 2, left = low, right = high, L = 0, R = 0;
    // ref为所取中间元素的值，设其为参考值
    // leftNum/rightNum为从左/右开始当前所找到的数的值
    int ref = array[M], leftNum = 0, rightNum = 0;
    // 计数，当遍历完当前序列中所有数时跳出排序循环
    int count = 0;
    // Lpick/Rpick代表从左/右开始是否找到了比ref大/小的元素
    // 一开始默认未找到置为false，置为true则代表找到了
    bool Lpick = false, Rpick = false;
    // 当遍历完当前序列中所有数时跳出排序循环
    while (count < high - low + 1)
    {
        // 从左往右寻找比ref大的元素
        while (1)
        {
            // 当遍历完当前序列中所有数时跳出排序循环
            if (count == high - low + 1)
                break;
            // L指向当前访问位置
            L = left;
            if (left != M)
            {
                // 取出当前位置元素，记为leftNum
                leftNum = array[left];
                // 如果当前位置比原有空位大，调换两者
                if (L > M)
                    swap(L, M);
                // 如果leftNum>ref，则说明已找到需要的元素，跳出循环
                if (leftNum > ref)
                {
                    Lpick = true;
                    break;
                }
                // 如果leftNum<=ref，则将其放在最左边的空位上
                array[L] = leftNum;
            }
            // 向右跳至下一个位置
            left++;
            // 访问一个位置后计数增加
            count++;
        }
        // 从右向左寻找比ref小的元素
        while (1)
        {
            // 当遍历完当前序列中所有数时跳出排序循环
            if (count == high - low + 1)
                break;
            // R指向当前访问位置
            R = right;
            if (right != M)
            {
                // 取出当前位置元素，记为rightNum
                rightNum = array[right];
                // 如果当前位置比原有空位小，调换两者
                if (R < M)
                    swap(R, M);
                // 如果rightNum<ref，则说明已找到需要的元素，跳出循环
                if (rightNum < ref)
                {
                    Rpick = true;
                    break;
                }
                // 如果rightNum>=ref，则将其放在最右边的空位上
                array[R] = rightNum;
            }
            // 向左跳至下一个位置
            right--;
            // 访问一个位置后计数增加
            count++;
        }
        // 如果两边都找到了符合要求的数，则为一般情况
        // 此时leftNum>ref>rightNum，L<M<R
        if (Lpick && Rpick)
        {
            // 将右边找到的数放在最左边空位上
            array[L] = rightNum;
            // 将左边找到的数放在最右边空位上
            array[R] = leftNum;
        }
        // 如果仅有左边找到了符合要求的数
        // 此时leftNum>ref，L<M，需要将leftNum放在最右边空位上
        // 故应将leftNum放在M所指向位置，应互换L，M的值
        else if (Lpick)
        {
            swap(L, M);
            array[L] = leftNum;
        }
        // 如果仅有右边找到了符合要求的数
        // 此时rightNum<ref，R>M，需要将rightNum放在最左边的空位上
        // 故应将rightNum放在M所指向位置，应互换R，M的值
        else if (Rpick)
        {
            swap(R, M);
            array[R] = rightNum;
        }
        // 重置两个标志
        Lpick = false;
        Rpick = false;
    }
    // 剩余空位即为ref所应处于的位置
    array[M] = ref;
    // 对左子序列进行排序
    quick_sort(array, low, M - 1);
    // 对右子序列进行排序
    quick_sort(array, M + 1, high);
}

int main()
{
    int *array = new int[SIZE];
    srand((unsigned int)time(NULL));
    // 随机生成SIZE个0~1000的数
    for (int i = 0; i < SIZE; i++)
        array[i] = 1000 * (float)rand() / RAND_MAX;
    // 输出原始序列
    for (int i = 0; i < SIZE; i++)
        cout << array[i] << ' ';
    cout << endl;
    // 调用重构的快速排序函数
    quick_sort(array, 0, SIZE - 1);
    // 输出排序后的序列
    for (int i = 0; i < SIZE; i++)
        cout << array[i] << ' ';
    cout << endl;
    // 对排序结果进行检验
    for (int i = 0; i < SIZE - 1; i++)
        if (array[i] > array[i + 1])
            cout << "Error" << endl;
    return 0;
}