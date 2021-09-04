#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum
{
    OK,
    ERROR
} Status;

typedef float ElemType;

typedef struct Child_Node
{
    int ID;
    Child_Node *Next;
} CNode;

typedef struct Tree_Node
{
    ElemType Capacity;
    int ID;
    Tree_Node *Parent;
    Child_Node *First_Child;
    int Degree;
} TNode;

typedef struct Tree
{
    TNode *Root;
    int Node_Num;
} Tree;

Status Init_Tree(Tree &T)
{
    T.Node_Num = 0;
    T.Root = NULL;
    return OK;
}

Status Build_Tree(Tree &T, int Parent, int Child)
{
    if (Parent == Child)
        return ERROR;
    TNode *p = NULL, *c = NULL;
    for (int i = 0; (i < T.Node_Num) && (!(p && c)); i++)
    {
        if (T.Root[i].ID == Parent)
            p = T.Root + i;
        if (T.Root[i].ID == Child)
            c = T.Root + i;
        if ((i == T.Node_Num - 1) && (!(p && c)))
            return ERROR;
    }
    p->Degree++;
    if (c)
        return ERROR;
    c->Parent = p;
    if (p->First_Child == NULL)
    {
        p->First_Child = (CNode *)malloc(sizeof(CNode));
        p->First_Child->ID = c->ID;
        p->First_Child->Next = NULL;
    }
    else
    {
        CNode *pc = p->First_Child;
        while (pc->Next)
            pc = pc->Next;
        pc->Next = (CNode *)malloc(sizeof(CNode));
        pc = pc->Next;
        pc->ID = c->ID;
        pc->Next = NULL;
    }
    return OK;
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
            if (fscanf(rp, "%d", &Child) == EOF)
                return OK;
            Build_Tree(T, Parent, Child);
            char Skip = fgetc(rp);
            if (Skip == '\n')
                break;
        }
    }
    return OK;
}

float Max_Capacity(Tree T, int ID)
{
    int Max = T.Root[ID - 1].Capacity;
    CNode *c = T.Root[ID - 1].First_Child;
    while (c)
    {
        Max += Max_Capacity(T, c->ID);
        c = c->Next;
    }
    return Max;
}

Status Print_Tree(FILE *wp, Tree T)
{
    for (int i = 0; i < T.Node_Num; i++)
        fprintf(wp, "%.1f ", Max_Capacity(T, i + 1));
    fputc('\n', wp);
    return OK;
}

Status Change_Tree(Tree T, int Node_ID, int Value)
{
    T.Root[Node_ID - 1].Capacity = Value;
    return OK;
}

Status Shift_Tree(Tree T, int Child, int Parent)
{
    if (Child == Parent)
        return ERROR;
    TNode *p = NULL, *c = NULL;
    for (int i = 0; (i < T.Node_Num) && (!(p && c)); i++)
    {
        if (T.Root[i].ID == Parent)
            p = T.Root + i;
        if (T.Root[i].ID == Child)
            c = T.Root + i;
        if ((i == T.Node_Num - 1) && (!(p && c)))
            return ERROR;
    }
    TNode *cp = c->Parent;
    cp->Degree--;
    if (cp->First_Child->ID == Child)
    {
        free(c->First_Child);
        c->First_Child = NULL;
    }
    else
    {
        CNode *cpc = cp->First_Child;
        while (cpc->Next->ID != Child)
        {
            cpc = cpc->Next;
            if (cpc == NULL)
                return ERROR;
        }
        CNode *Temp = cpc->Next;
        cpc->Next = cpc->Next->Next;
        free(Temp);
        Temp = NULL;
    }
    Build_Tree(T, Parent, Child);
    return OK;
}

int main()
{
    Tree T;
    Init_Tree(T);
    FILE *rp = fopen("data.txt", "r");
    FILE *op = fopen("operation.txt", "r");
    FILE *wp = fopen("output.txt", "w");
    if (!(rp && wp && op))
    {
        printf("The file could not be opened.\n");
        return -1;
    }
    else
    {
        In_Tree(rp, T);
        char Order[50];
        while (!feof(op))
        {
            memset(Order, 0, sizeof(Order));
            fgets(Order, 50, op);
            if (Order[0] == 'p')
                Print_Tree(wp, T);
            else if (Order[0] == 'c')
            {
                while (1)
                {
                    int Node_Num = 0;
                    float Value = 0;
                    if (fscanf(op, "%d %f", &Node_Num, &Value) == 0)
                        break;
                    Change_Tree(T, Node_Num, Value);
                }
            }
            else if (Order[0] == 's')
            {
                int Child = 0, Parent = 0;
                Child = Order[6] - '0';
                Parent = Order[8] - '0';
                Shift_Tree(T, Child, Parent);
            }
            else
                break;
        }
        fclose(rp);
        fclose(wp);
    }
    system("pause");
    return 0;
}