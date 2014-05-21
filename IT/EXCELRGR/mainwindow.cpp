#include "mainwindow.h"
#include "ui_mainwindow.h"



char colNames[24] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','V','X','Y','Z'};


struct item{
    int type;
    int X,Y;
    char func[256];
    char value[256];
};
item table[24][30];

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(24);
    ui->tableWidget->setRowCount(30);
    for(int i=0;i<24;i++)
      {
        ui->tableWidget->setHorizontalHeaderItem(i,new QTableWidgetItem(QChar(colNames[i])));
        ui->tableWidget->setColumnWidth(i,70);
        for(int j=0;j<30;j++)
          {
            ui->tableWidget->setRowHeight(i,20);
            table[i][j].type = 1;
            table[i][j].X = j;
            table[i][j].Y = i;
          }
      }
}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    Parse(item);
}
char  MainWindow::getCharFromPos(int pos)
{
    return  colNames[pos];
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

char*  MainWindow::getValueFromItem(int row,char col)
{
    char* out = new char[strlen(table[row][getPosFromChar(col)].value)];
    strcpy(out,table[row][getPosFromChar(col)].value);
    return out;
}

char*  MainWindow::getVariable(char *text)//получение строки между скобками
{
    QRegExp exp("\\((.*)\\)"); int s = 0;
    if(exp.indexIn(text) >= 0)
    {
        s = 1;
    }
    qDebug() << exp.cap(1).toUtf8().data();
    return s==1?exp.cap(1).toUtf8().data():NULL;
}
char*  MainWindow::getVariableBR(char *text)//получение строки между скобками
{
    QRegExp exp("\\{(.*)\\}"); int s = 0;
    if(exp.indexIn(text) >= 0)
    {
        s = 1;
    }
    qDebug() << exp.cap(1).toUtf8().data();
    return s==1?exp.cap(1).toUtf8().data():NULL;
}

double  MainWindow::isValue(char* t)
{
    if(atof(t)==0)
    {
        int row = strlen(t)!=2?((t[1]-'0')*10+(t[2]-'0')):(t[1]-'0'); char col = t[0];
        qDebug() << "ROW: "<< row<<"   COL: " << col;
        if(table[row][getPosFromChar(col)].value!=NULL)
        {
            return atof(table[row][getPosFromChar(col)].value);
        }
    }
    return -1;
}
double  MainWindow::SUM(char* text)
{
    double out = 0;
    qDebug() <<"INPUT TEXT:" <<text;
    QStringList list = QString(text).split(";");
    qDebug() << "COUNT:" << list.count();
    checkListItems(list); //TODO
    for(int i =0;i<list.count();i++)
    {
        out+=isValue(list[i].toUtf8().data())!=-1?isValue(list[i].toUtf8().data()):0.0;
    }
    qDebug() << "SUM: "<< out;
    return out;
}

double  MainWindow::isFunc(char* t){
    qDebug()<<"isFunc(atof test): " << atof(t);
    qDebug() << endl;
    qDebug() << "ATOI ISALNUM" << isalnum(atoi(t));
    if(atof(t)==0)
    {
        qDebug() << "isFunc: " << t;
        qDebug() << endl;
        if (QString(t).toLower().contains("abs"))
        {
            return isValue(t)!=-1 ? (double)abs((int)isValue(getVariableBR(t))) : -1;
        }
        else if(QString(t).toLower().contains("asin"))
        {
            return isValue(t)!=-1?sin(isValue(getVariableBR(t))):-1;
        }
        else if(QString(t).toLower().contains("atan"))
        {
            return isValue(t)!=-1?atan(isValue(getVariableBR(t))):-1;
        }
        else if(QString(t).toLower().contains("cos"))
        {
            return isValue(t)!=-1?cos(isValue(getVariableBR(t))):-1;
        }
        else if(QString(t).toLower().contains("exp"))
        {
            return isValue(t)!=-1?exp(isValue(getVariableBR(t))):-1;
        }
        else if(QString(t).toLower().contains("floor"))
        {
            return isValue(t)!=-1?floor(isValue(getVariableBR(t))):-1;
        }
        else if(QString(t).toLower().contains("log10"))
        {
            return isValue(t)!=-1?log10(isValue(getVariableBR(t))):-1;
        }
        else if(QString(t).toLower().contains("log"))
        {
            return isValue(t)!=-1?log(isValue(getVariableBR(t))):-1;
        }
        else if(QString(t).toLower().contains("max"))
        {
            //return (atof(getVariableBR(t)));
        }
        else if(QString(t).toLower().contains("min"))
        {
            //
        }
        else if(QString(t).toLower().contains("pow"))
        {
            //
        }
        else if(QString(t).toLower().contains("round"))
        {
            return isValue(t)!=-1?round(isValue(getVariableBR(t))):-1;
        }
        else if(QString(t).toLower().contains("sinh"))
        {
            return isValue(t)!=-1?sinh(isValue(getVariableBR(t))):-1;
        }
        else if(QString(t).toLower().contains("sin"))
        {
            return isValue(t)!=-1?sin(isValue(getVariableBR(t))):-1;
        }
        else if(QString(t).toLower().contains("sqrt"))
        {
            return isValue(t)!=-1?sqrt(isValue(getVariableBR(t))):-1;
        }
        else if(QString(t).toLower().contains("tanh"))
        {
            return isValue(t)!=-1?tanh(isValue(getVariableBR(t))):-1;
        }
        else if(QString(t).toLower().contains("tan"))
        {
            return isValue(t)!=-1?tan(isValue(getVariableBR(t))):-1;
        }
        else if(QString(t).toLower().contains("sum"))
        {
            return SUM(getVariableBR(t));
        }
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
        if(isFunc(list[i].toUtf8().data())!=-1)
        {
            qDebug() << "FUNC BEFORE: " << list[i];
            list.replace(i,QString::number(isFunc(list[i].toUtf8().data())));
        }
        if(isValue(list[i].toUtf8().data())!=-1)
        {
            list.replace(i,QString::number(isValue(list[i].toUtf8().data())));
        }
    }
}

char*  MainWindow::calc(char* text)
{
    char signs[32]; int iteratorI=0,i = 0; double out = 0; char* ret = new char[1000];
    for(;text[i]!=0;i++)
    {
        if(text[i]=='-'||text[i]=='+'||text[i]=='*'||text[i]==':')
        { signs[iteratorI] = text[i]; iteratorI++; }
    }
    qDebug()<< text;
    QRegExp rx("(\\+|\\-|\\*|\\:)");
    QStringList l = QString(text).split(rx);
    qDebug() << "COUNT: " << l.count() << " LIST:" << l;
    checkListItems(l);
    qDebug() << "NEW COUNT: " << l.count() << " LIST:" << l<< "  ITERATOR: " << iteratorI <<" SIGNS:" << signs;
    while(iteratorI>0){
        if(containsChar(signs,'*')!=-1)
        {
            //15+521*(1+2*3)
            int j =containsChar(signs,'*');
            out = (atof(l[j].toUtf8().constData()))*(atof(l[j+1].toUtf8().constData()));
            l[j] = QString::number(out);
            for(int k=j;k<iteratorI-1;k++)
                l.insert(k,l[k+1]);
            if(l.count()>1) l.removeLast();
            deleteChar(signs,'*');
            iteratorI--;
        }
        else if(containsChar(signs,':')!=-1)
        {
            int j =containsChar(signs,':');
            out = (atof(l[j].toUtf8().constData()))/(atof(l[j+1].toUtf8().constData()));
            l[j] = QString::number(out);
            for(int k=j;k<iteratorI-1;k++)
                l.insert(k,l[k+1]);
            if(l.count()>1) l.removeLast();
            deleteChar(signs,':');
            iteratorI--;
        }
        else if(containsChar(signs,'+')!=-1)
        {
            int j =containsChar(signs,'+');
            out = (atof(l[j].toUtf8().constData()))+(atof(l[j+1].toUtf8().constData()));
            l[j] = QString::number(out);
            for(int k=j;k<iteratorI-1;k++)
                l.insert(k,l[k+1]);
            if(l.count()>1) l.removeLast();
            deleteChar(signs,'+');
            iteratorI--;
        }
        else if(containsChar(signs,'-')!=-1)
        {
            int j =containsChar(signs,'-');
            out = (atof(l[j].toUtf8().constData()))-(atof(l[j+1].toUtf8().constData()));
            l[j] = QString::number(out);
            for(int k=j;k<iteratorI-1;k++)
                l.insert(k,l[k+1]);
            if(l.count()>1) l.removeLast();
            deleteChar(signs,'-');
            iteratorI--;
        }
    }
    strcpy(ret,QString::number(out).toUtf8().constData());
    return ret;
}

bool  MainWindow::haveBrackets(char* t)
{
    QRegExp exp("\\((.*)\\)");
    if(exp.indexIn(t) >= 0)
    {
        return true;
    }else return false;
}
void  MainWindow::Parse(QTableWidgetItem *item)
{
    if(item->text().contains("="))
    {
        char* functemp = new char[strlen(item->text().toUtf8().data())];
        QString temp = QString(item->text()); strcpy(functemp,temp.toUtf8().constData());
        temp.remove("=");
        QRegExp rx("(\\+|\\-|\\*|\\:)");
        QStringList list = temp.split(rx);
        qDebug() << "Parser count: " << list.count();
        char* out = new char[strlen(temp.toUtf8().data())];
        strcpy(out,temp.toUtf8().constData());
        if(!haveBrackets(temp.toUtf8().data()))
        {
            strcpy(functemp,QString("=(%1)").arg(temp).toUtf8().constData());
            temp = QString("(%1)").arg(temp);
        }
        else strcpy(functemp,temp.toUtf8().constData());
        if(list.count()==1)
        {
            if(temp.remove("=").toInt()!=0)
            {
                strcpy(table[item->row()][item->column()].func,item->text().contains("=")?item->text().remove("=").toUtf8().constData():item->text().toUtf8().constData());
                strcpy(table[item->row()][item->column()].value,item->text().contains("=")?item->text().toUtf8().constData():item->text().remove("=").toUtf8().constData());
                return;
            }

            if(isFunc(temp.toUtf8().data())!=-1)
            {
                qDebug() << temp;
                item->setText(QString::number(isFunc(getVariable(temp.toUtf8().data()))));
                strcpy(table[item->row()][item->column()].func,temp.toUtf8().constData());
                strcpy(table[item->row()][item->column()].value,item->text().toUtf8().constData());
            }
            if(isValue(temp.toUtf8().data())!=-1)
            {
                strcpy(table[item->row()][item->column()].func,temp.toUtf8().constData());
                item->setText(QString::number(isValue(getVariable(temp.toUtf8().data()))));
                strcpy(table[item->row()][item->column()].value,item->text().toUtf8().constData());
            }
        }
        else
        {
            char* t = new char[1000]; strcpy(t,out);
            while(haveBrackets(out))
            {
                while(haveBrackets(t))
                    strcpy(t,getVariable(t));
                char* t2 = new char[1000];
                QString fix = QString("(%1)").arg(t);
                strcpy(t2,QString(out).replace(fix,calc(t)).remove(("=")).toUtf8().constData());
                qDebug() << "BIG FUNC: " << t2;
                strcpy(out,t2);
            }
            item->setText(out);
            strcpy(table[item->row()][item->column()].func,functemp);
        }
    }
    else
    {
        strcpy(table[item->row()][item->column()].func,item->text().contains("=")?item->text().remove("=").toUtf8().constData():item->text().toUtf8().constData());
        strcpy(table[item->row()][item->column()].value,item->text().contains("=")?item->text().toUtf8().constData():item->text().remove("=").toUtf8().constData());
        return;
    }



}
