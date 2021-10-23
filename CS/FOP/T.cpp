#include <iostream>
#include <stdlib.h>
using namespace std;

void test(char a[3])
{
}

int main()
{
    string test;
    getline(cin, test);
    cout << test << endl;
    const char *a = test.c_str();
    cout << a << endl;
    system("pause");
    return 0;
}