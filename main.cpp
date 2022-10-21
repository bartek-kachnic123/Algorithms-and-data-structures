#include "sorts_bib.h"
#include <array>

int main()
{
    std::array<int, 5> arr = {2, 1, 4, 1, 2};

    insertionSort(arr.begin(), arr.end());
    for (auto element: arr)
    {
        std::cout << element << ' ';
    }
    

    return 0;
}