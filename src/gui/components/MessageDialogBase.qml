import QtQuick
import QtQuick.Dialogs

MessageDialog {
    title: Qt.application.name
    onVisibleChanged: if (!visible) destroy()
    Component.onCompleted: open()
}
