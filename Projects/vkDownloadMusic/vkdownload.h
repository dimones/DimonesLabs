#ifndef VKDOWNLOAD_H
#define VKDOWNLOAD_H

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
#include <QDateTime>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QShortcut>
#include <json.h>
class vkDownload
{
public:
    vkDownload(int count,QString path);
private slots:
    void startNextDownload();
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void downloadFinished();
    void downloadReadyRead();
private:
    void append(const QUrl &url);
    void append(const QStringList &urlList);
    QFile output;
    QTime downloadTime;
    int downloadedCount = 0;
    int totalCount;
    QQueue<QUrl> downloadQueue;
    QNetworkReply *currentDownload;
};

#endif // VKDOWNLOAD_H
