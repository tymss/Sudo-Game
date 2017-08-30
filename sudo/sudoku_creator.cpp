#include "sudoku_creator.h"

void creator::read()
{
    QFile f(":/sudoku/sudoku/sudoku1.txt");
    if(!f.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        return;
    }
    QTextStream reading(&f);
    int n=0;
    int num;
    while(!reading.atEnd())
    {
        QString text=reading.read(1);
        if(text!=' '&&text!="\n")
        {
            n++;
            if(text.toInt())
            {
                num=text.toInt();
                sudo[(n-1)/9][(n-1)%9]=num;
            }
        }
    }
    f.close();
}

void creator::change(int type, int a, int b)
{
    if(type==1)
    {
        for(int i=0;i<9;i++)
        {
            int m=sudo[a][i];
            sudo[a][i]=sudo[b][i];
            sudo[b][i]=m;
        }
    }
    else
    {
        for(int i=0;i<9;i++)
        {
            int m=sudo[i][a];
            sudo[i][a]=sudo[i][b];
            sudo[i][b]=m;
        }
    }
}

void creator::create()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for(int i=0;i<10;i++)
    {
        switch (qrand()%3) {
        case 0:
            change(1,0,1);
            break;
        case 1:
            change(1,1,2);
            break;
        case 2:
            change(1,0,2);
            break;
        }
    }
    for(int i=0;i<10;i++)
    {
        switch (qrand()%3) {
        case 0:
            change(1,3,4);
            break;
        case 1:
            change(1,3,5);
            break;
        case 2:
            change(1,4,5);
            break;
        }
    }
    for(int i=0;i<10;i++)
    {
        switch (qrand()%3) {
        case 0:
            change(1,6,7);
            break;
        case 1:
            change(1,8,7);
            break;
        case 2:
            change(1,6,8);
            break;
        }
    }
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for(int i=0;i<10;i++)
    {
        switch (qrand()%3) {
        case 0:
            change(2,0,1);
            break;
        case 1:
            change(2,1,2);
            break;
        case 2:
            change(2,0,2);
            break;
        }
    }
    for(int i=0;i<10;i++)
    {
        switch (qrand()%3) {
        case 0:
            change(2,3,4);
            break;
        case 1:
            change(2,3,5);
            break;
        case 2:
            change(2,4,5);
            break;
        }
    }
    for(int i=0;i<10;i++)
    {
        switch (qrand()%3) {
        case 0:
            change(2,6,7);
            break;
        case 1:
            change(2,8,7);
            break;
        case 2:
            change(2,6,8);
            break;
        }
    }
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for(int i=0;i<10;i++)
    {
        switch (qrand()%3) {
        case 0:
            change(1,0,3);
            change(1,1,4);
            change(1,2,5);
            break;
        case 1:
            change(1,0,6);
            change(1,1,7);
            change(1,2,8);
            break;
        case 2:
            change(1,3,6);
            change(1,4,7);
            change(1,5,8);
            break;
        }
    }
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for(int i=0;i<10;i++)
    {
        switch (qrand()%3) {
        case 0:
            change(2,0,3);
            change(2,1,4);
            change(2,2,5);
            break;
        case 1:
            change(2,0,6);
            change(2,1,7);
            change(2,2,8);
            break;
        case 2:
            change(2,3,6);
            change(2,4,7);
            change(2,5,8);
            break;
        }
    }
}

creator::creator()
{
    read();
}

int creator::sudo_cre(int i, int j)
{
    return sudo[i][j];
}
