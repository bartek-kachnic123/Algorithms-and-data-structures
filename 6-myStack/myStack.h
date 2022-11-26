#ifndef MYSTACK_H
#define MYSTACK_H
#include <iostream>
#include <vector>
// Interfejs stosu na bazie kontenera std::vector.
template <typename T>
class MyStack {
    std::vector<T> lst;
public:
    MyStack(int s=10) { lst.reserve(s); } // default constructor
    ~MyStack() { lst.clear(); }
    MyStack(const MyStack& other); // copy constructor
    MyStack(MyStack&& other); // move constructor
    MyStack& operator=(const MyStack& other); // copy assignment operator, return *this
    MyStack& operator=(MyStack&& other); // move assignment operator, return *this
    bool empty() const { return lst.empty(); } // checks if the container has no elements
    bool full() const { return lst.size() == lst.capacity(); }
    int size() const { return lst.size(); }
    int max_size() const { return lst.capacity(); }
    void push(const T& item) { lst.push_back(item); }
    void push(T&& item) { lst.push_back(std::move(item)); }
    T& top() { return lst.back(); } // zwraca koniec, nie usuwa
    void pop() { lst.pop_back(); } // usuwa koniec
    void clear() { lst.clear(); }
    void display();
};

template <typename T>
MyStack<T>::MyStack(const MyStack& other)
{
    // zarezerwuj pamiec
    lst.reserve(other.max_size());

    for (T &elem : other.lst)
    {
        push(elem);
    }
}

template <typename T>
MyStack<T>::MyStack(MyStack&& other)
{
    // zarezerwuj pamiec
    lst.reserve(other.max_size());

    for (T &elem : other.lst)
    {
        push(std::move(elem));
    }
}

template <typename T>
MyStack<T> & MyStack<T>::operator=(const MyStack& other)
{
    if (this == &other) return *this;

    clear();
    if (lst.max_size() < other.max_size())
    {
        lst.reserve(other.max_size());
    }

    for (T &elem : other.lst)
    {
        push(elem);
    }
}

template <typename T>
MyStack<T> & MyStack<T>::operator=(MyStack&& other)
{
    if (this == &other) return *this;

    clear();
    if (lst.max_size() < other.max_size())
    {
        lst.reserve(other.max_size());
    }

    for (T &elem : other.lst)
    {
        push(std::move(elem));
    }
}


template <typename T>
void MyStack<T>::display()
{
    for (T &elem : lst)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}


#endif

// EOF