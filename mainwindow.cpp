#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "splay.h"
#include "treap.h"
#include <QIntValidator>
#include <QTimer>

QVector<QPushButton*> btns;

QGraphicsScene *avl_scene;
AVLTree* avl_tree;

QGraphicsScene *rb_scene;
RBTree* rb_tree;

QGraphicsScene *s_scene;
Splay* s_tree;

QGraphicsScene *t_scene;
Treap* t_tree;

bool CLICK_DELETE = 0;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    btns = {ui->AVLButton, ui->RBButton, ui->DDButton, ui->SplayButton};
    view = new GraphicsView;
    connect(view, &GraphicsView::mousePressed, this, &MainWindow::treeClick_checking );

    view->setGeometry(0,0,820,720);
    view->setDragMode(QGraphicsView::ScrollHandDrag);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    view->setRenderHint(QPainter::Antialiasing);    // Настраиваем рендер
    view->setCacheMode(QGraphicsView::CacheNone); // Кэш фона
    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    view->viewport()->setAttribute(Qt::WA_AcceptTouchEvents);

    avl_scene = new QGraphicsScene;
    avl_scene->setSceneRect(0,0,820,720);

    rb_scene = new QGraphicsScene;
    rb_scene->setSceneRect(0,0,820,720);

    s_scene = new QGraphicsScene;
    s_scene->setSceneRect(0,0,820,720);

    t_scene = new QGraphicsScene;
    t_scene->setSceneRect(0,0,820,720);

    avl_tree = new AVLTree();
    rb_tree = new RBTree();
    s_tree = new Splay();
    t_tree = new Treap();

    avl_tree->display(avl_scene,avl_tree->getRoot());

    view->setScene(avl_scene);

    QVBoxLayout *viewLayout = new QVBoxLayout(this);
    viewLayout->addWidget(view);
    ui->frame->setLayout(viewLayout);

    ui->InsertLine->setValidator(new QIntValidator(-2147483648,2147483647,this));
    ui->InsertSomeLine->setValidator(new QIntValidator(0,2147483647,this));
    ui->containsLine->setValidator(new QIntValidator(-2147483648,2147483647,this));


}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_RBButton_clicked()
{
    for(auto& i : btns) {
        i->setEnabled(true);
    }
    ui->RBButton->setEnabled(false);
    view->setScene(rb_scene);
}


void MainWindow::on_AVLButton_clicked()
{
    for(auto& i : btns) {
        i->setEnabled(true);
    }
    ui->AVLButton->setEnabled(false);
    view->setScene(avl_scene);
    view->toDefault();


}


void MainWindow::on_DDButton_clicked()
{
    for(auto& i : btns) {
        i->setEnabled(true);
    }
    ui->DDButton->setEnabled(false);
    view->setScene(t_scene);
    view->toDefault();


}


void MainWindow::on_SplayButton_clicked()
{
    for(auto& i : btns) {
        i->setEnabled(true);
    }
    ui->SplayButton->setEnabled(false);
    view->setScene(s_scene);
    view->toDefault();


}



void MainWindow::on_Insert_clicked()
{
    if(!ui->AVLButton->isEnabled()) {
        avl_tree->insert(ui->InsertLine->text().toInt());
        avl_tree->display(avl_scene,avl_tree->getRoot());
        ui->InsertLine->setText("");
    }
    else if(!ui->RBButton->isEnabled()) {
        rb_tree->insert(ui->InsertLine->text().toInt());
        rb_tree->display(rb_scene,rb_tree->getRoot());
        ui->InsertLine->setText("");
    }
    else if(!ui->SplayButton->isEnabled()) {
        s_tree->insert(ui->InsertLine->text().toInt());
        s_tree->display(s_scene,s_tree->getRoot());
        ui->InsertLine->setText("");
    }
    else if(!ui->DDButton->isEnabled()) {
        int pr = rand() % 2147483648;
        if(t_tree->searchTree(ui->InsertLine->text().toInt())) return;
        while(t_tree->searchPrior(t_tree->getRoot(), pr)) pr = rand() % 2147483648;
        t_tree->insert(ui->InsertLine->text().toInt(), pr);
        t_tree->display(t_scene,t_tree->getRoot());
        ui->InsertLine->setText("");
    }
}


void MainWindow::on_InsertSome_clicked()
{
    if(!ui->AVLButton->isEnabled()) {

        int num = ui->InsertSomeLine->text().toInt();
        int i = 0;
        while(i < num) {
            int pret = (rand() % 2147483648) - (rand() % 2147483648);
            if(!avl_tree->contains(pret)) {
                avl_tree->insert(pret);
                i++;
            }
        }
        avl_tree->display(avl_scene,avl_tree->getRoot());
        ui->InsertSomeLine->setText("");
    }
    else if(!ui->RBButton->isEnabled()) {
        int num = ui->InsertSomeLine->text().toInt();
        int i = 0;
        while(i < num) {
            int pret = (rand() % 2147483648) - (rand() % 2147483648);
            if(!rb_tree->searchTree(pret)) {
                rb_tree->insert(pret);
                i++;
            }
        }
        rb_tree->display(rb_scene,rb_tree->getRoot());
        ui->InsertSomeLine->setText("");
    }
    else if(!ui->SplayButton->isEnabled()) {
        int num = ui->InsertSomeLine->text().toInt();
        int i = 0;
        while(i < num) {
            int pret = (rand() % 2147483648) - (rand() % 2147483648);
            if(!s_tree->searchTree(pret)) {
                s_tree->insert(pret);
                i++;
            }
        }
        s_tree->display(s_scene,s_tree->getRoot());
        ui->InsertSomeLine->setText("");
    }
    else if(!ui->DDButton->isEnabled()) {
        int num = ui->InsertSomeLine->text().toInt();
        int i = 0;
        while(i < num) {
            int pret = (rand() % 2147483648) - (rand() % 2147483648);
            if(!t_tree->searchTree(pret)) {
                int pr = rand() % 2147483648;
                while(t_tree->searchPrior(t_tree->getRoot(), pr)) pr = rand() % 2147483648;
                t_tree->insert(pret, pr);
                i++;
            }
        }
        t_tree->display(t_scene,t_tree->getRoot());
        ui->InsertSomeLine->setText("");
    }
}


void MainWindow::on_InsertSomeLine_textChanged(const QString &arg1)
{
}

void MainWindow::treeClick_checking(int x, int y) {
    if(!CLICK_DELETE) return;
    if(!ui->AVLButton->isEnabled()) {
        avl_tree->click_delete(avl_tree->getRoot(),x,y);
        avl_tree->display(avl_scene,avl_tree->getRoot());
    }
    else if(!ui->RBButton->isEnabled()) {
        rb_tree->click_delete(rb_tree->getRoot(),x,y);
        rb_tree->display(rb_scene,rb_tree->getRoot());
    }
    else if(!ui->SplayButton->isEnabled()) {
        s_tree->click_delete(s_tree->getRoot(),x,y);
        s_tree->display(s_scene,s_tree->getRoot());
    }
    else if(!ui->DDButton->isEnabled()) {
        t_tree->click_delete(t_tree->getRoot(),x,y);
        t_tree->display(t_scene,t_tree->getRoot());
    }
}


void MainWindow::on_clickDel_clicked()
{
    CLICK_DELETE = ui->clickDel->isChecked();
}


void MainWindow::on_InsertLine_editingFinished()
{

}
void MainWindow::MessageClear() {
    ui->containsResult->setText("");
    ui->containsLine->setText("");
    ui->containsBtn->setEnabled(1);
    ui->containsLine->setReadOnly(0);
}

void MainWindow::on_containsBtn_clicked()
{
    if(!ui->AVLButton->isEnabled()) {
        if(avl_tree->contains(ui->containsLine->text().toInt())) {
            ui->containsResult->setText("There is a node with value " + QString::number(ui->containsLine->text().toInt()));
            ui->containsResult->setStyleSheet("color:green;");
        }
        else {
            ui->containsResult->setText("There are no nodes with value " + QString::number(ui->containsLine->text().toInt()));
            ui->containsResult->setStyleSheet("color:red;");
        }
        ui->containsBtn->setEnabled(0);
        ui->containsLine->setReadOnly(1);
        QTimer::singleShot(3000, this, &MainWindow::MessageClear);
    }
    else if(!ui->RBButton->isEnabled()) {
        if(rb_tree->searchTree(ui->containsLine->text().toInt())) {
            ui->containsResult->setText("There is a node with value " + QString::number(ui->containsLine->text().toInt()));
            ui->containsResult->setStyleSheet("color:green;");
        }
        else {
            ui->containsResult->setText("There are no nodes with value " + QString::number(ui->containsLine->text().toInt()));
            ui->containsResult->setStyleSheet("color:red;");
        }
        ui->containsBtn->setEnabled(0);
        ui->containsLine->setReadOnly(1);
        QTimer::singleShot(3000, this, &MainWindow::MessageClear);
    }
    else if(!ui->SplayButton->isEnabled()) {
        if(s_tree->searchTree(ui->containsLine->text().toInt())) {
            ui->containsResult->setText("There is a node with value " + QString::number(ui->containsLine->text().toInt()));
            ui->containsResult->setStyleSheet("color:green;");
        }
        else {
            ui->containsResult->setText("There are no nodes with value " + QString::number(ui->containsLine->text().toInt()));
            ui->containsResult->setStyleSheet("color:red;");
        }
        ui->containsBtn->setEnabled(0);
        ui->containsLine->setReadOnly(1);
        QTimer::singleShot(3000, this, &MainWindow::MessageClear);
    }
    else if(!ui->DDButton->isEnabled()) {
        if(t_tree->searchTree(ui->containsLine->text().toInt())) {
            ui->containsResult->setText("There is a node with value " + QString::number(ui->containsLine->text().toInt()));
            ui->containsResult->setStyleSheet("color:green;");
        }
        else {
            ui->containsResult->setText("There are no nodes with value " + QString::number(ui->containsLine->text().toInt()));
            ui->containsResult->setStyleSheet("color:red;");
        }
        ui->containsBtn->setEnabled(0);
        ui->containsLine->setReadOnly(1);
        QTimer::singleShot(3000, this, &MainWindow::MessageClear);
    }
}


void MainWindow::on_pushButton_clicked()
{
    view->toDefault();
}

