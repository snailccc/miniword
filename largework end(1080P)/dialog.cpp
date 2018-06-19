#include "dialog.h"
#include<QDebug>
#include<QSize>

SearchText::SearchText(QWidget *parent):
    QDialog(parent)
{

    QWidget::setAttribute(Qt::WA_QuitOnClose,false);
    this->setFixedSize(450,50);
    this->setWindowTitle("查找");

    label=new QLabel("查找内容:",this);
    label->setGeometry(10,10,65,30);
    content=new QLineEdit(this);
    content->setGeometry(80,10,250,30);

    up=new QPushButton(this);
    up->setIcon(QIcon(":icon/向上.png"));
    up->setGeometry(370,10,30,30);
    down=new QPushButton(this);
    down->setIcon(QIcon(":icon/向下.png"));
    down->setGeometry(340,10,30,30);
}


ReText::ReText(QWidget *parent):
    QDialog(parent)
{
    QWidget::setAttribute(Qt::WA_QuitOnClose,false);
    this->setFixedSize(450,100);
    this->setWindowTitle("替换");

    label=new QLabel("查找内容:",this);
    label->setGeometry(10,10,65,30);
    content=new QLineEdit(this);
    content->setGeometry(80,10,250,30);

    label=new QLabel("替换内容",this);
    label->setGeometry(10,50,65,30);
    re_content=new QLineEdit(this);
    re_content->setGeometry(80,50,250,30);

    up=new QPushButton(this);
    up->setIcon(QIcon(":icon/向上.png"));
    up->setGeometry(370,10,30,30);
    down=new QPushButton(this);
    down->setIcon(QIcon(":icon/向下.png"));
    down->setGeometry(340,10,30,30);
    rep=new QPushButton(this);
    rep->setIcon(QIcon(":icon/替换.png"));
    rep->setGeometry(340,50,30,30);


    QApplication::setQuitOnLastWindowClosed(false);
}


