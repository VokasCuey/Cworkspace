#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

int main()
{
    int leap = 2;
    char word = '\0';
    ifstream in;
    ofstream out;
    out.open("oup");
    in.open("inp");
    if (in && out)
    {
        in.seekg(-1, ios_base::end);
        while (1)
        {
            in.get(word);
            int now = in.tellg();
            out << word;
            if (now == leap - 1)
                break;
            if (word == '\n')
            {
                leap++;
                in.seekg(-leap - 1, ios_base::cur);
            }
            else
                in.seekg(-leap, ios_base::cur);
        }
        in.close();
        out.close();
    }
    else
        cout << "Not found." << endl;
    return 0;
}