#include "doubleend.h"
#include "ui_doubleend.h"

////////////////////////////////正常构造函数///////////////////////////////
Doubleend::Doubleend(int score1,int score2,QWidget *parent) : QMainWindow(parent), ui(new Ui::Doubleend)
{
    ui->setupUi(this);
    scoreOne=score1;
    scoreTwo=score2;
    //实现退出
    connect(ui->quit,&QAction::triggered,[=](){
        this->close();
    });
    //实现返回
    connect(ui->return_2,&QAction::triggered,[=](){
        qDebug()<<"发送信号";
        emit  back();
    });
    //初始化背景图
    initScene();
}
//////////////////////////////////////无解构造函数////////////////////////////////////////
Doubleend::Doubleend(int score1, int score2, bool noAnswer): ui(new Ui::Doubleend)
{
    ui->setupUi(this);
    scoreOne=score1;
    scoreTwo=score2;
    //实现退出
    connect(ui->quit,&QAction::triggered,[=](){
        this->close();
    });
    //实现返回
    connect(ui->return_2,&QAction::triggered,[=](){
        qDebug()<<"发送信号";
        emit  back();
    });
    //初始化背景
    initNoAnswer();
}
/////////////////////////////////////析构函数////////////////////////////////////////////////////
Doubleend::~Doubleend()
{
    delete ui;
}
////////////////////////////////////////正常初始化///////////////////////////////////////////////////
void Doubleend::initScene()
{
    //先初始化一下随机数种子
    srand((unsigned int)time(NULL));
    //再加载一些常规数据配置
    this->setFixedSize(GAME_WIDTH,GAME_HEIGHT+MENUBAR_INTERVAL);
    this->setWindowTitle("游戏结束");
    this->setWindowIcon(QIcon(TITLE_PATH));
    //随机加载一个结束背景
    int idx=rand()%3+1;
    if(idx==1) background.load(KEMIN_PATH);
    if(idx==2) background.load(JUEHAI_PATH);
    if(idx==3) background.load(MIJING_PATH);
    QLabel*endText=new QLabel(this);
    endText->move(0,MENUBAR_INTERVAL);
    endText->setFixedSize(GAME_WIDTH,GAME_HEIGHT);
    QString str=QString("游戏结束,玩家一消除%1个,玩家二消除%2个").arg(scoreOne).arg(scoreTwo);
    endText->setText(str);
    //设置居中对齐
    endText->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    //设置穿透属性
    endText->setAttribute(Qt::WA_TransparentForMouseEvents);
    //设置字体大小颜色等
    QFont font("华文新魏",30);
    endText->setFont(font);
    endText->setStyleSheet("color:yellow;");
}
////////////////////////////////////////////无解初始化///////////////////////////////////////////////
void Doubleend::initNoAnswer()
{
    //先初始化一下随机数种子
    srand((unsigned int)time(NULL));
    //再加载一些常规数据配置
    this->setFixedSize(GAME_WIDTH,GAME_HEIGHT+MENUBAR_INTERVAL);
    this->setWindowTitle("游戏结束");
    this->setWindowIcon(QIcon(TITLE_PATH));
    //随机加载一个结束背景
    int idx=rand()%3+1;
    if(idx==1) background.load(KEMIN_PATH);
    if(idx==2) background.load(JUEHAI_PATH);
    if(idx==3) background.load(MIJING_PATH);
    QLabel*endText=new QLabel(this);
    endText->move(0,MENUBAR_INTERVAL);
    endText->setFixedSize(GAME_WIDTH,GAME_HEIGHT);
    QString str=QString("余下无解,玩家一消除%1个,玩家二消除%2个").arg(scoreOne).arg(scoreTwo);
    endText->setText(str);
    //设置居中对齐
    endText->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    //设置穿透属性
    endText->setAttribute(Qt::WA_TransparentForMouseEvents);
    //设置字体大小颜色等
    QFont font("华文新魏",30);
    endText->setFont(font);
    endText->setStyleSheet("color:yellow;");
}
//////////////////////////////////////////////重写画图函数////////////////////////////////////////////////////
void Doubleend::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,MENUBAR_INTERVAL,background);
}
