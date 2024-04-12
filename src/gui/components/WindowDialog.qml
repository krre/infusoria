import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import QtQuick.Dialogs

Window {
    default property alias data: content.data
    property real indent: 10
    property int standardButtons: StandardButton.Ok | StandardButton.Cancel
    property bool stayOnScreen: false
    id: root
    width: 500
    height: 500
    minimumWidth: 200
    minimumHeight: 200
    visible: true
    modality: Qt.ApplicationModal
    color: sysPalette.window

    signal accepted
    signal rejected

    onVisibleChanged: if (!visible) root.destroy()

    SystemPalette {
        id: sysPalette
        colorGroup: SystemPalette.Active
    }

    Action {
        shortcut: "Esc"
        onTriggered: root.destroy()
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: indent
        Layout.alignment: Qt.AlignHCenter
        spacing: indent

        Item {
            id: content
            Layout.preferredWidth: parent.width
            Layout.fillHeight: true
            clip: true
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter

            ButtonBase {
                text: qsTr("OK")
                visible: (StandardButton.Ok & standardButtons) === StandardButton.Ok
                // isDefault: activeFocus || activeFocusItem && activeFocusItem.objectName !== "ButtonBase"
                onClicked: {
                    root.accepted()
                    if (!stayOnScreen) {
                        root.destroy()
                    }
                }
            }

            ButtonBase {
                text: qsTr("Cancel")
                visible: (StandardButton.Cancel & standardButtons) === StandardButton.Cancel
                onClicked: {
                    root.rejected()
                    root.destroy()
                }
            }

            ButtonBase {
                text: qsTr("Close")
                visible: (StandardButton.Close & standardButtons) === StandardButton.Close
                onClicked: {
                    root.rejected()
                    root.destroy()
                }
            }
        }
    }
}
