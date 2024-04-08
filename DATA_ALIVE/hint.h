//////////////////////////////////////////////////高亮道具////////////////////////////////////////////////////////
#pragma once
#include"Config.h"
#include<QPixmap>
class Hint
{
public:
    //显示的图片
    QPixmap propHint;
    //二维数组中的坐标
    int  propRow;
    int  propCol;
    //实际坐标
    int  propX;
    int  propY;
    //是否上场
    bool isUsed=false;
    //是否被初始化
    bool isInit=false;
    //////////////////////////////成员函数//////////////////////////////
    //构造函数
    Hint();
    //换照片
    void changePixmap(int pixNum);
    //更新实际情况下的坐标
    void updatePosition();
};


