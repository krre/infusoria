import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import "utils.js" as Utils
import "dialog.js" as Dialog

ApplicationWindow {
    id: mainRoot
    title: APP.name
    width: 800
    height: 600
    visible: true
    menuBar: MenuBar {
        Menu {
            title: qsTr("Infusoria")

            MenuItem {
                text: qsTr("New...")
                onTriggered: Utils.createDynamicObject(mainRoot, "qrc:/gui/NewInfusoria.qml")
            }

            MenuSeparator {}

            MenuItem {
                text: qsTr("Exit")
                shortcut: "Ctrl+Q"
                onTriggered: Qt.quit()
            }
        }

        Menu {
            title: qsTr("Tools")

            MenuItem {
                text: qsTr("Options...")
                onTriggered: Utils.createDynamicObject(mainRoot, "qrc:/gui/Options.qml")
            }
        }

        Menu {
            title: qsTr("Help")

            MenuItem {
                text: qsTr(String("About %1").arg(APP.name))
                onTriggered: Utils.createDynamicObject(mainRoot, "qrc:/gui/About.qml")
            }
        }
    }

    Component.onCompleted: {
        var geometry = SETTINGS.map("Gui")
        if (Object.keys(geometry).length) {
            x = geometry.x
            y = geometry.y
            width = geometry.width
            height = geometry.height
        } else {
            if (Screen.width && Screen.height) {
                x = (Screen.width - width) / 2
                y = (Screen.height - height) / 2
            } else {
                x = 200
                y = 200
            }
        }
    }

    onClosing: {
        SETTINGS.setMap("Gui", {
            x: x,
            y: y,
            width: width,
            height: height
        })
    }

    RowLayout {
        anchors.fill: parent
        spacing: 0

        TableView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            frameVisible: false

            TableViewColumn {
                title: qsTr("Name")
            }

            TableViewColumn {
                title: qsTr("State")
            }

            TableViewColumn {
                title: qsTr("Path")
            }
        }

        ColumnLayout {
            Layout.alignment: Qt.AlignTop
            Layout.margins: 7

            Button {
                text: qsTr("Add")
                onClicked: {
                    var selectFileDialog = Dialog.selectFile(mainRoot, {
                        selectMultiple: true, folder: UTILS.pathToUrl(SETTINGS.value("Path", "workspace")),
                        nameFilters: [ qsTr("Infusoria files (*.infu)"), qsTr("All files (*)") ]})
                    selectFileDialog.accepted.connect(function() {
                        for (var i in selectFileDialog.fileUrls) {
                            var filePath = UTILS.urlToPath(selectFileDialog.fileUrls[i])
                            print(filePath)
                        }
                    })
                }
            }

            Button {
                text: qsTr("Run")
            }

            Button {
                text: qsTr("Stop")
            }

            Button {
                text: qsTr("Remove")
            }
        }
    }
}
