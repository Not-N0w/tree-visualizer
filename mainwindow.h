#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "graphicsview.h"
#include <QMainWindow>
#include "avltree.h"
#include "rbtree.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    GraphicsView *view;
    ~MainWindow();

private slots:
    void on_RBButton_clicked();

    void on_AVLButton_clicked();

    void on_DDButton_clicked();

    void on_SplayButton_clicked();

    void on_Insert_clicked();

    void on_InsertSome_clicked();

    void on_InsertSomeLine_textChanged(const QString &arg1);

    void on_clickDel_clicked();

    void on_InsertLine_editingFinished();

    void on_containsBtn_clicked();

    void MessageClear();


    void on_pushButton_clicked();

public slots:
    void treeClick_checking(int, int);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
