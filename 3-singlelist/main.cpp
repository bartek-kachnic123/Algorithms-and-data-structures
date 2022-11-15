#include "singlelist.h"

void testCopy_constructor()
{
    SingleList<int> sList, sList2;
    for (int i = 1; i < 10; ++i)
    {
        sList.push_front(i);
    }
    std::cout << "Copy constructor test: " << std::endl;
    std::cout << "sList : ";
    sList.display();
    SingleList<int> emptyList(sList2);
    SingleList<int> sList3(sList);
    std::cout << "sList3 : ";
    sList3.display();
    std::cout << std::endl;
}

void testCopy_assigment_operator()
{
    SingleList<int> sList, sList2;
    for (int i = 1; i < 10; ++i)
    {
        sList.push_front(i);
    }
    sList2 = sList;
    std::cout << "Copy assigment operator test: " << std::endl;
    std::cout << "sList: ";
    sList.display();
    std::cout << "sList2: ";
    sList2.display();
    std::cout << std::endl;
}

void testReverse()
{
     SingleList<int> sList;
    for (int i = 1; i < 10; ++i)
    {
        sList.push_front(i);
    }
    std::cout << "Reverse test: " << std::endl;
    std::cout << "sList: ";
    sList.display();
    std::cout << std::endl;
    sList.reverse();
    std::cout << "After reverse: ";
    sList.display();
    std::cout << std::endl;

}

void testSize()
{
    SingleList<int> sList;
    std::cout << "Empty list size: " << sList.size() << std::endl;
    const int num_of_elements = 5;
    for (int i = 0; i < num_of_elements; ++i)
    {
        sList.push_back(i);
    }

    assert(sList.size() == num_of_elements);
    std::cout << "Size test passed" << std::endl;

    
}
int main()
{
    testCopy_assigment_operator();
    testCopy_constructor();
    testReverse();
    testSize();

    return 0;
}