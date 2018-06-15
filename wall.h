#ifndef WALL_H
#define WALL_H
#include <QRect>
#include <QImage>

class QPainter;
class MainWindow;
class Wall
{
public:
    Wall(int x,int y,int w,int h,bool ironWall,MainWindow* tc,int liveValue);
    void drawWall(QPainter &p);
    inline QRect getRect(){return QRect(x,y,w,h);}

    int x,y,w,h;
    bool ironWall;
    bool live;
    MainWindow* tc;
    int liveValue;

    static QList<QImage> wallImgs;
};

#endif // WALL_H
