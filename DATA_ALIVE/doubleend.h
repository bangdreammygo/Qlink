///////////////////////////////////////////////////////////双人模式结束场景////////////////////////////////////////////////////////////
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
class Doubleend;
}

class Doubleend : public QMainWindow
{
    Q_OBJECT

public:
    //背景图片
    QPixmap background;
    //两人分数1
    int scoreOne;
    int scoreTwo;
    //正常结束的构造函数
    explicit Doubleend(int score1,int score2,QWidget *parent = nullptr);
    //无解结束的构造函数
    Doubleend(int score1, int score2, bool noAnswer);
    ~Doubleend();
    //正常初始化
    void initScene();
    //无解初始化
    void initNoAnswer();
    //画图函数
    void  paintEvent(QPaintEvent *event);
signals:
    void back();
private:
    Ui::Doubleend *ui;
};


