#include <game.h>
#include <QDebug>
game::game()
{
    cre=new creator;
    time.setHMS(0,0,0);
    timer=new QTimer;
    timer->setInterval(1000);
    timer->setSingleShot(false);
    connect(timer,SIGNAL(timeout()),this,SLOT(times()));
}
QList<int> game::getnum(int x, int y)
{
    return number[x-1][y-1];
}
void game::deal(int x, int y, int ope)
{
    if(available[x-1][y-1])
    {
        sound=new QSound(":/sound/sound/operate.wav",this);
        sound->play();
        if(ope==0)
        {
            opelist.append(operate(x,y,number[x-1][y-1]));
            number[x-1][y-1].clear();
        }
        else
        {
            if(number[x-1][y-1].size()==4)
                return;
            number[x-1][y-1].append(ope);
            if(win())
            {
                timer->stop();
                sound=new QSound(":/sound/sound/win.wav",this);
                sound->play();
                emit winning();
            }
            opelist.append(operate(x,y,ope));
        }
        if(opelist.size()>10)
            opelist.removeFirst();
        emit display();
    }
    else
        return;
}
void game::last()
{
    if(!opelist.isEmpty())
    {
        sound=new QSound(":/sound/sound/operate.wav",this);
        sound->play();
        operate last_ope=opelist.last();
        next_ope=last_ope;
        opelist.removeLast();
        if(last_ope.ope)
            number[last_ope.position.x()-1][last_ope.position.y()-1].removeLast();
        else
            number[last_ope.position.x()-1][last_ope.position.y()-1]=last_ope.removing;
        emit display();
    }
    else
        return;
}
void game::next()
{
    if(next_ope.position!=QPoint(0,0))
    {
        operate op=next_ope;
        next_ope.position.setX(0);
        next_ope.position.setY(0);
        deal(op.position.x(),op.position.y(),op.ope);
    }
    else
        return;
}
bool game::is_available(int x, int y)
{
    return available[x-1][y-1];
}
bool game::win()
{
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
        {
            if(number[i][j].size()!=1)
                return false;
        }
    for(int i=0;i<9;i++)
    {
        bool num[10]={0};
        for(int j=0;j<9;j++)
        {
            if(num[number[i][j].first()])
                return false;
            num[number[i][j].first()]=1;
        }
    }
    for(int i=0;i<9;i++)
    {
        bool num[10]={0};
        for(int j=0;j<9;j++)
        {
            if(num[number[j][i].first()])
                return false;
            num[number[j][i].first()]=1;
        }
    }
    for(int i=0;i<9;i++)
    {
        bool num[10]={0};
        for(int j=0;j<9;j++)
        {
            if(num[number[3*(i%3)+j%3][3*(i/3)+j/3].first()])
                    return false;
            num[number[3*(i%3)+j%3][3*(i/3)+j/3].first()]=1;
        }
    }
    return true;
}
void game::times()
{
    time=time.addSecs(1);
    emit time_display(time);
}
void game::stop()
{
    if(timer->isActive())
        timer->stop();
    else
        timer->start();
}
void game::restart()
{
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
        {
            number[i][j].clear();
            if(!available[i][j])
                number[i][j]<<result[i][j];
        }
    time.setHMS(0,0,0);
    timer->start();
    emit display();
}

void game::reminder(int x, int y)
{
    if(available[x-1][y-1]&&number[x-1][y-1].isEmpty())
        deal(x,y,result[x-1][y-1]);
}
void game::initial(int _method)
{
    sound=new QSound(":/sound/sound/start.wav",this);
    sound->play();
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            available[i][j]=1;
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            number[i][j].clear();
    time.setHMS(0,0,0);
    timer->start();
    cre->create();
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
        {
            result[i][j]=cre->sudo_cre(i,j);
        }
    int p=75-_method*5;
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
        {
            int p0=qrand()%100;
            if(p0<p)
            {
                available[i][j]=0;
                number[i][j]<<result[i][j];
            }
        }
    emit display();
}
game::~game()
{
    delete timer;
}
