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




int main() {
    test_Insert();

    





    return 0;
}