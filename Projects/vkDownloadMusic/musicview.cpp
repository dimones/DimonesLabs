#include "musicview.h"
#include "ui_musicview.h"

using namespace QtJson;


//Definitions
QString tok,path; //temp token
QUrlQuery query("https://api.vk.com/method/audio.get"); //base query
QStringList name,urls,durations; //list of songs and urls
QList<QListWidgetItem*> checkedList;
QMediaPlayer *player;
int curSong,count,maxCount,currentPlay = 0,countPlayed = 0,indexLastPlayed = 0;
bool playing,downloading;

MusicView::MusicView(QWidget *parent, QString token) :
    QWidget(parent),
    ui(new Ui::MusicView)
{
    tok = token;
    ui->setupUi(this);
    query.addQueryItem("access_token",tok);
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
    connect(player,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(stateChangedH(QMediaPlayer::State)));
    connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(positionChangedH(qint64)));
    currentPlay = ui->listWidget->row(item);
    ui->curPlaySong->setText(name[currentPlay]);
    indexLastPlayed = ui->listWidget->row(item);
}

void MusicView::on_horizontalSlider_sliderMoved(int position)
{
    player->setVolume(position);
}

void MusicView::on_listWidget_itemSelectionChanged()
{
    if(downloading) return;
    checkedList =  ui->listWidget->selectedItems();
    if(checkedList.count()!=name.count()&&checkedList.count()!=1)
    {
        maxCount = count = checkedList.count();
        ui->label->setText("Выделено");
        ui->countSongs->setText(QString::number(checkedList.count()));
    }
    else
    {
        count = name.count();
        ui->label->setText("Кол-во песен");
        ui->countSongs->setText(QString::number(name.count()));
    }
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
    if(!downloading){
        ui->allProgress->reset();
        ui->allProgress->update();
        downloadedCount = 0;
        totalCount = 0;
        if(checkedList.count()!=0)
        {
            QStringList tempL;
            for(int i = 0;i<maxCount;i++)
            {
                tempL.push_back(urls[ui->listWidget->row(checkedList.at(i))]);
            }
            append(tempL);
        }
        else append(urls);
        downloading = true;
    }
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
    ui->current->setText(QString::number(downloadedCount));

    if (downloadQueue.isEmpty()) {
        printf("%d/%d files downloaded successfully\n", downloadedCount, maxCount);
        downloading = false;
        emit finished();
        return;
    }

    if(downloadedCount==maxCount) {downloading = false; return;}

    if(checkedList.count()<=1)
        ui->currentSong->setText(name[ui->listWidget->row(checkedList.at(0))]);
    else
        ui->currentSong->setText(name[ui->listWidget->row(checkedList.at(downloadedCount))]);

    QUrl url = downloadQueue.dequeue();
    QString filename;

    if(checkedList.count()<=1)
        filename = name[ui->listWidget->row(checkedList.at(0))]+".mp3";
    else
        filename = name[ui->listWidget->row(checkedList.at(downloadedCount))] + ".mp3";

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

void MusicView::stateChangedH(QMediaPlayer::State state)
{
    if(state == QMediaPlayer::PlayingState)
        playing = true;
    else playing  = false;
    /*
    if(!playing)
    if(player->isAvailable())
    if (state == QMediaPlayer::StoppedState)
    {
        if(indexLastPlayed == ui->listWidget->row(ui->listWidget->selectedItems()[0])) return;
        ++currentPlay;
        player->setMedia(QUrl(urls[currentPlay]));
        player->play();
        connect(player,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(stateChangedH(QMediaPlayer::State)));
        connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(positionChangedH(qint64)));
        ui->curPlaySong->setText(name[currentPlay]);
    }*/
}

void MusicView::on_play_pause_clicked()
{
    if(playing)
        player->pause();
    else
        if(player->state() == QMediaPlayer::StoppedState)
        {
            if(countPlayed==0)
            {
                currentPlay = 0;
                player->setMedia(QUrl(urls[currentPlay]));
                player->setVolume(ui->horizontalSlider->value());
                player->play();
                connect(player,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(stateChangedH(QMediaPlayer::State)));
                connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(positionChangedH(qint64)));
                ui->curPlaySong->setText(name[currentPlay]);
                countPlayed++;
            }
        }
        else player->play();
}

void MusicView::positionChangedH(qint64 pos)
{
    if(player->duration()>1)
        if(player->isSeekable())
            ui->curPlayer->setValue((double)pos/player->duration()*100);
    QDateTime time;
    ui->curSongTime->setText(QString("%1/%2").arg(GetTime(pos/1000)).arg(GetTime(player->duration()/1000)));
    if(pos>player->duration()-500)
    {
        ++currentPlay;
        player->setMedia(QUrl(urls[currentPlay]));
        player->play();
        connect(player,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(stateChangedH(QMediaPlayer::State)));
        connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(positionChangedH(qint64)));
        ui->curPlaySong->setText(name[currentPlay]);
    }
    // ui->curSongTime->setText(QString("%1.%2/%3.%4").arg(QString::number((double)pos/60000==0?0:(int)(double)(pos/60000))).arg("qf").arg("qf").arg("qf"));
}


QString MusicView::GetTime(qint64 pos)
{
    QString res;
    int seconds = (int) (pos % 60);
    pos /= 60;
    int minutes = (int) (pos % 60);
    pos /= 60;
    int hours = (int) (pos % 24);
    int days = (int) (pos / 24);
    if((hours == 0)&&(days == 0))
        return res.sprintf("%02d:%02d", minutes, seconds);
    if (days == 0)
        return res.sprintf("%02d:%02d:%02d", hours, minutes, seconds);
    return res.sprintf("%dd%02d:%02d:%02d", days, hours, minutes, seconds);
}

void MusicView::on_curPlayer_sliderMoved(int position)
{
    player->setPosition(player->duration()/position);
}

void MusicView::on_next_clicked()
{
    ++currentPlay;
    player->setMedia(QUrl(urls[currentPlay]));
    player->play();
    connect(player,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(stateChangedH(QMediaPlayer::State)));
    connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(positionChangedH(qint64)));
    ui->curPlaySong->setText(name[currentPlay]);
}

void MusicView::on_previous_clicked()
{
    --currentPlay;
    player->setMedia(QUrl(urls[currentPlay]));
    player->play();
    connect(player,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(stateChangedH(QMediaPlayer::State)));
    connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(positionChangedH(qint64)));
    ui->curPlaySong->setText(name[currentPlay]);
}

void MusicView::on_listWidget_itemClicked(QListWidgetItem *item)
{

}
