#include <iostream>
using namespace std;

int get_bit(int n,int pos)
{
    if (pos>=sizeof(n)*8)
        return 0;
    return ((n & (1 << pos)) >> pos);
}

int main()
{
    int a=0b10011101;
    cout << get_bit(a,1);
   return 0;
}