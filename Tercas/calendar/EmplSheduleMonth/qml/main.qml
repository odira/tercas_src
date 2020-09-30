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
    color: Qt.lighter('black')

    header:
        Rectangle {
        width: root.width
        height: 100
        color: 'yellow'

        RowLayout {
            anchors.fill: parent

        DatePicker {
            id: datePicker
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignCenter
            showDate: false
            onDpDateUpdated: {
                emplSheduleMonthModel.date = dpDate
                listView.daysInMonth = emplSheduleMonthModel.columnCount() - 1
            }
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
            Layout.leftMargin: 20
            Layout.rightMargin: leftMargin
            Layout.bottomMargin: 20
            focus: true
        }
    }
}
