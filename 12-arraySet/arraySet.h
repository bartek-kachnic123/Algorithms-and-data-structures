#if !defined(ARRAYSET_H)
#define ARRAYSET_H
#define DEFAULT_CAPACITY 128
#define CAPACITY_INCREASE 2
#define CAPACITY_DECREASE 0.25

#include <iostream>

template<typename T>
class ArraySet
{
private:
    /* data */
    T* _elements;
    unsigned int _current_size;
    unsigned int _capacity;

public:
    ArraySet();
    ArraySet(const ArraySet &other);
    ~ArraySet();

    ArraySet& operator=(const ArraySet &other);

    inline bool isFull();
    inline bool isEmpty();
    unsigned int size();
    bool isMember(T &element);
    void insert(T element);
    void remove();
    ArraySet& pop();
    ArraySet interSection(const ArraySet &other); 
    ArraySet sum(const ArraySet &other);
    ArraySet difference(const ArraySet &other);
    
private:
    void allocate_memory();
    void resize(int new_capacity);
    int binarySearch(T &element);


};

template<typename T>
ArraySet<T>::ArraySet()
    : _current_size(0),
    _capacity(DEFAULT_CAPACITY)
{
    allocate_memory();
}

template<typename T>
ArraySet<T>::ArraySet(const ArraySet &other)
    : _current_size(other._current_size),
    _capacity(other._capacity)
{
    allocate_memory();
    std::copy(other._elements, other._elements+_current_size, _elements);
}

template<typename T>
ArraySet<T>::~ArraySet()
{
    if (_elements != nullptr)
        delete []_elements;
}

template<typename T>
ArraySet<T>& ArraySet<T>::operator=(const ArraySet &other) {
    if (this == &other)
        return *this;
    
    delete []_elements;

    _current_size = other._current_size;
    _capacity = other._capacity;

    allocate_memory();

    std::copy(other._elements, other._elements+_current_size, _elements);
}

template<typename T>
inline bool ArraySet<T>::isFull() {
    return (_current_size == _capacity) ? true : false;
}

template<typename T>
inline bool ArraySet<T>::isEmpty() {
    return (_current_size == 0 ) ? true : false;
}

template<typename T>
unsigned int ArraySet<T>::size() {
    return _current_size;
}

template<typename T>
bool ArraySet<T>::isMember(T &element) {
    return (binarySearch() != -1) ? true : false;
}

template<typename T>
void ArraySet<T>::insert(T element) {
    if (binarySearch(element) == -1) {
        if (isFull()) {
            int new_capacity = _capacity * CAPACITY_DECREASE;

            T* tmp_elements = nullptr;
            
        }
    }
}


template<typename T> 
void ArraySet<T>::allocate_memory() {
    try
    {
        _elements = new T[_capacity];
    }
    catch(const std::bad_alloc& e)
    {
        std::cerr << e.what() << '\n';
        std::abort();
    }
}

template<typename T>
void ArraySet<T>::resize(int new_capacity) {
    T* tmp_elements;
    try {
        tmp_elements = new T[new_capacity];
    }
    catch(const std::bad_alloc& e) {
        std::cerr << e.what() << '\n';
        std::abort();
    }

    _capacity = new_capacity;
    std::copy(_elements, _elements+_current_size, tmp_elements);

    delete [] _elements;
    _elements = nullptr;

    _elements = tmp_elements;
}

template<typename T>
int ArraySet<T>::binarySearch(T &element) {
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


#endif // ARRAYSET_H
