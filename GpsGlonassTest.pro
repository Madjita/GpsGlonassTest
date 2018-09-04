#-------------------------------------------------
#
# Project created by QtCreator 2017-11-29T08:53:16
#
#-------------------------------------------------

QT       += core gui sql serialport charts network printsupport axcontainer quick quickcontrols2 qml widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Stend #GpsGlonassTest
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


#DEFINES += QT_NO_DEBUG_OUTPUT

SOURCES += main.cpp\
        mainwindow.cpp \
    page1_checketap.cpp \
    page2_connectdevice.cpp \
    n6700.cpp \
    n6700model.cpp \
    relizproverka.cpp \
    tp8.cpp \
    osuilograf.cpp \
    proverka.cpp \
    gsg.cpp \
    finddevice.cpp \
    camber.cpp \
    report.cpp \
    proverkaitem.cpp \
    cambermodel.cpp \
    port.cpp \
    relizproverkatimer.cpp \
    portmodel.cpp \
    gsgmodel.cpp \
    osuilografmodel.cpp \
    finddeviceitem.cpp \
    screencapture.cpp \
    bdata.cpp \
    page3_proverki.cpp \
    page4_startetapcamber.cpp \
    page5_prmwindow.cpp \
    page6_finddevice.cpp \
    clockcircle.cpp \
    proverkamodel.cpp

HEADERS  += mainwindow.h \
    page1_checketap.h \
    page2_connectdevice.h \
    n6700.h \
    n6700model.h \
    tp8.h \
    finddevice.h \
    report.h \
    proverkaitem.h \
    relizproverka.h \
    proverka.h \
    cambermodel.h \
    camber.h \
    gsg.h \
    port.h \
    osuilografmodel.h \
    osuilograf.h \
    finddeviceitem.h \
    portmodel.h \
    relizproverkatimer.h \
    gsgmodel.h \
    screencapture.h \
    bdata.h \
    page3_proverki.h \
    page4_startetapcamber.h \
    page5_prmwindow.h \
    page6_finddevice.h \
    clockcircle.h \
    proverkamodel.h

FORMS    += mainwindow.ui \
    page1_checketap.ui \
    page2_connectdevice.ui \
    page3_proverki.ui \
    page4_startetapcamber.ui \
    page5_prmwindow.ui \
    page6_finddevice.ui

# Загрузка библиотеки (dll) для работы с устойствами по SCPI
# должна лежать в корне программы исходников для компиляции
LIBS += -L$$PWD/ -lMiVISA32


RESOURCES += \
    qml.qrc
