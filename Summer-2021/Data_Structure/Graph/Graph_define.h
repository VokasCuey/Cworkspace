#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Graph_Link
{
    int ID;
    int Loc;
    int Loc1;
    int Weight;
    int Visit;
} GLink;

typedef struct Link_Node
{
    GLink *Link;
    Link_Node *Next_Link;
} LNode;

typedef struct Graph_Vex
{
    int Num;
    int ID;
    int Loc;
    LNode *First_Link;
    int Visit;
} GVex;

typedef struct Island
{
    int Num;
    int Vex_Num;
    GVex **Start;
} Island;

typedef struct Graph
{
    int Vex_Num;
    int Link_Num;
    int Island_Num;
    GVex *Vex_Start;
    GLink *Link_Start;
    Island *Island_Start;
} Graph;
