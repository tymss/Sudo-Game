#ifndef SUDOKU_CREATOR_H
#define SUDOKU_CREATOR_H
#include <QFile>
#include <QtGlobal>
#include <QTime>
#include <QString>
#include <QTextStream>
class creator
{
private:
    int sudo[9][9];
    void read();
    void change(int type,int a,int b);
public:
    void create();
    creator();
    int sudo_cre(int i,int j);
};
#endif // SUDOKU_CREATOR_H
