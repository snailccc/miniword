#ifndef VIEWLIST_H
#define VIEWLIST_H
#include "mainwindow.h"
#include "background.h"
#include<QListView>

class viewlist:public QWidget
{
    Q_OBJECT
public:
    viewlist(BackGround*parent);
    void movecurse();
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent*event);
    void mouseReleaseEvent(QMouseEvent*event);
    void inputMethodEvent(QInputMethodEvent * a);
    string ToString(const QString& qstr);
    void getqstring(QString&qstr,string&str);
    void changechineseword(int a,int b);
    int judgebetweenchineseword(int b,int a);
    void get_next(string str,int next[]);
    int Index_Kmp(string str1, string str2, int pos,int next[]);
    void resizeEvent(QResizeEvent *event);
    void changescrolllength();
    QLabel *searchline;
    QString qstr;
    string str;
    Storage*t;
    QLabel *curse;//设置光标
    QLabel *pLabel[100];    //行label指针
    QLabel *qLabel[100];
    QLabel *mLabel[100];
    QLabel *blackboard;
    QTimer*timer1;
    QTimer*timer2;
    int curse_sum;                //光标闪烁次数
    int curse_x,curse_y;   //光标当前坐标
    int capslock_num;
    int capslock;         //当前大小写状态
    int wheelnum;         //滚轮滚动数目
    int copyx1,copyy1;   //拷贝块的两个坐标
    int copyx2,copyy2;
    int question;
    QFont ft;     //描述字的大小
    bool chineseword[100][1000];
    QPalette*color;  //设置颜色
    int line,row;
    int viewlistheight,viewlistwidth;
    int startline;
    int startrow;
    int shadow;//选定阴影
    BackGround *background;

    ~viewlist(){}
protected slots:
    void cursestar();
};

#endif // VIEWLIST_H
