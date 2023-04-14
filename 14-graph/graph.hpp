#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <stdexcept>
#include <set>

template<typename T>
class GraphVertex {
    std::set<int> adjancency_list;
    T value;
};


template<typename T>
class Graph
{
private:
    /* data */
    GraphVertex<T> *vertexTab;
public:
    Graph(int numVert);
    ~Graph();

    void addEdge(int i, int j);
    void removeEdge(int i, int j);
    bool hasEdge(int i, int j);

    std::set<int> inConnection(int i);
    std::set<int> outConnection(int i);
    std::set<int> allConnections(int i);

};

template<typename T>
Graph<T>::Graph(int numVert)
{
    try {
        vertexTab = new GraphVertex<T>[numVert];
    }
    catch (std::bad_alloc &e) {
        std::cerr << e.what() << std::endl;
        std::abort();
    }
}

template<typename T>
Graph<T>::~Graph()
{
    delete [] vertexTab;
}







#endif // GRAPH_H