#include "treap.h"
#include "qgraphicsitem.h"
#include "qgraphicsscene.h"

const int NODE_DIAMETR = 100, Y_DISTANCE = 200;


Node_t * Treap::searchTreeHelper(Node_t * node, int key) {
    if (node == nullptr || key == node->data) {
        return node;
    }

    if (key < node->data) {
        return searchTreeHelper(node->left, key);
    }
    return searchTreeHelper(node->right, key);
}




// rotate left at node x
void Treap::leftRotate(Node_t * x) {
    Node_t * y = x->right;
    x->right = y->left;
    if (y->left != nullptr) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        this->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

// rotate right at node x
void Treap::rightRotate(Node_t * x) {
    Node_t * y = x->left;
    x->left = y->right;
    if (y->right != nullptr) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        this->root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

// we move the node up until its priority is greater than
// or equal the parent's priority
void Treap::moveUp(Node_t * x) {
    if (x->parent == nullptr) {
        return;
    }
    if (x->parent != nullptr && x->priority >= x->parent->priority) {
        return;
    }

    if (x == x->parent->left) {
        rightRotate(x->parent);
    } else {
        leftRotate(x->parent);
    }

    // recursively move the x up
    moveUp(x);
}

// delete key k
void Treap::deleteNodeHelper(Node_t * node, int k) {
    // find k
    Node_t * x = nullptr;
    while (node != nullptr) {
        if (node->data == k) {
            x = node;
            break;
        }

        if (node->data <= k) {
            node = node->right;
        } else {
            node = node->left;
        }
    }

    if (x == nullptr) {
        return;
    }

    // move down x
    moveDown(x);

    // in this point x is in the leaf node
    // delete x
    if (x == x->parent->left) {
        x->parent->left = nullptr;
    } else {
        x->parent->right = nullptr;
    }
    delete x;
    x = nullptr;
}

// move down x to the leaf of the tree
void Treap::moveDown(Node_t * x) {
    if (x->left == nullptr && x->right == nullptr) {
        return;
    }

    if (x->left != nullptr && x->right != nullptr) {
        if (x->left->priority < x->right->priority) {
            rightRotate(x);
        } else {
            leftRotate(x);
        }
    } else if (x->left != nullptr) {
        rightRotate(x);
    } else {
        leftRotate(x);
    }

    moveDown(x);
}
Treap::Treap() {
    root = nullptr;
}

Node_t * Treap::searchTree(int k) {
    return searchTreeHelper(this->root, k);
}

// find the node with the minimum key
Node_t * Treap::minimum(Node_t * node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

// find the node with the maximum key
Node_t * Treap::maximum(Node_t * node) {
    while (node->right != nullptr) {
        node = node->right;
    }
    return node;
}

// find the successor of a given node

// insert the key to the tree in its appropriate position
void Treap::insert(int key, float priority) {
    Node_t * node = new Node_t;
    node->parent = nullptr;
    node->left = nullptr;
    node->right = nullptr;
    node->data = key;
    node->priority = priority;
    Node_t * y = nullptr;
    Node_t * x = this->root;

    while (x != nullptr) {
        y = x;
        if (node->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    // y is parent of x
    node->parent = y;
    if (y == nullptr) {
        root = node;
    } else if (node->data < y->data) {
        y->left = node;
    } else {
        y->right = node;
    }

    // rotate the tree to fix the priorities.
    if (node->parent != nullptr) {
        moveUp(node);
    }
}

// split the tree into two trees
void Treap::split(int x, Treap* t1, Treap* t2) {
    // insert a dummy node with lowest priority
    this->insert(x, -99);

    // this node is in the root node
    t1->root = this->root->left;
    t2->root = this->root->right;

    this->root->left = nullptr;
    this->root->right = nullptr;
    delete this->root;
    this->root = nullptr;
}

// merge trees t1 and t2
void Treap::merge(Treap t1, Treap t2) {
    // find the largest node in t1
    Node_t * largest = t1.maximum(t1.root);
    // find the smallest node in t2
    Node_t * smallest = t2.minimum(t2.root);

    // create a dummy node
    Node_t * newRoot = new Node_t();
    newRoot->data = (largest->data + smallest->data) / 2;
    newRoot->left = t1.root;
    newRoot->right = t2.root;
    newRoot->parent = nullptr;
    newRoot->priority = 99;

    // move down the dummy node to the leaf node
    moveDown(newRoot);

    Node_t * currPtr = newRoot;
    while(currPtr->parent != nullptr) {
        currPtr = currPtr->parent;
    }

    this->root = currPtr;

    if (newRoot == newRoot->parent->left) {
        newRoot->parent->left = nullptr;
    } else {
        newRoot->parent->right = nullptr;
    }

    // delete the dummy node
    delete(newRoot);
    newRoot = nullptr;

}

Node_t * Treap::getRoot(){
    return this->root;
}

// delete the node from the tree
void Treap::deleteNode(int data) {
    deleteNodeHelper(this->root, data);
}



void Node_t::setPos(int x,int y) {
    this->x = x;
    this->y = y;
}




void treeFilling(Node_t*&x, int dl) {
    if(x == NULL) return;

    if(x->left) x->left->x -= dl;
    if(x->right) x->right->x -=dl;

    treeFilling(x->left, dl);
    treeFilling(x->right, dl);

}

int max_right(Node_t*x, int mx) {
    if(x == NULL) return mx;
    mx = fmax(x->x + NODE_DIAMETR,max_right(x->right,mx));
    mx = fmax(x->x + NODE_DIAMETR,max_right(x->left,mx));
    return mx;
}

int max_left(Node_t*x, int mx) {
    if(x == NULL) return mx;
    mx = fmin(x->x,max_left(x->right,mx));
    mx = fmin(x->x,max_left(x->left,mx));
    return mx;
}

void Stand(Node_t*&x) {
    if(x == NULL) return;

    Stand(x->left);
    Stand(x->right);
    int mr =max_right(x->left, -1e6), ml = max_left(x->right, 1e6);

    int delta = (mr == -1e6 || ml == 1e6 ? 0 : ml - mr);
    if( delta < 0) {
        if(x->left)
            x->left->x -= (abs(delta)/2 + 25);
        if(x->right)
            x->right->x += (abs(delta)/2 + 25);

        treeFilling(x->left, (abs(delta)/2 + 25));
        treeFilling(x->right, -(abs(delta)/2 + 25));
    }

}

void fix_position(Node_t*&x) {
    if(x == NULL) return;
    if(x->parent == NULL) {
        x->x = 300;
        x->y = 100;
    }
    else {
        if(x->parent->left == x) {
            x->setPos(x->parent->x - NODE_DIAMETR, x->parent->y + Y_DISTANCE );
        }
        else {
            x->setPos(x->parent->x + NODE_DIAMETR, x->parent->y + Y_DISTANCE);

        }
    }
    fix_position(x->left);
    fix_position(x->right);
}

void Standing(Node_t* &x) {
    fix_position(x);
    Stand(x);
}

void paintTree(Node_t* x, QGraphicsScene* &scene) {
    if(!x) return;
    QGraphicsEllipseItem *ellipse = new QGraphicsEllipseItem(x->x, x->y,NODE_DIAMETR, NODE_DIAMETR);
    ellipse->setBrush(QBrush(Qt::white));
    QGraphicsTextItem* text= new QGraphicsTextItem(QString::number(x->data));
    text->setDefaultTextColor(Qt::black);
    text->setZValue(100);
    text->setPos(ellipse->boundingRect().center() - text->boundingRect().center() + QPointF(0,-8));

    QGraphicsTextItem* textPrior= new QGraphicsTextItem(QString::number(x->priority));
    textPrior->setPos(ellipse->boundingRect().center() - textPrior->boundingRect().center() + QPointF(0,8));
    textPrior->setDefaultTextColor(Qt::black);
    textPrior->setZValue(100);
    QFont f = text->font();
    f.setBold(1);
    text->setFont(f);


    scene->addItem(ellipse);
    scene->addItem(text);

    scene->addItem(textPrior);
    if(x->parent) {
        QGraphicsLineItem *line = new QGraphicsLineItem(x->parent->x + NODE_DIAMETR/2,x->parent->y + NODE_DIAMETR/2, x->x + NODE_DIAMETR/2, x->y + NODE_DIAMETR/2);
        line->setZValue(-1);
        scene->addItem(line);
    }
    paintTree(x->left, scene);
    paintTree(x->right, scene);

}


void Treap::display(QGraphicsScene* scene, Node_t* root)
{
    scene->clear();
    Standing(root);
    paintTree(root,scene);

}

void Treap::click_delete(Node_t* cur, int x,int y) {
    if(!cur) return;
    if(x > cur->x && x < cur->x + NODE_DIAMETR && y > cur->y && y < cur->y + NODE_DIAMETR) {
        this->deleteNode(cur->data);
    }
    else {
        click_delete(cur->left,x,y);
        click_delete(cur->right,x,y);
    }
}
bool Treap::searchPrior(Node_t* x, int p) {
    if(!x) return 0;
    if(x->priority == p) return 1;
    bool i = searchPrior(x->left, p);
    if(i) return 1;
    return searchPrior(x->right, p);
}
