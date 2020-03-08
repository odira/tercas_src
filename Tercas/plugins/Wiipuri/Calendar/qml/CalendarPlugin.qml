import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    width: 1000; height: 800

    property date curDate: new Date()

    ColumnLayout {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 5
        anchors.topMargin: 5

        Label {
            background: Rectangle {
                color: "lightblue"
            }
            text: curDate
        }

        DatePicker {
            id: datePicker
            pickerDate: curDate
            onPickerDateUpdated: curDate = pickerDate
        }

        DatePicker {
            showDate: false
            pickerDate: curDate
            onPickerDateUpdated: curDate = pickerDate
        }
    }
}
