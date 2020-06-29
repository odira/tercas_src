import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    id: singleDelegate

    function editItem() {
        state = 'Edit'
    }
    function deleteItem() {

    }
    function saveItem() {
        date = dateField.text
        type = dateField.text
        note = dateField.text
        console.log(date + type + note)
    }
    function discardItem() {

    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 5
        spacing: 10

        ColumnLayout {
            id: widgetBox
            Layout.fillWidth: true
            Layout.fillHeight: true
            enabled: false

            TextField {
                id: dateField
                Layout.fillWidth: true
                text: date.toLocaleDateString(Qt.locale("ru_RU"), "dd MMMM yyyy")
            }
            TextField {
                id: typeField
                Layout.fillWidth: true
                text: type
            }
            TextField {
                id: noteField
                Layout.fillWidth: true
                text: note
            }
            Item {
                id: spacing
                Layout.fillHeight: true
            }
        }

        RowLayout {
            id: buttonBox
            Layout.fillWidth: true
            Layout.fillHeight: false
            Layout.preferredHeight: 70

            Item { Layout.fillWidth: true }

            RoundButton {
                id: editButton
                Layout.fillHeight: true
                Layout.preferredWidth: 150
                radius: 0
                text: qsTr('Edit')

                onClicked: editItem()

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
            RoundButton {
                id: saveButton
                Layout.fillHeight: true
                Layout.preferredWidth: 150
                radius: 0
                text: qsTr('Save')

                onClicked: saveItem()

                background: Rectangle {
                    color: 'orange'
                    border.color: 'pink'
                }
            }
            RoundButton {
                id: discardButton
                Layout.fillHeight: true
                Layout.preferredWidth: 150
                radius: 0
                text: qsTr('Discard')

                onClicked: discardItem()

                background: Rectangle {
                    color: 'orange'
                    border.color: 'pink'
                }
            }
            Item { Layout.fillWidth: true }
        }
    }


    state: 'Normal'
    states: [
        State {
            name: 'Normal'
            PropertyChanges { target: widgetBox; enabled: false }
            PropertyChanges { target: editButton; visible: true }
            PropertyChanges { target: deleteButton; visible: true }
            PropertyChanges { target: saveButton; visible: false }
            PropertyChanges { target: discardButton; visible: false }
        },
        State {
            name: 'Edit'
            PropertyChanges { target: widgetBox; enabled: true }
            PropertyChanges { target: editButton; visible: false }
            PropertyChanges { target: deleteButton; visible: false }
            PropertyChanges { target: saveButton; visible: true }
            PropertyChanges { target: discardButton; visible: true }
        }
    ]
}
