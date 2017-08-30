#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "game.h"
#include <QMouseEvent>
#include <QPushButton>
#include <QLCDNumber>
#include <QSignalMapper>
#include <selectdlg.h>
#include <QFile>
#include <QMessageBox>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
private:
    Ui::Widget *ui;
    QPoint chosen;
    QPushButton *restart,*stop,*last,*next,*flag,*del,*select;
    QPushButton* num[9];
    QLCDNumber* time;
    QSignalMapper* map;
    game* gm;
    selectdlg* dlg;
    QPushButton *remind;
    bool have_flag[9][9];
private slots:
    void to_deal(int ope);
    void redisplay();  //刷新界面
    void showtime(QTime);
    void change();  //改变暂停按钮状态
    void win();  //游戏胜利
    void addflag();  //添加标记
    void showdlg();
    void showtitle(int);
    void reminding();
signals:
    void dealing(int,int,int);
    void reminding(int,int);
};

#endif // WIDGET_H
