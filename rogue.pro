#-------------------------------------------------
#
# Project created by QtCreator 2016-05-11T11:35:52
#
#-------------------------------------------------

QT       += core gui
CONFIG   += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Rogue
TEMPLATE = app


SOURCES += main.cpp\
    gui/autosizetableview.cpp \
    gui/mainwindow.cpp \
    gui/mapview.cpp \
    gui/mapsizedialog.cpp \
    gui/playerinfowidget.cpp \
    items/abstractcollectibleitem.cpp \
    items/abstractcombatitem.cpp \
    items/abstractmapitem.cpp \
    items/abstractnpc.cpp \
    items/gold.cpp \
    items/monster.cpp \
    items/obstacle.cpp \
    items/player.cpp \
    mechanics/dice.cpp \
    mechanics/moveset.cpp \
    mechanics/playerlog.cpp \
    mechanics/randomizer.cpp \
    world/dungeon.cpp \
    world/dungeongenerator.cpp \
    world/mapmodel.cpp \
    gui/playerlogwidget.cpp

HEADERS  += gui/mainwindow.h \
    gui/autosizetableview.h \
    gui/mainwindow.h \
    gui/mapview.h \
    gui/mapsizedialog.h \
    gui/playerinfowidget.h \
    items/abstractcollectibleitem.h \
    items/abstractcombatitem.h \
    items/abstractmapitem.h \
    items/abstractnpc.h \
    items/gold.h \
    items/monster.h \
    items/obstacle.h \
    items/player.h \
    mechanics/constants.h \
    mechanics/dice.h \
    mechanics/moveset.h \
    mechanics/playerlog.h \
    mechanics/randomizer.h \
    world/dungeon.h \
    world/dungeongenerator.h \
    world/mapmodel.h \
    gui/playerlogwidget.h

FORMS    += gui/mainwindow.ui \
    gui/mapsizedialog.ui \
    gui/playerinfowidget.ui

INCLUDEPATH += gui\
               items\
               mechanics\
               world

DISTFILES +=

RESOURCES += \
    Resources/images.qrc
