QT       += core gui multimedia testlib


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    block.cpp \
    doubleend.cpp \
    doubleplayer.cpp \
    endwidget.cpp \
    helpwidget.cpp \
    hint.cpp \
    main.cpp \
    mainscene.cpp \
    mypushbutton.cpp \
    plustime.cpp \
    role.cpp \
    selectscene.cpp \
    shuffleprop.cpp \
    simpletest.cpp \
    singleplayer.cpp

HEADERS += \
    Config.h \
    block.h \
    doubleend.h \
    doubleplayer.h \
    endwidget.h \
    helpwidget.h \
    hint.h \
    mainscene.h \
    mypushbutton.h \
    plustime.h \
    role.h \
    selectscene.h \
    shuffleprop.h \
    simpletest.h \
    singleplayer.h

FORMS += \
    doubleend.ui \
    doubleplayer.ui \
    endwidget.ui \
    helpwidget.ui \
    mainscene.ui \
    selectscene.ui \
    singleplayer.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
