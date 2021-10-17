//
// Created by Decane on 26.01.2021.
//
#ifndef ZESTAW6_FINAL_BINARYTREE_H
#define ZESTAW6_FINAL_BINARYTREE_H
#pragma once
#include "queue.hxx"
#include "stack.hxx"
#include <iostream>
#define newline std::cout << '\n'

template<typename T>
class BSTree{
public:
    BSTree();
    class TreeNode;
    class TreeIterator;

    template<class U>
    void insert(U&& t_x);


    TreeNode* search(T);
    TreeNode* searchRecursive(T, TreeNode*);
    TreeNode* searchRecursive(T);
    int size();
    int depth();
    void printInOrder(TreeNode*);
    void printPreOrder(TreeNode*);
    void printPostOrder(TreeNode*);
    TreeNode* getRoot();
    void printInOrder();
    void printPreOrder();
    void printPostOrder();
    bool isEmpty();
    TreeIterator begin();
    TreeIterator end();



private:
    TreeNode* m_root;
    size_t m_size;
};

template<typename T>
inline BSTree<T>::BSTree()
{
    m_root = nullptr;
    m_size = 0;
}

template<typename T>
struct BSTree<T>::TreeNode{
    TreeNode *m_parent, *m_left, *m_right;
    T m_key;

    TreeNode(TreeNode* t_parent, TreeNode* t_left, TreeNode* t_right, T t_key)
            : m_parent(t_parent), m_left(t_left), m_right(t_left), m_key(t_key)
    {
    }

    TreeNode& operator=(const TreeNode& rhs) {
        m_key = rhs.m_key;
        m_parent = rhs.m_parent;
        m_left = rhs.m_left;
        m_right = rhs.m_right;

        return *this;
    }
};

template<typename T>
class BSTree<T>::TreeIterator{
public:
    TreeNode* current;

    TreeIterator() = default;
    TreeIterator(TreeNode* node)
    {
        current = min_node(node);
    }

    TreeIterator& operator++()
    {
        if(current->m_right!=nullptr)
        {
            current = current->m_right;
            while(current->m_left!=nullptr)
            {
                current = current->m_left;
            }
            return *this;
        }

        TreeNode* y = current->m_parent;
        while(y!=nullptr && current == y->m_right)
        {
            current = y;
            y = y->m_parent;
        }
        current = y;
        return *this;
    }
    TreeIterator& operator--()
    {
        if(current->m_left!=nullptr)
        {
            current = current->left;
            while(current->m_right!=nullptr)
            {
                current = current->m_right;
            }
            return *this;
        }

        TreeNode* y = current->m_parent;
        while(y!=nullptr && current == y->m_left)
        {
            current = y;
            y = y->m_parent;
        }
        current = y;
        return *this;
    }
    bool operator==(const TreeIterator& ref)
    {
        return this->current == ref.current;
    }
    bool operator!=(const TreeIterator& ref)
    {
        return this->current != ref.current;
    }
    T& operator*()
    {
        return current->m_key;
    }

    TreeNode* min_node(TreeNode* node)
    {
        if(!node)
        {
            return nullptr;
        }else if(!node->m_left){
            return node;
        }else{
            return min_node(node->m_left);
        }
    }
};

template<typename T>
template<class U>
inline void BSTree<T>::insert(U&& t_x) {
    if (!isEmpty()) {
        TreeNode* p = m_root;
        TreeNode* prev = nullptr;
        while (p!=nullptr)
        {
            prev = p;
            if (p->m_key <= t_x) {
                p = p->m_right;
            }
            else if (p->m_key > t_x) {
                p = p->m_left;
            }
        }

        if (prev->m_key >= t_x) {
            TreeNode* nodeToInsert = new TreeNode(prev, nullptr, nullptr, std::forward<U>(t_x));
            prev->m_left = nodeToInsert;
            ++m_size;
        }
        else {
            TreeNode* nodeToInsert = new TreeNode(prev, nullptr, nullptr, std::forward<U>(t_x));
            prev->m_right = nodeToInsert;
            ++m_size;
        }
    }
    else {
        m_root = new TreeNode(nullptr, nullptr, nullptr, std::forward<U>(t_x));
        m_size++;
    }
}
template<typename T>
inline typename BSTree<T>::TreeNode* BSTree<T>::search(T t_key) {
    if (size())
    {
        TreeNode* p = m_root;
        while (p != nullptr)
        {
            if (p->m_key == t_key) {
                return p;
            }

            if (t_key > p->m_key) {
                p = p->m_right;
            }
            else if (t_key < p->m_key) {
                p = p->m_left;
            }
        }
        return nullptr;
    }
    else {
        return nullptr;
    }
}

template<typename T>
inline typename BSTree<T>::TreeNode* BSTree<T>::searchRecursive(T t_value, TreeNode* t_node) {
    if (size())
    {
        TreeNode* isFound = nullptr;
        if (!t_node || t_node->m_key == t_value)
            return t_node;

        isFound = searchRecursive(t_value, t_node->m_left);
        return (isFound) ? isFound : searchRecursive(t_value, t_node->m_right);
    }
    else {
        return nullptr;
    }
}
template<typename T>
inline typename BSTree<T>::TreeNode* BSTree<T>::searchRecursive(T t_value)
{
    searchRecursive(t_value, m_root);
}

template<typename T>
inline int BSTree<T>::size() {
    return m_size;
}
template<typename T>
inline bool BSTree<T>::isEmpty(){
    return m_root == nullptr;
}
template<typename T>
inline int BSTree<T>::depth() {
    if (size()) {
        Queue<TreeNode*, 10000> q;
        q.push(m_root);
        int depth = 0;
        while (true)
        {
            int howMany = q.size();
            if (howMany == 0)
            {
                return depth;
            }

            depth++;

            while (howMany > 0) {
                auto Node = q.pop();
                if (Node->m_left != nullptr) {
                    q.push(Node->m_left);
                }
                if (Node->m_right != nullptr) {
                    q.push(Node->m_right);
                }
                howMany--;
            }
        }
    }
    else {
        return 0;
    }

}
template<typename T>
inline void BSTree<T>::printInOrder(TreeNode* node) {
    if(node==nullptr){
        return;
    }

    printInOrder(node->m_left);
    std::cout << node->m_key << " ";
    printInOrder(node->m_right);
}
template<typename T>
inline void BSTree<T>::printPostOrder(TreeNode* node) {
    if(node==nullptr){
        return;
    }

    printPostOrder(node->m_left);
    printPostOrder(node->m_right);
    std::cout << node->m_key << " ";
}
template<typename T>
inline void BSTree<T>::printPreOrder(TreeNode* node) {
    if(node==nullptr){
        return;
    }

    std::cout << node->m_key << ' ';
    printPreOrder(node->m_left);
    printPreOrder(node->m_right);
}
template<typename T>
inline void BSTree<T>::printPreOrder() {
    printPreOrder(m_root);
}
template<typename T>
inline void BSTree<T>::printPostOrder() {
    printPostOrder(m_root);
}
template<typename T>
inline void BSTree<T>::printInOrder() {
    for(TreeIterator it = begin(); it!=end(); ++it)
    {
        std::cout << *it << ' ';
    }
}

template<typename T>
typename BSTree<T>::TreeIterator BSTree<T>::begin() {
    return BSTree<T>::TreeIterator(m_root);
}

template<typename T>
typename BSTree<T>::TreeIterator BSTree<T>::end() {
    return nullptr;
}



#endif
