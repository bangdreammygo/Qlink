/////////////////////////////////////////主场景/////////////////////////////////////////
#pragma once
#include<QTimer>
#include <QMainWindow>
#include <QPaintEvent>
#include <QPainter>
#include <QPixmap>
#include"Config.h"
#include<QPushButton>
#include<QDebug>
#include"singleplayer.h"
#include<QLabel>
#include<QMovie>
#include"endwidget.h"
#include"selectscene.h"
#include"doubleplayer.h"
#include"mypushbutton.h"
#include"helpwidget.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Mainscene; }
QT_END_NAMESPACE

class Mainscene : public QMainWindow
{
    Q_OBJECT

public:
    ////////////////////////////成员变量/////////////////////////////
    //主场景的背景地图
    QPixmap mainMap;
    //一个单人场景的指针维护
    Singleplayer*singleScene;
    //一个选择场景的指针维护
    Selectscene*selectPlayer;
    //一个双人模式的指针维护
    Doubleplayer*doubleScene;
    //记录一下从选择配置来的参数
    int sceneNum=1;
    int bgmNum=1;
    //////////////////////////成员函数///////////////////////////////
    //重写绘图事件
    void paintEvent(QPaintEvent *event);
    //初始化场景函数
    void initScene();
    //初始化帮助
    void initHelp();
    //构造函数
    Mainscene(QWidget *parent = nullptr);
    //析构函数
    ~Mainscene();

private:
    Ui::Mainscene *ui;
};

