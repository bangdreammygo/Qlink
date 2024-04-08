#ifndef  SIMPLETEST_H
#define  SIMPLETEST_H
#include<QtTest/QtTest>
#include"singleplayer.h"
class simpleTest : public QObject
{
    Q_OBJECT

private slots:
    void case1Test();
    void case2Test();
public:
     simpleTest();

};
#endif

