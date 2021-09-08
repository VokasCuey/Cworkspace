#include "Graph_fun.h"
int main()
{
    Tree T;
    Init_Tree(T);
    FILE *rp = fopen("电气设备表.txt", "r");
    if (!rp)
    {
        printf("The file could not be opened.\n");
        return -1;
    }
    else
    {
        In_Tree(rp, T);
        Graph G;
        Init_Graph(T, G);
        Update_Model(T.Root, G);
        GtoT(T.Root, G);
        Gen_Island(T, G);
        char Order[MAX_WORD_LENGTH];
        while (1)
        {
            memset(Order, 0, sizeof(Order));
            printf("Please enter your order.\n");
            gets(Order);
            printf("-------------------------------\n");
            if (Order[0] == 'i')
            {
                int ID = 0, Tag = -1, Loc = 0, Loc1 = 0;
                char Name[MAX_WORD_LENGTH], Status[MAX_WORD_LENGTH], Info[MAX_WORD_LENGTH], Num[MAX_WORD_LENGTH];
                memset(Name, 0, sizeof(Name));
                memset(Status, 0, sizeof(Status));
                memset(Info, 0, sizeof(Info));
                memset(Num, 0, sizeof(Num));
                printf("Please enter the info.\n");
                printf("ID=");
                scanf("%d", &ID);
                printf("Device=");
                scanf("%s", Name);
                getchar();
                while (1)
                {
                    printf("Location=");
                    gets(Info);
                    if ((Info[0] == 'F') || (Info[0] == 'A'))
                        break;
                    else
                        printf("Location Error.\n");
                }
                if (Info[0] == 'F')
                {
                    int i = 5;
                    Tag = 1;
                    for (int j = 0; Info[i] != ' '; i++, j++)
                        Num[j] = Info[i];
                    Loc = atoi(Num);
                    memset(Num, 0, sizeof(Num));
                    i += 4;
                    for (int j = 0; Info[i] != '\0'; i++, j++)
                        Num[j] = Info[i];
                    Loc1 = atoi(Num);
                }
                else
                {
                    int i = 3;
                    Tag = 0;
                    Loc1 = None;
                    for (int j = 0; Info[i] != '\0'; i++, j++)
                        Num[j] = Info[i];
                    Loc = atoi(Num);
                }
                memset(Info, 0, sizeof(Info));
                while (1)
                {
                    printf("Status=");
                    gets(Info);
                    if (Info[0] == 'S')
                        break;
                    else
                        printf("Status Error.\n");
                }
                for (int i = 7, j = 0; i < strlen(Info); i++, j++)
                    Status[j] = Info[i];
                printf("-------------------------------\n");
                if (Insert(T, ID, Name, Tag, Loc, Loc1, Status) == ERROR)
                    printf("Insert Error.\n");
                else
                    printf("Insert Complete.\n");
                printf("-------------------------------\n");
            }
            else if (Order[0] == 'd')
            {
                int ID = 0;
                printf("Please enter the ID of the device.\nID=");
                scanf("%d", &ID);
                printf("-------------------------------\n");
                if (Delete(T, ID) == ERROR)
                    printf("Delete Error.\n");
                else
                    printf("Delete Complete.\n");
                printf("-------------------------------\n");
                getchar();
            }
            else if (Order[0] == 'c')
            {
                int ID = 0, New_Loc = 0, New_Loc1 = 0;
                char New_Status[MAX_WORD_LENGTH], Info[MAX_WORD_LENGTH], Num[MAX_WORD_LENGTH];
                memset(New_Status, 0, sizeof(New_Status));
                memset(Info, 0, sizeof(Info));
                memset(Num, 0, sizeof(Num));
                printf("Please enter ID\nID=");
                scanf("%d", &ID);
                getchar();
                printf("Please enter the new location.\n");
                while (1)
                {
                    printf("New Location=");
                    gets(Info);
                    if ((Info[0] == 'F') || (Info[0] == 'A'))
                        break;
                    else
                        printf("Location Error.\n");
                }
                if (Info[0] == 'F')
                {
                    int i = 5;
                    for (int j = 0; Info[i] != ' '; i++, j++)
                        Num[j] = Info[i];
                    New_Loc = atoi(Num);
                    memset(Num, 0, sizeof(Num));
                    i += 4;
                    for (int j = 0; Info[i] != '\0'; i++, j++)
                        Num[j] = Info[i];
                    New_Loc1 = atoi(Num);
                }
                else
                {
                    int i = 3;
                    New_Loc1 = None;
                    for (int j = 0; Info[i] != '\0'; i++, j++)
                        Num[j] = Info[i];
                    New_Loc = atoi(Num);
                }
                memset(Info, 0, sizeof(Info));
                while (1)
                {
                    printf("Status=");
                    gets(Info);
                    if (Info[0] == 'S')
                        break;
                    else
                        printf("Status Error.\n");
                }
                for (int i = 7, j = 0; i < strlen(Info); i++, j++)
                    New_Status[j] = Info[i];
                printf("-------------------------------\n");
                if (Change(T, ID, New_Loc, New_Loc1, New_Status) == ERROR)
                    printf("Change Error.\n");
                else
                    printf("Change Complete\n");
                printf("-------------------------------\n");
            }
            else if (Order[0] == 'p')
            {
                int ID = 0;
                printf("Please enter the ID of the device.\nID=");
                scanf("%d", &ID);
                printf("-------------------------------\n");
                Print(T, ID);
                printf("-------------------------------\n");
                getchar();
            }
            else if (Order[0] == 'f')
            {
                int fromto = 0, Num = 0;
                printf("Please enter fromto.\nfromto=");
                scanf("%d", &fromto);
                printf("-------------------------------\n");
                int ID = Find(T.Root, fromto, Num);
                if (Num == 0)
                    printf("Find Error.\n");
                else
                {
                    printf("ToTal Num=%d.\n", Num);
                    printf("-------------------------------\n");
                    printf("Find Complete.\n");
                }
                printf("-------------------------------\n");
                getchar();
            }
            else if (Order[0] == 'e')
            {
                char File_Name[MAX_WORD_LENGTH];
                memset(File_Name, 0, sizeof(File_Name));
                printf("Please enter the name of file.\nFile Name=");
                scanf("%s", File_Name);
                printf("-------------------------------\n");
                if (Execute(T, File_Name) == ERROR)
                    printf("Excute Error.\n");
                else
                    printf("Excute Complete.\n");
                printf("-------------------------------\n");
                getchar();
            }
            else if (Order[0] == 'b')
                break;
            else
            {
                printf("Order Error.\n");
                getchar();
            }
        }
        fclose(rp);
    }
    system("pause");
    return 0;
}