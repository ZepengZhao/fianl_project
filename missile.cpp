#include "missile.h"
#include <QtGui>
#include "mainwindow.h"
#include <QList>
#include "tank.h"
#include "explode.h"
#include "wall.h"
QList<QImage> Missile::missileImgs;

Missile::Missile(int x,int y,int w,int h,Dir dir,MainWindow* tc,bool good)
{
  this->x=x;
  this->y=y;
  this->w=w;
  this->h=h;
  this->dir=dir;
  live=true;
  this->tc=tc;
  this->good=good;
}

void Missile::drawMissile(QPainter &p)
{
    if(!live)
    {
        tc->missile.removeOne(this);
        return ;
    }
    switch(dir)
    {
        case U: p.drawImage(x,y,missileImgs[0]);break;
        case D: p.drawImage(x,y,missileImgs[1]);break;
        case L: p.drawImage(x,y,missileImgs[2]);break;
        case R: p.drawImage(x,y,missileImgs[3]);break;

        case LU: p.drawImage(x,y,missileImgs[4]);break;
        case LD: p.drawImage(x,y,missileImgs[5]);break;
        case RU: p.drawImage(x,y,missileImgs[6]);break;
        case RD: p.drawImage(x,y,missileImgs[7]);break;
        default:break;
    }
    moveMissile();
}

void Missile::moveMissile()
{
    switch(dir)
    {
        case U: y-=15;break;
        case D: y+=15;break;
        case L: x-=15;break;
        case R: x+=15;break;

        case LU: x-=15;y-=15;break;
        case LD: x-=15;y+=15;break;
        case RU: x+=15;y-=15;break;
        case RD: x+=15;y+=15;break;
        default:break;
    }
    if(x<=0||y<=0||x>=MainWindow::GAME_WIDTH||y>=MainWindow::GAME_HEIGHT)live=false;
}
bool Missile::hitTank(Tank* t)
{
    if(live&&t->live&&good!=t->good&&this->getRect().intersects(t->getRect()))
    {
        live=false;
        t->liveValue-=20;
        if( t->liveValue==0)
        {
            t->live=false;
            Explode* e=new Explode(x,y,tc);//´´˝¨±¬Ő¨¶ÔĎó
            tc->explodes.push_back(e);
            return true;
        }
    }
    return false;
}
void Missile::hitTanks(QList<Tank*> ts)
{
    for(int i=0;i<ts.size();i++)
    {
        if(hitTank(ts[i]))return ;
    }
}

bool Missile::hitWall(Wall* w)
{

    if(live&&w->ironWall&&this->getRect().intersects(w->getRect()))
    {
        if(!good)
        {
            live=false;
            return true;
        }
    }
    if(live&&!(w->ironWall)&&this->getRect().intersects(w->getRect()))
    {
        live=false;
        w->liveValue-=25;
        if(!good&&w->liveValue==0)
        {
            w->live=false;
            return true;
        }

    }

    return false;
}
void Missile::hitWalls(QList<Wall*> ws)
{
    for(int i=0;i<ws.size();i++)
    {
        if(hitWall(ws[i]))return;
    }
}

