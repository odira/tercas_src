import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12
import QtQml.Models 2.12

//import ColumnsEnums 1.0 as Enums

ApplicationWindow {
    id: root
    visible: true
    width: Screen.width * 2/3
    height: Screen.height * 2/3
    title: qsTr("Период активности")

    TableView {
        anchors.fill: parent
        anchors.margins: 10

        columnWidthProvider: function(column) {
            if (column === 0 ||
                column === 1 ||
                column === 8 ||
                column === 9 ||
                column === 11 ||
                column === 12 ||
                column === 16)
                return 0;
            else if (column === 2 ||
                     column === 3 ||
                     column === 4 ||
                     column === 5 ||
                     column === 7)
                return 200;
            else if (column === 6)
                return 20;
            else if (column === 15)
                return 30;
            else
                return 150;
        }

        model: periodModel
        columnSpacing: 10
        rowSpacing: 10

        delegate: Rectangle {
            implicitWidth: 100
            implicitHeight: 30
            border.color: "red"
            Text {
                anchors.centerIn: parent
                text: {
                    if (column === 13)
                        return start_date.toLocaleDateString(Qt.locale("ru_RU"), "dd MMMM yyyy");
                    else if (column === 14)
                        return end_date.toLocaleDateString(Qt.locale("ru_RU"), "dd MMMM yyyy");
                    else
                        return display;
                }
            }
        }
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
