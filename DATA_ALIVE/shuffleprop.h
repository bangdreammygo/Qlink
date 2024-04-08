///////////////////////////////////////重新洗地图函数//////////////////////////////////////////////
#pragma once
#include"Config.h"
#include<QPixmap>

class Shuffleprop
{
public:
    //////////////////////成员变量///////////////////////
    //显示图片
    QPixmap propShu;
    //二维数组中的坐标
    int propRow;
    int propCol;
    //实际坐标系下的坐标
    int propX;
    int propY;
    //是否上场
    bool isUsed=false;
    //是否被初始化过
    bool isInit=false;
    ///////////////////成员函数//////////////////
    //构造函数
    Shuffleprop();
    //换照片
    void changePixmap(int pixNum);
    //更新实际情况下的坐标
    void updatePosition();

};
