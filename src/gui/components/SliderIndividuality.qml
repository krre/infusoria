import QtQuick
import QtQuick.Controls

Slider {
    // tickmarksEnabled: true
    // maximumValue: 1
    // minimumValue: -1
    value: Math.random() * (maximumValue - minimumValue) + minimumValue
}
