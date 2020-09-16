#ifndef PEOPLEWIDGET_H
#define PEOPLEWIDGET_H

#include <QWidget>

namespace Ui {
class PeopleWidget;
}

class PeopleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PeopleWidget(QWidget *parent = 0);
    ~PeopleWidget();
    int currentx;
    int currenty;

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);

signals:
    void mySignal();

private slots:
    void on_pushButton_released();

    void on_pushButton_3_released();

    void on_pushButton_4_released();

    void on_pushButton_2_released();

private:
    Ui::PeopleWidget *ui;
    int a[20][20];
    int player;
    int isWin(int, int);
    int f1(int, int);
    int f2(int, int);
    int f3(int, int);
    int f4(int, int);
    int isPeace();
    int isJinShou(int, int);
    int f5(int, int);
    int f6(int, int);
};

#endif // PEOPLEWIDGET_H
