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
    step=0;
    start=false;
    gameover=false;
    victory=false;
    Tank::init();
    setWindowTitle(tr("̹tank"));
    setFixedSize(GAME_WIDTH,GAME_HEIGHT);

    move(100,100);
    AllObject();

    QPushButton* restartGame=new QPushButton(tr("restart game"),this);
    button.push_back(restartGame);
    QPushButton* startGame=new QPushButton(tr("start game"),this);
    button.push_back(startGame);
    QPushButton* exitGame=new QPushButton(tr("exit"),this);
    button.push_back(exitGame);
    button[0]->setGeometry(75,100,130,50);
    button[1]->setGeometry(255,100,130,50);
    button[2]->setGeometry(435,100,130,50);
    connect(button[0],SIGNAL(clicked()),this,SLOT(pressRestart()));
    connect(button[1],SIGNAL(clicked()),this,SLOT(pressStart()));
    connect(button[2],SIGNAL(clicked()),this,SLOT(close()));

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
        mytank->drawTank(p);
        mytank->TankHitWalls(myWall);

        for(int i=0;i<missile.size();i++)
        {
            missile[i]->hitTanks(etanks);
            missile[i]->hitTank(mytank);
            missile[i]->hitWalls(myWall);
            missile[i]->drawMissile(p);
        }
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
        if(myWall.size()==0||!mytank->live)
        {
            start=false;
            gameover=true;
            step=0;
        }
        if(etanks.size()==0)
        {
            start=false;
            victory=true;
            step=0;
        }
    }
    else
    {
        if(gameover)
        p.drawImage(140,400-3*step,logoImgs[1]);
        else if(victory)
        {
            p.drawImage(140,400-3*step,logoImgs[2]);
        }
        else
        p.drawImage(140,400-3*step,MainWindow::logoImgs[0]);
        step++;
        if(step>=80)step=80;
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
    for(int i=0;i<10;i++)
    {
        Tank* t=new Tank(40+50*i,20,30,30,this,false,100);
        etanks.push_back(t);
    }

    for(int i=0;i<13;i++)
    {
        if(i==4)i=i+5;
        Wall* w=new Wall(120+30*i,220,30,30,true,this,100);
        myWall.push_back(w);
    }
    for(int i=0;i<5;i++)
    {
        Wall* w=new Wall(240+30*i,310,30,30,true,this,100);
        myWall.push_back(w);
    }
    for(int j=0;j<3;j++)
    {
        for(int i=0;i<5;i++)
        {
            if(j==2)i=4;
            Wall* w=new Wall(240+30*i,390+30*j,30,30,false,this,100);
            myWall.push_back(w);
            if(j==1)i=i+3;
        }

    }
}

void MainWindow::pressStart()
{
     mytank->keyPress(Qt::Key_F2);
}

void MainWindow::pressRestart()
{
   mytank->keyPress(Qt::Key_F1);
}

