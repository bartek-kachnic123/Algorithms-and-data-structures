#include "myStack.h"
#include <cassert>
#include <sstream>
#include <stdexcept>
int calculate(int a, int b, std::string op)
{
    if (op == "+") return a + b;
    else if (op == "-") return a - b;
    else if (op == "*") return a * b;
    else if (op == "/") 
    {
        assert(b!=0);
        return a / b;
    }

    throw std::invalid_argument("Invalid operator");
}
int rpn(std::vector<std::string> input)
{
    int a, b;
    MyStack<std::string> S = MyStack<std::string>();

    for (auto & item : input)
    {
        if (item != "*" && item != "/" && item != "+" && item != "-")
        {
            S.push(item);
        }
        else {
            std::istringstream(S.top()) >> a;
            S.pop();

            std::istringstream(S.top()) >> b;
            S.pop();

            S.push(std::to_string(calculate(b, a, item)));

        }
    }
    int result;
    std::istringstream(S.top()) >> result;
    return result;
}


void test_rpn()
{
    // test 1
    std::vector<std::string> input { "-6", "2", "/" };
    assert(rpn(input) == -3); // result should be -3
    std::cout << "Test 1 passed!" << std::endl;

    // test 2
    std::vector<std::string> input2 { "12", "2", "3" ,"4","*", "10",  "5",  "/", "+",  "*" , "+"};
    assert(rpn(input2) == 40); // result should be 40
    std::cout << "Test 2 passed!" << std::endl;
}
int main()
{
    test_rpn();



    return 0;
}