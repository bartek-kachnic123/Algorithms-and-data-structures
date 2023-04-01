#include <cstdlib>
#include "priorityQueue.hpp"

void test_Insert() {
    PriorityQueue<int> priority_queue;
    srand(time(0));
    for (int i = 1; i < 12; i++) {
        priority_queue.insert(i, rand() % 9 + 1);
    }
    std::cout << "Insert test: " << std::endl;
    std::cout << priority_queue << std::endl;

}

void test_Max() {
    PriorityQueue<int> priority_queue;
    srand(time(0));
    for (int i = 1; i < 12; i++) {
        priority_queue.insert(i, rand() % 9 + 1);
    }
    std::cout << "Max test: " << std::endl;
    std::cout << "Q: " << priority_queue << std::endl;
    std::cout << "Max : " << priority_queue.max() << std::endl;
}
void test_ExtractMax() {
    PriorityQueue<int> priority_queue;
    srand(time(0));
    for (int i = 1; i < 8; i++) {
        priority_queue.insert(i, rand() % 10);
    }

    std::cout <<"ExtractMax test: " << std::endl;
    std::cout <<"Q : " << priority_queue << std::endl;
    int size = priority_queue.size();
    for (int i = 0; i < size; i++) {
        std::cout << priority_queue.extractMax() << ", ";
    }
    std::cout << std::endl;


    
}
void test_Resize() {
    PriorityQueue<double> priority_queue;
    srand(time(0));
    for (int i = 1; i < 200; i++) {
        priority_queue.insert(i, rand() % 9 + 1);
    }
    
    int size = priority_queue.size();
    for (int i = 50; i < size; i++) {
        priority_queue.extractMax();
    }
}
int main() {
    test_Insert();
    test_Max();
    test_ExtractMax();
    test_Resize();
}