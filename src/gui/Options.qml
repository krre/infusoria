import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtQuick.Window 2.2
import "components"


WindowDialog {
    property real indent: 10
    id: root
    title: qsTr("Options")
    width: 500
    height: 200

    onAccepted: {}

    GridLayout {
        width: parent.width
        columns: 3

        Label {
            text: qsTr("Workspace:")
        }

        TextField {
            id: workspacePath
            Layout.fillWidth: true
            text: SETTINGS.value("Path", "workspace")
        }

        Button {
            implicitWidth: 30
            text: "..."
            onClicked: {}
        }

        Label {
            text: qsTr("Log:")
        }

        TextField {
            id: logPath
            Layout.fillWidth: true
            text: SETTINGS.value("Path", "log")
        }

        Button {
            implicitWidth: 30
            text: "..."
            onClicked: {}
        }

        Label {
            text: qsTr("Port:")
        }

        TextField {
            id: port
            Layout.fillWidth: true
            Layout.columnSpan: 2
            text: SETTINGS.value("Server", "port")
        }
    }
}

