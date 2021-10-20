#include "Get_Bit.cpp"
bool Facts_Judge(int num)
{
    bool S1 = (Get_Bit(num, 0) || Get_Bit(num, 1)),
         S2 = (Get_Bit(num, 0) + Get_Bit(num, 4) + Get_Bit(num, 5) > 1),
         S3 = (!Get_Bit(num, 0) || !Get_Bit(num, 3)),
         S4 = (Get_Bit(num, 1) == Get_Bit(num, 2)),
         S5 = (Get_Bit(num, 2) != Get_Bit(num, 3)),
         S6 = (Get_Bit(num, 3) || (!Get_Bit(num, 4)));
    if (S1 && S2 && S3 && S4 && S5 && S6)
        return true;
    return false;
}