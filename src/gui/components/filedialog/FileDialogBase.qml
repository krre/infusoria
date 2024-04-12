import QtQuick
import QtQuick.Dialogs

FileDialog {
    onVisibleChanged: if (!visible) destroy()
    Component.onCompleted: open()
}

