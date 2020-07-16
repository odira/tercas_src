import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    id: root

    property alias dateValue: dateField.text
    property alias typeValue: typeField.text
    property alias noteValue: noteField.text

    ColumnLayout {
        anchors.fill: parent

        ColumnLayout {
            Layout.alignment: Qt.AlignTop

            RowLayout {
                Text {
                    Layout.preferredWidth: root.width * 1/5
                    text: qsTr('Дата (календарная)')
                }
                TextField {
                    id: dateField; objectName: 'dateField'
                    Layout.fillWidth: true
                    text: date.toLocaleDateString(Qt.locale("ru_RU"), "dd MMMM yyyy")
                }
            }
            RowLayout {
                Text {
                    Layout.preferredWidth: root.width * 1/5
                    text: qsTr('Наименование дня')
                }
                TextField {
                    id: typeField
                    Layout.fillWidth: true
                    text: type
                }
            }
            RowLayout {
                Text {
                    Layout.preferredWidth: root.width * 1/5
                    text: qsTr('Примечание')
                }
                TextField {
                    id: noteField
                    Layout.fillWidth: true
                    text: note
                }
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

    states: [
        State {
            name: 'normal'
            PropertyChanges { target: dateField; readOnly: true }
            PropertyChanges { target: typeField; readOnly: true }
            PropertyChanges { target: noteField; readOnly: true }
            PropertyChanges { target: editButton; visible: true }
            PropertyChanges { target: saveButton; visible: false }
            PropertyChanges { target: discardButton; visible: false }

        },
        State {
            name: 'edit'
            PropertyChanges { target: dateField; readOnly: false }
            PropertyChanges { target: typeField; readOnly: false }
            PropertyChanges { target: noteField; readOnly: false }
            PropertyChanges { target: editButton; visible: false }
            PropertyChanges { target: saveButton; visible: true }
            PropertyChanges { target: discardButton; visible: true }
        }
    ]
}
