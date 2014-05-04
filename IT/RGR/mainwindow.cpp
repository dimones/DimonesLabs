#include "mainwindow.h"
#include "ui_mainwindow.h"


using namespace std;
char colNames[25] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','V','X','Y','Z'};
struct item{
  int type;
  int X,Y;
  char func[256];
  char value[256];
};

item table[24][30];

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)//Конструктор окна
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

MainWindow::~MainWindow()//деструктор
{
  delete ui;
}
char getCharFromPos(int pos)
{
  return colNames[pos];
}
int getPosFromChar(char c)
{
  int out,i=0;
  for(;i<strlen(colNames);i++)
    if(colNames[i]==c){
        out = i;
        return i;
      }
  return out;
}

char* getValueFromItem(int row,char col)
{
  char* out = new char[100];
  strcpy(out,table[row][getPosFromChar(col)].value);
  return out;
}

char* getVariable(char *text)//получение строки между скобками
{
  char* out= new char[64];
  QRegExp exp("\\((.*)\\)");
  if(exp.indexIn(text) >= 0)
    {
      strcpy(out,exp.cap(1).toUtf8().constData());
    }
  qDebug() << out;
  return out;
}
char* getVariable2(char *text)//получение строки между скобками
{
  char* out= new char[64];
  QRegExp exp("\\((.*)\\)");
  if(exp.indexIn(text) >= 0)
    {
      strcpy(out,exp.cap(1).toUtf8().constData());
      QStringList list; int pos = 0;
      while((pos = exp.indexIn(text,pos))!=-1)
        {
          list << exp.cap(2);
          //qDebug() << exp.cap(2);
          pos+=exp.matchedLength();
        }/*
      for(int i =0;i<pos;i++)
       {
          qDebug() << list[i];
        }*/
    }
  return out;
}
double isValue(char* t)
{
  qDebug() << "isValue: " << atof(t);
  qDebug() << endl;
  if(atof(t)==0)
    {
      int row = strlen(t)!=2?((t[1]-'0')*10+(t[2]-'0')):(t[1]-'0'); char col = t[0];
      qDebug() << "ROW: "<< row<<"   COL: " << col;
      if(table[row-1][getPosFromChar(col)-1].value!=NULL)
        {
          return atof(table[row-1][getPosFromChar(col)].value);
        }
    }
  return -1;
}
double SUM(char* text)
{
  double out;
  qDebug() <<"INPUT TEXT:" <<text;
  QStringList list = QString(text).split(";");
  qDebug() << "COUNT:" << list.count();
  for(int i =0;i<list.count();i++)
    {
      out+=atof(list[i].toUtf8().constData());
    }
  qDebug() << "SUM: "<< out;
  return out;
}

int containsChar(char s[],char c)
{
  for(int i =0;s[i]!=0;i++)
    if(s[i]==c) return i;
  return -1;
}
void deleteChar(char s[],char c)
{
  int i =0;
  for(i=containsChar(s,c);s[i]!=0;i++)
    s[i] = s[i+1];
  s[i+1]=0;
}
void checkListItems(QStringList &list)
{
  for(int i=0;i<list.count();i++)
    {
      if(isValue(list[i].toUtf8().data())!=-1)
        {
          list.replace(i,QString::number(isValue(list[i].toUtf8().data())));
          qDebug() << endl;
        }
    }
}

char* calc(char* text)
{
  char signs[32]; int iteratorI=0,i = 0; double out = 0,temp; char* ret = new char[1000];
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
  qDebug() << "OUT: " << out << endl;
  strcpy(ret,QString::number(out).toUtf8().constData());
  return ret;
}

bool haveBrackets(char* t)
{
  QRegExp exp("\\((.*)\\)");
  qDebug()<<exp.captureCount();
  if(exp.indexIn(t) >= 0)
    {
      qDebug() <<"FROM BRACKETS: " <<  exp.cap(1);
      return true;
    }else return false;
}


void SUPERPARSER(QTableWidgetItem *item)
{
  char* functemp = new char[1000];

  QString temp = QString(item->text());
  temp.remove("=");
  if(!haveBrackets(item->text().toUtf8().data()))
    {
      strcpy(functemp,QString("=(%1)").arg(temp).toUtf8().constData());
      temp = QString("(%1)").arg(temp);
    }
  else strcpy(functemp,item->text().toUtf8().constData());
  qDebug() << temp;
  qDebug() << endl;
  QRegExp rx("(\\+|\\-|\\*|\\:)");
  QStringList list = temp.split(rx);
  qDebug() << "SUPER: " << list.count();
  char* out = new char[100];
  strcpy(out,temp.toUtf8().constData());
  if(list.count()==1)
    {
      if(isValue)
        {
          char* tem = new char[100]; char* tem2 = new char[100];
          strcpy(tem,temp.toUtf8().constData()); strcpy(tem2,item->text().toUtf8().constData());
          strcpy(table[item->row()][item->column()].func,tem2);
          item->setText(QString::number(isValue(tem)));
        }
    }
  else
    {
      int i = 0;
      while(haveBrackets(out))
        {
          char* t = new char[1000]; strcpy(t,out);
          while(haveBrackets(t))
            {
              strcpy(t,getVariable2(t));
            }
          char* t2 = new char[1000];
          QString fix = QString("(%1)").arg(t);
          strcpy(t2,QString(out).replace(fix,calc(t)).toUtf8().constData());
          qDebug()<<t2;
          qDebug()<<endl;
          strcpy(out,t2);
        }
      item->setText(out);
      strcpy(table[item->row()][item->column()].func,functemp);
    }
}

void Parser(QTableWidgetItem *item)
{
  if (item->text().toLower().contains("=abs"))
    {
      char* temp = new char[100];
      strcpy(temp,item->text().toLower().toUtf8().constData());
      strcpy(table[item->row()][item->column()].func,item->text().toLower().toUtf8().constData());//записали в функцию то что мы наделали
      strcpy(table[item->row()][item->column()].value,QString::number(abs(atoi(getVariable(temp)))).toUtf8().constData());
      item->setText(QString(table[item->row()][item->column()].value));
    }
  else if(item->text().toLower().contains("=asin"))
    {
      char* temp = new char[100];
      strcpy(temp,item->text().toLower().toUtf8().constData());
      strcpy(table[item->row()][item->column()].func,item->text().toLower().toUtf8().constData());//записали в функцию то что мы наделали
      strcpy(table[item->row()][item->column()].value,QString::number(asin(atof(getVariable(temp)))).toUtf8().constData());
      item->setText(QString(table[item->row()][item->column()].value));
    }
  else if(item->text().toLower().contains("=atan"))
    {
      char* temp = new char[100];
      strcpy(temp,item->text().toLower().toUtf8().constData());
      strcpy(table[item->row()][item->column()].func,item->text().toLower().toUtf8().constData());//записали в функцию то что мы наделали
      strcpy(table[item->row()][item->column()].value,QString::number(atan(atof(getVariable(temp)))).toUtf8().constData());
      item->setText(QString(table[item->row()][item->column()].value));
    }
  else if(item->text().toLower().contains("=cos"))
    {
      char* temp = new char[100];
      strcpy(temp,item->text().toLower().toUtf8().constData());
      strcpy(table[item->row()][item->column()].func,item->text().toLower().toUtf8().constData());//записали в функцию то что мы наделали
      strcpy(table[item->row()][item->column()].value,QString::number(cos(atof(getVariable(temp)))).toUtf8().constData());
      item->setText(QString(table[item->row()][item->column()].value));
    }
  else if(item->text().toLower().contains("=exp"))
    {
      char* temp = new char[100];
      strcpy(temp,item->text().toLower().toUtf8().constData());
      strcpy(table[item->row()][item->column()].func,item->text().toLower().toUtf8().constData());//записали в функцию то что мы наделали
      strcpy(table[item->row()][item->column()].value,QString::number(exp(atof(getVariable(temp)))).toUtf8().constData());
      item->setText(QString(table[item->row()][item->column()].value));
    }
  else if(item->text().toLower().contains("=floor"))
    {
      char* temp = new char[100];
      strcpy(temp,item->text().toLower().toUtf8().constData());
      strcpy(table[item->row()][item->column()].func,item->text().toLower().toUtf8().constData());//записали в функцию то что мы наделали
      strcpy(table[item->row()][item->column()].value,QString::number(floor(atof(getVariable(temp)))).toUtf8().constData());
      item->setText(QString(table[item->row()][item->column()].value));

    }
  else if(item->text().toLower().contains("=log10"))
    {
      char* temp = new char[100];
      strcpy(temp,item->text().toLower().toUtf8().constData());
      strcpy(table[item->row()][item->column()].func,item->text().toLower().toUtf8().constData());//записали в функцию то что мы наделали
      strcpy(table[item->row()][item->column()].value,QString::number(log10(atof(getVariable(temp)))).toUtf8().constData());
      item->setText(QString(table[item->row()][item->column()].value));
    }
  else if(item->text().toLower().contains("=log"))
    {
      char* temp = new char[100];
      strcpy(temp,item->text().toLower().toUtf8().constData());
      strcpy(table[item->row()][item->column()].func,item->text().toLower().toUtf8().constData());//записали в функцию то что мы наделали
      strcpy(table[item->row()][item->column()].value,QString::number(log(atof(getVariable(temp)))).toUtf8().constData());
      item->setText(QString(table[item->row()][item->column()].value));
    }
  else if(item->text().toLower().contains("=max"))
    {
      char* temp = new char[100];
      strcpy(temp,item->text().toLower().toUtf8().constData());
      strcpy(table[item->row()][item->column()].func,item->text().toLower().toUtf8().constData());//записали в функцию то что мы наделали
      strcpy(table[item->row()][item->column()].value,QString::number(abs(atoi(getVariable(temp)))).toUtf8().constData());
      item->setText(QString(table[item->row()][item->column()].value));
    }
  else if(item->text().toLower().contains("=min"))
    {
      char* temp = new char[100];
      strcpy(temp,item->text().toLower().toUtf8().constData());
      strcpy(table[item->row()][item->column()].func,item->text().toLower().toUtf8().constData());//записали в функцию то что мы наделали
      //itoa(cos(atof(out)),table[item->row()][item->column()].value,10);//получаем значение выполненной функции
      item->setText(QString(table[item->row()][item->column()].value));
    }
  else if(item->text().toLower().contains("=pow"))
    {
      char* temp = new char[100];
      strcpy(temp,item->text().toLower().toUtf8().constData());
      strcpy(table[item->row()][item->column()].func,item->text().toLower().toUtf8().constData());//записали в функцию то что мы наделали
      //itoa(cos(atof(out)),table[item->row()][item->column()].value,10);//получаем значение выполненной функции
      item->setText(QString(table[item->row()][item->column()].value));
    }
  else if(item->text().toLower().contains("=round"))
    {
      char* temp = new char[100];
      strcpy(temp,item->text().toLower().toUtf8().constData());
      strcpy(table[item->row()][item->column()].func,item->text().toLower().toUtf8().constData());//записали в функцию то что мы наделали
      strcpy(table[item->row()][item->column()].value,QString::number(round(atof(getVariable(temp)))).toUtf8().constData());
      item->setText(QString(table[item->row()][item->column()].value));
    }
  else if(item->text().toLower().contains("=sinh"))
    {
      char* temp = new char[100];
      strcpy(temp,item->text().toLower().toUtf8().constData());
      strcpy(table[item->row()][item->column()].func,item->text().toLower().toUtf8().constData());//записали в функцию то что мы наделали
      strcpy(table[item->row()][item->column()].value,QString::number(sinh(atof(getVariable(temp)))).toUtf8().constData());
      item->setText(QString(table[item->row()][item->column()].value));
    }
  else if(item->text().toLower().contains("=sin"))
    {
      char* temp = new char[100];
      strcpy(temp,item->text().toLower().toUtf8().constData());
      strcpy(table[item->row()][item->column()].func,item->text().toLower().toUtf8().constData());//записали в функцию то что мы наделали
      strcpy(table[item->row()][item->column()].value,QString::number(sin(atof(getVariable(temp)))).toUtf8().constData());
      item->setText(QString(table[item->row()][item->column()].value));
    }
  else if(item->text().toLower().contains("=sqrt"))
    {
      char* temp = new char[100];
      strcpy(temp,item->text().toLower().toUtf8().constData());
      strcpy(table[item->row()][item->column()].func,item->text().toLower().toUtf8().constData());//записали в функцию то что мы наделали
      strcpy(table[item->row()][item->column()].value,QString::number(sqrt(atof(getVariable(temp)))).toUtf8().constData());
      item->setText(QString(table[item->row()][item->column()].value));
    }
  else if(item->text().toLower().contains("=tanh"))
    {
      char* temp = new char[100];
      strcpy(temp,item->text().toLower().toUtf8().constData());
      strcpy(table[item->row()][item->column()].func,item->text().toLower().toUtf8().constData());//записали в функцию то что мы наделали
      strcpy(table[item->row()][item->column()].value,QString::number(tanh(atof(getVariable(temp)))).toUtf8().constData());
      item->setText(QString(table[item->row()][item->column()].value));
    }
  else if(item->text().toLower().contains("=tan"))
    {
      char* temp = new char[100];
      strcpy(temp,item->text().toLower().toUtf8().constData());
      strcpy(table[item->row()][item->column()].func,item->text().toLower().toUtf8().constData());//записали в функцию то что мы наделали

      strcpy(table[item->row()][item->column()].value,QString::number(tan(atof(getVariable(temp)))).toUtf8().constData());
      item->setText(QString(table[item->row()][item->column()].value));
    }
  else if(item->text().toLower().contains("=sum"))
    {
      char* temp = new char[100];
      strcpy(temp,item->text().toLower().toUtf8().constData());
      strcpy(table[item->row()][item->column()].func,item->text().toLower().toUtf8().constData());//записали в функцию то что мы наделали
      strcpy(table[item->row()][item->column()].value,QString::number(SUM(getVariable(temp))).toUtf8().constData());
      item->setText(QString(table[item->row()][item->column()].value));
    }
  else if(item->text().contains("=")) SUPERPARSER(item);
  else {
      char* temp = new char[100];
      strcpy(temp,item->text().toUtf8().constData());
      strcpy(table[item->row()][item->column()].func,temp);
      strcpy(table[item->row()][item->column()].value,temp);
    }
}

void MainWindow::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
  Parser(item);
  ui->lineEdit->setText(item->text());
}

void MainWindow::on_tableWidget_itemClicked(QTableWidgetItem *item)
{
  if(table[item->row()][item->column()].func[0]!='\0')
    {
      ui->lineEdit->setText(table[item->row()][item->column()].func);
    }else ui->lineEdit->setText("");
}

void MainWindow::on_pushButton_clicked()
{
  Functions *func = new Functions();
  func->show();
}

void MainWindow::on_tableWidget_itemDoubleClicked(QTableWidgetItem *item)
{
  item->setText(table[item->row()][item->column()].func);
}

void MainWindow::on_tableWidget_itemPressed(QTableWidgetItem *item)
{
  item->setText(table[item->row()][item->column()].func);
}

void MainWindow::on_tableWidget_itemEntered(QTableWidgetItem *item)
{
  item->setText(table[item->row()][item->column()].func);
}
