#include "arrayList.h"

void testPush_Front() {
    ArrayList<int> arr1;
    const int x = arr1.max_size();


    // add more elements;
    for (int i = 1; i < x; ++i)
    {
        arr1.push_front(i);
    }
    
    arr1.push_front(x);
    // list should be full
    arr1.push_front(x);

    std::cout << "Front push elements:" << std::endl;
    std::cout << arr1 << std::endl;

}

void testCopy_constructor()
{
    ArrayList<float> x;
    float value;
    for (int i = 1; i < 5; ++i)
    {
        value = i * 0.25;
        x.push_front(value);
    }
    ArrayList<float> y(x);
    // arrays should be the same
    std::cout << "Test copy constructor: " << std::endl;
    std::cout << "x: " << x << std::endl;
    std::cout << "y: " << y << std::endl;
}

void testCopyAssigment() {
    ArrayList<int> arr1, arr2;
    const int x = arr1.max_size();
    const int y = arr2.max_size();



    // add more elements;
    for (int i = 1; i < x; ++i)
    {
        arr1.push_front(i);
    }

    for (int i = y; i > 0; --i)
    {
        arr2.push_front(i);
    }

    std::cout << "Before copy assigment: " << std::endl;
    std::cout << "arr1 : " << arr1 << std::endl;
    std::cout << "arr2 : " << arr2 << std::endl;
    arr1 = arr2;
    std::cout << "After copy assigment arr1: " << arr1 << std::endl;
}

void testPush_Back()
{
    ArrayList<int> list1;
    const int x = list1.max_size();

    for (int i=0; i < x; ++i)
    {
        list1.push_back(i);
    }
    std::cout << "Push Back elements: " << std::endl;
    std::cout << list1 << std::endl;

    std::cout << "One more than full: " << std::endl;
    list1.push_back(x);
    
}

void testFront_and_Back()
{
    ArrayList<int> list1;
    const int x = list1.max_size();

    for (int i=0; i < x; ++i)
    {
        list1.push_back(i);
    }
    std::cout << "Front and back test " << std::endl;
    std::cout << "Full list " << list1 << std::endl;
    try {

    
        std::cout << "First element: " << list1.front() << std::endl;
        std::cout << "Last element: " << list1.back() << std::endl;


        // empty list
        ArrayList<int> list2;
        std::cout << list2.front() << std::endl;
    }
    catch(std::length_error &e)
    {
        std::cout << e.what() << std::endl;
    }
}
void testPop_Front_and_Pop_Back()
{
    ArrayList<int> list1;
    const int x = list1.max_size();

    for (int i=0; i < x; ++i)
    {
        list1.push_back(i);
    }
    try {
        std::cout << "List before pop_front : " << list1 << std::endl;
        list1.pop_front();
        std::cout << "List after pop_front : " << list1 << std::endl;
        list1.pop_back();
        std::cout <<"List after pop_back : " << list1 << std::endl;
    }
    catch(std::length_error &e)
    {
        std::cout << e.what() << std::endl;
    }

}
void testClear() {
    ArrayList<int> list1;
    const int x = list1.max_size();

    for (int i=0; i < x; ++i)
    {
        list1.push_back(i);
    }

    list1.clear();
    assert(list1.empty());

}
void testReverse() {
    ArrayList<int> list1;
    const int x = list1.max_size();

    for (int i=0; i < x; ++i)
    {
        list1.push_back(i);
    }

    std::cout << "Before reverse: " << list1 << std::endl;
    list1.reverse();
    std::cout <<"After reverse: " << list1 << std::endl;

}
void testSort() {
    ArrayList<int> list1;
    const int x = list1.max_size();

    for (int i=0; i < x/2; ++i)
    {
        list1.push_back(i);
        list1.push_front(i);
    }
    
    std::cout <<"Before sorting: " << list1 << std::endl;
    list1.sort();
    std::cout <<"After sorting: " << list1 << std::endl;

}
void testMerge()
{
    ArrayList<int> list1, list2;
    const int x = list1.max_size();
    const int y = list2.max_size();

    for (int i=1; i < x / 2; ++i)
    {
        list1.push_back(i);
        list1.push_front(i);
        list2.push_back(i);
    }

    std::cout << "List1 before merge: " << list1 << std::endl;
    std::cout << "List2 : " <<  list2 << std::endl;
    list1.merge(list2);
    std::cout << "List1 after merge: " << list1 << std::endl;


}
void run_ArrayListTests()
{
    testPush_Front();
    std::cout << std::endl;
    testCopy_constructor();
    std::cout << std::endl;
    testCopyAssigment();
    std::cout << std::endl;
    testPush_Back();
    std::cout << std::endl;
    testFront_and_Back();
    std::cout << std::endl;
    testPop_Front_and_Pop_Back();

    testClear();
    std::cout << std::endl;
    testReverse();
    std::cout << std::endl;
    testSort();
    std::cout << std::endl;
    testMerge();
}

int main() {
    run_ArrayListTests();
    
    

    return 0;
}