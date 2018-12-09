#-------------------------------------------------
#
# Project created by QtCreator 2018-12-08T22:19:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FitMaster5000
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

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    login_dialog.cpp \
    show_events_dialog.cpp \
    add_event_dialog.cpp \
    signup_for_event_dialog.cpp


HEADERS += \
        mainwindow.h \
    login_dialog.h \
    show_events_dialog.h \
    typedefs.h \
    add_event_dialog.h \
    signup_for_event_dialog.h


FORMS += \
        mainwindow.ui \
    login_dialog.ui \
    show_events_dialog.ui \
    add_event_dialog.ui \
    signup_for_event_dialog.ui
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
