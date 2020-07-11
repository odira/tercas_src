import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import QtQml.Models 2.12

ApplicationWindow {
    id: root
    width: Screen.width * 3/4; height: Screen.height * 3/4
    visible: true
    title: qsTr("Holiday Database")

    DelegateModel {
        id: visualModel
        model: holidayModel
        delegate: Package {
            ListDelegate {
                id: listDelegate; Package.name: 'listDelegate'
                width: listItem.width; height: 50
            }
            SingleDelegate {
                id: singleDelegate; Package.name: 'singleDelegate'
                width: singleItem.width; height: singleItem.height
            }
        }
//        property int currentIndex
    }

    function showList() {
        content.state = 'inList';
    }
    function showSingle() {
        content.state = 'inSingle'
        singleView.currentIndex = listView.currentIndex
    }

    function addItem() {
        showSingle()
        singleView.contentItem.children[0].state = 'Add'
    }
    function deleteItem() {
        console.log('Delete')
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
                Layout.preferredWidth: height; Layout.fillHeight: true
                radius: 0
                onClicked: content.state = 'inList'
                Image {
                    fillMode: Image.PreserveAspectFit
                    anchors.centerIn: parent
                    sourceSize.width: listButton.width
                    sourceSize.height: listButton.height
                    source: "qrc:images/arrow.jpg"
                }
            }

            RowLayout {
                id: listFooter
                Layout.fillWidth: false; Layout.fillHeight: false
                Layout.alignment: Qt.AlignHCenter

                RoundButton {
                    id: addButton
                    text: qsTr('Add Item')
                    onClicked: addItem()
                }
                RoundButton {
                    id: deleteButton
                    text: qsTr('Delete Item')
                    onClicked: deleteItem()
                }
            }

            RoundButton {
                id: quitButton
                Layout.preferredWidth: height; Layout.fillHeight: true
                Layout.alignment: Qt.AlignRight
                radius: 0
                onClicked: Qt.quit()
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
        id: content
        anchors.fill: parent; anchors.margins: 5

        ColumnLayout {
            id: listItem
            anchors.fill: parent

            RowLayout {
                id: listHeader
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignTop

                TextField {
                    Layout.preferredWidth: parent.width * 1/8
                    text: qsTr('Дата')
                }
                TextField {
                    Layout.preferredWidth: parent.width * 3/8
                    text: qsTr('Календарный день')
                }
                TextField {
                    Layout.fillWidth: true
                    text: qsTr('Примечание')
                }
            }

            ScrollView {
                id: scrollList
                Layout.fillWidth: true; Layout.fillHeight: true
                ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
                ScrollBar.vertical.policy: ScrollBar.AlwaysOn
                focus: true

                ListView {
                    id: listView
                    Layout.fillWidth: true;Layout.fillHeight: true
                    model: visualModel.parts.listDelegate
                    snapMode: ListView.SnapOneItem
                    clip: true
                    boundsBehavior: ListView.SnapToItem
        //                                highlight: Rectangle { color: 'yellow' }
        //                                highlightFollowsCurrentItem: true
        //                                highlightMoveDuration: 0
                                        focus: true
        //                                onCurrentIndexChanged: singleView.currentIndex = currentIndex
        //                                onCurrentIndexChanged:
                }
            }
        }

        ColumnLayout {
            id: singleItem
            anchors.fill: parent

            ScrollView {
                id: scrollSingle
                Layout.fillWidth: true; Layout.fillHeight: false
                ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

                ListView {
                    id: singleView
                    Layout.fillWidth: true; Layout.fillHeight: true
                    model: visualModel.parts.singleDelegate
                    snapMode: ListView.SnapOneItem
                    orientation: ListView.Horizontal
                    visible: true
                    clip: true
                    boundsBehavior: ListView.StopAtBounds

                    highlightMoveDuration: 0
                }

            }
            RowLayout {
                id: buttonBox
                Layout.fillWidth: true; Layout.fillHeight: false
                Layout.alignment: Qt.AlignHCenter

                property color buttonBackground: "#8EC9BB"

                function edit() {
                    singleView.contentItem.children[singleView.currentIndex].state = 'Edit'
                    singleButtonBox.state = 'Edit'
                }
                function discard() {
                    singleView.contentItem.children[singleView.currentIndex].state = 'Normal'
                    singleButtonBox.state = 'Normal'
                }

                RoundButton {
                    id: editButton
                    Layout.fillHeight: true
                    Layout.preferredWidth: 150
                    text: qsTr('Edit')
                    onClicked: edit()
                }
                RoundButton {
                    id: saveButton
                    Layout.fillHeight: true
                    Layout.preferredWidth: 150
                    text: qsTr('Save')
                    onClicked: save()
                }
                RoundButton {
                    id: discardButton
                    Layout.fillHeight: true
                    Layout.preferredWidth: 150
                    text: qsTr('Discard')
                    onClicked: discard()
                }

                state: 'Normal'
                states: [
                    State {
                        name: 'Normal'
                        PropertyChanges { target: editButton; enabled: true }
                        PropertyChanges { target: saveButton; enabled: false }
                        PropertyChanges { target: discardButton; enabled: false }
                    },
                    State {
                        name: 'Edit'
                        PropertyChanges { target: editButton; enabled: false }
                        PropertyChanges { target: saveButton; enabled: true }
                        PropertyChanges { target: discardButton; enabled: true }
                    }
                ]
            }
        }


//        ColumnLayout {
//            id: single
//            anchors.fill: parent

//            ScrollView {
//                id: scrollSingle
//                Layout.fillWidth: true
//                Layout.fillHeight: true
//                ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

//                ListView {
//                    id: singleView
//                    Layout.fillWidth: true
//                    Layout.fillHeight: true
//                    model: visualModel.parts.single
//                    snapMode: ListView.SnapOneItem
//                    orientation: ListView.Horizontal
//                    visible: true
//                    clip: true
//                    boundsBehavior: ListView.StopAtBounds

//                    highlightMoveDuration: 0
//                }
//            }
//            SingleFooter {
//                id: singleFooter
//                Layout.fillWidth: true
//                Layout.fillHeight: false
//                Layout.preferredHeight: 60
//            }
//        }

        state: 'inList'
//        state: 'inSingle'
        states: [
            State {
                name: 'inList'
                PropertyChanges { target: listItem; visible: true }
//                PropertyChanges { target: scrollList; focus: true }
//                PropertyChanges { target: listView; focus: true }
                PropertyChanges { target: singleItem; visible: false }
//                PropertyChanges { target: singleView; focus: false }
//                PropertyChanges { target: listButton; enabled: false; opacity: 0.1 }
            },
            State {
                name: 'inSingle'
                PropertyChanges { target: listItem; visible: false }
//                PropertyChanges { target: listView; focus: false }
                PropertyChanges { target: singleItem; visible: true }
//                PropertyChanges { target: singleView; focus: true }
//                PropertyChanges { target: listButton; enabled: true; opacity: 0.9 }
            }
        ]
    }
}
