#include "myPriorityQueue.h"
#include <cassert>

void test_CopyConstructor()
{
    MyPriorityQueue<int> priorityQueue;
    for (int i=1; i < 5; ++i)
    {
        priorityQueue.push(i);
        priorityQueue.push(i+4);
    }

    MyPriorityQueue<int> priorityQueue2(priorityQueue);

    std::cout << "Test Copy Constructor: " << std::endl;
    std::cout << "PrioriryQueue 1: ";
    priorityQueue.display();
    std::cout << "PriorityQueue 2: ";
    priorityQueue.display();
    std::cout << std::endl;

    std::cout << "Test Move Constructor: " << std::endl;
    MyPriorityQueue<int> priorityQueue3(std::move(priorityQueue));
    std::cout << "PriorityQueue 3: ";
    priorityQueue3.display();
    assert(priorityQueue.empty());
    std::cout << "Test passed!" << std::endl;
    std::cout << std::endl;

}

void test_CopyAssigmentOperator()
{
    MyPriorityQueue<int> priorityQueue, priorityQueue2;
    for (int i=1; i < 5; ++i)
    {
        priorityQueue.push(i);
        priorityQueue.push(i+4);
    }

    

    std::cout << "Test Copy Assigment Operator: " << std::endl;
    priorityQueue2 = priorityQueue;
    std::cout << "PrioriryQueue 1: ";
    priorityQueue.display();
    std::cout << "PriorityQueue 2: ";
    priorityQueue.display();
    std::cout << std::endl;

    std::cout << "Test Move Assigment Operator: " << std::endl;
    MyPriorityQueue<int> priorityQueue3 = std::move(priorityQueue);
    std::cout << "PriorityQueue 3: ";
    priorityQueue3.display();
    assert(priorityQueue.empty());
    std::cout << "Test passed!" << std::endl;
}
int main()
{
    test_CopyConstructor();
    test_CopyAssigmentOperator();







    return 0;
}