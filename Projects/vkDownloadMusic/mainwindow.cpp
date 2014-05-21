#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->webView->load(QUrl("https://oauth.vk.com/authorize?client_id=4258201&scope=offline,audio&redirect_uri=https://oauth.vk.com/blank.html&display=popup&v=5.21&response_type=token"));
    connect(ui->webView,SIGNAL(urlChanged(QUrl)),this,SLOT(checkUrl(QUrl)));
    this->setWindowIcon(QIcon(":/new/prefix1/1400157672_vk.com.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::checkUrl(QUrl url)
{
    QString s = url.toString().replace('#','&');
    if(!s.contains("access_token"))
        return;
    qDebug() <<"TOKEN HERE" << url.toString();
    MusicView *view = new MusicView(0,QUrlQuery(s).queryItemValue("access_token"),QUrlQuery(s).queryItemValue("user_id"));
    view->show();
    this->close();
}
