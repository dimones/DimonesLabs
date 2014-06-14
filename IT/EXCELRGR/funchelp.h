#ifndef FUNCHELP_H
#define FUNCHELP_H

#include <QWidget>

namespace Ui {
class funcHelp;
}

class funcHelp : public QWidget
{
    Q_OBJECT

public:
    explicit funcHelp(QWidget *parent = 0);
    ~funcHelp();

private slots:
    void on_listWidget_itemSelectionChanged();

private:
    Ui::funcHelp *ui;
};

#endif // FUNCHELP_H
