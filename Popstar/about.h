#ifndef ABOUT_H
#define ABOUT_H

#include "main.h"

class buttonAni;

/*
  class aboutMenu:
    Handles all the interactions in the "About" menu.
    */
class aboutMenu:public QWidget{
private:
    int now;
        // frame counter for animation, means which frame to display.
    int cnt;
        // frame counter for animation, stops when (now==cnt).
    int timer;
        // the identification of starttimer().
    QLabel* Lbl;
        // Text area for displaying.
    QLabel* Title;
    buttonAni* btnMenu;
        // the return button.
public:
    aboutMenu(QWidget*);
        // call aboutMenu(this) to display in existing QWidget window.
    ~aboutMenu();
        // automatically frees memory for QLabels and buttons.
protected:
    void timerEvent(QTimerEvent *);
    void paintEvent(QPaintEvent *);
};

#endif
