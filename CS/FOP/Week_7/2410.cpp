#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

#define JUDGE (((text[i] >= 'a') && (text[i] <= 'z')) || ((text[i] >= 'A') && (text[i] <= 'Z')))

int main()
{
    char text[50000];
    //char *text = new char;
    int totalNum = 0;
    int num[26] = {0};
    gets(text);
    for (int i = 0; i < strlen(text); i++)
        if (JUDGE)
        {
            totalNum++;
            for (int j = 0; j < 26; j++)
                if ((text[i] == 'a' + j) || (text[i] == 'A' + j))
                {
                    num[j]++;
                    break;
                }
        }
    for (int i = 0; i < 26; i++)
        printf("%c %.2f%\n", char('a' + i), (totalNum == 0 ? 0.0 : 100.0 * num[i] / totalNum));
    return 0;
}