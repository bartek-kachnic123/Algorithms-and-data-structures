#if !defined(SORTS_BIB)
#define SORTS_BIB
#include <iostream>
#include <iterator>
#include <array>
#include <algorithm>

template <typename Iterator>
void print_arr(Iterator first, Iterator last)
{
    Iterator i;
    for (i = first; i != last; i++)
    {
        std::cout << *i << " ";
    }
    std::cout << std::endl;
}

template <typename Iterator>
void insertionSort(Iterator first, Iterator last)
{
    Iterator i, j, key;
    for (i = first; ++i < last;)
    {
        key = i;
        print_arr(first, last);
        j = i - 1;
        while (j >= first && *j > *key)
        {
            std::iter_swap(j, key);
            --j;
            --key;
        }
    }
}

template <typename T>
void heapify(T *arr, int N, int i)
{

    int largest = i;

    int l = 2 * i + 1;

    int r = 2 * i + 2;

    if (l < N && arr[l] > arr[largest])
        largest = l;

    if (r < N && arr[r] > arr[largest])
        largest = r;

    if (largest != i)
    {
        std::swap(arr[i], arr[largest]);

        heapify(arr, N, largest);
    }
}

template <typename T>
void heapSort(T *arr, int left, int right)
{

    // Build heap
    for (int i = (left + right) / 2 - 1; i >= left; i--)
        heapify(arr, right + 1, i);

    for (int i = right; i > left; i--)
    {
        std::swap(arr[left], arr[i]);
        heapify(arr, i, left);
    }
}

#endif // SORTS_BIB
