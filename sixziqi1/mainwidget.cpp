#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QPainter>
MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    connect(&peopleWin, SIGNAL(mySignal()), this, SLOT(dealSub()) );
    connect(&comWin, SIGNAL(mySignal()), this, SLOT(dealSub1()) );
    connect(&doublecomWin, SIGNAL(mySignal()), this, SLOT(dealSub2()) );
}
void MainWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawPixmap(rect(), QPixmap("../Image/u=2806031943,697112918&fm=26&gp=0"));
}
MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::on_pushButton_2_released()
{
    comWin.show();
    this->close();

}

void MainWidget::on_pushButton_released()
{
    peopleWin.show();
    this->close();

}

void MainWidget::on_pushButton_3_released()
{
    doublecomWin.show();
    this->close();

}
void MainWidget::dealSub()
{
    peopleWin.hide();
    this->show();
}
void MainWidget::dealSub1()
{
    comWin.hide();
    this->show();
}
void MainWidget::dealSub2()
{
    doublecomWin.hide();
    this->show();
}
