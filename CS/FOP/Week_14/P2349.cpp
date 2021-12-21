#include <iostream>
#include <limits.h>
using namespace std;

struct state
{
    int sheep;
    int wolf;
};

struct stateList
{
    state *elem;
    int num;
};

stateList get_strategy(stateList &s, int m)
{
    s.num = 0;
    for (int sheep = 0; sheep <= m; sheep++)
        for (int wolf = 0; sheep + wolf <= m; wolf++)
            if (sheep + wolf != 0 && (sheep >= wolf || sheep == 0))
            {
                s.elem[s.num].sheep = sheep;
                s.elem[s.num].wolf = wolf;
                s.num++;
            }
    return s;
}

int n = 0, m = 0, minStep = INT_MAX;
stateList strategy;
stateList memo;

state next_state(state cur, state elem, int dir)
{
    state newState = {cur.sheep + dir * elem.sheep, cur.wolf + dir * elem.wolf};
    return newState;
}

bool equal(state s1, state s2)
{
    if (s1.sheep == s2.sheep && s1.wolf == s2.wolf)
        return true;
    return false;
}

bool valid(state cur, int step)
{
    if (cur.sheep > n || cur.wolf > n || cur.sheep < 0 || cur.wolf < 0)
        return false;
    if (!(cur.sheep == 0 || cur.sheep == n || cur.sheep == cur.wolf))
        return false;
    for (int i = step - 2; i >= 0; i -= 2)
        if (equal(cur, memo.elem[i]))
            return false;
    return true;
}

void get_step(state cur, int step)
{
    int dir = ((step % 2) ? 1 : -1);
    if (cur.sheep == 0 && cur.wolf == 0)
        if (step < minStep)
        {
            minStep = step;
            return;
        }
    for (int i = 0; i < strategy.num; i++)
    {
        state newState = next_state(cur, strategy.elem[i], dir);
        if (!valid(newState, step + 1))
            continue;
        memo.elem[step + 1].sheep = newState.sheep;
        memo.elem[step + 1].wolf = newState.wolf;
        get_step(newState, step + 1);
    }
}

int main()
{
    cin >> n >> m;
    strategy.elem = new state[100000];
    get_strategy(strategy, m);
    memo.elem = new state[100000];
    memo.num = 0;
    state begin = {n, n};
    memo.elem[0] = begin;
    get_step(begin, 0);
    cout << ((minStep == INT_MAX) ? -1 : minStep) << endl;
    return 0;
}