import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

Window {
    visible: true
    width: 1024
    height: 800
    title: qsTr("Person Database")


    ListView {
        anchors.fill: parent
        model: personModel
        delegate: Rectangle {
            width: 200
            height: 50
            Text {

                text: surname
            }
        }
    }

//    Column {
//        anchors.fill: parent

//        TableView {
//            anchors.left: parent.left
//            anchors.right: parent.right
//            anchors.top: parent.top
//            anchors.bottom: bottonBox.top
//            anchors.margins: 10
//            columnSpacing: 2
//            rowSpacing: 2
//            model: personModel

//            columnWidthProvider: function (column) {
//                if (column === 0 || column === 1)
//                    return 0;
//                else
//                    return 100;
//            }

//            delegate: Rectangle {
//                implicitWidth: 100
//                implicitHeight: 50
//                border.color: "black"

//                Text {
//                    anchors.centerIn: parent
//                    text: display
//                }
//            }
//        }

//        Rectangle {
//            id: bottonBox
//            height: 100
//            anchors.left: parent.left
//            anchors.right: parent.right
//            anchors.bottom: parent.bottom
//            anchors.margins: 10

//            RoundButton {
//                radius: 0
//                text: qsTr("Quit")
//            }
//        }
//    }
}
