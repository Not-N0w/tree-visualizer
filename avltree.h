#ifndef AVLTREE_H
#define AVLTREE_H


#include "qgraphicsscene.h"
#include <iostream>

class Node {
public:
    int x,y;
    int value;
    int height;
    Node* left;
    Node* right;
    Node* parent;
    void setPos(int,int);
    Node(int value);
};

class AVLTree {
public:
    AVLTree();
    ~AVLTree();
    void insert(int value);
    void remove(int value);
    bool contains(int value);
    void display(QGraphicsScene* scene, Node* root);
    Node* getRoot() const;
    void click_delete(Node* cur, int x,int y);


private:
    Node* root;

    void fixheight(Node* p);
    int bfactor(Node* p);
    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    Node* balance(Node* node);
    void insert(Node* &node,Node*, int value);
    void remove(Node* &node, int value);
    bool contains(Node* node, int value);
    void deleteTree(Node* node);
};

#endif // AVLTREE_H
