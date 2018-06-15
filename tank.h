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
    void moveTank();
    void fire();
    void fire(Dir tdir);
    void superfire();//żŞ´óŐĐ

    bool TankHitWall(Wall* w); //Ľě˛âĚążËşÍÇ˝±ÚĘÇ·ńĹö×˛
    void TankHitWalls(QList<Wall*> ws);

    static void init();
    inline QRect getRect(){return QRect(x,y,w,h);}//»ńµĂ×ÔÉíĎŕ˝»µÄľŘĐÎ

    int x,y,w,h;
    bool BU,BD,BL,BR;
    Dir dir;
    Dir ptDir;
    MainWindow* tc;
    bool good;
    bool live;
    int step;
    int xtemp,ytemp;//ÓĂÓÚĽÇÂĽĚążËÉĎ´ÎµÄÎ»ÖĂ
    int liveValue;
    int count;//ĽÇÂĽ´óŐĐ´ÎĘý
    static QList<QImage> tankImgs;

};

#endif // TANK_H
