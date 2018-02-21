#ifndef START2_H
#define START2_H

#include "main.h"

class gameWindow;
class shiningStar;
class titleAni;
class buttonAni;
class singCing;
class soundControl;
class helpMenu;
class aboutMenu;

class mainWindow :public QWidget{
private:
    shiningStar* star;
    titleAni* title;
    buttonAni* btn1,* btn2,* btn3,* btn4,* btn5,* btn6;
    singCing* sing;
    helpMenu* help;
    aboutMenu* about;
    gameWindow* nowGame;
public:
    mainWindow();
    soundControl* sC;
    int nowBtn, nowMode;
protected:
    void paintEvent(QPaintEvent *);
    bool event(QEvent *);
};

class shiningStar :public QWidget{
private:
    QImage *preload[20];
    int h[210], cnt, now;
public:
    shiningStar(QWidget *);
protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
};

class titleAni :public QWidget{
private:
    const QString Text;
    int now, cnt, h[50], delta;
public:
    titleAni(QWidget *);
    void in();
    void out();
protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
};

class buttonAni :public QWidget{
private:
    const QString Text;
    int nowy, desty, x, deltay, y1, y2, btnNo;
    int &nowBtn, &nowMode;
public:
    buttonAni(mainWindow *,QString,int,int);
    void in();
    void out();
protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
};

class singCing :public QWidget{
private:
    const QString Text;
    QImage img;
    int h[40],now,cnt,delta;
public:
    singCing(QWidget *);
    void in();
    void out();
protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
};

class loading :public QWidget{
private:
    const QString Text;
    bool visible;
public:
    loading(QWidget *p,QString t):QWidget(p), visible(true), Text(t){

    }
};

#endif
