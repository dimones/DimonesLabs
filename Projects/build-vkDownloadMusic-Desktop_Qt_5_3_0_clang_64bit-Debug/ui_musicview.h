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
#include <QtWidgets/QColumnView>
#include <QtWidgets/QGroupBox>
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
    QLabel *currentSongSpeed;
    QGroupBox *groupBox;
    QSlider *curPlayer;
    QPushButton *previous;
    QPushButton *play_pause;
    QPushButton *next;
    QSlider *horizontalSlider;
    QLabel *curSongTime;
    QLabel *curPlaySong;
    QColumnView *columnView;

    void setupUi(QWidget *MusicView)
    {
        if (MusicView->objectName().isEmpty())
            MusicView->setObjectName(QStringLiteral("MusicView"));
        MusicView->resize(1330, 426);
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
        label->setGeometry(QRect(460, 40, 91, 16));
        countSongs = new QLabel(MusicView);
        countSongs->setObjectName(QStringLiteral("countSongs"));
        countSongs->setGeometry(QRect(560, 40, 61, 16));
        allProgress = new QProgressBar(MusicView);
        allProgress->setObjectName(QStringLiteral("allProgress"));
        allProgress->setGeometry(QRect(460, 70, 361, 23));
        allProgress->setValue(0);
        label_2 = new QLabel(MusicView);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(640, 40, 121, 16));
        curProgBar = new QProgressBar(MusicView);
        curProgBar->setObjectName(QStringLiteral("curProgBar"));
        curProgBar->setGeometry(QRect(460, 150, 111, 23));
        curProgBar->setValue(0);
        label_3 = new QLabel(MusicView);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(460, 110, 121, 16));
        current = new QLabel(MusicView);
        current->setObjectName(QStringLiteral("current"));
        current->setGeometry(QRect(760, 40, 71, 16));
        currentSong = new QLabel(MusicView);
        currentSong->setObjectName(QStringLiteral("currentSong"));
        currentSong->setGeometry(QRect(620, 100, 191, 31));
        currentSong->setAutoFillBackground(true);
        currentSong->setTextFormat(Qt::PlainText);
        currentSong->setScaledContents(false);
        currentSong->setWordWrap(true);
        currentSong->setTextInteractionFlags(Qt::NoTextInteraction);
        downButton = new QPushButton(MusicView);
        downButton->setObjectName(QStringLiteral("downButton"));
        downButton->setGeometry(QRect(620, 140, 181, 41));
        currentSongSpeed = new QLabel(MusicView);
        currentSongSpeed->setObjectName(QStringLiteral("currentSongSpeed"));
        currentSongSpeed->setGeometry(QRect(460, 150, 101, 16));
        QFont font;
        font.setFamily(QStringLiteral("Helvetica"));
        currentSongSpeed->setFont(font);
        currentSongSpeed->setAlignment(Qt::AlignCenter);
        currentSongSpeed->setWordWrap(false);
        groupBox = new QGroupBox(MusicView);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(450, 260, 381, 151));
        curPlayer = new QSlider(groupBox);
        curPlayer->setObjectName(QStringLiteral("curPlayer"));
        curPlayer->setGeometry(QRect(10, 130, 271, 21));
        curPlayer->setValue(0);
        curPlayer->setSliderPosition(0);
        curPlayer->setOrientation(Qt::Horizontal);
        previous = new QPushButton(groupBox);
        previous->setObjectName(QStringLiteral("previous"));
        previous->setGeometry(QRect(20, 70, 111, 51));
        QIcon icon;
        icon.addFile(QStringLiteral(":/new/prefix1/1400113331_icon-ios7-arrow-back.png"), QSize(), QIcon::Normal, QIcon::On);
        previous->setIcon(icon);
        previous->setIconSize(QSize(48, 48));
        previous->setAutoDefault(false);
        previous->setDefault(false);
        previous->setFlat(false);
        play_pause = new QPushButton(groupBox);
        play_pause->setObjectName(QStringLiteral("play_pause"));
        play_pause->setGeometry(QRect(130, 70, 111, 51));
        QIcon icon1;
        icon1.addFile(QStringLiteral("../../../../Downloads/1400113310_icon-play.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon1.addFile(QStringLiteral(":/new/prefix1/1400113310_icon-play.png"), QSize(), QIcon::Normal, QIcon::On);
        play_pause->setIcon(icon1);
        play_pause->setIconSize(QSize(40, 45));
        play_pause->setAutoDefault(false);
        play_pause->setDefault(false);
        play_pause->setFlat(false);
        next = new QPushButton(groupBox);
        next->setObjectName(QStringLiteral("next"));
        next->setGeometry(QRect(240, 70, 111, 51));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/new/prefix1/1400113324_icon-ios7-arrow-forward.svg"), QSize(), QIcon::Normal, QIcon::On);
        next->setIcon(icon2);
        next->setIconSize(QSize(48, 48));
        next->setAutoDefault(false);
        next->setDefault(false);
        next->setFlat(false);
        horizontalSlider = new QSlider(groupBox);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(300, 130, 71, 22));
        horizontalSlider->setValue(50);
        horizontalSlider->setOrientation(Qt::Horizontal);
        curSongTime = new QLabel(groupBox);
        curSongTime->setObjectName(QStringLiteral("curSongTime"));
        curSongTime->setGeometry(QRect(90, 120, 121, 16));
        curPlaySong = new QLabel(groupBox);
        curPlaySong->setObjectName(QStringLiteral("curPlaySong"));
        curPlaySong->setGeometry(QRect(20, 20, 351, 31));
        curPlaySong->setTextFormat(Qt::PlainText);
        columnView = new QColumnView(MusicView);
        columnView->setObjectName(QStringLiteral("columnView"));
        columnView->setGeometry(QRect(840, 20, 471, 391));

        retranslateUi(MusicView);

        QMetaObject::connectSlotsByName(MusicView);
    } // setupUi

    void retranslateUi(QWidget *MusicView)
    {
        MusicView->setWindowTitle(QApplication::translate("MusicView", "Form", 0));
        setPath->setText(QApplication::translate("MusicView", "\320\237\321\203\321\202\321\214", 0));
        label->setText(QApplication::translate("MusicView", "\320\232\320\276\320\273-\320\262\320\276 \320\277\320\265\321\201\320\265\320\275", 0));
        countSongs->setText(QString());
        label_2->setText(QApplication::translate("MusicView", "\320\236\320\261\321\211\320\270\320\271 \320\277\321\200\320\276\320\263\321\200\320\265\321\201\321\201", 0));
        label_3->setText(QApplication::translate("MusicView", "\320\242\320\265\320\272\321\203\321\211\320\260\321\217 \320\277\320\265\321\201\320\275\321\217", 0));
        current->setText(QString());
        currentSong->setText(QString());
        downButton->setText(QApplication::translate("MusicView", "DOWNLOAD", 0));
        currentSongSpeed->setText(QString());
        groupBox->setTitle(QApplication::translate("MusicView", "Player", 0));
        previous->setText(QString());
        play_pause->setText(QString());
        next->setText(QString());
        curSongTime->setText(QString());
        curPlaySong->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MusicView: public Ui_MusicView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MUSICVIEW_H
