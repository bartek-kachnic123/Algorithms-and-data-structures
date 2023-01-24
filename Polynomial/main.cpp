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

    std::cout << "Test passed!" << std::endl;

    std::map<unsigned int,double> mapData = {{1, 9.22}, {3, 3.6}, {4, 7}};
    Poly<double> polynomial_4(mapData);
    std::cout << polynomial_4 << std::endl;
}

void test_copyConstructor() {
    std::cout << "Test copy constructor: " << std::endl;
    int arr[] = {1, 2, 0,  3, 0};
    Poly<int> polynomial_1(arr, 5);
    Poly<int> polynomial_copy(polynomial_1);
    std::cout << "1: " << polynomial_1 << std::endl;
    std::cout << "2: " << polynomial_copy << std::endl;
    
}
void test_moveConstructor() {
    std::cout << "Test move constructor " << std::endl;

    double arr[] = {1, 2, 3, 0, 4};
    Poly<double> polynomial_1(arr, 4);
    Poly<double> polynomial_2(std::move(polynomial_1));

    for (int i=0; i < 4; ++i) {
        assert(arr[i] == polynomial_2[i]);
    }
    std::cout << "Test 1 passed!" << std::endl;

}

void test_copyAssigment() {
    std::cout << "Test copy assigment: " << std::endl;
    int arr[] = {1, 2, 0,  3, 0};
    Poly<int> polynomial_1(arr, 5);
    Poly<int> polynomial_copy = polynomial_1;
    std::cout << "1: " << polynomial_1 << std::endl;
    std::cout << "2: " << polynomial_copy << std::endl;
}

void test_moveAssigment() {
    std::cout << "Test move assigment: " << std::endl;
    double arr[] = {1.5, 1.2, 0.0, 1.2};
    Poly<double> polynomial_1(arr, 4);
    arr[0] = 1.24;
    Poly<double> polynomial_2(arr, 4);

    polynomial_2 = std::move(polynomial_1);
    arr[0] = 1.5;
    for (int i = 0; i < 4; ++i) {
        assert(arr[i] == polynomial_2[i]);
    }
    std::cout << "Test 1 passed!" << std::endl;


}

void test_equalOperator() {
    std::cout << "Test equal operator: " << std::endl;
    double arr1[] = {1, 2, 3};
    double arr2[] = {1, 2, 3};
    Poly<double> poly1(arr1, 3);
    Poly<double> poly2(arr2, 3);
    assert(poly1 == poly2);

    double arr3[] = {1, 2, 3, 1};
    Poly<double> poly3(arr3, 4);
    assert(poly3 != poly1);

    double arr4[] = {1, 10, 2};
    Poly<double> poly4(arr4, 3);
    assert(poly4 != poly1);

    std::cout << "Test passed!" << std::endl;
}

void test_calcValue() {
    std::cout << "Test Horner: " << std::endl;
    int arr[] = {1, 2, 0, 2};
    Poly<int> polynomial_1(arr, 4);
    int result = polynomial_1.calcValue(2);
    assert(result == 18);
    std::cout << "Test 1 passed!" << std::endl;

    double arr2[] = {1, 2, 3};
    Poly<double> polynomial_2(arr2, 3);
    result = polynomial_2.calcValue(2);
    assert(result == 11);
    std::cout << "Test 2 passed!" << std::endl;
}

void test_addOperator() {
    std::cout << "Test add operator: " << std::endl;
    double arr[] = {1, 2, 3};
    double arr2[] = {1.9, 1.2};

    Poly<double> polynomial_1(arr, 3);
    Poly<double> polynomial_2(arr2, 2);

    std::cout << "Added: " << polynomial_1 + polynomial_2 << std::endl;
}
void test_subtractOperator() {
    std::cout << "Test substract operator: " << std::endl;
    double arr[] = {1, 2, 3};
    double arr2[] = {1.9, 1.2, 1};

    Poly<double> polynomial_1(arr, 3);
    Poly<double> polynomial_2(arr2, 3);

    std::cout << "Subtracted 1: " << polynomial_1 - polynomial_2 << std::endl;

    Poly<double> polynomial_3 = polynomial_1;
    std::cout << "Subtracted 2: " << polynomial_3 - polynomial_1 << std::endl;

    double arr4[] = {1.9, 1.2, 4};
    Poly<double> polynomial_4(arr4, 3);
    std::cout << "Subtracted 3: " << polynomial_2 - polynomial_4 << std::endl;

    double arr5[] = {1, 9, 0.5, 0, 19};
    Poly<double> polynomial_5(arr5, 5);
    std::cout << "Subtracted 4: " << polynomial_5 - polynomial_1 << std::endl;

    std::cout << "Subtracted 5: " << polynomial_1 - polynomial_5 << std::endl;
}

void test_multiplyOperator() {
    std::cout << "Test multiply operator: " << std::endl;
    double arr[] = {1, -2, 3};
    double arr2[] = {1, -2, 3};

    Poly<double> polynomial_1(arr, 3);
    Poly<double> polynomial_2(arr2, 3);

    std::cout << "Multiply : " << polynomial_1 *  polynomial_2 << std::endl;
    std::cout << "Multiply: " << polynomial_1 * polynomial_1 * polynomial_1 << std::endl;
}
int main()
{
    test_constructors();
    test_copyConstructor();
    test_moveConstructor();
    test_copyAssigment();
    test_moveAssigment();
    test_equalOperator();
    test_calcValue();
    test_addOperator();
    test_subtractOperator();
    test_multiplyOperator();





    return 0;
}