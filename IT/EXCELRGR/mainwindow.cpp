#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    Functions::haveBrackets(item->text().toUtf8().data());
//    func::Parse(item);
}
