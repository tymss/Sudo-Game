#include "selectdlg.h"
#include "ui_selectdlg.h"

selectdlg::selectdlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::selectdlg)
{
    ui->setupUi(this);
    setWindowTitle("关卡选择");
    box=new QComboBox(this);
    start=new QPushButton("开始",this);
    end=new QPushButton("退出",this);
    mes=new QLabel("请选择关卡:",this);
    box->setMaxCount(10);
    box->setInsertPolicy(QComboBox::InsertAtBottom);
    for(int i=1;i<=10;i++)
    box->addItem(QString("关卡%1-难度系数%1").arg(i));
    setFixedSize(260,250);
    setAutoFillBackground(true);
    QPalette pal;
    pal.setBrush(QPalette::Background,QBrush(QPixmap(":/image/image/back0.png")));
    setPalette(pal);
    move((QApplication::desktop()->width()-width())/2,(QApplication::desktop()->height()-height())/2);
    mes->setFixedSize(200,50);
    mes->move(30,20);
    box->setFixedSize(200,30);
    box->move(30,70);
    start->setFixedSize(200,40);
    end->setFixedSize(200,40);
    start->move(30,120);
    end->move(30,170);
    setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
    connect(end,SIGNAL(clicked(bool)),this,SIGNAL(to_close()));
    connect(start,SIGNAL(clicked(bool)),this,SLOT(starting()));
    QFont font;
    font.setFamily("华文琥珀");
    font.setPointSize(10);
//    font.setBold(true);
    this->setFont(font);
    end->setStyleSheet("QPushButton{background-color:rgb(85, 170, 255);\
                        color: white;   border-radius: 10px;  border: 0px;\
                        border-style: outset;}"
                        "QPushButton:hover{background-color:white; color: black;}"
                        "QPushButton:pressed{background-color:rgb(85, 170, 255);\
                        border-style: inset; }");
    start->setStyleSheet("QPushButton{background-color:rgb(85, 170, 255);\
                        color: white;   border-radius: 10px;  border: 0px;\
                        border-style: outset;}"
                        "QPushButton:hover{background-color:white; color: black;}"
                        "QPushButton:pressed{background-color:rgb(85, 170, 255);\
                        border-style: inset; }");
    box->setStyleSheet("QComboBox{border-radius:6px;color:darkblue;border:0px; }"
                       "QComboBox::drop-down{style:Macintosh style;min-width:25px;}");
}

selectdlg::~selectdlg()
{
    delete ui;
}
void selectdlg::starting()
{
    int n=box->currentIndex();
    emit to_start(n);
    close();
}

