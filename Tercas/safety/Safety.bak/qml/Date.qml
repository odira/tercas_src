import QtQuick 2.7

Rectangle {
    property date date: new Date()

    width: 80
    height: width
    radius: width /5
    border { width: 2; color: "gray" }
    antialiasing: true

    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: monthText.top
        font.pixelSize: 14
        text: Qt.formatDate(date, "yyyy")
    }
    Text {
        id: monthText

        anchors.centerIn: parent
        font.pointSize: 11
        color: "red"
        text: Qt.formatDate(date, "MMMM")
    }
    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: monthText.bottom
        font.pixelSize: 20
        color: "gray"
        text: Qt.formatDate(date, "dd")
    }
}
