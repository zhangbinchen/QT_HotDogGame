#ifndef MYBUTTON_H
#define MYBUTTON_H
#include<QPushButton>

class Mybutton : public QPushButton
{
public:
    Mybutton();
    Mybutton(QString normalImg,QString pressImg="");
    QString normalImgPath;
    QString pressImgPath;

    void zoom1();
    void zoom2();


};

#endif // MYBUTTON_H
