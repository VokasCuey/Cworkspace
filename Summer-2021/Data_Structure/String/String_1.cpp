#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STRING_SIZE 100
typedef enum
{
    OK,
    ERROR
} Status;

typedef struct String
{
    char Str[MAX_STRING_SIZE+1];
    int Length;
} String;

Status Init_String(String &S)
{
    S.Length=0;
    memset(S.Str,0,sizeof(S.Str));
}

Status Concat_String(String &S, String T)
{
    if ((S.Length+T.Length)>MAX_STRING_SIZE) printf("The string would be cut off.\n");
    int i=0;
    for (i=0;(i<T.Length)&&((S.Length+i)<MAX_STRING_SIZE);i++)
    {
        S.Str[i+S.Length]=T.Str[i];
    }
    S.Str[S.Length+i]='\0';
    if ((S.Length+T.Length)>MAX_STRING_SIZE) S.Length=MAX_STRING_SIZE;
    else S.Length+=T.Length;
    return OK;
}

int main()
{
    system("pause");
    return 0;
}