#include "avltree.h"
#include "qfontmetrics.h"
#include "qgraphicsitem.h"
#include "qgraphicsscene.h"

const int NODE_DIAMETR = 100, Y_DISTANCE = 200;

Node::Node(int value) {
    this->value = value;
    this->height = 1;
    this->left = nullptr;
    this->right = nullptr;
    x = 0;
    y = 0;
    parent = NULL;
}

AVLTree::AVLTree() {
    root = nullptr;
}

AVLTree::~AVLTree() {
    deleteTree(root);
}

int getHeight(Node* node) {
      if (node == nullptr) {
          return 0;
      }
      return node->height;
  }

  int getBalance(Node* node) {
      if (node == nullptr) {
          return 0;
      }
      return getHeight(node->left) - getHeight(node->right);
  }

void AVLTree::fixheight(Node* p)
{
    unsigned char hl = getHeight(p->left);
    unsigned char hr = getHeight(p->right);
    p->height = (hl>hr?hl:hr)+1;
}

void AVLTree::deleteTree(Node* node) {
    if (node != nullptr) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

void AVLTree::insert(int value) {
    insert(root, NULL, value);
}

void AVLTree::insert(Node* &node,Node*prev, int value) {
    if (node == nullptr) {
        node = new Node(value);
        node->parent = prev;
    } else if (value < node->value) {
        insert(node->left,node, value);
    } else if (value > node->value) {
        insert(node->right, node, value);
    }
    node = balance(node);
}

void AVLTree::remove(int value) {
    remove(root, value);
}

void AVLTree::remove(Node* &node, int value) {
    if (node == nullptr) {
        return;
    }
    if (value < node->value) {
        remove(node->left, value);
    } else if (value > node->value) {
        remove(node->right, value);
    } else {
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            node = nullptr;
        } else if (node->left == nullptr) {
            Node* temp = node;
            node = node->right;
            node->parent = temp->parent;
            delete temp;
        } else if (node->right == nullptr) {
            Node* temp = node;
            node = node->left;
            node->parent = temp->parent;
            delete temp;
        } else {
            Node* temp = node->left;
            while (temp->right != nullptr) {
                temp = temp->right;
            }
            node->value = temp->value;
            remove(node->left, temp->value);
        }
    }
    node = balance(node);
}

bool AVLTree::contains(int value) {
    return contains(root, value);
}

bool AVLTree::contains(Node* node, int value) {
    if (node == nullptr) {
        return false;
    } else if (value < node->value) {
        return contains(node->left, value);
    } else if (value > node->value) {
        return contains(node->right, value);
    } else {
        return true;
    }
}

Node* AVLTree::rotateLeft(Node* q) {
    Node* p = q->right;
    p->parent = q->parent;
    q->parent = p;

    q->right = p->left;
    p->left = q;
    if(q->right != NULL)
        q->right->parent = q;

    fixheight(q);
    fixheight(p);
    return p;
}



Node* AVLTree::rotateRight(Node* p) {

    Node* q = p->left;
    q->parent = p->parent;
    p->parent = q;

    p->left = q->right;
    q->right = p;
    if(p->left != NULL)
        p->left->parent = p;

    fixheight(p);
    fixheight(q);
    return q;
}

int AVLTree::bfactor(Node* p)
{
    return getHeight(p->right)-getHeight(p->left);
}


Node* AVLTree::balance(Node* p) {
    if(!p) return NULL;
    fixheight(p);
    auto oo = bfactor(p);
    if( bfactor(p)==2 )
    {
        if( bfactor(p->right) < 0 ) {
            p->right = rotateRight(p->right);
        }

        return rotateLeft(p);
    }
    if( bfactor(p)==-2 )
    {
        if( bfactor(p->left) > 0  ) {
            p->left = rotateLeft(p->left);
        }
        return rotateRight(p);
    }
    return p;
}

void Node::setPos(int x,int y) {
    this->x = x;
    this->y = y;
}


void treeFilling(Node*&x, int dl) {
    if(x == NULL) return;

    if(x->left) x->left->x -= dl;
    if(x->right) x->right->x -=dl;

    treeFilling(x->left, dl);
    treeFilling(x->right, dl);

}

int max_right(Node*x, int mx) {
    if(x == NULL) return mx;
    mx = fmax(x->x + NODE_DIAMETR,max_right(x->right,mx));
    mx = fmax(x->x + NODE_DIAMETR,max_right(x->left,mx));
    return mx;
}

int max_left(Node*x, int mx) {
    if(x == NULL) return mx;
    mx = fmin(x->x,max_left(x->right,mx));
    mx = fmin(x->x,max_left(x->left,mx));
    return mx;
}

void Stand(Node*&x) {
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

void fix_position(Node*&x) {
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

void Standing(Node* &x) {
    fix_position(x);
    Stand(x);
}

void paintTree(Node* x, QGraphicsScene* &scene) {
    if(!x) return;
    QGraphicsEllipseItem *ellipse = new QGraphicsEllipseItem(x->x, x->y,NODE_DIAMETR, NODE_DIAMETR);
    ellipse->setBrush(QBrush(Qt::white));
    QGraphicsTextItem* text= new QGraphicsTextItem(QString::number(x->value));
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


void AVLTree::display(QGraphicsScene* scene, Node* root)
{
    scene->clear();
    Standing(root);
    paintTree(root,scene);

}


Node* AVLTree::getRoot() const {
   return root;
}

void AVLTree::click_delete(Node* cur, int x,int y) {
    if(!cur) return;
    if(x > cur->x && x < cur->x + NODE_DIAMETR && y > cur->y && y < cur->y + NODE_DIAMETR) {
        this->remove(cur->value);
    }
    else {
        click_delete(cur->left,x,y);
        click_delete(cur->right,x,y);
    }
}
