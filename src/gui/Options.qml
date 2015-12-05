import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtQuick.Window 2.2
import "components"
import "dialog.js" as Dialog

WindowDialog {
    property real indent: 10
    id: root
    title: qsTr("Options")
    width: 500
    height: 200

    onAccepted: {
        SETTINGS.setValue("Path", "workspace", workspacePath.text)
        SETTINGS.setValue("Path", "log", logPath.text)
        SETTINGS.setValue("Network", "port", port.text)
    }

    ColumnLayout {
        width: parent.width

        GroupBox {
            title: qsTr("Directory")
            Layout.preferredWidth: parent.width

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
                    Component.onCompleted: forceActiveFocus()
                }

                BrowseButton {
                    onClicked: {
                        var selectDirectoryDialog = Dialog.selectDirectory(root)
                        selectDirectoryDialog.accepted.connect(function() {
                            workspacePath.text = UTILS.urlToPath(selectDirectoryDialog.fileUrl)
                        })
                    }
                }

                Label {
                    text: qsTr("Log:")
                }

                TextField {
                    id: logPath
                    Layout.fillWidth: true
                    text: SETTINGS.value("Path", "log")
                }

                BrowseButton {
                    onClicked: {
                        var selectDirectoryDialog = Dialog.selectDirectory(root)
                        selectDirectoryDialog.accepted.connect(function() {
                            logPath.text = UTILS.urlToPath(selectDirectoryDialog.fileUrl)
                        })
                    }
                }
            }
        }

        GroupBox {
            title: qsTr("Network")
            Layout.preferredWidth: parent.width

            RowLayout {

                Label {
                    text: qsTr("Port:")
                }

                TextField {
                    id: port
                    text: SETTINGS.value("Network", "port")
                }
            }
        }
    }
}

