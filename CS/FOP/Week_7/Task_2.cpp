#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

//定义结构体matrix（方阵）
typedef struct matrix
{
    // 矩阵大小
    int n;
    // 矩阵元素
    // 行array[i]，单个元素array[i][j]
    int **array;
} mat;

//初始化矩阵
void init_mat(mat m)
{
    m.n = 0;
    m.array = NULL;
}
//输出矩阵
void output(mat m)
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
bool spin(mat m, int a, int b)
{
    int i[4] = {a - 1, m.n - b, m.n - a, b - 1};
    int j[4] = {b - 1, a - 1, m.n - b, m.n - a};
    int t = m.array[i[0]][j[0]];
    for (int k = 0; k < 3; k++)
        m.array[i[k]][j[k]] = m.array[i[k + 1]][j[k + 1]];
    m.array[i[3]][j[3]] = t;
    return true;
}
//向右旋转矩阵90°
bool rotate(mat m)
{
    for (int i = 1; i <= m.n / 2; i++)
        for (int j = i; j <= m.n - i; j++)
            if (!spin(m, i, j)) //依次旋转1区中单个元素
                return false;
    return true;
}
//沿dir方向压缩矩阵
bool compress(mat m, char *dir)
{
    if (!strcmp(dir, "up"))
        for (int j = 0; j < m.n; j++)
            for (int i = 1; i < m.n; i++)
            {
                //将元素压缩至第一行，并将其余元素置为0
                m.array[0][j] += m.array[i][j];
                m.array[i][j] = 0;
            }
    else if (!strcmp(dir, "down"))
        for (int j = 0; j < m.n; j++)
            for (int i = 0; i < m.n - 1; i++)
            {
                //将元素压缩至最后一行，并将其余元素置为0
                m.array[m.n - 1][j] += m.array[i][j];
                m.array[i][j] = 0;
            }
    else if (!strcmp(dir, "left"))
        for (int i = 0; i < m.n; i++)
            for (int j = 1; j < m.n; j++)
            {
                //将元素压缩至第一列，并将其余元素置为0
                m.array[i][0] += m.array[i][j];
                m.array[i][j] = 0;
            }
    else if (!strcmp(dir, "right"))
        for (int i = 0; i < m.n; i++)
            for (int j = 0; j < m.n - 1; j++)
            {
                //将元素压缩至最后一列，并将其余元素置为0
                m.array[i][m.n - 1] += m.array[i][j];
                m.array[i][j] = 0;
            }
    else
        return false;
    return true;
}

int main()
{
    mat m;
    init_mat(m);
    // cin >> m.n;
    m.n = 4;
    //分配矩阵内存
    m.array = (int **)malloc(sizeof(int *) * m.n);
    for (int i = 0; i < m.n; i++)
        m.array[i] = (int *)malloc(sizeof(int) * m.n);
    //输入矩阵
    for (int i = 0; i < m.n; i++)
        for (int j = 0; j < m.n; j++)
            cin >> m.array[i][j];
    char *cmd = new char;
    char *dir = new char;
    //输入指令
    cout << "Please enter the command and direction." << endl;
    cout << "cmd:compress/rotate"
         << "   "
         << "dir:up/down/left/right" << endl;
    cin >> cmd >> dir;
    //输出初始矩阵
    cout << "Original matrix:" << endl;
    output(m);
    //执行指令
    if (!strcmp(cmd, "compress"))
        if (!compress(m, dir))
            return -1;
    if (!strcmp(cmd, "rotate"))
        if (!rotate(m))
            return -1;
    //输出结果矩阵
    cout << "Changed matrix:" << endl;
    output(m);
    return 0;
}