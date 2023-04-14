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

    void addEdge(int v1, int v2);
    void removeEdge(int i, int j);
    bool hasEdge(int v1, int v2);

    std::set<int> inConnections(int i);
    std::set<int> outConnections(int i);
    std::set<int> allConnections(int i);

private:
    inline bool hasVertex(int v);

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
void Graph<T>::addEdge(int v1, int v2) {
    if (v1 != v2 && hasVertex(v1) && hasVertex(v2)) 
        vertexTab[v1].adjancency_list.insert(v2);
}

template<typename T>
void Graph<T>::removeEdge(int v1, int v2) {
    if (v1 != v2 && hasVertex(v1) && hasVertex(v2)) 
        vertexTab[v1].adjancency_list.erase(v2);
}

template<typename T>
bool Graph<T>::hasEdge(int v1, int v2) {
    if (v1 != v2 && hasVertex(v1) && hasVertex(v2)) {
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
template<typename T>
std::set<int> Graph<T>::inConnections(int v) {

}

template<typename T>
std::set<int> Graph<T>::outConnections(int v) {
    if (hasVertex(v))
        return vertexTab[v].adjancency_list;
    throw std::invalid_argument("vertex doesnt exist in graph");
}
template<typename T>
inline bool Graph<T>::hasVertex(int v) {
    return  ((-1 < v) < _numVert) ? true : false;
}
#endif // GRAPH_H