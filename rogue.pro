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
        mainwindow.cpp \
    mapview.cpp \
    mapmodel.cpp \
    randomizer.cpp \
    mapsizedialog.cpp \
    player.cpp \
    abstractmapitem.cpp \
    obstacle.cpp \
    gold.cpp \
    playerinfowidget.cpp \
    abstractcollectibleitem.cpp \
    dungeongenerator.cpp \
    autosizetableview.cpp

HEADERS  += mainwindow.h \
    mapview.h \
    mapmodel.h \
    randomizer.h \
    mapsizedialog.h \
    player.h \
    abstractmapitem.h \
    obstacle.h \
    gold.h \
    playerinfowidget.h \
    abstractcollectibleitem.h \
    dungeongenerator.h \
    autosizetableview.h

FORMS    += mainwindow.ui \
    mapsizedialog.ui \
    playerinfowidget.ui

DISTFILES +=

RESOURCES += \
    Resources/images.qrc
