#pragma once

#include <ostream>
#include <list>

template <typename T, typename K>
class Tree
{
private:

    struct Node
    {
        Node* left = nullptr;
        Node* right = nullptr;
        T value;
        K key;
        int subtree_size = 0;
    } *head = nullptr;

    int quantity = 0;
    int visited_node_quantity = 0;

    void recursion_add(K, T, Node*);
    void recursion_add(Node* added_node, Node* viewed_node);
    void recursion_out(Node*, int);
    void recursion_clean(Node*);
    T& recursion_at(K, Node*);
    bool recursion_remove(K, Node*, Node*);
    void recursion_list_of_keys(Node*, std::list<K>&);
    bool recursion_serial_number(K, Node*, int&);
    void recursion_decrement_subtree_size(K, Node*);
    static Node* find_node(int, Node*);

public:

    Tree();
    Tree(const Tree&);
    ~Tree();

    int size();
    void clean();
    bool empty();
    T& at(K);
    void add(K, T);
    bool remove(K);
    std::list<K> list_of_keys();
    int get_visited_node_quantity();

    int serial_number(const K);

    void out();

    class iterator
    {
    private:

        friend class Tree;

        Node* ptr = nullptr;
        Node* head = nullptr;
        int index = 0;

        iterator();
        iterator(Node* node, int index);

    public:

        const iterator& operator=(const iterator&);
        const T& operator*();
        const K& getKey();
        const iterator& operator++();
        const iterator operator++(int);
        const iterator& operator--();
        const iterator operator--(int);

        const bool operator==(const iterator&);
        const bool operator!=(const iterator&);

    };

    const iterator begin();
    const iterator end();

    class reverse_iterator
    {
    private:

        friend class Tree;

        Node* ptr = nullptr;
        Node* head = nullptr;
        int index = 0;

        reverse_iterator();
        reverse_iterator(Node* node, int index);

    public:

        const reverse_iterator& operator=(const reverse_iterator&);
        const T& operator*();
        const K& getKey();
        const reverse_iterator& operator++();
        const reverse_iterator operator++(int);
        const reverse_iterator& operator--();
        const reverse_iterator operator--(int);

        const bool operator==(const reverse_iterator&);
        const bool operator!=(const reverse_iterator&);

    };

    const reverse_iterator rbegin();
    const reverse_iterator rend();

};

template<typename T, typename K>
Tree<T, K>::reverse_iterator::reverse_iterator() {

}

template<typename T, typename K>
Tree<T, K>::reverse_iterator::reverse_iterator(Tree::Node* node, int index) {
    this->head = node;
    this->index = index;
    if (node)
        this->ptr = find_node(index, node);
}

template<typename T, typename K>
const typename Tree<T, K>::reverse_iterator& Tree<T, K>::reverse_iterator::operator=(const Tree::reverse_iterator& it) {
    this->ptr = it.ptr;
    return *this;
}

template<typename T, typename K>
const T& Tree<T, K>::reverse_iterator::operator*() {
    return ptr->value;
}

template<typename T, typename K>
inline const K& Tree<T, K>::reverse_iterator::getKey()
{
    if (!ptr) throw std::runtime_error("У неустановленного итератора нельзя получить ключ");
    return ptr->key;
}

template<typename T, typename K>
const typename Tree<T, K>::reverse_iterator& Tree<T, K>::reverse_iterator::operator++() {
    this->ptr = Tree<T, K>::find_node(--this->index, this->head);
    return *this;
}

template<typename T, typename K>
const typename Tree<T, K>::reverse_iterator Tree<T, K>::reverse_iterator::operator++(int) {
    reverse_iterator it = *this;
    this->ptr = Tree<T, K>::find_node(--index, head);
    return *this;
}

template<typename T, typename K>
const typename Tree<T, K>::reverse_iterator& Tree<T, K>::reverse_iterator::operator--() {
    this->ptr = Tree<T, K>::find_node(++this->index, this->head);
    return *this;
}

template<typename T, typename K>
const typename Tree<T, K>::reverse_iterator Tree<T, K>::reverse_iterator::operator--(int) {
    reverse_iterator it = *this;
    this->ptr = Tree<T, K>::find_node(++index, head);
    return *this;
}

template<typename T, typename K>
const bool Tree<T, K>::reverse_iterator::operator==(const Tree::reverse_iterator& it) {
    return this->ptr == it.ptr;
}

template<typename T, typename K>
const bool Tree<T, K>::reverse_iterator::operator!=(const Tree::reverse_iterator& it) {
    return this->ptr != it.ptr;
}

template<typename T, typename K>
Tree<T, K>::iterator::iterator() {

}

template<typename T, typename K>
Tree<T, K>::iterator::iterator(Tree::Node* node, int index) {
    this->head = node;
    this->index = index;
    if (node)
        this->ptr = find_node(index, node);
}

template<typename T, typename K>
const typename Tree<T, K>::iterator& Tree<T, K>::iterator::operator=(const Tree::iterator& it) {
    this->ptr = it.ptr;
    return *this;
}

template<typename T, typename K>
const T& Tree<T, K>::iterator::operator*() {
    if (!ptr) throw std::runtime_error("Неустановленный итератор нельзя разыменовать");
    return ptr->value;
}

template<typename T, typename K>
const K& Tree<T, K>::iterator::getKey()
{
    if (!ptr) throw std::runtime_error("У неустановленного итератора нельзя получить ключ");
    return ptr->key;
}

template<typename T, typename K>
const typename Tree<T, K>::iterator& Tree<T, K>::iterator::operator++() {
    this->ptr = Tree<T, K>::find_node(++this->index, this->head);
    return *this;
}

template<typename T, typename K>
const typename Tree<T, K>::iterator Tree<T, K>::iterator::operator++(int) {
    iterator it = *this;
    this->ptr = Tree<T, K>::find_node(++index, head);
    return *this;
}

template<typename T, typename K>
const typename Tree<T, K>::iterator& Tree<T, K>::iterator::operator--() {
    this->ptr = Tree<T, K>::find_node(--this->index, this->head);
    return *this;
}

template<typename T, typename K>
const typename Tree<T, K>::iterator Tree<T, K>::iterator::operator--(int) {
    iterator it = *this;
    this->ptr = Tree<T, K>::find_node(--index, head);
    return *this;
}

template<typename T, typename K>
const bool Tree<T, K>::iterator::operator==(const Tree::iterator& it) {
    return this->ptr == it.ptr;
}

template<typename T, typename K>
const bool Tree<T, K>::iterator::operator!=(const Tree::iterator& it) {
    return this->ptr != it.ptr;
}

template <typename T, typename K>
void Tree<T, K>::recursion_out(Node* node, int depth) {
    if (node->left != nullptr) recursion_out(node->left, depth + 1);
    for (int i = 0; i < depth * 2; i++)
        std::cout << ' ';
    std::cout << node->key << ", " << node->value << ", " << node->subtree_size << std::endl;
    if (node->right != nullptr) recursion_out(node->right, depth + 1);
}

template <typename T, typename K>
void Tree<T, K>::out() {
    if (head != nullptr) recursion_out(head, 0);
}

template <typename T, typename K>
Tree<T, K>::Tree() = default;

template <typename T, typename K>
Tree<T, K>::Tree(const Tree & tree) {

}

template <typename T, typename K>
Tree<T, K>::~Tree() {
    clean();
}

template <typename T, typename K>
void Tree<T, K>::recursion_add(K key, T value, Tree<T, K>::Node * node) {
    visited_node_quantity++;
    if (node->key == key) {
        recursion_decrement_subtree_size(key, head);
        throw std::invalid_argument("Такой ключ уже существует");
    }
    node->subtree_size++;
    if (node->key > key) {
        if (node->left == nullptr) {
            node->left = new Node();
            node->left->key = key;
            node->left->value = value;
        }
        else
            recursion_add(key, value, node->left);
    }
    else {
        if (node->right == nullptr) {
            node->right = new Node();
            node->right->key = key;
            node->right->value = value;
        }
        else
            recursion_add(key, value, node->right);
    }
}

template <typename T, typename K>
void Tree<T, K>::add(K key, T value) {
    visited_node_quantity = 0;
    if (head == nullptr) {
        head = new Node();
        head->value = value;
        head->key = key;
    }
    else {
        recursion_add(key, value, head);
    }
    quantity++;
}

template <typename T, typename K>
int Tree<T, K>::size() {
    return quantity;
}

template <typename T, typename K>
bool Tree<T, K>::empty() {
    return quantity == 0;
}

template <typename T, typename K>
T& Tree<T, K>::at(K key) {
    visited_node_quantity = 0;
    if (head != nullptr)
        return recursion_at(key, head);
    else throw std::invalid_argument("Дерево пустое");
}

template <typename T, typename K>
T& Tree<T, K>::recursion_at(K key, Node * node) {
    visited_node_quantity++;
    if (node->key == key) return node->value;
    if (node->key > key)
        if (node->left != nullptr)
            recursion_at(key, node->left);
        else
            throw std::invalid_argument("Такого ключа нет в коллекции");
    else
        if (node->right != nullptr)
            recursion_at(key, node->right);
        else
            throw std::invalid_argument("Такого ключа нет в коллекции");
}

template <typename T, typename K>
void Tree<T, K>::clean() {
    if (head != nullptr) recursion_clean(head);
    head = nullptr;
}

template <typename T, typename K>
void Tree<T, K>::recursion_clean(Node * node) {
    if (node->left != nullptr) recursion_clean(node->left);
    if (node->right != nullptr) recursion_clean(node->right);
    delete node;
}

template <typename T, typename K>
bool Tree<T, K>::remove(K key) {
    visited_node_quantity = 0;
    if (head != nullptr) {
        if (head->key == key) {
            Node* left = head->left;
            Node* right = head->right;
            delete head;
            quantity--;
            if (left != nullptr) {
                head = left;
                if (right != nullptr) recursion_add(right, head);
            }
            else if (right != nullptr) {
                head = right;
            }
            else
                head = nullptr;
            return true;
        }
        if (head->key > key)
            return recursion_remove(key, head->left, head);
        else
            return recursion_remove(key, head->right, head);
    }
    return false;
}

template <typename T, typename K>
bool Tree<T, K>::recursion_remove(K key, Node * node, Node * parent) {
    visited_node_quantity++;
    if (node->key == key) {
        if (parent->left == node)
            parent->left = nullptr;
        else
            parent->right = nullptr;
        if (node->left != nullptr) recursion_add(node->left, head);
        if (node->right != nullptr) recursion_add(node->right, head);
        delete node;
        quantity--;
        return true;
    }
    if (node->key > key) {
        if (node->left != nullptr)
            recursion_remove(key, node->left, node);
        else
            return false;
    }
    else {
        if (node->right != nullptr)
            recursion_remove(key, node->right, node);
        else
            return false;
    }
    return false;
}

template <typename T, typename K>
void Tree<T, K>::recursion_add(Node * added_node, Node * viewed_node) {
    if (added_node->key == viewed_node->key) throw std::invalid_argument("Такой ключ уже существует");
    viewed_node->subtree_size += added_node->subtree_size;
    if (viewed_node->key > added_node->key) {
        if (viewed_node->left == nullptr)
            viewed_node->left = added_node;
        else
            recursion_add(added_node, viewed_node->left);
    }
    else {
        if (viewed_node->right == nullptr)
            viewed_node->right = added_node;
        else
            recursion_add(added_node, viewed_node->right);
    }
}

template<typename T, typename K>
std::list<K> Tree<T, K>::list_of_keys() {
    visited_node_quantity = 0;
    std::list<K> list;
    if (head != nullptr) recursion_list_of_keys(head, list);
    return list;
}

template<typename T, typename K>
int Tree<T, K>::get_visited_node_quantity()
{
    return visited_node_quantity;
}

template<typename T, typename K>
void Tree<T, K>::recursion_list_of_keys(Node * node, std::list<K>&list) {
    visited_node_quantity++;
    list.push_back(node->key);
    if (node->left != nullptr) recursion_list_of_keys(node->left, list);
    if (node->right != nullptr) recursion_list_of_keys(node->right, list);
}

template<typename T, typename K>
int Tree<T, K>::serial_number(const K key) {
    visited_node_quantity = 0;
    int number = 0;
    if (!head) throw std::runtime_error("Дерево пустое: нельзя узнать порядковый номер");
    recursion_serial_number(key, head, number);
    return number;
}

template<typename T, typename K>
bool Tree<T, K>::recursion_serial_number(K key, Tree::Node * node, int& number) {
    visited_node_quantity++;
    if (node->key == key) return true;
    if (node->key > key) {
        number++;
        if (node->left != nullptr)
            recursion_serial_number(key, node->left, number);
        else
            throw std::invalid_argument("Такого ключа нет в коллекции");
    }
    else {
        number += (node->left != nullptr ? node->left->subtree_size + 2 : 1);
        if (node->right != nullptr)
            recursion_serial_number(key, node->right, number);
        else
            throw std::invalid_argument("Такого ключа нет в коллекции");
    }
}

template<typename T, typename K>
void Tree<T, K>::recursion_decrement_subtree_size(K key, Node * node) {
    node->subtree_size--;
    if (node->key > key) {
        if (node->left != nullptr) recursion_decrement_subtree_size(key, node->left);
    }
    else {
        if (node->right != nullptr) recursion_decrement_subtree_size(key, node->right);
    }
}

template<typename T, typename K>
const typename Tree<T, K>::iterator Tree<T, K>::begin() {
    if (!head) return iterator(nullptr, 0);
    iterator it(head, 0);
    return it;
}

template<typename T, typename K>
const typename Tree<T, K>::iterator Tree<T, K>::end() {
    iterator it(head, head->subtree_size + 1);
    return it;
}

template<typename T, typename K>
typename Tree<T, K>::Node* Tree<T, K>::find_node(int index, Node * head) {
    if (index > head->subtree_size || index < 0) return nullptr;
    int index_now = 0;
    Node* node_now = head;
    while (index_now != index) {
        if (node_now->left != nullptr) {
            if (node_now->left->subtree_size + 1 >= index - index_now) {
                index_now++;
                node_now = node_now->left;
            }
            else {
                if (node_now->right != nullptr) {
                    index_now += (node_now->left->subtree_size + 2);
                    node_now = node_now->right;
                }
            }
        }
        else {
            index_now++;
            if (node_now->right != nullptr)
                node_now = node_now->right;
        }
    }
    return node_now;
}

template<typename T, typename K>
const typename Tree<T, K>::reverse_iterator Tree<T, K>::rbegin() {
    if (!quantity) return reverse_iterator(nullptr, 0);
    reverse_iterator it(head, head->subtree_size);
    return it;
}

template<typename T, typename K>
const typename Tree<T, K>::reverse_iterator Tree<T, K>::rend() {
    reverse_iterator it(head, -1);
    return it;
}
