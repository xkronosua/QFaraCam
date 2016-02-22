#-------------------------------------------------
#
# Project created by QtCreator 2016-02-20T21:33:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QFaraCam
TEMPLATE = app
QT += multimedia multimediawidgets

SOURCES += main.cpp\
        qfaracam.cpp \
    capturethread.cpp \
    videowidget.cpp \
    myqgraphicsview.cpp

HEADERS  += qfaracam.h \
    capturethread.h \
    videowidget.h \
    myqgraphicsview.h

FORMS    += qfaracam.ui
LIBS += -lv4l2 -lv4lconvert
