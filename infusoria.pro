TEMPLATE = app
QT += widgets qml quick sql websockets

CONFIG += c++11
CONFIG += console
CONFIG -= app_bundle

SOURCES += \
    src/main.cpp \
    src/database/init.cpp \
    src/net/websocketmanager.cpp \
    src/mind/mind.cpp \
    src/repl/repl.cpp \
    src/logger/logger.cpp \
    src/base/settings.cpp

HEADERS += \
    src/database/init.h \
    src/global/macro.h \
    src/global/app.h \
    src/net/websocketmanager.h \
    src/mind/mind.h \
    src/repl/repl.h \
    src/logger/logger.h \
    src/base/settings.h

RESOURCES += \
    src/qml.qrc

DISTFILES += \
    README.md \
    src/gui/main.qml \
    src/gui/Options.qml
