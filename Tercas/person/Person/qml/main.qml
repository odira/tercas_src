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

    ColumnLayout {
        id: rootLayout
        anchors.fill: parent
        anchors.margins: 5

        RowLayout {
            id: toolbar
            Layout.fillWidth: true
            Layout.preferredHeight: 70

            Button {
                id: listButton
                Layout.preferredWidth: 70
                Layout.preferredHeight: 70
                onClicked: view.state = 'inList'

                Image {
                    id: image
                    fillMode: Image.PreserveAspectFit
                    anchors.centerIn: parent
                    sourceSize.width: listButton.width
                    sourceSize.height: listButton.height
                    source: "qrc:images/arrow.jpg"
                }
                ColorOverlay {
                    anchors.fill: parent
                    source: image
                    color: "#efffffff"
                }
            }
        }

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
                    PropertyChanges { target: listButton; enabled: false }
                },
                State {
                    name: 'inSingle'
                    PropertyChanges { target: listView; visible: false; focus: false }
                    PropertyChanges { target: singleView; visible: true; focus: true }
                    PropertyChanges { target: listButton; enabled: true }
                }
            ]
        }

        RowLayout {
            id: bottonBox
            Layout.fillWidth: true
            height: 60
            layoutDirection: Qt.RightToLeft
            spacing: 10

            RoundButton {
                implicitWidth: 200
                height: parent.height
                radius: 0
                text: qsTr("Quit")
                onClicked: Qt.quit()
            }
        }
    }
}
