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

//    palette.highlight: 'violet'
//    palette.buttonText: 'red'

    DelegateModel {
        id: visualModel
        model: holidayModel
        delegate: Package {
            ListDelegate { id: listDelegate; Package.name: 'listDelegate' }
            SingleDelegate { id: singleDelegate; Package.name: 'singleDelegate' }
        }
    }

//    function getChildWithName(contentItem, name) {
//        for (var i = 0; i < contentItem.children.length; i++) {
//            var item = contentItem.children[i];
////            if (item.contentItem.children.length > 0)


//            if (item.objectName == name)
//                return item;
//        }

//        return undefined;
//    }

    function showList() {
        listView.currentIndex = singleView.currentIndex;
        content.state = 'list';
        buttons.state = 'list'
    }
    function showSingle() {
        content.state = 'single'
        buttons.state = 'single-normal'
        singleView.contentItem.children[singleView.currentIndex].state = 'normal'
    }

    function addItem() {
        showSingle()
        singleView.contentItem.children[singleView.currentIndex].state = 'add'
    }
    function editItem() {
        buttons.state = 'single-edit'
        singleView.contentItem.children[singleView.currentIndex].state = 'edit'
    }
    function deleteItem() {
        console.log('Delete')
    }

    function saveItem() {
        buttons.state = 'single-normal'
        singleView.contentItem.children[singleView.currentIndex].state = 'normal'
    }
    function discardItem() {
        buttons.state = 'single-normal'
        singleView.contentItem.children[singleView.currentIndex].state = 'normal'
    }

    header: Rectangle {
        id: buttons
        width: root.width
        height: backButton.height + 10

        state: 'list'
        states: [
            State {
                name: 'list'
                PropertyChanges { target: backButton; visible: false }
                PropertyChanges { target: addButton; visible: true }
                PropertyChanges { target: deleteButton; visible: true }
                PropertyChanges { target: quitButton; visible: true }
            },
            State {
                name: 'single-normal'
                PropertyChanges { target: backButton; visible: true }
                PropertyChanges { target: addButton; visible: false }
                PropertyChanges { target: deleteButton; visible: false }
                PropertyChanges { target: quitButton; visible: true }
            },
            State {
                name: 'single-edit'
                PropertyChanges { target: backButton; visible: false }
                PropertyChanges { target: addButton; visible: false }
                PropertyChanges { target: deleteButton; visible: false }
                PropertyChanges { target: quitButton; visible: false }
            }
        ]

        RowLayout {
            anchors.fill: parent
            anchors.margins: 5

            RoundButton {
                id: backButton
                Layout.preferredWidth: height; Layout.fillHeight: true
                onClicked: showList();
                Image {
                    fillMode: Image.PreserveAspectFit
                    anchors.centerIn: parent
                    sourceSize.width: backButton.width
                    sourceSize.height: backButton.height
                    source: "qrc:images/arrow.jpg"
                }
            }

            RoundButton {
                id: quitButton
                Layout.preferredWidth: height; Layout.fillHeight: true
                Layout.alignment: Qt.AlignRight
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
                width: parent.width
                Layout.alignment: Qt.AlignTop

                TextField {
                    Layout.preferredWidth: listHeader.width * 1/8
                    text: qsTr('Дата')
                }
                TextField {
                    Layout.preferredWidth: listHeader.width * 3/8
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
                    Layout.fillWidth: true; Layout.fillHeight: true
                    model: visualModel.parts.listDelegate
                    snapMode: ListView.SnapOneItem
                    clip: true
                    boundsBehavior: ListView.SnapToItem
//                    highlight: Rectangle { color: 'yellow' }
//                    highlightFollowsCurrentItem: true
//                    highlightMoveDuration: 0
                    focus: true
                }
            }
            RowLayout {
                id: buttonBox
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
        }

        ColumnLayout {
            id: singleItem
            anchors.fill: parent

            ScrollView {
                id: scrollSingle
                Layout.fillWidth: true; Layout.fillHeight: true
                ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

                ListView {
                    id: singleView
                    Layout.fillWidth: true
                    model: visualModel.parts.singleDelegate
//                    model: holidayModel
//                    delegate: SingleDelegate { }
                    snapMode: ListView.SnapOneItem
                    orientation: ListView.Horizontal
                    clip: true
                    boundsBehavior: ListView.StopAtBounds
                    highlightMoveDuration: 0
                }
            }
            RowLayout {
                Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom

                RoundButton {
                    id: editButton
                    text: qsTr('Edit')
                    onClicked: editItem()
                }
                RoundButton {
                    id: saveButton
                    text: qsTr('Save')
                    onClicked: saveItem()
                }
                RoundButton {
                    id: discardButton
                    text: qsTr('Discard')
                    onClicked: discardItem()
                }
            }
        }

        state: 'list'
        states: [
            State {
                name: 'list'
                PropertyChanges { target: listItem; visible: true }
                PropertyChanges { target: scrollList; focus: true }
                PropertyChanges { target: singleItem; visible: false }
            },
            State {
                name: 'single'
                PropertyChanges { target: listItem; visible: false }
                PropertyChanges { target: singleItem; visible: true }
            }
        ]
    }
}
