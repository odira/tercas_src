import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Window 2.3

import Wiipuri.Calendar 1.0

ApplicationWindow {
    id: root
    title: qsTr("Месячный Календарь Работников")
    visible: true
    width: Screen.width
    height: Screen.height

    header: RowLayout {
        Layout.fillWidth: true
        height: 80

        DatePicker {
            id: datePicker
            Layout.alignment: Qt.AlignHCenter
            showDate: false
            onPickerDateUpdated: {
                emplSheduleMonthModel.date = pickerDate
                listView.daysInMonth = emplSheduleMonthModel.columnCount() - 1
            }
        }
    }

    ColumnLayout {
        anchors.fill: parent

        MonthModelView {
            id: listView
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignTop
            Layout.margins: 20
            focus: true
        }
    }
}
