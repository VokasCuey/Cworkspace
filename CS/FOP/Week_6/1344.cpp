#include <iostream>
using namespace std;

void Output_array(int *array, int num)
{
    for (int i = 0; i < num; i++)
        cout << array[i] << " ";
    cout << endl;
}
bool Moveback(int *array, int num, int i)
{
    if (array[i - 1] >= array[i - 2])
        return false;
    else
    {
        int t = array[i - 1];
        array[i - 1] = array[i - 2];
        cout << "  Move back:";
        Output_array(array, num);
        array[i - 2] = t;
    }
    if (i == 2)
        return false;
    return true;
}
int main()
{
    int n = 0;
    cin >> n;
    int *array = new int[n]();
    for (int i = 0; i < n; i++)
    {
        cin >> array[i];
        cout << "Insert element[" << i + 1 << "]:" << endl;
        cout << "  Init:";
        Output_array(array, i + 1);
        if (i != 0)
            for (int j = i + 1; Moveback(array, i + 1, j); j--)
                ;
        cout << "  Final:";
        Output_array(array, i + 1);
    }
    return 0;
}