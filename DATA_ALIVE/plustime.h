//////////////////////////////////////////+1s时间道具//////////////////////////////////////////////
#pragma once
#include"Config.h"
#include<QPixmap>
class Plustime
{
public:
    //显示的图片
    QPixmap propTime;
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
    //改变图片
    void Changepix(int pixNum);
    //默认构造函数，显示绝缘
    Plustime();
    //更新实际坐标
    void  updateposition();
};
