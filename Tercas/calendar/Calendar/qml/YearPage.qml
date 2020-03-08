import QtQuick 2.0

Item {
    id: yearPage

    Component {
        id: yearCalendarDelegate

        Item {
            width: yearCalendar.cellWidth
            height: yearCalendar.cellHeight

            TerkasCalendar {
                anchors.fill: parent
                anchors.margins: 5
                shiftNum: root.shift
                selectedDate: new Date(root.year, index, 1)
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    root.month = month
                    calendarStack.state = "monthCalendar";
                }
            }
        }
    }

    GridView {
        id: yearCalendar
        anchors.fill: parent
        cellWidth: width / 4
        cellHeight: height / 3
        model: 12
        delegate: yearCalendarDelegate
        clip: true
        interactive: false
    }
}
