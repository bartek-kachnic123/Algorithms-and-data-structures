#include "arraySet.h"
#include <cassert>



void test_Insert() {
    ArraySet<double> set;
    for (int i = 1; i < 10; ++i)
        set.insert(i);
    std::cout << set << std::endl;
    assert(set.size() == 9);

    set.insert(5);
    set.insert(2.2);
    set.insert(0.5);
    set.insert(11);
    std::cout << set << std::endl;
    
}

void test_Remove() {
    ArraySet<double> set;
    for (int i = 1; i < 10; ++i)
        set.insert(i);
    set.insert(5);
    set.insert(2.2);
    
    set.remove(1);
    set.remove(9);
    set.remove(5);
    set.remove(5);

    std::cout << set << std::endl;
}


void test_Pop() {
    ArraySet<int> set;
    set.insert(3);
    set.insert(6);
    set.insert(2);

    assert(set.pop() == 6);
    std::cout << set << std::endl;
}

void test_InterSection() {
    ArraySet<double> set1, set2;
    for (int i = 1; i < 5; ++i) {
        set1.insert(i);
    }
    for (int i= 2; i < 5; i+=2) {
        set2.insert(i);
    }

    std::cout << set1.interSection(set2) << std::endl;

    ArraySet<double> empty_set;

    std::cout << set1.interSection(empty_set) << std::endl;
    std::cout << empty_set.interSection(set2) << std::endl;

}

int main() {
    test_Insert();
    test_Remove();
    test_Pop();
    test_InterSection();

    





    return 0;
}