#ifndef MAIN_H
#define MAIN_H

#include <Qt>
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPalette>
#include <QPainter>
#include <QBitmap>
#include <QPixmap>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTimerEvent>
#include <QThread>
#include <QList>
#include <QDebug>
#include <QSound>
#include <QMediaPlayer>
#include <QSoundEffect>

#include <cstdlib>
#include <time.h>
#include <assert.h>
#include <vector>
#include <algorithm>
#include <queue>

#include "start2.h"
#include "sound.h"
#include "game.h"
#include "help.h"
#include "about.h"

typedef std::pair<int,int> pii;

const QColor __game_color[]={QColor(0xFF,0x40,0x40),QColor(0x40,0xFF,0x40),QColor(0x40,0x40,0xFF),QColor(0xEE,0xEE,0x00)};
const int __game_score[]={0,0,10,20,45,85,180,300,450,580,700,880,1000,1200,1500,2000,2700,3500,4500,6000,7500,10000,12000,14100,16400,18000,20000,24000,27000,32000,36000,50000,90000,150000,280000,500000,1000000,1800000,3500000,5000000};
const int __game_dropspdx=16, __game_dropspdy=32;
const int __game_movespd=10;
const int __WINDOW_W=600, __WINDOW_H=848;
const int __game_lx=0,__game_ly=100,__game_rx=600,__game_ry=700;
const int __game_level_map[][10][10]={
    {
        {1,2,3,4,5,5,4,3,2,1},
        {2,2,3,4,4,4,4,3,2,2},
        {2,3,3,4,3,3,4,3,3,2},
        {3,3,3,4,4,4,4,3,3,3},
        {1,2,3,4,5,5,4,3,2,1},
        {2,2,3,4,4,4,4,3,2,2},
        {2,3,3,4,3,3,4,3,3,2},
        {3,3,3,4,4,4,4,3,3,3},
        {1,2,3,4,5,5,4,3,2,1},
        {2,2,3,4,4,4,4,3,2,2},
    },{
        {1,5,2,4,1,1,4,2,5,1},
        {3,5,2,4,1,1,4,2,5,2},
        {3,2,5,1,4,4,1,5,2,3},
        {5,2,5,1,4,4,1,5,2,5},
        {5,1,3,3,4,4,3,3,1,5},
        {2,1,3,5,4,4,5,3,1,2},
        {2,2,4,4,4,4,4,4,2,2},
        {1,2,4,2,4,4,2,4,2,1},
        {1,5,1,1,5,5,1,1,5,1},
        {1,5,1,1,4,4,1,1,5,1},
    },{
        {2,4,4,5,4,4,5,4,4,2},
        {1,3,5,1,3,3,1,5,3,1},
        {4,5,3,4,5,5,4,3,5,4},
        {4,1,5,3,1,1,3,5,1,4},
        {5,3,4,1,5,5,1,4,3,5},
        {4,5,4,2,1,1,2,4,5,4},
        {5,1,4,4,5,5,4,4,1,5},
        {5,5,1,2,4,4,2,1,5,5},
        {2,2,3,4,2,2,4,3,2,2},
        {3,3,1,5,5,5,5,1,3,3},
    },{
        {4,1,3,3,1,1,3,3,1,4},
        {2,3,3,5,2,2,5,3,3,2},
        {3,2,2,4,1,1,4,2,2,3},
        {5,3,2,2,3,3,2,2,3,5},
        {5,5,4,3,5,1,3,4,5,5},
        {2,3,1,1,3,3,1,1,3,2},
        {5,4,3,4,3,3,4,3,4,5},
        {4,1,4,2,5,5,2,4,1,4},
        {5,1,4,1,3,3,1,4,1,5},
        {2,1,1,2,4,4,2,1,1,2},
    },{
        {3,4,4,1,5,5,1,4,4,3},
        {2,2,2,4,2,2,4,2,2,2},
        {4,4,5,4,1,1,4,4,4,4},
        {4,1,4,3,5,5,3,4,1,4},
        {5,3,2,4,3,3,4,2,3,5},
        {2,4,3,4,5,5,5,3,4,2},
        {2,3,1,3,4,4,3,1,3,2},
        {1,3,4,5,3,3,5,2,3,1},
        {1,3,4,3,4,4,3,4,3,1},
        {1,3,1,3,4,4,3,1,3,1},
    }
};
const int __game_level_row[]={10,10,10,10,10},
          __game_level_col[]={10,10,10,10,10};
static const QString __help_text("  Take out nearby blocks with the same color.\n  Gain as many scores as you can.\n->CLASSIC MODE: With increasing difficulty, and increasing goal points.\n->CHANLLENGE MODE: Try to take out all blocks !\n->ENDLESS MODE: New blocks are falling down, but time is limited.");
static const QString __about_text("Game designers:\n    (sorted lexicographically)\nProgramming:\t ChengYuan\nUi & Graphics:\t WangZhoudong\nArt & Writing:\t XingKai\nMusic & Sound:\t XuLanglang\nLevel design:\t YangYang\n\nContact Email:\ncy1818cy@bupt.edu.cn");
enum myEvent{
    STARTBUTTON_PRESSED=1001,
    MAINSCENE_CHANGED,
    MAINSCENE_RECHANGED,
    STARTBUTTON_QUITED,
    TIMECOUNTER_TIMESUP,
    SCOREDROPPER_QUITTED,
    SOUNDCONTROL_LOADED
};

#endif
