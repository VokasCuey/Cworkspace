#include <iostream>
using namespace std;

typedef struct LinkListNode
{
    int num;
    LinkListNode *next;
} Lnode;
typedef struct LinkList
{
    Lnode *head;
    Lnode *tail;
    int len;
} Llist;

void init(Llist &L)
{
    L.head = NULL;
    L.tail = NULL;
    L.len = 0;
}
void create(Llist &L, int n)
{
    L.len = n;
    L.head = new Lnode;
    // L.head = (Lnode *)malloc(sizeof(Lnode));
    L.head->num = 1;
    L.head->next = NULL;
    Lnode *p = L.head;
    for (int i = 1; i < n; i++)
    {
        p->next = new Lnode;
        // p->next = (Lnode *)malloc(sizeof(Lnode));
        p->next->num = i + 1;
        p->next->next = NULL;
        p = p->next;
    }
    p->next = L.head;
    L.tail = p;
}
void find(Llist &L, int m)
{
    Lnode *p = L.head, *q = L.tail;
    int count = 1;
    while (L.len != 1)
    {
        if (count == m)
        {
            cout << "Delete node " << p->num << endl;
            count = 1;
            q->next = p->next;
            Lnode *r = p;
            p = p->next;
            delete r;
            L.len--;
        }
        else
        {
            q = p;
            p = p->next;
            count++;
        }
    }
    L.head = q;
}

int main()
{
    int n = 0, m = 0;
    cin >> n >> m;
    Llist L;
    init(L);
    create(L, n);
    find(L, m);
    cout << "The left node is " << L.head->num << endl;
    return 0;
}