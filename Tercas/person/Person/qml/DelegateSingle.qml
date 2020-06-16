import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    id: root

    ColumnLayout {
        anchors.fill: parent

        TextField {
            Layout.fillWidth: true
            text: surname
        }
        TextField {
            Layout.fillWidth: true
            text: model.name
        }
        TextField {
            Layout.fillWidth: true
            text: middlename
        }
        TextField {
            Layout.fillWidth: true
            text: birthday
        }
        TextField {
            Layout.fillWidth: true
            text: mobile_phone
        }
        TextField {
            Layout.fillWidth: true
            text: tab_num
        }
        TextField {
            Layout.fillWidth: true
            text: position
        }
        TextField {
            Layout.fillWidth: true
            text: model.class
        }
        TextField {
            Layout.fillWidth: true
            text: shift_num
        }
        TextField {
            Layout.fillWidth: true
            text: sectors_pool
        }
        TextField {
            Layout.fillWidth: true
            text: service_period
        }
        TextField {
            Layout.fillWidth: true
            text: admission
        }
        TextField {
            Layout.fillWidth: true
            text: note
        }
    }
}
