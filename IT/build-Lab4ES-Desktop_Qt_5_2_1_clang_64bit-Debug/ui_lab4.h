/********************************************************************************
** Form generated from reading UI file 'lab4.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAB4_H
#define UI_LAB4_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Lab4
{
public:
    QWidget *centralWidget;
    QListWidget *listWidget;
    QListWidget *listWidget_2;
    QPushButton *pushButton;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton_2;
    QLineEdit *lineEdit_2;
    QPushButton *addItem;
    QPushButton *deleteItem;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEdit_3;

    void setupUi(QMainWindow *Lab4)
    {
        if (Lab4->objectName().isEmpty())
            Lab4->setObjectName(QStringLiteral("Lab4"));
        Lab4->resize(273, 481);
        centralWidget = new QWidget(Lab4);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(10, 130, 101, 341));
        listWidget_2 = new QListWidget(centralWidget);
        listWidget_2->setObjectName(QStringLiteral("listWidget_2"));
        listWidget_2->setGeometry(QRect(160, 130, 101, 341));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(120, 280, 31, 32));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 10, 101, 16));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(140, 10, 113, 21));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(140, 60, 111, 32));
        lineEdit_2 = new QLineEdit(centralWidget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(10, 100, 101, 21));
        addItem = new QPushButton(centralWidget);
        addItem->setObjectName(QStringLiteral("addItem"));
        addItem->setGeometry(QRect(120, 150, 31, 32));
        deleteItem = new QPushButton(centralWidget);
        deleteItem->setObjectName(QStringLiteral("deleteItem"));
        deleteItem->setGeometry(QRect(120, 200, 31, 32));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 70, 101, 16));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(0, 40, 121, 20));
        lineEdit_3 = new QLineEdit(centralWidget);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(140, 40, 113, 21));
        Lab4->setCentralWidget(centralWidget);

        retranslateUi(Lab4);

        QMetaObject::connectSlotsByName(Lab4);
    } // setupUi

    void retranslateUi(QMainWindow *Lab4)
    {
        Lab4->setWindowTitle(QApplication::translate("Lab4", "Lab4", 0));
        pushButton->setText(QApplication::translate("Lab4", "->", 0));
        label->setText(QApplication::translate("Lab4", "\320\232\320\276\320\273-\320\262\320\276 \320\272\320\276\321\201\321\202\320\265\320\271:", 0));
        pushButton_2->setText(QApplication::translate("Lab4", "getRandom()", 0));
        addItem->setText(QApplication::translate("Lab4", "+", 0));
        deleteItem->setText(QApplication::translate("Lab4", "-", 0));
        label_2->setText(QApplication::translate("Lab4", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214:", 0));
        label_3->setText(QApplication::translate("Lab4", "\320\240\320\260\320\275\320\264\320\276\320\274\320\275\320\276\320\265 \320\272\320\276\320\273-\320\262\320\276:", 0));
    } // retranslateUi

};

namespace Ui {
    class Lab4: public Ui_Lab4 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAB4_H
