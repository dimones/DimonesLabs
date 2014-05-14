#ifndef VKSTARTWINDOW_H
#define VKSTARTWINDOW_H

#include <QMainWindow>

namespace Ui {
class vkStartWindow;
}

class vkStartWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit vkStartWindow(QWidget *parent = 0);
    ~vkStartWindow();

private:
    Ui::vkStartWindow *ui;
};

#endif // VKSTARTWINDOW_H
