import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

RoundButton {
    id: button

    enum Orientation {
        Previous,
        Next
    }
    property int orientation: DirectionButton.Orientation.Previous
    property color color: "transparent"

    width: datePicker.directionButtonWidth
    height: datePicker.directionButtonHeight

    flat: true
    font: directionButtonFont

    contentItem: Text {
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.bold: true
        font.pixelSize: 24
        text: {
            if (orientation === DirectionButton.Orientation.Previous)
                return '<';
            else if (orientation === DirectionButton.Orientation.Next)
                return '>';
        }
    }

    background: Rectangle {
        implicitWidth: button.width
        implicitHeight: button.height
        color: button.color
        radius: 0
    }
}
