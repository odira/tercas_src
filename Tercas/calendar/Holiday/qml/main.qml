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

    }
    function deleteItem() {

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

    footer: Rectangle {
        id: footer
        width: root.width
        height: 70
        border.color: 'pink'

        RowLayout {
//            anchors.fill: parent
            anchors.centerIn: parent
            height: parent.height - 10
            anchors.margins: 5

            RoundButton {
                id: addButton
                Layout.fillHeight: true
                Layout.preferredWidth: 150
                radius: 0
                text: qsTr('Add Item')

                onClicked: addItem()

                background: Rectangle {
                    color: 'orange'
                    border.color: 'pink'
                }
            }
            RoundButton {
                id: deleteButton
                Layout.fillHeight: true
                Layout.preferredWidth: 150
                radius: 0
                text: qsTr('Delete Item')

                onClicked: deleteItem()

                background: Rectangle {
                    color: 'orange'
                    border.color: 'pink'
                }
            }

        }
    }

    // CONTENT ITEM
    contentData:  Item {
        id: view
        anchors.fill: parent
        anchors.margins: 5

        ScrollView {
            id: scrollList
            anchors.fill: parent
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
            ScrollBar.vertical.policy: ScrollBar.AlwaysOn

            ListView {
                id: listView
                anchors.fill: parent
                model: visualModel.parts.list
                snapMode: ListView.SnapToItem
                visible: true
                clip: true
                spacing: 5

                headerPositioning: ListView.OverlayHeader
                header: Item {
                    width: view.width
                    height: 60
                    z: 2

                    ColumnLayout {
                        anchors.fill: parent
                        spacing: 0

                        RowLayout {
                            Layout.fillWidth: true
                            Layout.fillHeight: true

                            TextField {
                                Layout.preferredWidth: 50
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                text: qsTr('Дата')
                                font.bold: true
                                horizontalAlignment: TextField.AlignHCenter
                                background: Rectangle {
                                    color: 'lightblue'
                                    border.color: 'pink'
                                }
                            }
                            TextField {
                                Layout.preferredWidth: 150
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                text: qsTr('Календарный день')
                                horizontalAlignment: TextField.AlignHCenter
                                background: Rectangle {
                                    color: 'lightblue'
                                    border.color: 'pink'
                                }
                            }
                            TextField {
                                Layout.preferredWidth: 200
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                text: qsTr('Примечание')
                                horizontalAlignment: TextField.AlignHCenter
                                background: Rectangle {
                                    color: 'lightblue'
                                    border.color: 'pink'
                                }
                            }
                        }

                        Rectangle {
                            id: spacing2
                            Layout.fillWidth: true
                            height: 10
                        }
                    }
                }
            }
        }

        ScrollView {
            id: scrollSingle
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

        state: 'inSingle'
        states: [
            State {
                name: 'inList'
                PropertyChanges { target: listView; visible: true; focus: true }
                PropertyChanges { target: scrollList; visible: true }
                PropertyChanges { target: scrollSingle; visible: false }
                PropertyChanges { target: singleView; visible: false; focus: false }
                PropertyChanges { target: listButton; enabled: false; opacity: 0.1 }
                PropertyChanges { target: addButton; visible: true }
                PropertyChanges { target: deleteButton; visible: true }
            },
            State {
                name: 'inSingle'
                PropertyChanges { target: listView; visible: false; focus: false }
                PropertyChanges { target: scrollList; visible: false }
                PropertyChanges { target: scrollSingle; visible: true }
                PropertyChanges { target: singleView; visible: true; focus: true }
                PropertyChanges { target: listButton; enabled: true; opacity: 0.9 }
                PropertyChanges { target: addButton; visible: false }
                PropertyChanges { target: deleteButton; visible: false }
            }
        ]
    }
}
