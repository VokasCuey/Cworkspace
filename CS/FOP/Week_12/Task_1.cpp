#include <iostream>
#include <fstream>
#include <string.h>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <conio.h>
using namespace std;

#define MAX_WORD_LENGTH 1000
// 定义生成整数值中2的最大幂次
#define MAX_2_POWER 2
// 定义指令数量
#define CMD_NUM 3
// 定义方阵大小
#define SQUARE_DEFAULT_SIZE 4
// 定义键盘输入代表的方向
const char dir[4] = {'k', 'l', 'i', 'j'};
// 定义文件名
const char config_filename[] = "config.txt";
const char cmd_filename[] = "cmd.txt";
// 定义指令名
const char cmdName[CMD_NUM][10] = {"Quit", "Rotate", "Melt"};
// 定义文件内容合法格式
const char sizeFormat[8] = "SIZE = ";
const char randFormat[8] = "RAND = ";
const char logFormat[8] = "LOG = ";
const char boxFormat[8] = "BOX = ";
// 是否找到RAND = X，找到为true，否则为false
bool RfindTag = true;
// 是否找到box = true行，默认为false，找到后置为true
bool box = false;
// 是否需要键盘输入，默认为false，若cmd.txt文件内容为空则置为true
bool keyboard = false;
// 找到LOG = FILENAME行后所读取的filename，用output_filename[0]来表示是否找到该行
char output_filename[MAX_WORD_LENGTH] = {0};

//定义结构体square（方阵）
typedef struct square_matrix
{
    // 矩阵大小
    int n;
    // 矩阵元素
    int **data;
} mat;

void line(int n)
{
    for (int i = 0; i < n; i++)
        cout << '-';
    cout << endl;
}
//初始化矩阵
void init(mat &m)
{
    m.n = 0;
    m.data = NULL;
}
// 给ptr分配空内存并将矩阵内容赋值给ptr
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
// 将ptr内的值赋值给矩阵,并释放ptr内存
void inv_copy(int **ptr, mat &m)
{
    int count = 0;
    for (int i = 0; i < m.n; i++)
        for (int j = 0; j < m.n; j++)
        {
            *((int *)m.data + count) = ptr[i][j];
            count++;
        }
    for (int i = 0; i < m.n; i++)
        delete[] ptr[i];
    delete[] ptr;
}
// 读入config.txt文件
void cfg_read(const char *cfg_filename, mat &m, float &per)
{
    ifstream cfgtxt(cfg_filename);
    if (cfgtxt)
    {
        while (!cfgtxt.eof())
        {
            // skipTag代表是否需要跳过该行（即该行内容是否有效），true代表需要跳过该行
            // sizeTag代表该行是否在设置矩阵大小，true代表是
            // randTag代表该行是否在设置矩阵非零元比例，true代表是
            // logTag代表该行是否在设置输出文件，true代表是
            // boxTag代表改行是否在设置有无边框，true代表是
            bool skipTag = false, sizeTag = false, randTag = false, logTag = false, boxTag = false;
            ;
            char tmp[MAX_WORD_LENGTH] = {0};
            char word = '\0';
            // 读取该行第一个字符，判断该行是否有效，若有效进一步判断该行所设置的值
            word = cfgtxt.get();
            if (word == '#')
                skipTag = true;
            else if (word == 'S')
                sizeTag = true;
            else if (word == 'R')
                randTag = true;
            else if (word == 'L')
                logTag = true;
            else if (word == 'B')
                boxTag = true;
            else
                skipTag = true;
            // 根据所判断读取数据的不同进行不同位数的读入
            for (int i = 1; i < ((sizeTag || randTag) ? 7 : 6); i++)
            {
                if (skipTag)
                    break;
                word = cfgtxt.get();
                // 不符合格式则需跳过改行
                if (word != sizeFormat[i] && word != randFormat[i] && word != logFormat[i] && word != boxFormat[i])
                    skipTag = true;
            }
            // 若不符合格式则跳过改行
            if (skipTag)
            {
                cfgtxt.getline(tmp, MAX_WORD_LENGTH);
                continue;
            }
            cfgtxt.getline(tmp, MAX_WORD_LENGTH);
            // 判断所读取的size/per/output_filename/box是否符合要求，是则对变量进行覆盖性修改
            if (sizeTag)
                for (int i = 0; i < strlen(tmp); i++)
                    if (tmp[i] == '.')
                        continue;
            if (sizeTag)
                m.n = (atoi(tmp) < 1 ? m.n : atoi(tmp));
            if (randTag)
                per = ((atof(tmp) < 0 || atof(tmp) > 100) ? per : atof(tmp));
            if (logTag)
            {
                memset(output_filename, 0, sizeof(output_filename));
                strcpy(output_filename, tmp);
            }
            if (boxTag)
                if (!strcmp(tmp, "TRUE"))
                    box = true;
                else
                    box = false;
        }
        cfgtxt.close();
    }
    else
        cout << "Could not find file config.txt!" << endl;
    // 如果未找到SIZE = X形式的行，则将矩阵大小设置为预设值（4）
    if (!m.n)
    {
        cout << "Could not find size in config.txt!" << endl;
        m.n = SQUARE_DEFAULT_SIZE;
    }
    // 如果未找到RAND = X形式的行，则将矩阵非零元个数设置为1，同时将RfindTag设为false，代表未找到per的预设值
    if (!per)
    {
        cout << "Could not find percent in config.txt!" << endl;
        per = 100.0 / (m.n * m.n);
        RfindTag = false;
    }
    cout << "Get square matrix size " << m.n << endl
         << "Get nonzero percent " << per << '%' << endl;
    if (output_filename[0])
        cout << "Get LOG = " << output_filename << endl;
    else
        cout << "Could not find filename in config.txt!" << endl;
    cout << "Get BOX = " << (box ? "true" : "false") << endl;
}
// 创造矩阵，进行内存分配和赋值
void create(mat &m, float per, bool cmdTag)
{
    // 矩阵中应有的非零元个数
    int nonZero = int(per * m.n * m.n / 100);
    // 对每一个元素对应设置一个zeroTag，元素为0为true，否则为false
    bool **zeroTag = new bool *[m.n];
    for (int i = 0; i < m.n; i++)
        zeroTag[i] = new bool[m.n];
    for (int i = 0; i < m.n * m.n; i++)
        *((bool *)zeroTag + i) = true;
    // 分配矩阵空间并初始化
    m.data = new int *[m.n];
    for (int i = 0; i < m.n; i++)
        m.data[i] = new int[m.n];
    for (int i = 0; i < m.n * m.n; i++)
        *((int *)m.data + i) = 0;
    // 矩阵当前非零元个数
    int nonzeroNum = 0;
    srand((unsigned int)time(NULL));
    // 当矩阵中非零元个数等于预设值时，跳出赋值循环
    while (nonzeroNum != nonZero)
    {
        // 随机产生0~n^2-1整数，通过一维数组形式进行赋值
        int pos = ((float)rand() / RAND_MAX) * m.n * m.n;
        // 如果该处元素非零则不再重新赋值
        if (*((bool *)zeroTag + pos))
        {
            // 随机生成2^1~2^MAX_2_POWER整数
            *((int *)m.data + pos) = pow(2, int(MAX_2_POWER * ((float)rand() / RAND_MAX) + 1));
            // 该处元素非零，将对应的zeroTag置为false
            *((bool *)zeroTag + pos) = false;
            // 矩阵内非零元个数增加
            nonzeroNum++;
        }
    }
    // 如果未找到cmd.txt文件
    if (!cmdTag)
    {
        // 四个方向所对应的pos（一维数组）变化
        int dir[4] = {-m.n, m.n, -1, 1};
        for (int i = 0; i < m.n * m.n; i++)
            if (*((bool *)zeroTag + i))
                for (int j = 0; j < 4; j++)
                {
                    // 如果沿某个方向超出矩阵范围，则不计数
                    if ((i + dir[j] < m.n * m.n) && (i + dir[j] >= 0) && ((((i + dir[j]) % m.n) == (i % m.n)) || (((i + dir[j]) / m.n) == (i / m.n))))
                        // 如果沿该方向相邻元素为非零元，则计数增加
                        if (!(*((bool *)zeroTag + i + dir[j])))
                            (*((int *)m.data + i))++;
                }
        for (int i = 0; i < m.n * m.n; i++)
        {
            // 如果该点在随机生成时未生成值，而是在后来计数时计数赋值，则输出计数值
            if (*((bool *)zeroTag + i))
                cout << setw(4) << *((int *)m.data + i) << ' ';
            else
                // 如果该点是在随机生成时就已有值，则输出*
                cout << setw(4) << '*' << ' ';
            if (i % m.n == m.n - 1)
                cout << endl;
        }
    }
}
//输出矩阵
void print(mat m, ofstream &output)
{
    // 通过output_filename[0]判断是否需要向文件中输出数据
    // 通过box判断是否需要添加边框
    int **ptr = copy(m), maxPos = 0;
    for (int i = 0; i < m.n; i++)
        for (int j = 0; j < m.n; j++)
        {
            int pos = 0;
            for (int k = 0;; k++)
            {
                pos = k;
                if (!(int)(ptr[i][j] / pow(10, k)))
                    break;
            }
            pos > maxPos ? maxPos = pos : maxPos = maxPos;
        }
    for (int i = 0; i < m.n; i++)
    {
        // 若box=true，则加载边框，下同
        if (box)
        {
            for (int j = 0; j < m.n; j++)
            {
                cout << "+";
                for (int k = 0; k < maxPos; k++)
                    cout << '-';
            }
            cout << '+' << endl;
            // 若output_filename[0]不为'\0'，则向文件中输出数据，下同
            if (output_filename[0])
            {
                for (int j = 0; j < m.n; j++)
                {
                    output << "+";
                    for (int k = 0; k < maxPos; k++)
                        output << '-';
                }
                output << '+' << endl;
            }
            cout << '|';
            if (output_filename[0])
                output << '|';
        }
        for (int j = 0; j < m.n; j++)
        {
            if (ptr[i][j])
                cout << setw(maxPos) << ptr[i][j];
            else
                for (int k = 0; k < maxPos; k++)
                    cout << ' ';
            cout << (box ? '|' : ' ');
            if (output_filename[0])
            {
                if (ptr[i][j])
                    output << setw(maxPos) << ptr[i][j];
                else
                    for (int k = 0; k < maxPos; k++)
                        output << ' ';
                output << (box ? '|' : ' ');
            }
        }
        cout << endl;
        if (output_filename[0])
            output << endl;
    }
    if (box)
    {
        for (int j = 0; j < m.n; j++)
        {
            cout << "+";
            for (int k = 0; k < maxPos; k++)
                cout << '-';
        }
        cout << '+' << endl;
        if (output_filename[0])
        {
            for (int j = 0; j < m.n; j++)
            {
                output << "+";
                for (int k = 0; k < maxPos; k++)
                    output << '-';
            }
            output << '+' << endl;
        }
    }
}
//给定1区坐标后，确定2，3，4区坐标并旋转交换值
void spin(mat m, int **&ptr, int a, int b)
{
    int i[4] = {a - 1, m.n - b, m.n - a, b - 1};
    int j[4] = {b - 1, a - 1, m.n - b, m.n - a};
    int t = ((int **)ptr)[i[0]][j[0]];
    for (int k = 0; k < 3; k++)
        ptr[i[k]][j[k]] = ptr[i[k + 1]][j[k + 1]];
    ptr[i[3]][j[3]] = t;
}
//向右旋转矩阵90°
void rotate(mat &m, int **&ptr)
{
    for (int i = 1; i <= m.n / 2; i++)
        for (int j = i; j <= m.n - i; j++)
            spin(m, ptr, i, j); //依次旋转1区中单个元素
}
//消融
void melt(mat &m, int **&ptr)
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
        melt(m, ptr);
}
// 执行指令
void cmdexe(mat &m, const char *cmd_filename)
{
    // 定义函数指针
    void (*fun[2])(mat &, int **&) = {rotate, melt};
    // 打开cmd文件，创造/打开名为output_filename的文件
    ifstream cmdtxt(cmd_filename);
    ofstream output(output_filename);
    // 输出原始矩阵
    cout << "Initial matrix:" << endl;
    if (output_filename[0])
        output << "Initial matrix:" << endl;
    print(m, output);
    // 计数变量
    int count = 0;
    // 代表是否停止读取、执行指令，停止为true，否则为false
    bool stopTag = false;
    char tmp[MAX_WORD_LENGTH] = {0};
    while (!cmdtxt.eof())
    {
        if (stopTag)
            break;
        count++;
        // 逐行读取指令
        cmdtxt.getline(tmp, 8);
        for (int i = 0; i < CMD_NUM; i++)
        {
            // 与现有指令依次匹配
            if (!strcmp(tmp, cmdName[i]))
            {
                cout << "***Step " << count << ": " << cmdName[i] << "***" << endl;
                if (output_filename[0])
                    output << "***Step " << count << ": " << cmdName[i] << "***" << endl;
                // i=0代表quit，则将stopTag置为true，并跳过循环内其他内容
                if (!i)
                {
                    stopTag = true;
                    break;
                }
                // 将矩阵内内容复制给ptr，对ptr进行操作
                int **ptr = copy(m);
                // 当指令不是quit时，调用对应函数
                fun[i - 1](m, ptr);
                // 将ptr内内容复制给矩阵
                inv_copy(ptr, m);
                // 输出操作后的矩阵
                cout << "Changed matrix:" << endl;
                if (output_filename[0])
                    output << "Changed matrix:" << endl;
                print(m, output);
                break;
            }
        }
    }
    // cmd.txt文件为空
    if (count == 1 && !tmp[0])
    {
        keyboard = true;
        return;
    }
    cout << "***End***";
    if (output_filename[0])
        output << "***End***";
    cmdtxt.close();
    output.close();
}
// 通过旋转n次，消融，再旋转4-n次实现向四个方向的消融
bool melt_dir(mat &m, char ch)
{
    int i = 0;
    for (i = 0; i < 4; i++)
        // 判断方向
        if (ch == dir[i])
        {
            int **ptr = copy(m);
            // 需要先旋转i次
            for (int j = 0; j < i; j++)
                rotate(m, ptr);
            // 消融
            melt(m, ptr);
            // 再旋转4-i次
            for (int j = 0; j < 4 - i; j++)
                rotate(m, ptr);
            inv_copy(ptr, m);
            return true;
        }
    return false;
}
// 在矩阵中随机空位置生成2或4
bool gen(mat &m)
{
    int i = 0;
    // 判断矩阵中是否有非零元
    for (i = 0; i < m.n * m.n; i++)
        if (!(*((int *)m.data + i)))
            break;
    // 没有非零元则生成失败
    if (i == m.n * m.n)
        return false;
    int pos = 0;
    // 寻找空位置
    do
        pos = ((float)rand() / RAND_MAX) * m.n * m.n;
    while (*((int *)m.data + pos));
    // 随机生成2或4
    *((int *)m.data + pos) = pow(2, int(MAX_2_POWER * ((float)rand() / RAND_MAX) + 1));
    return true;
}
// 判断游戏是否结束
bool judge(mat &m)
{
    // 找到空位则未结束
    for (int i = 0; i < m.n * m.n; i++)
        if (!(*((int *)m.data + i)))
            return true;
    for (int i = 0; i < 4; i++)
    {
        mat newM;
        newM.n = m.n;
        newM.data = new int *[newM.n * newM.n];
        // 将元素复制到新矩阵newM中
        for (int j = 0; j < newM.n * newM.n; j++)
            *((int *)newM.data + j) = *((int *)m.data + j);
        // 依次向四个方向消融
        melt_dir(newM, dir[i]);
        // 如果消融后有空位则游戏未结束
        for (int i = 0; i < newM.n * newM.n; i++)
            if (!(*((int *)newM.data + i)))
            {
                // 释放内存
                delete[] newM.data;
                return true;
            }
        // 释放内存
        delete[] newM.data;
    }
    // 若五种情况下均无空位则游戏结束
    return false;
}
// 键盘输入
void keyboard_input(mat &m)
{
    // 表示游戏是否结束
    bool gameover = false;
    ofstream output(output_filename);
    // 轮数
    int count = 0;
    while (1)
    {
        if (gameover)
        {
            cout << "GAME OVER" << endl;
            break;
        }
        char ch = getch();
        cout << "cmd:" << '[' << ch << ']' << endl;
        if (cmd_filename[0])
            output << "cmd:" << '[' << ch << ']' << endl;
        if (ch == 'q')
            break;
        // 消融
        if (!melt_dir(m, ch))
        {
            cout << "Direction error" << endl;
            continue;
        }
        // 生成新数字
        if (!gen(m))
            cout << "Could not generate new number!" << endl;
        else
            count++;
        // 判断游戏是否结束
        if (!judge(m))
            gameover = true;
        cout << "Step: " << count << endl;
        if (cmd_filename[0])
            output << "Step: " << count << endl;
        // 输出改变后的矩阵
        print(m, output);
        line(100);
    }
    cout << "***End***" << endl;
    if (output_filename[0])
        output << "***End***";
    output.close();
}
int main()
{
    // 表示cmd.txt文件是否存在，存在为true，不存在为false
    bool cmdTag = true;
    // 非零元比例
    float per = 0;
    mat m;
    init(m);
    // 读入config文件内容
    cfg_read(config_filename, m, per);
    // 打开cmd.txt文件
    ifstream cmdtxt(cmd_filename);
    if (!cmdtxt)
        cmdTag = false;
    // 创造矩阵
    create(m, per, cmdTag);
    if (!cmdTag)
    {
        cout << "Could not find file cmd.txt!" << endl;
        return -1;
    }
    else
    {
        cmdtxt.close();
        // 执行指令
        cmdexe(m, cmd_filename);
        // 如果cmd.txt文件为空则键盘输入
        if (keyboard)
            keyboard_input(m);
    }
    return 0;
}