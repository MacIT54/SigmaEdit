#-------------------------------------------------
#
# Project created by QtCreator 2024-10-03T20:29:51
#
#-------------------------------------------------

QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SigmaEdit
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
QT += multimedia


# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        bird.cpp \
        circle.cpp \
        graphiceditor.cpp \
        ledinletters.cpp \
        line.cpp \
        main.cpp \
        mainwindow.cpp \
        movabletextitem.cpp \
        mrikhletters.cpp \
        objectclass.cpp \
        objecteditor.cpp \
        phone.cpp \
        rectangle.cpp \
        shape.cpp \
        triangle.cpp

HEADERS += \
        bird.h \
        circle.h \
        graphiceditor.h \
        ledinletters.h \
        line.h \
        mainwindow.h \
        movabletextitem.h \
        mrikhletters.h \
        objectclass.h \
        objecteditor.h \
        phone.h \
        rectangle.h \
        shape.h \
        triangle.h

FORMS += \
        mainwindow.ui

RESOURCES += icons.qrc \
    icons.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
