import QtQuick 2.9
import QtQuick.Controls 2.3

RoundButton {
    id: roundButton
    padding: 69 / 2

    contentItem: Grid {
        width: 69
        height: 69
        columns: 3
        spacing: 0

        Rectangle { color: "transparent"; width: 23; height: 23 }
        Rectangle { color: "yellow"; width: 23; height: 23 }
        Rectangle { color: "transparent"; width: 23; height: 23 }

        Rectangle { color: "yellow"; width: 23; height: 23 }
        Rectangle { color: "yellow"; width: 23; height: 23 }
        Rectangle { color: "yellow"; width: 23; height: 23 }

        Rectangle { color: "transparent"; width: 23; height: 23 }
        Rectangle { color: "yellow"; width: 23; height: 23 }
        Rectangle { color: "transparent"; width: 23; height: 23 }
    }

    background: Rectangle {
        implicitWidth: 69 * 2
        implicitHeight: implicitWidth
        radius: implicitWidth / 2
        color: "red"
    }
}
