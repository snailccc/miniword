#ifndef RESTORE_H
#define RESTORE_H
#include<header.h>
#define store_size 100

typedef struct chunk {
    char data[store_size];
    struct chunk * next;
}chunk;

typedef struct line {
    chunk*head, *tail;
    int len;//不考虑数组0位，有多少字符len就为几
    struct line*nextline;
}line;

typedef struct file {//文件
    line *firstline;
    line *lastline;
    int linenum;
}File;
typedef struct forundo{
  int type;
    int oldhang1,oldlie1,oldhang2,oldlie2;
    int newhang1,newlie1,newhang2,newlie2;
    char oldch,newch;
    string oldstr,newstr;
    line* kuai;

}forundo;
class Storage
{
public:
    line* initline();
    void initfile(File*a);
    chunk* lineindexcut(line*a,int  index);
    line* lineindexcopy(line*a, int index1,int index2);
    void zeroenter(File *a);
    line*lineindexdeletebetween(line*a, int index1, int index2);
    void fileatlinelastenter(File *a,int lineindex) ;
    void fileatlineindexenter(File*a, int lineindex, int index);
    line* filechunkcopy(File*a, int lineindex1, int index1, int lineindex2, int index2);
    void filechunkdelete(File*a, int lineindex1, int index1, int lineindex2, int index2);
    void inlineinsertatlast(line* a,char data);
    void inlineinsertatindex(line*a, int index,char data);
    void inlinebackspacelast(line*a);
    void inlinebackspaceindex(line*a,int index);
    void fileinlineinsertatlast(File *a, int lineindex,char data);
    void fileinlineinsertatindex(File *a, int lineindex,int index,char data);
    void fileinlinebackspacelast(File*a, int lineindex);
    void fileinlinebackspaceindex(File*a, int lineindex, int index);
    int filesearchlinelength(File*a,int lineindex);
    void filechunkpaste(File*a, int lineindex, int index,line* copy);
    void filestringprint(File*a);
    void fileinlinedeleteindex(File*a, int lineindex, int index);
    int judgeposition(File*a,int line,int row);
    void changestring(File*a,string&kp,int linenum);
    void fileinlineinsertstring(File*a, int lineindex, int index, string s);
    line stringinlineinsertatindex(line*a, int index,char s); //index
    void filerefresh(File*a);
    void printxingfile(File*a);
    void printxingline(line*a);
    void filesubstitude(File*a, int lineindex1,int  index1,int  lineindex2,int  index2, string s);
    line*getmarkcopy(line*a);
    forundo initforundo();
    forundo undoredotrans(forundo a);
    File*file;
    string forprint[100];
    line*worklinee;
    line*copyline;
    line*markcopy;//复制串
    bool markcopychinese[100][1000];
    forundo undo[100];
    int posforundo;
};


#endif // RESTORE_H
