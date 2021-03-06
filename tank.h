#ifndef TANK_H
#define TANK_H
#include "pub.h"
#include <QRect>
#include <QList>
#include <QImage>

class QPainter;
class MainWindow;
class Wall;
class Tank
{
public:
    Tank(int x,int y,int w,int h,MainWindow* tc,bool good,int liveValue);
    void drawTank(QPainter &p);
    void keyRelease(int key);
    void keyPress(int key);
    void moveTank(int speed);
    void fire();
    void fire(Dir tdir);

    bool TankHitWall(Wall* w);
    void TankHitWalls(QList<Wall*> ws);
    void TankHitTank(Tank* tank);
    static void init();
    inline QRect getRect(){return QRect(x,y,w,h);}

    int x,y,w,h;
    bool BU,BD,BL,BR;
    Dir dir;
    Dir ptDir;
    MainWindow* tc;
    bool good;
    bool live;
    int step;
    int xtemp,ytemp;
    int liveValue;
    int count;
    static QList<QImage> tankImgs;

};

#endif // TANK_H
