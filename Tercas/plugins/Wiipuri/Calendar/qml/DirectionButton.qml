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
    property var buttonColor: "gray"

    Layout.fillHeight: true
    flat: true
    font.bold: true

    contentItem: Text {
        color: buttonColor
        text: {
            if (orientation === DirectionButton.Orientation.Previous)
                return '<';
            else if (orientation === DirectionButton.Orientation.Next)
                return '>';
        }
    }

    background: Rectangle {
        color: "transparent"
        border.color: buttonColor
        height: width
        radius: (width > height) ? width / 10 : height / 10
    }
}
