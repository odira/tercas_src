import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

RowLayout {

    property string backgroundColor: '#FA6E4F'
    property string fontColor: 'white'
    property int fontSize: 14

    TextField {
        Layout.preferredWidth: 50
        Layout.fillWidth: true
        Layout.fillHeight: true
        text: qsTr('Дата')
        font.bold: true
        font.pixelSize: fontSize
        color: fontColor
        horizontalAlignment: TextField.AlignHCenter
        background: Rectangle {
            color: backgroundColor
            border.color: 'pink'
        }
    }
    TextField {
        Layout.preferredWidth: 150
        Layout.fillWidth: true
        Layout.fillHeight: true
        text: qsTr('Календарный день')
        font.bold: true
        font.pixelSize: fontSize
        color: fontColor
        horizontalAlignment: TextField.AlignHCenter
        background: Rectangle {
            color: backgroundColor
            border.color: 'pink'
        }
    }
    TextField {
        Layout.preferredWidth: 200
        Layout.fillWidth: true
        Layout.fillHeight: true
        text: qsTr('Примечание')
        font.bold: true
        font.pixelSize: fontSize
        color: fontColor
        horizontalAlignment: TextField.AlignHCenter
        background: Rectangle {
            color: backgroundColor
            border.color: 'pink'
        }
    }

}
