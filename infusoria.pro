TEMPLATE = app
QT += widgets qml quick sql websockets

CONFIG += c++20

include(src/common/common.pri)

SOURCES += \
    src/base/FileOperations.cpp \
    src/base/InfuController.cpp \
    src/base/InfuProto.cpp \
    src/database/Init.cpp \
    src/infusoria/Infusoria.cpp \
    src/logger/Logger.cpp \
    src/main.cpp \
    src/net/WebSocketManager.cpp

HEADERS += \
    src/base/FileOperations.h \
    src/base/InfuController.h \
    src/base/InfuProto.h \
    src/database/Init.h \
    src/infusoria/Infusoria.h \
    src/logger/Logger.h \
    src/net/WebSocketManager.h

RESOURCES += \
    src/qml.qrc

DISTFILES += \
    README.md \
    src/gui/main.qml \
    src/gui/Options.qml \
    src/gui/components/filedialog/FileDialogBase.qml \
    src/gui/components/filedialog/FileDialogDirectory.qml \
    src/gui/components/filedialog/FileDialogOpen.qml \
    src/gui/components/BrowseButton.qml \
    src/gui/components/WindowDialog.qml \
    src/gui/dialog.js \
    src/gui/utils.js \
    src/gui/About.qml \
    src/gui/NewInfusoria.qml \
    src/gui/components/ButtonBase.qml \
    src/gui/components/SliderIndividuality.qml \
    src/gui/Editor.qml \
    src/gui/components/MessageDialogBase.qml
