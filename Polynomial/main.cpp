#include "Poly.h"

void test_constructors() {

    std::cout << "Constructors test!" << std::endl;
    // first 
    Poly<int> polynomial_1;
    std::cout << polynomial_1 << std::endl;


    // second
    double arr[] = {1, 2, -3, 4, -5};
    Poly<double> polynomial_2(arr, sizeof(arr)/sizeof(arr[0]));
    std::cout << polynomial_2 << std::endl;

    Poly<int> polynomial_3({}, 0);

    std::cout << "Test passed!" << std::endl;
}
int main()
{
    test_constructors();





    return 0;
}