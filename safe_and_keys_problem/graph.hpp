#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <stdexcept>
#include <set>
#include <algorithm>
#include <queue>
#include <vector>




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

    std::vector<int> bfs(int v);

    void dfs();

    template<typename U>
    friend int dfs2(Graph<U> &graph);

    template<typename U>
    friend void dfs_visit2(Graph<U> &graph, const int &v, std::vector<int> &chest_list, std::vector<int> &end_processing, const int &v_main);

private:
    inline bool hasVertex(int v);
    void allocate_memory();

    void dfs_visit(const int &v, std::vector<int> &start_processing, std::vector<int> &end_processing, int &time);

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
std::vector<int> Graph<T>::bfs(int v)
{
    if (hasVertex(v)) {
        std::queue<int> qu;  
        std::vector<int> distance_array(_numVert, -1); //_numVert elements with value -1

        distance_array[v] = 0; // start 
        qu.push(v); 

        while (!qu.empty())
        {
            v = qu.front();      
            qu.pop();

            for (const int &x : vertexTab[v].adjancency_list) {
                if (distance_array[x] == -1)
                {
                    qu.push(x);
                    distance_array[x] = distance_array[v] + 1;
                }
            }
            
        }
        return distance_array;
    } 
    
    throw std::invalid_argument("vertex doesnt exist in graph");
}

template <typename T>
void Graph<T>::dfs()
{
    std::vector<int> start_processing(_numVert, -1);
    std::vector<int> end_processing(_numVert);

    int time_counter = 0;

    for (int v = 0; v < _numVert; v++)
    {
        if (start_processing[v] == -1)
        {
            dfs_visit(v, start_processing, end_processing, time_counter);
        }
        
    }
    
    for (int &i: start_processing)
        std::cout << i << ", ";
    std::cout << std::endl;

    for (int &i: end_processing)
        std::cout << i << ", ";
    std::cout << std::endl;
    
    
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
template <typename T>
void Graph<T>::dfs_visit(const int &v, std::vector<int> &start_processing, std::vector<int> &end_processing,  int &time)
{
    time++;
    start_processing[v] = time;
    for (const int &x : vertexTab[v].adjancency_list)
    {
        if (start_processing[x] == -1)
            dfs_visit(x, start_processing, end_processing, time);
    }
    time++;
    end_processing[v] = time;
    
}
#endif // GRAPH_H