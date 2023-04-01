#if !defined(PRIORITY_QUEUE_HPP)
#define PRIORITY_QUEUE_HPP
#include <iostream>

template<typename T>
class QueueElem {
    /* data */
    int _priority;
    T _obj;
    
    QueueElem(int &priority, T &obj) {
        _priority = priority;
        _obj = obj;
    };

    public:
    QueueElem(){};
    ~QueueElem(){};

    friend std::ostream& operator<<(std::ostream& os, const QueueElem& qe) {
        os << qe._obj;
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

private:
    
    void allocate_memory();
    void resize(int new_capacity);
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


#endif // PRIORITY_QUEUE_HPP
