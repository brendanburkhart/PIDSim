#-------------------------------------------------
#
# Project created by QtCreator 2019-05-08T21:35:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PIDSim
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

CONFIG += c++11 qwt static

SOURCES += \
        angularsim.cpp \
        graphcontroller.cpp \
        inputgraph.cpp \
        linearsim.cpp \
        main.cpp \
        mainwindow.cpp \
        model.cpp \
        outputgraph.cpp \
        pid.cpp \
        utils.cpp

HEADERS += \
        angularsim.h \
        graphcontroller.h \
        inputgraph.h \
        linearsim.h \
        mainwindow.h \
        model.h \
        outputgraph.h \
        pid.h \
        utils.h

FORMS += \
        mainwindow.ui

win32:RC_ICONS += icon.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += C:\qwt-static-6.1.4\src
LIBS += -LC:\qwt-static-6.1.4\lib -lqwt
