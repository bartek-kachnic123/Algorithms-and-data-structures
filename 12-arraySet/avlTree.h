#if !defined(AVLTREE_H)
#define AVLTREE_H

#include <algorithm>
#include <iostream>

/* AVL node */
template <typename T>
class AVLnode {
public:
    T key;
    int balance;
    AVLnode *left, *right, *parent;

    AVLnode(T k, AVLnode *p)
    {
        key = k;
        balance = 0;
        parent = p;
        left = nullptr;
        right = nullptr;
    }

    ~AVLnode() {}
};

/* AVL tree */
template <typename T>
class AVLtree {
public:
    AVLtree(void);
    ~AVLtree(void);
    bool insert(T key);
    void deleteKey(const T key);
    void printBalance();
    T * find_min();
    T * find_max();
    T * search(const T &key) const;
    AVLnode<T> * top() const;

private:
    AVLnode<T> *root;

    AVLnode<T>* rotateLeft          ( AVLnode<T> *a );
    AVLnode<T>* rotateRight         ( AVLnode<T> *a );
    AVLnode<T>* rotateLeftThenRight ( AVLnode<T> *n );
    AVLnode<T>* rotateRightThenLeft ( AVLnode<T> *n );
    void rebalance                  ( AVLnode<T> *n );
    int height                      ( AVLnode<T> *n );
    void setBalance                 ( AVLnode<T> *n );
    void printBalance               ( AVLnode<T> *n );
    void clear                      ( AVLnode<T> *n );
};

/* AVL class definition */
template <typename  T>
void AVLtree<T>::rebalance(AVLnode<T> *n) {
    setBalance(n);

    if (n->balance == -2) {
        if (height(n->left->left) >= height(n->left->right))
            n = rotateRight(n);
        else
            n = rotateLeftThenRight(n);
    }
    else if (n->balance == 2) {
        if (height(n->right->right) >= height(n->right->left))
            n = rotateLeft(n);
        else
            n = rotateRightThenLeft(n);
    }

    if (n->parent != nullptr) {
        rebalance(n->parent);
    }
    else {
        root = n;
    }
}

template <typename  T>
AVLnode<T>* AVLtree<T>::rotateLeft(AVLnode<T> *a) {
    AVLnode<T> *b = a->right;
    b->parent = a->parent;
    a->right = b->left;

    if (a->right != nullptr)
        a->right->parent = a;

    b->left = a;
    a->parent = b;

    if (b->parent != nullptr) {
        if (b->parent->right == a) {
            b->parent->right = b;
        }
        else {
            b->parent->left = b;
        }
    }

    setBalance(a);
    setBalance(b);
    return b;
}

template <typename  T>
AVLnode<T>* AVLtree<T>::rotateRight(AVLnode<T> *a) {
    AVLnode<T> *b = a->left;
    b->parent = a->parent;
    a->left = b->right;

    if (a->left != nullptr)
        a->left->parent = a;

    b->right = a;
    a->parent = b;

    if (b->parent != nullptr) {
        if (b->parent->right == a) {
            b->parent->right = b;
        }
        else {
            b->parent->left = b;
        }
    }

    setBalance(a);
    setBalance(b);
    return b;
}

template <typename  T>
AVLnode<T>* AVLtree<T>::rotateLeftThenRight(AVLnode<T> *n) {
    n->left = rotateLeft(n->left);
    return rotateRight(n);
}

template <typename  T>
AVLnode<T>* AVLtree<T>::rotateRightThenLeft(AVLnode<T> *n) {
    n->right = rotateRight(n->right);
    return rotateLeft(n);
}

template <typename  T>
int AVLtree<T>::height(AVLnode<T> *n) {
    if (n == nullptr)
        return -1;
    return 1 + std::max(height(n->left), height(n->right));
}

template <typename  T>
void AVLtree<T>::setBalance(AVLnode<T> *n) {
    n->balance = height(n->right) - height(n->left);
}

template <typename  T>
void AVLtree<T>::printBalance(AVLnode<T> *n) {
    if (n != nullptr) {
        printBalance(n->left);
        std::cout << n->balance << " ";
        printBalance(n->right);
    }
}

template <typename  T>
AVLtree<T>::AVLtree(void) : root(nullptr) {}

template <typename  T>
AVLtree<T>::~AVLtree() {
    clear(root);
    root = nullptr;
}

template <typename  T>
void AVLtree<T>::clear(AVLnode<T> *n) {
    if (n == nullptr) return;

    clear(n->left);
    clear(n->right);

    delete n;
}

template <typename  T>
bool AVLtree<T>::insert(T key) {
    if (root == nullptr) {
        root = new AVLnode<T>(key, nullptr);
    }
    else {
        AVLnode<T>
            *n = root,
            *parent;

        while (true) {
            if (n->key == key)
                return false;

            parent = n;

            bool goLeft = n->key > key;
            n = goLeft ? n->left : n->right;

            if (n == nullptr) {
                if (goLeft) {
                    parent->left = new AVLnode<T>(key, parent);
                }
                else {
                    parent->right = new AVLnode<T>(key, parent);
                }

                rebalance(parent);
                break;
            }
        }
    }

    return true;
}

template <typename T>
void AVLtree<T>::deleteKey(const T delKey) {
    if (root == nullptr)
        return;

    AVLnode<T>
        *n       = root,
        *parent  = root,
        *delNode = nullptr,
        *child   = root;

    while (child != nullptr) {
        parent = n;
        n = child;
        child = delKey >= n->key ? n->right : n->left;
        if (delKey == n->key)
            delNode = n;
    }

    if (delNode != nullptr) {
        delNode->key = n->key;

        child = n->left != nullptr ? n->left : n->right;

        if (root->key == delKey) {
            root = child;
        }
        else {
            if (parent->left == n) {
                parent->left = child;
            }
            else {
                parent->right = child;
            }

            rebalance(parent);
            
        }

        delete delNode;
        
    }
    
}

template <typename  T>
void AVLtree<T>::printBalance() {
    printBalance(root);
    std::cout << std::endl;
}

template <typename T>
T * AVLtree<T>::find_min() {

    if (root == nullptr) return nullptr;
    
    AVLnode<T> *node = root;
    while(node->left != nullptr) {
        node = node->left;
    }
    T* wsk = &node->key;
    return wsk;
}

template <typename T>
T * AVLtree<T>::find_max() {

    if (root == nullptr) return nullptr;

    AVLnode<T> *node = root;
    while(node->right != nullptr) {
        node = node->right;
    }
    T* wsk = &node->key;
    return wsk;
}

template <typename T>
 T* AVLtree<T>::search(const T& item) const {
        for (auto node=root; node != nullptr; ) {
            if (item == node->key) {
                return &(node->key);
            } else if (item < node->key) {
                node = node->left;
            } else {
                node = node->right;
            }
        }
        return nullptr;
    }

template <typename T>
AVLnode<T>* AVLtree<T>::top() const{
    return root;
}
#endif // AVLTREE_H
