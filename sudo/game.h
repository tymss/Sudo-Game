#ifndef GAME_H
#define GAME_H
#include <QList>
#include <QObject>
#include <QPoint>
#include "sudoku_creator.h"
#include <QTimer>
#include <QSound>
class operate
{
public:
    QPoint position;
    int ope;
    QList<int> removing;
    operate()
    {
        position.setX(0);
        position.setY(0);
    }
    operate(int x,int y,int _ope)
    {
        position.setX(x);
        position.setY(y);
        ope=_ope;
    }
    operate(int x,int y,QList<int> lis)
    {
        position.setX(x);
        position.setY(y);
        ope=0;
        removing=lis;
    }
};

class game:public QObject
{
    Q_OBJECT

private:
    QList<int> number[9][9];
    QList<operate> opelist;
    operate next_ope;
    bool available[9][9];
    QTime time;
    QTimer *timer;
    QSound *sound;
    creator *cre;
    int result[9][9];
    bool win();    //判断是否胜利
public:
    game();
    QList<int> getnum(int x,int y);
    bool is_available(int x,int y);    
    ~game();
private slots:
    void initial(int method);
    void deal(int x,int y,int ope);
    void last();
    void next();
    void times();
    void stop();
    void restart();
    void reminder(int,int);
signals:
    void display();   //通知主窗口刷新
    void time_display(QTime);
    void winning();
};

#endif // GAME_H
