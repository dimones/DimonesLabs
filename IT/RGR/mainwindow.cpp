#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qfiledialog.h"


using namespace std;

elem table[24][30];

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
char MainWindow::getCharFromPos(int pos)
{
  return colNames[pos];
}
int MainWindow::getPosFromChar(char c)
{
  int out = 0,i=0;
  for(;i<strlen(colNames);i++)
    if(colNames[i]==c){
        out = i;
        return i;
      }
  return out;
}

char* MainWindow::getValueFromItem(int row,char col)
{
  char* out = new char[100];
  strcpy(out,table[row][getPosFromChar(col)].value);
  return out;
}

char* MainWindow::getVariable(char *text)//получение строки между скобками
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
/*
char* getVariable(char *text)//получение строки между скобками
{
  char* out= new char[100];
  QRegExp exp("\\{(.*)\\}");
  if(exp.indexIn(text) >= 0)
    {
      strcpy(out,exp.cap(1).toUtf8().constData());
    }
  qDebug() << "BR: " << out;
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
          pos+=exp.matchedLength();
        }
    }
  return out;
}*/

double MainWindow::isValue(char* t)
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

double MainWindow::SUM(char* text)
{
  double out = 0;
  qDebug() <<"INPUT TEXT:" <<text;
  QStringList list = QString(text).split(";");
  qDebug() << "COUNT:" << list.count();
  checkItemsInList(list);
  for(int i =0;i<list.count();i++)
    {
      out+=atof(list[i].toUtf8().constData());
    }
  qDebug() << "SUM: "<< out;
  return out;
}

double MainWindow::isFunc(char* t){
  qDebug()<<"isFunc(atof test): " << atof(t);
  qDebug() << endl;
  if(atof(t)==0)
    {
      qDebug() << "isFunc: " << t;
      qDebug() << endl;
      if (QString(t).toLower().contains("abs"))
        {
          return isValue(t)!=-1 ? (double)abs((int)isValue(getVariable(t))) : -1;
        }
      else if(QString(t).toLower().contains("asin"))
        {
          return isValue(t)!=-1?sin(isValue(getVariable(t))):-1;
        }
      else if(QString(t).toLower().contains("atan"))
        {
          return isValue(t)!=-1?atan(isValue(getVariable(t))):-1;
        }
      else if(QString(t).toLower().contains("cos"))
        {
          return isValue(t)!=-1?cos(isValue(getVariable(t))):-1;
        }
      else if(QString(t).toLower().contains("exp"))
        {
          return isValue(t)!=-1?exp(isValue(getVariable(t))):-1;
        }
      else if(QString(t).toLower().contains("floor"))
        {
          return isValue(t)!=-1?floor(isValue(getVariable(t))):-1;
        }
      else if(QString(t).toLower().contains("log10"))
        {
          return isValue(t)!=-1?log10(isValue(getVariable(t))):-1;
        }
      else if(QString(t).toLower().contains("log"))
        {
          return isValue(t)!=-1?log(isValue(getVariable(t))):-1;
        }
      else if(QString(t).toLower().contains("max"))
        {
          //return (atof(getVariable(t)));
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
          return isValue(t)!=-1?round(isValue(getVariable(t))):-1;
        }
      else if(QString(t).toLower().contains("sinh"))
        {
          return isValue(t)!=-1?sinh(isValue(getVariable(t))):-1;
        }
      else if(QString(t).toLower().contains("sin"))
        {
          return isValue(t)!=-1?sin(isValue(getVariable(t))):-1;
        }
      else if(QString(t).toLower().contains("sqrt"))
        {
          return isValue(t)!=-1?sqrt(isValue(getVariable(t))):-1;
        }
      else if(QString(t).toLower().contains("tanh"))
        {
          return isValue(t)!=-1?tanh(isValue(getVariable(t))):-1;
        }
      else if(QString(t).toLower().contains("tan"))
        {
          return isValue(t)!=-1?tan(isValue(getVariable(t))):-1;
        }
      else if(QString(t).toLower().contains("sum"))
        {
          return SUM(getVariable(t));
        }
    }
  return -1;
}

int MainWindow::containsChar(char s[],char c)
{
  for(int i =0;s[i]!=0;i++)
    if(s[i]==c) return i;
  return -1;
}
void MainWindow::deleteChar(char s[],char c)
{
  int i =0;
  for(i=containsChar(s,c);s[i]!=0;i++)
    s[i] = s[i+1];
  s[i+1]=0;
}
void MainWindow::checkItemsInList(QStringList &list)
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


char* MainWindow::calc(char* text)
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
  checkItemsInList(l);
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

bool MainWindow::haveBrackets(char* t)
{
  QRegExp exp("\\((.*)\\)");
  if(exp.indexIn(t) >= 0)
    {
      return true;
    }else return false;
}

void MainWindow::superParser(QTableWidgetItem *item)
{
  char* functemp = new char[1000];
  QString temp = QString(item->text()); strcpy(functemp,temp.toUtf8().constData());
  /*
  if(isFuncEq(temp.toUtf8().data())!=-1)
    {
      qDebug() << "OOPS FORM FUNC";
      if(!haveBrackets(item->text().toUtf8().data()))
        {
          strcpy(functemp,QString("=%1").arg(temp).toUtf8().constData());
          temp = QString("%1").arg(temp);
        }
      else strcpy(functemp,item->text().toUtf8().constData());
      strcpy(table[item->row()][item->column()].func,functemp);
      if(!haveBrackets(item->text().toUtf8().data()))
        item->setText(QString::number(isFunc(temp.toUtf8().data())));
      else item->setText(QString::number(isFunc(getVariable(temp.toUtf8().data()))));
    }
  else
    {
      temp.remove("=");
      if(isValue(temp.toUtf8().data())!=-1)
        {
          qDebug() << "OOPS";
          if(isValue(temp.toUtf8().data()))
            {
              char* tem = new char[100]; char* tem2 = new char[100];
              strcpy(tem,temp.toUtf8().constData()); strcpy(tem2,item->text().toUtf8().constData());
              strcpy(table[item->row()][item->column()].func,tem2);
              item->setText(QString::number(isValue(tem)));
            }
        }*/
  /*if(!haveBrackets(item->text().toUtf8().data()))
    {
      strcpy(functemp,QString("=(%1)").arg(temp).toUtf8().constData());
      temp = QString("%1").arg(temp);
    }
  else strcpy(functemp,item->text().toUtf8().constData());*/
  temp.remove("=");
  qDebug() << temp;
  qDebug() << endl;
  QRegExp rx("(\\+|\\-|\\*|\\:)");
  QStringList list = temp.split(rx);
  qDebug() << "SUPER: " << list.count();
  char* out = new char[100];
  strcpy(out,temp.toUtf8().constData());
  if(list.count()==1)
    {
/*
      if(isFunc(temp.toUtf8().data())!=-1)
        {
          qDebug()<<temp;
          strcpy(table[item->row()][item->column()].func,temp.toUtf8().constData());
          item->setText(QString::number(isFunc(getVariable(temp.toUtf8().data()))));
        }*/
      if(isValue(temp.toUtf8().data())!=-1)
        {
          strcpy( table[item->row()][item->column()].func,temp.toUtf8().constData());
          item->setText(QString::number(isValue(temp.toUtf8().data())));
          /*
          char* tem = new char[100]; char* tem2 = new char[100];
          strcpy(tem,temp.toUtf8().constData()); strcpy(tem2,item->text().toUtf8().constData());
          strcpy( table[item->row()][item->column()].func,tem2);
          item->setText(QString::number(isValue(tem)));*/
        }
    }
  else
    {
      while(haveBrackets(out))
        {
          char* t = new char[1000]; strcpy(t,out);
          while(haveBrackets(t))
            {
              strcpy(t,getVariable(t));
            }
          char* t2 = new char[1000];
          QString fix = QString("(%1)").arg(t);
          strcpy(t2,QString(out).replace(fix,calc(t)).remove("=").toUtf8().constData());
          qDebug()<<"many func: " << t2;
          strcpy(out,t2);
        }
      item->setText(out);
      strcpy( table[item->row()][item->column()].func,functemp);
    }
}


void MainWindow::Parser(QTableWidgetItem *item)
{
  if(item->text().contains("=")) superParser(item);
  else {
      char* temp = new char[100];
      strcpy(temp,item->text().toUtf8().constData());
      strcpy( table[item->row()][item->column()].func,temp);
      strcpy( table[item->row()][item->column()].value,temp);
    }
}

void MainWindow::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
  Parser(item);
  ui->lineEdit->setText(item->text());
}

void MainWindow::on_tableWidget_itemClicked(QTableWidgetItem *item)
{
  if( table[item->row()][item->column()].func[0]!='\0')
    {
      ui->lineEdit->setText( table[item->row()][item->column()].func);
    }else ui->lineEdit->setText("");
}

void MainWindow::on_pushButton_clicked()
{
}

void MainWindow::on_tableWidget_itemDoubleClicked(QTableWidgetItem *item)
{
  item->setText( table[item->row()][item->column()].func);
}

void MainWindow::on_tableWidget_itemPressed(QTableWidgetItem *item)
{
  item->setText( table[item->row()][item->column()].func);
}

void MainWindow::on_tableWidget_itemEntered(QTableWidgetItem *item)
{
  item->setText( table[item->row()][item->column()].func);
}

void MainWindow::on_pushButton_3_clicked()
{
  QString path = QFileDialog::getSaveFileName();
  FILE *fd = fopen(path.toUtf8().constData(),"wb+");
  fwrite(& table,sizeof( table),1,fd);
  fclose(fd);
}

void MainWindow::on_pushButton_2_clicked()
{
  QString path = QFileDialog::getOpenFileName();
  if(path!=NULL)
    {
      for(int i=0;i<24;i++)
        {
          for(int j=0;j<30;j++)
            {
              strcpy( table[i][j].func,"");
              strcpy( table[i][j].value,"");
               table[i][j].type = 1;
               table[i][j].X = i;
               table[i][j].Y = j;
            }
        }
      FILE *fd = fopen(path.toUtf8().constData(),"r");
      fread(& table,sizeof( table),1,fd);
      ui->tableWidget->clear();
      for(int i=0;i<24;i++)
        {
          ui->tableWidget->setHorizontalHeaderItem(i,new QTableWidgetItem(QChar(colNames[i])));
          for(int j=0;j<30;j++)
            {
              /*strcpy( table[i][j].value,"");

               table[i][j].value = temp[i][j].value;
               table[i][j].func = temp[i][j].func;
               table[i][j].type = temp[i][j].type;
               table[i][j].X = temp[i][j].X;*/
              QTableWidgetItem *item = new QTableWidgetItem(QString( table[i][j].value));
              ui->tableWidget->setItem(i,j,item);
            }
        }
      fclose(fd);
    }
}

void MainWindow::on_pushButton_4_clicked()
{

}
