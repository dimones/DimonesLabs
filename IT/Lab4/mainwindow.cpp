#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qfiledialog.h"
#include "qdebug.h"


QString path;
int N;

int C[20][20];

int A = 0;

int AA[20];

int ns = 0;


int B[20], Bmin[20], lmin = -1;

int cnt = 0;

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

void wBlok(int n, int s, int l){

    int d, i;

    cnt++;

    if (lmin != -1 && l >= lmin) return;

    if (n == N){

        if (N / 2 != s) return;

        if (lmin == -1 || l<lmin){

            lmin = l;

            for (int j = 0; j<N; j++) Bmin[j] = B[j];

        }

        qDebug() << "Vizovov = " << cnt << "\r\nminimalnoe kolvo souznikov = " << lmin << endl;
        qDebug() << endl;
        for (i = 0; i < N; i++) qDebug() <<  Bmin[i] << " ";

        return;

    }

    B[n] = 0;

    for (d = 0, i = 0; i<n; i++)

        if (C[i][n] == 1 && B[i] != B[n]) d++;

    wBlok(n + 1, s, l + d);

    B[n] = 1;	 //

    for (d = 0, i = 0; i<n; i++)

        if (C[i][n] == 1 && B[i] != B[n]) d++;

    wBlok(n + 1, s + 1, l + d);

}

void test(QTableWidget *table,QLabel *viz,QLabel *min_viz,QTreeWidget *tree)

{

    int i, j;

    FILE *in = fopen(path.toUtf8().constData(), "r");

    fscanf(in, "%d", &N);

    for (j = 0; j<N; j++)

        for (i = 0; i<N; i++)

            fscanf(in, "%d", &C[j][i]);

    fclose(in);
    A = N / 2;
    B[0] = 0;
    table->setRowCount(N); table->setColumnCount(N); for(int i=0;i<N;i++){ table->setColumnWidth(i,20); table->setRowHeight(i,20);}
    wBlok(1, 0, 0);
    viz->setText(QString::number(cnt));
    min_viz->setText(QString::number(lmin));
    QStringList list;
    for (i = 0; i<N; i++)
    {
        QTreeWidgetItem *it = new QTreeWidgetItem(tree);
        it->setText(0,QString("Страна  %1 - %2").arg(QString::number(i+1),QString::number(Bmin[i])));
        qDebug() << QString("Страна  %1 - %2").arg(QString::number(i+1),QString::number(Bmin[i]));
    }

    qDebug()<< "\n\nmatrica smejnosti:\n";

    puts("");

    for (i = 0; i<N / 2; i++)

        for (j = 0; j<N; j++)

            if (C[AA[i]][j] == 1) ns++;

    for (j = 0; j<N; j++)
    {
        for (i = 0; i<N; i++)
        {
            QTableWidgetItem *item = new QTableWidgetItem(QString::number((C[j][i])));
            table->setItem(j,i,item);
        }
    }

}
void MainWindow::on_openFile_clicked()
{
    path = QFileDialog::getOpenFileName();
    qDebug()<<path;
    test(ui->tableWidget,ui->viz,ui->min_viz,ui->treeWidget);
}




