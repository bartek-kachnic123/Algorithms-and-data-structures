#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include "graph.hpp"



struct TypeChest {
    enum {NO_VISITED=0, VISITED, TO_DESTROY};
};
template <typename T>
int dfs2(Graph<T> &graph)
{
    std::vector<int> chest_list(graph._numVert, TypeChest::NO_VISITED);
    std::vector<int> chest_destroy(graph._numVert, TypeChest::NO_VISITED);


    for (int v = 0; v < graph._numVert; v++)
    {
        if (chest_list[v] == TypeChest::NO_VISITED)
        {
            chest_destroy[v] = TypeChest::TO_DESTROY;
            chest_list[v] = TypeChest::VISITED;
            dfs_visit2(graph, v, chest_list, chest_destroy, v);
        }
        
    }
    for (auto &x : chest_destroy) {
        std::cout << x << " | ";
    }
    std::cout << std::endl;
    
    int chest_number = std::count(chest_destroy.begin(), chest_destroy.end(), TypeChest::TO_DESTROY);
    std::cout << chest_number << std::endl;
    return chest_number;
}

template<typename T>
void dfs_visit2(Graph<T> &graph, const int &v, std::vector<int> &chest_list, std::vector<int> &chest_destroy, const int &v_main)
{
    
    for (const int &x : graph.vertexTab[v].adjancency_list)
    {
        if (chest_list[x] == TypeChest::NO_VISITED) {
            chest_list[x] = TypeChest::VISITED;
            dfs_visit2(graph, x, chest_list, chest_destroy, v_main);
        }
        else if (x == v_main) {
            continue;
        }
         
        else if (chest_destroy[x] == TypeChest::TO_DESTROY) {
            chest_destroy[x] = TypeChest::VISITED;
        }
        
        
       

    }
    
}

int solve(int *data, int n) {
    Graph<int> graph(n);

    for (int i = 0; i < n; i++)
    {
        graph.addEdge(data[i]-1, i);
    }

    for (int i = 0; i < n ;++i) {
        std::cout << i+1 << ": ";
        for (auto &elem : graph.outConnections(i))
            std::cout << elem+1 << " ";
        std::cout << std::endl;
    }

    return dfs2(graph);
}

void test(std::string filename) {
    std::ifstream   file (filename);
    int num;
    int *data = nullptr;
    int test_counter = 1;
    int chests_to_destroy = 0;
    std::string line;
    if (file.is_open()) {
        while(std::getline(file, line)) {
            // Number of chest
            std::stringstream s(line);
            s >> num;
            std::getline(file, line);
            // Chests
            std::stringstream s2(line);
            data = new int[num];
            for (int i = 0; i < num; ++i)
                s2 >> data[i];
            // Chest to destroy:
            std::getline(file, line);
            std::stringstream s3(line);
            s3 >> chests_to_destroy;
    
            std::cout << "Test nr " << test_counter << std::endl;
            assert(chests_to_destroy == solve(data, num));
            std::cout << "Test nr " << test_counter++ << " passed!" << std::endl;


            delete[] data;
            data = nullptr;
        }
    }
    file.close();
}
int main() {
    test("data.txt");





    return 0;
}