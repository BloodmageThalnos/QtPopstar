#include "about.h"

aboutMenu::aboutMenu(QWidget *p)
    :QWidget(p){
    resize(__WINDOW_W,__WINDOW_H);
    Lbl=new QLabel(this);
    Lbl->move(80,140);
    Lbl->resize(450,600);
    Lbl->setFont(QFont("Agency FB",20));
    Lbl->setPalette([]{QPalette t;t.setColor(QPalette::WindowText,QColor(202,190,202));return t;}());
    Lbl->setWordWrap(true);
    Lbl->setAlignment(Qt::AlignTop);
    Title=new QLabel(this);
    Title->move(80,45);
    Title->resize(450,60);
    Title->setFont(QFont("Jokerman",24));
    Title->setPalette([]{QPalette t;t.setColor(QPalette::WindowText,QColor(202,190,202));return t;}());
    Title->setText("About");
    show();
    btnMenu=new buttonAni((mainWindow*)parent(),"Menu",760,8);
    btnMenu->in();
    now=0, cnt=__about_text.length();
    timer=startTimer(30);
}

aboutMenu::~aboutMenu(){
    btnMenu->out();
    delete Lbl;
    delete Title;
    destroy();
}

void aboutMenu::paintEvent(QPaintEvent *event){
    QPainter p(this);
    p.drawImage(0,0,QImage(":/res/bg3"));
}

void aboutMenu::timerEvent(QTimerEvent *event){
    now++;
    if(now==cnt){
        Lbl->setText(__about_text);
        killTimer(timer);
        return;
    }
    Lbl->setText(__about_text.mid(0,now)+'_');
}
