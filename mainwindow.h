#ifndef TANKCLIENT_H
#define TANKCLIENT_H

#include <QMainWindow>
#include "tank.h"
#include "missile.h"
#include <QImage>

class Explode;
class Wall;
class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
    void AllObject();


    static const int GAME_WIDTH=640;
    static const int GAME_HEIGHT=480;

    bool start;
    bool gameover,victory;
    Tank* mytank;
    QList<Missile*> missile;
    QList<Tank*> etanks;
    QList<Explode*> explodes;
    QList<Wall*> myWall;
    QList<QPushButton*> button;

    static QList<QImage> logoImgs;
    int step;

private slots:
    void pressStart();
    void pressRestart();

};

#endif // TANKCLIENT_H
