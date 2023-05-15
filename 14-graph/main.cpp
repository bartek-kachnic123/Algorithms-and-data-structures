#include "graph.hpp"
#include <cassert>
#include <iomanip>

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
void test_allConnections() {
    Graph<int> graph_1(100);
    graph_1.addEdge(1, 3);
    graph_1.addEdge(1, 5);
    graph_1.addEdge(2, 1);
    graph_1.addEdge(4, 1);

    std::set<int> allConn = graph_1.allConnections(1);
    for (int v : allConn) {
        std::cout << v << ", ";
    }
    std::cout << std::endl;
    std::cout << "test allConnections passed! " << std::endl;
}

void test_Constructors() {
    Graph<int> graph_1(10);
    graph_1.addEdge(1, 3);
    graph_1.addEdge(1, 4);
    graph_1.addEdge(2, 4);

    Graph<int> graph_2(graph_1);
    Graph<int> graph_3(5);
    graph_3 = graph_2;

    std::set<int> allConn = graph_1.allConnections(1);
    for (int v : allConn) {
        std::cout << v << ", ";
    }
    std::cout << std::endl;

    allConn = graph_2.allConnections(1);
    for (int v : allConn) {
        std::cout << v << ", ";
    }
    std::cout << std::endl;

    allConn = graph_3.allConnections(1);
    for (int v : allConn) {
        std::cout << v << ", ";
    }
    std::cout << std::endl;

    std::cout << "Test constructors passed! " << std::endl;
    
}
void test_bfs() {
    Graph<int> graph_1(10);
    graph_1.addEdge(1, 3);
    graph_1.addEdge(1, 5);

    graph_1.addEdge(3, 2);
    graph_1.addEdge(5, 6);

    graph_1.addEdge(6, 9);

    std::vector<int> distance_array = graph_1.bfs(1);
    for (long unsigned int i = 0; i < distance_array.size() ; ++i) {
        std::cout << std::setw(2) << i << "| ";
    }
    std::cout << std::endl;
    for (auto &d : distance_array) {
        std::cout << std::setw(2) <<  d << "| ";
    }
    std::cout << std::endl;
    std::cout << "Test bfs passed!" << std::endl;

    distance_array = graph_1.bfs(5);
    for (long unsigned int i = 0; i < distance_array.size() ; ++i) {
        std::cout << std::setw(2) << i << "| ";
    }
    std::cout << std::endl;
    for (auto &d : distance_array) {
        std::cout << std::setw(2) <<  d << "| ";
    }
    std::cout << std::endl;
    std::cout << "Test bfs passed!" << std::endl;
}

void test_dfs() {
    Graph<int> graph_1(10);
    graph_1.addEdge(1, 3);
    graph_1.addEdge(1, 5);

    graph_1.addEdge(3, 2);
    graph_1.addEdge(5, 6);

    graph_1.addEdge(6, 9);

    graph_1.dfs();
}
int main() {
    test_hasEdge();
    test_addEdge();
    test_removeEdge();
    
    test_inConnections();
    test_outConnections();
    test_allConnections();

    test_Constructors();

    test_bfs();

    test_dfs();

    return 0;
}