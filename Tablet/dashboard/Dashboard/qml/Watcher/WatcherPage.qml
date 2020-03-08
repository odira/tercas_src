import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import WatcherModel 1.0

Page {
    id: watcherPage

    property int currentWatcher: -1

    WatcherDialog {
        id: watcherDialog

        onFinished: {
            if (currentWatcher === -1)
                watcherListView.model.append(fullName, sector, seat, new Date(), "")
            else
                watcherListView.model.set(currentWatcher, fullName, sector, seat, new Date(), "")
        }
    }

//    header: Item {
//        id: header
//        width: parent.width
//        height: headerLayout.height

//        RowLayout {
//            id: headerLayout
//            anchors.horizontalCenter: parent.horizontalCenter
//            spacing: 10

//            Text {
//                font.pixelSize: 20
//                font.bold: true
//                color: "red"
//                text: qsTr("Рабочее время на секторе")
//            }
//            Text {
//                font.pixelSize: 24
//                font.bold: true
//                color: "blue"
//                text: qsTr(sector)
//            }
//        }
//    }

    contentItem: ListView {
        id: watcherListView
        focus: true
        boundsBehavior: Flickable.StopAtBounds
        clip: true
        spacing: 10
        model: WatcherModel { }
        delegate: WatcherDelegate {
            width: parent.width

            MouseArea {
                anchors.fill: parent
                onPressAndHold: {
                    currentRestriction = index;
                    delegateMenu.open();
                }
            }
        }
    }



//    contentItem: ListView {
//        id: watcherListView

//        signal pressAndHold(int index)

//        snapMode: ListView.SnapOneItem
//        clip: true
//        focus: true
//        boundsBehavior: Flickable.StopAtBounds
//        model: WatcherModel {
//            id: watcherModel
//        }

//        delegate: WatcherDelegate {
//            id: delegate
////            startTime: watcherModel.get(index).startTime

//            Connections {
//                target: delegate
//                onPressAndHold: watcherListView.pressAndHold(index)
//            }
//        }

//        onPressAndHold: {
//            currentWatcher = index;
//            watcherMenu.open();
//        }
//    }

    Menu {
        id: watcherMenu
        x: parent.width / 2 - width / 2
        y: parent.height / 2 - height / 2
        modal: true
        font.pixelSize: 20
        font.bold: true

        Label {
            padding: 10
            font.bold: true
            color: "red"
            width: parent.width
            horizontalAlignment: Qt.AlignHCenter
            text: currentWatcher >= 0 ? watcherListView.model.get(currentWatcher).fullName : ""
        }
        MenuItem {
            text: qsTr("Edit...")
            onTriggered: watcherDialog.edit(watcherListView.model.get(currentWatcher));
        }
        MenuItem {
            text: qsTr("Remove")
            onTriggered: watcherListView.model.remove(currentWatcher);
        }
    }

//    AddingButton {
//        onClicked: {
//            currentWatcher = -1;
//            watcherDialog.createWatcher();
//        }
//    }
}
