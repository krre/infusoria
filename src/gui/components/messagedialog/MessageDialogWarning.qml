import QtQuick 2.5
import QtQuick.Dialogs 1.2

MessageDialogBase {
    title: qsTr("Warning")
    icon: StandardIcon.Warning
    standardButtons: StandardButton.Yes | StandardButton.No
}

