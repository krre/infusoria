import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

ApplicationWindow {
    id: mainRoot
    title: "Infusoria Manager"
    width: 800
    height: 600
    visible: true
    menuBar: MenuBar {
        Menu {
            title: qsTr("Help")

            MenuItem {
                text: qsTr("About Infusoria Manager")
                onTriggered: aboutDialog.open()
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

    MessageDialog {
        id: aboutDialog
        title: qsTr("About Infusoria Manager")
        standardButtons: StandardButton.Ok
        text: String("<h3>%1 %2</h3>
              Based on Qt %3<br>
              Build date %4<br><br>
              Copyright (c) 2015, Vladimir Zarypov").arg(APP.name).arg(APP.version).arg(APP.qtVersion).arg(APP.buildDate)
    }
}
