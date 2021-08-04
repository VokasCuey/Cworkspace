//changes
#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

bool nameCheck(char c[3]);
int fac(int n);
float power(float x, int n);
float sin(float x);
float cos(float x);
void Run(char c[3], float x);

int main()
{
    char fname[3];
    float x;
    cout << "Please enter the value of variable x." << endl;
    cin >> x;
    cout << "Please choose the name of funtion." << endl
         << "sin or cos." << endl;
    cin >> fname;
    Run(fname, x);
    system("pause");
    return 0;
}

bool nameCheck(char c[3])
{
    if (!strcmp(c, "sin"))
        return true;
    else if (!strcmp(c, "cos"))
        return false;
    else
    {
        cout << "There is an error in the name of function,Please rechoose the name of funtion." << endl
             << "sin or cos." << endl;
        cin >> c;
        nameCheck(c);
    }
}
int fac(int n)
{
    if (n < 0)
        return -1;
    else if (n == 0)
        return 1;
    else
    {
        int r = 1;
        for (int i = 1; i <= n; i++)
            r = r * i;
        return r;
    }
}
float power(float x, int n)
{
    if (n == 0)
        return 1;
    else if (n < 0)
        return 1 / power(x, -n);
    else
    {
        float r = 1;
        for (int i = 1; i <= n; i++)
            r = r * x;
        return r;
    }
}
float sin(float x)
{
    float r = 0;
    for (int i = 0; power(x, 2 * i + 1) / fac(2 * i + 1) > 1e-10; i++)
        r = r + power(x, 2 * i + 1) / fac(2 * i + 1) * power(-1, i);
    return r;
}
float cos(float x)
{
    float r = 0;
    for (int i = 0; power(x, 2 * i) / fac(2 * i) > 1e-10; i++)
        r = r + power(x, 2 * i) / fac(2 * i) * power(-1, i);
    return r;
}
void Run(char c[3], float x)
{
    float r = 0;
    if (nameCheck(c))
        r = sin(x);
    else
        r = cos(x);
    cout << c << "(" << x << ")=" << r << endl;
}