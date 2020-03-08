import QtQuick 2.6

ListView {
    id: listView

    clip: true
    keyNavigationWraps: true
    snapMode: ListView.SnapToItem
    focus: true
    boundsBehavior: Flickable.StopAtBounds
    model: safetyModel
    currentIndex: -1 // Don't pre-select any item
    delegate: listViewDelegate
    highlightMoveDuration: 250
    highlightMoveVelocity: 3000
    highlightFollowsCurrentItem: true

    highlight: Rectangle {
        width: listView.width
        height: listViewDelegate.height
        color: "orange"
        opacity: 0.2
        z: 1

        Rectangle {
            width: 50
            height: listViewDelegate.height
            x: parent.x
            y: parent.y
            color: "red"
            z: 2
        }
    }

    Component {
        id: listViewDelegate

        Item {
            width: listView.width
            height: date.height + 20

            Rectangle {
                anchors.fill: parent
                anchors.margins: 10
//                border.width: 2
//                border.color: "gray"

                Date {
                    id: date

                    date: model.datetime
                }

                Column {
                    id: contentColumn

                    anchors.left: date.right; anchors.leftMargin: 10
                    anchors.right: parent.right; anchors.rightMargin: 10
                    anchors.verticalCenter: parent.verticalCenter
                    spacing: 3

                    Text {
                        color: "red"
                        font.pointSize: 12
                        verticalAlignment: Text.AlignVCenter
                        text: model.classification
                    }
                    Text {
                        width: contentColumn.width
                        color: "blue"
                        font.pointSize: 11
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.WordWrap
                        text: model.type
                    }
                    Row {
                        spacing: 20

                        Text {
                            color: "#000000"
                            font.pointSize: 10
                            verticalAlignment: Text.AlignVCenter
                            text: model.acc
                        }
                    }
                }
                MouseArea {
                    anchors.fill: parent;
                    onClicked: {
                        if (listView.currentIndex !== index)
                            listView.currentIndex = index;
//                        root.currentIndex = 1;
                    }
                }
                Keys.onPressed: {
                    if (event.key === Qt.Key_Down) {
                        listView.currentIndex++;
                        event.accepted = true;
                    } else if (event.key === Qt.Key_Up) {
                        listView.currentIndex--;
                        event.accepted = true;
                    } /*else if (event.key === Qt.Key_Return) {
                        root.currentIndex = 1;
                    }*/
                }
            }
            Rectangle {
                id: endingLine

                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                height: 1
                width: parent.width
                color: "#d7d7d7"
            }
        }
    }

    Component.onCompleted: listView.currentIndex = 0
}
