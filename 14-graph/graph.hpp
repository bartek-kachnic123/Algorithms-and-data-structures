#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <stdexcept>
#include <set>
#include <algorithm>

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
    Graph(const Graph& other);
    ~Graph();

    Graph& operator=(const Graph& other);

    void addEdge(int v1, int v2);
    void removeEdge(int v1, int v2);
    bool hasEdge(int v1, int v2);

    std::set<int> inConnections(int v);
    std::set<int> outConnections(int v);
    std::set<int> allConnections(int v);

private:
    inline bool hasVertex(int v);
    void allocate_memory();

};

template<typename T>
Graph<T>::Graph(int numVert)
    : _numVert(numVert)
{
    allocate_memory();
}

template<typename T>
Graph<T>::Graph(const Graph& other) 
    : _numVert(other._numVert)
{
    allocate_memory();
    std::copy(other.vertexTab, other.vertexTab+_numVert, vertexTab);
}

template<typename T>
Graph<T>& Graph<T>::operator=(const Graph<T> &other) {
    if (this == &other)
        return *this;
    
    delete []vertexTab;

    _numVert = other._numVert;

    allocate_memory();

    std::copy(other.vertexTab, other.vertexTab+_numVert, vertexTab);
    return *this;
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
        if (vertexTab[v1].adjancency_list.contains(v2))
            return true;
    }
    return false;
}
template<typename T>
std::set<int> Graph<T>::inConnections(int v) {
    if (hasVertex(v)) {
        std::set<int> in_connections;
        for (int i = 0; i < _numVert; i++) {
            if (v == i)
                continue;
            
            if (vertexTab[i].adjancency_list.contains(v))
                in_connections.insert(i);
        }
        return in_connections;
    }
    throw std::invalid_argument("vertex doesnt exist in graph");

}

template<typename T>
std::set<int> Graph<T>::outConnections(int v) {
    if (hasVertex(v))
        return vertexTab[v].adjancency_list;
    throw std::invalid_argument("vertex doesnt exist in graph");
}

template<typename T>
std::set<int> Graph<T>::allConnections(int v) {
    std::set<int> in = inConnections(v);
    std::set<int> out = outConnections(v);
    in.insert(out.begin(), out.end());
    return in;
}
template<typename T>
inline bool Graph<T>::hasVertex(int v) {
    return  ((-1 < v) < _numVert) ? true : false;
}

template<typename T> 
void Graph<T>::allocate_memory() {
    try
    {
        vertexTab = new GraphVertex<T>[_numVert];
    }
    catch(const std::bad_alloc& e)
    {
        std::cerr << e.what() << '\n';
        std::abort();
    }
}
#endif // GRAPH_H