#include "plustime.h"
////////////////////////有参构造函数////////////////////////
void Plustime::Changepix(int pixNum)
{
    if(pixNum==1)propTime.load(PROPTIME_PATH1);
    if(pixNum==2)propTime.load(PROPTIME_PATH2);
}

///////////////////////////默认构造函数//////////////////////////////
Plustime::Plustime()
{
    //加载绝缘沙，原神，启动！
    propTime.load(PROPTIME_PATH1);
    //row和col的数据初始化就留给游戏场景负责吧，这里只是稍微初始化一下
    propRow=0;propCol=0;
}
//////////////////////////更新实际坐标的函数//////////////////////
void Plustime::updateposition()
{
    propX=(propCol-1)*60;
    propY=(propRow-1)*60+MENUBAR_INTERVAL;
}
