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
    start=false;
    gameover=false;
    victory=false;
    Tank::init();
    setWindowTitle(tr("̹tank war"));
    setFixedSize(640,480);

    move(100,100);
    AllObject();

    QPushButton* restartGame=new QPushButton(tr("restart game"),this);
    button.push_back(restartGame);
    QPushButton* startGame=new QPushButton(tr("start game"),this);
    button.push_back(startGame);
    QPushButton* exitGame=new QPushButton(tr("exit"),this);
    button.push_back(exitGame);
    button[0]->setGeometry(75,360,130,50);
    button[1]->setGeometry(255,360,130,50);
    button[2]->setGeometry(435,360,130,50);
    connect(button[0],SIGNAL(clicked()),this,SLOT(pressRestart()));
    connect(button[1],SIGNAL(clicked()),this,SLOT(pressStart()));
    connect(button[2],SIGNAL(clicked()),this,SLOT(close()));

    startTimer(25);
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
        p.drawImage(140,150,logoImgs[1]);
        else if(victory)
        {
            p.drawImage(140,150,logoImgs[2]);
        }
        else
        p.drawImage(70,0,logoImgs[0]);

        if(gameover||victory)
        {
            button[0]->show();
            button[1]->hide();
            button[2]->show();
        }
        else
        {
            for(int i=0;i<button.size();i++)
            {
                button[i]->show();
            }
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
   else
   {
       switch(e->key())
       {
           case Qt::Key_F1: mytank->keyPress(Qt::Key_F1);break;
           case Qt::Key_Escape: mytank->keyPress(Qt::Key_Escape);break;
           default: break;
       }
   }
}
void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
   if(mytank->live)
    mytank->keyRelease(e->key());
}
void MainWindow::AllObject()
{
    mytank=new Tank(300,450,30,30,this,true,100);
    for(int i=0;i<8;i++)
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
        Wall* w=new Wall(30*i,330,30,30,2,this,100);
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
    for(int i=0;i<7;i++)
    {
        Wall* w=new Wall(30+30*i,390,30,30,1,this,100);
        myWall.push_back(w);
    }
    for(int i=0;i<7;i++)
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

}

void MainWindow::pressStart()
{
    start=!start;
    if(!(start))
    {
        button[1]->setText(QObject::tr("јМРшУОП·"));
    }

}

void MainWindow::pressRestart()
{
    while(missile.size())
        missile.removeOne(missile[0]);
    while(etanks.size())
        etanks.removeOne(etanks[0]);
    while(myWall.size())
        myWall.removeOne(myWall[0]);
    AllObject();
    start=true;
    gameover=false;

}


