#include <stdio.h>
#include <stdlib.h>
typedef enum
{
    OK,
    ERROR
} Status;

typedef struct Elem
{
    int i;
    int j;
    float Value;
} ElemType;

typedef struct Sym_Sparse_Array
{
    ElemType *Head;
    int Num;
    int Nonzero_Num;
} SSArray;

Status
Init_SSArray(SSArray &A)
{
    A.Head = NULL;
    A.Num = 0;
    A.Nonzero_Num = 0;
}

Status
In_SSArray(FILE *rp, SSArray &A)
{
    fscanf(rp, "%d", &A.Num);
    for (int i = 0; i < A.Num; i++)
    {
        for (int j = 0; j < i + 1; j++)
        {
            int value = 0;
            fscanf(rp, "%d", &value);
            if (value == 0)
                continue;
            else
            {
                A.Nonzero_Num++;
            }
        }
    }
}

int main()
{
    FILE *rp = fopen("数组作业输入.txt", "r");
    if (!rp)
    {
        printf("The file could not be opened.\n");
        return -1;
    }
    else
    {
        SSArray A;
        Init_SSArray(A);
        In_SSArray(rp, A);
        fclose(rp);
    }
    system("pause");
    return 0;
}