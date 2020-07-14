import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    id: root

    ColumnLayout {
        id: widgetBox
        width: parent.width

        RowLayout {
            width: parent.width
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
            width: parent.width
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
            width: parent.width
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

    states: [
        State {
            name: 'normal'
            PropertyChanges { target: dateField; readOnly: true }
            PropertyChanges { target: typeField; readOnly: true }
            PropertyChanges { target: noteField; readOnly: true }
        },
        State {
            name: 'edit'
            PropertyChanges { target: dateField; readOnly: false }
            PropertyChanges { target: typeField; readOnly: false }
            PropertyChanges { target: noteField; readOnly: false }
        },
        State {
            name: 'add'
            PropertyChanges { target: widgetBox; enabled: true }
        }
    ]
}
