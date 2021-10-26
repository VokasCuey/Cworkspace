#include <iostream>
using namespace std;

struct Node
{
    int x, y;
} a, b;

Node mean(Node a, Node b)
{
    Node c={0,0};
    c.x=0.5*(a.x+b.x);
    c.y=0.5*(a.y+b.y);
    return c;
}

int main()
{

    cin >> a.x >> a.y;
    cin >> b.x >> b.y;

    Node c = mean(a, b);
    cout << c.x << " " << c.y << endl;
    return 0;
}