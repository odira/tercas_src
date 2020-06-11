import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12
import QtQml.Models 2.12

ApplicationWindow {
    id: root
    visible: true
    width: Screen.width * 2/3
    height: Screen.height * 2/3
    title: qsTr("Период активности")

    TableView {
        anchors.fill: parent
        anchors.margins: 10
        model: periodModel
        delegate: Rectangle {
            implicitWidth: 100
            implicitHeight: 30
            Text {
                anchors.centerIn: parent
                text: display
            }
        }
    }
}
