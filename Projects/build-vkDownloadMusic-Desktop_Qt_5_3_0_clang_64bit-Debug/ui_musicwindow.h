/********************************************************************************
** Form generated from reading UI file 'musicwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MUSICWINDOW_H
#define UI_MUSICWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QColumnView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_musicWindow
{
public:
    QColumnView *musicView;
    QWidget *widget;
    QWidget *widget_2;

    void setupUi(QWidget *musicWindow)
    {
        if (musicWindow->objectName().isEmpty())
            musicWindow->setObjectName(QStringLiteral("musicWindow"));
        musicWindow->resize(1100, 680);
        musicView = new QColumnView(musicWindow);
        musicView->setObjectName(QStringLiteral("musicView"));
        musicView->setGeometry(QRect(0, 100, 1100, 580));
        widget = new QWidget(musicWindow);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 70, 1101, 30));
        widget->setStyleSheet(QStringLiteral("background-color: qlineargradient(spread:reflect, x1:0.5, y1:1, x2:0.5, y2:0.5, stop:0.0547264 rgba(255, 255, 255, 255), stop:1 rgba(213, 213, 213, 255));"));
        widget_2 = new QWidget(musicWindow);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setGeometry(QRect(0, 0, 1101, 71));
        widget_2->setStyleSheet(QStringLiteral("background-color: qlineargradient(spread:repeat, x1:0.5, y1:0, x2:0.5, y2:1, stop:0.0547264 rgba(255, 255, 255, 255), stop:0.960199 rgba(213, 213, 213, 255));"));

        retranslateUi(musicWindow);

        QMetaObject::connectSlotsByName(musicWindow);
    } // setupUi

    void retranslateUi(QWidget *musicWindow)
    {
        musicWindow->setWindowTitle(QApplication::translate("musicWindow", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class musicWindow: public Ui_musicWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MUSICWINDOW_H
