#include "play.h"
#include<QPixmap>
#include<QIcon>
#include <QPainter>
#include<QPixmap>
#include<QPainter>
#include"mybutton.h"
#include<QTimer>
#include<QLabel>
#include"myfood.h"
#include"dataconfig.h"
#include<QDebug>
#include<QRect>
#include<QPropertyAnimation>
#include<QAbstractAnimation>
#include<QSound>

Play::Play(int levalIndex)
{
    this->levalIndex=levalIndex;
    this->setFixedSize(1024,610);
    this->setWindowIcon(QIcon(":/image/gonxi.png"));
    this->setWindowTitle("Play");
    /*、翻转按钮、胜利音效*/

    QSound *playSound=new QSound(":/image/eat.wav",this);
    QSound *winSound=new QSound(":/image/LevelWinSound.wav",this);
    Mybutton *p_back=new Mybutton(":/image/back2.png");
    p_back->setParent(this);
    p_back->move(830,460);


    connect(p_back,&Mybutton::clicked,[=]()   /*点击back发送chooseBack信号*/
    {

        //        QTimer::singleShot(10,this,[=]()
        //        {
        emit this->chooseBack();
        //        });

    });
    /*设置显示当前关卡label*/
    QLabel*label=new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("Hobo Std");
    font.setPointSize(20);
    label->setFont(font);

    QString str=QString("Leavel:%1").arg(this->levalIndex);
    label->setText(str);
    label->move(150,200);
    //label->setGeometry();

    /*获胜图片*/
    QLabel *winLabel=new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/image/gonxi.png");
    winLabel->selectedText();
   // winLabel->setGeometry(700,200,tmpPix.width(),tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move(700,-tmpPix.height());




    /*初始化二维数组*/
    dataConfig config;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            this->gameArray[i][j]=config.mData[this->levalIndex][i][j];

        }
    }

    for(int i=0;i<4;i++)  /*Food按钮背景*/
    {
        for(int j=0;j<4;j++)
        {
            QLabel* label=new QLabel;
            label->setGeometry(0,0,100,100);
            label->setPixmap(QPixmap(":/image/Food_back.png"));
            label->setParent(this);
            label->move(330+i*100,150+j*100);



            QString str;                          /*初始化关卡*/
            if(this->gameArray[i][j]==1)
            {
                str=":/image/food/smallhotdog1.png";
            }
            else
            {
                str=":/image/food/smallhotdog8.png";
            }
            Myfood*food=new Myfood(str);/*food*/
            food->setParent(this);
            food->move(330+i*100,150+j*100);

            food->posX=i;/*Food属性*/
            food->posY=j;
            food->flag=this->gameArray[i][j];

            foodBtn[i][j]=food;                 /*将food放入二维数组中*/
            connect(food,&Myfood::clicked,[=]()
            {
                playSound->play();
                for(int i=0;i<4;i++)   /*屏蔽按钮点击*/
                {
                    for(int j=0;j<4;j++)
                    {
                        foodBtn[i][j]->isWin=true;

                    }
                }

                food->changeFlag();
                this->gameArray[i][j]=this->gameArray[i][j]==1?0:1;

                /*延时翻周围*/
                QTimer::singleShot(300,this,[=]()
                {
                    /*右侧*/
                    if(food->posX+1<=3)
                    {
                        foodBtn[food->posX+1][food->posY]->changeFlag();
                        this->gameArray[food->posX+1][food->posY]=this->gameArray[food->posX+1][food->posY]==1?0:1;

                    }
                    /*左侧*/
                    if(food->posX-1>=0)
                    {
                        foodBtn[food->posX-1][food->posY]->changeFlag();
                        this->gameArray[food->posX-1][food->posY]=this->gameArray[food->posX-1][food->posY]==1?0:1;

                    }
                    /*下侧*/
                    if(food->posY+1<=3)
                    {
                        foodBtn[food->posX][food->posY+1]->changeFlag();
                        this->gameArray[food->posX][food->posY+1]=this->gameArray[food->posX][food->posY+1]==1?0:1;

                    }
                    /*上策*/
                    if(food->posY-1>=0)
                    {
                        foodBtn[food->posX][food->posY-1]->changeFlag();
                        this->gameArray[food->posX][food->posY-1]=this->gameArray[food->posX][food->posY-1]==1?0:1;
                    }

                    /*food允许点击*/
                    for(int i=0;i<4;i++)
                    {
                        for(int j=0;j<4;j++)
                        {
                            foodBtn[i][j]->isWin=false;
                        }
                    }

                    /*是否胜利*/
                    this->isWin=true;
                    for(int i=0;i<4;i++)
                    {
                        for(int j=0;j<4;j++)
                        {
                            if(foodBtn[i][j]->flag==false)
                            {
                                this->isWin=false;
                                break;
                            }
                        }
                    }
                    if(this->isWin)
                    {
                        winSound->play();
                        qDebug()<<"获胜";
                        for(int i=0;i<4;i++)
                        {
                            for(int j=0;j<4;j++)
                            {
                                foodBtn[i][j]->isWin=true;
                            }
                        }


                        QPropertyAnimation* animation=new QPropertyAnimation(winLabel,"geometry");
                        animation->setDuration(1000);
                        animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                        animation->setEndValue(QRect(winLabel->x(),winLabel->y()+500,winLabel->width(),winLabel->height()));
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        animation->start(QAbstractAnimation::DeleteWhenStopped);

                    }
                });
            });



        }
    }

}
void Play::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/back.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

}
