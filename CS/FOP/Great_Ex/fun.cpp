#include "define.cpp"
#include <iostream>
#include <string.h>
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
    {
        int j = 0;
        for (j = 0; j < strlen(f.cmdName[i]); j++)
            if (word[j] != f.cmdName[i][j])
                break;
        if (j == strlen(f.cmdName[i]))
            return i;
    }
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
    bool (*fun[MAX_CMD_NUM])(F &) = {inbox, outbox, add, sub, copyto, copyfrom, jumpifzero, jump};
    for (int i = 0; i < f.cmdNum; i++)
    {
        char tmp[MAX_LINE_LENGTH] = {0};
        gets(tmp);
        f.cmdStream[i] = trans(f, tmp);
        if (f.cmdStream[i] >= 0)
        {
            char tmp2[MAX_LINE_LENGTH] = {0};
            for (int j = strlen(f.cmdName[f.cmdStream[i]]) + 1, k = 0; j < strlen(tmp); j++, k++)
                tmp2[k] = tmp[j];
            if (f.cmdStream[i] == 0 || f.cmdStream[i] == 1)
            {
                if (tmp2[0])
                {
                    f.cmdError[i] = true;
                }
            }
            else
            {
                f.cmdX[i] = ((atoi(tmp2) == atof(tmp2) && atof(tmp2) != 0) || tmp2[0] == '0') ? atoi(tmp2) : -1;
                if (tmp2[0] == '0' && tmp2[1])
                    f.cmdX[i] = -1;
                if (f.cmdX[i] < 0)
                    f.cmdError[i] = true;
            }
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