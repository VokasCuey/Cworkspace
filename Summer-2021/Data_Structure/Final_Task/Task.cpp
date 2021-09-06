#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LH +1
#define EH 0
#define RH -1
#define Left 0
#define Right 1
#define None 0
#define MAX_SKIP_NUM 100
#define MAX_WORD_LENGTH 50
#define OK 0
#define ERROR -1

typedef struct Elem
{
    int ID;
    char *Name;
    int Tag;
    int Loc;
    int Loc1;
    char *Status;
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

int Init_Tree(Tree &T)
{
    T.Root = NULL;
    return OK;
}

int Build(TNode *Parent, TNode *Child, int Pos)
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

int Depth_Mod(TNode *Root, int Depth)
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

int BF_Mod(Tree &T, TNode *Node)
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

int LL(Tree &T, TNode *Node)
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

int RR(Tree &T, TNode *Node)
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

int LR(Tree &T, TNode *Node)
{
    RR(T, Node->Child[Left]);
    LL(T, Node);
    return OK;
}

int RL(Tree &T, TNode *Node)
{
    LL(T, Node->Child[Right]);
    RR(T, Node);
    return OK;
}

int Insert_Balance_Tree(Tree &T, TNode *Root)
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

int Insert(Tree &T, int ID, char *Name, int Tag, int Loc, int Loc1, char *Status)
{
    if (!T.Root)
    {
        T.Root = (TNode *)malloc(sizeof(TNode));
        if (!T.Root)
            return ERROR;
        T.Root->Data.ID = ID;
        T.Root->Data.Name = (char *)malloc(sizeof(char) * (strlen(Name) + 1));
        if (!T.Root->Data.Name)
            return ERROR;
        strcpy(T.Root->Data.Name, Name);
        T.Root->Data.Tag = Tag;
        T.Root->Data.Loc = Loc;
        T.Root->Data.Loc1 = Loc1;
        T.Root->Data.Status = (char *)malloc(sizeof(char) * (strlen(Status) + 1));
        if (!T.Root->Data.Status)
            return ERROR;
        strcpy(T.Root->Data.Status, Status);
        T.Root->Parent = NULL;
        T.Root->Child[Left] = NULL;
        T.Root->Child[Right] = NULL;
        T.Root->Depth = 1;
        T.Root->B_Factor = EH;
    }
    else
    {
        TNode *p = T.Root, *pp = NULL;
        int Pos = 0;
        while (p)
        {
            pp = p;
            if (ID <= p->Data.ID)
            {
                p = p->Child[Left];
                Pos = Left;
            }
            else
            {
                p = p->Child[Right];
                Pos = Right;
            }
        }
        p = (TNode *)malloc(sizeof(TNode));
        if (!p)
            return ERROR;
        p->Parent = NULL;
        p->Child[Left] = NULL;
        p->Child[Right] = NULL;
        p->B_Factor = EH;
        p->Depth = pp->Depth + 1;
        p->Data.ID = ID;
        p->Data.Name = (char *)malloc(sizeof(char) * (strlen(Name) + 1));
        if (!p->Data.Name)
            return ERROR;
        strcpy(p->Data.Name, Name);
        p->Data.Tag = Tag;
        p->Data.Loc = Loc;
        p->Data.Loc1 = Loc1;
        p->Data.Status = (char *)malloc(sizeof(char *) * (strlen(Status) + 1));
        if (!p->Data.Status)
            return ERROR;
        strcpy(p->Data.Status, Status);
        Build(pp, p, Pos);
        BF_Mod(T, T.Root);
        if (pp != T.Root)
            Insert_Balance_Tree(T, pp);
    }
    return OK;
}

int Delete_Balance_Tree(Tree &T, TNode *Root)
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

int Delete(Tree &T, int ID)
{
    TNode *p = T.Root;
    while (p)
    {
        if (p->Data.ID != ID)
            ID < p->Data.ID ? p = p->Child[Left] : p = p->Child[Right];
        else
            break;
    }
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
//wait to modify
int Find(TNode *Root, int Loc0, int &Num)
{
    if (Root)
    {
        if (((Root->Data.Loc == Loc0) || (Root->Data.Loc1 == Loc0)) && (Root->Data.Tag == 1))
        {
            printf("ID=%d\n",Root->Data.ID);
            Num++;
        }
        Find(Root->Child[Left],Loc0,Num);
        Find(Root->Child[Right],Loc0,Num);
    }
    return Num;
}

int Print(Tree &T, int ID)
{
    TNode *p = T.Root;
    while (p)
    {
        if (p->Data.ID == ID)
            break;
        else
            ID < p->Data.ID ? p = p->Child[Left] : p = p->Child[Right];
    }
    if (p == NULL)
    {
        printf("Print Error.\n");
        return ERROR;
    }
    if (p->Data.Tag == 0)
        printf("ID:%d \nDevice:%s \nLocation:AT %d \nStatus:Status %s", p->Data.ID, p->Data.Name, p->Data.Loc, p->Data.Status);
    else if (p->Data.Tag == 1)
        printf("ID:%d \nDevice:%s \nLocation:FROM %d TO %d\nStatus:Status %s", p->Data.ID, p->Data.Name, p->Data.Loc, p->Data.Loc1, p->Data.Status);
    else
    {
        printf("Print Error.\n");
        return ERROR;
    }
    return OK;
}
//wait to modify
int Change(Tree &T, int ID, char *New_Status)
{
    TNode *p = T.Root;
    while (p)
    {
        if (ID == p->Data.ID)
            break;
        else if (ID < p->Data.ID)
            p = p->Child[Left];
        else if (ID > p->Data.ID)
            p = p->Child[Right];
    }
    if (p == NULL)
        return ERROR;
    p->Data.Status = (char *)realloc(p->Data.Status, sizeof(char) * (strlen(New_Status) + 1));
    strcpy(p->Data.Status, New_Status);
    return OK;
}

int In_Tree(FILE *rp, Tree &T)
{
    char Skip[MAX_SKIP_NUM];
    memset(Skip, 0, sizeof(Skip));
    fgets(Skip, MAX_SKIP_NUM, rp);
    int ID = 0, Tag = 0, Loc = 0, Loc1 = 0;
    char Name[MAX_WORD_LENGTH];
    memset(Name, 0, sizeof(Name));
    char Status[MAX_WORD_LENGTH];
    memset(Status, 0, sizeof(Status));
    while (!feof(rp))
    {
        if (fscanf(rp, "%d %s", &ID, Name) == EOF)
            break;
        char c = '\0';
        while (!((c == 'F') || (c == 'A')))
            c = fgetc(rp);
        if (c == 'F')
        {
            Tag = 1;
            fscanf(rp, "%s %d %s %d", Skip, &Loc, Skip, &Loc1);
        }
        else
        {
            Tag = 0;
            fscanf(rp, "%s %d", Skip, &Loc);
            Loc1 = None;
        }
        while (c != 'S')
            c = fgetc(rp);
        fscanf(rp, "%s", Skip);
        fgets(Status, MAX_WORD_LENGTH, rp);
        Insert(T, ID, Name, Tag, Loc, Loc1, Status);
    }
    return OK;
}

int main()
{
    Tree T;
    Init_Tree(T);
    FILE *rp = fopen("电气设备表.txt", "r");
    if (!rp)
    {
        printf("The file could not be opened.\n");
        return -1;
    }
    else
    {
        In_Tree(rp, T);
        char Order[MAX_WORD_LENGTH];
        while (1)
        {
            memset(Order, 0, sizeof(Order));
            printf("Please enter your order.\n");
            gets(Order);
            printf("-------------------------------\n");
            if (Order[0] == 'i')
            {
            }
            else if (Order[0] == 'd')
            {
                int ID = 0;
                printf("Please enter the ID of the device.\nID=");
                scanf("%d", &ID);
                printf("-------------------------------\n");
                if (Delete(T, ID) == ERROR)
                    printf("Delete Error.\n");
                else
                    printf("Delete Complete.\n");
                printf("-------------------------------\n");
            }
            else if (Order[0] == 'c')
            {
            }
            else if (Order[0] == 'p')
            {
                int ID = 0;
                printf("Please enter the ID of the device.\nID=");
                scanf("%d", &ID);
                printf("-------------------------------\n");
                Print(T, ID);
                printf("-------------------------------\n");
            }
            else if (Order[0] == 'f')
            {
                int fromto = 0, Num = 0;
                printf("Please enter fromto.\nfromto=");
                scanf("%d", &fromto);
                printf("-------------------------------\n");
                int ID = Find(T.Root, fromto, Num);
                if (Num==0)
                    printf("Find Error.\n");
                else
                    printf("ToTal Num=%d.\n",Num);
                printf("-------------------------------\n");
            }
            else if (Order[0] == 'e')
            {
            }
            else if (Order[0] == 'b')
                break;
            else
            {
                printf("Order Error.\n");
                getchar();
            }
            getchar();
        }
        fclose(rp);
    }
    system("pause");
    return 0;
}