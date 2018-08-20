#include "choose.h"
#include<QPainter>
#include<QPaintEvent>
#include<QPixmap>
#include<QWidget>
#include<QPushButton>
#include<QIcon>
#include "mybutton.h"
#include<QLabel>
#include<QFont>
#include<QColor>
#include <QTimer>
#include<QTime>
#include"play.h"
#include<QCoreApplication>
#include<QProcess>

#include<QSound>
Choose::Choose(QWidget *parent) : QWidget(parent)
{

    this->setFixedSize(1024,610);
    this->setWindowIcon (QIcon(":/image/f11meet.png"));
    this->setWindowTitle("选择关卡");
    QSound *chooseSound=new QSound(":/image/bbq.wav",this);/*选择按钮音效*/
    QSound *p_BackSound=new QSound(":/image/BackButtonSound.wav",this);/*play页返回按钮*/


    for(int i=0;i<12;i++)
    {
        Mybutton *chooseBtn=new Mybutton(":/image/smallmeet.png");
        chooseBtn->setParent(this);
        chooseBtn->move(360+(i%4)*150,160+(i/4)*110);
        QLabel *label=new QLabel;
        label->setParent(this);
        label->setFixedSize(chooseBtn->width(),chooseBtn->height());
        label->setFont(QFont("Hobo Std"));
        //label->setFont(QColor("red"));
        label->setText(QString::number(i+1));

        label->move(360+(i%4)*150,160+(i/4)*110);
        label->setAttribute(Qt::WA_TransparentForMouseEvents,true);

        connect(chooseBtn,&Mybutton::clicked,[=]()/*选关按钮监听*/
        {
            chooseSound->play();

            play=new Play(i+1);



            /*场景位置*/
            this->play->setGeometry(this->geometry());
            this->play->show();
            this->hide();


            //            QTime dieTime=QTime::currentTime().addMSecs(10);
            //            while(QTime::currentTime()<dieTime)
            //            QCoreApplication::processEvents(QEventLoop::AllEvents,100);/*闪烁*/
            connect(play,&Play::chooseBack,[=]()/*接收chooseBack信号跳转回选关窗口*/
            {
                p_BackSound->play();
                this->setGeometry(this->play->geometry());
                this->show();
                delete this->play;
                this->play=NULL;

            });
        });



    }
}
void Choose:: paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/back.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

}
