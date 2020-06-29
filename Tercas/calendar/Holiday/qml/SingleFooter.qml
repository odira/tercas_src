import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

RowLayout {
    Layout.alignment: Qt.AlignHCenter

    RoundButton {
        id: editButton
        Layout.fillHeight: true
        Layout.preferredWidth: 150
        radius: 0
        text: qsTr('Edit')
        font.bold: true

        onClicked: edit()

        background: Rectangle {
            color: '#F45104'
            border.color: 'pink'
        }
    }
    RoundButton {
        id: saveButton
        Layout.fillHeight: true
        Layout.preferredWidth: 150
        radius: 0
        text: qsTr('Save')
        font.bold: true

        onClicked: save()

        background: Rectangle {
            color: '#F45104'
            border.color: 'pink'
        }
    }
    RoundButton {
        id: discardButton
        Layout.fillHeight: true
        Layout.preferredWidth: 150
        radius: 0
        text: qsTr('Discard')
        font.bold: true

        onClicked: discard()

        background: Rectangle {
            color: '#F45104'
            border.color: 'pink'
        }
    }
}
