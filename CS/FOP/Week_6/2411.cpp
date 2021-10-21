#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

#define MAXLENGTH 5000
#define LETTERJUDGE (((Word[strlen(Word) - 1] >= 'a') && (Word[strlen(Word) - 1] <= 'z')) || ((Word[strlen(Word) - 1] >= 'A') && (Word[strlen(Word) - 1] <= 'Z')))

void Output(char *Word)
{
    if (LETTERJUDGE)
        cout << Word[strlen(Word) - 1];
    for (int i = strlen(Word) - 1; i > 0; i--)
        cout << Word[i - 1];
    if (!LETTERJUDGE)
        cout << Word[strlen(Word) - 1];
}

int main()
{
    char Words[MAXLENGTH], Word[MAXLENGTH];
    memset(Words, 0, sizeof(Words));
    memset(Word, 0, sizeof(Word));
    gets(Words);
    for (int i = 0; i < strlen(Words); i++)
    {
        Word[strlen(Word)] = Words[i];
        if ((!LETTERJUDGE) || (i == strlen(Words) - 1))
        {
            Output(Word);
            memset(Word, 0, sizeof(Word));
        }
    }
    return 0;
}