.import QtQuick.Dialogs as Dialogs
.import "utils.js" as Utils

var messageDialogUrl = "qrc:/gui/components/MessageDialogBase.qml"

function selectFile(parent, options) {
    return Utils.createDynamicObject(parent, "qrc:/gui/components/filedialog/FileDialogOpen.qml", options || {})
}

function selectDirectory(parent) {
    return Utils.createDynamicObject(parent, "qrc:/gui/components/filedialog/FileDialogDirectory.qml")
}

function info(message, parent) {
    return Utils.createDynamicObject(parent || mainRoot, messageDialogUrl,
                                     { icon: Dialogs.StandardIcon.Information, text: message })
}

function warning(message, parent) {
    return Utils.createDynamicObject(parent || mainRoot, messageDialogUrl,
                                     { icon: Dialogs.StandardIcon.Information, text: message })
}

function question(message, parent) {
    return Utils.createDynamicObject(parent || mainRoot, messageDialogUrl,
                                     { icon: Dialogs.StandardIcon.Information, standardButtons: Dialogs.StandardButton.Yes | Dialogs.StandardButton.No, text: message })
}

function error(message, parent) {
    return Utils.createDynamicObject(parent || mainRoot, messageDialogUrl,
                                     { icon: Dialogs.StandardIcon.Critical, text: message })
}
