TEMPLATE = app
QT += sql websockets
QT -= gui

CONFIG += c++11
CONFIG += console
CONFIG -= app_bundle

SOURCES += \
    src/main.cpp \
    src/database/init.cpp \
    src/net/websocketmanager.cpp

HEADERS += \
    src/database/init.h \
    src/global/macro.h \
    src/global/app.h \
    src/net/websocketmanager.h
