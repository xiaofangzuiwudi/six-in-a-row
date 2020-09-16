#include "peoplewidget.h"
#include "ui_peoplewidget.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QDebug>
#include <QMouseEvent>
#include <QMessageBox>
#include <QTimerEvent>
PeopleWidget::PeopleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PeopleWidget)
{
    ui->setupUi(this);
    resize(1000,840);
    memset(a, 0, 20 * 20 * sizeof(int));
    player = 0;
}

PeopleWidget::~PeopleWidget()
{
    delete ui;
}
void PeopleWidget::paintEvent(QPaintEvent *e)
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

void PeopleWidget::mousePressEvent(QMouseEvent *e)
{
    int x, y;
    if(e->x() >= 40 && e->x() <=800 && e->y() >=40 && e->y() <= 800)
    {
        x = (e->x() - 21) / 40;
        y = (e->y() - 21) / 40;
        currentx = x;
        currenty = y;
        if(!a[x][y])
        {
            a[x][y] = player++ % 2 + 1;
        }
        if(isJinShou(x, y) && ((player % 2) == 1))
        {
            QMessageBox::information(this, "Win", "blackLose", QMessageBox::Ok);
            memset(a, 0, 20 * 20 * sizeof(int));
            player++;
            update();
        }
        else if(isWin(x, y))
        {
            if(player % 2 == 0)
            QMessageBox::information(this, "Win", "whiteWin", QMessageBox::Ok);
            else QMessageBox::information(this, "Win", "blackWin", QMessageBox::Ok);
            memset(a, 0, 20 * 20 * sizeof(int));
            if((player % 2) == 1)
            player++;
            update();
        }
        if(isPeace())
        {
            QMessageBox::information(this, "Stalemate", "Stalemate", QMessageBox::Ok);
            memset(a, 0, 20 * 20 * sizeof(int));
            if((player % 2) == 1)
            player++;
            update();
        }
    }
    update();
}

int PeopleWidget::isWin(int x, int y)
{
    return f1(x, y) || f2(x, y) || f3(x, y) || f4(x, y);
}

int PeopleWidget::f1(int x, int y)
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

int PeopleWidget::f2(int x, int y)
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

int PeopleWidget::f3(int x, int y)
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

int PeopleWidget::f4(int x, int y)
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

int PeopleWidget::isPeace()
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

void PeopleWidget::on_pushButton_released()
{
    if(player % 2 == 1)
    QMessageBox::information(this, "Win", "white give up", QMessageBox::Ok);
    else QMessageBox::information(this, "Win", "black give up", QMessageBox::Ok);
    memset(a, 0, 20 * 20 * sizeof(int));
    if((player % 2) == 1)
    player++;
    update();
}

int PeopleWidget::isJinShou(int x, int y)
{
    return f5(x, y) || f6(x, y) ;
}

int PeopleWidget::f5(int x, int y)
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
int PeopleWidget::f6(int x, int y)
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

void PeopleWidget::on_pushButton_3_released()
{
    emit mySignal();
    memset(a, 0, 20 * 20 * sizeof(int));
    if((player % 2) == 1)
    player++;
    update();
}

void PeopleWidget::on_pushButton_4_released()
{
    memset(a, 0, 20 * 20 * sizeof(int));
    if((player % 2) == 1)
    player++;
    update();
}

void PeopleWidget::on_pushButton_2_released()
{
    if(a[currentx][currenty] != 0)
    {
        a[currentx][currenty]=0;
        player++;
    }
    update();
}
