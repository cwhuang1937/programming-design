#-------------------------------------------------
#
# Project created by QtCreator 2018-06-02T13:23:53
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Project3
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    Bullet.cpp \
    Enemy.cpp \
    Enemy_1.cpp \
    Player.cpp \
    Bullet_p1.cpp \
    Bullet_e1.cpp \
    Enemy_2.cpp \
    Bullet_e2.cpp \
    Bullet_boss1.cpp \
    Boss.cpp \
    Tool1.cpp \
    Tool2.cpp \
    Bomb.cpp

HEADERS += \
        mainwindow.h \
    Enemy.h \
    Enemy_1.h \
    Bullet.h \
    Player.h \
    Bullet_p1.h \
    Bullet_e1.h \
    Enemy_2.h \
    Bullet_e2.h \
    Boss.h \
    Bullet_boss1.h \
    Tool1.h \
    Tool2.h \
    Bomb.h

FORMS += \
        mainwindow.ui
RESOURCES += \
    res.qrc

