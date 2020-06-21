import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import ColumnsEnum 1.0

Item {
    RowLayout {
        anchors.fill: parent

        TextField {
            Layout.preferredWidth: 200
            Layout.fillWidth: true
            Layout.fillHeight: true
            text: person_surname
            font.bold: true
            background: Rectangle {
                border.color: 'pink'
            }
        }
        TextField {
            Layout.preferredWidth: 150
            Layout.fillWidth: true
            Layout.fillHeight: true
            text: person_name
            background: Rectangle {
                border.color: 'pink'
            }
        }
        TextField {
            Layout.preferredWidth: 150
            Layout.fillWidth: true
            Layout.fillHeight: true
            text: person_middlename
            background: Rectangle {
                border.color: 'pink'
            }
        }
        TextField {
            Layout.preferredWidth: 200
            Layout.fillWidth: true
            Layout.fillHeight: true
            text: person_position
            background: Rectangle {
                border.color: 'pink'
            }
        }
        TextField {
            Layout.preferredWidth: 40
            Layout.fillWidth: true
            Layout.fillHeight: true
            text: person_shift_num
            horizontalAlignment: TextField.AlignHCenter
            background: Rectangle {
                border.color: 'pink'
            }
        }
        TextField {
            Layout.preferredWidth: 250
            Layout.fillWidth: true
            Layout.fillHeight: true
            text: person_sectors_pool
            background: Rectangle {
                border.color: 'pink'
            }
        }
        TextField {
            Layout.preferredWidth: 50
            Layout.fillWidth: true
            Layout.fillHeight: true
            font.bold: true
            text: activity_abbr
            horizontalAlignment: TextField.AlignHCenter
            background: Rectangle {
                border.color: model.activity_color
                color: model.activity_color
            }
        }
        TextField {
            Layout.preferredWidth: 150
            Layout.fillWidth: true
            Layout.fillHeight: true
            text: activity_activity
            background: Rectangle {
                border.color: 'pink'
            }
        }
        TextField {
            Layout.preferredWidth: 150
            Layout.fillWidth: true
            Layout.fillHeight: true
            text: start_date.toLocaleDateString(Qt.locale("ru_RU"), "dd MMMM yyyy")
            background: Rectangle {
                border.color: 'pink'
            }
        }
        TextField {
            Layout.preferredWidth: 150
            Layout.fillWidth: true
            Layout.fillHeight: true
            text: end_date.toLocaleDateString(Qt.locale("ru_RU"), "dd MMMM yyyy")
            background: Rectangle {
                border.color: 'pink'
            }
        }
        TextField {
            Layout.preferredWidth: 40
            Layout.fillWidth: true
            Layout.fillHeight: true
            text: duration
            horizontalAlignment: TextField.AlignHCenter
            background: Rectangle {
                border.color: 'pink'
            }
        }
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            listView.currentIndex = index
            showSingle()
        }
    }
}


//    border.color: {
////        if (column === ColumnsEnum.Column_activity_abbr)
////            return activity_color;
//        return "pink";
//    }
//    color: {
////        if (column === ColumnsEnum.Column_activity_abbr) {
////            return activity_color;
////        }
////        else
//            return "transparent";
//    }
//    Text {
//        anchors.fill: parent
//        anchors.leftMargin: 10
//        horizontalAlignment: Text.AlignLeft
//        verticalAlignment: Text.AlignVCenter
//        text: {
////            if (column === 13)
////                return start_date.toLocaleDateString(Qt.locale("ru_RU"), "dd MMMM yyyy");
////            else if (column === 14)
////                return end_date.toLocaleDateString(Qt.locale("ru_RU"), "dd MMMM yyyy");
////            else
//                return display;
//        }
//    }
