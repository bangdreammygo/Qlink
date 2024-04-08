#include "mainscene.h"
#include "ui_mainscene.h"
//////////////////////////////////构造函数////////////////////////////////////
Mainscene::Mainscene(QWidget *parent): QMainWindow(parent), ui(new Ui::Mainscene)
{
    ui->setupUi(this);
    //初始化场景配置
    initScene();
    //初始化帮助
    initHelp();
}
/////////////////////////////////析构函数//////////////////////////////////////
Mainscene::~Mainscene()
{
    delete ui;
}
////////////////////////////////////初始化场景函数/////////////////////////////////////
void Mainscene::initScene()
{
    Mypushbutton*btn=new Mypushbutton(SHEZHI_PATH);
    btn->setParent(this);
    //设置单人模式按钮
    Mypushbutton*btnSingle=new Mypushbutton(SINGLE_PATH);
    btnSingle->setParent(this);
    btnSingle->move(60*2+280,280+MENUBAR_INTERVAL);
    //设置双人模式按钮
    Mypushbutton*btnDouble=new Mypushbutton(DOUBLE_PATH);
    btnDouble->setParent(this);
    btnDouble->move(60*3+280*2,280+MENUBAR_INTERVAL);
    selectPlayer=new Selectscene;
    btn->move(60,280+MENUBAR_INTERVAL);
     //修复bug，短时间内点两次会创建两个场景
     //开始游戏设置
    connect(btn,&Mypushbutton::clicked,[=](){
       //查看禁用情况
       if(btn->isClicked==false){
           //禁用按钮(所有按钮)
           btnSingle->isClicked=true;
           btnDouble->isClicked=true;
           btn->isClicked=true;
           //播放动画
           btn->zoom1();
           btn->zoom2();
           QTimer::singleShot(300,this,[=](){
               selectPlayer->setGeometry(this->geometry());
               selectPlayer->show();
               this->hide();
               connect(selectPlayer,&Selectscene::justBack,[=](){
                   this->setGeometry(selectPlayer->geometry());
                   this->show();
                   //解除按钮(所有)禁用
                   btnSingle->isClicked=false;
                   btnDouble->isClicked=false;
                   btn->isClicked=false;
                   selectPlayer->hide();
               });
               connect(selectPlayer,&Selectscene::beginGame,[=](int b,int s){
                   this->setGeometry(selectPlayer->geometry());
                   this->show();
                   //解除按钮(所有)禁用
                   btnSingle->isClicked=false;
                   btnDouble->isClicked=false;
                   btn->isClicked=false;
                   selectPlayer->hide();
                   this->bgmNum=b ;this->sceneNum=s;
                   qDebug()<<s;
               });
           });
       }
    });
    //设置窗口标题
    setWindowTitle("战双消消乐");
   //设置窗口图标
   setWindowIcon(QIcon(TITLE_PATH));
   //设置尺寸
   setFixedSize(GAME_WIDTH,GAME_HEIGHT+MENUBAR_INTERVAL);
   //初始化背景资源图片
   mainMap.load(GAME_BACKGROUND_PATH);
   //实现退出功能
   connect(ui->quit,&QAction::triggered,[=](){
       this->close();
   });
   //修复bug，短时间内点两次会创建两个场景
   //解决方案：按钮禁用
   //实现单人场景转换功能
   connect(btnSingle,&Mypushbutton::clicked,[=](){
     //按钮未被禁用
     if(btnSingle->isClicked==false){
         //禁用按钮(所有按钮)
         btnSingle->isClicked=true;
         btnDouble->isClicked=true;
         btn->isClicked=true;
         //创建单人模式场景
         singleScene=new Singleplayer(sceneNum,bgmNum);
         //播放动画
         btnSingle->zoom1();
         btnSingle->zoom2();
         QTimer::singleShot(300,this,[=](){
                     singleScene->show();
                     this->hide();
                 });
         //要有了单人场景才能开始监听
         //实现从单人场景回到主界面的功能(监听来自单人场景的信号)
         connect(singleScene,&Singleplayer::back,[=](){
              this->setGeometry(singleScene->geometry());
              this->show();
              //解除按钮(所有)禁用
              btnSingle->isClicked=false;
              btnDouble->isClicked=false;
              btn->isClicked=false;
              singleScene->hide();
              delete singleScene;
              singleScene=nullptr;
     });

     }
   });
   //实现双人模式的场景转换功能
   connect(btnDouble,&Mypushbutton::clicked,[=](){
      //未被禁用则创建场景
      if(btnDouble->isClicked==false){
          //禁用所有按钮
          btnSingle->isClicked=true;
          btnDouble->isClicked=true;
          btn->isClicked=true;
          //创建双人模式
          doubleScene=new Doubleplayer(sceneNum,bgmNum);
          //播放动画
          btnDouble->zoom1();
          btnDouble->zoom2();
          QTimer::singleShot(300,this,[=](){
              doubleScene->show();
              this->hide();
          });
          //有了双人模式才能监听
          //实现返回主场景的功能（监听来自双人模式的信号）
          connect(doubleScene,&Doubleplayer::back,[=](){
              this->setGeometry(doubleScene->geometry());
              this->show();
              //解除按钮(所有)禁用
              btnSingle->isClicked=false;
              btnDouble->isClicked=false;
              btn->isClicked=false;
              doubleScene->hide();
              delete doubleScene;
              doubleScene=nullptr;
          });
      }
   });
}
/////////////////////////////////////初始化帮助页面//////////////////////////////////////////////////
void Mainscene::initHelp()
{
    helpWidget*helpRule=new helpWidget();
    connect(ui->actionhelp,&QAction::triggered,[=](){
       helpRule->setGeometry(this->geometry());
       this->hide();
       helpRule->show();
       connect(helpRule,&helpWidget::back,[=](){
           this->setGeometry(helpRule->geometry());
           this->show();
           helpRule->hide();
       });
    });
}
/////////////////////////////////////重写绘图事件/////////////////////////////
void Mainscene::paintEvent(QPaintEvent *event)
{
    //创建画家对象和绘图设备(this)
    QPainter Painter(this);
    Painter.drawPixmap(0,MENUBAR_INTERVAL,mainMap);
}
