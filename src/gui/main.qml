import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import "utils.js" as Utils
import "dialog.js" as Dialog

ApplicationWindow {
    property string infuListPath: APP.applicationDirPath + "/infu.txt"
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

        var infuList = UTILS.loadInfuList(infuListPath)
        if (infuList) {
            infuModel.addInfuList(infuList)
        }
    }

    onClosing: {
        SETTINGS.setMap("Gui", {
            x: x,
            y: y,
            width: width,
            height: height
        })
        var list = []
        for (var i = 0; i < infuModel.count; i++) {
            list.push(infuModel.get(i).path)
        }
        UTILS.saveInfuList(infuListPath, list)
    }

    ListModel {
        id: infuModel

        function addInfuList(list, isUrl) {
            for (var i in list) {
                var path = isUrl ? UTILS.urlToPath(list[i]) : list[i]
                if (UTILS.isFileExists(path)) {
                    var name = UTILS.urlToFileName(list[i]).replace(".infu", "")
                    for (var j = 0; j < infuModel.count; j++) {
                        if (infuModel.get(j).name === name) return
                    }
                    infuModel.append({ name: name, state: "", path: path })
                }
            }
        }
    }

    RowLayout {
        anchors.fill: parent
        spacing: 0

        TableView {
            id: infuTable
            Layout.fillWidth: true
            Layout.fillHeight: true
            frameVisible: false
            model: infuModel
            selectionMode: SelectionMode.ExtendedSelection

            TableViewColumn {
                title: qsTr("Name")
                role: "name"
            }

            TableViewColumn {
                title: qsTr("State")
                role: "state"
            }

            TableViewColumn {
                title: qsTr("Path")
                role: "path"
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
                        infuModel.addInfuList(selectFileDialog.fileUrls, true)
                    })
                }
            }

            Button {
                text: qsTr("Start")
                enabled: infuTable.currentRow !== -1
                onClicked: {
                    infuTable.selection.forEach( function(rowIndex) {
                        infuModel.setProperty(rowIndex, "state", qsTr("Online"))
                    })
                }
            }

            Button {
                text: qsTr("Stop")
                enabled: infuTable.currentRow !== -1
                onClicked: {
                    infuTable.selection.forEach( function(rowIndex) {
                        infuModel.setProperty(rowIndex, "state", "")
                    })
                }
            }

            Button {
                text: qsTr("Remove")
                enabled: infuTable.currentRow !== -1
                onClicked: {
                    var list = []
                    infuTable.selection.forEach( function(rowIndex) {
                        list.push(rowIndex)
                    })
                    // remove in reverse order
                    for (var i = list.length - 1; i >= 0; i--) {
                        infuModel.remove(list[i])
                    }
                    infuTable.selection.clear()
                }
            }

            Button {
                text: qsTr("Clear")
                enabled: infuTable.rowCount > 0
                onClicked: infuModel.clear()
            }
        }
    }
}
