#include <iostream>
#include "Facts_Judge.cpp"
#include "Print_Result.cpp"
using namespace std;

int main()
{
    int i = 0;
    for (i = 0; i < 63; i++)
        if (Facts_Judge(i))
            Print_Result(i);
    return 0;
}