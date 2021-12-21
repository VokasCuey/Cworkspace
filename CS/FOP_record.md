### record

---

#### Week_11

---

#### Week_12

---

##### P1687.n皇后问题——有坑版

---

###### ***Description:***

Description:

>   给定一个n*n的棋盘，棋盘中有一些位置有坑，不能放皇后。现在要向棋盘中放入皇后，使得任意两个皇后都不在同一行、同一列或同一条对角线上。问最多能放多少个皇后？

Input:

>   输入的第一行为一个整数n，表示棋盘的大小。
>   接下来n行，每行n个0或1的整数，如果一个整数为1，表示对应的位置可以放皇后，如果一个整数为0，表示对应的位置不可以放皇后。

Output:

>   输出一个整数，表示最多能放多少个皇后。

Input example:

```
4
1 0 0 0
0 1 0 0
0 0 0 1
1 0 0 1
```

Output example:

```
3
```

Note:

>   ***data size:***
>
>   对于20%数据，n=4；
>
>   对于90%数据，n<=8；
>   对于100%数据，n<=13。
>
>   本题时间限制1s，内存限制256MB。

---

###### ***src:***

```C++
#include <iostream>
using namespace std;

int maxPlace = 0;
bool _try(int col, int n, int num, bool **place, bool *rowUnsafe, bool *LUnsafe, bool *RUnsafe)
{
    if (col == n)
    {
        num > maxPlace ? maxPlace = num : maxPlace = maxPlace;
        return true;
    }
    for (int row = 0; row < n + 1; row++)
    {
        if (row < n)
        {
            if (!place[row][col] || rowUnsafe[row] || LUnsafe[row + col] || RUnsafe[row - col + n - 1])
                continue;
            num++;
            rowUnsafe[row] = true;
            LUnsafe[row + col] = true;
            RUnsafe[row - col + n - 1] = true;
            _try(col + 1, n, num, place, rowUnsafe, LUnsafe, RUnsafe);
            num--;
            rowUnsafe[row] = false;
            LUnsafe[row + col] = false;
            RUnsafe[row - col + n - 1] = false;
        }
        else
            _try(col + 1, n, num, place, rowUnsafe, LUnsafe, RUnsafe);
    }
    return true;
}

int main()
{
    int n = 0;
    cin >> n;
    bool **place = new bool *[n]();
    for (int i = 0; i < n; i++)
        place[i] = new bool[n]();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            int tmp = 0;
            cin >> tmp;
            if (tmp)
                place[i][j] = true;
        }
    bool *rowUnsafe = new bool[n]();
    bool *LUnsafe = new bool[2 * n - 1]();
    bool *RUnsafe = new bool[2 * n - 1]();
    _try(0, n, 0, place, rowUnsafe, LUnsafe, RUnsafe);
    cout << maxPlace << endl;
    return 0;
}
```

---

##### P2341.下楼问题

---

###### ***Description:***

Description:

>   从楼上走到楼下共有h个台阶，每一步有3种走法：走一个台阶；走两个台阶；走三个台阶。规定只能往下走，不能往上走。
>
>   调皮的小明在n个台阶上撒了水，为了防止滑倒，不能踏上这n个台阶，问从楼上到楼下可走出多少种方案？

Input:

>   第一行两个数字h, n，分别表示总台阶数和不能走的台阶数  (1 <= n < h <= 15)
>
>   接下来n行，每行一个整数a_i，表示第a_i级台阶被撒了水不能走

Output:

>   一个整数，表示从楼上到楼下的方案数。

Input example:

```
5 1
3
```

Output example:

```
5
```

Note:

>   第0级和第h级台阶保证不会有水

---

###### ***src:***

```C++
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
```

---

##### P2344.跳马问题1

---

###### ***Description:***

Description:

>   马按中国象棋的规则走，中国象棋半张棋盘如图1所示，棋盘大小为n*m。马自左下角 (0, 0) 向右上角 (n, m) 跳。规定只能往右跳，不准往左跳，不能跳出棋盘，即x坐标只能增大。比如下图所示为一种跳行路线。
>
>   ![1543216994851015532](D:\University\课程\大二上\程序设计基础\1543216994851015532.png)
>
>   小明觉得这道题太简单，所以在棋盘上放了K个己方棋子，马不能跳到己方棋子上，**己方棋子不会绊马脚**，保证起点和终点上没有棋子，问此时跳马的路径总数。

Input:

>   第一个三个整数n, m, K  (1< n, m<=15, 0<=K<n*m)
>
>   接下来K行每行两个整数，分别表示第k个己方棋子的横坐标和纵坐标

Output:

>   只有一个数：总方案数total。

Input example:

```
样例1:
8 4 0

样例2:
4 4 1
2 0
```

Output example:

```
样例1:
37

样例2:
1
```

Note:

>   对于4*4的棋盘原本有两条路线:
>
>   (0,0)->(1,2)->(2,0)->(3,2)->(4,4)
>
>   (0,0)->(1,2)->(2,4)->(3,2)->(4,4)
>
>   
>
>   第一条线路经过(2, 0)，而此位置已经有棋子，所以不能走

---

###### ***src:***

```C++
#include <iostream>
using namespace std;

void step(int n, int m, int curX, int curY, int &total, bool **unStep)
{
    if (curX == n && curY == m)
    {
        total++;
        return;
    }
    int dir[4][2] = {{1, 2}, {2, 1}, {2, -1}, {1, -2}};
    for (int i = 0; i < 4; i++)
    {
        if (curX + dir[i][0] > n || curY + dir[i][1] > m || curY + dir[i][1] < 0)
            continue;
        if (unStep[curX + dir[i][0]][curY + dir[i][1]])
            continue;
        curX += dir[i][0];
        curY += dir[i][1];
        step(n, m, curX, curY, total, unStep);
        curX -= dir[i][0];
        curY -= dir[i][1];
    }
}

int main()
{
    int n = 0, m = 0, k = 0;
    cin >> n >> m >> k;
    bool **unStep = new bool *[n + 1]();
    for (int i = 0; i < n + 1; i++)
        unStep[i] = new bool[m + 1]();
    for (int i = 0; i < k; i++)
    {
        int tmp1 = 0, tmp2 = 0;
        cin >> tmp1 >> tmp2;
        unStep[tmp1][tmp2] = true;
    }
    int total = 0;
    step(n, m, 0, 0, total, unStep);
    cout << total << endl;
    return 0;
}
```

---

---

#### Week_13

---

##### P2030.数字金字塔

---

###### ***Description:***

Description:

>   观察下面的数字金字塔。
>
>   写一个程序来查找从最高点到底部任意处结束的路径，使路径经过数字的和最大。每一步可以走到左下方的点也可以到达右下方的点。
>
>   ```
>           7 
>         3   8 
>       8   1   0    
>     2   7   4   4 
>   4   5   2   6   5 
>   ```
>
>   在上面的样例中,从7 到 3 到 8 到 7 到 5 的路径产生了最大的和。

Input:

>   输入有多行。
>
>   第一个行包含 R(1<= R<=1000) ,表示行的数目。
>
>   后面每行为这个数字金字塔特定行包含的整数。
>
>   所有的被供应的整数是非负的且不大于100。

Output:

>   输出仅有一行,包含那个可能得到的最大的和。

Input example:

```
5
7
3 8
8 1 0
2 7 4 4
4 5 2 6 5
```

Output example:

```
30
```

---

###### ***src:***

```c++
#include <iostream>
using namespace std;

#define MAX(a, b) ((a > b) ? a : b)
#define SIZE 1000

int pyramid[SIZE][SIZE] = {0}, maxVal[SIZE][SIZE] = {0};

void way(int n, int x, int y, int pyramid[SIZE][SIZE], int maxVal[SIZE][SIZE])
{
    if (x > n)
        return;
    if (x == 1)
        maxVal[0][0] = pyramid[0][0];
    else if (y == 1)
        maxVal[x - 1][y - 1] = maxVal[x - 2][y - 1] + pyramid[x - 1][y - 1];
    else if (y == n)
        maxVal[x - 1][y - 1] = maxVal[x - 2][y - 2] + pyramid[x - 1][y - 1];
    else
        maxVal[x - 1][y - 1] = MAX(maxVal[x - 2][y - 1], maxVal[x - 2][y - 2]) + pyramid[x - 1][y - 1];
}

int main()
{
    int n = 0;
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= i; j++)
            cin >> pyramid[i][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= i; j++)
            way(n, i + 1, j + 1, pyramid, maxVal);
    int max = 0;
    for (int i = 0; i < n; i++)
        if (maxVal[n - 1][i] > max)
            max = maxVal[n - 1][i];
    cout << max << endl;
    return 0;
}
```

---

##### P2250.哼哼哈兮

###### ***Description:***

Description:

>   有N种类型的短棒，第i种短棒长度为a_i，武力值为b_i，数量无限。这些短棒可以多个粘到一起成为长一些的棒。普通情况下，长度为A的棒和长度为B的棒组成一个长度为A+B的棒，此时
>
>   *   长度为A+B的棒的武力值 = 长度为A的棒的武力值 + 长度为B的棒的武力值
>
>   但是，如果A与B的长度相等，则其武力值还要再增加233（因为这样它比较像双节棍，然后忍不住哼哼哈兮，引得大家233）。也就是说，若用两个长度为K的棒，组成一个长度为2K的棒，此时，
>
>   *   长度为2K的棒的武力值 = 长度为K的棒的武力值*2 + 233。
>
>   现在，已知需要一根长M的棒，且要求武力值最大化。那么请问这根棒最大的武力值是多少？

Input:

>   第一行输入两个数N，M。 
>   第二行为N个整数a_i，表示每种短棒的长度。 
>   第三行为N个整数b_i，表示每种短棒的武力值。
>   输入数据保证有解。
>   (0 < N, M, a_i ≤ 1000)
>   (a_i ≤ M) 
>   (0 < b_i ≤ 10000)

Output:

>   输出一个整数，表示长M的棒的最大武力值。

Input example:

```
3 10
1 2 3
1000 3000 6000
```

Output example:

```
19233
```

Note

>   以下为几种可能的组成方案: 
>
>   ((2 2) (2 2)) (2) = ((30002+233)2+233) + 3000 = 15699 
>   ((2 2) (2)) (2 2) = ((30002+233) + 3000) + (30002+233) = 15466 
>   ((2 2) 1) (1 (2 2)) = ((30002+233)+1000)2+233 = 14699 
>   (2 3) (2 3) = (3000+6000)2+233 = 18233 
>   (1 3) (3 3) = (1000+6000)+(60002+233) = 19233
>
>   容易发现，拼接的顺序，对于最后的武力值也有影响。

---

###### ***src:***

```C++
#include <iostream>
using namespace std;

#define OFFSET 233

int a[1000] = {0}, b[1000] = {0}, val[1000] = {0};

void sort(int n)
{
    for (int i = 0; i < n; i++)
        if (b[i] > val[a[i]])
            val[a[i]] = b[i];
}
int link(int len1, int len2, int val1, int val2)
{
    if (len1 == len2)
        return val1 + val2 + OFFSET;
    else
        return val1 + val2;
}
int cut(int m)
{
    for (int i = 1; i <= m; i++)
    {
        int max = 0, tmp = 0;
        for (int j = 1; j <= i; j++)
        {
            tmp = link(i - j, j, val[i - j], val[j]);
            if (tmp > max)
                max = tmp;
        }
        val[i] = max;
    }
    return val[m];
}

int main()
{
    int n = 0, m = 0;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n; i++)
        cin >> b[i];
    sort(n);
    cout << cut(m) << endl;
    return 0;
}
```

---

##### P1284.最小差方和

###### ***Description:***

Description:

>   给定n和L，以及n个整数a[i]。
>
>   要求把a[i]分成连续的若干段。对于每一段，假设其和为S，则其代价为(S-L)^2。
>
>   整个划分方案的代价定义为每一段代价之和。
>
>   求所有划分方案中的最小代价。

Input:

>   第一行两个正整数n和L。
>
>   第二行n个整数a[i]。

Output:

>   一行一个非负整数表示最小代价。

Input example:

Output example:

Note:

>   ***data size:***
>
>   60%的数据，n<=100，L<=1000;
>
>   100%的数据，n<=3000，L<=2^20-1，|a[i]|<=100000。

---

###### ***src:***

```C++
//时间复杂度有待改善
#include <iostream>
using namespace std;

#define SIZE 4000
int n = 0, l = 0;
long long a[SIZE] = {0}, cost[SIZE] = {0};

long long _cost(int i, int j)
{
    long long sum = 0;
    for (int k = i; k <= j; k++)
        sum += a[k];
    return (sum - l) * (sum - l);
}
long long min_cost()
{
    for (int i = 1; i <= n; i++)
    {
        long long min = _cost(1, i);
        for (int j = 1; j <= i; j++)
        {
            long long tmp = cost[i - j] + _cost(i - j + 1, i);
            if (tmp < min)
                min = tmp;
        }
        cost[i] = min;
    }
    return cost[n];
}
int main()
{
    cin >> n >> l;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    cout << min_cost() << endl;
    return 0;
}
```

---

##### P1525.飞弹拦截

###### ***Description:***

Description:

>   强大的kAc建立了强大的帝国，但人民深受其学霸及23文化的压迫，于是勇敢的高达决心反抗。
>
>   高达能远程发飞弹打击，他先后对着城市开了n发，第i个飞弹高度为hi。然而kAc帝国也有一门炮可以拦截高达发射的飞弹，虽然拦截成功率为100%，但由于技术问题，这门炮每次只能拦截比上一次高度相同或更高的飞弹（第一次可以拦截任意飞弹）。玛德go负责此次拦截，他刚算好拦截方案又接到了上级的任务：一些给定的飞弹由于杀伤力大必须拦截。玛德go显然已经不屑于解决这种问题了，他显然要做一些更有意义的事情。于是这问题就交给了你，在打掉指定飞弹的前提下打掉最多飞弹。

Input:

>   第一行一个数n，第二行n个数，依次表示飞来的飞弹高度。
>
>   第三行一个数m，表示必须拦截的飞弹个数，第四行m个数表示这些飞弹的编号（0到n-1），并且保证单调递增，保证存在至少一种打击方案。

Output:

>   一个数表示最多打掉的飞弹。

Input example:

```
5
2 4 3 4 5
2
1 3
```

Output example:

```
4
```

Note:

>   ***data size:***
>
>   30%的数据n<=10
>
>   70%的数据n<=100
>
>   100%的数据n<=1000，m<=100
>
>   飞弹的高度在int表示范围内

---

###### ***src:***

```C++
#include <iostream>
using namespace std;

int n = 0, m = 0;
int height[1005] = {0}, maxDes[1005] = {0}, must[105] = {0};
bool getMax[1005] = {0};

int max_destroy(int left, int right, int cur)
{
    if (left == right)
        return 0;
    if (!getMax[left])
    {
        int max = 0;
        for (int i = left + 1; i <= right; i++)
        {
            int num = 0;
            bool skip = false;
            for (int j = 0; j < m; j++)
                if ((must[j] > left && must[j] < i) || (must[j] > i && height[i] > height[must[j]]))
                {
                    skip = true;
                    break;
                }
            if (skip || height[i] < cur)
                continue;
            num = max_destroy(i, right, height[i]) + 1;
            if (num > max)
                max = num;
        }
        maxDes[left] = max;
        getMax[left] = true;
    }
    return maxDes[left];
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> height[i];
    cin >> m;
    for (int i = 0; i < m; i++)
        cin >> must[i];
    cout << max_destroy(-1, n - 1, 0) << endl;
    return 0;
}
```

---

---

#### Week_14

---

##### P1316.最长公共子序列

---

###### ***Description:***

Description:

> 给定两个字符串，寻找这两个字串之间的最长公共子序列。

Input:

> 输入两行，分别包含一个字符串，仅含有小写字母。

Output:

> 最长公共子序列的长度。

Input example:

```C++
abcdgh

aedfhb
```

Output example:

```C++
3
```

note:

> ***data size：***
> 字串长度1~1000。

---

###### ***src:***

```c++
#include <iostream>
#include <cstring>
using namespace std;

#define MAX(a, b) ((a > b) ? a : b)
#define MAXLEN 1005

char str1[MAXLEN] = {0}, str2[MAXLEN] = {0};
int subLen[MAXLEN][MAXLEN] = {0};

int main()
{
    cin >> str1 >> str2;
    for (int i = 1; i <= strlen(str1); i++)
        for (int j = 1; j <= strlen(str2); j++)
        {
            if (str1[i - 1] == str2[j - 1])
                subLen[i][j] = subLen[i - 1][j - 1] + 1;
            else
            	subLen[i][j] = MAX(subLen[i - 1][j], subLen[i][j - 1]);
        }
    cout << subLen[strlen(str1)][strlen(str2)] << endl;
    return 0;
}
```

---

##### P1622.采药

---

###### ***Description:***

Description:

> 辰辰是个天资聪颖的孩子，他的梦想是成为世界上最伟大的医师。为此，他想拜附近最有威望的医师为师。医师为了判断他的资质，给他出了一个难题。医师把他带到一个到处都是草药的山洞里对他说：“孩子，这个山洞里有一些不同的草药，采每一株都需要一些时间，每一株也有它自身的价值。我会给你一段时间，在这段时间里，你可以采到一些草药。如果你是一个聪明的孩子，你应该可以让采到的草药的总价值最大。”

Input:

>   第一行有两个整数T（1 <= T <= 1000）和M（1 <= M <= 100），用一个空格隔开，T代表总共能够用来采药的时间，M代表山洞里的草药的数目。接下来的M行每行包括两个在1到100之间（包括1和100）的整数，分别表示采摘某株草药的时间和这株草药的价值。

Output:

>   包括一行，这一行只包含一个整数，表示在规定的时间内，可以采到的草药的最大总价值。

Input example:

```
70 3

71 100

69 1

1 2
```

Output example:

```
3
```

Note:

>   ***data size：***
>
>   10；
>
>   对于全部的数据，M <= 100。
>
>   

---

###### ***src:***

```c++
#include <iostream>
using namespace std;

#define MAX(a, b) ((a > b) ? a : b)

int T = 0, M = 0;
int cost[105] = {0}, val[105] = {0};
int maxVal[105][1005] = {0};

int main()
{
    cin >> T >> M;
    for (int i = 1; i <= M; i++)
        cin >> cost[i] >> val[i];
    for (int i = 1; i <= M; i++)
        for (int j = 1; j <= T; j++)
        {
            if (cost[i] <= j)
                maxVal[i][j] = MAX(maxVal[i - 1][j], maxVal[i - 1][j - cost[i]] + val[i]);
            else
                maxVal[i][j] = maxVal[i - 1][j];
        }
    cout << maxVal[M][T];
    return 0;
}
```

---

##### P2349.小羊与小狼

---

###### ***Description:***

Description:

>   有n只羊与n只狼，牧羊人须要把他们摆渡到河对岸。船上最多可以容纳m只动物，任何时刻，任何地点（两岸或者船上）只要羊的数目小于狼的数目，狼就会把羊吃掉。由于牧羊人害怕寂寞，在摆渡时船上必须至少有一只动物。在船行驶到对岸之后，先所有动物瞬时下船，接着下一波动物瞬时上船。问最少摆渡次数。

Input:

>   有n只羊与n只狼，牧羊人须要把他们摆渡到河对岸。船上最多可以容纳m只动物，任何时刻，任何地点（两岸或者船上）只要羊的数目小于狼的数目，狼就会把羊吃掉。由于牧羊人害怕寂寞，在摆渡时船上必须至少有一只动物。在船行驶到对岸之后，先所有动物瞬时下船，接着下一波动物瞬时上船。问最少摆渡次数。

Output:

>   一个整数，表示答案。若无法完成，则输出-1。

Input example:

```
3 2
```

Output example:

```
11
```

---

###### ***src:***

```C++
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
```

---

##### P2347.过桥问题【多步决策、穷举】

---

###### ***Description:***

Description:

>   在漆黑的夜里，n位旅行者来到了一座狭窄而且没有护栏的桥边。如果不借助手电筒的话，大家是无论如何也不敢过桥去的。不幸的是，n个人一共只带了一只手电筒，而桥窄得只够让两个人同时通过。如果各自单独过桥的话，第i个人所需要的时间是time[i]；而如果两人同时过桥，所需要的时间就是走得比较慢的那个人单独行动时所需的时间。 此时，请问让所有人都过桥，最少需要多长时间？

Input:

>   第一行包含一个整数，代表n。(n <= 6)
>
>   之后有n行，每行包含一个整数， 代表time[i]。 (time[i] <= 10000)

Output:

>   一个整数，表示最少的花费时间。

Input example:

```
5
1
3
6
8
12
```

Output example:

```
29
```

Note:

>   请使用课上讲解的【多步决策】方法解决。

---

###### ***src:***

```C++
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
```

---

