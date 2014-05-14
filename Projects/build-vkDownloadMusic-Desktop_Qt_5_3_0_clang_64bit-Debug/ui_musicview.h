/********************************************************************************
** Form generated from reading UI file 'musicview.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MUSICVIEW_H
#define UI_MUSICVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MusicView
{
public:
    QListWidget *listWidget;
    QPushButton *setPath;
    QLineEdit *lineEdit;
    QLabel *label;
    QLabel *countSongs;
    QProgressBar *allProgress;
    QLabel *label_2;
    QProgressBar *curProgBar;
    QLabel *label_3;
    QLabel *current;
    QLabel *currentSong;
    QPushButton *downButton;
    QSlider *horizontalSlider;
    QLabel *label_4;
    QLabel *label_5;
    QProgressBar *progressBar_3;
    QLabel *currentSongSpeed;

    void setupUi(QWidget *MusicView)
    {
        if (MusicView->objectName().isEmpty())
            MusicView->setObjectName(QStringLiteral("MusicView"));
        MusicView->resize(841, 428);
        listWidget = new QListWidget(MusicView);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(10, 40, 431, 371));
        listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
        listWidget->setModelColumn(0);
        setPath = new QPushButton(MusicView);
        setPath->setObjectName(QStringLiteral("setPath"));
        setPath->setGeometry(QRect(600, 0, 114, 41));
        lineEdit = new QLineEdit(MusicView);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(10, 10, 581, 21));
        label = new QLabel(MusicView);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(460, 60, 91, 16));
        countSongs = new QLabel(MusicView);
        countSongs->setObjectName(QStringLiteral("countSongs"));
        countSongs->setGeometry(QRect(560, 60, 91, 16));
        allProgress = new QProgressBar(MusicView);
        allProgress->setObjectName(QStringLiteral("allProgress"));
        allProgress->setGeometry(QRect(460, 140, 351, 23));
        allProgress->setValue(0);
        label_2 = new QLabel(MusicView);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(460, 100, 121, 16));
        curProgBar = new QProgressBar(MusicView);
        curProgBar->setObjectName(QStringLiteral("curProgBar"));
        curProgBar->setGeometry(QRect(460, 220, 351, 23));
        curProgBar->setValue(0);
        label_3 = new QLabel(MusicView);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(460, 180, 121, 16));
        current = new QLabel(MusicView);
        current->setObjectName(QStringLiteral("current"));
        current->setGeometry(QRect(600, 100, 121, 16));
        currentSong = new QLabel(MusicView);
        currentSong->setObjectName(QStringLiteral("currentSong"));
        currentSong->setGeometry(QRect(610, 180, 121, 16));
        currentSong->setWordWrap(false);
        downButton = new QPushButton(MusicView);
        downButton->setObjectName(QStringLiteral("downButton"));
        downButton->setGeometry(QRect(460, 250, 351, 41));
        horizontalSlider = new QSlider(MusicView);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(560, 330, 160, 22));
        horizontalSlider->setValue(50);
        horizontalSlider->setOrientation(Qt::Horizontal);
        label_4 = new QLabel(MusicView);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(460, 300, 121, 16));
        label_5 = new QLabel(MusicView);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(480, 330, 71, 16));
        progressBar_3 = new QProgressBar(MusicView);
        progressBar_3->setObjectName(QStringLiteral("progressBar_3"));
        progressBar_3->setGeometry(QRect(460, 360, 351, 23));
        progressBar_3->setValue(0);
        currentSongSpeed = new QLabel(MusicView);
        currentSongSpeed->setObjectName(QStringLiteral("currentSongSpeed"));
        currentSongSpeed->setGeometry(QRect(580, 220, 121, 16));
        currentSongSpeed->setWordWrap(false);

        retranslateUi(MusicView);

        QMetaObject::connectSlotsByName(MusicView);
    } // setupUi

    void retranslateUi(QWidget *MusicView)
    {
        MusicView->setWindowTitle(QApplication::translate("MusicView", "Form", 0));
        setPath->setText(QApplication::translate("MusicView", "PATH", 0));
        label->setText(QApplication::translate("MusicView", "\320\232\320\276\320\273-\320\262\320\276 \320\277\320\265\321\201\320\265\320\275", 0));
        countSongs->setText(QString());
        label_2->setText(QApplication::translate("MusicView", "\320\236\320\261\321\211\320\270\320\271 \320\277\321\200\320\276\320\263\321\200\320\265\321\201\321\201", 0));
        label_3->setText(QApplication::translate("MusicView", "\320\242\320\265\320\272\321\203\321\211\320\260\321\217 \320\277\320\265\321\201\320\275\321\217", 0));
        current->setText(QString());
        currentSong->setText(QString());
        downButton->setText(QApplication::translate("MusicView", "DOWNLOAD", 0));
        label_4->setText(QApplication::translate("MusicView", "Player", 0));
        label_5->setText(QApplication::translate("MusicView", "Volume", 0));
        currentSongSpeed->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MusicView: public Ui_MusicView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MUSICVIEW_H
