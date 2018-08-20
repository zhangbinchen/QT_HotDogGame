#ifndef CHOOSE_H
#define CHOOSE_H
#include"play.h"
#include <QWidget>
#include"gif.h"

class Choose : public QWidget
{
    Q_OBJECT
public:
    explicit Choose(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event);
    Play *play=NULL;
    Gif *gif;



signals:
    void chooseBack();
public slots:
};

#endif // CHOOSE_H
