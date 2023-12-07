import QtQuick 2.5
import "components"

MessageDialogBase {
    title: qsTr(String("About %1").arg(Qt.application.name))
    text: String("<h3>%1 %2</h3>
          Based on Qt %3<br>
          Build on %4<br><br>
          Copyright © 2015-2023, Vladimir Zarypov").arg(Qt.application.name).arg(Qt.application.version).arg(APP.qtVersion).arg(APP.buildDate)
}
