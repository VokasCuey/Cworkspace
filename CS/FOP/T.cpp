#include <iostream>
#include <cstring>
#include <cmath>
#include <stdlib.h>
#include <fstream>
#include <ctime>
using namespace std;

int main()
{
    char str[]="TSINGHUA";
    ofstream out("out.txt");
    out << str;
    out.close();

    out.open("out.bin",ios::binary);
    out.write(str,strlen(str));
    out.close();
    //system("pause");
    return 0;
}