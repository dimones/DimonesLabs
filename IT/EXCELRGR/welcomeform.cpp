#include "welcomeform.h"
#include "ui_welcomeform.h"

welcomeForm::welcomeForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::welcomeForm)
{
    ui->setupUi(this);
}

welcomeForm::~welcomeForm()
{
    delete ui;
}

void welcomeForm::on_open_clicked()
{

}
