#include <stdio.h>
#include <stdlib.h>

typedef enum {OK,ERROR,OVERFLOW} Status;

typedef int ElemType;
const ElemType Empty =0;

typedef struct QNode
{
    ElemType Data;
    QNode *Next;
}Node;

typedef struct Linked_Queue
{
    int Length;
    Node *Front;
    Node *Rear;
}LinkQueue;

Status Init_LinkQueue(LinkQueue &Q)
{
    Q.Length=0;
    Node *p=(Node*)malloc(sizeof(Node));
    p->Data=Empty;p->Next=NULL;
    Q.Front=NULL;Q.Rear=NULL;
    return OK;
}

Status Insert_LinkQueue(LinkQueue &Q, ElemType e)
{}

int main()
{
    LinkQueue Q;
    Init_LinkQueue(Q);
    system("pause");
    return 0;
}