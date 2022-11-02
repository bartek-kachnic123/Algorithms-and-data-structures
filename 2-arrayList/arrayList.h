// arraylist.h

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <iostream>     // deklaracje strumieni cout, cin, cerr
#include <cassert>    // assert()
#include <stdexcept>   // length_error
#include <algorithm> // is_sorted

template <typename T>
class ArrayList {
    T* tab;
    int msize; // najwieksza mozliwa liczba elementow
    int last; // pierwsza wolna pozycja
public:
    ArrayList(int s=10) : msize(s), last(0) {
        assert( s > 0 );
        tab = new T[s];
        assert( tab != nullptr );
    } // default constructor
    ~ArrayList() { delete [] tab; }
    ArrayList(const ArrayList& other) // copy constructor
    {
        
        tab = new T[other.max_size()];
        last = other.size();
        msize = other.max_size();
        assert(tab != nullptr );
        std::copy(other.tab, other.tab+last, tab);
    }
    // usage:   ArrayList<int> list2(list1);
    ArrayList(ArrayList&& other); // move constructor NIEOBOWIAZKOWE
    // usage:   ArrayList<int> list2(std::move(list1));
    ArrayList& operator=(const ArrayList& other) // copy assignment operator, return *this
    {
        if (this == &other)
        {
            return *this;
        }
        delete [] tab;
        last = other.size();
        msize = other.max_size();
        tab = new T[msize];
        assert(tab != nullptr);
        std::copy(other.tab, other.tab+last, tab);
        

        return *this;
    }
    // usage:   list2 = list1; NIEOBOWIAZKOWE
    ArrayList& operator=(ArrayList&& other); // move assignment operator, return *this
    // usage:   list2 = std::move(list1);
    bool empty() const { return last == 0; } // checks if the container has no elements
    bool full() const { return last == msize; } // checks if the container is full
    int size() const { return last; } // liczba elementow na liscie
    int max_size() const { return msize; } // najwieksza mozliwa liczba elementow
    void push_front(const T& item) // dodanie na poczatek
    {
        if (this->empty()) {tab[last++] = item; }
        else if (this->full()) {std::cout << "List is full!" << std::endl;}
        else {
            std::copy_backward(tab, tab+this->size(), tab+this->size()+1);
            tab[0] = item;
            last++;
        }
    }
    void push_front(T&& item); // dodanie na poczatek NIEOBOWIAZKOWE
    void push_back(const T& item) // dodanie na koniec
    {
        if (!this->full()) {
            tab[last++] = item;
        }
        else {std::cout << "List is full!" << std::endl;}
        
    }
    void push_back(T&& item); // dodanie na koniec NIEOBOWIAZKOWE
    T& front() // zwraca poczatek, nie usuwa, error dla pustej listy
    {
        if (this->empty()) 
        {
            throw std::length_error("List is empty!");
        }
        else {return tab[0];}
    }
    T& back() // zwraca koniec, nie usuwa, error dla pustej listy
    {
        if (this->empty()) 
        {
            throw std::length_error("List is empty!");
        }
        else {return tab[last-1];}
    }

    void pop_front() // usuwa poczatek, error dla pustej listy
    {
        if (this->empty()) 
        {
            throw std::length_error("List is empty!");
        }
        else {
            std::copy_backward(tab+1, tab+this->size(), tab+this->size()-1);
            tab[last-1] = T();
            --last;
        }
    }
    void pop_back() // usuwa koniec, error dla pustej listy
    {
        if (this->empty()) 
        {
            throw std::length_error("List is empty!");
        }
        else {
            tab[last-1] = T();
            --last;
        }
    }
    void clear() // czyszczenie listy z elementow
    {
        while(--last != 0)
        {
            tab[last] = T();
        }
    }
    void display() // lepiej zdefiniowac operator<<
    {
        for (int i=0; i < last; ++i) { // odwolanie L.last
            std::cout << tab[i] << " ";   // odwolanie L.tab
        }
    }
    void reverse() // odwracanie kolejnosci
    {
        int j = last-1;
        for (int i = 0; i < j ; ++i)
        {
            std::swap(tab[i], tab[j]);
            --j;
        }
    }
    void sort() // sortowanie listy
    {
        heapSort(tab, 0, last-1);
    }
    
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

    void merge(ArrayList& other) //  merges two sorted lists into one
    {
        // if list is not sorted, sort it
        if (!std::is_sorted(tab, tab+last)) {this->sort();}
        if (!std::is_sorted(other.tab, other.tab+other.size())) {other.sort();}
        
        T* newTab = new T[this->msize+other.max_size()];
        assert( newTab != nullptr );

        int i = 0, j = 0, x = 0;
        while (i < last && j < other.size())
        {
            if (tab[i] < other.tab[j])
            {
                newTab[x++] = tab[i++];
            }
            else {
                newTab[x++] = other.tab[j++];
        
            }
        }

        while (i < last)
        {
            newTab[x++] = tab[i++];
        }
        while  (j < other.size())
        {
            newTab[x++] = tab[j++];
        }

        delete [] tab;
        tab = newTab;
        last = last + other.size();
        msize = msize + other.max_size();


    }
    // Operacje z indeksami. NIEOBOWIAZKOWE
    // https://en.cppreference.com/w/cpp/language/operators
    // Array subscript operator
    T& operator[](int pos); // podstawienie L[pos]=item
    const T& operator[](int pos) const; // odczyt L[pos]
    void erase(int pos); // usuniecie elementu na pozycji pos
    int index(const T& item); // jaki index na liscie (-1 gdy nie ma)
    void insert(int pos, const T& item); // inserts item before pos
    void insert(int pos, T&& item); // inserts item before pos
    // Jezeli pos=0, to wstawiamy na poczatek.
    // Jezeli pos=size(), to wstawiamy na koniec.
    friend std::ostream& operator<<(std::ostream& os, const ArrayList& L) {
        for (int i=0; i < L.last; ++i) { // odwolanie L.last
            os << L.tab[i] << " ";   // odwolanie L.tab
        }
        return os;
    } // usage:   std::cout << L << std::endl;
};

#endif

// EOF