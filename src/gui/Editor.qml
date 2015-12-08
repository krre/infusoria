import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import "components"
import "dialog.js" as Dialog
import "utils.js" as Utils

WindowDialog {
    property alias name: name.text
    property alias path: path.text
    id: root
    title: qsTr("Edit Infusoria")
    width: 400
    height: 300

    onAccepted: {

    }

    GridLayout {
        width: parent.width
        columns: 2

        Label {
            text: qsTr("Name:")
        }

        TextField {
            id: name
            Layout.fillWidth: true
            Component.onCompleted: forceActiveFocus()
        }

        Label {
            text: qsTr("Path:")
        }

        TextField {
            id: path
            Layout.fillWidth: true
            text: path
            readOnly: true
        }
    }
}
