#-------------------------------------------------
#
# Project created by QtCreator 2019-04-02T09:14:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AutoTest
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
    sdkcontext.cpp \
    sdkkinematic.cpp \
    ioservice.cpp \
    varservice.cpp \
    paramservice.cpp \
    movementservice.cpp \
    servoservice.cpp

HEADERS += \
        mainwindow.h \
    sdkcontext.h \
    sdkkinematic.h \
    ioservice.h \
    varservice.h \
    paramservice.h \
    movementservice.h \
    servoservice.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -LD:/UbuntuShare/elt_industry_robot_sdk/release_64/lib/ -leltrobot
else:win32:CONFIG(debug, debug|release): LIBS += -LD:/UbuntuShare/elt_industry_robot_sdk/release_64/lib/ -leltrobotd
else:unix: LIBS += -LD:/UbuntuShare/elt_industry_robot_sdk/release_64/lib/ -leltrobot

INCLUDEPATH += D:/UbuntuShare/elt_industry_robot_sdk/release_64/include
DEPENDPATH += D:/UbuntuShare/elt_industry_robot_sdk/release_64/include

win32:CONFIG(release, debug|release): LIBS += -LD:/UbuntuShare/elt_industry_robot_sdk/release_64/lib/ -lpthreadVC2
else:win32:CONFIG(debug, debug|release): LIBS += -LD:/UbuntuShare/elt_industry_robot_sdk/release_64/lib/ -lpthreadVC2d
else:unix: LIBS += -LD:/UbuntuShare/elt_industry_robot_sdk/release_64/lib/ -lpthreadVC2

INCLUDEPATH += D:/UbuntuShare/elt_industry_robot_sdk/release_64/include
DEPENDPATH += D:/UbuntuShare/elt_industry_robot_sdk/release_64/include
