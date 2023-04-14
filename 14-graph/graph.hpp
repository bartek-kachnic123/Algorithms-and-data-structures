#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <stdexcept>
#include <set>

template<typename T>
struct GraphVertex {
    std::set<int> adjancency_list;
    T value;
};


template<typename T>
class Graph
{
private:
    /* data */
    int _numVert;
    GraphVertex<T> *vertexTab;
public:
    Graph(int numVert);
    ~Graph();

    void addEdge(int i, int j);
    void removeEdge(int i, int j);
    bool hasEdge(int v1, int v2);

    std::set<int> inConnection(int i);
    std::set<int> outConnection(int i);
    std::set<int> allConnections(int i);

};

template<typename T>
Graph<T>::Graph(int numVert)
    : _numVert(numVert)
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



template<typename T>
bool Graph<T>::hasEdge(int v1, int v2) {
    if (v1 != v2 && (-1 < v1) < _numVert && (-1  < v2 )< _numVert) {
        try
        {
            if (vertexTab[v1].adjancency_list.contains(v2))
                return true;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }
    return false;
}



#endif // GRAPH_H