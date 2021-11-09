#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;

#define MAX_LENGTH 1000

int sub_pos(char *main, char *sub)
{
    if (strlen(main) < strlen(sub))
        return -1;
    for (int i = 0, j = 0; i < strlen(main); i++)
    {
        j = 0;
        for (; j < strlen(sub); j++)
        {
            if (main[i + j] != sub[j])
                break;
        }
        if (j == strlen(sub))
            return i;
    }
    return -1;
}

int main()
{
    ifstream fin;
    ofstream fou;
    fin.open("input.txt");
    fou.open("output.txt");
    if (fin && fou)
    {
        char a[MAX_LENGTH], b[MAX_LENGTH];
        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));
        fin.getline(a, MAX_LENGTH);
        fin.getline(b, MAX_LENGTH);
        fou << sub_pos(a, b);
        fin.close();
        fou.close();
    }
    else
        cout << "Not found.\n";
    return 0;
}