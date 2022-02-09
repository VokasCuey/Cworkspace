#include <iostream>
using namespace std;

class person
{
public:
    int display(int a);

private:
    int num;

protected:
    char name;

public:
    int day;
    int month;
    int year;
};

int person::display(int a)
{
    cout << day << ' ' << month << ' ' << year << endl;
    cout << name << endl;
    cout << num << endl;
    return 1;
}

int main()
{
    person p;
    person *ptr = &p;
    return 0;
}