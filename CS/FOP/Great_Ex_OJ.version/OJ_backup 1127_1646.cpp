#include <iostream>
#include <string.h>
#include <stdlib.h>
#define IN 0
#define OUT 1
#define TARGET 2
#define INBOX 0
#define OUTBOX 1
#define ADD 2
#define SUB 3
#define COPYTO 4
#define COPYFROM 5
#define JUMP 6
#define JUMPIFZERO 7
#define MAX_CMD_NUM 8
#define MAX_CMD_LENGTH 20
const char cmdName[MAX_CMD_NUM][MAX_CMD_LENGTH] = {"inbox", "outbox", "add", "sub", "copyto", "copyfrom", "jump", "jumpifzero"};

typedef struct List
{
    int *array;
    int curLen;
    int maxLen;
} L;
typedef struct Blank
{
    int *array;
    bool *arrayExist;
    int curLen;
    int maxLen;
} B;
typedef struct Field
{
    bool endTag;
    L *list;
    B blank;
    int cmdNum;
    int curCmd;
    int *cmdStream;
    int *cmdX;
    bool *cmdError;
    bool curBox;
    int curNum;
    bool cmdEnable[MAX_CMD_NUM];
    char cmdName[MAX_CMD_NUM][MAX_CMD_LENGTH];
} F;
void init(F &f)
{
    for (int i = 0; i < MAX_CMD_NUM; i++)
    {
        strcpy(f.cmdName[i], cmdName[i]);
        f.cmdEnable[i] = false;
    }
    f.list = new L[3]();
    for (int i = 0; i < 3; i++)
    {
        f.list[i].array = new int;
        f.list[i].curLen = 0;
        f.list[i].maxLen = 0;
    }
    f.blank.array = NULL;
    f.blank.arrayExist = NULL;
    f.blank.curLen = 0;
    f.blank.maxLen = 0;
    f.curBox = false;
    f.curNum = 0;
    f.curCmd = 0;
    f.cmdNum = 0;
}
void create(F &f)
{
    f.endTag = false;
    f.blank.arrayExist = new bool[f.blank.maxLen];
    for (int i = 0; i < f.blank.maxLen; i++)
        f.blank.arrayExist[i] = false;
    f.blank.array = new int[f.blank.maxLen];
    f.cmdStream = new int[f.cmdNum]();
    f.cmdX = new int[f.cmdNum]();
    f.cmdError = new bool[f.cmdNum]();
}
int trans(F f, char *word)
{
    for (int i = 0; i < MAX_CMD_NUM; i++)
        if (!strcmp(word, f.cmdName[i]))
            return i;
    return -1;
}
bool inbox(F &f)
{
    if (!f.list[IN].curLen)
        f.endTag = true;
    else
    {
        f.curBox = true;
        f.curNum = f.list[IN].array[0];
        f.list[IN].curLen--;
        for (int i = 0; i < f.list[IN].curLen; i++)
            f.list[IN].array[i] = f.list[IN].array[i + 1];
    }
    return true;
}
bool outbox(F &f)
{
    if (!f.curBox)
        return false;
    else
    {
        f.list[OUT].array[f.list[OUT].curLen] = f.curNum;
        f.list[OUT].curLen++;
        f.curBox = false;
        f.curNum = 0;
        return true;
    }
}
bool add(F &f)
{
    if (f.cmdX[f.curCmd] < 0 || f.cmdX[f.curCmd] > f.blank.maxLen - 1 || !f.blank.arrayExist[f.cmdX[f.curCmd]] || !f.curBox)
        return false;
    else
        f.curNum += f.blank.array[f.cmdX[f.curCmd]];
    return true;
}
bool sub(F &f)
{
    if (f.cmdX[f.curCmd] < 0 || f.cmdX[f.curCmd] > f.blank.maxLen - 1 || !f.blank.arrayExist[f.cmdX[f.curCmd]] || !f.curBox)
        return false;
    else
        f.curNum -= f.blank.array[f.cmdX[f.curCmd]];
    return true;
}
bool copyto(F &f)
{
    if (!f.curBox || f.cmdX[f.curCmd] < 0 || f.cmdX[f.curCmd] > f.blank.maxLen - 1)
        return false;
    else
    {
        f.blank.arrayExist[f.cmdX[f.curCmd]] = true;
        f.blank.array[f.cmdX[f.curCmd]] = f.curNum;
    }
    return true;
}
bool copyfrom(F &f)
{
    if (f.cmdX[f.curCmd] < 0 || f.cmdX[f.curCmd] > f.blank.maxLen - 1 || !f.blank.arrayExist[f.cmdX[f.curCmd]])
        return false;
    else
    {
        f.curBox = true;
        f.curNum = f.blank.array[f.cmdX[f.curCmd]];
    }
    return true;
}
bool jump(F &f)
{
    if (f.cmdX[f.curCmd] < 1 || f.cmdX[f.curCmd] > f.cmdNum)
        return false;
    else
        f.curCmd = f.cmdX[f.curCmd] - 2;
    return true;
}
bool jumpifzero(F &f)
{
    if (f.cmdX[f.curCmd] < 1 || f.cmdX[f.curCmd] > f.cmdNum || !f.curBox)
        return false;
    else if (!f.curNum)
        f.curCmd = f.cmdX[f.curCmd] - 2;
    return true;
}
void judge(F &f)
{
    if (f.list[OUT].curLen != f.list[TARGET].curLen)
        std::cout << "Fail" << std::endl;
    else
    {
        for (int i = 0; i < f.list[OUT].curLen; i++)
            if (f.list[OUT].array[i] != f.list[TARGET].array[i])
            {
                std::cout << "Fail" << std::endl;
                return;
            }
        std::cout << "Success" << std::endl;
    }
    return;
}
void cmdexe(F &f)
{
    bool (*fun[MAX_CMD_NUM])(F &) = {inbox, outbox, add, sub, copyto, copyfrom, jump, jumpifzero};
    for (int i = 0; i < f.cmdNum; i++)
    {
        char cmd[MAX_CMD_LENGTH] = {0};
        std::cin >> cmd;
        while (atof(cmd) || cmd[0] == '0')
        {
            f.cmdError[i - 1] = true;
            std::cin >> cmd;
        }
        f.cmdStream[i] = trans(f, cmd);
        if ((f.cmdStream[i] != 0) && (f.cmdStream[i] != 1) && (f.cmdStream[i] > 0))
        {
            float k = 0;
            std::cin >> k;
            f.cmdX[i] = (k - (int)k == 0) ? k : -1;
        }
    }
    while (1)
    {
        if (f.endTag || f.cmdError[f.curCmd])
            break;
        if (!f.cmdEnable[f.cmdStream[f.curCmd]] || f.cmdStream[f.curCmd] < 0 || f.cmdStream[f.curCmd] > MAX_CMD_NUM - 1)
        {
            f.cmdError[f.curCmd] = true;
            break;
        }
        if (!fun[f.cmdStream[f.curCmd]](f))
        {
            f.cmdError[f.curCmd] = true;
            break;
        }
        if (f.curCmd == f.cmdNum - 1)
        {
            f.endTag = true;
            break;
        }
        f.curCmd++;
    }
    if (f.cmdError[f.curCmd])
        std::cout << "Error on instruction " << f.curCmd + 1 << std::endl;
    else if (f.endTag)
        judge(f);
    else
        return;
}
void delete_(F &f)
{
    delete[] f.list;
    delete[] f.blank.array;
    delete[] f.blank.arrayExist;
    delete[] f.cmdStream;
    delete[] f.cmdX;
}
void level_1(F &f)
{
    f.cmdEnable[INBOX] = true;
    f.cmdEnable[OUTBOX] = true;
    f.blank.curLen = 0;
    f.blank.maxLen = 0;
    f.list[IN].curLen = 2;
    f.list[IN].maxLen = 2;
    f.list[IN].array[0] = 1;
    f.list[IN].array[1] = 2;
    f.list[TARGET].maxLen = 2;
    f.list[TARGET].curLen = 2;
    f.list[TARGET].array[0] = 1;
    f.list[TARGET].array[1] = 2;
    return;
}
void level_2(F &f)
{
    for (int i = 0; i < MAX_CMD_NUM; i++)
        f.cmdEnable[i] = true;
    f.blank.curLen = 0;
    f.blank.maxLen = 3;
    f.list[IN].curLen = 8;
    f.list[IN].maxLen = 8;
    f.list[IN].array[0] = 3;
    f.list[IN].array[1] = 9;
    f.list[IN].array[2] = 5;
    f.list[IN].array[3] = 1;
    f.list[IN].array[4] = -2;
    f.list[IN].array[5] = -2;
    f.list[IN].array[6] = 9;
    f.list[IN].array[7] = -9;
    f.list[TARGET].maxLen = 8;
    f.list[TARGET].curLen = 8;
    f.list[TARGET].array[0] = -6;
    f.list[TARGET].array[1] = 6;
    f.list[TARGET].array[2] = 4;
    f.list[TARGET].array[3] = -4;
    f.list[TARGET].array[4] = 0;
    f.list[TARGET].array[5] = 0;
    f.list[TARGET].array[6] = 18;
    f.list[TARGET].array[7] = -18;
    return;
}
void level_3(F &f)
{
    for (int i = 0; i < MAX_CMD_NUM; i++)
        f.cmdEnable[i] = true;
    f.blank.curLen = 0;
    f.blank.maxLen = 3;
    f.list[IN].curLen = 8;
    f.list[IN].maxLen = 8;
    f.list[IN].array[0] = 6;
    f.list[IN].array[1] = 2;
    f.list[IN].array[2] = 7;
    f.list[IN].array[3] = 7;
    f.list[IN].array[4] = -9;
    f.list[IN].array[5] = 3;
    f.list[IN].array[6] = -3;
    f.list[IN].array[7] = -3;
    f.list[TARGET].maxLen = 2;
    f.list[TARGET].curLen = 2;
    f.list[TARGET].array[0] = 7;
    f.list[TARGET].array[1] = -3;
    return;
}
int main()
{
    void (*levelFun[3])(F &) = {level_1, level_2, level_3};
    F field;
    init(field);
    int level = 0;
    std::cin >> level >> field.cmdNum;
    levelFun[level - 1](field);
    create(field);
    cmdexe(field);
    delete_(field);
    return 0;
}
