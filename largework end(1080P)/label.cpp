#include<header.h>
/*
label::QLabel(QWidget *parent) :
    QMainWindow(parent),
{
}
*/
label::~label()
{
    //delete ui;
}

void label::keyPressEvent(QKeyEvent *event)
{
    //0x30对应Ascii表中0，0x31表示1，剩下的一次类推

    if (0x30 <= event->key() && 0x39 >= event->key())  //数字
    {
        //cout<<"qq"<<endl;
        qDebug()<<event->key();
    }
    /*
    else if (0x2a == event->key())
    {

        qDebug()<<event->key();
    }
    else if (0x1b == event->key())
    {

    qDebug()<<event->key();
    }
    else if (0x08 == event->key())
    {
    qDebug()<<event->key();
    }
    else if (0x23 == event->key())
    {

    qDebug()<<event->key();
    }
    else if (0x0d == event->key())
    {
    qDebug()<<event->key();
    }
    else if (0x2e == event->key())
    {
        //sKey = ".";
        qDebug()<<"%d"<<event->key();
    }

    else if (0x54 == event->key())
    {
    qDebug()<<event->key();
    }
    */
    else if (0x41 <= event->key() && 0x48 >= event->key())//一部分字母
    {
    //cout<<"uu"<<endl;
    //qDebug()<<event->key();
    //qLabel->close();
    }
    else  //剩下的字母
    {
    //cout<<"mm"<<endl;
    //qDebug()<<event->key();
    }

}
