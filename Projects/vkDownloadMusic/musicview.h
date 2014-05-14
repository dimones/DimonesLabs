#ifndef MUSICVIEW_H
#define MUSICVIEW_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QUrl>
#include <QEventLoop>
#include <QTimer>
#include <QDebug>
#include <QMap>
#include <QMediaPlayer>
#include <QListWidgetItem>
#include <QFileDialog>
#include <QQueue>
#include "json.h"
namespace Ui {
class MusicView;
}

class MusicView : public QWidget
{
    Q_OBJECT

public:
    explicit MusicView(QWidget *parent = 0,QString token = NULL);
    ~MusicView();
    QNetworkAccessManager *m_NetworkMngr;
    QNetworkReply *reply;


signals:
    void finished();

private slots:
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
    // void percentage(quint64 i);
    void on_horizontalSlider_sliderMoved(int position);
    void on_listWidget_itemSelectionChanged();
    void on_setPath_clicked();
    void on_lineEdit_editingFinished();
    void on_downButton_clicked();
    void startNextDownload();
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void downloadFinished();
    void downloadReadyRead();

private:
    Ui::MusicView *ui;
    void append(const QUrl &url);
    void append(const QStringList &urlList);
    QByteArray GET(QUrl r);
    QNetworkAccessManager manager;
    QQueue<QUrl> downloadQueue;
    QNetworkReply *currentDownload;
    QFile output;
    QTime downloadTime;
    int downloadedCount = 0;
    int totalCount;
};

#endif // MUSICVIEW_H
