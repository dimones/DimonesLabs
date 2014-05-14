#include "vkstartwindow.h"
#include "ui_vkstartwindow.h"

vkStartWindow::vkStartWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::vkStartWindow)
{
    ui->setupUi(this);
}

vkStartWindow::~vkStartWindow()
{
    delete ui;
}
