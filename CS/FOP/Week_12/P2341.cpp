#include <iostream>
using namespace std;

void step(int cur, int h, bool *unWalk, int &total)
{
    if (cur == h)
    {
        total++;
        return;
    }
    for (int i = 0; i < 3; i++)
    {
        if (unWalk[cur + i] || cur + i + 1 > h)
            continue;
        cur += i + 1;
        step(cur, h, unWalk, total);
        cur -= i + 1;
    }
}

int main()
{
    int h = 0, n = 0;
    cin >> h >> n;
    bool *unWalk = new bool[h]();
    for (int i = 0; i < n; i++)
    {
        int tmp = 0;
        cin >> tmp;
        unWalk[tmp - 1] = true;
    }
    int total = 0;
    step(0, h, unWalk, total);
    cout << total << endl;
    return 0;
}