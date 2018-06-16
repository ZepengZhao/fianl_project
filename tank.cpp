#include "pub.h"
#include "tank.h"
#include <QtGui>
#include "missile.h"
#include "mainwindow.h"
#include "explode.h"
#include "wall.h"
#include<QPushButton>
#include <QImage>
#include <QTime>

QList<QImage> Tank::tankImgs;
Tank::Tank(int x,int y,int w,int h,MainWindow* tc,bool good,int liveValue)
{
  this->x=x;
  this->y=y;
  this->w=w;
  this->h=h;
  BU=BD=BL=BR=false;
  this->tc=tc;
  dir=STOP;
  ptDir=U;
  this->good=good;
  live=true;
  step=0;
  xtemp=ytemp=0;
  count=8;
  this->liveValue=liveValue;
}

void Tank::drawTank(QPainter &p)
{
    if(!live)
    {
        tc->etanks.removeOne(this);
        return ;
    }
    if(dir!=STOP)
        ptDir=dir;
    switch(ptDir)
    {
        case U: p.drawImage(x,y,tankImgs[0]);break;
        case D: p.drawImage(x,y,tankImgs[1]);break;
        case L: p.drawImage(x,y,tankImgs[2]);break;
        case R: p.drawImage(x,y,tankImgs[3]);break;

        case LU: p.drawImage(x,y,tankImgs[4]);break;
        case LD: p.drawImage(x,y,tankImgs[5]);break;
        case RU: p.drawImage(x,y,tankImgs[6]);break;
        case RD: p.drawImage(x,y,tankImgs[7]);break;
        default:break;
    }

    p.setBrush(Qt::black);
    p.drawRect(x,y,33,5);
    if(this->good)
    {
        p.setBrush(Qt::red);
        p.drawRect(x,y,liveValue/3,5);
    }
    else
    {
        p.setBrush(Qt::green);
        p.drawRect(x,y,liveValue/3,5);
    }
}


void Tank::keyPress(int key)
{
    switch(key)
    {
        case Qt::Key_W: BU=true;break;
        case Qt::Key_S: BD=true;break;
        case Qt::Key_A: BL=true;break;
        case Qt::Key_D: BR=true;break;
        case Qt::Key_J: fire();break;

        default:break;
    }
    if(BU&&!BD&&!BL&&!BR)dir=U;
    else if(!BU&&BD&&!BL&&!BR)dir=D;
    else if(!BU&&!BD&&BL&&!BR)dir=L;
    else if(!BU&&!BD&&!BL&&BR)dir=R;

    else if(BU&&!BD&&BL&&!BR)dir=LU;
    else if(!BU&&BD&&BL&&!BR)dir=LD;
    else if(BU&&!BD&&!BL&&BR)dir=RU;
    else if(!BU&&BD&&!BL&&BR)dir=RD;
    else dir=STOP;
}

void Tank::keyRelease(int key)
{
    switch(key)
    {
        case Qt::Key_W: BU=false;break;
        case Qt::Key_S: BD=false;break;
        case Qt::Key_A: BL=false;break;
        case Qt::Key_D: BR=false;break;
        default:break;
    }
    if(BU&&!BD&&!BL&&!BR)dir=U;
    else if(!BU&&BD&&!BL&&!BR)dir=D;
    else if(!BU&&!BD&&BL&&!BR)dir=L;
    else if(!BU&&!BD&&!BL&&BR)dir=R;


    else if(BU&&!BD&&BL&&!BR)dir=LU;
    else if(!BU&&BD&&BL&&!BR)dir=LD;
    else if(BU&&!BD&&!BL&&BR)dir=RU;
    else if(!BU&&BD&&!BL&&BR)dir=RD;
    else dir=STOP;

}


bool Tank::TankHitWall(Wall* w)
{
    if(live&&getRect().intersects(w->getRect())&&(w->choose==0||w->choose==1))
    {
        x=xtemp;
        y=ytemp;
    }
    if(live&&getRect().intersects(w->getRect())&&w->choose==2)
    {
       // moveTank(5);
       return true;


    }
    if(live&&getRect().intersects(w->getRect())&&w->choose==3)
    {

        return true;

    }

   return false;

}

void Tank::TankHitWalls(QList<Wall*> ws)
{
    moveTank(5);
    for(int i=0;i<ws.size();i++)
    {
        if(TankHitWall(ws[i]))
        {
           return;
        }
    }
}

void Tank::moveTank(int speed)
{
    xtemp=x;
    ytemp=y;

    switch(dir)
    {
        case U: y-=speed;break;
        case D: y+=speed;break;
        case L: x-=speed;break;
        case R: x+=speed;break;


        case LU: x-=speed;y-=speed;break;
        case LD: x-=speed;y+=speed;break;
        case RU: x+=speed;y-=speed;break;
        case RD: x+=speed;y+=speed;break;

        default:break;
    }

    if(x<=0)x=0;
    if(y<=0)y=0;
    if(x>=640-w)x=640-w;
    if(y>=480-h)y=480-h;
    if(!good)
    {
        if(qrand()%20>18)fire();
        if(step==0)
        {
            dir=Dir(qrand()%9);
            step=qrand()%15+10;
        }
       step--;
    }
}

void Tank::fire()
{
    int mw=10;
    int mh=10;
    int mx=x+w/2-mw/2;
    int my=y+h/2-mh/2;
    Missile* m=new Missile(mx,my,mw,mh,ptDir,tc,good);
    tc->missile.push_back(m);
}
void  Tank::fire(Dir tdir)
{
    int mw=10;
    int mh=10;
    int mx=x+w/2-mw/2;
    int my=y+h/2-mh/2;
    Missile* m=new Missile(mx,my,mw,mh,tdir,tc,good);
    tc->missile.push_back(m);
}



void Tank::init()
{
    tankImgs.push_back(QImage(":images/tU.gif"));
    tankImgs.push_back(QImage(":images/tD.gif"));
    tankImgs.push_back(QImage(":images/tL.gif"));
    tankImgs.push_back(QImage(":images/tR.gif"));
    tankImgs.push_back(QImage(":images/tLU.gif"));
    tankImgs.push_back(QImage(":images/tLD.gif"));
    tankImgs.push_back(QImage(":images/tRU.gif"));
    tankImgs.push_back(QImage(":images/tRD.gif"));

    Explode::explodeImgs.push_back(QImage(":images/0.gif"));
    Explode::explodeImgs.push_back(QImage(":images/1.gif"));
    Explode::explodeImgs.push_back(QImage(":images/2.gif"));
    Explode::explodeImgs.push_back(QImage(":images/3.gif"));
    Explode::explodeImgs.push_back(QImage(":images/4.gif"));
    Explode::explodeImgs.push_back(QImage(":images/5.gif"));
    Explode::explodeImgs.push_back(QImage(":images/6.gif"));
    Explode::explodeImgs.push_back(QImage(":images/7.gif"));
    Explode::explodeImgs.push_back(QImage(":images/8.gif"));
    Explode::explodeImgs.push_back(QImage(":images/9.gif"));
    Explode::explodeImgs.push_back(QImage(":images/10.gif"));

    Wall::wallImgs.push_back(QImage(":images/wall0.bmp"));
    Wall::wallImgs.push_back(QImage(":images/wall1.bmp"));
    Wall::wallImgs.push_back(QImage(":images/wall2.bmp"));
    Wall::wallImgs.push_back(QImage(":images/wall3.bmp"));

    MainWindow::logoImgs.push_back(QImage(":images/logo.jpg"));
    MainWindow::logoImgs.push_back(QImage(":images/gameover.png"));
    MainWindow::logoImgs.push_back(QImage(":images/victory.png"));
}
