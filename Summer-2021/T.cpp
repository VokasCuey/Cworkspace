#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

int main()
{
    char test[1000];
    memset(test,0,sizeof(test));
    cout << strlen(test) << endl;
    system("pause");
    return 0;
}