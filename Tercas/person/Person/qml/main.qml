import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.5

Window {
    visible: true
    width: 1024
    height: 800
    title: qsTr("Person Database")

    TableView {
        anchors.fill: parent
        anchors.margins: 10
        columnSpacing: 2
        rowSpacing: 2
        model: personModel

        delegate: Rectangle {
            implicitWidth: 100
            implicitHeight: 50

            Text {
                anchors.centerIn: parent
                text: display
            }
        }
    }
}
