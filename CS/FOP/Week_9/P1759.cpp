#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

#define MAX_LENGTH 100

bool ltr_judge(char c)
{
    if (((c > 'a' - 1) && (c < 'z' + 1)) || ((c > 'A' - 1) && (c < 'Z' + 1)))
        return true;
    else
        return false;
}
bool num_judge(char c)
{
    if ((c > '0' - 1) && (c < '9' + 1))
        return true;
    else
        return false;
}
char trans(char ltr)
{
    if (num_judge(ltr))
        return ltr;
    else if (!ltr_judge(ltr))
        return '\0';
    else
        return (((ltr > 'A' - 1) && (ltr < 'Z' + 1)) ? (ltr + 'a' - 'A') : (ltr));
}

int str_judge(char str[MAX_LENGTH])
{
    int num = 0;
    for (int i = 0; i < strlen(str); i++)
        if (trans(str[i]))
            num++;
    for (int i = 0, j = strlen(str) - 1, k = 0; k < num / 2;)
    {
        char head = trans(str[i]), tail = trans(str[j]);
        if (head && tail)
        {
            k++;
            if (head != tail)
                return 0;
            i++;
            j--;
        }
        else
        {
            head ? j-- : i++;
            continue;
        }
    }
    return 1;
}

int main()
{
    char str[MAX_LENGTH] = {0};
    gets(str);
    cout << str_judge(str);
    // cout << trans('A');
    // cout << trans('b');
    // cout << trans('1');
    // cout << trans('/');
    // if ('\0')
    //     cout << 1;
    // else
    //     cout << 0;
    return 0;
}