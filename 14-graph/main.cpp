#include "graph.hpp"
#include <cassert>

void test_hasEdge() {
    Graph<int> graph_1(10);
    assert(graph_1.hasEdge(1, 9) == false);
    assert(graph_1.hasEdge(9, 9) == false);
    assert(graph_1.hasEdge(10, 12) == false);
    assert(graph_1.hasEdge(-1, -2) == false);
    std::cout << "Test hasEdge passed!" << std::endl;

    graph_1.addEdge(1, 9);
    assert(graph_1.hasEdge(1, 9) == true);


}
void test_addEdge() {
    Graph<int> graph_1(10);

    graph_1.addEdge(1, 9);
    assert(graph_1.hasEdge(1, 9) == true);

    graph_1.addEdge(1, 1);
    assert(graph_1.hasEdge(1, 1) == false);
    std::cout << "Test addEdge passed!" << std::endl;

}
int main() {
    test_hasEdge();
    test_addEdge();
   
    return 0;
}