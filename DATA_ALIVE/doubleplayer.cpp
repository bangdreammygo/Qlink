#include "doubleplayer.h"
#include "ui_doubleplayer.h"
////////////////////////////////////////构造函数//////////////////////////////////////////
Doubleplayer::Doubleplayer(int sceneNum,int bgmNum,QWidget *parent) : QMainWindow(parent),ui(new Ui::Doubleplayer)
{
    ui->setupUi(this);
    mapNum=sceneNum;
    this->bgmNum=bgmNum;
    //初始化关卡
    initScene(sceneNum,bgmNum);
    //启动游戏
    play();
}
///////////////////////////////////////////析构函数///////////////////////////////////////
Doubleplayer::~Doubleplayer()
{
    delete ui;
}
////////////////////////////////////////////绘图事件/////////////////////////////////////////////
void Doubleplayer::paintEvent(QPaintEvent *event)
{
    //画地图
    QPainter painter(this);
    //画背景图
    painter.drawPixmap(0,MENUBAR_INTERVAL,doubleMap);
    //画边框
    painter.drawPixmap(GAME_WIDTH,MENUBAR_INTERVAL,markBox);
    //加载方块图
    //先把各自的pixmap加载好,避免画图的时候调用耽误时间
    //加载方块,其中1为常态，2为玩家一激发态
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
    //3为玩家二的激活状态
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
            if(allMap[i][j].isActive==true){//说明是玩家一激活态，则绘制激活态图片
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
            //画玩家2的激活态
            if(allMap[i][j].isHint==true){
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
        }
    }
    //画角色
    //画第一个角色
    painter.drawPixmap(playerOne.x,playerOne.y+MENUBAR_INTERVAL,playerOne.rolePix);
    //画第二个角色
    painter.drawPixmap(playerTwo.x,playerTwo.y+MENUBAR_INTERVAL,playerTwo.rolePix);
}
////////////////////////////////////////////初始化关卡//////////////////////////////////////////////
void Doubleplayer::initScene(int sceneNum, int bgmNum)
{
    //先初始化随机数种子
    srand((unsigned int)time(NULL));
    //设置窗口尺寸
    setFixedSize(GAME_WIDTH+BOX_WIDTH,GAME_HEIGHT+MENUBAR_INTERVAL);
    //设置标题
    setWindowTitle("双人♂模式");
    //加载消除音效
    dis=new QSound(DIS_MUSIC_PATH,this);
    //设置图标
    setWindowIcon(QIcon(TITLE_PATH));
    //设置边框
    markBox.load(MARKBPX_PATH);
    //加载背景音乐
    if(bgmNum==1) bgm=new QSound(BGM_PATH1,this);
    if(bgmNum==2) bgm=new QSound(BGM_PATH2,this);
    if(bgmNum==3) bgm=new QSound(BGM_PATH3,this);
    bgm->setLoops(-1);
    bgm->play();
    //设置背景图
    if(sceneNum==1)doubleMap.load(GAME_BACKGROUND_PATH);
    if(sceneNum==2)doubleMap.load(JUEHAI_PATH);
    if(sceneNum==3)doubleMap.load(KEMIN_PATH);
    //实现退出功能
    connect(ui->quit,&QAction::triggered,[=](){
        if(QMessageBox::Yes==QMessageBox::question(this,"退出","是否选择退出游戏"))
        {this->close();}
    });
    //实现返回功能
    connect(ui->return_2,&QAction::triggered,[=](){
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
    //随机排布方块
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
     //初始化玩家位置
     randPlayerposition();
     //初始化周围方块
     initSurround();
     //初始化边框
     initBox();
}
////////////////////////////////启动函数/////////////////////////////////////////////
void Doubleplayer::play()
{
    //启动定时器
    timer.start(TIMER_INTERVAL);
    //刷新画面
    connect((&timer),&QTimer::timeout,[=](){
        //刷新画面
        update();
        //更新全局信息
        updatePosition();
        //更新边框信息
        updateBox();
    });

    //第二个定时器
    timer2.start(1000);
    //刷新时间
    connect((&timer2),&QTimer::timeout,[=](){
        gameTime--;
        //时间结束时游戏也结束
        if(gameTime==0) emit gameOver();
        //更新时间栏
        QString str=QString("剩余时间:%1秒").arg(gameTime);
        ui->timeLab->setText(str);
        QFont font2("华文行楷",20);
        ui->timeLab->setFont(font2);
        ui->timeLab->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->timeLab->setAttribute(Qt::WA_TransparentForMouseEvents);
        ui->timeLab->setStyleSheet("color:darkred");
    });
    //实现几个退出
    //正常退出
    connect(this,&Doubleplayer::gameOver,[=](){
        //停止计时器
        timer.stop();
        timer2.stop();
        //构造
        endScene=new Doubleend(haveEliminateOne,haveEliminateTwo);
        endScene->setGeometry(this->geometry());
        endScene->show();
        this->hide();
        //接收来自最终场景的信号
        connect(endScene,&Doubleend::back,[=](){
            delete endScene;
            emit back();
        });
    });
    //无解退出
    connect(this,&Doubleplayer::noAnswer,[=](){
        //停止计时
        timer.stop();
        timer2.stop();
        //构造
        endScene=new Doubleend(haveEliminateOne,haveEliminateTwo,true);
        endScene->setGeometry(this->geometry());
        endScene->show();
        this->hide();
        //接收来自最终场景的信号
        connect(endScene,&Doubleend::back,[=](){
            delete endScene;
            emit back();
        });
    });
    //暂停函数
    //暂停和继续
    connect(ui->actionaccontinue,&QAction::triggered,[=](){
        timer.start(TIMER_INTERVAL);
        timer2.start(1000);
    });
    connect(ui->actionstoponce,&QAction::triggered,[=](){
        timer.stop();
        timer2.stop();
    });
    //读档与存档
    connect(ui->actionwrite,&QAction::triggered,[=](){
        writeFile();
    });
    connect(ui->actionread,&QAction::triggered,[=](){
        readFile();
    });
}
///////////////////////////////////随机初始化方块位置/////////////////////////////////////////////////
void Doubleplayer::randInition()
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
////////////////////////////////////////////初始化玩家位置/////////////////////////////////////////////////////
void Doubleplayer::randPlayerposition()
{
    //先初始第一个玩家的位置
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
    playerOne.roleRow=row;
    playerTwo.roleCol=col;
    playerOne.updatePosition();
    //再初始化玩家二的位置
    while(true)
    {
        row=rand()%GAME_ROW+1;
        col=rand()%GAME_COL+1;
        //找一处空地作为人物的初始位置
        if(row==playerOne.roleRow&&col==playerOne.roleCol) continue;
        if(allMap[row-1][col-1].pixNum==0){
            break;
        }
    }
    playerTwo.roleRow=row;
    playerTwo.roleCol=col;
    playerTwo.updatePosition();
}
////////////////////////////////////////////初始化周围方块/////////////////////////////////////////////////////
void Doubleplayer::initSurround()
{
    for(int i=0;i<GAME_ROW;i++){
        for(int j=0;j<GAME_COL;j++){
            allMap[i][j].blockRow=i+1;
            allMap[i][j].blockCol=j+1;
        }
    }
}
///////////////////////////////////////////////重写键盘控制函数////////////////////////////////////////////////
void Doubleplayer::keyPressEvent(QKeyEvent *event)
{
    //第一个键盘的控制
    if(event->key()==Qt::Key_A) {typeOne=LEFT;}
    else if(event->key()==Qt::Key_D){typeOne=RIGHT;}
    else if(event->key()==Qt::Key_W){typeOne=KEY_UP;}
    else if(event->key()==Qt::Key_S){typeOne=DOWN;}
    //第二个键盘的控制
    if(event->key()==Qt::Key_Left) {typeTwo=LEFT;}
    else if(event->key()==Qt::Key_Right){typeTwo=RIGHT;}
    else if(event->key()==Qt::Key_Up){typeTwo=KEY_UP;}
    else if(event->key()==Qt::Key_Down){typeTwo=DOWN;}
}
///////////////////////////////////////更新全局信息////////////////////////////////////////////////////
void Doubleplayer::updatePosition()
{
    //更新人物信息
    updatePlayerPosition();
    //用完调零
    typeOne=0;
    typeTwo=0;
    //玩家一的消除
    if(activeNumOne==2){
        activeNumOne=0;
        if(canEliminate(allMap[tmp1RowOne-1][tmp1ColOne-1],allMap[tmp2RowOne-1][tmp2ColOne-1])==false){
            //消不掉，那就简单的还原即可
            allMap[tmp1RowOne-1][tmp1ColOne-1].isActive=false;
            allMap[tmp2RowOne-1][tmp2ColOne-1].isActive=false;
        }
        else{//可以消除
            dis->play();
           doEliminateOne();
           //玩家一上分
           haveEliminateOne+=2;
           if(canStillEliminate()==false&&(haveEliminateOne+haveEliminateTwo!=100)){
               //无法消除，进入结算页面
            emit noAnswer();
           }
        }
    }
    //玩家2的消除
    if(activeNumTwo==2){
        activeNumTwo=0;
        if(canEliminate(allMap[tmp1RowTwo-1][tmp1ColTwo-1],allMap[tmp2RowTwo-1][tmp2ColTwo-1])==false){
            //消不掉，那就简单的还原即可
            allMap[tmp1RowTwo-1][tmp1ColTwo-1].isHint=false;
            allMap[tmp2RowTwo-1][tmp2ColTwo-1].isHint=false;
        }
        else{//可以消除
            dis->play();
           doEliminateTwo();
           //玩家二上分
           haveEliminateTwo+=2;
           //判断无解的条件有两个，一是无法再消除，二是有遗留没消完的
           if(canStillEliminate()==false&&(haveEliminateOne+haveEliminateTwo!=100)){
               //无解要给出无解标志
               haveAnswer=false;
               //无解进入结算页面
               emit noAnswer();
           }
        }
    }
    //已经消除完了，也要进入结算页面
    if(haveEliminateOne+haveEliminateTwo==100){
        timer.stop();
        timer2.stop();
        emit gameOver();
    }
}
////////////////////////////////////////更新人物信息////////////////////////////////////////////////////////
void Doubleplayer::updatePlayerPosition()
{
    //第一个角色的移动
    //没动键盘不作为
    if(typeOne==0){typeOne=0;}
    //左移
    if(typeOne==LEFT){
        //左边可以走才行
        if(playerOne.roleCol>1){
            //如果左边没有方块，正常移动
            if(allMap[playerOne.roleRow-1][playerOne.roleCol-2].pixNum==0){playerOne.movePosition(LEFT);}
            //有方块则激活该方块,并进行判断
            else{
                if(allMap[playerOne.roleRow-1][playerOne.roleCol-2].isActive==false){
                 allMap[playerOne.roleRow-1][playerOne.roleCol-2].isActive=true;activeNumOne++;
                   //第一个被激活的方块，放入tmp1里
                   if(activeNumOne==1){tmp1RowOne=playerOne.roleRow; tmp1ColOne=playerOne.roleCol-1;}
                   //否则就放tmp2
                   else{tmp2RowOne=playerOne.roleRow;tmp2ColOne=playerOne.roleCol-1;}
                }
            }
        }
    }
    //右移
   else if(typeOne==RIGHT){
        if(playerOne.roleCol<GAME_COL){
            //如果右边没有方块，正常移动
            if(allMap[playerOne.roleRow-1][playerOne.roleCol].pixNum==0){playerOne.movePosition(RIGHT);}
            //有方块则激活该方块,并进行判断
            else{
                if(allMap[playerOne.roleRow-1][playerOne.roleCol].isActive==false){
                allMap[playerOne.roleRow-1][playerOne.roleCol].isActive=true;activeNumOne++;
                   //第一个被激活的方块，放入tmp1里,否则放tmp2里
                   if(activeNumOne==1){tmp1RowOne=playerOne.roleRow;tmp1ColOne=playerOne.roleCol+1;}
                   else{tmp2RowOne=playerOne.roleRow;tmp2ColOne=playerOne.roleCol+1;}
                }
            }
        }
    }
    //上移
    else if(typeOne==KEY_UP){
         if(playerOne.roleRow>1){
             //如果上边没有方块，正常移动
             if(allMap[playerOne.roleRow-2][playerOne.roleCol-1].pixNum==0){playerOne.movePosition(KEY_UP);}
             //有方块则激活该方块,并进行判断
             else{
                 if(allMap[playerOne.roleRow-2][playerOne.roleCol-1].isActive==false){
                     allMap[playerOne.roleRow-2][playerOne.roleCol-1].isActive=true;activeNumOne++;
                        //第一个被激活的方块，放入tmp1里,否则放tmp2里
                        if(activeNumOne==1){tmp1RowOne=playerOne.roleRow-1;tmp1ColOne=playerOne.roleCol;}
                        else{tmp2RowOne=playerOne.roleRow-1;tmp2ColOne=playerOne.roleCol;}
                 }
             }
         }
     }
    //下移
    else if(typeOne==DOWN){
         if(playerOne.roleRow<GAME_ROW){
             //如果上边没有方块，正常移动
             if(allMap[playerOne.roleRow][playerOne.roleCol-1].pixNum==0){playerOne.movePosition(DOWN);}
             //有方块则激活该方块,并进行判断
             else{
                 if(allMap[playerOne.roleRow][playerOne.roleCol-1].isActive==false){
                     allMap[playerOne.roleRow][playerOne.roleCol-1].isActive=true;activeNumOne++;
                        //第一个被激活的方块，放入tmp1里,否则放tmp2里
                        if(activeNumOne==1){tmp1RowOne=playerOne.roleRow+1;tmp1ColOne=playerOne.roleCol;}
                        else{tmp2RowOne=playerOne.roleRow+1;tmp2ColOne=playerOne.roleCol;}
                 }
             }
         }
     }
    //第二个人物的坐标
    //没动键盘不作为
    if(typeTwo==0){typeTwo=0;}
    //左移
    if(typeTwo==LEFT){
        //左边可以走才行
        if(playerTwo.roleCol>1){
            //如果左边没有方块，正常移动
            if(allMap[playerTwo.roleRow-1][playerTwo.roleCol-2].pixNum==0){playerTwo.movePosition(LEFT);}
            //有方块则激活该方块,并进行判断
            else{
                if(allMap[playerTwo.roleRow-1][playerTwo.roleCol-2].isHint==false){
                 allMap[playerTwo.roleRow-1][playerTwo.roleCol-2].isHint=true;activeNumTwo++;
                   //第一个被激活的方块，放入tmp1里
                   if(activeNumTwo==1){tmp1RowTwo=playerTwo.roleRow; tmp1ColTwo=playerTwo.roleCol-1;}
                   //否则就放tmp2
                   else{tmp2RowTwo=playerTwo.roleRow;tmp2ColTwo=playerTwo.roleCol-1;}
                }
            }
        }
    }
    //右移
   else if(typeTwo==RIGHT){
        if(playerTwo.roleCol<GAME_COL){
            //如果右边没有方块，正常移动
            if(allMap[playerTwo.roleRow-1][playerTwo.roleCol].pixNum==0){playerTwo.movePosition(RIGHT);}
            //有方块则激活该方块,并进行判断
            else{
                if(allMap[playerTwo.roleRow-1][playerTwo.roleCol].isHint==false){
                allMap[playerTwo.roleRow-1][playerTwo.roleCol].isHint=true;activeNumTwo++;
                   //第一个被激活的方块，放入tmp1里,否则放tmp2里
                   if(activeNumTwo==1){tmp1RowTwo=playerTwo.roleRow;tmp1ColTwo=playerTwo.roleCol+1;}
                   else{tmp2RowTwo=playerTwo.roleRow;tmp2ColTwo=playerTwo.roleCol+1;}
                }
            }
        }
    }
    //上移
    else if(typeTwo==KEY_UP){
         if(playerTwo.roleRow>1){
             //如果上边没有方块，正常移动
             if(allMap[playerTwo.roleRow-2][playerTwo.roleCol-1].pixNum==0){playerTwo.movePosition(KEY_UP);}
             //有方块则激活该方块,并进行判断
             else{
                 if(allMap[playerTwo.roleRow-2][playerTwo.roleCol-1].isHint==false){
                     allMap[playerTwo.roleRow-2][playerTwo.roleCol-1].isHint=true;activeNumTwo++;
                        //第一个被激活的方块，放入tmp1里,否则放tmp2里
                        if(activeNumTwo==1){tmp1RowTwo=playerTwo.roleRow-1;tmp1ColTwo=playerTwo.roleCol;}
                        else{tmp2RowTwo=playerTwo.roleRow-1;tmp2ColTwo=playerTwo.roleCol;}
                 }
             }
         }
     }
    //下移
    else if(typeTwo==DOWN){
         if(playerTwo.roleRow<GAME_ROW){
             //如果上边没有方块，正常移动
             if(allMap[playerTwo.roleRow][playerTwo.roleCol-1].pixNum==0){playerTwo.movePosition(DOWN);}
             //有方块则激活该方块,并进行判断
             else{
                 if(allMap[playerTwo.roleRow][playerTwo.roleCol-1].isHint==false){
                     allMap[playerTwo.roleRow][playerTwo.roleCol-1].isHint=true;activeNumTwo++;
                        //第一个被激活的方块，放入tmp1里,否则放tmp2里
                        if(activeNumTwo==1){tmp1RowTwo=playerTwo.roleRow+1;tmp1ColTwo=playerTwo.roleCol;}
                        else{tmp2RowTwo=playerTwo.roleRow+1;tmp2ColTwo=playerTwo.roleCol;}
                 }
             }
         }
    }
}
///////////////////////////////////////////判断是否能消除///////////////////////////////////////////////////////////
bool Doubleplayer::canEliminate(Block b1, Block b2)
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
//////////////////////////////////////////零折判断//////////////////////////////////////////////////
bool Doubleplayer::noCornor(Block b1, Block b2)
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
///////////////////////////////////////////一折判断//////////////////////////////////////////////////////////
bool Doubleplayer::oneCornor(Block b1, Block b2)
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
/////////////////////////////////////////////二折消除///////////////////////////////////////////////////////////
bool Doubleplayer::twoCornor(Block b1, Block b2)
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
//////////////////////////////////////////////判断剩余是否有解的函数//////////////////////////////////////////////////////
bool Doubleplayer::canStillEliminate()
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
////////////////////////////////////////执行实际消除指令//////////////////////////////////////////////
void Doubleplayer::doEliminateOne()
{
    int kind=allMap[tmp1RowOne-1][tmp1ColOne-1].pixNum;
    int f1Idx=allMap[tmp1RowOne-1][tmp1ColOne-1].fatherIdx;
    int f2Idx=allMap[tmp2RowOne-1][tmp2ColOne-1].fatherIdx;
    //先在地图中消除
    allMap[tmp1RowOne-1][tmp1ColOne-1].pixNum=0;
    allMap[tmp2RowOne-1][tmp2ColOne-1].pixNum=0;
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
/////////////////////////////////////////////第二玩家消除/////////////////////////////////////////////////
void Doubleplayer::doEliminateTwo()
{
    int kind=allMap[tmp1RowTwo-1][tmp1ColTwo-1].pixNum;
    int f1Idx=allMap[tmp1RowTwo-1][tmp1ColTwo-1].fatherIdx;
    int f2Idx=allMap[tmp2RowTwo-1][tmp2ColTwo-1].fatherIdx;
    //先在地图中消除
    allMap[tmp1RowTwo-1][tmp1ColTwo-1].pixNum=0;
    allMap[tmp2RowTwo-1][tmp2ColTwo-1].pixNum=0;
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
///////////////////////////////////////////////初始化边框/////////////////////////////////////////////////////////////
void Doubleplayer::initBox()
{
    //第一个时间框
    ui->timeBox->setFixedSize(BOX_WIDTH,TIME_BOX_HEIGHT);
    ui->timeBox->move(GAME_WIDTH,0);
    ui->timeBox->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->timeBox->setAttribute(Qt::WA_TransparentForMouseEvents);
    QFont font1("华文新魏",15);
    ui->timeBox->setFont(font1);
    //第二个显示时间框
    ui->timeLab->setFixedSize(BOX_WIDTH,160);
    ui->timeLab->move(GAME_WIDTH,0+TIME_BOX_HEIGHT);
    //设置文字更新到play()函数里更新,这里仅作初始化
    QString str=QString("剩余时间:%1秒").arg(gameTime);
    ui->timeLab->setText(str);
    QFont font2("华文行楷",20);
    ui->timeLab->setFont(font2);
    ui->timeLab->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->timeLab->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->timeLab->setStyleSheet("color:darkred");
    //第三个框，玩家一的消除数
    QFont font3("华文琥珀",17);
    ui->PlayerOneBox->setFixedSize(BOX_WIDTH,120);
    ui->PlayerOneBox->move(GAME_WIDTH,280);
    ui->PlayerOneBox->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->PlayerOneBox->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->PlayerOneBox->setFont(font3);
    ui->PlayerOneBox->setStyleSheet("color:darkgreen");
    //第四个框，显示数量
    QFont font4("华文隶书",22);
    ui->playerOneNum->setFixedSize(BOX_WIDTH,160);
    ui->playerOneNum->move(GAME_WIDTH,120+160+120);
    QString str2=QString("已消除%1个").arg(haveEliminateOne);
    ui->playerOneNum->setText(str2);
    ui->playerOneNum->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->playerOneNum->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->playerOneNum->setFont(font4);
    ui->playerOneNum->setStyleSheet("color:darkgreen");
    //第五个框，玩家二消除数
    ui->playerTwoBox->setFixedSize(BOX_WIDTH,120);
    ui->playerTwoBox->move(GAME_WIDTH,120+120+160+160);
    ui->playerTwoBox->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->playerTwoBox->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->playerTwoBox->setFont(font3);
    ui->playerTwoBox->setStyleSheet("color:darkblue");
    //最后一个框,显示玩家二的分数
    ui->playerTwoNum->setFixedSize(BOX_WIDTH,160);
    ui->playerTwoNum->move(GAME_WIDTH,240+320+120);
    QString str3=QString("已消除%1个").arg(haveEliminateTwo);
    ui->playerTwoNum->setText(str3);
    ui->playerTwoNum->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->playerTwoNum->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->playerTwoNum->setFont(font4);
    ui->playerTwoNum->setStyleSheet("color:darkblue");
}
/////////////////////////////////////////更新边框/////////////////////////////////////////////
void Doubleplayer::updateBox()
{
    QFont font4("华文隶书",22);
    ui->playerOneNum->setFixedSize(BOX_WIDTH,160);
    ui->playerOneNum->move(GAME_WIDTH,120+160+120);
    QString str2=QString("已消除%1个").arg(haveEliminateOne);
    ui->playerOneNum->setText(str2);
    ui->playerOneNum->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->playerOneNum->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->playerOneNum->setFont(font4);
    ui->playerOneNum->setStyleSheet("color:darkgreen");
    ui->playerTwoNum->setFixedSize(BOX_WIDTH,160);
    ui->playerTwoNum->move(GAME_WIDTH,240+320+120);
    QString str3=QString("已消除%1个").arg(haveEliminateTwo);
    ui->playerTwoNum->setText(str3);
    ui->playerTwoNum->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->playerTwoNum->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->playerTwoNum->setFont(font4);
    ui->playerTwoNum->setStyleSheet("color:darkblue");
}
////////////////////////////////////存档函数/////////////////////////////////////////////////
void Doubleplayer::writeFile()
{
    //打开文件
     QFile  file(FILE_PATH2);
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
     //再写当前的活跃状态(P1)
     for(int i=LINK_START_ROW-1;i<LINK_END_ROW;i++){
         for(int j=LINK_START_COL-1;j<LINK_END_COL;j++){
             if(allMap[i][j].isActive==true) file.write("1\n");
             else  file.write("0\n");
         }
     }
     //再写当前的高亮状态(P2)
     for(int i=LINK_START_ROW-1;i<LINK_END_ROW;i++){
         for(int j=LINK_START_COL-1;j<LINK_END_COL;j++){
             if(allMap[i][j].isHint==true) file.write("1\n");
             else  file.write("0\n");
         }
     }
     //再写目前P1的上一个活跃方块坐标
     QTextStream out(&file);
     QString str=QString("%1\n").arg(QString::number(tmp1RowOne));
     out<<str;
     str=QString("%1\n").arg(QString::number(tmp1ColOne));
     out<<str;
     //再写目前P2的上一个活跃方块坐标
     str=QString("%1\n").arg(QString::number(tmp1RowTwo));
     out<<str;
     str=QString("%1\n").arg(QString::number(tmp1ColTwo));
     out<<str;
     //写P1激活个数
     str=QString("%1\n").arg(QString::number(activeNumOne));
     out<<str;
     //写P2的激活个数
     str=QString("%1\n").arg(QString::number(activeNumTwo));
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
     //再写P1人物坐标
     str=QString("%1\n").arg(QString::number(playerOne.roleRow));
     out<<str;
     str=QString("%1\n").arg(QString::number(playerOne.roleCol));
     out<<str;
     //再写P2人物坐标
     str=QString("%1\n").arg(QString::number(playerTwo.roleRow));
     out<<str;
     str=QString("%1\n").arg(QString::number(playerTwo.roleCol));
     out<<str;
     //记录时间
     str=QString("%1\n").arg(QString::number(gameTime));
     out<<str;
     //记录P1消球个数
     str=QString("%1\n").arg(QString::number(haveEliminateOne));
     out<<str;
     //记录P2消球个数
     str=QString("%1\n").arg(QString::number(haveEliminateTwo));
     out<<str;
     //写地图
     str=QString("%1\n").arg(QString::number(mapNum));
     out<<str;
     //写bgm
     str=QString("%1\n").arg(QString::number(bgmNum));
     out<<str;
}
/////////////////////////////////////存档函数/////////////////////////////////////////////////
void Doubleplayer::readFile()
{
    QFile file(FILE_PATH2);
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
    //再读取当前P1的活跃坐标
    str=file.readLine();
    num=str.toInt();
    tmp1RowOne=num;
    str=file.readLine();
    num=str.toInt();
    tmp1ColOne=num;
    //再读取当前P2的活跃坐标
    str=file.readLine();
    num=str.toInt();
    tmp1RowTwo=num;
    str=file.readLine();
    num=str.toInt();
    tmp1ColTwo=num;
    //读取P1激活个数
    str=file.readLine();
    num=str.toInt();
    activeNumOne=num;
    //读取P2激活个数
    str=file.readLine();
    num=str.toInt();
    activeNumTwo=num;
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
    //读取P1人物坐标
    str=file.readLine();
    num=str.toInt();
    playerOne.roleRow=num;
    str=file.readLine();
    num=str.toInt();
    playerOne.roleCol=num;
    playerOne.updatePosition();
    //读取P2人物坐标
    str=file.readLine();
    num=str.toInt();
    playerTwo.roleRow=num;
    str=file.readLine();
    num=str.toInt();
    playerTwo.roleCol=num;
    playerTwo.updatePosition();
    //读取时间
    str=file.readLine();
    num=str.toInt();
    gameTime=num;
    //读取P1消球个数
    str=file.readLine();
    num=str.toInt();
    haveEliminateOne=num;
    //读取P2消球个数
    str=file.readLine();
    num=str.toInt();
    haveEliminateTwo=num;
    //读地图
    str=file.readLine();
    num=str.toInt();
    mapNum=num;
    if(mapNum==1) doubleMap.load(GAME_BACKGROUND_PATH);
    if(mapNum==2) doubleMap.load(JUEHAI_PATH);
    if(mapNum==3) doubleMap.load(KEMIN_PATH);
    //读bgm
    str=file.readLine();
    num=str.toInt();
    bgmNum=num;
    delete bgm;
    if(bgmNum==1) bgm=new QSound(BGM_PATH1,this);
    if(bgmNum==2) bgm=new QSound(BGM_PATH2,this);
    if(bgmNum==3) bgm=new QSound(BGM_PATH3,this);
    bgm->setLoops(-1);
    bgm->play();
}













