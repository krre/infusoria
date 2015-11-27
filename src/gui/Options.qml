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

        Item {
            id: content
            Layout.preferredWidth: parent.width
            Layout.fillHeight: true
            clip: true
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

