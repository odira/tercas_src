import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

RowLayout {
    Layout.alignment: Qt.AlignHCenter

    property color buttonBackground: "#8EC9BB"

    RoundButton {
        id: addButton
        Layout.fillHeight: true
        Layout.preferredWidth: 150
        radius: 0
        text: qsTr('Add Item')
        font.bold: true

        onClicked: addItem()

        background: Rectangle {
            color: buttonBackground
            border.color: 'pink'
        }
    }
    RoundButton {
        id: deleteButton
        Layout.fillHeight: true
        Layout.preferredWidth: 150
        radius: 0
        text: qsTr('Delete Item')
        font.bold: true

        onClicked: deleteItem()

        background: Rectangle {
            color: buttonBackground
            border.color: 'pink'
        }
    }

}
