#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_S_SIZE 10000
typedef enum
{
    OK,
    ERROR
} Status;

typedef struct HString
{
    char *Head;
    int Length;
} String;

Status Init_String(String &S)
{
    S.Head = NULL;
    S.Length = 0;
    return OK;
}

Status Assign_String(String &S, char *Str)
{
    S.Head = (char *)malloc(sizeof(char) * strlen(Str));
    if (!S.Head)
        return ERROR;
    S.Length = strlen(Str);
    int i = 0;
    for (i = 0; i < S.Length; i++)
        S.Head[i] = Str[i];
    return OK;
}

Status In_String(FILE *rp, String &S)
{
    char In[MAX_S_SIZE];
    memset(In, 0, sizeof(In));
    fgets(In, MAX_S_SIZE, rp);
    Assign_String(S, In);
    return OK;
}

Status Gen_Next(String T, int *Next)
{
    Next[0] = 0;
    for (int j = 1; j <= T.Length; j++)
    {
        if (j == 1)
            Next[j] = 0;
        else
        {
            int Max_k = 0;
            for (int k = 2; k < j; k++)
            {
                int Tag = 0;
                for (int i = 1; i < k; i++)
                {
                    if (!(T.Head[i - 1] == T.Head[j - k + i - 1]))
                    {
                        Tag = 0;
                        break;
                    }
                    if (i == k - 1)
                    {
                        Tag = 1;
                        break;
                    }
                }
                if (Tag == 1)
                {
                    if (k > Max_k)
                    {
                        Max_k = k;
                    }
                }
            }
            if (Max_k == 0)
            {
                Next[j] = 1;
            }
            else
            {
                Next[j] = Max_k;
            }
        }
    }
    return OK;
}

int KMP(String S, String T)
{
    int Pos = 0;
    int *Next = (int *)malloc(sizeof(int) * (T.Length + 1));
    memset(Next, 0, sizeof(Next));
    Gen_Next(T, Next);
    for (int i = 1, j = 1; i < S.Length - T.Length + 1;)
    {
        if ((S.Head[i - 1] == T.Head[j - 1]) || (j == 0))
        {
            i++, j++;
        }
        else
        {
            j = Next[j];
        }
        if (j == T.Length + 1)
        {
            Pos = i - T.Length;
            break;
        }
    }
    return Pos;
}

int main()
{
    FILE *rp = fopen("In.txt", "r");
    if (!rp)
    {
        printf("The file could not be opened.\n");
        return -1;
    }
    else
    {
        String S, T;
        Init_String(S);
        Init_String(T);
        In_String(rp, S);
        In_String(rp, T);
        KMP(S, T);
        printf("The position is %d.\n", KMP(S, T));
        fclose(rp);
    }
    system("pause");
    return 0;
}