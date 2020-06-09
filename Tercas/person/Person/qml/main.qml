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
    title: qsTr("Person Database")

    DelegateModel {
        id: visualModel
        delegate: Delegate {}
        model: personModel
    }

    ColumnLayout {
        id: rootLayout
        anchors.fill: parent
        anchors.margins: 10
        spacing: 10

        RowLayout {
            id: toolbar
            Layout.fillWidth: true
            height: 60
            spacing: 10

            RoundButton {
                implicitWidth: 100
                height: parent.height
                radius: 0
                text: qsTr("List")
                onClicked: view.state = 'inList'
            }

            RoundButton {
                implicitWidth: 100
                height: parent.height
                radius: 0
                text: qsTr("Single")
                onClicked: view.state = 'inSingle'
            }
        }

        Rectangle {
            id: view
            Layout.fillWidth: true
            Layout.fillHeight: true
            border.color: "black"

            ListView {
                id: listView
                anchors.fill: parent
                anchors.margins: 1
                model: visualModel.parts.list
                snapMode: ListView.SnapOneItem
                visible: false
                clip: true
            }

            ListView {
                id: singleView
                anchors.fill: parent
                anchors.margins: 1
                model: visualModel.parts.single
                snapMode: ListView.SnapOneItem
                orientation: ListView.Horizontal
                visible: true
                clip: true
            }

            state: 'inList'
            states: [
                State {
                    name: 'inList'
                    PropertyChanges { target: listView; visible: true; focus: true }
                    PropertyChanges { target: singleView; visible: false; focus: false }
                },
                State {
                    name: 'inSingle'
                    PropertyChanges { target: listView; visible: false; focus: false }
                    PropertyChanges { target: singleView; visible: true; focus: true }
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
