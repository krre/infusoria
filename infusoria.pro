TEMPLATE = app
QT += sql
QT -= gui

CONFIG += c++11
CONFIG += console
CONFIG -= app_bundle

SOURCES += \
    src/main.cpp \
    src/database/init.cpp

HEADERS += \
    src/database/init.h \
    src/global/macro.h
