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
    renamermodel.cpp \
    operationsform.cpp \
    operation/insertform.cpp \
    selectionform.cpp \
    operationmodel.cpp

HEADERS  += mainwindow.h \
    renamermodel.h \
    renameritem.h \
    operationsform.h \
    operation/insertform.h \
    selectionform.h \
    operationmodel.h

FORMS    += mainwindow.ui \
    operationsform.ui \
    operation/insertform.ui \
    selectionform.ui
