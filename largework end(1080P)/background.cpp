#include"background.h"
#include<header.h>
#include<QHBoxLayout>

BackGround::BackGround(QWidget *parent):
    QWidget(parent)
{
    text=new viewlist(this);
    this->setWindowModality(Qt::WindowModal);
    imagelabel=new QLabel;
    imagelabel->setScaledContents(true);
    //滚轮
    horizental=new QScrollBar(this);
    horizental->setOrientation(Qt::Horizontal);
    horizental->setValue(0);
    horizental->setMaximum(0);
    horizental->setMinimum(0);
    horizental->setFocusPolicy(Qt::StrongFocus);
    vertical=new QScrollBar(this);
    vertical->setMaximum(0);
    vertical->setValue(0);
    vertical->setMinimum(0);
    vertical->setFocusPolicy(Qt::StrongFocus);
    connect(vertical,SIGNAL(valueChanged(int)),this,SLOT(scrollmove2()));
    connect(horizental,SIGNAL(valueChanged(int)),this,SLOT(scrollmove1()));
    horizentalmaxvalue=0;
    horizentalminvalue=0;
    verticalmaxvalue=0;
    verticalminvalue=0;
    horizentalvalue=0;
    verticalvalue=0;
    //行列
    linelabel=new QLabel(this);
    rowlabel=new QLabel(this);
    linesum=new QLabel(this);
    rowsum=new QLabel(this);
    linelabel->setText("行数:");
    linelabel->setFixedHeight(15);
    rowlabel->setText("列数:");
    //     rowlabel->setFixedSize(30,15);
    itoa(text->line,c,10);
    str=c;
    qstr = QString::fromStdString(str);
    linesum->setText(qstr);
    itoa(text->row,c,10);
    str=c;
    qstr = QString::fromStdString(str);
    rowsum->setText(qstr);
    flag=0;
    mainLayout = new QGridLayout(this);
    mainLayout->setContentsMargins(10,10,10,0);
    mainLayout->addWidget(text,0,0,8,4);
    mainLayout->addWidget(vertical,0,4,8,1);
    mainLayout->addWidget(horizental,8,0,1,4);
    mainLayout->setVerticalSpacing(2);
    mainLayout->addWidget(linelabel,9,0);
    mainLayout->addWidget(linesum,9,1);
    mainLayout->addWidget(rowlabel,9,2);
    mainLayout->addWidget(rowsum,9,3);
    text->setFocusPolicy(Qt::ClickFocus);
    //setWindowOpacity(0.9);//透明度
}
int BackGround::scrollmove1() //水平
{
    QScrollBar *it = qobject_cast<QScrollBar*>(sender());
    int i;
    int num;
    //horizentalvalue=horizental->value();
    text->startrow=horizental->value();
    int div=horizental->value();
    //选定阴影改变
    cout<<this->text->shadow<<endl;
    if(this->text->shadow)
    {
        int copyx1=this->text->copyx1,copyx2=this->text->copyx2,copyy1=this->text->copyy1,copyy2=this->text->copyy2;
        if(this->text->copyx1!=this->text->copyx2)
        {
            int m=this->text->copyx1;
            int n=this->text->copyx2;
            if(copyx1<copyx2)
            {
                for(i=m;i<=n;i++)
                {
                    if(i>m&&i<n)
                    {
                        this->text->qLabel[i]->setGeometry(g_linestartspace-div*g_word_width,g_rowstartspace+(i-1-this->text->startline)*g_lineheight,g_word_width*(this->text->t->filesearchlinelength(this->text->t->file,i)),g_lineheight);
                        this->text->qLabel[i]->show();
                    }
                    else if(i==m)
                    {
                        this->text->qLabel[i]->setGeometry(g_linestartspace+(this->text->copyy1-div)*g_word_width,g_rowstartspace+(i-1-this->text->startline)*g_lineheight,g_word_width*(this->text->t->filesearchlinelength(this->text->t->file,i)-this->text->copyy1),g_lineheight);
                        this->text->qLabel[i]->show();
                    }
                    else if(i==n)
                    {
                        //                    cout<<"horizen:"<<(g_linestartspace-div*g_word_width)/10<<","<<copyy2<<","<<i-this->text->startline<<endl;
                        this->text->qLabel[i]->setGeometry(g_linestartspace-div*g_word_width,g_rowstartspace+(i-1-this->text->startline)*g_lineheight,g_word_width*copyy2,g_lineheight);
                        this->text->qLabel[i]->show();
                    }
                }
            }
            else if(copyx1>copyx2)
            {
                if(i>0)
                {
                    this->text->qLabel[i]->setStyleSheet("background-color:yellow");
                    this->text->pLabel[i]->setStyleSheet("background:transparent");
                }
                for(i=m;i>=n;i--)
                {
                    if(i<m&&i>n)
                    {
                        this->text->qLabel[i]->setGeometry(g_linestartspace-div*g_word_width,g_rowstartspace+(i-1-this->text->startline)*g_lineheight,g_word_width*(this->text->t->filesearchlinelength(this->text->t->file,i)),g_lineheight);
                        this->text->qLabel[i]->show();
                    }
                    else if(i==m)
                    {
                        this->text->qLabel[i]->setGeometry(g_linestartspace-div*g_word_width,g_rowstartspace+(i-1-this->text->startline)*g_lineheight,g_word_width*(copyy1),g_lineheight);
                        this->text->qLabel[i]->show();
                    }
                    else if(i==n)
                    {
                        this->text->qLabel[i]->setGeometry(g_linestartspace+(this->text->copyy2-this->text->startrow)*g_word_width,g_rowstartspace+(i-1-this->text->startline)*g_lineheight,g_word_width*(this->text->t->filesearchlinelength(this->text->t->file,i)-this->text->copyy2),g_lineheight);
                        this->text->qLabel[i]->show();
                    }
                }
            }
        }
        else if(copyx1==copyx2)
        {
            cout<<1<<endl;
            this->text->qLabel[copyx1]->setStyleSheet("background-color:yellow");
            this->text->pLabel[copyx1]->setStyleSheet("background-color:transparent");
            if(copyy2-copyy1>0)
            {
                this->text->qLabel[copyx1]->setGeometry(g_linestartspace+(copyy1-this->text->startrow)*g_word_width,g_rowstartspace+(copyx1-1-this->text->startline)*g_lineheight,g_word_width*(copyy2-copyy1),g_lineheight);
                this->text->qLabel[copyx1]->show();
            }
            else
            {
                this->text->qLabel[copyx1]->setGeometry(g_linestartspace+(copyy2-this->text->startrow)*g_word_width,g_rowstartspace+(copyx1-this->text->startline-1)*g_lineheight,g_word_width*(copyy1-copyy2),g_lineheight);
                this->text->qLabel[copyx1]->show();
            }
        }

    }
    for(i=1;i<=text->t->file->linenum;i++)
    {
        text->pLabel[i]->setGeometry(g_linestartspace-(text->startrow)*g_word_width,g_rowstartspace+(i-1-text->startline)*g_lineheight,g_linetotalwidth,g_lineheight);
    }
    text->curse_x=g_linestartspace+(text->row-text->startrow)*g_word_width-2;
    text->curse_y=g_rowstartspace+(text->line-text->startline)*g_lineheight;
    text->curse->setGeometry(text->curse_x,text->curse_y,g_curse_width,g_lineheight);
    return it->value();
}

int BackGround::scrollmove2() //垂直
{
    QScrollBar *it = qobject_cast<QScrollBar*>(sender());
    int i;
    int num;
    text->startline=vertical->value();
    int div=vertical->value();
    for(i=1;i<=text->t->file->linenum;i++)
    {
        text->pLabel[i]->setGeometry(g_linestartspace-(text->startrow)*g_word_width,g_rowstartspace+(i-1-text->startline)*g_lineheight,g_linetotalwidth,g_lineheight);
    }
    //选定阴影改变
    if(this->text->shadow)
    {
        int copyx1=this->text->copyx1,copyx2=this->text->copyx2,copyy1=this->text->copyy1,copyy2=this->text->copyy2;
        if(this->text->copyx1!=this->text->copyx2)
        {
            int m=this->text->copyx1;
            int n=this->text->copyx2;
            if(copyx1<copyx2)
            {
                for(i=m;i<=n;i++)
                {
                    if(i>m&&i<n)
                    {
                        this->text->qLabel[i]->setGeometry(g_linestartspace,g_rowstartspace+(i-1-this->text->startline)*g_lineheight,g_word_width*(this->text->t->filesearchlinelength(this->text->t->file,i)),g_lineheight);
                        this->text->qLabel[i]->show();
                    }
                    else if(i==m)
                    {
                        this->text->qLabel[i]->setGeometry(g_linestartspace+(this->text->copyy1)*g_word_width,g_rowstartspace+(i-1-this->text->startline)*g_lineheight,g_word_width*(this->text->t->filesearchlinelength(this->text->t->file,i)-this->text->copyy1),g_lineheight);
                        this->text->qLabel[i]->show();
                    }
                    else if(i==n)
                    {
                        this->text->qLabel[i]->setGeometry(g_linestartspace,g_rowstartspace+(i-1-this->text->startline)*g_lineheight,g_word_width*copyy2,g_lineheight);
                        this->text->qLabel[i]->show();
                    }
                }
            }
            else if(copyx1>copyx2)
            {
                if(i>0)
                {
                    this->text->qLabel[i]->setStyleSheet("background-color:yellow");
                    this->text->pLabel[i]->setStyleSheet("background:transparent");
                }
                for(i=m;i>=n;i--)
                {
                    if(i<m&&i>n)
                    {
                        this->text->qLabel[i]->setGeometry(g_linestartspace,g_rowstartspace+(i-1-this->text->startline)*g_lineheight,g_word_width*(this->text->t->filesearchlinelength(this->text->t->file,i)),g_lineheight);
                        this->text->qLabel[i]->show();
                    }
                    else if(i==m)
                    {
                        this->text->qLabel[i]->setGeometry(g_linestartspace,g_rowstartspace+(i-1-this->text->startline)*g_lineheight,g_word_width*(copyy1),g_lineheight);
                        this->text->qLabel[i]->show();
                    }
                    else if(i==n)
                    {
                        this->text->qLabel[i]->setGeometry(g_linestartspace+(this->text->copyy2-this->text->startrow)*g_word_width,g_rowstartspace+(i-1-this->text->startline)*g_lineheight,g_word_width*(this->text->t->filesearchlinelength(this->text->t->file,i)-this->text->copyy2),g_lineheight);
                        this->text->qLabel[i]->show();
                    }
                }
            }
        }
        else if(copyx1==copyx2)
        {
            this->text->qLabel[copyx1]->setStyleSheet("background-color:yellow");
            this->text->pLabel[copyx1]->setStyleSheet("background-color:transparent");
            if(copyy2-copyy1>0)
            {
                this->text->qLabel[copyx1]->setGeometry(g_linestartspace+(copyy1-this->text->startrow)*g_word_width,g_rowstartspace+(copyx1-1-this->text->startline)*g_lineheight,g_word_width*(copyy2-copyy1),g_lineheight);
                this->text->qLabel[copyx1]->show();
            }
            else
            {
                this->text->qLabel[copyx1]->setGeometry(g_linestartspace+(copyy2-this->text->startrow)*g_word_width,g_rowstartspace+(copyx1-this->text->startline-1)*g_lineheight,g_word_width*(copyy1-copyy2),g_lineheight);
                this->text->qLabel[copyx1]->show();
            }
        }

    }
    text->curse_x=g_linestartspace+(text->row-text->startrow)*g_word_width-2;
    text->curse_y=g_rowstartspace+(text->line-text->startline-1)*g_lineheight;
    text->curse->setGeometry(text->curse_x,text->curse_y,g_curse_width,g_lineheight);
    return it->value();
}



void BackGround::changelineandrow(int line, int row)
{
    itoa(line,c,10);
    str=c;
    qstr = QString::fromStdString(str);
    linesum->setText(qstr);
    itoa(row,c,10);
    str=c;
    qstr = QString::fromStdString(str);
    rowsum->setText(qstr);
}




