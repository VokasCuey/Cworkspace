#include "Tree_fun.h"

int Get_Num(TNode *Root, Graph &G)
{
    if (Root)
    {
        if (Root->Data.Tag == 0)
            G.Vex_Num++;
        else
            G.Link_Num++;
        Get_Num(Root->Child[Left], G);
        Get_Num(Root->Child[Right], G);
    }
    return OK;
}

int Init_Graph(Tree T, Graph &G)
{
    G.Vex_Num = 0;
    G.Link_Num = 0;
    G.Island_Num = 1;
    G.Vex_Start = NULL;
    G.Link_Start = NULL;
    G.Island_Start = NULL;
    Get_Num(T.Root, G);
    G.Link_Start = (GLink *)malloc(sizeof(GLink) * G.Link_Num);
    G.Vex_Num = 0;
    G.Link_Num = 0;
    return OK;
}

int Init_Island(Island &I)
{
    I.Num = 0;
    I.Start = NULL;
    I.Vex_Num = 0;
    return OK;
}

int Exist_Vex(Graph G, int Loc)
{
    int Num = 0;
    for (int i = 0; i < G.Vex_Num; i++)
    {
        if (G.Vex_Start[i].Loc == Loc)
        {
            Num = G.Vex_Start[i].Num;
            break;
        }
    }
    return Num;
}

int LoctoID(TNode *Root, int Loc, int Loc1)
{
    int ID = 0;
    if (Root)
    {
        if (((Root->Data.Loc == Loc) && (Root->Data.Loc1 == Loc1)) || ((Root->Data.Loc == Loc1) && (Root->Data.Loc1 == Loc)))
            ID = Root->Data.ID;
        if (ID)
            return ID;
        if (int i = LoctoID(Root->Child[Left], Loc, Loc1))
            ID = i;
        if (ID)
            return ID;
        else if (int i = LoctoID(Root->Child[Right], Loc, Loc1))
            ID = i;
        return ID;
    }
    return 0;
}

int IDtoVex(TNode *Root, int ID, GVex *&Vex)
{
    if (Root && (!Vex))
    {
        if (ID == Root->Data.ID)
        {
            Vex = Root->Vex;
            return OK;
        }
        else if (ID < Root->Data.ID)
            Root = Root->Child[Left];
        else if (ID > Root->Data.ID)
            Root = Root->Child[Right];
        IDtoVex(Root, ID, Vex);
    }
    if (Vex)
        return OK;
    return ERROR;
}

int IDtoLink(TNode *Root, int ID, GLink *&Link)
{
    if (Root && (!Link))
    {
        if (ID == Root->Data.ID)
            Link = Root->Link;
        else if (ID < Root->Data.ID)
            Root = Root->Child[Left];
        else if (ID > Root->Data.ID)
            Root = Root->Child[Right];
        if (Link)
            return OK;
        IDtoLink(Root, ID, Link);
    }
    if (Link)
        return OK;
    return ERROR;
}

int Create_Vex(Graph &G, int ID, int Loc0)
{
    G.Vex_Num++;
    G.Vex_Start = (GVex *)realloc(G.Vex_Start, sizeof(GVex) * G.Vex_Num);
    if (!G.Vex_Start)
        return ERROR;
    G.Vex_Start[G.Vex_Num - 1].Num = G.Vex_Num;
    G.Vex_Start[G.Vex_Num - 1].ID = ID;
    G.Vex_Start[G.Vex_Num - 1].Loc = Loc0;
    G.Vex_Start[G.Vex_Num - 1].Visit = 0;
    G.Vex_Start[G.Vex_Num - 1].First_Link = NULL;
    return G.Vex_Num;
}

int Create_Link(Graph &G, int ID, int Loc, int Loc1, int Weight)
{
    G.Link_Num++;
    G.Link_Start[G.Link_Num - 1].ID = ID;
    G.Link_Start[G.Link_Num - 1].Loc = Loc;
    G.Link_Start[G.Link_Num - 1].Loc1 = Loc1;
    G.Link_Start[G.Link_Num - 1].Weight = Weight;
    G.Link_Start[G.Link_Num - 1].Visit = 0;
    return G.Link_Num;
}

int Bind(GVex *Vex, GLink *Link)
{
    LNode *p = Vex->First_Link, *pp = NULL;
    while (p)
    {
        pp = p;
        p = p->Next_Link;
    }
    p = (LNode *)malloc(sizeof(LNode));
    if (!p)
        return ERROR;
    p->Link = Link;
    p->Next_Link = NULL;
    if (!pp)
        Vex->First_Link = p;
    else
        pp->Next_Link = p;
    return OK;
}

int Update_Model(TNode *Root, Graph &G)
{
    if (Root)
    {
        if (Root->Data.Tag == 0)
        {
            int i = 0;
            if (i = Exist_Vex(G, Root->Data.Loc))
                G.Vex_Start[i - 1].ID = Root->Data.ID;
            else
                i = Create_Vex(G, Root->Data.ID, Root->Data.Loc);
        }
        else
        {
            int i = 0;
            if (strcmp(Root->Data.Name, "开关") == 0)
                i = Create_Link(G, Root->Data.ID, Root->Data.Loc, Root->Data.Loc1, 0);
            else
                i = Create_Link(G, Root->Data.ID, Root->Data.Loc, Root->Data.Loc1, 1);
            if (int j = Exist_Vex(G, Root->Data.Loc))
                Bind(G.Vex_Start + j - 1, G.Link_Start + i - 1);
            else
            {
                j = Create_Vex(G, None, Root->Data.Loc);
                Bind(G.Vex_Start + j - 1, G.Link_Start + i - 1);
            }
            if (int j = Exist_Vex(G, Root->Data.Loc1))
                Bind(G.Vex_Start + j - 1, G.Link_Start + i - 1);
            else
            {
                j = Create_Vex(G, None, Root->Data.Loc1);
                Bind(G.Vex_Start + j - 1, G.Link_Start + i - 1);
            }
        }
        Update_Model(Root->Child[Left], G);
        Update_Model(Root->Child[Right], G);
    }
    return OK;
}

int Visit_Island(Tree T, Graph G, GVex *Vex, Island &I, int Weight)
{
    if (Vex)
        if (!Vex->Visit)
        {
            Vex->Visit = 1;
            if (Weight)
            {
                I.Vex_Num++;
                I.Start = (GVex **)realloc(I.Start, sizeof(GVex *) * I.Vex_Num);
                if (!I.Start)
                    return ERROR;
                I.Start[I.Vex_Num - 1] = Vex;
            }
            LNode *p = Vex->First_Link;
            while (p)
            {
                int Loc = 0;
                GVex *Next_Vex = NULL;
                if (p->Link->Loc == Vex->Loc)
                    Loc = p->Link->Loc1;
                else
                    Loc = p->Link->Loc;
                IDtoVex(T.Root, LoctoID(T.Root, Loc, None), Next_Vex);
                if (!Next_Vex)
                    for (int i = 0; i < G.Vex_Num; i++)
                        if (G.Vex_Start[i].ID == 0)
                            if (G.Vex_Start[i].Loc == Loc)
                            {
                                Next_Vex = G.Vex_Start + i;
                                break;
                            }
                Visit_Island(T, G, Next_Vex, I, p->Link->Weight);
                p = p->Next_Link;
            }
            return 1;
        }
    return 0;
}

int Island_Copy(Island *Dest, Island *Source)
{
    Dest->Vex_Num = Source->Vex_Num;
    Dest->Start = (GVex **)malloc(sizeof(GVex *) * Dest->Vex_Num);
    if (!Dest->Start)
        return ERROR;
    for (int i = 0; i < Dest->Vex_Num; i++)
    {
        Dest->Start[i] = Source->Start[i];
    }
    return OK;
}

int Gen_Island(Tree T, Graph &G)
{
    Island I;
    Init_Island(I);
    G.Island_Num = 0;
    for (int i = 0; i < G.Vex_Num; i++)
    {
        Init_Island(I);
        if (Visit_Island(T, G, G.Vex_Start + i, I, 1))
        {
            G.Island_Num++;
            G.Island_Start = (Island *)realloc(G.Island_Start, sizeof(Island) * G.Island_Num);
            if (!G.Island_Start)
                return ERROR;
            Island_Copy(G.Island_Start + G.Island_Num - 1, &I);
            G.Island_Start[G.Island_Num - 1].Num = G.Island_Num;
        }
    }
    for (int i = 0; i < G.Vex_Num; i++)
        G.Vex_Start[i].Visit = 0;
    return OK;
}

int GtoT(TNode *Root, Graph G)
{
    if (Root)
    {
        if (Root->Data.Tag == 0)
        {
            for (int i = 0; i < G.Vex_Num; i++)
            {
                if (G.Vex_Start[i].ID == Root->Data.ID)
                {
                    Root->Vex = G.Vex_Start + i;
                    Root->Link = NULL;
                    break;
                }
            }
            if (!Root->Vex)
                return ERROR;
        }
        else
        {
            for (int i = 0; i < G.Link_Num; i++)
            {
                if (G.Link_Start[i].ID == Root->Data.ID)
                {
                    Root->Link = G.Link_Start + i;
                    Root->Vex = NULL;
                    break;
                }
            }
            if (!Root->Link)
                return ERROR;
        }
        GtoT(Root->Child[Left], G);
        GtoT(Root->Child[Right], G);
    }
    return OK;
}

int Sort_Island(Graph &G)
{
    Island Test;
    Init_Island(Test);
    for (int i = 0; i < G.Island_Num; i++)
        for (int j = i + 1; j < G.Island_Num; j++)
            if (G.Island_Start[i].Vex_Num < G.Island_Start[j].Vex_Num)
            {
                Island_Copy(&Test, G.Island_Start + i);
                Island_Copy(G.Island_Start + i, G.Island_Start + j);
                Island_Copy(G.Island_Start + j, &Test);
            }
    return OK;
}

int Gen_Matrix(Graph G)
{
    return OK;
}

int Get_Island(Graph G, int Num)
{
    Island *I = G.Island_Start + Num - 1;
    if (!I)
        return ERROR;
    for (int i = 0; i < I->Vex_Num; i++)
        printf("%d ", i + 1);
    printf("\n");
    return OK;
}

int Get_Node(Tree T, Graph G, GVex *Vex, int Weight, int &Num)
{
    if (!Num)
        if (Vex)
            if (!Vex->Visit)
                if (!Weight)
                {
                    Vex->Visit = 1;
                    for (int i = 0; i < G.Island_Num; i++)
                    {
                        for (int j = 0; j < G.Island_Start[i].Vex_Num; j++)
                            if (Vex == G.Island_Start[i].Start[j])
                            {
                                Num = j + 1;
                                break;
                            }
                        if (Num)
                            break;
                    }
                    if (!Num)
                    {
                        LNode *p = Vex->First_Link;
                        while (p)
                        {
                            int Loc = 0;
                            GVex *Next_Vex = NULL;
                            if (p->Link->Loc == Vex->Loc)
                                Loc = p->Link->Loc1;
                            else
                                Loc = p->Link->Loc;
                            IDtoVex(T.Root, LoctoID(T.Root, Loc, None), Next_Vex);
                            if (!Next_Vex)
                                for (int i = 0; i < G.Vex_Num; i++)
                                    if (G.Vex_Start[i].ID == 0)
                                        if (G.Vex_Start[i].Loc == Loc)
                                        {
                                            Next_Vex = G.Vex_Start + i;
                                            break;
                                        }
                            Get_Node(T, G, Next_Vex, p->Link->Weight, Num);
                            p = p->Next_Link;
                        }
                    }
                }
    return OK;
}

int Get_Bus(Tree T, Graph G, int ID)
{
    GVex *Vex = NULL;
    IDtoVex(T.Root, ID, Vex);
    if (Vex)
    {
        int Num = 0;
        Get_Node(T, G, Vex, 0, Num);
        printf("%d\n", Num);
    }
    else
    {
        GLink *Link = NULL;
        IDtoLink(T.Root, ID, Link);
        GVex *Vex1 = NULL;
        IDtoVex(T.Root, LoctoID(T.Root, Link->Loc, None), Vex);
        if (!Vex)
            for (int i = 0; i < G.Vex_Num; i++)
                if (G.Vex_Start[i].ID == 0)
                    if (G.Vex_Start[i].Loc == Link->Loc)
                    {
                        Vex = G.Vex_Start + i;
                        break;
                    }
        IDtoVex(T.Root, LoctoID(T.Root, Link->Loc1, None), Vex1);
        if (!Vex1)
            for (int i = 0; i < G.Vex_Num; i++)
                if (G.Vex_Start[i].ID == 0)
                    if (G.Vex_Start[i].Loc == Link->Loc1)
                    {
                        Vex1 = G.Vex_Start + i;
                        break;
                    }
        if (!(Vex && Vex1))
            return ERROR;
        int Num = 0, Num1 = 0;
        Get_Node(T, G, Vex, 0, Num);
        for (int i = 0; i < G.Vex_Num; i++)
            G.Vex_Start[i].Visit = 0;
        Get_Node(T, G, Vex1, 0, Num1);
        printf("%d %d\n", Num, Num1);
    }
    for (int i = 0; i < G.Vex_Num; i++)
        G.Vex_Start[i].Visit = 0;
    return OK;
}

int Get_Node_Link(Tree T, Graph G, GVex *Vex, int Weight)
{
    if (Vex)
        if (!Vex->Visit)
            if (!Weight)
            {
                Vex->Visit = 1;
                if (Vex->ID)
                    printf("%d\n", Vex->ID);
                LNode *p = Vex->First_Link;
                while (p)
                {
                    if (!p->Link->Visit)
                        printf("%d\n", p->Link->ID);
                    p->Link->Visit = 1;
                    int Loc = 0;
                    GVex *Next_Vex = NULL;
                    if (p->Link->Loc == Vex->Loc)
                        Loc = p->Link->Loc1;
                    else
                        Loc = p->Link->Loc;
                    IDtoVex(T.Root, LoctoID(T.Root, Loc, None), Next_Vex);
                    if (!Next_Vex)
                        for (int i = 0; i < G.Vex_Num; i++)
                            if (G.Vex_Start[i].ID == 0)
                                if (G.Vex_Start[i].Loc == Loc)
                                {
                                    Next_Vex = G.Vex_Start + i;
                                    break;
                                }
                    Get_Node_Link(T, G, Next_Vex, p->Link->Weight);
                    p = p->Next_Link;
                }
                return OK;
            }
}

int Get_Equip(Tree T, Graph G, int Island_Num, int Num)
{
    GVex *Vex = NULL;
    for (int i = 0; i < G.Island_Start[Island_Num - 1].Vex_Num; i++)
        if (Num == i + 1)
        {
            Vex = G.Island_Start[Island_Num - 1].Start[i];
            break;
        }
    if (!Vex)
        return ERROR;
    Get_Node_Link(T, G, Vex, 0);
    for (int i = 0; i < G.Vex_Num; i++)
        G.Vex_Start[i].Visit = 0;
    for (int i = 0; i < G.Link_Num; i++)
        G.Link_Start[i].Visit = 0;
    return OK;
}

int Get_Line(Tree T, Graph G, int i, int j)
{
    for (int m = 0; m < G.Link_Num; m++)
    {
        if (G.Link_Start[m].Weight == 1)
        {
            GVex *Vex = NULL, *Vex1 = NULL;
            int Num = 0, Num1 = 0;
            IDtoVex(T.Root, LoctoID(T.Root, G.Link_Start[m].Loc, None), Vex);
            if (!Vex)
                for (int n = 0; n < G.Vex_Num; n++)
                    if (G.Vex_Start[n].Loc == G.Link_Start[m].Loc)
                    {
                        Vex = G.Vex_Start + n;
                        break;
                    }
            if (!Vex)
                return ERROR;
            Get_Node(T, G, Vex, 0, Num);
            IDtoVex(T.Root, LoctoID(T.Root, G.Link_Start[m].Loc1, None), Vex1);
            if (!Vex1)
                for (int n = 0; n < G.Vex_Num; n++)
                    if (G.Vex_Start[n].Loc == G.Link_Start[m].Loc1)
                    {
                        Vex1 = G.Vex_Start + n;
                        break;
                    }
            if (!Vex1)
                return ERROR;
            Get_Node(T, G, Vex1, 0, Num1);
            if (((i == Num) && (j == Num1)) || ((i == Num1) && (j == Num)))
            {
                printf("%d\n", G.Link_Start[m].ID);
                return G.Link_Start[m].ID;
            }
        }
    }
    return ERROR;
}

int Get_Y(int i, int j)
{
    return OK;
}