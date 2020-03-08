import QtQuick 2.5

Item {
    TerkasCalendar {
        id: monthCalendar

        anchors.fill: parent
        anchors.margins: 5

        visibleYear: root.year
        visibleMonth: root.month
    }
}
