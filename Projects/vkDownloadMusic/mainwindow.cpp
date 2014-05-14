#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QUrl>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->webView->load(QUrl("https://oauth.vk.com/authorize?client_id=4258201&scope=offline,audio&redirect_uri=https://oauth.vk.com/blank.html&display=popup&v=5.21&response_type=token"));
    connect(ui->webView,SIGNAL(urlChanged(QUrl)),this,SLOT(check_url(QUrl)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::check_url(QUrl url)
{
    QString s = url.toString().replace('#','&');
    if(!s.contains("access_token"))
            return;
    s = QUrlQuery(s).queryItemValue("access_token");
    MusicView *view = new MusicView(0,s);
    view->show();
    this->close();
}
