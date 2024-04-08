////////////////////角色类//////////////////////
#pragma once
#include"Config.h"
#include<QPixmap>
#include<QString>
class Role
{
public:
    ///////////////////成员变量///////////////////////
    //角色的行和列
    int roleRow;
    int roleCol;
    //角色的行列映射到实际坐标系下的位置,也就是绘图事件实际会画的位置
    int x;
    int y;
    //角色的图片展示
    QPixmap rolePix;
    /////////////////成员函数///////////////////
    //更新坐标
    void updatePosition();
    //构造函数
    Role(QString str=SOLON_PATH);
    //移动函数
    void  movePosition(int tpye);
};


