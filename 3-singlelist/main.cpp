#include "singlelist.h"

void testCopy_constructor() {
    SingleList<int> sList;
    for (int i=1; i < 10; ++i)
    {
        sList.push_front(i);
    }

    SingleList<int> sList2(sList);
    std::cout << "sList 1: ";
    sList.display();
    std::cout << std::endl;

    std::cout << "sList 2: ";
    sList2.display();
    std::cout << std::endl;


}
int main()
{
    testCopy_constructor();












    return 0;
}