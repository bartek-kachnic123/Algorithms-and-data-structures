#include "graph.hpp"
#include <cassert>

void test_hasEdge() {
    Graph<int> graph_1(10);
    assert(graph_1.hasEdge(1, 9) == false);
    assert(graph_1.hasEdge(9, 9) == false);
    assert(graph_1.hasEdge(10, 12) == false);
    assert(graph_1.hasEdge(-1, -2) == false);
    std::cout << "Test hasEdge passed!" << std::endl;

}
int main() {
    test_hasEdge();
   
    return 0;
}