/////////////////////////////////////帮助页面////////////////////////////////////////////
#pragma once
#include <QMainWindow>
#include <QPixmap>
#include <QPainter>
#include "Config.h"
namespace Ui {
class helpWidget;
}

class helpWidget : public QMainWindow
{
    Q_OBJECT

public:
    //帮助文档图片
    QPixmap helpPix;
    explicit helpWidget(QWidget *parent = nullptr);
    ~helpWidget();
    //重写绘图事件
    void paintEvent(QPaintEvent *event);
    signals:
    //返回信号
    void back();


private:
    Ui::helpWidget *ui;
};

