#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <ctime>
#include <cmath>
using namespace std;

//定义结构体square（方阵）
typedef struct square_matrix
{
    // 矩阵大小
    int n;
    // 矩阵元素
    // 行array[i]，单个元素array[i][j]
    int **array;
} mat;

//初始化矩阵
void init(mat &m)
{
    m.n = 0;
    m.array = NULL;
}
//生成初始随机矩阵
bool create(mat &m, int per)
{
    m.n = 4;
    //分配矩阵内存
    //m.array = (int **)malloc(sizeof(int *) * m.n);
    m.array = new int *[m.n];
    if (!m.array)
        return false;
    for (int i = 0; i < m.n; i++)
    {
        //m.array[i] = (int *)malloc(sizeof(int) * m.n);
        m.array[i] = new int[m.n];
        if (!m.array[i])
            return false;
    }
    srand((unsigned int)time(NULL));
    for (int i = 0; i < m.n; i++)
        for (int j = 0; j < m.n; j++)
            m.array[i][j] = pow(2, int(4 * rand() / RAND_MAX));
    return true;
}
//输出矩阵
void print(mat m)
{
    for (int i = 0; i < m.n; i++)
    {
        for (int j = 0; j < m.n; j++)
            cout << m.array[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}
//给定1区坐标后，确定2，3，4区坐标并旋转交换值
void spin(mat &m, int a, int b)
{
    int i[4] = {a - 1, m.n - b, m.n - a, b - 1};
    int j[4] = {b - 1, a - 1, m.n - b, m.n - a};
    int t = m.array[i[0]][j[0]];
    for (int k = 0; k < 3; k++)
        m.array[i[k]][j[k]] = m.array[i[k + 1]][j[k + 1]];
    m.array[i[3]][j[3]] = t;
}
//向右旋转矩阵90°
void rotate(mat &m)
{
    for (int i = 1; i <= m.n / 2; i++)
        for (int j = i; j <= m.n - i; j++)
            spin(m, i, j); //依次旋转1区中单个元素
}
//消融
void melt(mat &m)
{
    for (int j = 0; j < m.n; j++)
        for (int i = 0; i < m.n - 1; i++)
            if (!m.array[i][j])
            {
            }
    for (int j = 0; j < m.n; j++)
        for (int i = 0; i < m.n - 1; i++)
            if (m.array[i][j] == m.array[i + 1][j])
            {
                m.array[i + 1][j] += m.array[i][j];
                m.array[i][j] = 0;
            }
}

int main()
{
    int per = 0;
    void (*fun[2])(mat &) = {rotate, melt};
    mat m;
    init(m);
    cin >> per;
    if (!create(m, per))
    {
        cout << "***Create matrix failure***" << endl;
        return -1;
    }
    else
        cout << "***Create matrix successfully***" << endl;
    cout << "Initial matrix:" << endl;
    print(m);
    while (1)
    {
        int cmd = 0;
        //输入指令
        cout << "***Please enter the command***" << endl;
        cout << "0 for quit." << endl
             << "1 for rotate." << endl
             << "2 for melt." << endl;
        cin >> cmd;
        if (!cmd)
        {
            cout << "***Quit successfully***" << endl;
            break;
        }
        else
            fun[cmd - 1](m);
        cout << "Changed matrix:" << endl;
        print(m);
    }
    cout << "***End***";
    return 0;
}