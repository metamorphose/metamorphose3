#-------------------------------------------------
#
# Project created by QtCreator 2015-03-09T11:17:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += "-std=c++11"

TARGET = metamorphose3
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    core/renamermodel.cpp \
    operationsform.cpp \
    operation/insertform.cpp \
    selectionform.cpp \
    core/operationmodel.cpp \
    core/renameritem.cpp \
    core/insertoperation.cpp \
    operationformmodel.cpp \
    suboperationsform.cpp \
    core/operationitem.cpp \
    operationformitem.cpp

HEADERS  += mainwindow.h \
    core/renamermodel.h \
    core/renameritem.h \
    operationsform.h \
    operation/insertform.h \
    selectionform.h \
    core/operationmodel.h \
    core/insertoperation.h \
    operationformmodel.h \
    core/operationitem.h \
    suboperationsform.h \
    operationformitem.h

FORMS    += mainwindow.ui \
    operationsform.ui \
    operation/insertform.ui \
    selectionform.ui \
    suboperationsform.ui \
    operationformitem.ui

RESOURCES += \
    resources.qrc
