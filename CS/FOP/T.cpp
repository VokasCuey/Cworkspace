#include <iostream>
using namespace std;

int main()
{
    int a = 0, b = 0;
    cin >> a >> b;
    if (((a % 100) / 10) == b)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
    return 0;
}