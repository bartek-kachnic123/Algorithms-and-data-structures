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
int main() {
    PriorityQueue<int> priority_queue;
    test_Insert();
}