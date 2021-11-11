#include <iostream>
#include <fstream>
#include <malloc.h>
#include <cmath>
#include <string.h>
using namespace std;

#define MAX_NAME_LENGTH 30
#define sum 0
#define ch 1
#define math 2
#define eng 3
#define phy 4

typedef struct student
{
    char name[MAX_NAME_LENGTH] = {0};
    float score[5] = {0};
} stu;

void swap(stu &s1, stu &s2)
{
    stu s = s1;
    s1 = s2;
    s2 = s;
}
void sort(stu *array, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            for (int k = 0; k < 5; k++)
                if (abs(array[i].score[k] - array[j].score[k]) > 1e-3)
                {
                    if (array[i].score[k] < array[j].score[k])
                        swap(array[i], array[j]);
                    break;
                }
}

int main()
{
    ifstream in;
    ofstream out;
    in.open("input.txt");
    out.open("output.txt");
    if (in && out)
    {
        int n = 0;
        in >> n;
        stu *array = (stu *)malloc(sizeof(stu) * n);
        for (int i = 0; i < n; i++)
        {
            memset(array[i].name, 0, sizeof(array[i].name));
            in >> array[i].name;
            for (int j = 1; j < 5; j++)
            {
                in >> array[i].score[j];
                array[i].score[0] += array[i].score[j];
            }
        }
        sort(array, n);
        for (int i = 0; i < n; i++)
            out << array[i].name << endl;
        in.close();
        out.close();
    }
    else
        cout << "Not found.\n";
    return 0;
}