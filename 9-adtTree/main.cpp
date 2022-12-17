#include "randomBinaryTree.h"

void test_Sum()
{
    RandomBinaryTree<int> binaryTree;
    int sum = 0;
    for (int i = 1; i < 10; ++i)
    {
        binaryTree.insert(i*2);
        sum += i*2;
    }
    assert(binaryTree.sum() == sum);
    std::cout << "Test Sum passed!" << std::endl;
}
void test_iterSum()
{
    RandomBinaryTree<int> binaryTree;
    int sum = 0;
    for (int i = 1; i < 10; ++i)
    {
        binaryTree.insert(i*2);
        sum += i*2;
    }
    assert(binaryTree.iter_sum() == sum);
    std::cout << "Test iter Sum passed!" << std::endl;
}
int main()
{
    test_Sum();
    test_iterSum();






    return 0;
}