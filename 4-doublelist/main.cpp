#include "doublelist.h"

void testCopy_constructor()
{
    DoubleList<int> dList, emptyList;
    for (int i=1; i<10; ++i)
    {
        dList.push_back(i);
    }
    DoubleList<int> dList2(emptyList);
    DoubleList<int> dList3(dList);

    std::cout << "Test copy constructor: " << std::endl;
    assert(dList2.empty());
    std::cout << "Empty list test passed" << std::endl;
    std::cout << "dList: ";
    dList.display();
    std::cout << "dList3: ";
    dList3.display();
    std::cout << std::endl;

}
void testCopy_assigment_operator()
{
       DoubleList<int> dList, emptyList;
    for (int i=1; i<10; ++i)
    {
        dList.push_back(i);
    }
    DoubleList<int> dList2 = emptyList;
    DoubleList<int> dList3 = dList;

    std::cout << "Test copy assigment operator: " << std::endl;
    assert(dList2.empty());
    std::cout << "Empty list test passed" << std::endl;
    std::cout << "dList: ";
    dList.display();
    std::cout << "dList3: ";
    dList3.display();
    std::cout << std::endl;
}
void testDisplay()
{
    DoubleList<int> dList;
    for (int i=1; i<10; ++i)
    {
        dList.push_back(i);
    }
    std::cout << "Test display: ";
    dList.display();
    std::cout << std::endl;

    std::cout << "Test display-reversed: ";
    dList.display_reversed();
    std::cout << std::endl;
}
void testPush_back()
{
    DoubleList<int> dList;
    for (int i=1; i<10; ++i)
    {
        dList.push_back(i);
    }
    std::cout << "Test push_Back: ";
    dList.display();
}
void testPop_front_and_back()
{
    
    DoubleList<int> dList;
    for (int i=1; i<10; ++i)
    {
        dList.push_back(i);
    }
    std::cout << "Test pop front and back: " << std::endl;
    std::cout << "dList: ";
    dList.display();
    

    dList.pop_front();
    std::cout << "dList after pop_front: ";
    dList.display();
    

    dList.pop_back();
    std::cout<< "dList after pop_back: ";
    dList.display();
    std::cout << std::endl;
}

void testSize()
{
    DoubleList<int> dList;
    std::cout << "Empty list size: " << dList.size() << std::endl;
    const int num_of_elements = 5;
    for (int i = 0; i < num_of_elements; ++i)
    {
        dList.push_back(i);
    }

    assert(dList.size() == num_of_elements);
    std::cout << "Size test passed" << std::endl;

    
}
void testClear()
{
    DoubleList<int> dList;
    for (int i=1; i<10; ++i)
    {
        dList.push_back(i);
    }
    dList.clear();
    assert(dList.empty());
    std::cout << "Test clear passed" << std::endl;
}
int main()
{
    testCopy_constructor();
    testCopy_assigment_operator();
    testDisplay();
    testPush_back();
    testPop_front_and_back();
    testSize();
    testClear();


    return 0;
}