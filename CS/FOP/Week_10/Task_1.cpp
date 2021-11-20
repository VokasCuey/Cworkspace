#include <iostream>
using namespace std;

// 定义结构体链表节点
typedef struct LinkListNode
{
    // 序号
    int num;
    // 指向下一个节点的指针
    LinkListNode *next;
    // 指向上一个节点的指针
    LinkListNode *prev;
} Lnode;
// 定义结构体链表
typedef struct LinkList
{
    // 链表头
    Lnode *head;
    // 链表尾
    Lnode *tail;
    // 链表长度
    int len;
} Llist;

// 初始化链表
void init(Llist &L)
{
    L.head = NULL;
    L.tail = NULL;
    L.len = 0;
}
// 根据节点数创建新链表
void create(Llist &L, int n)
{
    L.len = n;
    L.head = new Lnode;
    // L.head = (Lnode *)malloc(sizeof(Lnode));
    // 创建链表头结点
    L.head->num = 1;
    L.head->next = NULL;
    L.head->prev = NULL;
    Lnode *p = L.head, *q = L.head;
    for (int i = 1; i < n; i++)
    {
        p->next = new Lnode;
        // p->next = (Lnode *)malloc(sizeof(Lnode));
        p->next->num = i + 1;
        p->next->next = NULL;
        // p跳转至下一个节点
        p = p->next;
        p->prev = q;
        q = p;
    }
    // 链表尾节点指向头结点
    p->next = L.head;
    L.tail = p;
    L.head->prev = L.tail;
}
// 根据已有链表和间隔数找到最后剩余的节点
void find(Llist &L, int m)
{
    // p指向当前节点，q指向p的上一个节点
    Lnode *p = L.head, *q = L.tail;
    // 防止出现野指针
    L.head = NULL, L.tail = NULL;
    int count = 1;
    // 只剩一个节点时跳出，否则继续删除节点
    while (L.len != 1)
    {
        // 数到第m个节点时删除该节点
        if (count == m)
        {
            cout << "Delete node " << p->num << endl;
            count = 1;
            // 将待删除节点的上一个节点与其下一个节点相连
            q->next = p->next;
            Lnode *r = p;
            p = p->next;
            // 删除当前节点
            delete r;
            L.len--;
        }
        // 未数到第m个节点时p，q继续往后跳转
        else
        {
            q = p;
            p = p->next;
            count++;
        }
    }
    // 链表头尾均指向最后一个剩余节点
    L.head = q;
    L.tail = q;
}

int main()
{
    int n = 0, m = 0;
    // 输入节点数和间隔
    cout << "Please enter the node num n." << endl;
    cin >> n;
    cout << "Please enter the gap m." << endl;
    cin >> m;
    // 新建空链表
    Llist L;
    // 初始化链表
    init(L);
    // 创建节点数为n的链表
    create(L, n);
    // 在间隔为m的条件下寻找最后一个剩余节点
    find(L, m);
    // 输出最后一个剩余节点
    cout << "The left node is " << L.head->num << endl;
    return 0;
}