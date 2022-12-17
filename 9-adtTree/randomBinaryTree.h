#ifndef RANDOM_BINARY_TREE
#define RANDOM_BINARY_TREE
#include <cstdlib>   // std::rand(), RAND_MAX, std::srand()
#include <iostream>
#include <cassert>
#include <stack>
#include <queue>

// Szablon dla węzła drzewa binarnego i drzewa BST.
template <typename T>
struct BSTNode {
// the default access mode and default inheritance mode are public
    T value;
    BSTNode *left, *right;
    //BSTNode *parent;   // używane w pewnych zastosowaniach
    // kostruktor domyślny
    BSTNode() : value(T()), left(nullptr), right(nullptr) {}
    // konstruktor zwykły
    BSTNode(const T& item) : value(item), left(nullptr), right(nullptr) {}
    ~BSTNode() {} // destruktor
};
// Szablon dla przypadkowego drzewa binarnego.
template <typename T>
class RandomBinaryTree {
    BSTNode<T> *root;
public:
    RandomBinaryTree() : root(nullptr) {} // konstruktor domyślny
    ~RandomBinaryTree() { clear(); } // trzeba wyczyścić
    bool empty() const { return root == nullptr; }
    T& top() { assert(root != nullptr); return root->value; } // podgląd korzenia
    void insert(const T& item) { root = insert(root, item); }
    //void remove(const T& item); // na razie nie usuwamy elementów
    // Szukając element dostajemy wskaźnik do elementu lub nullptr.
    T* search(const T& item) const {
        auto ptr = search(root, item);
        return ((ptr == nullptr) ? nullptr : &(ptr->value));
    }
    void preorder() { preorder(root); }
    void inorder() { inorder(root); }
    void postorder() { postorder(root); }
    void iter_preorder();
    void iter_inorder(); // trudne
    void iter_postorder(); // trudne
    void bfs(); // przejście poziomami (wszerz)
    void clear() { clear(root); root = nullptr; }
    void display() { display(root, 0); }
    T  sum() { return sum(root); }

    // Metody bezpośrednio odwołujące się do node.
    // Mogą działać na poddrzewie.
    void clear(BSTNode<T> *node);
    BSTNode<T> * insert(BSTNode<T> *node, const T& item); // zwraca nowy korzeń
    BSTNode<T> * search(BSTNode<T> *node, const T& item) const;
    void preorder(BSTNode<T> *node);
    void inorder(BSTNode<T> *node);
    void postorder(BSTNode<T> *node);
    void display(BSTNode<T> *node, int level);
    virtual void visit(BSTNode<T> *node) {
        assert(node != nullptr);
        std::cout << "visiting " << node->value << std::endl;
    }
    T sum(BSTNode<T> *node);
};
// Wyświetlanie obróconego (counterclockwise) drzewa binarnego.
template <typename T>
void RandomBinaryTree<T>::display(BSTNode<T> *node, int level) {
    if (node == nullptr) return;
    display(node->right, level + 1);
    std::cout << std::string(3 * level, ' ') << node->value << std::endl;
    display(node->left, level + 1);
}

template <typename T>
BSTNode<T> * RandomBinaryTree<T>::insert(BSTNode<T> *node, const T& item) {
    if (node == nullptr) {
        return new BSTNode<T>(item);
    }
    if (std::rand() % 2) { // można lepiej
        node->left = insert(node->left, item);
    } else {
        node->right = insert(node->right, item);
    }
    return node; // zwraca nowy korzen
}
template <typename T>
BSTNode<T> * RandomBinaryTree<T>::search(BSTNode<T> *node, const T& item) const {
    if (node == nullptr || node->value == item) {
        return node;
    }
    T* ptr;
    ptr = search(node->left, item);
    if (ptr == nullptr) {
        ptr = search(node->right, item);
    }
    return ptr;
}
// PRZECHODZENIE PO DRZEWIE WSZERZ (BFS)
// Przechodzenie wszerz polega na odwiedzeniu korzenia, potem na przechodzeniu poziomami. Poziomy są przechodzone w kolejności od najbliższych do najdalszych, a w ramach poziomu węzły są odwiedzane od lewej do prawej. W implementacji wykorzystuje się kolejkę.

template <typename T>
void RandomBinaryTree<T>::bfs() {
    if (root == nullptr) return;
    std::queue<BSTNode<T>*> Q; // wskaźniki do wezłów
    BSTNode<T> *node = root;
    Q.push(node);
    while (!Q.empty()) {
        node = Q.front(); // podglądamy
        Q.pop();        // usuwamy z kolejki
        visit(node); // tu jest właściwe przetworzenie węzła
        if (node->left != nullptr)
            Q.push(node->left);
        if (node->right != nullptr)
            Q.push(node->right);
    }
}
// PRZECHODZENIE PO DRZEWIE W GŁĄB
// Podczas przechodzenia w głąb przechodzimy możliwie daleko w lewo (lub w prawo), następnie wracamy do najbliższego rozwidlenia i przechodzimy jeden krok w prawo (lub w lewo). Czynności powtarzamy, aż odwiedzimy wszystkie węzły. Moment odwiedzania węzła może być wybrany na kilka sposobów, stąd pochodzą trzy podstawowe odmiany przechodzenia:

// przechodzenie z wyprzedzeniem (ang. preorder),
// przechodzenie bezpośrednie (ang. inorder),
// przechodzenie z opóźnieniem (ang. postorder).

template <typename T>
void RandomBinaryTree<T>::inorder(BSTNode<T> *node) {
    if (node == nullptr) return;
    inorder(node->left);
    visit(node);
    inorder(node->right);
}

template <typename T>
void RandomBinaryTree<T>::preorder(BSTNode<T> *node) {
    if (node == nullptr) return;
    visit(node);
    preorder(node->left);
    preorder(node->right);
}

template <typename T>
void RandomBinaryTree<T>::postorder(BSTNode<T> *node) {
    if (node == nullptr) return;
    postorder(node->left);
    postorder(node->right);
    visit(node);
}

//Przechodzenie przez drzewo w kolejności preorder możemy zaimplementować iteracyjnie za pomocą stosu.
template <typename T>
void RandomBinaryTree<T>::iter_preorder() {
    if (root == nullptr) return;
    std::stack<BSTNode<T>*> S; // wskaźniki do węzłów
    BSTNode<T> *node = root;
    S.push(node);
    while (!S.empty()) {
        node = S.top(); // podglądamy
        S.pop();        // usuwamy ze stosu
        visit(node); // tu jest właściwe przetworzenie węzła
        if (node->right != nullptr) // najpierw prawe poddrzewo!
            S.push(node->right);
        if (node->left != nullptr)
            S.push(node->left);
    }
}
template <typename T>
void RandomBinaryTree<T>::clear(BSTNode<T> *node)
{
    if (node == nullptr) return;

    clear(node->left);

    clear(node->right);
    
    delete node;
}

template <typename T>
T RandomBinaryTree<T>::sum(BSTNode<T> *node)
{
    if (node == nullptr) return T();
    
    return node->value + sum(node->left) + sum(node->right);
}

#endif