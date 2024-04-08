///////////////////////////////////////结算界面///////////////////////////////////////////
#pragma once
#include <QMainWindow>
#include <QPixmap>
#include"Config.h"
#include<QLabel>
#include<ctime>
#include<QPainter>
#include<QString>
#include<QColor>
#include<QFont>
#include<QPalette>
#include<QDebug>
namespace Ui {
class Endwidget;
}

class Endwidget : public QMainWindow
{
    Q_OBJECT

public:
    /////////////////////////////成员变量///////////////////////
    //背景图片
    QPixmap background;
    int totalScore;
    ///////////////////////成员函数///////////////////////////
    explicit Endwidget(int score,QWidget *parent = nullptr);
    Endwidget(int score, bool noAnswer);
    ~Endwidget();
    //初始化背景
    void initScene();
    void initNoAnswerScene();
    //重写绘图事件
    void paintEvent(QPaintEvent *event);
    ////////////////////////信号/////////////////////////
signals:
    void back();

private:
    Ui::Endwidget *ui;
};


