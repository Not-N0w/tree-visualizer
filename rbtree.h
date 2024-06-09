#ifndef RBTREE_H
#define RBTREE_H

#include "qgraphicsitem.h"
#include "qgraphicsscene.h"
#include <iostream>

enum Color {RED, BLACK};

struct Node_rb
{
    int data;
    Color color;
    Node_rb* left;
    Node_rb* right;
    Node_rb* parent;

    int x, y;

    void setPos(int x,int y);

};

class RBTree {
private:

    Node_rb* root;
    Node_rb* TNULL;


    bool searchTreeHelper(Node_rb* node, int key);

    void fixDelete(Node_rb* x);

    void rbTransplant(Node_rb* u, Node_rb* v);
    void deleteNodeHelper(Node_rb* node, int key);
    void fixInsert(Node_rb* k);
    void paintTree(Node_rb* x, QGraphicsScene* &scene);
    void treeFilling(Node_rb*&x, int dl);
    int max_left(Node_rb*x, int mx);
    int max_right(Node_rb*x, int mx);
    void Stand(Node_rb*&x);
    void fix_position(Node_rb*&x);
    void Standing(Node_rb* &x);






public:
    RBTree();

    bool searchTree(int k);

    void click_delete(Node_rb* cur, int x,int y);
    void display(QGraphicsScene* scene, Node_rb* root);


    Node_rb* minimum(Node_rb* node);

    Node_rb* maximum(Node_rb* node);
    void leftRotate(Node_rb* x);
    void rightRotate(Node_rb* x);
    void insert(int key);

    Node_rb* getRoot();

    // delete the node from the tree
    void deleteNode(int data);

};

#endif
