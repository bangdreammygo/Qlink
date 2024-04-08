////////////////////////////消除方块类/////////////////////////////
#pragma once
#include"Config.h"
#include<QPixmap>
class Block
{
public:
    ///////////////////成员变量/////////////////
    //记录成员编号
    int pixNum;
    //记录是否激活
    bool isActive;
    //记录它在地图里的坐标(在地图里会被初始化)
    int blockRow;
    int blockCol;
    //这个变量是为了整个地图服务的，这个变量记录了地图录进去的是他承自谁的下标
    int fatherIdx;
    //记录是否高亮(也是双人模式里的第二人激活后的高亮)
    bool  isHint=false;
    /////////////////成员函数////////////////
    //构造函数
    Block();
};


