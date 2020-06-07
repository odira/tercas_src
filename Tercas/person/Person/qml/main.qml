import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import QtQml.Models 2.12

Window {
    id: root
    visible: true
    width: 1024
    height: 800
    title: qsTr("Person Database")

    DelegateModel {
        id: visualModel
        delegate: Delegate {}
        model: personModel
    }

    ListView {
        id: listView
        anchors.fill: parent
        model: visualModel.parts.list
        snapMode: ListView.SnapOneItem
        visible: false
    }

    ListView {
        id: singleView
        anchors.fill: parent
        model: visualModel.parts.single
        snapMode: ListView.SnapOneItem
        orientation: ListView.Horizontal
        visible: true
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
