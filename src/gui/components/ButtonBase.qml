import QtQuick
import QtQuick.Controls

Button {
    objectName: "ButtonBase"
    // activeFocusOnPress: true
    // isDefault: activeFocus

    Action {
        shortcut: "Return"
        enabled: isDefault
        onTriggered: clicked()
    }
}
