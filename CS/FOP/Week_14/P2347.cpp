#include <iostream>
#include <limits.h>
using namespace std;

#define MAX(a, b) ((a > b) ? a : b)

int n = 0, cost[10] = {0}, minTime = INT_MAX, strategy[2][28] = {0}, sNum = 0;

struct state
{
    bool opp[10];
} memo[1000] = {0};

void get_strategy()
{
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++)
        {
            strategy[0][sNum] = i;
            strategy[1][sNum] = j;
            sNum++;
        }
}
bool done(state cur)
{
    for (int i = 1; i <= n; i++)
        if (!cur.opp[i])
            return false;
    return true;
}
state next_state(state cur, int k, int dir)
{
    state newState = cur;
    newState.opp[strategy[0][k]] = (dir ? true : false);
    newState.opp[strategy[1][k]] = (dir ? true : false);
    return newState;
}
bool equal(state s1, state s2)
{
    for (int i = 1; i <= n; i++)
        if (s1.opp[i] != s2.opp[i])
            return false;
    return true;
}
bool valid(state cur, int k, bool dir, int step)
{
    if (dir)
        if (cur.opp[strategy[0][k]] || cur.opp[strategy[1][k]])
            return false;
    if (!dir)
        if ((!cur.opp[strategy[0][k]]) || (!cur.opp[strategy[1][k]]))
            return false;
    for (int i = step - 2; i >= 0; i--)
        if (equal(next_state(cur, k, dir), memo[i]))
            return false;
    return true;
}
void login(state s, int step)
{
    for (int i = 1; i <= n; i++)
        memo[step].opp[i] = s.opp[i];
}
bool judge(state cur, int k, int dir)
{
    int num = 0;
    for (int i = 1; i <= n; i++)
        if (!cur.opp[i])
            num++;
    if (dir && num != 1)
        if (strategy[0][k] == strategy[1][k])
            return false;
    if (!dir)
        if (strategy[0][k] != strategy[1][k])
            return false;
    return true;
}
void get_step(state cur, int step, int curTime)
{
    bool dir = ((step % 2) ? false : true);
    if (done(cur))
    {
        if (curTime < minTime)
            minTime = curTime;
        return;
    }
    for (int i = 0; i < sNum; i++)
    {
        if (!valid(cur, i, dir, step + 1))
            continue;
        if (!judge(cur, i, dir))
            continue;
        state nextState = next_state(cur, i, dir);
        login(nextState, step + 1);
        get_step(nextState, step + 1, curTime + MAX(cost[strategy[0][i]], cost[strategy[1][i]]));
    }
}
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> cost[i];
    get_strategy();
    memo[0] = {0};
    state start = {0};
    get_step(start, 0, 0);
    cout << minTime << endl;
    return 0;
}