#include <iostream>
#include "graph.hpp"



void solve(int *data, int n) {
    Graph<int> graph(n);

    for (int i = 1; i < n; i++)
    {
        graph.addEdge(data[i-1], i);
    }

    for (int i = 1; i < n ;++i) {
        std::cout << i << ": ";
        for (auto &elem : graph.outConnections(i))
            std::cout << elem << " ";
        std::cout << std::endl;
    }

    
}

int main() {
    int data[] = {2, 1, 2, 4};
    solve(data, 5);





    return 0;
}