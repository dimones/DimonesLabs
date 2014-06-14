#include "funchelp.h"
#include "ui_funchelp.h"
#include <QFile>
#include <QTextStream>

funcHelp::funcHelp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::funcHelp)
{
    ui->setupUi(this);
    QStringList *list  = new QStringList;
    QFile inputFile("://funcs.txt");
    if (inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
        while ( !in.atEnd() )
        {
            QString line = in.readLine();
            ui->listWidget->addItem(line);
        }
        inputFile.close();
    }
    QFile inputFile1("://abs.txt");
    if (inputFile1.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile1);
        ui->textBrowser->setText(in.readAll());
    }
}

funcHelp::~funcHelp()
{
    delete ui;
}

void funcHelp::on_listWidget_itemSelectionChanged()
{
    QList<QModelIndex> list = ui->listWidget->selectionModel()->selectedIndexes();
    QFile inputFile("://"+list[0].data().toString()+".txt");
    if (inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
        ui->textBrowser->setText(in.readAll());
    }
}
