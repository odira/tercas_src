import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    id: root

    function edit() {
        console.log('Edit')
        state = 'Edit'
    }
    function save() {
        date = dateField.text
        type = dateField.text
        note = dateField.text
    }
    function discard() {
        console.log('Undo')
        dateField.undo()
    }

    ColumnLayout {
        anchors.fill: parent; anchors.margins: 5
        spacing: 10

        ColumnLayout {
            id: widgetBox
            Layout.fillWidth: true; Layout.fillHeight: true
            enabled: false

            RowLayout {
                Layout.fillWidth: true
                Text {
                    Layout.preferredWidth: parent.width * 1/5
                    text: qsTr('Дата (календарная)')
                }
                TextField {
                    id: dateField
                    Layout.fillWidth: true
                    text: date.toLocaleDateString(Qt.locale("ru_RU"), "dd MMMM yyyy")
                }
            }
            RowLayout {
                Layout.fillWidth: true
                Text {
                    Layout.preferredWidth: parent.width * 1/5
                    text: qsTr('Наименование дня')
                }
                TextField {
                    id: typeField
                    Layout.fillWidth: true
                    text: type
                }
            }
            RowLayout {
                Layout.fillWidth: true
                Text {
                    Layout.preferredWidth: parent.width * 1/5
                    text: qsTr('Примечание')
                }
                TextField {
                    id: noteField
                    Layout.fillWidth: true
                    text: note
                }
            }
        }
    }

//    state: 'Normal'
    states: [
        State {
            name: 'Normal'
//            PropertyChanges { target: widgetBox; enabled: false }
//            PropertyChanges { target: editButton; visible: true }
//            PropertyChanges { target: saveButton; visible: false }
//            PropertyChanges { target: discardButton; visible: false }
            PropertyChanges { target: dateField; readOnly: true }
            PropertyChanges { target: typeField; readOnly: true }
            PropertyChanges { target: noteField; readOnly: true }
        },
        State {
            name: 'Edit'
            PropertyChanges { target: widgetBox; enabled: true }
//            PropertyChanges { target: editButton; visible: false }
//            PropertyChanges { target: saveButton; visible: true }
//            PropertyChanges { target: discardButton; visible: true }
        },
        State {
            name: 'Add'
            PropertyChanges { target: widgetBox; enabled: true }
        }
    ]
}
