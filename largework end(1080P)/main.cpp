#include "mainwindow.h"
#include <QApplication>
#include<QSplashScreen>
#include<QElapsedTimer>
#include<header.h>
int main(int argc, char *argv[])
{

    QTextStream cin(stdin,  QIODevice::ReadOnly);
    QTextStream cout(stdout,  QIODevice::WriteOnly);
    QTextStream cerr(stderr,  QIODevice::WriteOnly);
    QString strText;
    QApplication a(argc, argv);

    //启动初始化界面
    QPixmap pixmap(":icon/启动界面.png");
    QSplashScreen screen(pixmap);
    screen.show();
//    screen.showMessage("编写此程序的人都是大帅哥", Qt::AlignCenter, Qt::red);
    int delayTime = 1;
    QElapsedTimer timer;

    timer.start();
    while(timer.elapsed() < (delayTime * 1000)&&0)
    {
         a.processEvents();
    }

    MainWindow w;
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    screen.finish(&w);
    w.show();
    return a.exec();
}
