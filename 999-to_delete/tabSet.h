#if !defined(SORTEDSET_H)
#define SORTEDSET_H
#define DEFAULT_CAPACITY 128
#define CAPACITY_INCREASE 2
#define CAPACITY_DECREASE 0.25

#include <iostream>
#include <cassert>


template<typename T>
class SortedSet
{
private:
    /* data */
    T* elements;
    unsigned int curr_size;
    unsigned int capacity;

public:
    SortedSet();
    SortedSet(const SortedSet &other);
    ~SortedSet();

    SortedSet& operator=(const SortedSet &other);

    inline bool isFull();
    inline bool isEmpty();
    unsigned int size();
    int isMember(T element);
    void insert(T element);
    void remove();
    SortedSet& pop();
    SortedSet interSection(const SortedSet &other); 
    SortedSet sum(const SortedSet &other);
    SortedSet difference(const SortedSet &other);
    


};

template<typename T>
SortedSet<T>::SortedSet()
    : curr_size(0),
    capacity(DEFAULT_CAPACITY)
{
    elements = new T[capacity];
    assert(elements != nullptr);
}

template<typename T>
SortedSet<T>::SortedSet(const SortedSet &other)
    : curr_size(other.curr_size),
    capacity(other.capacity)
{
    elements = new T[capacity];
    assert(elements != nullptr);
    std::copy(other.elements, other.elements+curr_size, elements);
}

template<typename T>
SortedSet<T>::~SortedSet()
{
    if (elements != nullptr)
        delete []elements;
}

template<typename T>
SortedSet<T>& SortedSet<T>::operator=(const SortedSet &other) {
    if (this == &other)
        return *this;
    
    delete []elements;

    curr_size = other.curr_size;
    capacity = other.capacity;

    elements = new T[capacity];
    assert(elements != nullptr);

    std::copy(other.elements, other.elements+curr_size, elements);
}

template<typename T>
inline bool SortedSet<T>::isFull() {
    return (curr_size == capacity) ? true : false;
}

template<typename T>
inline bool SortedSet<T>::isEmpty() {
    return (curr_size == 0 ) ? true : false;
}

template<typename T>
unsigned int SortedSet<T>::size() {
    return curr_size;
}

template<typename T>
int SortedSet<T>::isMember(T element) {
    int left = 0;
    int right = size() - 1;
    int mid;
    while(left < right) {
        mid = (left + right) / 2;

        if (element[mid] == element)
            return mid;
        else if (element[mid] > element)
            right = mid - 1;
        else
            left = mid + 1;
    }
    return -1;
}

template<typename T>
void SortedSet<T>::insert(T element) {
    if (isMember(element) == -1) {
        if (isFull()) {
            int new_capacity = capacity * CAPACITY_DECREASE;

            T* tmp_elements = new T[new_capacity];
            assert(tmp_elements != nullptr);

            
        }
    }
}



#endif // SORTEDSET_H
