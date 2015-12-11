import QtQuick 2.5
import QtQuick.Dialogs 1.2

MessageDialog {
    title: qsTr(String("About %1").arg(APP.name))
    standardButtons: StandardButton.Ok
    text: String("<h3>%1 %2</h3>
          Based on Qt %3<br>
          Build on %4<br><br>
          Copyright (c) 2015, Vladimir Zarypov").arg(APP.name).arg(APP.version).arg(APP.qtVersion).arg(APP.buildDate)
    onVisibleChanged: if (!visible) destroy()
    Component.onCompleted: open()
}
