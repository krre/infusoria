import QtQuick 2.5
import QtQuick.Controls 1.4

Slider {
    tickmarksEnabled: true
    maximumValue: 1
    minimumValue: -1
    value: Math.random() * (maximumValue - minimumValue) + minimumValue
}
