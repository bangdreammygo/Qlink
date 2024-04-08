#pragma once
#include<QString>
#include <QPushButton>
#include"Config.h"
#include<QPixmap>
#include"QDebug"
#include<QPropertyAnimation>//动画对象
#include<QMouseEvent>
#include<QTimer>
class Mypushbutton : public QPushButton
{
    Q_OBJECT
public:

    //重写构造函数
    Mypushbutton(QString path);
    //向下跳跃
    void  zoom1();
    //向上跳跃
    void  zoom2();
    //按钮禁用的标志
    bool isClicked=false;

signals:

};
