#ifndef MY_PRIORITY_QUEUE
#define MY_PRIORITY_QUEUE

#include <algorithm> // make_heap, push_heap,
#include <iostream>
#include <vector>

template <typename T>
class MyPriorityQueue
{
    std::vector<T> lst; // działa domyślny konstruktor dla std::vector
public:
    MyPriorityQueue(int s = 10) { lst.reserve(s); } // default constructor
    ~MyPriorityQueue() { lst.clear(); }
    MyPriorityQueue(const MyPriorityQueue &other);            // copy constructor
    MyPriorityQueue(MyPriorityQueue &&other);                 // move constructor
    MyPriorityQueue &operator=(const MyPriorityQueue &other); // copy assignment operator, return *this
    MyPriorityQueue &operator=(MyPriorityQueue &&other);      // move assignment operator, return *this
    bool empty() const { return lst.empty(); }
    int size() const { return lst.size(); } // liczba elementów w kolejce
    void push(const T &item)
    { // dodanie do kolejki
        lst.push_back(item);
        std::push_heap(lst.begin(), lst.end());
    }
    void push(T &&item)
    { // dodanie do kolejki
        lst.push_back(std::move(item));
        std::push_heap(lst.begin(), lst.end());
    }
    T &top() { return lst.front(); } // zwraca element największy, nie usuwa
    void pop()
    { // usuwa element największy
        std::pop_heap(lst.begin(), lst.end());
        lst.pop_back();
    }
    void clear() { lst.clear(); } // czyszczenie listy z elementów
    void display();
};

template <typename T>
MyPriorityQueue<T>::MyPriorityQueue(const MyPriorityQueue &other) // copy constructor
{
    lst.reserve(other.lst.capacity());
    lst = other.lst;
}

template <typename T>
MyPriorityQueue<T>::MyPriorityQueue(MyPriorityQueue &&other) // move constructor
{
    lst.reserve(other.lst.capacity());
    lst = std::move(other.lst);
}

template <typename T>
MyPriorityQueue<T> &MyPriorityQueue<T>::operator=(const MyPriorityQueue &other) // copy assignment operator, return *this
{
    if (this == &other)
        return *this;

    if (lst.capacity() < other.lst.capacity())
        lst.reserve(other.lst.capacity());

    lst = other.lst;

    return *this;
}

template <typename T>
MyPriorityQueue<T> &MyPriorityQueue<T>::operator=(MyPriorityQueue &&other) // move assignment operator, return *this
{
    if (this == &other)
        return *this;

    if (lst.capacity() < other.lst.capacity)
        lst.reserve(other.lst.capacity());

    lst = std::move(other.lst);

    return *this;
}

template <typename T>
void MyPriorityQueue<T>::display()
{
    std::vector<T> lst_copy = lst;
    while(!lst_copy.empty())
    {
        std::pop_heap(lst_copy.begin(), lst_copy.end());

        std::cout << lst_copy.back() << " ";
        lst_copy.pop_back();
    }
    std::cout << std::endl;

}

#endif
// EOF