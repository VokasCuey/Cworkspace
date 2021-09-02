#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

Status Init_SSArray(SSArray &A)
{
    A.Head = NULL;
    A.Num = 0;
    A.Nonzero_Num = 0;
    return OK;
}

Status In_SSArray(FILE *rp, SSArray &A)
{
    A.Head = (ElemType *)malloc(sizeof(ElemType));
    fscanf(rp, "%d", &A.Num);
    char Skip[100];
    memset(Skip, 0, sizeof(Skip));
    for (int i = 0; i < A.Num; i++)
    {
        for (int j = 0; j < i + 1; j++)
        {
            float value = 0;
            fscanf(rp, "%f", &value);
            if (value == 0)
                continue;
            else
            {
                A.Nonzero_Num++;
                A.Head = (ElemType *)realloc(A.Head, sizeof(ElemType) * A.Nonzero_Num);
                if (!A.Head)
                    return ERROR;
                A.Head[A.Nonzero_Num - 1].i = i + 1;
                A.Head[A.Nonzero_Num - 1].j = j + 1;
                A.Head[A.Nonzero_Num - 1].Value = value;
            }
        }
        fgets(Skip, 1000, rp);
    }
    return OK;
}

Status Remove_SSArray(SSArray &A, int i, int j, float y)
{
    if (i == j)
        return ERROR;
    else if (i > j)
    {
        int t = j;
        j = i;
        i = t;
    }
    else
    {
        for (int k = 0; k < A.Nonzero_Num; k++)
        {
            if ((A.Head[k].i == i) && (A.Head[k].j == i))
            {
                A.Head[k].Value += y;
                if (A.Head[k].Value == 0)
                {
                    A.Head[k].i = 0;
                    A.Head[k].j = 0;
                }
                break;
            }
            if (k == A.Nonzero_Num - 1)
            {
                A.Nonzero_Num++;
                A.Head = (ElemType *)realloc(A.Head, sizeof(ElemType) * A.Nonzero_Num);
                A.Head[A.Nonzero_Num - 1].i = i;
                A.Head[A.Nonzero_Num - 1].j = i;
                A.Head[A.Nonzero_Num - 1].Value = y;
            }
        }
        for (int k = 0; k < A.Nonzero_Num; k++)
        {
            if ((A.Head[k].i == j) && (A.Head[k].j == j))
            {
                A.Head[k].Value += y;
                if (A.Head[k].Value == 0)
                {
                    A.Head[k].i = 0;
                    A.Head[k].j = 0;
                }
                break;
            }
            if (k == A.Nonzero_Num - 1)
            {
                A.Nonzero_Num++;
                A.Head = (ElemType *)realloc(A.Head, sizeof(ElemType) * A.Nonzero_Num);
                A.Head[A.Nonzero_Num - 1].i = j;
                A.Head[A.Nonzero_Num - 1].j = j;
                A.Head[A.Nonzero_Num - 1].Value = y;
            }
        }
        for (int k = 0; k < A.Nonzero_Num; k++)
        {
            if ((A.Head[k].i == j) && (A.Head[k].j == i))
            {
                A.Head[k].Value -= y;
                if (A.Head[k].Value == 0)
                {
                    A.Head[k].i = 0;
                    A.Head[k].j = 0;
                }
                break;
            }
            if (k == A.Nonzero_Num - 1)
            {
                A.Nonzero_Num++;
                A.Head = (ElemType *)realloc(A.Head, sizeof(ElemType) * A.Nonzero_Num);
                A.Head[A.Nonzero_Num - 1].i = j;
                A.Head[A.Nonzero_Num - 1].j = i;
                A.Head[A.Nonzero_Num - 1].Value = (-y);
            }
        }
    }
}

Status Add_SSArray(SSArray &A, int i, int j, float y)
{
    if (i == j)
        return ERROR;
    else if (i > j)
    {
        int t = j;
        j = i;
        i = t;
    }
    else
    {
        for (int k = 0; k < A.Nonzero_Num; k++)
        {
            if ((A.Head[k].i == i) && (A.Head[k].j == i))
            {
                A.Head[k].Value -= y;
                if (A.Head[k].Value == 0)
                {
                    A.Head[k].i = 0;
                    A.Head[k].j = 0;
                }
                break;
            }
            if (k == A.Nonzero_Num - 1)
            {
                A.Nonzero_Num++;
                A.Head = (ElemType *)realloc(A.Head, sizeof(ElemType) * A.Nonzero_Num);
                A.Head[A.Nonzero_Num - 1].i = i;
                A.Head[A.Nonzero_Num - 1].j = i;
                A.Head[A.Nonzero_Num - 1].Value = (-y);
            }
        }
        for (int k = 0; k < A.Nonzero_Num; k++)
        {
            if ((A.Head[k].i == j) && (A.Head[k].j == j))
            {
                A.Head[k].Value -= y;
                if (A.Head[k].Value == 0)
                {
                    A.Head[k].i = 0;
                    A.Head[k].j = 0;
                }
                break;
            }
            if (k == A.Nonzero_Num - 1)
            {
                A.Nonzero_Num++;
                A.Head = (ElemType *)realloc(A.Head, sizeof(ElemType) * A.Nonzero_Num);
                A.Head[A.Nonzero_Num - 1].i = j;
                A.Head[A.Nonzero_Num - 1].j = j;
                A.Head[A.Nonzero_Num - 1].Value = (-y);
            }
        }
        for (int k = 0; k < A.Nonzero_Num; k++)
        {
            if ((A.Head[k].i == j) && (A.Head[k].j == i))
            {
                A.Head[k].Value += y;
                if (A.Head[k].Value == 0)
                {
                    A.Head[k].i = 0;
                    A.Head[k].j = 0;
                }
                break;
            }
            if (k == A.Nonzero_Num - 1)
            {
                A.Nonzero_Num++;
                A.Head = (ElemType *)realloc(A.Head, sizeof(ElemType) * A.Nonzero_Num);
                A.Head[A.Nonzero_Num - 1].i = j;
                A.Head[A.Nonzero_Num - 1].j = i;
                A.Head[A.Nonzero_Num - 1].Value = y;
            }
        }
    }
}

float Print_SSArray(SSArray A, int i, int j)
{
    if ((i < 1) || (j < 1) || (i > A.Num) || (j > A.Num))
        return ERROR;
    for (int k = 0; k < A.Nonzero_Num; k++)
    {
        if (((A.Head[k].i == i) && (A.Head[k].j == j)) || ((A.Head[k].i == j) && (A.Head[k].j == i)))
            return A.Head[k].Value;
    }
    return 0;
}

int main()
{
    FILE *rp = fopen("数组作业输入.txt", "r");
    FILE *wp = fopen("数组作业输出.txt", "w");
    if (!(rp && wp))
    {
        printf("The file could not be opened.\n");
        return -1;
    }
    else
    {
        SSArray A;
        Init_SSArray(A);
        In_SSArray(rp, A);
        char Skip[100];
        memset(Skip, 0, sizeof(Skip));
        fgets(Skip, 100, rp);
        while (!feof(rp))
        {
            char Order[10];
            fscanf(rp, "%s", Order);
            if (Order[0] == '\n')
            {
                continue;
            }
            if (Order[0] == 'r')
            {
                int i = 0, j = 0;
                float y = 0;
                fscanf(rp, "%d %d %f", &i, &j, &y);
                Remove_SSArray(A, i, j, y);
            }
            if (Order[0] == 'a')
            {
                int i = 0, j = 0;
                float y = 0;
                fscanf(rp, "%d %d %f", &i, &j, &y);
                Add_SSArray(A, i, j, y);
            }
            if (Order[0] == 'p')
            {
                int i = 0, j = 0;
                fscanf(rp, "%d %d", &i, &j);
                fprintf(wp, "%f\n", Print_SSArray(A, i, j));
            }
        }
        fclose(rp);
    }
    system("pause");
    return 0;
}