#include "BinarySearchTree.h"


void test_Find_Max_and_Min() {
    BinarySearchTree<float> bst;
    
    for (int i=1; i < 10; ++i)
    {
        bst.insert(i*1.00);
    }
    float * max_value = bst.find_max();
    assert(*max_value == 9.00);
    std::cout << "Test max passed!" << std::endl;
    
    float *min_value = bst.find_min();
    assert(*min_value == 1.00);
    std::cout << "Test min passed!" << std::endl;
}
int main()
{
    test_Find_Max_and_Min();


    return 0;
}
