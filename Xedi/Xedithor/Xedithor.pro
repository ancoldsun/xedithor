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
    src/moduletablemodel.cpp \
    src/hlinegraphicsitem.cpp \
    src/graphwidgets.cpp \
    src/editwindow.cpp \
    src/moduleslist.cpp \
    src/rowdata.cpp \
    src/rowdatahandler.cpp \
    src/xdframe.cpp \
    src/uidmanager.cpp \
    src/animatedPixmapItem.cpp

HEADERS  += mainwindow.h \
    src/xscene.h \
    src/rowdata.h \
    src/rectselectionitem.h \
    src/moduletablemodel.h \
    src/mainwindow.h \
    src/hlinegraphicsitem.h \
    src/graphwidgets.h \
    src/globalconstant.h \
    src/editwindow.h \
    src/moduleslist.h \
    src/rowdatahandler.h \
    src/xdframe.h \
    src/uidmanager.h \
    src/animatedPixmapItem.h


FORMS    += mainwindow.ui \
    editwindow.ui \
    toolDialog.ui

RESOURCES += \
    XedithorResources.qrc

OTHER_FILES += \
    temp.txt




















































