#include "simpletest.h"
////////////////////////测试案例////////////////////////////
/// 测试1：有解测试
void simpleTest::case1Test()
{
    Singleplayer testSimple(1,3);
    //搭建测试场景地图
   Block testMap[5][5];
   for(int i=0;i<5;i++){
       for(int j=0;j<5;j++){
           testMap[i][j].blockRow=i+1;
           testMap[i][j].blockCol=j+1;
       }
   }
   //初始化测试方块数据
   testMap[1][1].pixNum=LUOSAITA_NUM;
   testMap[3][3].pixNum=LUOSAITA_NUM;
   testMap[1][2].pixNum=QU_NUM;
   testMap[2][1].pixNum=LUSIYA_NUM;
   testMap[3][2].pixNum=QU_NUM;
   testMap[2][2].pixNum=LUSIYA_NUM;
   QVERIFY(testSimple.canEliminate(testMap[1][1],testMap[3][3])==true);
}
///测试2：无解测试
void simpleTest::case2Test()
{
    Singleplayer testSimple(1,3);
    //搭建测试场景地图
   Block testMap[4][4];
   for(int i=0;i<4;i++){
       for(int j=0;i<4;i++){
           testMap[i][j].blockRow=i+1;
           testMap[i][j].blockCol=j+1;
       }
   }
   //初始化消除方块数据
   testMap[1][1].pixNum=LUOSAITA_NUM;
   testMap[2][2].pixNum=LUOSAITA_NUM;
   testMap[1][2].pixNum=QU_NUM;
   testMap[2][1].pixNum=LUSIYA_NUM;
   QVERIFY(testSimple.canEliminate(testMap[1][1],testMap[2][2])==false);
}


////////////////////////////测试结束////////////////////////////////////////
simpleTest::simpleTest()
{

}
/////////////////////////////游戏运行时注释掉下面这一行，测试时注释掉main.cpp里的main函数////////////////////////
//QTEST_MAIN(simpleTest)
