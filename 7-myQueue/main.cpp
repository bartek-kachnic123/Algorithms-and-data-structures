#include "myQueue.h"

void testCopy_Constructor()
{
    MyQueue<double> queue1;
    for (int i = 0; i < queue1.max_size(); i++)
    {
        queue1.push(i * 0.8);
    }
    MyQueue<double> queue2(queue1);
    std::cout << "Test Copy Constructor : " << std::endl;
    std::cout << "Q1: ";
    queue1.display();
    std::cout << "Q2: ";
    queue2.display();
    std::cout << std::endl;

    MyQueue<double> queue3(std::move(queue1));
    std::cout << "Test Move Constructor: ";
    assert(queue1.empty());
    std::cout << "Q3: ";
    queue3.display();
    std::cout << "Test passed!" << std::endl;
    std::cout << std::endl;
}

void testCopy_Assigment()
{
    MyQueue<double> queue1, queue2;
    for (int i = 0; i < queue1.max_size(); i++)
    {
        queue1.push(i * 0.8);
    }

    queue2 = queue1;
    std::cout << "Test Copy Assigment : " << std::endl;
    std::cout << "Q1: ";
    queue1.display();
    std::cout << "Q2: ";
    queue2.display();
    std::cout << std::endl;

    MyQueue<double> queue3 = std::move(queue1);
    std::cout << "Test Move Assigment: ";
    assert(queue1.empty());
    std::cout << "Q3: ";
    queue3.display();
    std::cout << "Test passed!" << std::endl;
    std::cout << std::endl;
}

void testPop_and_clear()
{
    MyQueue<double> queue1, queue2;
    for (int i = 0; i < queue1.max_size(); i++)
    {
        queue1.push(i * 0.8);
    }
    std::cout << "Test pop and clear: " << std::endl;
    queue1.clear();
    assert(queue1.size() == 0);

    std::cout << "Test passed!" << std::endl;
}
int main()

{
    testCopy_Constructor();
    testCopy_Assigment();
    testPop_and_clear();

    return 0;
}