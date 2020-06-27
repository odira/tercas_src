import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

RowLayout {
    Layout.alignment: Qt.AlignHCenter

    RoundButton {
        id: addButton
        Layout.fillHeight: true
        Layout.preferredWidth: 150
        radius: 0
        text: qsTr('Add Item')
        font.bold: true

        onClicked: addItem()

        background: Rectangle {
            color: '#F45104'
            border.color: 'pink'
        }
    }

}
