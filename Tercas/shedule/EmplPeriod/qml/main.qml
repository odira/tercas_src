import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12
import QtQml.Models 2.12

import ColumnsEnum 1.0

ApplicationWindow {
    id: root
    visible: true
    width: Screen.width
    height: Screen.height
    title: qsTr("Период активности")

    TableView {
        anchors.fill: parent
        anchors.margins: 10

        columnWidthProvider: function(column) {
            if (column === ColumnsEnum.Column_pid ||
                column === ColumnsEnum.Column_person_pid ||
                column === ColumnsEnum.Column_activity_pid ||
                column === ColumnsEnum.Column_activity_color ||
                column === ColumnsEnum.Column_activity_note ||
                column === ColumnsEnum.Column_note)
                return 0;
            else if (column === ColumnsEnum.Column_person_surname ||
                     column === ColumnsEnum.Column_person_name ||
                     column === ColumnsEnum.Column_person_middlename ||
                     column === ColumnsEnum.Column_person_position ||
                     column === ColumnsEnum.Column_person_sectors_pool)
                return 200;
            else if (column === ColumnsEnum.Column_person_shift_num ||
                     column === ColumnsEnum.Column_activity_abbr ||
                     column === ColumnsEnum.Column_duration)
                return 35;
            else
                return 150;
        }

        model: periodModel
        columnSpacing: 5
        rowSpacing: 10

        delegate: Delegate {}
    }

//    ListView {
//        id: view
//        anchors.fill: parent
//        anchors.margins: 10
//        model: periodModel
//        delegate: Rectangle {
//            width: 150
//            height: 40
//            Text {
//                anchors.centerIn: parent
//                text: period
//            }
//        }
//    }
}
