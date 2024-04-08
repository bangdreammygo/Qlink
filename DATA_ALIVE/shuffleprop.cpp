#include "shuffleprop.h"
///////////////////////////////////构造函数////////////////////////////////////
Shuffleprop::Shuffleprop()
{
    //加载魔女杯子
    propShu.load(PROPSHU_PATH1);
    //稍微初始化一下row和col
    propRow=0;propCol=0;

}
/////////////////////////////////换照片函数///////////////////////////////
void Shuffleprop::changePixmap(int pixNum)
{
   if(pixNum==1)propShu.load(PROPSHU_PATH1);
   //还可能加载乐团杯子
   if(pixNum==2)propShu.load(PROPSHU_PATH2);

}
/////////////////////////////////////更新实际坐标///////////////////////////////////
void Shuffleprop::updatePosition()
{
   propX=(propCol-1)*60;
   propY=(propRow-1)*60+MENUBAR_INTERVAL;

}
