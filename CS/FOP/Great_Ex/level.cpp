#include "fun.cpp"
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
