////////////////////////////////////////自选配置场景//////////////////////////////////////////////
#pragma once
#include <QMainWindow>
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
namespace Ui {
class Selectscene;
}

class Selectscene : public QMainWindow
{
    Q_OBJECT

public:

    ///////////////////变量配置////////////////
    //背景板
    QPixmap background;
    /////////////////函数////////////////
    explicit Selectscene(QWidget *parent = nullptr);
    ~Selectscene();
    void paintEvent(QPaintEvent *event);
signals:
    //返回配置参数
    void beginGame(int bgm,int scene);
    //只是返回
    void justBack();
private:
    Ui::Selectscene *ui;
};


