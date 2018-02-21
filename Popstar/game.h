#ifndef GAME_H
#define GAME_H

#include "main.h"

class buttonAni;
class scoreAdder;
class timeCounter;
class soundControl;

/*
  class gamewindow:
    The main window of the game.
    Handles and processes the calculation while gaming.
    Receives events from its children.
    */
class gameWindow :public QWidget{
private:
    QImage *bkpic, *preIcon[10];
        // background picture and square icons.
        // loaded from files before the game starts.
    int width,height;
        // window size.
    int leftX,leftY,rightX,rightY;
        // actual game size.
    /*
      struct node
        restores the information of squares.
        */
    struct node{
        int color;
            // color:
            //  0 - red
            //  1 - yellow
            //  2 - blue
            //  3 - green
            //  4 - purple
        bool del;
            // has been deleted or not.
        int nowx, nowy;
            // now position.
            // in most times it equals to destx/desty.
            // when the square moves, this value changes by time in order to perform animation.
        int destx, desty;
            // destination position.
    };
    node* Map[21][21];
        // the game map.
    int row,col;
        // the number of rows and columns.
    int sizW,sizH;
        // the size of a square.
        // dymatically changes to adjust row/col changes.
    int colorCnt;
        // the number of colors.
    int startCnt;
        // the number of milliseconds before start.
    int locked;
        // the number of squares that is not ready.
    int level;
    int timer;
        // the identification of startTimer().
    long long score, destscore;
        // destscore is used in gameMode 1.
    int gameMode;
    bool gameOver;
    timeCounter* tC;
        // the time counter used in gameMode 3.
    soundControl* sC;
        // the global sound controller.
    buttonAni* btnMenu;
        // the return button.
    QSound* bgm;
        // the background music
public:
    gameWindow(QWidget* ,int);
    ~gameWindow();
    void init();
    void start();
    void restart();
    void choose(int,int,int,int);
        // calculate the changes when clicked on a square.
    inline bool testEmptyCol(int);
        // return true if a column is empty.
    inline bool testCannotMove();
        // return true if there is no square to choose.
    inline int getscore(int);
    void showBoard();
    void showScore();
    void showFinal();
        // shows the gameOver/nextLevel board.
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void timerEvent(QTimerEvent *);
    bool event(QEvent *);
friend class sqrSmasher;
friend class sqrRotater;
};

/*
  class scoreAdder:
    Handles the animation of the score adding to the lefttop/righttop.
    */
class scoreAdder:public QWidget{
private:
    QString Text;
    int nowx,nowy,destx,desty;
    int dx,dy;
public:
    scoreAdder(QWidget*,int,int,int,int,QString);
protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
};

/*
  class timerCounter:
    Counts the time, displays it in the righttop.
    sends TIMECOUNTER_TIMESUP event to gameWindow when time's up.
    */
class timeCounter:public QWidget{
private:
    int timeCnt;
public:
    timeCounter(QWidget*,int);
    QString convert(int);
    void add(int);
protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
};

/*
  class scoreDropper:
    Handles messages like "GameOver YourScore:xxx" dropping down.
    */
class scoreDropper:public QWidget{
private:
    QImage bg;
    QString Text1,Text2,Text3;
    int h[50], cnt, now, delta;
    bool type;
public:
    scoreDropper(QWidget*,QString,QString,QString="",bool=false);
protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void mouseReleaseEvent(QMouseEvent *);
};

/*
  class sqrSmasher:
    Handles the animation when a square is smashed.
    */
class sqrSmasher:public QWidget{
private:
    int x[50], y[50], cnt, now;
    qreal o[50], opa;
    int delayms;
    QImage* img;
public:
    sqrSmasher(gameWindow*,int,int,int=0);
protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
};

/*
  class sqrRotater:
    Handles the animation before the game starts.
    */
class sqrRotater:public QWidget{
private:
    int x, y, w, h, sizw[50], sizh[50], cnt, now;
    int rot[50];
    int delayms;
    QImage* img;
public:
    sqrRotater(gameWindow*,int,int,int);
protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
};

#endif
