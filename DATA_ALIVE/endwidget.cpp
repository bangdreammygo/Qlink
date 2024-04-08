#include "endwidget.h"
#include "ui_endwidget.h"
////////////////////////////////////构造函数///////////////////
Endwidget::Endwidget(int score, QWidget *parent) :QMainWindow(parent),ui(new Ui::Endwidget)
{
    ui->setupUi(this);
    totalScore=score;
    //实现退出
    connect(ui->quit,&QAction::triggered,[=](){
        this->close();
    });
    //实现返回
    connect(ui->return_2,&QAction::triggered,[=](){
        qDebug()<<"发送信号";
        emit  back();
    });
    //初始化化背景
    initScene();
}
//////////////////////////////////无解下的构造函数/////////////////////////////
Endwidget::Endwidget(int score, bool noAnswer):ui(new Ui::Endwidget)
{
     ui->setupUi(this);
    totalScore=score;
    //实现退出
    connect(ui->quit,&QAction::triggered,[=](){
        this->close();
    });
    //实现返回
    connect(ui->return_2,&QAction::triggered,[=](){
        qDebug()<<"发送信号";
        emit  back();
    });
    //初始化化背景
    initNoAnswerScene();
}
//////////////////////////////////析构函数///////////////////
Endwidget::~Endwidget()
{
    delete ui;
}
///////////////////////////////初始化函数/////////////////////////
void Endwidget::initScene()
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
    QString str=QString("游戏结束,你获得%1分").arg(totalScore);
    endText->setText(str);
    //设置居中对齐
    endText->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    //设置穿透属性
    endText->setAttribute(Qt::WA_TransparentForMouseEvents);
    //设置字体大小颜色等
    QFont font("华文新魏",45);
    endText->setFont(font);
    endText->setStyleSheet("color:yellow;");

}
////////////////////////////////初始化无解下的背景///////////////////////////////
void Endwidget::initNoAnswerScene()
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
    QString str=QString("余下已无解游戏结束,你获得%1分").arg(totalScore);
    endText->setText(str);
    //设置居中对齐
    endText->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    //设置穿透属性
    endText->setAttribute(Qt::WA_TransparentForMouseEvents);
    //设置字体大小颜色等
    QFont font("华文新魏",37);
    endText->setFont(font);
    endText->setStyleSheet("color:yellow;");
}
///////////////////////////////绘图事件/////////////////
void Endwidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,MENUBAR_INTERVAL,background);
}
