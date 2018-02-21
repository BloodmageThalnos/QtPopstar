#include "start2.h"

mainWindow::mainWindow(){
    resize(__WINDOW_W,__WINDOW_H);
    show();
    star=new shiningStar(this);
    title=new titleAni(this);
    title->in();
    nowBtn=nowMode=0;
    btn1=new buttonAni(this,"Start",650,1);
    btn2=new buttonAni(this,"Help",710,2);
    btn3=new buttonAni(this,"About",770,3);
    btn4=new buttonAni(this,"Standard Mode",650,1);
    btn5=new buttonAni(this,"Challenge Mode",710,2);
    btn6=new buttonAni(this,"Endless Mode",770,3);
    sC=new soundControl(this);
    sC->load();
}

bool mainWindow::event(QEvent *event)
{
    switch(event->type()){
    case SOUNDCONTROL_LOADED:
    {
        btn1->in(), btn2->in(), btn3->in();
        return true;
    }
    case STARTBUTTON_PRESSED:
    {
        if(nowBtn==2 || nowBtn==3){
            title->out();
            btn1->out(), btn2->out(), btn3->out();
        }else if(nowBtn==1 && !nowMode){
            btn1->out(), btn2->out(), btn3->out();
        }else if(nowBtn==1){
            title->out();
            btn4->out(), btn5->out(), btn6->out();
        }else if(nowBtn==6){
            nowMode=6;
            delete help;
            (new singCing(this))->out();
        }else if(nowBtn==7){
            nowMode=6;
            delete nowGame;
            (new singCing(this))->out();
        }else if(nowBtn==8){
            nowMode=6;
            delete about;
            (new singCing(this))->out();
        }
        return true;
    }
    case STARTBUTTON_QUITED:
    {
        static int cnt=0;
        cnt++;
        if(nowBtn>=2 && cnt==4)
            nowMode=2+nowBtn, nowBtn=cnt=0, (new singCing(this))->in();
        else if(nowBtn==1 && !nowMode && cnt==3)
            btn4->in(), btn5->in(), btn6->in();
        else if(cnt==7){
            nowBtn=cnt=0, (new singCing(this))->in();
        }
        return true;
    }
    case MAINSCENE_CHANGED:
    {
        if(nowMode<=3){
            nowBtn=0;
            nowGame=new gameWindow(this,nowMode);
            nowGame->init();
            nowGame->start();
        }else if(nowMode==4){
            nowBtn=0;
            help=new helpMenu(this);
        }else if(nowMode==5){
            nowBtn=0;
            about=new aboutMenu(this);
        }else if(nowMode==6){
            nowBtn=nowMode=0;
            title->in();
            btn1->in(), btn2->in(), btn3->in();
        }
        return true;
    }
    default:
        return QWidget::event(event);
    }
}

void mainWindow::paintEvent(QPaintEvent *event){
    QPainter p(this);
    p.drawImage(0,0,QImage(":/res/bg2"));
}

shiningStar::shiningStar(QWidget *p):
    QWidget(p){
    for(int i=0;i<=10;i++){
        QString temp;
        temp.sprintf(":/res/0_%02d",i);
        preload[i]=new QImage(temp);
    }
    for(int i=0;i<30;i++)h[i]=0;
    for(int i=30;i<40;i++)h[i]=i-30;
    for(int i=40;i<50;i++)h[i]=10;
    for(int i=50;i<60;i++)h[i]=60-i;
    cnt=60, now=0;
    resize(302,371);
    move(300,0);
    show();
    startTimer(40);
}

void shiningStar::paintEvent(QPaintEvent *event){
    QPainter p(this);
    p.drawImage(0,0,*preload[h[now]]);
}

void shiningStar::timerEvent(QTimerEvent *event){
    if(++now==cnt)now=0;
    update();
}

titleAni::titleAni(QWidget* p)
    :QWidget(p), Text("POPSTAR"){
    resize(400,150);
    h[1]=-400;
    h[2]=-390;
    h[3]=-361;
    h[4]=-246;
    h[5]=-160;
    h[6]=-74;
    h[7]=-6;
    h[8]=32;
    h[9]=60;
    h[10]=70;
    h[11]=60;
    h[12]=32;
    h[13]=10;
    h[14]=0;
    move(h[1],400);
    show();
}

void titleAni::in(){
    now=0, cnt=15;
    delta=1;
    startTimer(50);
}

void titleAni::out(){
    now=15, cnt=0;
    delta=-1;
    startTimer(50);
}

void titleAni::timerEvent(QTimerEvent *event){
    now+=delta;
    if(now==cnt){
        killTimer(event->timerId());
        if(delta==-1)QApplication::sendEvent(parent(),new QEvent((QEvent::Type)STARTBUTTON_QUITED));
        return;
    }
    move(h[now],400);
    update();
}

void titleAni::paintEvent(QPaintEvent *event){
    QPainter p(this);
    p.setFont(QFont("Agency FB",61));
    p.setPen(QColor(191,191,208));
    p.drawText(0,0,400,150,0,Text);
}

buttonAni::buttonAni(mainWindow* p,QString _t,int _y,int _b)
    :QWidget(p), Text(_t), y1(_y), btnNo(_b), nowBtn(p->nowBtn), nowMode(p->nowMode){
    x=300;
    nowy=desty=y2=y1+300;
    resize(300,150);
    move(x,nowy);
    show();
}

void buttonAni::in(){
    deltay=-20;
    desty=y1;
    startTimer(45);
}

void buttonAni::out(){
    deltay=20;
    desty=y2;
    startTimer(45);
}

void buttonAni::timerEvent(QTimerEvent *event){
    if(nowy==desty){
        killTimer(event->timerId());
        if(deltay>0 && btnNo<6)QApplication::sendEvent(parent(),new QEvent((QEvent::Type)STARTBUTTON_QUITED));
        return;
    }
    nowy+=deltay;
    move(x,nowy);
    update();
}

void buttonAni::paintEvent(QPaintEvent *event){
    QPainter p(this);
    p.setFont(QFont("Agency FB",27));
    p.setPen(QColor(191,191,208));
    p.drawText(0,0,300,150,Qt::AlignRight,Text);
}

void buttonAni::mousePressEvent(QMouseEvent *event){
    move(x+4,nowy+4);
    update();
}

void buttonAni::mouseReleaseEvent(QMouseEvent *event){
    move(x,nowy);
    update();
    if(!nowBtn)nowBtn=btnNo, nowMode=0;
    else nowMode=btnNo;
    QApplication::sendEvent(parent(),new QEvent((QEvent::Type)STARTBUTTON_PRESSED));
}

singCing::singCing(QWidget* p)
    :QWidget(p), Text("POPSTAR"), img(":/res/bg4"){
    resize(__WINDOW_W,__WINDOW_H*2);h[1]=2;
    h[2]=8;
    h[3]=17;
    h[4]=30;
    h[5]=47;
    h[6]=68;
    h[7]=92;
    h[8]=120;
    h[9]=152;
    h[10]=188;
    h[11]=226;
    h[12]=263;
    h[13]=301;
    h[14]=338;
    h[15]=376;
    h[16]=414;
    h[17]=451;
    h[18]=489;
    h[19]=526;
    h[20]=564;
    h[21]=600;
    h[22]=632;
    h[23]=660;
    h[24]=684;
    h[25]=705;
    h[26]=722;
    h[27]=735;
    h[28]=744;
    h[29]=750;
    h[30]=752;
    show();
}

void singCing::in(){
    delta=1;
    now=0, cnt=31;
    startTimer(50);
}

void singCing::out(){
    delta=-1;
    now=30, cnt=0;
    move(0,-h[now]);
    update();
    startTimer(50);
}

void singCing::timerEvent(QTimerEvent *event){
    now+=delta;
    if(now==cnt){
        killTimer(event->timerId());
        QApplication::sendEvent(parent(),new QEvent((QEvent::Type)MAINSCENE_CHANGED));
        delete this;
        return;
    }
    move(0,-h[now]);
    update();
}

void singCing::paintEvent(QPaintEvent *event){
    QPainter p(this);
    p.drawImage(0,0,img);
}
