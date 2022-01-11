#include <iostream>
using namespace std;

const int month_day[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool IsLeap(int year)
{
    if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
        return true;
    return false;
}

int convert(int n)
{
    int day = n % 100;
    n = n / 100;
    int month = n % 100;
    n = n / 100;
    int year = n;
    int sum = 0;
    for (int i = 2022; i <= year; i++)
    {
        sum += 365;
        if (IsLeap(i - 1))
            sum += 1;
    }
    for (int i = 1; i < month; i++)
        sum += month_day[i];
    sum += day;
    return sum;
}

int main()
{
    int day1 = 0, day2 = 0;
    cin >> day1 >> day2;
    cout << convert(day2) - convert(day1) + 1 << endl;
    return 0;
}