
#include "sound.h"

void soundControl::load(){
    loaded=0;
    q.setSource(QUrl::fromLocalFile(":/res/5_01"));
    q.setVolume(0.0f);
    connect(&q,SIGNAL(statusChanged()),this,SLOT(loadok()));
    q.play();
}

void soundControl::loadok(){
    QApplication::sendEvent(parent(),new QEvent((QEvent::Type)SOUNDCONTROL_LOADED));
}

void soundControl::play(int x){
    q.setVolume(1.0f);
    q.play();
}
