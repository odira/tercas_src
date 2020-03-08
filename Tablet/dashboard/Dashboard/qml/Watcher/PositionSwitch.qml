import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Item {
    RowLayout {
        id: positionSwitch

        Label {
            anchors.verticalCenter: parent.verticalCenter
            text: qsTr("РЛУ")
        }
        Switch {
            anchors.verticalCenter: parent.verticalCenter
        }
        Label {
            anchors.verticalCenter: parent.verticalCenter
            text: qsTr("ПК")
        }
    }
}
