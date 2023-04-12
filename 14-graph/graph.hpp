#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <forward_list>
#include <stdexcept>

template<typename T>
class GraphVertex {
    std::forward_list<GraphVertex<T>> list_neigbours;
    T value;
};


template<typename T>
class Graph
{
private:
    /* data */
    GraphVertex<T> **vertexTab;
public:
    Graph(int numVert);
    ~Graph();
};

template<typename T>
Graph<T>::Graph(int numVert)
{
    try {
        vertexTab = new GraphVertex<T>*[numVert];
    }
    catch (std::bad_alloc &e) {
        std::cerr << e.what() << std::endl;
        std::abort(1);
    }
}

template<typename T>
Graph<T>::~Graph()
{
}







#endif // GRAPH_H