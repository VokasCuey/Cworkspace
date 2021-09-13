#include <iostream>
#include <stdlib.h>
#include <fstream>
using namespace std;

int main()
{
    int i=0;
    ofstream fout;
    fout.open("test.txt");
    if (!fout)
    return -1;
    fout << 1 << endl;
    fout.close();
    ifstream fin;
    fin.open("test,txt");
    if (!fin)
        return -1;
    fin >> i;
    cout << i << endl;
    fin.close();
    typedef void (*p)();
    typedef int (*q)(int, char);
    system("pause");
    return 0;
}