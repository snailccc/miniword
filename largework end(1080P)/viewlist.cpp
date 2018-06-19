#include "viewlist.h"
#include "mainwindow.h"
#include "background.h"
#include"background.h"
#include<header.h>
#include<QHBoxLayout>
#include<QGraphicsOpacityEffect>


viewlist::viewlist(BackGround*parent)
{
    question=0;

    shadow=1;
    background=parent;
    int i,j;
    this->setAttribute(Qt::WA_InputMethodEnabled);
    this->setAttribute(Qt::WA_KeyCompression);
    this->setFocusPolicy(Qt::WheelFocus);

    this->setStyleSheet("background:white");
    for(i=0;i<100;i++)
    {
        mLabel[i]=new QLabel(this);
        qLabel[i]=new QLabel(this);
        mLabel[i]->setGeometry(g_linestartspace,g_rowstartspace+(i-1)*g_lineheight,g_linetotalwidth,g_lineheight);
    }

    searchline=new QLabel(this);
    searchline->setStyleSheet("background-color:yellow");
    searchline->setVisible(false);

    for(i=0;i<100;i++){
        pLabel[i]=new QLabel(this);
        pLabel[i]->setStyleSheet("background:transparent");
        pLabel[i]->setGeometry(g_linestartspace,g_rowstartspace+(i-1)*g_lineheight,g_linetotalwidth,g_lineheight);
    }

    for(i=0;i<100;i++)
        for(j=0;j<1000;j++)
            chineseword[i][j]=false;

    curse_x=g_linestartspace-2;
    curse_y=g_rowstartspace;
    capslock=0;
    line=1;
    row=0;
    capslock_num=0;
    copyx1=copyx2=copyy1=copyy2=0;
    ft.setPointSize(g_pointsize);
    pLabel[line]->setGeometry(g_linestartspace,g_rowstartspace,g_linetotalwidth,g_lineheight);
    pLabel[line]->show();
    t=new Storage;
    t->file=new File;
    t->initfile(t->file);

    curse_sum=0;
    timer1=new QTimer(this);
    timer2=new QTimer(this);

    connect(timer1,SIGNAL(timeout()),this,SLOT(cursestar()));
    connect(timer2,SIGNAL(timeout()),this,SLOT(searchmainwindowsize()));
    timer1->start(700);
    timer2->start(100);
    wheelnum=0;
    startline=0;
    startrow=0;

    t->posforundo=0;
    for(int i=0;i<=99;i++)
        t->undo[i]=t->initforundo();

    curse=new QLabel(this);
    curse->setText("|");
    curse->setGeometry(curse_x,curse_y,g_curse_width,g_lineheight);
    curse->setStyleSheet("background:transparent");
    QGraphicsOpacityEffect *opacityEffect=new QGraphicsOpacityEffect;
    this->setGraphicsEffect(opacityEffect);
    opacityEffect->setOpacity(0.7);

}

void viewlist::mousePressEvent(QMouseEvent *event)
{
    int i,j;
    if(event->button()==Qt::LeftButton)
    {
        for(i=1;i<100;i++)
            qLabel[i]->setVisible(false);
        i=event->pos().x()-event->pos().x()%g_word_width-2;
        j=(event->pos().y()-g_rowstartspace)-(event->pos().y()-g_rowstartspace)%g_lineheight+g_rowstartspace;

        if(t->judgeposition(t->file,(j-g_rowstartspace)/g_lineheight+1+startline,(i+2-g_linestartspace)/10+startrow)&&judgebetweenchineseword((j-g_rowstartspace)/g_lineheight+1,(i+2-g_linestartspace)/10)&&(j-g_rowstartspace)/g_lineheight+1>=0&&(i+2-g_linestartspace)/10>=0){
            curse_x=i;
            curse_y=j;
            row=(curse_x+2-g_linestartspace)/10+startrow;
            line=(curse_y-g_rowstartspace)/g_lineheight+1+startline;
            copyx1=copyx2=line;
            copyy1=copyy2=row;
            curse->setGeometry(curse_x,curse_y,g_curse_width,g_lineheight);
            background->changelineandrow(line,row);
            shadow=0;
        }
        else if(t->judgeposition(t->file,(j-g_rowstartspace)/g_lineheight+1+startline,(i+2-g_linestartspace)/10+startrow)&&judgebetweenchineseword((j-g_rowstartspace)/g_lineheight+1+startline,(i+2-g_linestartspace)/10+startrow)==0&&(j-g_rowstartspace)/g_lineheight+startline+1>=0&&(i+2-g_linestartspace)/10+startrow>=0)
        {
            curse_x=i;
            curse_y=j;
            row=(curse_x+2-g_linestartspace)/10-1+startrow;
            curse_x=g_linestartspace+row*g_word_width;
            line=(curse_y-g_rowstartspace)/g_lineheight+1+startline;
            copyx1=line;
            copyy1=row;
            background->changelineandrow(line,row);
            curse->setGeometry(curse_x,curse_y,g_curse_width,g_lineheight);
        }
    }
    else if(event->button()==Qt::RightButton)
    {

    }
}

void viewlist::mouseMoveEvent(QMouseEvent *event)
{
    int i,j,k,m,n;
    int x,y;
    x=event->pos().x()-event->pos().x()%g_word_width-2;
    y=(event->pos().y()-g_rowstartspace)-(event->pos().y()-g_rowstartspace)%g_lineheight+g_rowstartspace;
    if(t->judgeposition(t->file,(y-g_rowstartspace)/g_lineheight+startline+1,(x+2-g_linestartspace)/10+startrow))
    {
        if(x<0)
        {
            int v=background->horizental->value();
            background->horizental->setValue(v-1);
        }
        if(x>this->width()&&background->horizental->value()<background->horizental->maximum())
        {
            int v=background->horizental->value();
            background->horizental->setValue(v+1);
        }
        if(y<0)
        {
            int v=background->vertical->value();
            background->vertical->setValue(v-1);
        }
        if(y>this->height() && background->vertical->value()<background->vertical->maximum())
        {
            int v=background->vertical->value();
            background->vertical->setValue(v+1);
        }
        for(i=1;i<100;i++)
            qLabel[i]->setVisible(false);
        if(judgebetweenchineseword((y-g_rowstartspace)/g_lineheight+1+startline,(x+2-g_linestartspace)/g_word_width+startrow))
        {

            curse_x=x;
            curse_y=y;
            i=(curse_y-g_rowstartspace)/g_lineheight+1+startline;//获取列
            j=(curse_x+2-g_linestartspace)/10+startrow;//获取行

        }
        else
        {

            curse_x=x;
            curse_y=y;
            i=(curse_y-g_rowstartspace)/g_lineheight+1+startrow;
            j=(curse_x+2-g_linestartspace)/10-1+startline;
        }
        if(i!=line||j!=row){
            copyx2=i;
            copyy2=j;
            if(copyx1!=copyx2)
            {
                m=copyx1;
                n=copyx2;
                if(copyx1<copyx2)
                {
                    for(i=m;i<=n;i++)
                    {
                        qLabel[i]->setStyleSheet("background-color:yellow");
                        pLabel[i]->setStyleSheet("background-color:transparent");
                        if(i>m&&i<n){
                            qLabel[i]->setGeometry(g_linestartspace,g_rowstartspace+(i-1-startline)*g_lineheight,g_word_width*(t->filesearchlinelength(t->file,i)),g_lineheight);
                            qLabel[i]->show();
                        }
                        else if(i==m)
                        {
                            qLabel[i]->setGeometry(g_linestartspace+(copyy1-startrow)*g_word_width,g_rowstartspace+(i-1-startline)*g_lineheight,g_word_width*(t->filesearchlinelength(t->file,i)-copyy1),g_lineheight);
                            qLabel[i]->show();
                        }
                        else if(i==n)
                        {
                            qLabel[i]->setGeometry(g_linestartspace,g_rowstartspace+(i-1-startline)*g_lineheight,g_word_width*(copyy2-startrow),g_lineheight);
                            qLabel[i]->show();
                        }
                    }
                }
                else if(copyx1>copyx2)
                {
                    if(i>0)
                    {
                        qLabel[i]->setStyleSheet("background-color:yellow");
                        pLabel[i]->setStyleSheet("background:transparent");
                    }
                    for(i=m;i>=n;i--)
                    {
                        if(i<m&&i>n)
                        {
                            qLabel[i]->setGeometry(g_linestartspace,g_rowstartspace+(i-1-startline)*g_lineheight,g_word_width*(t->filesearchlinelength(t->file,i)),g_lineheight);
                            qLabel[i]->show();
                        }
                        else if(i==m)
                        {
                            qLabel[i]->setGeometry(g_linestartspace,g_rowstartspace+(i-1-startline)*g_lineheight,g_word_width*(copyy1-startrow),g_lineheight);
                            qLabel[i]->show();
                        }
                        else if(i==n)
                        {
                            qLabel[i]->setGeometry(g_linestartspace+(copyy2-startrow)*g_word_width,g_rowstartspace+(i-1-startline)*g_lineheight,g_word_width*(t->filesearchlinelength(t->file,i)-copyy2),g_lineheight);
                            qLabel[i]->show();
                        }
                    }
                }
            }
            else if(copyx1==copyx2)
            {
                qLabel[copyx1]->setStyleSheet("background-color:yellow");
                pLabel[copyx1]->setStyleSheet("background-color:transparent");
                if(copyy2-copyy1>0)
                {

                    qLabel[copyx1]->setGeometry(g_linestartspace+(copyy1-startrow)*g_word_width,g_rowstartspace+(copyx1-1-startline)*g_lineheight,g_word_width*(copyy2-copyy1),g_lineheight);
                    qLabel[copyx1]->show();
                }
                else
                {
                    qLabel[copyx1]->setGeometry(g_linestartspace+(copyy2-startrow)*g_word_width,g_rowstartspace+(copyx1-startline-1)*g_lineheight,g_word_width*(copyy1-copyy2),g_lineheight);
                    qLabel[copyx1]->show();
                }
            }

            shadow=1;
        }
    }

}

void viewlist::mouseReleaseEvent(QMouseEvent *event)
{
    int i,j,x,y;
    x=event->pos().x()-event->pos().x()%g_word_width-2;
    y=(event->pos().y()-g_rowstartspace)-(event->pos().y()-g_rowstartspace)%g_lineheight+g_rowstartspace;
    if(t->judgeposition(t->file,(y-g_rowstartspace)/g_lineheight+1+startline,(x+2-g_linestartspace)/g_word_width+startrow)&&judgebetweenchineseword((y-g_rowstartspace)/g_lineheight+1+startline,(x+2-g_linestartspace)/g_word_width+startrow))
    {
        curse_x=x;
        curse_y=y;
        i=(curse_y-g_rowstartspace)/g_lineheight+1+startline;
        j=(curse_x+2-g_linestartspace)/g_word_width+startrow;
        copyx2=i;
        copyy2=j;
        if(i!=line||j!=row){
        }
    }
}

void viewlist::wheelEvent(QWheelEvent *event)
{
    if(event->delta()>0)
        background->vertical->setValue(background->vertical->value()-1);
    else
        background->vertical->setValue(background->vertical->value()+1);
}

void viewlist::cursestar()
{
    if(curse_sum%2==0)
        curse->setVisible(false);
    else
        curse->setVisible(true);
    curse_sum++;
}

void viewlist::keyPressEvent(QKeyEvent *event)
{
    int i;
    question=1;
    if(event->key()==Qt::Key_Right)
    {
        if(t->filesearchlinelength(t->file,line)>row){
            if((curse_x+2-g_linestartspace)/g_word_width<=(this->width()-g_linestartspace*2)/g_word_width)
            {
                if(chineseword[line][row+1]==false){
                    row++;
                    curse_x+=g_word_width;
                }
                else {
                    row+=2;
                    curse_x+=2*g_word_width;
                }
                curse->setGeometry(curse_x,curse_y,g_curse_width,g_lineheight);
            }
            else
            {
                if(chineseword[line][row+1]==false){
                    row++;
                    startrow++;
                    background->horizental->setValue(background->horizental->value()+1);
                }
                else {
                    row+=2;
                    startrow+=2;
                    background->horizental->setValue(background->horizental->value()+2);
                }
            }
        }
    }
    else if(event->key()==Qt::Key_Left)
    {
        if(row>0&&(row-startrow)>0){
            if(chineseword[line][row]==false)
            {
                row--;
                curse_x-=g_word_width;
            }
            else if(chineseword[line][row]==true){
                row-=2;
                curse_x-=2*g_word_width;
            }
            curse->setGeometry(curse_x,curse_y,g_curse_width,g_lineheight);
        }
        else if(row>0&&startrow>0&&(row-startrow)==0)
        {
            if(chineseword[line][row]==false)
            {
                row--;
                startrow--;
                background->horizental->setValue(background->horizental->value()-1);
            }
            else if(chineseword[line][row]==true){
                row-=2;
                startrow-=2;
                background->horizental->setValue(background->horizental->value()-2);
            }
        }
    }
    else if(event->key()==Qt::Key_Down){
        if(line<t->file->linenum&&row<=t->filesearchlinelength(t->file,line+1))
        {
            if(chineseword[line+1][row]==false||(chineseword[line+1][row]==true&&judgebetweenchineseword(line+1,row))){
                if(curse_y/g_lineheight>=g_rowstartspace+((this->height()-2*g_rowstartspace)/g_lineheight-1))
                {
                    background->vertical->setValue(background->vertical->value()+1);
                }
                else
                {
                    curse_y+=g_lineheight;
                }
            }
            else if(chineseword[line+1][row]==true&&judgebetweenchineseword(line+1,row)==0){
                if(curse_y>g_rowstartspace+((this->height()-2*g_rowstartspace)/g_lineheight-1)*g_lineheight)
                    background->vertical->setValue(background->vertical->value()+1);
                else curse_y+=g_lineheight;
                curse_x-=g_word_width;
                row--;
            }
            line++;
            curse->setGeometry(curse_x,curse_y,g_curse_width,g_lineheight);
        }
        else if(line<t->file->linenum&&row>t->filesearchlinelength(t->file,line+1))
        {
            line++;
            row=t->filesearchlinelength(t->file,line);
            if(line<t->file->linenum&&curse_y>=g_rowstartspace+((this->height())/g_lineheight)*g_lineheight)
            {
                background->vertical->setValue(background->vertical->value()+1);
                if(startrow>row)
                    background->horizental->setValue(row);
            }
            else{
                if(startrow>row)
                    background->horizental->setValue(row);
                else
                {
                    curse_x=g_linestartspace+(row-startrow)*g_word_width-2;
                    curse_y=g_rowstartspace+(line-1-startline)*g_lineheight;
                    curse->setGeometry(curse_x,curse_y,g_curse_width,g_lineheight);
                }
            }
        }
    }
    else if(event->key()==Qt::Key_Up)
    {
        if(curse_y>g_rowstartspace&&row<=t->filesearchlinelength(t->file,line-1)){
            if(chineseword[line-1][row]==false||(chineseword[line-1][row]==true&&judgebetweenchineseword(line-1,row)))
                curse_y-=g_lineheight;
            else if(chineseword[line-1][row]==true&&judgebetweenchineseword(line-1,row)==0){
                curse_y-=g_lineheight;
                curse_x-=g_word_width;
                row--;
            }
            curse->setGeometry(curse_x,curse_y,g_curse_width,g_lineheight);
            line--;
        }
        else if(curse_y>g_rowstartspace&&row>t->filesearchlinelength(t->file,line-1)){

            line--;
            row=t->filesearchlinelength(t->file,line);
            if(startrow>row)
            {
                startrow=row;
                background->horizental->setValue(row);
            }
            else
            {
                curse_y-=g_lineheight;
                curse_x=g_linestartspace-2+(row-startrow)*g_word_width;
                curse->setGeometry(curse_x,curse_y,g_curse_width,g_lineheight);
            }
        }
        else if(startline>0&&curse_y==g_rowstartspace)
        {
            line--;
            background->vertical->setValue(background->vertical->value()-1);
        }
    }
    else if(event->key()==Qt::Key_Backspace)
    {
        str.clear();
        if(copyx1!=copyx2||copyy1!=copyy2)    //块删除操作
        {
            if( copyx1<copyx2||((copyx1==copyx2)&&copyy1<=copyy2))
            {
                t->undo[t->posforundo].kuai=t->filechunkcopy(t->file,copyx1,copyy1+1,copyx2,copyy2);
                t->filechunkdelete(t->file,copyx1,copyy1+1,copyx2,copyy2);
                curse_x=(copyy1-startrow)*g_word_width-g_linestartspace-2;
                curse_y=(copyx1-startline-1)*g_lineheight-g_rowstartspace;
                curse->setGeometry(curse_x,curse_y,g_curse_width,g_lineheight);


                t->undo[t->posforundo].type=4;
                t->undo[t->posforundo].newhang1=t->undo[t->posforundo].oldhang1=copyx1;
                t->undo[t->posforundo].oldlie1=copyy1+1;
                t->undo[t->posforundo].oldhang2=copyx2;
                t->undo[t->posforundo].oldlie2=copyy2;
                t->undo[t->posforundo].newlie1=copyy1;
                t->posforundo++;
                for(int i=t->posforundo;i<=99;i++)
                    t->undo[i]=t->initforundo();


                line=copyx1;
                row=copyy1;
                copyx2=copyx1;
                copyy2=copyy1;

            }
            else {
                //反向选块时候改变markcopy坐标
                if(copyx2<=0)
                    copyx2=1;
                if(copyy2<=0)
                    copyy2=0;

                t->undo[t->posforundo].kuai=t->filechunkcopy(t->file,copyx2,copyy2+1,copyx1,copyy1);
                t->filechunkdelete(t->file,copyx2,copyy2+1,copyx1,copyy1);
                curse_x=(copyy2-startrow)*g_word_width-g_linestartspace-2;
                curse_y=(copyx2-startline-1)*g_lineheight-g_rowstartspace;
                curse->setGeometry(curse_x,curse_y,g_curse_width,g_lineheight);

                t->undo[t->posforundo].type=4;
                t->undo[t->posforundo].newhang1=t->undo[t->posforundo].oldhang1=copyx2;
                t->undo[t->posforundo].oldlie1=copyy2+1;
                t->undo[t->posforundo].oldhang2=copyx1;
                t->undo[t->posforundo].oldlie2=copyy1;
                t->undo[t->posforundo].newlie1=copyy2;
                t->posforundo++;
                for(int i=t->posforundo;i<=99;i++)
                    t->undo[i]=t->initforundo();

                line=copyx2;
                row=copyy2;
                copyx1=copyx2;
                copyy1=copyy2;

            }
            string temp;
            background->text->t->filestringprint(background->text->t->file);
            for(int linecount=0;linecount<background->text->t->file->linenum;linecount++){
                temp=background->text->t->forprint[linecount];
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
                        chineseword[linecount+1][i+1]=0;
                    }
                }
            }
            for(i=1;i<100;i++)
                pLabel[i]->clear();
            for(i=1;i<=t->file->linenum;i++)
            {
                getqstring(qstr,t->forprint[i-1]);
                pLabel[i]->setText(qstr);
                pLabel[i]->setFont(ft);
                pLabel[i]->setGeometry(g_linestartspace,g_rowstartspace+(i-1-startline)*g_lineheight,g_linetotalwidth,g_lineheight);
            }
            changescrolllength();
            if(t->file->linenum<background->vertical->maximum()+(this->height()-g_rowstartspace)/g_lineheight+1 && background->vertical->maximum()>0)
            {
                if(background->vertical->value()==background->vertical->maximum())
                {
                    if(t->file->linenum<=this->height()/g_lineheight)
                    {
                        background->vertical->setMaximum(0);
                        background->vertical->setValue(0);
                    }
                    else
                    {
                        background->vertical->setMaximum(t->file->linenum-this->height()/g_lineheight-1);
                        background->vertical->setValue(background->vertical->maximum());
                    }
                }
                else
                {
                    if(t->file->linenum<=this->height()/g_lineheight)
                    {
                        background->vertical->setMaximum(0);
                        background->vertical->setValue(0);
                    }
                    else
                    {
                        background->vertical->setMaximum(t->file->linenum-this->height()/g_lineheight-1);
                        background->vertical->setValue(background->vertical->maximum());
                    }
                }
            }
            for(i=1;i<100;i++)
                qLabel[i]->setVisible(false);
        }
        else if(row>0){
            if(curse_x==-2){

                t->fileinlinebackspaceindex(t->file,line,row);
                t->undo[t->posforundo].type=3;
                t->undo[t->posforundo].oldhang1=t->undo[t->posforundo].newhang1=line;
                t->undo[t->posforundo].oldlie1=t->undo[t->posforundo].newlie1=row;
                t-> undo[t->posforundo].newch=str[row-1];
                t->posforundo++;
                for(int i=t->posforundo;i<=99;i++)
                    t->undo[i]=t->initforundo();

                row--;
                t->changestring(t->file,str,line);
                getqstring(qstr,str);
                pLabel[line]->setText(qstr);
                changechineseword(row,0);
                background->horizental->setValue(background->horizental->value()-1);

            }
            else {
                if(chineseword[line][row]==false)
                {
                    t->fileinlinebackspaceindex(t->file,line,row);
                    t->undo[t->posforundo].type=3;
                    t->undo[t->posforundo].oldhang1=t->undo[t->posforundo].newhang1=line;
                    t->undo[t->posforundo].oldlie1=t->undo[t->posforundo].newlie1=row;
                    t-> undo[t->posforundo].oldch=t-> undo[t->posforundo].newch=str[row-1];
                    t->posforundo++;
                    for(int i=t->posforundo;i<=99;i++)
                        t->undo[i]=t->initforundo();
                    //
                    row--;
                    changechineseword(row,0);
                    curse_x-=g_word_width;
                    curse->setGeometry(curse_x,curse_y,g_curse_width,g_lineheight);
                }
                else if(chineseword[line][row]==true){
                    t->undo[t->posforundo].kuai=t->filechunkcopy(t->file,line,row-1,line,row);
                    for(i=row;i>row-2;i--)
                    {
                        t->fileinlinebackspaceindex(t->file,line,i);
                        chineseword[line][i]=false;
                    }
                    t->undo[t->posforundo].type=4;
                    t->undo[t->posforundo].newhang1=t->undo[t->posforundo].oldhang1=line;
                    t->undo[t->posforundo].oldlie1=row-1;
                    t->undo[t->posforundo].oldhang2=line;
                    t->undo[t->posforundo].oldlie2=row;
                    t->undo[t->posforundo].newlie1=row-2;
                    t->posforundo++;
                    for(int i=t->posforundo;i<=99;i++)
                        t->undo[i]=t->initforundo();
                    row-=2;
                    curse_x-=g_word_width*2;
                    curse->setGeometry(curse_x,curse_y,g_curse_width,g_lineheight);
                }
                str.clear();
                qstr.clear();
                t->changestring(t->file,str,line);
                getqstring(qstr,str);
                pLabel[line]->setText(qstr);
                changescrolllength();
            }
        }
        else if(line>1)
        {
            int i,j,m;
            //行列值修改
            m=t->filesearchlinelength(t->file,line-1);
            i=line;
            j=row;
            line--;
            row=t->filesearchlinelength(t->file,line);
            background->changelineandrow(line,row);
            curse_x=g_linestartspace-2+g_word_width*row;
            curse_y-=g_lineheight;
            curse->setGeometry(curse_x,curse_y,g_curse_width,g_lineheight);
            t->fileinlinebackspaceindex(t->file,i,j);
            changechineseword(m,2);
            for(i=1;i<100;i++)
                pLabel[i]->clear();
            t->filestringprint(t->file);
            for(i=1;i<=t->file->linenum;i++)
            {
                getqstring(qstr,t->forprint[i-1]);
                pLabel[i]->setText(qstr);
                pLabel[i]->setFont(ft);
            }
            changescrolllength();
            background->horizental->setValue(background->horizental->maximum());
            if(t->file->linenum<background->vertical->maximum()+(this->height()-g_rowstartspace)/g_lineheight+1 && background->vertical->maximum()>0)
            {
                if(background->vertical->value()==background->vertical->maximum())
                {
                    background->vertical->setMaximum(t->file->linenum-((this->height()-g_rowstartspace)/g_lineheight+1));
                    background->vertical->setValue(background->vertical->maximum());
                }
                else
                {
                    background->vertical->setValue(background->vertical->value()-(background->vertical->maximum()-t->file->linenum+(this->height()-g_rowstartspace)/g_lineheight+1));
                    background->vertical->setMaximum(t->file->linenum-(this->height()-g_rowstartspace)/g_lineheight+1);
                }
            }
        }
    }
    else if(event->key()==Qt::Key_Delete)
    {
        string str;
        QString qstr;
        if(row<t->filesearchlinelength(t->file,line))
        {
            t->fileinlinebackspaceindex(t->file,line,row+1);
            t->changestring(t->file,str,line);
            getqstring(qstr,str);
            pLabel[line]->setText(qstr);
            pLabel[line]->setGeometry(g_linestartspace-(startrow)*g_word_width,g_rowstartspace+(line-1-startline)*g_lineheight,g_linetotalwidth,g_lineheight);
        }
        changescrolllength();
    }
    else if(event->key()==Qt::Key_CapsLock)
    {
        if(capslock_num%2==0)
            capslock=0;
        else capslock=1;
        capslock_num++;
    }
    else if(event->key()==Qt::Key_Return||event->key()==Qt::Key_Enter)
    {
        int i;
        changechineseword(row+1,3);
        if(line==1&&row==0)
        {
            t->zeroenter(t->file);
            t->undo[t->posforundo].type=6;
            t->undo[t->posforundo].newhang1=2;
            t->undo[t->posforundo].newlie1=0;
            t->posforundo++;
            for(int i=t->posforundo;i<=99;i++)
                t->undo[i]=t->initforundo();
        }
        else if(row==t->filesearchlinelength(t->file,line))
        {
            t->fileatlinelastenter(t->file,line);
            t->undo[t->posforundo].type=7;
            t->undo[t->posforundo].newhang1=line+1;
            t->undo[t->posforundo].newlie1=0;
            t->undo[t->posforundo].oldhang1=line;
            t->posforundo++;
            for(int i=t->posforundo;i<=99;i++)
                t->undo[i]=t->initforundo();
        }
        else
        {
            t->fileatlineindexenter(t->file,line,row+1);
            t->undo[t->posforundo].type=8;
            t->undo[t->posforundo].newhang1=line+1;
            t->undo[t->posforundo].newlie1=0;
            t->undo[t->posforundo].oldhang1=line;
            t->undo[t->posforundo].oldlie1=row+1;
            t->posforundo++;
            for(int i=t->posforundo;i<=99;i++)
                t->undo[i]=t->initforundo();
        }
        //处理行列和光标
        line++;
        row=0;
        //处理内容
        t->filestringprint(t->file);
        for(i=1;i<=t->file->linenum;i++)
        {
            getqstring(qstr,t->forprint[i-1]);
            pLabel[i]->setText(qstr);
            pLabel[i]->setFont(ft);
            pLabel[i]->setGeometry(g_linestartspace,g_rowstartspace+(i-1)*g_lineheight,g_linetotalwidth,g_lineheight);
        }
        if(t->file->linenum>(this->height())/g_lineheight){
            startline=line-(this->height()-2*g_rowstartspace)/g_lineheight;
            curse_x=-2;
            //滚轮变长操作
            int ver_max=background->vertical->maximum();
            if(t->file->linenum>ver_max+this->height()/g_lineheight)
            {
                background->vertical->setMaximum(ver_max+1);
                background->vertical->setValue(background->vertical->value()+1);
            }
            else
            {
                background->horizental->setValue(background->horizental->value()+1);
            }
            for(i=1;i<=t->file->linenum;i++)
            {
                pLabel[i]->setGeometry(g_linestartspace,g_rowstartspace+(i-1-startline)*g_lineheight,g_linetotalwidth,g_lineheight);
            }
            curse->setGeometry(curse_x,curse_y,g_curse_width,g_lineheight);
            curse->show();
        }
        else
        {
            //background->horizental->setValue(0);
            curse_x=g_linestartspace-2;
            curse_y=g_rowstartspace+(line-1)*g_lineheight;
            curse->setGeometry(curse_x,curse_y,g_curse_width,g_lineheight);
        }
        //startrow=0;   //屏幕回到起始位置
        //changescrolllength();
        background->horizental->setValue(0);
        changescrolllength();
    }
    else if(event->key()==Qt::Key_Home)
    {
        row=0;
        curse_x=-2;
        curse_y=g_rowstartspace+(line-1)*g_lineheight;
        curse->setGeometry(curse_x,curse_y,g_curse_width,g_lineheight);
        background->horizental->setValue(0);
        background->changelineandrow(line,row);
    }
    else if(event->key()==Qt::Key_PageUp)
    {
        if(line>this->height()/g_lineheight)
            background->vertical->setValue(background->vertical->value()-(this->height()/g_lineheight+1));
    }
    else if(event->key()==Qt::Key_PageDown)
    {
        if(line+this->height()/g_lineheight+1<=t->file->linenum)
            background->vertical->setValue(background->vertical->value()+(this->height()/g_lineheight+1));
    }
    else if (65 <= event->key() && 91 >= event->key()||(event->key()>=48&&event->key()<=57)||event->key()==32)//所有字母
    {
        row++;
        i=event->key();
        if(capslock==0&&65 <= event->key() && 91 >= event->key())
            i+=32;
        t->fileinlineinsertatindex(t->file,line,row,i);

        t->undo[t->posforundo].type=1;
        t->undo[t->posforundo].oldhang1=t->undo[t->posforundo].newhang1=line;
        t->undo[t->posforundo].oldlie1=t->undo[t->posforundo].newlie1=row;
        t-> undo[t->posforundo].oldch=(char)i;
        t->posforundo++;
        for(int i=t->posforundo;i<=99;i++)
            t->undo[i]=t->initforundo();

        changechineseword(row,1);
        str.clear();
        if(t->filesearchlinelength(t->file,line)<=(this->width()-g_linestartspace*2)/g_word_width+background->horizental->value())
        {
            t->changestring(t->file,str,line);
            getqstring(qstr,str);
            pLabel[line]->setText(qstr);
            pLabel[line]->setFont(ft);
            background->changelineandrow(line,row);
            curse_x+=g_word_width;
            curse->setGeometry(curse_x,curse_y,g_curse_width,g_lineheight);
        }

        else if(t->filesearchlinelength(t->file,line)>(this->width()-g_linestartspace*2)/g_word_width+background->horizental->value())
        {
            startrow++; //记录屏幕起始位置
            if(t->filesearchlinelength(t->file,line)>background->horizental->maximum()+(this->width()-g_linestartspace)/g_word_width)
            {
                background->horizental->setMaximum(background->horizental->maximum()+1);
                background->horizental->setValue(background->horizental->value()+1);
            }
            else
            {
                background->horizental->setValue(background->horizental->value()+1);
            }
            for(i=1;i<=t->file->linenum;i++)
            {
                str.clear();
                qstr.clear();
                t->changestring(t->file,str,i);
                getqstring(qstr,str);
                pLabel[i]->setText(qstr);
                pLabel[i]->setGeometry(g_linestartspace-(startrow)*g_word_width,g_rowstartspace+(i-1-startline)*g_lineheight,g_linetotalwidth,g_lineheight);
            }
        }
    }
    background->changelineandrow(line,row);
}

int viewlist::judgebetweenchineseword(int b,int a)  //判断此时光标是否落在汉字之间
{
    int i,j;
    if(chineseword[b][a]==false)
        return 1;
    else
    {
        for(i=a;i>=0;i--)
        {
            if(chineseword[b][i]==false)
                break;
        }
        if((a-i)%2) return 0;
        else return 1;
    }
}

void viewlist::changechineseword(int a,int b)   //根据不同操作改变汉字数组的标志
{
    int i,j;
    if(b==0)           //第一种修改汉语方式  在一行中删除汉字
        for(i=a;i<=t->filesearchlinelength(t->file,line);i++)
        {
            if(chineseword[line][i]==true)
            {
                chineseword[line][i+1]=false;
                chineseword[line][i-1]=true;
                i++;
            }
        }
    else if(b==1)    //第二种修改汉语   在一行中插入字符
    {
        for(i=t->filesearchlinelength(t->file,line)+1;i>a;i--)
        {
            if(chineseword[line][i]==true)
            {
                chineseword[line][i+1]=true;
                chineseword[line][i-1]=false;
                i--;
            }
        }
    }
    else if(b==2)   //第三种修改汉语方式 删除掉一行
    {
        for(i=a+1;i<=t->filesearchlinelength(t->file,line);i++)
        {
            chineseword[line][i]=chineseword[line+1][i-a];

        }
        for(i=line+1;i<=t->file->linenum;i++)
            for(j=1;j<=t->filesearchlinelength(t->file,i);j++)
                chineseword[i][j]=chineseword[i+1][j];
    }
    else if(b==3)         //第四种修改汉语  按下回车之后改变
    {
        for(i=t->file->linenum;i>=line+1;i--)
        {
            for(j=1;j<=t->filesearchlinelength(t->file,i);j++)
                chineseword[i+1][j]=chineseword[i][j];
        }

        for(i=a;i<=t->filesearchlinelength(t->file,line);i++)
        {
            chineseword[line+1][i-a+1]=chineseword[line][i];
            chineseword[line][i]=false;
        }
    }
}

void viewlist::inputMethodEvent(QInputMethodEvent * a)
{
    int i;
    string s =ToString(a->commitString());
    if(a->commitString()=="")
    {}
    else
    {
        if(a->commitString().length()!=s.length())
        {
            t->fileinlineinsertstring(t->file,line,row+1,s);
            changechineseword(row,2);
            for(i=row+1;i<=row+s.length();i++)
                chineseword[line][i]=true;
        }
        else if(s.length()==a->commitString().length())
        {
            t->fileinlineinsertstring(t->file,line,row+1,s);
            changechineseword(row,2);
            for(i=row+1;i<=row+s.length();i++)
                chineseword[line][i]=false;
        }
        t->undo[t->posforundo].type=2;
        t->undo[t->posforundo].oldhang1=t->undo[t->posforundo].newhang1=line;
        t->undo[t->posforundo].oldlie1=row+1;
        t->undo[t->posforundo].newlie1=row+1;
        t->undo[t->posforundo].newlie2=row+s.length();
        t-> undo[t->posforundo].oldstr=s;
        t->posforundo++;
        for(int i=t->posforundo;i<=99;i++)
            t->undo[i]=t->initforundo();

        row+=s.length();
        str.clear();
        t->changestring(t->file,str,line);
        getqstring(qstr,str);
        pLabel[line]->setText(qstr);
        pLabel[line]->setFont(ft);
        background->changelineandrow(line,row);
        if(t->filesearchlinelength(t->file,line)<(this->width())/g_word_width)
        {
            curse_x+=g_word_width*s.length();
            curse->setGeometry(curse_x,curse_y,g_curse_width,g_lineheight);
            background->horizental->setValue(background->horizental->value()+2);
        }
        else
            if(t->filesearchlinelength(t->file,line)>=(this->width())/g_word_width){
                {
                    background->horizental->setMaximum(t->filesearchlinelength(t->file,line)-(this->width())/g_word_width);
                    //background->horizental->setMaximum(background->horizental->maximum()+2);
                    background->horizental->setValue(background->horizental->maximum());
                }

            }
    }
}

void viewlist::getqstring(QString&qstr,string&str)
{
    QTextCodec* pCodec = QTextCodec::codecForName("gb2312");
    qstr = pCodec->toUnicode(str.c_str(), str.length());
}

string viewlist::ToString(const QString& qstr)
{
    QTextCodec* pCodec = QTextCodec::codecForName("gb2312");
    if(!pCodec) return "";
    QByteArray arr = pCodec->fromUnicode(qstr);
    string cstr = arr.data();
    return cstr;
}

int viewlist::Index_Kmp(string str1, string str2, int pos,int next[])
{
    pos++;
    int k=0;
    int i=pos;
    int j=1;
    while(i<=str1.length()-1&&j<=str2.length()-1)
    {
        if(j==0||str1[i]==str2[j])
        {
            i++;
            j++;
        }
        else j=next[j];
    }
    if(j>str2[0])
        return i-str2.length();
    else return -1;
}

void viewlist::get_next(string str, int next[])
{
    int i=1;
    int j=0;
    next[1]=0;
    while(i<str.length())
    {
        if(j==0||str[i]==str[j])
        {
            i++;
            j++;
            next[i]=j;
        }
        else j=next[j];
    }
}

void viewlist::changescrolllength()
{
    int maxline=0;
    for(int i=1;i<=t->file->linenum;i++)
    {
        int temp=t->filesearchlinelength(t->file,i);
        if(temp>maxline)maxline=temp;
    }
    if(maxline-this->width()/g_word_width>0)
        background->horizental->setMaximum(maxline-this->width()/g_word_width);
    else background->horizental->setMaximum(0);

}

void viewlist::resizeEvent(QResizeEvent *event)
{

    int w=event->size().width(),h=event->size().height();//获取窗口大小
    //水平滚轮变换
    int maxline=0;
    for(int i=1;i<=t->file->linenum;i++)
    {
        int temp=t->filesearchlinelength(t->file,i);
        if(temp>maxline)maxline=temp;
    }
    if(maxline<=(w-g_linestartspace)/g_word_width)
    {
        this->background->horizental->setValue(0);
        this->background->horizental->setMaximum(0);
    }
    else if(maxline<this->background->horizental->maximum()+(w-g_linestartspace)/g_word_width)
    {
        if(this->background->horizental->value()>=this->background->horizental->maximum())this->background->horizental->setValue(maxline-(this->width()-g_linestartspace)/g_word_width);
        if(maxline-(w-g_linestartspace)/g_word_width>0)this->background->horizental->setMaximum(maxline-(w-g_linestartspace)/g_word_width);
    }
    else if(maxline>this->background->horizental->maximum()+(w-g_linestartspace)/g_word_width)
    {
        if(maxline-(w-g_linestartspace)/g_word_width>0)this->background->horizental->setMaximum(maxline-(this->width()-g_linestartspace)/g_word_width);
    }
    //竖直滚轮变化
    if(t->file->linenum<=(h-g_rowstartspace)/g_lineheight+1 && background->vertical->maximum()>0)
    {
        this->background->vertical->setValue(0);
        this->background->vertical->setMaximum(0);
    }
    else if(t->file->linenum<this->background->vertical->maximum()+(h-g_rowstartspace)/g_lineheight+1)
    {
        if(this->background->vertical->value()>t->file->linenum-(h-g_rowstartspace)/g_lineheight+1)this->background->vertical->setValue(t->file->linenum-(h-g_rowstartspace)/g_lineheight+1);
        if(t->file->linenum-(h-g_rowstartspace)/g_lineheight+1>0)this->background->vertical->setMaximum(t->file->linenum-(h-g_rowstartspace)/g_lineheight+1);
    }
    else if(t->file->linenum>this->background->vertical->maximum()+(h-g_rowstartspace)/g_lineheight+1)
    {
        if(t->file->linenum-(h-g_rowstartspace)/g_lineheight+1>0)this->background->vertical->setMaximum(t->file->linenum-(h-g_rowstartspace)/g_lineheight+1);
    }

}
