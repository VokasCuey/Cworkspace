#include <iostream>
#include <cstring>
using namespace std;

struct node
{
    char color[25];
    char shape[25];
    node *next;
};

node *head = NULL;
int num = 0;

void swap(node *p1, node *p2)
{
    if ((p1 == head || p2 == head) && (p1->next == p2 || p2->next == p1))
    {
        node *p = NULL, *q = NULL;
        if (p1 == head)
        {
            p = p1;
            q = p2;
        }
        else
        {
            p = p2;
            q = p1;
        }
        node *k = q->next;
        head = q;
        q->next = p;
        p->next = k;
    }
    else if (p1 == head || p2 == head)
    {
        if (p1 == head)
        {
            node *k1 = p1->next, *k2 = p2->next;
            node *q2 = head;
            while (1)
            {
                if (q2->next == p2)
                    break;
                else
                    q2 = q2->next;
            }
            q2->next = p1;
            p1->next = k2;
            p2->next = k1;
            head = p2;
        }
        else if (p2 == head)
        {
            node *k1 = p1->next, *k2 = p2->next;
            node *q1 = head;
            while (1)
            {
                if (q1->next == p1)
                    break;
                else
                    q1 = q1->next;
            }
            q1->next = p2;
            p2->next = k1;
            p1->next = k2;
            head = p1;
        }
    }
    else if (p1->next == p2 || p2->next == p1)
    {
        if (p1->next == p2)
        {
            node *q = head, *k = p2->next;
            while (q->next != p1)
                q = q->next;
            q->next = p2;
            p1->next = k;
            p2->next = p1;
        }
        else if (p2->next == p1)
        {
            node *q = head, *k = p1->next;
            while (q->next != p2)
                q = q->next;
            q->next = p1;
            p2->next = k;
            p1->next = p2;
        }
    }
    else
    {
        node *k1 = p1->next, *k2 = p2->next;
        node *q1 = head, *q2 = head;
        while (1)
        {
            if (q1->next == p1 && q2->next == p2)
                break;
            if (q1->next != p1)
                q1 = q1->next;
            if (q2->next != p2)
                q2 = q2->next;
        }
        q1->next = p2;
        p2->next = k1;
        q2->next = p1;
        p1->next = k2;
    }
}

void create(char c[], char s[])
{
    node *n = new node();
    memset(n->color, 0, sizeof(n->color));
    memset(n->shape, 0, sizeof(n->shape));
    n->next = NULL;
    strcpy(n->color, c);
    strcpy(n->shape, s);
    if (!head)
        head = n;
    else
    {
        node *p = head;
        for (int i = 1; i < num; i++)
            p = p->next;
        p->next = n;
    }
    num++;
}

int main()
{
    int n = 0;
    cin >> n;
    char cmd[25] = {0};
    for (int i = 1; i <= n; i++)
    {
        memset(cmd, 0, sizeof(cmd));
        cin >> cmd;
        if (!strcmp(cmd, "CREATE"))
        {
            char color[25] = {0}, shape[25] = {0};
            cin >> color >> shape;
            create(color, shape);
        }
        else if (!strcmp(cmd, "DUP"))
        {
            int m = 0;
            char color[25] = {0};
            cin >> m >> color;
            node *p = head;
            for (int i = 1; i < m; i++)
            {
                if (!p)
                    break;
                p = p->next;
            }
            create(color, p->shape);
        }
        else if (!strcmp(cmd, "CRASH"))
        {
            int m = 0;
            cin >> m;
            node *p = head;
            if (m == 1)
            {
                if (head)
                {
                    head = p->next;
                    delete[] p;
                }
            }
            else
            {
                for (int i = 1; i < m - 1; i++)
                    p = p->next;
                node *q = p->next;
                p->next = q->next;
                delete[] q;
            }
            num--;
        }
        else if (!strcmp(cmd, "ORDER"))
        {
            node *p = head;
            for (int i = 1; i < num; i++)
            {
                node *q = p->next;
                for (int j = i; j < num; j++)
                {
                    if (!strcmp(p->color, q->color))
                    {
                        for (int k = 0;; k++)
                        {
                            if (p->shape[k] < q->shape[k])
                                break;
                            if (p->shape[k] > q->shape[k])
                            {
                                swap(p, q);
                                node *tmp = p;
                                p = q;
                                q = tmp;
                                break;
                            }
                        }
                    }
                    else
                    {
                        for (int k = 0;; k++)
                        {
                            if (p->color[k] < q->color[k])
                                break;
                            if (p->color[k] > q->color[k])
                            {
                                swap(p, q);
                                node *tmp = p;
                                p = q;
                                q = tmp;
                                break;
                            }
                        }
                    }
                    q = q->next;
                }
                p = p->next;
            }
        }
    }
    node *p = head;
    while (p)
    {
        cout << p->color << ' ' << p->shape << endl;
        p = p->next;
    }
    return 0;
}