#include "hint.h"

Hint::Hint()
{
    //稍微初始化一下
    propRow=0;propCol=0;
    //加载磐岩毛
    propHint.load(PROPHINT_PATH1);
}

void Hint::changePixmap(int pixNum)
{
    if(pixNum==1)propHint.load(PROPHINT_PATH1);
    if(pixNum==2)propHint.load(PROPHINT_PATH2);

}
/////////////////////////////////更新实际坐标////////////////////////////////////
void Hint::updatePosition()
{
    propX=(propCol-1)*60;
    propY=(propRow-1)*60+MENUBAR_INTERVAL;
}
