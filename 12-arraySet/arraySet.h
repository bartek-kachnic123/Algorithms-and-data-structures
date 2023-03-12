#if !defined(ARRAYSET_H)
#define ARRAYSET_H
#define DEFAULT_CAPACITY 128
#define CAPACITY_INCREASE 2
#define CAPACITY_DECREASE 0.25

#include <iostream>
#include <algorithm>

template<typename T>
class ArraySet
{
private:
    /* data */
    T* _elements;
    int _current_size;
    int _capacity;

public:
    ArraySet(size_t capacity = DEFAULT_CAPACITY);
    ArraySet(const ArraySet &other);
    ~ArraySet();

    ArraySet& operator=(const ArraySet &other);

    inline bool isFull();
    inline bool isEmpty();
    int size() const;
    bool isMember(T &element) const;
    void insert(T element);
    void remove(T element);
    T pop();
    ArraySet interSection(const ArraySet &other_set); 
    ArraySet sum(const ArraySet &other);
    ArraySet difference(const ArraySet &other);

    
private:
    void allocate_memory();
    void resize(int new_capacity);
    int binarySearch(T &element) const;

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const ArraySet<U> &set);



};

template<typename T>
ArraySet<T>::ArraySet(size_t capacity)
    : _current_size(0),
    _capacity(capacity)
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
int ArraySet<T>::size() const{
    return _current_size;
}

template<typename T>
bool ArraySet<T>::isMember(T &element) const {
    return (binarySearch(element) != -1) ? true : false;
}

template<typename T>
void ArraySet<T>::insert(T element) {
    if (!isMember(element)) {

        if (isFull()) {
            resize(_capacity * CAPACITY_DECREASE);
        }

        auto pos = std::lower_bound(_elements, _elements+_current_size, element);
        std::copy_backward(pos,  _elements+_current_size, _elements+_current_size + 1);
        *pos = element;
        _current_size++;

    }
}
template<typename T>
void ArraySet<T>::remove(T element) {
    if (isMember(element))
    {
        T *delete_position = std::lower_bound(_elements, _elements+_current_size, element);
        std::copy(delete_position + 1, _elements+_current_size, delete_position);
        _current_size--;

        if (_current_size <= _capacity * CAPACITY_DECREASE)
        {
            resize(_capacity / CAPACITY_INCREASE);
        }
    }
    
}
template<typename T>
T ArraySet<T>::pop() {
    if (!isEmpty()) {
        T element = _elements[--_current_size];

        if (_current_size <= _capacity * CAPACITY_DECREASE)
            resize(_capacity / CAPACITY_INCREASE);
        
        return element;
    }
    throw std::runtime_error("Set is empty!");
}

template<typename T>
ArraySet<T> ArraySet<T>::interSection(const ArraySet &other_set) {
    
    ArraySet<T> new_set(std::min(this->_capacity, other_set._capacity));

    if (this->size() < other_set.size()) {
        for (int i = 0; i < this->size(); i++) {
            if (other_set.isMember(this->_elements[i])) 
                new_set.insert(this->_elements[i]);  
        }
    }
    else {
        for (int i = 0; i < other_set.size(); i++) {
            if (this->isMember(other_set._elements[i]))
                new_set.insert(other_set._elements[i]);
        }
    }

    return new_set;
}

template<typename U>
std::ostream& operator<<(std::ostream& os, const ArraySet<U> &set){
    os << "{ ";
    for (int i = 0; i < set.size(); i++)
    {
        os << set._elements[i] << ", ";
    }
    os << "}";

    return os;
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
int ArraySet<T>::binarySearch(T &element) const {
    int left = 0;
    int right = size() - 1;
    int mid;
    while(left <= right) {
        mid = (left + right) / 2;

        if (_elements[mid] == element)
            return mid;
        else if (_elements[mid] > element)
            right = mid - 1;
        else
            left = mid + 1;
    }
    return -1;
}


#endif // ARRAYSET_H
