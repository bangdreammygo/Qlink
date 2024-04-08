////////////////////////////////////////单人模式主场景/////////////////////////////////////////
#pragma once
#include"Config.h"
#include <QMainWindow>
#include<QPixmap>
#include<QPainter>
#include<QPaintEvent>
#include<QMessageBox>
#include"block.h"
#include<QTimer>
#include<ctime>
#include<QDebug>
#include"role.h"
#include<QKeyEvent>
#include<QSound>
#include"endwidget.h"
#include<QFont>
#include"plustime.h"
#include"shuffleprop.h"
#include"hint.h"
#include<QFile>
#include<QTextStream>
#include<QPushButton>
#include<algorithm>
namespace Ui {
class Singleplayer;
}

class Singleplayer : public QMainWindow
{
    Q_OBJECT

public:
    ///////////////////////////////////////成员变量/////////////////////////////////////////////
    //单人模式下的地图背景板
    QPixmap singleMap;
    //记录一下
    int    mapNum;
    //一个整个地图的二维数组维护地图数据
    Block allMap[GAME_ROW][GAME_COL];
    //需要一个定时器来实时刷新画面
    QTimer timer;
    //接着是十种消除块的数组
    //罗塞塔的十个数据
    Block luo[10];
    //丽芙的十个数据
    Block lif[10];
    //露西亚的十个数据
    Block lxy[10];
    //七实的十个数据
    Block nanami[10];
    //比安卡的十个数据
    Block bak[10];
    //阿尔法的十个数据
    Block arf[10];
    //薇拉的十个数据
    Block wela[10];
    //赛琳娜的十个数据
    Block sln[10];
    //露娜的十个数据
    Block luna[10];
    //曲的十个数据
    Block qu[10];
    //记录数据的数组
    int   arrMap[100];
    //这十个角色各自的数组的访问下标(初始为0)
    int luoIdx=0;
    int lifIdx=0;
    int lxyIdx=0;
    int nanamiIdx=0;
    int bakIdx=0;
    int arfIdx=0;
    int welaIdx=0;
    int slnIdx=0;
    int lunaIdx=0;
    int quIdx=0;
    //玩家控制的可操控角色
    Role  Player;
    //记录按键状态
    int type=0;
    //一个记录当前场上的激活个数的变量
    int activeNum;
    //记录第一个激活的方块的位置
    int tmp1Row;
    int tmp1Col;
    //记录第二个激活的方块的位置
    int tmp2Row;
    int tmp2Col;
    //存储消除音效
    QSound*dis;
    //加载一个背景音乐
    QSound*bgm;
    //记录一下
    int  backgmNum;
    //记录已经消除的球的个数
    int haveEliminated=0;
    //一个最终结算场景的指针
    Endwidget*endScene;
    //追加一个积分和时间的框
    QPixmap markBox;
    //剩余时间(150秒)
    int gameTime=GAME_TIME;
    //第二个定时器（记录时间）
    QTimer timer2;
    //显示异常状况时的时间间隔和判断标准
    int    problemInterval=0;
    bool   canLink=true;
    //加一秒时间道具数组,共四个加时间的道具
    Plustime timeprop[4];
    //加一秒消息提示参数
    bool     plusTime=false;
    int      plusInterval=0;
    //加重排地图道具数组，共两个道具
    Shuffleprop  shuffleMap[2];
    //加地图重排消息提示参数
    bool     isShuffle=false;
    int      shuffleInterval=0;
    //加一个高亮道具
    Hint     hintBlock;
    //加入高亮消息提示参数
    int      hintInterval=0;
    //加入一个参数记录当前场上的高亮方块个数
    int      haveHint=0;
    //第三个定时器，道具定时器，记录hint的十秒
    QTimer*hintTimer;
    //记录十秒
    int     tenSec=0;
    //记录是否开始高亮
    bool    isStartHint=false;
    //记录游戏是否已经结束
    bool    haveOver=false;
    //////////////////////////////////////成员函数///////////////////////////////////////
    //构造函数
    explicit Singleplayer(int sceneNum,int bgmNum, QWidget *parent = nullptr);
    //析构函数
    ~Singleplayer();
    //重写绘图事件
    void paintEvent(QPaintEvent *event);
    //初始化整体关卡的函数
    void initScene(int sceneNum,int bgmNum);
    //初始化最外层一圈的方块
    void initSurround();
    //初始化框框的函数
    void initBox();
    //更新框框的函数
    void updateBox();
    //游戏启动（定时器等）
    void play();
    //随机初始化方块的函数
    void randInition();
    //随机初始化玩家位置
    void randPlayerposition();
    //全局变量位置和状态更新
    void updatePosition();
    //人物坐标更新
    void updatePlayerposition();
    //重写键盘控制函数
    void  keyPressEvent(QKeyEvent *event);
    //////////////////////////////////////////////////消除函数，可以copy到双人模式里/////////////////////////////////////////////////
    //重点1：判断消除是否合理的函数,判断两个方块之间能不能进行消除
    bool canEliminate(Block b1, Block b2);
    //封装零折判断
    bool noCornor(Block b1, Block b2);
    //封装一折函数
    bool oneCornor(Block b1, Block b2);
    //封装二折函数
    bool twoCornor(Block b1, Block b2);
    //重点2：得到自动判断是否有解的函数
    bool  canStillEliminate();
    //消除函数，执行地图消除以及数组中的对应消除
    void doEliminate();
    //////////////////////////////////道具函数和读档函数，双人模式里不需要实现////////////////////////////////////
    //生成+1道具
    void generatePlusProp();
    //消除+1道具
    void eliminatePlusprop();
    //生成地图重排道具
    void generateShuffleProp();
    //消除重排道具
    void eliminateShuffleprop();
    //生成高亮道具
    void  generateHint();
    //消除高亮道具
    void  eliminateHintprop();
    //实现hint
    void  startHint();
    //重点函数之存档函数/读档函数
    void    readFile();
    void    writeFlie();
    //////////////////////////信号////////////////////////////////
signals:
    //回归信号
    void back();
    //结束信号
    void  gameOver();
    //无解信号
    void  noAnswer();
    //键盘控制暂停和存档
    void  pause();
    void  archive();
private:
    Ui::Singleplayer *ui;
};

