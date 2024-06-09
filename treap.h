#ifndef TREAP_H
#define TREAP_H

#include "qgraphicsscene.h"
#include <iostream>

struct Node_t {
    int data; // holds the key
    int priority; // priority of the node
    Node_t *parent; // pointer to the parent
    Node_t *left; // pointer to left child
    Node_t *right; // pointer to right child
    int x,y;
    void setPos(int x,int y);
};

class Treap {
private:
    Node_t * root;


    Node_t * searchTreeHelper(Node_t * node, int key);
    void leftRotate(Node_t * x);
    void rightRotate(Node_t * x);
    void moveUp(Node_t * x);
    void deleteNodeHelper(Node_t * node, int k);
    void moveDown(Node_t * x);
public:
    Treap();

    void display(QGraphicsScene* scene, Node_t* root);
    void click_delete(Node_t* cur, int x,int y);
    Node_t * searchTree(int k);
    bool searchPrior(Node_t*,int x);
    Node_t * minimum(Node_t * node);
    Node_t * maximum(Node_t * node);
    void insert(int key, float priority);
    void split(int x, Treap* t1, Treap* t2);
    void merge(Treap t1, Treap t2);

    Node_t * getRoot();
    void deleteNode(int data);
};


#endif // TREAP_H
