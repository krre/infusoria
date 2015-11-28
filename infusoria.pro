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
    src/base/settings.cpp \
    src/global/utils.cpp

HEADERS += \
    src/database/init.h \
    src/global/macro.h \
    src/global/app.h \
    src/net/websocketmanager.h \
    src/mind/mind.h \
    src/repl/repl.h \
    src/logger/logger.h \
    src/base/settings.h \
    src/global/utils.h

RESOURCES += \
    src/qml.qrc

DISTFILES += \
    README.md \
    src/gui/main.qml \
    src/gui/Options.qml \
    src/gui/components/filedialog/FileDialogBase.qml \
    src/gui/components/filedialog/FileDialogDirectory.qml \
    src/gui/components/filedialog/FileDialogOpen.qml \
    src/gui/components/messagedialog/MessageDialogBase.qml \
    src/gui/components/messagedialog/MessageDialogError.qml \
    src/gui/components/messagedialog/MessageDialogInformation.qml \
    src/gui/components/messagedialog/MessageDialogQuestion.qml \
    src/gui/components/messagedialog/MessageDialogWarning.qml \
    src/gui/components/BrowseButton.qml \
    src/gui/components/WindowDialog.qml \
    src/gui/dialog.js \
    src/gui/utils.js \
    src/gui/About.qml \
    src/gui/NewInfusoria.qml
