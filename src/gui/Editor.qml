import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "components"
import "dialog.js" as Dialog
import "utils.js" as Utils

WindowDialog {
    property alias name: name.text
    property alias path: path.text
    property int row
    id: root
    title: qsTr("Edit Infusoria")
    width: 400
    height: 300

    Component.onCompleted: {
        birthday.text = new Date(Number(Init.birthday(path.text))).toLocaleString()
        var map = Init.individuality(path.text)
        if (map) {
            sociability.text = Number(map.sociability).toFixed(4)
            zeal.text = Number(map.zeal).toFixed(4)
            activity.text = Number(map.activity).toFixed(4)
        }
    }

    onAccepted: {
        Init.setName(name.text, path.text)
        mainRoot.infuModel.setProperty(row, "name", name.text)
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

        Label {
            id: path
            text: path
        }

        Label {
            text: qsTr("Birthday:")
        }

        Label {
            id: birthday
        }

        GroupBox {
            title: qsTr("Individuality")
            Layout.columnSpan: 2
            Layout.fillWidth: true

            GridLayout {
                columns: 3

                Label {
                    text: qsTr("Sociability:")
                }

                TextField {
                    id: sociability
                    readOnly: true
                }

                Label {
                    text: (sociability.text) < 0 ? qsTr("Silent") : qsTr("Talkative")
                }

                Label {
                    text: qsTr("Zeal:")
                }

                TextField {
                    id: zeal
                    readOnly: true
                }

                Label {
                    text: parseFloat(zeal.text) < 0 ? qsTr("Lazy") : qsTr("Hardworking")
                }

                Label {
                    text: qsTr("Activity:")
                }

                TextField {
                    id: activity
                    readOnly: true
                }

                Label {
                    text: parseFloat(activity.text) < 0 ? qsTr("Thinker") : qsTr("Working")
                }
            }
        }
    }
}
