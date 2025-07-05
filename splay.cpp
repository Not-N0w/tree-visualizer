#include "splay.h"
#include "qgraphicsitem.h"
#include "qgraphicsscene.h"

const int NODE_DIAMETR = 100, Y_DISTANCE = 200;


Splay::Splay()
{
    root = NULL;
}
void Splay::deleteNode(int data) {
    deleteNodeHelper(this->root, data);
}
Node_s* Splay::getRoot(){
    return this->root;
}
void Splay::insert(int key) {
    // normal BST insert
    Node_s* node = new Node_s;
    node->parent = nullptr;
    node->left = nullptr;
    node->right = nullptr;
    node->data = key;
    Node_s* y = nullptr;
    Node_s* x = this->root;

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

    // splay the node
    splay(node);
}
Node_s* Splay::maximum(Node_s* node) {
    while (node->right != nullptr) {
        node = node->right;
    }
    return node;
}
Node_s* Splay::minimum(Node_s* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}
Node_s* Splay::searchTree(int k) {
    Node_s* x = searchTreeHelper(this->root, k);
    if (x) {
        splay(x);
    }
    return x;
}
void Splay::split(Node_s* &x, Node_s* &s, Node_s* &t) {
    splay(x);
    if (x->right) {
        t = x->right;
        t->parent = nullptr;
    } else {
        t = nullptr;
    }
    s = x;
    s->right = nullptr;
    x = nullptr;
}
Node_s* Splay::join(Node_s* s, Node_s* t){
        if (!s) {
            return t;
        }

        if (!t) {
            return s;
        }
        Node_s* x = maximum(s);
        splay(x);
        x->right = t;
        t->parent = x;
        return x;
    }
void Splay::leftRotate(Node_s* x) {
    Node_s* y = x->right;
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
void Splay::rightRotate(Node_s* x) {
    Node_s* y = x->left;
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

// splaying
void Splay::splay(Node_s* x) {
    while (x->parent) {
        if (!x->parent->parent) {
            if (x == x->parent->left) {
                // zig rotation
                rightRotate(x->parent);
            } else {
                // zag rotation
                leftRotate(x->parent);
            }
        } else if (x == x->parent->left && x->parent == x->parent->parent->left) {
            // zig-zig rotation
            rightRotate(x->parent->parent);
            rightRotate(x->parent);
        } else if (x == x->parent->right && x->parent == x->parent->parent->right) {
            // zag-zag rotation
            leftRotate(x->parent->parent);
            leftRotate(x->parent);
        } else if (x == x->parent->right && x->parent == x->parent->parent->left) {
            // zig-zag rotation
            leftRotate(x->parent);
            rightRotate(x->parent);
        } else {
            // zag-zig rotation
            rightRotate(x->parent);
            leftRotate(x->parent);
        }
    }
}void Splay::deleteNodeHelper(Node_s* node, int key) {
    Node_s* x = nullptr;
    Node_s* t, *s;
    while (node != nullptr){
        if (node->data == key) {
            x = node;
        }

        if (node->data <= key) {
            node = node->right;
        } else {
            node = node->left;
        }
    }

    if (x == nullptr) {
        return;
    }
    split(x, s, t); // split the tree
    if (s->left){ // remove x
        s->left->parent = nullptr;
    }
    root = join(s->left, t);
    delete(s);
    s = nullptr;
}
Node_s *Splay::searchTreeHelper(Node_s* node, int key) {
        if (node == nullptr || key == node->data) {
            return node;
        }

        if (key < node->data) {
            return searchTreeHelper(node->left, key);
        }
        return searchTreeHelper(node->right, key);
    }


void Node_s::setPos(int x,int y) {
    this->x = x;
    this->y = y;
}




void treeFilling(Node_s*&x, int dl) {
    if(x == NULL) return;

    if(x->left) x->left->x -= dl;
    if(x->right) x->right->x -=dl;

    treeFilling(x->left, dl);
    treeFilling(x->right, dl);

}

int max_right(Node_s*x, int mx) {
    if(x == NULL) return mx;
    mx = fmax(x->x + NODE_DIAMETR,max_right(x->right,mx));
    mx = fmax(x->x + NODE_DIAMETR,max_right(x->left,mx));
    return mx;
}

int max_left(Node_s*x, int mx) {
    if(x == NULL) return mx;
    mx = fmin(x->x,max_left(x->right,mx));
    mx = fmin(x->x,max_left(x->left,mx));
    return mx;
}

void Stand(Node_s*&x) {
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

void fix_position(Node_s*&x) {
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

void Standing(Node_s* &x) {
    fix_position(x);
    Stand(x);
}

void paintTree(Node_s* x, QGraphicsScene* &scene) {
    if(!x) return;
    QGraphicsEllipseItem *ellipse = new QGraphicsEllipseItem(x->x, x->y,NODE_DIAMETR, NODE_DIAMETR);
    ellipse->setBrush(QBrush(Qt::white));
    QGraphicsTextItem* text= new QGraphicsTextItem(QString::number(x->data));
    text->setPos(ellipse->boundingRect().center() - text->boundingRect().center());
    text->setDefaultTextColor(Qt::black);
    text->setZValue(100);
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


void Splay::display(QGraphicsScene* scene, Node_s* root)
{
    scene->clear();
    Standing(root);
    paintTree(root,scene);

}

void Splay::click_delete(Node_s* cur, int x,int y) {
    if(!cur) return;
    if(x > cur->x && x < cur->x + NODE_DIAMETR && y > cur->y && y < cur->y + NODE_DIAMETR) {
        this->deleteNode(cur->data);
    }
    else {
        click_delete(cur->left,x,y);
        click_delete(cur->right,x,y);
    }
}
