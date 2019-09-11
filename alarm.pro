#-------------------------------------------------
#
# Project created by QtCreator 2017-01-23T16:50:54
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

TARGET = alarm

TEMPLATE = app
SOURCES += main.cpp\
	extendsensor.cpp \
        datarecord.cpp \
        mainwindow.cpp \
        coordparser.cpp \
        ftpmessage.cpp \
        message.cpp \
        filesmonitor.cpp \
        coords.cpp \
        sensors.cpp \
        latlong.cpp \
        timestruct.cpp \
        settings.cpp \
        myserver.cpp \
        messagesgenerator.cpp \
        synchronizer.cpp \
        ping.cpp \
        dialogdb.cpp \
        dialogstorage.cpp \
        course.cpp

HEADERS  += mainwindow.h \
	extendsensor.h \
        coordparser.h \
        ftpmessage.h \
        message.h \
        filesmonitor.h \
        datarecord.h \
        coords.h \
        sensors.h \
        latlong.h \
        timestruct.h \
        settings.h \
        myserver.h \
        messagesgenerator.h \
	synchronizer.h \
        ping.h \
        dbsettings.h \
        dialogdb.h \
        dialogstorage.h \
        course.h
        
FORMS   += mainwindow.ui \
    settings.ui \
    dialogdb.ui \
    dialogstorage.ui
