#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <chrono>
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
    //for (auto &x : chest_destroy) {
    //    std::cout << x << " | ";
    //}
    //std::cout << std::endl;
    
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

    //for (int i = 0; i < n ;++i) {
     //   std::cout << i+1 << ": ";
     //   for (auto &elem : graph.outConnections(i))
     //       std::cout << elem+1 << " ";
     //   std::cout << std::endl;
    //}

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

            std::cout << "----------------------" << std::endl;
            std::cout << "Test nr " << test_counter << std::endl;
            assert(chests_to_destroy == solve(data, num));
            std::cout << "Test nr " << test_counter++ << " passed!" << std::endl;
            std::cout << "----------------------" << std::endl;



            delete[] data;
            data = nullptr;
        }
    }
    file.close();
}
void test_fromFile(std::string filename, int expected_result) {
        std::ifstream   file (filename);
        std::string line;
        int num = 0;
        int *data = nullptr;

        std::chrono::_V2::steady_clock::time_point begin, end;


        if (std::getline(file, line)) {
            std::stringstream s(line);
            s >> num;
        }

        data = new int[num];
        
        for (int i = 0; i < num; i++) {
            if (std::getline(file, line)) {
                std::stringstream ss(line);
                ss >> data[i];
            }
        }
        std::cout << "----------------------" << std::endl;
        std::cout << "Test file " << filename << std::endl;

        begin = std::chrono::steady_clock::now();
        assert(expected_result == solve(data, num));
        end = std::chrono::steady_clock::now();

        std::cout << "Test passed! Elapsed time: " << 
        std::chrono::duration_cast<std::chrono::milliseconds>(end-begin).count() << " ms"
        << std::endl;
        std::cout << "----------------------" << std::endl;


        delete [] data;
        data = nullptr;

        file.close();
}

void extra_tests() {
    test_fromFile("1_23.txt", 23);
    test_fromFile("2_3.txt", 3);
    test_fromFile("3_8.txt", 8);
    test_fromFile("4_1000.txt", 1000);
    test_fromFile("5_500.txt", 500);
    test_fromFile("6_2.txt", 2);
    test_fromFile("7_31.txt", 31);
    test_fromFile("8_5041.txt", 5041);

}
int main() {
    test("data.txt");
    extra_tests();
    test("test1.txt");


    return 0;
}