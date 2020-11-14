import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    id: root

    ColumnLayout {
        anchors.fill: parent

        TextField {
            Layout.fillWidth: true
            text: person_surname
        }
        TextField {
            Layout.fillWidth: true
            text: person_name
        }
        TextField {
            Layout.fillWidth: true
            text: person_middlename
        }
        TextField {
            Layout.fillWidth: true
            text: person_position
        }
        TextField {
            Layout.fillWidth: true
            text: person_shift_num
        }
        TextField {
            Layout.fillWidth: true
            text: person_sectors_pool
        }
        TextField {
            Layout.fillWidth: true
            text: activity_pid
        }
        TextField {
            Layout.fillWidth: true
            text: activity_abbr
        }
        TextField {
            Layout.fillWidth: true
            text: activity_activity
        }
        TextField {
            Layout.fillWidth: true
            text: activity_color
        }
        TextField {
            Layout.fillWidth: true
            text: activity_note
        }
        TextField {
            Layout.fillWidth: true
            text: start_date
        }
        TextField {
            Layout.fillWidth: true
            text: end_date
        }
        TextField {
            Layout.fillWidth: true
            text: duration
        }
        TextField {
            Layout.fillWidth: true
            text: note
        }
        Item {
            id: spacing
            Layout.fillHeight: true
        }
    }
}
