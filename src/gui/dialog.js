.import "utils.js" as Utils

function selectFile(parent, options) {
    return Utils.createDynamicObject(parent, "qrc:/gui/components/filedialog/FileDialogOpen.qml", options ? options : {})
}

function selectDirectory(parent) {
    return Utils.createDynamicObject(parent, "qrc:/gui/components/filedialog/FileDialogDirectory.qml")
}

function infoMessage(message) {
    return Utils.createDynamicObject(mainRoot, "qrc:/gui/components/messagedialog/MessageDialogInformation.qml", { text: message })
}

function warningMessage(message) {
    return Utils.createDynamicObject(mainRoot, "qrc:/gui/components/messagedialog/MessageDialogWarning.qml", { text: message })
}

function questionMessage(message) {
    return Utils.createDynamicObject(mainRoot, "qrc:/gui/components/messagedialog/MessageDialogQuestion.qml", { text: message })
}

function errorMessage(message) {
    return Utils.createDynamicObject(mainRoot, "qrc:/gui/components/messagedialog/MessageDialogError.qml", { text: message })
}
