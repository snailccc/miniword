#include<header.h>
int STRING::Full()
{
    if (pos > 100)
    {
        //cout << "yes" << endl;
        return 1;
    }
    else
    {
        return 0;
    }
}


void STRING::write(int p,char c)
{
    int dis=1;
    for (int i = pos; i > p; i--)
    {
        if (s[i-dis] != 0)
        {
            s[i] = s[i - dis];
        }
        else
        {
            dis++;
            i--;
        }
    }
    pos = pos - dis + 2;
    for(int i=0;i<5;i++)
        cout<<s[i];
    cout<<endl;
}

/*
void STRING::Save(STRING *hp, char *path)
{
    ofstream out(path);
    if (!out.is_open())
    {
        cout << "Fail Operation!" << endl;
        return;
    }
    STRING *cp = hp;
    while (cp != NULL)
    {
        char *temp = new char[105];
        cp->Content(temp);
        for (int i = 0; i < strlen(temp); i++)
        {
            out.write(temp + i, sizeof(char));
        }
        cp = cp->Next();
    }
    out.close();
}
*/
