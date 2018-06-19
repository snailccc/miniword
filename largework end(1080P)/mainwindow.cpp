#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<header.h>
#include<Windows.h>
#pragma execution_character_set("utf-8")
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    int i,j;
    //阴影和内容设计
    mainwindowheight=600;
    mainwindowwidth=800;
    setMinimumSize(mainwindowwidth,mainwindowheight);
    havefileroute=0;
    setWindowTitle(tr(name));
    this->resize(QSize(800,600));
    background=new BackGround(this);
    this->setAutoFillBackground(true);
    palette.setBrush(QPalette::Window,
                     QBrush(QPixmap(":icon/背景5.jpg").scaled(
                                                           this->size(),
                                                           Qt::IgnoreAspectRatio,
                                                           Qt::SmoothTransformation)));             // 使用平滑的缩放方式
    ui->setupUi(this);
    this->setPalette(palette);
    //界面部分操作
    CreateActions();
    CreateMenus();
    CreateTools();
    CreateContextMenu();
    setCentralWidget(background);
    searchx1=searchy1=searchy2=-1;
    //background->setWindowOpacity(0.9);//透明度
    this->setWindowTitle("享受编辑的自由");

}

void MainWindow::CreateActions()
{

    //文件
    NewFile=new QAction(QIcon(":icon/新建.png"),tr("新建"),this);
    NewFile->setShortcut(tr("Ctrl+N"));
    connect(NewFile,SIGNAL(triggered()),this,SLOT(ShowNewFile()));

    OpenFile=new QAction(QIcon(":icon/打开.png"),tr("打开"),this);
    OpenFile->setShortcut(tr("Ctrl+O"));
    connect(OpenFile,SIGNAL(triggered()),this,SLOT(ShowOpenFile()));

    SaveFile=new QAction(QIcon(":icon/保存.png"),tr("保存"),this);
    SaveFile->setShortcut(tr("Ctrl+s"));
    connect(SaveFile,SIGNAL(triggered(bool)),this,SLOT(ShowSaveFile()));

    AnotherSaveFile=new QAction(QIcon(":icon/另存为.png"),tr("另存为"),this);
    connect(AnotherSaveFile,SIGNAL(triggered(bool)),this,SLOT(ShowAnotherSaveFile()));

    Quick=new QAction(QIcon(":icon/退出.png"),tr("退出"),this);
    Quick->setShortcut(tr("Ctrl+Q"));
    connect(Quick,SIGNAL(triggered()),this,SLOT(close()));

    //编辑
    Undo=new QAction(QIcon(":icon/撤销.png"),tr("撤销"),this);
    Undo->setShortcut(tr("Ctrl+z"));
    connect(Undo,SIGNAL(triggered(bool)),this,SLOT(undoaction()));

    Redo=new QAction(QIcon(":icon/重复.png"),tr("重复"),this);
    Redo->setShortcut(tr("Ctrl+Y"));
    connect(Redo,SIGNAL(triggered(bool)),this,SLOT(redoaction()));

    Copy=new QAction(QIcon(":icon/复制.png"),tr("复制"),this);
    Copy->setShortcut(tr("Ctrl+C"));
    connect(Copy,SIGNAL(triggered(bool)),this,SLOT(copyaction()));

    Paste=new QAction(QIcon(":icon/粘贴.png"),tr("粘贴"),this);
    Paste->setShortcut(tr("Ctrl+V"));
    connect(Paste,SIGNAL(triggered(bool)),this,SLOT(pasteaction()));

    Cut=new QAction(QIcon(":icon/剪切.png"),tr("剪切"),this);
    Cut->setShortcut(tr("Ctrl+X"));
    connect(Cut,SIGNAL(triggered(bool)),this,SLOT(cutaction()));

    Home=new QAction(QIcon(":icon/ppp.png"),tr("Home"),this);
    Home->setShortcut(tr("Home"));
    connect(Home,SIGNAL(triggered(bool)),this,SLOT(HomeAction()));

    cur_color=new QAction(QIcon(":icon/颜色.png"),tr("改变光标颜色"),this);
    connect(cur_color,SIGNAL(triggered(bool)),this,SLOT(Cur_Color()));

    word_count=new QAction(QIcon(":icon/统计.png"),tr("字符统计"),this);
    connect(word_count,SIGNAL(triggered(bool)),this,SLOT(Word_Count()));

    //查看
    C_all=new QAction(QIcon(":icon/全选.png"),tr("全选"),this);
    C_all->setShortcut(tr("Ctrl+A"));
    connect(C_all,SIGNAL(triggered(bool)),this,SLOT(C_allAction()));

    Search=new QAction(QIcon(":icon/查找.png"),tr("查找"),this);
    Search->setShortcut(tr("Ctrl+F"));
    connect(Search,SIGNAL(triggered(bool)),this,SLOT(SearchAction()));

    Replace=new QAction(QIcon(":icon/替换.png"),tr("替换"),this);
    Replace->setShortcut(tr("Ctrl+H"));
    connect(Replace,SIGNAL(triggered(bool)),this,SLOT(ReplaceAction()));
    //cha
    searchtext=new SearchText(this);
    retext=new ReText(this);
    connect(searchtext->up,SIGNAL(clicked(bool)),this,SLOT(s_searchfile_up()));
    connect(searchtext->down,SIGNAL(clicked(bool)),this,SLOT(s_searchfile_down()));
    connect(retext->up,SIGNAL(clicked(bool)),this,SLOT(r_searchfile_up()));
    connect(retext->down,SIGNAL(clicked(bool)),this,SLOT(r_searchfile_down()));
    connect(retext->rep,SIGNAL(clicked(bool)),this,SLOT(replacefile()));

    //帮助
    about=new QAction(QIcon(":icon/关于.png"),tr("关于"));
    connect(about,SIGNAL(triggered()),this,SLOT(AboutAction()));

}

void MainWindow::CreateTools()
{
    //    ui->mainToolBar=addToolBar("文件");
    fileTool=addToolBar("文件");
    delete ui->mainToolBar;
    fileTool->setToolTip("文件");
    fileTool->addAction(NewFile);
    fileTool->addAction(OpenFile);
    fileTool->addAction(SaveFile);

    doTool=addToolBar("编辑");
    doTool->addAction(Undo);
    doTool->addAction(Redo);
    doTool->addAction(cur_color);
    //滚轮
    //    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    //    mainLayout->addWidget(horizental);





}

void MainWindow::CreateMenus()
{

    file = menuBar()->addMenu(tr("文件"));
    file->addAction(NewFile);
    file->addAction(OpenFile);
    file->addAction(SaveFile);
    file->addAction(AnotherSaveFile);
    file->addAction(Quick);

    file=menuBar()->addMenu(tr("编辑"));
    file->addAction(Undo);
    file->addAction(Redo);
    file->addAction(Copy);
    file->addAction(Paste);
    file->addAction(Cut);
    file->addAction(cur_color);

    file=menuBar()->addMenu(tr("查看"));
    file->addAction(C_all);
    file->addAction(Search);
    file->addAction(Replace);
    file->addAction(word_count);


    file=menuBar()->addMenu(tr("帮助"));
    file->addAction(about);


}


void MainWindow::searchmainwindowsize()
{
    if(mainwindowwidth!=width())
    {
        mainwindowwidth=width();
    }
    if(mainwindowheight!=height())
    {
        mainwindowheight=height();
    }
}

void MainWindow::ShowNewFile()
{
    MainWindow *newWindow = new MainWindow;
    newWindow->show();
}


void MainWindow::loadFile(QString filename)
{
    printf("filename:%s\n",filename.data());

    QFile file(filename);
    if(file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream textStream(&file);
    }
}

void MainWindow::ShowSaveFile()
{
    background->text->question=0;
    if(havefileroute==0){
        QString file;
        file= QFileDialog::getSaveFileName(this);  // 这一行获取的是文件选择框选择之后的完整路径加文件名
        fileroute=file.toStdString();
    }
    havefileroute=1;
    ofstream outfilee(fileroute);
    string*forprint = new string[background->text->t->file->linenum];
    int k = background->text->t->file->linenum;
    int pp = 0;
    background->text->t->worklinee = NULL;
    chunk*workp = NULL;
    string kp;
    background->text->t->worklinee = background->text->t->file->firstline;
    while (k--&&background->text->t->worklinee != NULL) {
        workp = background->text->t->worklinee->head;
        kp.clear();
        while (workp != NULL) {
            for (int i = 0; i < store_size; i++)
            {
                if (workp->data[i] != '#')
                    kp += workp->data[i];
                else break;
            }
            workp = workp->next;
        }
        forprint[pp] = kp;
        pp++;
        background->text->t-> worklinee = background->text->t->worklinee->nextline;
        //workp = workline->head;
    }
    for (int k = 1; k <= background->text->t->file->linenum; k++)
    {
        {for(int i=0;i<forprint[k - 1].length();i++)
                if(forprint[k - 1][i]!='\0') outfilee << forprint[k - 1][i];
                else break;
        }
        outfilee << "\r\n";
    }
}

void MainWindow::ShowAnotherSaveFile()
{
    background->text->question=0;
    havefileroute=1;
    QString file;
    file= QFileDialog::getSaveFileName(this);  // 这一行获取的是文件选择框选择之后的完整路径加文件名
    fileroute=file.toStdString();
    ofstream outfilee(fileroute);
    string*forprint = new string[background->text->t->file->linenum];
    int k = background->text->t->file->linenum;
    int pp = 0;
    background->text->t->worklinee = NULL;
    chunk*workp = NULL;
    string kp;
    background->text->t->worklinee = background->text->t->file->firstline;
    while (k--&&background->text->t->worklinee != NULL) {
        workp = background->text->t->worklinee->head;
        kp.clear();
        while (workp != NULL) {
            for (int i = 0; i < store_size; i++)
            {
                if (workp->data[i] != '#')
                    kp += workp->data[i];
                else break;
            }
            workp = workp->next;
        }
        forprint[pp] = kp;
        pp++;
        background->text->t-> worklinee = background->text->t->worklinee->nextline;
        //workp = workline->head;
    }
    for (int k = 1; k <= background->text->t->file->linenum; k++)
    {
        {for(int i=0;i<forprint[k - 1].length();i++)
                if(forprint[k - 1][i]!='\0') outfilee << forprint[k - 1][i];
                else break;
        }
        outfilee << "\r\n";
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(background->text->question){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Waring", "检测到文件修改，是否需要保存?", QMessageBox::Yes | QMessageBox::No);
        if(reply == QMessageBox::Yes)
        {  ShowSaveFile();
        }
        else
        {
        }
    }
}
void MainWindow::undoaction()
{


    if( background->text->t->posforundo<=0)return;
    background->text->t->posforundo--;
    background->text->line=1;
    background->text->row=0;
    background->text->curse_x=(background->text->row+-background->text->startrow)*g_word_width-g_linestartspace-2;
    background->text->curse_y=(background->text->line-background->text->startline-1)*g_lineheight-g_rowstartspace;
    background->text->curse->setGeometry(background->text->curse_x,background->text->curse_y,g_curse_width,g_lineheight);
    cout<<"undo"<<background->text->t->posforundo<<endl;
    cout<<"type"<<background->text->t->undo[background->text->t->posforundo].type<<endl;
    if(background->text->t->undo[background->text->t->posforundo].type==1){//原操作是插入char
        background->text->t->fileinlinebackspaceindex(background->text->t->file,background->text->t->undo[background->text->t->posforundo].newhang1,background->text->t->undo[background->text->t->posforundo].newlie1);
    }
    else if(background->text->t->undo[background->text->t->posforundo].type==2){//原操作插入string
        //cout<<"undo"<<background->text->t->posforundo<<endl;
        //cout<<background->text->t->undo[background->text->t->posforundo].newhang1<<" "<<background->text->t->undo[background->text->t->posforundo].newlie1<<" "<<background->text->t->undo[background->text->t->posforundo].newhang1<<" "<<background->text->t->undo[background->text->t->posforundo].newlie2<<endl;
        background->text->t->filechunkdelete(background->text->t->file,background->text->t->undo[background->text->t->posforundo].newhang1,background->text->t->undo[background->text->t->posforundo].newlie1,background->text->t->undo[background->text->t->posforundo].newhang1,background->text->t->undo[background->text->t->posforundo].newlie2);
    }
    else if(background->text->t->undo[background->text->t->posforundo].type==3)//原操作删除ch
    {
        // cout<<"3"<<endl;
        background->text->t->fileinlineinsertatindex(background->text->t->file,background->text->t->undo[background->text->t->posforundo].newhang1,background->text->t->undo[background->text->t->posforundo].newlie1,background->text->t->undo[background->text->t->posforundo].newch);
    }
    else if(background->text->t->undo[background->text->t->posforundo].type==4){//原操作删除一块
        line*kuai=background->text->t->getmarkcopy(background->text->t->undo[background->text->t->posforundo].kuai);
        background->text->t->filechunkpaste(background->text->t->file,background->text->t->undo[background->text->t->posforundo].newhang1,background->text->t->undo[background->text->t->posforundo].newlie1,kuai);
    }

    else if(background->text->t->undo[background->text->t->posforundo].type==5)//原操作加了一块
    { cout<<2<<endl;
        cout<<background->text->t->undo[background->text->t->posforundo].newhang1<<endl<<background->text->t->undo[background->text->t->posforundo].newlie1<<endl<<background->text->t->undo[background->text->t->posforundo].newhang2<<endl<<background->text->t->undo[background->text->t->posforundo].newlie2<<endl;
        cout<<"over"<<endl;
        background->text->t->filechunkdelete(background->text->t->file,background->text->t->undo[background->text->t->posforundo].newhang1,background->text->t->undo[background->text->t->posforundo].newlie1,background->text->t->undo[background->text->t->posforundo].newhang2,background->text->t->undo[background->text->t->posforundo].newlie2);
        cout<<2<<endl;
        cout<<background->text->t->posforundo<<"pos"<<endl;
    }
    else if(background->text->t->undo[background->text->t->posforundo].type==6){
        background->text->t->fileinlinebackspaceindex(background->text->t->file,background->text->t->undo[background->text->t->posforundo].newhang1,background->text->t->undo[background->text->t->posforundo].newlie1);
    }
    else if(background->text->t->undo[background->text->t->posforundo].type==7){
        background->text->t->fileinlinebackspaceindex(background->text->t->file,background->text->t->undo[background->text->t->posforundo].newhang1,background->text->t->undo[background->text->t->posforundo].newlie1);

    }
    else if(background->text->t->undo[background->text->t->posforundo].type==8)
    {
        background->text->t->fileinlinebackspaceindex(background->text->t->file,background->text->t->undo[background->text->t->posforundo].newhang1,background->text->t->undo[background->text->t->posforundo].newlie1);
    }
    for(int i=1;i<100;i++)
        background->text->pLabel[i]->clear();
    background->text->t->filestringprint(background->text->t->file);
    for(int i=1;i<=background->text->t->file->linenum;i++)
    {
        background->text->getqstring(qstr,background->text->t->forprint[i-1]);
        background->text->pLabel[i]->setText(qstr);
        background->text->pLabel[i]->setFont(background->text->ft);
        background->text->pLabel[i]->setGeometry(g_linestartspace,g_rowstartspace+(i-1-background->text->startline)*g_lineheight,g_linetotalwidth,g_lineheight);
    }
    background->text->t->printxingfile(background->text->t->file);
}

void MainWindow::redoaction()
{

    forundo temp=background->text->t->undo[background->text->t->posforundo];
    if(temp.type==0)return ;
    if(temp.type==1){//加char  undo删除 再加char
        background->text->t->fileinlineinsertatindex(background->text->t->file,temp.oldhang1,temp.oldlie1,temp.oldch);
    }
    else if(temp.type==2)
    {
        background->text->t->fileinlineinsertstring(background->text->t->file,temp.oldhang1,temp.oldlie1,temp.oldstr);
    }
    else if(temp.type==3){
        background->text->t->fileinlinebackspaceindex(background->text->t->file,temp.oldhang1,temp.oldlie1);
    }
    else if(temp.type==4){
        background->text->t->filechunkdelete(background->text->t->file,temp.oldhang1,temp.oldlie1,temp.oldhang2,temp.oldlie2);
    }
    else if(temp.type==5){

        cout<<"lie"<<temp.oldlie1<<endl;
        background->text->t->filechunkpaste(background->text->t->file,temp.oldhang1,temp.oldlie1,temp.kuai);
    }
    else if(temp.type==6){
        background->text->t->zeroenter(background->text->t->file);
    }
    else if(temp.type==7){
        background->text->t->fileatlinelastenter(background->text->t->file,temp.oldhang1);
    }
    else if(temp.type==8){
        background->text->t->fileatlineindexenter(background->text->t->file,temp.oldhang1,temp.oldlie1);
    }
    background->text->t->posforundo++;


    //显示
    for(int i=1;i<100;i++)
    { background->text->pLabel[i]->clear();
        background->text->t->filestringprint(background->text->t->file);}
    for(int i=1;i<=background->text->t->file->linenum;i++)
    {
        background->text->getqstring(qstr,background->text->t->forprint[i-1]);
        background->text->pLabel[i]->setText(qstr);
        background->text->pLabel[i]->setFont(background->text->ft);
        background->text->pLabel[i]->setGeometry(g_linestartspace,g_rowstartspace+(i-1-background->text->startline)*g_lineheight,g_linetotalwidth,g_lineheight);
    }
    //background->text->t->printxingline(background->text->t->file->firstline);
    background->text->t->printxingfile(background->text->t->file);
}


void MainWindow::pasteaction()
{

    int i;
    background->text->t->copyline=background->text->t->getmarkcopy(background->text->t->markcopy);
    background->text->t->filechunkpaste(background->text->t->file,background->text->line,background->text->row,background->text->t->copyline);//第row个字符之后粘贴
    background->text->t->filestringprint(background->text->t->file);
    background->text->t->undo[background->text->t->posforundo].type=5;
    background->text->t->undo[background->text->t->posforundo].oldhang1=background->text->t->undo[background->text->t->posforundo].newhang1=background->text->line;
    background->text->t->undo[background->text->t->posforundo].oldlie1=background->text->row;
    background->text->t->undo[background->text->t->posforundo].newlie1=background->text->row+1;
    background->text->t->undo[background->text->t->posforundo].kuai=background->text->t->getmarkcopy(background->text->t->markcopy);
    if(markcopyx1==markcopyx2){//只粘贴一行

        background->text->t->undo[background->text->t->posforundo].newhang2=background->text->line;
        background->text->t->undo[background->text->t->posforundo].newlie2=background->text->row+markcopyy2-markcopyy1+1;
        cout<<"past"<< background->text->t->undo[background->text->t->posforundo].newlie2<<endl;
    }
    else if(markcopyx1+1<=markcopyx2)//及两行以上
    {
        background->text->t->undo[background->text->t->posforundo].newhang2=background->text->line+markcopyx2-markcopyx1;
        background->text->t->undo[background->text->t->posforundo].newlie2=markcopyy2;
    }
    background->text->t->posforundo++;
    string temp;
    // background->text->t->forprint[];
    int linecount;
    for(int linecount=0;linecount<background->text->t->file->linenum;linecount++){
        temp=background->text->t->forprint[linecount];  cout<<"bug2"<<endl;
        for (int i = 0; i<temp.length(); i++)
        {
            if (IsDBCSLeadByte(temp[i]))//双字节
            {
                background->text ->chineseword[linecount+1][i+1]=1;
                background->text ->chineseword[linecount+1][i+2]=1;
                i++;
            }
            else//单字节
            {
                background->text ->chineseword[linecount+1][i+1]=0;
            }
        }
    }
    for(int i=1;i<=background->text->t->file->linenum;i++)//打印
        for(int j=1;j<=50;j++)
        {
            cout<<background->text->chineseword[i][j];
            if(j==50)cout<<endl;
        }

    //显示函数

    background->text->t->filestringprint(background->text->t->file);
    for(i=1;i<=background->text->t->file->linenum;i++)
    {
        background->text->getqstring(qstr,background->text->t->forprint[i-1]);
        background->text->pLabel[i]->setText(qstr);
        background->text->pLabel[i]->setFont(background->text->ft);
        background->text->pLabel[i]->setGeometry(g_linestartspace,g_rowstartspace+(i-1-background->text->startline)*g_lineheight,g_linetotalwidth,g_lineheight);
    }
    if(background->text->t->file->linenum>=this->height()/g_lineheight+1)
    {
        background->vertical->setMaximum(background->text->t->file->linenum-(this->height()/g_lineheight+1));
        background->vertical->setValue(background->vertical->maximum());
    }
    background->text->changescrolllength();
}
void MainWindow::cutaction()
{
    cout<<"cut"<<endl;
}

void MainWindow::HomeAction()
{
    cout<<"Home"<<endl;
}

void MainWindow::C_allAction()
{
    int i;

    for(i=1;i<=background->text->t->file->linenum;i++)
    {
        background->text->copyx1=1;
        background->text->copyy1=0;
        background->text->copyx2=background->text->t->file->linenum;
        background->text->copyy2=background->text->t->filesearchlinelength(background->text->t->file,background->text->t->file->linenum);
        background->text->qLabel[i]->setVisible(true);
        background->text->pLabel[i]->setStyleSheet("background-color:transparent");
        background->text->qLabel[i]->setStyleSheet("background-color:yellow");
        background->text->qLabel[i]->setGeometry(g_linestartspace-background->text->startrow*g_word_width,g_rowstartspace+(i-1-background->text->startline)*g_lineheight,background->text->t->filesearchlinelength(background->text->t->file,i)*g_word_width,g_lineheight);
    }
}

void MainWindow::SearchAction()
{
    searchtext->setVisible(true);
    searchtext->exec();
    background->text->searchline->setVisible(false);
}

void MainWindow::ReplaceAction()
{
    retext->setVisible(true);
    retext->exec();
    background->text->searchline->setVisible(false);
}





void MainWindow::s_searchfile_down()
{
    int i,j,k;
    QString str;
    string str1,str2;
    str=searchtext->content->text();
    str1=background->text->ToString(str);
    int devi=str1.size();
    j=background->text->line;
    k=background->text->row;
    int next[10];
    for(i=0;i<10;i++)
        next[i]=0;
    str1.insert(0,1,str1.length());
    while(1)
    {
        str2.clear();
        background->text->t->changestring(background->text->t->file,str2,j);
        str2.insert(0,1,str2.length());
        background->text->get_next(str1,next);
        i=background->text->Index_Kmp(str2,str1,background->text->row,next);
        i++;
        if(i!=0)
        {
            /*
            if(j>background->text->startline+background->text->height()/g_lineheight+1)
                background->vertical->setValue(background->vertical->value()+j-(background->text->startline+background->text->width()/g_lineheight+1));
            */

            background->text->searchline->setStyleSheet("background-color:yellow");
            background->text->pLabel[j]->setStyleSheet("background:transparent");
            background->text->row=i-1+str1.length()-1;
            background->changelineandrow(background->text->line,background->text->row);
            k=background->text->row;

            //滚轮变化
            if(j>=background->text->height()/g_lineheight+1&&j<=background->vertical->value()+background->text->height()/g_lineheight)
            {
                background->vertical->setValue(j-1);
            }
            else
            {
                background->vertical->setValue(0);
            }
            if(k>=background->text->width()/g_word_width&&k<=background->horizental->value()+background->text->width()/g_word_width)
            {
                background->horizental->setValue(k);
            }
            else
            {
                background->horizental->setValue(0);
            }
            if(j>background->vertical->value()+background->text->height()/g_lineheight)
            {
                background->vertical->setValue(j-background->text->height()/g_lineheight);
            }
            if(k>background->horizental->value()+background->text->width()/g_word_width)
            {
                background->horizental->setValue(k-devi);
            }


            background->text->curse_x=g_linestartspace+background->text->row*g_word_width-2;
            background->text->curse_y=g_rowstartspace+(background->text->line-1)*g_lineheight;
            background->text->curse->setGeometry(background->text->curse_x,background->text->curse_y,20,g_lineheight);
            //background->text->searchline->setStyleSheet("background-color:yellow");
            background->text->searchline->setGeometry(g_linestartspace+(i-1-background->text->startrow)*g_word_width,g_rowstartspace+(j-1-background->text->startline)*g_lineheight,g_word_width*(str1.length()-1),g_lineheight);
            background->text->searchline->setVisible(1);
            background->text->searchline->show();
            break;
        }
        else if(i==0)
        {
            if(j==background->text->t->file->linenum)
                break;
            else {
                j++;
                background->text->line++;
                background->text->row=0;
                k=0;
            }
        }

    }
}
void MainWindow::s_searchfile_up()
{
    int i,j,k;
    QString str;
    str=searchtext->content->text();
    string str1,str2;
    str1=background->text->ToString(str);
    int devi=str1.size();
    //    cout<<devi<<endl;
    reverse(str1.begin(),str1.end());  //翻转字符串
    j=background->text->line;
    k=background->text->row;
    int next[10];
    for(i=0;i<10;i++)
        next[i]=0;
    str1.insert(0,1,str1.length());
    while(1)
    {
        //background->text->pLabel[j]->setStyleSheet("background:transparent");
        str2.clear();
        background->text->t->changestring(background->text->t->file,str2,j);
        reverse(str2.begin(),str2.end());
        str2.insert(0,1,str2.length());
        background->text->get_next(str1,next);
        i=background->text->Index_Kmp(str2,str1,background->text->t->filesearchlinelength(background->text->t->file,background->text->line)-background->text->row,next);
        if(i>=0)
            i=background->text->t->filesearchlinelength(background->text->t->file,background->text->line)-i-str1.length()+2;
        if(i>0)
        {
            background->text->searchline->setStyleSheet("background-color:yellow");
            background->text->pLabel[j]->setStyleSheet("background-color:transparent");
            background->text->row=i-1;
            background->changelineandrow(background->text->line,background->text->row);
            searchy1=i-1;
            searchy2=background->text->row;
            searchx1=background->text->line;
            k=background->text->row;

            //滚轮变化
            if(j>=background->text->height()/g_lineheight+1&&j<=background->vertical->value()+background->text->height()/g_lineheight)
            {
                background->vertical->setValue(j-1);
            }
            else
            {
                background->vertical->setValue(0);
            }
            if(k>=background->text->width()/g_word_width&&k<=background->horizental->value()+background->text->width()/g_word_width)
            {
                background->horizental->setValue(k);
            }
            else
            {
                background->horizental->setValue(0);
            }
            if(j>background->vertical->value()+background->text->height()/g_lineheight)
            {
                background->vertical->setValue(j-background->text->height()/g_lineheight);
            }
            if(k>background->horizental->value()+background->text->width()/g_word_width)
            {
                background->horizental->setValue(k-devi);
            }

            background->text->curse_x=g_linestartspace+background->text->row*g_word_width-2;
            background->text->curse_y=g_rowstartspace+(background->text->line-1)*g_lineheight;
            background->text->curse->setGeometry(background->text->curse_x,background->text->curse_y,20,g_lineheight);
            //background->text->searchline->setStyleSheet("background-color:yellow");
            //            cout<<g_linestartspace+(i-1)*g_word_width<<","<<g_rowstartspace+(j-1)*g_lineheight<<","<<g_word_width*(str1.length()-1)<<","<<g_lineheight<<endl;
            background->text->searchline->setGeometry(g_linestartspace+(i-1-background->text->startrow)*g_word_width,g_rowstartspace+(j-1-background->text->startline)*g_lineheight,g_word_width*(str1.length()-1),g_lineheight);
            background->text->searchline->setVisible(true);
            background->text->searchline->show();
            break;
        }
        else if(i<=0||background->text->row==0)
        {
            if(j==1)
                break;
            else {
                j--;
                background->text->line--;
                background->text->row=background->text->t->filesearchlinelength(background->text->t->file,background->text->line);
                k=background->text->row;
            }
        }
    }
}
void MainWindow::r_searchfile_down()
{
    int i,j,k;
    string str1,str2;
    QString str;
    str=retext->content->text();
    str1=background->text->ToString(str);
    int devi=str1.size();
    j=background->text->line;
    k=background->text->row;
    int next[10];
    for(i=0;i<10;i++)
        next[i]=0;
    str1.insert(0,1,str1.length());
    while(1)
    {

        str2.clear();
        background->text->t->changestring(background->text->t->file,str2,j);
        str2.insert(0,1,str2.length());
        background->text->get_next(str1,next);
        i=background->text->Index_Kmp(str2,str1,background->text->row,next);
        i++;
        if(i!=0)
        {
            background->text->searchline->setStyleSheet("background-color:yellow");
            background->text->pLabel[j]->setStyleSheet("background-color:transparent");
            background->text->row=i-1+str1.length()-1;
            searchy1=i;
            searchy2=background->text->row;
            searchx1=background->text->line;
            background->changelineandrow(background->text->line,background->text->row);
            k=background->text->row;

            //滚轮变化
            if(j>background->vertical->value()+background->text->height()/g_lineheight)
            {
                background->vertical->setValue(j-background->text->height()/g_lineheight);
            }
            if(k>background->horizental->value()+background->text->width()/g_word_width)
            {
                background->horizental->setValue(k-devi);
            }
            if(j>=background->text->height()/g_lineheight+1&&j<=background->vertical->value()+background->text->height()/g_lineheight)
            {
                background->vertical->setValue(j-1);
            }
            else
            {
                background->vertical->setValue(0);
            }
            if(k>=background->text->width()/g_word_width&&k<=background->horizental->value()+background->text->width()/g_word_width)
            {
                background->horizental->setValue(k);
            }
            else
            {
                background->horizental->setValue(0);
            }


            background->text->curse_x=g_linestartspace+background->text->row*g_word_width-2;
            background->text->curse_y=g_rowstartspace+(background->text->line-1)*g_lineheight;
            background->text->curse->setGeometry(background->text->curse_x,background->text->curse_y,20,g_lineheight);
            //background->text->searchline->setStyleSheet("background-color:yellow");
            background->text->searchline->setGeometry(g_linestartspace+(i-1)*g_word_width,g_rowstartspace+(j-1)*g_lineheight,g_word_width*(str1.length()-1),g_lineheight);
            background->text->searchline->setVisible(true);
            background->text->searchline->show();
            break;
        }
        else if(i==0)
        {
            if(j==background->text->t->file->linenum)
                break;
            else {
                j++;
                background->text->line++;
                background->text->row=0;
                k=0;
            }
        }

    }
}
void MainWindow::r_searchfile_up()
{
    int i,j,k;
    QString str;
    str=retext->content->text();
    string str1,str2;
    str1=background->text->ToString(str);
    int devi=str1.size();
    reverse(str1.begin(),str1.end());  //翻转字符串
    j=background->text->line;
    k=background->text->row;
    int next[10];
    for(i=0;i<10;i++)
        next[i]=0;
    str1.insert(0,1,str1.length());
    while(1)
    {
        //background->text->pLabel[j]->setStyleSheet("background:transparent");
        str2.clear();
        background->text->t->changestring(background->text->t->file,str2,j);
        reverse(str2.begin(),str2.end());
        str2.insert(0,1,str2.length());
        background->text->get_next(str1,next);
        i=background->text->Index_Kmp(str2,str1,background->text->t->filesearchlinelength(background->text->t->file,background->text->line)-background->text->row,next);
        if(i>=0)
            i=background->text->t->filesearchlinelength(background->text->t->file,background->text->line)-i-str1.length()+2;
        if(i>0)
        {
            background->text->searchline->setStyleSheet("background-color:yellow");
            background->text->pLabel[j]->setStyleSheet("background-color:transparent");
            background->text->row=i-1;
            background->changelineandrow(background->text->line,background->text->row);
            k=background->text->row;

            //滚轮变化
            if(j>=background->text->height()/g_lineheight+1&&j<=background->vertical->value()+background->text->height()/g_lineheight)
            {
                background->vertical->setValue(j-1);
            }
            else
            {
                background->vertical->setValue(0);
            }
            if(k>=background->text->width()/g_word_width&&k<=background->horizental->value()+background->text->width()/g_word_width)
            {
                background->horizental->setValue(k);
            }
            else
            {
                background->horizental->setValue(0);
            }
            if(j>background->vertical->value()+background->text->height()/g_lineheight)
            {
                background->vertical->setValue(j-background->text->height()/g_lineheight);
            }
            if(k>background->horizental->value()+background->text->width()/g_word_width)
            {
                background->horizental->setValue(k-devi);
            }


            searchy2=background->text->row+str1.length()-1;
            searchy1=background->text->row+1;
            searchx1=background->text->line;


            background->text->curse_x=g_linestartspace+background->text->row*g_word_width-2;
            background->text->curse_y=g_rowstartspace+(background->text->line-1)*g_lineheight;
            background->text->curse->setGeometry(background->text->curse_x,background->text->curse_y,20,g_lineheight);
            //background->text->searchline->setStyleSheet("background-color:yellow");
            background->text->searchline->setGeometry(g_linestartspace+(i-1)*g_word_width,g_rowstartspace+(j-1)*g_lineheight,g_word_width*(str1.length()-1),g_lineheight);
            background->text->searchline->setVisible(true);
            background->text->searchline->show();
            break;
        }
        else if(i<=0||background->text->row==0)
        {
            if(j==1)
                break;
            else {
                j--;
                background->text->line--;
                background->text->row=background->text->t->filesearchlinelength(background->text->t->file,background->text->line);
                k=background->text->row;
            }
        }

    }
}
void MainWindow::replacefile()
{
    QString str;
    string s;
    str=this->retext->re_content->text();
    if(searchx1==-1)
    {
        r_searchfile_down();
    }
    background->text->searchline->setVisible(false);
    if(searchx1!=-1)
    {
        s=background->text->ToString(str);
        if(searchy1<searchy2)
            background->text->t->filesubstitude(background->text->t->file,searchx1,searchy1,searchx1,searchy2,s);
        else
            background->text->t->filesubstitude(background->text->t->file,searchx1,searchy2,searchx1,searchy1,s);
        s.clear();
        background->text->t->changestring( background->text->t->file,s,searchx1);
        background->text->getqstring(str,s);
        background->text->pLabel[searchx1]->setText(str);
        background->text->pLabel[searchx1]->setGeometry(g_linestartspace-background->text->startrow*g_word_width,g_rowstartspace+(searchx1-1-background->text->startline)*g_lineheight,g_linetotalwidth,g_lineheight);
        searchx1=searchy1=searchy2=-1;
        background->text->changescrolllength();

    }
}





void MainWindow::AboutAction()
{
    cout<<"about"<<endl;
    AboutWindow *a;
    a=new AboutWindow;
    a->show();
}

void MainWindow::CreateContextMenu()
{
    this->addAction(Undo);
    this->addAction(Copy);
    this->addAction(Paste);
    this->addAction(Cut);
    this->addAction(C_all);
    this->setContextMenuPolicy(Qt::ActionsContextMenu);
}
//void MainWindow::searchfile1()
//{
//    int i,j,k;
//    QString str;
//    string str1,str2;
//    str=b->content->text();
//    str1=background->text->ToString(str);
//    j=background->text->line;
//    k=background->text->row;
//    int next[10];
//    for(i=0;i<10;i++)
//        next[i]=0;
//     str1.insert(0,1,str1.length());
//    while(1)
//    {
//        str2.clear();
//        background->text->t->changestring(background->text->t->file,str2,j);
//        str2.insert(0,1,str2.length());
//        background->text->get_next(str1,next);
//        i=background->text->Index_Kmp(str2,str1,background->text->row,next);
//        i++;
//        if(i!=0)
//        {
//            background->text->pLabel[j]->setStyleSheet("background:transparent");
//            background->text->row=i-1+str1.length()-1;
//            background->changelineandrow(background->text->line,background->text->row);
//            k=background->text->row;
//            background->text->curse_x=g_linestartspace+background->text->row*g_word_width-2;
//            background->text->curse_y=g_rowstartspace+(background->text->line-1)*g_lineheight;
//            background->text->curse->setGeometry(background->text->curse_x,background->text->curse_y,20,g_lineheight);
//            background->text->searchline->setStyleSheet("background-color:green");
//            background->text->searchline->setGeometry(g_linestartspace+(i-1)*g_word_width,g_rowstartspace+(j-1)*g_lineheight,g_word_width*(str1.length()-1),g_lineheight);
//            background->text->searchline->show();
//            break;
//        }
//        else if(i==0)
//        {
//            if(j==background->text->t->file->linenum)
//                break;
//            else {
//                j++;
//                background->text->line++;
//                background->text->row=0;
//                k=0;
//            }
//        }
//    }
//}

//void MainWindow::searchfile2()
//{
//    int i,j,k;
//    QString str;
//    string str1,str2;
//    str=b->content->text();
//    str1=background->text->ToString(str);
//    reverse(str1.begin(),str1.end());  //翻转字符串
//    j=background->text->line;
//    k=background->text->row;
//    int next[10];
//    for(i=0;i<10;i++)
//        next[i]=0;
//     str1.insert(0,1,str1.length());
//    while(1)
//    {
//        background->text->pLabel[j]->setStyleSheet("background:transparent");
//        str2.clear();
//        background->text->t->changestring(background->text->t->file,str2,j);
//        reverse(str2.begin(),str2.end());
//        str2.insert(0,1,str2.length());
//        background->text->get_next(str1,next);
//        i=background->text->Index_Kmp(str2,str1,background->text->t->filesearchlinelength(background->text->t->file,background->text->line)-background->text->row,next);
//        if(i>=0)
//        i=background->text->t->filesearchlinelength(background->text->t->file,background->text->line)-i-str1.length()+2;
//        if(i>0)
//        {
//            background->text->row=i-1;
//            background->changelineandrow(background->text->line,background->text->row);
//            k=background->text->row;
//            background->text->curse_x=g_linestartspace+background->text->row*g_word_width-2;
//            background->text->curse_y=g_rowstartspace+(background->text->line-1)*g_lineheight;
//            background->text->curse->setGeometry(background->text->curse_x,background->text->curse_y,20,g_lineheight);
//            background->text->searchline->setStyleSheet("background-color:green");
//            background->text->searchline->setGeometry(g_linestartspace+(i-1)*g_word_width,g_rowstartspace+(j-1)*g_lineheight,g_word_width*(str1.length()-1),g_lineheight);
//            background->text->searchline->show();
//            break;
//        }
//        else if(i<=0||background->text->row==0)
//        {
//            if(j==1)
//                break;
//            else {
//                j--;
//                background->text->line--;
//                background->text->row=background->text->t->filesearchlinelength(background->text->t->file,background->text->line);
//                k=background->text->row;
//            }
//        }
//    }
//    cout<<"mm"<<endl;
//}
void MainWindow::ShowOpenFile()
{
    background->text->question=0;
    int i,j;
    background->text->t->initfile(background->text->t->file);
    //fileName=QFileDialog::getOpenFileName(this);
    QString file, file_name, file_path;
    QFileInfo fi;
    file = QFileDialog::getOpenFileName(this);  // 这一行获取的是文件选择框选择之后的完整路径加文件名
    // fi = QFileInfo(file);
    // file_name = fi.fileName();  //获取文件名
    //file_path = fi.absolutePath(); //获取文件路径(不包含文件名)
    //qDebug()<<file_path<<endl;
    fileroute= file.toStdString();
    ifstream infile(fileroute);
    string temp;
    /*
    if (!infile.is_open())
    {
        cout << "未成功打开文件" << endl;
    }
    int linecount = 0;
    while (getline(infile, temp))
    {
        linecount++;
        if (temp.empty() && linecount == 1)//文件中第一行为空  无操作
            cout << "第1行空" << endl;
        else if (temp.empty())
            background->text->t->fileatlinelastenter(background->text->t->file, linecount - 1);
        else
        {
            background->text->t->fileatlinelastenter(background->text->t->file, linecount - 1);
           background->text-> t->fileinlineinsertstring(background->text->t->file, linecount, 1, temp);
        }
    }*/
    if (!infile.is_open())
    {
        cout << "未成功打开文件" << endl;
    }
    int linecount = 0;
    while (getline(infile, temp))
    {
        linecount++;
        if (temp.empty() && linecount == 1)//文件中第一行为空  无操作
            cout << "第1行空" << endl;
        else if (temp.empty())
            background->text->t->fileatlinelastenter(background->text->t->file, linecount - 1);
        else
        {
            background->text-> t->fileatlinelastenter(background->text->t->file, linecount - 1);
            background->text->t->fileinlineinsertstring(background->text->t->file, linecount, 1, temp);
            for (int i = 0; i<temp.length(); i++)
            {
                if (IsDBCSLeadByte(temp[i]))//双字节
                {
                    background->text ->chineseword[linecount][i+1]=1;
                    background->text ->chineseword[linecount][i+2]=1;
                    i++;
                }
                else//单字节
                {
                    background->text ->chineseword[linecount+1][i+1]=0;

                }
            }
        }
    }
    for(i=1;i<=background->text->line+1;i++)
        background->text->pLabel[i]->clear();
    background->text->t->filestringprint(background->text->t->file);
    for(i=1;i<=background->text->t->file->linenum;i++)
    {
        background->text->getqstring(qstr,background->text->t->forprint[i-1]);
        background->text->pLabel[i]->setText(qstr);
        background->text->pLabel[i]->setFont(background->text->ft);
        background->text->pLabel[i]->setGeometry(g_linestartspace,g_rowstartspace+(i-1)*g_lineheight,g_linetotalwidth,g_lineheight);
    }
    background->text->line=background->text->t->file->linenum;
    background->text->row=background->text->t->filesearchlinelength(background->text->t->file,background->text->line);
    background->changelineandrow(background->text->line,background->text->row);
    //background->text->t->printxingfile(background->text->t->file);
    //滚轮操作
    if(background->text->t->file->linenum>this->height()/g_lineheight+1)
        background->vertical->setMaximum(background->text->t->file->linenum-(this->height()/g_lineheight+1));
    background->text->changescrolllength();
    /*
    int maxline=0;
    for(int i=1;i<=background->text->t->file->linenum;i++)
    {
        int temp=background->text->t->filesearchlinelength(background->text->t->file,i);
        if(temp>maxline)maxline=temp;
    }
   if(maxline-this->width()/g_word_width>0)
    background->horizental->setMaximum(maxline-this->width()/g_word_width);
    */
}


void MainWindow::copyaction()
{
    if( background->text->copyx1<background->text->copyx2||((background->text->copyx1==background->text->copyx2)&&background->text->copyy1<=background->text->copyy2))
    { markcopyx1=background->text->copyx1;
        markcopyx2=background->text->copyx2;
        markcopyy1=background->text->copyy1+1;
        markcopyy2=background->text->copyy2;
    }
    else {//反向选块时候改变markcopy坐标
        markcopyx1=background->text->copyx2;
        markcopyx2=background->text->copyx1;
        markcopyy1=background->text->copyy2+1;
        markcopyy2=background->text->copyy1;
    }
    cout<<"copy"<<endl;
    background->text->t->markcopy=background->text->t->filechunkcopy(background->text->t->file, markcopyx1, markcopyy1,markcopyx2,markcopyy2);

}

void MainWindow::Word_Count()
{
    cout<<"word_cout"<<endl;
    QDialog *dia=new QDialog(this);
    dia->setPalette(palette);
    dia->setWindowTitle("字符统计");
    dia->setAttribute(Qt::WA_QuitOnClose,true);
    dia->setWindowModality(Qt::NonModal);
    dia->setFixedSize(300,100);
    int num=0;
    for(int i=1;i<=this->background->text->t->file->linenum;i++)
    {
        num+=this->background->text->t->filesearchlinelength(this->background->text->t->file,i);
    }
    QString t1,t2;
    t1="字符总数："+QString::number(num,10);
    t2="总行数："+QString::number(this->background->text->t->file->linenum,10);
    QLabel label1(dia);
    QLabel label2(dia);
    label1.setText(t1);
    label1.setGeometry(10,10,100,30);
    label1.show();
    label2.setText(t2);
    label2.setGeometry(10,50,100,30);
    label2.show();
    dia->exec();
}
void MainWindow::Cur_Color()
{
    switch (color%5) {
    case 0:
        pe.setColor(QPalette::WindowText,Qt::red);
        this->background->text->curse->setPalette(pe);
        break;
    case 1:
        pe.setColor(QPalette::WindowText,Qt::yellow);
        this->background->text->curse->setPalette(pe);
        break;
    case 2:
        pe.setColor(QPalette::WindowText,Qt::blue);
        this->background->text->curse->setPalette(pe);
        break;
    case 3:
        pe.setColor(QPalette::WindowText,Qt::black);
        this->background->text->curse->setPalette(pe);
        break;
    case 4:
        pe.setColor(QPalette::WindowText,Qt::green);
        this->background->text->curse->setPalette(pe);
        break;
    default:
        break;
    }
    color++;
}

