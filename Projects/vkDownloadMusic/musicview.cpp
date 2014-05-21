 #include "musicview.h"
#include "ui_musicview.h"

using namespace QtJson;


//Definitions
QString tok,userId,path,methodUrl = "https://api.vk.com/method/"; //temp token
QUrlQuery query; //base query
QStringList name,urls,durations; //list of songs and urls
QList<QListWidgetItem*> checkedList;
QMediaPlayer *player;
QTimer *timer;
int curSong,count,maxCount,currentPlay = 0,countPlayed = 0,indexLastPlayed = 0,curOffset;
bool playing,downloading;

MusicView::MusicView(QWidget *parent, QString token, QString user_id) :
    QWidget(parent),
    ui(new Ui::MusicView)
{
    tok = token;
    userId = user_id;
    ui->setupUi(this);
    path = "/Users/"+QString(getenv("USER"))+"/vkMusicDownloader";
    if(!QDir(path).exists())
        QDir().mkdir("/Users/"+QString(getenv("USER"))+"/vkMusicDownloader");
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(setMusic()));
    timer->start(200);
    //QShortcut *shortcut = new QShortcut(QKeySequence("⌘S"), this);
   // QObject::connect(shortcut, SIGNAL(activated()), this, SLOT(oneDownload()));

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
    qDebug() << req;
    return req;
}

void MusicView::getSongs()
{
    QUrlQuery qurl(methodUrl+"audio.get?");
    qurl.addQueryItem("access_token",tok);
    QByteArray t = GET(qurl.toString());
    qDebug() << "partMusic" << t;
    QVariantList _count = parse(QString(t)).toMap().value("response").toList();
}

void MusicView::setMusic()
{
    int soundCount = getSoundCount(userId);
    for(int i=0,temp = soundCount;temp>0;)
    {
        temp>100?i+=100:i = temp;
        timer = new QTimer(this);
        curOffset = i;
        connect(timer,SIGNAL(timeout()),this,SLOT(getPartSongs(int,int)));
        timer->start(1000);
        qDebug() << "__________________________" <<endl;
        temp-=100;
    }
}

void MusicView::getPartSongs(int offset=0,int count = 100)
{
    QUrlQuery qurl(methodUrl+"audio.get?");
    qurl.addQueryItem("access_token",tok);
    qurl.addQueryItem("offset",QString::number(curOffset));
    qurl.addQueryItem("count",QString::number(count));
    QByteArray t = GET(qurl.toString());
    qDebug() << "partMusic" << t;
    QVariantList _count = parse(QString(t)).toMap().value("response").toList();
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
    countPlayed=1;
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
{/*
    if(!downloading){
        ui->allProgress->reset();
        ui->allProgress->update();
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
    }*/
}



void MusicView::stateChangedH(QMediaPlayer::State state)
{
    if(state == QMediaPlayer::PlayingState)
    {
        ui->play_pause->setIcon(QIcon(":/new/prefix1/1400157620_icon-pause.png"));
        playing = true;
    }
    else
    {
        ui->play_pause->setIcon(QIcon(":/new/prefix1/1400113310_icon-play.png"));
        playing  = false;
    }
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
    ui->curSongTime->setText(QString("%1/%2").arg(GetTime(pos)).arg(GetTime(player->duration())));
    if(pos>player->duration()-1000)
    {
        ++currentPlay;
        player->setMedia(QUrl(urls[currentPlay]));
        player->play();
        connect(player,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(stateChangedH(QMediaPlayer::State)));
        connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(positionChangedH(qint64)));
        ui->curPlaySong->setText(name[currentPlay]);
    }    
}


QString MusicView::GetTime(qint64 pos) //get time from milliseconds/1000
{
    QString res; pos/=1000;
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

int MusicView::getSoundCount(QString user_id)//get soung count from user id
{
    QUrlQuery qurl(methodUrl+"audio.getCount?");
    qurl.addQueryItem("access_token",tok);
    qurl.addQueryItem("owner_id",user_id);
    QByteArray t = GET(QUrl(qurl.toString()));
    QString _count = parse(QString(t)).toMap().value("response").toString();
    return _count.toInt();
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

void MusicView::oneDownload()
{/*
    qDebug() << "HUI";
    if(!downloading){
        ui->label->setText("Один трек"); ui->countSongs->setText("1");
        ui->allProgress->reset();
        ui->allProgress->update();
        downloadedCount = 0;
        totalCount = 0;
        maxCount = 1;
        append(urls[ui->listWidget->row(ui->listWidget->selectedItems()[0])]);
        downloading = true;
    }*/
}



void MusicView::on_downButton_2_clicked()
{
    getSoundCount(userId);
}
