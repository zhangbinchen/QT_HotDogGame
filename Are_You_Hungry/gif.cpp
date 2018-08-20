#include "gif.h"
#include<QLabel>
#include<QMovie>
#include<QIcon>
Gif::Gif(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(1024,610);
    this->setWindowIcon(QIcon(":/image/hotdog.png"));
    this->setWindowTitle("AHHHHH");

    QMovie *movie=new QMovie(":/image/paidaxing.gif");
    movie->start();
    QLabel *label=new QLabel;
    label->setFixedSize(1024,610);
    label->setMovie(movie);
}
