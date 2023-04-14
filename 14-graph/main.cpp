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
void test_removeEdge() {
    Graph<double> graph_1(100);
    graph_1.addEdge(1, 99);
    assert(graph_1.hasEdge(1, 99) == true);

    graph_1.removeEdge(1, 99);
    assert(graph_1.hasEdge(1, 99) == false);

    std::cout << "Test removeEdge passed!" << std::endl;

}
void test_outConnections() {
    Graph<int> graph_1(120);
    for (int i = 2; i < 120; i+= 5) 
        graph_1.addEdge(1, i);
    std::set<int> outConn = graph_1.outConnections(1);
    for (int v : outConn) {
        std::cout << v << ", ";
    }
    std::cout << std::endl;
    std::cout << "test outConnections passed! " << std::endl;
    
}

void test_inConnections() {
    Graph<int> graph_1(100);
    for (int i = 1; i < 100; i+=6)
    {
        graph_1.addEdge(i, 0);
    }
    std::set<int> inConn = graph_1.inConnections(0);
    for (int v : inConn) {
        std::cout << v << ", ";
    }
    std::cout << std::endl;
    std::cout << "test inConnections passed! " << std::endl;
}
int main() {
    test_hasEdge();
    test_addEdge();
    test_removeEdge();
    
    test_inConnections();
    test_outConnections();
    return 0;
}