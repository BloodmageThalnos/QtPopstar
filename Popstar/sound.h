
#ifndef SOUND_H
#define SOUND_H

#include "main.h"

class soundControl:public QWidget{
    Q_OBJECT
private:
    QSoundEffect q;
    int loaded;
public:
    soundControl(QWidget *p):QWidget(p){}
    void load();
    void play(int);
    enum{
        SOUND_HIT1
    };
public slots:
    void loadok();
};

#endif
