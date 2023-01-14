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

void test_Horner() {
    std::cout << "Test Horner: " << std::endl;
    int arr[] = {1, 2, 3};
    Poly<int> polynomial_1(arr, 3);
    int result = polynomial_1.Horner(2);
    std::cout << result << std::endl;
}
int main()
{
    test_constructors();
    test_Horner();





    return 0;
}