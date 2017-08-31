#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QGridLayout>
#include <QDebug>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setFixedSize(600,800);
    chosen.setX(0);
    chosen.setY(0);
    isstop=0;
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            have_flag[i][j]=0;
    setAutoFillBackground(true);
    QPalette pal;
    pal.setBrush(QPalette::Background,QBrush(QPixmap(":/image/image/back.png")));
    this->setPalette(pal);
    QFont fon;
    fon.setFamily("华文琥珀");
    fon.setPointSize(10);
    this->setFont(fon);
    gm=new game;
    setWindowTitle("数独游戏-未开始");
    dlg=new selectdlg(this);
    select=new QPushButton("返回选关",this);
    restart=new QPushButton("重玩",this);
    stop=new QPushButton("暂停",this);
    last=new QPushButton("撤销",this);
    next=new QPushButton("恢复",this);
    flag=new QPushButton("标记",this);
    del=new QPushButton("删除",this);
    remind=new QPushButton("提示",this);
    for(int i=0;i<9;i++)
    {
        num[i]=new QPushButton(QString::number(i+1),this);
    }
    select->setFixedSize(150,30);
    select->move(30,7);
    last->setFixedSize(70,70);
    last->move(25,635);
    next->setFixedSize(70,70);
    next->move(105,635);
    flag->setFixedSize(70,70);
    flag->move(185,635);
    del->setFixedSize(70,70);
    del->move(265,635);
    remind->setFixedSize(70,70);
    remind->move(345,635);
    num[0]->setFixedSize(70,70);
    num[0]->move(425,635);
    num[1]->setFixedSize(70,70);
    num[1]->move(505,635);
    for(int i=0;i<7;i++)
    {
        num[i+2]->setFixedSize(70,70);
        num[i+2]->move(25+i*80,715);
    }
    restart->setFixedSize(100,30);
    restart->move(30,40);
    stop->setFixedSize(100,30);
    stop->move(150,40);
    time=new QLCDNumber(this);
    time->setDigitCount(8);
    time->resize(120,60);
    QTime t;
    t.setHMS(0,0,0);
    time->display(t.toString("hh:mm:ss"));
    time->move(400,10);
    time->setSegmentStyle(QLCDNumber::Flat);
    time->setStyleSheet("background-color: rgb(85, 170, 255);border-radius: 20px;  border: 0px;");
    map=new QSignalMapper(this);
    for(int i=0;i<9;i++)
    {
        connect(num[i],SIGNAL(clicked(bool)),map,SLOT(map()));
        map->setMapping(num[i],i+1);
    }
    connect(del,SIGNAL(clicked(bool)),map,SLOT(map()));
    map->setMapping(del,0);
    connect(map,SIGNAL(mapped(int)),this,SLOT(to_deal(int)));
    connect(gm,SIGNAL(display()),this,SLOT(redisplay()));
    connect(last,SIGNAL(clicked(bool)),gm,SLOT(last()));
    connect(next,SIGNAL(clicked(bool)),gm,SLOT(next()));
    connect(gm,SIGNAL(time_display(QTime)),this,SLOT(showtime(QTime)));
    connect(stop,SIGNAL(clicked(bool)),this,SLOT(change()));
    connect(stop,SIGNAL(clicked(bool)),gm,SLOT(stop()));
    connect(gm,SIGNAL(winning()),this,SLOT(win()));
    connect(restart,SIGNAL(clicked(bool)),gm,SLOT(restart()));
    connect(flag,SIGNAL(clicked(bool)),this,SLOT(addflag()));
    connect(select,SIGNAL(clicked(bool)),this,SLOT(showdlg()));
    connect(remind,SIGNAL(clicked(bool)),this,SLOT(reminding()));
    connect(this,SIGNAL(reminding(int,int)),gm,SLOT(reminder(int,int)));
    connect(dlg,SIGNAL(to_close()),this,SLOT(close()));
    connect(dlg,SIGNAL(to_start(int)),gm,SLOT(initial(int)));
    connect(dlg,SIGNAL(to_start(int)),this,SLOT(showtitle(int)));
    connect(this,SIGNAL(dealing(int,int,int)),gm,SLOT(deal(int,int,int)));
    stop->setStyleSheet("QPushButton{background-color:rgb(85, 170, 255);\
                        color: white;   border-radius: 10px;  border: 0px;\
                        border-style: outset;}"
                        "QPushButton:hover{background-color:white; color: black;}"
                        "QPushButton:pressed{background-color:rgb(85, 170, 255);\
                        border-style: inset; }");
    restart->setStyleSheet("QPushButton{background-color:rgb(255,127,80);\
                           color: white;   border-radius: 10px;  border:0px;\
                           border-style: outset;}"
                           "QPushButton:hover{background-color:white; color: black;}"
                           "QPushButton:pressed{background-color:rgb(85, 170, 255);\
                           border-style: inset; }");
    select->setStyleSheet("QPushButton{background-color:rgb(50,205,50);\
                          color: white;   border-radius: 10px;  border:0px;\
                          border-style: outset;}"
                          "QPushButton:hover{background-color:white; color: black;}"
                          "QPushButton:pressed{background-color:rgb(85, 170, 255);\
                          border-style: inset; }");
    last->setStyleSheet("QPushButton{background-color:rgb(85,170,255);\
                        color: white;   border-radius: 10px;  border: 0px;\
                        border-style: outset;}"
                        "QPushButton:hover{background-color:white; color: black;}"
                        "QPushButton:pressed{background-color:rgb(85, 170, 255);\
                        border-style: inset; }");
    next->setStyleSheet("QPushButton{background-color:rgb(85,170,255);\
                        color: white;   border-radius: 10px;  border: 0px;\
                        border-style: outset;}"
                        "QPushButton:hover{background-color:white; color: black;}"
                        "QPushButton:pressed{background-color:rgb(85, 170, 255);\
                        border-style: inset; }");
    flag->setStyleSheet("QPushButton{background-color:rgb(191,62,255);\
                        color: white;   border-radius: 10px;  border: 0px;\
                        border-style: outset;}"
                        "QPushButton:hover{background-color:white; color: black;}"
                        "QPushButton:pressed{background-color:rgb(85, 170, 255);\
                        border-style: inset; }");
    del->setStyleSheet("QPushButton{background-color:red;\
                       color: white;   border-radius: 10px;  border: 0px;\
                       border-style: outset;}"
                       "QPushButton:hover{background-color:white; color: black;}"
                       "QPushButton:pressed{background-color:rgb(85, 170, 255);\
                       border-style: inset; }");
    remind->setStyleSheet("QPushButton{background-color:rgb(255,215,0);\
                          color: white;   border-radius: 10px;  border: 0px;\
                          border-style: outset;}"
                          "QPushButton:hover{background-color:white; color: black;}"
                          "QPushButton:pressed{background-color:rgb(85, 170, 255);\
                          border-style: inset; }");
    for(int i=0;i<9;i++)
    {
        num[i]->setStyleSheet("QPushButton{background-color:rgb(255,99,71);\
                              color: white;   border-radius: 10px;  border:0px;\
                              border-style: outset;font-size:40px;}"
                              "QPushButton:hover{background-color:white; color: black;}"
                              "QPushButton:pressed{background-color:rgb(85, 170, 255);\
                              border-style: inset;}");
    }
    dlg->setModal(true);
    dlg->show();
}

Widget::~Widget()
{
    delete ui;
    delete gm;
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter *paint=new QPainter(this);
    paint->setPen(QPen(QColor(255,106,106),4));
    paint->drawRect(30,80,540,540);
    paint->drawLine(QPoint(210,80),QPoint(210,620));
    paint->drawLine(QPoint(390,80),QPoint(390,620));
    paint->drawLine(QPoint(30,260),QPoint(570,260));
    paint->drawLine(QPoint(30,440),QPoint(570,440));
    paint->setPen(QPen(QColor(255,106,106),1));
    for(int i=1;i<=8;i++)
    {
        paint->drawLine(QPoint(30+60*i,80),QPoint(30+60*i,620));
    }
    for(int i=1;i<=8;i++)
    {
        paint->drawLine(QPoint(30,80+60*i),QPoint(570,80+60*i));
    }
    if(isstop)
        return;
    if(chosen!=QPoint(0,0))
    {
        int xx=chosen.x();
        int yy=chosen.y();
        paint->setPen(QPen(Qt::blue,4));
        paint->drawRect(30+60*(xx-1),80,60,540);
        paint->drawRect(30,80+60*(yy-1),540,60);
    }
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
        {
            if(have_flag[i][j])
            {
                paint->setPen(QPen(Qt::yellow,4));
                paint->drawRect(30+60*i,80+60*j,60,60);
            }
        }
    QFont font("Courier");
    font.setBold(true);
    QList<int> high[9][9];
    if(chosen!=QPoint(0,0))
    for(int k=0;k<gm->getnum(chosen.x(),chosen.y()).size();k++)
    {
        for(int i=0;i<9;i++)
            for(int j=0;j<9;j++)
                for(int l=0;l<gm->getnum(i+1,j+1).size();l++)
                if(gm->getnum(chosen.x(),chosen.y()).at(k)==gm->getnum(i+1,j+1).at(l))
                    high[i][j]<<l;
    }
    for(int i=1;i<=9;i++)
        for(int j=1;j<=9;j++)
        {
            if(gm->is_available(i,j))
                paint->setPen(QPen(Qt::black));
            else
                paint->setPen(QPen(Qt::red));
            if(gm->getnum(i,j).size()==1)
            {
                font.setPixelSize(30);
                paint->setFont(font);
                if(high[i-1][j-1].indexOf(0)!=-1)
                    paint->setPen(QPen(QColor(0,139,0)));
                paint->drawText(53+(i-1)*60,94+(j-1)*60,30,30,0,QString::number(gm->getnum(i,j).first()));
            }
            if(gm->getnum(i,j).size()==2)
            {
                font.setPixelSize(25);
                paint->setFont(font);
                if(high[i-1][j-1].indexOf(0)!=-1)
                    paint->setPen(QPen(QColor(0,139,0)));
                paint->drawText(40+(i-1)*60,98+(j-1)*60,25,25,0,QString::number(gm->getnum(i,j).first()));
                if(gm->is_available(i,j))
                    paint->setPen(QPen(Qt::black));
                else
                    paint->setPen(QPen(Qt::red));
                if(high[i-1][j-1].indexOf(1)!=-1)
                    paint->setPen(QPen(QColor(0,139,0)));
                paint->drawText(66+(i-1)*60,98+(j-1)*60,25,25,0,QString::number(gm->getnum(i,j).last()));
            }
            if(gm->getnum(i,j).size()==3)
            {
                font.setPixelSize(23);
                paint->setFont(font);
                if(high[i-1][j-1].indexOf(0)!=-1)
                    paint->setPen(QPen(QColor(0,139,0)));
                paint->drawText(40+(i-1)*60,90+(j-1)*60,23,23,0,QString::number(gm->getnum(i,j).first()));
                if(gm->is_available(i,j))
                    paint->setPen(QPen(Qt::black));
                else
                    paint->setPen(QPen(Qt::red));
                if(high[i-1][j-1].indexOf(1)!=-1)
                    paint->setPen(QPen(QColor(0,139,0)));
                paint->drawText(66+(i-1)*60,90+(j-1)*60,23,23,0,QString::number(gm->getnum(i,j).at(1)));
                if(gm->is_available(i,j))
                    paint->setPen(QPen(Qt::black));
                else
                    paint->setPen(QPen(Qt::red));
                if(high[i-1][j-1].indexOf(2)!=-1)
                    paint->setPen(QPen(QColor(0,139,0)));
                paint->drawText(54+(i-1)*60,113+(j-1)*60,23,23,0,QString::number(gm->getnum(i,j).last()));
            }
            if(gm->getnum(i,j).size()==4)
            {
                font.setPixelSize(20);
                paint->setFont(font);
                if(high[i-1][j-1].indexOf(0)!=-1)
                    paint->setPen(QPen(QColor(0,139,0)));
                paint->drawText(40+(i-1)*60,90+(j-1)*60,20,20,0,QString::number(gm->getnum(i,j).first()));
                if(gm->is_available(i,j))
                    paint->setPen(QPen(Qt::black));
                else
                    paint->setPen(QPen(Qt::red));
                if(high[i-1][j-1].indexOf(1)!=-1)
                    paint->setPen(QPen(QColor(0,139,0)));
                paint->drawText(67+(i-1)*60,90+(j-1)*60,20,20,0,QString::number(gm->getnum(i,j).at(1)));
                if(gm->is_available(i,j))
                    paint->setPen(QPen(Qt::black));
                else
                    paint->setPen(QPen(Qt::red));
                if(high[i-1][j-1].indexOf(2)!=-1)
                    paint->setPen(QPen(QColor(0,139,0)));
                paint->drawText(40+(i-1)*60,113+(j-1)*60,20,20,0,QString::number(gm->getnum(i,j).at(2)));
                if(gm->is_available(i,j))
                    paint->setPen(QPen(Qt::black));
                else
                    paint->setPen(QPen(Qt::red));
                if(high[i-1][j-1].indexOf(3)!=-1)
                    paint->setPen(QPen(QColor(0,139,0)));
                paint->drawText(67+(i-1)*60,113+(j-1)*60,20,20,0,QString::number(gm->getnum(i,j).last()));
            }
        }

}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton&&event->pos().x()>=30&&
            event->pos().x()<570&&event->pos().y()>=80&&event->pos().y()<620)
    {
        int cx=event->pos().x();
        int cy=event->pos().y();
        if((cx-30)/60+1==chosen.x()&&(cy-80)/60+1==chosen.y())
        {
            chosen.setX(0);
            chosen.setY(0);
        }
        else
        {
            chosen.setX((cx-30)/60+1);
            chosen.setY((cy-80)/60+1);
        }
        repaint();
    }
    else
        QWidget::mousePressEvent(event);
}

void Widget::to_deal(int ope)
{
    if(chosen!=QPoint(0,0))
        emit dealing(chosen.x(),chosen.y(),ope);
}

void Widget::redisplay()
{
    repaint();
}

void Widget::showtime(QTime t)
{
    time->display(t.toString("hh:mm:ss"));
}

void Widget::change()
{
    if(stop->text()=="暂停")
    {
        stop->setText("开始");
        isstop=1;
        repaint();
    }
    else
    {
        stop->setText("暂停");
        isstop=0;
        repaint();
    }
}

void Widget::win()
{
    QMessageBox mesbox(QMessageBox::NoIcon,QString("游戏胜利"),QString("恭喜你完成了数独游戏!"));
    if(mesbox.exec()==QMessageBox::Ok)
    dlg->exec();
}

void Widget::addflag()
{
    have_flag[chosen.x()-1][chosen.y()-1]=!have_flag[chosen.x()-1][chosen.y()-1];
    repaint();
}

void Widget::showdlg()
{
    dlg->exec();
}

void Widget::showtitle(int method)
{
    QString title=QString("数独游戏 第%1关-难度%1").arg(method+1);
    setWindowTitle(title);
}

void Widget::reminding()
{
    emit reminding(chosen.x(),chosen.y());
}
