#include <iostream>
#include <stdlib.h>
using namespace std;

int main()
{
    int year = 0;
    bool leapTag = false;
    cin >> year;
    if (((!(year % 4)) && (year % 100)) || (!(year % 400)))
        leapTag = true;
    int sub = year - 2021;
    for (int i = 2022; i < year; i++)
        if (((!(i % 4)) && (i % 100)) || (!(i % 400)))
            sub++;
    int startDay = (5 + sub) % 7;
    if (startDay == 0)
        startDay = 7;
    cout << " 01  ";
    for (int j = 0; j < startDay - 1; j++)
        cout << "   ";
    for (int month = 0; month < 12; month++)
    {
        int dayNum = 0;
        if (month == 1)
        {
            if (leapTag)
                dayNum = 29;
            else
                dayNum = 28;
        }
        else if (month == 0 || month == 2 || month == 4 || month == 6 || month == 7 || month == 9 || month == 11)
            dayNum = 31;
        else
            dayNum = 30;
        for (int day = 0; day < dayNum;)
        {
            cout << day++ + 1;
            if (startDay == 7)
            {
                startDay = 0;
                cout << endl;
                if (day == dayNum)
                    cout << " ";
                if ((dayNum - day < 7) && (month < 11))
                {
                    if (day != dayNum)
                        cout << " ";
                    if (month + 2 < 10)
                        cout << '0';
                    cout << month + 2;
                    cout << " ";
                    if (day == dayNum)
                        cout << " ";
                }
                else
                {
                    if (day + 1 > 9)
                        cout << "    ";
                    else
                        cout << "     ";
                }
            }
            else
            {
                if ((day + 1 > 9) && (day != dayNum))
                    cout << " ";
                else
                    cout << "  ";
            }
            startDay++;
        }
    }
    cout << endl;
    system("pause");
    return 0;
}