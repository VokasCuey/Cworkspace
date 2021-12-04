#include <iostream>
using namespace std;

// 定义结构体链表节点
typedef struct LinkListNode
{
    // 序号
    int num;
    // 指向后一个节点的指针
    LinkListNode *next;
    // 指向前一个节点的指针
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
    // 创建链表头结点
    L.head->num = 1;
    L.head->next = NULL;
    L.head->prev = NULL;
    Lnode *p = L.head;
    for (int i = 1; i < n; i++)
    {
        // 对p的下一个节点进行内存分配、初始化和赋值
        p->next = new Lnode;
        p->next->num = i + 1;
        p->next->next = NULL;
        // p的下一个节点的prev指向p
        p->next->prev = p;
        // p跳转至下一个节点
        p = p->next;
    }
    // 链表尾节点的next指向头结点
    p->next = L.head;
    L.tail = p;
    L.head->prev = L.tail;
}
// 根据已有链表和间隔数找到最后剩余的节点
void find(Llist &L, int m, int k)
{
    bool clockwise = true;
    // p指向当前节点
    Lnode *p = L.head;
    // 防止出现野指针
    L.head = NULL, L.tail = NULL;
    // 计数变量
    int count = 1;
    // 只剩一个节点时跳出，否则继续删除节点
    while (L.len != 1)
    {
        // 数到第m个节点时删除该节点
        if (count == m)
        {
            cout << "Delete node " << p->num << endl;
            count = 1;
            // 判断是否改变方向
            if (p->num < k)
            {
                clockwise = !clockwise;
                cout << "Change dir to " << ((clockwise) ? "" : "anti") << "clockwise dir" << endl;
            }
            // 令r指向待删除节点
            Lnode *r = p;
            // 分别在两种方向的情况下将待删除节点的前后两个节点相连，且让p跳转至当前方向下的下一个节点
            if (clockwise)
            {
                p->prev->next = p->next;
                p->next->prev = p->prev;
                // p跳转至顺时针方向下的下一个节点
                p = p->next;
            }
            else
            {
                p->next->prev = p->prev;
                p->prev->next = p->next;
                // p跳转至逆时针方向下的下一个节点
                p = p->prev;
            }
            // 删除待删除节点
            delete r;
            // 链表长度减小
            L.len--;
        }
        // 未数到第m个节点时p继续往当前方向的下一个节点跳转
        else
        {
            if (clockwise)
                p = p->next;
            else
                p = p->prev;
            // 计数增加
            count++;
        }
    }
    // 链表头尾均指向最后一个剩余节点
    L.head = p;
    L.tail = p;
}

int main()
{
    int n = 0, m = 0, k = 0;
    // 输入参数
    cout << "Please enter the node num n." << endl;
    cin >> n;
    cout << "Please enter the gap m." << endl;
    cin >> m;
    cout << "Please enter the num k(1<k<" << m << ')' << endl;
    cin >> k;
    // 新建空链表
    Llist L;
    // 初始化链表
    init(L);
    // 创建节点数为n的链表
    create(L, n);
    // 在间隔为m的条件下寻找最后一个剩余节点
    find(L, m, k);
    // 输出最后一个剩余节点
    cout << "The left node is " << L.head->num << endl;
    return 0;
}