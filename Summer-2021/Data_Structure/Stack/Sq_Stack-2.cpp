#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OPP_STACK_SIZE 100

typedef enum
{
    OK,
    ERROR,
    OVERFLOW
} Status;

typedef int ElemType;

typedef struct Opposite_Stack
{
    ElemType Opp_Stack[OPP_STACK_SIZE];
    int Bottom_0;
    int Top_0;
    int Length_0;
    int Bottom_1;
    int Top_1;
    int Length_1;
} OppStack;

Status Init_OppStack(OppStack &S)
{
    memset(S.Opp_Stack, 0, sizeof(S.Opp_Stack));
    S.Bottom_0 = 0;
    S.Top_0 = 0;
    S.Length_0 = 0;
    S.Bottom_1 = OPP_STACK_SIZE - 1;
    S.Top_1 = OPP_STACK_SIZE - 1;
    return OK;
}

Status Push_OppStack(OppStack &S, int i, ElemType e)
{
    if ((S.Top_1 - S.Top_0 <= 1))
        return OVERFLOW;
    if (i == 0)
    {
        S.Top_0++;
        S.Opp_Stack[S.Top_0] = e;
    }
    else if (i == 1)
    {
        S.Top_1--;
        S.Opp_Stack[S.Top_1] = e;
    }
    else
    {
        return ERROR;
    }
    return OK;
}

Status Pop_OppStack(OppStack &S, int i)
{
    if (i == 0)
    {
        if (S.Top_0 == S.Bottom_0)
            return ERROR;
        S.Opp_Stack[S.Top_0] = 0;
        S.Top_0--;
    }
    else if (i == 1)
    {
        if (S.Top_1 == S.Bottom_1)
            return ERROR;
        S.Opp_Stack[S.Top_1] = 0;
        S.Top_1++;
    }
    else
    {
        return ERROR;
    }
    return OK;
}

int main()
{
    OppStack S;
    Init_OppStack(S);
    Push_OppStack(S, 0, 5);
    Push_OppStack(S, 1, 8);
    Pop_OppStack(S, 1);
    Pop_OppStack(S, 0);
    system("pause");
    return 0;
}
