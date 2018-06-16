#ifndef MISSILE_H
#define MISSILE_H

#include "pub.h"
#include <QRect>
#include <QList>
#include <QImage>

class QPainter;
class MainWindow;
class Tank;
class Wall;
class Missile
{
public:
    Missile(int x,int y,int w,int h,Dir dir,MainWindow* tc,bool good);
    void drawMissile(QPainter &p);
    void moveMissile();
    bool hitTank(Tank* t);
    void hitTanks(QList<Tank*> ts);
    bool hitWall(Wall* w);
    void hitWalls(QList<Wall*> ws);
    inline QRect getRect(){return QRect(x,y,w,h);}//»ńµĂ×ÔÉíĎŕ˝»µÄľŘĐÎ

    int x,y,w,h;
    Dir dir;
    bool live;
    MainWindow* tc;
    bool good;

    QImage missileImgs;

};
#endif // MISSILE_H
