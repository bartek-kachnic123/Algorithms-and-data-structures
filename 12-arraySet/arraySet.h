#if !defined(SORTEDSET_H)
#define SORTEDSET_H
#define DEFAULT_CAPACITY 128
#define CAPACITY_INCREASE 2
#define CAPACITY_DECREASE 0.25

#include <iostream>

template<typename T>
class ArraySet
{
private:
    /* data */
    T* elements;
    unsigned int current_size;
    unsigned int capacity;

public:
    ArraySet();
    ArraySet(const ArraySet &other);
    ~ArraySet();

    ArraySet& operator=(const ArraySet &other);

    inline bool isFull();
    inline bool isEmpty();
    unsigned int size();
    int isMember(T element);
    void insert(T element);
    void remove();
    ArraySet& pop();
    ArraySet interSection(const ArraySet &other); 
    ArraySet sum(const ArraySet &other);
    ArraySet difference(const ArraySet &other);
    


};

template<typename T>
ArraySet<T>::ArraySet()
    : current_size(0),
    capacity(DEFAULT_CAPACITY)
{
    try
    {
        elements = new T[capacity];
    }
    catch(const std::bad_alloc& e)
    {
        std::cerr << e.what() << '\n';
        std::abort();
    }
}

template<typename T>
ArraySet<T>::ArraySet(const ArraySet &other)
    : current_size(other.current_size),
    capacity(other.capacity)
{
    try
    {
        elements = new T[capacity];
    }
    catch(const std::bad_alloc& e)
    {
        std::cerr << e.what() << '\n';
        std::abort();
    }

    std::copy(other.elements, other.elements+current_size, elements);
}

template<typename T>
ArraySet<T>::~ArraySet()
{
    if (elements != nullptr)
        delete []elements;
}

template<typename T>
ArraySet<T>& ArraySet<T>::operator=(const ArraySet &other) {
    if (this == &other)
        return *this;
    
    delete []elements;

    current_size = other.current_size;
    capacity = other.capacity;

    try
    {
        elements = new T[capacity];
    }
    catch(const std::bad_alloc& e)
    {
        std::cerr << e.what() << '\n';
        std::abort();
    }

    std::copy(other.elements, other.elements+current_size, elements);
}

template<typename T>
inline bool ArraySet<T>::isFull() {
    return (current_size == capacity) ? true : false;
}

template<typename T>
inline bool ArraySet<T>::isEmpty() {
    return (current_size == 0 ) ? true : false;
}

template<typename T>
unsigned int ArraySet<T>::size() {
    return current_size;
}

template<typename T>
int ArraySet<T>::isMember(T element) {
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
void ArraySet<T>::insert(T element) {
    if (isMember(element) == -1) {
        if (isFull()) {
            int new_capacity = capacity * CAPACITY_DECREASE;

            T* tmp_elements;
            try {
                tmp_elements = new T[new_capacity];
            }
            catch(const std::bad_alloc& e) {       
                std::cerr << e.what() << '\n';
                std::abort();
            }
            
        }
    }
}



#endif // SORTEDSET_H
