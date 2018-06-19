#include<header.h>
#pragma execution_character_set("utf-8")
line* Storage::initline() {
    line* a=NULL;
    a = (line*)malloc(sizeof(line));
    chunk*curp = NULL;
    curp = (chunk*)malloc(sizeof(chunk));
    memset(curp->data, '\0', store_size);
    curp->next = NULL;
    a->len = 0;
    a->head = curp;
    a->tail = curp;
    a->nextline = NULL;
    return a;
}
void Storage::initfile(File*a) {//返回一个新建的文件
    line* new1 = initline();
    a->firstline = new1;
    a->lastline = new1;
    a->linenum=1;
}

chunk* Storage:: lineindexcut(line*a,int  index) {//在行的第index字符之前截断,注意a的len改动了，返回的新串是chunk，没有len的概念
    a->len = index - 1;//改行中字符个数的记录
    chunk*workp = a->head;
    int count = 0, pos = 0;
    while (count != index - 1)//使pos指向目标字符
    {
        if (pos % store_size == 0 && pos != 0)//到一块的最后一个则指向下一块
        {
            if (workp->next == NULL)
                cout << "error1";
            workp = workp->next;
        }
        if (workp->data[pos % store_size] != '\0')
        {
            count++;
            pos++;
        }
        else pos++;
    }
    if (workp->data[pos % store_size] == '\0')
        pos = store_size;//！！出现bug！！！！当查找的字符为某块的第一个字符，而前一块不满时，应该把pos改到index字符的位置
    if(pos%store_size==0&&pos!=0){//第index字符为某一块的第一个
        cout<<"qingkuang3"<<endl;
        chunk*markp = workp;
        workp = workp->next;
        a->tail = markp;
        markp->next = NULL;
        return workp;
    }
    else {
        //分情况，workp现在是不是尾块
        if (workp == a->tail)//是尾块的情况
        {cout<<"qingkuang1"<<endl;
            chunk*newchunk = (chunk*)malloc(sizeof(chunk));
            for (int i = 0; i <= store_size-1; i++)newchunk->data[i] = '\0';
            newchunk->next = NULL;
            for (int i = 0,j=pos%store_size; i <= store_size-1 &&j<=store_size-1&&workp->data[j]!='\0'; i++,j++)//从第index个字符开始拷贝到新块
            {
                newchunk->data[i] = workp->data[j];
            }
            for (int i = pos % store_size; i <= store_size-1; i++)//旧块后面断开设为空
                workp->data[i] = '\0';
            //cout<<"qingkuang1error"<<endl;
            return newchunk;
        }
        else {//不是尾块的情况
            chunk*newhead = NULL;
            chunk*marknext = workp->next;
            newhead= (chunk*)malloc(sizeof(chunk));
            for (int i = 0; i <= store_size-1; i++)newhead->data[i] = '\0';
            newhead->next = marknext;
            int flag=0;
            for (int i = 0, j = pos % store_size; i <= store_size-1 && j <= store_size-1 && workp->data[j] != '\0'; i++, j++)//从第index个字符开始拷贝到新块
            {flag=1;
                newhead->data[i] = workp->data[j];
                cout<<1;
            }cout<<"qingkuang2error"<<endl;
            if(!flag)cout<<"qingkuang2error"<<endl;
            for (int i = pos % store_size; i <= store_size-1; i++)//旧块后面断开设为空
                workp->data[i] = '\0';
            //for(int i=)
            workp->next = NULL;
            printxingline(a);
            a->tail = workp;
            //cout<<newhead->next->data[0]<<"qq"<<endl;
            cout<<"qingkuang2error"<<endl;
            return newhead;
        }
    }
}
line*Storage:: lineindexcopy(line*a, int index1,int index2) {
    //从该行的第index1个到index2个字符，复制并返回一个line*
    line*newline = initline();
    if (index1 == 1 && index2 == 0)return newline;
    chunk*workp = a->head;
    int count = 0, pos = 0;
    while (count != index1 - 1)
    {
        if (pos % store_size == 0 && pos != 0)//到一块的最后一个则指向下一块
        {
            if (workp->next == NULL)
                cout << "error1";
            workp = workp->next;
        }
        if (workp->data[pos % store_size] != '\0')
        {
            count++;
            pos++;
        }
        else pos++;
    }
    if (workp->data[pos % store_size] == '\0')
        pos = store_size;//！！出现bug！！！！当查找的字符为某块的第一个字符，而前一块不满时，应该把pos改到index字符的位置
    if (pos % store_size == 0 && pos != 0)
    {//第index字符为某一块的第一个
        workp = workp->next;
        chunk*creatworkp = newline->head;
        chunk*lastcreatworkp = newline->head;
        while (workp != NULL) {
            if (newline->len == index2 - index1 + 1)
                return newline;
            for (int i = pos % store_size; i <= store_size-1; i++)
            {
                if(creatworkp==NULL)cout<<"!"<<endl;
                if(workp->data[i % store_size]!='\0')
                {creatworkp->data[i % store_size] = workp->data[i % store_size];
                    newline->len++;
                }
                else break;
            }
            workp = workp->next;
            if (workp) {
                creatworkp = creatworkp->next;
                creatworkp = (chunk*)malloc(sizeof(chunk));
                for (int i = 0; i <= store_size-1; i++)creatworkp->data[i] = '\0';
                workp->next = NULL;
                lastcreatworkp ->next= creatworkp;
                lastcreatworkp = creatworkp;
                newline->tail = creatworkp;
            }
        }
        return newline;
    }
    else {
        chunk*creatworkp = newline->head;
        chunk*lastcreatworkp = newline->head;
        int creatpos = 0;
        while (!(workp == a->tail && (workp->data[pos % store_size] == '\0' || (pos % store_size == 0 && pos != 0))))
        {
            if (creatpos % store_size == 0&&creatpos!=0) {
                creatworkp = creatworkp->next;
                creatworkp = (chunk*)malloc(sizeof(chunk));
                for (int i = 0; i <= store_size-1; i++)creatworkp->data[i] = '\0';
                creatworkp->next = NULL;
                lastcreatworkp->next = creatworkp;
                lastcreatworkp = creatworkp;
                newline->tail = creatworkp;
            }
            if ((pos % store_size == 0 && pos != 0) || workp->data[pos % store_size] == '\0') {
                if (workp->data[pos % store_size] == '\0') {
                    workp = workp->next;
                    pos = 0;
                }
                else {
                    workp = workp->next; pos = 0;
                }
            }
            creatworkp->data[creatpos % store_size] = workp->data[pos % store_size];
            newline->len++;
            if (newline->len == index2 - index1 + 1)return newline;
            pos++; creatpos++;
        }
        return newline;
    }
}
line*Storage::lineindexdeletebetween(line*a, int index1, int index2) {//删除一行第index1个到第index2个字符
    if (index2 > a->len) {
        exit(-1);
    }
    int lenmark = a->len;
    if(index1==1)
    {
        if(index2==a->len){//删除整行
            chunk*freep=a->head;
            chunk*freepp=freep;
            while(freep->next!=NULL)//释放内存
            {
                freep=freep->next;
                free(freepp);
                freepp=freep;
            }
            free(freep);
            chunk*curp = NULL;
            curp = (chunk*)malloc(sizeof(chunk));
            memset(curp->data, '\0', store_size);
            curp->next = NULL;
            a->len = 0;
            a->head = curp;
            a->tail = curp;
            // a->nextline = NULL;
            return a;
        }
        else {//从行头删除到index2
            a->head=lineindexcut(a,index2 + 1);
            chunk*findtail = a->head;
            while (findtail->next != NULL)
                findtail = findtail->next;
            a->tail = findtail;
            findtail->next = NULL;
            a->len = lenmark - index2 + index1 - 1;
            return a;
        }
    }
    else {
        chunk*second = lineindexcut(a,index2 + 1);
        lineindexcut(a, index1);
        chunk*workp = a->head;
        while (workp->next != NULL)
            workp = workp->next;
        workp->next = second;
        chunk*findtail = a->head;
        while (findtail->next != NULL)
            findtail = findtail->next;
        a->tail = findtail;
        findtail->next = NULL;
        a->len = lenmark - index2 + index1 - 1;
        return a;
    }
}
void Storage::zeroenter(File *a) {//从文件左上角回车
    line*newline =initline();
    newline->nextline = a->firstline;
    a->firstline = newline;
    a->linenum++;
}
void Storage:: fileatlinelastenter(File *a,int lineindex) {//从第lineindex行最后回车，line从1开始
    line *curline = a->firstline;
    int linecou = 1;
    while (linecou < lineindex)//找到第indexline行
    {
        linecou++;
        curline = curline->nextline;
    }
    if (a->lastline == curline) {//从最后一行的最后回车
        //line*newline = (line*)malloc(sizeof(line));
        line*newline = initline();
        curline->nextline = newline;
        newline->nextline = NULL;
        a->lastline = newline;

    }
    else {
        line*newline = (line*)malloc(sizeof(line));
        newline = initline();
        line*nextline = curline->nextline;
        curline->nextline = newline;
        newline->nextline = nextline;
    }
    a->linenum++;
}
void Storage::fileatlineindexenter(File*a, int lineindex, int index) {//在第lineindex行（lineindex从1开始）的第index个字符之前回车
    fileatlinelastenter(a, lineindex);//在lineindex行之后插入一新行
    line *curline = a->firstline;
    int linecou = 1;
    while (linecou < lineindex)//找到第indexline行
    {
        linecou++;
        curline = curline->nextline;
    }
    int lenmark = curline->len;
    line*markline = curline;
    curline = curline->nextline;//转到lineindex行下一行的新空行
    curline->head = lineindexcut(markline, index);
    cout<<curline->head->data[1]<<"ii"<<endl;
    chunk*findtail = curline->head;
    while (findtail->next != NULL)findtail = findtail->next;//找新行的行尾
    curline->tail = findtail;
    curline->len =lenmark - index + 1;
}
line*Storage:: filechunkcopy(File*a, int lineindex1, int index1, int lineindex2, int index2) //将块操作选中的东西复制下来,从lineindex1行的
//第index1个字符开始，到lineindex2行的第index2个结束
{

    line *curline1 = a->firstline;
    int linecou = 1;
    while (linecou < lineindex1)//找到第indexline1行
    {
        linecou++;
        curline1 = curline1->nextline;
    }
    if (lineindex1 == lineindex2)return lineindexcopy(curline1,index1, index2);//********若块拷贝在同一行!!!!!!执行行拷贝
    line *curline2 = a->firstline;
    linecou = 1;
    while (linecou < lineindex2)//找到第indexline2行
    {
        linecou++;
        curline2 = curline2->nextline;
    }
    line*workline = curline1->nextline;
    line*copyline = lineindexcopy(curline1, index1,curline1->len);
    line*curcopyline = copyline;
    line*lastcopyline = curcopyline;
    while (workline != curline2) {
        //workline = workline->nextline;
        //curcopyline = NULL;
        curcopyline = lineindexcopy(workline, 1, workline->len);
        lastcopyline->nextline = curcopyline;
        lastcopyline = curcopyline;
        workline = workline->nextline;
    }
    curcopyline = lineindexcopy(workline, 1, index2);
    lastcopyline->nextline = curcopyline;

    return copyline;
}
void Storage::filechunkpaste(File*a, int lineindex, int index,line* copy) {//在lineindex行的第index个字符之后进行块粘贴（多行粘贴），
    //用index为0表示光标在行头
    //index为len表示光标在行末尾
    line *oldline = a->firstline;
    int linecou = 1;
    while (linecou < lineindex)//找到第indexline行
    {
        linecou++;
        oldline = oldline->nextline;
    }

    if (index > oldline->len) {
        cout << "paste error!";
        system("pause");
    }


    if (index == 0)//从行头粘贴时
    {
        if (lineindex == 1)//第一行时的情况
        {
            //	zeroenter(a);
            a->firstline = copy;
            line*findcopyend = copy;
            while (findcopyend->nextline != NULL)findcopyend = findcopyend->nextline;
            findcopyend->nextline = oldline->nextline;
            findcopyend->tail->next = oldline->head;
            findcopyend->tail = oldline->tail;
            findcopyend->len = findcopyend->len + oldline->len;


            if (findcopyend->nextline == NULL)a->lastline = findcopyend;
        }
        else {//不是从第一行情况
            line *frontline = a->firstline;
            int linecou = 1;
            while (linecou < lineindex - 1)//找到第indexline-1行frontline
            {
                linecou++;
                frontline = frontline->nextline;
            }
            frontline->nextline = copy;
            line*findcopyend = copy;
            while (findcopyend->nextline != NULL)findcopyend = findcopyend->nextline;
            findcopyend->nextline = oldline->nextline;
            findcopyend->tail->next = oldline->head;
            findcopyend->tail = oldline->tail;
            findcopyend->len = findcopyend->len + oldline->len;
        }

    }

    else if (index == oldline->len) {//从一行的最后粘贴

        line*findcopyend = copy;
        while (findcopyend->nextline != NULL)findcopyend = findcopyend->nextline;
        findcopyend->nextline = oldline->nextline;
        oldline->nextline = copy->nextline;
        oldline->tail->next = copy->head;
        oldline->tail = copy->tail;
        oldline->len += copy->len;
        if (findcopyend->nextline == NULL)a->lastline = findcopyend;//若是尾行则把尾行指针移动至此
    }

    else {//从一行的中间粘贴时
        int danhangflag=0;
        if(copy->nextline==NULL)//copy块只有一行
        {cout<<"copyjustoneline"<<endl;
            int markoldlinelen3 = oldline->len;//切前长度3
            chunk*houbanjie = lineindexcut(oldline, index + 1);
            oldline->tail->next = copy->head;//块第一行加到目标行的index之后
            copy->tail->next=houbanjie;
            oldline->len=markoldlinelen3+copy->len;
            chunk*findhoubanjieend = houbanjie;
            while (findhoubanjieend->next != NULL)findhoubanjieend = findhoubanjieend->next;//找到后半截的最后一块
            oldline->tail=findhoubanjieend;
            //if(oldline->head->next==NULL)cout<<"NULL";
            if(oldline->head->next==NULL)cout<<"error"<<endl;
        }

        else {//copy块不只一行
            //对一个copy块，块第一行用于加到目标行index之后，块最后一行后接目标行index后半截

            int markoldlinelen1 = oldline->len;//切前长度
            chunk*houbanjie = lineindexcut(oldline, index + 1);

            int markoldlinelen2 = oldline->len;//切后长度
            line*findcopyend = copy;
            if (copy == NULL)cout << "miao";//if you have a bug you say "miao"
            while (findcopyend->nextline != NULL)findcopyend = findcopyend->nextline;//找到copy的最后一行
            findcopyend->nextline = oldline->nextline;
            oldline->nextline = copy->nextline;
            oldline->tail->next = copy->head;//块第一行加到目标行的index之后
            oldline->tail = copy->tail;
            oldline->len += copy->len;

            findcopyend->tail->next = houbanjie;
            chunk*findhoubanjieend = houbanjie;
            while (findhoubanjieend->next != NULL)findhoubanjieend = findhoubanjieend->next;//找到后半截的最后一块
            findcopyend->tail = findhoubanjieend;
            findcopyend->len += markoldlinelen1 - markoldlinelen2;

        }
    }









    line* linecount = a->firstline;
    int linec = 1;
    while (linecount->nextline != NULL)//
    {
        linec++;
        linecount = linecount->nextline;
    }
    a->linenum = linec;
}

/*
void Storage::filechunkdelete(File*a, int lineindex1, int index1, int lineindex2, int index2) {//从lineindex1的第index1个字符开始到lineindex2的index2个结束，删除该块
    line *curline1 = a->firstline;
    int linecou = 1;
    while (linecou < lineindex1)//找到第indexline1行
    {
        linecou++;
        curline1 = curline1->nextline;
    }

    if (lineindex1 == lineindex2) {//块删除选中的两行是同一行的情况
        cout<<curline1<<"  "<<index1<<"  "<<index2;
        lineindexdeletebetween(curline1, index1, index2);
        return ;
    }



    line *curline2 = a->firstline;
     linecou = 1;
    while (linecou < lineindex2)//找到第indexline2行
    {
        linecou++;
        curline2 = curline2->nextline;
    }

    lineindexcut(curline1, index1);
    int lenmark2 = curline2->len;
    curline2->head = lineindexcut(curline2, index2 + 1);//注意加1

    chunk*findtail = curline2->head;
    while (findtail->next != NULL)findtail = findtail->next;//找lineindex2行的行尾
    curline1->tail->next = curline2->head;
    curline1->tail = findtail;
    line*freeworkline = curline1->nextline;
    curline1->nextline = curline2->nextline;

    //curline2->len = lenmark2 - index2;
    //line*freeworkline = curline1->nextline;
    //curline1->nextline = curline2;
    while (freeworkline != curline2)
    {
        line*t=freeworkline;
        freeworkline = freeworkline->nextline;
        free(t);
    }



    line* linecount = a->firstline;
    int linec = 1;
    while (linecount->nextline!=NULL)//找到第indexline2行
    {
        linec++;
        linecount = linecount->nextline;
    }
    a->linenum = linec;



}

*/
void Storage::filechunkdelete(File*a, int lineindex1, int index1, int lineindex2, int index2) {//从lineindex1的第index1个字符开始到lineindex2的index2个结束，删除该块
    int linecou = 1;
    cout<<"tongyihang111"<<endl;
    line *curline1 = a->firstline;
    while (linecou < lineindex1)//找到第indexline1行
    {
        linecou++;
        curline1 = curline1->nextline;
    }

    if (lineindex1 == lineindex2) {//块删除选中的两行是同一行的情况
        cout<<"tongyihang"<<endl;
        lineindexdeletebetween(curline1, index1, index2);
        return;
    }

    else{//不在同一行

        line *curline2 = a->firstline;
        linecou = 1;
        while (linecou < lineindex2)//找到第indexline2行
        {
            linecou++;
            curline2 = curline2->nextline;
        }

        if(index1==1){
            if(lineindex1!=1){
                int linecou = 1;
                line *curline1 = a->firstline;
                while (linecou < lineindex1-1)//找到第indexline1-1行
                {
                    linecou++;
                    curline1 = curline1->nextline;
                }
                curline1->nextline=curline2;
                lineindexdeletebetween(curline2,1,index2);
            }
            else{
                a->firstline=curline2;
                lineindexdeletebetween(curline2,1,index2);
            }
        }
        else if(index2==curline2->len){
            lineindexcut(curline1, index1);
            line*nextline=curline2->nextline;
            curline1->nextline=nextline;
        }

        else {
            lineindexcut(curline1, index1);
            int lenmark2 = curline2->len;
            curline2->head = lineindexcut(curline2, index2 + 1);//注意加1
            chunk*findtail = curline2->head;
            while (findtail->next != NULL)findtail = findtail->next;//找lineindex2行的行尾
            curline1->tail->next = curline2->head;
            curline1->tail = findtail;
            line*freeworkline = curline1->nextline;
            curline1->nextline = curline2->nextline;
            curline1->len+=(lenmark2 - index2);    printxingfile(a);
            //curline2->len = lenmark2 - index2;
            //line*freeworkline = curline1->nextline;
            //curline1->nextline = curline2;
            while (freeworkline != curline2)
            {
                line*t=freeworkline;
                freeworkline = freeworkline->nextline;
                free(t);
            }

        }
    }

    line* linecount = a->firstline;
    int linec = 1;
    while (linecount->nextline!=NULL)//找到第indexline2行
    {
        linec++;
        linecount = linecount->nextline;
    }

    a->linenum = linec;
}
void Storage::inlineinsertatlast(line* a,char data) {//在一行最后一块的第一个 处插入
    int pos = 0, count = 0;
    chunk*workp = a->tail;
    while (workp->data[pos] != '\0')
    {
        if (pos == store_size)break;
        pos++;
    }
    if (pos % store_size == 0&&pos!=0) {//创建下一块
        chunk*newp = NULL;
        newp = (chunk*)malloc(sizeof(chunk));
        newp->next = NULL;
        memset(newp->data, '\0', store_size);
        workp->next = newp;
        a->tail = newp;
        workp = workp->next;
        workp->data[pos % store_size]=data;
        a->len++;
        return ;
    }
    workp->data[pos % store_size]=data;
    a->len++;
    return ;
}
void Storage::inlineinsertatindex(line*a, int index,char data) //index为显示的第i个（i从1开始），从第i个之前插入
{
    chunk*workp = a->head;
    int count = 0, pos = 0;
    while (count!=index-1)
    {
        if (pos % store_size == 0 && pos != 0)//到一块的最后一个则指向下一块
        {
            if (workp->next == NULL)
                cout << "error1";
            workp = workp->next;
        }
        if (workp->data[pos%store_size] != '\0')
        {
            count++;
            pos++;
        }
        else pos++;
    }
    if (pos % store_size == 0 && pos != 0)//index表示的字母为下一块的第一个，pos现在指向目标字母的位置,
        //workp还在index所在块的上一块
    {cout<<"insert1";
        chunk*newp = NULL;
        newp = (chunk*)malloc(sizeof(chunk));
        newp->next = workp->next;
        memset(newp->data, '\0', store_size);
        workp->next = newp;
        //上为在两块间加一块
        //下为在新块插入字符
        workp = workp->next;
        workp->data[pos % store_size]=data;
        if(workp->next==NULL) a->tail=workp;
    }
    else {//index表示的字母为块的第二个至最后一个之间，此时将一个块划分为3块便于插入
        //要区分原块是不是tail块

        //cout<<"mwj222"<<endl;

        if (workp->data[pos%store_size] == '\0')
        {
            workp->data[pos%store_size]=data;
            a->len++;
            return ;
        }
        if (workp == a->tail)//是最后一块的情况
        {cout<<"insert2";

            int remark = pos%store_size;//为index的位置
            // chunk*newp1 = NULL;
            // newp1 = (chunk*)malloc(sizeof(chunk));
            // memset(newp1->data, '\0', store_size);
            chunk*newp2 = NULL;
            newp2 = (chunk*)malloc(sizeof(chunk));
            memset(newp2->data, '\0', store_size);
            workp->next = newp2;
            //newp1->next = newp2;
            newp2->next = NULL;
            for (int i = remark, j = 0; i <= store_size-1; i++, j++)//原块从index字母开始到最后一个复制到newp2块
            {
                newp2->data[j] = workp->data[i%store_size];
                workp->data[i] = '\0';
            }
            if(workp->data[pos%store_size]=='\0')cout<<"error";
            cout<<pos<<" ";
            workp->data[pos%store_size]=data;//输入newp1块的第一个字母
            a->tail = newp2;//尾巴移动
        }
        else {//原块不是最后一块情况
            cout<<"insert3";
            //cout << "bu是最后一块的情况" << endl;
            chunk*indexnext = workp->next;//原块的下一块
            chunk*newp1 = NULL;
            newp1 = (chunk*)malloc(sizeof(chunk));
            memset(newp1->data, '\0', store_size);
            chunk*newp2 = NULL;
            newp2 = (chunk*)malloc(sizeof(chunk));
            memset(newp2->data, '\0', store_size);
            workp->next = newp1;
            newp1->next = newp2;
            newp2->next = indexnext;
            for (int i = pos%store_size, j = 0; i <= store_size-1; i++, j++)//原块从index字母开始到最后一个复制到newp2块
            {
                newp2->data[j] = workp->data[i];
                workp->data[i] = '\0';
            }
            newp1->data[0]=data;
        }
    }
    cout<<a->tail->data[0]<<"uu"<<endl;
    a->len++;
    return ;
}
void Storage::inlinebackspacelast(line*a) {
    int pos = 0, count = 0;
    chunk*workp = a->tail;
    while (workp->data[pos%store_size] != '\0')
    {
        if (pos == store_size)break;
        pos++;
    }
    workp->data[pos%store_size - 1] = '\0';
    if (pos % store_size == 1&&workp!=a->head)//尾块的第一个字符被删除，应该free该块,若该块又是尾块又是首块则不free
    {
        chunk*freeworkp = a->head;
        while (freeworkp->next != workp)freeworkp = freeworkp->next;
        a->tail = freeworkp;
        freeworkp->next = NULL;
        free(workp);
    }
    a->len--;
}
void Storage::inlinebackspaceindex(line*a,int index)
{//删除第index个数并对可能出现的空白块进行处理
    chunk*workp = a->head;
    int count = 0, pos = 0;
    while (count != index - 1)
    {
        if (pos % store_size == 0 && pos != 0)//到一块的最后一个则指向下一块
        {
            if (workp->next == NULL)
                cout << "error1";
            workp = workp->next;
        }
        if (workp->data[pos % store_size] != '\0')
        {
            count++;
            pos++;
        }
        else pos++;
    }
    if (workp->data[pos%store_size] == '\0')pos = store_size;//！！出现bug！！！！当查找的字符为某块的第一个字符，而前一块不满时，应该把pos改到index字符的位置
    int freechunkflag = 0;
    chunk*markp = workp;
    if (pos % store_size == 0 && pos != 0)
    {  workp = workp->next;
        cout<<"k";
    }
    for (int i = pos % store_size; i <= store_size-1; i++)
    {
        if (i == 0&&workp->data[i+1]=='\0'&&workp!=a->head) {
            cout<<"l";
            freechunkflag = 1; break; }//只有一个字符的一块的第一个字符被删除，块应该被free
        else if (i == store_size-1)workp->data[i] = '\0';//到最后一个字符时必定要设为
        else if (workp->data[i + 1] == '\0')
        {
            workp->data[i] = '\0';
            break;
        }
        else workp->data[i] = workp->data[i + 1];
    }
    if (freechunkflag) {//此时该块全为空白，应该free掉
        if (workp == a->tail) {//index所在块为尾块的情况
            a->tail = markp;
            markp->next = NULL;
            free(workp);
        }
        else {//index所在块不是尾块情况
            markp->next = workp->next;
            free(workp);
        }
    }

    a->len--;
}
void Storage::fileinlineinsertatlast(File *a, int lineindex,char data) {//在第lineindex行末尾写入字符
    line *curline = a->firstline;
    int linecou = 1;
    while (linecou < lineindex)//找到第indexline行
    {
        linecou++;
        curline = curline->nextline;
    }
    cout<<a->linenum<<"rr"<<endl;
    inlineinsertatlast(curline,data);
}
void Storage::fileinlineinsertatindex(File *a, int lineindex,int index,char data) {//在第lineindex行第index个字符之前写入字符
    line *curline = a->firstline;
    int linecou = 1;
    while (linecou < lineindex)//找到第indexline行
    {
        linecou++;
        curline = curline->nextline;
    }
    inlineinsertatindex(curline,index,data);
}
void Storage::fileinlinebackspacelast(File*a, int lineindex) {//文件lineindex行的行末尾进行backspace
    line *curline = a->firstline;
    int linecou = 1;
    while (linecou < lineindex)//找到第indexline行
    {
        linecou++;
        curline = curline->nextline;
    }
    inlinebackspacelast(curline);
}
void Storage::fileinlinebackspaceindex(File*a, int lineindex, int index) {//删除第index个数
    line *curline = a->firstline;
    int linecou = 1;
    while (linecou < lineindex)//找到第indexline行
    {
        linecou++;
        curline = curline->nextline;
    }
    if (index == 1 && curline->len == 1)
    {
        free(curline->head);
        chunk*curp = NULL;
        curp = (chunk*)malloc(sizeof(chunk));
        memset(curp->data, '\0', store_size);
        curp->next = NULL;
        curline->len = 0;
        curline->head = curp;
        curline->tail = curp;
    }
    else if(index==0) {//在行后backspace该行与上一行合并
        if (lineindex == 1)return;//左上角删除，无变化
        else {

            line *lastline = a->firstline;
            int lastcou = 1;
            while (lastcou < lineindex-1)//找到第indexline-1行
            {
                lastcou++;
                lastline = lastline->nextline;
            }
            if(lastline->len==0){//上一行为空行时
                line*nextline = curline->nextline;
                lastline->nextline = nextline;
                lastline->head=curline->head;
                lastline->tail = curline->tail;
                lastline->len+=curline->len;
                free(curline);
                a->linenum--;
            }
            else{

                line*nextline = curline->nextline;
                lastline->nextline = nextline;
                lastline->tail->next = curline->head;
                lastline->tail = curline->tail;
                lastline->len+=curline->len;
                free(curline);
                a->linenum--;
            }}
    }
    else if (curline->len == 0&&lineindex!=0)
    {
        cout << "使用错误，空行被指定删除第某个字符!";
        return;
    }
    else
        inlinebackspaceindex(curline,index);
}
void Storage::fileinlinedeleteindex(File*a, int lineindex, int index) {//删除第index+1个数  delete倒序删除操作
    fileinlinebackspaceindex(a, lineindex, index + 1);
}

void Storage::filestringprint(File*a) {
    int k = a->linenum;
    int i = 0;

    for(i=0;i<100;i++)
        forprint[i].clear();

    i=0;
    line*workline =NULL;
    chunk*workp = NULL;
    string kp;
    workline = a->firstline;
    while (k--&&workline!=NULL) {
        workp = workline->head;
        kp.clear();
        while (workp != NULL) {
            for (int i = 0; i < store_size; i++)
            {
                if (workp->data[i] != '\0')
                    kp += workp->data[i];
                else break;
            }
            workp = workp->next;
        }
        forprint[i] = kp;
        i++;
        workline = workline->nextline;
    }
}
int Storage::filesearchlinelength(File*a,int lineindex)
{
    line*curline=a->firstline;
    int linecou=1;
    while (linecou < lineindex)//找到第indexline行
    {
        linecou++;
        curline = curline->nextline;
    }
    return curline->len;
}

int Storage::judgeposition(File*a,int linenum, int rownum)
{
    line*curline=a->firstline;
    int linecou=1;
    if(a->linenum>=linenum){
        while(linenum!=linecou &&linenum>0){
            curline=curline->nextline;
            linecou++;
        }
        if(curline->len>=rownum)
            return 1;
        else return 0;
    }
    else return 0;
}
void Storage::fileinlineinsertstring(File*a, int lineindex, int index, string s) {//在第几行第几个之前插入一段中文
    line *curline = a->firstline;
    int linecou = 1;
    while (linecou < lineindex)//找到第indexline行
    {
        linecou++;
        curline = curline->nextline;
    }
    int pianyi = 0;
    for (int i = 0; i < s.length(); i++)
    {
        stringinlineinsertatindex(curline, index + pianyi, s[i]);
        pianyi++;
    }
}


line Storage::stringinlineinsertatindex(line*a, int index,char s) //index为显示的第i个（i从1开始），从第i个之前插入
{
    chunk*workp = a->head;
    int count = 0, pos = 0;
    while (count != index - 1)
    {
        if (pos % store_size == 0 && pos != 0)//到一块的最后一个则指向下一块
        {
            if (workp->next == NULL)
                cout << "error1";
            workp = workp->next;
        }
        if (workp->data[pos%store_size] != '\0')
        {
            count++;
            pos++;
        }
        else pos++;

    }
    if (pos % store_size == 0 && pos != 0)//index表示的字母为下一块的第一个，pos现在指向目标字母的位置,
        //workp还在index所在块的上一块
    {
        chunk*newp = NULL;
        newp = (chunk*)malloc(sizeof(chunk));
        newp->next = workp->next;
        memset(newp->data, '\0', store_size);
        workp->next = newp;
        //上为在两块间加一块
        //下为在新块插入字符
        workp = workp->next;
        workp->data[pos % store_size]=s;
        if (workp->next == NULL)a->tail = workp;
    }
    else {//index表示的字母为块的第二个至最后一个之间，此时将一个块划分为3块便于插入
        //要区分原块是不是tail块
        if (workp->data[pos%store_size] == '\0')
        {
            workp->data[pos%store_size]=s;
            a->len++;
            return *a;
        }
        if (workp == a->tail)//是最后一块的情况
        {
            //cout << "是最后一块的情况" << endl;
            int remark = pos;//为index的位置
            chunk*newp1 = NULL;
            newp1 = (chunk*)malloc(sizeof(chunk));
            memset(newp1->data, '\0',store_size);
            chunk*newp2 = NULL;
            newp2 = (chunk*)malloc(sizeof(chunk));
            memset(newp2->data, '\0',store_size);
            workp->next = newp1;
            newp1->next = newp2;
            newp2->next = NULL;
            for (int i = remark, j = 0; i <= store_size - 1; i++, j++)//原块从index字母开始到最后一个复制到newp2块
            {
                newp2->data[j] = workp->data[i];
                workp->data[i] = '\0';
            }
            newp1->data[0]=s;//输入newp1块的第一个字母
            a->tail = newp2;//尾巴移动
        }
        else {//原块不是最后一块情况
            //cout << "bu是最后一块的情况" << endl;
            chunk*indexnext = workp->next;//原块的下一块
            chunk*newp1 = NULL;
            newp1 = (chunk*)malloc(sizeof(chunk));
            memset(newp1->data, '\0', store_size);
            chunk*newp2 = NULL;
            newp2 = (chunk*)malloc(sizeof(chunk));
            memset(newp2->data, '\0', store_size);
            workp->next = newp1;
            newp1->next = newp2;
            newp2->next = indexnext;
            for (int i = pos%store_size, j = 0; i <= store_size - 1; i++, j++)//原块从index字母开始到最后一个复制到newp2块
            {
                newp2->data[j] = workp->data[i];
                workp->data[i] = '\0';
            }
            newp1->data[0]=s;
        }
    }
    a->len++;
    return *a;
}

void Storage::filerefresh(File*a) {
    line*workline = a->firstline;
    int linecnt = 1;
    if (a->linenum == 1) {//只有一行
        line*newline = filechunkcopy(a, 1, 1, 1, a->firstline->len);
        //***********
        line*freeline = workline;
        chunk*freeworkp = freeline->head;//释放掉这种方法的内存，防止泄露
        chunk*freeworkpnext = freeline->head->next;
        free(freeworkp);
        while (freeworkpnext != NULL) {
            freeworkp = freeworkpnext;
            freeworkpnext = freeworkpnext->next;
            free(freeworkp);
        }
        free(freeline);
        //**********
        a->firstline = newline;
        a->lastline = newline;

    }
    else if (a->linenum >= 2) {//两行以上
        line*newline = filechunkcopy(a, 1, 1, 1, a->firstline->len);
        newline->nextline = a->firstline->nextline;
        a->firstline = newline;
        line*oldline = a->firstline;
        workline = a->firstline->nextline;
        while (workline != NULL) {
            linecnt++;
            line*newline = filechunkcopy(a, linecnt, 1, linecnt, workline->len);
            newline->nextline = workline->nextline;
            oldline->nextline = newline;

            oldline = oldline->nextline;//走到下一行
            line*freeline = workline;//存一下泄漏的内存地址
            workline = workline->nextline;//走到下一行

            //解决内存泄漏
            chunk*freeworkp = freeline->head;//释放掉这种方法的内存，防止泄露
            chunk*freeworkpnext = freeline->head->next;
            free(freeworkp);
            while (freeworkpnext != NULL) {
                freeworkp = freeworkpnext;
                freeworkpnext = freeworkpnext->next;
                free(freeworkp);
            }
            free(freeline);//解决
        }
    }
}

void Storage::printxingfile(File *a)
{
    line*workline = a->firstline;
    int i = 0;
    while (workline != NULL)
    {
        i++;
        printxingline(workline);
        workline = workline->nextline;
    }
}

void Storage::printxingline(line *a)
{
    chunk*workp = a->head;
    while (workp != NULL) {
        for (int i = 0; i < store_size; i++)
        {
            if (workp->data[i] != '\0')
                cout << workp->data[i];
            // else cout<<"#";
        }
        workp = workp->next;
    }
    cout << endl;
}


line *Storage::getmarkcopy(line *a)
{

    line*workline = a;
    line*newchunk = lineindexcopy(a, 1, a->len);
    line*newlineworkline = newchunk;
    while (workline->nextline != NULL)
    {
        workline = workline->nextline;
        newlineworkline->nextline = lineindexcopy(workline, 1, workline->len);
        newlineworkline = newlineworkline->nextline;
    }
    return newchunk;
}

forundo Storage::initforundo()
{
    forundo a;
    a.type=0;
    a.oldlie1=a.oldlie2=a.newhang1=a.newhang2=-2;
    a.newlie1=a.newlie2=a.oldhang1=a.oldhang2=-2;
    a.kuai=NULL;
    return a;
}

forundo Storage::undoredotrans(forundo a)
{
    forundo t;
    if(a.type==1)
    {
        t.oldhang1=t.newhang1=a.newhang1;
        t.oldlie1=t.newlie1=a.newlie1;
        t.newch=a.oldch;
        t.type=3;
    }
    else if(a.type==3){
        t.oldhang1=t.newhang1=a.newhang1;
        t.oldlie1=t.newlie1=a.newlie1;
        t.oldch=a.newch;
        t.type=1;
    }
    return t;
}


void Storage::changestring(File*a,string&kp,int lineindex)
{
    line*curline = a->firstline;
    int linecou = 1;
    while (linecou < lineindex)//找到第indexline行
    {
        linecou++;
        curline = curline->nextline;
    }

    chunk*workp =curline->head;
    while (workp !=NULL) {
        for (int i = 0; i < store_size; i++)
        {
            if (workp->data[i] != '\0')
            {kp += workp->data[i];
            }}
        workp = workp->next;
    }
}

void Storage::filesubstitude(File*a, int lineindex1,int  index1,int  lineindex2,int  index2, string s) {//第lineindex1行第index1个char类型字符到第lineindex2行第index2个
    //字符替换成string
    string str;
    filechunkdelete(a, lineindex1, index1, lineindex2, index2);
    changestring(file,str,lineindex1);
    fileinlineinsertstring(a, lineindex1, index1, s);
}

