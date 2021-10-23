#include <iostream>
using namespace std;

int main()
{
    cout << "char:" << endl;
    char a[3] = {1, 2, 3};
    for (int i = 0; i < 3; i++)
        cout << sizeof(a[i]) << " " << (void *)&(a[i]) << " | ";
    cout << endl;
    cout << "int:" << endl;
    int b[3] = {1, 2, 3};
    for (int i = 0; i < 3; i++)
        cout << sizeof(b[i]) << " " << &(b[i]) << " | ";
    cout << endl;
    cout << "float:" << endl;
    float c[3] = {1, 2, 3};
    for (int i = 0; i < 3; i++)
        cout << sizeof(c[i]) << " " << &(c[i]) << " | ";
    cout << endl;
    cout << "double:" << endl;
    double d[3] = {1, 2, 3};
    for (int i = 0; i < 3; i++)
        cout << sizeof(d[i]) << " " << &(d[i]) << " | ";
    cout << endl;
    return 0;
}