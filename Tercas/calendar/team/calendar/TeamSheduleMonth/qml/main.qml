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
            id: datePick
            Layout.alignment: Qt.AlignHCenter

            showDate:  false
            showMonth: true
            showYear:  true
            dpDate: calDate
            onDpDateUpdated: {
                teamSheduleMonthModel.date = pickerDate
//                listView.daysInMonth = emplSheduleMonthModel.columnCount() - 1
            }
        }
    }

    ColumnLayout {
        id: table
        anchors.fill: parent
        anchors.margins: 10

        function getMonthDay(column) {
            var prevMonthDays  = datePick.daysInMonth(datePick.month, datePick.year);
            var curMonthDays = datePick.daysInMonth(datePick.month + 1, datePick.year);

            if (column === 0)
                return prevMonthDays - 2;
            else if (column === 1)
                return prevMonthDays - 1;
            else if (column === 2)
                return prevMonthDays;
            else if (column <= curMonthDays + 2)
                return column - 2;
            else
                return column - 2 - curMonthDays;
        }

        function curMonth(column) {
            var curMonthDays = datePick.daysInMonth(datePick.month + 1, datePick.year);

            if (column <= 2)
                return false;
            else if (column > 2 && column <= curMonthDays + 2)
                return true;
            else
                return false;
        }

        // Graphical elements properties
        property int personCellWidth: 250
        property int dateCellWidth: (tableBody.width - personCellWidth) / 37 // 37 - number of days in calendar
        property int cellHeigth: dateCellWidth

        // TABLE HEADER
        Row {
            id: tableHeader
            Layout.fillWidth: true
            anchors.margins: 2

            Item {
                width: table.personCellWidth
                height: table.cellHeigth
                Rectangle {
                    anchors.fill: parent
                    anchors.margins: 2
                    color: "lightblue"
                    Text {
                        anchors.centerIn: parent
                        font.bold: true
                        text: "Person"
                    }
                }
            }

            Repeater {
                model: 37
                Item {
                    width: table.dateCellWidth
                    height: width
                    Rectangle {
                        anchors.fill: parent
                        anchors.margins: 2
                        color: "yellow"
                        border.color: "lightgray"
                        radius: height / 10
                        opacity: table.curMonth(index) ? 1.0 : 0.2
                        Text {
                            anchors.centerIn: parent
                            font.bold: true
                            text: table.getMonthDay(index)
                        }
                    }
                }
            }
        }

        // TABLE BODY
        TableView {
            id: tableBody
            Layout.fillWidth: true; Layout.fillHeight: true
            model: teamSheduleMonthModel
            clip: true

            delegate: Item {
                implicitWidth: column == 0 ? table.personCellWidth : table.dateCellWidth
                implicitHeight: table.dateCellWidth

                Rectangle {
                    anchors.fill: parent
                    anchors.margins: 2
                    color: column == 0 ? 'lightgreen' : 'orange'
                    opacity: model.out_of_month ? 1.0 : 0.2
                    border.color: "lightgray"
                    radius: height / 10

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
