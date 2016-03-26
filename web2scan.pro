#-------------------------------------------------
#
# Project created by QtCreator 2016-03-25T22:57:53
#
#-------------------------------------------------

CONFIG   += c++11
QT       += core gui concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -lcurl -std=c++11

LIBS += -lcurl

TARGET = web2scan
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    startthread.cpp \
    urltree.cpp

HEADERS  += mainwindow.h \
    startthread.h \
    urltree.h \
    url_util.h

FORMS    += mainwindow.ui
