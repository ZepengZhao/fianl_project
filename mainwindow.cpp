#include "mainwindow.h"
#include <QtGui>
#include "tank.h"
#include "missile.h"
#include "explode.h"
#include "wall.h"
#include<QPushButton>
QList<QImage> MainWindow::logoImgs;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mainmenu=true;
    start=false;
    gameover=false;
    victory=false;
    guideline = false;
    Tank::init();
    setWindowTitle("̹tank war");
    setFixedSize(640,480);
    AllObject();

    QPushButton* restartGame=new QPushButton("restart game",this);
    button.push_back(restartGame);
    QPushButton* startGame=new QPushButton("start game",this);
    button.push_back(startGame);
    QPushButton* exitGame=new QPushButton("exit",this);
    button.push_back(exitGame);
    QPushButton* guideline=new QPushButton("guideline",this);
    button.push_back(guideline);
    QPushButton* mainmenu=new QPushButton("mainmenu",this);
    button.push_back(mainmenu);
    button[0]->setGeometry(75,360,130,50);
    button[1]->setGeometry(255,360,130,50);
    button[2]->setGeometry(435,360,130,50);
    button[3]->setGeometry(75,360,130,50);
    button[4]->setGeometry(255,360,130,50);
    connect(button[0],SIGNAL(clicked()),this,SLOT(Restart()));
    connect(button[1],SIGNAL(clicked()),this,SLOT(Start()));
    connect(button[2],SIGNAL(clicked()),this,SLOT(close()));
    connect(button[3],SIGNAL(clicked()),this,SLOT(Guideline()));
    connect(button[4],SIGNAL(clicked()),this,SLOT(Mainmenu()));

    startTimer(30);
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    if(start)
    {
        for(int i=0;i<button.size();i++)
        {
            button[i]->hide();
        }


        for(int i=0;i<missile.size();i++)
        {
            missile[i]->hitTanks(etanks);
            missile[i]->hitTank(mytank);
            missile[i]->hitWalls(myWall);
            missile[i]->drawMissile(p);
        }

        mytank->TankHitWalls(myWall);

        mytank->drawTank(p);
        for(int i=0;i<etanks.size();i++)
        {
           etanks[i]->TankHitWalls(myWall);

            etanks[i]->drawTank(p);

        }
        for(int i=0;i<explodes.size();i++)
        {

            explodes[i]->drawExplode(p);
        }

        for(int i=0;i<myWall.size();i++)
        {
            myWall[i]->drawWall(p);
        }

        if(!mytank->live)
        {
            start=false;
            gameover=true;
        }
        if(etanks.size()==0)
        {
            start=false;
            victory=true;

        }
    }
    else
    {
        if(gameover)
        p.drawImage(140,30,logoImgs[1]);
        else if(victory)
        p.drawImage(140,30,logoImgs[2]);
        else if(mainmenu)
        p.drawImage(70,0,logoImgs[0]);
        else if(guideline)
        p.drawImage(70,30,logoImgs[3]);




        if(gameover||victory)
        {
            button[4]->setGeometry(255,360,130,50);
            button[0]->show();
            button[1]->hide();
            button[2]->show();
            button[3]->hide();
            button[4]->show();
        }

        else if(mainmenu)
        {
            button[4]->setGeometry(255,360,130,50);
            button[0]->hide();
            button[1]->show();
            button[2]->show();
            button[3]->show();
            button[4]->hide();
        }
        else if(guideline)
        {
            button[4]->setGeometry(75,360,130,50);
        }

    }
}

void MainWindow::timerEvent(QTimerEvent *)
{
    update();
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
   if(mytank->live)
    mytank->keyPress(e->key());
}
void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
   if(mytank->live)
    mytank->keyRelease(e->key());
}
void MainWindow::AllObject()
{
    mytank=new Tank(300,450,30,30,this,true,100);
    for(int i=0;i<7;i++)
    {
        Tank* t=new Tank(40+50*i,20,30,30,this,false,100);
        etanks.push_back(t);
    }

    for(int i=0;i<13;i++)
    {
        if(i==4)
            i=i+5;
        Wall* w=new Wall(120+30*i,220,30,30,1,this,100);
        myWall.push_back(w);
    }
    for(int i=1;i<20;i++)
    {
        Wall* w=new Wall(30*i,300,30,30,2,this,100);
        myWall.push_back(w);
    }
    for(int i=0;i<18;i++)
    {
        Wall* w=new Wall(0,30*i,30,30,2,this,100);
        myWall.push_back(w);
    }
    for(int i=0;i<5;i++)
    {
        Wall* w=new Wall(210+30*i,390,30,30,0,this,100);
        myWall.push_back(w);
    }

    for(int i=0;i<6;i++)
    {
        Wall* w=new Wall(30+30*i,390,30,30,1,this,100);
        myWall.push_back(w);
    }
    for(int i=0;i<6;i++)
    {
        Wall* w=new Wall(360+30*i,390,30,30,1,this,100);
        myWall.push_back(w);
    }
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<16;j++)
        {
        Wall* w=new Wall(640-30*i,450-30*j,30,30,3,this,100);
        myWall.push_back(w);
        }
    }

    {
        Wall* w=new Wall(120,120,30,30,0,this,100);
        myWall.push_back(w);
    }
    {
        Wall* w=new Wall(360,120,30,30,0,this,100);
        myWall.push_back(w);
    }
    \
}

void MainWindow::Guideline()
{
    start =false;
    gameover= false;
    mainmenu = false;
    victory = false;
    guideline= true;
    button[0]->hide();
    button[1]->show();
    button[2]->show();
    button[3]->hide();
    button[4]->show();
}

void MainWindow::Mainmenu()
{
    start =false;
    gameover= false;
    mainmenu = true;
    victory = false;
    guideline= false;
}

void MainWindow::Start()
{
    while(missile.size())
        missile.removeOne(missile[0]);
    while(etanks.size())
        etanks.removeOne(etanks[0]);
    while(myWall.size())
        myWall.removeOne(myWall[0]);
    AllObject();
    mainmenu= false;
    start=true;
    gameover=false;
    victory = false;
    guideline= false;
}

void MainWindow::Restart()
{
    while(missile.size())
        missile.removeOne(missile[0]);
    while(etanks.size())
        etanks.removeOne(etanks[0]);
    while(myWall.size())
        myWall.removeOne(myWall[0]);
    AllObject();
    mainmenu= false;
    start=true;
    gameover=false;
    victory = false;
    guideline= false;

}


