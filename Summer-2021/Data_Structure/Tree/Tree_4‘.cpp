#include <stdio.h>
#include <stdlib.h>
typedef enum
{
    OK,
    ERROR
} Status;

typedef float ElemType;

typedef struct Tree_Node
{
    ElemType Capacity;
    int ID;
    Tree_Node *Parent;
    Child_Node *First_Child;
    int Degree;
} TNode;

typedef struct Child_Node
{
    Tree_Node *Child;
    Child_Node *Next;
} CNode;

typedef struct Tree
{
    TNode *Root;
    int Depth;
    int Node_Num;
} Tree;

Status Init_Tree(Tree &T)
{
    T.Depth = 0;
    T.Node_Num = 0;
    T.Root = NULL;
    return OK;
}

Status Build_Tree(Tree &T, int Parent, int Child)
{
    TNode *p = NULL, *c = NULL;
    if (Parent == Child)
        return ERROR;
    for (int i = 0; i < T.Node_Num; i++)
    {
        if (T.Root[i].ID == Parent)
            p = T.Root + i;
        if (T.Root[i].ID == Child)
            c = T.Root + i;
        if ((i == T.Node_Num - 1) && (!(p && c)))
            return ERROR;
    }
    p->Degree++;
    c->Parent = p;
    if (p->First_Child == NULL)
    {
        p->First_Child = (CNode *)malloc(sizeof(CNode));
        p->First_Child->Child = c;
        p->First_Child->Next = NULL;
    }
    else
    {
        CNode *pc = p->First_Child;
        while (pc->Next)
            pc = pc->Next;
        pc->Next = (CNode *)malloc(sizeof(CNode));
        pc = pc->Next;
        pc->Next = NULL;
        pc->Child = c;
    }
}

Status In_Tree(FILE *rp, Tree &T)
{
    fscanf(rp, "%d", &T.Node_Num);
    T.Root = (TNode *)malloc(sizeof(TNode) * T.Node_Num);
    for (int i = 0; i < T.Node_Num; i++)
    {
        T.Root[i].ID = i + 1;
        T.Root[i].Degree = 0;
        T.Root[i].First_Child = NULL;
        T.Root[i].Parent = NULL;
        fscanf(rp, "%f", &T.Root[i].Capacity);
    }
    while (!feof(rp))
    {

        int Parent = 0;
        int Child = 0;
        fscanf(rp, "%d", &Parent);
        fgetc(rp);
        while (1)
        {
            fscanf(rp, "%d", &Child);
            Build_Tree(T, Parent, Child);
            char Skip = fgetc(rp);
            if (Skip == '\n')
                break;
        }
    }
    return OK;
}

int main()
{
    Tree T;
    Init_Tree(T);
    FILE *rp = fopen("data.txt", "r");
    FILE *wp = fopen("output.txt", "w");
    if (!(rp && wp))
    {
        printf("The file could not be opened.\n");
        return -1;
    }
    else
    {
        In_Tree(rp, T);
        fclose(rp);
        fclose(wp);
    }
    system("pause");
    return 0;
}