#-------------------------------------------------
#
# Project created by QtCreator 2014-01-11T08:04:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FlySightIngest
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    copyworker.cpp \
    filelistwidget.cpp \
    configdialog.cpp

HEADERS  += mainwindow.h \
    copyworker.h \
    filelistwidget.h \
    configdialog.h

FORMS    += mainwindow.ui \
    configdialog.ui

RC_FILE += FlySightIngest.rc
