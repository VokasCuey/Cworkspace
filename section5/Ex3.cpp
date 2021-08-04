//changes
#include <iostream>
#include <stdlib.h>
using namespace std;

int main()
{
    int num = 0;
    for (int i = 0; i <= 10; i++)
    {
        for (int j = 0; i + 2 * j <= 10; j++)
        {
            for (int k = 0; i + 2 * j + 5 * k <= 10; k++)
            {
                if (i + 2 * j + 5 * k == 10)
                {
                    num++;
                    cout << "NO." << num << ": " << i << " " << j << " " << k << endl;
                }
            }
        }
    }
    system("pause");
    return 0;
}