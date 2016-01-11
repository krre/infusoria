import QtQuick 2.5
import QtQuick.Dialogs 1.2

MessageDialog {
    title: qsTr(String("About %1").arg(Qt.application.name))
    standardButtons: StandardButton.Ok
    text: String("<h3>%1 %2</h3>
          Based on Qt %3<br>
          Build on %4<br><br>
          Copyright © 2015-216, Vladimir Zarypov").arg(Qt.application.name).arg(APP.version).arg(APP.qtVersion).arg(APP.buildDate)
    onVisibleChanged: if (!visible) destroy()
    Component.onCompleted: open()
}
