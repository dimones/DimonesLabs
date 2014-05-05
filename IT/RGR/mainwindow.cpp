#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qfiledialog.h"


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
  int out = 0,i=0;
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
char* getVariableBR(char *text)//получение строки между скобками
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
}
double isValue(char* t)
{
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
double isFuncSUM(char* t){
  qDebug()<<"isFunc(atof test): " << atof(t);
  qDebug() << endl;
  if(atof(t)==0)
    {
      qDebug() << "isFunc: " << t;
      qDebug() << endl;
      if (QString(t).toLower().contains("abs"))
        {
          return (double)abs(atoi(getVariableBR(t)));
        }
      else if(QString(t).toLower().contains("asin"))
        {
          return asin(atof(getVariableBR(t)));
        }
      else if(QString(t).toLower().contains("atan"))
        {
          return atan(atof(getVariableBR(t)));
        }
      else if(QString(t).toLower().contains("cos"))
        {
          return cos(atof(getVariableBR(t)));
        }
      else if(QString(t).toLower().contains("exp"))
        {
          return exp(atof(getVariableBR(t)));
        }
      else if(QString(t).toLower().contains("floor"))
        {
          return floor(atof(getVariableBR(t)));

        }
      else if(QString(t).toLower().contains("log10"))
        {
          return log10(atof(getVariableBR(t)));
        }
      else if(QString(t).toLower().contains("log"))
        {
          return log(atof(getVariableBR(t)));
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
          //
        }
      else if(QString(t).toLower().contains("sinh"))
        {
          return sinh(atof(getVariableBR(t)));
        }
      else if(QString(t).toLower().contains("sin"))
        {
          return sin(atof(getVariableBR(t)));
        }
      else if(QString(t).toLower().contains("sqrt"))
        {
          return sqrt(atof(getVariableBR(t)));
        }
      else if(QString(t).toLower().contains("tanh"))
        {
          return tanh(atof(getVariableBR(t)));
        }
      else if(QString(t).toLower().contains("tan"))
        {
          return tan(atof(getVariableBR(t)));
        }
    }
  return -1;
}
void checkListItemsSUM(QStringList &list)
{
  for(int i=0;i<list.count();i++)
    {
      if(isFuncSUM(list[i].toUtf8().data())!=-1)
        {
          qDebug() << "FUNC BEFORE: " << list[i];
          list.replace(i,QString::number(isFuncSUM(list[i].toUtf8().data())));
        }
      if(isValue(list[i].toUtf8().data())!=-1)
        {
          list.replace(i,QString::number(isValue(list[i].toUtf8().data())));
        }
    }
}
double SUM(char* text)
{
  double out = 0;
  qDebug() <<"INPUT TEXT:" <<text;
  QStringList list = QString(text).split(";");
  qDebug() << "COUNT:" << list.count();
  //checkListItemsSUM(list);
  for(int i =0;i<list.count();i++)
    {
      out+=atof(list[i].toUtf8().constData());
    }
  qDebug() << "SUM: "<< out;
  return out;
}
double isFuncEq(char* t)
{
  qDebug()<<"isFunc(atof test): " << atof(t);
  qDebug() << endl;
  if(atof(t)==0)
    {
      qDebug() << "isFunc: " << t;
      qDebug() << endl;
      if (QString(t).toLower().contains("=abs"))
        {
          return (double)abs(atoi(getVariableBR(t)));
        }
      else if(QString(t).toLower().contains("=asin"))
        {
          return asin(atof(getVariableBR(t)));
        }
      else if(QString(t).toLower().contains("=atan"))
        {
          return atan(atof(getVariableBR(t)));
        }
      else if(QString(t).toLower().contains("=cos"))
        {
          return cos(atof(getVariableBR(t)));
        }
      else if(QString(t).toLower().contains("=exp"))
        {
          return exp(atof(getVariableBR(t)));
        }
      else if(QString(t).toLower().contains("=floor"))
        {
          return floor(atof(getVariableBR(t)));

        }
      else if(QString(t).toLower().contains("=log10"))
        {
          return log10(atof(getVariableBR(t)));
        }
      else if(QString(t).toLower().contains("=log"))
        {
          return log(atof(getVariableBR(t)));
        }
      else if(QString(t).toLower().contains("=max"))
        {
          //return (atof(getVariableBR(t)));
        }
      else if(QString(t).toLower().contains("=min"))
        {
          //
        }
      else if(QString(t).toLower().contains("=pow"))
        {
          //
        }
      else if(QString(t).toLower().contains("=round"))
        {
          //
        }
      else if(QString(t).toLower().contains("=sinh"))
        {
          return sinh(atof(getVariableBR(t)));
        }
      else if(QString(t).toLower().contains("=sin"))
        {
          return sin(atof(getVariableBR(t)));
        }
      else if(QString(t).toLower().contains("=sqrt"))
        {
          return sqrt(atof(getVariableBR(t)));
        }
      else if(QString(t).toLower().contains("=tanh"))
        {
          return tanh(atof(getVariableBR(t)));
        }
      else if(QString(t).toLower().contains("=tan"))
        {
          return tan(atof(getVariableBR(t)));
        }
      else if(QString(t).toLower().contains("=sum"))
        {
          return SUM(getVariableBR(t));
        }
    }
  return -1;
}

double isFunc(char* t){
  qDebug()<<"isFunc(atof test): " << atof(t);
  qDebug() << endl;
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


char* calc(char* text)
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

bool haveBrackets(char* t)
{
  QRegExp exp("\\((.*)\\)");
  if(exp.indexIn(t) >= 0)
    {
      return true;
    }else return false;
}

void SUPERPARSER(QTableWidgetItem *item)
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

  if(!haveBrackets(item->text().toUtf8().data()))
    {
      strcpy(functemp,QString("=(%1)").arg(temp).toUtf8().constData());
      temp = QString("%1").arg(temp);
    }
  else strcpy(functemp,item->text().toUtf8().constData());
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

      if(isFunc(temp.toUtf8().data())!=-1)
        {
          qDebug()<<temp;
          strcpy(table[item->row()][item->column()].func,temp.toUtf8().constData());
          item->setText(QString::number(isFunc(temp.toUtf8().data())));
        }
      if(isValue(temp.toUtf8().data())!=-1)
        {
          strcpy(table[item->row()][item->column()].func,temp.toUtf8().constData());
          item->setText(QString::number(isValue(temp.toUtf8().data())));
          /*
          char* tem = new char[100]; char* tem2 = new char[100];
          strcpy(tem,temp.toUtf8().constData()); strcpy(tem2,item->text().toUtf8().constData());
          strcpy(table[item->row()][item->column()].func,tem2);
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
              strcpy(t,getVariable2(t));
            }
          char* t2 = new char[1000];
          QString fix = QString("(%1)").arg(t);
          strcpy(t2,QString(out).replace(fix,calc(t)).remove("=").toUtf8().constData());
          qDebug()<<"many func: " << t2;
          strcpy(out,t2);
        }
      item->setText(out);
      strcpy(table[item->row()][item->column()].func,functemp);
    }
}


void Parser(QTableWidgetItem *item)
{
  /*
  if (item->text().toLower().contains("=abs"))
    {
      char* temp = new char[100];
      strcpy(temp,item->text().toLower().toUtf8().constData());
      strcpy(table[item->row()][item->column()].func,item->text().toLower().toUtf8().constData());//записали в функцию то что мы наделали
      strcpy(table[item->row()][item->column()].value,QString::number(abs(atoi(getVariableBR(temp)))).toUtf8().constData());
      item->setText(QString(table[item->row()][item->column()].value));
    }
  else if(item->text().toLower().contains("=asin"))
    {
      char* temp = new char[100];
      strcpy(temp,item->text().toLower().toUtf8().constData());
      strcpy(table[item->row()][item->column()].func,item->text().toLower().toUtf8().constData());//записали в функцию то что мы наделали
      strcpy(table[item->row()][item->column()].value,QString::number(asin(atof(getVariableBR(temp)))).toUtf8().constData());
      item->setText(QString(table[item->row()][item->column()].value));
    }
  else if(item->text().toLower().contains("=atan"))
    {
      char* temp = new char[100];
      strcpy(temp,item->text().toLower().toUtf8().constData());
      strcpy(table[item->row()][item->column()].func,item->text().toLower().toUtf8().constData());//записали в функцию то что мы наделали
      strcpy(table[item->row()][item->column()].value,QString::number(atan(atof(getVariableBR(temp)))).toUtf8().constData());
      item->setText(QString(table[item->row()][item->column()].value));
    }
  else if(item->text().toLower().contains("=cos"))
    {
      char* temp = new char[100];
      strcpy(temp,item->text().toLower().toUtf8().constData());
      strcpy(table[item->row()][item->column()].func,item->text().toLower().toUtf8().constData());//записали в функцию то что мы наделали
      strcpy(table[item->row()][item->column()].value,QString::number(cos(atof(getVariableBR(temp)))).toUtf8().constData());
      item->setText(QString(table[item->row()][item->column()].value));
    }
  else if(item->text().toLower().contains("=exp"))
    {
      char* temp = new char[100];
      strcpy(temp,item->text().toLower().toUtf8().constData());
      strcpy(table[item->row()][item->column()].func,item->text().toLower().toUtf8().constData());//записали в функцию то что мы наделали
      strcpy(table[item->row()][item->column()].value,QString::number(exp(atof(getVariableBR(temp)))).toUtf8().constData());
      item->setText(QString(table[item->row()][item->column()].value));
    }
  else if(item->text().toLower().contains("=floor"))
    {
      char* temp = new char[100];
      strcpy(temp,item->text().toLower().toUtf8().constData());
      strcpy(table[item->row()][item->column()].func,item->text().toLower().toUtf8().constData());//записали в функцию то что мы наделали
      strcpy(table[item->row()][item->column()].value,QString::number(floor(atof(getVariableBR(temp)))).toUtf8().constData());
      item->setText(QString(table[item->row()][item->column()].value));

    }
  else if(item->text().toLower().contains("=log10"))
    {
      char* temp = new char[100];
      strcpy(temp,item->text().toLower().toUtf8().constData());
      strcpy(table[item->row()][item->column()].func,item->text().toLower().toUtf8().constData());//записали в функцию то что мы наделали
      strcpy(table[item->row()][item->column()].value,QString::number(log10(atof(getVariableBR(temp)))).toUtf8().constData());
      item->setText(QString(table[item->row()][item->column()].value));
    }
  else if(item->text().toLower().contains("=log"))
    {
      char* temp = new char[100];
      strcpy(temp,item->text().toLower().toUtf8().constData());
      strcpy(table[item->row()][item->column()].func,item->text().toLower().toUtf8().constData());//записали в функцию то что мы наделали
      strcpy(table[item->row()][item->column()].value,QString::number(log(atof(getVariableBR(temp)))).toUtf8().constData());
      item->setText(QString(table[item->row()][item->column()].value));
    }
  else if(item->text().toLower().contains("=max"))
    {
      char* temp = new char[100];
      strcpy(temp,item->text().toLower().toUtf8().constData());
      strcpy(table[item->row()][item->column()].func,item->text().toLower().toUtf8().constData());//записали в функцию то что мы наделали
      strcpy(table[item->row()][item->column()].value,QString::number(abs(atoi(getVariableBR(temp)))).toUtf8().constData());
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
      strcpy(table[item->row()][item->column()].value,QString::number(round(atof(getVariableBR(temp)))).toUtf8().constData());
      item->setText(QString(table[item->row()][item->column()].value));
    }
  else if(item->text().toLower().contains("=sinh"))
    {
      char* temp = new char[100];
      strcpy(temp,item->text().toLower().toUtf8().constData());
      strcpy(table[item->row()][item->column()].func,item->text().toLower().toUtf8().constData());//записали в функцию то что мы наделали
      strcpy(table[item->row()][item->column()].value,QString::number(sinh(atof(getVariableBR(temp)))).toUtf8().constData());
      item->setText(QString(table[item->row()][item->column()].value));
    }
  else if(item->text().toLower().contains("=sin"))
    {
      char* temp = new char[100];
      strcpy(temp,item->text().toLower().toUtf8().constData());
      strcpy(table[item->row()][item->column()].func,item->text().toLower().toUtf8().constData());//записали в функцию то что мы наделали
      strcpy(table[item->row()][item->column()].value,QString::number(sin(atof(getVariableBR(temp)))).toUtf8().constData());
      item->setText(QString(table[item->row()][item->column()].value));
    }
  else if(item->text().toLower().contains("=sqrt"))
    {
      char* temp = new char[100];
      strcpy(temp,item->text().toLower().toUtf8().constData());
      strcpy(table[item->row()][item->column()].func,item->text().toLower().toUtf8().constData());//записали в функцию то что мы наделали
      strcpy(table[item->row()][item->column()].value,QString::number(sqrt(atof(getVariableBR(temp)))).toUtf8().constData());
      item->setText(QString(table[item->row()][item->column()].value));
    }
  else if(item->text().toLower().contains("=tanh"))
    {
      char* temp = new char[100];
      strcpy(temp,item->text().toLower().toUtf8().constData());
      strcpy(table[item->row()][item->column()].func,item->text().toLower().toUtf8().constData());//записали в функцию то что мы наделали
      strcpy(table[item->row()][item->column()].value,QString::number(tanh(atof(getVariableBR(temp)))).toUtf8().constData());
      item->setText(QString(table[item->row()][item->column()].value));
    }
  else if(item->text().toLower().contains("=tan"))
    {
      char* temp = new char[100];
      strcpy(temp,item->text().toLower().toUtf8().constData());
      strcpy(table[item->row()][item->column()].func,item->text().toLower().toUtf8().constData());//записали в функцию то что мы наделали
      strcpy(table[item->row()][item->column()].value,QString::number(tan(atof(getVariableBR(temp)))).toUtf8().constData());
      item->setText(QString(table[item->row()][item->column()].value));
    }
  else if(item->text().toLower().contains("=sum"))
    {
      char* temp = new char[100];
      strcpy(temp,item->text().toLower().toUtf8().constData());
      strcpy(table[item->row()][item->column()].func,item->text().toLower().toUtf8().constData());//записали в функцию то что мы наделали
      strcpy(table[item->row()][item->column()].value,QString::number(SUM(getVariableBR(temp))).toUtf8().constData());
      item->setText(QString(table[item->row()][item->column()].value));
    }*/
  if(item->text().contains("=")) SUPERPARSER(item);
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

void MainWindow::on_pushButton_3_clicked()
{
  QString path = QFileDialog::getSaveFileName();
  FILE *fd = fopen(path.toUtf8().constData(),"wb+");
  fwrite(&table,sizeof(table),1,fd);
  fclose(fd);
}

void MainWindow::on_pushButton_2_clicked()
{
  item temp[24][30];
  QString path = QFileDialog::getOpenFileName();
  if(path!=NULL)
    {
      for(int i=0;i<24;i++)
        {
          for(int j=0;j<30;j++)
            {
              strcpy(table[i][j].func,"");
              strcpy(table[i][j].value,"");
              table[i][j].type = 1;
              table[i][j].X = i;
              table[i][j].Y = j;
            }
        }
      FILE *fd = fopen(path.toUtf8().constData(),"r");
      fread(&table,sizeof(table),1,fd);
      ui->tableWidget->clear();
      for(int i=0;i<24;i++)
        {
          ui->tableWidget->setHorizontalHeaderItem(i,new QTableWidgetItem(QChar(colNames[i])));
          for(int j=0;j<30;j++)
            {
              /*strcpy(table[i][j].value,"");

              table[i][j].value = temp[i][j].value;
              table[i][j].func = temp[i][j].func;
              table[i][j].type = temp[i][j].type;
              table[i][j].X = temp[i][j].X;*/
              QTableWidgetItem *item = new QTableWidgetItem(QString(table[i][j].value));
              ui->tableWidget->setItem(i,j,item);
            }
        }
      fclose(fd);
    }
}

void MainWindow::on_pushButton_4_clicked()
{

}
