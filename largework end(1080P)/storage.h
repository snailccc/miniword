#ifndef STORAGE_H
#define STORAGE_H
#include<header.h>
#include<iostream>

using namespace std;

class STRING
{
public:
    char s[100 + 5];
    STRING *next;
    int pos;
    int length;
    QTimer*timer;
    QString strText;
   // string str;
    STRING() { next = NULL; pos = 0;  }
    void write(char c)
    { s[pos++] = c;
        s[pos]='\0';
        cout<<c<<endl;
    }
    void write(int p, char c);
    void Del(int&p) { p--;s[p] = '\0'; }
    void Read();
    void Content(char *&content);
    void getrecord();
    STRING* Next() { return next; }
    int Full();
    STRING *Add() { next = new STRING; return next; }
    void Save(STRING *hp, char *path);
};
#endif // STORAGE_H
