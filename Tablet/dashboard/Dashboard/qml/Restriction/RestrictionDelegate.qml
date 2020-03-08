import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

ItemDelegate {
    width: parent.width
    height: grid.height + 20

    Rectangle {
        id: context
        anchors.fill: parent
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        color: Qt.darker(palette.window, 1.05)

        GridLayout {
            id: grid
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 10
            columns: 2

            ColumnLayout {
                Layout.minimumWidth: grid.width * 2/3
                Label { text: model.ad + ' ' + model.indxMil }
                Label { text: model.callSign }
                Label { text: model.note }
            }
            ColumnLayout {
                Layout.maximumWidth: grid.width * 1/3
                Label { text: model.zone }
                Label { text: model.levelFrom + ' ' + model.levelTo }
                Label { text: model.timeFrom + ' ' + model.timeTo }
            }
        }
    }
}

//ColumnLayout {
//    width: parent.width
//    spacing: 10

//    function showLevel(levelFrom, levelTo) {
//        var outputStr;
//        if (levelFrom) {
//            if (levelFrom === "GND")
//                outputStr = levelFrom;
//            else
//                outputStr = qsTr("От FL") + levelFrom;
//        }
//        if (levelTo) {
//            if (levelTo === "UNL")
//                outputStr += " " + levelTo;
//            else
//                outputStr += qsTr(" до FL") + levelTo;
//        }
//        return outputStr;
//    }

//    function showTime(timeFrom, timeTo) {
//        var outputStr;
//        if (timeFrom)
//            outputStr = qsTr("С ") + timeFrom + " ";
//        if (timeTo)
//            outputStr += qsTr("до ") + timeTo + qsTr(" UTC");
//        return outputStr;
//    }

//    Rectangle {
//        height: 1
//        anchors.left: parent.left
//        anchors.right: parent.right
//        anchors.leftMargin: 10
//        anchors.rightMargin: 10
//        color: "lightgray"
//    }

//    // Context
//    RowLayout {
//        anchors.left: parent.left
//        anchors.right: parent.right
//        anchors.leftMargin: 10
//        anchors.rightMargin: 10

//        // Label
//        ColumnLayout {
//            Layout.alignment: Qt.AlignTop

//            Text {
//                font.pixelSize: 30
//                font.bold: true
//                color: "tomato"
//                text: model.label
//            }
//            Text {
//                font.pixelSize: 12
//                color: "lightgray"
//                text: model.note
//            }
//        }

//        // Details
//        ColumnLayout {
//            anchors.right: parent.right

//            Text {
//                width: parent.width
//                anchors.horizontalCenter: parent.horizontalCenter
//                font.pixelSize: 20
//                font.bold: true
//                color: "white"
//                visible: model.zone
//                text: model.zone
//            }
//            Text {
//                anchors.horizontalCenter: parent.horizontalCenter
//                font.pixelSize: 16
//                font.bold: true
//                color: "lightgray"
//                visible: showLevel(model.levelFrom, model.levelTo);
//                text: showLevel(model.levelFrom, model.levelTo);
//            }
//            Text {
//                font.pixelSize: 14
//                font.bold: true
//                color: "lightgray"
//                visible: showTime(model.timeFrom, model.timeTo);
//                text: showTime(model.timeFrom, model.timeTo);
//            }
//        }
//    }
//}

//Item {
//    id: restrictionDelegate
//    width: parent.width
//    height: 50

//    ColumnLayout {
//        width: parent.width

//    // Spacing line
//    Rectangle {
//        width: parent.width
//        height: 1
////        anchors.leftMargin: 10
//        color: "lightgray"
//    }
//    }


////    ColumnLayout {
////        id: column
////        Layout.implicitWidth: parent.width * 2 /3
//////        width: parent.width * 2 / 3


////        GridLayout {
////            width: parent.width

////            // Label block
////            ColumnLayout {
////                id: labelBlock
////                width: parent.width * 2 / 3

////                Text {
////                    font.pixelSize: 20
////                    font.bold: true
////                    color: "red"
////                    text: model.label
////                }
////            }

////            // Zone block
////            ColumnLayout {
////                id: zoneBlock
////                anchors.right: parent.right
////                Layout.alignment: Qt.AlignRight

////                Text {
////                    font.pixelSize: 16
////                    font.bold: true
////                    color: "white"
////                    text: model.zone
////                }
////            }


////        }


////        // Note block
////        Text {
////            font.pixelSize: 12
////            color: "white"
////            text: model.note
////            visible: text ? true : false
////        }

//////        RowLayout {
//////            Text {
//////                font.pixelSize: 24
//////                font.bold: true
//////                color: "red"
//////                text: model.label
//////            }

//////            Text {
//////                font.pixelSize: 32
//////                color: "black"
//////                text: model.level
//////                visible: text ? true : false
//////            }
//////            Text {
//////                font.pixelSize: 24
//////                color: "blue"
//////                text: model.time
//////                visible: text ? true : false
//////            }
//////        }
////    }

////    swipe.right: Label {
////        id: deleteLabel
////        height: parent.height
////        anchors.right: parent.right
////        verticalAlignment: Label.AlignVCenter
////        padding: 12
////        color: "white"
////        font.pixelSize: 12
////        clip: true
////        text: qsTr("Delete")

////        background: Rectangle {
////            color: deleteLabel.SwipeDelegate.pressed ? Qt.darker("tomato", 1.1) : "tomato"
////        }

////        SwipeDelegate.onClicked: {
////            console.log('OKOKOKO')
////            restrictionListView.model.remove(index)
////        }
////    }

////    onClicked: restrictionListView.model.remove(index)
//}
