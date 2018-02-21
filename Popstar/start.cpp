#include "start.h"

void startpage::init(){
    preload[0]=new QImage(":/res/1_01");
    preload[1]=new QImage(":/res/1_02");
    preload[2]=new QImage(":/res/1_03");
    preload[3]=new QImage(":/res/1_04");
    preload[4]=new QImage(":/res/2_01");
    preload[5]=new QImage(":/res/2_02");
    preload[6]=new QImage(":/res/2_03");
    preload[7]=new QImage(":/res/2_04");
    preload[8]=new QImage("./res/4_01");
    resize(__WINDOW_W,__WINDOW_H);
    nowmenu=0;
    nowstate=0;
    setMouseTracking(true);
    QSound* s_01=new QSound(":/res/5_01");
    s_01->play();
    show();
}

void startpage::paintEvent(QPaintEvent* event){
    QPainter p(this);
    p.drawImage(0,0,*preload[nowstate]);
}

void startpage::mouseMoveEvent(QMouseEvent *event){
    int x=event->x(), y=event->y();
    switch(nowmenu){
    case 0:
        if(x>=114 && x<=466 && y>=359 && y<=455){      //button1
            nowstate=1;
            update();
        }else if(x>=114 && x<=466 && y>=500 && y<=596){//button2
            nowstate=2;
            update();
        }else if(x>=114 && x<=466 && y>=651 && y<=747){//button3
            nowstate=3;
            update();
        }else if(nowstate){
            nowstate=0;
            update();
        }
        break;
    case 1:
        if(x>=109 && x<=461 && y>=138 && y<=234){      //button1
            nowstate=5;
            update();
        }else if(x>=109 && x<=461 && y>=366 && y<=462){//button2
            nowstate=6;
            update();
        }else if(x>=109 && x<=461 && y>=597 && y<=693){//button3
            nowstate=7;
            update();
        }else if(nowstate!=4){
            nowstate=4;
            update();
        }
        break;
    case 2:
        break;
    default:
        assert(0);
    }
}

void startpage::mousePressEvent(QMouseEvent *event){
    int x=event->x(), y=event->y();
    switch(nowmenu){
    case 0:
        if(x>=114 && x<=466 && y>=359 && y<=455){      //button1
            nowstate=0;
            lastPress=1;
            update();
        }else if(x>=114 && x<=466 && y>=500 && y<=596){//button2
            nowstate=0;
            lastPress=2;
            update();
        }else if(x>=114 && x<=466 && y>=651 && y<=747){//button3
            nowstate=0;
            lastPress=3;
            update();
        }
        break;
    case 1:
        if(x>=109 && x<=461 && y>=138 && y<=234){      //button1
            nowstate=4;
            lastPress=5;
            update();
        }else if(x>=109 && x<=461 && y>=366 && y<=462){//button2
            nowstate=4;
            lastPress=6;
            update();
        }else if(x>=109 && x<=461 && y>=597 && y<=693){//button3
            nowstate=4;
            lastPress=7;
            update();
        }
        break;
    case 2:
        break;
    default:
        assert(0);
    }
}

void startpage::mouseReleaseEvent(QMouseEvent *event){
    int x=event->x(), y=event->y();
    switch(nowmenu){
    case 0:
        if(x>=114 && x<=466 && y>=359 && y<=455 && lastPress==1){      //button1
            nowstate=4;
            nowmenu=1;
            update();
        }else if(x>=114 && x<=466 && y>=500 && y<=596 && lastPress==2){//button2
            nowstate=8;
            nowmenu=2;
            update();
        }else if(x>=114 && x<=466 && y>=651 && y<=747 && lastPress==3){//button3
            nowstate=0;
            update();
        }
        break;
    case 1:
        if(x>=109 && x<=461 && y>=138 && y<=234 && lastPress==5){      //button1
            //game* G=new game(1);
        }else if(x>=109 && x<=461 && y>=366 && y<=462 && lastPress==6){//button2
            //game* G=new game(2);
        }else if(x>=109 && x<=461 && y>=597 && y<=693 && lastPress==7){//button3
            //game* G=new game(3);
        }
        break;
    case 2:
        nowstate=0;
        nowmenu=0;
        update();
        break;
    default:
        assert(0);
    }
}
