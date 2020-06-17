import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import QtQml.Models 2.12
import QtGraphicalEffects 1.12

ApplicationWindow {
    id: root
    visible: true
    width: Screen.width * 3/4
    height: Screen.height * 3/4
    title: qsTr("Person Database")

    DelegateModel {
        id: visualModel
        delegate: Delegate {}
        model: personModel
    }

    function showList() {
        listView.currentIndex = singleView.currentIndex
        view.state = 'inList';
    }
    function showSingle() {
        singleView.currentIndex = listView.currentIndex
        view.state = 'inSingle'
    }

    menuBar: Rectangle {
        id: menuBar
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
            Rectangle {
                id: spacing
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

//    // HEADER
//    header: Rectangle {
//        width: root.width
//        height: 50
//        border.color: 'pink'
//    }

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
                                Layout.preferredWidth: 200
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                text: qsTr('Фамилия')
                                font.bold: true
                                horizontalAlignment: TextField.AlignHCenter
                                background: Rectangle {
                                    border.color: 'pink'
                                }
                            }
                            TextField {
                                Layout.preferredWidth: 150
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                text: qsTr('Имя')
                                horizontalAlignment: TextField.AlignHCenter
                                background: Rectangle {
                                    border.color: 'pink'
                                }
                            }
                            TextField {
                                Layout.preferredWidth: 150
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                text: qsTr('Отчество')
                                horizontalAlignment: TextField.AlignHCenter
                                background: Rectangle {
                                    border.color: 'pink'
                                }
                            }
                            TextField {
                                Layout.preferredWidth: 50
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                wrapMode: TextInput.WordWrap
                                text: qsTr('Год рожд')
                                horizontalAlignment: TextField.AlignHCenter
                                background: Rectangle {
                                    border.color: 'pink'
                                }
                            }
                            TextField {
                                Layout.preferredWidth: 200
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                text: qsTr('Должность')
                                horizontalAlignment: TextField.AlignHCenter
                                background: Rectangle {
                                    border.color: 'pink'
                                }
                            }
                            TextField {
                                Layout.preferredWidth: 45
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                font.pixelSize: 11
                                text: qsTr('Класс')
                                horizontalAlignment: TextField.AlignHCenter
                                background: Rectangle {
                                    border.color: 'pink'
                                }
                            }
                            TextField {
                                Layout.preferredWidth: 45
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                font.pixelSize: 11
                                text: qsTr('Смена')
                                horizontalAlignment: TextField.AlignHCenter
                                background: Rectangle {
                                    border.color: 'pink'
                                }
                            }
                            TextField {
                                Layout.preferredWidth: 200
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                text: qsTr('Направление')
                                horizontalAlignment: TextField.AlignHCenter
                                background: Rectangle {
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

//                ScrollBar.vertical: ScrollBar {
//                    id: listScrollBar
//                    active: true
//                    orientation: Qt.Vertical
//                    opacity: active ? 1:0
//                    Behavior on opacity { NumberAnimation { duration: 500 }}

//                    contentItem: Rectangle {
//                        implicitWidth: 10
//                        implicitHeight: listView.contentItem.height
//                        radius: 1
//                        color: 'blue'
//                    }
//                }
            }
        }

        ScrollView {
            id: scrollSingle
            anchors.fill: parent
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
            ScrollBar.vertical.policy: ScrollBar.AlwaysOn

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
                PropertyChanges { target: listView; visible: true; focus: true }
                PropertyChanges { target: scrollList; visible: true }
                PropertyChanges { target: scrollSingle; visible: false }
                PropertyChanges { target: singleView; visible: false; focus: false }
                PropertyChanges { target: listButton; enabled: false; opacity: 0.1 }
            },
            State {
                name: 'inSingle'
                PropertyChanges { target: listView; visible: false; focus: false }
                PropertyChanges { target: scrollList; visible: false }
                PropertyChanges { target: scrollSingle; visible: true }
                PropertyChanges { target: singleView; visible: true; focus: true }
                PropertyChanges { target: listButton; enabled: true; opacity: 0.9 }
            }
        ]
    }
}
