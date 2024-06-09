/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QPushButton *AVLButton;
    QPushButton *RBButton;
    QPushButton *DDButton;
    QPushButton *SplayButton;
    QGroupBox *groupBox;
    QWidget *widget;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLineEdit *InsertLine;
    QPushButton *Insert;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *InsertSomeLine;
    QPushButton *InsertSome;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *containsLine;
    QPushButton *containsBtn;
    QLabel *containsResult;
    QCheckBox *clickDel;
    QPushButton *pushButton;
    QFrame *frame;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1150, 750);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(850, 10, 291, 731));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        AVLButton = new QPushButton(layoutWidget);
        AVLButton->setObjectName("AVLButton");
        AVLButton->setEnabled(false);
        AVLButton->setMinimumSize(QSize(0, 40));
        QFont font;
        font.setFamilies({QString::fromUtf8("Montserrat Medium")});
        font.setPointSize(14);
        AVLButton->setFont(font);

        verticalLayout->addWidget(AVLButton);

        RBButton = new QPushButton(layoutWidget);
        RBButton->setObjectName("RBButton");
        RBButton->setMinimumSize(QSize(0, 40));
        RBButton->setFont(font);

        verticalLayout->addWidget(RBButton);

        DDButton = new QPushButton(layoutWidget);
        DDButton->setObjectName("DDButton");
        DDButton->setMinimumSize(QSize(0, 40));
        DDButton->setFont(font);

        verticalLayout->addWidget(DDButton);

        SplayButton = new QPushButton(layoutWidget);
        SplayButton->setObjectName("SplayButton");
        SplayButton->setMinimumSize(QSize(0, 40));
        SplayButton->setFont(font);

        verticalLayout->addWidget(SplayButton);


        verticalLayout_2->addLayout(verticalLayout);

        groupBox = new QGroupBox(layoutWidget);
        groupBox->setObjectName("groupBox");
        groupBox->setMinimumSize(QSize(0, 500));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Montserrat Medium")});
        font1.setPointSize(10);
        groupBox->setFont(font1);
        widget = new QWidget(groupBox);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(10, 50, 271, 281));
        verticalLayout_6 = new QVBoxLayout(widget);
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName("horizontalLayout");
        InsertLine = new QLineEdit(widget);
        InsertLine->setObjectName("InsertLine");
        InsertLine->setMinimumSize(QSize(0, 40));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Montserrat Medium")});
        font2.setPointSize(9);
        InsertLine->setFont(font2);

        horizontalLayout->addWidget(InsertLine);

        Insert = new QPushButton(widget);
        Insert->setObjectName("Insert");
        Insert->setMinimumSize(QSize(100, 40));
        Insert->setFont(font1);

        horizontalLayout->addWidget(Insert);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        InsertSomeLine = new QLineEdit(widget);
        InsertSomeLine->setObjectName("InsertSomeLine");
        InsertSomeLine->setMinimumSize(QSize(0, 40));
        InsertSomeLine->setFont(font2);
        InsertSomeLine->setMaxLength(32767);
        InsertSomeLine->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(InsertSomeLine);

        InsertSome = new QPushButton(widget);
        InsertSome->setObjectName("InsertSome");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(InsertSome->sizePolicy().hasHeightForWidth());
        InsertSome->setSizePolicy(sizePolicy);
        InsertSome->setMinimumSize(QSize(100, 40));
        InsertSome->setFont(font1);
        InsertSome->setLayoutDirection(Qt::LeftToRight);
        InsertSome->setAutoExclusive(false);

        horizontalLayout_2->addWidget(InsertSome);


        verticalLayout_3->addLayout(horizontalLayout_2);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(2);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        containsLine = new QLineEdit(widget);
        containsLine->setObjectName("containsLine");
        containsLine->setMinimumSize(QSize(0, 40));
        containsLine->setFont(font2);

        horizontalLayout_3->addWidget(containsLine);

        containsBtn = new QPushButton(widget);
        containsBtn->setObjectName("containsBtn");
        containsBtn->setMinimumSize(QSize(100, 40));
        containsBtn->setFont(font1);

        horizontalLayout_3->addWidget(containsBtn);


        verticalLayout_4->addLayout(horizontalLayout_3);

        containsResult = new QLabel(widget);
        containsResult->setObjectName("containsResult");
        containsResult->setFont(font2);
        containsResult->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(containsResult);


        verticalLayout_3->addLayout(verticalLayout_4);


        verticalLayout_5->addLayout(verticalLayout_3);

        clickDel = new QCheckBox(widget);
        clickDel->setObjectName("clickDel");
        clickDel->setFont(font1);

        verticalLayout_5->addWidget(clickDel);


        verticalLayout_6->addLayout(verticalLayout_5);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName("pushButton");

        verticalLayout_6->addWidget(pushButton);


        verticalLayout_2->addWidget(groupBox);

        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 10, 830, 730));
        frame->setCursor(QCursor(Qt::ArrowCursor));
        frame->setMouseTracking(false);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        AVLButton->setText(QCoreApplication::translate("MainWindow", "AVL", nullptr));
        RBButton->setText(QCoreApplication::translate("MainWindow", "RB", nullptr));
        DDButton->setText(QCoreApplication::translate("MainWindow", "DD", nullptr));
        SplayButton->setText(QCoreApplication::translate("MainWindow", "SPLAY", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265", nullptr));
        InsertLine->setPlaceholderText(QCoreApplication::translate("MainWindow", "Value of node", nullptr));
        Insert->setText(QCoreApplication::translate("MainWindow", "Ins", nullptr));
        InsertSomeLine->setInputMask(QString());
        InsertSomeLine->setPlaceholderText(QCoreApplication::translate("MainWindow", "Number of nodes", nullptr));
        InsertSome->setText(QCoreApplication::translate("MainWindow", "Ins some", nullptr));
        containsLine->setPlaceholderText(QCoreApplication::translate("MainWindow", "Value of node", nullptr));
        containsBtn->setText(QCoreApplication::translate("MainWindow", "Contains?", nullptr));
        containsResult->setText(QString());
        clickDel->setText(QCoreApplication::translate("MainWindow", "Click == Delete", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "ToDefault", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
