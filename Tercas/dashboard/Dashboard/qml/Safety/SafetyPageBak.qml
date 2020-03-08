import QtQuick 2.9
import QtQuick.Controls 2.2

ListView {
    anchors.fill: parent
    anchors.topMargin: 10
    model: mainMenuModel
    spacing: 10
    delegate: ItemDelegate {
        width: ListView.view.width
        height: button.height

        RoundButton {
            id: button
            width: parent.width - 20
            anchors.horizontalCenter: parent.horizontalCenter
            radius: 10
            text: title
            contentItem: Label {
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                text: button.text
                font.pixelSize: 16
                font.bold: true
                color: "white"
            }
            background: Rectangle {
                implicitWidth: 150
                implicitHeight: 50
                radius: 10
                color: "lightblue"
            }
        }
    }

    ListModel {
        id: mainMenuModel
        ListElement { title: qsTr("Статистика") }
        ListElement { title: qsTr("Персонал") }
        ListElement { title: qsTr("Рабочее время") }
    }
}
