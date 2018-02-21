#include "game.h"

gameWindow::gameWindow(QWidget* p,int gm):
    QWidget(p), width(__WINDOW_W), height(__WINDOW_H), leftX(__game_lx), leftY(__game_ly), rightX(__game_rx), rightY(__game_ry), gameMode(gm)
{
}

gameWindow::~gameWindow(){
    killTimer(timer);
    delete bkpic;
    for(int i=0;i<=4;i++)delete preIcon[i];
    for(int i=1;i<=row;i++)
    for(int j=1;j<=col;j++)delete Map[i][j];
    btnMenu->out();
    destroy();
}

void gameWindow::init(){
    srand(time(0));
    bkpic=new QImage(":/res/bg3");
    preIcon[0]=new QImage(":/res/4_01");
    preIcon[1]=new QImage(":/res/4_05");
    preIcon[2]=new QImage(":/res/4_03");
    preIcon[3]=new QImage(":/res/4_04");
    preIcon[4]=new QImage(":/res/4_02");
    sC=((mainWindow*)parent())->sC;
    btnMenu=new buttonAni((mainWindow*)parent(),"Menu",760,7);
    if(gameMode==2){
        level=1;
        row=__game_level_row[level-1], col=__game_level_col[level-1], colorCnt=5;
    }else
        row=10, col=10, colorCnt=4;
    startCnt=0;
    sizW=(rightX-leftX)/col, sizH=(rightY-leftY)/row;
    for(int i=0;i<5;i++)
        *preIcon[i]=preIcon[i]->scaled(sizW,sizH,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    for(int i=1;i<=row;i++)
    for(int j=1;j<=col;j++){
        gameWindow::node* n=Map[i][j]=new gameWindow::node();
        if(gameMode==2){
            n->color=__game_level_map[level-1][j-1][i-1]-1;
        }else
            n->color=(rand()%colorCnt);
        n->nowx=n->destx=leftX+(i-1)*sizW, n->nowy=n->desty=leftY+(j-1)*sizH;
        n->del=true;
    }
    for(int i=1;i<=row;i++)Map[col+1][i]=new gameWindow::node(), Map[col+1][i]->del=true;
    score=0;
    gameOver=false;
    locked=row*col;
    resize(width,height);
    show();
    timer=startTimer(50);
}

void gameWindow::start(){
    for(int i=1;i<=row;i++)
    for(int j=1;j<=col;j++){
       new sqrRotater(this,j,i,row-i+1);
    }
    if(gameMode==1){
        destscore=2000;
    }else if(gameMode==3){
        tC=new timeCounter(this,200);
    }
    btnMenu->in();
}

void gameWindow::restart(){
    if(gameMode==1){
        destscore+=2500;
    }
    else if(gameMode==2){
        row=__game_level_row[level-1],
        col=__game_level_col[level-1],
        score=0;
    }
    for(int i=1;i<=row;i++)
    for(int j=1;j<=col;j++){
        gameWindow::node* n=Map[i][j]=new gameWindow::node();
        if(gameMode==2){
            n->color=__game_level_map[level-1][j-1][i-1]-1;
        }else
            n->color=(rand()%colorCnt);
        n->nowx=n->destx=leftX+(i-1)*sizW, n->nowy=n->desty=leftY+(j-1)*sizH;
        n->del=true;
    }
    gameOver=false;
    locked=row*col;
    for(int i=1;i<=row;i++)
    for(int j=1;j<=col;j++){
       new sqrRotater(this,j,i,row-i+1);
    }
}

bool gameWindow::event(QEvent *e){
    switch(e->type()){
    case TIMECOUNTER_TIMESUP:
    {
        gameOver=true;
        QString temp;
        temp.sprintf("%lld",score);
        if(gameMode==1){
            if(score<destscore){
                new scoreDropper(this,"You Lose!","Score:",temp);
            }else{
                new scoreDropper(this,"You Win!","Partial Score:",temp,true);
            }
        }else if(gameMode==2){
            if(!testEmptyCol(1)){
                new scoreDropper(this,"You Lose!","Click to ","try again.",true);
            }else{
                level++;
                new scoreDropper(this,"You Win!","Click to ","next level.",true);
            }
        }else {
            new scoreDropper(this,"Time's up!","Score:",temp);
        }
        return true;
    }
    case SCOREDROPPER_QUITTED:
    {
        restart();
        return true;
    }
    default:
        return QWidget::event(e);
    }
}

void gameWindow::timerEvent(QTimerEvent *event){
    for(int i=1;i<=row;i++)
    for(int j=1;j<=col;j++)if(!Map[i][j]->del){
        int& nx=Map[i][j]->nowx, dx=Map[i][j]->destx, &ny=Map[i][j]->nowy, dy=Map[i][j]->desty;
        int DELTAX=__game_dropspdx, DELTAY=__game_dropspdy;
        if(nx==dx);
        else if(nx<dx)nx=std::min(dx,nx+DELTAX);
        else nx=std::max(dx,nx-DELTAX);
        if(ny==dy);
        else if(ny<dy)ny=std::min(dy,ny+DELTAY);
        else ny=std::max(dy,ny-DELTAY);
    }
    update();
}

void gameWindow::paintEvent(QPaintEvent* event){
    QPainter p(this);
    p.drawImage(0,0,*bkpic);
    showBoard();
    showScore();
}

void gameWindow::mousePressEvent(QMouseEvent* event){
    int x=event->x(), y=event->y();
    if(x>=leftX && x<=rightX && y>=leftY && y<=rightY){
        choose((x-leftX)/sizW +1, (y-leftY)/sizH +1, x, y);
    }
}

bool gameWindow::testEmptyCol(int c){
    bool flag=false;
    for(int i=1;i<=row;i++)flag|=!Map[c][i]->del;
    return !flag;
}

bool gameWindow::testCannotMove(){
    for(int i=1;i<=col;i++){
        for(int j=1;j<row;j++){
            if(!Map[i][j]->del && !Map[i][j+1]->del && Map[i][j]->color==Map[i][j+1]->color)return false;
        }
    }
    for(int i=1;i<=row;i++){
        for(int j=1;j<col;j++){
            if(!Map[j][i]->del && !Map[j+1][i]->del && Map[j][i]->color==Map[j+1][i]->color)return false;
        }
    }
    return true;
}

int gameWindow::getscore(int x){
    if(x>50)return 99990000;
    if(x>40)return 9990000;
    return __game_score[x];
}

void gameWindow::showBoard(){
    QPainter p(this);
    for(int i=1;i<=row;i++)
    for(int j=1;j<=col;j++)if(!Map[i][j]->del){
        int sx=Map[i][j]->nowx, sy=Map[i][j]->nowy;
        p.drawImage(sx,sy,*preIcon[Map[i][j]->color],0,0,sizW,sizH);
   }
}

void gameWindow::showScore(){
    QPainter p(this);
    QString tS;
    tS.sprintf("  %lld",score);
    p.setPen(Qt::SolidLine);
    p.setPen(Qt::white);
    p.drawText(0,40,"Score:");
    p.drawText(0,85,tS);
    if(gameMode==1){
        tS.sprintf("%lld",destscore);
        p.drawText(0,0,__WINDOW_W,40,Qt::AlignRight,"Goal:  ");
        p.drawText(0,45,__WINDOW_W,85,Qt::AlignRight,tS);
    }else if(gameMode==2){
        tS.sprintf("Level %d",level);
        p.drawText(0,0,__WINDOW_W,40,Qt::AlignRight,tS);
    }
}

void gameWindow::choose(int x,int y,int mouseX,int mouseY){
    if(gameOver || locked)return;
    using namespace std;
    bool vis[12][12]={0};
    if(Map[x][y]->del)return;
    queue<pii>Q;
    vector<pii>V;
    Q.push(make_pair(x,y));
    V.push_back(make_pair(x,y));
    int nowc=Map[x][y]->color;
    vis[x][y]=1;
    while(!Q.empty()){
        int x=Q.front().first, y=Q.front().second;Q.pop();
        if(x>1 && !vis[x-1][y] && !Map[x-1][y]->del && Map[x-1][y]->color==nowc)V.push_back(make_pair(x-1,y)), Q.push(make_pair(x-1,y)), vis[x-1][y]=1;
        if(x<row && !vis[x+1][y] && !Map[x+1][y]->del && Map[x+1][y]->color==nowc)V.push_back(make_pair(x+1,y)), Q.push(make_pair(x+1,y)), vis[x+1][y]=1;
        if(y>1 && !vis[x][y-1] && !Map[x][y-1]->del && Map[x][y-1]->color==nowc)V.push_back(make_pair(x,y-1)), Q.push(make_pair(x,y-1)), vis[x][y-1]=1;
        if(y<col && !vis[x][y+1] && !Map[x][y+1]->del && Map[x][y+1]->color==nowc)V.push_back(make_pair(x,y+1)), Q.push(make_pair(x,y+1)), vis[x][y+1]=1;
    }
    if(V.size()==1)return;
    score+=getscore(V.size());
    QString temp;
    temp.sprintf("%d",getscore(V.size()));
    new scoreAdder(this,mouseX,mouseY,0,0,temp);
    sC->play(0);
    for(auto it:V)
        new sqrSmasher(this,it.first,it.second);
    sort(V.begin(), V.end(), [](auto& a,auto& b){
        return a.first==b.first?a.second<b.second:a.first<b.first;
    });
    if(gameMode==1 || gameMode==2){
        for(auto it:V){
            int x=it.first, y=it.second, j=1;
            while(Map[x][j]->del)j++;
            for(int i=y-1;i>=j;i--)
                *Map[x][i+1]=*Map[x][i], Map[x][i+1]->desty+=sizH;
            Map[x][j]->del=true;
        }
        int mostR=col;
        while(mostR && testEmptyCol(mostR))mostR--;
        if(!mostR){
            QApplication::sendEvent(this,new QEvent((QEvent::Type)TIMECOUNTER_TIMESUP));
            return;
        }
        for(int i=mostR-1;i;i--){
            if(testEmptyCol(i)){
                for(int j=i;j<=mostR;j++)
                for(int k=1;k<=row;k++)*Map[j][k]=*Map[j+1][k], Map[j][k]->destx-=sizW;
            }
        }
        bool t=testCannotMove();
        if(t){
            QApplication::sendEvent(this,new QEvent((QEvent::Type)TIMECOUNTER_TIMESUP));
            return;
        }
    }else if(gameMode==3){
        if(V.size()>40){
            tC->add(30);
            new scoreAdder(this,mouseX,mouseY,500,0,"+30s");
        }else if(V.size()>25){
            tC->add(10);
            new scoreAdder(this,mouseX,mouseY,500,0,"+10s");
        }else if(V.size()>15){
            tC->add(5);
            new scoreAdder(this,mouseX,mouseY,500,0,"+5s");
        }else if(V.size()>5){
            tC->add(1);
            new scoreAdder(this,mouseX,mouseY,500,0,"+1s");
        }
        for(auto it:V){
            int x=it.first, y=it.second, j=1;
            for(int i=y-1;i>=j;i--)
                *Map[x][i+1]=*Map[x][i], Map[x][i+1]->desty+=sizH;
            Map[x][j]->nowy-=sizH, Map[x][j]->color=(rand()%(colorCnt+(score>20000)));
        }
    }
}

scoreAdder::scoreAdder(QWidget* p,int nx,int ny,int tx,int ty,QString t)
    :QWidget(p),nowx(nx),nowy(ny),destx(tx),desty(ty),Text(t){
    dx=(destx-nowx)/__game_movespd;
    dy=(desty-nowy)/__game_movespd;
    destx=nowx+dx*__game_movespd;
    desty=nowy+dy*__game_movespd;
    resize(200,200);
    move(nowx,nowy);
    show();
    startTimer(50);
}

void scoreAdder::paintEvent(QPaintEvent *event){
    QPainter p(this);
    p.setPen(Qt::SolidLine);
    p.setPen(Qt::white);
    p.drawText(0,40,Text);
}

void scoreAdder::timerEvent(QTimerEvent *event){
    if(nowx==destx && nowy==desty){
        killTimer(event->timerId());
        Text="";
        repaint();
        destroy();
        delete this;
    }else{
        nowx+=dx;
        nowy+=dy;
        move(nowx,nowy);
    }
}

timeCounter::timeCounter(QWidget *p, int t)
    :QWidget(p), timeCnt(t){
    resize(300,40);
    move(400,0);
    show();
    startTimer(100);
}

QString timeCounter::convert(int x){
    QString temp;
    if(x)temp.sprintf("%02d:%02d.%1d%02d",x/600,(x%600)/10,x%10,rand()%100);
    else temp="00:00.000";
    return temp;
}

void timeCounter::paintEvent(QPaintEvent *event){
    QPainter p(this);
    p.setPen(Qt::SolidLine);
    if(timeCnt<50)p.setPen(Qt::red);
    else p.setPen(Qt::white);
    p.drawText(0,40,convert(timeCnt));
}

void timeCounter::timerEvent(QTimerEvent *event){
    if(timeCnt==0){
        QApplication::sendEvent(parent(),new QEvent((QEvent::Type)TIMECOUNTER_TIMESUP));
        killTimer(event->timerId());
        destroy();
        delete this;
    }
    else timeCnt--;
}

void timeCounter::add(int t){
    timeCnt+=t*10;
}

scoreDropper::scoreDropper(QWidget* p,QString s1,QString s2,QString s3,bool t)
    :QWidget(p), Text1(s1), Text2(s2), Text3(s3), type(t), bg(":/res/bg5"){
    bg=bg.scaled(400,600);
    h[3]=-598;
    h[4]=-580;
    h[5]=-568;
    h[6]=-534;
    h[7]=-502;
    h[8]=-473;
    h[9]=-439;
    h[10]=-401;
    h[11]=-359;
    h[12]=-312;
    h[13]=-262;
    h[14]=-208;
    h[15]=-150;
    h[16]=-88;
    h[17]=-22;
    h[18]=48;
    h[19]=122;
    h[20]=200;
    h[21]=282;
    h[22]=220;
    h[23]=180;
    h[24]=160;
    h[25]=155;
    h[26]=152;
    h[27]=150;
    cnt=28;
    now=2;
    resize(400,600);
    move(100,h[3]);
    show();
    startTimer(50);
    delta=1;
}

void scoreDropper::paintEvent(QPaintEvent *event){
    QPainter p(this);
    p.drawImage(0,0,bg);
    p.setPen(Qt::SolidLine);
    p.setPen(Qt::white);
    p.setFont(QFont("Jokerman"));
    //p.setPen(QColor(255,0,0));
    p.drawText(100,220,Text1);
    p.drawText(100,340,Text2);
    p.drawText(100,390,200,40,Qt::AlignCenter,Text3);
}

void scoreDropper::timerEvent(QTimerEvent *event){
    now+=delta;
    if(now==cnt){
        killTimer(event->timerId());
        if(type && delta<0){
            QApplication::sendEvent(parent(),new QEvent((QEvent::Type)SCOREDROPPER_QUITTED));
        }
        return;
    }else{
        move(100,h[now]);
    }
}

void scoreDropper::mouseReleaseEvent(QMouseEvent *event){
    if(now!=28)return;
    startTimer(50);
    delta=-1;
    now=28, cnt=2;
}

sqrSmasher::sqrSmasher(gameWindow *p,int i,int j,int t)
    :QWidget(p), delayms(t){
    int vx=(rand()%61-30), dy=15, vy=-rand()%45;
    x[0]=p->Map[i][j]->nowx, y[0]=p->Map[i][j]->nowy;
    for(int i=1;i<=10;i++)x[i]=x[i-1]+vx, y[i]=y[i-1]+vy, vy+=dy, o[i]=(100-i*i)/100.0;
    move(x[0],y[0]);
    resize(p->sizW,p->sizH);
    img=p->preIcon[p->Map[i][j]->color];
    show();
    now=0, cnt=11, opa=1.0;
    startTimer(50);
}

void sqrSmasher::paintEvent(QPaintEvent *event){
    QPainter p(this);
    p.setOpacity(opa);
    p.drawImage(0,0,*img);
}

void sqrSmasher::timerEvent(QTimerEvent *event){
    if(delayms){
        delayms--;
        return;
    }
    if(++now==cnt){
        killTimer(event->timerId());
        destroy();
        delete this;
        return;
    }
    move(x[now],y[now]), opa=o[now];
}

sqrRotater::sqrRotater(gameWindow *p,int i,int j,int t)
    :QWidget(p), x(i), y(j), delayms(t){
    sizw[5]=w=p->sizW, sizh[5]=h=p->sizH, rot[5]=90;
    for(int i=0;i<=4;i++)sizw[i]=w*i/5, sizh[i]=h*i/5, rot[i]=rot[5]*i/5;
    move(p->Map[i][j]->nowx,p->Map[i][j]->nowy);
    resize(p->sizW,p->sizH);
    img=p->preIcon[p->Map[i][j]->color];
    now=0, cnt=6;
    startTimer(50);
    show();
}

void sqrRotater::paintEvent(QPaintEvent *event){
    QPainter p(this);
    QImage temp(*img);
    p.drawImage(w/2-sizw[now]/2,h/2-sizh[now]/2,temp.scaled(sizw[now],sizh[now]));
}

void sqrRotater::timerEvent(QTimerEvent *event){
    if(delayms>0){
        delayms--;
        return;
    }
    if(++now==cnt){
        ((gameWindow*)parent())->Map[x][y]->del=false;
        ((gameWindow*)parent())->locked--;
        killTimer(event->timerId());
        destroy();
        delete this;
        return;
    }
}
