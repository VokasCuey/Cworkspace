#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LH +1
#define EH 0
#define RH -1
#define Left 0
#define Right 1
#define MAX_SKIP_NUM 50
#define MAX_WORD_SIZE 20
typedef enum
{
    OK,
    ERROR
} Status;

typedef struct Elem
{
    int Key;
    char *Word;
} ElemType;

typedef struct AVL_Tree_Node
{
    ElemType Data;
    AVL_Tree_Node *Parent, *Child[2];
    int B_Factor;
    int Depth;
} TNode;

typedef struct AVL_Tree
{
    TNode *Root;
} Tree;

Status Init_Tree(Tree &T)
{
    T.Root = NULL;
    return OK;
}

Status Build(TNode *Parent, TNode *Child, int Pos)
{
    Child->Parent = Parent;
    Parent->Child[Pos] = Child;
    return OK;
}

int Depth_Num(TNode *Node, int Depth)
{
    int Num = 0;
    if (Node)
    {
        if (Node->Depth == Depth)
            Num++;
        Num += Depth_Num(Node->Child[Left], Depth) + Depth_Num(Node->Child[Right], Depth);
    }
    return Num;
}

int Max_Depth(TNode *Node)
{
    int Depth = 0;
    if (Node)
    {
        int L_Depth = Max_Depth(Node->Child[Left]);
        int R_Depth = Max_Depth(Node->Child[Right]);
        if (Node->Depth > Depth)
            Depth = Node->Depth;
        if (L_Depth > Depth)
            Depth = L_Depth;
        if (R_Depth > Depth)
            Depth = R_Depth;
    }
    return Depth;
}

Status Depth_Mod(TNode *Root, int Depth)
{
    if (Root)
    {
        Root->Depth = Depth;
        Depth++;
        Depth_Mod(Root->Child[Left], Depth);
        Depth_Mod(Root->Child[Right], Depth);
    }
    return OK;
}

Status BF_Mod(Tree &T, TNode *Node)
{
    if (Node)
    {
        if (!(Node->Child[Left] || Node->Child[Right]))
        {
            Node->B_Factor = EH;
        }
        else if (!Node->Child[Right])
            Node->B_Factor = Max_Depth(Node->Child[Left]) - Node->Depth;
        else if (!Node->Child[Left])
            Node->B_Factor = Node->Depth - Max_Depth(Node->Child[Right]);
        else
            Node->B_Factor = Max_Depth(Node->Child[Left]) - Max_Depth(Node->Child[Right]);
        BF_Mod(T, Node->Child[Left]);
        BF_Mod(T, Node->Child[Right]);
    }
    return OK;
}

Status LL(Tree &T, TNode *Node)
{
    TNode *p = Node->Child[Left];
    if (Node != T.Root)
        Node->Parent->Child[Left] == Node ? Build(Node->Parent, p, Left) : Build(Node->Parent, p, Right);
    if (T.Root == Node)
    {
        T.Root = p;
        p->Parent = NULL;
    }
    if (p->Child[Right])
        Build(Node, p->Child[Right], Left);
    else
        Node->Child[Left] = NULL;
    Build(p, Node, Right);
    Depth_Mod(T.Root, 1);
    BF_Mod(T, T.Root);
    return OK;
}

Status RR(Tree &T, TNode *Node)
{
    TNode *p = Node->Child[Right];
    if (Node != T.Root)
        Node->Parent->Child[Left] == Node ? Build(Node->Parent, p, Left) : Build(Node->Parent, p, Right);
    if (T.Root == Node)
    {
        T.Root = p;
        p->Parent = NULL;
    }
    if (p->Child[Left])
    {
        Build(Node, p->Child[Left], Right);
    }
    else
        Node->Child[Right] = NULL;
    Build(p, Node, Left);
    Depth_Mod(T.Root, 1);
    BF_Mod(T, T.Root);
    return OK;
}

Status LR(Tree &T, TNode *Node)
{
    RR(T, Node->Child[Left]);
    LL(T, Node);
    return OK;
}

Status RL(Tree &T, TNode *Node)
{
    LL(T, Node->Child[Right]);
    RR(T, Node);
    return OK;
}

Status Insert_Balance_Tree(Tree &T, TNode *Root)
{
    if (Root)
    {
        if (Root->B_Factor > LH)
        {
            if (Root->Child[Left]->B_Factor == LH)
                LL(T, Root);
            else if (Root->Child[Left]->B_Factor == RH)
                LR(T, Root);
            else
                return ERROR;
        }
        else if (Root->B_Factor < RH)
        {
            if (Root->Child[Right]->B_Factor == RH)
                RR(T, Root);
            else if (Root->Child[Right]->B_Factor == LH)
                RL(T, Root);
            else
                return ERROR;
        }
        if ((Root->B_Factor > LH) || (Root->B_Factor < RH))
            return ERROR;
        if (Root != T.Root)
            Insert_Balance_Tree(T, Root->Parent);
    }
    return OK;
}

Status Insert(Tree &T, int Key, char *Word)
{
    if (!T.Root)
    {
        T.Root = (TNode *)malloc(sizeof(TNode));
        T.Root->Data.Key = Key;
        T.Root->Data.Word = (char *)malloc(sizeof(char) * (strlen(Word) - 1));
        strcpy(T.Root->Data.Word, Word);
        T.Root->Parent = NULL;
        T.Root->Child[Left] = NULL;
        T.Root->Child[Right] = NULL;
        T.Root->Depth = 1;
        T.Root->B_Factor = EH;
    }
    else
    {
        TNode *p = T.Root, *pp = NULL;
        int Tag = 0;
        while (p)
        {
            pp = p;
            if (Key <= p->Data.Key)
            {
                p = p->Child[Left];
                Tag = Left;
            }
            else
            {
                p = p->Child[Right];
                Tag = Right;
            }
        }
        p = (TNode *)malloc(sizeof(TNode));
        p->Parent = NULL;
        p->Child[Left] = NULL;
        p->Child[Right] = NULL;
        p->B_Factor = EH;
        p->Depth = pp->Depth + 1;
        p->Data.Key = Key;
        p->Data.Word = (char *)malloc(sizeof(char) * (strlen(Word) + 1));
        strcpy(p->Data.Word, Word);
        Build(pp, p, Tag);
        BF_Mod(T, T.Root);
        if (pp != T.Root)
            Insert_Balance_Tree(T, pp);
    }
    return OK;
}

Status Delete_Balance_Tree(Tree &T, TNode *Root)
{
    if (Root->B_Factor > LH)
    {
        if (Root->Child[Left]->B_Factor >= 0)
            LL(T, Root);
        else
            LR(T, Root);
    }
    else if (Root->B_Factor < RH)
    {
        if (Root->Child[Right]->B_Factor <= 0)
            RR(T, Root);
        else
            RL(T, Root);
    }
    if (Root != T.Root)
        Delete_Balance_Tree(T, Root->Parent);
    return OK;
}

Status Delete(Tree &T, int Key)
{
    TNode *p = T.Root;
    while ((p->Data.Key != Key) && p)
        Key < p->Data.Key ? p = p->Child[Left] : p = p->Child[Right];
    if (!p)
        return ERROR;
    if (p == T.Root)
    {
        if (!(p->Child[Left] || p->Child[Right]))
        {
            free(T.Root);
        }
        else if (!p->Child[Right])
        {
            T.Root = T.Root->Child[Left];
            T.Root->Parent = NULL;
            T.Root->Child[Left] = NULL;
            T.Root->Child[Right] = NULL;
            T.Root->Depth = 1;
            T.Root->B_Factor = EH;
        }
        else if (!p->Child[Left])
        {
            T.Root = T.Root->Child[Right];
            T.Root->Parent = NULL;
            T.Root->Child[Left] = NULL;
            T.Root->Child[Right] = NULL;
            T.Root->Depth = 1;
            T.Root->B_Factor = EH;
        }
        else
        {
            TNode *Left_Max_Node = p->Child[Left];
            while (Left_Max_Node->Child[Right])
                Left_Max_Node = Left_Max_Node->Child[Right];
            int Old_Depth = Left_Max_Node->Depth;
            Left_Max_Node->Depth = p->Depth;
            TNode *s = Left_Max_Node->Parent;
            (Left_Max_Node == Left_Max_Node->Parent->Child[Left]) ? Left_Max_Node->Parent->Child[Left] = NULL : Left_Max_Node->Parent->Child[Right] = NULL;
            if (p->Child[Left])
                Build(Left_Max_Node, p->Child[Left], Left);
            Build(Left_Max_Node, p->Child[Right], Right);
            Left_Max_Node->B_Factor = p->B_Factor;
            T.Root = Left_Max_Node;
            T.Root->Parent = NULL;
            BF_Mod(T, T.Root);
            Delete_Balance_Tree(T, s);
        }
    }
    else if (!(p->Child[Left] || p->Child[Right]))
    {
        (p == p->Parent->Child[Left]) ? p->Parent->Child[Left] = NULL : p->Parent->Child[Right] = NULL;
        BF_Mod(T, T.Root);
        Delete_Balance_Tree(T, p->Parent);
    }
    else if (!p->Child[Right])
    {
        (p == p->Parent->Child[Left]) ? Build(p->Parent, p->Child[Left], Left) : Build(p->Parent, p->Child[Left], Right);
        BF_Mod(T, T.Root);
        Delete_Balance_Tree(T, p->Parent);
    }
    else if (!p->Child[Left])
    {
        (p == p->Parent->Child[Left]) ? Build(p->Parent, p->Child[Right], Left) : Build(p->Parent, p->Child[Right], Right);
        BF_Mod(T, T.Root);
        Delete_Balance_Tree(T, p->Parent);
    }
    else
    {
        TNode *Left_Max_Node = p->Child[Left];
        while (Left_Max_Node->Child[Right])
            Left_Max_Node = Left_Max_Node->Child[Right];
        int Old_Depth = Left_Max_Node->Depth;
        Left_Max_Node->Depth = p->Depth;
        TNode *s = Left_Max_Node->Parent;
        Delete_Balance_Tree(T, Left_Max_Node->Parent);
        (Left_Max_Node == Left_Max_Node->Parent->Child[Left]) ? Left_Max_Node->Parent->Child[Left] = NULL : Left_Max_Node->Parent->Child[Right] = NULL;
        (p == p->Parent->Child[Left]) ? Build(p->Parent, Left_Max_Node, Left) : Build(p->Parent, Left_Max_Node, Right);
        if (p->Child[Left])
            Build(Left_Max_Node, p->Child[Left], Left);
        Build(Left_Max_Node, p->Child[Right], Right);
        BF_Mod(T, T.Root);
        Delete_Balance_Tree(T, s);
    }
    free(p);
    return OK;
}

char *Find(Tree T, int Key)
{
    char *Word = NULL;
    TNode *p = T.Root;
    while (p)
    {
        if (Key == p->Data.Key)
        {
            Word = p->Data.Word;
            break;
        }
        else if (Key < p->Data.Key)
            p = p->Child[Left];
        else if (Key > p->Data.Key)
            p = p->Child[Right];
    }
    return Word;
}

Status Change(Tree &T, int Key, char *New_Word)
{
    TNode *p = T.Root;
    while (p)
    {
        if (Key == p->Data.Key)
            break;
        else if (Key < p->Data.Key)
            p = p->Child[Left];
        else if (Key > p->Data.Key)
            p = p->Child[Right];
    }
    if (p == NULL)
        return ERROR;
    p->Data.Word = NULL;
    p->Data.Word = (char *)realloc(p->Data.Word, sizeof(char) * (strlen(New_Word) + 1));
    strcpy(p->Data.Word, New_Word);
    return OK;
}

Status In_Tree(FILE *rp, Tree &T)
{
    char Skip[MAX_SKIP_NUM];
    fgets(Skip, MAX_SKIP_NUM, rp);
    int Key = 0;
    char Word[MAX_WORD_SIZE];
    memset(Word, 0, sizeof(Word));
    while (!feof(rp))
    {
        memset(Word, 0, sizeof(Word));
        fscanf(rp, "%d %s", &Key, Word);
        Insert(T, Key, Word);
    }
    return OK;
}

int main()
{
    Tree T;
    Init_Tree(T);
    FILE *rp = fopen("data.txt", "r");
    FILE *op = fopen("operation.txt", "r");
    FILE *wp = fopen("output.txt", "w");
    if (!(rp && op && wp))
    {
        printf("The file could not be opened.\n");
        return -1;
    }
    else
    {
        In_Tree(rp, T);
        while (!feof(op))
        {
            int Key = 0;
            char Order[MAX_WORD_SIZE];
            memset(Order, 0, sizeof(Order));
            fgets(Order, MAX_WORD_SIZE, op);
            if (Order[0] == 'i')
            {
                char Insert_Word[MAX_WORD_SIZE];
                memset(Insert_Word, 0, sizeof(Insert_Word));
                fscanf(op, "%d %s", &Key, Insert_Word);
                Insert(T, Key, Insert_Word);
            }
            else if (Order[0] == 'd')
            {
                fscanf(op, "%d", &Key);
                Delete(T, Key);
            }
            else if (Order[0] == 'f')
            {
                fscanf(op, "%d", &Key);
                fprintf(wp, "%s\n", Find(T, Key));
            }
            else if (Order[0] == 'c')
            {
                char New_Word[MAX_WORD_SIZE];
                memset(New_Word, 0, sizeof(New_Word));
                fscanf(op, "%d %s", &Key, New_Word);
                Change(T, Key, New_Word);
            }
        }
        fclose(rp);
        fclose(op);
        fclose(wp);
    }
    system("pause");
    return 0;
}