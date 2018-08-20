#ifndef MYFOOD_H
#define MYFOOD_H
#include<QPushButton>
#include<QString>

class Myfood : public QPushButton
{
public:
    Myfood();

    Myfood(QString butImg);

    int posX;
    int posY;
    bool flag;             /*记录正反*/
    void changeFlag();   /*改变正反状态*/
    QTimer *timer1;
    QTimer *timer2;
    int min=1;
    int max=8;
    bool isAnimation=false;    /*动画状态*/
    void mousePressEvent(QMouseEvent *e);
    bool isWin=false;           /*输赢状态*/
};

#endif // MYFOOD_H
