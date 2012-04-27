#-------------------------------------------------
#
# Project created by QtCreator 2011-11-15T09:38:19
#
#-------------------------------------------------

QT       += core gui

TARGET = Xedithor
TEMPLATE = app


SOURCES += src\main.cpp\
        src\mainwindow.cpp \
    src/xscene.cpp \
    src/rectselectionitem.cpp \
    src/hlinegraphicsitem.cpp \
    src/graphwidgets.cpp \
    src/editwindow.cpp \
    src/moduleslist.cpp \
    src/rowdata.cpp \
    src/rowdatahandler.cpp \
    src/uidmanager.cpp \
    src/animatedPixmapItem.cpp \
    src/mfatablemodel.cpp \
    src/packtextureparser.cpp \
    src/exportdialog.cpp \
    src/spriteexporter.cpp \
    src/appconfig.cpp \
    src/setworkdirdialog.cpp

HEADERS  += mainwindow.h \
    src/xscene.h \
    src/rowdata.h \
    src/rectselectionitem.h \
    src/mainwindow.h \
    src/hlinegraphicsitem.h \
    src/graphwidgets.h \
    src/globalconstant.h \
    src/editwindow.h \
    src/moduleslist.h \
    src/rowdatahandler.h \
    src/uidmanager.h \
    src/animatedPixmapItem.h \
    src/mfatablemodel.h \
    src/packtextureparser.h \
    src/exportdialog.h \
    src/spriteexporter.h \
    src/appconfig.h \
    src/setworkdirdialog.h


FORMS    += layout_ui/mainwindow.ui \
    layout_ui/editwindow.ui \
    layout_ui/toolDialog.ui \
    layout_ui/exportdialog.ui \
    layout_ui/spriteselector.ui \
    layout_ui/setworkdirdialog.ui

RESOURCES += \
    XedithorResources.qrc

OTHER_FILES += \
    temp.txt

CONFIG += console









































































