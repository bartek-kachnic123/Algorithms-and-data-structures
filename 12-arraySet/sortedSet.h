#if !defined(SORTEDSET_H)
#define SORTEDSET_H
#include <cassert>
#include <iostream>
#include <iterator>

#include "avlTree.h"

template <typename T> class SortedSet
{
  private:
    /* data */
    AVLtree<T> set;
    unsigned int curr_size;

  public:
    SortedSet();
    SortedSet(const SortedSet &other);
    ~SortedSet();

    SortedSet &operator=(const SortedSet &other);

    bool isEmpty();
    unsigned int size();
    bool isMember(const T &item) const;
    void insert(const T item);
    void remove(const T item);
    SortedSet interSection(const SortedSet &other);
    SortedSet unionSet(const SortedSet &other);
    SortedSet difference(const SortedSet &other);
   

    class Iterator {
    private:
        AVLnode<T>* node;
    public:
        Iterator(AVLnode<T>* ptr) : node(ptr) {}

        Iterator& operator++() {
            
           if (node->right != nullptr) {
            node = node->right;
            while (node->left != nullptr) {
                node = node->left;
            }
        } else {
            AVLnode<T>* parent = node->parent;
            while (parent != nullptr && node == parent->right) {
                node = parent;
                parent = node->parent;
            }
            node = parent;
        }
    return *this;
        }

        bool operator!=(const Iterator& other) const {
            return node != other.node;
        }

        T operator*() const {
            return node->key;
        }

        
    };
    Iterator begin() const {
        AVLnode<T>* node = this->set.top();
        while (node->left != nullptr) {
            node = node->left;
        }
        return Iterator(node);
        }

        Iterator end() const {
            return Iterator(nullptr);
        }   

};

template<typename T>
SortedSet<T>::SortedSet() {
    curr_size = 0;
}
template<typename T>
SortedSet<T>::~SortedSet() {}

template<typename T>
bool SortedSet<T>::isEmpty() {
    return (curr_size == 0) ? true : false;
}

template<typename T>
unsigned int SortedSet<T>::size() {
    return curr_size;
}

template<typename T>
bool SortedSet<T>::isMember(const T &item) const{
    return (set.search(item) == nullptr) ? false : true;
}

template<typename T>
void SortedSet<T>::insert(const T item) {
    if (!isMember(item)) {
        set.insert(item);
        ++curr_size;
    }
}

template<typename T>
void SortedSet<T>::remove(const T item) {
    set.deleteKey(item);
    --curr_size;
}

#endif // SORTEDSET_H
