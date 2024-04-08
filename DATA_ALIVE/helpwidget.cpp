#include "helpwidget.h"
#include "ui_helpwidget.h"

helpWidget::helpWidget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::helpWidget)
{
    ui->setupUi(this);
    //页面基础设置
    this->setFixedSize(GAME_WIDTH,GAME_HEIGHT);
    this->setWindowTitle("游戏帮助");
    this->setWindowIcon(QIcon(TITLE_PATH));
    //图片加载
    helpPix.load(RULE_PATH);
    //实现退出
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });
    //实现返回
    connect(ui->actionreturn,&QAction::triggered,[=](){
        emit back();
    });
}

helpWidget::~helpWidget()
{
    delete ui;
}



//重写绘图事件
void helpWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,MENUBAR_INTERVAL-10,helpPix);
}
