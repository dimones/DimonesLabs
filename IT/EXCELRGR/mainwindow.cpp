#include "mainwindow.h"
#include "ui_mainwindow.h"
const int N = 1000;
const float PI = 3.14159265359;
char colNames[24] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','V','X','Y','Z'};

QString path;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    newTable(100,100);
    QObject::connect(ui->tableWidget->verticalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(handlerVertical(int)));
    QObject::connect(ui->tableWidget->horizontalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(handlerHorizontal(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handlerVertical(int y)
{
    if(y+22==ui->tableWidget->rowCount())
        resizeTable(1);
}

void MainWindow::handlerHorizontal(int x)
{
    if(x+11==ui->tableWidget->columnCount())
        resizeTable(2);
}

void MainWindow::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    firstParse(item);
}
char *MainWindow::getCharFromPos(int pos)
{
    int x = pos; int count = 0;
    while(x>24)
    {
        x-=24;
        count++;
    }
    if(count>0)
    {
        char *out = new char[count+1]; int i = 0;
        for(i = 0;i<count;i++)
            out[i] = colNames[0];
        out[i] = colNames[x];
        return out;
    }
    char *t = new char[1]; t[0] = colNames[pos];
    return  t;
}
int  MainWindow::getPosFromChar(char c)
{
    int out = 0,i=0;
    for(;i<strlen( colNames);i++)
        if( colNames[i]==c){
            out = i;
            return i;
        }
    return out;
}

void MainWindow::firstParse(QTableWidgetItem *item)
{
    if(item->text().contains("="))
        Parse(item);
    else
    {
        char* temp = new char[strlen(item->text().toUtf8().data())]; strcpy(temp,item->text().toUtf8().constData());
        T->pushTo(item->row(),item->column(),temp,temp);
    }
}

bool MainWindow::isNumber(char t)
{
    for(int i =0;i<10;i++)
        if(i==t-'0')
            return true;
    return false;
}

bool MainWindow::isChar(char t)
{
    for(int i = 0;i<100;i++)
        if(t == i)
            return true;
    return false;
}



char*  MainWindow::getValueFromItem(int row,char col)
{
    return T->getValue(row,getPosFromChar(col));
}

char*  MainWindow::getVariable(char *text)//получение строки между скобками
{
    char* temp = new char[strlen(text)-2];
    int left = 0,right = 0,i = 0;
    for(;right<=strlen(text)&&text[right]!=')';right++);
    for(left = right;left>0&&text[left]!='(';left--);
    for(int j = left+1;j<right;i++,j++) temp[i] = text[j]; temp[i] = NULL;
    return temp;
}
char*  MainWindow::getVariableBR(char *text)//получение строки между скобками
{
    char* temp = new char[strlen(text)-2];
    int left = 0,right = 0,i = 0;
    for(;right<=strlen(text)&&text[right]!='}';right++);
    for(left = right;left>0&&text[left]!='{';left--);
    for(int j = left+1;j<right;i++,j++) temp[i] = text[j]; temp[i] = NULL;
    return temp;
}

double  MainWindow::isValue(char* t)
{
    if(!QString(t).contains("&"))
        return -1;
    strcpy(t,QString(t).remove("&").toUtf8().constData());
    int X = 0,Y = 0; int outRow,outCol = 0;
    char *row = new char[100]; char *col = new char[100];
    for(int i = strlen(t);i>=0;i--)
    {
        if(isNumber(t[i]))
        {
            row[X] = t[i];
            X++;
        }
        else if(isalpha(t[i]))
        {
            col[Y] = t[i];
            Y++;
        }
    }
    outRow = QString(mirror(row)).toInt();
    if(strlen(mirror(col))>1)
    {
        char *temp = new char[strlen(mirror(col))];
        temp = mirror(col);
        for(int i = 0;i<strlen(temp);i++)
            if(containsChar(colNames,t[i])==0)
                outCol+=24;
            else
                outCol += containsChar(colNames,t[i]);
    }
    else outCol = containsChar(colNames,mirror(col)[0]);
    return atof(T->getValue(outRow-1,outCol)!=NULL?T->getValue(outRow-1,outCol):"-1");
}
double  MainWindow::SUM(char* text)
{
    double out = 0;
    QStringList list = QString(text).split(";");
    checkListItems(list);
    for(int i =0;i<list.count();i++)
        out += atof(list[i].toUtf8().data());
    return out;
}
double MainWindow::min(char *t)
{
    QStringList list = QString(t).split(";");
    checkListItems(list);
    qDebug() << "min list: " << list;
    double min = atof(list[0].toUtf8().data());
    for(int i=1;i<list.count();i++)
        if(atof(list[i].toUtf8().data())<min)
            min = atof(list[i].toUtf8().data());
    return min;
}
double MainWindow::max(char *t)
{
    QStringList list = QString(t).split(";");
    checkListItems(list);
    double max = atof(list[0].toUtf8().data());
    for(int i=1;i<list.count();i++)
        if(atof(list[i].toUtf8().data())>max)
            max = atof(list[i].toUtf8().data());
    return max;
}
double MainWindow::pow(char *t){
    QStringList list = QString(t).split(";");
    checkListItems(list);
    if(list.count()>2) return -1;
    return powf(atof(list[0].toUtf8().data()),atof(list[1].toUtf8().data()));
}

void MainWindow::resizeTable(int mode)
{
    switch (mode) {
    case 1:
    {
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+10);
        for(int i = ui->tableWidget->rowCount()-10;i<ui->tableWidget->rowCount();i++)
            ui->tableWidget->setRowHeight(i,20);
    }
        break;
    case 2:
    {
        ui->tableWidget->setColumnCount(ui->tableWidget->columnCount()+10);
        for(int i = ui->tableWidget->columnCount()-10;i<ui->tableWidget->columnCount();i++){
            ui->tableWidget->setColumnWidth(i,70);
            ui->tableWidget->setHorizontalHeaderItem(i,new QTableWidgetItem(QString(getCharFromPos(i))));
        }
    }
        break;
    default:
        break;
    }
}

char *MainWindow::mirror(char *in)
{
    char *out = new char[strlen(in)]; int i = 0; int j =strlen(in)-1;
    for( ; j>=0 ;j--,i++)
        out[i] = in[j];
    return out;
}

double  MainWindow::isFunc(char* t){
    if(isalnum(atoi(t))==0)
    {
        if (QString(t).toLower().contains("abs"))
            return abs(isValue(getVariableBR(t))!=-1? atof(getVariableBR(t)):isValue(getVariableBR(t)));
        else if(QString(t).toLower().contains("asin"))
            return asin(isValue(getVariableBR(t))!=-1? atof(getVariableBR(t)):isValue(getVariableBR(t)));
        else if(QString(t).toLower().contains("atan"))
            return atan(isValue(getVariableBR(t))!=-1? atof(getVariableBR(t)):isValue(getVariableBR(t)));
        else if(QString(t).toLower().contains("cos"))
            return cos((isValue(getVariableBR(t))!=-1?isValue(getVariableBR(t)):atof(getVariableBR(t)))*PI/180);
        else if(QString(t).toLower().contains("exp"))
            return exp(isValue(getVariableBR(t))!=-1?isValue(getVariableBR(t)):atof(getVariableBR(t)));
        else if(QString(t).toLower().contains("floor"))
            return floor(isValue(getVariableBR(t))!=-1?isValue(getVariableBR(t)):atof(getVariableBR(t)));
        else if(QString(t).toLower().contains("log10"))
            return log10(isValue(getVariableBR(t))!=-1?isValue(getVariableBR(t)):atof(getVariableBR(t)));
        else if(QString(t).toLower().contains("log"))
            return log(isValue(getVariableBR(t))!=-1?isValue(getVariableBR(t)):atof(getVariableBR(t)));
        else if(QString(t).toLower().contains("max"))
            return max(getVariableBR(t));
        else if(QString(t).toLower().contains("min"))
            return min(getVariableBR(t));
        else if(QString(t).toLower().contains("pow"))
            return pow(getVariableBR(t));
        else if(QString(t).toLower().contains("round"))
            return round(isValue(getVariableBR(t))!=-1?isValue(getVariableBR(t)):atof(getVariableBR(t)));
        else if(QString(t).toLower().contains("sinh"))
            return sinh((isValue(getVariableBR(t))!=-1?isValue(getVariableBR(t)):atof(getVariableBR(t)))*PI/180);
        else if(QString(t).toLower().contains("sin"))
        {

            //            qDebug() << "DEBUG";
            //            qDebug() << "VALUE: " << isValue(getVariableBR(t));
            //            qDebug() << "ATOF: " << atof(getVariableBR(t));
            //            qDebug() << "END DEBUG";
            //            qDebug() << "RESULT: " << QString::number(      sin(atof(getVariableBR(t))!=0.0 ?   isValue(getVariableBR(t)) :atof(getVariableBR(t)) ));
            //            qDebug() << "RESULT: " << QString::number(sin(isValue(getVariableBR(t))!=-1?isValue(getVariableBR(t)):atof(getVariableBR(t))));
            //            //return -1;
            //return sin(isValue(getVariableBR(t))!=-1?atof(getVariableBR(t)):isValue(getVariableBR(t)));
            return sin((isValue(getVariableBR(t))!=-1?isValue(getVariableBR(t)):atof(getVariableBR(t)))*PI/180);
        }
        else if(QString(t).toLower().contains("sqrt"))
            return sqrt(isValue(getVariableBR(t))!=-1?isValue(getVariableBR(t)):atof(getVariableBR(t)));
        else if(QString(t).toLower().contains("tanh"))
            return tanh((isValue(getVariableBR(t))!=-1?isValue(getVariableBR(t)):atof(getVariableBR(t)))*PI/180);
        else if(QString(t).toLower().contains("tan"))
            return tan((isValue(getVariableBR(t))!=-1?isValue(getVariableBR(t)):atof(getVariableBR(t)))*PI/180);
        else if(QString(t).toLower().contains("sum"))
            return SUM(getVariableBR(t));
    }
    return -1;
}

int  MainWindow::containsChar(char s[],char c)
{
    for(int i =0;s[i]!=0;i++)
        if(s[i]==c) return i;
    return -1;
}
void  MainWindow::deleteChar(char s[],char c)
{
    int i =0;
    for(i=containsChar(s,c);s[i]!=0;i++)
        s[i] = s[i+1];
    s[i+1]=0;
}
void  MainWindow::checkListItems(QStringList &list)
{
    for(int i=0;i<list.count();i++)
    {
        if(isValue(list[i].toUtf8().data())!=-1)
        {
            list.replace(i,QString::number(isValue(list[i].toUtf8().data()),'G',10));
            continue;
        }
        if(isFunc(list[i].toUtf8().data())!=-1)
        {
            list.replace(i,QString::number(isFunc(list[i].toUtf8().data()),'G',10));
            continue;
        }
    }
}

char*  MainWindow::calc(char* text)
{
    char signs[1000]; int iteratorI=0,i = 0; double out = 0; char* ret = new char[1000];
    for(;text[i]!=0;i++)
    {
        if(text[i]=='-'||text[i]=='+'||text[i]=='*'||text[i]==':')
        { signs[iteratorI] = text[i]; iteratorI++; }
    }
    QRegExp rx("(\\+|\\-|\\*|\\:)");
    QStringList l = QString(text).split(rx);
    for(int i = 0;i<l.count();i++)
    {
        if(l[i]=="")
        {
            l.replace(i+1,QString::number(-1*atof(l[i+1].toUtf8().data()),'G',10));
            for(int k = i;k<l.count();k++)
                signs[k] = signs[k+1];
            l.removeAt(i);
            iteratorI--;
        }
    }
    checkListItems(l);
    while(iteratorI>=1){
        if(containsChar(signs,'*')!=-1)
        {
            //15+521*(1+2*3)
            int j =containsChar(signs,'*');
            out = (atof(l[j].toUtf8().constData()))*(atof(l[j+1].toUtf8().constData()));
            l[j] = QString::number(out);
            for(int k=j+1;k<iteratorI;k++)
                l.replace(k,l[k+1]);
            if(l.count()>1) l.removeLast();
            deleteChar(signs,'*');
            iteratorI--;
        }
        else if(containsChar(signs,':')!=-1)
        {
            int j =containsChar(signs,':');
            out = (atof(l[j].toUtf8().constData()))/(atof(l[j+1].toUtf8().constData()));
            l[j] = QString::number(out);
            for(int k=j+1;k<iteratorI;k++)
                l.replace(k,l[k+1]);
            if(l.count()>1) l.removeLast();
            deleteChar(signs,':');
            iteratorI--;
        }
        else if(containsChar(signs,'+')!=-1)
        {
            int j = containsChar(signs,'+');
            out = (atof(l[j].toUtf8().constData()))+(atof(l[j+1].toUtf8().constData()));
            l[j] = QString::number(out);
            for(int k=j+1;k<iteratorI;k++)
                l.replace(k,l[k+1]);
            if(l.count()>1) l.removeLast();
            deleteChar(signs,'+');
            iteratorI--;
        }
        else if(containsChar(signs,'-')!=-1)
        {
            int j =containsChar(signs,'-');
            out = (atof(l[j].toUtf8().constData()))-(atof(l[j+1].toUtf8().constData()));
            l[j] = QString::number(out);
            for(int k=j+1;k<iteratorI;k++)
                l.replace(k,l[k+1]);
            if(l.count()>1) l.removeLast();
            deleteChar(signs,'-');
            iteratorI--;
        }
    }
    strcpy(ret,QString::number(out,'G',10).toUtf8().data());
    return ret;
}

bool  MainWindow::haveBrackets(char* t)
{
    QRegExp exp("\\((.*)\\)");
    if(exp.indexIn(t) >= 0)
    {
        return true;
    } else return false;
}
void  MainWindow::Parse(QTableWidgetItem *item)
{
    QString temp = item->text(); QString tempFunc = item->text();
    temp.remove("=");
    if(!haveBrackets(temp.toUtf8().data()))
    {
        QRegExp rx("(\\+|\\-|\\*|\\:)");
        QStringList list = temp.split(rx);
        if(list.count()>1)
            item->setText(QString(calc(item->text().remove("=").toUtf8().data())));
        else if(list.count()==1)
        {
            if(isValue(list[0].toUtf8().data())!=-1)
            {
                qDebug() << "is func epta : " << tempFunc << endl;
                item->setText(QString::number(isValue(list[0].toUtf8().data())));
                T->pushTo(item->row(),item->column(),QString::number(isValue(list[0].toUtf8().data())).toUtf8().data(),tempFunc.toUtf8().data());
                return;
            }
            if(isFunc(list[0].toUtf8().data())!=-1)
            {
                qDebug() << "is func epta : " << tempFunc << endl;
                item->setText(QString::number(isFunc(list[0].toUtf8().data())));
                T->pushTo(item->row(),item->column(),QString::number(isValue(list[0].toUtf8().data())).toUtf8().data(),tempFunc.toUtf8().data());
                return;
            }
        }
    }
    else
    {
        QString out = item->text().remove("="); QString temp = item->text();
        while(haveBrackets(out.toUtf8().data()))
        {
            QString t = out;
            while(haveBrackets(t.toUtf8().data()))
                t = QString(getVariable(t.toUtf8().data()));
            qDebug() << "func:    " << t;
            QString fix = QString("(%1)").arg(t);
            out = out.replace(fix,calc(t.toUtf8().data()));
            qDebug() << "OUT  :" << out;
            t.clear();
        }
        qDebug() << "is func epta : " << tempFunc << endl;
        T->pushTo(item->row(),item->column(),out.toUtf8().data(),temp.toUtf8().data());
        item->setText(out);
    }
}

void MainWindow::on_tableWidget_itemEntered(QTableWidgetItem *item)
{
    firstParse(item);
}

void MainWindow::on_tableWidget_itemClicked(QTableWidgetItem *item)
{
    qDebug() << "CLICKED ";
    ui->edit_func->setText(QString(T->getFunc(item->row(),item->column())));
}

void MainWindow::on_tableWidget_itemActivated(QTableWidgetItem *item)
{
    qDebug() << "QCTIVATED";
}

void MainWindow::on_tableWidget_itemPressed(QTableWidgetItem *item)
{
    qDebug() << "PRESSED";
    ui->edit_func->setText(QString(T->getFunc(item->row(),item->column())));
}

void MainWindow::on_tableWidget_itemSelectionChanged()
{
    QList<QModelIndex> list = ui->tableWidget->selectionModel()->selectedIndexes();
    if(list.count()==1)
        ui->edit_cur_item->setText(QString("%1%2").arg(QString(getCharFromPos(list[0].column()))).arg(QString::number(list[0].row()+1)));
    else if(list.count()>1)
    {
        int t = 0;
        ui->edit_cur_item->setText(QString("%1%2-%3%4").arg(QString(getCharFromPos(list[0].column())))
                .arg(QString::number(list[0].row()+1)).arg(QString(getCharFromPos(t!=0?t:list[list.count()-1].column()))).arg(QString::number(list[list.count()-1].row()+1)));
    }
}

void MainWindow::on_pushButton_clicked()
{
    funcHelp *h = new funcHelp();
    h->show();
}

void MainWindow::on_btn_home_clicked()
{
    T->printAll();
}

void MainWindow::on_btn_load_clicked()
{
    path = QFileDialog::getOpenFileName();
    FILE *fd = fopen(path.toUtf8().constData(),"r");
    ui->tableWidget->clear();
    while(!feof(fd))
    {
        int x,y;
        char *test = new char[256];
        char *test1 = new char[256];
        std::fread(&x,sizeof(int),1,fd);
        std::fread(&y,sizeof(int),1,fd);
        std::fread(&test,sizeof(char*),1,fd);
        std::fread(&test1,sizeof(char*),1,fd);
        T->pushTo(x,y,test,test1);
        QTableWidgetItem *item = new QTableWidgetItem(QString(test1));
        ui->tableWidget->setItem(x,y,item);
    }
    fclose(fd);
}

void MainWindow::on_btn_save_clicked()
{
    T->saveToFile(QFileDialog::getSaveFileName().toUtf8().data());
}

void MainWindow::on_action_triggered()
{
    newTable(100,100);
}

void MainWindow::on_open_triggered()
{
    on_btn_load_clicked();
}

void MainWindow::on_save_triggered()
{
    on_btn_save_clicked();
}

void MainWindow::on_exit_triggered()
{
    exit(1);
}

void MainWindow::on_func_help_triggered()
{
    funcHelp *h = new funcHelp();
    h->show();
}

void MainWindow::on_all_help_triggered()
{

}

void MainWindow::on_about_triggered()
{
    about *a = new about();
    a->show();
}

void MainWindow::newTable(int count_x,int count_y)
{
    List *t = new List();
    T = t;
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(count_x);
    ui->tableWidget->setRowCount(count_y);
    int countC = 0;
    for(int i=0;i<count_x;i++)
    {
        ui->tableWidget->setHorizontalHeaderItem(i,new QTableWidgetItem(QString(getCharFromPos(i))));
        ui->tableWidget->setColumnWidth(i,70);
        if(i/(countC+1)==strlen(colNames)) countC++;
        for(int j=0;j<count_y;j++)
            ui->tableWidget->setRowHeight(i,20);
    }
}

void MainWindow::on_tableWidget_viewportEntered()
{
    qDebug() << ui->tableWidget->pos();
}
