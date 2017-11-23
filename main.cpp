#include <iostream>
#include "clist.h"

int main()
{
    // Exercise: реализовать перегрузку оператора скобочки для списка
    // и оператор сложения списков (различные версии)

    CList cSomeList;

    cSomeList.push_back(1);
    cSomeList.push_back(2);
    cSomeList.push_back(3);
    cSomeList.push_back(4);

    CList cCopyList(cSomeList);

    cCopyList.push_back(5);
    cCopyList.push_back(6);

    CList cNextList;
    cNextList = cCopyList;

    cNextList = cNextList + cSomeList;
    cNextList += cCopyList;

    cNextList += cNextList;

    cNextList[2] = 777;

    cNextList.ShowAllElements();

    return 0;
}
