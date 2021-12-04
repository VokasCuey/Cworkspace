#include <iostream>
#include <fstream>
#include <string.h>
#include <ctime>
#include <cmath>
#include <iomanip>
using namespace std;

#define MAX_WORD_LENGTH 1000
// 定义生成整数值中2的最大幂次
#define MAX_2_POWER 5
// 定义指令数量
#define CMD_NUM 4
// 定义方阵大小
#define SQUARE_DEFAULT_SIZE 4
// 定义指令名
const char config_filename[] = "config.txt";
const char cmd_filename[] = "cmd.txt";
const char cmdName[CMD_NUM][10] = {"Quit", "Rotate", "Melt", "Compress"};
const char sizeFormat[8] = "SIZE = ";
const char randFormat[8] = "RAND = ";
bool RfindTag = true;

//定义结构体square（方阵）
typedef struct square_matrix
{
    // 矩阵大小
    int n;
    // 矩阵元素
    int **data;
} mat;

//初始化矩阵
void init(mat &m)
{
    m.n = 0;
    m.data = NULL;
}
int **copy(mat m)
{
    int **ptr = new int *[m.n], count = 0;
    for (int i = 0; i < m.n; i++)
        ptr[i] = new int[m.n];
    for (int i = 0; i < m.n; i++)
        for (int j = 0; j < m.n; j++)
        {
            ptr[i][j] = *((int *)m.data + count);
            count++;
        }
    return ptr;
}
void inv_copy(int **ptr, mat &m)
{
    int count = 0;
    for (int i = 0; i < m.n; i++)
        for (int j = 0; j < m.n; j++)
        {
            *((int *)m.data + count) = ptr[i][j];
            count++;
        }
}
//生成初始随机矩阵
void cfg_read(const char *cfg_filename, mat &m, float &per)
{
    ifstream cfgtxt(cfg_filename);
    if (cfgtxt)
    {
        while (!cfgtxt.eof())
        {
            bool skipTag = false, sizeTag = false, randTag = false;
            char temp[MAX_WORD_LENGTH] = {0};
            char word = '\0';
            word = cfgtxt.get();
            if (word == '#')
                skipTag = true;
            else if (word == 'S')
                sizeTag = true;
            else if (word == 'R')
                randTag = true;
            else
                skipTag = true;
            for (int i = 1; i < 7; i++)
            {
                if (skipTag)
                    break;
                word = cfgtxt.get();
                if ((word == '#' && i == 0) || ((word != sizeFormat[i]) && (word != randFormat[i])))
                    skipTag = true;
            }
            if (skipTag)
            {
                cfgtxt.getline(temp, MAX_WORD_LENGTH);
                continue;
            }
            // m.n = cfgtxt.get() - '0';
            cfgtxt.getline(temp, MAX_WORD_LENGTH);
            if (sizeTag)
                for (int i = 0; i < strlen(temp); i++)
                    if (temp[i] == '.')
                        continue;
            if (sizeTag)
                m.n = (atoi(temp) < 1 ? m.n : atoi(temp));
            if (randTag)
                per = ((atoi(temp) < 0 || atoi(temp) > 100) ? per : atoi(temp));
        }
        cfgtxt.close();
    }
    else
        cout << "Could not find file config.txt!" << endl;
    if (!m.n)
    {
        cout << "Could not find size int config.txt!" << endl;
        m.n = SQUARE_DEFAULT_SIZE;
    }
    if (!per)
    {
        cout << "Could not find percent int config.txt!" << endl;
        per = 100.0 / (m.n * m.n);
        RfindTag = false;
    }
    cout << "Get square matrix size " << m.n << endl
         << "Get nonzero percent " << per << '%' << endl;
}
void create(mat &m, float per, bool cmdTag)
{
    int nonZero = int(per * m.n * m.n / 100);
    bool **zeroTag = new bool *[m.n];
    for (int i = 0; i < m.n; i++)
        zeroTag[i] = new bool[m.n];
    for (int i = 0; i < m.n * m.n; i++)
        *((bool *)zeroTag + i) = true;
    m.data = new int *[m.n];
    for (int i = 0; i < m.n; i++)
        m.data[i] = new int[m.n];
    for (int i = 0; i < m.n * m.n; i++)
        *((int *)m.data + i) = 0;
    // for (int i = 0; i < m.n; i++)
    //     for (int j = 0; j < m.n; j++)
    //         m.data[i][j] = 0;
    int nonzeroNum = 0;
    srand((unsigned int)time(NULL));
    while (nonzeroNum != nonZero)
    {
        int pos = ((float)rand() / RAND_MAX) * m.n * m.n;
        if (*((bool *)zeroTag + pos))
        {
            *((int *)m.data + pos) = pow(2, int((RfindTag ? (MAX_2_POWER) : 2) * ((float)rand() / RAND_MAX) + 1));
            *((bool *)zeroTag + pos) = false;
            nonzeroNum++;
        }
    }
    if (!cmdTag)
    {
        int dir[4] = {-m.n, m.n, -1, 1};
        for (int i = 0; i < m.n * m.n; i++)
            if (*((bool *)zeroTag + i))
                for (int j = 0; j < 4; j++)
                {
                    if ((i + dir[j] < m.n * m.n) && (i + dir[j] >= 0) && ((((i + dir[j]) % m.n) == (i % m.n)) || (((i + dir[j]) / m.n) == (i / m.n))))
                        if (!(*((bool *)zeroTag + i + dir[j])))
                            (*((int *)m.data + i))++;
                }
        for (int i = 0; i < m.n * m.n; i++)
        {
            if (*((bool *)zeroTag + i))
                cout << setw(4) << *((int *)m.data + i) << ' ';
            else
                cout << setw(4) << '*' << ' ';
            if (i % m.n == m.n - 1)
                cout << endl;
        }
    }
}
//输出矩阵
void print(mat m)
{
    int **ptr = copy(m);
    for (int i = 0; i < m.n; i++)
    {
        for (int j = 0; j < m.n; j++)
            cout << setw(4) << ptr[i][j] << ' ';
        cout << endl;
    }
}
//给定1区坐标后，确定2，3，4区坐标并旋转交换值
void spin(mat &m, int a, int b)
{
    int **ptr = copy(m);
    int i[4] = {a - 1, m.n - b, m.n - a, b - 1};
    int j[4] = {b - 1, a - 1, m.n - b, m.n - a};
    int t = ((int **)ptr)[i[0]][j[0]];
    for (int k = 0; k < 3; k++)
        ptr[i[k]][j[k]] = ptr[i[k + 1]][j[k + 1]];
    ptr[i[3]][j[3]] = t;
    inv_copy(ptr, m);
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
    int **ptr = copy(m);
    int dir = 0;
    if (dir == 1)
        for (int j = 0; j < m.n; j++)
            for (int i = 1; i < m.n; i++)
            {
                //将元素压缩至第一行，并将其余元素置为0
                ptr[0][j] += ptr[i][j];
                ptr[i][j] = 0;
            }
    else if (dir == 2)
        for (int j = 0; j < m.n; j++)
            for (int i = 0; i < m.n - 1; i++)
            {
                //将元素压缩至最后一行，并将其余元素置为0
                ptr[m.n - 1][j] += ptr[i][j];
                ptr[i][j] = 0;
            }
    else if (dir == 3)
        for (int i = 0; i < m.n; i++)
            for (int j = 1; j < m.n; j++)
            {
                //将元素压缩至第一列，并将其余元素置为0
                ptr[i][0] += ptr[i][j];
                ptr[i][j] = 0;
            }
    else if (dir == 4)
        for (int i = 0; i < m.n; i++)
            for (int j = 0; j < m.n - 1; j++)
            {
                //将元素压缩至最后一列，并将其余元素置为0
                ptr[i][m.n - 1] += ptr[i][j];
                ptr[i][j] = 0;
            }
    else
        cout << "***Direction error***" << endl;
    inv_copy(ptr, m);
}
//消融
void melt(mat &m)
{
    int **ptr = copy(m);
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
            if (!ptr[i - 1][j])
            {
                int k = 0;
                for (k = i - 1; k > 0; k--)
                    // 如果有非零元将其挪到最下方，并跳转至当前点的下一点
                    if (ptr[k - 1][j])
                    {
                        ptr[i - 1][j] = ptr[k - 1][j];
                        ptr[k - 1][j] = 0;
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
            if (ptr[i][j] && (ptr[i][j] == ptr[i + 1][j]))
            {
                // 若发生了合并，则需再次进行消融操作，将exeTag置为true
                exeTag = true;
                ptr[i + 1][j] += ptr[i][j];
                ptr[i][j] = 0;
            }
    // 若一次合并都未发生，则不需再进行消融操作，跳出函数
    if (exeTag)
        melt(m);
    inv_copy(ptr, m);
}
void cmdexe(mat &m, const char *cmd_filename)
{
    void (*fun[3])(mat &) = {rotate, melt, compress};
    ifstream cmdtxt(cmd_filename);
    int count = 0;
    bool stopTag = false;
    while (!cmdtxt.eof())
    {
        if (stopTag)
            break;
        count++;
        char temp[MAX_WORD_LENGTH] = {0};
        cmdtxt.getline(temp, 8);
        for (int i = 0; i < CMD_NUM; i++)
        {
            if (!strcmp(temp, cmdName[i]))
            {
                cout << "***Step " << count << ": " << cmdName[i] << "***" << endl;
                if (!i)
                {
                    stopTag = true;
                    break;
                }
                fun[i - 1](m);
                cout << "Changed matrix:" << endl;
                print(m);
                break;
            }
            if (i == CMD_NUM - 1)
                cout << "Cmd error!" << endl;
        }
    }
    cout << "***End***";
    cmdtxt.close();
}

int main()
{
    bool cmdTag = true;
    float per = 0;
    mat m;
    init(m);
    cfg_read(config_filename, m, per);
    ifstream cmdtxt(cmd_filename);
    if (!cmdtxt)
        cmdTag = false;
    create(m, per, cmdTag);
    if (!cmdTag)
    {
        cout << "Could not find file cmd.txt!" << endl;
        return -1;
    }
    else
    {
        cout << "Initial matrix:" << endl;
        print(m);
        cmdtxt.close();
        cmdexe(m, cmd_filename);
    }
    return 0;
}