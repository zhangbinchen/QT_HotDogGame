#include "widget.h"
#include "ui_widget.h"
#include<QPainter>
#include<QPushButton>
#include<QMouseEvent>
#include<QDebug>
#include<QString>
#include<QIcon>
#include<QTimer>
#include"mybutton.h"
#include<QSound>
#include<QMovie>
#include<QLabel>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFixedSize(1024,610);
    this->setWindowIcon(QIcon(":/image/hamburger.png"));
    QSound *startSound=new QSound(":/image/over.wav",this);/*开始按钮音效*/
    Mybutton *StarBtn=new Mybutton(":/image/start1.png");/*按钮走重载的构造版本*/

    StarBtn->setParent(this);
    StarBtn->move(390,220);
    //StarBtn->isVisible(false);

    /*加载动画效果*/
    QMovie *movie=new QMovie(":/image/paidaxing.gif");

    //ui->label->setFixedSize(1024,610);
    //ui->label->setGeometry(0,0,this->width(),this->height());
    ui->label->setMovie(movie);

    choose=new Choose;
    connect(StarBtn,&Mybutton::clicked,[=]()
    {
        startSound->play();/*播放音效*/
        StarBtn->zoom1();
        StarBtn->zoom2();
        StarBtn->hide();
        movie->start();

        QTimer::singleShot(1500,this,[=]()
        {
            choose->setGeometry(this->geometry());
            choose->show();
            this->hide();
        });
    });
}

Widget::~Widget()
{
    delete ui;
}
void Widget::mousePressEvent(QMouseEvent *evn)     /*获取坐标*/
{
    if(evn->button()==Qt::LeftButton)
    {
        QString info=QString("点击位置坐标:%1,%2").arg(evn->x()).arg(evn->y());
        qDebug()<<info;
    }
}




void Widget::paintEvent(QPaintEvent *)    /*画背景*/
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/haibao.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);


}

