#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H
class AboutWindow:public QWidget
{
   public:
       AboutWindow(QWidget *parent = 0);
       ~AboutWindow(){};
   protected:
       void paintEvent(QPaintEvent *);
};
#endif // ABOUTWINDOW_H
