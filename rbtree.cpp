#include "rbtree.h"


const int NODE_DIAMETR = 100, Y_DISTANCE = 200;


RBTree::RBTree()
{
    TNULL = new Node_rb;
    TNULL->color = BLACK;
    TNULL->left = nullptr;
    TNULL->right = nullptr;
    root = TNULL;
}

bool RBTree::searchTreeHelper(Node_rb* node, int key) {
    if(node == TNULL) {
        return false;
    }
    if (key == node->data) {
        return true;
    }

    if (key < node->data) {
        return searchTreeHelper(node->left, key);
    }
    return searchTreeHelper(node->right, key);
}

void RBTree::fixDelete(Node_rb* x) {
    Node_rb* s;
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            s = x->parent->right;
            if (s->color == RED) {
                // case 3.RED
                s->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                s = x->parent->right;
            }

            if (s->left->color == BLACK && s->right->color == BLACK) {
                // case 3.2
                s->color = RED;
                x = x->parent;
            } else {
                if (s->right->color == BLACK) {
                    // case 3.3
                    s->left->color = BLACK;
                    s->color = RED;
                    rightRotate(s);
                    s = x->parent->right;
                }

                // case 3.4
                s->color = x->parent->color;
                x->parent->color = BLACK;
                s->right->color = BLACK;
                leftRotate(x->parent);
                x = root;
            }
        } else {
            s = x->parent->left;
            if (s->color == RED) {
                // case 3.RED
                s->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                s = x->parent->left;
            }

            if (s->right->color == BLACK && s->right->color == BLACK) {
                // case 3.2
                s->color = RED;
                x = x->parent;
            } else {
                if (s->left->color == BLACK) {
                    // case 3.3
                    s->right->color = BLACK;
                    s->color = RED;
                    leftRotate(s);
                    s = x->parent->left;
                }

                // case 3.4
                s->color = x->parent->color;
                x->parent->color = BLACK;
                s->left->color = BLACK;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}


void RBTree::rbTransplant(Node_rb* u, Node_rb* v){
    if (u->parent == NULL) {
        root = v;
    } else if (u == u->parent->left){
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

bool RBTree::searchTree(int k) {
    return searchTreeHelper(this->root, k);
}


Node_rb* RBTree::minimum(Node_rb* node) {
    while (node->left != TNULL) {
        node = node->left;
    }
    return node;
}

Node_rb* RBTree::maximum(Node_rb* node) {
    while (node->right != TNULL) {
        node = node->right;
    }
    return node;
}

void RBTree::deleteNodeHelper(Node_rb* node, int key) {
    // find the node containing key
    Node_rb* z = TNULL;
    Node_rb* x, *y;
    while (node != TNULL){
        if (node->data == key) {
            z = node;
        }

        if (node->data <= key) {
            node = node->right;
        } else {
            node = node->left;
        }
    }

    if (z == TNULL) {
        return;
    }

    y = z;
    int y_original_color = y->color;
    if (z->left == TNULL) {
        x = z->right;
        rbTransplant(z, z->right);
    } else if (z->right == TNULL) {
        x = z->left;
        rbTransplant(z, z->left);
    } else {
        y = minimum(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            rbTransplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        rbTransplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    delete z;
    if (y_original_color == BLACK){
        fixDelete(x);
    }
}

// fix the red-black tree
void RBTree::fixInsert(Node_rb* k){
    Node_rb* u;
    while (k->parent->color == RED) {
        if (k->parent == k->parent->parent->right) {
            u = k->parent->parent->left; // uncle
            if (u->color == RED) {
                // case 3.RED
                u->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->left) {
                    // case 3.2.2
                    k = k->parent;
                    rightRotate(k);
                }
                // case 3.2.RED
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                leftRotate(k->parent->parent);
            }
        } else {
            u = k->parent->parent->right; // uncle

            if (u->color == RED) {
                // mirror case 3.RED
                u->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->right) {
                    // mirror case 3.2.2
                    k = k->parent;
                    leftRotate(k);
                }
                // mirror case 3.2.RED
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                rightRotate(k->parent->parent);
            }
        }
        if (k == root) {
            break;
        }
    }
    root->color = BLACK;
}


void RBTree::leftRotate(Node_rb* x) {
    Node_rb* y = x->right;
    x->right = y->left;
    if (y->left != TNULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
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
void RBTree::rightRotate(Node_rb* x) {
    Node_rb* y = x->left;
    x->left = y->right;
    if (y->right != TNULL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        this->root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

// insert the key to the tree in its appropriate position
// and fix the tree
void RBTree::insert(int key) {
    if(this->searchTree(key)) return;
    // Ordinary Binary Search Insertion
    Node_rb* node = new Node_rb;
    node->parent = NULL;
    node->data = key;
    node->left = TNULL;
    node->right = TNULL;
    node->color = RED; // new node must be red

    Node_rb* y = NULL;
    Node_rb* x = this->root;

    while (x != TNULL) {
        y = x;
        if (node->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    // y is parent of x
    node->parent = y;
    if (y == NULL) {
        root = node;
    } else if (node->data < y->data) {
        y->left = node;
    } else {
        y->right = node;
    }

    // if new node is a root node, simply return
    if (node->parent == NULL){
        node->color = BLACK;
        return;
    }

    // if the grandparent is TNULL, simply return
    if (node->parent->parent == NULL) {
        return;
    }

    // Fix the tree
    fixInsert(node);
}

Node_rb* RBTree::getRoot(){
    return this->root;
}



void RBTree::treeFilling(Node_rb*&x, int dl) {
    if(x == NULL || x == TNULL) return;

    if(x->left) x->left->x -= dl;
    if(x->right) x->right->x -=dl;

    treeFilling(x->left, dl);
    treeFilling(x->right, dl);

}

int RBTree::max_right(Node_rb*x, int mx) {
    if(x == NULL || x == TNULL) return mx;
    mx = fmax(x->x + NODE_DIAMETR,max_right(x->right,mx));
    mx = fmax(x->x + NODE_DIAMETR,max_right(x->left,mx));
    return mx;
}

int RBTree::max_left(Node_rb*x, int mx) {
    if(x == NULL || x == TNULL) return mx;
    mx = fmin(x->x,max_left(x->right,mx));
    mx = fmin(x->x,max_left(x->left,mx));
    return mx;
}

void RBTree::Stand(Node_rb*&x) {
    if(x == NULL || x == TNULL) return;

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

void RBTree::fix_position(Node_rb*&x) {
    if(x == NULL || x == TNULL) return;
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

void RBTree::Standing(Node_rb* &x) {
    fix_position(x);
    Stand(x);
}

void RBTree::paintTree(Node_rb* x, QGraphicsScene* &scene) {
    if(!x || x == TNULL) return;
    QGraphicsEllipseItem *ellipse = new QGraphicsEllipseItem(x->x, x->y,NODE_DIAMETR, NODE_DIAMETR);
    QPen*pen = new QPen(Qt::black);
    if(x->color == RED) {
        pen->setColor(Qt::red);
    }
    ellipse->setPen(*pen);
    ellipse->setBrush(QBrush(Qt::white));
    QGraphicsTextItem* text= new QGraphicsTextItem(QString::number(x->data));
    text->setPos(ellipse->boundingRect().center() - text->boundingRect().center());
    scene->addItem(ellipse);
    scene->addItem(text);
    if(x->parent) {
        QGraphicsLineItem *line = new QGraphicsLineItem(x->parent->x + NODE_DIAMETR/2,x->parent->y + NODE_DIAMETR/2, x->x + NODE_DIAMETR/2, x->y + NODE_DIAMETR/2);
        line->setZValue(-1);
        scene->addItem(line);
    }
    paintTree(x->left, scene);
    paintTree(x->right, scene);

}


void RBTree::display(QGraphicsScene* scene, Node_rb* root)
{
    scene->clear();
    Standing(root);
    paintTree(root,scene);

}

void Node_rb::setPos(int x,int y) {
    this->x = x;
    this->y = y;
}

void RBTree::click_delete(Node_rb* cur, int x,int y) {
    if(!cur && cur != TNULL) return;
    if(x > cur->x && x < cur->x + NODE_DIAMETR && y > cur->y && y < cur->y + NODE_DIAMETR) {
        this->deleteNode(cur->data);
    }
    else {
        click_delete(cur->left,x,y);
        click_delete(cur->right,x,y);
    }
}

void RBTree::deleteNode(int data) {
    deleteNodeHelper(this->root, data);
}

