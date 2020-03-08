import QtQuick 2.9
import QtQuick.Controls 2.2
//import Process 1.0

Page {
    id: root

    property var pageModel
    property color delegateColor: "lightyellow"
    property color backgroundColor: "transparent"

    background: Rectangle {
        color: backgroundColor
    }

//    Process {
//        id: process
//    }

    GridView {
        id: gridView

        anchors.fill: parent
        anchors.margins: 30
        cellWidth: 170
        cellHeight: 170
        model: pageModel

        delegate: Item {
            id: wrapper
            width: 150
            height: 150

            Rectangle {
                anchors.fill: parent
                anchors.margins: 10
                color: delegateColor
                opacity: 1.0

                Label {
                    anchors.centerIn: parent
                    width: parent.width
                    horizontalAlignment: Text.AlignHCenter
                    font.bold: true
                    font.pixelSize: 14
                    wrapMode: Text.WordWrap
                    text: model.title
                }

            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if (model.processRun) {
//                        var processPath = model.process;
                        process.start("/usr/local/bin/EmplSheduleMonth.app/Contents/MacOS/EmplSheduleMonth");
//                        starter.run("/usr/local/bin/EmplSheduleMonth.app/Contents/MacOS/EmplSheduleMonth");
//                        process.start("OK");
                    }
                    if (model.path) {
                        var component = Qt.createComponent(model.path);
                        var object = component.createObject(parent);
                        object.show();
                    } else {
                        root.StackView.view.push(model.page)
                    }
                }
            }
        } // delegate
    }

    // Back Button
    Rectangle {
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.leftMargin: 10
        anchors.bottomMargin: 10
        width: 150
        height: 100
        color: "lightgreen"
        visible: (root.StackView.view.depth > 1) ? true : false // Show if not main page

        Text {
            anchors.centerIn: parent
            font.bold: true
            font.pixelSize: 14
            wrapMode: Text.WordWrap
            text: qsTr("Назад")
        }
        MouseArea {
            anchors.fill: parent
            onClicked: root.StackView.view.pop()
        }
    }
}
