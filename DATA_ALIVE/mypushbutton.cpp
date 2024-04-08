#include "mypushbutton.h"
//////////////////////////重写构造函数/////////////////////////////
Mypushbutton::Mypushbutton(QString path)
{
    //加载图标
    QPixmap pix;
    pix.load(path);
    //设置固定尺寸
    this->setFixedSize(pix.width(),pix.height());
    //设置不规则样式
    this->setStyleSheet("QPushButton{border:0px;}");
    //设置图标
    this->setIcon(pix);
    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));

}
////////////////////////////向下跳跃函数//////////////////////////
void Mypushbutton::zoom1()
{
    //创建动画对象
    QPropertyAnimation*animation=new QPropertyAnimation(this,"geometry");
    //设置时间间隔
    animation->setDuration(150);
    //设置起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置结束位置
    animation->setEndValue(QRect(this->x(),this->y()+6,this->width(),this->height()));
    //设置动画效果
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start(QAbstractAnimation::DeleteWhenStopped);

}
/////////////////////////////向下跳跃函数////////////////////////////
void Mypushbutton::zoom2()
{
    //创建动画对象
    QPropertyAnimation*animation=new QPropertyAnimation(this,"geometry");
    //设置时间间隔
    animation->setDuration(150);
    //设置起始位置
    animation->setStartValue(QRect(this->x(),this->y()+6,this->width(),this->height()));
    //设置结束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置动画效果
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}
