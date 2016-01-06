#-------------------------------------------------
#
# Project created by QtCreator 2015-08-31T23:36:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = settingspider
TEMPLATE = app


SOURCES += src/main.cpp\
        src/MainWindow.cpp \
    src/World.cpp \
    src/Entity.cpp \
    src/IdGenerator.cpp \
    src/Relation.cpp \
    src/GraphWidget.cpp \
    src/Connection.cpp \
    src/ColorScheme.cpp \
    src/LibraryImportWidget.cpp \
    src/LibraryAddWidget.cpp \
    src/LibraryViewWidget.cpp \
    src/PathPair.cpp \
    src/LibraryModel.cpp \
    src/LibraryItem.cpp

HEADERS  += \
    src/MainWindow.h \
    src/Entity.h \
    src/World.h \
    src/IdGenerator.h \
    src/Relation.h \
    src/cplusplus11.h \
    src/GraphWidget.h \
    src/Connection.h \
    src/ColorScheme.h \
    src/LibraryImportWidget.h \
    src/LibraryAddWidget.h \
    src/LibraryViewWidget.h \
    src/PathPair.h \
    src/LibraryModel.h \
    src/LibraryItem.h
