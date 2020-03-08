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
            columns: 4
            rows: 2

            // first row
            Label {
                Layout.minimumWidth: grid.width * 3/8
                text: model.fullName
            }
            Label { Layout.maximumWidth: grid.width * 1/8; text: model.sector }
            Label { Layout.maximumWidth: grid.width * 1/4; text: model.seat }
            Label {
                Layout.maximumWidth: grid.width * 1/4
//                text: model.startTime
                text: Qt.formatDateTime(model.startTime, "hh:mm:ss")
            }

            // second row
            Label { Layout.columnSpan: 4; text: model.note }
        }
    }
}

//SwipeDelegate {
//    id: delegate
//    width: parent.width
//    checkable: true

//    property var startTime
//    property int elapsed: 0

//    Timer {
//        id: timer
//        interval: 1000; running: false; repeat: true;
//        onTriggered: elapsed++;
//    }


//    contentItem: GridLayout {
//        id: grid
////        anchors.fill: parent
////        anchors.leftMargin: 30
////        anchors.rightMargin: 30
//        columns: 4

//        Item {
//            id: nameItem
//            Layout.preferredWidth: grid.width / 10 * 3

//            Text {
//                anchors.right: parent.right
//                anchors.verticalCenter: parent.verticalCenter
//                font.pixelSize: 24
//                font.bold: true
//                color: "red"
//                horizontalAlignment: Text.AlignRight
//                text: model.fullName
//            }
//        }
//        Item {
//            id: seatItem
//            Layout.preferredWidth: grid.width / 10 * 2

//            Text {
//                anchors.centerIn: parent
//                font.pixelSize: 24
//                font.bold: true
//                color: "green"
//                text: model.seat
//            }
//        }
//        Item {
//            id: startTimeItem
//            Layout.preferredWidth: grid.width / 10 * 2

//            property date startTime

//            ColumnLayout {
//                anchors.verticalCenter: parent.verticalCenter
//                anchors.horizontalCenter: parent.horizontalCenter
//                spacing: 0

//                Text {
//                    verticalAlignment: Text.AlignBottom
//                    anchors.horizontalCenter: parent.horizontalCenter
//                    font.pixelSize: 12
//                    font.bold: false
//                    text: qsTr('Начало')
//                }
//                Text {
//                    verticalAlignment: Text.AlignTop
//                    anchors.horizontalCenter: parent.horizontalCenter
//                    font.pixelSize: 24
//                    font.bold: true
//                    text: {
//                        if (startTime === undefined)
//                            return '-- : --';

//                        var hours = startTime.getUTCHours();
//                        var mins = startTime.getUTCMinutes();
//                        return (hours < 10 ? "0" + hours : hours) +
//                                  " : " +
//                                  (mins < 10 ? "0" + mins : mins);
//                    }
//                }
//                Text {
//                    verticalAlignment: Text.AlignTop
//                    anchors.horizontalCenter: parent.horizontalCenter
//                    font.pixelSize: 12
//                    font.bold: false
//                    text: {
//                        if (startTime === undefined)
//                            return '--';

//                        var secs = startTime.getUTCSeconds();
//                        return secs < 10 ? "0" + secs : secs;
//                    }
//                }
//            }
//        }
//        Item {
//            id: launchButtonItem
//            Layout.preferredWidth: grid.width / 10 * 3
//            Layout.preferredHeight: launchButton.height

//            Rectangle {
//                id: launchButton
//                width: launchButtonItem.width / 10 * 8
//                height: width
//                radius: width / 2
//                anchors.centerIn: parent
//                color: "lightgreen"

//                ColumnLayout {
//                    anchors.centerIn: parent
//                    spacing: 0

//                    Text {
//                        Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom
//                        font.pixelSize: 14
//                        font.bold: false
//                        text: qsTr('Период')
//                    }
//                    Text {
//                        Layout.alignment: Qt.AlignHCenter
//                        font.pixelSize: 24
//                        font.bold: true
//                        text:  {
//                            var hours = Math.floor(elapsed / 60 / 60);
//                            var mins = Math.floor(elapsed / 60);
//                            var hoursText = qsTr("0" + hours);
//                            var minsText = mins < 10 ? "0" + mins : mins;
//                            return hoursText + " : " + minsText;
//                        }
//                    }
//                    Text {
//                        Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
//                        font.pixelSize: 14
//                        text: {
//                            var hours = Math.floor(elapsed / 60 / 60);
//                            var mins = Math.floor(elapsed / 60);
//                            var secs = elapsed - (hours * 60 * 60 + mins * 60);
//                            var secsText = secs < 10 ? "0" + secs : secs;
//                            return secsText;
//                        }
//                    }
//                }
//                MouseArea {
//                    anchors.fill: parent
//                    onClicked: {
//                        startTime = new Date;
//                        if (launchButton.color == "#90ee90") {
//                            watcherListView.model.set(index, model.fullName, model.sector, model.seat, new Date(), '');
//                            timer.start();
//                            launchButton.color = "yellow";
//                        } else if (launchButton.color == '#ffff00') {
//                            timer.stop();
//                            elapsed = 0;
//                            startTime = undefined;
//                            launchButton.color = 'lightgreen';
//                        }
//                    }
//                }
//            }
//        }
//    }


//    swipe.right: Label {
//        id: deleteLabel
//        height: parent.height
//        anchors.right: parent.right
//        verticalAlignment: Label.AlignVCenter
//        padding: 12
//        color: "white"
//        font.pixelSize: 12
//        clip: true
//        text: qsTr("Delete")

//        background: Rectangle {
//            color: deleteLabel.SwipeDelegate.pressed ? Qt.darker("tomato", 1.1) : "tomato"
//        }

//        SwipeDelegate.onClicked: {
//            console.log('DELETED')
////            watcherListView.model.remove(index)
//            delegate.swipe.close()
//        }
//    }
//}
