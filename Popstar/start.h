#ifndef START_H
#define START_H

#include "main.h"

class startpage :public QWidget{
private:
    QImage *preload[20];
    int nowmenu, nowstate, lastPress;
public:
    startpage(){}
    void init();
protected:
    void paintEvent(QPaintEvent* );
    void mouseMoveEvent(QMouseEvent* );
    void mousePressEvent(QMouseEvent* );
    void mouseReleaseEvent(QMouseEvent* );
};

#endif
