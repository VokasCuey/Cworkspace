#include "level.cpp"

int main()
{
    void (*levelFun[3])(F &) = {level_1, level_2, level_3};
    F field;
    init(field);
    int level = 0;
    std::cin >> level >> field.cmdNum;
    getchar();
    levelFun[level - 1](field);
    create(field);
    cmdexe(field);
    delete_(field);
    return 0;
}