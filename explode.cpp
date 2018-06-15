#include "explode.h"
#include <QPainter>
#include "mainwindow.h"
QList<QImage> Explode::explodeImgs;

Explode::Explode(int x,int y,MainWindow* tc)
{
    this->x=x;
    this->y=y;
    live=true;
    i=0;
    int is[10]={10,12,15,20,23,25,27,30,32,35};
    for(int i=0;i<10;i++)
    {
        dis[i]=is[i];
    }
    this->tc=tc;
}
void Explode::drawExplode(QPainter &p)
{
    if(!live)
    {
        tc->explodes.removeOne(this);
        return ;
    }
    p.drawImage(x,y,explodeImgs[i]);
    i++;
    if(i==11)
    {
        i=0;
        live=false;
    }
}
