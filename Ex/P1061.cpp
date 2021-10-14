#include <iostream>
#include <string.h>
using namespace std;

int startNum = 0, stopNum = 0, jamLength = 0;

bool Modify(char *jam, int bit)
{
    jam[bit - 2]++;
    for (int i = bit; i < jamLength + 1; i++)
        jam[i - 1] = jam[i - 2] + 1;
    if ((jam[jamLength - 1] - 'a' + 1 > stopNum) && (bit > 1))
    {
        Modify(jam, bit - 1);
        return true;
    }
    else if (bit == 1)
        return false;
    else
        return true;
}

int main()
{
    cin >> startNum >> stopNum >> jamLength;
    char string[26], *jam = (char *)malloc(sizeof(char) * jamLength);
    memset(string, 0, sizeof(string));
    cin >> string;
    strcpy(jam, string);
    for (int i = 0; i < 5; i++)
    {
        bool tag = true;
        jam[jamLength - 1]++;
        if (jam[jamLength - 1] - 'a' + 1 > stopNum)
            tag = Modify(jam, jamLength);
        if (tag)
            cout << jam << endl;
        else
            break;
    }
    return 0;
}