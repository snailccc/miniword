#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<iostream>
using namespace std;
#include <QMainWindow>
#include<header.h>
#include<qscrollbar.h>
#include<QScrollArea>
class QLabel;
class STRING;
class Storage;
class dialog;
class scrollbar;
class SearchText;
class ReText;
namespace Ui {
class MainWindow;
}
class BackGround;
class QTextCharFormat;
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

    //界面创建
    void CreateMenus();
    void CreateTools();
    void CreateActions();
    void loadFile(QString filename);
    void mergeFormat(QTextCharFormat);
    void CreateContextMenu();
    //void setTabOrder(QWidget *, QWidget *);
private:
    //int line,row;      //当前行数列数
    Ui::MainWindow *ui;
    dialog*b;
    QLabel *searchline;
    int color=0;
    QPalette pe;
    int mainwindowheight;
    int mainwindowwidth;
    QString content;
    int markcopyx1,markcopyy1;//暂存块复制的坐标
    int markcopyx2,markcopyy2;
    QString qstr;
    string str;
    int searchx1,searchy1,searchy2;
    int havefileroute;
    string fileroute;
    //界面创建部分
    char name[60]="老流氓文本编辑器-未命名";
    int n=1;
    QPalette palette;
    QMenu *file;
    QImage img;
    QString fileName;
    BackGround *background;
    //文件菜单项
    QAction *OpenFile,*NewFile,*SaveFile,*AnotherSaveFile,*Quick;
    //编辑菜单项
    QAction *Undo,*Redo,*Copy,*Paste,*Cut,*Home,*cur_color;
    //查看菜单项
    QAction *C_all,*Search,*Replace,*word_count;
    SearchText *searchtext;
    ReText *retext;
    //帮助菜单项
    QAction *about;
    QToolBar *fileTool,*doTool;
    //滚轮




protected slots:
    void ShowNewFile();
    void ShowOpenFile();
    void ShowSaveFile();
    void ShowAnotherSaveFile();

    void undoaction();
    void redoaction();
    void cutaction();
    void copyaction();
    void pasteaction();
    void HomeAction();

    void C_allAction();
    void SearchAction();
    void ReplaceAction();
    void s_searchfile_up();
    void s_searchfile_down();
    void r_searchfile_up();
    void r_searchfile_down();
    void replacefile();
    void closeEvent(QCloseEvent *event);
    void AboutAction();

    void Word_Count();
    void Cur_Color();

    void searchmainwindowsize();

};

#endif // MAINWINDOW_H
