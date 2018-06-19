#ifndef BACKGROUND_H
#define BACKGROUND_H
#include<header.h>
#include "viewlist.h"
#include"mainwindow.h"
class QLabel;
class dialog;
class QListView;
class viewlist;
class Storage;
class QGridLayout;
#include<qscrollbar.h>
#include<QScrollArea>
class BackGround : public QWidget
{
    Q_OBJECT
public:
    explicit BackGround(QWidget *parent = 0);
    //查找部分 kmp算法
    int backgroundwidth;
    int backgroundheight;
    void changelineandrow(int line,int row);
    QImage img;
    QLabel *imagelabel;
    viewlist *text;
    QScrollBar *vertical;
    QScrollBar *horizental;
    QLabel*linelabel;    //行坐标label
    QLabel*rowlabel;     //列坐标label
    QLabel*rowsum;
    QLabel*linesum;
    char c[10];
    QString qstr;
    string str;
    QGridLayout*mainLayout;
    int horizentalmaxvalue;
    int horizentalminvalue;
    int verticalmaxvalue;
    int verticalminvalue;
    int horizentalvalue;
    int verticalvalue;
    int flag;
protected slots:
      int scrollmove1();
      int scrollmove2();

};

#endif // BACKGROUND_H
