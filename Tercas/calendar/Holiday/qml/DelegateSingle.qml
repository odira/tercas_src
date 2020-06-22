import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    id: root

    ColumnLayout {
        anchors.fill: parent

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

    state: 'Normal'
    states: [
        State {
            name: 'Normal'
            PropertyChanges { target: dateField; enabled: false }
        }

    ]
}
