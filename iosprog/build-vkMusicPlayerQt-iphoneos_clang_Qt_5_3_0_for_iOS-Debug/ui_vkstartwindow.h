/********************************************************************************
** Form generated from reading UI file 'vkstartwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VKSTARTWINDOW_H
#define UI_VKSTARTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_vkStartWindow
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *vkStartWindow)
    {
        if (vkStartWindow->objectName().isEmpty())
            vkStartWindow->setObjectName(QStringLiteral("vkStartWindow"));
        vkStartWindow->resize(400, 300);
        menuBar = new QMenuBar(vkStartWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        vkStartWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(vkStartWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        vkStartWindow->addToolBar(mainToolBar);
        centralWidget = new QWidget(vkStartWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        vkStartWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(vkStartWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        vkStartWindow->setStatusBar(statusBar);

        retranslateUi(vkStartWindow);

        QMetaObject::connectSlotsByName(vkStartWindow);
    } // setupUi

    void retranslateUi(QMainWindow *vkStartWindow)
    {
        vkStartWindow->setWindowTitle(QApplication::translate("vkStartWindow", "vkStartWindow", 0));
    } // retranslateUi

};

namespace Ui {
    class vkStartWindow: public Ui_vkStartWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VKSTARTWINDOW_H
