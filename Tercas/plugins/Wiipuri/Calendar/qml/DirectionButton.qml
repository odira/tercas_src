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

    Layout.fillHeight: true
    flat: true
    font.bold: true
    text: {
        if (orientation === DirectionButton.Orientation.Previous)
            return '<';
        else if (orientation === DirectionButton.Orientation.Next)
            return '>';
    }

    background: Rectangle {
        color: "transparent"
        border.color: "black"
        radius: (width > height) ? width / 5 : height / 5
    }
}
