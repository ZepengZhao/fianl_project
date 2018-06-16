#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
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



    bool start;
    bool gameover,victory;
    Tank* mytank;
    QList<Missile*> missile;
    QList<Tank*> etanks;
    QList<Explode*> explodes;
    QList<Wall*> myWall;
    QList<QPushButton*> button;

    static QList<QImage> logoImgs;

private slots:
    void Start();
    void Restart();

};

#endif
