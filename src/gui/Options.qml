import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
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
        Settings.setValue("Path", "workspace", workspacePath.text)
        Settings.setValue("Path", "log", logPath.text)
        Settings.setValue("Network", "port", port.text)
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
                    text: Settings.value("Path", "workspace")
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
                    text: Settings.value("Path", "log")
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
                    text: Settings.value("Network", "port")
                }
            }
        }
    }
}

