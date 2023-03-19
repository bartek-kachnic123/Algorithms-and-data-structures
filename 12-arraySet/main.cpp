#include "arraySet.h"
#include <cassert>



void test_Insert() {
    ArraySet<double> set;
    for (int i = 1; i < 10; ++i)
        set.insert(i);
    std::cout << "Insert Test: " << std::endl;
    std::cout << set << std::endl;
    assert(set.size() == 9);
    std::cout << "Inserting: 5 2.2 0.5 11" << std::endl;
    set.insert(5);
    set.insert(2.2);
    set.insert(0.5);
    set.insert(11);
    std::cout << set << std::endl;
    std::cout << std::endl;
}

void test_Remove() {
    ArraySet<double> set;
    for (int i = 1; i < 10; ++i)
        set.insert(i);
    set.insert(5);
    set.insert(2.2);
    
    std::cout << "Remove test: " << std::endl;
    std::cout << "Set : " << set << std::endl;
    std::cout << "Removing 1, 9, 5, 5 : " << std::endl;
    set.remove(1);
    set.remove(9);
    set.remove(5);
    set.remove(5);

    std::cout << set << std::endl;
    std::cout << "Removing: 2, 4, 8" << std::endl;
    set.remove(2);
    set.remove(4);
    set.remove(8);
    std::cout << set << std::endl;
    std::cout << std::endl;

}


void test_Pop() {
    ArraySet<int> set;
    set.insert(3);
    set.insert(6);
    set.insert(2);
    for (int i = 1; i < 5; ++i) {
        set.insert(i);
    }
    assert(set.pop() == 6);
    std::cout << "Pop test passed! " << std::endl;
    std::cout << set << std::endl;
    std::cout << std::endl;
}

void test_InterSection() {
    ArraySet<double> set1, set2;
    for (int i = 1; i < 5; ++i) {
        set1.insert(i);
    }
    for (int i= 2; i < 7; i+=2) {
        set2.insert(i);
    }
    std::cout << "Intersection Test : " << std::endl;
    std::cout << "Set 1: " << set1 << std::endl;
    std::cout << "Set 2: " << set2 << std::endl;
    std::cout <<"InterSection Set1 and Set2: " << set1.interSection(set2) << std::endl;

    ArraySet<double> empty_set;

    std::cout << "InterSection Set1 and empty set: " << set1.interSection(empty_set) << std::endl;
    std::cout << "Intersection empty set and Set1: " << empty_set.interSection(set2) << std::endl;
    std::cout << std::endl;
}

void test_unionSet() {
    ArraySet<double> set1, set2;
    for (int i = 1; i < 5; ++i) {
        set1.insert(i);
    }
    for (int i= 2; i < 10; i+=2) {
        set2.insert(i);
    }
    std::cout << "Union Test: " << std::endl;
    std::cout << "Set 1: " << set1 << std::endl;
    std::cout << "Set 2: " << set2 << std::endl;

    std::cout << "Union Set1 and Set2: " << set2.unionSet(set1) << std::endl;

    ArraySet<double> empty_set;

    std::cout << "Union Set1 and empty set" << set1.unionSet(empty_set) << std::endl;
    std::cout << std::endl;
}

void test_Difference() {
    ArraySet<double> set1, set2;
    for (int i = 5; i < 10; ++i) {
        set1.insert(i);
    }
    for (int i= 2; i < 17; i+=2) {
        set2.insert(i);
    }
    std::cout << "Difference Test : " << std::endl;
    std::cout << "Set 1: " << set1 << std::endl;
    std::cout << "Set 2: " << set2 << std::endl;

    std::cout << "Difference Set1 and Set2: " << set1.difference(set2) << std::endl;

    ArraySet<double> empty_set;
    std::cout << "Difference Set1 and empty_set: " << set1.difference(empty_set) << std::endl;
    std::cout << "Difference empty_set and Set1: " << empty_set.difference(set1) << std::endl;

    std::cout << std::endl;
}

int main() {
    test_Insert();
    test_Remove();
    test_Pop();
    test_InterSection();
    test_unionSet();
    test_Difference();

    





    return 0;
}