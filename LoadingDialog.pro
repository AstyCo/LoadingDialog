#-------------------------------------------------
#
# Project created by QtCreator 2016-11-10T17:12:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LoadingDialog
TEMPLATE = app

#LIBS += "$$PWD/lib/libqtwaitingspinner.a"
#INCLUDEPATH += "$$PWD/include"

SOURCES += main.cpp\
        mainwindow.cpp \
    loadingdialog.cpp \
    worker.cpp \
    specialworker.cpp \
    waitingspinnerwidget.cpp

HEADERS  += mainwindow.h \
    loadingdialog.h \
    worker.h \
    specialworker.h \
    waitingspinnerwidget.h

FORMS    += mainwindow.ui \
    loadingdialog.ui
