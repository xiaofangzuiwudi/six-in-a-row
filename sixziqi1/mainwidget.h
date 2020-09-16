#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "peoplewidget.h"
#include "computergame.h"
#include "doublecomputer.h"
namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private slots:
    void on_pushButton_2_released();

    void on_pushButton_released();

    void on_pushButton_3_released();

public slots:
    void dealSub();
    void dealSub1();
    void dealSub2();

protected:
    void paintEvent(QPaintEvent *);

private:
    Ui::MainWidget *ui;
    PeopleWidget peopleWin;
    ComputerGame comWin;
    DoubleComputer doublecomWin;
};

#endif // MAINWIDGET_H
