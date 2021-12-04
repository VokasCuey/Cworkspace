#define IN 0
#define OUT 1
#define TARGET 2
#define INBOX 0
#define OUTBOX 1
#define ADD 2
#define SUB 3
#define COPYTO 4
#define COPYFROM 5
#define JUMP 6
#define JUMPIFZERO 7
#define MAX_CMD_NUM 8
#define MAX_CMD_LENGTH 20
#define MAX_LINE_LENGTH 1000
const char cmdName[MAX_CMD_NUM][MAX_CMD_LENGTH] = {"inbox", "outbox", "add", "sub", "copyto", "copyfrom", "jumpifzero", "jump"};

typedef struct List
{
    int *array;
    int curLen;
    int maxLen;
} L;
typedef struct Blank
{
    int *array;
    bool *arrayExist;
    int curLen;
    int maxLen;
} B;
typedef struct Field
{
    bool endTag;
    L *list;
    B blank;
    int cmdNum;
    int curCmd;
    int *cmdStream;
    int *cmdX;
    bool *cmdError;
    bool curBox;
    int curNum;
    bool cmdEnable[MAX_CMD_NUM];
    char cmdName[MAX_CMD_NUM][MAX_CMD_LENGTH];
} F;