#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    OK,
    ERROR,
    OVERFLOW
} Status;

typedef int ElemType;
const ElemType Empty = 0;

typedef struct QNode
{
    ElemType Data;
    QNode *Next;
} Node;

typedef struct Linked_Queue
{
    int Length;
    Node *Front;
    Node *Rear;
} LinkQueue;

Status Init_LinkQueue(LinkQueue &Q)
{
    Q.Length = 0;
    Node *p = (Node *)malloc(sizeof(Node));
    p->Data = Empty;
    p->Next = NULL;
    Q.Front = NULL;
    Q.Rear = NULL;
    return OK;
}

Status Insert_LinkQueue(LinkQueue &Q, ElemType e)
{
    Node *p;
    p = (Node *)malloc(sizeof(Node));
    if (!p)
        return OVERFLOW;
    p->Data = NULL;
    p->Data = e;
    Q.Rear->Next = p;
    Q.Rear = p;
    return OK;
}

Status Delete_LinkQueue(LinkQueue &Q)
{
    if (Q.Front == Q.Rear)
        return ERROR;
    Node *p=Q.Front->Next;
    Q.Front->Next=p->Next;
    if (p==Q.Rear)
    Q.Rear=Q.Front;
    free(p);
    return OK;
}

Status Destroy_LinkQueue(LinkQueue &Q)
{
    while (!Q.Front)
    {
        Q.Rear=Q.Front->Next;
        free(Q.Front);
        Q.Front=Q.Rear;
    }
}

int main()
{
    LinkQueue Q;
    Init_LinkQueue(Q);
    system("pause");
    return 0;
}