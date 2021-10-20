int Max_Pos(int num)
{
    for (int i = 32; i > 0; i--)
        if (((num & (1 << (i - 1))) >> (i - 1)))
            return i-1;
    return -1;
}