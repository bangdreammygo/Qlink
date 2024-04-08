#include "singleplayer.h"
#include "ui_singleplayer.h"
///////////////////////////////////////构造函数///////////////////////////////
Singleplayer::Singleplayer(int sceneNum,int bgmNum,  QWidget *parent) :QMainWindow(parent),ui(new Ui::Singleplayer)
{
    ui->setupUi(this);
    //初始化场景
    initScene( sceneNum, bgmNum);
    mapNum=sceneNum;
    backgmNum=bgmNum;
    //初始化框框
    initBox();
    //启动游戏
    play();
}
///////////////////////////////////////析构函数///////////////////////////////////////////////
Singleplayer::~Singleplayer()
{
    delete ui;
}
//////////////////////////////////重写绘图事件/////////////////////////////////////////
void Singleplayer::paintEvent(QPaintEvent *event)
{
     QPainter painter(this);
     //画背景图
     painter.drawPixmap(0,MENUBAR_INTERVAL,singleMap);
     //画边框
     painter.drawPixmap(GAME_WIDTH,MENUBAR_INTERVAL,markBox);
     //接着依据数组的具体值画方块和人物
     //先把各自的pixmap加载好,避免画图的时候调用耽误时间
     //加载方块,其中1为常态，2为激发态
     QPixmap luo1;        luo1.load(LUOSAITA_NOR_PATH);        QPixmap luo2;    luo2.load(LUOSAITA_ACT_PATH);
     QPixmap lif1;        lif1.load(LIF_NOR_PATH);             QPixmap lif2;    lif2.load(LIF_ACT_PATH);
     QPixmap arf1;        arf1.load(ARFA_NOR_PATH);            QPixmap arf2;    arf2.load(ARFA_ACT_PATH);
     QPixmap bnk1;        bnk1.load(BIANKA_NOR_PATH);          QPixmap bnk2;    bnk2.load(BIANKA_ACT_PATH);
     QPixmap nanami1;     nanami1.load(NANAMI_NOR_PATH);       QPixmap nanami2; nanami2.load(NANAMI_ACT_PATH);
     QPixmap lxy1;        lxy1.load(LUSIYA_NOR_PATH);          QPixmap lxy2;    lxy2.load(LUSIYA_ACT_PATH);
     QPixmap sln1;        sln1.load(SALINA_NOR_PATH);          QPixmap sln2;    sln2.load(SALINA_ACT_PATH);
     QPixmap wela1;       wela1.load(WEILA_NOR_PATH);          QPixmap wela2;   wela2.load(WEILA_ACT_PATH);
     QPixmap luna1;       luna1.load(LUNA_NOR_PATH);           QPixmap luna2;   luna2.load(LUNA_ACT_PATH);
     QPixmap qu1;         qu1.load(QU_NOR_PATH);               QPixmap qu2;     qu2.load(QU_ACT_PATH);
     //加载高亮态
     QPixmap luo3;         luo3.load(LUOSITA_HINT_PATH);
     QPixmap lif3;         lif3.load(LIF_HIINT_PATH);
     QPixmap arf3;         arf3.load(ARFA_HINT_PATH);
     QPixmap bnk3;         bnk3.load(BIANKA_HINT_PATH);
     QPixmap nanami3;      nanami3.load(NANAMI_HINT_PATH);
     QPixmap lxy3;         lxy3.load(LUSIYA_HINT_PATH);
     QPixmap sln3;         sln3.load(SALINA_HINT_PATH);
     QPixmap wela3;        wela3.load(WEILA_HINT_PATH);
     QPixmap luna3;        luna3.load(LUNA_HINT_PATH);
     QPixmap  qu3;         qu3.load(QU_HINT_PATH);
     //开始遍历方块地图作画
     for(int i=LINK_START_ROW-1;i<LINK_END_ROW;i++){
         for(int j=LINK_START_COL-1;j<LINK_END_COL;j++){
             if(allMap[i][j].pixNum==0)continue;//是零就直接返回不耽误时间
             int x=j*60;
             int y=i*60+MENUBAR_INTERVAL;
             if(allMap[i][j].isActive==false){//isActive没有被激活，说明还是常态
             if(allMap[i][j].pixNum==LUOSAITA_NUM) {painter.drawPixmap(x,y,luo1);}
             if(allMap[i][j].pixNum==LIF_NUM) {painter.drawPixmap(x,y,lif1);}
             if(allMap[i][j].pixNum==ARFA_NUM){painter.drawPixmap(x,y,arf1);}
             if(allMap[i][j].pixNum==BIANKA_NUM){painter.drawPixmap(x,y,bnk1);}
             if(allMap[i][j].pixNum==NANAMI_NUM){painter.drawPixmap(x,y,nanami1);}
             if(allMap[i][j].pixNum==LUSIYA_NUM){painter.drawPixmap(x,y,lxy1);}
             if(allMap[i][j].pixNum==SALINA_NUM){painter.drawPixmap(x,y,sln1);}
             if(allMap[i][j].pixNum==WEILA_NUM){painter.drawPixmap(x,y,wela1);}
             if(allMap[i][j].pixNum==LUNA_NUM){painter.drawPixmap(x,y,luna1);}
             if(allMap[i][j].pixNum==QU_NUM){painter.drawPixmap(x,y,qu1);}
             }
             //画高亮状态（等级比普通高，比激活低）
             if(allMap[i][j].isHint==true){
                 //首先场上的高亮方块个数需要加一(高亮函数开启时才激活此判定)
                 if(isStartHint==true)haveHint++;
                 //其次再是画图高亮方块
                 if(allMap[i][j].pixNum==LUOSAITA_NUM) {painter.drawPixmap(x,y,luo3);}
                 if(allMap[i][j].pixNum==LIF_NUM) {painter.drawPixmap(x,y,lif3);}
                 if(allMap[i][j].pixNum==ARFA_NUM){painter.drawPixmap(x,y,arf3);}
                 if(allMap[i][j].pixNum==BIANKA_NUM){painter.drawPixmap(x,y,bnk3);}
                 if(allMap[i][j].pixNum==NANAMI_NUM){painter.drawPixmap(x,y,nanami3);}
                 if(allMap[i][j].pixNum==LUSIYA_NUM){painter.drawPixmap(x,y,lxy3);}
                 if(allMap[i][j].pixNum==SALINA_NUM){painter.drawPixmap(x,y,sln3);}
                 if(allMap[i][j].pixNum==WEILA_NUM){painter.drawPixmap(x,y,wela3);}
                 if(allMap[i][j].pixNum==LUNA_NUM){painter.drawPixmap(x,y,luna3);}
                 if(allMap[i][j].pixNum==QU_NUM){painter.drawPixmap(x,y,qu3);}
             }
             if(allMap[i][j].isActive==true){//说明是激活态，则绘制激活态图片
                 if(allMap[i][j].pixNum==LUOSAITA_NUM) {painter.drawPixmap(x,y,luo2);continue;}
                 if(allMap[i][j].pixNum==LIF_NUM) {painter.drawPixmap(x,y,lif2);continue;}
                 if(allMap[i][j].pixNum==ARFA_NUM){painter.drawPixmap(x,y,arf2);continue;}
                 if(allMap[i][j].pixNum==BIANKA_NUM){painter.drawPixmap(x,y,bnk2);continue;}
                 if(allMap[i][j].pixNum==NANAMI_NUM){painter.drawPixmap(x,y,nanami2);continue;}
                 if(allMap[i][j].pixNum==LUSIYA_NUM){painter.drawPixmap(x,y,lxy2);continue;}
                 if(allMap[i][j].pixNum==SALINA_NUM){painter.drawPixmap(x,y,sln2);continue;}
                 if(allMap[i][j].pixNum==WEILA_NUM){painter.drawPixmap(x,y,wela2);continue;}
                 if(allMap[i][j].pixNum==LUNA_NUM){painter.drawPixmap(x,y,luna2);continue;}
                 if(allMap[i][j].pixNum==QU_NUM){painter.drawPixmap(x,y,qu2);continue;}
             }
         }
     }
     //画时间道具
     for(int i=0;i<4;i++){
         if(timeprop[i].isUsed==true) painter.drawPixmap(timeprop[i].propX,timeprop[i].propY,timeprop[i].propTime);
     }
     //画重排道具
     for(int i=0;i<2;i++){
         if(shuffleMap[i].isUsed==true) painter.drawPixmap(shuffleMap[i].propX,shuffleMap[i].propY,shuffleMap[i].propShu);
     }
     //画高亮道具
     if(hintBlock.isUsed==true) painter.drawPixmap(hintBlock.propX,hintBlock.propY,hintBlock.propHint);
     //画人物(不管中间还要画什么，人物一定要留到最后画，因为人物显示最上层)
      painter.drawPixmap(Player.x,Player.y+MENUBAR_INTERVAL,Player.rolePix);
}
////////////////////////////////////初始化场景的函数/////////////////////////////
void Singleplayer::initScene(int sceneNum,int bgmNum)
{
    //先初始化随机数种子
    srand((unsigned int)time(NULL));
    //设置窗口尺寸
    setFixedSize(GAME_WIDTH+BOX_WIDTH,GAME_HEIGHT+MENUBAR_INTERVAL);
    //设置标题
    setWindowTitle("单人♂solon模式😍");
    //设置图标
    setWindowIcon(QIcon(TITLE_PATH));
    //设置背景图
    if(sceneNum==1)singleMap.load(GAME_BACKGROUND_PATH);
    if(sceneNum==2)singleMap.load(JUEHAI_PATH);
    if(sceneNum==3)singleMap.load(KEMIN_PATH);
    //设置边框
    markBox.load(MARKBPX_PATH);
    //场上激活个数为0
    activeNum=0;
    //加载音效
    dis=new QSound(DIS_MUSIC_PATH,this);
    //加载背景音乐
    if(bgmNum==1) bgm=new QSound(BGM_PATH1,this);
    if(bgmNum==2) bgm=new QSound(BGM_PATH2,this);
    if(bgmNum==3) bgm=new QSound(BGM_PATH3,this);
    bgm->setLoops(-1);
    bgm->play();
    //实现退出功能
    connect(ui->quit,&QAction::triggered,[=](){
        if(QMessageBox::Yes==QMessageBox::question(this,"退出","是否选择退出游戏"))
        {this->close();}
    });
    //实现返回功能
    connect(ui->return_3,&QAction::triggered,[=](){
        //判断是否要返回
        if(QMessageBox::Yes==QMessageBox::question(this,"确定选择","是否选择放弃当前进度返回")){
            emit back();
        }
    });
    //初始化10种方块(既有方块种类，又有方块下标)
    for(int i=0;i<10;i++){
        luo[i].pixNum=LUOSAITA_NUM; luo[i].fatherIdx=i;
        sln[i].pixNum=SALINA_NUM;   sln[i].fatherIdx=i;
        lxy[i].pixNum=LUSIYA_NUM;   lxy[i].fatherIdx=i;
        lif[i].pixNum=LIF_NUM;      lif[i].fatherIdx=i;
        arf[i].pixNum=ARFA_NUM;     arf[i].fatherIdx=i;
        nanami[i].pixNum=NANAMI_NUM;nanami[i].fatherIdx=i;
        wela[i].pixNum=WEILA_NUM;   wela[i].fatherIdx=i;
        bak[i].pixNum=BIANKA_NUM;   bak[i].fatherIdx=i;
        luna[i].pixNum=LUNA_NUM;    luna[i].fatherIdx=i;
        qu[i].pixNum=QU_NUM;        qu[i].fatherIdx=i;
    }
    //随机初始化地图
    //然后开始对每一个方块初始化
    randInition();
    //再将各个方块的访问下标全部置零，表示都没有被消除
     luoIdx=0;
     lifIdx=0;
     lxyIdx=0;
     nanamiIdx=0;
     bakIdx=0;
     arfIdx=0;
     welaIdx=0;
     slnIdx=0;
     lunaIdx=0;
     quIdx=0;
     //初始化玩家的位置
     randPlayerposition();
     //最后初始化外围一圈的方块坐标
     initSurround();
}
/////////////////////////初始化周围一圈方块的坐标参数///////////////////////////
void Singleplayer::initSurround()
{
  for(int i=0;i<GAME_ROW;i++){
      for(int j=0;j<GAME_COL;j++){
          allMap[i][j].blockRow=i+1;
          allMap[i][j].blockCol=j+1;
      }
  }
}
//////////////////////////////初始化框框的函数/////////////////////////////////////////
void Singleplayer::initBox()
{
    //第一个时间框
    ui->timeBox->setFixedSize(BOX_WIDTH,TIME_BOX_HEIGHT);
    ui->timeBox->move(GAME_WIDTH,0);
    ui->timeBox->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->timeBox->setAttribute(Qt::WA_TransparentForMouseEvents);
    QFont font1("华文新魏",15);
    ui->timeBox->setFont(font1);
    //第二个显示时间框
    ui->timeLab->setFixedSize(BOX_WIDTH,TIME_LAB_HEIGHT);
    ui->timeLab->move(GAME_WIDTH,0+TIME_BOX_HEIGHT);
    //设置文字更新到play()函数里更新,这里仅作初始化
    QString str=QString("剩余时间:%1秒").arg(gameTime);
    ui->timeLab->setText(str);
    QFont font2("华文行楷",20);
    ui->timeLab->setFont(font2);
    ui->timeLab->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->timeLab->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->timeLab->setStyleSheet("color:darkred");
    //第三个积分框
    ui->markBox->setFixedSize(BOX_WIDTH,TIME_BOX_HEIGHT);
    ui->markBox->move(GAME_WIDTH,0+TIME_BOX_HEIGHT+TIME_LAB_HEIGHT);
    ui->markBox->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->markBox->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->markBox->setFont(font1);
    //第四个显示实时积分
    ui->markLab->setFixedSize(BOX_WIDTH,TIME_LAB_HEIGHT);
    ui->markLab->move(GAME_WIDTH,0+TIME_BOX_HEIGHT*2+TIME_LAB_HEIGHT);
    //设置文字更新到play()函数里更新,这里仅作初始化
    QString str2=QString("已消除%1个").arg(haveEliminated);
    ui->markLab->setText(str2);
    ui->markLab->setFont(font2);
    ui->markLab->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->markLab->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->markLab->setStyleSheet("color:darkblue");
    //最后一个消息提示框
    ui->informationBox->setFixedSize(BOX_WIDTH,GAME_HEIGHT-2*TIME_LAB_HEIGHT-2*TIME_BOX_HEIGHT);
    ui->informationBox->move(GAME_WIDTH,0+2*TIME_LAB_HEIGHT+2*TIME_BOX_HEIGHT);
    ui->informationBox->setText("状态正常");
    ui->informationBox->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->informationBox->setAttribute(Qt::WA_TransparentForMouseEvents);
    QFont font3("华文隶书",25);
    ui->informationBox->setFont(font3);
    ui->informationBox->setStyleSheet("color:white");
}
///////////////////////////////////////////更新提示框的函数///////////////////////////////
void Singleplayer::updateBox()
{
    QFont font2("华文行楷",20);
    ui->markLab->setFixedSize(BOX_WIDTH,TIME_LAB_HEIGHT);
    ui->markLab->move(GAME_WIDTH,0+TIME_BOX_HEIGHT*2+TIME_LAB_HEIGHT);
    //设置文字更新到play()函数里更新,这里仅作初始化
    QString str2=QString("已消除%1个").arg(haveEliminated);
    ui->markLab->setText(str2);
    ui->markLab->setFont(font2);
    ui->markLab->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->markLab->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->markLab->setStyleSheet("color:darkblue");
    ui->informationBox->setText("状态正常");
    ui->informationBox->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->informationBox->setAttribute(Qt::WA_TransparentForMouseEvents);
    QFont font3("华文隶书",25);
    ui->informationBox->setFont(font3);
    ui->informationBox->setStyleSheet("color:green");
    //连接错误
    if(canLink==false){
        problemInterval++;
        if(problemInterval==10) {canLink=true; problemInterval=0;}
        ui->informationBox->setText("错误连接");
        ui->informationBox->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->informationBox->setAttribute(Qt::WA_TransparentForMouseEvents);
        QFont font3("华文隶书",25);
        ui->informationBox->setFont(font3);
        ui->informationBox->setStyleSheet("color:red");
    }
    //使用了加一秒道具
    if(plusTime==true){
            plusInterval++;
            if(plusInterval==10) {plusTime=false; plusInterval=0;}
            ui->informationBox->setText("+30秒");
            ui->informationBox->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            ui->informationBox->setAttribute(Qt::WA_TransparentForMouseEvents);
            QFont font3("华文隶书",25);
            ui->informationBox->setFont(font3);
            ui->informationBox->setStyleSheet("color:blue");
        }
    if(isShuffle==true){
            shuffleInterval++;
            if(shuffleInterval==10) {isShuffle=false; shuffleInterval=0;}
            ui->informationBox->setText("地图重排");
            ui->informationBox->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            ui->informationBox->setAttribute(Qt::WA_TransparentForMouseEvents);
            QFont font3("华文隶书",25);
            ui->informationBox->setFont(font3);
            ui->informationBox->setStyleSheet("color:blue");
        }
    if(isStartHint==true){
            ui->informationBox->setText("高亮时刻");
            ui->informationBox->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            ui->informationBox->setAttribute(Qt::WA_TransparentForMouseEvents);
            QFont font3("华文隶书",25);
            ui->informationBox->setFont(font3);
            ui->informationBox->setStyleSheet("color:blue");
        }
}
//////////////////////////////////////游戏启动(关联几个定时器事件)////////////////////////////////
void Singleplayer::play()
{

    //计时器1启动
    timer.start(TIMER_INTERVAL);
    //计时器2启动(1秒1动)
    timer2.start(1000);
    //计时器三设置
    hintTimer=new QTimer(this);
    hintTimer->start(1000);
    //将计时器事件关联起来
    connect((&timer),&QTimer::timeout,[=](){
        //每一跳更新一次全局信息
        updatePosition();
        //更新提示框
        updateBox();
        //生成时间道具
        generatePlusProp();
        //消除时间道具
        eliminatePlusprop();
        //生成重排道具
        generateShuffleProp();
        //消除重排道具
        eliminateShuffleprop();
        //生成高亮道具
        generateHint();
        //消除高亮道具
        eliminateHintprop();
        //高亮实现函数
        startHint();
        //每一跳刷新一次屏幕
        update();
    });
    //计时器
    connect((&timer2),&QTimer::timeout,[=](){
        gameTime--;
        if(gameTime==0) emit gameOver();
        QString str=QString("剩余时间:%1秒").arg(gameTime);
        ui->timeLab->setText(str);
        QFont font2("华文行楷",20);
        ui->timeLab->setFont(font2);
        ui->timeLab->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->timeLab->setAttribute(Qt::WA_TransparentForMouseEvents);
        ui->timeLab->setStyleSheet("color:darkred");
    });
    //将结束信号关联至结算场景
    connect(this,&Singleplayer::gameOver,[=](){
        //修正bug:当消除结束和时间归零同时发生，将会出现两个结算页面，修正从未触发过结束场景
        if(haveOver==false)
        {
        //先声明已经结束
        haveOver=true;
        //停止计时
        timer.stop();
        timer2.stop();
        //加载最终结算场景
        endScene=new Endwidget(haveEliminated*2+gameTime*3);
        endScene->setGeometry(this->geometry());
        endScene->show();
        this->hide();
        //接收来自最终场景的信号
        connect(endScene,&Endwidget::back,[=](){
            delete endScene;
            emit back();
        });
        }
    });
    //关联无解场景
    connect(this,&Singleplayer::noAnswer,[=](){
        //同理修复此处的bug
        if(haveOver==false){
        //声明结束
        haveOver=true;
        //停止计时
        timer.stop();
        timer2.stop();
        //加载最终结算场景
        endScene=new Endwidget(haveEliminated*2+gameTime*3,true);
        endScene->setGeometry(this->geometry());
        endScene->show();
        this->hide();
        //接收来自最终场景的信号
        connect(endScene,&Endwidget::back,[=](){
            delete endScene;
            emit back();
        });
        }
    });
    //关联道具定时器
    connect(hintTimer,&QTimer::timeout,[=](){
        if(isStartHint==true)tenSec++;
    });
    //暂停和继续
    connect(ui->accontinue,&QAction::triggered,[=](){
        hintTimer->start(1000);
        timer.start(TIMER_INTERVAL);
        timer2.start(1000);
    });
    connect(ui->stoponce,&QAction::triggered,[=](){
        hintTimer->stop();
        timer.stop();
        timer2.stop();
    });
    //读档与存档
    connect(ui->write,&QAction::triggered,[=](){
        writeFlie();
    });
    connect(ui->read,&QAction::triggered,[=](){
        readFile();
    });
    //外化暂停和存档
    connect(this,&Singleplayer::pause,[=](){
        hintTimer->stop();
        timer.stop();
        timer2.stop();
    });
    connect(this,&Singleplayer::archive,[=](){
        writeFlie();
    });
}
/////////////////////////////初始化消除方块的函数////////////////////////////////
void Singleplayer::randInition()
{
    for(int i=0;i<10;i++)arrMap[i]=1;
    for(int i=0;i<10;i++)arrMap[i+10]=2;
    for(int i=0;i<10;i++)arrMap[i+20]=3;
    for(int i=0;i<10;i++)arrMap[i+30]=4;
    for(int i=0;i<10;i++)arrMap[i+40]=5;
    for(int i=0;i<10;i++)arrMap[i+50]=6;
    for(int i=0;i<10;i++)arrMap[i+60]=7;
    for(int i=0;i<10;i++)arrMap[i+70]=8;
    for(int i=0;i<10;i++)arrMap[i+80]=9;
    for(int i=0;i<10;i++)arrMap[i+90]=10;
    std::random_shuffle(arrMap,arrMap+100);
    int k=0;
    for(int i=LINK_START_ROW-1;i<LINK_END_ROW;i++){
        for(int j=LINK_START_COL-1;j<LINK_END_COL;j++){
           int idx=arrMap[k++];
           if(idx==LUOSAITA_NUM){//抽到罗塞塔
              if(luoIdx<10){//10个还没放完，可以放进去,这里要顺便就把方块的坐标初始化掉
                 luo[luoIdx].blockRow=i+1;luo[luoIdx].blockCol=j+1;
                 allMap[i][j]=luo[luoIdx++];
                 continue;
              }
           }
           if(idx==LIF_NUM){
               if(lifIdx<10){//10个还没放完，可以放进去,这里要顺便就把方块的坐标初始化掉
                  lif[lifIdx].blockRow=i+1;lif[lifIdx].blockCol=j+1;
                  allMap[i][j]=lif[lifIdx++];
                   continue;
               }
           }
           if(idx==ARFA_NUM){
               if(arfIdx<10){//10个还没放完，可以放进去,这里要顺便就把方块的坐标初始化掉
                  arf[arfIdx].blockRow=i+1;arf[arfIdx].blockCol=j+1;
                  allMap[i][j]=arf[arfIdx++];
                   continue;
               }
               else { //不行就重抽
                   idx=rand()%10+1;}
           }
           if(idx==BIANKA_NUM){
               if(bakIdx<10){//10个还没放完，可以放进去,这里要顺便就把方块的坐标初始化掉
                  bak[bakIdx].blockRow=i+1;bak[bakIdx].blockCol=j+1;
                  allMap[i][j]=bak[bakIdx++];
                   continue;
               }
           }
           if(idx==NANAMI_NUM){
               if(nanamiIdx<10){//10个还没放完，可以放进去,这里要顺便就把方块的坐标初始化掉
                  nanami[nanamiIdx].blockRow=i+1;nanami[nanamiIdx].blockCol=j+1;
                  allMap[i][j]=nanami[nanamiIdx++];
                   continue;
               }
           }
           if(idx==LUSIYA_NUM){
               if(lxyIdx<10){//10个还没放完，可以放进去,这里要顺便就把方块的坐标初始化掉
                   lxy[lxyIdx].blockRow=i+1;lxy[lxyIdx].blockCol=j+1;
                   allMap[i][j]=lxy[lxyIdx++];
                   continue;
               }
           }
           if(idx==SALINA_NUM){
               if(slnIdx<10){//10个还没放完，可以放进去,这里要顺便就把方块的坐标初始化掉
                  sln[slnIdx].blockRow=i+1;sln[slnIdx].blockCol=j+1;
                  allMap[i][j]=sln[slnIdx++];
                   continue;
               }
           }
           if(idx==WEILA_NUM){
               if(welaIdx<10){//10个还没放完，可以放进去,这里要顺便就把方块的坐标初始化掉
                  wela[welaIdx].blockRow=i+1;wela[welaIdx].blockCol=j+1;
                  allMap[i][j]=wela[welaIdx++];
                   continue;
               }
          }
           if(idx==LUNA_NUM){
               if(lunaIdx<10){
                 luna[lunaIdx].blockRow=i+1;luna[lunaIdx].blockCol=j+1;
                 allMap[i][j]=luna[lunaIdx++];
                  continue;
               }
           }
           if(idx==QU_NUM){
               if(quIdx<10){
                   qu[quIdx].blockRow=i+1;qu[quIdx].blockCol=j+1;
                   allMap[i][j]=qu[quIdx++];
                   continue;
               }
           }
        }
    }
}
///////////////////////////////初始化玩家的位置/////////////////////////////
void Singleplayer::randPlayerposition()
{
    int row;
    int col;
    while(true)
    {
        row=rand()%GAME_ROW+1;
        col=rand()%GAME_COL+1;
        //找一处空地作为人物的初始位置
        if(allMap[row-1][col-1].pixNum==0){
            break;
        }
    }
    Player.roleRow=row;
    Player.roleCol=col;
    Player.updatePosition();
}
////////////////////////////全局坐标更新(含消除)////////////////////////////////////////
void Singleplayer::updatePosition()
{
    //更新人物坐标
    updatePlayerposition();
    type=0;//用完置零
    //判断是否需要调用两个判断函数
    //激活个数少于两个，不用判断消除，也不用判断有解
    if(activeNum<=1){return;}
    else{//说明已经激活了两个了，需要判断有解与否了
        //先把激活个数重新置零
        activeNum=0;
        if(canEliminate(allMap[tmp1Row-1][tmp1Col-1],allMap[tmp2Row-1][tmp2Col-1])==false){
            //消不掉,全部还原即可
            canLink=false;
            allMap[tmp1Row-1][tmp1Col-1].isActive=false;
            allMap[tmp2Row-1][tmp2Col-1].isActive=false;
        }
        else{//消得掉,先消除，再判断余下是否有解
             dis->play();
             doEliminate();
/////////////////////////////判断剩余解的函数/////////////////////////////////////
         //先逻辑实现，后续再切换画面
         if(canStillEliminate()==true) qDebug()<<"有解";
         if(canStillEliminate()==false&&haveEliminated!=100) emit noAnswer();
        }
    }
    //判定最终结束(暂时逻辑实现)
    if(haveEliminated==100){
        timer.stop();
        QTimer::singleShot(500,this,[=](){//延迟释放信号
             emit gameOver();
        });
    }
}
///////////////////////////////更新人物坐标（也包含更新方块激活状态）////////////////////////////////////
void Singleplayer::updatePlayerposition(){
    //没动键盘不作为
    if(type==0){type=0;}
    //左移
    if(type==LEFT){
        //左边可以走才行
        if(Player.roleCol>1){
            //如果左边没有方块，正常移动
            if(allMap[Player.roleRow-1][Player.roleCol-2].pixNum==0){Player.movePosition(LEFT);}
            //有方块则激活该方块,并进行判断
            else{
                if(allMap[Player.roleRow-1][Player.roleCol-2].isActive==false){
                 allMap[Player.roleRow-1][Player.roleCol-2].isActive=true;activeNum++;
                   //第一个被激活的方块，放入tmp1里
                   if(activeNum==1){tmp1Row=Player.roleRow; tmp1Col=Player.roleCol-1;}
                   //否则就放tmp2
                   else{tmp2Row=Player.roleRow;tmp2Col=Player.roleCol-1;}
                }
            }
        }
    }
    //右移
   else if(type==RIGHT){
        if(Player.roleCol<GAME_COL){
            //如果右边没有方块，正常移动
            if(allMap[Player.roleRow-1][Player.roleCol].pixNum==0){Player.movePosition(RIGHT);}
            //有方块则激活该方块,并进行判断
            else{
                if(allMap[Player.roleRow-1][Player.roleCol].isActive==false){
                allMap[Player.roleRow-1][Player.roleCol].isActive=true;activeNum++;
                   //第一个被激活的方块，放入tmp1里,否则放tmp2里
                   if(activeNum==1){tmp1Row=Player.roleRow;tmp1Col=Player.roleCol+1;}
                   else{tmp2Row=Player.roleRow;tmp2Col=Player.roleCol+1;}
                }
            }
        }
    }
    //上移
    else if(type==KEY_UP){
         if(Player.roleRow>1){
             //如果上边没有方块，正常移动
             if(allMap[Player.roleRow-2][Player.roleCol-1].pixNum==0){Player.movePosition(KEY_UP);}
             //有方块则激活该方块,并进行判断
             else{
                 if(allMap[Player.roleRow-2][Player.roleCol-1].isActive==false){
                     allMap[Player.roleRow-2][Player.roleCol-1].isActive=true;activeNum++;
                        //第一个被激活的方块，放入tmp1里,否则放tmp2里
                        if(activeNum==1){tmp1Row=Player.roleRow-1;tmp1Col=Player.roleCol;}
                        else{tmp2Row=Player.roleRow-1;tmp2Col=Player.roleCol;}
                 }
             }
         }
     }
    //下移
    else if(type==DOWN){
         if(Player.roleRow<GAME_ROW){
             //如果上边没有方块，正常移动
             if(allMap[Player.roleRow][Player.roleCol-1].pixNum==0){Player.movePosition(DOWN);}
             //有方块则激活该方块,并进行判断
             else{
                 if(allMap[Player.roleRow][Player.roleCol-1].isActive==false){
                     allMap[Player.roleRow][Player.roleCol-1].isActive=true;activeNum++;
                        //第一个被激活的方块，放入tmp1里,否则放tmp2里
                        if(activeNum==1){tmp1Row=Player.roleRow+1;tmp1Col=Player.roleCol;}
                        else{tmp2Row=Player.roleRow+1;tmp2Col=Player.roleCol;}
                 }
             }
         }
     }
}
/////////////////////////////重写键盘控制函数///////////////////////////////////
void Singleplayer::keyPressEvent(QKeyEvent *event)
{
    //依照不同的键盘按键，给予type不同的赋值
    if(event->key()==Qt::Key_A) {type=LEFT;}
    else if(event->key()==Qt::Key_D){type=RIGHT;}
    else if(event->key()==Qt::Key_W){type=KEY_UP;}
    else if(event->key()==Qt::Key_S){type=DOWN;}
    //P暂停Q存档
    if(event->key()==Qt::Key_P)emit pause();
    if(event->key()==Qt::Key_Q)emit archive();
}
////////////////////////////重点函数：判断是否可以消除////////////////////////////////////
bool Singleplayer::canEliminate(Block b1, Block b2)
{
    //首先两个得一样才能消
    if(b1.pixNum!=b2.pixNum){return false;}
    //其次无法接触到的也不能消(方便后续看有无解),即，上下左右均无空地
    if(allMap[b1.blockRow][b1.blockCol-1].pixNum!=0&&allMap[b1.blockRow-2][b1.blockCol-1].pixNum!=0&&
       allMap[b1.blockRow-1][b1.blockCol].pixNum!=0&&allMap[b1.blockRow-1][b1.blockCol-2].pixNum!=0     )
      {return false;}
    if(allMap[b2.blockRow][b2.blockCol-1].pixNum!=0&&allMap[b2.blockRow-2][b2.blockCol-1].pixNum!=0&&
       allMap[b2.blockRow-1][b2.blockCol].pixNum!=0&&allMap[b2.blockRow-1][b2.blockCol-2].pixNum!=0     )
      {return false;}
    /////////////////////////////////////判断零折消除(已经实现)(单独封装)
    if(noCornor(b1,b2)==true) return true;
    ////////////////////////////////////判断一折消除（单独封装）(拆成两个零折消除即可)(已完成)
    if(oneCornor(b1,b2)==true) return true;
    ////////////////////////////////////判断二折消除(单独封装)(零折加一折)
    if(twoCornor(b1,b2)==true) return true;
    //以上都不行则直接返回false
    return false;
}
////////////////////////////封装零折判断//////////////////////////////////
bool Singleplayer::noCornor(Block b1, Block b2)
{
    //同行不同列
    if(b1.blockRow==b2.blockRow){
        //1.紧挨
        if(qMax(b1.blockCol,b2.blockCol)==qMin(b1.blockCol,b2.blockCol)+1) return true;
        //2.隔着的
        bool flag=true;
        //遍历两个之间的方块，如果有其他方块则不能零折(注意是之间，所以从+1开始，到-1为止)
        for(int i=qMin(b1.blockCol,b2.blockCol);i<qMax(b1.blockCol,b2.blockCol)-1;i++){if(allMap[b1.blockRow-1][i].pixNum!=0) {flag=false;break;} }
        if(flag) return true;
    }
    //同列不同行
    if(b1.blockCol==b2.blockCol){
        //1.紧挨
        if(qMax(b1.blockRow,b2.blockRow)==1+qMin(b1.blockRow,b2.blockRow))return true;
        //2.隔着的
        bool flag=true;
        //遍历两个之间的方块，如果有其他方块则不能零折
        for(int i=qMin(b1.blockRow,b2.blockRow);i<qMax(b1.blockRow,b2.blockRow)-1;i++){if(allMap[i][b1.blockCol-1].pixNum!=0) {flag=false;break; }}
        if(flag) return true;
    }
     return false;
}
///////////////////////////////封装一折判断/////////////////////////////////
bool Singleplayer::oneCornor(Block b1, Block b2)
{
    //b1左上b2右下
    if(b1.blockRow<b2.blockRow&&b1.blockCol<b2.blockCol){
        //下右消除
        if(allMap[b2.blockRow-1][b1.blockCol-1].pixNum==0&&(noCornor(allMap[b2.blockRow-1][b1.blockCol-1],b1)&&noCornor(allMap[b2.blockRow-1][b1.blockCol-1],b2))) return true;
        //右下消除
        if(allMap[b1.blockRow-1][b2.blockCol-1].pixNum==0&&(noCornor(allMap[b1.blockRow-1][b2.blockCol-1],b1)&&noCornor(allMap[b1.blockRow-1][b2.blockCol-1],b2))) return true;
    }
    //b2左上b1右下
    if(b2.blockRow<b1.blockRow&&b2.blockCol<b1.blockCol){
        //下右消除
        if(allMap[b1.blockRow-1][b2.blockCol-1].pixNum==0&&(noCornor(allMap[b1.blockRow-1][b2.blockCol-1],b2)&&noCornor(allMap[b1.blockRow-1][b2.blockCol-1],b1))) return true;
        //右下消除
        if(allMap[b2.blockRow-1][b1.blockCol-1].pixNum==0&&(noCornor(allMap[b2.blockRow-1][b1.blockCol-1],b2)&&noCornor(allMap[b2.blockRow-1][b1.blockCol-1],b1))) return true;
    }
    //b1右上b2左下
    if(b1.blockRow<b2.blockRow&&b1.blockCol>b2.blockCol){
        //下左消除
        if(allMap[b2.blockRow-1][b1.blockCol-1].pixNum==0&&(noCornor(allMap[b2.blockRow-1][b1.blockCol-1],b1)&&noCornor(allMap[b2.blockRow-1][b1.blockCol-1],b2)))return true;
        //左下消除
        if(allMap[b1.blockRow-1][b2.blockCol-1].pixNum==0&&(noCornor(allMap[b1.blockRow-1][b2.blockCol-1],b1)&&noCornor(allMap[b1.blockRow-1][b2.blockCol-1],b2)))return true;
    }
    //b2右上b1左下
    if(b2.blockRow<b1.blockRow&&b2.blockCol>b1.blockCol){
        //下左消除
        if(allMap[b1.blockRow-1][b2.blockCol-1].pixNum==0&&(noCornor(allMap[b1.blockRow-1][b2.blockCol-1],b1)&&noCornor(allMap[b1.blockRow-1][b2.blockCol-1],b2)))return true;
        //左下消除
        if(allMap[b2.blockRow-1][b1.blockCol-1].pixNum==0&&(noCornor(allMap[b2.blockRow-1][b1.blockCol-1],b1)&&noCornor(allMap[b2.blockRow-1][b1.blockCol-1],b2)))return true;
    }
    //都不行就证明不能一折消除
    return false;
}
/////////////////////////////封装二折判断函数/////////////////////////////////////
bool Singleplayer::twoCornor(Block b1, Block b2)
{
     //1.竖二折，内部二折,b1在左边
    if(b1.blockCol<b2.blockCol){
        for(int i=b1.blockCol;i<b2.blockCol-1;i++){
            if(allMap[b1.blockRow-1][i].pixNum!=0) break;
            if(oneCornor(b2,allMap[b1.blockRow-1][i])==true) return true;
        }
    }
    //2.竖二折，内部二折,b2在左边
   if(b2.blockCol<b1.blockCol){
       for(int i=b2.blockCol;i<b1.blockCol-1;i++){
           if(allMap[b2.blockRow-1][i].pixNum!=0) break;
           if(oneCornor(b1,allMap[b2.blockRow-1][i])==true) return true;
       }
   }
    //3.横二折，二折在内部，b1在上面
   if(b1.blockRow<b2.blockRow){
       for(int i=b1.blockRow;i<b2.blockRow-1;i++){
           if(allMap[i][b1.blockCol-1].pixNum!=0) break;
           if(oneCornor(b2,allMap[i][b1.blockCol-1])==true) return true;
       }
   }
   //4.横二折，二折在内部，b2在上面
  if(b2.blockRow<b1.blockRow){
      for(int i=b2.blockRow;i<b1.blockRow-1;i++){
          if(allMap[i][b2.blockCol-1].pixNum!=0) break;
          if(oneCornor(b1,allMap[i][b2.blockCol-1])==true) return true;
      }
  }
  //5.竖二折,外部二折，b1在左边
  if(b1.blockCol<=b2.blockCol){
      //左延伸
    for(int i=b1.blockCol-2;i>=LINK_START_COL-2;i--){
        if(allMap[b1.blockRow-1][i].pixNum!=0) break;
        if(oneCornor(allMap[b1.blockRow-1][i],b2)==true) return true;
    }
     //右延伸
    for(int i=b2.blockCol;i<=LINK_END_COL;i++){
        if(allMap[b2.blockRow-1][i].pixNum!=0) break;
        if(oneCornor(allMap[b2.blockRow-1][i],b1)==true) return true;
    }
  }
  //6.竖二折,外部二折，b2在左边
  if(b2.blockCol<b1.blockCol){
      //左延伸
    for(int i=b2.blockCol-2;i>=LINK_START_COL-2;i--){
        if(allMap[b2.blockRow-1][i].pixNum!=0) break;
        if(oneCornor(allMap[b2.blockRow-1][i],b1)==true) return true;
    }
     //右延伸
    for(int i=b1.blockCol;i<=LINK_END_COL;i++){
        if(allMap[b1.blockRow-1][i].pixNum!=0) break;
        if(oneCornor(allMap[b1.blockRow-1][i],b2)==true) return true;
    }
  }
  //7.横二折，外部二折，b1在上面
  if(b1.blockRow<=b2.blockRow){
    //上延伸
      for(int i=b1.blockRow-2;i>=LINK_START_ROW-2;i--){
          if(allMap[i][b1.blockCol-1].pixNum!=0) break;
          if(oneCornor(b2,allMap[i][b1.blockCol-1])==true) return true;
      }
    //下延伸
      for(int i=b2.blockRow;i<=LINK_END_ROW;i++){
          if(allMap[i][b2.blockCol-1].pixNum!=0) break;
          if(oneCornor(allMap[i][b2.blockCol-1],b1)==true) return true;
      }
  }
  //8.横二折，外部二折，b2在上面
  if(b2.blockRow<=b1.blockRow){
    //上延伸
      for(int i=b2.blockRow-2;i>=LINK_START_ROW-2;i--){
          if(allMap[i][b2.blockCol-1].pixNum!=0) break;
          if(oneCornor(b1,allMap[i][b2.blockCol-1])==true) return true;
      }
    //下延伸
      for(int i=b1.blockRow;i<=LINK_END_ROW;i++){
          if(allMap[i][b1.blockCol-1].pixNum!=0) break;
          if(oneCornor(allMap[i][b1.blockCol-1],b2)==true) return true;
      }
  }
  return false;
}
/////////////////////////////判断剩余是否有解的函数//////////////////////////////////////////////////
bool Singleplayer::canStillEliminate()
{
  //判断有解与否，思路：从第一个数组开始一个一个遍历
   for(int i=0;i<9;i++){
       if(luo[i].pixNum==0) continue;
       else{
           for(int j=i+1;j<10;j++){
               if(canEliminate(luo[i],luo[j])==true) return true;
           }
       }
   }
   for(int i=0;i<9;i++){
       if(lif[i].pixNum==0) continue;
       else{
           for(int j=i+1;j<10;j++){
               if(canEliminate(lif[i],lif[j])==true) return true;
           }
       }
   }
   for(int i=0;i<9;i++){
       if(arf[i].pixNum==0) continue;
       else{
           for(int j=i+1;j<10;j++){
               if(canEliminate(arf[i],arf[j])==true) return true;
           }
       }
   }
   for(int i=0;i<9;i++){
       if(bak[i].pixNum==0) continue;
       else{
           for(int j=i+1;j<10;j++){
               if(canEliminate(bak[i],bak[j])==true) return true;
           }
       }
   }
   for(int i=0;i<9;i++){
       if(nanami[i].pixNum==0) continue;
       else{
           for(int j=i+1;j<10;j++){
               if(canEliminate(nanami[i],nanami[j])==true) return true;
           }
       }
   }
   for(int i=0;i<9;i++){
       if(lxy[i].pixNum==0) continue;
       else{
           for(int j=i+1;j<10;j++){
               if(canEliminate(lxy[i],lxy[j])==true) return true;
           }
       }
   }
   for(int i=0;i<9;i++){
       if(sln[i].pixNum==0) continue;
       else{
           for(int j=i+1;j<10;j++){
               if(canEliminate(sln[i],sln[j])==true) return true;
           }
       }
   }
   for(int i=0;i<9;i++){
       if(wela[i].pixNum==0) continue;
       else{
           for(int j=i+1;j<10;j++){
               if(canEliminate(wela[i],wela[j])==true) return true;
           }
       }
   }
   for(int i=0;i<9;i++){
       if(luna[i].pixNum==0) continue;
       else{
           for(int j=i+1;j<10;j++){
               if(canEliminate(luna[i],luna[j])==true) return true;
           }
       }
   }
   for(int i=0;i<9;i++){
       if(qu[i].pixNum==0) continue;
       else{
           for(int j=i+1;j<10;j++){
               if(canEliminate(qu[i],qu[j])==true) return true;
           }
       }
   }
   //遍历结束都无解说明确实无解，则返回false提示切换窗口至无解窗口
   return false;
}
/////////////////////////////实际执行的消除函数/////////////////////////////////////////////////
void Singleplayer::doEliminate()
{
    int kind=allMap[tmp1Row-1][tmp1Col-1].pixNum;
    int f1Idx=allMap[tmp1Row-1][tmp1Col-1].fatherIdx;
    int f2Idx=allMap[tmp2Row-1][tmp2Col-1].fatherIdx;
    //先在地图中消除
    allMap[tmp1Row-1][tmp1Col-1].pixNum=0;
    allMap[tmp2Row-1][tmp2Col-1].pixNum=0;
    haveEliminated+=2;
    //再在数组内也实现消除
    if(kind==LUOSAITA_NUM){
        luo[f1Idx].pixNum=0;
        luo[f2Idx].pixNum=0;
        return;
    }
    if(kind==LIF_NUM){
        lif[f1Idx].pixNum=0;
        lif[f2Idx].pixNum=0;
        return;
    }
    if(kind==ARFA_NUM){
        arf[f1Idx].pixNum=0;
        arf[f2Idx].pixNum=0;
        return;
    }
    if(kind==BIANKA_NUM){
        bak[f1Idx].pixNum=0;
        bak[f2Idx].pixNum=0;
        return;
    }
    if(kind==NANAMI_NUM){
        nanami[f1Idx].pixNum=0;
        nanami[f2Idx].pixNum=0;
        return;
    }
    if(kind==LUSIYA_NUM){
        lxy[f1Idx].pixNum=0;
        lxy[f2Idx].pixNum=0;
        return;
    }
    if(kind==SALINA_NUM){
        sln[f1Idx].pixNum=0;
        sln[f2Idx].pixNum=0;
        return;
    }
    if(kind==WEILA_NUM){
        wela[f1Idx].pixNum=0;
        wela[f2Idx].pixNum=0;
        return;
    }
    if(kind==LUNA_NUM){
        luna[f1Idx].pixNum=0;
        luna[f2Idx].pixNum=0;
        return;
    }
    if(kind==QU_NUM){
        qu[f1Idx].pixNum=0;
        qu[f2Idx].pixNum=0;
        return;
    }
}
//////////////////////////////生成+1时间道具/////////////////////////////////////////////////////////////////
void Singleplayer::generatePlusProp()
{
    //消除数达到20个，40个，60个，80个时会出现的道具
    //第一次出现
    if(haveEliminated==20&&timeprop[0].isInit==false){
        int r;int c;
        while (true) {
           r=rand()%GAME_ROW+1;
           c=rand()%GAME_COL+1;
           if(hintBlock.isUsed==true){if(r==hintBlock.propRow&&c==hintBlock.propCol){continue;}}
           if(shuffleMap[0].isUsed==true){ if(r==shuffleMap[0].propRow&&c==shuffleMap[0].propCol) continue;}
           if(shuffleMap[1].isUsed==true){ if(r==shuffleMap[1].propRow&&c==shuffleMap[1].propCol) continue;}
           if(allMap[r-1][c-1].pixNum==0&&(Player.roleRow!=r||Player.roleCol!=c)) break;
        }
        timeprop[0].isInit=true;
        timeprop[0].isUsed=true;
        timeprop[0].propRow=r;timeprop[0].propCol=c;
        timeprop[0].updateposition();
    }
    //第二次出现
    if(haveEliminated==40&&timeprop[1].isInit==false){
        int r;int c;
        while (true) {
           r=rand()%GAME_ROW+1;
           c=rand()%GAME_COL+1;
           if(hintBlock.isUsed==true){if(r==hintBlock.propRow&&c==hintBlock.propCol){continue;}}
           if(shuffleMap[0].isUsed==true){ if(r==shuffleMap[0].propRow&&c==shuffleMap[0].propCol) continue;}
           if(shuffleMap[1].isUsed==true){ if(r==shuffleMap[1].propRow&&c==shuffleMap[1].propCol) continue;}
           if(timeprop[0].isUsed==true){
               if(r==timeprop[0].propRow&&c==timeprop[0].propCol) continue;
           }
           if(allMap[r-1][c-1].pixNum==0&&(Player.roleRow!=r||Player.roleCol!=c)) break;
        }
        timeprop[1].isInit=true;
        timeprop[1].isUsed=true;
        timeprop[1].propRow=r;timeprop[1].propCol=c;
        timeprop[1].updateposition();
    }
    //第三次出现
    if(haveEliminated==60&&timeprop[2].isInit==false){
        int r;int c;
        while (true) {
           r=rand()%GAME_ROW+1;
           c=rand()%GAME_COL+1;
           if(hintBlock.isUsed==true){if(r==hintBlock.propRow&&c==hintBlock.propCol){continue;}}
           if(shuffleMap[0].isUsed==true){ if(r==shuffleMap[0].propRow&&c==shuffleMap[0].propCol) continue;}
           if(shuffleMap[1].isUsed==true){ if(r==shuffleMap[1].propRow&&c==shuffleMap[1].propCol) continue;}
           if(timeprop[0].isUsed==true){
               if(r==timeprop[0].propRow&&c==timeprop[0].propCol) continue;
           }
           if(timeprop[1].isUsed==true){
               if(r==timeprop[1].propRow&&c==timeprop[1].propCol) continue;
           }
           if(allMap[r-1][c-1].pixNum==0&&(Player.roleRow!=r||Player.roleCol!=c)) break;
        }
        timeprop[2].isInit=true;
        timeprop[2].isUsed=true;
        timeprop[2].propRow=r;timeprop[2].propCol=c;
        timeprop[2].updateposition();
    }
    //第四次出现
    if(haveEliminated==80&&timeprop[3].isInit==false){
        int r;int c;
        while (true) {
           r=rand()%GAME_ROW+1;
           c=rand()%GAME_COL+1;
           if(hintBlock.isUsed==true){if(r==hintBlock.propRow&&c==hintBlock.propCol){continue;}}
           if(shuffleMap[0].isUsed==true){ if(r==shuffleMap[0].propRow&&c==shuffleMap[0].propCol) continue;}
           if(shuffleMap[1].isUsed==true){ if(r==shuffleMap[1].propRow&&c==shuffleMap[1].propCol) continue;}
           if(timeprop[0].isUsed==true){
               if(r==timeprop[0].propRow&&c==timeprop[0].propCol) continue;
           }
           if(timeprop[1].isUsed==true){
               if(r==timeprop[1].propRow&&c==timeprop[1].propCol) continue;
           }
           if(timeprop[2].isUsed==true){
               if(r==timeprop[2].propRow&&c==timeprop[2].propCol) continue;
           }
           if(allMap[r-1][c-1].pixNum==0&&(Player.roleRow!=r||Player.roleCol!=c)) break;
        }
        timeprop[3].isInit=true;
        timeprop[3].isUsed=true;
        timeprop[3].propRow=r;timeprop[3].propCol=c;
        timeprop[3].updateposition();
    }
}
/////////////////////////////////消除加一道具///////////////////////////////////////////////////////////////
void Singleplayer::eliminatePlusprop()
{
    for(int i=0;i<4;i++){
        if(timeprop[i].isInit==false) continue;
        if(timeprop[i].isUsed==false) continue;
        if(timeprop[i].propRow==Player.roleRow&&timeprop[i].propCol==Player.roleCol){
            gameTime+=30;
            plusTime=true;
            timeprop[i].isUsed=false;
        }
    }
}
////////////////////////////////生成地图重排道具/////////////////////////////////////////////////////////////////////////
void Singleplayer::generateShuffleProp()
{
    // 消除了34个时第一次出现重排道具
    if(haveEliminated==34&&shuffleMap[0].isInit==false){
       //随机出现在地图的某个位置
        int r; int c;
        //生成一个不重复的坐标
        while (true) {
            r=rand()%GAME_ROW+1;
            c=rand()%GAME_COL+1;
            if(hintBlock.isUsed==true){if(r==hintBlock.propRow&&c==hintBlock.propCol){continue;}}
            if(shuffleMap[1].isUsed==true){ if(r==shuffleMap[1].propRow&&c==shuffleMap[1].propCol) continue;}
            if(timeprop[0].isUsed==true){
                if(r==timeprop[0].propRow&&c==timeprop[0].propCol) continue;
            }
            if(timeprop[1].isUsed==true){
                if(r==timeprop[1].propRow&&c==timeprop[1].propCol) continue;
            }
            if(timeprop[2].isUsed==true){
                if(r==timeprop[2].propRow&&c==timeprop[2].propCol) continue;
            }
            if(timeprop[3].isUsed==true){
                if(r==timeprop[3].propRow&&c==timeprop[3].propCol) continue;
            }
            if(allMap[r-1][c-1].pixNum==0&&(Player.roleRow!=r||Player.roleCol!=c)) break;
        }
       //将得到的坐标用来初始化
       shuffleMap[0].isInit=true;
       shuffleMap[0].isUsed=true;
       shuffleMap[0].propRow=r;
       shuffleMap[0].propCol=c;
       shuffleMap[0].updatePosition();
    }
    //66次消除时出现第二个重排道具
    if(haveEliminated==66&&shuffleMap[1].isInit==false){
       //随机出现在地图的某个位置
        int r; int c;
        //生成一个不重复的坐标
        while (true) {
            r=rand()%GAME_ROW+1;
            c=rand()%GAME_COL+1;
            if(hintBlock.isUsed==true){if(r==hintBlock.propRow&&c==hintBlock.propCol){continue;}}
            if(shuffleMap[0].isUsed==true){ if(r==shuffleMap[0].propRow&&c==shuffleMap[0].propCol) continue;}
            if(timeprop[0].isUsed==true){
                if(r==timeprop[0].propRow&&c==timeprop[0].propCol) continue;
            }
            if(timeprop[1].isUsed==true){
                if(r==timeprop[1].propRow&&c==timeprop[1].propCol) continue;
            }
            if(timeprop[2].isUsed==true){
                if(r==timeprop[2].propRow&&c==timeprop[2].propCol) continue;
            }
            if(timeprop[3].isUsed==true){
                if(r==timeprop[3].propRow&&c==timeprop[3].propCol) continue;
            }
            if(allMap[r-1][c-1].pixNum==0&&(Player.roleRow!=r||Player.roleCol!=c)) break;
        }
       //将得到的坐标用来初始化
       shuffleMap[1].isInit=true;
       shuffleMap[1].isUsed=true;
       shuffleMap[1].propRow=r;
       shuffleMap[1].propCol=c;
       shuffleMap[1].updatePosition();
    }
}
///////////////////////////////////消除重排道具//////////////////////////////////////////////////////////////////////////
void Singleplayer::eliminateShuffleprop()
{

    for(int i=0;i<2;i++){
        //先讨论不用消的情况
        if(shuffleMap[i].isInit==false)continue;
        if(shuffleMap[i].isUsed==false)continue;
        //再消除
        if(shuffleMap[i].propRow==Player.roleRow&&shuffleMap[i].propCol==Player.roleCol){
            //执行消除并履行其功能
            //重排地图后地图上所有的选中情况清零
            activeNum=0;
            //画面上消除
            shuffleMap[i].isUsed=false;
            //提示框上出现
            isShuffle=true;
            //重排地图（重点）
            //先把操作下标创建出来
            int luoIndx=0;
            int lifIndx=0;
            int arfIndx=0;
            int bakIndx=0;
            int nanamiIndx=0;
            int lxyIndx=0;
            int slnIndx=0;
            int welaIndx=0;
            int lunaIndx=0;
            int quIndx=0;
           //接着就是进入地图里详细的初始化(注意被消除的方块在原数组中的pixNum也被置零了的)
            for(int i=LINK_START_ROW-1;i<LINK_END_ROW;i++){
                for(int j=LINK_START_COL-1;j<LINK_END_COL;j++){
                    //原本就被消除了就直接跳过
                    if(allMap[i][j].pixNum==0) continue;
                    //采用类似初始化的方法随机抽取数组填充
                    int idx=rand()%10+1;
                    //先把这一格置零（避免死循环）
                    allMap[i][j].pixNum=0;
                    while(true){
                        //已经处理好就退出当前循环
                        if(allMap[i][j].pixNum!=0)break;
                        if(idx==LUOSAITA_NUM){
                            //先把数组中已经被删除的部分跳过
                            while(luo[luoIndx].pixNum==0&&luoIndx<11){luoIndx++;}
                            //没填完就可以填进去
                            if(luoIndx<10){
                                luo[luoIndx].blockRow=i+1;luo[luoIndx].blockCol=j+1;
                                allMap[i][j]=luo[luoIndx++];
                                 continue;
                            }
                            else{//不然就重抽
                                idx=rand()%10+1;
                            }
                        }
                        if(idx==LIF_NUM){
                            //先把数组中已经被删除的部分跳过
                            while(lif[lifIndx].pixNum==0&&lifIndx<11){lifIndx++;}
                            //没填完就可以填进去
                            if(lifIndx<10){
                                lif[lifIndx].blockRow=i+1;lif[lifIndx].blockCol=j+1;
                                allMap[i][j]=lif[lifIndx++];
                                 continue;
                            }
                            else{//不然就重抽
                                idx=rand()%10+1;
                            }
                        }
                        if(idx==ARFA_NUM){
                            //先把数组中已经被删除的部分跳过
                            while(arf[arfIndx].pixNum==0&&arfIndx<11){arfIndx++;}
                            //没填完就可以填进去
                            if(arfIndx<10){
                                arf[arfIndx].blockRow=i+1;arf[arfIndx].blockCol=j+1;
                                allMap[i][j]=arf[arfIndx++];
                                 continue;
                            }
                            else{//不然就重抽
                                idx=rand()%10+1;
                            }
                        }

                        if(idx==BIANKA_NUM){
                            //先把数组中已经被删除的部分跳过
                            while(bak[bakIndx].pixNum==0&&bakIndx<11){bakIndx++;}
                            //没填完就可以填进去
                            if(bakIndx<10){
                                bak[bakIndx].blockRow=i+1;bak[bakIndx].blockCol=j+1;
                                allMap[i][j]=bak[bakIndx++];
                                 continue;
                            }
                            else{//不然就重抽
                                idx=rand()%10+1;
                            }
                        }
                        if(idx==NANAMI_NUM){
                            //先把数组中已经被删除的部分跳过
                            while(nanami[nanamiIndx].pixNum==0&&nanamiIndx<11){nanamiIndx++;}
                            //没填完就可以填进去
                            if(nanamiIndx<10){
                                nanami[nanamiIndx].blockRow=i+1;nanami[nanamiIndx].blockCol=j+1;
                                allMap[i][j]=nanami[nanamiIndx++];
                                 continue;
                            }
                            else{//不然就重抽
                                idx=rand()%10+1;
                            }
                        }
                        if(idx==LUSIYA_NUM){
                            //先把数组中已经被删除的部分跳过
                            while(lxy[lxyIndx].pixNum==0&&lxyIndx<11){lxyIndx++;}
                            //没填完就可以填进去
                            if(lxyIndx<10){
                                lxy[lxyIndx].blockRow=i+1;lxy[lxyIndx].blockCol=j+1;
                                allMap[i][j]=lxy[lxyIndx++];
                                 continue;
                            }
                            else{//不然就重抽
                                idx=rand()%10+1;
                            }
                        }
                        if(idx==SALINA_NUM){
                            //先把数组中已经被删除的部分跳过
                            while(sln[slnIndx].pixNum==0&&slnIndx<11){slnIndx++;}
                            //没填完就可以填进去
                            if(slnIndx<10){
                                sln[slnIndx].blockRow=i+1;sln[slnIndx].blockCol=j+1;
                                allMap[i][j]=sln[slnIndx++];
                                 continue;
                            }
                            else{//不然就重抽
                                idx=rand()%10+1;
                            }
                        }
                        if(idx==WEILA_NUM){
                            //先把数组中已经被删除的部分跳过
                            while(wela[welaIndx].pixNum==0&&welaIndx<11){welaIndx++;}
                            //没填完就可以填进去
                            if(welaIndx<10){
                                wela[welaIndx].blockRow=i+1;wela[welaIndx].blockCol=j+1;
                                allMap[i][j]=wela[welaIndx++];
                                 continue;
                            }
                            else{//不然就重抽
                                idx=rand()%10+1;
                            }
                        }
                        if(idx==LUNA_NUM){
                            //先把数组中已经被删除的部分跳过
                            while(luna[lunaIndx].pixNum==0&&lunaIndx<11){lunaIndx++;}
                            //没填完就可以填进去
                            if(lunaIndx<10){
                                luna[lunaIndx].blockRow=i+1;luna[lunaIndx].blockCol=j+1;
                                allMap[i][j]=luna[lunaIndx++];
                                continue;
                            }
                            else{//不然就重抽
                                idx=rand()%10+1;
                            }
                        }
                        if(idx==QU_NUM){
                            //先把数组中已经被删除的部分跳过
                            while(qu[quIndx].pixNum==0&&quIndx<11){quIndx++;}
                            //没填完就可以填进去
                            if(quIndx<10){
                                qu[quIndx].blockRow=i+1;qu[quIndx].blockCol=j+1;
                                allMap[i][j]=qu[quIndx++];
                                 continue;
                            }
                            else{//不然就重抽
                                idx=rand()%10+1;
                            }
                        }
                    }
                }
            }
        }
    }
}
////////////////////////////////////////生成高亮道具///////////////////////////////////////////////////////////////////
void Singleplayer::generateHint()
{
     //消除了50个时会生成一个高亮道具
    if(haveEliminated==50&&hintBlock.isInit==false){
        //随机出现在地图的某个位置
         int r; int c;
         //生成一个不重复的坐标
         while(true){
             r=rand()%GAME_ROW+1;
             c=rand()%GAME_COL+1;
             //重复性检测
             if(shuffleMap[0].isUsed==true){ if(r==shuffleMap[0].propRow&&c==shuffleMap[0].propCol) continue;}
             if(shuffleMap[0].isUsed==true){ if(r==shuffleMap[0].propRow&&c==shuffleMap[0].propCol) continue;}
             if(timeprop[0].isUsed==true){
                 if(r==timeprop[0].propRow&&c==timeprop[0].propCol) continue;
             }
             if(timeprop[1].isUsed==true){
                 if(r==timeprop[1].propRow&&c==timeprop[1].propCol) continue;
             }
             if(timeprop[2].isUsed==true){
                 if(r==timeprop[2].propRow&&c==timeprop[2].propCol) continue;
             }
             if(timeprop[3].isUsed==true){
                 if(r==timeprop[3].propRow&&c==timeprop[3].propCol) continue;
             }
             if(allMap[r-1][c-1].pixNum==0&&(Player.roleRow!=r||Player.roleCol!=c)) break;
         }
         //用得来的坐标进行初始化
         hintBlock.propRow=r;
         hintBlock.propCol=c;
         hintBlock.updatePosition();
         hintBlock.isInit=true;
         hintBlock.isUsed=true;
    }
}
///////////////////////////////////////////消除高亮道具///////////////////////////////////////////////////////////////////////////
void Singleplayer::eliminateHintprop()
{
    //先讨论不用消除的情况
    //当超时过后，就解除高亮
    if(tenSec>=10) return;
    if(hintBlock.isInit==false) return;
    //再消除
    if(hintBlock.propRow==Player.roleRow&&hintBlock.propCol==Player.roleCol){
        //图片上消除
        hintBlock.isUsed=false;
        //再开始实现功能
        isStartHint=true;
    }
}
//////////////////////////////////////实现高亮/////////////////////////////////////////////
void Singleplayer::startHint()
{
    //没开始高亮就回去
    if(isStartHint==false) return;
    //如果因为不按提示消除导致高亮只有一个了，则清空当前高亮
    if(haveHint>2){
        for(int i=LINK_START_ROW-1;i<LINK_END_ROW;i++){
            for(int j=LINK_START_COL-1;j<LINK_END_COL;j++){
                allMap[i][j].isHint=false;
            }
        }
    }
    //如果高亮个数已经有两个了，表明不用再加高亮方块，所以也直接返回
    if(haveHint==2){
        //清空当前高亮数目，返回，直到下次画图函数给出判断
        haveHint=0;
        return;
    }
    //过了十秒，结束高亮
    if(tenSec==10){
        for(int i=LINK_START_ROW-1;i<LINK_END_ROW;i++){
            for(int j=LINK_START_COL-1;j<LINK_END_COL;j++){
                allMap[i][j].isHint=false;
            }
        }
    }
    if(tenSec>=10) isStartHint=false;
    //记录十秒钟
    if(tenSec<10){
        qDebug()<<tenSec;
        //遍历找解，画成高亮
        for(int i=0;i<9;i++){
            if(luo[i].pixNum==0) continue;
            else{
                for(int j=i+1;j<10;j++){
                    if(canEliminate(luo[i],luo[j])==true) {
                        allMap[luo[i].blockRow-1][luo[i].blockCol-1].isHint=true;
                        allMap[luo[j].blockRow-1][luo[j].blockCol-1].isHint=true;
                        return;
                    }
                }
            }
        }
        for(int i=0;i<9;i++){
            if(lif[i].pixNum==0) continue;
            else{
                for(int j=i+1;j<10;j++){
                    if(canEliminate(lif[i],lif[j])==true) {
                        allMap[lif[i].blockRow-1][lif[i].blockCol-1].isHint=true;
                        allMap[lif[j].blockRow-1][lif[j].blockCol-1].isHint=true;
                        return;
                    }
                }
            }
        }
        for(int i=0;i<9;i++){
            if(arf[i].pixNum==0) continue;
            else{
                for(int j=i+1;j<10;j++){
                    if(canEliminate(arf[i],arf[j])==true) {
                        allMap[arf[i].blockRow-1][arf[i].blockCol-1].isHint=true;
                        allMap[arf[j].blockRow-1][arf[j].blockCol-1].isHint=true;
                        return;
                    }
                }
            }
        }
        for(int i=0;i<9;i++){
            if(bak[i].pixNum==0) continue;
            else{
                for(int j=i+1;j<10;j++){
                    if(canEliminate(bak[i],bak[j])==true) {
                        allMap[bak[i].blockRow-1][bak[i].blockCol-1].isHint=true;
                        allMap[bak[j].blockRow-1][bak[j].blockCol-1].isHint=true;
                        return;
                    }
                }
            }
        }
        for(int i=0;i<9;i++){
            if(nanami[i].pixNum==0) continue;
            else{
                for(int j=i+1;j<10;j++){
                    if(canEliminate(nanami[i],nanami[j])==true) {
                        allMap[nanami[i].blockRow-1][nanami[i].blockCol-1].isHint=true;
                        allMap[nanami[j].blockRow-1][nanami[j].blockCol-1].isHint=true;
                        return;
                    }
                }
            }
        }
        for(int i=0;i<9;i++){
            if(lxy[i].pixNum==0) continue;
            else{
                for(int j=i+1;j<10;j++){
                    if(canEliminate(lxy[i],lxy[j])==true) {
                        allMap[lxy[i].blockRow-1][lxy[i].blockCol-1].isHint=true;
                        allMap[lxy[j].blockRow-1][lxy[j].blockCol-1].isHint=true;
                        return;
                    }
                }
            }
        }
        for(int i=0;i<9;i++){
            if(sln[i].pixNum==0) continue;
            else{
                for(int j=i+1;j<10;j++){
                    if(canEliminate(sln[i],sln[j])==true) {
                        allMap[sln[i].blockRow-1][sln[i].blockCol-1].isHint=true;
                        allMap[sln[j].blockRow-1][sln[j].blockCol-1].isHint=true;
                        return;
                    }
                }
            }
        }
        for(int i=0;i<9;i++){
            if(wela[i].pixNum==0) continue;
            else{
                for(int j=i+1;j<10;j++){
                    if(canEliminate(wela[i],wela[j])==true) {
                        allMap[wela[i].blockRow-1][wela[i].blockCol-1].isHint=true;
                        allMap[wela[j].blockRow-1][wela[j].blockCol-1].isHint=true;
                        return;
                    }
                }
            }
        }
        for(int i=0;i<9;i++){
            if(luna[i].pixNum==0) continue;
            else{
                for(int j=i+1;j<10;j++){
                    if(canEliminate(luna[i],luna[j])==true) {
                        allMap[luna[i].blockRow-1][luna[i].blockCol-1].isHint=true;
                        allMap[luna[j].blockRow-1][luna[j].blockCol-1].isHint=true;
                        return;
                    }
                }
            }
        }
        for(int i=0;i<9;i++){
            if(qu[i].pixNum==0) continue;
            else{
                for(int j=i+1;j<10;j++){
                    if(canEliminate(qu[i],lxy[j])==true) {
                        allMap[qu[i].blockRow-1][qu[i].blockCol-1].isHint=true;
                        allMap[qu[j].blockRow-1][qu[j].blockCol-1].isHint=true;
                        return;
                    }
                }
            }
        }
    }
}
/////////////////////////////////////////读档函数/////////////////////////////////////////////////
void Singleplayer::readFile()
{
    QFile file(FILE_PATH);
    file.open(QIODevice::ReadOnly);
    QString str;
    int num;
    //先读取地图方块种类
    for(int i=LINK_START_ROW-1;i<LINK_END_ROW;i++){
        for(int j=LINK_START_COL-1;j<LINK_END_COL;j++){
            str=file.readLine();
            num=str.toInt();
            allMap[i][j].pixNum=num;
        }}
    //再读取方块活跃状态
    for(int i=LINK_START_ROW-1;i<LINK_END_ROW;i++){
        for(int j=LINK_START_COL-1;j<LINK_END_COL;j++){
            str=file.readLine();
            num=str.toInt();
            allMap[i][j].isActive=num;
        }}
    //再读取当前的高亮状态
    for(int i=LINK_START_ROW-1;i<LINK_END_ROW;i++){
        for(int j=LINK_START_COL-1;j<LINK_END_COL;j++){
            str=file.readLine();
            num=str.toInt();
            allMap[i][j].isHint=num;
        }}
    //再读取当前的活跃坐标
    str=file.readLine();
    num=str.toInt();
    tmp1Row=num;
    str=file.readLine();
    num=str.toInt();
    tmp1Col=num;
    //读取激活个数
    str=file.readLine();
    num=str.toInt();
    activeNum=num;
    //再读父下标，并对应初始化数组坐标
    for(int i=LINK_START_ROW-1;i<LINK_END_ROW;i++){
        for(int j=LINK_START_COL-1;j<LINK_END_COL;j++){
            str=file.readLine();
            num=str.toInt();
            allMap[i][j].fatherIdx=num;
            if(allMap[i][j].pixNum==1){luo[allMap[i][j].fatherIdx].blockRow=i+1;luo[allMap[i][j].fatherIdx].blockCol=j+1;}
            if(allMap[i][j].pixNum==2){lif[allMap[i][j].fatherIdx].blockRow=i+1;lif[allMap[i][j].fatherIdx].blockCol=j+1;}
            if(allMap[i][j].pixNum==3){arf[allMap[i][j].fatherIdx].blockRow=i+1;arf[allMap[i][j].fatherIdx].blockCol=j+1;}
            if(allMap[i][j].pixNum==4){bak[allMap[i][j].fatherIdx].blockRow=i+1;bak[allMap[i][j].fatherIdx].blockCol=j+1;}
            if(allMap[i][j].pixNum==5){nanami[allMap[i][j].fatherIdx].blockRow=i+1;nanami[allMap[i][j].fatherIdx].blockCol=j+1;}
            if(allMap[i][j].pixNum==6){lxy[allMap[i][j].fatherIdx].blockRow=i+1;lxy[allMap[i][j].fatherIdx].blockCol=j+1;}
            if(allMap[i][j].pixNum==7){sln[allMap[i][j].fatherIdx].blockRow=i+1;sln[allMap[i][j].fatherIdx].blockCol=j+1;}
            if(allMap[i][j].pixNum==8){wela[allMap[i][j].fatherIdx].blockRow=i+1;wela[allMap[i][j].fatherIdx].blockCol=j+1;}
            if(allMap[i][j].pixNum==9){luna[allMap[i][j].fatherIdx].blockRow=i+1;luna[allMap[i][j].fatherIdx].blockCol=j+1;}
            if(allMap[i][j].pixNum==10){qu[allMap[i][j].fatherIdx].blockRow=i+1;qu[allMap[i][j].fatherIdx].blockCol=j+1;}
        }}
    //再读取数组数据状态
    for(int i=0;i<10;i++){
        str=file.readLine();
        num=str.toInt();
        luo[i].pixNum=num;
    }
    for(int i=0;i<10;i++){
        str=file.readLine();
        num=str.toInt();
        lif[i].pixNum=num;
    }
    for(int i=0;i<10;i++){
        str=file.readLine();
        num=str.toInt();
        arf[i].pixNum=num;
    }
    for(int i=0;i<10;i++){
        str=file.readLine();
        num=str.toInt();
        bak[i].pixNum=num;
    }
    for(int i=0;i<10;i++){
        str=file.readLine();
        num=str.toInt();
        nanami[i].pixNum=num;
    }
    for(int i=0;i<10;i++){
        str=file.readLine();
        num=str.toInt();
        lxy[i].pixNum=num;
    }
    for(int i=0;i<10;i++){
        str=file.readLine();
        num=str.toInt();
        sln[i].pixNum=num;
    }
    for(int i=0;i<10;i++){
        str=file.readLine();
        num=str.toInt();
        wela[i].pixNum=num;
    }
    for(int i=0;i<10;i++){
        str=file.readLine();
        num=str.toInt();
        luna[i].pixNum=num;
    }
    for(int i=0;i<10;i++){
        str=file.readLine();
        num=str.toInt();
        qu[i].pixNum=num;
    }
    //读取人物坐标
    str=file.readLine();
    num=str.toInt();
    Player.roleRow=num;
    str=file.readLine();
    num=str.toInt();
    Player.roleCol=num;
    Player.updatePosition();
    //读取时间
    str=file.readLine();
    num=str.toInt();
    gameTime=num;
    //读取消球个数
    str=file.readLine();
    num=str.toInt();
    haveEliminated=num;
    //读取加一道具
    for(int i=0;i<4;i++){
        //是否初始化
        str=file.readLine();
        num=str.toInt();
        timeprop[i].isInit=num;
        //是否使用
        str=file.readLine();
        num=str.toInt();
        timeprop[i].isUsed=num;
        //坐标
        str=file.readLine();
        num=str.toInt();
        timeprop[i].propRow=num;
        str=file.readLine();
        num=str.toInt();
        timeprop[i].propCol=num;
        timeprop[i].updateposition();
    }
    //读取重排函数
    for(int i=0;i<2;i++){
        //是否初始化
        str=file.readLine();
        num=str.toInt();
        shuffleMap[i].isInit=num;
        //是否使用
        str=file.readLine();
        num=str.toInt();
        shuffleMap[i].isUsed=num;
        //坐标
        str=file.readLine();
        num=str.toInt();
        shuffleMap[i].propRow=num;
        str=file.readLine();
        num=str.toInt();
        shuffleMap[i].propCol=num;
        shuffleMap[i].updatePosition();
    }
    //读取高亮函数
    str=file.readLine();
    num=str.toInt();
    hintBlock.isInit=num;
    //是否使用
    str=file.readLine();
    num=str.toInt();
    hintBlock.isUsed=num;
    //坐标
    str=file.readLine();
    num=str.toInt();
    hintBlock.propRow=num;
    str=file.readLine();
    num=str.toInt();
    hintBlock.propCol=num;
    hintBlock.updatePosition();
    //读取是否开始高亮
    str=file.readLine();
    num=str.toInt();
    isStartHint=num;
    //读取“十秒”
    str=file.readLine();
    num=str.toInt();
    tenSec=num;
    //读地图
    str=file.readLine();
    num=str.toInt();
    mapNum=num;
    if(mapNum==1) singleMap.load(GAME_BACKGROUND_PATH);
    if(mapNum==2) singleMap.load(JUEHAI_PATH);
    if(mapNum==3) singleMap.load(KEMIN_PATH);
    //读bgm
    str=file.readLine();
    num=str.toInt();
    backgmNum=num;
    delete bgm;
    if(backgmNum==1) bgm=new QSound(BGM_PATH1,this);
    if(backgmNum==2) bgm=new QSound(BGM_PATH2,this);
    if(backgmNum==3) bgm=new QSound(BGM_PATH3,this);
    bgm->setLoops(-1);
    bgm->play();
}
///////////////////////////////////////////存档函数/////////////////////////////////////////////////////
void Singleplayer::writeFlie()
{
   //打开文件
    QFile  file(FILE_PATH);
    file.open(QIODevice::WriteOnly|QIODevice::Text);
    //先写进去当前地图的每个格子的种类
    for(int i=LINK_START_ROW-1;i<LINK_END_ROW;i++){
        for(int j=LINK_START_COL-1;j<LINK_END_COL;j++){
            if(allMap[i][j].pixNum==0) {file.write("0\n");continue;}
            if(allMap[i][j].pixNum==1) {file.write("1\n");continue;}
            if(allMap[i][j].pixNum==2) {file.write("2\n");continue;}
            if(allMap[i][j].pixNum==3) {file.write("3\n");continue;}
            if(allMap[i][j].pixNum==4) {file.write("4\n");continue;}
            if(allMap[i][j].pixNum==5) {file.write("5\n");continue;}
            if(allMap[i][j].pixNum==6) {file.write("6\n");continue;}
            if(allMap[i][j].pixNum==7) {file.write("7\n");continue;}
            if(allMap[i][j].pixNum==8) {file.write("8\n");continue;}
            if(allMap[i][j].pixNum==9) {file.write("9\n");continue;}
            if(allMap[i][j].pixNum==10) {file.write("10\n");continue;}
        }
    }
    //再写当前的活跃状态
    for(int i=LINK_START_ROW-1;i<LINK_END_ROW;i++){
        for(int j=LINK_START_COL-1;j<LINK_END_COL;j++){
            if(allMap[i][j].isActive==true) file.write("1\n");
            else  file.write("0\n");
        }
    }
    //再写当前的高亮状态
    for(int i=LINK_START_ROW-1;i<LINK_END_ROW;i++){
        for(int j=LINK_START_COL-1;j<LINK_END_COL;j++){
            if(allMap[i][j].isHint==true) file.write("1\n");
            else  file.write("0\n");
        }
    }
    //再写目前的上一个活跃方块坐标
    QTextStream out(&file);
    QString str=QString("%1\n").arg(QString::number(tmp1Row));
    out<<str;
    str=QString("%1\n").arg(QString::number(tmp1Col));
    out<<str;
    //写激活个数
    str=QString("%1\n").arg(QString::number(activeNum));
    out<<str;
    //写各自的父坐标
    for(int i=LINK_START_ROW-1;i<LINK_END_ROW;i++){
        for(int j=LINK_START_COL-1;j<LINK_END_COL;j++){
            if(allMap[i][j].fatherIdx==1) {out<<("1\n");continue;}
            if(allMap[i][j].fatherIdx==2) {out<<("2\n");continue;}
            if(allMap[i][j].fatherIdx==3) {out<<("3\n");continue;}
            if(allMap[i][j].fatherIdx==4) {out<<("4\n");continue;}
            if(allMap[i][j].fatherIdx==5) {out<<("5\n");continue;}
            if(allMap[i][j].fatherIdx==6) {out<<("6\n");continue;}
            if(allMap[i][j].fatherIdx==7) {out<<("7\n");continue;}
            if(allMap[i][j].fatherIdx==8) {out<<("8\n");continue;}
            if(allMap[i][j].fatherIdx==9) {out<<("9\n");continue;}
            if(allMap[i][j].fatherIdx==0) {out<<("0\n");continue;}
        }
    }
    //写各个数组中的数据的状态
    for(int i=0;i<10;i++){
        str=QString("%1\n").arg(QString::number(luo[i].pixNum));
        out<<str;
    }
    for(int i=0;i<10;i++){
        str=QString("%1\n").arg(QString::number(lif[i].pixNum));
        out<<str;
    }
    for(int i=0;i<10;i++){
        str=QString("%1\n").arg(QString::number(arf[i].pixNum));
        out<<str;
    }
    for(int i=0;i<10;i++){
        str=QString("%1\n").arg(QString::number(bak[i].pixNum));
        out<<str;
    }
    for(int i=0;i<10;i++){
        str=QString("%1\n").arg(QString::number(nanami[i].pixNum));
        out<<str;
    }
    for(int i=0;i<10;i++){
        str=QString("%1\n").arg(QString::number(lxy[i].pixNum));
        out<<str;
    }
    for(int i=0;i<10;i++){
        str=QString("%1\n").arg(QString::number(sln[i].pixNum));
        out<<str;
    }
    for(int i=0;i<10;i++){
        str=QString("%1\n").arg(QString::number(wela[i].pixNum));
        out<<str;
    }
    for(int i=0;i<10;i++){
        str=QString("%1\n").arg(QString::number(luna[i].pixNum));
        out<<str;
    }
    for(int i=0;i<10;i++){
        str=QString("%1\n").arg(QString::number(qu[i].pixNum));
        out<<str;
    }
    //再写人物坐标
    str=QString("%1\n").arg(QString::number(Player.roleRow));
    out<<str;
    str=QString("%1\n").arg(QString::number(Player.roleCol));
    out<<str;
    //记录时间
    str=QString("%1\n").arg(QString::number(gameTime));
    out<<str;
    //记录消球个数
    str=QString("%1\n").arg(QString::number(haveEliminated));
    out<<str;
    //记录+1道具的参数
    for(int i=0;i<4;i++){
        //是否初始化
        str=QString("%1\n").arg(QString::number(timeprop[i].isInit));
        out<<str;
        //是否使用
        str=QString("%1\n").arg(QString::number(timeprop[i].isUsed));
        out<<str;
        //坐标
        str=QString("%1\n").arg(QString::number(timeprop[i].propRow));
        out<<str;
        str=QString("%1\n").arg(QString::number(timeprop[i].propCol));
        out<<str;
    }
    //记录重排函数
    for(int i=0;i<2;i++){
        //记录是否初始化
        str=QString("%1\n").arg(QString::number(shuffleMap[i].isInit));
        out<<str;
        //记录是否使用
        str=QString("%1\n").arg(QString::number(shuffleMap[i].isUsed));
        out<<str;
        //记录坐标
        str=QString("%1\n").arg(QString::number(shuffleMap[i].propRow));
        out<<str;
        str=QString("%1\n").arg(QString::number(shuffleMap[i].propCol));
        out<<str;
    }
    //记录高亮函数
    //记录是否初始化
    str=QString("%1\n").arg(QString::number(hintBlock.isInit));
    out<<str;
    //记录是否使用
    str=QString("%1\n").arg(QString::number(hintBlock.isUsed));
    out<<str;
    //记录坐标
    str=QString("%1\n").arg(QString::number(hintBlock.propRow));
    out<<str;
    str=QString("%1\n").arg(QString::number(hintBlock.propCol));
    out<<str;
    //写是否开启高亮
    str=QString("%1\n").arg(QString::number(isStartHint));
    out<<str;
    //写“十秒”
    str=QString("%1\n").arg(QString::number(tenSec));
    out<<str;
    //写地图
    str=QString("%1\n").arg(QString::number(mapNum));
    out<<str;
    //写bgm
    str=QString("%1\n").arg(QString::number(backgmNum));
    out<<str;
}
















