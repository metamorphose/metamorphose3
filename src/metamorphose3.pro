#-------------------------------------------------
#
# Project created by QtCreator 2015-03-09T11:17:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = metamorphose3
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    diritem.cpp \
    selectionparams.cpp \
    renamermodel.cpp \
    operation/insert.cpp

HEADERS  += mainwindow.h \
    selectionparams.h \
    renamermodel.h \
    renameritem.h \
    operation/insert.h

FORMS    += mainwindow.ui \
    selectionparams.ui \
    operation/insert.ui
