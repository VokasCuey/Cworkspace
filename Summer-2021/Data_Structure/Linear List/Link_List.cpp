#include <stdio.h>
#include <stdlib.h>

typedef struct Element
{
    int ID;
    char Type[20];
    char Reg[20];
    char Ava[20];
    char Sta[20];
    char Life[20];
    char Runtime[20];
} ElemType;
const ElemType Empty = {0, {0}, {0}, {0}, {0}, {0}, {0}};

typedef struct LNode
{
    ElemType Elem;
    LNode *Next;
} Node, *Pt;

typedef struct LinkedList
{
    Node *Head;
    int Length;
} LinkList;

typedef enum
{
    OK,
    ERROR,
    INEQUAL,
    OVERFLOW
} Status;

Status InitLinkList(LinkList &L)
{
    L.Head = (Pt)malloc(sizeof(Node));
    if (!L.Head)
    {
        exit(OVERFLOW);
    }
    L.Length = 0;
    L.Head->Elem = Empty;
    L.Head->Next = NULL;
    L.Head->Next = NULL;
    return OK;
}

Status Read_Elem(FILE *f, ElemType &e)
{
    fscanf(f, "%d %s %s %s %s %s %s", &(e.ID), e.Type, e.Reg, e.Ava, e.Sta, e.Life, e.Runtime);
    return OK;
}

Status Insert_Elem(LinkList &L, int i, ElemType e)
{
    return OK;
}

int main()
{
    LinkList L = {NULL, 0};
    InitLinkList(L);
    FILE *rp = fopen("输入.txt", "r");
    FILE *wp = fopen("输出.txt", "w");
    if (!(rp && wp))
    {
        printf("The file could not be opened.\n");
    }
    else
    {
        int row_Num = 0, column_Num = 0;
        fscanf(rp, "%d %d", &row_Num, &column_Num);
        char Skip[100];
        fgets(Skip, 100, rp);
        fgets(Skip, 100, rp);
        ElemType e = Empty;
        Node *p = L.Head, *s;
        for (int i = 0; i < row_Num; i++)
        {
            Read_Elem(rp, e);
            s = (Pt)malloc(sizeof(Node));
            s->Elem = e;
            s->Next = NULL;
            p->Next = s;
            p = s;
        }
    }
    system("pause");
    return 0;
}