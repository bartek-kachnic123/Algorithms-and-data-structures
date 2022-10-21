#if !defined(SORTS_BIB)
#define SORTS_BIB
#include <iostream>
#include <iterator>
#include <array>




template<typename Iterator>
void insertionSort(Iterator first, Iterator last)
{
    Iterator i, j, key;
    for (i = first + 1; i != last; i++)
    {
        key = i;
        j = i - 1;
 
        // Move elements of arr[0..i-1], 
        // that are greater than key, to one
        // position ahead of their
        // current position
        while (j != first && *j > *key)
        {
            *(j+1) = *j;
            j = j - 1;
        }
        *(j + 1) = *key;
    }
}


#endif // SORTS_BIB
