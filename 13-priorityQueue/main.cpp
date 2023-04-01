#include <cstdlib>
#include "priorityQueue.hpp"

void test_Insert() {
    PriorityQueue<int> priority_queue;
    srand(time(0));
    for (int i = 1; i < 12; i++) {
        priority_queue.insert(i, rand() % 10);
    }
    std::cout << "Insert test: " << std::endl;
    std::cout << priority_queue << std::endl;

}

void test_Max() {
    PriorityQueue<int> priority_queue;
    srand(time(0));
    for (int i = 1; i < 12; i++) {
        priority_queue.insert(i, rand() % 10);
    }
    std::cout << "Max test: " << std::endl;
    std::cout << "Q: " << priority_queue << std::endl;
    std::cout << "Max : " << priority_queue.max() << std::endl;
}
int main() {
    test_Insert();
    test_Max();
}