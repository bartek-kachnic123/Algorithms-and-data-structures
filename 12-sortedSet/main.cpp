#include "sortedSet.h"



void test_Insert() {
    SortedSet<double> set;
    set.insert(10.4);
    set.insert(1.52);
    set.insert(1200);
    set.insert(1200);
    set.insert(10.4);
    set.insert(1220);
    set.insert(12);

    assert(set.size() == 5);
    std::cout << "Test 1 passed! " << std::endl;
    for (auto it = set.begin(); it != set.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void test_Remove() {
    SortedSet<double> set;
    set.insert(10.4);
    set.insert(1.52);
    set.insert(1200);
    set.insert(1200);

    set.remove(1200);
    set.remove(1.52);
    set.remove(10.4);
    assert(set.size() == 0);
    std::cout << "Test 1 passed! " << std::endl;
}


int main() {
    test_Insert();
    test_Remove();
    





    return 0;
}