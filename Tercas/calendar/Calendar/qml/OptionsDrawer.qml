import QtQuick 2.5
import QtQuick.Controls 2.0

Drawer {
    id: drawer

    property int shift

    edge: Qt.RightEdge
    dragMargin: 5

    GridView {
        id: grid

        width: parent.width - 40
        height: width * 2/3
        anchors.horizontalCenter: parent.horizontalCenter
        y: 20

        cellWidth: grid.width / 3
        cellHeight: grid.height / 2
        delegate: Rectangle {
            width: grid.cellWidth - 10
            height: grid.cellHeight - 10
            color: (index == root.shift - 1) ? "yellow" : "lightblue"

            Label {
                anchors.centerIn: parent
                text: model.index + 1
                font.pointSize: 12
                font.bold: true
            }
            MouseArea {
                anchors.fill: parent
                onClicked: drawer.shift = model.index + 1
            }
        }
        model: 6
    }
}
