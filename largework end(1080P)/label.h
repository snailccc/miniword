#ifndef LABEL_H
#define LABEL_H
#include<header.h>
class label : public QLabel
{
    Q_OBJECT
public:
    //explicit label(QWidget *parent = 0);
    ~label();
    void keyPressEvent(QKeyEvent *event);
};
#endif // LABEL_H
