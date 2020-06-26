import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

RowLayout {

    TextField {
        Layout.preferredWidth: 50
        Layout.fillWidth: true
        Layout.fillHeight: true
        text: qsTr('Дата')
        font.bold: true
        horizontalAlignment: TextField.AlignHCenter
        background: Rectangle {
            color: 'lightblue'
            border.color: 'pink'
        }
    }
    TextField {
        Layout.preferredWidth: 150
        Layout.fillWidth: true
        Layout.fillHeight: true
        text: qsTr('Календарный день')
        horizontalAlignment: TextField.AlignHCenter
        background: Rectangle {
            color: 'lightblue'
            border.color: 'pink'
        }
    }
    TextField {
        Layout.preferredWidth: 200
        Layout.fillWidth: true
        Layout.fillHeight: true
        text: qsTr('Примечание')
        horizontalAlignment: TextField.AlignHCenter
        background: Rectangle {
            color: 'lightblue'
            border.color: 'pink'
        }
    }

}
