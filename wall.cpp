#include "wall.h"
#include <QtGui>
#include "mainwindow.h"
QList<QImage> Wall::wallImgs;

Wall::Wall(int x,int y,int w,int h,int choose,MainWindow* tc,int liveValue)
{
    this->x=x;
    this->y=y;
    this->w=w;
    this->h=h;
    this->tc=tc;
    this->choose=choose;
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

    if(choose==0)
    {
        p.drawImage(x,y,Wall::wallImgs[0]);
    }
    else if(choose==1)
    {
       p.drawImage(x,y,Wall::wallImgs[1]);
    }
    else if(choose==2)
    {
        p.drawImage(x,y,Wall::wallImgs[2]);
    }
    else
    {
        p.drawImage(x,y,Wall::wallImgs[3]);
    }
}
