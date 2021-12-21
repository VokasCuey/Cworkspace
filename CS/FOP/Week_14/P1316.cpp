#include <iostream>
#include <cstring>
using namespace std;

#define MAX(a, b) ((a > b) ? a : b)
#define MAXLEN 1005

char str1[MAXLEN] = {0}, str2[MAXLEN] = {0};
int subLen[MAXLEN][MAXLEN] = {0};

int main()
{
    cin >> str1 >> str2;
    for (int i = 1; i <= strlen(str1); i++)
        for (int j = 1; j <= strlen(str2); j++)
        {
            if (str1[i - 1] == str2[j - 1])
                subLen[i][j] = subLen[i - 1][j - 1] + 1;
            else
                subLen[i][j] = MAX(subLen[i - 1][j], subLen[i][j - 1]);
        }
    cout << subLen[strlen(str1)][strlen(str2)] << endl;
    return 0;
}