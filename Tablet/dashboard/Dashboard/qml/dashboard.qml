import QtQuick 2.9
import QtQuick.Controls 2.2
import "./Restriction"
import "./Watcher"

ApplicationWindow {
    id: window
    title: qsTr("ATC Dashboard")
    width: 480
    height: 640
    visible: true

    property string sectorLabel: 'П1'

    header: Item {
        id: header
        height: sectorButton.height + 20

        Button {
            id: sectorButton
            anchors.centerIn: parent
            width: sectorText.implicitWidth + 40

            contentItem: Text {
                id: sectorText
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 18
                font.bold: true
                color: "white"
                text: sectorLabel
            }

            background: Rectangle {
                radius: 10
                color: "green"
            }

            onClicked: sectorMenu.open();
        }
    }

    // Content Item
    SwipeView {
        id: mainView
        anchors.fill: parent

        contentData: [
            RestrictionPage { },
            WatcherPage { }
        ]
    }

    footer: Item {
        id: pageIndicator
        height: 20

        // Page Indicator
        PageIndicator {
            anchors.horizontalCenter: parent.horizontalCenter
            count: mainView.count
            currentIndex: mainView.currentIndex
        }
    }

    Menu {
        id: sectorMenu
        parent: sectorButton
        x: (parent.width - width) / 2
        y: parent.y + parent.height
        modal: true
        font.pixelSize: 18

        Label {
            padding: 10
            color: "green"
            width: parent.width
            horizontalAlignment: Qt.AlignHCenter
            text: qsTr("Выберите сектор")
        }
        MenuItem {
            text: qsTr("П1")
            onTriggered: sectorLabel = text;
        }
        MenuItem {
            text: qsTr("В1П2")
            onTriggered: sectorLabel = text;
        }
        MenuItem {
            text: qsTr("В1П1П2")
            onTriggered: sectorLabel = text;
        }
    }
}
