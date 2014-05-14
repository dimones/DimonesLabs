#include "musicview.h"
#include "ui_musicview.h"

using namespace QtJson;


//Definitions
QString tok,path; //temp token
QUrlQuery query("https://api.vk.com/method/audio.get"); //base query
QStringList name,urls; //list of songs and urls
QMediaPlayer *player;
int curSong,count,maxCount;

MusicView::MusicView(QWidget *parent, QString token) :
    QWidget(parent),
    ui(new Ui::MusicView)
{
    tok = token;
    ui->setupUi(this);
    query.addQueryItem("access_token",tok);
    qDebug() << "QUERY" << query.toString();
    QByteArray t = GET(QUrl(query.toString().replace("&","?")));
    QVariantList list = parse(QString(t)).toMap().value("response").toList();
    for(int i = 0;i<list.size();i++)
    {
        QVariantMap cur = list[i].toMap();
        name.push_back(QString(cur.value("artist").toString() + " - " +cur.value("title").toString()));
        urls.push_back(QString(cur.value("url").toString().split("?")[0]));
    }
    ui->listWidget->addItems(name);
    player = new QMediaPlayer();
    ui->countSongs->setText(QString::number(urls.count()));
    path = "/Users/"+QString(getenv("USER"))+"/vkMusicDownloader";
    if(!QDir(path).exists())
        QDir().mkdir("/Users/"+QString(getenv("USER"))+"/vkMusicDownloader");
    ui->lineEdit->setText(QString(path));
    maxCount = urls.count();
}

MusicView::~MusicView()
{
    delete ui;
}

QByteArray MusicView::GET(QUrl r)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    QNetworkReply* reply = manager->get(QNetworkRequest(r));
    QEventLoop await;
    connect(manager,SIGNAL(finished(QNetworkReply*)),&await,SLOT(quit()));
    QTimer::singleShot(10000,&await,SLOT(quit()));
    connect(manager,SIGNAL(finished(QNetworkReply*)),manager,SLOT(deleteLater()));
    await.exec();
    QByteArray req = reply->readAll();
    reply->deleteLater();
    return req;
}

void MusicView::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    player->setMedia(QUrl(urls[ui->listWidget->row(item)]));
    player->setVolume(ui->horizontalSlider->value());
    player->play();
    // connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(percentage(quint64)));
}

void MusicView::on_horizontalSlider_sliderMoved(int position)
{
    player->setVolume(position);
}

void MusicView::on_listWidget_itemSelectionChanged()
{
    QList<QListWidgetItem*> list =  ui->listWidget->selectedItems();
}

void MusicView::on_setPath_clicked()
{
    path = QFileDialog::getExistingDirectory();
    ui->lineEdit->setText(path);
}

void MusicView::on_lineEdit_editingFinished()
{
    path = ui->lineEdit->text();
}

void MusicView::on_downButton_clicked()
{
    append(urls);
}



void MusicView::append(const QStringList &urlList)
{
    foreach (QString url, urlList)
        append(QUrl::fromEncoded(url.toLocal8Bit()));

    if (downloadQueue.isEmpty())
        QTimer::singleShot(0, this, SIGNAL(finished()));
}
void MusicView::append(const QUrl &url)
{
    if (downloadQueue.isEmpty())
        QTimer::singleShot(0, this, SLOT(startNextDownload()));

    downloadQueue.enqueue(url);
    ++totalCount;
}
void MusicView::startNextDownload()
{
    //UI BLOCK
    ui->allProgress->setValue((double)downloadedCount/maxCount*100);
    ui->currentSong->setText(name[downloadedCount]);

    ui->current->setText(QString::number(downloadedCount));
    if (downloadQueue.isEmpty()) {
        printf("%d/%d files downloaded successfully\n", downloadedCount, maxCount);
        emit finished();
        return;
    }

    QUrl url = downloadQueue.dequeue();

    QString filename = name[downloadedCount]+".mp3";
    output.setFileName(path+"/"+filename);
    if (!output.open(QIODevice::WriteOnly)) {
        fprintf(stderr, "Problem opening save file '%s' for download '%s': %s\n",
                qPrintable(filename), url.toEncoded().constData(),
                qPrintable(output.errorString()));
        startNextDownload();
        return;                 // skip this download
    }

    QNetworkRequest request(url);
    currentDownload = manager.get(request);
    connect(currentDownload, SIGNAL(downloadProgress(qint64,qint64)),
            SLOT(downloadProgress(qint64,qint64)));
    connect(currentDownload, SIGNAL(finished()),
            SLOT(downloadFinished()));
    connect(currentDownload, SIGNAL(readyRead()),
            SLOT(downloadReadyRead()));
    // prepare the output
    printf("Downloading %s...\n", url.toEncoded().constData());
    downloadTime.start();
}

void MusicView::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    // calculate the download speed
    double speed = bytesReceived * 1000.0 / downloadTime.elapsed();
    QString unit;
    if (speed < 1024) {
        unit = "bytes/sec";
    } else if (speed < 1024*1024) {
        speed /= 1024;
        unit = "kB/s";
    } else {
        speed /= 1024*1024;
        unit = "MB/s";
    }
    ui->curProgBar->setValue((double)bytesReceived/bytesTotal*100);
    ui->curProgBar->update();
    ui->currentSongSpeed->setText(QString::number(speed)+" "+unit);
}

void MusicView::downloadFinished()
{
    output.close();

    if (currentDownload->error()) {
        // download failed
        fprintf(stderr, "Failed: %s\n", qPrintable(currentDownload->errorString()));
    } else {
        printf("Succeeded.\n");
        ++downloadedCount;
    }
    currentDownload->deleteLater();
    startNextDownload();
}

void MusicView::downloadReadyRead()
{output.write(currentDownload->readAll());}

