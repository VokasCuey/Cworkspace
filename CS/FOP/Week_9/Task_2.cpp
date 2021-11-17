#include <iostream>
#include <string>
#include <ctime>
#include <cmath>
#include <iomanip>
using namespace std;

// 定义生成整数值中2的最大幂次
#define MAX_2_POWER 5
// 定义指令数量
#define CMD_NUM 4
// 定义方阵大小
#define SQUARE_MATRIX_SIZE 4
// 定义指令名
const char cmdName[CMD_NUM][10] = {"Quit", "Rotate", "Melt", "Compress"};

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
bool create(mat &m, int nonzero)
{
    if ((nonzero < 0) || (nonzero > m.n * m.n))
        return false;
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
    // 初始化
    for (int i = 0; i < m.n; i++)
        for (int j = 0; j < m.n; j++)
            m.array[i][j] = 0;
    // 方阵非零元个数
    int nonzeroNum = 0;
    srand((unsigned int)time(NULL));
    // 遍历矩阵内所有点依次生成值，直到方阵内非零元个数等于输入值
    while (nonzeroNum < nonzero)
    {
        for (int i = 0; i < m.n; i++)
            for (int j = 0; j < m.n; j++)
                // 若该点值为0，则尝试生成值；若不为0，说明已经生成过非零值，不再重新生成
                if (!m.array[i][j])
                    // 若方阵内非零元个数小于输入值，则尝试生成
                    if (nonzeroNum < nonzero)
                    {
                        // 先随机生成0~1
                        m.array[i][j] = rand() / RAND_MAX;
                        // 若<0.5则置为0
                        if (m.array[i][j] < 0.5)
                            m.array[i][j] = 0;
                        // 若>0.5则生成非0值
                        else
                        {
                            m.array[i][j] = pow(2, int((MAX_2_POWER + 1) * rand() / RAND_MAX));
                            nonzeroNum++;
                        }
                    }
                    // 若方阵内非零元个数已等于输入值，则跳出函数
                    else
                        return true;
    }
    return true;
}
//输出矩阵
void print(mat m)
{
    for (int i = 0; i < m.n; i++)
    {
        for (int j = 0; j < m.n; j++)
            cout << setw(5) << m.array[i][j] << " ";
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
//压缩
void compress(mat &m)
{
    int x[2] = {0}, y[2] = {0};
    int dir = 0;
    cout << "***Please enter the direction***" << endl
         << "1 for up" << endl
         << "2 for down" << endl
         << "3 for left" << endl
         << "4 for right" << endl;
    cin >> dir;
    if (dir == 1)
        for (int j = 0; j < m.n; j++)
            for (int i = 1; i < m.n; i++)
            {
                //将元素压缩至第一行，并将其余元素置为0
                m.array[0][j] += m.array[i][j];
                m.array[i][j] = 0;
            }
    else if (dir == 2)
        for (int j = 0; j < m.n; j++)
            for (int i = 0; i < m.n - 1; i++)
            {
                //将元素压缩至最后一行，并将其余元素置为0
                m.array[m.n - 1][j] += m.array[i][j];
                m.array[i][j] = 0;
            }
    else if (dir == 3)
        for (int i = 0; i < m.n; i++)
            for (int j = 1; j < m.n; j++)
            {
                //将元素压缩至第一列，并将其余元素置为0
                m.array[i][0] += m.array[i][j];
                m.array[i][j] = 0;
            }
    else if (dir == 4)
        for (int i = 0; i < m.n; i++)
            for (int j = 0; j < m.n - 1; j++)
            {
                //将元素压缩至最后一列，并将其余元素置为0
                m.array[i][m.n - 1] += m.array[i][j];
                m.array[i][j] = 0;
            }
    else
        cout << "***Direction error***" << endl;
}
//消融
void melt(mat &m)
{
    // 遍历每一列，从下至上寻找是否有0
    for (int j = 0; j < m.n; j++)
    {
        // zeroTag置为true代表这一列从某一点往上全为0，否则有非零元
        bool zeroTag = false;
        for (int i = m.n; i > 1; i--)
        {
            // 若从上一点往上全为0，则不需在遍历该列，跳转至下一列
            if (zeroTag)
                break;
            // 如果有0，从这一点向上寻找是否有非零元
            if (!m.array[i - 1][j])
            {
                int k = 0;
                for (k = i - 1; k > 0; k--)
                    // 如果有非零元将其挪到最下方，并跳转至当前点的下一点
                    if (m.array[k - 1][j])
                    {
                        m.array[i - 1][j] = m.array[k - 1][j];
                        m.array[k - 1][j] = 0;
                        break;
                    }
                // 如果没有非零元则说明这一列从当前点往上全为0，将zeroTag置为true
                if (!k)
                    zeroTag = true;
            }
        }
    }
    // 进行相同元合并
    // exeTag置为true代表需要再进行下一次消融操作，否则不需要
    bool exeTag = false;
    for (int j = 0; j < m.n; j++)
        for (int i = 0; i < m.n - 1; i++)
            // 如果相邻两个元相等且不为0，进行合并
            if (m.array[i][j] && (m.array[i][j] == m.array[i + 1][j]))
            {
                // 若发生了合并，则需再次进行消融操作，将exeTag置为true
                exeTag = true;
                m.array[i + 1][j] += m.array[i][j];
                m.array[i][j] = 0;
            }
    // 若一次合并都未发生，则不需再进行消融操作，跳出函数
    if (exeTag)
        melt(m);
}

int main()
{
    int nonzero = 0;
    char *cmd = new char;
    // 定义函数指针
    void (*fun[3])(mat &) = {rotate, melt, compress};
    mat m;
    init(m);
    m.n = SQUARE_MATRIX_SIZE;
    //输入非零元个数
    cout << "Please enter the nonzero number in the square matrix." << endl
         << "The number should be in [0," << m.n * m.n << ']' << endl;
    cin >> nonzero;
    //生成方阵
    if (!create(m, nonzero))
    {
        cout << "***Create matrix failure***" << endl;
        return -1;
    }
    else
        cout << "***Create matrix success***" << endl;
    //输出原始矩阵
    cout << "Initial matrix:" << endl;
    print(m);
    //输入指令流（无间隔输入）
    cout << "***Please enter the command stream continuously***" << endl
         << "0 for quit" << endl
         << "1 for rotate." << endl
         << "2 for melt." << endl
         << "3 for compress." << endl;
    getchar();
    gets(cmd);
    for (int i = 0;; i++)
    {
        //当前指令
        int nowCmd = cmd[i] - '0';
        // 指令超出预设范围
        if ((nowCmd > CMD_NUM - 1) || (nowCmd < 0))
        {
            cout << "***Cmd error***" << endl;
            continue;
        }
        else
        {
            //依次执行指令
            cout << "***Step " << i + 1 << ": " << cmdName[nowCmd] << " ***" << endl;
            // 指令为0（quit）时跳出
            if (!nowCmd)
                break;
            // 指令不为0时调用函数
            else
                fun[nowCmd - 1](m);
        }
        //输出执行当前指令后的矩阵
        cout << "Changed matrix:" << endl;
        print(m);
    }
    cout << "***End***";
    return 0;
}