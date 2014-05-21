#include "vkdownload.h"

vkDownload::vkDownload(int count,QString path)
{

}

void vkDownload::append(const QStringList &urlList)
{
    /*
    foreach (QString url, urlList)
        append(QUrl::fromEncoded(url.toLocal8Bit()));

    if (downloadQueue.isEmpty())
        QTimer::singleShot(0, this, SIGNAL(finished()));*/
}
void vkDownload::append(const QUrl &url)
{
//    if (downloadQueue.isEmpty())
//        QTimer::singleShot(0, this, SLOT(startNextDownload()));

//    downloadQueue.enqueue(url);
//    ++totalCount;
}
void vkDownload::startNextDownload()
{
//    //UI BLOCK
//    ui->allProgress->setValue((double)downloadedCount/maxCount*100);
//    ui->current->setText(QString::number(downloadedCount));

//    if (downloadQueue.isEmpty()) {
//        printf("%d/%d files downloaded successfully\n", downloadedCount, maxCount);
//        downloading = false;
//        emit finished();
//        return;
//    }

//    if(downloadedCount==maxCount) {downloading = false; return;}

//    if(checkedList.count()<=1)
//        ui->currentSong->setText(name[ui->listWidget->row(checkedList.at(0))]);
//    else
//        ui->currentSong->setText(name[ui->listWidget->row(checkedList.at(downloadedCount))]);

//    QUrl url = downloadQueue.dequeue();
//    QString filename;

//    if(checkedList.count()<=1)
//        filename = name[ui->listWidget->row(checkedList.at(0))]+".mp3";
//    else
//        filename = name[ui->listWidget->row(checkedList.at(downloadedCount))] + ".mp3";

//    output.setFileName(path+"/"+filename);

//    if (!output.open(QIODevice::WriteOnly)) {
//        fprintf(stderr, "Problem opening save file '%s' for download '%s': %s\n",
//                qPrintable(filename), url.toEncoded().constData(),
//                qPrintable(output.errorString()));
//        startNextDownload();
//        return;                 // skip this download
//    }

//    QNetworkRequest request(url);
//    currentDownload = manager.get(request);
//    connect(currentDownload, SIGNAL(downloadProgress(qint64,qint64)),
//            SLOT(downloadProgress(qint64,qint64)));
//    connect(currentDownload, SIGNAL(finished()),
//            SLOT(downloadFinished()));
//    connect(currentDownload, SIGNAL(readyRead()),
//            SLOT(downloadReadyRead()));
//    printf("Downloading %s...\n", url.toEncoded().constData());
//    downloadTime.start();
//}

//void vkDownload::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
//{
//    // calculate the download speed
//    double speed = bytesReceived * 1000.0 / downloadTime.elapsed();
//    QString unit;
//    if (speed < 1024) {
//        unit = "bytes/sec";
//    } else if (speed < 1024*1024) {
//        speed /= 1024;
//        unit = "kB/s";
//    } else {
//        speed /= 1024*1024;
//        unit = "MB/s";
//    }
//    ui->curProgBar->setValue((double)bytesReceived/bytesTotal*100);
//    ui->curProgBar->update();
//    ui->currentSongSpeed->setText(QString::number(speed)+" "+unit);
}

void vkDownload::downloadFinished()
{
//    output.close();

//    if (currentDownload->error()) {
//        // download failed
//        fprintf(stderr, "Failed: %s\n", qPrintable(currentDownload->errorString()));
//    } else {
//        printf("Succeeded.\n");
//        ++downloadedCount;
//    }
//    currentDownload->deleteLater();
//    startNextDownload();
}

void vkDownload::downloadReadyRead()
{//output.write(currentDownload->readAll());
}
