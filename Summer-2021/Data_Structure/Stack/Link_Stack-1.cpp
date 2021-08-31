#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    OK,
    ERROR
} Status;

typedef char ElemType;

typedef struct Stack_Node
{
    ElemType Data;
    Stack_Node *Next;
} Node;

typedef struct Linked_Stack
{
    Node *Top;
    int Length;
} LinkStack;

Status Init_LinkStack(LinkStack &S)
{
    S.Length = 0;
    S.Top = (Node *)malloc(sizeof(Node));
    S.Top->Next = NULL;
    S.Top->Data = 0;
    return OK;
}

Status Push_LinkStack(LinkStack &S, ElemType e)
{
    Node *p;
    p = (Node *)malloc(sizeof(Node));
    if (!p)
    {
        return ERROR;
    }
    p->Data = e;
    p->Next = S.Top->Next;
    S.Top->Next = p;
    S.Length++;
    return OK;
}

Status Pop_LinkStack(LinkStack &S)
{
    if (S.Top->Next == NULL)
    {
        return ERROR;
    }
    Node *p = S.Top->Next;
    S.Top->Next = p->Next;
    free(p);
    p = NULL;
    S.Length--;
    return OK;
}

Status Modify(FILE *wp, LinkStack &S, ElemType e)
{
    if (e == 'H')
    {
        Push_LinkStack(S, e);
        fprintf(wp, "Push %c\n", e);
    }
    else if (e == 'S')
    {
        Push_LinkStack(S, e);
        fprintf(wp, "Push %c\n", e);
        Pop_LinkStack(S);
        fprintf(wp, "Pop %c\n", e);
    }
    else
    {
        return ERROR;
    }
    return OK;
}

int main()
{
    LinkStack S;
    Init_LinkStack(S);
    FILE *rp = fopen("第一题输入.txt", "r");
    FILE *wp = fopen("第一题输出.txt", "w");
    if (!(rp && wp))
    {
        printf("The file could not be opened.\n");
        return ERROR;
    }
    else
    {
        int Num = 0;
        fscanf(rp, "%d", &Num);
        fgetc(rp);
        for (int i = 0; i < Num; i++)
        {
            Modify(wp, S, fgetc(rp));
        }
        while (S.Top->Next)
        {
            fprintf(wp, "Pop %c\n", S.Top->Next->Data);
            Pop_LinkStack(S);
        }
        fclose(rp);
        fclose(wp);
    }
    system("pause");
    return 0;
}