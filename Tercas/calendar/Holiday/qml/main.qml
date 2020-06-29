import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import QtQml.Models 2.12

ApplicationWindow {
    id: root
    visible: true
    width: Screen.width * 3/4
    height: Screen.height * 3/4
    title: qsTr("Holiday Database")

    DelegateModel {
        id: visualModel
        delegate: Delegate {}
        model: holidayModel
    }

    function showList() {
        listView.currentIndex = singleView.currentIndex
        view.state = 'inList';
    }
    function showSingle() {
        singleView.currentIndex = listView.currentIndex
        view.state = 'inSingle'
    }
    function addItem() {
        console.log('Add')
    }

    header: Rectangle {
        id: header
        width: root.width
        height: 70
        border.color: 'pink'

        RowLayout {
            anchors.fill: parent
            anchors.margins: 5

            RoundButton {
                id: listButton
                Layout.fillHeight: true
                Layout.preferredWidth: height
                radius: 0

                onClicked: view.state = 'inList'

                background: Rectangle {
                    color: 'white'
                    border.color: 'pink'
                }

                Image {
                    fillMode: Image.PreserveAspectFit
                    anchors.centerIn: parent
                    sourceSize.width: listButton.width
                    sourceSize.height: listButton.height
                    source: "qrc:images/arrow.jpg"
                }
            }
            // spacing
            Item {
                Layout.fillWidth: true
            }
            RoundButton {
                id: quitButton
                Layout.fillHeight: true
                Layout.preferredWidth: height
                radius: 0

                onClicked: Qt.quit()

                background: Rectangle {
                    color: 'white'
                    border.color: 'pink'
                }

                Image {
                    fillMode: Image.PreserveAspectFit
                    anchors.centerIn: parent
                    sourceSize.width: quitButton.width
                    sourceSize.height: quitButton.height
                    source: "qrc:images/quit.png"
                }
            }

        }
    }

    // CONTENT ITEM
    contentData: Item {
        id: view
        anchors.fill: parent

        ColumnLayout {
            id: list
            anchors.fill: parent
            anchors.margins: 5

            ListHeader {
                id: listHeader
                Layout.fillWidth: true
                Layout.preferredHeight: 60
            }
            ScrollView {
                id: scrollList
                Layout.fillWidth: true
                Layout.fillHeight: true
                ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
                ScrollBar.vertical.policy: ScrollBar.AlwaysOn
                focus: true

                ListView {
                    id: listView
                    anchors.fill: parent
                    model: visualModel.parts.list
                    snapMode: ListView.SnapOneItem
                    clip: true
                    spacing: 5
                    boundsBehavior: ListView.StopAtBounds

                    highlight: Rectangle { color: 'yellow' }
                    highlightFollowsCurrentItem: true
                    highlightMoveDuration: 0
                }

            }
            ListFooter {
                id: listFooter
                Layout.fillWidth: true
                Layout.preferredHeight: 60
            }
        }

        ScrollView {
            id: single
            anchors.fill: parent
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

            ListView {
                id: singleView
                anchors.fill: parent
                model: visualModel.parts.single
                snapMode: ListView.SnapOneItem
                orientation: ListView.Horizontal
                visible: true
                clip: true
                highlightMoveDuration: 0
            }
        }

        state: 'inList'
        states: [
            State {
                name: 'inList'
                PropertyChanges { target: list; visible: true }
                PropertyChanges { target: scrollList; focus: true }
                PropertyChanges { target: listView; focus: true }
                PropertyChanges { target: single; visible: false }
                PropertyChanges { target: singleView; focus: false }
                PropertyChanges { target: listButton; enabled: false; opacity: 0.1 }
            },
            State {
                name: 'inSingle'
                PropertyChanges { target: list; visible: false; focus: false }
                PropertyChanges { target: listView; focus: false }
                PropertyChanges { target: single; visible: true }
                PropertyChanges { target: singleView; focus: true }
                PropertyChanges { target: listButton; enabled: true; opacity: 0.9 }
            }
        ]
    }
}
