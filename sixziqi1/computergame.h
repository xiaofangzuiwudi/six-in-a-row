#ifndef COMPUTERGAME_H
#define COMPUTERGAME_H

#include <QWidget>

namespace Ui {
class ComputerGame;
}

class ComputerGame : public QWidget
{
    Q_OBJECT

public:
    explicit ComputerGame(QWidget *parent = 0);
    ~ComputerGame();

    // 存储当前游戏棋盘和棋子的情况,空白为0，黑子1，白子-1
    std::vector<std::vector<int>> a;

    // 存储各个点位的评分情况，作为AI下棋依据
    std::vector<std::vector<int>> scoreMapVec;

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void AI();
    void Score();

private slots:
    void on_pushButton_4_released();

    void on_pushButton_3_released();

    void on_pushButton_2_released();

    void on_pushButton_released();

signals:
    void mySignal();

private:
    Ui::ComputerGame *ui;
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
    int currentx, currenty, currentx1, currenty1;
};

#endif // COMPUTERGAME_H
