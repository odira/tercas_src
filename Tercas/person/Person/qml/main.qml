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
//                    opacity: 0.1
                }
//                ColorOverlay {
//                    anchors.fill: parent
//                    source: image
//                    color: "#efffffff"
//                }
            }
            Rectangle {
                id: spacingi
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

    header: Rectangle {
        width: root.width
        height: 50
        anchors.margins: 5
        border.color: 'pink'
    }

    ColumnLayout {
        id: rootLayout
        anchors.fill: parent
        anchors.margins: 5

        Rectangle {
            id: view
            Layout.fillWidth: true
            Layout.fillHeight: true
            border.color: "pink"

            ScrollView {
                id: scroll
                anchors.fill: parent
                ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
                ScrollBar.vertical.policy: ScrollBar.AlwaysOn
                visible: listView.visible

                ListView {
                    id: listView
                    anchors.fill: parent
                    anchors.margins: 10
                    model: visualModel.parts.list
                    snapMode: ListView.SnapOneItem
                    visible: true
                    clip: true
                }
            }

            ListView {
                id: singleView
                anchors.fill: parent
                anchors.margins: 10
                model: visualModel.parts.single
                snapMode: ListView.SnapOneItem
                orientation: ListView.Horizontal
                visible: true
                clip: true
                highlightMoveDuration: 0
            }

            state: 'inList'
            states: [
                State {
                    name: 'inList'
                    PropertyChanges { target: listView; visible: true; focus: true }
                    PropertyChanges { target: scroll; visible: true }
                    PropertyChanges { target: singleView; visible: false; focus: false }
                    PropertyChanges { target: listButton; enabled: false; opacity: 0.1 }
                },
                State {
                    name: 'inSingle'
                    PropertyChanges { target: listView; visible: false; focus: false }
                    PropertyChanges { target: singleView; visible: true; focus: true }
                    PropertyChanges { target: listButton; enabled: true; opacity: 0.9 }
                }
            ]
        }
    }
}
