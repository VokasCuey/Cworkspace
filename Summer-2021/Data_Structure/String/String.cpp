#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
    OK,
    ERROR,
    OVERFLOW
} Status;

typedef struct HString
{
    char *Head;
    int Length;
} String;
const String Empty = {NULL, 0};

Status Init_String(String &Str)
{
    Str.Head = NULL;
    Str.Length = 0;
}

Status Assign_String(String &Str, char *T)
{
    Str.Head = (char *)malloc(sizeof(char) * strlen(T));
    if (!Str.Head)
        return ERROR;
    Str.Length = strlen(T);
    char *p = Str.Head;
    for (int i = 0; i < Str.Length; i++)
    {
        *p = T[i];
        p++;
    }
    return OK;
}

String Concat_String(String S1, String S2)
{
    String S;
    Init_String(S);
    S.Length = S1.Length + S2.Length;
    S.Head = (char *)malloc(sizeof(char) * S.Length);
    if (!S.Head)
        return Empty;
    int j = 0;
    for (int i = 0; i < S1.Length; i++, j++)
    {
        S.Head[j] = S1.Head[i];
    }
    for (int i = 0; i < S2.Length; i++, j++)
    {
        S.Head[j] = S2.Head[i];
    }
    S.Head[j] = '\0';
    return S;
}

int main()
{
    String Str;
    Init_String(Str);
    char *test = "abcdef";
    Assign_String(Str, test);
    system("pause");
    return 0;
}