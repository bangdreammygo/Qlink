////////////////////////////////资源数据配置文件/////////////////////////////////
#pragma once
///////////////////场景数据////////////////////
#define  GAME_WIDTH  1080 //主场景宽度
#define  GAME_HEIGHT 840  //主场景高度
#define  GAME_BACKGROUND_PATH  ":/zs/stack/mainscene.jpg" //主场景的背景图片资源路径
#define  TITLE_PATH ":/zs/stack/craybird.jpg" //标题图标
#define  GAME_ROW  14
#define  GAME_COL  18
#define  TIMER_INTERVAL 50//50ms刷新一次屏幕
#define  MENUBAR_INTERVAL 27//菜单栏的高度挡了一部分(注意，该部分不影响二维数组中的部分)
#define  DIS_MUSIC_PATH ":/delete/stack/disappear.wav"
#define  SELECT_BACKGROUND_PATH":/active/stack/select.jpg"
////////////////////////人物数据/////////////////////////
#define  ROLE_SPEED 60//人物的移动速度
#define  ROLE_NUM    37//玩家操控角色的特征数字为37
#define  WIHTE_SB_PATH ":/zs/stack/White_SB.jpg"//白鲨碧的资源路径
#define  BLACK_SB_PATH ":/zs/stack/Black_SB.png"//黑化鲨碧的资源路径
#define  DAVENKI_PATH  ":/zs/stack/Davenqi.png"//达芬奇的资源路径
#define  KULIKE_PATH   ":/zs/stack/Kulike.png"//库利科的资源路径
#define  LI_PATH       ":/zs/stack/li.png"//里的资源路径
#define  SOLON_PATH    ":/zs/stack/solen.png"//松伦哥的路径
#define  SOLON_NV_PATH ":/zs/stack/solon.png"//女装solon哥的路径
////////人物的移动方向封装//////////////////////////
#define  LEFT  1
#define  RIGHT 2
#define  KEY_UP    3
#define  DOWN  4
//////////////////////消除方块数据////////////////////////
#define  LINK_START_ROW 3//消球开始排布的初始行数
#define  LINK_END_ROW  12//消球截至排布的结束行数
#define  LINK_START_COL 5//消球开始排布的初始列数
#define  LINK_END_COL  14//消球截至排布的结束列数
#define  BLOCK_NUM  10//每个方块数组里应该放10个相同的成员
//////////////////////不同方块的编号//////////////////////
#define  LUOSAITA_NUM 1//罗塞塔为1
#define  LIF_NUM 2     //丽芙为2
#define  ARFA_NUM 3    //阿尔法为3
#define  BIANKA_NUM 4  //比安卡为4
#define  NANAMI_NUM 5  //七实为5
#define  LUSIYA_NUM 6  //露西亚为6
#define  SALINA_NUM 7  //赛琳娜为7
#define  WEILA_NUM  8  //维拉为8
#define  LUNA_NUM   9  //露娜为9
#define  QU_NUM     10 //曲为10
/////////////////////////不同方块各自的常态路径//////////////////////////////
#define  LUOSAITA_NOR_PATH ":/zs/stack/luosaita.png"//罗塞塔的常态图片路径
#define  ARFA_NOR_PATH ":/zs/stack/arfa.png"//阿尔法的常态图片路径
#define  LIF_NOR_PATH ":/zs/stack/lif.png"//丽芙的常态图片路径
#define  BIANKA_NOR_PATH ":/zs/stack/bianka.png"//比安卡的常态图片路径
#define  NANAMI_NOR_PATH ":/zs/stack/nanami.png"//七实的常态图片路径
#define  LUSIYA_NOR_PATH ":/zs/stack/lusiya.png"//露西亚的常态路径
#define  SALINA_NOR_PATH ":/zs/stack/salina.png"//赛琳娜的常态路径
#define  WEILA_NOR_PATH  ":/zs/stack/weila.png"//薇拉的常态路径
#define  LUNA_NOR_PATH   ":/zs/stack/luna.png"//露娜的常态路径
#define  QU_NOR_PATH     ":/zs/stack/qu.png"//曲的常态路径
/////////////////////////不同方块的激活态路径//////////////////////////////////////////////
#define  LUOSAITA_ACT_PATH ":/active/stack/luosaita_active.png"//罗塞塔的激活态路径
#define  ARFA_ACT_PATH     ":/active/stack/arfa_active.png"//阿尔法的激活态路径
#define  LIF_ACT_PATH      ":/active/stack/lif_active.png"//丽芙的激活态路径
#define  BIANKA_ACT_PATH   ":/active/stack/bianka_active.png"//比安卡的激活态路径
#define  NANAMI_ACT_PATH   ":/active/stack/nanami_active.png"//七实的激活态路径
#define  LUSIYA_ACT_PATH   ":/active/stack/lusiya_active.png"//露西亚的激活态路径
#define  SALINA_ACT_PATH   ":/active/stack/salina_active"//赛琳娜的激活态路径
#define  WEILA_ACT_PATH    ":/active/stack/weila_active"//薇拉的激活态路径
#define  LUNA_ACT_PATH     ":/active/stack/luna_active.png"//露娜的激活态路径
#define  QU_ACT_PATH       ":/active/stack/qu_active.png"//曲的激活态路径
///////////////////////////////////////////结算场景的几张图/////////////////////////////////////////////
#define  KEMIN_PATH        ":/end/stack/keminluoxuan.jpg"
#define  JUEHAI_PATH       ":/end/stack/juehaixinghuo.jpg"
#define  MIJING_PATH       ":/end/stack/mijingkehen.jpg"
////////////////////////////////////////////追加一个边栏///////////////////////////////////////////
#define  MARKBPX_PATH      ":/mark/stack/timerkeeper.jpg"
#define  BOX_WIDTH         240
#define  TIME_BOX_HEIGHT   120
#define  TIME_LAB_HEIGHT   150
//////////////////////////////////////////道具的参数/////////////////////////////////////////////////////////
///////时间道具
#define  PROPTIME_PATH1    ":/props/stack/Plust1.png"//绝缘沙
#define  PROPTIME_PATH2    ":/props/stack/Plust2.png"//草套沙漏
//////高亮道具
#define  PROPHINT_PATH1    ":/props/stack/Hint1.png"//追忆羽毛
#define  PROPHINT_PATH2    ":/props/stack/Hint2.png"//磐岩羽毛
/////重新洗地图的道具
#define  PROPSHU_PATH1     ":/props/stack/Shuffle1.png"//魔女火伤杯
#define  PROPSHU_PATH2     ":/props/stack/Shuffle2.jpg"//乐团冰伤杯
//////////////////////////////////////////背景音乐///////////////////////////////////////////////////////////////
#define  BGM_PATH1         "C:/Users/asus/Desktop/嗨格式视频转换器/punish1.WAV"
#define  BGM_PATH2         "C:/Users/asus/Desktop/嗨格式视频转换器/punish2.WAV"
#define  BGM_PATH3         "C:/Users/asus/Desktop/嗨格式视频转换器/punish3.WAV"
///////////////////////////////////////////高亮图片路径//////////////////////////////////////////////////////////////////////
#define  LUOSITA_HINT_PATH ":/hint/stack/luosaita_hint.png"
#define  LIF_HIINT_PATH    ":/hint/stack/lif_hint.png"
#define  ARFA_HINT_PATH    ":/hint/stack/arfa_hint.png"
#define  BIANKA_HINT_PATH  ":/hint/stack/bianka_hint.png"
#define  NANAMI_HINT_PATH  ":/hint/stack/nanami_hint.png"
#define  LUSIYA_HINT_PATH  ":/hint/stack/lusiya_hint.png"
#define  SALINA_HINT_PATH  ":/hint/stack/salina_hint.png"
#define  WEILA_HINT_PATH   ":/hint/stack/weila_hint.png"
#define  LUNA_HINT_PATH    ":/hint/stack/luna_hint.png"
#define  QU_HINT_PATH      ":/hint/stack/qu_hint.png"
/////////////////////////////////////文件路径///////////////////////////////////////////
#define  FILE_PATH         "E:/Qt_project_Qlink/DATA_ALIVE/stack_of_file/file_of_archive.txt"
#define  FILE_PATH2        "E:/Qt_project_Qlink/DATA_ALIVE/file_of_double/doublefile.txt"
///////////////////////////////////////按钮路径//////////////////////////////////////////////
#define  SINGLE_PATH       ":/btn/stack/single.jpg"
#define  DOUBLE_PATH       ":/btn/stack/double.jpg"
#define  SHEZHI_PATH       ":/btn/stack/shezhi.jpg"
//////////////////////////////////////////游戏帮助图片路径//////////////////////////////////////////////////
#define  RULE_PATH         ":/zs/stack/RULE.png"
///////////////////////////////////////计时器/////////////////////////////////////////////////////
#define  GAME_TIME          150










