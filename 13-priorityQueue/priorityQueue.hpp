#if !defined(PRIORITY_QUEUE_HPP)
#define PRIORITY_QUEUE_HPP
#include <iostream>
#include <stdexcept>

template<typename T>
class QueueElem {
    /* data */
    int _priority;
    T _obj;
    

    public:
    QueueElem(){};
    QueueElem(T &obj, int &priority) {
        _priority = priority;
        _obj = obj;
    };
    ~QueueElem(){};
    void setPriority(int priority) {
        _priority = priority;
    }
    bool operator<(const QueueElem& qe) {
        return (this->_priority < qe._priority);
    }
    bool operator>(const QueueElem& qe) {
        return (this->_priority > qe._priority);
    }
    friend std::ostream& operator<<(std::ostream& os, const QueueElem& qe) {
        os << qe._obj << "[K:" << qe._priority << "]";
        return os;
    }
};

template<typename T>
class PriorityQueue
{
private:
    /* data */
    QueueElem<T>* _queue_elements;
    int _current_size;
    int _capacity;

    static int DEFAULT_CAPACITY;
    static int CAPACITY_INCREASE;
    static double CAPACITY_DECREASE;
public:
    PriorityQueue(int capacity = DEFAULT_CAPACITY);
    ~PriorityQueue();

    void insert(T element, int key);
    QueueElem<T> max();
    QueueElem<T> extractMax();
    inline bool isEmpty();
    inline bool isFull();
    inline int size() const;

private:
    
    void allocate_memory();
    void resize(int new_capacity);

    inline int parent(int i);
    inline int leftChild(int i);
    inline int rightChild(int i);

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const PriorityQueue<U>& pq);
};

// static variables
template<typename T> int PriorityQueue<T>::DEFAULT_CAPACITY = 8;
template<typename T> int PriorityQueue<T>::CAPACITY_INCREASE = 2;
template<typename T> double PriorityQueue<T>::CAPACITY_DECREASE = 0.25;

template<typename T>
PriorityQueue<T>::PriorityQueue(int capacity)
    : _current_size(0),
    _capacity(capacity)
{
    allocate_memory();
}

template<typename T>
PriorityQueue<T>::~PriorityQueue()
{
    if (_queue_elements != nullptr)
        delete []_queue_elements;
}

template<typename T>
void PriorityQueue<T>::insert(T element, int key) {
    if (isFull()) {
        resize(_capacity * CAPACITY_INCREASE);
    }

    _queue_elements[_current_size++] = QueueElem<T>(element, key);
    int i = _current_size - 1;
    while(_queue_elements[i] < _queue_elements[parent(i)]) {
        std::swap(_queue_elements[i], _queue_elements[parent(i)]);

        i = parent(i);
    }
}

template<typename T>
QueueElem<T> PriorityQueue<T>::max() {
    if (isEmpty())
        throw std::runtime_error("Priority queue is empty");
    return _queue_elements[0];
}

template<typename T>
QueueElem<T> PriorityQueue<T>::extractMax() {
    if (isEmpty())
        throw std::runtime_error("Priority queue is empty");

    QueueElem<T> maxQueueElem = max();
    QueueElem<T> lastElem = _queue_elements[size() - 1];
    _current_size--;

    int i = 0;
    while(leftChild(i) < _current_size) {
        if (_queue_elements[leftChild(i)] < _queue_elements[rightChild(i)]) {
            _queue_elements[i] = _queue_elements[leftChild(i)];
            i = leftChild(i);
        }
        else {
            _queue_elements[i] = _queue_elements[rightChild(i)];
            i = rightChild(i);
        }
       
    }
    _queue_elements[i] = lastElem;

    
    if (_current_size < _capacity * CAPACITY_DECREASE)
        resize(_capacity / CAPACITY_INCREASE);

    return maxQueueElem;
}
template<typename T>
bool PriorityQueue<T>::isEmpty() {
    return (_current_size == 0);
}

template<typename T>
bool PriorityQueue<T>::isFull() {
    return (_current_size == _capacity);
}
template<typename T>
int PriorityQueue<T>::size() const {
    return _current_size;
}
template<typename T> 
void PriorityQueue<T>::allocate_memory() {
    try
    {
        _queue_elements = new QueueElem<T>[_capacity];
    }
    catch(const std::bad_alloc& e)
    {
        std::cerr << e.what() << '\n';
        std::abort();
    }
}

template<typename T>
void PriorityQueue<T>::resize(int new_capacity) {

    if(new_capacity < DEFAULT_CAPACITY)
            new_capacity = DEFAULT_CAPACITY;

    QueueElem<T>* tmp_queue_elements;
    try {
        tmp_queue_elements = new QueueElem<T>[new_capacity];
    }
    catch(const std::bad_alloc& e) {
        std::cerr << e.what() << '\n';
        std::abort();
    }

    _capacity = new_capacity;
    std::copy(_queue_elements, _queue_elements+_current_size, tmp_queue_elements);

    delete [] _queue_elements;
    _queue_elements = nullptr;

    _queue_elements = tmp_queue_elements;
}


template<typename T>
int PriorityQueue<T>::parent(int i) {
    return (i != 0) ? (i - 1) / 2 : 0;
}

template<typename T>
int PriorityQueue<T>::leftChild(int i) {
    return (i * 2) + 1;
}

template<typename T>
int PriorityQueue<T>::rightChild(int i) {
    return (i * 2) + 2;
}

template<typename U>
std::ostream& operator<<(std::ostream& os, const PriorityQueue<U> &pq){
    os << "{ ";
    for (int i = 0; i < pq._current_size; i++)
    {
        os << pq._queue_elements[i] << ", ";
    }
    os << "}";

    return os;
}

#endif // PRIORITY_QUEUE_HPP
