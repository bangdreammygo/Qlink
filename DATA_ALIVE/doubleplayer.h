///////////////////////////////////////////////////////双人模式///////////////////////////////////////////////////////////////
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
#include"doubleend.h"
namespace Ui {
class Doubleplayer;
}

class Doubleplayer : public QMainWindow
{
    Q_OBJECT

public:
    ////////////////////////////////////////////////成员变量//////////////////////////////////////////////////////
    //双人模式下的地图背景板
    QPixmap doubleMap;
    //记录地图
    int mapNum;
    //记录bgm
    int bgmNum;
    //一个整个地图的二维数组维护地图数据
    Block allMap[GAME_ROW][GAME_COL];
    //需要一个定时器来实时刷新画面
    QTimer timer;
    //需要第二个定时器来计时
    QTimer timer2;
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
    //两个角色
    Role playerOne;
    Role playerTwo=Role(SOLON_NV_PATH);
    //记录两个玩家按键状态
    //第一个玩家
    int typeOne=0;
    //第二个玩家
    int typeTwo=0;
    //一个记录当前场上的激活个数的变量
    //第一个玩家的激活个数
    int activeNumOne=0;
    //第二格玩家的激活个数
    int activeNumTwo=0;
    //保存第一个玩家的激活方块
    int tmp1RowOne;
    int tmp1ColOne;
    int tmp2RowOne;
    int tmp2ColOne;
    //保存第二个玩家的方块激活信息
    int tmp1RowTwo;
    int tmp1ColTwo;
    int tmp2RowTwo;
    int tmp2ColTwo;
    //加载消除音效
    QSound*dis;
    //玩家一消除的方块数量
    int haveEliminateOne=0;
    //玩家二消除的方块数量
    int haveEliminateTwo=0;
    //追加一个积分和时间的图片栏
    QPixmap  markBox;
    //游戏总时间150秒
    int gameTime=GAME_TIME;
    //一个结束场景的指针维护
    Doubleend*endScene;
    //加载一个背景音乐
    QSound*bgm;
    //初始化地图的辅助数组
    int arrMap[100];
    //无解的标志
    bool haveAnswer=true;
    ////////////////////////////////////////////////成员函数///////////////////////////////////////////////
    //构造函数
    explicit Doubleplayer(int sceneNum,int bgmNum,QWidget *parent = nullptr);
    ~Doubleplayer();
    //重写绘图事件
    void paintEvent(QPaintEvent *event);
    //初始化整体关卡的函数
    void initScene(int sceneNum,int bgmNum);
    //初始化最外层一圈的方块
    void initSurround();
    //游戏启动（定时器等）
    void play();
    //随机初始化方块的函数
    void randInition();
    //随机初始化玩家位置
    void randPlayerposition();
    //重写键盘控制函数
    void  keyPressEvent(QKeyEvent *event);
    //更新全局信息
    void  updatePosition();
    //更新人物坐标信息
    void updatePlayerPosition();
    //////////////////////////////////////////消除逻辑///////////////////////////////////////////////////////////
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
    void doEliminateOne();
    void doEliminateTwo();
    //初始化边框
    void initBox();
    //更新边框
    void updateBox();
    //存档函数
    void writeFile();
    //读档函数
    void readFile();
    ///////////////////////////////////////////////////信号////////////////////////////////////////////////////
signals:
    //返回信号
    void  back();
    //结束信号
    void  gameOver();
    //无解信号
    void  noAnswer();
private:
    Ui::Doubleplayer *ui;
};

