#include "computergame.h"
#include "ui_computergame.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QDebug>
#include <QMouseEvent>
#include <QMessageBox>
ComputerGame::ComputerGame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ComputerGame)
{
    ui->setupUi(this);
    resize(1000,840);
    a.clear();
    for (int i = 0; i < 20; i++)
    {
        std::vector<int> lineBoard;
        for (int j = 0; j < 20; j++)
            lineBoard.push_back(0);
        a.push_back(lineBoard);
    }
    scoreMapVec.clear();
    for (int i = 0; i < 20; i++)
    {
        std::vector<int> lineScores;
        for (int j = 0; j < 20; j++)
            lineScores.push_back(0);
        scoreMapVec.push_back(lineScores);
    }
    player = 0;
}

ComputerGame::~ComputerGame()
{
    delete ui;
}
void ComputerGame::paintEvent(QPaintEvent *e)
{
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor("#E6CA3B"));
    this->setPalette(palette);
    QPainter p(this);
    QBrush brush;
    QPen pen = p.pen();
    pen.setWidth(5);
    p.setPen(pen);
    brush.setColor(QColor("#E8DB9F"));
    brush.setStyle(Qt::SolidPattern);
    p.setBrush(brush);
    p.drawRect(20, 20, 800, 800);
    p.setRenderHint(QPainter::Antialiasing, true);
    pen.setWidth(3);
    p.setPen(pen);
    int i, j;
    for(i = 0; i < 20; i++)
    {
        p.drawLine(40, 40 + i * 40, 800, 40 + i * 40);
        p.drawLine(40 + i * 40, 40, 40 + i * 40, 800);
    }


    for(i = 0; i < 20; i++)
        for(j = 0; j < 20; j++)
        {
            if(a[i][j]  == 1)
            {
                brush.setColor(Qt::black);
                p.setBrush(brush);
                p.drawEllipse(QPoint((i + 1) * 40, (j + 1) * 40), 15, 15);
            }
            else if(a[i][j]  == 2)
            {
                brush.setColor(Qt::white);
                p.setBrush(brush);
                p.drawEllipse(QPoint((i + 1) * 40, (j + 1) * 40), 15, 15);
            }
        }

}
void ComputerGame::mousePressEvent(QMouseEvent *e)
{
    int x, y;
    if(e->x() > 60 && e->x() <=800 && e->y() > 60 && e->y() <= 800)
    {
        x = (e->x() - 21) / 40;
        y = (e->y() - 21) / 40;
        if(!a[x][y])
        {
            a[x][y] = player++ % 2 + 1;
        }
        currentx = x;
        currenty = y;
        if(isJinShou(x, y) && ((player % 2) == 1))
        {
            QMessageBox::information(this, "Win", "blackLose", QMessageBox::Ok);
            a.clear();
            for (int i = 0; i < 20; i++)
            {
                std::vector<int> lineBoard;
                for (int j = 0; j < 20; j++)
                    lineBoard.push_back(0);
                a.push_back(lineBoard);
            }
            scoreMapVec.clear();
            for (int i = 0; i < 20; i++)
            {
                std::vector<int> lineScores;
                for (int j = 0; j < 20; j++)
                    lineScores.push_back(0);
                scoreMapVec.push_back(lineScores);
            }
            update();
        }
        else if(isWin(x, y))
        {
            if(player % 2 == 0)
            QMessageBox::information(this, "Win", "whiteWin", QMessageBox::Ok);
            else QMessageBox::information(this, "Win", "blackWin", QMessageBox::Ok);
            a.clear();
            for (int i = 0; i < 20; i++)
            {
                std::vector<int> lineBoard;
                for (int j = 0; j < 20; j++)
                    lineBoard.push_back(0);
                a.push_back(lineBoard);
            }
            scoreMapVec.clear();
            for (int i = 0; i < 20; i++)
            {
                std::vector<int> lineScores;
                for (int j = 0; j < 20; j++)
                    lineScores.push_back(0);
                scoreMapVec.push_back(lineScores);
            }
            update();
        }
        if(isPeace())
        {
            QMessageBox::information(this, "Stalemate", "Stalemate", QMessageBox::Ok);
            a.clear();
            for (int i = 0; i < 20; i++)
            {
                std::vector<int> lineBoard;
                for (int j = 0; j < 20; j++)
                    lineBoard.push_back(0);
                a.push_back(lineBoard);
            }
            update();
        }
        if((player %2 + 1) == 2)
        AI();
    }
    update();
}
int ComputerGame::isWin(int x, int y)
{
    return f1(x, y) || f2(x, y) || f3(x, y) || f4(x, y);
}

int ComputerGame::f1(int x, int y)
{
    int i;
    for(i = 0; i < 6; i++)
    {
        if(y - i >= 0 &&
           y + 5 - i < 20 &&
           a[x][y - i] == a[x][y + 1 - i] &&
           a[x][y - i] == a[x][y + 2 - i] &&
           a[x][y - i] == a[x][y + 3 - i] &&
           a[x][y - i] == a[x][y + 4 - i] &&
           a[x][y - i] == a[x][y + 5 - i] )
        return 1;
    }
    return 0;
}

int ComputerGame::f2(int x, int y)
{
    int i;
    for(i = 0; i < 6; i++)
    {
        if(x - i >= 0 &&
           x + 5 - i < 20 &&
           a[x - i][y] == a[x + 1 - i][y] &&
           a[x - i][y] == a[x + 2 - i][y] &&
           a[x - i][y] == a[x + 3 - i][y] &&
           a[x - i][y] == a[x + 4 - i][y] &&
           a[x - i][y] == a[x + 5 - i][y] )
        return 1;
    }
    return 0;
}

int ComputerGame::f3(int x, int y)
{
    int i;
    for(i = 0; i < 6; i++)
    {
        if(x - i >= 0 &&
           y - i >= 0 &&
           x + 5 - i < 20 &&
           y + 5 - i < 20 &&
           a[x - i][y - i] == a[x + 1 - i][y + 1 -i] &&
           a[x - i][y - i] == a[x + 2 - i][y + 2 -i] &&
           a[x - i][y - i] == a[x + 3 - i][y + 3 -i] &&
           a[x - i][y - i] == a[x + 4 - i][y + 4 -i] &&
           a[x - i][y - i] == a[x + 5 - i][y + 5 -i] )
        return 1;
    }
    return 0;
}

int ComputerGame::f4(int x, int y)
{
    int i;
    for(i = 0; i < 6; i++)
    {
        if(x + i < 20 &&
           y - i >= 0 &&
           x - 5 + i >= 0 &&
           y + 5 - i < 20 &&
           a[x + i][y - i] == a[x - 1 + i][y + 1 -i] &&
           a[x + i][y - i] == a[x - 2 + i][y + 2 -i] &&
           a[x + i][y - i] == a[x - 3 + i][y + 3 -i] &&
           a[x + i][y - i] == a[x - 4 + i][y + 4 -i] &&
           a[x + i][y - i] == a[x - 5 + i][y + 5 -i] )
        return 1;
    }
    return 0;
}

int ComputerGame::isPeace()
{
    int i, j, flag = 1;
    for(i = 0; i < 20; i++)
        for(j = 0; j < 20; j++)
        {
            if(a[i][j] == 0)
            {
                flag = 0;
            }
        }
    return flag;
}
void ComputerGame::AI()
{
    // 计算评分
    Score();

    // 从评分中找出最大分数的位置
    int maxScore = 0;
    std::vector<std::pair<int, int>> maxPoints;

    for (int row = 0; row < 20; row++)
        for (int col = 0; col < 20; col++)
        {
            // 前提是这个坐标是空的
            if (a[row][col] == 0)
            {
                if (scoreMapVec[row][col] > maxScore)          // 找最大的数和坐标
                {
                    maxPoints.clear();
                    maxScore = scoreMapVec[row][col];
                    maxPoints.push_back(std::make_pair(row, col));
                }
                else if (scoreMapVec[row][col] == maxScore)     // 如果有多个最大的数，都存起来
                    maxPoints.push_back(std::make_pair(row, col));
            }
        }

    // 随机落子，如果有多个点的话
    srand((unsigned)time(0));
    int index = rand() % maxPoints.size();

    std::pair<int, int> pointPair = maxPoints.at(index);
    int x = pointPair.first; // 记录落子点
    int y = pointPair.second;
    a[x][y] = 2;
    currentx1 = x;
    currenty1 = y;
    player++;
    if(isWin(x, y))
    {
        if(player % 2 == 0)
        QMessageBox::information(this, "Win", "whiteWin", QMessageBox::Ok);
        else QMessageBox::information(this, "Win", "blackWin", QMessageBox::Ok);
        a.clear();
        for (int i = 0; i < 20; i++)
        {
            std::vector<int> lineBoard;
            for (int j = 0; j < 20; j++)
                lineBoard.push_back(0);
            a.push_back(lineBoard);
        }
        scoreMapVec.clear();
        for (int i = 0; i < 20; i++)
        {
            std::vector<int> lineScores;
            for (int j = 0; j < 20; j++)
                lineScores.push_back(0);
            scoreMapVec.push_back(lineScores);
        }
        update();
    }
    if(isPeace())
    {
        QMessageBox::information(this, "Stalemate", "Stalemate", QMessageBox::Ok);
        a.clear();
        for (int i = 0; i < 20; i++)
        {
            std::vector<int> lineBoard;
            for (int j = 0; j < 20; j++)
                lineBoard.push_back(0);
            a.push_back(lineBoard);
        }
        scoreMapVec.clear();
        for (int i = 0; i < 20; i++)
        {
            std::vector<int> lineScores;
            for (int j = 0; j < 20; j++)
                lineScores.push_back(0);
            scoreMapVec.push_back(lineScores);
        }
        update();
    }
}

// 最关键的计算评分函数
void ComputerGame::Score()
{
    // 统计玩家或者电脑连成的子
    int personNum = 0; // 玩家连成子的个数
    int botNum = 0; // AI连成子的个数
    int emptyNum = 0; // 各方向空白位的个数

    // 清空评分数组
    scoreMapVec.clear();
    for (int i = 0; i < 20; i++)
    {
        std::vector<int> lineScores;
        for (int j = 0; j < 20; j++)
            lineScores.push_back(0);
        scoreMapVec.push_back(lineScores);
    }

    // 计分（此处是完全遍历，其实可以用bfs或者dfs加减枝降低复杂度，通过调整权重值，调整AI智能程度以及攻守风格）
    for (int row = 0; row < 20; row++)
        for (int col = 0; col < 20; col++)
        {
            // 空白点就算
            if (row > 0 && col > 0 &&
                a[row][col] == 0)
            {
                // 遍历周围八个方向
                for (int y = -1; y <= 1; y++)
                    for (int x = -1; x <= 1; x++)
                    {
                        // 重置
                        personNum = 0;
                        botNum = 0;
                        emptyNum = 0;

                        // 原坐标不算
                        if (!(y == 0 && x == 0))
                        {
                            // 每个方向延伸4个子

                            // 对玩家白子评分（正反两个方向）
                            for (int i = 1; i <= 6; i++)
                            {
                                if (row + i * y > 0 && row + i * y < 20 &&
                                    col + i * x > 0 && col + i * x < 20 &&
                                    a[row + i * y][col + i * x] == 1) // 真人玩家的子
                                {
                                    personNum++;
                                }
                                else if (row + i * y > 0 && row + i * y < 20 &&
                                         col + i * x > 0 && col + i * x < 20 &&
                                         a[row + i * y][col + i * x] == 0) // 空白位
                                {
                                    emptyNum++;
                                    break;
                                }
                                else            // 出边界
                                    break;
                            }

                            for (int i = 1; i <= 6; i++)
                            {
                                if (row - i * y > 0 && row - i * y < 20 &&
                                    col - i * x > 0 && col - i * x < 20 &&
                                    a[row - i * y][col - i * x] == 1) // 玩家的子
                                {
                                    personNum++;
                                }
                                else if (row - i * y > 0 && row - i * y < 20 &&
                                         col - i * x > 0 && col - i * x < 20 &&
                                         a[row - i * y][col - i * x] == 0) // 空白位
                                {
                                    emptyNum++;
                                    break;
                                }
                                else            // 出边界，或者有AI自己的棋子
                                    break;
                            }

                            if (personNum == 1)                      // 杀二
                                scoreMapVec[row][col] += 10;
                            else if (personNum == 2)                 // 杀三
                            {
                                if (emptyNum == 1)
                                    scoreMapVec[row][col] += 30;
                                else if (emptyNum == 2)
                                    scoreMapVec[row][col] += 40;
                            }
                            else if (personNum == 3)                 // 杀四
                            {
                                // 量变空位不一样，优先级不一样
                                if (emptyNum == 1)
                                    scoreMapVec[row][col] += 60;
                                else if (emptyNum == 2)
                                    scoreMapVec[row][col] += 110;
                            }
                            else if (personNum == 4)                 // 杀四
                            {
                                // 量变空位不一样，优先级不一样
                                if (emptyNum == 1)
                                    scoreMapVec[row][col] += 1000;
                                else if (emptyNum == 2)
                                    scoreMapVec[row][col] += 2000;
                            }
                            else if (personNum == 5)                 // 杀五
                                scoreMapVec[row][col] += 100000;

                            // 进行一次清空
                            emptyNum = 0;

                            // 对AI黑子评分
                            for (int i = 1; i <= 6; i++)
                            {
                                if (row + i * y > 0 && row + i * y < 20 &&
                                    col + i * x > 0 && col + i * x < 20 &&
                                    a[row + i * y][col + i * x] == -1) // 玩家的子
                                {
                                    botNum++;
                                }
                                else if (row + i * y > 0 && row + i * y < 20 &&
                                         col + i * x > 0 && col + i * x < 20 &&
                                         a[row +i * y][col + i * x] == 0) // 空白位
                                {
                                    emptyNum++;
                                    break;
                                }
                                else            // 出边界
                                    break;
                            }

                            for (int i = 1; i <= 6; i++)
                            {
                                if (row - i * y > 0 && row - i * y < 20 &&
                                    col - i * x > 0 && col - i * x < 20 &&
                                    a[row - i * y][col - i * x] == -1) // AI的子
                                {
                                    botNum++;
                                }
                                else if (row - i * y > 0 && row - i * y < 20 &&
                                         col - i * x > 0 && col - i * x < 20 &&
                                         a[row - i * y][col - i * x] == 0) // 空白位
                                {
                                    emptyNum++;
                                    break;
                                }
                                else            // 出边界
                                    break;
                            }

                            if (botNum == 0)                      // 普通下子
                                scoreMapVec[row][col] += 5;
                            else if (botNum == 1)                 // 活二
                                scoreMapVec[row][col] += 10;
                            else if (botNum == 2)
                            {
                                if (emptyNum == 1)                // 死三
                                    scoreMapVec[row][col] += 25;
                                else if (emptyNum == 2)
                                    scoreMapVec[row][col] += 50;  // 活三
                            }
                            else if (botNum == 3)
                            {
                                if (emptyNum == 1)                // 死四
                                    scoreMapVec[row][col] += 55;
                                else if (emptyNum == 2)
                                    scoreMapVec[row][col] += 100; // 活四
                            }
                            else if (botNum == 4)
                            {
                                if (emptyNum == 1)                // 死四
                                    scoreMapVec[row][col] += 990;
                                else if (emptyNum == 2)
                                    scoreMapVec[row][col] += 2000; // 活四
                            }
                            else if (botNum >= 5)
                                scoreMapVec[row][col] += 1110000;   // 活五，应该具有最高优先级

                        }
                    }

            }
        }
}
int ComputerGame::isJinShou(int x, int y)
{
    return f5(x, y) || f6(x, y) ;
}

int ComputerGame::f5(int x, int y)
{
    int i, flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0;
    for(i = 0; i < 4; i++)
    {
        if(y - i >= 0 &&
           y + 3 - i < 20 &&
           a[x][y - i] == a[x][y + 1 - i] &&
           a[x][y - i] == a[x][y + 2 - i] &&
           a[x][y - i] == a[x][y + 3 - i] &&
           a[x][y - i - 1] == 0 &&
           a[x][y - i + 4] == 0)
            flag1 = 1;
        if(x - i >= 0 &&
           x + 3 - i < 20 &&
           a[x - i][y] == a[x + 1 - i][y] &&
           a[x - i][y] == a[x + 2 - i][y] &&
           a[x - i][y] == a[x + 3 - i][y] &&
           a[x - 1 - i][y] == 0 &&
           a[x + 4 - i][y] == 0)
            flag2 = 1;
        if(x - i >= 0 &&
           y - i >= 0 &&
           x + 3 - i < 20 &&
           y + 3 - i < 20 &&
           a[x - i][y - i] == a[x + 1 - i][y + 1 -i] &&
           a[x - i][y - i] == a[x + 2 - i][y + 2 -i] &&
           a[x - i][y - i] == a[x + 3 - i][y + 3 -i] &&
           a[x - 1 - i][y - 1 -i] == 0 &&
           a[x + 4 - i][y + 4 -i] == 0)
            flag3 = 1;
        if(x + i < 20 &&
           y - i >= 0 &&
           x - 3 + i >= 0 &&
           y + 3 - i < 20 &&
           a[x + i][y - i] == a[x - 1 + i][y + 1 -i] &&
           a[x + i][y - i] == a[x - 2 + i][y + 2 -i] &&
           a[x + i][y - i] == a[x - 3 + i][y + 3 -i] &&
           a[x + 1 + i][y - 1 -i] == 0 &&
           a[x - 4 + i][y + 4 -i] == 0)
            flag4 = 1;
    }
    if((flag1 + flag2 + flag3 + flag4) >= 2)
        return 1;
    else return 0;
}
int ComputerGame::f6(int x, int y)
{
    int i, flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0;
    for(i = 0; i < 5; i++)
    {
        if(y - i >= 0 &&
           y + 4 - i < 20 &&
           a[x][y - i] == a[x][y + 1 - i] &&
           a[x][y - i] == a[x][y + 2 - i] &&
           a[x][y - i] == a[x][y + 3 - i] &&
           a[x][y - i] == a[x][y + 4 - i] &&
           (a[x][y - i - 1] == 0 ||
            a[x][y - i + 5] == 0))
            flag1 = 1;
        if(x - i >= 0 &&
           x + 4 - i < 20 &&
           a[x - i][y] == a[x + 1 - i][y] &&
           a[x - i][y] == a[x + 2 - i][y] &&
           a[x - i][y] == a[x + 3 - i][y] &&
           a[x - i][y] == a[x + 4 - i][y] &&
           (a[x - 1 - i][y] == 0 ||
            a[x + 5 - i][y] == 0))
            flag2 = 1;
        if(x - i >= 0 &&
           y - i >= 0 &&
           x + 5 - i < 20 &&
           y + 5 - i < 20 &&
           a[x - i][y - i] == a[x + 1 - i][y + 1 -i] &&
           a[x - i][y - i] == a[x + 2 - i][y + 2 -i] &&
           a[x - i][y - i] == a[x + 3 - i][y + 3 -i] &&
           a[x - i][y - i] == a[x + 4 - i][y + 4 -i] &&
           (a[x - 1 - i][y - 1 -i] == 0 ||
            a[x + 5 - i][y + 5 -i] == 0))
            flag3 = 1;
        if(x + i < 20 &&
           y - i >= 0 &&
           x - 4 + i >= 0 &&
           y + 4 - i < 20 &&
           a[x + i][y - i] == a[x - 1 + i][y + 1 -i] &&
           a[x + i][y - i] == a[x - 2 + i][y + 2 -i] &&
           a[x + i][y - i] == a[x - 3 + i][y + 3 -i] &&
           a[x + i][y - i] == a[x - 4 + i][y + 4 -i] &&
           (a[x + 1 + i][y - 1 -i] == 0 ||
            a[x - 5 + i][y + 5 -i] == 0))
            flag4 = 1;
    }
    if((flag1 + flag2 + flag3 + flag4) >= 2)
        return 1;
    else return 0;
}

void ComputerGame::on_pushButton_4_released()
{
    emit mySignal();
    a.clear();
    for (int i = 0; i < 20; i++)
    {
        std::vector<int> lineBoard;
        for (int j = 0; j < 20; j++)
            lineBoard.push_back(0);
        a.push_back(lineBoard);
    }
    scoreMapVec.clear();
    for (int i = 0; i < 20; i++)
    {
        std::vector<int> lineScores;
        for (int j = 0; j < 20; j++)
            lineScores.push_back(0);
        scoreMapVec.push_back(lineScores);
    }
    if((player % 2) == 1)
    player++;
    update();
}

void ComputerGame::on_pushButton_3_released()
{
    if(player % 2 == 1)
    QMessageBox::information(this, "Win", "white give up", QMessageBox::Ok);
    else QMessageBox::information(this, "Win", "black give up", QMessageBox::Ok);
    a.clear();
    for (int i = 0; i < 20; i++)
    {
        std::vector<int> lineBoard;
        for (int j = 0; j < 20; j++)
            lineBoard.push_back(0);
        a.push_back(lineBoard);
    }
    scoreMapVec.clear();
    for (int i = 0; i < 20; i++)
    {
        std::vector<int> lineScores;
        for (int j = 0; j < 20; j++)
            lineScores.push_back(0);
        scoreMapVec.push_back(lineScores);
    }
    if((player % 2) == 1)
    player++;
    update();
}

void ComputerGame::on_pushButton_2_released()
{
    if(a[currentx][currenty] != 0)
    {
        a[currentx][currenty]=0;
        player++;
    }
    if(a[currentx1][currenty1] != 0)
    {
        a[currentx1][currenty1]=0;
        player++;
    }
    update();
}

void ComputerGame::on_pushButton_released()
{
    a.clear();
    for (int i = 0; i < 20; i++)
    {
        std::vector<int> lineBoard;
        for (int j = 0; j < 20; j++)
            lineBoard.push_back(0);
        a.push_back(lineBoard);
    }
    scoreMapVec.clear();
    for (int i = 0; i < 20; i++)
    {
        std::vector<int> lineScores;
        for (int j = 0; j < 20; j++)
            lineScores.push_back(0);
        scoreMapVec.push_back(lineScores);
    }
    if((player % 2) == 1)
    player++;
    update();
}
