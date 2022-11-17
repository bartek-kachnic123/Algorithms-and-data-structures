#include "mydeque.h"

void testCopy_constructor()
{
    MyDeque<int> deque1;
    for (int i = 1; i < deque1.max_size(); ++i)
    {
        deque1.push_back(i);
    }
    deque1.pop_front();
    deque1.pop_front();
    
    std::cout << "Test copy constructor: " << std::endl;
    MyDeque<int> deque2(deque1);
    std::cout <<"Deque 1: ";
    deque1.display();
    std::cout << "Deque 2: ";
    deque2.display();
    std::cout << std::endl;
    
}

void testCopy_assigment_operator()
{
    MyDeque<int> deque1;
    for (int i = 1; i < deque1.max_size(); ++i)
    {
        deque1.push_back(i);
    }
    deque1.pop_front();
    deque1.pop_back();
    
    std::cout << "Test copy assigment operator: " << std::endl;
    MyDeque<int> deque2 = deque1;
    std::cout <<"Deque 1: ";
    deque1.display();
    std::cout << "Deque 2: ";
    deque2.display();
    
}

void testPop_front_and_back()
{
    MyDeque<int> deque1;
    int x = 5;
    deque1.push_back(x);
    deque1.pop_front();
    assert(deque1.size() == 0);

    for (int i=1; i < 4; ++i)
    {
        deque1.push_back(i);
    }

    deque1.pop_front();
    assert(deque1.size() == 2);
    std::cout << "test pop front passed!" << std::endl;

    deque1.pop_back();
    assert(deque1.size() == 1);
    deque1.pop_back();
    assert(deque1.size() == 0);
    std::cout << "test pop back passed!" << std::endl;
    
}

void testClear()
{
    MyDeque<int> deque1;
    for (int i = 1; i < deque1.max_size(); ++i)
    {
        deque1.push_back(i);
    }

    deque1.clear();
    assert(deque1.size() == 0);
    std::cout << "Test clear passed!" << std::endl;

}

int main()
{
    testCopy_constructor();
    testCopy_assigment_operator();
    testPop_front_and_back();
    testClear();
    return 0;
}