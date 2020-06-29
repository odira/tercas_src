import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
//    id: singleDelegate

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
    }

//    state: 'Normal'
    states: [
        State {
            name: 'Normal'
            PropertyChanges { target: widgetBox; enabled: false }
//            PropertyChanges { target: editButton; visible: true }
//            PropertyChanges { target: saveButton; visible: false }
//            PropertyChanges { target: discardButton; visible: false }
        },
        State {
            name: 'Edit'
            PropertyChanges { target: widgetBox; enabled: true }
//            PropertyChanges { target: editButton; visible: false }
//            PropertyChanges { target: saveButton; visible: true }
//            PropertyChanges { target: discardButton; visible: true }
        }
    ]
}
