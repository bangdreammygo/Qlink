#include "role.h"
///////////////////////更新实时坐标的函数///////////////////////
void Role::updatePosition()
{
    x=(roleCol-1)*ROLE_SPEED;
    y=(roleRow-1)*ROLE_SPEED;
}
////////////////////////构造函数////////////////////////////////////
Role::Role(QString str)
{
    //初始化角色图片
    rolePix.load(str);
    //初始化坐标
    x=0;y=0;roleCol=1;roleRow=1;
}
//移动函数
void Role::movePosition(int type)
{   //移动(二维数组中的位置移动)
    //无键盘操作则不动
    if(type==0){return;}
    if(type==LEFT){roleCol--;}
    else if(type==RIGHT){roleCol++;}
    else if(type==KEY_UP){roleRow--;}
    else if(type==DOWN){roleRow++;}
    //横向边界判断
    if(roleRow<1) roleRow=1;
    if(roleRow>GAME_ROW) roleRow=GAME_ROW;
    //纵向边界判断
    if(roleCol<1) roleCol=1;
    if(roleCol>GAME_COL) roleCol=GAME_COL;
    //映射到实际坐标位置更新
    updatePosition();
}
