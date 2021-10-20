int Get_Bit(int num, int pos)
{
    if (pos > sizeof(num) * 8)
        return -1;
    return ((num & (1 << pos)) >> pos);
}