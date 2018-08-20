#ifndef PLAY_H
#define PLAY_H
#include"myfood.h"
#include <QWidget>

class Play : public QWidget
{
    Q_OBJECT
public:
    explicit Play(QWidget *parent = nullptr);

    int levalIndex;/*关卡号*/
    Play(int levalIndex);

    void paintEvent(QPaintEvent *event);

    int gameArray[4][4];

    Myfood*foodBtn[4][4];/*Food按钮数组*/

    bool isWin=true;/*胜利标志*/
signals:
    void chooseBack();
public slots:
};

#endif // PLAY_H
