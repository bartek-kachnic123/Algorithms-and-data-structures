// myqueue.h
#if !defined(MYQUEUE_H)
#define MYQUEUE_H
#include <iostream>
#include <cassert>

template <typename T>
class MyQueue
{
    T *tab;
    int msize; // największa możliwa liczba elementów plus jeden
    int head;  // pierwszy do pobrania
    int tail;  // pierwsza wolna pozycja
public:
    MyQueue(int s = 10) : msize(s + 1), head(0), tail(0)
    {
        tab = new T[s + 1];
        assert(tab != nullptr);
    } // default constructor
    ~MyQueue() { delete[] tab; }
    MyQueue(const MyQueue &other);            // copy constructor
    MyQueue(MyQueue &&other);                 // move constructor
    MyQueue &operator=(const MyQueue &other); // copy assignment operator, return *this
    MyQueue &operator=(MyQueue &&other);      // move assignment operator, return *this
    bool empty() const { return head == tail; }
    bool full() const { return (head + msize - 1) % msize == tail; }
    int size() const { return (tail - head + msize) % msize; }
    int max_size() const { return msize - 1; }
    void push(const T &item);                             // dodanie na koniec
    void push(T &&item);                                  // dodanie na koniec
    T &front() { return tab[head]; }                      // zwraca początek
    T &back() { return tab[(tail + msize - 1) % msize]; } // zwraca koniec
    void pop();                                           // usuwa początek
    void clear();                                         // czyszczenie listy z elementów
    void display();
};

template <typename T>
MyQueue<T>::MyQueue(const MyQueue &other)
{
    head = tail = 0;
    msize = other.msize;
    tab = new T[msize];
    assert(tab != nullptr);

    for (int i = other.head; i != other.tail; i = (i + 1) % other.msize)
    {
        push(other.tab[i]);
    }
}

template <typename T>
MyQueue<T>::MyQueue(MyQueue &&other)
{
    head = tail = 0;
    tab = nullptr;
    msize = other.msize;
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(tab, other.tab);
}

template <typename T>
MyQueue<T> &MyQueue<T>::operator=(const MyQueue &other)
{
    if (this == &other)
        return *this;

    head = tail = 0;
    msize = other.msize;

    delete[] tab;
    tab = new T[msize];
    assert(tab != nullptr);

    for (int i = other.head; i != other.tail; i = (i + 1) % other.msize)
    {
        push(other.tab[i]);
    }

    return *this;
}

template <typename T>
MyQueue<T> &MyQueue<T>::operator=(MyQueue &&other)
{
    if (this == &other)
        return *this;

    head = tail = 0;
    tab == nullptr;
    msize = other.msize;

    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(tab, other.tab);

    return *this;
}
template <typename T>
void MyQueue<T>::push(const T &item)
{
    tab[tail] = item;
    tail = (tail + 1) % msize;
}

template <typename T>
void MyQueue<T>::push(T &&item)
{
    tab[tail] = std::move(item);
    tail = (tail + 1) % msize;
}

template <typename T>
void MyQueue<T>::pop()
{
    assert(!empty());
    tab[head] = T();
    head = (head + 1) % msize;
}

template <typename T>
void MyQueue<T>::clear()
{
    while (!empty())
        pop();
}
template <typename T>
void MyQueue<T>::display()
{
    for (int i = head; i != tail; i = (i + 1) % msize)
    {
        std::cout << tab[i] << " ";
    }
    std::cout << std::endl;
}

#endif // MYQUEUE_H