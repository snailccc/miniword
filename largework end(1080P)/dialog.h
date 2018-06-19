#ifndef DIALOG_H
#define DIALOG_H
#include "mainwindow.h"
#include<QDialog>
#include<QMessageBox>
#include<QLineEdit>


class SearchText:public QDialog
{
    Q_OBJECT

public:
    explicit SearchText(QWidget *parent = 0);
    ~SearchText(){}

    QPushButton *button;
    QLabel *label;
    QLineEdit *content,*re_content;
    QPushButton *up,*down;
    QString str;

};

class ReText:public QDialog
{
    Q_OBJECT

public:
    explicit ReText(QWidget *parent = 0);
    ~ReText(){delete this;}

    QPushButton *button;
    QLabel *label;
    QLineEdit *content,*re_content;
    QPushButton *up,*down;
    QPushButton *rep;
    QString str;
};

#endif // DIALOG_H
