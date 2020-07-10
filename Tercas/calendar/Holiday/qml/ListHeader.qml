import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

RowLayout {

    TextField {
        Layout.preferredWidth: parent.width * 1/8
        Layout.fillWidth: true
        Layout.fillHeight: true
        text: qsTr('Дата')
    }
    TextField {
        Layout.preferredWidth: parent.width * 3/8
        Layout.fillWidth: true
        Layout.fillHeight: true
        text: qsTr('Календарный день')
    }
    TextField {
        Layout.preferredWidth: parent.width * 4/8
        Layout.fillWidth: true
        Layout.fillHeight: true
        text: qsTr('Примечание')
    }

}
