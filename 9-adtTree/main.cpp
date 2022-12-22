#include "randomBinaryTree.h"

void test_calc_total()
{
    RandomBinaryTree<int> binaryTree;
    int sum = 0;
    for (int i = 1; i < 10; ++i)
    {
        binaryTree.insert(i*2);
        sum += i*2;
    }
    assert(binaryTree.calc_total() == sum);
    std::cout << "Test Sum passed!" << std::endl;
}
void test_IterCalcTotal()
{
    RandomBinaryTree<int> binaryTree;
    int sum = 0;
    for (int i = 1; i < 10; ++i)
    {
        binaryTree.insert(i*2);
        sum += i*2;
    }
    assert(binaryTree.iter_calc_total() == sum);
    std::cout << "Test iter Sum passed!" << std::endl;
}
int main()
{
    test_calc_total();
    test_IterCalcTotal();






    return 0;
}