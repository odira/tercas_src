import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

import WiiCalendar 1.0

ApplicationWindow {
    id: rootWindow
    visible: true
    width: Screen.width
    height: Screen.height
    title: qsTr("EmplSheduleYear")


    TableView {
        id: table
        anchors.fill: parent
        anchors.leftMargin: 3
        anchors.rightMargin: 3
        anchors.topMargin: header.implicitHeight
        //            columnSpacing: 1
        //            rowSpacing: 1
        clip: true

        Text {
            id: header
            width: rootWindow.width
            horizontalAlignment: Text.AlignHCenter
            text: "Year Shedule"
            font.pixelSize: 24
            font.bold: true
            color: "black"
            z: 2
        }


        property var personCellWidth: 100
        property var commonCellWidth: (table.width - personCellWidth - columnSpacing) / (emplSheduleYearModel.columnCount() - 1)
        columnWidthProvider: function(column) {
            if (column === 0) return personCellWidth;
            return commonCellWidth
        }

        model: emplSheduleYearModel
        delegate: tableViewDelegate


        Component {
            id: tableViewDelegate
            Rectangle {
                id: tableDelegate
                implicitHeight: 50
                //                border.color: "gray"
                //                border.width: 1

                Label {
                    anchors.fill: parent
                    background: Rectangle {
                        height: (column == 0) ? parent.height : parent.height / 3
                        anchors.bottom: parent.bottom
                        color: background
                    }
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    text: display
                }
            }
        }
    }
}
