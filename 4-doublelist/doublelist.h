// doublelist.h

#ifndef DOUBLELIST_H
#define DOUBLELIST_H

#include <iostream>     // deklaracje strumieni cout, cin, cerr
#include <cassert>    // assert()

template <typename T>
struct DoubleNode {
// the default access mode and default inheritance mode are public
    T value;
    DoubleNode *next, *prev;
    // konstruktor domyslny (niepotrzebny)
    DoubleNode() : value(T()), next(nullptr), prev(nullptr) {}
    DoubleNode(const T& item, DoubleNode *nptr=nullptr, DoubleNode *pptr=nullptr)
        : value(item), next(nptr), prev(pptr) {} // konstruktor
    ~DoubleNode() {} // destruktor
};


template <typename T>
class DoubleList {
    DoubleNode<T> *head, *tail;
public:
    DoubleList() : head(nullptr), tail(nullptr) {}
    ~DoubleList(); // tu trzeba wyczyscic wezly

    DoubleList(const DoubleList& other) // copy constructor
    {
        head = tail = nullptr;
        DoubleNode<T> *node = other.head;
        while (node)
        {
            push_back(node->value);
            node = node->next;
        }
    }
    // usage:   DoubleList<int> list2(list1);

    DoubleList(DoubleList&& other); // move constructor NIEOBOWIAZKOWE
    // usage:   DoubleList<int> list2(std::move(list1));

    DoubleList& operator=(const DoubleList& other) // copy assignment operator, return *this
    {
        if (this == &other) return *this;
        
        clear();
        head = tail = nullptr;

        DoubleNode<T> *node = other.head;
        while(node)
        {
            push_back(node->value);
            node = node->next;
        }
    }
    // usage:   list2 = list1;

    DoubleList& operator=(DoubleList&& other); // move assignment operator, return *this
    // usage:   list2 = std::move(list1); NIEOBOWIAZKOWE

    bool empty() const { return head == nullptr; }
    int size() const; // O(n) bo trzeba policzyc
    void push_front(const T& item); // O(1)
    void push_front(T&& item); // O(1) NIEOBOWIAZKOWE
    void push_back(const T& item); // O(1)
    void push_back(T&& item); // O(1) NIEOBOWIAZKOWE
    T& front() const { return head->value; } // zwraca poczatek, nie usuwa
    T& back() const { return tail->value; } // zwraca koniec, nie usuwa
    void pop_front(); // usuwa poczatek O(1)
    void pop_back(); // usuwa koniec O(1)
    void clear(); // czyszczenie listy z elementow O(n)
    void display(); // O(n)
    void display_reversed(); // O(n)

    // Operacje z indeksami. NIEOBOWIAZKOWE
    T& operator[](int pos); // podstawienie L[pos]=item, odczyt L[pos]
    const T& operator[](int pos) const; // dostep do obiektu const
    void erase(int pos);
    int index(const T& item); // jaki index na liscie (-1 gdy nie ma) O(n)
    void insert(int pos, const T& item); // inserts item before pos,
    void insert(int pos, T&& item); // inserts item before pos,
    // Jezeli pos=0, to wstawiamy na poczatek.
    // Jezeli pos=size(), to wstawiamy na koniec.
};
template <typename T>
DoubleList<T>::~DoubleList()
{
    while(!empty()) pop_front();
}
template <typename T>
int DoubleList<T>::size() const
{
    int size = 0;
    DoubleNode<T> *node = head;
    while(node)
    {
        node = node->next;
        ++size;
    }
    return size;
}
template <typename T>
void DoubleList<T>::push_front(const T& item) {
    if (!empty()) {
        head = new DoubleNode<T>(item, head);
        head->next->prev = head;
    } else {
        head = tail = new DoubleNode<T>(item);
    }
}

template <typename T>
void DoubleList<T>::push_front(T&& item) {
    if (!empty()) {
        head = new DoubleNode<T>(std::move(item), head);
        head->next->prev = head;
    } else {
        head = tail = new DoubleNode<T>(std::move(item));
    }
}

template <typename T>
void DoubleList<T>::push_back(const T& item) {
    if (!empty()) {
        tail->next = new DoubleNode<T>(item, nullptr,  tail);
        tail = tail->next;
    
    } else {
        head = tail = new DoubleNode<T>(item);
    }
}
template <typename T>
void DoubleList<T>::pop_front()
{
    assert(!empty());
    DoubleNode<T> *node = head;

    if (head == tail)
    {
        head = tail = nullptr;
    }
    else {
        head = head->next;
        head->prev = nullptr;
    }

    delete node;
}

template <typename T>
void DoubleList<T>::pop_back()
{
    assert(!empty());
    DoubleNode<T> *node = tail;

    if (head == tail)
    {
        head = tail = nullptr;
    }
    else {
        tail = tail->prev;
        tail->next = nullptr;
    }

    delete node;

}
template <typename T>
void DoubleList<T>::clear()
{
    while(!empty()) pop_front();
}
template <typename T>
void DoubleList<T>::display()
{
    DoubleNode<T> *node = head;
    while(node)
    {
        std::cout << node->value << " ";
        node = node->next;
    }
    std::cout << std::endl;
}

template <typename T>
void DoubleList<T>::display_reversed()
{
    DoubleNode<T> *node = tail;
    while(node)
    {
        std::cout << node->value << " ";
        node = node->prev;
    }
    std::cout << std::endl;
}

#endif

// EOF