import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtQuick.Window 2.2

Window {
    property real indent: 10
    id: root
    title: qsTr("Options")
    width: 500
    height: 200
    minimumWidth: 200
    minimumHeight: 200
    visible: true
    modality: Qt.ApplicationModal
    color: sysPalette.window

    onVisibleChanged: if (!visible) root.destroy()

    SystemPalette {
        id: sysPalette
        colorGroup: SystemPalette.Active
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: indent
        Layout.alignment: Qt.AlignHCenter
        spacing: indent

        GridLayout {
            Layout.preferredWidth: parent.width
            Layout.fillHeight: true
            clip: true
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

        RowLayout {
            Layout.alignment: Qt.AlignHCenter

            Button {
                text: qsTr("OK")
                onClicked: {

                    root.destroy()
                }
            }

            Button {
                text: qsTr("Cancel")
                onClicked: root.destroy()
            }
        }
    }
}

