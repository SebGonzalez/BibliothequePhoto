#-------------------------------------------------
#
# Project created by QtCreator 2019-01-19T09:49:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IHM
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++17

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    bibliotheque.cpp \
    image.cpp \
    dialog.cpp \
    bibliothequewidget.cpp \
    landingpage.cpp \
    ajouttag.cpp \
    mainwindowredesigned.cpp \
    viewer.cpp \
    textoverphoto.cpp \
    tagdialog.cpp \
    albumdialog.cpp

HEADERS += \
        mainwindow.h \
    bibliotheque.h \
    image.h \
    dialog.h \
    global_variables.h \
    bibliothequewidget.h \
    landingpage.h \
    ajouttag.h \
    mainwindowredesigned.h \
    viewer.h \
    textoverphoto.h \
    tagdialog.h \
    albumdialog.h


FORMS += \
        mainwindow.ui \
        dialog.ui \
    landingpage.ui \
    ajouttag.ui \
    mainwindowredesigned.ui \
    viewer.ui \
    tagdialog.ui \
    albumdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
