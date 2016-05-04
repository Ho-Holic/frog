
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = relation
TEMPLATE = app

INCLUDEPATH += src/

#temporary
INCLUDEPATH += ../../

SOURCES += \
    src/main.cpp\
    src/MainWindow.cpp \
    src/IdGenerator.cpp \
    src/world/World.cpp \
    src/world/Entity.cpp \
    src/world/Relation.cpp \
    src/world/Connection.cpp \
    src/render/GraphWidget.cpp \
    src/render/ColorScheme.cpp \
    src/import/LibraryImportWidget.cpp \
    src/import/LibraryAddWidget.cpp \
    src/import/LibraryViewWidget.cpp \
    src/import/LibraryModel.cpp \
    src/import/LibraryItem.cpp \
    src/import/LibraryItemData.cpp \
    src/world/VectorMath.cpp \
    src/convert/Convertor.cpp \
    src/world/WorldEvent.cpp \
    src/world/Header.cpp \
    src/render/tools/Tool.cpp \
    src/render/tools/HandTool.cpp \
    src/render/tools/ConnectTool.cpp \
    src/render/tools/MoveTool.cpp \
    src/render/Tools.cpp \
    src/render/Environment.cpp \
    src/render/tools/MarkingMenuItem.cpp

HEADERS  += \
    src/cplusplus11.h \
    src/MainWindow.h \
    src/IdGenerator.h \
    src/world/World.h \
    src/world/Entity.h \
    src/world/Relation.h \
    src/world/Connection.h \
    src/render/GraphWidget.h \
    src/render/ColorScheme.h \
    src/import/LibraryImportWidget.h \
    src/import/LibraryAddWidget.h \
    src/import/LibraryViewWidget.h \
    src/import/LibraryModel.h \
    src/import/LibraryItem.h \
    src/import/LibraryItemData.h \
    src/world/VectorMath.h \
    src/convert/Convertor.h \
    src/world/WorldEvent.h \
    src/world/Header.h \
    src/render/tools/Tool.h \
    src/render/tools/HandTool.h \
    src/render/tools/ConnectTool.h \
    src/render/tools/MoveTool.h \
    src/render/Tools.h \
    src/render/Environment.h \
    src/render/tools/MarkingMenuItem.h
