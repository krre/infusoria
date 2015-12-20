import QtQuick 2.5
import QtQuick.Dialogs 1.2

MessageDialog {
    title: mainRoot.title
    onVisibleChanged: if (!visible) destroy()
    Component.onCompleted: open()
}
