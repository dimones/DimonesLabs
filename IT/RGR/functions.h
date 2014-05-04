#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QMainWindow>

namespace Ui {
class Functions;
}

class Functions : public QMainWindow
{
    Q_OBJECT

public:
    explicit Functions(QWidget *parent = 0);
    ~Functions();

private:
    Ui::Functions *ui;
};

#endif // FUNCTIONS_H
