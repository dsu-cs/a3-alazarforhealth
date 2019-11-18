#pragma once

// include this library to use NULL, otherwise use nullptr instead
#include <cstddef>
#include <iostream>
#include<string>
#include "node.hpp"

template<class T>
class BST{
public:
    // Constructor for the BST class, creates an empty tree
    BST(void);
    // Destructor for the BST class, destroys the tree
    ~BST(void);
    // Inserts data into the tree
    // param: The data to be inserted into the tree
    void insert(T);
    // Removes data from the tree
    // param: The data to be removed from the tree
    void remove(T);
    // Performs an inorder traversal
    // returns: pointer to a vector containing the tree traversal
    std::vector<T> *inorder(void);
    // Performs an postorder traversal
    // returns: pointer to a vector containing the tree traversal
    std::vector<T> *postorder(void);
    // Performs an preorder traversal
    // returns: pointer to a vector containing the tree traversal
    std::vector<T> *preorder(void);
    // Searches the tree for a given value
    // param: the data to search for
    // returns: a pointer to the node containing the data or NULL if the data
    //          was not found
    Node<T> *search(T);
    // Gets the current number of nodes in the tree
    // returns: the number of nodes in the tree
    int get_size(void);
private:
    // the root node of the tree
    Node<T> *root;
    // the number of nodes in the tree
    int node_count;

    void inhelper(std::vector<T> * vec, Node<T>* node);

    void prehelper(std::vector<T> * vec, Node<T>* node);

    void posthelper(std::vector<T> * vec, Node<T>* node);

    Node<T> *iHelper(T val, Node<T>* node);

    Node<T> *sHelper(T val, Node<T>* node);

    Node<T> *rHelper(T val, Node<T>* node);


};

template<class T>
BST<T>::BST()
{
    root = NULL;
    node_count = 0;
}

template<class T>
BST<T>::~BST()
{
    root = NULL;
    while(root != NULL)
    {
        remove(root->get_data());
    }
}

template<class T>
 std::vector<T> * BST<T>::inorder()
{
    std::vector<T> *vec = new std::vector<T>;

    inhelper(vec, root);
    
    return vec;
}

template<class T>
void BST<T>::inhelper(std::vector<T> * vec, Node<T>* node){
    if(node == NULL){
        return ;
    }
    else{
        inhelper(vec, node->get_left());
        vec-> push_back(node->get_data());
        inhelper(vec, node->get_right());
    }
}

template<class T>
 std::vector<T> * BST<T>::preorder()
{
    std::vector<T> *vec = new std::vector<T>;
    prehelper(vec, root);
    return vec;
}

template<class T>
void BST<T>::prehelper(std::vector<T> * vec, Node<T>* node){
    if(node == NULL){
        return ;
    }
    else{
        vec-> push_back(node->get_data());
        prehelper(vec, node->get_left());
        prehelper(vec, node->get_right());
    }
}

template<class T>
 std::vector<T> * BST<T>::postorder()
{
    std::vector<T> *vec = new std::vector<T>;
    posthelper(vec, root);
    return vec;
}


template<class T>
void BST<T>::posthelper(std::vector<T> * vec, Node<T>* node){
        if(node == NULL){
        return ;
    }
    else{
        posthelper(vec, node->get_left());
        posthelper(vec, node->get_right());
        vec-> push_back(node->get_data());
    }
}

template<class T>
void BST<T>::insert(T new_data)
{
    if(node_count == 0){
       root = iHelper(new_data, root); 
    }
    else{
      iHelper(new_data, root);  
    }
    ++node_count;
}

template<class T>
Node<T> *BST<T>::iHelper(T val, Node<T>* node)
{
    if(node == NULL){
        return new Node<T>(val);
    }
    else if ( val > node->get_data()) {
         node->set_right(iHelper(val, node->get_right()));
    }
    else {
         node->set_left(iHelper(val, node->get_left()));
    }

    return node;
}


template<class T>
Node<T> *BST<T>::search(T val)
{
    return sHelper(val, root);
}

template<class T>
Node<T> *BST<T>::sHelper(T val, Node<T>* node)
{
    if(node == NULL || node->get_data() == val){
        return node;
    }
    else if ( val > node->get_data()){
        sHelper(val, node->get_right()); 
    }
    else{
        sHelper(val, node->get_left());
    }
}

template<class T>
void BST<T>::remove(T val)
{
    root = rHelper(val, root);
    --node_count;
}

template<class T>
Node<T> * BST<T>::rHelper(T val, Node<T>* node)
{
    if(node != NULL){
        if( node->get_data() == val){
            if(node->get_left() == NULL && node->get_right() == NULL){
                delete node;
                return NULL;
            }
            else if(node->get_right() == NULL){
                Node<T>* left = node->get_left();
                delete node;
                return left;
            }
            else if(node->get_left() == NULL){
                Node<T>* right = node->get_right();
                delete node;
                return right;
            }
            else{
                Node<T>* temp = node->get_right();
                while(temp->get_left() != NULL){
                    temp = temp->get_left();
                }
                T tempval = temp->get_data();
                node->set_data(tempval);
                node->set_right(rHelper(temp->get_data(), root->get_right())); 
                }
        }
        else if ( val > node->get_data()){
            node->set_right(rHelper(val, node->get_right()));
        }
        else{
            node->set_left(rHelper(val, node->get_left()));
        }
    }

    return node;
}

    
  
    

template<class T>
int BST<T>::get_size()
{
    return node_count;
}