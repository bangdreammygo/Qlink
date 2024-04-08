#include "selectscene.h"
#include "ui_selectscene.h"

Selectscene::Selectscene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Selectscene)
{
    ui->setupUi(this);
    background.load(SELECT_BACKGROUND_PATH);
    setFixedSize(GAME_WIDTH,GAME_HEIGHT+MENUBAR_INTERVAL);
    setWindowTitle("选择场景配置");
    setWindowIcon(QIcon(TITLE_PATH));
    ui->widget->setFixedSize(400,360);
    ui->widget->move(0.5*GAME_WIDTH-0.5*ui->widget->width(),0.5*GAME_HEIGHT-0.5*ui->widget->height());
    connect(ui->quit,&QAction::triggered,[=](){close();});
    connect(ui->return_2,&QAction::triggered,[=](){emit justBack();});
    //加场景选项
    ui->cbx1->addItem("场景：战双——刻命螺旋");
    ui->cbx1->addItem("场景：战双——绝海星火");
    ui->cbx1->addItem("场景：原神——璃月");
    //加背景音乐选项
    ui->cbx2->addItem("bgm:爝火长明");
    ui->cbx2->addItem("bgm:萦森歧路");
    ui->cbx2->addItem("bgm:凛桎鸣渊");
    connect(ui->btn,&QPushButton::clicked,[=](){
        int scene;
        int bgm;
        if(ui->cbx1->currentText()=="场景：战双——刻命螺旋") scene=3;
        if(ui->cbx1->currentText()=="场景：战双——绝海星火") scene=2;
        if(ui->cbx1->currentText()=="场景：原神——璃月")    scene=1;
        if(ui->cbx2->currentText()=="bgm:爝火长明")       bgm=1;
        if(ui->cbx2->currentText()=="bgm:萦森歧路")       bgm=2;
        if(ui->cbx2->currentText()=="bgm:凛桎鸣渊")       bgm=3;
        emit beginGame(bgm,scene);
    });
}

Selectscene::~Selectscene()
{
    delete ui;
}

void Selectscene::paintEvent(QPaintEvent *event)
{
    QPainter  painter(this);
    painter.drawPixmap(0,MENUBAR_INTERVAL,background);
}
