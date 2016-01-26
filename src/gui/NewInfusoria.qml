import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import "components"
import "dialog.js" as Dialog
import "utils.js" as Utils

WindowDialog {
    id: root
    title: qsTr("New Infusoria")
    width: 400
    height: 300

    onAccepted: {
        if (!name.text) {
            stayOnScreen = true
            Dialog.errorMessage(qsTr("Name is empty"))
            name.forceActiveFocus()
        } else {
            var filePath = directory.text + "/" + file.text
            if (UTILS.isFileExists(filePath)) {
                stayOnScreen = true
                var warningDialog = Dialog.warning(qsTr("File is exists. Overwrite?"))
                warningDialog.yes.connect(function() {
                    UTILS.removeFile(filePath)
                    INIT.create(name.text, filePath, getIndividuality())
                    root.destroy()
                })
            } else {
                INIT.create(name.text, filePath, getIndividuality())
                if (openAfterCreating.checked) {
                    infuModel.append({ name: name.text, state: "", path: filePath })
                }
            }
        }
    }

    function getIndividuality() {
        var individuality = {}
        individuality.sociability = sociability.value
        individuality.zeal = zeal.value
        individuality.activity = activity.value
        return individuality
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
            onTextChanged: file.text = name.text.trim().replace(/ /g, '-').toLowerCase() + ".infu"
            Component.onCompleted: forceActiveFocus()
        }

        Label {
            text: qsTr("File:")
        }

        TextField {
            id: file
            Layout.fillWidth: true
        }

        Label {
            text: qsTr("Directory:")
        }

        RowLayout {
            Layout.fillWidth: true

            TextField {
                id: directory
                Layout.fillWidth: true
                text: SETTINGS.value("Path", "workspace")
            }

            BrowseButton {
                onClicked: {
                    var selectDirectoryDialog = Dialog.selectDirectory(root)
                    selectDirectoryDialog.accepted.connect(function() {
                        directory.text = UTILS.urlToPath(selectDirectoryDialog.fileUrl)
                    })
                }
            }
        }

        CheckBox {
            id: openAfterCreating
            Layout.columnSpan: 2
            text: qsTr("Add after creating")
            checked: true
        }

        GroupBox {
            title: qsTr("Individuality")
            Layout.columnSpan: 2
            Layout.fillWidth: true

            GridLayout {
                width: parent.width
                columns: 3

                Label {
                    text: qsTr("Silent")
                }

                SliderIndividuality {
                    id: sociability
                    Layout.fillWidth: true
                }

                Label {
                    text: qsTr("Talkative")
                }

                Label {
                    text: qsTr("Lazy")
                }

                SliderIndividuality {
                    id: zeal
                    Layout.fillWidth: true
                }

                Label {
                    text: qsTr("Hardworking")
                }

                Label {
                    text: qsTr("Thinker")
                }

                SliderIndividuality {
                    id: activity
                    Layout.fillWidth: true
                }

                Label {
                    text: qsTr("Working")
                }
            }
        }
    }
}
