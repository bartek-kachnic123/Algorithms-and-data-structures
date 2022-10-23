#include "sorts_bib.hpp"
#include <array>
#include <cassert>

int main()
{
    std::array<int, 5> arr = {2, 1, 4, 1, 2};

    insertionSort(arr.begin(), arr.end());
    for (auto element : arr)
    {
        std::cout << element << ' ';
    }
    std::cout << std::endl;
    assert(std::is_sorted(arr.begin(), arr.end()));

    float arr2[5] = {1, -2.5, -3.1, 120, 5};

    heapSort(arr2, 0, 5);

    print_arr(std::begin(arr2), std::end(arr2));

    return 0;
}