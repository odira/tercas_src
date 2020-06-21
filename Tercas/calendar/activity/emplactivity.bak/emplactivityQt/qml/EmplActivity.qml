import QtQuick 2.9

Item {
    id: emplActivity
    width: 35; height: 35

    property string itemabbr: abbr
    property color color: "yellow"

    Rectangle {
        anchors.fill: parent
        anchors.margins: 2
        radius: 2
        color: emplActivity.color

        Text {
            anchors.centerIn: parent
            text: itemabbr
        }
    }
}
