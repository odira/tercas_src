import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import ColumnsEnum 1.0

Rectangle {
    implicitWidth: 100
    implicitHeight: 35
    border.color: {
        if (column === ColumnsEnum.Column_activity_abbr)
            return activity_color;
        return "pink";
    }
    color: {
        if (column === ColumnsEnum.Column_activity_abbr) {
            return activity_color;
        }
        else
            return "transparent";
    }
    Text {
//        anchors.centerIn: parent
        anchors.fill: parent
        anchors.leftMargin: 10
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
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
