#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Left 0
#define Right 1
#define OK 1
#define ERROR -1
#define None 0
#define MAX_SKIP_NUM 100
#define MAX_WORD_LENGTH 50

typedef struct Elem
{
    int ID;
    char *Name;
    int Tag;
    int Loc;
    int Loc1;
    char *Status;
} ElemType;

typedef struct Tree_Node
{
    ElemType Data;
    Tree_Node *Child[2];
} TNode;

typedef struct Tree
{
    TNode *Root;
} Tree;

int Init_Tree(Tree &T)
{
    T.Root = NULL;
    return OK;
}

int Insert_Tree(Tree &T, int ID, char *Name, int Tag, int Loc, int Loc1, char *Status)
{
    if (!T.Root)
    {
        T.Root = (TNode *)malloc(sizeof(TNode));
        if (!T.Root)
            return ERROR;
        T.Root->Child[Left] = NULL;
        T.Root->Child[Right] = NULL;
        T.Root->Data.ID = ID;
        T.Root->Data.Loc = Loc;
        T.Root->Data.Loc1 = Loc1;
        T.Root->Data.Tag = Tag;
        T.Root->Data.Name = (char *)malloc(sizeof(char *) * (strlen(Name) + 1));
        if (!T.Root->Data.Name)
            return ERROR;
        strcpy(T.Root->Data.Name, Name);
        T.Root->Data.Status = (char *)malloc(sizeof(char) * (strlen(Status) + 1));
        if (!T.Root->Data.Status)
            return ERROR;
        strcpy(T.Root->Data.Status, Status);
    }
    else
    {
        TNode *p = T.Root, *pp = NULL;
        int Tag = -1;
        while (p)
        {
            pp = p;
            ID <= p->Data.ID ? p = p->Child[Left] : p = p->Child[Right];
        }
        ID <= pp->Data.ID ? Tag = Left : Tag = Right;
        pp->Child[Tag] = (TNode *)malloc(sizeof(TNode));
        p = pp->Child[Tag];
        if (!p)
            return ERROR;
        p->Child[Left] = NULL;
        p->Child[Right] = NULL;
        p->Data.ID = ID;
        p->Data.Name = (char *)malloc(sizeof(char) * (strlen(Name) + 1));
        if (!p->Data.Name)
            return ERROR;
        strcpy(p->Data.Name, Name);
        p->Data.Tag = Tag;
        p->Data.Loc = Loc;
        p->Data.Loc1 = Loc1;
        p->Data.Status = ((char *)malloc(sizeof(char) * (strlen(Status) + 1)));
        if (!p->Data.Status)
            return ERROR;
        strcpy(p->Data.Status, Status);
    }
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
        if (fscanf(rp, "%d %s", &ID, Name)==EOF)
            break;
        char c='\0';
        while(!((c=='F')||(c=='A')))
            c=fgetc(rp);
        if (c == 'F')
        {
            Tag=1;
            fscanf(rp,"%s %d %s %d",Skip,&Loc,Skip,&Loc1);
        }
        else
        {
            Tag=0;
            fscanf(rp,"%s %d",Skip,&Loc);
            Loc1=None;
        }
        while(c!='S')
            c=fgetc(rp);
            fscanf(rp,"%s",Skip);
        fgets(Status,MAX_WORD_LENGTH,rp);
        Insert_Tree(T,ID,Name,Tag,Loc,Loc1,Status);
    }
    return OK;
}

int main()
{
    Tree T;
    Init_Tree(T);
    FILE *rp = fopen("电气设备表.txt", "r");
    FILE *op = fopen("op.txt", "r");
    if (!(rp && op))
    {
        printf("The file could not be opened.\n");
        return ERROR;
    }
    else
    {
        In_Tree(rp, T);
        fclose(rp);
        fclose(op);
    }
    system("pause");
    return OK;
}