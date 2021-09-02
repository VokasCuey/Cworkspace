#include <stdio.h>
#include <stdlib.h>
typedef enum
{
    OK,
    ERROR
} Status;

typedef int T_ElemType;

typedef struct Binary_Tree_Node
{
    T_ElemType Data;
    int ID;
    Binary_Tree_Node *LChild, *RChild;
} BTNode;
const BTNode BTEmpty = {0, 0, NULL, NULL};

typedef struct Tree
{
    BTNode *Root;
    int Depth;
} Tree;

typedef BTNode Q_ElemType;

typedef struct Queue_Node
{
    Q_ElemType Data;
    Queue_Node *Next;
} Q_Node;

typedef struct Queue
{
    int Length;
    Q_Node *Front;
    Q_Node *Rear;
} Queue;

Status Init_Tree(Tree &T)
{
    T.Root = NULL;
    T.Depth = 1;
}

Status Init_Queue(Queue &Q)
{
    Q_Node *p = (Q_Node *)malloc(sizeof(Q_Node));
    p->Next = NULL;
    p->Data = BTEmpty;
    Q.Front = p;
    Q.Rear = p;
    Q.Length = 0;
}

Status Insert_Queue(Queue &Q, Q_ElemType e)
{
    Q_Node *p = (Q_Node *)malloc(sizeof(Q_Node));
    if (!p)
        return ERROR;
    p->Data = e;
    p->Next = NULL;
    Q.Rear->Next = p;
    Q.Rear = p;
    return OK;
}

Status Delete_Queue(Queue &Q)
{
    Q_Node *p = Q.Front->Next;
    Q.Front->Next = p->Next;
    if (p == Q.Rear)
        Q.Rear = Q.Front;
    free(p);
    return OK;
}

Status BFS(Tree T)
{
    Queue Q;
    Init_Queue(Q);
}

int main()
{
    Tree T;
    Init_Tree(T);
    system("pause");
    return 0;
}