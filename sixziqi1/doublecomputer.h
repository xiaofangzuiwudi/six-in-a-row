#ifndef DOUBLECOMPUTER_H
#define DOUBLECOMPUTER_H

#include <QWidget>

namespace Ui {
class DoubleComputer;
}

class DoubleComputer : public QWidget
{
    Q_OBJECT

public:
    explicit DoubleComputer(QWidget *parent = 0);
    ~DoubleComputer();
    // 存储当前游戏棋盘和棋子的情况,空白为0，黑子1，白子-1
    std::vector<std::vector<int>> a;

    // 存储各个点位的评分情况，作为AI下棋依据
    std::vector<std::vector<int>> scoreMapVec;

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void actionByAI();
    void calculateScore();

private slots:
    void on_pushButton_4_released();

    void on_pushButton_3_released();

    void on_pushButton_2_released();

    void on_pushButton_released();

signals:
    void mySignal();

private:
    Ui::DoubleComputer *ui;
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
    int currentx;
    int currenty;
};

#endif // DOUBLECOMPUTER_H
