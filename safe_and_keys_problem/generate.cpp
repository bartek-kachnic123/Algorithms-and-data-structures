#include <iostream>
#include <fstream>
#include <random>

void generate(std::string filename, int max_number, int expected_value) {
    // Create and open a text file
    std::ofstream MyFile(filename);
    int random_number = 0;

    srand(0);

    MyFile << max_number << '\n';

    for (int i = 0; i < max_number; i++) {
        random_number = rand() % max_number + 1;
        
        if (i != max_number - 1)
            MyFile << random_number << ' ';
        else
            MyFile << random_number << '\n';

    }
    MyFile << expected_value;



    MyFile.close();
}
int main() {
    generate("test1.txt", 100000, -1);

}