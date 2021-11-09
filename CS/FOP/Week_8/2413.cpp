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
int replace(char res[MAX_LENGTH], char str[3][MAX_LENGTH])
{
    if (sub_pos(str[0], str[1]) == -1)
    {
        strcpy(res, str[0]);
        return -1;
    }
    int i = 0;
    for (; i < sub_pos(str[0], str[1]); i++)
        res[i] = str[0][i];
    for (int j = 0; i < sub_pos(str[0], str[1]) + strlen(str[2]); i++, j++)
        res[i] = str[2][j];
    for (int j = sub_pos(str[0], str[1]) + strlen(str[1]); i < strlen(str[0]) + strlen(str[2]); i++, j++)
        res[i] = str[0][j];
    res[i] = '\0';
    return 1;
}

int main()
{
    char str[3][MAX_LENGTH];
    for (int i = 0; i < 3; i++)
        memset(str, 0, sizeof(str));
    ifstream in;
    ofstream out;
    in.open("input.txt");
    out.open("output.txt");
    if (in && out)
    {
        for (int i = 0; i < 3; i++)
            in.getline(str[i], MAX_LENGTH);
        char res[MAX_LENGTH];
        memset(res, 0, sizeof(res));
        replace(res, str);
        out << res;
        in.close();
        out.close();
    }
    else
        cout << "Not found.\n";
    return 0;
}