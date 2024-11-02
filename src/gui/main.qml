import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import QtQuick.Dialogs
import Qt.labs.platform as QtLabs
import Qt.labs.qmlmodels
import "utils.js" as Utils
import "dialog.js" as Dialog

ApplicationWindow {
    property string infuListPath: APP.applicationDirPath + "/infu.txt"
    property alias infuModel: infuModel
    id: mainRoot
    title: Qt.application.name
    width: 800
    height: 600
    visible: true
    menuBar: MenuBar {
        Menu {
            title: qsTr("Infusoria")

            MenuItem {
                text: qsTr("New...")
                // shortcut: "Ctrl+N"
                onTriggered: Utils.createDynamicObject(mainRoot, "qrc:/gui/NewInfusoria.qml")
            }

            MenuSeparator {}

            MenuItem {
                text: qsTr("Exit")
                // shortcut: "Ctrl+Q"
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
                text: qsTr(String("About %1...").arg(Qt.application.name))
                onTriggered: Utils.createDynamicObject(mainRoot, "qrc:/gui/About.qml")
            }
        }
    }

    Component.onCompleted: {
        var geometry = Settings.map("MainWindow")
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

        var infuList = FileOperations.loadList(infuListPath)
        if (infuList) {
            infuModel.addInfuList(infuList)
        }
    }

    onClosing: {
        Settings.setMap("MainWindow", {
            x: x,
            y: y,
            width: width,
            height: height
        })
        var list = []
        for (var i = 0; i < infuModel.count; i++) {
            list.push(infuModel.get(i).path)
        }
        FileOperations.saveList(infuListPath, list)
    }

    TableModel {
        id: infuModel

        TableModelColumn { display:  "name" }
        TableModelColumn { display:  "state" }
        TableModelColumn { display:  "path" }

        function addInfuList(list, isUrl) {
            for (var i in list) {
                var path = isUrl ? UTILS.urlToPath(list[i]) : list[i]
                if (UTILS.isFileExists(path)) {
                    var name = Init.name(path)
                    var isAdded = false
                    for (var j = 0; j < infuModel.count; j++) {
                        if (infuModel.get(j).name === name) {
                            isAdded = true
                            break
                        }
                    }
                    if (!isAdded) {
                        var uuid = Init.uuid(path)
                        infuModel.append({ name: name, state: "", path: path, uuid: uuid })
                    }
                }
            }
        }
    }

    RowLayout {
        anchors.fill: parent
        spacing: 7

        TableView {
            id: infuTable
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: infuModel
            selectionMode: TableView.ExtendedSelection

            // onDoubleClicked: openEditor()

            function openEditor() {
                Utils.createDynamicObject(mainRoot, "qrc:/gui/Editor.qml", {
                    name: infuModel.get(currentRow).name,
                    path: infuModel.get(currentRow).path,
                    row: currentRow
                })
            }

            // TableViewColumn {
            //     title: qsTr("Name")
            //     role: "name"
            // }

            // TableViewColumn {
            //     title: qsTr("State")
            //     role: "state"
            // }

            // TableViewColumn {
            //     title: qsTr("Path")
            //     role: "path"
            // }
        }

        ColumnLayout {
            property bool inverse: false // for force updating start and stop buttons
            id: buttons
            Layout.alignment: Qt.AlignTop
            Layout.rightMargin: 7
            Layout.topMargin: 7

            Button {
                text: qsTr("Add")
                onClicked: {
                    var selectFileDialog = Dialog.selectFile(mainRoot, {
                        selectMultiple: true, folder: UTILS.pathToUrl(Settings.value("Path", "workspace")),
                        nameFilters: [ qsTr("Infusoria files (*.infu)"), qsTr("All files (*)") ]})
                    selectFileDialog.accepted.connect(function() {
                        infuModel.addInfuList(selectFileDialog.fileUrls, true)
                    })
                }
            }

            Button {
                text: qsTr("Start")
                enabled: { buttons.inverse; return infuTable.currentRow !== -1 && infuModel.get(infuTable.currentRow).state === "" }
                onClicked: {
                    infuTable.selection.forEach( function(rowIndex) {
                        infuModel.setProperty(rowIndex, "state", qsTr("Online"))
                        InfuController.startInfusoria(infuModel.get(rowIndex).path)
                        buttons.inverse = !buttons.inverse
                    })
                }
            }

            Button {
                text: qsTr("Stop")
                enabled: { buttons.inverse; return infuTable.currentRow !== -1 && infuModel.get(infuTable.currentRow).state === qsTr("Online") }
                onClicked: {
                    infuTable.selection.forEach( function(rowIndex) {
                        infuModel.setProperty(rowIndex, "state", "")
                        InfuController.stopInfusoria(infuModel.get(rowIndex).uuid)
                        buttons.inverse = !buttons.inverse
                    })
                }
            }

            Button {
                text: qsTr("Edit")
                enabled: infuTable.currentRow !== -1
                onClicked: infuTable.openEditor()
            }

            Button {
                text: qsTr("Remove")
                enabled: infuTable.currentRow !== -1 && infuModel.get(infuTable.currentRow).state === ""
                onClicked: {
                    var dialog = Dialog.question(qsTr("Are you sure?"))
                    dialog.yes.connect(function() {
                        var list = []
                        infuTable.selection.forEach( function(rowIndex) {
                            list.push(rowIndex)
                        })
                        // remove in reverse order
                        for (var i = list.length - 1; i >= 0; i--) {
                            infuModel.remove(list[i])
                        }
                        infuTable.selection.clear()
                    })
                }
            }

            Button {
                text: qsTr("Clear")
                enabled: infuTable.rowCount > 0
                onClicked: {
                    var dialog = Dialog.question(qsTr("Are you sure?"))
                    dialog.yes.connect(function() {
                        for (var i = infuModel.count - 1; i >= 0; i--) {
                            if (!infuModel.get(i).state) {
                                infuModel.remove(i)
                            }
                        }
                    })
                }
            }
        }
    }
}
