#include "Graph_define.h"
#define LH +1
#define EH 0
#define RH -1
#define Left 0
#define Right 1
#define None 0
#define MAX_SKIP_NUM 100
#define MAX_WORD_LENGTH 100
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
    GVex *Vex;
    GLink *Link;
} TNode;

typedef struct AVL_Tree
{
    TNode *Root;
} Tree;