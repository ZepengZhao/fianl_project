#ifndef EXPLODE_H
#define EXPLODE_H
#include <QList>
#include <QImage>
class QPainter;
class MainWindow;
class Explode
{
public:
    Explode(int x,int y,MainWindow* tc);
    void drawExplode(QPainter &p);

    int x,y;
    bool live;
    int dis[10];
    int i;
    MainWindow* tc;

    static QList<QImage> explodeImgs;
};

#endif // EXPLODE_H
