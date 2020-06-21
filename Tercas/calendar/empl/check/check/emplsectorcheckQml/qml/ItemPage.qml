import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Page {
    id: root

    property int row

    header: ToolBar {
        ToolButton {
            contentItem: Rectangle {
                width: 20
                height: 20
                anchors.left: parent.left
                anchors.leftMargin: 20
                color: "transparent"
                Image {
                    anchors.fill: parent
                    rotation: 180
                    source: "qrc:arrowImage"
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: root.StackView.view.pop()
                }
            }
        }
        Label {
            anchors.centerIn: parent
            font.pixelSize: 16
            text: qsTr("Данные по проверке ") + emplSectorCheckModel.get(row).personfullname + qsTr(" на секторе ") + emplSectorCheckModel.get(row).sectorlabel
        }
    }

    ColumnLayout {
        id: column

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: 20
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        spacing: 10

        Label {
            id: personfullname
            font.pixelSize: 16
            font.bold: true
            text: emplSectorCheckModel.get(row).personfullname
        }
        Label {
            id: sectorlabel
            font.pixelSize: 12
            font.bold: true
            color: "green"
            text: emplSectorCheckModel.get(row).sectorlabel
        }
        Label {
            id: sectorcheck
            font.pixelSize: 12
            text: emplSectorCheckModel.get(row).sectorcheck
        }
        Label {
            id: date
            font.pixelSize: 12
            color: "blue"
            text: Qt.formatDate(emplSectorCheckModel.get(row).date, "dd MMMM yyyy")
        }
    }

    footer: ToolBar {
        Label {
            anchors.centerIn: parent
            font.pixelSize: 16
            text: qsTr("Footer")
        }
    }
}
