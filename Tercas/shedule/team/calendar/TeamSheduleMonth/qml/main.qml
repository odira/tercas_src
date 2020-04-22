import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12

import Wiipuri.Calendar 1.0

ApplicationWindow {
    id: root
    title: qsTr("Месячный Календарь Работников")
    visible: true
    width: Screen.width
    height: Screen.height

    property date calDate: teamSheduleMonthModel.date

    header: RowLayout {
        Layout.fillWidth: true
        height: 80

        DatePicker {
            id: datePicker
            Layout.alignment: Qt.AlignHCenter

            showDate:  false
            showMonth: true
            showYear:  true
            pickerDate: calDate
            onPickerDateUpdated: {
                teamSheduleMonthModel.date = pickerDate
//                listView.daysInMonth = emplSheduleMonthModel.columnCount() - 1
            }
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10



        Row {
            Layout.fillWidth: true; height: 50

            Rectangle {
                anchors.fill: parent
                anchors.margins: 2
                color: "red"
            }
        }

        TableView {
            id: table
            Layout.fillWidth: true; Layout.fillHeight: true
            model: teamSheduleMonthModel
            clip: true

            delegate: Item {
                property int personColumnWidth: 250
                property int dateColumnWidth: (table.width - personColumnWidth) / 37 // 37 - number of days in calendar

                implicitWidth: column == 0 ? personColumnWidth : dateColumnWidth
                implicitHeight: dateColumnWidth

                Rectangle {
                    anchors.fill: parent
                    anchors.margins: 2
                    color: column == 0 ? 'lightgreen' : 'orange'
                    opacity: model.out_of_month ? 1.0 : 0.2
                    border.color: "gray"
                    Text {
                        anchors.fill: parent
                        anchors.leftMargin: column == 0 ? 10 : 0
                        horizontalAlignment: column == 0 ? Text.AlignLeft : Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        font.pixelSize: 8
                        text: display
                    }
                }
            }
        }
    }
}
