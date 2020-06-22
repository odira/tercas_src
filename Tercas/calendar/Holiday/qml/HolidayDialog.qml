import QtQuick 2.12
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.5

Dialog {
    id: holidayDialog
    title: qsTr("Детальная Информация")
    anchors.centerIn: parent
    height: 500
    modal: true
    spacing: 10

    property alias currentState: dialogStateGroup.state
    property int currentRow: 0
    property var date
    property var type
    property var noteRu

    header: RowLayout {
        width: root.width
        height: 60

        RowLayout {
            Layout.alignment: Qt.AlignCenter

            RoundButton {
                id: prevButton
                radius: 0
                font.bold: true
                text: "-"
                onClicked: currentRow--
            }
            TextField {
                width: 100
                Layout.alignment: Qt.AlignHCenter
                readOnly: true
                text: "Item " + (currentRow + 1)
            }
            RoundButton {
                id: nextButton
                radius: 0
                font.bold: true
                text: "+"
                onClicked: currentRow++
            }
        }
    }

    contentItem: ColumnLayout {
        Layout.fillWidth: true
        Layout.fillHeight: true

        RowLayout {
            id: dateLayout
            Layout.fillWidth: true
            TextField {
                id: dateField
                Layout.fillWidth: true
                text: date //holidayModel.get(currentRow).date
            }
            RoundButton {
                id: calendarButton
                width: 100
                height: dateField.height
                radius: 0
                font.bold: true
                text: "..."
                onClicked: calendarDialog.open()
            }
        }
        ComboBox {
            id: typeCombo
            Layout.fillWidth: true
            model:  [
                'Нерабочий праздничный день',
                'Выходной день',
                'Рабочий день'
            ]
            currentIndex: type_pid  // find(holidayModel.get(currentRow).type_pid)
        }
        TextArea {
            id: noteField
            implicitWidth: 1100
            implicitHeight: 200
            background: Rectangle {
                border.color: "black"
            }
            wrapMode: TextEdit.WordWrap
            text: holidayModel.get(currentRow).note
        }
    }

    footer: Item {
//        Layout.fillWidth: true
        width: holidayDialog.width
        height: 70

        RowLayout {
//            Layout.fillHeight: true
//            Layout.alignment: Qt.AlignCenter
            anchors.fill: parent
            anchors.margins: 10

            RoundButton {
                id: editButton
                implicitWidth: 100
                Layout.fillHeight: true
                radius: 0
                text: "Edit"
                onClicked: {
                    currentState = "EDIT"
                }
            }
            RoundButton {
                id: closeButton
                implicitWidth: 100
                radius: 0
                text: qsTr("Close")
                onClicked: {
                    close()
                }
            }

            RoundButton {
                id: saveButton
                implicitWidth: 100
                radius: 0
                text: "Save"
                onClicked: {
                    if (currentState == "EDIT")
                    {
                        date = dateField.text
                        type = typeCombo.currentText
                        noteRu = noteRuField.text

                        holidayModel.set(holidayDialog.currentRow, date, 'date');
                        holidayModel.set(holidayDialog.currentRow, type, 'holiday_type');
                        holidayModel.set(holidayDialog.currentRow, noteRu, 'note_ru');
                        holidayModel.submitDB()

                        currentState = "NORMAL"
                    }
                    else if (currentState == "ADD")
                    {
                        date = dateField.text
                        type = typeCombo.currentText
                        noteRu = noteRuField.text

                        holidayModel.add(date, type, noteRu)
                        holidayModel.submitDB()

                        currentState = "NORMAL"
                        close()
                    }
                }
            }
            RoundButton {
                id: cancelButton
                implicitWidth: 100
                radius: 0
                text: "Cancel"
                onClicked: {
                    holidayModel.revertAll()
                    currentState = "NORMAL"
                }
            }
        }
    }

    StateGroup {
        id: dialogStateGroup
        states: [
            State {
                name: "NORMAL"
                PropertyChanges { target: dateField; readOnly: true }
                PropertyChanges { target: noteRuField; readOnly: true }
                PropertyChanges { target: calendarButton; enabled: false }
                PropertyChanges { target: editButton; visible: true }
                PropertyChanges { target: closeButton; visible: true }
                PropertyChanges { target: prevButton; enabled: true }
                PropertyChanges { target: nextButton; enabled: true }
                PropertyChanges { target: saveButton; visible: false }
                PropertyChanges { target: cancelButton; visible: false }
            },
            State {
                name: "EDIT"
                PropertyChanges { target: dateField; readOnly: false; focus: true }
                PropertyChanges { target: noteRuField; readOnly: false }
                PropertyChanges { target: calendarButton; enabled: true }
                PropertyChanges { target: editButton; visible: false }
                PropertyChanges { target: closeButton; visible: false }
                PropertyChanges { target: prevButton; enabled: false }
                PropertyChanges { target: nextButton; enabled: false }
                PropertyChanges { target: saveButton; visible: true }
                PropertyChanges { target: cancelButton; visible: true }
            },
            State {
                name: "ADD"
                PropertyChanges { target: dateField; readOnly: false; text: ''; focus: true }
                PropertyChanges { target: noteRuField; readOnly: false; text: '' }
                PropertyChanges { target: calendarButton; enabled: true }
                PropertyChanges { target: editButton; visible: false }
                PropertyChanges { target: closeButton; visible: false }
                PropertyChanges { target: prevButton; enabled: false }
                PropertyChanges { target: nextButton; enabled: false }
                PropertyChanges { target: saveButton; visible: true }
                PropertyChanges { target: cancelButton; visible: true }
            }
        ]
    }
    Component.onCompleted: dialogStateGroup.state = currentState

    CalendarDialog {
        id: calendarDialog
        calendarDate: dateField.text
        onAccepted: dateField.text = calendarDate
    }
}
