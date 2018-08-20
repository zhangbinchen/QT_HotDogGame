#include "mybutton.h"
#include<QDebug>
#include<QPropertyAnimation>
Mybutton::Mybutton()
{

}
Mybutton::Mybutton(QString normalImg,QString pressImg)
{
    normalImgPath=normalImg;
    pressImgPath=pressImg;
    QPixmap pixmap;
    bool ret=pixmap.load(normalImgPath);
    if(!ret)
    {
        qDebug()<<normalImg<<"加载图片失败！";
    }

    this->setFixedSize(pixmap.width(),pixmap.height());
   this->setStyleSheet("QPushButton{border:0px}");
   this->setIcon(pixmap);
   this->setIconSize(QSize(pixmap.width(),pixmap.height()));

}
void Mybutton::zoom1()
{
    QPropertyAnimation *animation1=new QPropertyAnimation(this,"geometry");
    animation1->setDuration(200);
    animation1->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation1->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation1->setEasingCurve(QEasingCurve::OutBounce);
    animation1->start(QAbstractAnimation::DeleteWhenStopped);
}

void Mybutton::zoom2()
{
    QPropertyAnimation*animation1=new QPropertyAnimation(this,"geometry");
    animation1->setDuration(200);
    animation1->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation1->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation1->setEasingCurve(QEasingCurve::OutBounce);
    animation1->start(QAbstractAnimation::DeleteWhenStopped);
}







