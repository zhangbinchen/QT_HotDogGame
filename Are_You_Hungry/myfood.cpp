#include "myfood.h"
#include<QPixmap>
#include<QDebug>
#include<QPushButton>
#include<QTimer>


//Myfood::Myfood()
//{

//}
Myfood::Myfood(QString butImg)
{
    QPixmap pix;
    bool ret=pix.load(butImg);
    if(!ret)
    {
        qDebug()<<butImg<<"加载图片失败";
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    timer1=new QTimer(this);
    timer2=new QTimer(this);                             /*翻转动画特效*/
    connect(timer1,&QTimer::timeout,[=]()                /*正面翻转监听*/
    {
        QPixmap pix;
        QString str=QString(":/image/food/smallhotdog%1").arg(this->min++);
        pix.load(str);
        bool ret=pix.load(str);
        if(!ret)
        {
            qDebug()<<"图片加载失败min"<<butImg<<min;
            return;
        }
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        if(this->min>this->max)
        {
            this->min=1;
            timer1->stop();
            this->isAnimation=false;

        }
    });
    connect(timer2,&QTimer::timeout,[=]()                     /*反面翻转监听*/
    {
        QPixmap pix;
        QString str=QString(":/image/food/smallhotdog%1").arg(this->max--);
        pix.load(str);
        bool ret=pix.load(str);
        if(!ret)
        {
            qDebug()<<"图片加载失败max"<<butImg<<max;

            return;
        }
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        if(this->max<this->min)
        {
            this->max=8;
            timer2->stop();
            this->isAnimation=false;

        }
    });
}
void Myfood::changeFlag()   /*改变正反*/
{
    if(this->flag)
    {
        timer1->start(30);
        this->isAnimation=true;  /*正面timer启动，动画状态*/
        this->flag=false;       /*flag状态改变（动画结束就将正面翻转为反面，状态改为反面）*/
    }
    else
    {
        timer2->start(30);
        this->isAnimation=true;
        this->flag=true;
    }
}
void Myfood::mousePressEvent(QMouseEvent *e)/*鼠标按下时间重写*/
{
    if(this->isAnimation||this->isWin)
    {
        return;
    }
    else
    {
        QPushButton::mousePressEvent(e);
    }
}
