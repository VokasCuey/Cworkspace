#include <stdio.h>
#include <stdlib.h>

#define INIT_LIST_SIZE 100
#define LIST_SIZE_INCREASEMEN 50

typedef struct Elem
{
    int ID;
    char Type[20];
    char Reg[20];
    char Ava[20];
    char Sta[20];
    char Life[20];
    char Runtime[20];
} Elem;
typedef struct Elem ElemType;
const ElemType Empty = {0, {0}, {0}, {0}, {0}, {0}, {0}};

typedef struct SqList
{
    ElemType *Head;
    int ListSize;
    int Length;
} SqList;

typedef enum
{
    OK,
    ERROR,
    OVERFLOW
} Status;

Status Init_SqList(SqList &L)
{
    L.Head = (ElemType *)malloc(INIT_LIST_SIZE * sizeof(ElemType));
    if (!L.Head)
    {
        return ERROR;
    }
    L.Length = 0;
    L.ListSize = INIT_LIST_SIZE;
    return OK;
}

Status Insert_Elem(SqList &L, int i, ElemType e)
{
    if (i < 1 || i > L.Length + 1)
    {
        return ERROR;
    }
    if (L.Length >= L.ListSize)
    {
        ElemType *newbase = (ElemType *)realloc(L.Head, (L.ListSize + LIST_SIZE_INCREASEMEN) * sizeof(ElemType));
        if (!newbase)
            return ERROR;
        L.Head = newbase;
        L.ListSize += LIST_SIZE_INCREASEMEN;
    }
    ElemType *move = &(L.Head[L.Length - 1]);
    ElemType *insert = &(L.Head[i - 1]);
    for (; move >= insert; move--)
    {
        *(move + 1) = *(move);
    }
    *insert = e;
    L.Length++;
    return OK;
}

Status Read_Elem(FILE *f, ElemType &e)
{
    fscanf(f, "%d %s %s %s %s %s %s", &(e.ID), e.Type, e.Reg, e.Ava, e.Sta, e.Life, e.Runtime);
    return OK;
}

Status Get_Elem(SqList L, int i, ElemType &e)
{
    if ((i < 1) || (i > L.Length))
    {
        return ERROR;
    }
    ElemType *p = L.Head;
    for (int j = 0; j < i - 1; j++)
    {
        p++;
    }
    e = *p;
    return OK;
}

Status Find_Elem(SqList L, int id, ElemType &e)
{
    for (int i = 0; i < L.Length; i++)
    {
        if ((L.Head + i)->ID == id)
        {
            e = *(L.Head + i);
            return OK;
        }
    }
    return ERROR;
}

Status Delete_Elem(SqList &L, int i)
{
    if ((i < 1) || (i > L.Length))
    {
        return ERROR;
    }
    ElemType *p = L.Head;
    for (int j = 1; j < i; j++)
    {
        p++;
    }
    for (int j = i; j < L.Length; j++)
    {
        *p = *(p + 1);
        p++;
    }
    *p = Empty;
    L.Length--;
    return OK;
}

int main()
{
    SqList L = {NULL, 0, 0};
    Init_SqList(L);
    FILE *rp = fopen("输入.txt", "r");
    FILE *wp = fopen("输出.txt", "w");
    if (!(rp && wp))
    {
        printf("The file could not be opened.\n");
        return ERROR;
    }
    else
    {
        int row_Num = 0, column_Num = 0;
        fscanf(rp, "%d %d", &row_Num, &column_Num);
        char skip[100];
        fgets(skip, 100, rp);
        fgets(skip, 100, rp);
        ElemType e;
        ElemType *p = L.Head;
        for (int i = 0; i < row_Num; i++)
        {
            Read_Elem(rp, e);
            *p = e;
            L.Length++;
            p++;
        }
        char Order[10];
        while (!feof(rp))
        {
            fscanf(rp, "%s", Order);
            if (Order[0] == 'i')
            {
                Read_Elem(rp, e);
                Insert_Elem(L, L.Length + 1, e);
            }
            if (Order[0] == 'g')
            {
                int i = 0;
                fscanf(rp, "%d", &i);
                Get_Elem(L, i, e);
                fprintf(wp, "%d %s %s %s %s %s %s", &(e.ID), e.Type, e.Reg, e.Ava, e.Sta, e.Life, e.Runtime);
            }
            if (Order[0] == 'f')
            {
                int id = 0;
                fgets(skip, 5, rp);
                fscanf(rp, "%d", &id);
                Find_Elem(L, id, e);
                fprintf(wp, "%d %s %s %s %s %s %s", &(e.ID), e.Type, e.Reg, e.Ava, e.Sta, e.Life, e.Runtime);
            }
            if (Order[0] == 'd')
            {
                int i = 0;
                fscanf(rp, "%d", &i);
                Delete_Elem(L, i);
            }
        }
        fclose(rp);
        fclose(wp);
    }
    system("pause");
    return 0;
}