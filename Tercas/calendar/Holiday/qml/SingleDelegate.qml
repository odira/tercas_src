import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    id: root
    width: ListView.view.width; height: ListView.view.height

    property int   pidValue:  model.pid
    property alias dateValue: dateField.text //.fromLocaleDateString(Qt.locale("ru_RU"), "dd MMMM yyyy")
    property alias typeValue: typeCombo.currentText
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
                ComboBox {
                    id: typeCombo
                    Layout.fillWidth: true
                    model: [
                        'Нерабочий праздничный день',
                        'Выходной день',
                        'Рабочий день'
                    ]
                    displayText: type
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
    }

    states: [
        State {
            name: 'normal'
            PropertyChanges { target: dateField; readOnly: true }
            PropertyChanges { target: typeCombo; editable: false }
            PropertyChanges { target: noteField; readOnly: true }

        },
        State {
            name: 'edit'
            PropertyChanges { target: dateField; readOnly: false }
            PropertyChanges { target: typeCombo; editable: true }
            PropertyChanges { target: noteField; readOnly: false }
        },
        State {
            name: 'add'
            PropertyChanges { target: dateField; readOnly: false }
            PropertyChanges { target: typeCombo; editable: true }
            PropertyChanges { target: noteField; readOnly: false }
        }
    ]
}
