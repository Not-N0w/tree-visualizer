#ifndef SPLAY_H
#define SPLAY_H

#include "qgraphicsscene.h"
#include <iostream>

struct Node_s {
    int data; // holds the key
    Node_s *parent; // pointer to the parent
    Node_s *left; // pointer to left child
    Node_s *right; // pointer to right child
    int x, y;
    void setPos(int,int);


};

class Splay {
private:
    Node_s *root;


    Node_s *searchTreeHelper(Node_s* node, int key);

    void deleteNodeHelper(Node_s* node, int key);


    // rotate left at node x
    void leftRotate(Node_s* x) ;
    void rightRotate(Node_s* x) ;


    // splaying
    void splay(Node_s* x) ;

    // joins two trees s and t
    Node_s* join(Node_s* s, Node_s* t);

    // splits the tree into s and t
    void split(Node_s* &x, Node_s* &s, Node_s* &t);
public:
    Splay();
    void click_delete(Node_s* cur, int x,int y);


    Node_s* searchTree(int k);

    // find the node with the minimum key
    Node_s* minimum(Node_s* node);

    // find the node with the maximum key
    Node_s* maximum(Node_s* node);

        // insert the key to the tree in its appropriate position
    void insert(int key);
    Node_s* getRoot();
    // delete the node from the tree
    void deleteNode(int data) ;
    void display(QGraphicsScene* scene, Node_s* root);



};

#endif // SPLAY_H
