#ifndef WELCOMEFORM_H
#define WELCOMEFORM_H

#include <QWidget>

namespace Ui {
class welcomeForm;
}

class welcomeForm : public QWidget
{
    Q_OBJECT

public:
    explicit welcomeForm(QWidget *parent = 0);
    ~welcomeForm();

private slots:
    void on_open_clicked();

private:
    Ui::welcomeForm *ui;
};

#endif // WELCOMEFORM_H
