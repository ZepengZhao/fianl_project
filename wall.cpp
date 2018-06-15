#include "wall.h"
#include <QtGui>
#include "mainwindow.h"
QList<QImage> Wall::wallImgs;

Wall::Wall(int x,int y,int w,int h,bool ironWall,MainWindow* tc,int liveValue)
{
    this->x=x;
    this->y=y;
    this->w=w;
    this->h=h;
    this->tc=tc;
    this->ironWall=ironWall;
    this->live=true;
    this->liveValue=liveValue;
}
void Wall::drawWall(QPainter &p)
{
    if(!live)
    {
        tc->myWall.removeOne(this);
        return;
    }
    if(ironWall)
    {
        p.drawImage(x,y,Wall::wallImgs[1]);
    }
    else
    {
       p.drawImage(x,y,Wall::wallImgs[0]);
    }
}
