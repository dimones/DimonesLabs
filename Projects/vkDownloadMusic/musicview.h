#ifndef MUSICVIEW_H
#define MUSICVIEW_H

#include <vkdownload.h>
namespace Ui {
class MusicView;
}

class MusicView : public QWidget
{
    Q_OBJECT

public:
    explicit MusicView(QWidget *parent = 0,QString token = NULL,QString user_id = NULL);
    ~MusicView();
    QNetworkAccessManager *m_NetworkMngr;
    QNetworkReply *reply;


signals:
    void finished();

private slots:
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
    void on_horizontalSlider_sliderMoved(int position);
    void on_listWidget_itemSelectionChanged();
    void on_setPath_clicked();
    void on_lineEdit_editingFinished();
    void on_downButton_clicked();
    void stateChangedH(QMediaPlayer::State state);
    void on_play_pause_clicked();
    void positionChangedH(qint64 pos);
    void on_curPlayer_sliderMoved(int position);
    void on_next_clicked();
    void on_previous_clicked();
    void oneDownload();
    void setMusic();
    void on_downButton_2_clicked();
    void getPartSongs(int offset,int count);

private:
    Ui::MusicView *ui;
    QByteArray GET(QUrl r);
    QNetworkAccessManager manager;
    void getSongs();

    QString GetTime(qint64 pos);
    int getSoundCount(QString user_id);

};

#endif // MUSICVIEW_H
